/*******************************************************************************
|  File Name:  DioIf_Cfg.h
|  Description:  Implementation of the DioIf Config Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| wcj            wcj                    CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 2025-11-15    00.00.01     wcj       Creation
|******************************************************************************/
	
#ifndef _MCAL_DIOIF_CFG_H_
#define _MCAL_DIOIF_CFG_H_

/*******************************************************************************
|	 Other Header File Inclusion
|******************************************************************************/
#include "Typedef.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define DIOIF_PIN_LOW		(0u)
#define DIOIF_PIN_HIGH		(1u)
#define DIOIF_PIN_MAX_NUM	(16u)

#define HW_DIO_PORTA_NUM	(0u)
#define HW_DIO_PORTB_NUM	(32u)
#define HW_DIO_PORTC_NUM	(64u)
#define HW_DIO_PORTD_NUM	(96u)
#define HW_DIO_PORTE_NUM	(128u)



/*User Config*/
/*Output*/
/* PTE13 */
#define HW_DIO_MCU_LIN_SLPn   (HW_DIO_PORTE_NUM + 13u)

/* PTE5 */
#define HW_DIO_COMP_12V_EN    (HW_DIO_PORTE_NUM + 5u)

/* PTE4 */
#define HW_DIO_COMP_12V_DEN   (HW_DIO_PORTE_NUM + 4u)

/* PTD16 */
#define HW_DIO_MCU_Hold_on    (HW_DIO_PORTD_NUM + 16u)

/* PTD15 */
#define HW_DIO_VCC_46V_EN     (HW_DIO_PORTD_NUM + 15u)

/* PTA16 */
#define HW_DIO_KL30_AD_EN     (HW_DIO_PORTA_NUM + 16u)

/* PTD6 */
#define HW_DIO_HW_12V_DEN     (HW_DIO_PORTD_NUM + 6u)

/* PTD8 */
#define HW_DIO_HALL_5V_EN     (HW_DIO_PORTD_NUM + 8u)

/* PTE7 */
#define HW_DIO_HF_12V_DEN     (HW_DIO_PORTE_NUM + 7u)

/* PTE2 */
#define HW_DIO_MCU_LEDDRV_EN  (HW_DIO_PORTE_NUM + 2u)

/* PTA11 */
#define HW_DIO_MCU_CAN_EN     (HW_DIO_PORTA_NUM + 11u)

/* PTE1 */
#define HW_DIO_MCU_CAN_STBn   (HW_DIO_PORTE_NUM + 1u)

/* PTA17 */
#define HW_DIO_MCU_PD_SLPn    (HW_DIO_PORTA_NUM + 17u)

/* PTD7 */
#define HW_DIO_FAN_12V_DEN     (HW_DIO_PORTD_NUM + 7u)


/*Input*/
/* PTE14 */
#define HW_DIO_HW_REV0        (HW_DIO_PORTE_NUM + 14u)

/* PTE3 */
#define HW_DIO_HW_REV1        (HW_DIO_PORTE_NUM + 3u)

/* PTD10 */
#define HW_DIO_HALL_MCU_PWM   (HW_DIO_PORTD_NUM + 10u)


/* PTD4 */
#define HW_DIO_PD_MCU_FLTn    (HW_DIO_PORTD_NUM + 4u)

/* PTA15 */
#define HW_DIO_LEDDRV_MCU_FLTn1 (HW_DIO_PORTA_NUM + 15u)

/* PTE6 */
#define HW_DIO_LEDDRV_MCU_FLTn2 (HW_DIO_PORTE_NUM + 6u)

/* PTE0 */
#define HW_DIO_CAN_MCU_ERRn   (HW_DIO_PORTE_NUM + 0u)



/*Config Conmmnication Channel*/

/*Config 5180 Channel*/


/*Config System Power Channel*/
/*IGN Input*/


/*Config Load Channel*/


/*Config Sensor Channel*/



/*Config Conmmnication Channel*/


/*Config Indication En Channel */

/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef struct
{
    uint8 ucChannel;
    uint8 ucInitPinLevel;
    uint8 ucDeInitPinLevel;
}DioIfCfg_Struct;
/*******************************************************************************
|	 Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|	 Global Variable with extern linkage
|******************************************************************************/

//extern const DioIfCfg_Struct stDioIfCfg[DIOIF_PIN_MAX_NUM];
/*******************************************************************************
|	 Global Function Prototypes
|******************************************************************************/

#endif /* DIOIF_CFG_H_ */
