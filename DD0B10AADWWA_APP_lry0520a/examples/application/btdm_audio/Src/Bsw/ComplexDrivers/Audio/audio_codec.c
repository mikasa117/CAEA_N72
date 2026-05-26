/*
 * @Author: BlueboxChamil
 * @Date: 2026-01-14 16:42:48
 * @LastEditTime: 2026-03-04 17:52:39
 * @FilePath: \examples\application\btdm_audio\Src\my_es8389.c
 * @Description:
 * Copyright (c) 2026 by BlueboxChamil, All Rights Reserved.
 */
#include "audio_codec.h"

#define DEBUG
#ifdef  DEBUG
#define dprint         printf
#else
#define dprint(...)
#endif 

/* Defines a flag that app mutes amplifier */
static uint8_t app_mute_amp = 0;

/* Defines a flag that battery voltage is 24V or 12V */
static uint8_t  gBatt_24V = 0;

/* Defines a delay time while pa is muted */
static uint8_t  mute_pa_delay = 50; // 50 ms

GPIO_InitTypeDef gpio_config;
//I2C_HandleTypeDef I2C1_Handle;

bt_tone_t bt_tone[2];
read_flash_4k_t read_4k;

// 单次读4k数据
uint8_t read_flash_4k_buf[READ_FLASH_SIZE];

static uint16_t aec_ring_buff[AEC_RING_BUFF_SIZE];

#if 0
/*
 * Function: Defines a task in which codec es8389 is initialised once.
 */
uint8_t codec_init_ok = 0;
static void audio_codec_task(void *arg)
{
    uint32_t curr_time = FREE_COUNTER_VALUE;
    printf("Fore: %u\r\n", curr_time);
    my_es8389_init();
    printf("After: %u\r\n", curr_time - FREE_COUNTER_VALUE);
    codec_init_ok = 1;
    
    /* Initialise once */
    vTaskDelete(NULL);
}

void audio_codec_task_init(void)
{
    xTaskCreate(audio_codec_task, 
                "audio_codec", 
                128, 
                NULL, 
                2, 
                NULL);
}
#endif

/* 
 * Function: Check battery voltage 
 * Author: chuzewei
 * Date:   2026/03/04
 */
void check_battery_voltage(void)
{
    __SYSTEM_GPIOD_CLK_ENABLE();
    gpio_config.Pin  = GPIO_PIN_11;
    gpio_config.Mode = GPIO_MODE_INPUT;
    gpio_config.Pull = GPIO_NOPULL;
    gpio_config.Alternate = GPIO_FUNCTION_0;
    gpio_init(GPIOD, &gpio_config);
    system_delay_us(5);
    gBatt_24V = gpio_read_pin(GPIOD, GPIO_PIN_11);
    dprint("Battery voltage is %d V.\r\n", (gBatt_24V ? 24 : 12));
}


/*
 * Function: Determine whether voltage of battery is 24V or not.
 * Return: 1: 24V.  0: 12V
 */
uint8_t battery_voltage_is_24V(void)
{
    return gBatt_24V;
}

/*
 * Function: Pull down the gpiob_0 to turn off microphone at power up system.
 * Author: chuzewei
 * Date: 2026/03/16
 */
void microphone_initialise(void)
{
    __SYSTEM_GPIOB_CLK_ENABLE();
    gpio_config.Pin = GPIO_PIN_0;
    gpio_config.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_config.Pull = GPIO_NOPULL;
    gpio_config.Alternate = GPIO_FUNCTION_0;
    gpio_init(GPIOB, &gpio_config);
    
    gpio_write_pin(GPIOB, GPIO_PIN_0, GPIO_PIN_CLEAR); // turns off MIC
    system_delay_us(5);
}

/*
 * Function: Pull up the gpiod_4 and gpiod_5 at power up in case of pop noise.
 * Author: chuzewei
 * Date: 2026/03/11
 */
void amplifier_initialise(void)
{
    app_mute_amp = 0;
    
    __SYSTEM_GPIOD_CLK_ENABLE();
    gpio_config.Pin = GPIO_PIN_4 | GPIO_PIN_5;
    gpio_config.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_config.Pull = GPIO_NOPULL;
    gpio_config.Alternate = GPIO_FUNCTION_0;
    gpio_init(GPIOD, &gpio_config);
    
    gpio_write_pin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET); // mute amp. GPIO_PIN_CLEAR
    system_delay_us(5);
    gpio_write_pin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET); // make amp stand-by. GPIO_PIN_CLEAR
}


