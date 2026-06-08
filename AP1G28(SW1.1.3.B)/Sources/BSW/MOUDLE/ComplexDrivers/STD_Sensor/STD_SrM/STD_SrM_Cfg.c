/*******************************************************************************
|  File Name:  STD_SrM_Cfg.c
|  Description:  Implementation of the Sensor Management config
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           xiayajun               CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2018-06-21    01.00.00     XYJ       Creation
| 2019-12-27	   /	     XJW       Modified for AC-DI18
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_SrM_Cfg.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#if (SRM_ENABLE == SRM_EN_CLASS)

/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Global variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/

/*******************************************************************************
|    Extern variables and functions declaration
|******************************************************************************/

/*******************************************************************************
|    Extern variables and functions declaration
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/

const SrMChanCfg_Struct stSrMChanCfgArray[SRCFG_CH_MAX_NUM] = /*PRQA S 3211*/
    {

/*TS1 TABLE ClASS*/
#if (SRCFG_TEMP_TS1_NTC_ENABLE == SRCFG_ENABLE)
        {(uint8)SRADCTR_TABLE_TEMP_TS1_NTC_CH, &SRADCTR_TableGetValidValue, &SRADCTR_TableGetValidStatus},
#endif
#if (SRCFG_TEMP_TS2_NTC_ENABLE == SRCFG_ENABLE)
        {(uint8)SRADCTR_TABLE_TEMP_TS2_NTC_CH, &SRADCTR_TableGetValidValue, &SRADCTR_TableGetValidStatus},
#endif
#if (SRCFG_TEMP_PCB_NTC_ENABLE == SRCFG_ENABLE)
        {(uint8)SRADCTR_TABLE_TEMP_PCB_NTC_CH, &SRADCTR_TableGetValidValue, &SRADCTR_TableGetValidStatus},
#endif
/*AD TABLE ClASS*/
#if (SRCFG_TEMP_TFT_NTC_ENABLE == SRCFG_ENABLE)
        {(uint8)SRADCTR_TABLE_TEMP_TFT_NTC_CH, &SRADCTR_TableGetValidValue, &SRADCTR_TableGetValidStatus},
#endif

        /*AD LINE ClASS unused*/

        /*PWM ClASS unused*/

};
#endif


/*EOF*/

