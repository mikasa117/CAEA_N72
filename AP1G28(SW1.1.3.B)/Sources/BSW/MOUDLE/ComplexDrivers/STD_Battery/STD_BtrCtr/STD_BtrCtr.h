/*******************************************************************************
|  File Name:  STD_BtrCtr.h
|  Description:  Implementation of the Battery voltage Management
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

#if !defined (_STD_BTRCTR_H)
#define _STD_BTRCTR_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
//#include "Std_Types.h"
#include "STD_BtrCtr_Cfg.h"
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


extern void BTRCTR_InitMemory(void);
extern void BTRCTR_InitKamMemory( void );

extern void BTRCTR_ModeFunction(void);
extern uint16 BTRCTR_GetSysBatteryVolt(void);
extern uint8 BTRCTR_GetSysBatteryModeAStatus(void);
extern uint8 BTRCTR_GetSysBatteryModeBStatus(void);

#if (BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_MODE_C_ENABLE)
extern uint8 BTRCTR_GetSysBatteryModeCStatus(void);
#endif
#if (BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_MODE_D_ENABLE)
extern uint8 BTRCTR_GetSysBatteryModeDStatus(void);
#endif
#if (BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_LOW_VOL_ENABLE)
extern uint8 BTRCTR_GetSysLowVoltageStatus(void);
extern uint8 BTRCTR_GetHighVoltageStatus(void);
#endif
#if (BTRCTR_ENABLE == BTRCTR_LOAD_BATTERY_ENABLE)
extern uint8 BTRCTR_GetLoadBatteryModeAStatus(void);
extern uint8 BTRCTR_GetLoadBatteryModeBStatus(void);
#if (BTRCTR_ENABLE == BTRCTR_LOAD_BATTERY_LOW_VOL_ENABLE)
extern uint8 BTRCTR_GetLoadLowVoltageStatus(void);
#endif
#endif
extern uint16 BTRCTR_Get_KL30_VoltValue(void); // accuracy=0.1v

#endif
/*EOF*/
