/*******************************************************************************
||  File Name: RTE_APP.h
||  Description: Header file for AUTOSAR APP Can Interface
||-------------------------------------------------------------------------------
||  (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
||     All rights are reserved by CAEA.
||-------------------------------------------------------------------------------
|| Initials      Name                   Company
|| --------      ---------------------  -----------------------------------------
||                                    CAEA
||-------------------------------------------------------------------------------
||               R E V I S I O N   H I S T O R Y
||-------------------------------------------------------------------------------
|| Date          Version      Author    Description
|| ------------  --------     -------   -----------------------------------------
|| 2025.10.20     V1.0         SSS                                               
||
||******************************************************************************/

#ifndef RTE_APP_H
#define RTE_APP_H
#include "CAEA_Types.h"
#include "Rte_CAN.h"
/*******************************************************************************
||    Other Header File Inclusion
||******************************************************************************/ 

/*******************************************************************************
||    Macro Definition
||******************************************************************************/
/* RTE Read Can Signal */
#define   RTE_APP_Can_Read_BcmPwrStsFb()                  (RTE_NET_Can_Read_BcmPwrStsFb())  
#define   RTE_APP_Can_Read_FridgeWorkReq()                (RTE_NET_Can_Read_FridgeWorkReq())
#define   RTE_APP_Can_Read_ContinueWorkSw()               (RTE_NET_Can_Read_ContinueWorkSw())
#define   RTE_APP_Can_Read_FridgeModeReq()                (RTE_NET_Can_Read_FridgeModeReq())
#define   RTE_APP_Can_Read_FridgeCoolTempReq()            (RTE_NET_Can_Read_FridgeCoolTempReq())
#define   RTE_APP_Can_Read_FridgeHeatTempReq()            (RTE_NET_Can_Read_FridgeHeatTempReq())
#define   RTE_APP_Can_Read_FridgeDoorWarnTimeSet()        (RTE_NET_Can_Read_FridgeDoorWarnTimeSet())
#define   RTE_APP_Can_Read_FridgeQFunReq()                (RTE_NET_Can_Read_FridgeQFunReq())
#define   RTE_APP_Can_Read_FridgeUVLedReq()               (RTE_NET_Can_Read_FridgeUVLedReq())
#define   RTE_APP_Can_Read_FridgeUVLedWorkTimeSet()       (RTE_NET_Can_Read_FridgeUVLedWorkTimeSet())  
#define   RTE_APP_Can_Read_ContinueWorkTimeSet()          (RTE_NET_Can_Read_ContinueWorkTimeSet())
#define   RTE_APP_Can_Read_DcdcOperSts()                  (RTE_NET_Can_Read_DcdcOperSts())

/* RTE Write Can Signal */
#define   RTE_APP_Can_Write_FridgeErrSt(x)                (RTE_NET_Can_Write_FridgeErrSt(x))    
#define   RTE_APP_Can_Write_FridgeWorkSt(x)               (RTE_NET_Can_Write_FridgeWorkSt(x))
#define   RTE_APP_Can_Write_FridgeModeSt(x)               (RTE_NET_Can_Write_FridgeModeSt(x))
#define   RTE_APP_Can_Write_FridgeCoolTempSt(x)           (RTE_NET_Can_Write_FridgeCoolTempSt(x))
#define   RTE_APP_Can_Write_FridgeHeatTempSt(x)           (RTE_NET_Can_Write_FridgeHeatTempSt(x))
#define   RTE_APP_Can_Write_FridgeQFunSt(x)               (RTE_NET_Can_Write_FridgeQFunSt(x))
#define   RTE_APP_Can_Write_FridgeDoorWarnTimeSt(x)       (RTE_NET_Can_Write_FridgeDoorWarnTimeSt(x))
#define   RTE_APP_Can_Write_FridgeDoorSt(x)               (RTE_NET_Can_Write_FridgeDoorSt(x))
#define   RTE_APP_Can_Write_FridgeDoorWarnSt(x)           (RTE_NET_Can_Write_FridgeDoorWarnSt(x))
#define   RTE_APP_Can_Write_FridgeUVLedWorkSt(x)          (RTE_NET_Can_Write_FridgeUVLedWorkSt(x))
#define   RTE_APP_Can_Write_FridgeUVLedSt(x)              (RTE_NET_Can_Write_FridgeUVLedSt(x))
#define   RTE_APP_Can_Write_ContinueWorkTimeSt(x)         (RTE_NET_Can_Write_ContinueWorkTimeSt(x))
#define   RTE_APP_Can_Write_VrhcuRefrAcpTemp(x)           (RTE_NET_Can_Write_VrhcuRefrAcpTemp(x))
#define   RTE_APP_Can_Write_VrhcuOffReas(x)               (RTE_NET_Can_Write_VrhcuOffReas(x))
#define   RTE_APP_Can_Write_VrhcuRequestACOn(x)           (RTE_NET_Can_Write_VrhcuRequestACOn(x))
#define   RTE_APP_Can_Write_FridgeHeatActSt(x)            (RTE_NET_Can_Write_FridgeHeatActSt(x))

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

