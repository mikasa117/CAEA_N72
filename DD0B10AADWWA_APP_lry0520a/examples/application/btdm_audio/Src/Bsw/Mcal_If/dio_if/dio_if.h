/*
 * @Author: liuranyang liuranyang@cncaea.cn
 * @Date: 2026-01-29 13:08:15
 * @LastEditors: liuranyang liuranyang@cncaea.cn
 * @LastEditTime: 2026-03-13 11:16:50
 * @FilePath: \FR30xxC-SDK-v0.3.1\examples\application\btdm_audio\Src\Bsw\Mcal_If\dio_if\dio_if.h
 * @Description: 默认设置
 */

#ifndef __DIO_IF_H_
#define __DIO_IF_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "fr30xx.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
typedef enum dio_if_cl_s
{
    dio_cl_adc_bat,
    dio_cl_adc_acc,
    dio_cl_adc_msw_l,
    dio_cl_adc_msw_r,
    dio_cl_bat_ad_en,
    dio_cl_mic_8v_en,
    dio_cl_mcu_can_stbn,
    dio_cl_mcu_hold_on,
    dio_cl_amp_stbyn,
    dio_cl_amp_muten,
    dio_cl_max,
}dio_if_cl_t;

typedef struct
{
    dio_if_cl_t ucChannel;
    GPIO_TypeDef *ucGpioGrp;
    uint16_t ucGpioPin;
    enum_GPIO_MODE_t ucGpioMode;
    enum_Pull_t ucGpioPull;
    enum_PinStatus_t ucInitPinLevel;
}dio_if_struct;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

extern void dio_if_Init(void);

#endif /* #ifndef __DIO_IF_H_ */

/*EoF*/