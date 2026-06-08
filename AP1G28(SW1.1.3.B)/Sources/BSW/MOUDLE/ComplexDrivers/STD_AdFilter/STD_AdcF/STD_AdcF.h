/*******************************************************************************
|  File Name:  STD_AdcF.h
|  Description:  Implementation of the Adc Filter Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           YaJun Xia              CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2016-09-30    01.00.00     XYJ       Creation
|
|******************************************************************************/

#if !defined (_STD_ADCF_H)
/* polyspace<MISRA-C3:2.5:Not a defect:Other> No fluence *//* polyspace<MISRA-C3:21.1:Not a defect:Other> No fluence */
#define _STD_ADCF_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Typedef.h"
#include "STD_AdcF_Cfg.h"
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


#if (ADCFCFG_CLASS_BUDDLE_MIDDLE == ADCFCFG_ENABLE)
extern void ADCF_BubbleSortMiddleConversion(uint8 ucChannel, uint16 usInsertValue);
#endif
#if (ADCFCFG_CLASS_BUDDLE_AVERAGE == ADCFCFG_ENABLE)
extern void ADCF_BubbleSortAverageConversion(uint8 ucChannel, uint16 usInsertValue);
#endif
#if ( ADCFCFG_CLASS_SIMPLE_AVERAGE == ADCFCFG_ENABLE)
void ADCF_SimpleAverageConversion(uint8 ucChannel, uint16 usInsertValue);
#endif
#if ( ADCFCFG_CLASS_FAST_AVERAGE == ADCFCFG_ENABLE)
void ADCF_FastAverageConversion(uint8 ucChannel, uint16 usInsertValue);
#endif
extern uint16 ADCF_GetValidValue(uint8 ucChannel);
extern uint16 ADCF_GetCurrentValue(uint8 ucChannel);
extern void ADCF_InitMemory(void);



#endif
/*EOF*/
