/* -----------------------------------------------------------------------------
  Filename:    can_par.h
  Description: Toolversion: 02.03.18.01.80.01.04.01.00.00
               
               Serial Number: CBD1800104
               Customer Info: Wenzhou Changjiang Automobile Electronic System Co.,Ltd.?CAEA)
                              Package: CBD_Vector_SLP2
                              Micro: FS32K146
                              Compiler: GNU 9.2.0
               
               
               Generator Fwk   : GENy 
               Generator Module: DrvCan__base
               
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

#if !defined(__CAN_PAR_H__)
#define __CAN_PAR_H__

#include "can_cfg.h"
#include "v_inc.h"
#include "drv_par.h"

/* -----------------------------------------------------------------------------
    &&&~ Extern declarations of callback functions
 ----------------------------------------------------------------------------- */

#if defined(C_MULTIPLE_RECEIVE_CHANNEL) || defined(C_SINGLE_RECEIVE_CHANNEL)
/* CODE CATEGORY 1 START */
extern vuint8 Pretransmit_VRHCU_6F9(CanTxInfoStruct ctis);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 Pretransmit_VRHCU_6EE(CanTxInfoStruct ctis);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 Pretransmit_NmMsg(CanTxInfoStruct ctis);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 Pretransmit_VRHCU_3F3(CanTxInfoStruct ctis);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 Pretransmit_VRHCU_3EE(CanTxInfoStruct ctis);
/* CODE CATEGORY 1 END */