void my_es8389_init(void)
{
    //uint32_t begin_time = FREE_COUNTER_VALUE;
    
    //GPIO_InitTypeDef gpio_config;
    // PA stanby and mute

    check_battery_voltage();
    
    /*
     * Notes: Init audio amplifier and microphone
     */
    amplifier_initialise();
    microphone_initialise();
    
    __SYSTEM_GPIOD_CLK_ENABLE();
    /* configure PB8~PB11 to I2S1 function */
    gpio_config.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
    gpio_config.Mode = GPIO_MODE_AF_PP;
    gpio_config.Pull = GPIO_PULLUP;
    gpio_config.Alternate = GPIO_FUNCTION_B;
    gpio_init(GPIOD, &gpio_config);
    
    user_i2c_init();
    es8389_init();
    // es8389_play_test();
    // es8389_mic_test();
    // es8389_init();
    dprint("my_es8389_init ok!\r\n");
}

void regmap_write(uint8_t addr, uint8_t reg, uint8_t value)
{
    iic_Write_handle(addr >> 1, reg, &value, 1);
}

void regmap_read(uint8_t addr, uint8_t reg, uint8_t *data)
{
    iic_Read_handle(addr >> 1, reg, data, 1);
}

void regmap_update_bits(uint8_t addr, uint8_t reg, uint8_t mask, uint8_t value)
{
    uint8_t old_val;
    uint8_t new_val;

    // 1. 先读出当前寄存器的值
    regmap_read(addr, reg, &old_val);

    // 2. 计算新值：保留 mask 之外的位，更新 mask 覆盖的位
    // 逻辑：(原值 清空掩码位) | (新值 取掩码位)
    new_val = (old_val & ~mask) | (value & mask);

    // 3. 只有当值确实发生变化时才写入，提高效率并减少总线占用
    if (old_val != new_val)
    {
        regmap_write(addr, reg, new_val);
    }
}

/*
 * Function: Set audio codec volumn.
 * Input params:   
 *     level: volumn level. range: [0, 14]. Default level is 5
 */

void set_audio_codec_volumn(uint8_t level)
{
    static uint8_t last_level = 20;
    uint8_t level_num = sizeof(es8389_vol_lut_16);
    
    if (last_level == level)
    {
        return;
    }
    //if (level > 14
    if (level >= level_num)
    {
        level = level_num - 1;
    }
    dprint("set_audio_codec_volumn@@level=%d, val=0x%X\r\n", level, es8389_vol_lut_16[level]);
    es8389_init_play_vol(es8389_vol_lut_16[level]);
    
    
    /*
     * Notes: When playing mp3, codec should be in mute state 
     *        once decrease volumn to zero.
     *        But this logic should be made by app.
     *
     * System is booted on, this function is called .
     * So, comment out the below mute/unmute in case of pop noise.
     */
    #if 0
    if (level == 0)
    {
        enable_media_mute(1);
    }
    else //if (last_level == 0)
    {
        enable_media_mute(0);
    }
    #endif
    last_level = level;
}

#if 0
/*
 * Function: Enable audio amp into standby state
 * Input params:
 *   @on. 1: Enable; 0: Disable
 */
void enable_amp_standby(uint8_t on)
{
    static uint8_t last_status = 2;
    
    if (last_status == on)
    {
        return;
    }
    
    if (on)
    {
        //pin Output high Level 
        gpio_write_pin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
        //system_delay_us(5000);
    }
    else
    {
        //pin Output low Level 
        gpio_write_pin(GPIOD, GPIO_PIN_4, GPIO_PIN_CLEAR); 
        //system_delay_us(5000); 
    }
    last_status = on ? 1 : 0;
}
#endif

/*
 * Function: Enable audio amplifier in mute mode.
 *           This function is called by app.
 * Input params:
 *   @on. 1: Enable; 0: Disable
 *
 */
