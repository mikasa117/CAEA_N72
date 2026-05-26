/*
  ******************************************************************************
  * @file    driver_yuv2rgb.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2022
  * @brief   Header file of YUV2RGB HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_YUV2RGB_H__
#define __DRIVER_YUV2RGB_H__

#include "fr30xx.h"

/** @addtogroup YUV2RGB_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* YUV2RGB Config Register */
typedef struct
{
    uint32_t YUV_MODE   : 1;
    uint32_t YUV_FORMAT : 1;
    uint32_t RGB_FORMAT : 2;
    uint32_t rsv_0      : 28;
}REG_YUV2RGB_CFG_t;

/* YUV FIFO control */
typedef struct
{
    uint32_t YUV_FIFO_ALMOST_EMPTY_LEVEL : 5;
    uint32_t rsv_0                       : 3;
    uint32_t YUV_FIFO_ALMOST_FULL_LEVEL  : 5;
    uint32_t rsv_1                       : 19;
}REG_YUV_FIFO_CTRL_t;

/* RGB FIFO control */
typedef struct
{
    uint32_t RGB_FIFO_ALMOST_EMPTY_LEVEL : 5;
    uint32_t rsv_0                       : 3;
    uint32_t RGB_FIFO_ALMOST_FULL_LEVEL  : 5;
    uint32_t rsv_1                       : 19;
}REG_RGB_FIFO_CTRL_t;

/* FIFO status control */
typedef struct
{
    uint32_t rsv_0           : 8;
    uint32_t YUV_FIFO_COUNT  : 6;
    uint32_t rsv_1           : 2;
    uint32_t RGB_FIFO_COUNT  : 6;
    uint32_t rsv_2           : 10;
}REG_FIFO_STATUS_t;

/* DMA control */
typedef struct
{
    uint32_t DMA_EN        : 1;
    uint32_t rsv_0         : 7;
    uint32_t YUV_DMA_LEVEL : 5;
    uint32_t rsv_1         : 3;
    uint32_t RGB_DMA_LEVEL : 5;
    uint32_t rsv_2         : 11;
}REG_DMA_CTRL_t;

/* DMA control */
typedef struct
{
    uint32_t YUV_FLOW_LEVEL : 6;
    uint32_t rsv_0          : 2;
    uint32_t RGB_FLOW_LEVEL : 6;
    uint32_t rsv_1          : 18;
}REG_FLOW_CTRL_t;

/* Result auto Incremen threshold control */
typedef struct
{
    uint32_t RGB565_B_THR : 3;
    uint32_t RGB565_G_THR : 2;
    uint32_t RGB565_R_THR : 3;
    uint32_t rsv_0        : 8;
    uint32_t RGB322_B_THR : 6;
    uint32_t RGB322_G_THR : 5;
    uint32_t RGB322_R_THR : 5;
}REG_OPTIMIZE_CTRL_t;

/* DVP Config Register */
typedef struct
{
    uint32_t DVP_EN                : 1;
    uint32_t DVP_DCLKPOL           : 1;
    uint32_t DVP_HDPOL             : 1;
    uint32_t DVP_VDPOL             : 1;    
    uint32_t DVP_CONV              : 1;  
    uint32_t HADDR_CUT             : 1; 
    uint32_t VADDR_CUT             : 1; 
    uint32_t SINGLE_FRAME_EN       : 1;
    uint32_t DVP_SFT_RST           : 1;    
    uint32_t DVP_FIFO_PUSH_CLR     : 1; 
    uint32_t FRAME_CNT_VAL         : 4;    
    uint32_t BUS_WIDTH_SEL         : 2;
    uint32_t BIT_SWAP              : 1;   
    uint32_t YUV_SWAP              : 2;  
    uint32_t RGB_SWAP              : 1;   
    uint32_t RGB_REC_EN            : 1; 
    uint32_t REC_WIDTH_SEL         : 1;    
    uint32_t rsv_0                 : 10;
}REG_DVP_CFG_t;

/* DVP IMAGE HADDR CUT Register */
typedef struct
{
    uint32_t CHSTR                 : 11;
    uint32_t rsv_0                 : 5;
    uint32_t CHNUM                 : 11;
    uint32_t rsv_1                 : 5;    
}REG_DVP_HADDR_CUT_t;

/* DVP IMAGE VADDR CUT Register */
typedef struct
{
    uint32_t CVSTR                 : 11;
    uint32_t rsv_0                 : 5;
    uint32_t CVNUM                 : 11;
    uint32_t rsv_1                 : 5;    
}REG_DVP_VADDR_CUT_t;

