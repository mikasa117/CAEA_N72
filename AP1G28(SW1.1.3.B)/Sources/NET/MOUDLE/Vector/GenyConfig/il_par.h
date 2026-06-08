/* -----------------------------------------------------------------------------
  Filename:    il_par.h
  Description: Toolversion: 02.03.18.01.80.01.04.01.00.00
               
               Serial Number: CBD1800104
               Customer Info: Wenzhou Changjiang Automobile Electronic System Co.,Ltd.?CAEA)
                              Package: CBD_Vector_SLP2
                              Micro: FS32K146
                              Compiler: GNU 9.2.0
               
               
               Generator Fwk   : GENy 
               Generator Module: Il_Vector
               
               Configuration   : E:\work\ChangAn\AP1G28AACXWA\APP\config\Geny\CX810.gny
               
               ECU: 
                       TargetSystem: Hw_S32Cpu
                       Compiler:     GNU
                       Derivates:    S32K146
               
               Channel "Channel0":
                       Databasefile: E:\work\ChangAn\AP1G28AACXWA\APP\config\inputfile\1VIUF1_CAN_CX810.dbc
                       Bussystem:    CAN
                       Manufacturer: Vector
                       Node:         VRHCU

 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2001-2015 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

#if !defined(__IL_PAR_H__)
#define __IL_PAR_H__

/* -----------------------------------------------------------------------------
    &&&~ Typedefs
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX)
typedef vuint8 IltTxCounter;
#endif

#if defined(IL_ENABLE_TX)
typedef vuint8 IltTxUpdateCounter;
#endif

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT)
typedef vuint8 IltTxTimeoutCounter;
#endif

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
typedef vuint16 IltRxTimeoutCounter;
#endif

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_SECURE_EVENT)
typedef vuint8 IltTxRepetitionCounter;
#endif



/* -----------------------------------------------------------------------------
    &&&~ Message Handles
 ----------------------------------------------------------------------------- */

#define IlRxMsgHndVIU_FR_3ED                 0
#define IlRxMsgHndVIU_FR_3D3                 1
#define IlRxMsgHndVIU_FR_3D1                 2
#define IlRxMsgHndVIU_FR_2F7                 3
#define IlRxMsgHndVIU_FR_2EF                 4
#define IlRxMsgHndVIU_FR_2EC                 5
#define IlRxMsgHndVIU_FR_288                 6
#define IlRxMsgHndVIU_FR_1C3                 7
#define IlTxMsgHndVRHCU_6F9                  0
#define IlTxMsgHndVRHCU_6EE                  1
#define IlTxMsgHndVRHCU_3F3                  2
#define IlTxMsgHndVRHCU_3EE                  3


/* -----------------------------------------------------------------------------
    &&&~ Signal Handles
 ----------------------------------------------------------------------------- */

