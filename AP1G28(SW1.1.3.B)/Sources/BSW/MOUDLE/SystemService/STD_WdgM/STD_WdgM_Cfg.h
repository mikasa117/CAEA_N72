/*******************************************************************************
|  File Name:  SysM_Cfg.h
|  Description:  Implementation of the System Config Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| WCj           WangChaojian               CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2025-10-31    01.00.01     WCj       Creation
|
|******************************************************************************/


#if !defined (_STD_WDGM_CFG_H)
#define _STD_WDGM_CFG_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
//#include "Std_Types.h"
#include "STD_Interface.h"
#include "STD_Lib.h"
#include "Mcal_App.h"

/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define WDGM_CODE_RAM	//__attribute__ ((section(".BSW_RAM_DATA")))
#define WDGM_CODE_KAM	//__attribute__ ((section(".BSW_KAM_DATA")))

#define WDGM_DISABLE	(0u)
#define WDGM_ENABLE		(1u)

#define	WDGM_EN_CLASS					WDGM_ENABLE

#define WDGM_MODE_OFF		(0u)
#define WDGM_MODE_SLOW		(1u)
#define WDGM_MODE_FAST		(2u)

#define WDGM_DEVICE_NUM		(1u)
#define WDGM_TRIGGER_PERIOD		   (500U)/*500us*/
#define WDGM_TIMEOUT_CNT	(30000u/WDGM_TRIGGER_PERIOD)


#define WDGM_EnterCriticalArea_0() LIB_ENTER_EXCLUSIVE_AREA_0()
#define WDGM_LeaveCriticalArea_0() LIB_EXIT_EXCLUSIVE_AREA_0()
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