/* ------------------------------------------------*/
/*                 YUV2RGB Register                */
/* ------------------------------------------------*/
typedef struct 
{
    volatile uint32_t                   YUV2RGB_CTL;         /* Offset 0x00 */
    volatile REG_YUV2RGB_CFG_t          YUV2RGB_CFG;         /* Offset 0x04 */
    volatile uint32_t                   YUV_DATA;            /* Offset 0x08 */
    volatile uint32_t                   RGB_DATA;            /* Offset 0x0C */
    volatile REG_YUV_FIFO_CTRL_t        YUV_FIFO_CTRL;       /* Offset 0x10 */
    volatile REG_RGB_FIFO_CTRL_t        RGB_FIFO_CTRL;       /* Offset 0x14 */
    volatile REG_FIFO_STATUS_t          FIFO_STATUS;         /* Offset 0x18 */
    volatile uint32_t                   INT_CTRL;            /* Offset 0x1C */
    volatile uint32_t                   INT_STATUS;          /* Offset 0x20 */
    volatile uint32_t                   INT_RAW;             /* Offset 0x24 */
    volatile REG_DMA_CTRL_t             DMA_CTRL;            /* Offset 0x28 */
    volatile REG_FLOW_CTRL_t            FLOW_CTRL;           /* Offset 0x2C */
    volatile REG_OPTIMIZE_CTRL_t        OPTIMIZE_CTRL;       /* Offset 0x30 */
    volatile REG_DVP_CFG_t              DVP_CFG;             /* Offset 0x34 */
    volatile REG_DVP_HADDR_CUT_t        HADDR_CUT;           /* Offset 0x38 */
    volatile REG_DVP_VADDR_CUT_t        VADDR_CUT;           /* Offset 0x3C */
    volatile uint32_t                   DVP_INT_EN;          /* Offset 0x40 */ 
    volatile uint32_t                   DVP_RAW_STATUS;      /* Offset 0x44 */
}struct_YUV2RGB_t;

#define YUV2RGB    ((struct_YUV2RGB_t *)YUV2RGB_BASE)
/* ################################ Register Section END ################################## */
/**
  * @}
  */



/** @addtogroup YUV2RGB_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization, Config Section Start ################################ */

/* YUV2RGB status index */
typedef enum
{
    YUV_FIFO_EMPTY        = 0x01,       /*!< YUV FIFO empty        */
    YUV_FIFO_ALMOST_EMPTY = 0x02,       /*!< YUV FIFO almost empty */
    YUV_FIFO_FULL         = 0x04,       /*!< YUV FIFO full         */
    YUV_FIFO_ALMOST_FULL  = 0x08,       /*!< YUV FIFO almost full  */
    RGB_FIFO_EMPTY        = 0x10,       /*!< RGB FIFO empty        */
    RGB_FIFO_ALMOST_EMPTY = 0x20,       /*!< RGB FIFO almost empty */
    RGB_FIFO_FULL         = 0x40,       /*!< RGB FIFO full         */
    RGB_FIFO_ALMOST_FULL  = 0x80,       /*!< RGB FIFO almost full  */
}enum_YUV2RGB_STATUS_t;

/* YUV2RGB calculate mode */
typedef enum
{
    YUV2RGB_CALCULATE_MODE_A,
    YUV2RGB_CALCULATE_MODE_B,
}enum_YUV2RGB_CALCULATE_MODE_t;

/* RGB FORMAT */
typedef enum
{
    RGB_FORMAT_888,
    RGB_FORMAT_565,
    RGB_FORMAT_332,
}enum_RGB_FORMAT_t;

/* YUV FORMAT */
typedef enum
{
    YUV_FORMAT_444,
    YUV_FORMAT_422,
}enum_YUV_FORMAT_t;


/* DVP WIDTH */
typedef enum
{
    WIDTH_SIZE_12BIT,
    WIDTH_SIZE_10BIT,
    WIDTH_SIZE_8BIT,
}enum_DVP_WIDTH_t;

/* DVP DCLK polarity */
typedef enum
{
    SAMPLE_RISING_EDGE,
    SAMPLE_FALLING_EDGE,
}enum_DVP_DCLKPOL_t;

/* DVP VSYNC polarity */
typedef enum
{
    VSYNC_LOW_LEVEL_VALID,
    VSYNC_HIGH_LEVEL_VALID,
}enum_DVP_VSYNCPOL_t;

