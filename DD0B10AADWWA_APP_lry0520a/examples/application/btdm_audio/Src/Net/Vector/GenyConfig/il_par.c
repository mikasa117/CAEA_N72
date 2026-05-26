/* -----------------------------------------------------------------------------
  Filename:    il_par.c
  Description: Toolversion: 02.03.18.01.80.01.04.01.00.00
               
               Serial Number: CBD1800104
               Customer Info: Wenzhou Changjiang Automobile Electronic System Co.,Ltd.?CAEA)
                              Package: CBD_Vector_SLP2
                              Micro: FS32K146
                              Compiler: GNU 9.2.0
               
               
               Generator Fwk   : GENy 
               Generator Module: Il_Vector
               
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

/* -----------------------------------------------------------------------------
    &&&~ Misra  justifications
 ----------------------------------------------------------------------------- */

/* PRQA S 3458 EOF *//* MD_CBD_19.4 */
/* PRQA S 3408 EOF *//* MD_Il_8.8 */
/* PRQA S 3460 EOF *//* MD_CBD_19.4 */
/* PRQA S 3412 EOF *//* MD_CBD_19.4 */
/* PRQA S 3453 EOF *//* MD_CBD_19.7 */
/* PRQA S 2006 EOF *//* MD_CBD_14.7 */
/* PRQA S 0777 EOF *//* MD_Il_0777 */
/* PRQA S 0778 EOF *//* MD_Il_0778 */
/* PRQA S 0779 EOF *//* MD_Il_0779 */
/* PRQA S 3673 EOF *//* MD_Il_3673 */
/* PRQA S 0310 EOF *//* MD_Il_0310 */
/* PRQA S 0312 EOF *//* MD_Il_0312 */
/* PRQA S 0635 EOF *//* MD_Il_0635 */
/* PRQA S 0781 EOF *//* MD_Il_0781 */
/* PRQA S 3410 EOF *//* MD_Il_3410 */
/* PRQA S 1330 EOF *//* MD_Il_1330 */
/* PRQA S 0342 EOF *//* MD_Il_0342 */
/* PRQA S 0857 EOF *//* MD_CBD_1.1 */
/* PRQA S 3109 EOF *//* MD_CBD_14.3 */
/* PRQA S 0883 EOF *//* */


#include "il_inc.h"

/* -----------------------------------------------------------------------------
    &&&~ local variables
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_CYCLIC_EVENT)
#endif



/* -----------------------------------------------------------------------------
    &&&~ Local function prototypes
 ----------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
    &&&~ IL internal rx message timeout indication functions
 ----------------------------------------------------------------------------- */

static void IlMsgPMS_VINTimeoutIndication(void);
static void IlMsgIPK_TotalOdometerTimeoutIndication(void);
static void IlMsgTBOX_DateTime_InfoTimeoutIndication(void);
static void IlMsgEHB_StatusTimeoutIndication(void);




/* -----------------------------------------------------------------------------
    &&&~ Internal Timer Handles
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
#define IlParHndRxPMS_VIN                    0
#define IlParHndRxIPK_TotalOdometer          1
#define IlParHndRxTBOX_DateTime_Info         2
#define IlParHndRxEHB_Status                 3
#endif



#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT)
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 IlTxTimeoutIndirection[kIlNumberOfTxObjects] = 
{
  kIlNoTxToutIndirection /* ID: 0x000002a4, Handle: 0, MMI_Status_Info [BC] */, 
  kIlNoTxToutIndirection /* ID: 0x00000249, Handle: 1, TTS_Status [BC] */, 
  kIlNoTxToutIndirection /* ID: 0x000000fb, Handle: 2, MMI_TextMMData [BC] */, 
  kIlNoTxToutIndirection /* ID: 0x000000f9, Handle: 3, MMI_TextBTData [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_FAST_ON_START)
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxFastOnStartDuration[kIlNumberOfTxObjects] = 
{
  kIlNoFastOnStartDuration /* ID: 0x000002a4, Handle: 0, MMI_Status_Info [BC] */, 
  kIlNoFastOnStartDuration /* ID: 0x00000249, Handle: 1, TTS_Status [BC] */, 
  kIlNoFastOnStartDuration /* ID: 0x000000fb, Handle: 2, MMI_TextMMData [BC] */, 
  kIlNoFastOnStartDuration /* ID: 0x000000f9, Handle: 3, MMI_TextBTData [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_FAST_ON_START) && defined(IL_ENABLE_TX_MODE_SIGNALS)
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxFastOnStartMuxDelay[kIlNumberOfTxObjects] = 
{
  0 /* ID: 0x000002a4, Handle: 0, MMI_Status_Info [BC] */, 
  0 /* ID: 0x00000249, Handle: 1, TTS_Status [BC] */, 
  0 /* ID: 0x000000fb, Handle: 2, MMI_TextMMData [BC] */, 
  0 /* ID: 0x000000f9, Handle: 3, MMI_TextBTData [BC] */
};
#endif


