/*
  ******************************************************************************
  * @file    driver_yuv2rgb.c
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2022
  * @brief   YUV2RGB module driver.
  *          This file provides firmware functions to manage the YUV2RGB.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#include "fr30xx.h"

/************************************************************************************
 * @fn      yuv2rgb_init
 *
 * @brief   Initialize YUV2RGB UART according to the specified parameters 
 *          in the struct_YUV2RGBInit_t.
 *
 * @param   hyuv2rgb: YUV2RGB handle.
 */
void yuv2rgb_init(YUV2RGB_HandleTypeDef *hyuv2rgb)
{
    /* YUV2RGB enable */
    __YUV2RGB_ENABLE(hyuv2rgb->YUV2RGBx);
    /* DMA default enable */
    __YUV2RGB_DMA_ENABLE(hyuv2rgb->YUV2RGBx);
    
    /* Set YUV2RGB format, calculate Mode */
    hyuv2rgb->YUV2RGBx->YUV2RGB_CFG.RGB_FORMAT = hyuv2rgb->Init.RGB_Format;
    hyuv2rgb->YUV2RGBx->YUV2RGB_CFG.YUV_FORMAT = hyuv2rgb->Init.YUV_Format;
    hyuv2rgb->YUV2RGBx->YUV2RGB_CFG.YUV_MODE   = hyuv2rgb->Init.YUV_CalculateMode;

    if (hyuv2rgb->Init.YUV_Format == YUV_FORMAT_444)
        hyuv2rgb->YUV2RGBx->FLOW_CTRL.YUV_FLOW_LEVEL = 1;
    else
        hyuv2rgb->YUV2RGBx->FLOW_CTRL.YUV_FLOW_LEVEL = 2;

    hyuv2rgb->YUV2RGBx->FLOW_CTRL.RGB_FLOW_LEVEL = 30;
}

/************************************************************************************
 * @fn      yuv2rgb_convert
 *
 * @brief   YUV to RGB convert in blocking mode.
 *
 * @param   hyuv2rgb: YUV2RGB handle.
 *          YUV_Buffer:  YUV data buffer.
 *          RGB_BUffer:  RGB data buffer.
 *          fu32_Pixels: 
 */
void yuv2rgb_convert(YUV2RGB_HandleTypeDef *hyuv2rgb, void *YUV_Buffer, void *RGB_Buffer, uint32_t fu32_Pixels)
{
    uint32_t lu32_RGBCount = 0;
    uint32_t lu32_YUVCount = 0;

    hyuv2rgb->u_YUVData.p_data = YUV_Buffer;
    hyuv2rgb->u_RGBData.p_data = RGB_Buffer;

    while(true)
    {
        if (!(__YUV2RGB_GET_INT_RAW_STATUS(hyuv2rgb->YUV2RGBx) & RGB_FIFO_EMPTY))
        {
            if (lu32_RGBCount < fu32_Pixels)
            {
                switch (hyuv2rgb->Init.RGB_Format)
                {
                    case RGB_FORMAT_888: *hyuv2rgb->u_RGBData.p_u32++ = hyuv2rgb->YUV2RGBx->RGB_DATA; break;
                    case RGB_FORMAT_565: *hyuv2rgb->u_RGBData.p_u16++ = hyuv2rgb->YUV2RGBx->RGB_DATA; break;
                    case RGB_FORMAT_332: *hyuv2rgb->u_RGBData.p_u8++  = hyuv2rgb->YUV2RGBx->RGB_DATA; break;
                    default:break;
                }
                lu32_RGBCount++;
                if (lu32_RGBCount >= fu32_Pixels)
                    break;
            }
        }

        if (!(__YUV2RGB_GET_INT_RAW_STATUS(hyuv2rgb->YUV2RGBx) & YUV_FIFO_FULL))
        {
            if (lu32_YUVCount < fu32_Pixels)
            {
                switch (hyuv2rgb->Init.YUV_Format)
                {
                    case YUV_FORMAT_444: hyuv2rgb->YUV2RGBx->YUV_DATA = *hyuv2rgb->u_YUVData.p_u32++; break;
                    case YUV_FORMAT_422: hyuv2rgb->YUV2RGBx->YUV_DATA = *hyuv2rgb->u_YUVData.p_u16++; break;
                    default: break;
                }

                lu32_YUVCount++;
            }
        }
    }
}

/************************************************************************************
 * @fn      dvp_init
 *
 * @brief   Initialize dvp init according to the specified parameters 
 *          in the struct_DVPInit_t.
 *
 * @param   hyuv2rgb: YUV2RGB handle.
 */
