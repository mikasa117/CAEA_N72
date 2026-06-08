/*******************************************************************************
|  File Name:  HallCtr.c
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

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "AMP_AdCtr.h"
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



/*******************************************************************************
|    Function Source Code
|******************************************************************************/

uint16 AMP_AdCtr_Get_HeatFilm_Value(void)
{
    uint16 tempAMP = 0u;
    uint16 tempAdcValue = 0u;
    tempAdcValue = ADCM_GetCurrentValue(ADCMCFG_HF_12V_IS_AD_CH);

    tempAMP = (uint16)((tempAdcValue / 4096.0) * 7250u);

    return tempAMP;
}

uint16 AMP_AdCtr_Get_HeatWire_Value(void) // mA
{
    uint16 tempAMP = 0u;
    uint16 tempAdcValue = 0u;
    tempAdcValue = ADCM_GetCurrentValue(ADCMCFG_HW_12V_IS_AD_CH);

    tempAMP = (uint16)((tempAdcValue / 4096.0) * 898u);

    return tempAMP;
}

uint16 AMP_AdCtr_Get_COMP_12V_Value(void) // mA
{
    uint16 tempAMP = 0u;
    uint16 tempAdcValue = 0u;
    tempAdcValue = ADCM_GetCurrentValue(ADCMCFG_COMP_12V_IS_AD_CH);

    tempAMP = (uint16)((tempAdcValue / 4096.0) * 12950u);

    return tempAMP;
}

uint16 AMP_AdCtr_Get_FAN_Value(void) // mA
{
    uint16 tempAMP = 0u;
    uint16 tempAdcValue = 0u;
    tempAdcValue = ADCM_GetCurrentValue(ADCMCFG_FAN_12V_AD_CH);

    tempAMP = (uint16)((tempAdcValue / 4096.0) * 350u);

    return tempAMP;
}
/*EOF*/
