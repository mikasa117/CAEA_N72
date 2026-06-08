/*******************************************************************************
||  File Name: RTE_CAN.h
||  Description: Header file for AUTOSAR Can Interface
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

#ifndef RTE_CAN_H
#define RTE_CAN_H
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

/********************************** Can Initialization **********************************/
extern void RTE_NET_Can_Init(void);

/********************************** Can Read Functions **********************************/
/***************Start of 0x1C3************************/
extern uint32 RTE_NET_Can_Read_EspVehSpd(void);
extern uint8 RTE_NET_Can_Read_EspVehSpdVld(void);
/***************End of 0x1C3***************/

/***************Start of 0x2EC***************/
extern uint8 RTE_NET_Can_Read_VcuGearPosn(void);
extern uint8 RTE_NET_Can_Read_VcuVehGearPosnVld(void);
/***************End of 0x2EC***************/

/***************Start of 0x2EF***************/
extern uint16 RTE_NET_Can_Read_CdcTotMilg(void);
/***************End of 0x2EF***************/


/***************Start of 0x2F7***************/
extern uint8 RTE_NET_Can_Read_TboxLocalTiDate(void);
extern uint8 RTE_NET_Can_Read_TboxLocalTiHr(void);
extern uint8 RTE_NET_Can_Read_TboxLocalTiMins(void);
extern uint8 RTE_NET_Can_Read_TboxLocalTiMth(void);
extern uint8 RTE_NET_Can_Read_TboxLocalTiSec(void);
extern uint8 RTE_NET_Can_Read_TboxLocalTiVld(void);
extern uint16 RTE_NET_Can_Read_TboxLocalTiYear(void);
/***************End of 0x2F7***************/

/***************Start of 0x3ED************************/
extern uint8 RTE_NET_Can_Read_FridgeUnlockCtrl(void);
extern uint8 RTE_NET_Can_Read_FridgeDoorWarnTimeSet(void);
extern uint8 RTE_NET_Can_Read_FridgeChdLockReq(void);
extern uint8 RTE_NET_Can_Read_EgySaveModReq(void);
extern uint8 RTE_NET_Can_Read_FridgeWorkReq(void);
extern uint8 RTE_NET_Can_Read_FridgeQFunReq(void);
extern uint8 RTE_NET_Can_Read_ContinueWorkSw(void);
extern uint8 RTE_NET_Can_Read_ContinueWorkTimeSet(void);
extern uint8 RTE_NET_Can_Read_FridgeUVLedReq(void);
extern uint8 RTE_NET_Can_Read_FridgeUVLedWorkTimeSet(void);
extern uint8 RTE_NET_Can_Read_FridgeModeReq(void);
extern uint8 RTE_NET_Can_Read_FridgeCoolTempReq(void);
extern uint8 RTE_NET_Can_Read_FridgeHeatTempReq(void);
extern uint8 RTE_NET_Can_Read_VrhcuExOffReas(void);
extern uint8 RTE_NET_Can_Read_VrhcuONReas(void);
/***************End of 0x3ED***************/

/***************Start of 0x288***************/
extern uint8 RTE_NET_Can_Read_BcmPwrStsFb(void);
/***************End of 0x288***************/

/***************Start of 0x3D1***************/
extern uint8 RTE_NET_Can_Read_DcdcOperSts(void);
/***************End of 0x3D1***************/

/***************Start of 0x3D3***************/
extern uint8 RTE_NET_Can_Read_BcuOperMod(void);
/***************End of 0x3D3***************/

