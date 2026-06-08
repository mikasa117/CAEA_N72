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

#define C_DRV_INTERNAL
#include "can_inc.h"
#include "can_par.h"
#include "v_inc.h"

/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tCanTxId0 V_MEMROM2 CanTxId0[kCanNumberOfTxObjects] = 
{
  MK_STDID0(0x6F9u) /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  MK_STDID0(0x6EEu) /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  MK_STDID0(0x402u) /* ID: 0x00000402, Handle: 2, NMm_VRHCU [BC] */, 
  MK_STDID0(0x3F3u) /* ID: 0x000003f3, Handle: 3, VRHCU_3F3 [BC] */, 
  MK_STDID0(0x3EEu) /* ID: 0x000003ee, Handle: 4, VRHCU_3EE [BC] */, 
  MK_STDID0(0x7FFu) /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */


/* -----------------------------------------------------------------------------
    &&&~ CanTxDLC
 ----------------------------------------------------------------------------- */

/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tCanDlc V_MEMROM2 CanTxDLC[kCanNumberOfTxObjects] = 
{
  MK_TX_DLC(8) /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  MK_TX_DLC(8) /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  MK_TX_DLC(8) /* ID: 0x00000402, Handle: 2, NMm_VRHCU [BC] */, 
  MK_TX_DLC(8) /* ID: 0x000003f3, Handle: 3, VRHCU_3F3 [BC] */, 
  MK_TX_DLC(8) /* ID: 0x000003ee, Handle: 4, VRHCU_3EE [BC] */, 
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
  8 /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  8 /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  8 /* ID: 0x00000402, Handle: 2, NMm_VRHCU [BC] */, 
  8 /* ID: 0x000003f3, Handle: 3, VRHCU_3F3 [BC] */, 
  8 /* ID: 0x000003ee, Handle: 4, VRHCU_3EE [BC] */, 
  8 /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */

#endif




#ifdef C_ENABLE_COPY_TX_DATA
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 TxDataPtr V_MEMROM2 CanTxDataPtr[kCanNumberOfTxObjects] = 
{
  (TxDataPtr) VRHCU_6F9._c /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  (TxDataPtr) VRHCU_6EE._c /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  (TxDataPtr) NMm_VRHCU._c /* ID: 0x00000402, Handle: 2, NMm_VRHCU [BC] */, 
  (TxDataPtr) VRHCU_3F3._c /* ID: 0x000003f3, Handle: 3, VRHCU_3F3 [BC] */, 
  (TxDataPtr) VRHCU_3EE._c /* ID: 0x000003ee, Handle: 4, VRHCU_3EE [BC] */, 
  (TxDataPtr) TxDynamicMsg0._c /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_PRETRANSMIT_FCT
/* ROM CATEGORY 1 START */
/* PRQA  S 1334 QAC_Can_1334 */ /* MD_Can_1334 */
V_MEMROM0 V_MEMROM1 ApplPreTransmitFct V_MEMROM2 CanTxApplPreTransmitPtr[kCanNumberOfTxObjects] = 
{
  Pretransmit_VRHCU_6F9 /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  Pretransmit_VRHCU_6EE /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  Pretransmit_NmMsg /* ID: 0x00000402, Handle: 2, NMm_VRHCU [BC] */, 
  Pretransmit_VRHCU_3F3 /* ID: 0x000003f3, Handle: 3, VRHCU_3F3 [BC] */, 
  Pretransmit_VRHCU_3EE /* ID: 0x000003ee, Handle: 4, VRHCU_3EE [BC] */, 
  V_NULL /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};
/* PRQA  L:QAC_Can_1334 */

/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_CONFIRMATION_FCT
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 ApplConfirmationFct V_MEMROM2 CanTxApplConfirmationPtr[kCanNumberOfTxObjects] = 
{
  TxAckCbk_VRHCU_6F9 /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  TxAckCbk_VRHCU_6EE /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  CanNm_NmMsgConfirmation /* ID: 0x00000402, Handle: 2, NMm_VRHCU [BC] */, 
  TxAckCbk_VRHCU_3F3 /* ID: 0x000003f3, Handle: 3, VRHCU_3F3 [BC] */, 
  TxAckCbk_VRHCU_3EE /* ID: 0x000003ee, Handle: 4, VRHCU_3EE [BC] */, 
  TpDrvConfirmation /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_PART_OFFLINE
/* ROM CATEGORY 2 START */

V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanTxSendMask[kCanNumberOfTxObjects] = 
{
  (vuint8) C_SEND_GRP_IL /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  (vuint8) C_SEND_GRP_IL /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  (vuint8) C_SEND_GRP_NM /* ID: 0x00000402, Handle: 2, NMm_VRHCU [BC] */, 
  (vuint8) C_SEND_GRP_IL /* ID: 0x000003f3, Handle: 3, VRHCU_3F3 [BC] */, 
  (vuint8) C_SEND_GRP_IL /* ID: 0x000003ee, Handle: 4, VRHCU_3EE [BC] */, 
  (vuint8) C_SEND_GRP_NONE /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};

/* ROM CATEGORY 2 END */

#endif


#ifdef C_ENABLE_CONFIRMATION_FLAG
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanConfirmationOffset[kCanNumberOfTxObjects] = 
{
  0 /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  0 /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  0 /* ID: 0x00000402, Handle: 2, NMm_VRHCU [BC] */, 
  0 /* ID: 0x000003f3, Handle: 3, VRHCU_3F3 [BC] */, 
  0 /* ID: 0x000003ee, Handle: 4, VRHCU_3EE [BC] */, 
  0 /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanConfirmationMask[kCanNumberOfTxObjects] = 
{
  0x01u /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  0x02u /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  0x00u /* ID: 0x00000402, Handle: 2, NMm_VRHCU [BC] */, 
  0x04u /* ID: 0x000003f3, Handle: 3, VRHCU_3F3 [BC] */, 
  0x08u /* ID: 0x000003ee, Handle: 4, VRHCU_3EE [BC] */, 
  0x10u /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */


#endif




/* Id table depending on search algorithm */
/* Linear search */
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tCanRxId0 V_MEMROM2 CanRxId0[kCanNumberOfRxObjects] = 
{
  MK_STDID0(0x7DFu) /* ID: 0x000007df, Handle: 8, VIU_FR_7DF [FC] */, 
  MK_STDID0(0x777u) /* ID: 0x00000777, Handle: 9, VIU_FR_777 [FC] */, 
  MK_STDID0(0x3EDu) /* ID: 0x000003ed, Handle: 0, VIU_FR_3ED [FC] */, 
  MK_STDID0(0x3D3u) /* ID: 0x000003d3, Handle: 1, VIU_FR_3D3 [FC] */, 
  MK_STDID0(0x3D1u) /* ID: 0x000003d1, Handle: 2, VIU_FR_3D1 [FC] */, 
  MK_STDID0(0x2F7u) /* ID: 0x000002f7, Handle: 3, VIU_FR_2F7 [FC] */, 
  MK_STDID0(0x2EFu) /* ID: 0x000002ef, Handle: 4, VIU_FR_2EF [FC] */, 
  MK_STDID0(0x2ECu) /* ID: 0x000002ec, Handle: 5, VIU_FR_2EC [FC] */, 
  MK_STDID0(0x288u) /* ID: 0x00000288, Handle: 6, VIU_FR_288 [FC] */, 
  MK_STDID0(0x1C3u) /* ID: 0x000001c3, Handle: 7, VIU_FR_1C3 [FC] */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 CanReceiveHandle V_MEMROM2 CanRxMsgIndirection[kCanNumberOfRxObjects] = 
{
  8 /* ID: 0x000007df, Handle: 8, VIU_FR_7DF */, 
  9 /* ID: 0x00000777, Handle: 9, VIU_FR_777 */, 
  0 /* ID: 0x000003ed, Handle: 0, VIU_FR_3ED */, 
  1 /* ID: 0x000003d3, Handle: 1, VIU_FR_3D3 */, 
  2 /* ID: 0x000003d1, Handle: 2, VIU_FR_3D1 */, 
  3 /* ID: 0x000002f7, Handle: 3, VIU_FR_2F7 */, 
  4 /* ID: 0x000002ef, Handle: 4, VIU_FR_2EF */, 
  5 /* ID: 0x000002ec, Handle: 5, VIU_FR_2EC */, 
  6 /* ID: 0x00000288, Handle: 6, VIU_FR_288 */, 
  7 /* ID: 0x000001c3, Handle: 7, VIU_FR_1C3 */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanRxDataLen[kCanNumberOfRxObjects] = 
{
  7 /* ID: 0x000003ed, Handle: 0, VIU_FR_3ED [FC] */, 
  6 /* ID: 0x000003d3, Handle: 1, VIU_FR_3D3 [FC] */, 
  1 /* ID: 0x000003d1, Handle: 2, VIU_FR_3D1 [FC] */, 
  6 /* ID: 0x000002f7, Handle: 3, VIU_FR_2F7 [FC] */, 
  4 /* ID: 0x000002ef, Handle: 4, VIU_FR_2EF [FC] */, 
  1 /* ID: 0x000002ec, Handle: 5, VIU_FR_2EC [FC] */, 
  6 /* ID: 0x00000288, Handle: 6, VIU_FR_288 [FC] */, 
  6 /* ID: 0x000001c3, Handle: 7, VIU_FR_1C3 [FC] */, 
  0 /* ID: 0x000007df, Handle: 8, VIU_FR_7DF [FC] */, 
  0 /* ID: 0x00000777, Handle: 9, VIU_FR_777 [FC] */
};
/* ROM CATEGORY 1 END */


#ifdef C_ENABLE_COPY_RX_DATA
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 RxDataPtr V_MEMROM2 CanRxDataPtr[kCanNumberOfRxObjects] = 
{
  (RxDataPtr) VIU_FR_3ED._c /* ID: 0x000003ed, Handle: 0, VIU_FR_3ED [FC] */, 
  (RxDataPtr) VIU_FR_3D3._c /* ID: 0x000003d3, Handle: 1, VIU_FR_3D3 [FC] */, 
  (RxDataPtr) VIU_FR_3D1._c /* ID: 0x000003d1, Handle: 2, VIU_FR_3D1 [FC] */, 
  (RxDataPtr) VIU_FR_2F7._c /* ID: 0x000002f7, Handle: 3, VIU_FR_2F7 [FC] */, 
  (RxDataPtr) VIU_FR_2EF._c /* ID: 0x000002ef, Handle: 4, VIU_FR_2EF [FC] */, 
  (RxDataPtr) VIU_FR_2EC._c /* ID: 0x000002ec, Handle: 5, VIU_FR_2EC [FC] */, 
  (RxDataPtr) VIU_FR_288._c /* ID: 0x00000288, Handle: 6, VIU_FR_288 [FC] */, 
  (RxDataPtr) VIU_FR_1C3._c /* ID: 0x000001c3, Handle: 7, VIU_FR_1C3 [FC] */, 
  (RxDataPtr) 0 /* ID: 0x000007df, Handle: 8, VIU_FR_7DF [FC] */, 
  (RxDataPtr) 0 /* ID: 0x00000777, Handle: 9, VIU_FR_777 [FC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_PRECOPY_FCT
/* CODE CATEGORY 1 START */
/* CODE CATEGORY 1 END */

/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 ApplPrecopyFct V_MEMROM2 CanRxApplPrecopyPtr[kCanNumberOfRxObjects] = 
{
  IlMsgVIU_FR_3EDPreCopy /* ID: 0x000003ed, Handle: 0, VIU_FR_3ED [FC] */, 
  IlMsgVIU_FR_3D3PreCopy /* ID: 0x000003d3, Handle: 1, VIU_FR_3D3 [FC] */, 
  IlMsgVIU_FR_3D1PreCopy /* ID: 0x000003d1, Handle: 2, VIU_FR_3D1 [FC] */, 
  IlMsgVIU_FR_2F7PreCopy /* ID: 0x000002f7, Handle: 3, VIU_FR_2F7 [FC] */, 
  IlMsgVIU_FR_2EFPreCopy /* ID: 0x000002ef, Handle: 4, VIU_FR_2EF [FC] */, 
  IlMsgVIU_FR_2ECPreCopy /* ID: 0x000002ec, Handle: 5, VIU_FR_2EC [FC] */, 
  IlMsgVIU_FR_288PreCopy /* ID: 0x00000288, Handle: 6, VIU_FR_288 [FC] */, 
  IlMsgVIU_FR_1C3PreCopy /* ID: 0x000001c3, Handle: 7, VIU_FR_1C3 [FC] */, 
  TpPrecopyNormalDiagFunc /* ID: 0x000007df, Handle: 8, VIU_FR_7DF [FC] */, 
  TpPrecopyNormalDiagPhys /* ID: 0x00000777, Handle: 9, VIU_FR_777 [FC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_INDICATION_FCT
/* ROM CATEGORY 1 START */
/* PRQA  S 1334 QAC_Can_1334 */ /* MD_Can_1334 */
V_MEMROM0 V_MEMROM1 ApplIndicationFct V_MEMROM2 CanRxApplIndicationPtr[kCanNumberOfRxObjects] = 
{
  IlMsgVIU_FR_3EDInd /* ID: 0x000003ed, Handle: 0, VIU_FR_3ED [FC] */, 
  IlMsgVIU_FR_3D3Ind /* ID: 0x000003d3, Handle: 1, VIU_FR_3D3 [FC] */, 
  IlMsgVIU_FR_3D1Ind /* ID: 0x000003d1, Handle: 2, VIU_FR_3D1 [FC] */, 
  IlMsgVIU_FR_2F7Ind /* ID: 0x000002f7, Handle: 3, VIU_FR_2F7 [FC] */, 
  IlMsgVIU_FR_2EFInd /* ID: 0x000002ef, Handle: 4, VIU_FR_2EF [FC] */, 
  IlMsgVIU_FR_2ECInd /* ID: 0x000002ec, Handle: 5, VIU_FR_2EC [FC] */, 
  IlMsgVIU_FR_288Ind /* ID: 0x00000288, Handle: 6, VIU_FR_288 [FC] */, 
  IlMsgVIU_FR_1C3Ind /* ID: 0x000001c3, Handle: 7, VIU_FR_1C3 [FC] */, 
  V_NULL /* ID: 0x000007df, Handle: 8, VIU_FR_7DF [FC] */, 
  V_NULL /* ID: 0x00000777, Handle: 9, VIU_FR_777 [FC] */
};
/* PRQA  L:QAC_Can_1334 */

/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_INDICATION_FLAG
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanIndicationOffset[kCanNumberOfRxObjects] = 
{
  0 /* ID: 0x000003ed, Handle: 0, VIU_FR_3ED [FC] */, 
  0 /* ID: 0x000003d3, Handle: 1, VIU_FR_3D3 [FC] */, 
  0 /* ID: 0x000003d1, Handle: 2, VIU_FR_3D1 [FC] */, 
  0 /* ID: 0x000002f7, Handle: 3, VIU_FR_2F7 [FC] */, 
  0 /* ID: 0x000002ef, Handle: 4, VIU_FR_2EF [FC] */, 
  0 /* ID: 0x000002ec, Handle: 5, VIU_FR_2EC [FC] */, 
  0 /* ID: 0x00000288, Handle: 6, VIU_FR_288 [FC] */, 
  0 /* ID: 0x000001c3, Handle: 7, VIU_FR_1C3 [FC] */, 
  0 /* ID: 0x000007df, Handle: 8, VIU_FR_7DF [FC] */, 
  0 /* ID: 0x00000777, Handle: 9, VIU_FR_777 [FC] */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanIndicationMask[kCanNumberOfRxObjects] = 
{
  0x00u /* ID: 0x000003ed, Handle: 0, VIU_FR_3ED [FC] */, 
  0x00u /* ID: 0x000003d3, Handle: 1, VIU_FR_3D3 [FC] */, 
  0x00u /* ID: 0x000003d1, Handle: 2, VIU_FR_3D1 [FC] */, 
  0x00u /* ID: 0x000002f7, Handle: 3, VIU_FR_2F7 [FC] */, 
  0x00u /* ID: 0x000002ef, Handle: 4, VIU_FR_2EF [FC] */, 
  0x00u /* ID: 0x000002ec, Handle: 5, VIU_FR_2EC [FC] */, 
  0x00u /* ID: 0x00000288, Handle: 6, VIU_FR_288 [FC] */, 
  0x00u /* ID: 0x000001c3, Handle: 7, VIU_FR_1C3 [FC] */, 
  0x00u /* ID: 0x000007df, Handle: 8, VIU_FR_7DF [FC] */, 
  0x00u /* ID: 0x00000777, Handle: 9, VIU_FR_777 [FC] */
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
    (vuint32) 0x02BA0003u /* Control 1 register */
  }
};

V_MEMROM0 V_MEMROM1 tCanInitBasicCan V_MEMROM2 CanInitBasicCan[8] = 
{
  
  {
    (vuint32) 0x1FFFFFFFu /* Mask Register */, 
    (vuint32) 0x0003FFFFu /* Code Register */
  }, 
  
  {
    (vuint32) 0x1C03FFFFu /* Mask Register */, 
    (vuint32) 0x1003FFFFu /* Code Register */
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
  0x01u /* ID: 0x000003ed, Handle: 0, VIU_FR_3ED [FC] */, 
  0x01u /* ID: 0x000003d3, Handle: 1, VIU_FR_3D3 [FC] */, 
  0x01u /* ID: 0x000003d1, Handle: 2, VIU_FR_3D1 [FC] */, 
  0x01u /* ID: 0x000002f7, Handle: 3, VIU_FR_2F7 [FC] */, 
  0x01u /* ID: 0x000002ef, Handle: 4, VIU_FR_2EF [FC] */, 
  0x01u /* ID: 0x000002ec, Handle: 5, VIU_FR_2EC [FC] */, 
  0x01u /* ID: 0x00000288, Handle: 6, VIU_FR_288 [FC] */, 
  0x01u /* ID: 0x000001c3, Handle: 7, VIU_FR_1C3 [FC] */, 
  0x01u /* ID: 0x000007df, Handle: 8, VIU_FR_7DF [FC] */, 
  0x01u /* ID: 0x00000777, Handle: 9, VIU_FR_777 [FC] */
};
/* ROM CATEGORY 1 END */

/* ROM CATEGORY 4 START */
V_MEMROM0 V_MEMROM1 tVIdentityMsk V_MEMROM2 CanTxIdentityAssignment[kCanNumberOfTxObjects] = 
{
  0x01u /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  0x01u /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  0x01u /* ID: 0x00000402, Handle: 2, NMm_VRHCU [BC] */, 
  0x01u /* ID: 0x000003f3, Handle: 3, VRHCU_3F3 [BC] */, 
  0x01u /* ID: 0x000003ee, Handle: 4, VRHCU_3EE [BC] */, 
  0x01u /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 4 END */

#endif


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanRxMinDataLen[kCanNumberOfRxObjects] = 
{
  7 /* ID: 0x000003ed, Handle: 0, VIU_FR_3ED [FC] */, 
  6 /* ID: 0x000003d3, Handle: 1, VIU_FR_3D3 [FC] */, 
  1 /* ID: 0x000003d1, Handle: 2, VIU_FR_3D1 [FC] */, 
  6 /* ID: 0x000002f7, Handle: 3, VIU_FR_2F7 [FC] */, 
  4 /* ID: 0x000002ef, Handle: 4, VIU_FR_2EF [FC] */, 
  1 /* ID: 0x000002ec, Handle: 5, VIU_FR_2EC [FC] */, 
  6 /* ID: 0x00000288, Handle: 6, VIU_FR_288 [FC] */, 
  6 /* ID: 0x000001c3, Handle: 7, VIU_FR_1C3 [FC] */, 
  0 /* ID: 0x000007df, Handle: 8, VIU_FR_7DF [FC] */, 
  0 /* ID: 0x00000777, Handle: 9, VIU_FR_777 [FC] */
};
/* ROM CATEGORY 1 END */

#ifdef C_ENABLE_TX_FULLCAN_OBJECTS
/* ROM CATEGORY 2 START */
V_MEMROM0 V_MEMROM1 CanObjectHandle V_MEMROM2 CanTxMailbox[kCanNumberOfTxObjects] = 
{
  0x0Bu /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  0x0Bu /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  0x0Bu /* ID: 0x00000402, Handle: 2, NMm_VRHCU [BC] */, 
  0x0Bu /* ID: 0x000003f3, Handle: 3, VRHCU_3F3 [BC] */, 
  0x0Bu /* ID: 0x000003ee, Handle: 4, VRHCU_3EE [BC] */, 
  0x0Bu /* ID: 0x000007ff, Handle: 5, TxDynamicMsg0 [BC] */
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
  { 8, 1 } /* MailboxHandle: 1, Channel: Channel0, VIU_FR_7DF */, 
  { 9, 1 } /* MailboxHandle: 2, Channel: Channel0, VIU_FR_777 */, 
  { 10, 1 } /* MailboxHandle: 3, Channel: Channel0, VIU_FR_3ED */, 
  { 11, 1 } /* MailboxHandle: 4, Channel: Channel0, VIU_FR_3D3 */, 
  { 12, 1 } /* MailboxHandle: 5, Channel: Channel0, VIU_FR_3D1 */, 
  { 13, 1 } /* MailboxHandle: 6, Channel: Channel0, VIU_FR_2F7 */, 
  { 14, 1 } /* MailboxHandle: 7, Channel: Channel0, VIU_FR_2EF */, 
  { 15, 1 } /* MailboxHandle: 8, Channel: Channel0, VIU_FR_2EC */, 
  { 16, 1 } /* MailboxHandle: 9, Channel: Channel0, VIU_FR_288 */, 
  { 17, 1 } /* MailboxHandle: 10, Channel: Channel0, VIU_FR_1C3 */, 
  { 18, 1 } /* MailboxHandle: 11, Channel: Channel0, TxNormal */
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
  1 /* Index: 8, Channel: Channel0, HwObjHandle: 8 */, 
  2 /* Index: 9, Channel: Channel0, HwObjHandle: 9 */, 
  3 /* Index: 10, Channel: Channel0, HwObjHandle: 10 */, 
  4 /* Index: 11, Channel: Channel0, HwObjHandle: 11 */, 
  5 /* Index: 12, Channel: Channel0, HwObjHandle: 12 */, 
  6 /* Index: 13, Channel: Channel0, HwObjHandle: 13 */, 
  7 /* Index: 14, Channel: Channel0, HwObjHandle: 14 */, 
  8 /* Index: 15, Channel: Channel0, HwObjHandle: 15 */, 
  9 /* Index: 16, Channel: Channel0, HwObjHandle: 16 */, 
  10 /* Index: 17, Channel: Channel0, HwObjHandle: 17 */, 
  11 /* Index: 18, Channel: Channel0, HwObjHandle: 18 */
} /* MailboxHandle */;
/* ROM CATEGORY 1 END */