/* DVP HSYNC polarity */
typedef enum
{
    HSYNC_HIGH_LEVEL_VALID,
    HSYNC_LOW_LEVEL_VALID,
}enum_DVP_HSYNCPOL_t;

/* DVP work mode */
typedef enum
{
    RGB565_TO_RGB565,
    YUV422_TO_RGB565,
    YUV444_TO_RGB888,
    YUV444_TO_RGB565,
}enum_DVP_MODE_t;

/** @defgroup DVP_interrupt_definition
  * @{
  */
#define DVP_INT_VSTART                (1 << 0)       /*!< vertical start  */
#define DVP_INT_VEND                  (1 << 1)       /*!< vertical stop   */
/**
  * @}
  */

/**
  * @brief YUV2RGB Init Structure definition
  */
typedef struct
{
    uint32_t YUV_Format;            /*!< Specifies the number of YUV format.
                                         This parameter can be a value of @ref enum_YUV_FORMAT_t. */

    uint32_t RGB_Format;            /*!< Specifies the number of RGB format.
                                         This parameter can be a value of @ref enum_RGB_FORMAT_t. */
                                        
    uint32_t YUV_CalculateMode;     /*!< Specifies the number of YUV2RGB calculate mode.
                                         This parameter can be a value of @ref enum_YUV2RGB_CALCULATE_MODE_t. */
}struct_YUV2RGBInit_t;

/**
  * @brief DVP Init Structure definition
  */
typedef struct
{
    uint32_t DVP_Mode;             /*!< Specifies the work mode of DVP.
                                        This parameter can be a value of @ref enum_DVP_MODE_t. */

    uint32_t DVP_VSYNCPOL;         /*!< Specifies the VSYNC polarity.
                                        This parameter can be a value of @ref enum_DVP_VSYNCPOL_t. */
    uint32_t DVP_HSYNCPOL;         /*!< Specifies the HSYNC polarity.
                                        This parameter can be a value of @ref enum_DVP_HSYNCPOL_t. */
    uint32_t DVP_DCLKPOL;          /*!< Specifies the data clock polarity.
                                        This parameter can be a value of @ref enum_DVP_DCLKPOL_t. */

    uint32_t DVP_BusWidth;         /*!< Specifies the Bus Width of DVP.
                                        This parameter can be a value of @ref enum_DVP_WIDTH_t. */

    uint32_t DVP_RGB_AlmostFull_Level;    /*!< Specifies the RGB FIFO almost full threshold of DVP.
                                               This parameter can be a value 0 ~ 31 */
}struct_DVPInit_t;

/**
  * @brief  YUV2RGB handle Structure definition
  */
typedef struct
{
    struct_YUV2RGB_t      *YUV2RGBx;              /*!< YUV2RGB registers base address */

    struct_YUV2RGBInit_t   Init;                  /*!< YUV2RGB Init parameters */
    
    struct_DVPInit_t       DVP_Init;              /*!< DVP Init parameters */    

    union {
        volatile void      *p_data;
        volatile uint16_t  *p_u16;
        volatile uint32_t  *p_u32;
    }u_YUVData;

    union {
        volatile void      *p_data;
        volatile uint8_t   *p_u8;
        volatile uint16_t  *p_u16;
        volatile uint32_t  *p_u32;
    }u_RGBData;

    volatile bool           b_CovertBusy;
    volatile uint32_t       u32_Pixels;
    volatile uint32_t       u32_RGBCount;
    volatile uint32_t       u32_YUVCount;
}YUV2RGB_HandleTypeDef;

/* ################################ Initialization, Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* YUV2RGB enable */
#define __YUV2RGB_ENABLE(__YUV2RGB__)                                   (__YUV2RGB__->YUV2RGB_CTL = 1)
#define __YUV2RGB_DISABLE(__YUV2RGB__)                                  (__YUV2RGB__->YUV2RGB_CTL = 0)

#define __YUV2RGB_YUV_FORMAT_CONFIG(__YUV2RGB__, __CFG__)               (__YUV2RGB__->YUV2RGB_CFG.YUV_FORMAT = __CFG__)
#define __YUV2RGB_RGB_FORMAT_CONFIG(__YUV2RGB__, __CFG__)               (__YUV2RGB__->YUV2RGB_CFG.RGB_FORMAT = __CFG__)

