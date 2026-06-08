/*******************************************************************************
|  File Name:  AdcM.h
|  Description:  Implementation of the Adc Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           YaJun Xia          CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2016-10-18    01.00.00     XYJ       Creation
|
|******************************************************************************/

#if !defined (_STD_ADCM_H)
/* polyspace<MISRA-C3:2.5:Not a defect:Other> No fluence *//* polyspace<MISRA-C3:21.1:Not a defect:Other> No fluence */
#define _STD_ADCM_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Typedef.h"
#include "STD_AdcMCfg.h"

/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

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
|    Table Definition
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/


extern void ADCM_InitMemory( void );
extern void ADCM_ADC0_StartFunction( void );
extern void ADCM_MainFunction( void );

extern void ADCM_CallbackSampleValue( uint8 ucChannal, uint16 usSampleValue );

extern uint16 ADCM_GetValidValue( uint8 ucChannal );
extern uint16 ADCM_GetCurrentValue( uint8 ucChannal );

#if (ADCMCFG_CALLBACK_EN == 1u)
extern void ADCB_InitMemory(void);
extern void ADCB0_SamplingCallBack(void);
extern void ADCB1_SamplingCallBack(void);
#endif



#endif
/*EOF*/
