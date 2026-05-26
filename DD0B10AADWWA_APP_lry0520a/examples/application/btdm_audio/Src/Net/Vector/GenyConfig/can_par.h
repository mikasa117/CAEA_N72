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
               
               Configuration   : E:\Bluetooth\GENy\GENy1_N72_260119.gny
               
               ECU: 
                       TargetSystem: Hw_S32Cpu
                       Compiler:     GNU
                       Derivates:    S32K146
               
               Channel "Channel0":
                       Databasefile: E:\Bluetooth\DBC\N72ÏîÄ¿BTM_20260117.dbc
                       Bussystem:    CAN
                       Manufacturer: Vector
                       Node:         BTM

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
#endif

/* CODE CATEGORY 1 START */
extern vuint8 IlMsgPMS_VINPreCopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 IlMsgIPK_TotalOdometerPreCopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 IlMsgTBOX_DateTime_InfoPreCopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 IlMsgEHB_StatusPreCopy(CanRxInfoStructPtr rxStruct);
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
extern void TxAckCbk_BTM_DiagResp(CanTransmitHandle txObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void TxAckCbk_MMI_Status_Info(CanTransmitHandle txObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void TxAckCbk_TTS_Status(CanTransmitHandle txObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void TxAckCbk_MMI_TextMMData(CanTransmitHandle txObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void TxAckCbk_MMI_TextBTData(CanTransmitHandle txObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void TpDrvConfirmation(CanTransmitHandle txObject);
/* CODE CATEGORY 1 END */



/* -----------------------------------------------------------------------------
    &&&~ Extern declarations of indication functions
 ----------------------------------------------------------------------------- */

/* CODE CATEGORY 1 START */
extern void IlMsgPMS_VINInd(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void IlMsgIPK_TotalOdometerInd(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void IlMsgTBOX_DateTime_InfoInd(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void IlMsgEHB_StatusInd(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void IlMsgFunc_DiagReqInd(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void IlMsgBTM_DiagReqInd(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */





/* -----------------------------------------------------------------------------
    &&&~ Handles of send objects
 ----------------------------------------------------------------------------- */

#define CanTxBTM_DiagResp                    0
#define CanTxMMI_Status_Info                 1
#define CanTxTTS_Status                      2
#define CanTxMMI_TextMMData                  3
#define CanTxMMI_TextBTData                  4
#define CanTxTxDynamicMsg0                   5


/* -----------------------------------------------------------------------------
    &&&~ Access to confirmation flags
 ----------------------------------------------------------------------------- */

#define BTM_DiagResp_conf_b                  (CanConfirmationFlags.w[0].b0)
#define CanWriteSyncBTM_DiagResp_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  BTM_DiagResp_conf_b = (x); \
  CanEndFlagWriteSync(); \
}
#define MMI_Status_Info_conf_b               (CanConfirmationFlags.w[0].b1)
#define CanWriteSyncMMI_Status_Info_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  MMI_Status_Info_conf_b = (x); \
  CanEndFlagWriteSync(); \
}
#define TTS_Status_conf_b                    (CanConfirmationFlags.w[0].b2)
#define CanWriteSyncTTS_Status_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  TTS_Status_conf_b = (x); \
  CanEndFlagWriteSync(); \
}
#define MMI_TextMMData_conf_b                (CanConfirmationFlags.w[0].b3)
#define CanWriteSyncMMI_TextMMData_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  MMI_TextMMData_conf_b = (x); \
  CanEndFlagWriteSync(); \
}
#define MMI_TextBTData_conf_b                (CanConfirmationFlags.w[0].b4)
#define CanWriteSyncMMI_TextBTData_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  MMI_TextBTData_conf_b = (x); \
  CanEndFlagWriteSync(); \
}
#define TxDynamicMsg0_conf_b                 (CanConfirmationFlags.w[0].b5)
#define CanWriteSyncTxDynamicMsg0_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  TxDynamicMsg0_conf_b = (x); \
  CanEndFlagWriteSync(); \
}


/* -----------------------------------------------------------------------------
    &&&~ Handles of receive objects
 ----------------------------------------------------------------------------- */

#define CanRxPMS_VIN                         0
#define CanRxIPK_TotalOdometer               1
#define CanRxTBOX_DateTime_Info              2
#define CanRxEHB_Status                      3
#define CanRxFunc_DiagReq                    4
#define CanRxBTM_DiagReq                     5


/* -----------------------------------------------------------------------------
    &&&~ Access to indication flags
 ----------------------------------------------------------------------------- */

#define Func_DiagReq_ind_b                   (CanIndicationFlags.w[0].b0)
#define CanWriteSyncFunc_DiagReq_ind_b(x) \
{ \
  CanStartFlagWriteSync(); \
  Func_DiagReq_ind_b = (x); \
  CanEndFlagWriteSync(); \
}
#define BTM_DiagReq_ind_b                    (CanIndicationFlags.w[0].b1)
#define CanWriteSyncBTM_DiagReq_ind_b(x) \
{ \
  CanStartFlagWriteSync(); \
  BTM_DiagReq_ind_b = (x); \
  CanEndFlagWriteSync(); \
}


/* -----------------------------------------------------------------------------
    &&&~ Access to signals
 ----------------------------------------------------------------------------- */

#define b_Func_DiagResp_0_b                  (Func_DiagReq.Func_DiagReq.Func_DiagResp_0)
#define b_Func_DiagResp_1_b                  (Func_DiagReq.Func_DiagReq.Func_DiagResp_1)
#define b_Func_DiagResp_2_b                  (Func_DiagReq.Func_DiagReq.Func_DiagResp_2)
#define b_Func_DiagResp_3_b                  (Func_DiagReq.Func_DiagReq.Func_DiagResp_3)
#define b_Func_DiagResp_4_b                  (Func_DiagReq.Func_DiagReq.Func_DiagResp_4)
#define b_Func_DiagResp_5_b                  (Func_DiagReq.Func_DiagReq.Func_DiagResp_5)
#define b_Func_DiagResp_6_b                  (Func_DiagReq.Func_DiagReq.Func_DiagResp_6)
#define b_Func_DiagResp_7_b                  (Func_DiagReq.Func_DiagReq.Func_DiagResp_7)
#define b_BTM_DiagReq_0_b                    (BTM_DiagReq.BTM_DiagReq.BTM_DiagReq_0)
#define b_BTM_DiagReq_1_b                    (BTM_DiagReq.BTM_DiagReq.BTM_DiagReq_1)
#define b_BTM_DiagReq_2_b                    (BTM_DiagReq.BTM_DiagReq.BTM_DiagReq_2)
#define b_BTM_DiagReq_3_b                    (BTM_DiagReq.BTM_DiagReq.BTM_DiagReq_3)
#define b_BTM_DiagReq_4_b                    (BTM_DiagReq.BTM_DiagReq.BTM_DiagReq_4)
#define b_BTM_DiagReq_5_b                    (BTM_DiagReq.BTM_DiagReq.BTM_DiagReq_5)
#define b_BTM_DiagReq_6_b                    (BTM_DiagReq.BTM_DiagReq.BTM_DiagReq_6)
#define b_BTM_DiagReq_7_b                    (BTM_DiagReq.BTM_DiagReq.BTM_DiagReq_7)


/* -----------------------------------------------------------------------------
    &&&~ Access to data bytes of Rx messages
 ----------------------------------------------------------------------------- */

/* ID: 0x00000610, Handle: 0, PMS_VIN [BC] */
#define c1_PMS_VIN_c                         (PMS_VIN._c[0])
#define c2_PMS_VIN_c                         (PMS_VIN._c[1])
#define c3_PMS_VIN_c                         (PMS_VIN._c[2])
#define c4_PMS_VIN_c                         (PMS_VIN._c[3])
#define c5_PMS_VIN_c                         (PMS_VIN._c[4])
#define c6_PMS_VIN_c                         (PMS_VIN._c[5])
#define c7_PMS_VIN_c                         (PMS_VIN._c[6])
#define c8_PMS_VIN_c                         (PMS_VIN._c[7])

/* ID: 0x000003f1, Handle: 1, IPK_TotalOdometer [BC] */
#define c1_IPK_TotalOdometer_c               (IPK_TotalOdometer._c[0])
#define c2_IPK_TotalOdometer_c               (IPK_TotalOdometer._c[1])
#define c3_IPK_TotalOdometer_c               (IPK_TotalOdometer._c[2])

/* ID: 0x000003e0, Handle: 2, TBOX_DateTime_Info [BC] */
#define c1_TBOX_DateTime_Info_c              (TBOX_DateTime_Info._c[0])
#define c2_TBOX_DateTime_Info_c              (TBOX_DateTime_Info._c[1])
#define c3_TBOX_DateTime_Info_c              (TBOX_DateTime_Info._c[2])
#define c4_TBOX_DateTime_Info_c              (TBOX_DateTime_Info._c[3])
#define c5_TBOX_DateTime_Info_c              (TBOX_DateTime_Info._c[4])
#define c6_TBOX_DateTime_Info_c              (TBOX_DateTime_Info._c[5])

/* ID: 0x00000125, Handle: 3, EHB_Status [BC] */
#define c1_EHB_Status_c                      (EHB_Status._c[0])
#define c2_EHB_Status_c                      (EHB_Status._c[1])
#define c3_EHB_Status_c                      (EHB_Status._c[2])

/* ID: 0x000007df, Handle: 4, Func_DiagReq [BC] */
#define c1_Func_DiagReq_c                    (Func_DiagReq._c[0])
#define c2_Func_DiagReq_c                    (Func_DiagReq._c[1])
#define c3_Func_DiagReq_c                    (Func_DiagReq._c[2])
#define c4_Func_DiagReq_c                    (Func_DiagReq._c[3])
#define c5_Func_DiagReq_c                    (Func_DiagReq._c[4])
#define c6_Func_DiagReq_c                    (Func_DiagReq._c[5])
#define c7_Func_DiagReq_c                    (Func_DiagReq._c[6])
#define c8_Func_DiagReq_c                    (Func_DiagReq._c[7])

/* ID: 0x00000761, Handle: 5, BTM_DiagReq [BC] */
#define c1_BTM_DiagReq_c                     (BTM_DiagReq._c[0])
#define c2_BTM_DiagReq_c                     (BTM_DiagReq._c[1])
#define c3_BTM_DiagReq_c                     (BTM_DiagReq._c[2])
#define c4_BTM_DiagReq_c                     (BTM_DiagReq._c[3])
#define c5_BTM_DiagReq_c                     (BTM_DiagReq._c[4])
#define c6_BTM_DiagReq_c                     (BTM_DiagReq._c[5])
#define c7_BTM_DiagReq_c                     (BTM_DiagReq._c[6])
#define c8_BTM_DiagReq_c                     (BTM_DiagReq._c[7])



/* -----------------------------------------------------------------------------
    &&&~ Access to data bytes of Tx messages
 ----------------------------------------------------------------------------- */

/* ID: 0x00000769, Handle: 0, BTM_DiagResp [BC] */
#define c1_BTM_DiagResp_c                    (BTM_DiagResp._c[0])
#define c2_BTM_DiagResp_c                    (BTM_DiagResp._c[1])
#define c3_BTM_DiagResp_c                    (BTM_DiagResp._c[2])
#define c4_BTM_DiagResp_c                    (BTM_DiagResp._c[3])
#define c5_BTM_DiagResp_c                    (BTM_DiagResp._c[4])
#define c6_BTM_DiagResp_c                    (BTM_DiagResp._c[5])
#define c7_BTM_DiagResp_c                    (BTM_DiagResp._c[6])
#define c8_BTM_DiagResp_c                    (BTM_DiagResp._c[7])

/* ID: 0x000002a4, Handle: 1, MMI_Status_Info [BC] */
#define c1_MMI_Status_Info_c                 (MMI_Status_Info._c[0])
#define c2_MMI_Status_Info_c                 (MMI_Status_Info._c[1])
#define c3_MMI_Status_Info_c                 (MMI_Status_Info._c[2])
#define c4_MMI_Status_Info_c                 (MMI_Status_Info._c[3])
#define c5_MMI_Status_Info_c                 (MMI_Status_Info._c[4])
#define c6_MMI_Status_Info_c                 (MMI_Status_Info._c[5])
#define c7_MMI_Status_Info_c                 (MMI_Status_Info._c[6])
#define c8_MMI_Status_Info_c                 (MMI_Status_Info._c[7])

/* ID: 0x00000249, Handle: 2, TTS_Status [BC] */
#define c1_TTS_Status_c                      (TTS_Status._c[0])
#define c2_TTS_Status_c                      (TTS_Status._c[1])
#define c3_TTS_Status_c                      (TTS_Status._c[2])
#define c4_TTS_Status_c                      (TTS_Status._c[3])
#define c5_TTS_Status_c                      (TTS_Status._c[4])
#define c6_TTS_Status_c                      (TTS_Status._c[5])
#define c7_TTS_Status_c                      (TTS_Status._c[6])
#define c8_TTS_Status_c                      (TTS_Status._c[7])

/* ID: 0x000000fb, Handle: 3, MMI_TextMMData [BC] */
#define c1_MMI_TextMMData_c                  (MMI_TextMMData._c[0])
#define c2_MMI_TextMMData_c                  (MMI_TextMMData._c[1])
#define c3_MMI_TextMMData_c                  (MMI_TextMMData._c[2])
#define c4_MMI_TextMMData_c                  (MMI_TextMMData._c[3])
#define c5_MMI_TextMMData_c                  (MMI_TextMMData._c[4])
#define c6_MMI_TextMMData_c                  (MMI_TextMMData._c[5])
#define c7_MMI_TextMMData_c                  (MMI_TextMMData._c[6])
#define c8_MMI_TextMMData_c                  (MMI_TextMMData._c[7])

/* ID: 0x000000f9, Handle: 4, MMI_TextBTData [BC] */
#define c1_MMI_TextBTData_c                  (MMI_TextBTData._c[0])
#define c2_MMI_TextBTData_c                  (MMI_TextBTData._c[1])
#define c3_MMI_TextBTData_c                  (MMI_TextBTData._c[2])
#define c4_MMI_TextBTData_c                  (MMI_TextBTData._c[3])
#define c5_MMI_TextBTData_c                  (MMI_TextBTData._c[4])
#define c6_MMI_TextBTData_c                  (MMI_TextBTData._c[5])
#define c7_MMI_TextBTData_c                  (MMI_TextBTData._c[6])
#define c8_MMI_TextBTData_c                  (MMI_TextBTData._c[7])

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
    &&&~ RDSSignalAccess_RI20
 ----------------------------------------------------------------------------- */

#define b_CAN_Func_DiagResp_0_b              (RDSBasic.Func_DiagReq.Func_DiagResp_0)
#define b_CAN_Func_DiagResp_1_b              (RDSBasic.Func_DiagReq.Func_DiagResp_1)
#define b_CAN_Func_DiagResp_2_b              (RDSBasic.Func_DiagReq.Func_DiagResp_2)
#define b_CAN_Func_DiagResp_3_b              (RDSBasic.Func_DiagReq.Func_DiagResp_3)
#define b_CAN_Func_DiagResp_4_b              (RDSBasic.Func_DiagReq.Func_DiagResp_4)
#define b_CAN_Func_DiagResp_5_b              (RDSBasic.Func_DiagReq.Func_DiagResp_5)
#define b_CAN_Func_DiagResp_6_b              (RDSBasic.Func_DiagReq.Func_DiagResp_6)
#define b_CAN_Func_DiagResp_7_b              (RDSBasic.Func_DiagReq.Func_DiagResp_7)


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_Func_DiagReq_RDS_msgTypeTag
{
  vbittype Func_DiagResp_7 : 8;
  vbittype Func_DiagResp_6 : 8;
  vbittype Func_DiagResp_5 : 8;
  vbittype Func_DiagResp_4 : 8;
  vbittype Func_DiagResp_3 : 8;
  vbittype Func_DiagResp_2 : 8;
  vbittype Func_DiagResp_1 : 8;
  vbittype Func_DiagResp_0 : 8;
} _c_Func_DiagReq_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSSignalAccess_RI20
 ----------------------------------------------------------------------------- */

#define b_CAN_BTM_DiagReq_0_b                (RDSBasic.BTM_DiagReq.BTM_DiagReq_0)
#define b_CAN_BTM_DiagReq_1_b                (RDSBasic.BTM_DiagReq.BTM_DiagReq_1)
#define b_CAN_BTM_DiagReq_2_b                (RDSBasic.BTM_DiagReq.BTM_DiagReq_2)
#define b_CAN_BTM_DiagReq_3_b                (RDSBasic.BTM_DiagReq.BTM_DiagReq_3)
#define b_CAN_BTM_DiagReq_4_b                (RDSBasic.BTM_DiagReq.BTM_DiagReq_4)
#define b_CAN_BTM_DiagReq_5_b                (RDSBasic.BTM_DiagReq.BTM_DiagReq_5)
#define b_CAN_BTM_DiagReq_6_b                (RDSBasic.BTM_DiagReq.BTM_DiagReq_6)
#define b_CAN_BTM_DiagReq_7_b                (RDSBasic.BTM_DiagReq.BTM_DiagReq_7)


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_BTM_DiagReq_RDS_msgTypeTag
{
  vbittype BTM_DiagReq_7 : 8;
  vbittype BTM_DiagReq_6 : 8;
  vbittype BTM_DiagReq_5 : 8;
  vbittype BTM_DiagReq_4 : 8;
  vbittype BTM_DiagReq_3 : 8;
  vbittype BTM_DiagReq_2 : 8;
  vbittype BTM_DiagReq_1 : 8;
  vbittype BTM_DiagReq_0 : 8;
} _c_BTM_DiagReq_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_PMS_VIN_RDS_msgTypeTag
{
  vbittype PMS_VINMessageNum_S : 8;
  vbittype PMS_VINCode1_8_15_S : 8;
  vbittype PMS_VINCode2_9_16_S : 8;
  vbittype PMS_VINCode3_10_17_S : 8;
  vbittype PMS_VINCode4_11_S : 8;
  vbittype PMS_VINCode5_12_S : 8;
  vbittype PMS_VINCode6_13_S : 8;
  vbittype PMS_VINCode7_14_S : 8;
} _c_PMS_VIN_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_IPK_TotalOdometer_RDS_msgTypeTag
{
  vbittype IPK_IPKTotalOdometer_2 : 8;
  vbittype IPK_IPKTotalOdometer_1 : 8;
  vbittype IPK_IPKTotalOdometer_0 : 8;
} _c_IPK_TotalOdometer_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_TBOX_DateTime_Info_RDS_msgTypeTag
{
  vbittype TBOX_Second : 8;
  vbittype TBOX_Minute : 8;
  vbittype TBOX_Hour : 8;
  vbittype TBOX_Month : 8;
  vbittype TBOX_Day : 8;
  vbittype TBOX_Year : 8;
} _c_TBOX_DateTime_Info_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_EHB_Status_RDS_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype EHB_VehicleSpeed_1 : 8;
  vbittype unused1 : 2;
  vbittype EHB_VehicleSpeedInvalid : 1;
  vbittype EHB_VehicleSpeed_0 : 5;
} _c_EHB_Status_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_BTM_DiagResp_RDS_msgTypeTag
{
  vbittype BTM_DiagResp_7 : 8;
  vbittype BTM_DiagResp_6 : 8;
  vbittype BTM_DiagResp_5 : 8;
  vbittype BTM_DiagResp_4 : 8;
  vbittype BTM_DiagResp_3 : 8;
  vbittype BTM_DiagResp_2 : 8;
  vbittype BTM_DiagResp_1 : 8;
  vbittype BTM_DiagResp_0 : 8;
} _c_BTM_DiagResp_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_MMI_Status_Info_RDS_msgTypeTag
{
  vbittype MMI_RightSwStatus : 2;
  vbittype MMI_LeftSwStatus : 2;
  vbittype MMI_UpSwStatus : 2;
  vbittype MMI_DownSwStatus : 2;
  vbittype MMI_ConfirmSwStatus : 2;
  vbittype MMI_ReturnSwStatus : 2;
  vbittype MMI_WorkMode : 2;
  vbittype unused0 : 2;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 8;
} _c_MMI_Status_Info_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_TTS_Status_RDS_msgTypeTag
{
  vbittype unused0 : 4;
  vbittype TTS_BluetoothFunction : 1;
  vbittype TTS_BluetoothConnect : 1;
  vbittype unused1 : 2;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 8;
  vbittype unused7 : 8;
  vbittype unused8 : 8;
} _c_TTS_Status_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_MMI_TextMMData_RDS_msgTypeTag
{
  vbittype MMI_TextMultDataFrame_7 : 8;
  vbittype MMI_TextMultDataFrame_6 : 8;
  vbittype MMI_TextMultDataFrame_5 : 8;
  vbittype MMI_TextMultDataFrame_4 : 8;
  vbittype MMI_TextMultDataFrame_3 : 8;
  vbittype MMI_TextMultDataFrame_2 : 8;
  vbittype MMI_TextMultDataFrame_1 : 8;
  vbittype MMI_TextMultDataFrame_0 : 8;
} _c_MMI_TextMMData_RDS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ RDSMsgStruct_RI20
 ----------------------------------------------------------------------------- */

typedef struct _c_MMI_TextBTData_RDS_msgTypeTag
{
  vbittype MMI_TextBTDataFrame_7 : 8;
  vbittype MMI_TextBTDataFrame_6 : 8;
  vbittype MMI_TextBTDataFrame_5 : 8;
  vbittype MMI_TextBTDataFrame_4 : 8;
  vbittype MMI_TextBTDataFrame_3 : 8;
  vbittype MMI_TextBTDataFrame_2 : 8;
  vbittype MMI_TextBTDataFrame_1 : 8;
  vbittype MMI_TextBTDataFrame_0 : 8;
} _c_MMI_TextBTData_RDS_msgType;




/* -----------------------------------------------------------------------------
    &&&~ RDSUnionForCanObjects_RI20
 ----------------------------------------------------------------------------- */

typedef union _c_RDSBasic_bufTag
{
  vuint8 _c[8];
  _c_Func_DiagReq_RDS_msgType Func_DiagReq;
  _c_BTM_DiagReq_RDS_msgType BTM_DiagReq;
  _c_PMS_VIN_RDS_msgType PMS_VIN;
  _c_IPK_TotalOdometer_RDS_msgType IPK_TotalOdometer;
  _c_TBOX_DateTime_Info_RDS_msgType TBOX_DateTime_Info;
  _c_EHB_Status_RDS_msgType EHB_Status;
} _c_RDSBasic_buf;
typedef union _c_RDS_Tx_bufTag
{
  vuint8 _c[8];
  _c_BTM_DiagResp_RDS_msgType BTM_DiagResp;
  _c_MMI_Status_Info_RDS_msgType MMI_Status_Info;
  _c_TTS_Status_RDS_msgType TTS_Status;
  _c_MMI_TextMMData_RDS_msgType MMI_TextMMData;
  _c_MMI_TextBTData_RDS_msgType MMI_TextBTData;
} _c_RDS_Tx_buf;


/* -----------------------------------------------------------------------------
    &&&~ RDSMacrosForCanObjects_RI20
 ----------------------------------------------------------------------------- */

#define RDSBasic                             ((* ((_c_RDSBasic_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDSTx                                ((* ((_c_RDS_Tx_buf MEMORY_NORMAL *)(canRDSTxPtr[0]))))




/* -----------------------------------------------------------------------------
    &&&~ Message Hardware Objects RI20
 ----------------------------------------------------------------------------- */

#define C_BASIC0_HW_OBJ                      0
#define C_BASIC0_HW_CHANNEL                  0
#define C_TX_NORMAL_HW_OBJ                   1
#define C_TX_NORMAL_HW_CHANNEL               0





#endif /* __CAN_PAR_H__ */
