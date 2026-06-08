/*******************************************************************************
|  File Name: CanApp.h
|  Description: Implementation of the AUTOSAR CAN Interface
|-------------------------------------------------------------------------------
|  (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      ---------------------  -----------------------------------------
|                                  CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
  2019.05.18     V1.0         xyh                                               

|******************************************************************************/
#ifndef CANAPP_H
#define CANAPP_H
/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Platform_Types.h"
#include "il_inc.h"
#define CeCanApp_e_True   1U
#define CeCanApp_e_False  0U
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


typedef enum 
{
    VeCanApp_e_VIU_FR_1C3 = 0u,
    VeCanApp_e_VIU_FR_288 = 1u,
    VeCanApp_e_VIU_FR_2EC = 2u,
    VeCanApp_e_VIU_FR_2F7 = 3u,
    VeCanApp_e_VIU_FR_2EF = 4u,
    VeCanApp_e_VIU_FR_3D1 = 5u,    
    VeCanApp_e_VIU_FR_3D3 = 6u,
    VeCanApp_e_VIU_FR_3ED = 7u,
    VeCanApp_e_MsgMaxNum = 8u
}TeCanApp_e_MsgIdType;

typedef enum
{
    CanMsg_BcmPwrStsFb_OFF = 0U,
    CanMsg_BcmPwrStsFb_ON = 2U
}TeCanApp_e_BcmPwrStsFbType;

/*******************************************************************************
|    Global Variable with extern linkage
|******************************************************************************/

extern void SetCanApp_ClearTimeOut(void);
/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/
extern void CanApp_SetPositiveReqNet(uint8 LeCanApp_u_ReqNetFlag);
extern void CanApp_SetDiagReqNet(uint8 LeCanApp_u_DiagReqNetFlag);
extern uint8 CanApp_GetDiagReqNet(void);
extern void CanApp_SetWakeUpSource_Nm(uint8 LeCanApp_u_WakeUpSource_Nm);
extern void CanApp_SetAwakeSource_Nm(uint8 LeCanApp_u_AwakeSource);
extern void  CanApp_SetWakeupMode_NM(uint8 LeCanApp_u_WakeUpStateChange);
extern uint8 CanApp_GetWakeUpMode_Nm(void);
extern void CanApp_EnableImmediateNmTx(void);
extern void CanApp_DisableImmediateNmTx(void);
extern void CanApp_EnableRequestCommunication(void);
extern void CanApp_DisableRequestCommunication(void);
extern uint8 CanApp_GetPositiveReqNetFlag(void);
extern uint16 CanApp_GetDiagReqNetFlag(void);
extern uint8 CanApp_GetWakeUpSource_Nm(void);
extern uint8 CanApp_GetAwakeSource_Nm(void);

extern void CanApp_u_SetBusOffStaus(uint8 LeCanSignal_u_Idx);
extern uint8 CanApp_u_GetBusOffStaus(void);
extern void CanApp_u_SetNetWorkStaus(uint8 LeCanSignal_u_Idx);
extern uint8 CanApp_u_GetNetWorkStaus(void);

extern void SetCanApp_BusOffOccurNumInc(void);
extern void SetCanApp_BusOffOccurNumClr(void);
extern uint8 CanCbk_GetBusOffDtcConditionState(void);/*BusOff *///GGL
extern void SetCanApp_MsgReceiveSts( TeCanApp_e_MsgIdType LeCanApp_u_MsgIndex );
extern uint8 GetCanApp_MsgReceiveSts( TeCanApp_e_MsgIdType LeCanApp_u_MsgIndex );
extern uint8 GetCanApp_u_MsgCurrentPresent( TeCanApp_e_MsgIdType LeCanApp_u_MsgIndex );
extern void SetCanApp_MsgCurrentPresent( TeCanApp_e_MsgIdType LeCanApp_u_MsgIndex,uint8 LeCanApp_u_MsgSts);
extern uint8 GetCanApp_u_NetWorkSleepAllowed(void);

extern void CanApp_InitMemoryKAM(void);
extern void CanApp_InitMemory(void);
extern void CanApp_MainFunction(void) ;

/*VIU_FR_1C3*/
extern uint16 GetCanApp_u_EspVehSpd(void);
extern uint8 GetCanApp_u_EspVehSpdVld(void);

/*VIU_FR_288*/
extern uint8 GetCanApp_u_BcmPwrStsFb(void);

/*VIU_FR_2EC*/
extern uint8 GetCanApp_u_VcuGearPosn(void);
extern uint8 GetCanApp_u_VcuVehGearPosnVld(void);

/*VIU_FR_2EF*/
extern uint32 GetCanApp_u_CdcTotMilg(void);
/*VIU_FR_2F7*/
extern uint8 GetCanApp_u_TboxLocalTiDate(void);
extern uint8 GetCanApp_u_TboxLocalTiHr(void);
extern uint8 GetCanApp_u_TboxLocalTiMins(void);
extern uint8 GetCanApp_u_TboxLocalTiMth(void);
extern uint8 GetCanApp_u_TboxLocalTiSec(void);
extern uint8 GetCanApp_u_TboxLocalTiVld(void);
extern uint8 GetCanApp_u_TboxLocalTiYear(void);

