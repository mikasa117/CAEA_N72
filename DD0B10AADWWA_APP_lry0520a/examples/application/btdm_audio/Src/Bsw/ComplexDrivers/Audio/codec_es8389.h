#ifndef __CODEC_ES8389_H__
#define __CODEC_ES8389_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "audio_codec.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

struct _coeff_div
{
    uint16_t Ratio;
    uint32_t MCLK;
    uint32_t LRCK;
    uint8_t Reg0x04;
    uint8_t Reg0x05;
    uint8_t Reg0x06;
    uint8_t Reg0x07;
    uint8_t Reg0x08;
    uint8_t Reg0x09;
    uint8_t Reg0x0A;
    uint8_t Reg0x0F;
    uint8_t Reg0x11;
    uint8_t Reg0x21;
    uint8_t Reg0x22;
    uint8_t Reg0x26;
    uint8_t Reg0x30;
    uint8_t Reg0x41;
    uint8_t Reg0x42;
    uint8_t Reg0x43;
    uint8_t Reg0xF0;
    uint8_t Reg0xF1;
    uint8_t Reg0x16;
    uint8_t Reg0x18;
    uint8_t Reg0x19;
};

#define ES8389_ADDR 0x20
#define  ES8389_ADDR_8BITS_24V     0x24  /*  0010 010 R|W BIT */
#define  ES8389_ADDR_8BITS_12V     0x20  /*  0010 000 R|W BIT */

#define ES8389_ID0_REG0xFD  0xFD
#define ES8389_ID1_REG0xFE  0xFE
#define ES8389_ID           0x8389
/*
 *   ES8389_REGISTER NAME_REG_REGISTER ADDRESS
 */
#define ES8389_RESET_REG0x00 0x00

/*
 *   ES8389 MISC CONTROL ADDRESS
 */
#define ES8389_MISC_CONTROL_REG0x01 0x01

/*
 * Clock Scheme Register definition
 */
#define ES8389_CLK_MANAGER_REG0x02 0x02
#define ES8389_CLK_MANAGER_REG0x03 0x03
#define ES8389_CLK_MANAGER_REG0x04 0x04
#define ES8389_CLK_MANAGER_REG0x05 0x05
#define ES8389_CLK_MANAGER_REG0x06 0x06
#define ES8389_CLK_MANAGER_REG0x07 0x07
#define ES8389_CLK_MANAGER_REG0x08 0x08
#define ES8389_CLK_MANAGER_REG0x09 0x09
#define ES8389_CLK_MANAGER_REG0x0A 0x0A
#define ES8389_CLK_MANAGER_REG0x0B 0x0B
#define ES8389_CLK_MANAGER_REG0x0C 0x0C
#define ES8389_CLK_MANAGER_REG0x0D 0x0D
#define ES8389_CLK_MANAGER_REG0x0E 0x0E
#define ES8389_CLK_MANAGER_REG0x0F 0x0F
#define ES8389_CLK_MANAGER_REG0x10 0x10
#define ES8389_CLK_MANAGER_REG0x11 0x11

/*
 * ADC SP CONTROL
 */
#define ES8389_ADC_SP_CONTROL_REG0x20 0x20
#define ES8389_ADC_SP_CONTROL_REG0x21 0x21
#define ES8389_ADC_SP_CONTROL_REG0x22 0x22
#define ES8389_ADC_SP_CONTROL_REG0x23 0x23
#define ES8389_ADC_SP_CONTROL_REG0x24 0x24
#define ES8389_ADC_SP_CONTROL_REG0x25 0x25
#define ES8389_ADC_SP_CONTROL_REG0x26 0x26
#define ES8389_ADC_SP_CONTROL_REG0x27 0x27
#define ES8389_ADC_SP_CONTROL_REG0x28 0x28
#define ES8389_ADC_SP_CONTROL_REG0x2A 0x2A
#define ES8389_ADC_SP_CONTROL_REG0x2F 0x2F
#define ES8389_ADC_SP_CONTROL_REG0x31 0x31

/*
 * ALC CONTROL
 */
#define ES8389_ALC_CONTROL_REG0x29 0x29
#define ES8389_ALC_CONTROL_REG0x2B 0x2B
#define ES8389_ALC_CONTROL_REG0x2C 0x2C
#define ES8389_ALC_CONTROL_REG0x2D 0x2D