void enable_amp_mute(uint8_t mute)
{
    static uint8_t last_status = 2;
    
    if (last_status == mute)
    {
        return;
    }
    
    last_status = mute ? 1 : 0;
    app_mute_amp = last_status;
    if (mute)
    {
        //pin Output high Level 
        gpio_write_pin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
        system_delay_us(5);
        gpio_write_pin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET); 
    }
    else
    {
        //pin Output low Level 
        gpio_write_pin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
        system_delay_us(5); 
        gpio_write_pin(GPIOD, GPIO_PIN_4, GPIO_PIN_CLEAR); 
        system_delay_us(5);
        gpio_write_pin(GPIOD, GPIO_PIN_5, GPIO_PIN_CLEAR);
    }
}

/*
 * Function: Turn on audio amp.
 *           Must enable amp in mute mode in prior to entering (exitting) standby state 
 *           avoiding POP noise.
 * Input params:
 *   @on. 1: Turn on; 0: Turn off
 */
 void turn_on_audio_amp(uint8_t on)
{
    static uint8_t last_status = 2;

    //dprint("turn_on_audio_amp: on = %d\r\n", on);
    if (app_mute_amp)
    {
        return;
    }
    
    if (last_status == on)
    {
        return;
    }
    
    last_status = (on ? 1 : 0);
    if (on)
    {
        //enable_amp_mute(1);
        gpio_write_pin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
        
        // FAE advise that should delay 50ms at least.
        //system_delay_us(mute_pa_delay * 1000); 
        system_delay_us(5); 
        
        //enable_amp_standby(0);
        gpio_write_pin(GPIOD, GPIO_PIN_4, GPIO_PIN_CLEAR); 
        system_delay_us(5);
        //enable_amp_mute(0);
        gpio_write_pin(GPIOD, GPIO_PIN_5, GPIO_PIN_CLEAR);
        //system_delay_us(30000);
    }
    else
    {
        //enable_amp_mute(1);
        gpio_write_pin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
        system_delay_us(5); 
        
        //enable_amp_standby(1);
        gpio_write_pin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
        //system_delay_us(30000);
    }
}

/*
 * FUNCTION: Control mic during a call.
 *  Input params:
 *  @on: 1: turn on; 0: turn off
 */
void turn_on_audio_mic(uint8_t on)
{
    static uint8_t last_status = 2;

    if (last_status == on)
    {
        return;
    }
    
    last_status = (on ? 1 : 0);
    gpio_write_pin(GPIOB, GPIO_PIN_0, ((on & 0x01) ? GPIO_PIN_SET : GPIO_PIN_CLEAR));
    system_delay_us(5);
}

#if 0
/* There is no requirement ! */
/*
* Function: Make phone mute
* Input params: 
*   en:  1: mute;        0: unmute
 */
void enable_phone_mute(uint8_t mute)
{
    static uint8_t last_status = 2;
    
    if (last_status == mute)
    {
        return;
    }
    
    last_status = (mute) ? 1 : 0;
    if (mute)
    {
        es8389_set_adc_mute(true);
        dprint("mute es8389 mic.\r\n");
    }
    else
    {
        es8389_set_adc_mute(false);
        dprint("unmute es8389 mic.\r\n");
    }
    
}
#endif


/*
 * Function : Make mute while playing mp3
 * Input params: 
 *   en:  1: mute;        0: unmute
 */
void enable_media_mute(uint8_t mute)
{
    static uint8_t last_status = 2;
    
    if (last_status == mute)
    {
        return;
    }
    
    last_status = (mute) ? 1 : 0;
    if (mute)
    {
        es8389_set_dac_mute(true);
        dprint("mute es8389 spk.\r\n");
    }
    else
    {
        es8389_set_dac_mute(false);
        dprint("unmute es8389 spk.\r\n");
    }
    
}

void ussleep(uint32_t us)
{
    // vTaskDelay(pdMS_TO_TICKS(ms));
    system_delay_us(us);
}

void em_audio_write_reg(uint8_t reg, uint8_t val)
{
    em_es8389_write(reg, val);
    dprint("em_audio_write_reg@@reg: 0x%x, val: 0x%x\r\n", reg, val);
}

uint8_t em_audio_read_reg(uint8_t reg)
{
    uint8_t val;
    val = em_es8389_read(reg);
    dprint("em_audio_read_reg@@reg: 0x%x, val: 0x%x\r\n", reg, val);
    return val;
}

