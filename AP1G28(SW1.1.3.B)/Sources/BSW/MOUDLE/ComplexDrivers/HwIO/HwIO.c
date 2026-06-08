/*******************************************************************************
|  File Name:  HwIO.c
|  Description:  Implementation of the HwIO Config Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| WCJ           WangChaojian          CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author        Description
| ------------  --------     -------       -----------------------------------------
| 2025-11-    01.00.00     WCj           Creation
17
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "HwIO.h"
#include "STD_DioIf.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/

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

/*******************************************************************************
|  HwIO_CanTrcv
|******************************************************************************/

/***************************************OUTPUT**********************************/

/*MCU_LIN_SLPn*/
void HwIO_MCU_LIN_SLPn_ON(void)
{
	DioIf_WriteChannel(HW_DIO_MCU_LIN_SLPn, DIOIF_PIN_HIGH);
}
void HwIO_MCU_LIN_SLPn_OFF(void)
{
	DioIf_WriteChannel(HW_DIO_MCU_LIN_SLPn, DIOIF_PIN_LOW);
}
/*COMP_12V_EN*/
void HwIO_COMP_12V_EN_ON(void)
{
	DioIf_WriteChannel(HW_DIO_COMP_12V_EN, DIOIF_PIN_HIGH);
}
void HwIO_COMP_12V_EN_OFF(void)
{
	DioIf_WriteChannel(HW_DIO_COMP_12V_EN, DIOIF_PIN_LOW);
}
/*COMP_12V_DEN*/
void HwIO_COMP_12V_DEN_ON(void)
{
	DioIf_WriteChannel(HW_DIO_COMP_12V_DEN, DIOIF_PIN_HIGH);
}
void HwIO_COMP_12V_DEN_OFF(void)
{
	DioIf_WriteChannel(HW_DIO_COMP_12V_DEN, DIOIF_PIN_LOW);
}
/*MCU_Hold_on*/
void HwIO_MCU_Hold_on_EN(void)
{
	DioIf_WriteChannel(HW_DIO_MCU_Hold_on, DIOIF_PIN_HIGH);
}
void HwIO_MCU_Hold_on_DEN(void)
{
	DioIf_WriteChannel(HW_DIO_MCU_Hold_on, DIOIF_PIN_LOW);
}
/*VCC_48V_EN*/
void HwIO_VCC_46V_EN_ON(void)
{
	DioIf_WriteChannel(HW_DIO_VCC_46V_EN, DIOIF_PIN_HIGH);
}
void HwIO_VCC_46V_EN_OFF(void)
{
	DioIf_WriteChannel(HW_DIO_VCC_46V_EN, DIOIF_PIN_LOW);
}
/*KL30_AD_EN*/
void HwIO_KL30_AD_EN_High(void)
{
	DioIf_WriteChannel(HW_DIO_KL30_AD_EN, DIOIF_PIN_HIGH);
}
void HwIO_KL30_AD_EN_Low(void)
{
	DioIf_WriteChannel(HW_DIO_KL30_AD_EN, DIOIF_PIN_LOW);
}
/*HW_12V_DEN*/
void HwIO_HW_12V_DEN_ON(void)
{
	DioIf_WriteChannel(HW_DIO_HW_12V_DEN, DIOIF_PIN_HIGH);
}
void HwIO_HW_12V_DEN_OFF(void)
{
	DioIf_WriteChannel(HW_DIO_HW_12V_DEN, DIOIF_PIN_LOW);
}
/*HALL_5V_EN*/
void HwIO_HALL_5V_EN_ON(void)
{
	DioIf_WriteChannel(HW_DIO_HALL_5V_EN, DIOIF_PIN_HIGH);
}
void HwIO_HALL_5V_EN_OFF(void)
{
	DioIf_WriteChannel(HW_DIO_HALL_5V_EN, DIOIF_PIN_LOW);
}
/*HF_12V_DEN*/
void HwIO_HF_12V_DEN_ON(void)
{
	DioIf_WriteChannel(HW_DIO_HF_12V_DEN, DIOIF_PIN_HIGH);
}
void HwIO_HF_12V_DEN_OFF(void)
{
	DioIf_WriteChannel(HW_DIO_HF_12V_DEN, DIOIF_PIN_LOW);
}
/*MCU_LEDDRV_EN*/
void HwIO_MCU_LEDDRV_EN_ON(void)
{
	DioIf_WriteChannel(HW_DIO_MCU_LEDDRV_EN, DIOIF_PIN_HIGH);
}
void HwIO_MCU_LEDDRV_EN_OFF(void)
{
	DioIf_WriteChannel(HW_DIO_MCU_LEDDRV_EN, DIOIF_PIN_LOW);
}
/*MCU_CAN_EN*/
void HwIO_MCU_CAN_EN_ON(void)
{
	DioIf_WriteChannel(HW_DIO_MCU_CAN_EN, DIOIF_PIN_HIGH);
}
void HwIO_MCU_CAN_EN_OFF(void)
{
	DioIf_WriteChannel(HW_DIO_MCU_CAN_EN, DIOIF_PIN_LOW);
}
/*MCU_CAN_STBn*/
void HwIO_MCU_CAN_STBn_High(void)
{
	DioIf_WriteChannel(HW_DIO_MCU_CAN_STBn, DIOIF_PIN_HIGH);
}
void HwIO_MCU_CAN_STBn_Low(void)
{
	DioIf_WriteChannel(HW_DIO_MCU_CAN_STBn, DIOIF_PIN_LOW);
}