/*
 * DAC SERIAL PORT CONTROL
 */
#define ES8389_DAC_CONTROL_REG0x40 0x40
#define ES8389_DAC_CONTROL_REG0x41 0x41
#define ES8389_DAC_CONTROL_REG0x42 0x42
#define ES8389_DAC_CONTROL_REG0x43 0x43
#define ES8389_DAC_CONTROL_REG0x44 0x44
#define ES8389_DAC_CONTROL_REG0x45 0x45
#define ES8389_DAC_CONTROL_REG0x46 0x46
#define ES8389_DAC_CONTROL_REG0x47 0x47
#define ES8389_DAC_CONTROL_REG0x48 0x48
#define ES8389_DAC_CONTROL_REG0x49 0x49
#define ES8389_DAC_CONTROL_REG0x4D 0x4D

/*
 * VMID CONTROL
 */

#define ES8389_VMID_CONTROL_REG0x60 0x60

/*
 * ANALOG ENABLE CONTROL
 */
#define ES8389_ANALOG_CONTROL_REG0x61 0x61
#define ES8389_ANALOG_CONTROL_REG0x62 0x62
#define ES8389_ANALOG_CONTROL_REG0x63 0x63
#define ES8389_ANALOG_CONTROL_REG0x64 0x64
#define ES8389_ANALOG_CONTROL_REG0x69 0x69
#define ES8389_ANALOG_CONTROL_REG0x6B 0x6B
#define ES8389_ANALOG_CONTROL_REG0x6C 0x6C
#define ES8389_ANALOG_CONTROL_REG0x6D 0x6D
#define ES8389_ANALOG_CONTROL_REG0x6E 0x6E
#define ES8389_ANALOG_CONTROL_REG0x6F 0x6F
#define ES8389_ANALOG_CONTROL_REG0x70 0x70
#define ES8389_ANALOG_CONTROL_REG0x71 0x71

/*
 *  PGA1 GAIN CONTROL
 */
#define ES8389_PGA1_GAIN_CONTROL_REG0x72 0x72
#define ES8389_PGA1_GAIN_CONTROL_REG0x73 0x73

/*
 *  CHIP MISC CONTROL
 */
#define ES8389_CHIP_MISC_CONTROL_REG0xF0 0xF0

/*
 *  CSM STATE REPORT
 */
#define ES8389_CSM_STATE_REG0xF1 0xF1

/*
 *  PULL DOWN CONTROL
 */
#define ES8389_PULL_DOWN_CONTROL_REG0xF2 0xF2

/*
 *   ISOLATION CONTROL
 */
#define ES8389_ISOLATION_CONTROL_REG0xF3 0xF3

/*
 *    CSM STATE CONTROL
 */
#define ES8389_CSM_STATE_CONTROL_REG0xF4 0xF4

/*
 *     CHIP ID1 ID2
 */
#define ES8389_CHIP_ID1_CONTROL_REG0xFD 0xFD
#define ES8389_CHIP_ID2_CONTROL_REG0xFE 0xFE

#define ES8389_MAX_REGISTER 0xFF

/* ES8389 Data Format Definition */
#define ES8389_DAIFMT_I2S (0 << 2)
#define ES8389_DAIFMT_LEFT_J (1 << 2)
#define ES8389_DAIFMT_DSP_A (1 << 3)
#define ES8389_DAIFMT_DSP_B (3 << 3)

/* ES8389 Data length Definition */
#define ES8389_S24_LE (0 << 5)
#define ES8389_S20_LE (1 << 5)
#define ES8389_S18_LE (2 << 5)
#define ES8389_S16_LE (3 << 5)
#define ES8389_S32_LE (4 << 5)

/* ALSA call function used */
#define ES8389_MASK_MSModeSel (1 << 0)
#define ES8389_MASK_LRCKINV (1 << 4)
#define ES8389_MASK_SCLKINV (1 << 0)
#define ES8389_MASK_DATALEN (7 << 5)
#define ES8389_MASK_DAIFMT (7 << 2)

#define ES8389_MIC_SEL_MASK (7 << 4)
#define ES8389_MIC_DEFAULT (1 << 4)

#define ES8389_MASTER_MODE_EN (1 << 0)