void em_gpio_write_port(int group, int number, uint8_t val)
{
    GPIO_TypeDef* gpio_group[] = {GPIOA, GPIOB, GPIOC, GPIOD};
    uint16_t gpio_number[] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3,
                              GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7,
                              GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11,
                              GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};
    
    if ((group < 0 || group > 3) || (number < 0 || number > 15))
    {
        printf("em_gpio_write_port@@invalid params.\r\n");
        return;
    }
    /* gpio_read_pin(GPIO_TypeDef *GPIOx, uint16_t fu16_Pin) */
    //gpio_write_pin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
    gpio_write_pin(gpio_group[group], 
                   gpio_number[number], 
                   (val) ? GPIO_PIN_SET : GPIO_PIN_CLEAR);
    return;
}

int em_gpio_read_port(int group, int number)
{
    int val;
    GPIO_TypeDef* gpio_group[] = {GPIOA, GPIOB, GPIOC, GPIOD};
    uint16_t gpio_number[] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3,
                              GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7,
                              GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11,
                              GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};
    
    if ((group < 0 || group > 3) || (number < 0 || number > 15))
    {
        printf("em_gpio_read_port@@invalid params.\r\n");
        return -1;
    }
    /* gpio_read_pin(GPIO_TypeDef *GPIOx, uint16_t fu16_Pin) */
    val = (int)gpio_read_pin(gpio_group[group], gpio_number[number]);
    return val;
}

void em_set_pa_mute_delay(uint8_t delay)
{
    mute_pa_delay = delay;
}

void em_audio_enable_loopback(uint8_t on)
{
    //uint8_t val = 0x13;
    
    if (on)
    {
        em_es8389_write(0xF0, 0x1E);
        //turn_on_audio_mic(on & 0x01);
        es8389_mic_start();
        gpio_write_pin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
        turn_on_audio_amp(1);
    }
    else
    {
        turn_on_audio_amp(0);
        gpio_write_pin(GPIOB, GPIO_PIN_0, GPIO_PIN_CLEAR);
        es8389_mic_stop();
        em_es8389_write(0xF0, 0x1A);
    }
}

void em_audio_set_mic_gain(uint8_t val)
{
    es8389_init_mic_gain(val);
}


/**
 * @brief 配置蓝牙提示音的相关信息
 *
 */
void bt_tone_init()
{
    bt_tone[0].flash_offset = 0;
    bt_tone[0].offset = 0;
    bt_tone[0].play_offset = 0;
    bt_tone[0].size = 7776;

    bt_tone[1].flash_offset = 7776;
    bt_tone[1].offset = 0;
    bt_tone[1].play_offset = 0;
    bt_tone[1].size = 7920;

    read_4k.id = 0;
    read_4k.buf = read_flash_4k_buf;
    read_4k.read_offset = READ_FLASH_SIZE;
}

/**
 * @brief 播放bt提示音
 *
 * @param id 0：蓝牙已开机 1：蓝牙已连接
 */
void bt_tone_play(uint8_t id)
{
    read_4k.id = id;
    read_4k.read_offset = READ_FLASH_SIZE;
    bt_tone[read_4k.id].offset = 0;
    bt_tone[read_4k.id].play_offset = 0;

    app_audio_tone_play(AUDIO_TYPE_SBC, NULL, 0);
}

/**
 * @brief 用于处理flash读取音频数据以及音频播放
 *
 * @param data
 * @param len
 * @return uint32_t
 */
uint32_t read_flash_tone(uint8_t *data, uint32_t len)
{
    // 缓存区数据不足，从flash读数据到缓存区
    if (READ_FLASH_SIZE - read_4k.read_offset < len)
    {
        // printf("bt_tone[%d].offset = %d\r\n", read_4k.id, bt_tone[read_4k.id].offset);
        //IC_W25Qxx_Read_Data(read_4k.buf, bt_tone[read_4k.id].flash_offset + bt_tone[read_4k.id].offset, READ_FLASH_SIZE);
        bt_tone[read_4k.id].offset += READ_FLASH_SIZE;
        read_4k.read_offset = 0;
    }

    // 判断是否有足够的数据用于播放
    uint32_t vaild_size = bt_tone[read_4k.id].size - bt_tone[read_4k.id].play_offset;
    // printf("vaild_size = %d\r\n", vaild_size);
    if (vaild_size < len)
    {
        memcpy(data, &(read_4k.buf[read_4k.read_offset]), vaild_size);
        read_4k.read_offset += vaild_size;
        bt_tone[read_4k.id].play_offset += vaild_size;
        return vaild_size;
    }
    else
    {
        memcpy(data, &(read_4k.buf[read_4k.read_offset]), len);
        read_4k.read_offset += len;
        bt_tone[read_4k.id].play_offset += len;
        return len;
    }
}

