/*******************************************************************************
|  File Name:  STD_AdcMCfg.h
|  Description:  Implementation of the AdcM Config
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
| 2017-01-05    01.00.00     XYJ       Creation
|
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_AdcMCfg.h"
#include "STD_AdcF.h"
//#include "BYD_MR_Include.h"
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


const TsADCF_h_CfgType stAdcM_CfgTable[ADCMCFG_CH_MAX_NUM] =/*PRQA S 3211*/
{
    /*adc1*/
#if (ADCMCFG_PA_BUS_I_ENABLE == ADCMCFG_ENABLE)
    {ADCMCFG_PA_BUS_I_COLLECT_NUM,       ADCMCFG_PA_BUS_I_S_OFFSET,       &ADCF_BubbleSortMiddleConversion},
#endif
#if (ADCMCFG_PA_W_I_ENABLE == ADCMCFG_ENABLE)
    {ADCMCFG_PA_W_I_COLLECT_NUM,         ADCMCFG_PA_W_I_S_OFFSET,         &ADCF_BubbleSortMiddleConversion},
#endif
#if (ADCMCFG_PA_V_I_ENABLE == ADCMCFG_ENABLE)
    {ADCMCFG_PA_V_I_COLLECT_NUM,         ADCMCFG_PA_V_I_S_OFFSET,         &ADCF_BubbleSortMiddleConversion},
#endif
#if (ADCMCFG_FAN_I_ENABLE == ADCMCFG_ENABLE)
    {ADCMCFG_FAN_I_COLLECT_NUM,          ADCMCFG_FAN_I_S_OFFSET,          &ADCF_BubbleSortMiddleConversion},
#endif
    /*adc0*/
#if (ADCMCFG_KL30_ENABLE == ADCMCFG_ENABLE)
    {ADCMCFG_KL30_COLLECT_NUM,           ADCMCFG_KL30_S_OFFSET,           &ADCF_BubbleSortMiddleConversion},
#endif
#if (ADCMCFG_HALL_5V_ENABLE == ADCMCFG_ENABLE)
    {ADCMCFG_HALL_5V_COLLECT_NUM,        ADCMCFG_HALL_5V_S_OFFSET,        &ADCF_BubbleSortMiddleConversion},
#endif
#if (ADCMCFG_COMP_12V_ENABLE == ADCMCFG_ENABLE)
    {ADCMCFG_COMP_12V_COLLECT_NUM,       ADCMCFG_COMP_12V_S_OFFSET,       &ADCF_BubbleSortMiddleConversion},
#endif
#if (ADCMCFG_COMP_12V_IS_ENABLE == ADCMCFG_ENABLE)
    {ADCMCFG_COMP_12V_IS_COLLECT_NUM,    ADCMCFG_COMP_12V_IS_S_OFFSET,    &ADCF_BubbleSortMiddleConversion},
#endif
#if (ADCMCFG_FAN_12V_ENABLE == ADCMCFG_ENABLE)
    {ADCMCFG_FAN_12V_COLLECT_NUM,        ADCMCFG_FAN_12V_S_OFFSET,        &ADCF_BubbleSortMiddleConversion},
#endif
#if (ADCMCFG_TS3_ENABLE == ADCMCFG_ENABLE)
    {ADCMCFG_TS3_COLLECT_NUM,            ADCMCFG_TS3_S_OFFSET,            &ADCF_BubbleSortMiddleConversion},
#endif
#if (ADCMCFG_PCB_TEMP_ENABLE == ADCMCFG_ENABLE)
    {ADCMCFG_PCB_TEMP_COLLECT_NUM,       ADCMCFG_PCB_TEMP_S_OFFSET,       &ADCF_BubbleSortMiddleConversion},
#endif
#if (ADCMCFG_VCC_48V_ENABLE == ADCMCFG_ENABLE)
    {ADCMCFG_VCC_48V_COLLECT_NUM,        ADCMCFG_VCC_48V_S_OFFSET,        &ADCF_BubbleSortMiddleConversion},
#endif
#if (ADCMCFG_HW_12V_IS_ENABLE == ADCMCFG_ENABLE)
    {ADCMCFG_HW_12V_IS_COLLECT_NUM,      ADCMCFG_HW_12V_IS_S_OFFSET,      &ADCF_BubbleSortMiddleConversion},
#endif
#if (ADCMCFG_HW_12V_ENABLE == ADCMCFG_ENABLE)
    {ADCMCFG_HW_12V_COLLECT_NUM,         ADCMCFG_HW_12V_S_OFFSET,         &ADCF_BubbleSortMiddleConversion},
#endif
#if (ADCMCFG_HF_12V_ENABLE == ADCMCFG_ENABLE)
    {ADCMCFG_HF_12V_COLLECT_NUM,         ADCMCFG_HF_12V_S_OFFSET,         &ADCF_BubbleSortMiddleConversion},
#endif
#if (ADCMCFG_HF_12V_IS_ENABLE == ADCMCFG_ENABLE)
    {ADCMCFG_HF_12V_IS_COLLECT_NUM,      ADCMCFG_HF_12V_IS_S_OFFSET,      &ADCF_BubbleSortMiddleConversion},
#endif
#if (ADCMCFG_TS1_ENABLE == ADCMCFG_ENABLE)
    {ADCMCFG_TS1_COLLECT_NUM,            ADCMCFG_TS1_S_OFFSET,            &ADCF_BubbleSortMiddleConversion},
#endif
#if (ADCMCFG_TS2_ENABLE == ADCMCFG_ENABLE)
    {ADCMCFG_TS2_COLLECT_NUM,            ADCMCFG_TS2_S_OFFSET,             &ADCF_BubbleSortMiddleConversion},
#endif
};


/*******************************************************************************
|    Table Const Definition
|******************************************************************************/

/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/




/*EOF*/