#else
/* CODE CATEGORY 1 START */
extern vuint8 Pretransmit_VRHCU_6F9(CanChipDataPtr txObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 Pretransmit_VRHCU_6EE(CanChipDataPtr txObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 Pretransmit_NmMsg(CanChipDataPtr txObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 Pretransmit_VRHCU_3F3(CanChipDataPtr txObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 Pretransmit_VRHCU_3EE(CanChipDataPtr txObject);
/* CODE CATEGORY 1 END */

#endif

/* CODE CATEGORY 1 START */
extern vuint8 IlMsgVIU_FR_3EDPreCopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 IlMsgVIU_FR_3D3PreCopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 IlMsgVIU_FR_3D1PreCopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 IlMsgVIU_FR_2F7PreCopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 IlMsgVIU_FR_2EFPreCopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 IlMsgVIU_FR_2ECPreCopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 IlMsgVIU_FR_288PreCopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 IlMsgVIU_FR_1C3PreCopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 TpPrecopyNormalDiagFunc(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 TpPrecopyNormalDiagPhys(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */


/* -----------------------------------------------------------------------------
    &&&~ Extern declarations of confirmation functions
 ----------------------------------------------------------------------------- */

/* CODE CATEGORY 1 START */
extern void TxAckCbk_VRHCU_6F9(CanTransmitHandle txObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void TxAckCbk_VRHCU_6EE(CanTransmitHandle txObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void CanNm_NmMsgConfirmation(CanTransmitHandle txObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void TxAckCbk_VRHCU_3F3(CanTransmitHandle txObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void TxAckCbk_VRHCU_3EE(CanTransmitHandle txObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void TpDrvConfirmation(CanTransmitHandle txObject);
/* CODE CATEGORY 1 END */



/* -----------------------------------------------------------------------------
    &&&~ Extern declarations of indication functions
 ----------------------------------------------------------------------------- */

/* CODE CATEGORY 1 START */
extern void IlMsgVIU_FR_3EDInd(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void IlMsgVIU_FR_3D3Ind(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void IlMsgVIU_FR_3D1Ind(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void IlMsgVIU_FR_2F7Ind(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void IlMsgVIU_FR_2EFInd(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void IlMsgVIU_FR_2ECInd(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void IlMsgVIU_FR_288Ind(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void IlMsgVIU_FR_1C3Ind(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */





/* -----------------------------------------------------------------------------
    &&&~ Handles of send objects
 ----------------------------------------------------------------------------- */

#define CanTxVRHCU_6F9                       0
#define CanTxVRHCU_6EE                       1
#define CanTxNMm_VRHCU                       2
#define CanTxVRHCU_3F3                       3
#define CanTxVRHCU_3EE                       4
#define CanTxTxDynamicMsg0                   5


/* -----------------------------------------------------------------------------
    &&&~ Access to confirmation flags
 ----------------------------------------------------------------------------- */

#define VRHCU_6F9_conf_b                     (CanConfirmationFlags.w[0].b0)
#define CanWriteSyncVRHCU_6F9_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  VRHCU_6F9_conf_b = (x); \
  CanEndFlagWriteSync(); \
}
#define VRHCU_6EE_conf_b                     (CanConfirmationFlags.w[0].b1)
#define CanWriteSyncVRHCU_6EE_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  VRHCU_6EE_conf_b = (x); \
  CanEndFlagWriteSync(); \
}
#define VRHCU_3F3_conf_b                     (CanConfirmationFlags.w[0].b2)
#define CanWriteSyncVRHCU_3F3_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  VRHCU_3F3_conf_b = (x); \
  CanEndFlagWriteSync(); \
}
#define VRHCU_3EE_conf_b                     (CanConfirmationFlags.w[0].b3)
#define CanWriteSyncVRHCU_3EE_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  VRHCU_3EE_conf_b = (x); \
  CanEndFlagWriteSync(); \
}
#define TxDynamicMsg0_conf_b                 (CanConfirmationFlags.w[0].b4)
#define CanWriteSyncTxDynamicMsg0_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  TxDynamicMsg0_conf_b = (x); \
  CanEndFlagWriteSync(); \
}


/* -----------------------------------------------------------------------------
    &&&~ Handles of receive objects
 ----------------------------------------------------------------------------- */

#define CanRxVIU_FR_3ED                      0
#define CanRxVIU_FR_3D3                      1
#define CanRxVIU_FR_3D1                      2
#define CanRxVIU_FR_2F7                      3
#define CanRxVIU_FR_2EF                      4
#define CanRxVIU_FR_2EC                      5
#define CanRxVIU_FR_288                      6
#define CanRxVIU_FR_1C3                      7
#define CanRxVIU_FR_7DF                      8
#define CanRxVIU_FR_777                      9


/* -----------------------------------------------------------------------------
    &&&~ Access to data bytes of Rx messages
 ----------------------------------------------------------------------------- */

/* ID: 0x000003ed, Handle: 0, VIU_FR_3ED [FC] */
#define c1_VIU_FR_3ED_c                      (VIU_FR_3ED._c[0])
#define c2_VIU_FR_3ED_c                      (VIU_FR_3ED._c[1])
#define c3_VIU_FR_3ED_c                      (VIU_FR_3ED._c[2])
#define c4_VIU_FR_3ED_c                      (VIU_FR_3ED._c[3])
#define c5_VIU_FR_3ED_c                      (VIU_FR_3ED._c[4])
#define c6_VIU_FR_3ED_c                      (VIU_FR_3ED._c[5])
#define c7_VIU_FR_3ED_c                      (VIU_FR_3ED._c[6])

/* ID: 0x000003d3, Handle: 1, VIU_FR_3D3 [FC] */
#define c1_VIU_FR_3D3_c                      (VIU_FR_3D3._c[0])
#define c2_VIU_FR_3D3_c                      (VIU_FR_3D3._c[1])
#define c3_VIU_FR_3D3_c                      (VIU_FR_3D3._c[2])
#define c4_VIU_FR_3D3_c                      (VIU_FR_3D3._c[3])
#define c5_VIU_FR_3D3_c                      (VIU_FR_3D3._c[4])
#define c6_VIU_FR_3D3_c                      (VIU_FR_3D3._c[5])

/* ID: 0x000003d1, Handle: 2, VIU_FR_3D1 [FC] */
#define c1_VIU_FR_3D1_c                      (VIU_FR_3D1._c[0])

/* ID: 0x000002f7, Handle: 3, VIU_FR_2F7 [FC] */
#define c1_VIU_FR_2F7_c                      (VIU_FR_2F7._c[0])
#define c2_VIU_FR_2F7_c                      (VIU_FR_2F7._c[1])
#define c3_VIU_FR_2F7_c                      (VIU_FR_2F7._c[2])
#define c4_VIU_FR_2F7_c                      (VIU_FR_2F7._c[3])
#define c5_VIU_FR_2F7_c                      (VIU_FR_2F7._c[4])
#define c6_VIU_FR_2F7_c                      (VIU_FR_2F7._c[5])

/* ID: 0x000002ef, Handle: 4, VIU_FR_2EF [FC] */
#define c1_VIU_FR_2EF_c                      (VIU_FR_2EF._c[0])
#define c2_VIU_FR_2EF_c                      (VIU_FR_2EF._c[1])
#define c3_VIU_FR_2EF_c                      (VIU_FR_2EF._c[2])
#define c4_VIU_FR_2EF_c                      (VIU_FR_2EF._c[3])

/* ID: 0x000002ec, Handle: 5, VIU_FR_2EC [FC] */
#define c1_VIU_FR_2EC_c                      (VIU_FR_2EC._c[0])

/* ID: 0x00000288, Handle: 6, VIU_FR_288 [FC] */
#define c1_VIU_FR_288_c                      (VIU_FR_288._c[0])
#define c2_VIU_FR_288_c                      (VIU_FR_288._c[1])
#define c3_VIU_FR_288_c                      (VIU_FR_288._c[2])
#define c4_VIU_FR_288_c                      (VIU_FR_288._c[3])
#define c5_VIU_FR_288_c                      (VIU_FR_288._c[4])
#define c6_VIU_FR_288_c                      (VIU_FR_288._c[5])

/* ID: 0x000001c3, Handle: 7, VIU_FR_1C3 [FC] */
#define c1_VIU_FR_1C3_c                      (VIU_FR_1C3._c[0])
#define c2_VIU_FR_1C3_c                      (VIU_FR_1C3._c[1])
#define c3_VIU_FR_1C3_c                      (VIU_FR_1C3._c[2])
#define c4_VIU_FR_1C3_c                      (VIU_FR_1C3._c[3])
#define c5_VIU_FR_1C3_c                      (VIU_FR_1C3._c[4])
#define c6_VIU_FR_1C3_c                      (VIU_FR_1C3._c[5])



/* -----------------------------------------------------------------------------
    &&&~ Access to data bytes of Tx messages
 ----------------------------------------------------------------------------- */

/* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */
#define c1_VRHCU_6F9_c                       (VRHCU_6F9._c[0])
#define c2_VRHCU_6F9_c                       (VRHCU_6F9._c[1])
#define c3_VRHCU_6F9_c                       (VRHCU_6F9._c[2])
#define c4_VRHCU_6F9_c                       (VRHCU_6F9._c[3])
#define c5_VRHCU_6F9_c                       (VRHCU_6F9._c[4])
#define c6_VRHCU_6F9_c                       (VRHCU_6F9._c[5])
#define c7_VRHCU_6F9_c                       (VRHCU_6F9._c[6])
#define c8_VRHCU_6F9_c                       (VRHCU_6F9._c[7])

/* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */
#define c1_VRHCU_6EE_c                       (VRHCU_6EE._c[0])
#define c2_VRHCU_6EE_c                       (VRHCU_6EE._c[1])
#define c3_VRHCU_6EE_c                       (VRHCU_6EE._c[2])
#define c4_VRHCU_6EE_c                       (VRHCU_6EE._c[3])
#define c5_VRHCU_6EE_c                       (VRHCU_6EE._c[4])
#define c6_VRHCU_6EE_c                       (VRHCU_6EE._c[5])
#define c7_VRHCU_6EE_c                       (VRHCU_6EE._c[6])
#define c8_VRHCU_6EE_c                       (VRHCU_6EE._c[7])

/* ID: 0x00000402, Handle: 2, NMm_VRHCU [BC] */
#define c1_NMm_VRHCU_c                       (NMm_VRHCU._c[0])
#define c2_NMm_VRHCU_c                       (NMm_VRHCU._c[1])
#define c3_NMm_VRHCU_c                       (NMm_VRHCU._c[2])
#define c4_NMm_VRHCU_c                       (NMm_VRHCU._c[3])
#define c5_NMm_VRHCU_c                       (NMm_VRHCU._c[4])
#define c6_NMm_VRHCU_c                       (NMm_VRHCU._c[5])
#define c7_NMm_VRHCU_c                       (NMm_VRHCU._c[6])
#define c8_NMm_VRHCU_c                       (NMm_VRHCU._c[7])

/* ID: 0x000003f3, Handle: 3, VRHCU_3F3 [BC] */
#define c1_VRHCU_3F3_c                       (VRHCU_3F3._c[0])
#define c2_VRHCU_3F3_c                       (VRHCU_3F3._c[1])
#define c3_VRHCU_3F3_c                       (VRHCU_3F3._c[2])
#define c4_VRHCU_3F3_c                       (VRHCU_3F3._c[3])
#define c5_VRHCU_3F3_c                       (VRHCU_3F3._c[4])
#define c6_VRHCU_3F3_c                       (VRHCU_3F3._c[5])
#define c7_VRHCU_3F3_c                       (VRHCU_3F3._c[6])
#define c8_VRHCU_3F3_c                       (VRHCU_3F3._c[7])

/* ID: 0x000003ee, Handle: 4, VRHCU_3EE [BC] */
#define c1_VRHCU_3EE_c                       (VRHCU_3EE._c[0])
#define c2_VRHCU_3EE_c                       (VRHCU_3EE._c[1])
#define c3_VRHCU_3EE_c                       (VRHCU_3EE._c[2])
#define c4_VRHCU_3EE_c                       (VRHCU_3EE._c[3])
#define c5_VRHCU_3EE_c                       (VRHCU_3EE._c[4])
#define c6_VRHCU_3EE_c                       (VRHCU_3EE._c[5])
#define c7_VRHCU_3EE_c                       (VRHCU_3EE._c[6])
#define c8_VRHCU_3EE_c                       (VRHCU_3EE._c[7])

/* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
#define c1_TxDynamicMsg0_c                   (TxDynamicMsg0._c[0])
#define c2_TxDynamicMsg0_c                   (TxDynamicMsg0._c[1])
#define c3_TxDynamicMsg0_c                   (TxDynamicMsg0._c[2])
#define c4_TxDynamicMsg0_c                   (TxDynamicMsg0._c[3])
#define c5_TxDynamicMsg0_c                   (TxDynamicMsg0._c[4])
#define c6_TxDynamicMsg0_c                   (TxDynamicMsg0._c[5])
#define c7_TxDynamicMsg0_c                   (TxDynamicMsg0._c[6])
#define c8_TxDynamicMsg0_c                   (TxDynamicMsg0._c[7])



/* -----------------------------------------------------------------------------
    &&&~ RDS Access RI2.0
 ----------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
    &&&~ RDSSignalAccessStructs_RI20
 ----------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_VIU_FR_7DF_RDS_msgTypeTag
{
  vbittype Diagnose_message_7DF_7 : 8;
  vbittype Diagnose_message_7DF_6 : 8;
  vbittype Diagnose_message_7DF_5 : 8;
  vbittype Diagnose_message_7DF_4 : 8;
  vbittype Diagnose_message_7DF_3 : 8;
  vbittype Diagnose_message_7DF_2 : 8;
  vbittype Diagnose_message_7DF_1 : 8;
  vbittype Diagnose_message_7DF_0 : 8;
} _c_VIU_FR_7DF_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_VIU_FR_777_RDS_msgTypeTag
{
  vbittype Diagnose_message_777_7 : 8;
  vbittype Diagnose_message_777_6 : 8;
  vbittype Diagnose_message_777_5 : 8;
  vbittype Diagnose_message_777_4 : 8;
  vbittype Diagnose_message_777_3 : 8;
  vbittype Diagnose_message_777_2 : 8;
  vbittype Diagnose_message_777_1 : 8;
  vbittype Diagnose_message_777_0 : 8;
} _c_VIU_FR_777_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_VIU_FR_3ED_RDS_msgTypeTag
{
  vbittype FridgeQFunReq : 4;
  vbittype FridgeModeReq : 2;
  vbittype FridgeWorkReq : 2;
  vbittype FridgeUnlockCtrl : 2;
  vbittype FridgeHeatTempReq : 5;
  vbittype unused0 : 1;
  vbittype FridgeChdLockReq : 2;
  vbittype FridgeCoolTempReq : 5;
  vbittype unused1 : 1;
  vbittype FridgeUVLedReq : 2;
  vbittype FridgeUVLedWorkTimeSet : 5;
  vbittype unused2 : 1;
  vbittype ContinueWorkSw : 2;
  vbittype EgySaveModReq : 2;
  vbittype FridgeDoorWarnTimeSet : 3;
  vbittype unused3 : 1;
  vbittype ContinueWorkTimeSet : 8;
  vbittype unused4 : 4;
  vbittype VrhcuONReas : 2;
  vbittype VrhcuExOffReas : 2;
} _c_VIU_FR_3ED_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_VIU_FR_3D3_RDS_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 4;
  vbittype BcuOperMod : 4;
} _c_VIU_FR_3D3_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_VIU_FR_3D1_RDS_msgTypeTag
{
  vbittype unused0 : 4;
  vbittype DcdcOperSts : 4;
} _c_VIU_FR_3D1_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_VIU_FR_2F7_RDS_msgTypeTag
{
  vbittype TboxLocalTiYear : 8;
  vbittype TboxLocalTiMth : 4;
  vbittype unused0 : 4;
  vbittype TboxLocalTiDate : 5;
  vbittype unused1 : 3;
  vbittype TboxLocalTiHr : 5;
  vbittype unused2 : 3;
  vbittype TboxLocalTiMins : 6;
  vbittype unused3 : 2;
  vbittype TboxLocalTiSec : 6;
  vbittype TboxLocalTiVld : 1;
  vbittype unused4 : 1;
} _c_VIU_FR_2F7_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_VIU_FR_2EF_RDS_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype CdcTotMilg_2 : 8;
  vbittype CdcTotMilg_1 : 8;
  vbittype CdcTotMilg_0 : 8;
} _c_VIU_FR_2EF_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_VIU_FR_2EC_RDS_msgTypeTag
{
  vbittype unused0 : 2;
  vbittype VcuVehGearPosnVld : 1;
  vbittype VcuGearPosn : 3;
  vbittype unused1 : 2;
} _c_VIU_FR_2EC_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_VIU_FR_288_RDS_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 2;
  vbittype BcmPwrStsFb : 2;
  vbittype unused6 : 4;
} _c_VIU_FR_288_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_VIU_FR_1C3_RDS_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype EspVehSpd_1 : 5;
  vbittype EspVehSpdVld : 1;
  vbittype unused4 : 2;
  vbittype EspVehSpd_0 : 8;
} _c_VIU_FR_1C3_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_VRHCU_6F9_RDS_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype VRHCP_WakeUp_BYTE3BIT0 : 1;
  vbittype unused3 : 7;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 8;
  vbittype VRHCP_NotSleep_BYTE7BIT0 : 1;
  vbittype VRHCP_NotSleep_BYTE7BIT1 : 1;
  vbittype VRHCP_NotSleep_BYTE7BIT2 : 1;
  vbittype unused7 : 5;
} _c_VRHCU_6F9_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_VRHCU_6EE_RDS_msgTypeTag
{
  vbittype VrhcuDTC1_HighByte : 8;
  vbittype VrhcuDTC1_MiddByte : 8;
  vbittype VrhcuDTC1_LowByte : 8;
  vbittype VrhcuDTC1_Status : 8;
  vbittype VrhcuDTC2_HighByte : 8;
  vbittype VrhcuDTC2_MiddByte : 8;
  vbittype VrhcuDTC2_LowByte : 8;
  vbittype VrhcuDTC2_Status : 8;
} _c_VRHCU_6EE_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_NMm_VRHCU_RDS_msgTypeTag
{
  vbittype srcNodeID_VRHCU : 8;
  vbittype RMR_VRHCU : 1;
  vbittype unused0 : 2;
  vbittype NMCSR_VRHCU : 1;
  vbittype AWU_VRHCU : 1;
  vbittype unused1 : 1;
  vbittype PNI_VRHCU : 1;
  vbittype unused2 : 1;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 7;
  vbittype NMSI_VRHCU : 1;
  vbittype unused7 : 8;
  vbittype FunctionID_VRHCU : 8;
} _c_NMm_VRHCU_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_VRHCU_3F3_RDS_msgTypeTag
{
  vbittype VrhcuRequestACOn : 1;
  vbittype VrhcuRefrAcpTemp : 7;
  vbittype Vrhcupower : 7;
  vbittype unused0 : 1;
  vbittype VrhcuOffReas : 2;
  vbittype unused1 : 6;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 8;
} _c_VRHCU_3F3_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_VRHCU_3EE_RDS_msgTypeTag
{
  vbittype FridgeWorkSt : 2;
  vbittype FridgeUVLedWorkSt : 5;
  vbittype unused0 : 1;
  vbittype FridgeDoorSt : 2;
  vbittype FridgeHeatTempSt : 5;
  vbittype unused1 : 1;
  vbittype FridgeModeSt : 2;
  vbittype FridgeCoolTempSt : 5;
  vbittype unused2 : 1;
  vbittype FridgeDoorWarnSt : 2;
  vbittype FridgeErrSt : 5;
  vbittype unused3 : 1;
  vbittype FridgeHeatActSt : 7;
  vbittype unused4 : 1;
  vbittype FridgeQFunSt : 4;
  vbittype FridgeChdLockSt : 2;
  vbittype EgySaveModSt : 2;
  vbittype FridgestuffSt : 2;
  vbittype FridgeUVLedSt : 2;
  vbittype FridgeDoorWarnTimeSt : 2;
  vbittype unused5 : 2;
  vbittype ContinueWorkTimeSt : 8;
} _c_VRHCU_3EE_RDS_msgType;




/* -----------------------------------------------------------------------------
    &&&~ RDSUnionForCanObjects_RI20
 ----------------------------------------------------------------------------- */

typedef union _c_RDS1_bufTag
{
  vuint8 _c[8];
  _c_VIU_FR_7DF_RDS_msgType VIU_FR_7DF;
} _c_RDS1_buf;
typedef union _c_RDS2_bufTag
{
  vuint8 _c[8];
  _c_VIU_FR_777_RDS_msgType VIU_FR_777;
} _c_RDS2_buf;
typedef union _c_RDS3_bufTag
{
  vuint8 _c[7];
  _c_VIU_FR_3ED_RDS_msgType VIU_FR_3ED;
} _c_RDS3_buf;
typedef union _c_RDS4_bufTag
{
  vuint8 _c[6];
  _c_VIU_FR_3D3_RDS_msgType VIU_FR_3D3;
} _c_RDS4_buf;
typedef union _c_RDS5_bufTag
{
  vuint8 _c[1];
  _c_VIU_FR_3D1_RDS_msgType VIU_FR_3D1;
} _c_RDS5_buf;
typedef union _c_RDS6_bufTag
{
  vuint8 _c[6];
  _c_VIU_FR_2F7_RDS_msgType VIU_FR_2F7;
} _c_RDS6_buf;
typedef union _c_RDS7_bufTag
{
  vuint8 _c[4];
  _c_VIU_FR_2EF_RDS_msgType VIU_FR_2EF;
} _c_RDS7_buf;
typedef union _c_RDS8_bufTag
{
  vuint8 _c[1];
  _c_VIU_FR_2EC_RDS_msgType VIU_FR_2EC;
} _c_RDS8_buf;
typedef union _c_RDS9_bufTag
{
  vuint8 _c[6];
  _c_VIU_FR_288_RDS_msgType VIU_FR_288;
} _c_RDS9_buf;
typedef union _c_RDS10_bufTag
{
  vuint8 _c[6];
  _c_VIU_FR_1C3_RDS_msgType VIU_FR_1C3;
} _c_RDS10_buf;
typedef union _c_RDS_Tx_bufTag
{
  vuint8 _c[8];
  _c_VRHCU_6F9_RDS_msgType VRHCU_6F9;
  _c_VRHCU_6EE_RDS_msgType VRHCU_6EE;
  _c_NMm_VRHCU_RDS_msgType NMm_VRHCU;
  _c_VRHCU_3F3_RDS_msgType VRHCU_3F3;
  _c_VRHCU_3EE_RDS_msgType VRHCU_3EE;
} _c_RDS_Tx_buf;


/* -----------------------------------------------------------------------------
    &&&~ RDSMacrosForCanObjects_RI20
 ----------------------------------------------------------------------------- */

#define RDS1                                 ((* ((_c_RDS1_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS2                                 ((* ((_c_RDS2_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS3                                 ((* ((_c_RDS3_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS4                                 ((* ((_c_RDS4_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS5                                 ((* ((_c_RDS5_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS6                                 ((* ((_c_RDS6_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS7                                 ((* ((_c_RDS7_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS8                                 ((* ((_c_RDS8_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS9                                 ((* ((_c_RDS9_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS10                                ((* ((_c_RDS10_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDSTx                                ((* ((_c_RDS_Tx_buf MEMORY_NORMAL *)(canRDSTxPtr[0]))))




/* -----------------------------------------------------------------------------
    &&&~ Message Hardware Objects RI20
 ----------------------------------------------------------------------------- */

#define C_BASIC0_HW_OBJ                      0
#define C_BASIC0_HW_CHANNEL                  0
#define CanRxVIU_FR_7DF_HW_OBJ               1
#define CanRxVIU_FR_7DF_HW_CHANNEL           0
#define CanRxVIU_FR_777_HW_OBJ               2
#define CanRxVIU_FR_777_HW_CHANNEL           0
#define CanRxVIU_FR_3ED_HW_OBJ               3
#define CanRxVIU_FR_3ED_HW_CHANNEL           0
#define CanRxVIU_FR_3D3_HW_OBJ               4
#define CanRxVIU_FR_3D3_HW_CHANNEL           0
#define CanRxVIU_FR_3D1_HW_OBJ               5
#define CanRxVIU_FR_3D1_HW_CHANNEL           0
#define CanRxVIU_FR_2F7_HW_OBJ               6
#define CanRxVIU_FR_2F7_HW_CHANNEL           0
#define CanRxVIU_FR_2EF_HW_OBJ               7
#define CanRxVIU_FR_2EF_HW_CHANNEL           0
#define CanRxVIU_FR_2EC_HW_OBJ               8
#define CanRxVIU_FR_2EC_HW_CHANNEL           0
#define CanRxVIU_FR_288_HW_OBJ               9
#define CanRxVIU_FR_288_HW_CHANNEL           0
#define CanRxVIU_FR_1C3_HW_OBJ               10
#define CanRxVIU_FR_1C3_HW_CHANNEL           0
#define C_TX_NORMAL_HW_OBJ                   11
#define C_TX_NORMAL_HW_CHANNEL               0





#endif /* __CAN_PAR_H__ */