#if (USING_AEC_RB == 1)
/**
 * @brief aec算法环形缓存初始化
 *
 * @param rb
 */
void aec_rb_init(aec_ring_buff_t *rb)
{
    rb->buf = aec_ring_buff;
    rb->max_size = AEC_RING_BUFF_SIZE;
    rb->w_idx = 0;
    rb->r_idx = 0;
    rb->count = 0;
    rb->is_initialized = false;

    memset(aec_ring_buff, 0, sizeof(aec_ring_buff));

    /* This delay time is automatic adaptable. */
    aec_rb_set_delay(rb, 4);
}

/**
 * @brief aec算法设置mic与spk的偏移量,是字节数
 *
 * @param rb
 * @param new_delay
 */
void aec_rb_set_delay(aec_ring_buff_t *rb, uint16_t new_delay)
{
    if (new_delay == 0)
        return;

    if (!rb->is_initialized)
    {
        rb->offset_size = new_delay;
        return;
    }

    // 偏移量增大，r_idx往前
    if (new_delay > rb->offset_size)
    {
        uint16_t delta = new_delay - rb->offset_size;
        rb->r_idx = (rb->r_idx + delta) % rb->max_size;
        rb->count -= delta;
    }
    // 偏移减小，r_idx回退
    else if (new_delay < rb->offset_size)
    {
        uint16_t delta = rb->offset_size - new_delay;

        if (delta > rb->count)
        {
            delta = rb->count;
        }

        rb->r_idx = (rb->r_idx - delta + rb->max_size) % rb->max_size;
        rb->count += delta;
    }

    rb->offset_size = new_delay;
}

/**
 * @brief 向aec环形数组写入数据
 *
 * @param rb
 * @param p_input
 * @param len
 * @return uint16_t
 */
uint16_t aec_rb_write(aec_ring_buff_t *rb, const uint16_t *p_input, uint16_t len)
{
    uint16_t free_space = rb->max_size - rb->count;
    if (len > free_space)
    {
        len = free_space;
    }

    uint16_t space_to_end = rb->max_size - rb->w_idx;

    if (len <= space_to_end)
    {
        memcpy(&rb->buf[rb->w_idx], p_input, len * sizeof(uint16_t));
    }
    else
    {
        memcpy(&rb->buf[rb->w_idx], p_input, space_to_end * sizeof(uint16_t));
        memcpy(&rb->buf[0], &p_input[space_to_end], (len - space_to_end) * sizeof(uint16_t));
    }

    rb->w_idx = (rb->w_idx + len) % rb->max_size;
    rb->count += len;

    return len;
}

/**
 * @brief 从aec环形数组读取数据
 *
 * @param rb
 * @param p_output
 * @param len
 * @return uint16_t
 */
uint16_t aec_rb_read(aec_ring_buff_t *rb, uint16_t *p_output, uint16_t len)
{
    // 首次读取，建立初始延迟偏移
    if (!rb->is_initialized)
    {
        // 缓存数据还不够，不符合读取条件
        if (rb->count < len + rb->offset_size)
        {
            return 0;
        }

        rb->r_idx = (rb->r_idx + rb->offset_size) % rb->max_size;
        rb->count -= rb->offset_size;
        rb->is_initialized = true;
    }

    if (rb->count < len + rb->offset_size) // 改动在这里
    {
        return 0;
    }

    uint16_t data_to_end = rb->max_size - rb->r_idx;

    if (len <= data_to_end)
    {
        memcpy(p_output, &rb->buf[rb->r_idx], len * sizeof(uint16_t));
    }
    else
    {
        memcpy(p_output, &rb->buf[rb->r_idx], data_to_end * sizeof(uint16_t));
        memcpy(&p_output[data_to_end], &rb->buf[0], (len - data_to_end) * sizeof(uint16_t));
    }

    rb->r_idx = (rb->r_idx + len) % rb->max_size;
    rb->count -= len;

    return len;
}

void aec_rb_reset(aec_ring_buff_t *rb)
{
    rb->w_idx = 0;
    rb->r_idx = 0;
    rb->count = 0;
    rb->is_initialized = false;
}
#endif