/*MCU_PD_SLPn*/
void HwIO_MCU_PD_SLPn_Enable(void)
{
	DioIf_WriteChannel(HW_DIO_MCU_PD_SLPn, DIOIF_PIN_HIGH);
}
void HwIO_MCU_PD_SLPn_Disable(void)
{
	DioIf_WriteChannel(HW_DIO_MCU_PD_SLPn, DIOIF_PIN_LOW);
}

/*FAN_12V_DEN*/
void HwIO_FAN_12V_DEN_Enable(void)
{
	DioIf_WriteChannel(HW_DIO_FAN_12V_DEN, DIOIF_PIN_HIGH);
}
void HwIO_FAN_12V_DEN_Disable(void)
{
	DioIf_WriteChannel(HW_DIO_FAN_12V_DEN, DIOIF_PIN_LOW);
}

/**********************************INPUT*********************************/
/*HW_REV0*/
uint8_t HwIO_GetHW_REV0(void)
{
	uint8_t Rtn = 0;
	Rtn = DioIf_ReadChannel(HW_DIO_HW_REV0);
	return Rtn;
}
/*HW_REV1*/
uint8_t HwIO_GetHW_REV1(void)
{
	uint8_t Rtn = 0;
	Rtn = DioIf_ReadChannel(HW_DIO_HW_REV1);
	return Rtn;
}
/*HALL_MCU_PWM*/
#if 0
uint8_t HwIO_GetHALL_MCU_PWM(void)
{
	uint8_t Rtn = 0;
	Rtn = DioIf_ReadChannel(HW_DIO_HALL_MCU_PWM);
	return Rtn;
}
#endif 
/*PD_MCU_FLTn*/
uint8_t HwIO_GetPD_MCU_FLTn(void)
{
	uint8_t Rtn = 0;
	Rtn = DioIf_ReadChannel(HW_DIO_PD_MCU_FLTn);
	return Rtn;
}
/*LEDDRV_MCU_FLTn1*/
uint8_t HwIO_GetLEDDRV_MCU_FLTn1(void)
{
	uint8_t Rtn = 0;
	Rtn = DioIf_ReadChannel(HW_DIO_LEDDRV_MCU_FLTn1);
	return Rtn;
}
/*LEDDRV_MCU_FLTn2*/
uint8_t HwIO_GetLEDDRV_MCU_FLTn2(void)
{
	uint8_t Rtn = 0;
	Rtn = DioIf_ReadChannel(HW_DIO_LEDDRV_MCU_FLTn2);
	return Rtn;
}
/*CAN_MCU_ERRn*/
uint8_t HwIO_GetCAN_MCU_ERRn(void)
{
	uint8_t Rtn = 0;
	Rtn = DioIf_ReadChannel(HW_DIO_CAN_MCU_ERRn);
	return Rtn;
}



/*EOF*/