/*VIU_FR_3D1*/
extern uint8 GetCanApp_u_DcdcOperSts(void);

/*VIU_FR_3D3*/
extern uint8 GetCanApp_u_BcuOperMod(void);

/*VIU_FR_3ED*/
extern uint8 GetCanApp_u_FridgeUnlockCtrl(void);
extern uint8 GetCanApp_u_FridgeDoorWarnTimeSet(void);
extern uint8 GetCanApp_u_FridgeChdLockReq(void);
extern uint8 GetCanApp_u_EgySaveModReq(void);
extern uint8 GetCanApp_u_FridgeWorkReq(void);
extern uint8 GetCanApp_u_FridgeQFunReq(void);
extern uint8 GetCanApp_u_ContinueWorkSw(void);
extern uint8 GetCanApp_u_ContinueWorkTimeSet(void);
extern uint8 GetCanApp_u_FridgeUVLedReq(void);
extern uint8 GetCanApp_u_FridgeUVLedWorkTimeSet(void);
extern uint8 GetCanApp_u_FridgeModeReq(void);
extern uint8 GetCanApp_u_FridgeCoolTempReq(void);
extern uint8 GetCanApp_u_FridgeHeatTempReq(void);
extern uint8 GetCanApp_u_VrhcuExOffReas(void);
extern uint8 GetCanApp_u_VrhcuONReas(void);

extern uint8 CanApp_HoldWakeupMode_Flag(void);

/*VIU_FR_3EE*/
#define WriteCanApp_FridgeErrSt                IlPutTxFridgeErrSt
#define WriteCanApp_FridgeDoorWarnTimeSt       IlPutTxFridgeDoorWarnTimeSt
#define WriteCanApp_FridgeChdLockSt            IlPutTxFridgeChdLockSt
#define WriteCanApp_EgySaveModSt               IlPutTxEgySaveModSt
#define WriteCanApp_FridgeWorkSt               IlPutTxFridgeWorkSt
#define WriteCanApp_FridgeQFunSt               IlPutTxFridgeQFunSt
#define WriteCanApp_ContinueWorkTimeSt         IlPutTxContinueWorkTimeSt
#define WriteCanApp_FridgeDoorWarnSt           IlPutTxFridgeDoorWarnSt
#define WriteCanApp_FridgeDoorSt               IlPutTxFridgeDoorSt
#define WriteCanApp_FridgeUVLedWorkSt          IlPutTxFridgeUVLedWorkSt
#define WriteCanApp_FridgeUVLedSt              IlPutTxFridgeUVLedSt
#define WriteCanApp_FridgeHeatActSt            IlPutTxFridgeHeatActSt
#define WriteCanApp_FridgestuffSt              IlPutTxFridgestuffSt
#define WriteCanApp_FridgeModeSt               IlPutTxFridgeModeSt
#define WriteCanApp_FridgeCoolTempSt           IlPutTxFridgeCoolTempSt
#define WriteCanApp_FridgeHeatTempSt           IlPutTxFridgeHeatTempSt

/*VIU_FR_3F3*/
#define WriteCanApp_VrhcuRequestACOn           IlPutTxVrhcuRequestACOn
#define WriteCanApp_VrhcuRefrAcpTemp           IlPutTxVrhcuRefrAcpTemp
#define WriteCanApp_Vrhcupower                 IlPutTxVrhcupower
#define WriteCanApp_VrhcuOffReas               IlPutTxVrhcuOffReas

/*VIU_FR_6EE*/
#define WriteCanApp_VrhcuDTC1_HighByte         IlPutTxVrhcuDTC1_HighByte
#define WriteCanApp_VrhcuDTC1_LowByte          IlPutTxVrhcuDTC1_LowByte
#define WriteCanApp_VrhcuDTC1_MiddByte         IlPutTxVrhcuDTC1_MiddByte
#define WriteCanApp_VrhcuDTC1_Status           IlPutTxVrhcuDTC1_Status 
#define WriteCanApp_VrhcuDTC2_HighByte         IlPutTxVrhcuDTC2_HighByte
#define WriteCanApp_VrhcuDTC2_LowByte          IlPutTxVrhcuDTC2_LowByte
#define WriteCanApp_VrhcuDTC2_MiddByte         IlPutTxVrhcuDTC2_MiddByte
#define WriteCanApp_VrhcuDTC2_Status           IlPutTxVrhcuDTC2_Status 

/*VIU_FR_6F9*/
#define WriteCanApp_VRHCP_WakeUp_BYTE3BIT0     IlPutTxVRHCP_WakeUp_BYTE3BIT0
#define WriteCanApp_VRHCP_NotSleep_BYTE7BIT0   IlPutTxVRHCP_NotSleep_BYTE7BIT0
#define WriteCanApp_VRHCP_NotSleep_BYTE7BIT1   IlPutTxVRHCP_NotSleep_BYTE7BIT1
#define WriteCanApp_VRHCP_NotSleep_BYTE7BIT2   IlPutTxVRHCP_NotSleep_BYTE7BIT2
#endif