#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxStartCycles[kIlNumberOfTxObjects] = 
{
  kIlNoCycleTime /* ID: 0x000002a4, Handle: 0, MMI_Status_Info [BC] */, 
  kIlNoCycleTime /* ID: 0x00000249, Handle: 1, TTS_Status [BC] */, 
  kIlNoCycleTime /* ID: 0x000000fb, Handle: 2, MMI_TextMMData [BC] */, 
  kIlNoCycleTime /* ID: 0x000000f9, Handle: 3, MMI_TextBTData [BC] */
};
#endif


#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 IltTxUpdateCounter V_MEMROM2 IlTxUpdateCycles[kIlNumberOfTxObjects] = 
{
  kIlNoDelayTime /* ID: 0x000002a4, Handle: 0, MMI_Status_Info [BC] */, 
  kIlNoDelayTime /* ID: 0x00000249, Handle: 1, TTS_Status [BC] */, 
  kIlNoDelayTime /* ID: 0x000000fb, Handle: 2, MMI_TextMMData [BC] */, 
  kIlNoDelayTime /* ID: 0x000000f9, Handle: 3, MMI_TextBTData [BC] */
};
#endif


#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxCyclicCycles[kIlNumberOfTxObjects] = 
{
  20 /* ID: 0x000002a4, Handle: 0, MMI_Status_Info [BC] */, 
  20 /* ID: 0x00000249, Handle: 1, TTS_Status [BC] */, 
  4 /* ID: 0x000000fb, Handle: 2, MMI_TextMMData [BC] */, 
  4 /* ID: 0x000000f9, Handle: 3, MMI_TextBTData [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && (defined(IL_ENABLE_TX_CYCLIC_EVENT) || defined(IL_ENABLE_TX_SECURE_EVENT) || defined(IL_ENABLE_TX_FAST_ON_START))
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxEventCycles[kIlNumberOfTxObjects] = 
{
  kIlNoCycleTimeFast /* ID: 0x000002a4, Handle: 0, MMI_Status_Info [BC] */, 
  kIlNoCycleTimeFast /* ID: 0x00000249, Handle: 1, TTS_Status [BC] */, 
  kIlNoCycleTimeFast /* ID: 0x000000fb, Handle: 2, MMI_TextMMData [BC] */, 
  kIlNoCycleTimeFast /* ID: 0x000000f9, Handle: 3, MMI_TextBTData [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_POLLING)
V_MEMROM0 V_MEMROM1 IlConfirmationFct V_MEMROM2 IlTxConfirmationFctPtr[kIlNumberOfTxObjects] = 
{
  V_NULL /* ID: 0x000002a4, Handle: 0, MMI_Status_Info [BC] */, 
  V_NULL /* ID: 0x00000249, Handle: 1, TTS_Status [BC] */, 
  V_NULL /* ID: 0x000000fb, Handle: 2, MMI_TextMMData [BC] */, 
  V_NULL /* ID: 0x000000f9, Handle: 3, MMI_TextBTData [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT) && defined(C_MULTIPLE_RECEIVE_CHANNEL) && defined(IL_ENABLE_TX_VARYING_TIMEOUT) && (kIlNumberOfChannels > 1)
V_MEMROM0 V_MEMROM1 IltTxTimeoutCounter V_MEMROM2 IlTxTimeout[kIlNumberOfChannels] = 
{
  2
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_SECURE_EVENT) && defined(IL_ENABLE_TX_VARYING_REPETITION) && (kIlNumberOfTxObjects > 1)
V_MEMROM0 V_MEMROM1 IltTxRepetitionCounter V_MEMROM2 IlTxRepetitionCounters[kIlNumberOfTxObjects] = 
{
  0 /* ID: 0x000002a4, Handle: 0, MMI_Status_Info [BC] */, 
  0 /* ID: 0x00000249, Handle: 1, TTS_Status [BC] */, 
  0 /* ID: 0x000000fb, Handle: 2, MMI_TextMMData [BC] */, 
  0 /* ID: 0x000000f9, Handle: 3, MMI_TextBTData [BC] */
};
#endif