#define IlRxSigHndFridgeQFunReq              IlRxMsgHndVIU_FR_3ED
#define IlRxSigHndFridgeModeReq              IlRxMsgHndVIU_FR_3ED
#define IlRxSigHndFridgeWorkReq              IlRxMsgHndVIU_FR_3ED
#define IlRxSigHndFridgeUnlockCtrl           IlRxMsgHndVIU_FR_3ED
#define IlRxSigHndFridgeHeatTempReq          IlRxMsgHndVIU_FR_3ED
#define IlRxSigHndFridgeChdLockReq           IlRxMsgHndVIU_FR_3ED
#define IlRxSigHndFridgeCoolTempReq          IlRxMsgHndVIU_FR_3ED
#define IlRxSigHndFridgeUVLedReq             IlRxMsgHndVIU_FR_3ED
#define IlRxSigHndFridgeUVLedWorkTimeSet     IlRxMsgHndVIU_FR_3ED
#define IlRxSigHndContinueWorkSw             IlRxMsgHndVIU_FR_3ED
#define IlRxSigHndEgySaveModReq              IlRxMsgHndVIU_FR_3ED
#define IlRxSigHndFridgeDoorWarnTimeSet      IlRxMsgHndVIU_FR_3ED
#define IlRxSigHndContinueWorkTimeSet        IlRxMsgHndVIU_FR_3ED
#define IlRxSigHndVrhcuONReas                IlRxMsgHndVIU_FR_3ED
#define IlRxSigHndVrhcuExOffReas             IlRxMsgHndVIU_FR_3ED
#define IlRxSigHndBcuOperMod                 IlRxMsgHndVIU_FR_3D3
#define IlRxSigHndDcdcOperSts                IlRxMsgHndVIU_FR_3D1
#define IlRxSigHndTboxLocalTiYear            IlRxMsgHndVIU_FR_2F7
#define IlRxSigHndTboxLocalTiMth             IlRxMsgHndVIU_FR_2F7
#define IlRxSigHndTboxLocalTiDate            IlRxMsgHndVIU_FR_2F7
#define IlRxSigHndTboxLocalTiHr              IlRxMsgHndVIU_FR_2F7
#define IlRxSigHndTboxLocalTiMins            IlRxMsgHndVIU_FR_2F7
#define IlRxSigHndTboxLocalTiSec             IlRxMsgHndVIU_FR_2F7
#define IlRxSigHndTboxLocalTiVld             IlRxMsgHndVIU_FR_2F7
#define IlRxSigHndCdcTotMilg                 IlRxMsgHndVIU_FR_2EF
#define IlRxSigHndVcuVehGearPosnVld          IlRxMsgHndVIU_FR_2EC
#define IlRxSigHndVcuGearPosn                IlRxMsgHndVIU_FR_2EC
#define IlRxSigHndBcmPwrStsFb                IlRxMsgHndVIU_FR_288
#define IlRxSigHndEspVehSpd                  IlRxMsgHndVIU_FR_1C3
#define IlRxSigHndEspVehSpdVld               IlRxMsgHndVIU_FR_1C3
#define IlTxSigHndVRHCP_WakeUp_BYTE3BIT0     IlTxMsgHndVRHCU_6F9
#define IlTxSigHndVRHCP_NotSleep_BYTE7BIT0   IlTxMsgHndVRHCU_6F9
#define IlTxSigHndVRHCP_NotSleep_BYTE7BIT1   IlTxMsgHndVRHCU_6F9
#define IlTxSigHndVRHCP_NotSleep_BYTE7BIT2   IlTxMsgHndVRHCU_6F9
#define IlTxSigHndVrhcuDTC1_HighByte         IlTxMsgHndVRHCU_6EE
#define IlTxSigHndVrhcuDTC1_MiddByte         IlTxMsgHndVRHCU_6EE
#define IlTxSigHndVrhcuDTC1_LowByte          IlTxMsgHndVRHCU_6EE
#define IlTxSigHndVrhcuDTC1_Status           IlTxMsgHndVRHCU_6EE
#define IlTxSigHndVrhcuDTC2_HighByte         IlTxMsgHndVRHCU_6EE
#define IlTxSigHndVrhcuDTC2_MiddByte         IlTxMsgHndVRHCU_6EE
#define IlTxSigHndVrhcuDTC2_LowByte          IlTxMsgHndVRHCU_6EE
#define IlTxSigHndVrhcuDTC2_Status           IlTxMsgHndVRHCU_6EE
#define IlTxSigHndVrhcuRequestACOn           IlTxMsgHndVRHCU_3F3
#define IlTxSigHndVrhcuRefrAcpTemp           IlTxMsgHndVRHCU_3F3
#define IlTxSigHndVrhcupower                 IlTxMsgHndVRHCU_3F3
#define IlTxSigHndVrhcuOffReas               IlTxMsgHndVRHCU_3F3
#define IlTxSigHndFridgeWorkSt               IlTxMsgHndVRHCU_3EE
#define IlTxSigHndFridgeUVLedWorkSt          IlTxMsgHndVRHCU_3EE
#define IlTxSigHndFridgeDoorSt               IlTxMsgHndVRHCU_3EE
#define IlTxSigHndFridgeHeatTempSt           IlTxMsgHndVRHCU_3EE
#define IlTxSigHndFridgeModeSt               IlTxMsgHndVRHCU_3EE
#define IlTxSigHndFridgeCoolTempSt           IlTxMsgHndVRHCU_3EE
#define IlTxSigHndFridgeDoorWarnSt           IlTxMsgHndVRHCU_3EE
#define IlTxSigHndFridgeErrSt                IlTxMsgHndVRHCU_3EE
#define IlTxSigHndFridgeHeatActSt            IlTxMsgHndVRHCU_3EE
#define IlTxSigHndFridgeQFunSt               IlTxMsgHndVRHCU_3EE
#define IlTxSigHndFridgeChdLockSt            IlTxMsgHndVRHCU_3EE
#define IlTxSigHndEgySaveModSt               IlTxMsgHndVRHCU_3EE
#define IlTxSigHndFridgestuffSt              IlTxMsgHndVRHCU_3EE
#define IlTxSigHndFridgeUVLedSt              IlTxMsgHndVRHCU_3EE
#define IlTxSigHndFridgeDoorWarnTimeSt       IlTxMsgHndVRHCU_3EE
#define IlTxSigHndContinueWorkTimeSt         IlTxMsgHndVRHCU_3EE


/* -----------------------------------------------------------------------------
    &&&~ Critical section macros for signals
 ----------------------------------------------------------------------------- */