void dvp_init(YUV2RGB_HandleTypeDef *hyuv2rgb)
{
    __DVP_RESET(hyuv2rgb->YUV2RGBx);
    while(hyuv2rgb->YUV2RGBx->DVP_CFG.DVP_SFT_RST);

    /* Almost Full level */
    if (hyuv2rgb->DVP_Init.DVP_RGB_AlmostFull_Level)
    {
        __YUV2RGB_DMA_ENABLE(hyuv2rgb->YUV2RGBx);
        __YUC2RGB_DMA_RGB_LEVEL(hyuv2rgb->YUV2RGBx, hyuv2rgb->DVP_Init.DVP_RGB_AlmostFull_Level);
        __YUV2RGB_RGB_FIFO_ALMOST_FULL_LEVEL(hyuv2rgb->YUV2RGBx, hyuv2rgb->DVP_Init.DVP_RGB_AlmostFull_Level);
    }

    /* polarity */
    __DVP_SET_VSYNC_POLARITY_CONFIG(hyuv2rgb->YUV2RGBx, hyuv2rgb->DVP_Init.DVP_VSYNCPOL);
    __DVP_SET_HSYNC_POLARITY_CONFIG(hyuv2rgb->YUV2RGBx, hyuv2rgb->DVP_Init.DVP_HSYNCPOL);
    __DVP_SET_DCLK_POLARITY_CONFIG(hyuv2rgb->YUV2RGBx, hyuv2rgb->DVP_Init.DVP_DCLKPOL);
    /* frame continuous */
    __DVP_SINGLE_FRAME_DISABLE(hyuv2rgb->YUV2RGBx);
    /* Bus Width */
    __DVP_BUS_WIDTH_CONFIG(hyuv2rgb->YUV2RGBx, hyuv2rgb->DVP_Init.DVP_BusWidth);

    switch (hyuv2rgb->DVP_Init.DVP_Mode)
    {
        case RGB565_TO_RGB565:
        {
            __DVP_RECEIVE_WIDTH_CONFIG(hyuv2rgb->YUV2RGBx, 0);
            __DVP_RECEIVE_RGB_ENABLE(hyuv2rgb->YUV2RGBx);
            __DVP_RGB_CONVERT_DISABLE(hyuv2rgb->YUV2RGBx);

            __YUV2RGB_YUV_FORMAT_CONFIG(hyuv2rgb->YUV2RGBx, 0);
            __YUV2RGB_RGB_FORMAT_CONFIG(hyuv2rgb->YUV2RGBx, 0);
        }break;

        case YUV422_TO_RGB565:
        {
            __DVP_RECEIVE_WIDTH_CONFIG(hyuv2rgb->YUV2RGBx, 0);
            __DVP_RECEIVE_RGB_DISABLE(hyuv2rgb->YUV2RGBx);
            __DVP_RGB_CONVERT_ENABLE(hyuv2rgb->YUV2RGBx);

            __YUV2RGB_YUV_FORMAT_CONFIG(hyuv2rgb->YUV2RGBx, YUV_FORMAT_422);
            __YUV2RGB_RGB_FORMAT_CONFIG(hyuv2rgb->YUV2RGBx, RGB_FORMAT_565);
        }break;

        case YUV444_TO_RGB888:
        {
            __DVP_RECEIVE_WIDTH_CONFIG(hyuv2rgb->YUV2RGBx, 1);
            __DVP_RECEIVE_RGB_DISABLE(hyuv2rgb->YUV2RGBx);
            __DVP_RGB_CONVERT_ENABLE(hyuv2rgb->YUV2RGBx);

            __YUV2RGB_YUV_FORMAT_CONFIG(hyuv2rgb->YUV2RGBx, YUV_FORMAT_444);
            __YUV2RGB_RGB_FORMAT_CONFIG(hyuv2rgb->YUV2RGBx, RGB_FORMAT_888);
        }break;
        
        case YUV444_TO_RGB565:
        {
            __DVP_RECEIVE_WIDTH_CONFIG(hyuv2rgb->YUV2RGBx, 1);
            __DVP_RECEIVE_RGB_DISABLE(hyuv2rgb->YUV2RGBx);
            __DVP_RGB_CONVERT_ENABLE(hyuv2rgb->YUV2RGBx);

            __YUV2RGB_YUV_FORMAT_CONFIG(hyuv2rgb->YUV2RGBx, YUV_FORMAT_444);
            __YUV2RGB_RGB_FORMAT_CONFIG(hyuv2rgb->YUV2RGBx, RGB_FORMAT_565);
        }break;

        default:break;
    }
}

