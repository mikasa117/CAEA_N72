/* -----------------------------------------------------------------------------
  Filename:    can_par.c
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

#define C_DRV_INTERNAL
#include "can_inc.h"
#include "can_par.h"
#include "v_inc.h"

/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tCanTxId0 V_MEMROM2 CanTxId0[kCanNumberOfTxObjects] = 
{
  (0x769u) /* ID: 0x00000769, Handle: 0, BTM_DiagResp [BC] */, 
  (0x2A4u) /* ID: 0x000002a4, Handle: 1, MMI_Status_Info [BC] */, 
  (0x249u) /* ID: 0x00000249, Handle: 2, TTS_Status [BC] */, 
  (0x0FBu) /* ID: 0x000000fb, Handle: 3, MMI_TextMMData [BC] */, 
  (0x0F9u) /* ID: 0x000000f9, Handle: 4, MMI_TextBTData [BC] */, 
  (0x7FFu) /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */


/* -----------------------------------------------------------------------------
    &&&~ CanTxDLC
 ----------------------------------------------------------------------------- */

/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tCanDlc V_MEMROM2 CanTxDLC[kCanNumberOfTxObjects] = 
{
  MK_TX_DLC(8) /* ID: 0x00000769, Handle: 0, BTM_DiagResp [BC] */, 
  MK_TX_DLC(8) /* ID: 0x000002a4, Handle: 1, MMI_Status_Info [BC] */, 
  MK_TX_DLC(8) /* ID: 0x00000249, Handle: 2, TTS_Status [BC] */, 
  MK_TX_DLC(8) /* ID: 0x000000fb, Handle: 3, MMI_TextMMData [BC] */, 
  MK_TX_DLC(8) /* ID: 0x000000f9, Handle: 4, MMI_TextBTData [BC] */, 
  MK_TX_DLC(8) /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */



/* -----------------------------------------------------------------------------
    &&&~ CanTxMessageLength
 ----------------------------------------------------------------------------- */

#ifdef C_ENABLE_CAN_FD_FULL
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanTxMessageLength[kCanNumberOfTxObjects] = 
{
  8 /* ID: 0x00000769, Handle: 0, BTM_DiagResp [BC] */, 
  8 /* ID: 0x000002a4, Handle: 1, MMI_Status_Info [BC] */, 
  8 /* ID: 0x00000249, Handle: 2, TTS_Status [BC] */, 
  8 /* ID: 0x000000fb, Handle: 3, MMI_TextMMData [BC] */, 
  8 /* ID: 0x000000f9, Handle: 4, MMI_TextBTData [BC] */, 
  8 /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */

#endif




#ifdef C_ENABLE_COPY_TX_DATA
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 TxDataPtr V_MEMROM2 CanTxDataPtr[kCanNumberOfTxObjects] = 
{
  (TxDataPtr) BTM_DiagResp._c /* ID: 0x00000769, Handle: 0, BTM_DiagResp [BC] */, 
  (TxDataPtr) MMI_Status_Info._c /* ID: 0x000002a4, Handle: 1, MMI_Status_Info [BC] */, 
  (TxDataPtr) TTS_Status._c /* ID: 0x00000249, Handle: 2, TTS_Status [BC] */, 
  (TxDataPtr) MMI_TextMMData._c /* ID: 0x000000fb, Handle: 3, MMI_TextMMData [BC] */, 
  (TxDataPtr) MMI_TextBTData._c /* ID: 0x000000f9, Handle: 4, MMI_TextBTData [BC] */, 
  (TxDataPtr) TxDynamicMsg0._c /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_PRETRANSMIT_FCT
/* ROM CATEGORY 1 START */
/* PRQA  S 1334 QAC_Can_1334 */ /* MD_Can_1334 */
V_MEMROM0 V_MEMROM1 ApplPreTransmitFct V_MEMROM2 CanTxApplPreTransmitPtr[kCanNumberOfTxObjects] = 
{
  V_NULL /* ID: 0x00000769, Handle: 0, BTM_DiagResp [BC] */, 
  V_NULL /* ID: 0x000002a4, Handle: 1, MMI_Status_Info [BC] */, 
  V_NULL /* ID: 0x00000249, Handle: 2, TTS_Status [BC] */, 
  V_NULL /* ID: 0x000000fb, Handle: 3, MMI_TextMMData [BC] */, 
  V_NULL /* ID: 0x000000f9, Handle: 4, MMI_TextBTData [BC] */, 
  V_NULL /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};
/* PRQA  L:QAC_Can_1334 */

/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_CONFIRMATION_FCT
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 ApplConfirmationFct V_MEMROM2 CanTxApplConfirmationPtr[kCanNumberOfTxObjects] = 
{
  TxAckCbk_BTM_DiagResp /* ID: 0x00000769, Handle: 0, BTM_DiagResp [BC] */, 
  TxAckCbk_MMI_Status_Info /* ID: 0x000002a4, Handle: 1, MMI_Status_Info [BC] */, 
  TxAckCbk_TTS_Status /* ID: 0x00000249, Handle: 2, TTS_Status [BC] */, 
  TxAckCbk_MMI_TextMMData /* ID: 0x000000fb, Handle: 3, MMI_TextMMData [BC] */, 
  TxAckCbk_MMI_TextBTData /* ID: 0x000000f9, Handle: 4, MMI_TextBTData [BC] */, 
  TpDrvConfirmation /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_PART_OFFLINE
/* ROM CATEGORY 2 START */

V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanTxSendMask[kCanNumberOfTxObjects] = 
{
  (vuint8) C_SEND_GRP_NONE /* ID: 0x00000769, Handle: 0, BTM_DiagResp [BC] */, 
  (vuint8) C_SEND_GRP_NONE /* ID: 0x000002a4, Handle: 1, MMI_Status_Info [BC] */, 
  (vuint8) C_SEND_GRP_NONE /* ID: 0x00000249, Handle: 2, TTS_Status [BC] */, 
  (vuint8) C_SEND_GRP_NONE /* ID: 0x000000fb, Handle: 3, MMI_TextMMData [BC] */, 
  (vuint8) C_SEND_GRP_NONE /* ID: 0x000000f9, Handle: 4, MMI_TextBTData [BC] */, 
  (vuint8) C_SEND_GRP_NONE /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};

/* ROM CATEGORY 2 END */

#endif


#ifdef C_ENABLE_CONFIRMATION_FLAG
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanConfirmationOffset[kCanNumberOfTxObjects] = 
{
  0 /* ID: 0x00000769, Handle: 0, BTM_DiagResp [BC] */, 
  0 /* ID: 0x000002a4, Handle: 1, MMI_Status_Info [BC] */, 
  0 /* ID: 0x00000249, Handle: 2, TTS_Status [BC] */, 
  0 /* ID: 0x000000fb, Handle: 3, MMI_TextMMData [BC] */, 
  0 /* ID: 0x000000f9, Handle: 4, MMI_TextBTData [BC] */, 
  0 /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanConfirmationMask[kCanNumberOfTxObjects] = 
{
  0x01u /* ID: 0x00000769, Handle: 0, BTM_DiagResp [BC] */, 
  0x02u /* ID: 0x000002a4, Handle: 1, MMI_Status_Info [BC] */, 
  0x04u /* ID: 0x00000249, Handle: 2, TTS_Status [BC] */, 
  0x08u /* ID: 0x000000fb, Handle: 3, MMI_TextMMData [BC] */, 
  0x10u /* ID: 0x000000f9, Handle: 4, MMI_TextBTData [BC] */, 
  0x20u /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */


#endif




/* Id table depending on search algorithm */
/* Linear search */
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tCanRxId0 V_MEMROM2 CanRxId0[kCanNumberOfRxObjects] = 
{
  MK_STDID0(0x7DFu) /* ID: 0x000007df, Handle: 4, Func_DiagReq [BC] */, 
  MK_STDID0(0x761u) /* ID: 0x00000761, Handle: 5, BTM_DiagReq [BC] */, 
  MK_STDID0(0x610u) /* ID: 0x00000610, Handle: 0, PMS_VIN [BC] */, 
  MK_STDID0(0x3F1u) /* ID: 0x000003f1, Handle: 1, IPK_TotalOdometer [BC] */, 
  MK_STDID0(0x3E0u) /* ID: 0x000003e0, Handle: 2, TBOX_DateTime_Info [BC] */, 
  MK_STDID0(0x125u) /* ID: 0x00000125, Handle: 3, EHB_Status [BC] */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 CanReceiveHandle V_MEMROM2 CanRxMsgIndirection[kCanNumberOfRxObjects] = 
{
  4 /* ID: 0x000007df, Handle: 4, Func_DiagReq */, 
  5 /* ID: 0x00000761, Handle: 5, BTM_DiagReq */, 
  0 /* ID: 0x00000610, Handle: 0, PMS_VIN */, 
  1 /* ID: 0x000003f1, Handle: 1, IPK_TotalOdometer */, 
  2 /* ID: 0x000003e0, Handle: 2, TBOX_DateTime_Info */, 
  3 /* ID: 0x00000125, Handle: 3, EHB_Status */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanRxDataLen[kCanNumberOfRxObjects] = 
{
  8 /* ID: 0x00000610, Handle: 0, PMS_VIN [BC] */, 
  3 /* ID: 0x000003f1, Handle: 1, IPK_TotalOdometer [BC] */, 
  6 /* ID: 0x000003e0, Handle: 2, TBOX_DateTime_Info [BC] */, 
  3 /* ID: 0x00000125, Handle: 3, EHB_Status [BC] */, 
  8 /* ID: 0x000007df, Handle: 4, Func_DiagReq [BC] */, 
  8 /* ID: 0x00000761, Handle: 5, BTM_DiagReq [BC] */
};
/* ROM CATEGORY 1 END */


#ifdef C_ENABLE_COPY_RX_DATA
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 RxDataPtr V_MEMROM2 CanRxDataPtr[kCanNumberOfRxObjects] = 
{
  (RxDataPtr) PMS_VIN._c /* ID: 0x00000610, Handle: 0, PMS_VIN [BC] */, 
  (RxDataPtr) IPK_TotalOdometer._c /* ID: 0x000003f1, Handle: 1, IPK_TotalOdometer [BC] */, 
  (RxDataPtr) TBOX_DateTime_Info._c /* ID: 0x000003e0, Handle: 2, TBOX_DateTime_Info [BC] */, 
  (RxDataPtr) EHB_Status._c /* ID: 0x00000125, Handle: 3, EHB_Status [BC] */, 
  (RxDataPtr) Func_DiagReq._c /* ID: 0x000007df, Handle: 4, Func_DiagReq [BC] */, 
  (RxDataPtr) BTM_DiagReq._c /* ID: 0x00000761, Handle: 5, BTM_DiagReq [BC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_PRECOPY_FCT
/* CODE CATEGORY 1 START */
/* CODE CATEGORY 1 END */

/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 ApplPrecopyFct V_MEMROM2 CanRxApplPrecopyPtr[kCanNumberOfRxObjects] = 
{
  IlMsgPMS_VINPreCopy /* ID: 0x00000610, Handle: 0, PMS_VIN [BC] */, 
  IlMsgIPK_TotalOdometerPreCopy /* ID: 0x000003f1, Handle: 1, IPK_TotalOdometer [BC] */, 
  IlMsgTBOX_DateTime_InfoPreCopy /* ID: 0x000003e0, Handle: 2, TBOX_DateTime_Info [BC] */, 
  IlMsgEHB_StatusPreCopy /* ID: 0x00000125, Handle: 3, EHB_Status [BC] */, 
  TpPrecopyNormalDiagFunc /* ID: 0x000007df, Handle: 4, Func_DiagReq [BC] */, 
  TpPrecopyNormalDiagPhys /* ID: 0x00000761, Handle: 5, BTM_DiagReq [BC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_INDICATION_FCT
/* ROM CATEGORY 1 START */
/* PRQA  S 1334 QAC_Can_1334 */ /* MD_Can_1334 */
V_MEMROM0 V_MEMROM1 ApplIndicationFct V_MEMROM2 CanRxApplIndicationPtr[kCanNumberOfRxObjects] = 
{
  IlMsgPMS_VINInd /* ID: 0x00000610, Handle: 0, PMS_VIN [BC] */, 
  IlMsgIPK_TotalOdometerInd /* ID: 0x000003f1, Handle: 1, IPK_TotalOdometer [BC] */, 
  IlMsgTBOX_DateTime_InfoInd /* ID: 0x000003e0, Handle: 2, TBOX_DateTime_Info [BC] */, 
  IlMsgEHB_StatusInd /* ID: 0x00000125, Handle: 3, EHB_Status [BC] */, 
  V_NULL /* ID: 0x000007df, Handle: 4, Func_DiagReq [BC] */, 
  V_NULL /* ID: 0x00000761, Handle: 5, BTM_DiagReq [BC] */
};
/* PRQA  L:QAC_Can_1334 */

/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_INDICATION_FLAG
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanIndicationOffset[kCanNumberOfRxObjects] = 
{
  0 /* ID: 0x00000610, Handle: 0, PMS_VIN [BC] */, 
  0 /* ID: 0x000003f1, Handle: 1, IPK_TotalOdometer [BC] */, 
  0 /* ID: 0x000003e0, Handle: 2, TBOX_DateTime_Info [BC] */, 
  0 /* ID: 0x00000125, Handle: 3, EHB_Status [BC] */, 
  0 /* ID: 0x000007df, Handle: 4, Func_DiagReq [BC] */, 
  0 /* ID: 0x00000761, Handle: 5, BTM_DiagReq [BC] */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanIndicationMask[kCanNumberOfRxObjects] = 
{
  0x00u /* ID: 0x00000610, Handle: 0, PMS_VIN [BC] */, 
  0x00u /* ID: 0x000003f1, Handle: 1, IPK_TotalOdometer [BC] */, 
  0x00u /* ID: 0x000003e0, Handle: 2, TBOX_DateTime_Info [BC] */, 
  0x00u /* ID: 0x00000125, Handle: 3, EHB_Status [BC] */, 
  0x01u /* ID: 0x000007df, Handle: 4, Func_DiagReq [BC] */, 
  0x02u /* ID: 0x00000761, Handle: 5, BTM_DiagReq [BC] */
};
/* ROM CATEGORY 1 END */


#endif




/* -----------------------------------------------------------------------------
    &&&~ Init structures
 ----------------------------------------------------------------------------- */

/* ROM CATEGORY 4 START */
/* PRQA S 3408 1 */ /* MD_Can_3408_extLinkage */

/* ROM CATEGORY 4 END */

/* ROM CATEGORY 4 START */
V_MEMROM0 V_MEMROM1 tCanInitObject V_MEMROM2 CanInitObject[1] = 
{
  
  {
    (vuint32) 0x27DB0000u /* Control 1 register */
  }
};

V_MEMROM0 V_MEMROM1 tCanInitBasicCan V_MEMROM2 CanInitBasicCan[8] = 
{
  
  {
    (vuint32) 0x1FFFFFFFu /* Mask Register */, 
    (vuint32) 0x0003FFFFu /* Code Register */
  }, 
  
  {
    (vuint32) 0x1FFFFFFFu /* Mask Register */, 
    (vuint32) 0x0003FFFFu /* Code Register */
  }, 
  
  {
    (vuint32) 0x1FFFFFFFu /* Mask Register */, 
    (vuint32) 0x0003FFFFu /* Code Register */
  }, 
  
  {
    (vuint32) 0x1FFFFFFFu /* Mask Register */, 
    (vuint32) 0x0003FFFFu /* Code Register */
  }, 
  
  {
    (vuint32) 0x1FFFFFFFu /* Mask Register */, 
    (vuint32) 0x0003FFFFu /* Code Register */
  }, 
  
  {
    (vuint32) 0x1FFFFFFFu /* Mask Register */, 
    (vuint32) 0x0003FFFFu /* Code Register */
  }, 
  
  {
    (vuint32) 0x1FFFFFFFu /* Mask Register */, 
    (vuint32) 0x0003FFFFu /* Code Register */
  }, 
  
  {
    (vuint32) 0x1FFFFFFFu /* Mask Register */, 
    (vuint32) 0x0003FFFFu /* Code Register */
  }
};

V_MEMROM0 V_MEMROM1 vuint16 V_MEMROM2 CanInitBasicCanIndex[1] = 
{
  (vuint16) 0x0000u
};

/* ROM CATEGORY 4 END */



#if defined(C_ENABLE_MULTI_ECU_CONFIG)
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanPhysToLogChannel[kVNumberOfIdentities][kCanNumberOfPhysChannels] = 
{
  
  {
    0
  }
};
/* ROM CATEGORY 1 END */

#endif

#if defined(C_ENABLE_MULTI_ECU_CONFIG)
/* ROM CATEGORY 2 START */

V_MEMROM0 V_MEMROM1 tVIdentityMsk V_MEMROM2 CanChannelIdentityAssignment[kCanNumberOfChannels] = 
{
  0x01u
};

/* ROM CATEGORY 2 END */

#endif

#if defined(C_ENABLE_MULTI_ECU_PHYS)
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tVIdentityMsk V_MEMROM2 CanRxIdentityAssignment[kCanNumberOfRxObjects] = 
{
  0x01u /* ID: 0x00000610, Handle: 0, PMS_VIN [BC] */, 
  0x01u /* ID: 0x000003f1, Handle: 1, IPK_TotalOdometer [BC] */, 
  0x01u /* ID: 0x000003e0, Handle: 2, TBOX_DateTime_Info [BC] */, 
  0x01u /* ID: 0x00000125, Handle: 3, EHB_Status [BC] */, 
  0x01u /* ID: 0x000007df, Handle: 4, Func_DiagReq [BC] */, 
  0x01u /* ID: 0x00000761, Handle: 5, BTM_DiagReq [BC] */
};
/* ROM CATEGORY 1 END */

/* ROM CATEGORY 4 START */
V_MEMROM0 V_MEMROM1 tVIdentityMsk V_MEMROM2 CanTxIdentityAssignment[kCanNumberOfTxObjects] = 
{
  0x01u /* ID: 0x00000769, Handle: 0, BTM_DiagResp [BC] */, 
  0x01u /* ID: 0x000002a4, Handle: 1, MMI_Status_Info [BC] */, 
  0x01u /* ID: 0x00000249, Handle: 2, TTS_Status [BC] */, 
  0x01u /* ID: 0x000000fb, Handle: 3, MMI_TextMMData [BC] */, 
  0x01u /* ID: 0x000000f9, Handle: 4, MMI_TextBTData [BC] */, 
  0x01u /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 4 END */

#endif


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanRxMinDataLen[kCanNumberOfRxObjects] = 
{
  8 /* ID: 0x00000610, Handle: 0, PMS_VIN [BC] */, 
  3 /* ID: 0x000003f1, Handle: 1, IPK_TotalOdometer [BC] */, 
  6 /* ID: 0x000003e0, Handle: 2, TBOX_DateTime_Info [BC] */, 
  3 /* ID: 0x00000125, Handle: 3, EHB_Status [BC] */, 
  8 /* ID: 0x000007df, Handle: 4, Func_DiagReq [BC] */, 
  8 /* ID: 0x00000761, Handle: 5, BTM_DiagReq [BC] */
};
/* ROM CATEGORY 1 END */

#ifdef C_ENABLE_TX_FULLCAN_OBJECTS
/* ROM CATEGORY 2 START */
V_MEMROM0 V_MEMROM1 CanObjectHandle V_MEMROM2 CanTxMailbox[kCanNumberOfTxObjects] = 
{
  0x01u /* ID: 0x00000769, Handle: 0, BTM_DiagResp [BC] */, 
  0x01u /* ID: 0x000002a4, Handle: 1, MMI_Status_Info [BC] */, 
  0x01u /* ID: 0x00000249, Handle: 2, TTS_Status [BC] */, 
  0x01u /* ID: 0x000000fb, Handle: 3, MMI_TextMMData [BC] */, 
  0x01u /* ID: 0x000000f9, Handle: 4, MMI_TextBTData [BC] */, 
  0x01u /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 2 END */

#endif



/* -----------------------------------------------------------------------------
    &&&~ Can_Mailbox table
 ----------------------------------------------------------------------------- */

/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tCanMailbox V_MEMROM2 Can_Mailbox[kCanNumberOfMailboxes] = 
{
  { 0, 1 } /* MailboxHandle: 0, Channel: Channel0, RxBasicCan */, 
  { 8, 1 } /* MailboxHandle: 1, Channel: Channel0, TxNormal */
} /* HwObjHandle, HwObjCount */;
/* ROM CATEGORY 1 END */



/* -----------------------------------------------------------------------------
    &&&~ Can_HwObjToCanMailboxIndirectionTable
 ----------------------------------------------------------------------------- */

/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 CanObjectHandle V_MEMROM2 Can_HwObjToMailboxIndirection[kCanNumberOfHwObjToMailboxIndirections] = 
{
  0 /* Index: 0, Channel: Channel0, HwObjHandle: 0 */, 
  kCanMailboxNotUsed /* Index: 1, Channel: Channel0, HwObjHandle: 1 */, 
  kCanMailboxNotUsed /* Index: 2, Channel: Channel0, HwObjHandle: 2 */, 
  kCanMailboxNotUsed /* Index: 3, Channel: Channel0, HwObjHandle: 3 */, 
  kCanMailboxNotUsed /* Index: 4, Channel: Channel0, HwObjHandle: 4 */, 
  kCanMailboxNotUsed /* Index: 5, Channel: Channel0, HwObjHandle: 5 */, 
  kCanMailboxNotUsed /* Index: 6, Channel: Channel0, HwObjHandle: 6 */, 
  kCanMailboxNotUsed /* Index: 7, Channel: Channel0, HwObjHandle: 7 */, 
  1 /* Index: 8, Channel: Channel0, HwObjHandle: 8 */
} /* MailboxHandle */;
/* ROM CATEGORY 1 END */