#define IlEnterCriticalVRHCP_WakeUp_BYTE3BIT0() CanGlobalInterruptDisable()
#define IlLeaveCriticalVRHCP_WakeUp_BYTE3BIT0() CanGlobalInterruptRestore()
#define IlEnterCriticalVRHCP_NotSleep_BYTE7BIT0() CanGlobalInterruptDisable()
#define IlLeaveCriticalVRHCP_NotSleep_BYTE7BIT0() CanGlobalInterruptRestore()
#define IlEnterCriticalVRHCP_NotSleep_BYTE7BIT1() CanGlobalInterruptDisable()
#define IlLeaveCriticalVRHCP_NotSleep_BYTE7BIT1() CanGlobalInterruptRestore()
#define IlEnterCriticalVRHCP_NotSleep_BYTE7BIT2() CanGlobalInterruptDisable()
#define IlLeaveCriticalVRHCP_NotSleep_BYTE7BIT2() CanGlobalInterruptRestore()
#define IlEnterCriticalVrhcuDTC1_HighByte()  CanGlobalInterruptDisable()
#define IlLeaveCriticalVrhcuDTC1_HighByte()  CanGlobalInterruptRestore()
#define IlEnterCriticalVrhcuDTC1_MiddByte()  CanGlobalInterruptDisable()
#define IlLeaveCriticalVrhcuDTC1_MiddByte()  CanGlobalInterruptRestore()
#define IlEnterCriticalVrhcuDTC1_LowByte()   CanGlobalInterruptDisable()
#define IlLeaveCriticalVrhcuDTC1_LowByte()   CanGlobalInterruptRestore()
#define IlEnterCriticalVrhcuDTC1_Status()    CanGlobalInterruptDisable()
#define IlLeaveCriticalVrhcuDTC1_Status()    CanGlobalInterruptRestore()
#define IlEnterCriticalVrhcuDTC2_HighByte()  CanGlobalInterruptDisable()
#define IlLeaveCriticalVrhcuDTC2_HighByte()  CanGlobalInterruptRestore()
#define IlEnterCriticalVrhcuDTC2_MiddByte()  CanGlobalInterruptDisable()
#define IlLeaveCriticalVrhcuDTC2_MiddByte()  CanGlobalInterruptRestore()
#define IlEnterCriticalVrhcuDTC2_LowByte()   CanGlobalInterruptDisable()
#define IlLeaveCriticalVrhcuDTC2_LowByte()   CanGlobalInterruptRestore()
#define IlEnterCriticalVrhcuDTC2_Status()    CanGlobalInterruptDisable()
#define IlLeaveCriticalVrhcuDTC2_Status()    CanGlobalInterruptRestore()
#define IlEnterCriticalVrhcuRequestACOn()    CanGlobalInterruptDisable()
#define IlLeaveCriticalVrhcuRequestACOn()    CanGlobalInterruptRestore()
#define IlEnterCriticalVrhcuRefrAcpTemp()    CanGlobalInterruptDisable()
#define IlLeaveCriticalVrhcuRefrAcpTemp()    CanGlobalInterruptRestore()
#define IlEnterCriticalVrhcupower()          CanGlobalInterruptDisable()
#define IlLeaveCriticalVrhcupower()          CanGlobalInterruptRestore()
#define IlEnterCriticalVrhcuOffReas()        CanGlobalInterruptDisable()
#define IlLeaveCriticalVrhcuOffReas()        CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeWorkSt()        CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeWorkSt()        CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeUVLedWorkSt()   CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeUVLedWorkSt()   CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeDoorSt()        CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeDoorSt()        CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeHeatTempSt()    CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeHeatTempSt()    CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeModeSt()        CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeModeSt()        CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeCoolTempSt()    CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeCoolTempSt()    CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeDoorWarnSt()    CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeDoorWarnSt()    CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeErrSt()         CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeErrSt()         CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeHeatActSt()     CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeHeatActSt()     CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeQFunSt()        CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeQFunSt()        CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeChdLockSt()     CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeChdLockSt()     CanGlobalInterruptRestore()
#define IlEnterCriticalEgySaveModSt()        CanGlobalInterruptDisable()
#define IlLeaveCriticalEgySaveModSt()        CanGlobalInterruptRestore()
#define IlEnterCriticalFridgestuffSt()       CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgestuffSt()       CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeUVLedSt()       CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeUVLedSt()       CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeDoorWarnTimeSt() CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeDoorWarnTimeSt() CanGlobalInterruptRestore()
#define IlEnterCriticalContinueWorkTimeSt()  CanGlobalInterruptDisable()
#define IlLeaveCriticalContinueWorkTimeSt()  CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeQFunReq()       CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeQFunReq()       CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeModeReq()       CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeModeReq()       CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeWorkReq()       CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeWorkReq()       CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeUnlockCtrl()    CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeUnlockCtrl()    CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeHeatTempReq()   CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeHeatTempReq()   CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeChdLockReq()    CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeChdLockReq()    CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeCoolTempReq()   CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeCoolTempReq()   CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeUVLedReq()      CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeUVLedReq()      CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeUVLedWorkTimeSet() CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeUVLedWorkTimeSet() CanGlobalInterruptRestore()
#define IlEnterCriticalContinueWorkSw()      CanGlobalInterruptDisable()
#define IlLeaveCriticalContinueWorkSw()      CanGlobalInterruptRestore()
#define IlEnterCriticalEgySaveModReq()       CanGlobalInterruptDisable()
#define IlLeaveCriticalEgySaveModReq()       CanGlobalInterruptRestore()
#define IlEnterCriticalFridgeDoorWarnTimeSet() CanGlobalInterruptDisable()
#define IlLeaveCriticalFridgeDoorWarnTimeSet() CanGlobalInterruptRestore()
#define IlEnterCriticalContinueWorkTimeSet() CanGlobalInterruptDisable()
#define IlLeaveCriticalContinueWorkTimeSet() CanGlobalInterruptRestore()
#define IlEnterCriticalVrhcuONReas()         CanGlobalInterruptDisable()
#define IlLeaveCriticalVrhcuONReas()         CanGlobalInterruptRestore()
#define IlEnterCriticalVrhcuExOffReas()      CanGlobalInterruptDisable()
#define IlLeaveCriticalVrhcuExOffReas()      CanGlobalInterruptRestore()
#define IlEnterCriticalBcuOperMod()          CanGlobalInterruptDisable()
#define IlLeaveCriticalBcuOperMod()          CanGlobalInterruptRestore()
#define IlEnterCriticalDcdcOperSts()         CanGlobalInterruptDisable()
#define IlLeaveCriticalDcdcOperSts()         CanGlobalInterruptRestore()
#define IlEnterCriticalTboxLocalTiYear()     CanGlobalInterruptDisable()
#define IlLeaveCriticalTboxLocalTiYear()     CanGlobalInterruptRestore()
#define IlEnterCriticalTboxLocalTiMth()      CanGlobalInterruptDisable()
#define IlLeaveCriticalTboxLocalTiMth()      CanGlobalInterruptRestore()
#define IlEnterCriticalTboxLocalTiDate()     CanGlobalInterruptDisable()
#define IlLeaveCriticalTboxLocalTiDate()     CanGlobalInterruptRestore()
#define IlEnterCriticalTboxLocalTiHr()       CanGlobalInterruptDisable()
#define IlLeaveCriticalTboxLocalTiHr()       CanGlobalInterruptRestore()
#define IlEnterCriticalTboxLocalTiMins()     CanGlobalInterruptDisable()
#define IlLeaveCriticalTboxLocalTiMins()     CanGlobalInterruptRestore()
#define IlEnterCriticalTboxLocalTiSec()      CanGlobalInterruptDisable()
#define IlLeaveCriticalTboxLocalTiSec()      CanGlobalInterruptRestore()
#define IlEnterCriticalTboxLocalTiVld()      CanGlobalInterruptDisable()
#define IlLeaveCriticalTboxLocalTiVld()      CanGlobalInterruptRestore()
#define IlEnterCriticalCdcTotMilg()          CanGlobalInterruptDisable()
#define IlLeaveCriticalCdcTotMilg()          CanGlobalInterruptRestore()
#define IlEnterCriticalVcuVehGearPosnVld()   CanGlobalInterruptDisable()
#define IlLeaveCriticalVcuVehGearPosnVld()   CanGlobalInterruptRestore()
#define IlEnterCriticalVcuGearPosn()         CanGlobalInterruptDisable()
#define IlLeaveCriticalVcuGearPosn()         CanGlobalInterruptRestore()
#define IlEnterCriticalBcmPwrStsFb()         CanGlobalInterruptDisable()
#define IlLeaveCriticalBcmPwrStsFb()         CanGlobalInterruptRestore()
#define IlEnterCriticalEspVehSpd()           CanGlobalInterruptDisable()
#define IlLeaveCriticalEspVehSpd()           CanGlobalInterruptRestore()
#define IlEnterCriticalEspVehSpdVld()        CanGlobalInterruptDisable()
#define IlLeaveCriticalEspVehSpdVld()        CanGlobalInterruptRestore()


