/*
 * @Author: liuranyang liuranyang@cncaea.cn
 * @Date: 2026-01-28 15:15:31
 * @LastEditors: liuranyang liuranyang@cncaea.cn
 * @LastEditTime: 2026-03-18 14:39:07
 * @FilePath: \FR30xxC-SDK-v0.3.1\examples\application\btdm_audio\Src\Bsw\Mcal_If\adc_if\adc_if.c
 * @Description: 默认设置
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "adc_if.h"
#include "btdm_mem.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define ADC_IF_DEBUG  (0u)

// 任务配置
#define ADC_IF_PROCESS_TASK_PRIO     2       // 处理任务优先级
#define ADC_IF_PROCESS_TASK_STACK    256     // 处理任务栈大小

// 队列配置
QueueHandle_t xADQueue;                 // AD 采样值队列句柄
#define AD_QUEUE_LENGTH         20      // 队列长度（缓存最近20个采样值）
#define AD_QUEUE_ITEM_SIZE      sizeof(uint16_t) // 队列项大小

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static BaseType_t xHighPriorityTaskWoken = pdFALSE;

static adc_if_map_t adc_map[adc_cl_max] = 
{
    {adc_cl_bat,       SARADC_CHANNEL_0, ADC_CH_MAP_PMU_IO3 },
    {adc_cl_acc,       SARADC_CHANNEL_1, ADC_CH_MAP_PMU_IO4 },
    {adc_cl_msw_l,     SARADC_CHANNEL_2, ADC_CH_MAP_PORTD_13},
    {adc_cl_msw_r,     SARADC_CHANNEL_3, ADC_CH_MAP_PORTD_14},
    {adc_cl_mic_8v_cs, SARADC_CHANNEL_4, ADC_CH_MAP_PORTD_15},
};

static adc_if_struct adcf[adc_cl_max];
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* ========================================================================== */
/*                        Application Local Functions                         */
/* ========================================================================== */

/**
 * @description: 初始化ADC硬件
 * @return {*}
 */
static void adc_if_hw_init(void)
{
    saradc_InitConfig_t * InitConfig;
    saradc_LoopConfig_t * LoopConfig;

    /* ADC Power on */
    pmu_adc_power_ctrl(ADC_IF_TRUE);
    /* ADC clock enable */
    __SYSTEM_ADC_CLK_ENABLE();

    //gpio_write_pin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	
    pmu_set_pin_dir(PMU_PIN_2, PMU_GPIO_MODE_INPUT);
    pmu_set_pin_pull(PMU_PIN_2, PMU_GPIO_NO_PULL);

    pmu_set_pin_dir(PMU_PIN_4, PMU_GPIO_MODE_INPUT);
    pmu_set_pin_pull(PMU_PIN_4, PMU_GPIO_NO_PULL);

    InitConfig = btdm_malloc(sizeof(saradc_InitConfig_t));
    LoopConfig = btdm_malloc(sizeof(saradc_LoopConfig_t));

    InitConfig->saradc_reference = SARADC_REF_IOLDO;
    InitConfig->saradc_sampling_cycle = 16;
    InitConfig->saradc_clock_div = 24;              // 24M/24 = 1M
    InitConfig->saradc_interval_clock_div = 10;     // 1M/10  = 100K
    InitConfig->saradc_voltage_divider = SARADC_VOLTAGE_DIVIDER_BYPASS;
    InitConfig->saradc_mode = SARADC_LOOP_MODE;
    saradc_init(InitConfig);

    LoopConfig->loop_triggerMode = SARADC_TRIGGER_HARDWARE;
    LoopConfig->loop_max_channel = 5;
    LoopConfig->loop_interval = 4000;    // interval 40ms
    LoopConfig->loop_FIFO_enable = SARADC_FIFO_DISABLE;
    saradc_loop_config(LoopConfig);

    for (int i = 0; i < sizeof(adc_map) / sizeof(adc_if_map_t); i++)
    {
        saradc_channel_single_config(adc_map[i].saradc_channel, adc_map[i].adc_channel_map);
    }
    
    saradc_loop_convert_start();

    saradc_int_enable(SARADC_INT_STATUS_LOOP);
    NVIC_EnableIRQ(SARADC_IRQn);
}


/**
 * @description: 计算平均值
 * @param {uint16_t} *pData
 * @param {uint8_t} length
 * @return {*}
 */
static uint16_t adc_if_calculateAverage(const uint16_t *pData, uint8_t length)
{
    uint8_t  i;
    uint32_t e_dw_sum = (uint32_t)0u;
    uint16_t e_w_average = (uint16_t)0u;

    if( ( length > (uint8_t)0u ) && ( length < 0xFFu ) )
    {
        for( i = (uint8_t)0u; i < length; i++ )
        {
            e_dw_sum += pData[i];
        }
        e_w_average = (uint16_t)( e_dw_sum / length );
    }

    return (e_w_average);
}

/**
 * @description: 处理AD采样值任务
 * @param {void} *pvParameters
 * @return {*}
 */