/********************************** Can Write Functions **********************************/
/***************Start of 0x3EE***************/
extern void RTE_NET_Can_Write_FridgeErrSt(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_FridgeDoorWarnTimeSt(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_FridgeChdLockSt(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_EgySaveModSt(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_FridgeWorkSt(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_FridgeQFunSt(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_ContinueWorkTimeSt(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_FridgeDoorWarnSt(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_FridgeDoorSt(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_FridgeUVLedWorkSt(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_FridgeUVLedSt(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_FridgeHeatActSt(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_FridgestuffSt(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_FridgeModeSt(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_FridgeCoolTempSt(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_FridgeHeatTempSt(uint8 LeRteCan_u_Value);
/***************End of 0x3EE***************/

/***************Start of 0x6F9***************/
extern void RTE_NET_Can_Write_VRHCP_WakeUp_BYTE3BIT0(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_VRHCP_NotSleep_BYTE7BIT0(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_VRHCP_NotSleep_BYTE7BIT1(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_VRHCP_NotSleep_BYTE7BIT2(uint8 LeRteCan_u_Value);
/***************End of 0x6F9***************/

/***************Start of 0x3F3***************/
extern void RTE_NET_Can_Write_VrhcuRequestACOn(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_VrhcuRefrAcpTemp(sint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_Vrhcupower(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_VrhcuOffReas(uint8 LeRteCan_u_Value);
/***************End of 0x3F3***************/

/***************Start of 0x6EE***************/
extern void RTE_NET_Can_Write_VrhcuDTC1_HighByte(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_VrhcuDTC1_LowByte(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_VrhcuDTC1_MiddByte(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_VrhcuDTC1_Status(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_VrhcuDTC2_HighByte(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_VrhcuDTC2_LowByte(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_VrhcuDTC2_MiddByte(uint8 LeRteCan_u_Value);
extern void RTE_NET_Can_Write_VrhcuDTC2_Status(uint8 LeRteCan_u_Value);
/***************End of 0x6EE***************/

/***************Start of 0x777***************/
extern uint8 RTE_NET_Can_Read_DiagRequest(uint8 LeRteCan_u_Value);
/***************End of 0x777***************/

/***************Start of 0x77F***************/
extern void RTE_NET_Can_Write_DiagResponse(uint8 LeRteCan_u_Value);
/***************End of 0x77F***************/

/********************************** Timeout Functions **********************************/
extern uint8 RTE_NET_Can_Timeout_0x1C3_Msg(void);
extern uint8 RTE_NET_Can_Timeout_0x3ED_Msg(void);
extern uint8 RTE_NET_Can_Timeout_0x288_Msg(void);
extern uint8 RTE_NET_Can_Timeout_0x2EC_Msg(void);
extern uint8 RTE_NET_Can_Timeout_0x2EF_Msg(void);
extern uint8 RTE_NET_Can_Timeout_0x2F7_Msg(void);
extern uint8 RTE_NET_Can_Timeout_0x3D1_Msg(void);
extern uint8 RTE_NET_Can_Timeout_0x3D3_Msg(void);

/********************************** Can BusOff Functions **********************************/
extern uint8 RTE_NET_Can_BusOff(void);

/********************************** Can Communicate Stop and Start **********************************/
void RTE_NET_Can_IlRxStop(void);
void RTE_NET_Can_IlRxStart(void);
void RTE_NET_Can_IlTxStop(void);
void RTE_NET_Can_IlTxStart(void);

/********************************** Can Main Functions **********************************/
extern void RTE_NET_Can_10msMainFunction(void);
extern void RTE_NET_Can_20msMainFunction(void);

/****************** other *********************/
extern void RteCan_SetPositiveReqNet(uint8 LeRteCan_u_ReqNetFlag);
extern uint8 RteCan_GetNetworkSleepAllowed(void);
extern void RteCan_EnableImmediateNmTx(void);
extern void RteCan_DisableImmediateNmTx(void);
extern uint8 RteCan_CanApp_GetWakeUpSource_Nm(void);
extern uint8 RteCan_CanApp_GetAwakeSource_Nm(void);
extern uint8 RteCan_CanApp_GetDiagReqNetFlag(void);
extern void RteCan_CanBusWakeupInt(void);

#endif /* RTE_CAN_H */