/* -----------------------------------------------------------------------------
    &&&~ Declaration Confirmation Functions
 ----------------------------------------------------------------------------- */

/* Application signal confirmation callback functions */


/* -----------------------------------------------------------------------------
    &&&~ Declaration Indication Functions
 ----------------------------------------------------------------------------- */

/* Application signal indication callback functions */


/* -----------------------------------------------------------------------------
    &&&~ Declaration Rx Timeout Indication Functions
 ----------------------------------------------------------------------------- */

extern void ApplVIU_FR_3EDMsgTimeout(void);
extern void ApplVIU_FR_3D3MsgTimeout(void);
extern void ApplVIU_FR_3D1MsgTimeout(void);
extern void ApplVIU_FR_2F7MsgTimeout(void);
extern void ApplVIU_FR_2EFMsgTimeout(void);
extern void ApplVIU_FR_2ECMsgTimeout(void);
extern void ApplVIU_FR_288MsgTimeout(void);
extern void ApplVIU_FR_1C3MsgTimeout(void);


/* -----------------------------------------------------------------------------
    &&&~ Declaration User Timeout Functions
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT)
#endif



/* -----------------------------------------------------------------------------
    &&&~ Get Rx Signal Access for signals smaller or equal 8bit
 ----------------------------------------------------------------------------- */

