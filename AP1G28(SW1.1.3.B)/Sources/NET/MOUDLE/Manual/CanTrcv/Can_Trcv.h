
/*******************************************************************************
|  File Name: 
|  Description: Implementation of the AUTOSAR CAN Interface
|-------------------------------------------------------------------------------
|  (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      ---------------------  -----------------------------------------
| qxj           qiuxiaojian            CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 2014-11-10    0.01         fsl       firstimplementation
|******************************************************************************/
#ifndef CAN_TRCV_H
#define CAN_TRCV_H
/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Platform_Types.h"
#include "ccl_inc.h"
#include "CanNm.h"
/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define CeCanTrcv_e_Standbymode  1u
#define CeCanTrcv_e_Normalmode  0u
/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/


/*******************************************************************************
|    Global Variable with extern linkage
|******************************************************************************/


/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/

extern void CanTrcv_WakeupClearFlag(void);
extern void CanTrcv_DisableWakeup(void);
extern void CanTrcv_EnableWakeup(void);

extern void CanTrcv_DisableTrcv(void);
extern void CanTrcv_WakeUpTrcv(void);
extern uint8 CanTrcv_CheckWakeup(void);
extern void CanTrcv_DummyFun(void);


extern void CanTrcv_MainFunction(void);
extern uint8 GetCanTrcv_CurrentMode(void);
/* upper layer informs transceiver about wakeup mode through this API */
extern void CanTrcv_SetWakeupMode(uint8 mode);








#endif