/* YUV FIFO almost full threshold */
/* YUV FIFO almost empty threshold */
#define __YUV2RGB_YUV_FIFO_ALMOST_FULL_LEVEL(__YUV2RGB__, __LEVEL__)    (__YUV2RGB__->YUV_FIFO_CTRL.YUV_FIFO_ALMOST_FULL_LEVEL  = __LEVEL__)
#define __YUV2RGB_YUV_FIFO_ALMOST_EMPTY_LEVEL(__YUV2RGB__, __LEVEL__)   (__YUV2RGB__->YUV_FIFO_CTRL.YUV_FIFO_ALMOST_EMPTY_LEVEL = __LEVEL__)
/* RGB FIFO almost full threshold */
/* RGB FIFO almost empty threshold */
#define __YUV2RGB_RGB_FIFO_ALMOST_FULL_LEVEL(__YUV2RGB__, __LEVEL__)    (__YUV2RGB__->RGB_FIFO_CTRL.RGB_FIFO_ALMOST_FULL_LEVEL  = __LEVEL__)
#define __YUV2RGB_RGB_FIFO_ALMOST_EMPTY_LEVEL(__YUV2RGB__, __LEVEL__)   (__YUV2RGB__->RGB_FIFO_CTRL.RGB_FIFO_ALMOST_EMPTY_LEVEL = __LEVEL__)

/* Get RGB FIFO data count */
/* Get YUV FIFO data count */
#define __YUV2RGB_GET_RGB_FIFO_COUNT(__YUV2RGB__)                       (__YUV2RGB__->FIFO_STATUS.RGB_FIFO_COUNT)
#define __YUV2RGB_GET_YUV_FIFO_COUNT(__YUV2RGB__)                       (__YUV2RGB__->FIFO_STATUS.YUV_FIFO_COUNT)

/* YUV2RGB DMA enable */
#define __YUV2RGB_DMA_ENABLE(__YUV2RGB__)                               (__YUV2RGB__->DMA_CTRL.DMA_EN = 1)
#define __YUV2RGB_DMA_DISABLE(__YUV2RGB__)                              (__YUV2RGB__->DMA_CTRL.DMA_EN = 0)
#define __YUV2RGB_DMA_YUV_LEVEL(__YUV2RGB__, __LEVEL__)                 (__YUV2RGB__->DMA_CTRL.YUV_DMA_LEVEL = __LEVEL__)
#define __YUC2RGB_DMA_RGB_LEVEL(__YUV2RGB__, __LEVEL__)                 (__YUV2RGB__->DMA_CTRL.RGB_DMA_LEVEL = __LEVEL__)

/* YUV flow threshold */
/* RGB flow threshold */
#define __YUV2RGB_YUV_FLOW_LEVEL(__YUV2RGB__, __LEVEL__)                (__YUV2RGB__->FLOW_CTRL.YUV_FLOW_LEVEL = __LEVEL__)
#define __YUV2RGB_RGB_FLOW_LEVEL(__YUV2RGB__, __LEVEL__)                (__YUV2RGB__->FLOW_CTRL.RGB_FLOW_LEVEL = __LEVEL__)

/* RGB565 RGB optimize threshold */
/* RGB322 RGB optimize threshold */
#define __YUV2RGB_RGB322_R_OPTIMIZE_LEVEL(__YUV2RGB__, __LEVEL__)       (__YUV2RGB__->OPTIMIZE_CTRL.RGB322_R_THR = __LEVEL__)
#define __YUV2RGB_RGB322_G_OPTIMIZE_LEVEL(__YUV2RGB__, __LEVEL__)       (__YUV2RGB__->OPTIMIZE_CTRL.RGB322_G_THR = __LEVEL__)
#define __YUV2RGB_RGB322_B_OPTIMIZE_LEVEL(__YUV2RGB__, __LEVEL__)       (__YUV2RGB__->OPTIMIZE_CTRL.RGB322_B_THR = __LEVEL__)
#define __YUV2RGB_RGB565_R_OPTIMIZE_LEVEL(__YUV2RGB__, __LEVEL__)       (__YUV2RGB__->OPTIMIZE_CTRL.RGB565_R_THR = __LEVEL__)
#define __YUV2RGB_RGB565_G_OPTIMIZE_LEVEL(__YUV2RGB__, __LEVEL__)       (__YUV2RGB__->OPTIMIZE_CTRL.RGB565_G_THR = __LEVEL__)
#define __YUV2RGB_RGB565_B_OPTIMIZE_LEVEL(__YUV2RGB__, __LEVEL__)       (__YUV2RGB__->OPTIMIZE_CTRL.RGB565_B_THR = __LEVEL__)