/* Handle:    0,Name:                  FridgeQFunReq,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxFridgeQFunReq()               (VIU_FR_3ED.VIU_FR_3ED.FridgeQFunReq)
#endif

/* Handle:    1,Name:                  FridgeModeReq,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxFridgeModeReq()               (VIU_FR_3ED.VIU_FR_3ED.FridgeModeReq)
#endif

/* Handle:    2,Name:                  FridgeWorkReq,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxFridgeWorkReq()               (VIU_FR_3ED.VIU_FR_3ED.FridgeWorkReq)
#endif

/* Handle:    3,Name:               FridgeUnlockCtrl,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxFridgeUnlockCtrl()            (VIU_FR_3ED.VIU_FR_3ED.FridgeUnlockCtrl)
#endif

/* Handle:    4,Name:              FridgeHeatTempReq,Size:  5,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxFridgeHeatTempReq()           (VIU_FR_3ED.VIU_FR_3ED.FridgeHeatTempReq)
#endif

/* Handle:    5,Name:               FridgeChdLockReq,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxFridgeChdLockReq()            (VIU_FR_3ED.VIU_FR_3ED.FridgeChdLockReq)
#endif

/* Handle:    6,Name:              FridgeCoolTempReq,Size:  5,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxFridgeCoolTempReq()           (VIU_FR_3ED.VIU_FR_3ED.FridgeCoolTempReq)
#endif

/* Handle:    7,Name:                 FridgeUVLedReq,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxFridgeUVLedReq()              (VIU_FR_3ED.VIU_FR_3ED.FridgeUVLedReq)
#endif

/* Handle:    8,Name:         FridgeUVLedWorkTimeSet,Size:  5,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxFridgeUVLedWorkTimeSet()      (VIU_FR_3ED.VIU_FR_3ED.FridgeUVLedWorkTimeSet)
#endif

/* Handle:    9,Name:                 ContinueWorkSw,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxContinueWorkSw()              (VIU_FR_3ED.VIU_FR_3ED.ContinueWorkSw)
#endif

/* Handle:   10,Name:                  EgySaveModReq,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxEgySaveModReq()               (VIU_FR_3ED.VIU_FR_3ED.EgySaveModReq)
#endif

/* Handle:   11,Name:          FridgeDoorWarnTimeSet,Size:  3,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxFridgeDoorWarnTimeSet()       (VIU_FR_3ED.VIU_FR_3ED.FridgeDoorWarnTimeSet)
#endif

/* Handle:   12,Name:            ContinueWorkTimeSet,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxContinueWorkTimeSet()         (VIU_FR_3ED.VIU_FR_3ED.ContinueWorkTimeSet)
#endif

/* Handle:   13,Name:                    VrhcuONReas,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxVrhcuONReas()                 (VIU_FR_3ED.VIU_FR_3ED.VrhcuONReas)
#endif

/* Handle:   14,Name:                 VrhcuExOffReas,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxVrhcuExOffReas()              (VIU_FR_3ED.VIU_FR_3ED.VrhcuExOffReas)
#endif

/* Handle:   15,Name:                     BcuOperMod,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxBcuOperMod()                  (VIU_FR_3D3.VIU_FR_3D3.BcuOperMod)
#endif

/* Handle:   16,Name:                    DcdcOperSts,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxDcdcOperSts()                 (VIU_FR_3D1.VIU_FR_3D1.DcdcOperSts)
#endif

/* Handle:   17,Name:                TboxLocalTiYear,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTboxLocalTiYear()             (VIU_FR_2F7.VIU_FR_2F7.TboxLocalTiYear)
#endif

/* Handle:   18,Name:                 TboxLocalTiMth,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTboxLocalTiMth()              (VIU_FR_2F7.VIU_FR_2F7.TboxLocalTiMth)
#endif

/* Handle:   19,Name:                TboxLocalTiDate,Size:  5,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTboxLocalTiDate()             (VIU_FR_2F7.VIU_FR_2F7.TboxLocalTiDate)
#endif

/* Handle:   20,Name:                  TboxLocalTiHr,Size:  5,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTboxLocalTiHr()               (VIU_FR_2F7.VIU_FR_2F7.TboxLocalTiHr)
#endif

/* Handle:   21,Name:                TboxLocalTiMins,Size:  6,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTboxLocalTiMins()             (VIU_FR_2F7.VIU_FR_2F7.TboxLocalTiMins)
#endif

/* Handle:   22,Name:                 TboxLocalTiSec,Size:  6,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTboxLocalTiSec()              (VIU_FR_2F7.VIU_FR_2F7.TboxLocalTiSec)
#endif

/* Handle:   23,Name:                 TboxLocalTiVld,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTboxLocalTiVld()              (VIU_FR_2F7.VIU_FR_2F7.TboxLocalTiVld)
#endif

/* Handle:   25,Name:              VcuVehGearPosnVld,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxVcuVehGearPosnVld()           (VIU_FR_2EC.VIU_FR_2EC.VcuVehGearPosnVld)
#endif

/* Handle:   26,Name:                    VcuGearPosn,Size:  3,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxVcuGearPosn()                 (VIU_FR_2EC.VIU_FR_2EC.VcuGearPosn)
#endif

/* Handle:   27,Name:                    BcmPwrStsFb,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxBcmPwrStsFb()                 (VIU_FR_288.VIU_FR_288.BcmPwrStsFb)
#endif

/* Handle:   29,Name:                   EspVehSpdVld,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxEspVehSpdVld()                (VIU_FR_1C3.VIU_FR_1C3.EspVehSpdVld)
#endif



/* -----------------------------------------------------------------------------
    &&&~ Get Rx Signal Access for signals greater 8bit and smaller or equal 32bit
 ----------------------------------------------------------------------------- */

