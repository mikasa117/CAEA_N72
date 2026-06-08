/*******************************************************************************
|  File Name:  STD_SrCfg.h
|  Description:  Implementation of the Sensor Ctr Config Management
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


#if !defined (_STD_SR_CFG_H)
#define _STD_SR_CFG_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "SysTypes.h"

/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
/*Sensor Battery Mode limit condition*/
#define SRCFG_ENABLE								(1u)
#define SRCFG_DISABLE								(0u)

/*Sensor Channel index*/
#define SRCFG_TEMP_TFT_NTC_ENABLE				SRCFG_DISABLE /*used TFT temprature */
#define SRCFG_TEMP_DAT2_ENABLE					SRCFG_DISABLE/* all below un-used*/
#define SRCFG_TEMP_DAT3_ENABLE					SRCFG_DISABLE
#define SRCFG_TEMP_DAT4_ENABLE					SRCFG_DISABLE
#define SRCFG_TEMP_DAT5_ENABLE					SRCFG_DISABLE
#define SRCFG_TEMP_DAT6_ENABLE					SRCFG_DISABLE
/*CX810*/
#define SRCFG_TEMP_TS1_NTC_ENABLE               SRCFG_ENABLE/*TS1_AD*/
#define SRCFG_TEMP_TS2_NTC_ENABLE               SRCFG_ENABLE/*TS2_AD*/
#define SRCFG_TEMP_PCB_NTC_ENABLE               SRCFG_ENABLE/*PCB_TEMP_AD*/

#if ((SYS_ECCTYPE == SYS_C2VF02) || (SYS_ECCTYPE == SYS_C2VF02A) || (SYS_ECCTYPE == SYS_C2SF02A) || (SYS_ECCTYPE == SYS_C2WF02))
#define SRCFG_TEMP_INCAR_ENABLE					SRCFG_DISABLE
#endif
#if ((SYS_ECCTYPE == SYS_C2FF02) || (SYS_ECCTYPE == SYS_C2YF02))
#define SRCFG_TEMP_INCAR_ENABLE					SRCFG_DISABLE
#endif

#define SRCFG_BATTERY_MODE_LIMIT_ENABLE				SRCFG_DISABLE

#define SRCFG_TEMP_MAX_NUM			(2u) /*un-used*/
/*******************************************************************************
|    Enum Definition
|******************************************************************************/
typedef enum
{

/*TS1 TABLE CLASS*/
#if (SRCFG_TEMP_TS1_NTC_ENABLE == SRCFG_ENABLE)
    SRCFG_TEMP_TS1_NTC_CH,
#endif
/*TS2 TABLE CLASS*/
#if (SRCFG_TEMP_TS2_NTC_ENABLE == SRCFG_ENABLE)
    SRCFG_TEMP_TS2_NTC_CH,
#endif
#if (SRCFG_TEMP_PCB_NTC_ENABLE == SRCFG_ENABLE)
    SRCFG_TEMP_PCB_NTC_CH,
#endif
/*AD TABLE CLASS*/
#if (SRCFG_TEMP_TFT_NTC_ENABLE == SRCFG_ENABLE)
    SRCFG_TEMP_TFT_NTC_CH,
#endif
	
#if (SRCFG_TEMP_DAT2_ENABLE == SRCFG_ENABLE)
    SRCFG_TEMP_DAT2_CH,
#endif

#if (SRCFG_TEMP_DAT3_ENABLE == SRCFG_ENABLE)
    SRCFG_TEMP_DAT3_CH,
#endif

#if (SRCFG_TEMP_DAT4_ENABLE == SRCFG_ENABLE)
    SRCFG_TEMP_DAT4_CH,
#endif

#if (SRCFG_TEMP_DAT5_ENABLE == SRCFG_ENABLE)
    SRCFG_TEMP_DAT5_CH,
#endif

#if (SRCFG_TEMP_DAT6_ENABLE == SRCFG_ENABLE)
    SRCFG_TEMP_DAT6_CH,
#endif
    SRCFG_CH_MAX_NUM
} SRCFG_CH_Enum;

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