void vADProcessTask(void *pvParameters)
{
    uint8_t ucChannal = 0u;
    uint16_t ad_value, validValue;

    while (1)
    {
        if (xQueueReceive(xADQueue, &ad_value, portMAX_DELAY) == pdPASS)
        {
            // 处理AD采样值
            adc_if_struct * const pAdcF = &adcf[ucChannal];
            pAdcF->e_w_currentValue	= ad_value;
            pAdcF->e_w_buff[pAdcF->e_u_index] = ad_value;
            if ( pAdcF->e_u_index >= (pAdcF->e_u_collectNum - (uint8_t)1u) )
            {
                pAdcF->e_u_index = 0u;
                pAdcF->e_u_flag = ADC_IF_TRUE;
            }
            else
            {
                pAdcF->e_u_index++;
            }

            if ( ADC_IF_TRUE == pAdcF->e_u_flag )
            {
                validValue = adc_if_calculateAverage(&(pAdcF->e_w_buff[0u]), (pAdcF->e_u_collectNum));
            }
            else
            {
                validValue = adc_if_calculateAverage(&(pAdcF->e_w_buff[0u]), (pAdcF->e_u_index));
            }
            taskENTER_CRITICAL();
            pAdcF->e_w_validValue = validValue;
            taskEXIT_CRITICAL();

            ucChannal++;
            if (ucChannal >= adc_cl_max)
            {
                ucChannal = 0u;
            }
        }
    }
}

#if ADC_IF_DEBUG
void vADTestTask(void *pvParameters)
{
    uint16_t ad_value;
    uint8_t reg;
    while(1) {
        vTaskDelay(pdMS_TO_TICKS(500u));
        ad_value = adc_if_get_validValue(adc_cl_bat);
        printf("adc bat: %d\r\n", ad_value);
        printf("ad val 1: %d, %d, %d, %d\r\n", adcf[adc_cl_bat].e_w_buff[0], adcf[adc_cl_bat].e_w_buff[1], adcf[adc_cl_bat].e_w_buff[2], adcf[adc_cl_bat].e_w_buff[3]);
        ad_value = adc_if_get_validValue(adc_cl_acc);
        printf("adc acc: %d\r\n", ad_value);
        ad_value = adc_if_get_validValue(adc_cl_msw_l);
        printf("adc msw_l: %d\r\n", ad_value);
        ad_value = adc_if_get_validValue(adc_cl_msw_r);
        printf("adc msw_r: %d\r\n", ad_value);
        ad_value = adc_if_get_validValue(adc_cl_mic_8v_cs);
        printf("adc mic_8v_cs: %d\r\n", ad_value);

        reg = ool_read(0x4A);
        printf("reg 0x4A: 0x%x\r\n", reg);
        reg = ool_read(0x48);
        printf("reg 0x48: 0x%x\r\n", reg);
        reg = ool_read(0x46);
        printf("reg 0x46: 0x%x\r\n", reg);
        reg = ool_read(0x44);
        printf("reg 0x44: 0x%x\r\n", reg);
    }
}
#endif

/**
 * @description: call from main
 * @return {*}
 */
void adc_if_init(void)
{
    TaskHandle_t xADProcessTaskHandle;      // 处理任务句柄
    #if ADC_IF_DEBUG
    TaskHandle_t xADTestTaskHandle;        // 测试任务句柄
    #endif
    uint8_t ucChannal;

    // 1. 创建AD采样值消息队列（不变）
    xADQueue = xQueueCreate(AD_QUEUE_LENGTH, AD_QUEUE_ITEM_SIZE);
    if (xADQueue == NULL)
    {
        while (1); // 队列创建失败，卡死
    }

    // 3. 创建AD按键处理任务
    xTaskCreate(vADProcessTask, "AD_Process_Task", ADC_IF_PROCESS_TASK_STACK, NULL, ADC_IF_PROCESS_TASK_PRIO, &xADProcessTaskHandle);
    if (xADProcessTaskHandle == NULL)
    {
        // 任务创建失败，添加错误处理
        while (1);
    }

    for(ucChannal = 0u; ucChannal < (uint8_t)(adc_cl_max); ucChannal++)
    {
        adcf[ucChannal].e_u_flag = ADC_IF_FALSE;
        adcf[ucChannal].e_u_index = 0u;
        adcf[ucChannal].e_u_collectNum = ADC_IF_COLLECT_MAX_NUM;
        memset(adcf[ucChannal].e_w_buff, 0u, sizeof(adcf[ucChannal].e_w_buff));
    }

    adc_if_hw_init();

#if ADC_IF_DEBUG
    xTaskCreate(vADTestTask, "AD_Test_Task", 256, NULL, 2, &xADTestTaskHandle);
#endif
}

/**
 * @description: SARADC中断处理函数
 * @return {*}
 */
void saradc_irq(void)
{
    if (saradc_get_int_raw_status() & SARADC_INT_STATUS_LOOP)
    {
        uint16_t ad_value;
        for (int i = 0; i < adc_cl_max; i++)
        {
            ad_value = saradc_get_channel_data(adc_map[i].saradc_channel);
            xQueueSendFromISR(xADQueue, &ad_value, &xHighPriorityTaskWoken);
        }
        portYIELD_FROM_ISR(xHighPriorityTaskWoken);
        saradc_int_status_clear(SARADC_INT_STATUS_LOOP);
    }
}

/**
 * @description: 获取AD采样值任务处理结果
 * @param {uint8_t} ucChannel
 * @return {*}
 */
uint16_t adc_if_get_validValue(uint8_t ucChannel)
{
    uint16_t validValue = 0xFFFFu;
    if (ucChannel < adc_cl_max)
    {
        taskENTER_CRITICAL();
        validValue = adcf[ucChannel].e_w_validValue;
        taskEXIT_CRITICAL();
    }
    return validValue;
}

/**
 * @description: 获取AD采样值任务处理结果
 * @param {uint8_t} ucChannel
 * @return {*}
 */
uint16_t adc_if_get_currValue(uint8_t ucChannel)
{
    uint16_t currValue = 0xFFFFu;
    if (ucChannel < adc_cl_max)
    {
        taskENTER_CRITICAL();
        currValue = adcf[ucChannel].e_w_currentValue;
        taskEXIT_CRITICAL();
    }
    return currValue;
}
/*EoF*/