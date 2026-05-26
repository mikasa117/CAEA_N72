/*
 * @Author: BlueboxChamil
 * @Date: 2026-01-16 14:34:58
 * @LastEditTime: 2026-01-30 11:32:31
 * @FilePath: \examples\application\btdm_audio\Src\my_es8389.h
 * @Description:
 * Copyright (c) 2026 by BlueboxChamil, All Rights Reserved.
 *
 * Modification:
 *  1, 20260401  chuzewei   Deletes those codes on the external flash is25lp040e
 *                          because of not using it.
 */
#ifndef __AUDIO_CODEC_H__
#define __AUDIO_CODEC_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "driver_gpio.h"
#include "driver_i2c.h"
#include "FreeRTOS.h"
#include "task.h"

#include "codec_es8389.h"

//#include "fal.h"
#include "driver_iic_soft.h"
#include "audio_common.h"
#include "app_audio.h"

/*
 * using AEC_RB. Not use in default
 */
#define USING_AEC_RB    0

#define READ_FLASH_SIZE (4 * 1024)

// 在采样率16k，立体声，位深16时，1ms的音频个数是64bytes,目前假设300ms
#define AEC_RING_BUFF_SIZE (64 * 300) 

typedef struct
{
    uint32_t size;         // 音频大小
    uint32_t flash_offset; // 音频在flash中的偏移量
    uint32_t offset;       // 音频已读取的大小
    uint32_t play_offset;  // 音频已播放大小
} bt_tone_t;

typedef struct
{
    uint8_t id;           // 对应要播放的音频id
    uint8_t *buf;         // 缓存从flash读取的4k数据
    uint32_t read_offset; // 当前已使用4k缓存区的大小
} read_flash_4k_t;

void microphone_initialise(void);
void amplifier_initialise(void);
void enable_phone_mute(uint8_t mute);
void enable_media_mute(uint8_t mute);
void enable_amp_mute(uint8_t mute);
void set_audio_codec_volumn(uint8_t level);
void turn_on_audio_amp(uint8_t on);
void turn_on_audio_mic(uint8_t on);
void em_audio_write_reg(uint8_t reg, uint8_t val);
uint8_t em_audio_read_reg(uint8_t reg);
void em_set_pa_mute_delay(uint8_t delay);
void em_audio_enable_loopback(uint8_t on);
void em_audio_set_mic_gain(uint8_t val);

void my_es8389_init(void);
void regmap_write(uint8_t addr, uint8_t reg, uint8_t value);
void regmap_read(uint8_t addr, uint8_t reg, uint8_t *data);
void regmap_update_bits(uint8_t addr, uint8_t reg, uint8_t mask, uint8_t value);
void ussleep(uint32_t us);

void bt_tone_init();
void bt_tone_play(uint8_t id);
uint32_t read_flash_tone(uint8_t *data, uint32_t len);

#if (USING_AEC_RB == 1)
typedef struct
{
    uint16_t *buf;        // 环形数组
    uint16_t max_size;    // 环形数组最大大小
    uint16_t offset_size; // 设置aec延偏移量
    uint16_t w_idx;       // 写偏移量
    uint16_t r_idx;       // 读偏移量
    uint32_t count;       // 环形数组有效数据量
    bool is_initialized;// 首次读取时建立延迟偏移，完成后置true
} aec_ring_buff_t;

void aec_rb_init(aec_ring_buff_t *rb);
/*
 * This delay time ia automatic adaptable. 
 */
void aec_rb_set_delay(aec_ring_buff_t *rb, uint16_t new_delay);
uint16_t aec_rb_write(aec_ring_buff_t *rb, const uint16_t *p_input, uint16_t len);
uint16_t aec_rb_read(aec_ring_buff_t *rb, uint16_t *p_output, uint16_t len);
void aec_rb_reset(aec_ring_buff_t *rb);
#endif
#endif