/* Handle:   24,Name:                     CdcTotMilg,Size: 24,UsedBytes:  3,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint32 IlGetRxCdcTotMilg(void);
#endif

/* Handle:   28,Name:                      EspVehSpd,Size: 13,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxEspVehSpd(void);
#endif



/* -----------------------------------------------------------------------------
    &&&~ Set Tx Signal Access for signals smaller or equal 8bit, SendType cyclic or none
 ----------------------------------------------------------------------------- */

/* Handle:    0,Name:         VRHCP_WakeUp_BYTE3BIT0,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxVRHCP_WakeUp_BYTE3BIT0(vuint8 sigData);
#endif

/* Handle:    1,Name:       VRHCP_NotSleep_BYTE7BIT0,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxVRHCP_NotSleep_BYTE7BIT0(vuint8 sigData);
#endif

/* Handle:    2,Name:       VRHCP_NotSleep_BYTE7BIT1,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxVRHCP_NotSleep_BYTE7BIT1(vuint8 sigData);
#endif

/* Handle:    3,Name:       VRHCP_NotSleep_BYTE7BIT2,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxVRHCP_NotSleep_BYTE7BIT2(vuint8 sigData);
#endif

/* Handle:    4,Name:             VrhcuDTC1_HighByte,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxVrhcuDTC1_HighByte(vuint8 sigData);
#endif

/* Handle:    5,Name:             VrhcuDTC1_MiddByte,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxVrhcuDTC1_MiddByte(vuint8 sigData);
#endif

/* Handle:    6,Name:              VrhcuDTC1_LowByte,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxVrhcuDTC1_LowByte(vuint8 sigData);
#endif

/* Handle:    7,Name:               VrhcuDTC1_Status,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxVrhcuDTC1_Status(vuint8 sigData);
#endif

/* Handle:    8,Name:             VrhcuDTC2_HighByte,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxVrhcuDTC2_HighByte(vuint8 sigData);
#endif

/* Handle:    9,Name:             VrhcuDTC2_MiddByte,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxVrhcuDTC2_MiddByte(vuint8 sigData);
#endif

/* Handle:   10,Name:              VrhcuDTC2_LowByte,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxVrhcuDTC2_LowByte(vuint8 sigData);
#endif

/* Handle:   11,Name:               VrhcuDTC2_Status,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxVrhcuDTC2_Status(vuint8 sigData);
#endif

/* Handle:   12,Name:               VrhcuRequestACOn,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxVrhcuRequestACOn(vuint8 sigData);
#endif

/* Handle:   13,Name:               VrhcuRefrAcpTemp,Size:  7,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxVrhcuRefrAcpTemp(vuint8 sigData);
#endif

/* Handle:   14,Name:                     Vrhcupower,Size:  7,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxVrhcupower(vuint8 sigData);
#endif

/* Handle:   15,Name:                   VrhcuOffReas,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxVrhcuOffReas(vuint8 sigData);
#endif

/* Handle:   16,Name:                   FridgeWorkSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxFridgeWorkSt(vuint8 sigData);
#endif

/* Handle:   17,Name:              FridgeUVLedWorkSt,Size:  5,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxFridgeUVLedWorkSt(vuint8 sigData);
#endif

/* Handle:   18,Name:                   FridgeDoorSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxFridgeDoorSt(vuint8 sigData);
#endif

/* Handle:   19,Name:               FridgeHeatTempSt,Size:  5,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxFridgeHeatTempSt(vuint8 sigData);
#endif

/* Handle:   20,Name:                   FridgeModeSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxFridgeModeSt(vuint8 sigData);
#endif

/* Handle:   21,Name:               FridgeCoolTempSt,Size:  5,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxFridgeCoolTempSt(vuint8 sigData);
#endif

/* Handle:   22,Name:               FridgeDoorWarnSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxFridgeDoorWarnSt(vuint8 sigData);
#endif

/* Handle:   23,Name:                    FridgeErrSt,Size:  5,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxFridgeErrSt(vuint8 sigData);
#endif

/* Handle:   24,Name:                FridgeHeatActSt,Size:  7,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxFridgeHeatActSt(vuint8 sigData);
#endif

/* Handle:   25,Name:                   FridgeQFunSt,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxFridgeQFunSt(vuint8 sigData);
#endif

/* Handle:   26,Name:                FridgeChdLockSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxFridgeChdLockSt(vuint8 sigData);
#endif

/* Handle:   27,Name:                   EgySaveModSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxEgySaveModSt(vuint8 sigData);
#endif

/* Handle:   28,Name:                  FridgestuffSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxFridgestuffSt(vuint8 sigData);
#endif

/* Handle:   29,Name:                  FridgeUVLedSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxFridgeUVLedSt(vuint8 sigData);
#endif

/* Handle:   30,Name:           FridgeDoorWarnTimeSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxFridgeDoorWarnTimeSt(vuint8 sigData);
#endif

/* Handle:   31,Name:             ContinueWorkTimeSt,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxContinueWorkTimeSt(vuint8 sigData);
#endif



/* -----------------------------------------------------------------------------
    &&&~ AUTOSAR Signal API
 ----------------------------------------------------------------------------- */