/* YUV2RGB get interrupt raw status */
#define __YUV2RGB_GET_INT_RAW_STATUS(__YUV2RGB__)                       (__YUV2RGB__->INT_RAW)
/* YUV2RGB get interrupt status */
#define __YUV2RGB_GET_INT_STATUS(__YUV2RGB__)                           (__YUV2RGB__->INT_STATUS)
/* YUV2RGB set interrupt enable */
/* YUV2RGB set interrupt disable */
#define __YUV2RGB_INT_ENABLE(__YUV2RGB__, __INT__)                      (__YUV2RGB__->INT_CTRL |= (__INT__))
#define __YUV2RGB_INT_DISABLE(__YUV2RGB__, __INT__)                     (__YUV2RGB__->INT_CTRL &= ~(__INT__))


/* DVP enable and disable */
#define __DVP_START(__YUV2RGB__)                                        (__YUV2RGB__->DVP_CFG.DVP_EN = 1)
#define __DVP_STOP(__YUV2RGB__)                                         (__YUV2RGB__->DVP_CFG.DVP_EN = 0)
/* DVP VSYNC HSYNC DCLK polarity */ 
#define __DVP_SET_VSYNC_POLARITY_CONFIG(__YUV2RGB__, __CFG__)           (__YUV2RGB__->DVP_CFG.DVP_VDPOL = __CFG__)
#define __DVP_SET_HSYNC_POLARITY_CONFIG(__YUV2RGB__, __CFG__)           (__YUV2RGB__->DVP_CFG.DVP_HDPOL = __CFG__)
#define __DVP_SET_DCLK_POLARITY_CONFIG(__YUV2RGB__, __CFG__)            (__YUV2RGB__->DVP_CFG.DVP_DCLKPOL = __CFG__)
/* DVP RGB convert enable */
#define __DVP_RGB_CONVERT_ENABLE(__YUV2RGB__)                           (__YUV2RGB__->DVP_CFG.DVP_CONV = 1)
#define __DVP_RGB_CONVERT_DISABLE(__YUV2RGB__)                          (__YUV2RGB__->DVP_CFG.DVP_CONV = 0)
/* DVP cut */
#define __DVP_VCUT_ENABLE(__YUV2RGB__)                                  (__YUV2RGB__->DVP_CFG.VADDR_CUT = 1)
#define __DVP_VCUT_DISABLE(__YUV2RGB__)                                 (__YUV2RGB__->DVP_CFG.VADDR_CUT = 0)
#define __DVP_HCUT_ENABLE(__YUV2RGB__)                                  (__YUV2RGB__->DVP_CFG.HADDR_CUT = 1)
#define __DVP_HCUT_DISABLE(__YUV2RGB__)                                 (__YUV2RGB__->DVP_CFG.HADDR_CUT = 0)
/* DVP single frame receive enable */
#define __DVP_SINGLE_FRAME_ENABLE(__YUV2RGB__)                          (__YUV2RGB__->DVP_CFG.SINGLE_FRAME_EN = 1)
#define __DVP_SINGLE_FRAME_DISABLE(__YUV2RGB__)                         (__YUV2RGB__->DVP_CFG.SINGLE_FRAME_EN = 0)
/* DVP reset */
#define __DVP_RESET(__YUV2RGB__)                                        (__YUV2RGB__->DVP_CFG.DVP_SFT_RST = 1)
#define __DVP_FIFO_RESET(__YUV2RGB__)                                   (__YUV2RGB__->DVP_CFG.DVP_FIFO_PUSH_CLR = 1)
/* DVP dropped frames */
#define __DVP_DROPPED_FRAMES_CONFIG(__YUV2RGB__, __CFG__)               (__YUV2RGB__->DVP_CFG.FRAME_CNT_VAL = __CFG__)
/* DVP bus width */
#define __DVP_BUS_WIDTH_CONFIG(__YUV2RGB__, __CFG__)                    (__YUV2RGB__->DVP_CFG.BUS_WIDTH_SEL = __CFG__)
/* DVP SWAP */
#define __DVP_BIT_SWAP_CONFIG(__YUV2RGB__, __CFG__)                     (__YUV2RGB__->DVP_CFG.BIT_SWAP = __CFG__)
#define __DVP_YUV_SWAP_CONFIG(__YUV2RGB__, __CFG__)                     (__YUV2RGB__->DVP_CFG.YUV_SWAP = __CFG__)
#define __DVP_RGB_SWAP_CONFIG(__YUV2RGB__, __CFG__)                     (__YUV2RGB__->DVP_CFG.RGB_SWAP = __CFG__)
/* DVP receive RGB enable */
#define __DVP_RECEIVE_RGB_ENABLE(__YUV2RGB__)                           (__YUV2RGB__->DVP_CFG.RGB_REC_EN = 1)
#define __DVP_RECEIVE_RGB_DISABLE(__YUV2RGB__)                          (__YUV2RGB__->DVP_CFG.RGB_REC_EN = 0)
#define __DVP_RECEIVE_WIDTH_CONFIG(__YUV2RGB__, __CFG__)                (__YUV2RGB__->DVP_CFG.REC_WIDTH_SEL = __CFG__)

