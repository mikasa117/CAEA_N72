/*******************************************************************************
|  File Name:  VOLT_AdCtr.c
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
| 2026-01-28    01.00.00     WCj       Creation
|
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "VOLT_AdCtr.h"
#include "STD_AdcM.h"
#include "STD_Lib.h"


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
|    Static local KAM variables Declaration
|******************************************************************************/


/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Table Const Definition
|******************************************************************************/

/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/
//static uint16 VOLT_AdCtr_Get_46V_Value(void); // mV 46V change COMP_12V_AD

/*******************************************************************************
|    Function Source Code
|******************************************************************************/

uint16 VOLT_AdCtr_Get_46V_Value(void) // mV 46V change COMP_12V_AD
{

    uint16 tempVOLT = 0u;
    uint16 tempAdcValue = 0u;
    float tempDerivedValue = 0;
    tempAdcValue = ADCM_GetCurrentValue(ADCMCFG_VCC_46V_AD_CH);
    tempDerivedValue = (tempAdcValue * 55.0) / 4096;
    tempDerivedValue = tempDerivedValue * 1000;
    tempVOLT = (uint16)tempDerivedValue;
    return tempVOLT;
}

uint16 VOLT_AdCtr_Get_COMP_12V_AD_VOLT_Value(void) // mV
{
    uint16 TempBatteryAd = 0u;
    float tempDerivedValue = 0;
    uint16 tempVOLT = 0u;
    TempBatteryAd = ADCM_GetCurrentValue(ADCMCFG_VCC_46V_AD_CH);
    tempDerivedValue = (TempBatteryAd / 153.9);
    tempDerivedValue = tempDerivedValue * 1000;
    tempVOLT = (uint16)tempDerivedValue;
    return tempVOLT;
}

uint16 VOLT_AdCtr_Get_COMP_12V_AD_VOLT_Souce_Value(void) // mV
{
    uint16 TempBatteryAd_Tmp = 0u;
    float tempDerivedValue = 0;
    uint16 tempVOLT = 0u;
    #if 0
    TempBatteryAd = ADCM_GetCurrentValue(ADCMCFG_VCC_46V_AD_CH);
    tempDerivedValue = (TempBatteryAd / 153.9);
    tempDerivedValue = tempDerivedValue * 1000;
    tempVOLT = (uint16)tempDerivedValue;
    #endif
    TempBatteryAd_Tmp = ADCM_GetCurrentValue(ADCMCFG_VCC_46V_AD_CH);
    tempDerivedValue = (uint32)(TempBatteryAd_Tmp*1000 / 2066);
    tempVOLT = (uint16)tempDerivedValue;
    return tempVOLT;
}
/*EOF*/
