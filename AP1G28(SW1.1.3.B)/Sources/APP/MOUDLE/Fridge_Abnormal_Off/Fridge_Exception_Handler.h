/*******************************************************************************
||  File Name: Fridge_Exception_Handler.h
||  Description: Header file for AUTOSAR Fridge Abnormal Off
||-------------------------------------------------------------------------------
||  (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
||     All rights are reserved by CAEA.
||-------------------------------------------------------------------------------
|| Initials      Name                   Company
|| --------      ---------------------  -----------------------------------------
|| 	                               CAEA
||-------------------------------------------------------------------------------
||               R E V I S I O N   H I S T O R Y
||-------------------------------------------------------------------------------
|| Date          Version      Author    Description
|| ------------  --------     -------   -----------------------------------------
|| 2025.10.20     V1.0         SSS                                               
||
||******************************************************************************/

#ifndef FRIDGE_ABNORMAL_OFF_H
#define FRIDGE_ABNORMAL_OFF_H
#include "CAEA_Types.h"
/*******************************************************************************
||    Other Header File Inclusion
||******************************************************************************/ 

/*******************************************************************************
||    Macro Definition
||******************************************************************************/

/*******************************************************************************
||    Enum Definition
||******************************************************************************/

/*******************************************************************************
||    Typedef Definition
||******************************************************************************/

/*******************************************************************************
||    Global variables Declaration
||******************************************************************************/

/*******************************************************************************
||    Extern variables and functions declaration
||******************************************************************************/

// /********************************** Can Initialization **********************************/
// extern void RTE_NET_Can_Init(void);

// /********************************** Can Read Functions **********************************/
// /***************Start of 0x3ED************************/
// extern uint8 RTE_NET_Can_Read_FridgeUnlockCtrl(void);
// extern uint8 RTE_NET_Can_Read_FridgeDoorWarnTimeSet(void);
// extern uint8 RTE_NET_Can_Read_FridgeChdLockReq(void);
// extern uint8 RTE_NET_Can_Read_EgySaveModReq(void);
// extern uint8 RTE_NET_Can_Read_FridgeWorkReq(void);
// extern uint8 RTE_NET_Can_Read_FridgeQFunReq(void);
// extern uint8 RTE_NET_Can_Read_ContinueWorkSw(void);
// extern uint8 RTE_NET_Can_Read_ContinueWorkTimeSet(void);
// extern uint8 RTE_NET_Can_Read_FridgeUVLedReq(void);
// extern uint8 RTE_NET_Can_Read_FridgeUVLedWorkTimeSet(void);
// extern uint8 RTE_NET_Can_Read_FridgeModeReq(void);
// extern uint8 RTE_NET_Can_Read_FridgeCoolTempReq(void);
// extern uint8 RTE_NET_Can_Read_FridgeHeatTempReq(void);
// extern uint8 RTE_NET_Can_Read_VrhcuExOffReas(void);
// extern uint8 RTE_NET_Can_Read_VrhcuONReas(void);
// /***************End of 0x3ED***************/

// /***************Start of 0x288***************/
// extern uint8 RTE_NET_Can_Read_BcmPwrStsFb(void);
// /***************End of 0x288***************/

// /***************Start of 0x3D1***************/
// extern uint8 RTE_NET_Can_Read_DcdcOperSts(void);
// /***************End of 0x3D1***************/

// /***************Start of 0x3D3***************/
// extern uint8 RTE_NET_Can_Read_BcuOperMod(void);
// /***************End of 0x3D3***************/

// /********************************** Can Main Functions **********************************/
// extern void RTE_NET_Can_10msMainFunction(void);
// extern void RTE_NET_Can_20msMainFunction(void);

#endif /* FRIDGE_ABNORMAL_OFF_H */
