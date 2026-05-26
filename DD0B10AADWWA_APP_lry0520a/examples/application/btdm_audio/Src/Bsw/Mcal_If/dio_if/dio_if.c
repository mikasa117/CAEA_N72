/*
 * @Author: liuranyang liuranyang@cncaea.cn
 * @Date: 2026-01-29 13:07:59
 * @LastEditors: liuranyang liuranyang@cncaea.cn
 * @LastEditTime: 2026-04-27 11:03:44
 * @FilePath: \FR30xxC-SDK-v0.3.1\examples\application\btdm_audio\Src\Bsw\Mcal_If\dio_if\dio_if.c
 * @Description: 默认设置
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "dio_if.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static dio_if_struct dio_map[dio_cl_max] =
{
    {dio_cl_adc_bat,      GPIOA, GPIO_PIN_5  , GPIO_MODE_INPUT ,     GPIO_NOPULL, GPIO_PIN_CLEAR},
    {dio_cl_adc_acc,      GPIOD, GPIO_PIN_12 , GPIO_MODE_INPUT ,     GPIO_NOPULL, GPIO_PIN_CLEAR},
    {dio_cl_adc_msw_l,    GPIOD, GPIO_PIN_13 , GPIO_MODE_INPUT ,     GPIO_NOPULL, GPIO_PIN_CLEAR},
    {dio_cl_adc_msw_r,    GPIOD, GPIO_PIN_14 , GPIO_MODE_INPUT ,     GPIO_NOPULL, GPIO_PIN_CLEAR},
    {dio_cl_bat_ad_en,    GPIOA, GPIO_PIN_4  , GPIO_MODE_OUTPUT_PP , GPIO_NOPULL, GPIO_PIN_SET},
    {dio_cl_mic_8v_en,    GPIOB, GPIO_PIN_0  , GPIO_MODE_OUTPUT_PP , GPIO_NOPULL, GPIO_PIN_CLEAR},
    {dio_cl_mcu_can_stbn, GPIOB, GPIO_PIN_8  , GPIO_MODE_OUTPUT_PP , GPIO_NOPULL, GPIO_PIN_SET},
    {dio_cl_mcu_hold_on,  GPIOB, GPIO_PIN_9  , GPIO_MODE_OUTPUT_PP , GPIO_NOPULL, GPIO_PIN_CLEAR},
    {dio_cl_amp_stbyn,    GPIOD, GPIO_PIN_4  , GPIO_MODE_OUTPUT_PP , GPIO_NOPULL, GPIO_PIN_SET},
    {dio_cl_amp_muten,    GPIOD, GPIO_PIN_5  , GPIO_MODE_OUTPUT_PP , GPIO_NOPULL, GPIO_PIN_SET},
};
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* ========================================================================== */
/*                        Application Local Functions                         */
/* ========================================================================== */

/**
 * @description: dio_if_Init
 * @return {*}
 */
void dio_if_Init(void)
{
    uint8_t tempDioChan;
    GPIO_InitTypeDef gpio_config;

    __SYSTEM_GPIOA_CLK_ENABLE();
    __SYSTEM_GPIOB_CLK_ENABLE();
    __SYSTEM_GPIOC_CLK_ENABLE();
    __SYSTEM_GPIOD_CLK_ENABLE();

    for(tempDioChan = 0u; tempDioChan < dio_cl_max; tempDioChan++)
	{
        gpio_config.Pin  = dio_map[tempDioChan].ucGpioPin;
        gpio_config.Mode = dio_map[tempDioChan].ucGpioMode;
        gpio_config.Pull = dio_map[tempDioChan].ucGpioPull;
        gpio_config.Alternate = GPIO_FUNCTION_0;
        gpio_init(dio_map[tempDioChan].ucGpioGrp, &gpio_config);
        gpio_write_pin(dio_map[tempDioChan].ucGpioGrp, dio_map[tempDioChan].ucGpioPin, dio_map[tempDioChan].ucInitPinLevel);
	}
}
/*EoF*/