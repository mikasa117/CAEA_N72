/*
 * @Author: liuranyang liuranyang@cncaea.cn
 * @Date: 2026-01-28 15:15:43
 * @LastEditors: liuranyang liuranyang@cncaea.cn
 * @LastEditTime: 2026-02-04 13:56:50
 * @FilePath: \FR30xxC-SDK-v0.3.1\examples\application\btdm_audio\Src\Bsw\Mcal_If\adc_if\adc_if.h
 * @Description: 默认设置
 */

#ifndef __ADC_IF_H__
#define __ADC_IF_H__

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "fr30xx.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ADC_IF_TRUE    (bool)(1u)
#define ADC_IF_FALSE   (bool)(0u)

#define	ADC_IF_COLLECT_MAX_NUM    (uint8_t)(4u)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef enum adc_if_cl_s
{
    adc_cl_bat = 0,
    adc_cl_acc = 1,
    adc_cl_msw_l = 2,
    adc_cl_msw_r = 3,
    adc_cl_mic_8v_cs = 4,
    adc_cl_max,
} adc_if_cl_t;

typedef struct adc_if_map_s 
{
    adc_if_cl_t adc_cl;
    enum_saradc_channel_t saradc_channel;
    enum_ADC_Channel_Map_t adc_channel_map;
} adc_if_map_t;

typedef	struct
{
    uint16_t e_w_buff[ADC_IF_COLLECT_MAX_NUM];     /*cache array*/
    uint16_t e_w_validValue;                       /*valid value when filtering is completed*/
    uint16_t e_w_currentValue;                     /*the current value - unfiltered value*/
    uint8_t e_u_index;                             /*the current input index*/
    uint8_t e_u_collectNum;                        /*acquisition size*/
    uint8_t e_u_flag;                              /*completion flag*/
} adc_if_struct;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* adc_demo */
extern void adc_if_init(void);
extern uint16_t adc_if_get_validValue(uint8_t ucChannel);
extern uint16_t adc_if_get_currValue(uint8_t ucChannel);

#endif /* #ifndef __ADC_IF_H__ */

/*EoF*/