#if ((COM_AR_MAJOR_VERSION == 1) && (COM_AR_MINOR_VERSION == 0) && (COM_AR_PATCH_VERSION == 0))
typedef vuint8 Com_ReturnType;
#define COM_OK                               (Com_ReturnType) 0
#define Com_SendSignal(x, y)                 (ComIlPut##x((y)), COM_OK)
#define Com_ReceiveSignal(x, y)              (ComIlGet##x((y)), COM_OK)
#define Com_SendSignalGroup(x)               (ComIlPut##x(), COM_OK)
#define Com_ReceiveSignalGroup(x)            (ComIlGet##x(), COM_OK)
#define Com_ReceiveShadowSignal(x, y)        (ComIlGet##x((y)), COM_OK)
#define Com_UpdateShadowSignal(x, y)         (ComIlPut##x((y)), COM_OK)
#else
#if ((COM_AR_MAJOR_VERSION == 2) && (COM_AR_MINOR_VERSION == 0) && (COM_AR_PATCH_VERSION == 0))
#define Com_SendSignal(x, y)                 (ComIlPut##x((y)), E_OK)
#define Com_ReceiveSignal(x, y)              (ComIlGet##x((y)), E_OK)
#define Com_SendSignalGroup(x)               (ComIlPut##x(), E_OK)
#define Com_ReceiveSignalGroup(x)            (ComIlGet##x(), E_OK)
#define Com_ReceiveShadowSignal(x, y)        (ComIlGet##x((y)), E_OK)
#define Com_UpdateShadowSignal(x, y)         (ComIlPut##x((y)), E_OK)
#endif

#endif

/* -----------------------------------------------------------------------------
    &&&~ Set Tx Signals
 ----------------------------------------------------------------------------- */

#define ComIlPutVRHCP_WakeUp_BYTE3BIT0(x)    IlPutTxVRHCP_WakeUp_BYTE3BIT0(*(x))
#define ComIlPutVRHCP_NotSleep_BYTE7BIT0(x)  IlPutTxVRHCP_NotSleep_BYTE7BIT0(*(x))
#define ComIlPutVRHCP_NotSleep_BYTE7BIT1(x)  IlPutTxVRHCP_NotSleep_BYTE7BIT1(*(x))
#define ComIlPutVRHCP_NotSleep_BYTE7BIT2(x)  IlPutTxVRHCP_NotSleep_BYTE7BIT2(*(x))
#define ComIlPutVrhcuDTC1_HighByte(x)        IlPutTxVrhcuDTC1_HighByte(*(x))
#define ComIlPutVrhcuDTC1_MiddByte(x)        IlPutTxVrhcuDTC1_MiddByte(*(x))
#define ComIlPutVrhcuDTC1_LowByte(x)         IlPutTxVrhcuDTC1_LowByte(*(x))
#define ComIlPutVrhcuDTC1_Status(x)          IlPutTxVrhcuDTC1_Status(*(x))
#define ComIlPutVrhcuDTC2_HighByte(x)        IlPutTxVrhcuDTC2_HighByte(*(x))
#define ComIlPutVrhcuDTC2_MiddByte(x)        IlPutTxVrhcuDTC2_MiddByte(*(x))
#define ComIlPutVrhcuDTC2_LowByte(x)         IlPutTxVrhcuDTC2_LowByte(*(x))
#define ComIlPutVrhcuDTC2_Status(x)          IlPutTxVrhcuDTC2_Status(*(x))
#define ComIlPutVrhcuRequestACOn(x)          IlPutTxVrhcuRequestACOn(*(x))
#define ComIlPutVrhcuRefrAcpTemp(x)          IlPutTxVrhcuRefrAcpTemp(*(x))
#define ComIlPutVrhcupower(x)                IlPutTxVrhcupower(*(x))
#define ComIlPutVrhcuOffReas(x)              IlPutTxVrhcuOffReas(*(x))
#define ComIlPutFridgeWorkSt(x)              IlPutTxFridgeWorkSt(*(x))
#define ComIlPutFridgeUVLedWorkSt(x)         IlPutTxFridgeUVLedWorkSt(*(x))
#define ComIlPutFridgeDoorSt(x)              IlPutTxFridgeDoorSt(*(x))
#define ComIlPutFridgeHeatTempSt(x)          IlPutTxFridgeHeatTempSt(*(x))
#define ComIlPutFridgeModeSt(x)              IlPutTxFridgeModeSt(*(x))
#define ComIlPutFridgeCoolTempSt(x)          IlPutTxFridgeCoolTempSt(*(x))
#define ComIlPutFridgeDoorWarnSt(x)          IlPutTxFridgeDoorWarnSt(*(x))
#define ComIlPutFridgeErrSt(x)               IlPutTxFridgeErrSt(*(x))
#define ComIlPutFridgeHeatActSt(x)           IlPutTxFridgeHeatActSt(*(x))
#define ComIlPutFridgeQFunSt(x)              IlPutTxFridgeQFunSt(*(x))
#define ComIlPutFridgeChdLockSt(x)           IlPutTxFridgeChdLockSt(*(x))
#define ComIlPutEgySaveModSt(x)              IlPutTxEgySaveModSt(*(x))
#define ComIlPutFridgestuffSt(x)             IlPutTxFridgestuffSt(*(x))
#define ComIlPutFridgeUVLedSt(x)             IlPutTxFridgeUVLedSt(*(x))
#define ComIlPutFridgeDoorWarnTimeSt(x)      IlPutTxFridgeDoorWarnTimeSt(*(x))
#define ComIlPutContinueWorkTimeSt(x)        IlPutTxContinueWorkTimeSt(*(x))


