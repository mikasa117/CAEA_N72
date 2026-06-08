/*******************************************************************************
|  File Name:  STD_BtrM.h
|  Description:  Implementation of the Battery Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XZS           Zhangsheng Xia         CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2017-02-22    01.00.00     XZS       Creation
|
|******************************************************************************/

#if !defined (_STD_BTRM_H)
#define _STD_BTRM_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
//#include "Std_Types.h"

#include "STD_BtrM_Cfg.h"

/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define	BTRM_GetSysBatteryModeAStatus			BTRCTR_GetSysBatteryModeAStatus
#define	BTRM_GetSysBatteryModeBStatus			BTRCTR_GetSysBatteryModeBStatus
#define	BTRM_GetSysBatteryModeCStatus			BTRCTR_GetSysBatteryModeCStatus
#define	BTRM_GetSysLowVoltageStatus				BTRCTR_GetSysLowVoltageStatus
#define BTRM_GetHighVoltageStatus                BTRCTR_GetHighVoltageStatus
#if (BTRCTR_ENABLE == BTRCTR_LOAD_BATTERY_ENABLE)
#define	BTRM_GetLoadBatteryModeAStatus			BTRCTR_GetLoadBatteryModeAStatus
#define	BTRM_GetLoadBatteryModeBStatus			BTRCTR_GetLoadBatteryModeBStatus
#define	BTRM_GetLoadLowVoltageStatus			BTRCTR_GetLoadLowVoltageStatus
#endif

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

extern void BTRM_InitMemory(void);
extern void BTRM_InitKamMemory( void );
extern void BTRM_MainFunction(void);

#endif
/*EOF*/