// /********************************** Can Write Functions **********************************/
// /***************Start of 0x3EE***************/
// extern void RTE_NET_Can_Write_FridgeErrSt(uint8 LeRteCan_u_Value);
// extern void RTE_NET_Can_Write_FridgeDoorWarnTimeSt(uint8 LeRteCan_u_Value);
// extern void RTE_NET_Can_Write_FridgeChdLockSt(uint8 LeRteCan_u_Value);
// extern void RTE_NET_Can_Write_EgySaveModSt(uint8 LeRteCan_u_Value);
// extern void RTE_NET_Can_Write_FridgeWorkSt(uint8 LeRteCan_u_Value);
// extern void RTE_NET_Can_Write_FridgeQFunSt(uint8 LeRteCan_u_Value);
// extern void RTE_NET_Can_Write_ContinueWorkTimeSt(uint8 LeRteCan_u_Value);
// extern void RTE_NET_Can_Write_FridgeDoorWarnSt(uint8 LeRteCan_u_Value);
// extern void RTE_NET_Can_Write_FridgeDoorSt(uint8 LeRteCan_u_Value);
// extern void RTE_NET_Can_Write_FridgeUVLedWorkSt(uint8 LeRteCan_u_Value);
// extern void RTE_NET_Can_Write_FridgeUVLedSt(uint8 LeRteCan_u_Value);
// extern void RTE_NET_Can_Write_FridgeHeatActSt(uint8 LeRteCan_u_Value);
// extern void RTE_NET_Can_Write_FridgestuffSt(uint8 LeRteCan_u_Value);
// extern void RTE_NET_Can_Write_FridgeModeSt(uint8 LeRteCan_u_Value);
// extern void RTE_NET_Can_Write_FridgeCoolTempSt(uint8 LeRteCan_u_Value);
// extern void RTE_NET_Can_Write_FridgeHeatTempSt(uint8 LeRteCan_u_Value);
// /***************End of 0x3EE***************/

// /***************Start of 0x3F3***************/
// extern void RTE_NET_Can_Write_VrhcuRequestACOn(uint8 LeRteCan_u_Value);
// extern void RTE_NET_Can_Write_VrhcuRefrAcpTemp(uint8 LeRteCan_u_Value);
// extern void RTE_NET_Can_Write_Vrhcupower(uint8 LeRteCan_u_Value);
// extern void RTE_NET_Can_Write_VrhcuOffReas(uint8 LeRteCan_u_Value);
// /***************End of 0x3F3***************/

// /********************************** Can Main Functions **********************************/
// extern void RTE_NET_Can_10msMainFunction(void);
// extern void RTE_NET_Can_20msMainFunction(void);

#endif /* RTE_APP_H */