/* -----------------------------------------------------------------------------
    &&&~ Get Rx Signals
 ----------------------------------------------------------------------------- */

#define ComIlGetFridgeQFunReq(x)             (*(x) = IlGetRxFridgeQFunReq())
#define ComIlGetFridgeModeReq(x)             (*(x) = IlGetRxFridgeModeReq())
#define ComIlGetFridgeWorkReq(x)             (*(x) = IlGetRxFridgeWorkReq())
#define ComIlGetFridgeUnlockCtrl(x)          (*(x) = IlGetRxFridgeUnlockCtrl())
#define ComIlGetFridgeHeatTempReq(x)         (*(x) = IlGetRxFridgeHeatTempReq())
#define ComIlGetFridgeChdLockReq(x)          (*(x) = IlGetRxFridgeChdLockReq())
#define ComIlGetFridgeCoolTempReq(x)         (*(x) = IlGetRxFridgeCoolTempReq())
#define ComIlGetFridgeUVLedReq(x)            (*(x) = IlGetRxFridgeUVLedReq())
#define ComIlGetFridgeUVLedWorkTimeSet(x)    (*(x) = IlGetRxFridgeUVLedWorkTimeSet())
#define ComIlGetContinueWorkSw(x)            (*(x) = IlGetRxContinueWorkSw())
#define ComIlGetEgySaveModReq(x)             (*(x) = IlGetRxEgySaveModReq())
#define ComIlGetFridgeDoorWarnTimeSet(x)     (*(x) = IlGetRxFridgeDoorWarnTimeSet())
#define ComIlGetContinueWorkTimeSet(x)       (*(x) = IlGetRxContinueWorkTimeSet())
#define ComIlGetVrhcuONReas(x)               (*(x) = IlGetRxVrhcuONReas())
#define ComIlGetVrhcuExOffReas(x)            (*(x) = IlGetRxVrhcuExOffReas())
#define ComIlGetBcuOperMod(x)                (*(x) = IlGetRxBcuOperMod())
#define ComIlGetDcdcOperSts(x)               (*(x) = IlGetRxDcdcOperSts())
#define ComIlGetTboxLocalTiYear(x)           (*(x) = IlGetRxTboxLocalTiYear())
#define ComIlGetTboxLocalTiMth(x)            (*(x) = IlGetRxTboxLocalTiMth())
#define ComIlGetTboxLocalTiDate(x)           (*(x) = IlGetRxTboxLocalTiDate())
#define ComIlGetTboxLocalTiHr(x)             (*(x) = IlGetRxTboxLocalTiHr())
#define ComIlGetTboxLocalTiMins(x)           (*(x) = IlGetRxTboxLocalTiMins())
#define ComIlGetTboxLocalTiSec(x)            (*(x) = IlGetRxTboxLocalTiSec())
#define ComIlGetTboxLocalTiVld(x)            (*(x) = IlGetRxTboxLocalTiVld())
#define ComIlGetCdcTotMilg(x)                (*(x) = IlGetRxCdcTotMilg())
#define ComIlGetVcuVehGearPosnVld(x)         (*(x) = IlGetRxVcuVehGearPosnVld())
#define ComIlGetVcuGearPosn(x)               (*(x) = IlGetRxVcuGearPosn())
#define ComIlGetBcmPwrStsFb(x)               (*(x) = IlGetRxBcmPwrStsFb())
#define ComIlGetEspVehSpd(x)                 (*(x) = IlGetRxEspVehSpd())
#define ComIlGetEspVehSpdVld(x)              (*(x) = IlGetRxEspVehSpdVld())





#endif /* __IL_PAR_H__ */
