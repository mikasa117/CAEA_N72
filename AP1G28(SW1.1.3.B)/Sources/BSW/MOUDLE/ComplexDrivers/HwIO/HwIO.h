/*******************************************************************************
|  File Name:  HwIO.h
|  Description:  Implementation of the HwIO Config Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| WCj           WangChaojian          CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author        Description
| ------------  --------     -------       -----------------------------------------
| 2025-11-17    01.00.00     WCj           Creation

|******************************************************************************/

#ifndef _HwIO_H_
#define _HwIO_H_

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "CAEA_Types.h"
#include "pin_mux.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define HWIO_PIN_HIGH                  1u
#define HWIO_PIN_LOW                   0u
/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Global Variable with extern linkage
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/

/*OUTPUT*/
extern void HwIO_MCU_LIN_SLPn_ON(void);
extern void HwIO_MCU_LIN_SLPn_OFF(void);

extern void HwIO_COMP_12V_EN_ON(void);
extern void HwIO_COMP_12V_EN_OFF(void);

extern void HwIO_COMP_12V_DEN_ON(void);
extern void HwIO_COMP_12V_DEN_OFF(void);

extern void HwIO_MCU_Hold_on_EN(void);
extern void HwIO_MCU_Hold_on_DEN(void);

extern void HwIO_VCC_46V_EN_ON(void);
extern void HwIO_VCC_46V_EN_OFF(void);

extern void HwIO_KL30_AD_EN_High(void);
extern void HwIO_KL30_AD_EN_Low(void);

extern void HwIO_HW_12V_DEN_ON(void);
extern void HwIO_HW_12V_DEN_OFF(void);

extern void HwIO_HALL_5V_EN_ON(void);
extern void HwIO_HALL_5V_EN_OFF(void);

extern void HwIO_HF_12V_DEN_ON(void);
extern void HwIO_HF_12V_DEN_OFF(void);

extern void HwIO_MCU_LEDDRV_EN_ON(void);
extern void HwIO_MCU_LEDDRV_EN_OFF(void);

extern void HwIO_MCU_CAN_EN_ON(void);
extern void HwIO_MCU_CAN_EN_OFF(void);

extern void HwIO_MCU_CAN_STBn_High(void);
extern void HwIO_MCU_CAN_STBn_Low(void);

extern void HwIO_MCU_PD_SLPn_Enable(void);
extern void HwIO_MCU_PD_SLPn_Disable(void);

extern void HwIO_FAN_12V_DEN_Enable(void);
extern void HwIO_FAN_12V_DEN_Disable(void);

/*INPUT*/
extern uint8_t HwIO_GetHW_REV0(void);
extern uint8_t HwIO_GetHW_REV1(void);
//extern uint8_t HwIO_GetHALL_MCU_PWM(void);
extern uint8_t HwIO_GetPD_MCU_FLTn(void);
extern uint8_t HwIO_GetLEDDRV_MCU_FLTn1(void);
extern uint8_t HwIO_GetLEDDRV_MCU_FLTn2(void);
extern uint8_t HwIO_GetCAN_MCU_ERRn(void);

#endif 