/************************************************************************************
 * @fn      dvp_start/stop
 *
 * @brief   DVP interface receive data start/stop.
 *
 * @param   hyuv2rgb: YUV2RGB handle.
 */
void dvp_start(YUV2RGB_HandleTypeDef *hyuv2rgb)
{
    __DVP_START(hyuv2rgb->YUV2RGBx);
}
void dvp_stop(YUV2RGB_HandleTypeDef *hyuv2rgb)
{
    __DVP_STOP(hyuv2rgb->YUV2RGBx);
}

/************************************************************************************
 * @fn      dvp_vertical_cut_enable/disable
 *
 * @brief   DVP vertical cut config.
 *
 * @param   hyuv2rgb: YUV2RGB handle.
 * @param   fu16_VSTR: vertical cut start addr.(0 ~ 2047)
 * @param   fu16_VLEN: vertical data length.(0 ~ 2047)
 */
void dvp_vertical_cut_enable(YUV2RGB_HandleTypeDef *hyuv2rgb, uint16_t fu16_VSTR, uint16_t fu16_VLEN)
{
    if (fu16_VSTR > 0x7FF)
        fu16_VSTR = 0x7FF;
    if (fu16_VLEN > 0x7FF)
        fu16_VLEN = 0x7FF;

    __DVP_VCUT_ENABLE(hyuv2rgb->YUV2RGBx);
    __DVP_VCUT_START_CONFIG(hyuv2rgb->YUV2RGBx, fu16_VSTR);
    __DVP_VCUT_LEN_CONFIG(hyuv2rgb->YUV2RGBx, fu16_VLEN - 1);
}
void dvp_vertical_cut_disable(YUV2RGB_HandleTypeDef *hyuv2rgb)
{
    __DVP_VCUT_DISABLE(hyuv2rgb->YUV2RGBx);
}

/************************************************************************************
 * @fn      dvp_horizontal_cut_enable/disable
 *
 * @brief   DVP horizontal cut config.
 *
 * @param   hyuv2rgb: YUV2RGB handle.
 * @param   fu16_HSTR: horizontal cut start addr.(0 ~ 2047)
 * @param   fu16_HLEN: horizontal data length.(0 ~ 2047)
 */
void dvp_horizontal_cut_enable(YUV2RGB_HandleTypeDef *hyuv2rgb, uint16_t fu16_HSTR, uint16_t fu16_HLEN)
{
    if (fu16_HSTR > 0x7FF)
        fu16_HSTR = 0x7FF;
    if (fu16_HLEN > 0x7FF)
        fu16_HLEN = 0x7FF;

    __DVP_HCUT_ENABLE(hyuv2rgb->YUV2RGBx);
    __DVP_HCUT_START_CONFIG(hyuv2rgb->YUV2RGBx, fu16_HSTR);
    __DVP_HCUT_LEN_CONFIG(hyuv2rgb->YUV2RGBx, fu16_HLEN - 1);
}
void dvp_horizontal_cut_disable(YUV2RGB_HandleTypeDef *hyuv2rgb)
{
    __DVP_HCUT_DISABLE(hyuv2rgb->YUV2RGBx);
}

/************************************************************************************
 * @fn      dvp_int_enable/disable/clear status/get status
 *
 * @brief   dvp interrupt control.
 *
 * @param   hyuv2rgb: YUV2RGB handle.
 * @param   fu32_INT: dvp interrupt index, @ref DVP_interrupt_definition
 *          This parameter can be one of the following values:
 *          @arg : DVP_INT_VSTART: vertical start interrupt
 *          @arg : DVP_INT_VSTOP:  vertical stop interrupt
 */
void dvp_int_enable(YUV2RGB_HandleTypeDef *hyuv2rgb, uint32_t fu32_INT)
{
    __DVP_INT_ENABLE(hyuv2rgb->YUV2RGBx, fu32_INT);
}
void dvp_int_disable(YUV2RGB_HandleTypeDef *hyuv2rgb, uint32_t fu32_INT)
{
    __DVP_INT_DISABLE(hyuv2rgb->YUV2RGBx, fu32_INT);
}
void dvp_int_status_clear(YUV2RGB_HandleTypeDef *hyuv2rgb, uint32_t fu32_INT)
{
    fu32_INT = fu32_INT << 16;
    __DVP_CLR_INT_STATUS(hyuv2rgb->YUV2RGBx, fu32_INT);
}
uint32_t dvp_get_int_raw_status(YUV2RGB_HandleTypeDef *hyuv2rgb)
{
    return __DVP_GET_INT_STATUS(hyuv2rgb->YUV2RGBx);
}