/* -----------------------------------------------------------------------------
    &&&~ Rx Timeout Table
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
V_MEMROM0 V_MEMROM1 IltRxTimeoutCounter V_MEMROM2 IlRxTimeoutTbl[kIlNumberOfRxTimeoutCounters] = 
{
  500 /* ID: 0x00000610, PMS_VIN [BC] */, 
  500 /* ID: 0x000003f1, IPK_TotalOdometer [BC] */, 
  500 /* ID: 0x000003e0, TBOX_DateTime_Info [BC] */, 
  25 /* ID: 0x00000125, EHB_Status [BC] */
};
#endif




#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
V_MEMROM0 V_MEMROM1 IlTimeoutIndicationFct V_MEMROM2 IlRxTimeoutFctPtr[kIlNumberOfRxTimeoutCounters] = 
{
  IlMsgPMS_VINTimeoutIndication /* ID: 0x00000610, PMS_VIN [BC] */, 
  IlMsgIPK_TotalOdometerTimeoutIndication /* ID: 0x000003f1, IPK_TotalOdometer [BC] */, 
  IlMsgTBOX_DateTime_InfoTimeoutIndication /* ID: 0x000003e0, TBOX_DateTime_Info [BC] */, 
  IlMsgEHB_StatusTimeoutIndication /* ID: 0x00000125, EHB_Status [BC] */
};
#endif