/* DVP cut config */
#define __DVP_VCUT_START_CONFIG(__YUV2RGB__, __CFG__)                   (__YUV2RGB__->VADDR_CUT.CVSTR = __CFG__)
#define __DVP_VCUT_LEN_CONFIG(__YUV2RGB__, __CFG__)                     (__YUV2RGB__->VADDR_CUT.CVNUM = __CFG__)
#define __DVP_HCUT_START_CONFIG(__YUV2RGB__, __CFG__)                   (__YUV2RGB__->HADDR_CUT.CHSTR = __CFG__)
#define __DVP_HCUT_LEN_CONFIG(__YUV2RGB__, __CFG__)                     (__YUV2RGB__->HADDR_CUT.CHNUM = __CFG__)

/* DVP get interrupt status */
#define __DVP_GET_INT_STATUS(__YUV2RGB__)                               (__YUV2RGB__->DVP_RAW_STATUS)
/* DVP clr interrupt status */
#define __DVP_CLR_INT_STATUS(__YUV2RGB__, __INT__)                   (__YUV2RGB__->DVP_INT_EN |= (__INT__))
/* DVP set interrupt enable */
/* DVP set interrupt disable */
#define __DVP_INT_ENABLE(__YUV2RGB__, __INT__)                        (__YUV2RGB__->DVP_INT_EN |= (__INT__))
#define __DVP_INT_DISABLE(__YUV2RGB__, __INT__)                       (__YUV2RGB__->DVP_INT_EN &= ~(__INT__))

/* Exported functions --------------------------------------------------------*/

/* yuv2rgb_IRQHandler */
void yuv2rgb_IRQHandler(YUV2RGB_HandleTypeDef *hyuv2rgb);

/* yuv2rgb_init */
void yuv2rgb_init(YUV2RGB_HandleTypeDef *hyuv2rgb);
/* yuv2rgb_convert */
/* yuv2rgb_convert_IT */
void yuv2rgb_convert(YUV2RGB_HandleTypeDef *hyuv2rgb, void *YUV_Buffer, void *RGB_Buffer, uint32_t fu32_Pixels);
void yuv2rgb_convert_IT(YUV2RGB_HandleTypeDef *hyuv2rgb, void *YUV_Buffer, void *RGB_Buffer, uint32_t fu32_Pixels);

/* dvp_init */
void dvp_init(YUV2RGB_HandleTypeDef *hyuv2rgb);
/* dvp start/stop */
void dvp_start(YUV2RGB_HandleTypeDef *hyuv2rgb);
void dvp_stop(YUV2RGB_HandleTypeDef *hyuv2rgb);

void dvp_vertical_cut_enable(YUV2RGB_HandleTypeDef *hyuv2rgb, uint16_t fu16_VSTR, uint16_t fu16_VLEN);
void dvp_vertical_cut_disable(YUV2RGB_HandleTypeDef *hyuv2rgb);

void dvp_horizontal_cut_enable(YUV2RGB_HandleTypeDef *hyuv2rgb, uint16_t fu16_HSTR, uint16_t fu16_HLEN);
void dvp_horizontal_cut_disable(YUV2RGB_HandleTypeDef *hyuv2rgb);

void dvp_int_enable(YUV2RGB_HandleTypeDef *hyuv2rgb, uint32_t fu32_INT);
void dvp_int_disable(YUV2RGB_HandleTypeDef *hyuv2rgb, uint32_t fu32_INT);
void dvp_int_status_clear(YUV2RGB_HandleTypeDef *hyuv2rgb, uint32_t fu32_INT);
uint32_t dvp_get_int_raw_status(YUV2RGB_HandleTypeDef *hyuv2rgb);

#endif
