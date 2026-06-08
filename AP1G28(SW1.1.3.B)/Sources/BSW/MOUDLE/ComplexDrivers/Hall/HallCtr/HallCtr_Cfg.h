
/*******************************************************************************
|  File Name:  HallCtr_Cfg.h
|  Description:  Implementation of the Battery voltage Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| WCj           Chaojian Wang         CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2025-11-29    01.00.00     WCj       Creation
|
|******************************************************************************/

#if !defined (_HALL_CTR_CFG_H)
#define _HALL_CTR_CFG_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_AdcM.h"

/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define HALL_CTR_CODE_RAM	//__attribute__ ((section(".BSW_RAM_DATA")))
#define HALL_CTR_CODE_KAM	//__attribute__ ((section(".BSW_KAM_DATA")))



#define HALLCTR_GetBatteryAdValue()                      ADCM_GetCurrentValue((uint8)ADCMCFG_HALL_5V_AD_CH)


#define HALLCTR_TASK_PERIOD                              ((uint16)10u)
#define	BTRCTR_5msTASK_PERIOD							 (5u)

#define HALLCTR_FILTER_40MS                              (uint8)((uint16)40u/HALLCTR_TASK_PERIOD)
#define HALLCTR_FILTER_1200MS                            (uint8)((uint16)1200u/HALLCTR_TASK_PERIOD)
#define HALLCTR_FILTER_5000MS                            (uint8)((uint16)5000u/HALLCTR_TASK_PERIOD)


#define HALLCTR_FILTER_TIME_FAST                         HALLCTR_FILTER_40MS
#define HALLCTR_FILTER_TIME_LONG                         HALLCTR_FILTER_5000MS


/******************/
//(HALL_5V-0.03)*560.5
#define BTRCTR_SYS_HALL_5V_HIGH_VOLT                (3066u)     /* (5.5v-0.03)*560.5 */
#define BTRCTR_SYS_HALL_5V_LOW_VOLT                  (2505u)     /* (4.5V  -0.03)*560.5 */

/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Table Definition
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/

#endif
/*EOF*/