#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_POLLING)
V_MEMROM0 V_MEMROM1 IlIndicationFct V_MEMROM2 IlCanRxIndicationFctPtr[kIlCanNumberOfRxObjects] = 
{
  V_NULL /* ID: 0x00000610, Handle: 0, PMS_VIN [BC] */, 
  V_NULL /* ID: 0x000003f1, Handle: 1, IPK_TotalOdometer [BC] */, 
  V_NULL /* ID: 0x000003e0, Handle: 2, TBOX_DateTime_Info [BC] */, 
  V_NULL /* ID: 0x00000125, Handle: 3, EHB_Status [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_DEFAULTVALUE)
V_MEMROM0 IL_MEMROM1 vuint8 IL_MEMROM2 IL_MEMROM3 *V_MEMROM1 V_MEMROM2  IlTxDefaultInitValue[kIlNumberOfTxObjects] =
{
  V_NULL,
  V_NULL,
  V_NULL,
  V_NULL
};
#endif



/* -----------------------------------------------------------------------------
    &&&~ RxDefaultInitValue
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_DEFAULTVALUE)
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 V_MEMROM3* V_MEMROM1 V_MEMROM2 IlRxDefaultInitValue[kIlNumberOfRxObjects] = 
{
  V_NULL, 
  V_NULL, 
  V_NULL, 
  V_NULL
};
#endif

/* -----------------------------------------------------------------------------
    &&&~ Implementation of Precopy Functions
 ----------------------------------------------------------------------------- */

#ifdef IL_ENABLE_RX
vuint8 IlMsgPMS_VINPreCopy(CanRxInfoStructPtr rxStruct)
{
  rxStruct = rxStruct;
  IlEnterCriticalFlagAccess();
  ilRxTimerFlags[0] |= (vuint8) 0x01;
  IlLeaveCriticalFlagAccess();
  return kCanCopyData;
}


#endif

#ifdef IL_ENABLE_RX
vuint8 IlMsgIPK_TotalOdometerPreCopy(CanRxInfoStructPtr rxStruct)
{
  rxStruct = rxStruct;
  IlEnterCriticalFlagAccess();
  ilRxTimerFlags[0] |= (vuint8) 0x02;
  IlLeaveCriticalFlagAccess();
  return kCanCopyData;
}


#endif

#ifdef IL_ENABLE_RX
vuint8 IlMsgTBOX_DateTime_InfoPreCopy(CanRxInfoStructPtr rxStruct)
{
  rxStruct = rxStruct;
  IlEnterCriticalFlagAccess();
  ilRxTimerFlags[0] |= (vuint8) 0x04;
  IlLeaveCriticalFlagAccess();
  return kCanCopyData;
}


#endif

#ifdef IL_ENABLE_RX
vuint8 IlMsgEHB_StatusPreCopy(CanRxInfoStructPtr rxStruct)
{
  rxStruct = rxStruct;
  IlEnterCriticalFlagAccess();
  ilRxTimerFlags[0] |= (vuint8) 0x08;
  IlLeaveCriticalFlagAccess();
  return kCanCopyData;
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Implementation Rx Timeout Indication Functions
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_RX) && (defined(IL_ENABLE_RX_TIMEOUT) || defined(IL_ENABLE_RX_EXT_TIMEOUT))
static void IlMsgPMS_VINTimeoutIndication(void)
{
  ApplPMS_VIN_TimeoutMsgTimeout();
}


#endif

#if defined(IL_ENABLE_RX) && (defined(IL_ENABLE_RX_TIMEOUT) || defined(IL_ENABLE_RX_EXT_TIMEOUT))
static void IlMsgIPK_TotalOdometerTimeoutIndication(void)
{
  ApplIPK_TotalOdometer_TimeoutMsgTimeout();
}


#endif

#if defined(IL_ENABLE_RX) && (defined(IL_ENABLE_RX_TIMEOUT) || defined(IL_ENABLE_RX_EXT_TIMEOUT))
static void IlMsgTBOX_DateTime_InfoTimeoutIndication(void)
{
  ApplTBOX_DateTime_Info_TimeoutMsgTimeout();
}


#endif

#if defined(IL_ENABLE_RX) && (defined(IL_ENABLE_RX_TIMEOUT) || defined(IL_ENABLE_RX_EXT_TIMEOUT))
static void IlMsgEHB_StatusTimeoutIndication(void)
{
  ApplEHB_Status_TimeoutMsgTimeout();
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Implementation of a function to check IfActive flags
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_SYS_TX_SIGNALS_ARE_ACTIVE_FCT)
Il_Boolean IlTxSignalsAreActive(void )
{
  return IL_FALSE;
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Implementation function to reset indication flags
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_POLLING)
void IlResetCanIndicationFlags(void )
{
  CanGlobalInterruptDisable();
  CanGlobalInterruptRestore();
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Implementation function to reset confirmation flags
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX)
void IlResetCanConfirmationFlags(void )
{
  CanGlobalInterruptDisable();
  IlGetTxConfirmationFlags(0) &= (vuint8) 0xE1;
  CanGlobalInterruptRestore();
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Get Rx Signal Access for signals greater 8bit and smaller or equal 32bit
 ----------------------------------------------------------------------------- */

/* Handle:    8,Name:           IPK_IPKTotalOdometer,Size: 24,UsedBytes:  3,SingleSignal */
#ifdef IL_ENABLE_RX
vuint32 IlGetRxIPK_IPKTotalOdometer(void)
{
  vuint32 rc;
  IlEnterCriticalIPK_IPKTotalOdometer();
  rc = ((vuint32) IPK_TotalOdometer.IPK_TotalOdometer.IPK_IPKTotalOdometer_0);
  rc |= ((vuint32) IPK_TotalOdometer.IPK_TotalOdometer.IPK_IPKTotalOdometer_1) << 8;
  rc |= ((vuint32) IPK_TotalOdometer.IPK_TotalOdometer.IPK_IPKTotalOdometer_2) << 16;
  IlLeaveCriticalIPK_IPKTotalOdometer();
  return rc;
}


#endif

/* Handle:   16,Name:               EHB_VehicleSpeed,Size: 13,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxEHB_VehicleSpeed(void)
{
  vuint16 rc;
  IlEnterCriticalEHB_VehicleSpeed();
  rc = ((vuint16) EHB_Status.EHB_Status.EHB_VehicleSpeed_0);
  rc |= ((vuint16) EHB_Status.EHB_Status.EHB_VehicleSpeed_1) << 5;
  IlLeaveCriticalEHB_VehicleSpeed();
  return rc;
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Set Tx Signal Access for signals smaller or equal 8bit, SendType cyclic or none
 ----------------------------------------------------------------------------- */

/* Handle:    0,Name:              MMI_RightSwStatus,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxMMI_RightSwStatus(vuint8 sigData)
{
  IlEnterCriticalMMI_RightSwStatus();
  MMI_Status_Info.MMI_Status_Info.MMI_RightSwStatus = sigData;
  IlLeaveCriticalMMI_RightSwStatus();
}


#endif

/* Handle:    1,Name:               MMI_LeftSwStatus,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxMMI_LeftSwStatus(vuint8 sigData)
{
  IlEnterCriticalMMI_LeftSwStatus();
  MMI_Status_Info.MMI_Status_Info.MMI_LeftSwStatus = sigData;
  IlLeaveCriticalMMI_LeftSwStatus();
}


#endif

/* Handle:    2,Name:                 MMI_UpSwStatus,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxMMI_UpSwStatus(vuint8 sigData)
{
  IlEnterCriticalMMI_UpSwStatus();
  MMI_Status_Info.MMI_Status_Info.MMI_UpSwStatus = sigData;
  IlLeaveCriticalMMI_UpSwStatus();
}


#endif

/* Handle:    3,Name:               MMI_DownSwStatus,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxMMI_DownSwStatus(vuint8 sigData)
{
  IlEnterCriticalMMI_DownSwStatus();
  MMI_Status_Info.MMI_Status_Info.MMI_DownSwStatus = sigData;
  IlLeaveCriticalMMI_DownSwStatus();
}


#endif

/* Handle:    4,Name:            MMI_ConfirmSwStatus,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxMMI_ConfirmSwStatus(vuint8 sigData)
{
  IlEnterCriticalMMI_ConfirmSwStatus();
  MMI_Status_Info.MMI_Status_Info.MMI_ConfirmSwStatus = sigData;
  IlLeaveCriticalMMI_ConfirmSwStatus();
}


#endif

/* Handle:    5,Name:             MMI_ReturnSwStatus,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxMMI_ReturnSwStatus(vuint8 sigData)
{
  IlEnterCriticalMMI_ReturnSwStatus();
  MMI_Status_Info.MMI_Status_Info.MMI_ReturnSwStatus = sigData;
  IlLeaveCriticalMMI_ReturnSwStatus();
}


#endif

/* Handle:    6,Name:                   MMI_WorkMode,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxMMI_WorkMode(vuint8 sigData)
{
  IlEnterCriticalMMI_WorkMode();
  MMI_Status_Info.MMI_Status_Info.MMI_WorkMode = sigData;
  IlLeaveCriticalMMI_WorkMode();
}


#endif

/* Handle:    7,Name:          TTS_BluetoothFunction,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxTTS_BluetoothFunction(vuint8 sigData)
{
  IlEnterCriticalTTS_BluetoothFunction();
  TTS_Status.TTS_Status.TTS_BluetoothFunction = sigData;
  IlLeaveCriticalTTS_BluetoothFunction();
}


#endif

/* Handle:    8,Name:           TTS_BluetoothConnect,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxTTS_BluetoothConnect(vuint8 sigData)
{
  IlEnterCriticalTTS_BluetoothConnect();
  TTS_Status.TTS_Status.TTS_BluetoothConnect = sigData;
  IlLeaveCriticalTTS_BluetoothConnect();
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Set Tx Signal Access 
 ----------------------------------------------------------------------------- */

/* Handle:    9,Name:          MMI_TextMultDataFrame,Size: 64,UsedBytes:  8,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxMMI_TextMultDataFrame(vuint8* pData)
{
  IlEnterCriticalMMI_TextMultDataFrame();
  MMI_TextMMData.MMI_TextMMData.MMI_TextMultDataFrame_0 = pData[0];
  MMI_TextMMData.MMI_TextMMData.MMI_TextMultDataFrame_1 = pData[1];
  MMI_TextMMData.MMI_TextMMData.MMI_TextMultDataFrame_2 = pData[2];
  MMI_TextMMData.MMI_TextMMData.MMI_TextMultDataFrame_3 = pData[3];
  MMI_TextMMData.MMI_TextMMData.MMI_TextMultDataFrame_4 = pData[4];
  MMI_TextMMData.MMI_TextMMData.MMI_TextMultDataFrame_5 = pData[5];
  MMI_TextMMData.MMI_TextMMData.MMI_TextMultDataFrame_6 = pData[6];
  MMI_TextMMData.MMI_TextMMData.MMI_TextMultDataFrame_7 = pData[7];
  IlSecureEvent(IlTxSigHndMMI_TextMultDataFrame);
  IlLeaveCriticalMMI_TextMultDataFrame();
}


#endif

/* Handle:   10,Name:            MMI_TextBTDataFrame,Size: 64,UsedBytes:  8,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxMMI_TextBTDataFrame(vuint8* pData)
{
  IlEnterCriticalMMI_TextBTDataFrame();
  MMI_TextBTData.MMI_TextBTData.MMI_TextBTDataFrame_0 = pData[0];
  MMI_TextBTData.MMI_TextBTData.MMI_TextBTDataFrame_1 = pData[1];
  MMI_TextBTData.MMI_TextBTData.MMI_TextBTDataFrame_2 = pData[2];
  MMI_TextBTData.MMI_TextBTData.MMI_TextBTDataFrame_3 = pData[3];
  MMI_TextBTData.MMI_TextBTData.MMI_TextBTDataFrame_4 = pData[4];
  MMI_TextBTData.MMI_TextBTData.MMI_TextBTDataFrame_5 = pData[5];
  MMI_TextBTData.MMI_TextBTData.MMI_TextBTDataFrame_6 = pData[6];
  MMI_TextBTData.MMI_TextBTData.MMI_TextBTDataFrame_7 = pData[7];
  IlSecureEvent(IlTxSigHndMMI_TextBTDataFrame);
  IlLeaveCriticalMMI_TextBTDataFrame();
}


#endif



#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 CanTransmitHandle V_MEMROM2 IlTxIndirection[kIlNumberOfTxObjects] = 
{
  1 /* ID: 0x000002a4, Handle: 0, MMI_Status_Info [BC] */, 
  2 /* ID: 0x00000249, Handle: 1, TTS_Status [BC] */, 
  3 /* ID: 0x000000fb, Handle: 2, MMI_TextMMData [BC] */, 
  4 /* ID: 0x000000f9, Handle: 3, MMI_TextBTData [BC] */
};
#endif


/* -----------------------------------------------------------------------------
    &&&~ CAN handle to Il start stop handle
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX) && defined(C_ENABLE_CAN_CANCEL_NOTIFICATION)
V_MEMROM0 V_MEMROM1 IlStartStopHnd V_MEMROM2 IlCanHndToIlHnd[kIlCanNumberOfTxObjects] = 
{
  { 0, 0 } /* no Il message */, 
  { 0, 1 } /* start - stop  ID: 0x000002a4, MMI_Status_Info [BC] */, 
  { 1, 2 } /* start - stop  ID: 0x00000249, TTS_Status [BC] */, 
  { 2, 3 } /* start - stop  ID: 0x000000fb, MMI_TextMMData [BC] */, 
  { 3, 4 } /* start - stop  ID: 0x000000f9, MMI_TextBTData [BC] */, 
  { 0, 0 } /* no Il message */
};
#endif




/* -----------------------------------------------------------------------------
    &&&~ TxTypes for interaction layer tx messages 
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 IlTxType[kIlNumberOfTxObjects] = 
{
  kTxSendCyclic /* ID: 0x000002a4, Handle: 0, MMI_Status_Info [BC] */, 
  kTxSendCyclic /* ID: 0x00000249, Handle: 1, TTS_Status [BC] */, 
  kTxSendCyclic /* ID: 0x000000fb, Handle: 2, MMI_TextMMData [BC] */, 
  kTxSendCyclic /* ID: 0x000000f9, Handle: 3, MMI_TextBTData [BC] */
};
#endif