#define ES8389_TDM_OFF (0 << 0)
#define ES8389_STDM_ON (1 << 7)
#define ES8389_PTDM_ON (1 << 6)

#define ES8389_TDM_MODE ES8389_TDM_OFF
#define ES8389_TDM_SLOT (0x70 << 0)
#define ES8389_TDM_SHIFT 4

#define ES8389_MCLK_SOURCE (1 << 6)
#define ES8389_MCLK_PIN (1 << 6)
#define ES8389_SCLK_PIN (0 << 6)

#define ES8389_STATE_ON (13 << 0)
#define ES8389_STATE_STANDBY (7 << 0)

////////////////////////////////////////////////////
#define ES8389_DriveSel_Normal 0
#define ES8389_DriveSel_LowPower 1
#define ES8389_DriveSel_HeadPhone 2

#define ES8389_Analog_DriveSel ES8389_DriveSel_Normal /* Normal;LowPower;HeadPhone */

typedef enum
{
    ES_I2S_MIN = -1,
    ES_I2S_NORMAL = 0,
    ES_I2S_LEFT = 1,
    ES_I2S_RIGHT = 2,
    ES_I2S_DSP = 3,
    ES_I2S_MAX
} es_i2s_fmt_t;

typedef enum
{
    ES8389_MIC_GAIN_0DB,
    ES8389_MIC_GAIN_3_5DB,
    ES8389_MIC_GAIN_6_5DB,
    ES8389_MIC_GAIN_9_5DB,
    ES8389_MIC_GAIN_12_5DB = 6,
    ES8389_MIC_GAIN_15_5DB,
    ES8389_MIC_GAIN_18_5DB,
    ES8389_MIC_GAIN_21_5DB,
    ES8389_MIC_GAIN_24_5DB,
    ES8389_MIC_GAIN_27_5DB,
    ES8389_MIC_GAIN_30_5DB,
    ES8389_MIC_GAIN_33_5DB,
    ES8389_MIC_GAIN_36_5DB
} es8389_mic_gain_t;

typedef enum
{
    ES8389_STANDY,       // 待机模式
    ES8389_MIC,          // 仅录音模式
    ES8389_PLAY,         // 仅播放模式
    ES8389_PLAY_AND_MIC, // 录音+播放模式
    ES8389_LOOP,         // mic输入扬声器直接输出仅用于测试
} es8389_mode_e;

typedef struct
{
    uint32_t now_sample_rate;
    es8389_mode_e mode; // 当前工作模式

} user_es8389_info_t;

//////////////////用户使用/////////////////////////
extern const uint8_t es8389_vol_lut_16[16];

void es8389_init(void);
void es8389_play_init(uint32_t sample_rate);
void es8389_mic_init(uint32_t sample_rate);
void es8389_play_and_mic_init(uint32_t sample_rate);
void es8389_standby_init(void);
void es8389_loop_init(uint32_t sample_rate);

void es8389_play_start(void);
void es8389_play_stop(void);
void es8389_mic_start(void);
void es8389_mic_stop(void);
void es8389_loop_start(void);
void es8389_loop_stop(void);

void es8389_read_all_reg(void);
void es8389_init_play_vol(uint8_t vol);
void es8389_init_mic_gain(uint8_t gain_db);
void es8389_set_adc_mute(bool mute);
void es8389_set_dac_mute(bool mute);
void em_es8389_write(uint8_t reg, uint8_t val);
uint8_t em_es8389_read(uint8_t reg);

//////////////////驱动部分/////////////////////////
static void es8389_open(void);
static void es8389_config_sample(int sample_rate, int bits);
static void es8389_set_bits_per_sample(int bits);
static void es8389_config_fmt(es_i2s_fmt_t fmt);
static void es8389_set_bias(bool ret);
static void es8389_set_bias_standby(void);
static void es8389_set_bias_on(void);
static void es8389_set_vol(uint8_t vol);
static void es8389_set_mic_gain(es8389_mic_gain_t gain_db);
static int get_coeff(uint32_t mclk, uint32_t rate);
static void es8389_set_config(es8389_mode_e mode, uint32_t sample_rate);
static void print_es8389_mode(es8389_mode_e mode);
static void es8389_init_config(es8389_mode_e mode, uint32_t sample_rate);
#endif