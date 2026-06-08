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
               
               Configuration   : E:\work\ChangAn\AP1G28AACXWA\config\Geny\CX810.gny
               
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

static void IlMsgVIU_FR_3EDTimeoutIndication(void);
static void IlMsgVIU_FR_3D3TimeoutIndication(void);
static void IlMsgVIU_FR_3D1TimeoutIndication(void);
static void IlMsgVIU_FR_2F7TimeoutIndication(void);
static void IlMsgVIU_FR_2EFTimeoutIndication(void);
static void IlMsgVIU_FR_2ECTimeoutIndication(void);
static void IlMsgVIU_FR_288TimeoutIndication(void);
static void IlMsgVIU_FR_1C3TimeoutIndication(void);




/* -----------------------------------------------------------------------------
    &&&~ Internal Timer Handles
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
#define IlParHndRxVIU_FR_3ED                 0
#define IlParHndRxVIU_FR_3D3                 1
#define IlParHndRxVIU_FR_3D1                 2
#define IlParHndRxVIU_FR_2F7                 3
#define IlParHndRxVIU_FR_2EF                 4
#define IlParHndRxVIU_FR_2EC                 5
#define IlParHndRxVIU_FR_288                 6
#define IlParHndRxVIU_FR_1C3                 7
#endif



#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT)
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 IlTxTimeoutIndirection[kIlNumberOfTxObjects] = 
{
  kIlNoTxToutIndirection /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  kIlNoTxToutIndirection /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  kIlNoTxToutIndirection /* ID: 0x000003f3, Handle: 2, VRHCU_3F3 [BC] */, 
  kIlNoTxToutIndirection /* ID: 0x000003ee, Handle: 3, VRHCU_3EE [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_FAST_ON_START)
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxFastOnStartDuration[kIlNumberOfTxObjects] = 
{
  kIlNoFastOnStartDuration /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  kIlNoFastOnStartDuration /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  kIlNoFastOnStartDuration /* ID: 0x000003f3, Handle: 2, VRHCU_3F3 [BC] */, 
  kIlNoFastOnStartDuration /* ID: 0x000003ee, Handle: 3, VRHCU_3EE [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_FAST_ON_START) && defined(IL_ENABLE_TX_MODE_SIGNALS)
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxFastOnStartMuxDelay[kIlNumberOfTxObjects] = 
{
  0 /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  0 /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  0 /* ID: 0x000003f3, Handle: 2, VRHCU_3F3 [BC] */, 
  0 /* ID: 0x000003ee, Handle: 3, VRHCU_3EE [BC] */
};
#endif


#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxStartCycles[kIlNumberOfTxObjects] = 
{
  kIlNoCycleTime /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  kIlNoCycleTime /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  kIlNoCycleTime /* ID: 0x000003f3, Handle: 2, VRHCU_3F3 [BC] */, 
  kIlNoCycleTime /* ID: 0x000003ee, Handle: 3, VRHCU_3EE [BC] */
};
#endif


#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 IltTxUpdateCounter V_MEMROM2 IlTxUpdateCycles[kIlNumberOfTxObjects] = 
{
  kIlNoDelayTime /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  kIlNoDelayTime /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  kIlNoDelayTime /* ID: 0x000003f3, Handle: 2, VRHCU_3F3 [BC] */, 
  kIlNoDelayTime /* ID: 0x000003ee, Handle: 3, VRHCU_3EE [BC] */
};
#endif


#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxCyclicCycles[kIlNumberOfTxObjects] = 
{
  200 /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  100 /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  20 /* ID: 0x000003f3, Handle: 2, VRHCU_3F3 [BC] */, 
  20 /* ID: 0x000003ee, Handle: 3, VRHCU_3EE [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && (defined(IL_ENABLE_TX_CYCLIC_EVENT) || defined(IL_ENABLE_TX_SECURE_EVENT) || defined(IL_ENABLE_TX_FAST_ON_START))
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxEventCycles[kIlNumberOfTxObjects] = 
{
  kIlNoCycleTimeFast /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  kIlNoCycleTimeFast /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  kIlNoCycleTimeFast /* ID: 0x000003f3, Handle: 2, VRHCU_3F3 [BC] */, 
  kIlNoCycleTimeFast /* ID: 0x000003ee, Handle: 3, VRHCU_3EE [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_POLLING)
V_MEMROM0 V_MEMROM1 IlConfirmationFct V_MEMROM2 IlTxConfirmationFctPtr[kIlNumberOfTxObjects] = 
{
  V_NULL /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  V_NULL /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  V_NULL /* ID: 0x000003f3, Handle: 2, VRHCU_3F3 [BC] */, 
  V_NULL /* ID: 0x000003ee, Handle: 3, VRHCU_3EE [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT) && defined(C_MULTIPLE_RECEIVE_CHANNEL) && defined(IL_ENABLE_TX_VARYING_TIMEOUT) && (kIlNumberOfChannels > 1)
V_MEMROM0 V_MEMROM1 IltTxTimeoutCounter V_MEMROM2 IlTxTimeout[kIlNumberOfChannels] = 
{
  0
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_SECURE_EVENT) && defined(IL_ENABLE_TX_VARYING_REPETITION) && (kIlNumberOfTxObjects > 1)
V_MEMROM0 V_MEMROM1 IltTxRepetitionCounter V_MEMROM2 IlTxRepetitionCounters[kIlNumberOfTxObjects] = 
{
  0 /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  0 /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  0 /* ID: 0x000003f3, Handle: 2, VRHCU_3F3 [BC] */, 
  0 /* ID: 0x000003ee, Handle: 3, VRHCU_3EE [BC] */
};
#endif


/* -----------------------------------------------------------------------------
    &&&~ Rx Timeout Table
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
V_MEMROM0 V_MEMROM1 IltRxTimeoutCounter V_MEMROM2 IlRxTimeoutTbl[kIlNumberOfRxTimeoutCounters] = 
{
  200 /* ID: 0x000003ed, VIU_FR_3ED [FC] */, 
  200 /* ID: 0x000003d3, VIU_FR_3D3 [FC] */, 
  200 /* ID: 0x000003d1, VIU_FR_3D1 [FC] */, 
  1000 /* ID: 0x000002f7, VIU_FR_2F7 [FC] */, 
  200 /* ID: 0x000002ef, VIU_FR_2EF [FC] */, 
  200 /* ID: 0x000002ec, VIU_FR_2EC [FC] */, 
  200 /* ID: 0x00000288, VIU_FR_288 [FC] */, 
  200 /* ID: 0x000001c3, VIU_FR_1C3 [FC] */
};
#endif




#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
V_MEMROM0 V_MEMROM1 IlTimeoutIndicationFct V_MEMROM2 IlRxTimeoutFctPtr[kIlNumberOfRxTimeoutCounters] = 
{
  IlMsgVIU_FR_3EDTimeoutIndication /* ID: 0x000003ed, VIU_FR_3ED [FC] */, 
  IlMsgVIU_FR_3D3TimeoutIndication /* ID: 0x000003d3, VIU_FR_3D3 [FC] */, 
  IlMsgVIU_FR_3D1TimeoutIndication /* ID: 0x000003d1, VIU_FR_3D1 [FC] */, 
  IlMsgVIU_FR_2F7TimeoutIndication /* ID: 0x000002f7, VIU_FR_2F7 [FC] */, 
  IlMsgVIU_FR_2EFTimeoutIndication /* ID: 0x000002ef, VIU_FR_2EF [FC] */, 
  IlMsgVIU_FR_2ECTimeoutIndication /* ID: 0x000002ec, VIU_FR_2EC [FC] */, 
  IlMsgVIU_FR_288TimeoutIndication /* ID: 0x00000288, VIU_FR_288 [FC] */, 
  IlMsgVIU_FR_1C3TimeoutIndication /* ID: 0x000001c3, VIU_FR_1C3 [FC] */
};
#endif


#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_POLLING)
V_MEMROM0 V_MEMROM1 IlIndicationFct V_MEMROM2 IlCanRxIndicationFctPtr[kIlCanNumberOfRxObjects] = 
{
  V_NULL /* ID: 0x000003ed, Handle: 0, VIU_FR_3ED [FC] */, 
  V_NULL /* ID: 0x000003d3, Handle: 1, VIU_FR_3D3 [FC] */, 
  V_NULL /* ID: 0x000003d1, Handle: 2, VIU_FR_3D1 [FC] */, 
  V_NULL /* ID: 0x000002f7, Handle: 3, VIU_FR_2F7 [FC] */, 
  V_NULL /* ID: 0x000002ef, Handle: 4, VIU_FR_2EF [FC] */, 
  V_NULL /* ID: 0x000002ec, Handle: 5, VIU_FR_2EC [FC] */, 
  V_NULL /* ID: 0x00000288, Handle: 6, VIU_FR_288 [FC] */, 
  V_NULL /* ID: 0x000001c3, Handle: 7, VIU_FR_1C3 [FC] */
};
#endif


/* -----------------------------------------------------------------------------
    &&&~ RxDefaultInitValue Message Tables
 ----------------------------------------------------------------------------- */

V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 VIU_FR_3EDIlRxDefaultInitValue[7] = 
{
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00
};
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 VIU_FR_3D3IlRxDefaultInitValue[6] = 
{
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00
};
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 VIU_FR_3D1IlRxDefaultInitValue[1] = 
{
  0x00
};
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 VIU_FR_2F7IlRxDefaultInitValue[6] = 
{
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00
};
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 VIU_FR_2EFIlRxDefaultInitValue[4] = 
{
  0x00, 
  0x00, 
  0x00, 
  0x00
};
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 VIU_FR_2ECIlRxDefaultInitValue[1] = 
{
  0x00
};
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 VIU_FR_288IlRxDefaultInitValue[6] = 
{
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00
};
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 VIU_FR_1C3IlRxDefaultInitValue[6] = 
{
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00
};


/* -----------------------------------------------------------------------------
    &&&~ RxDefaultInitValue
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_DEFAULTVALUE)
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 V_MEMROM3* V_MEMROM1 V_MEMROM2 IlRxDefaultInitValue[kIlNumberOfRxObjects] = 
{
  VIU_FR_3EDIlRxDefaultInitValue, 
  VIU_FR_3D3IlRxDefaultInitValue, 
  VIU_FR_3D1IlRxDefaultInitValue, 
  VIU_FR_2F7IlRxDefaultInitValue, 
  VIU_FR_2EFIlRxDefaultInitValue, 
  VIU_FR_2ECIlRxDefaultInitValue, 
  VIU_FR_288IlRxDefaultInitValue, 
  VIU_FR_1C3IlRxDefaultInitValue
};
#endif



/* -----------------------------------------------------------------------------
    &&&~ Implementation of Precopy Functions
 ----------------------------------------------------------------------------- */

#ifdef IL_ENABLE_RX
vuint8 IlMsgVIU_FR_3EDPreCopy(CanRxInfoStructPtr rxStruct)
{
  rxStruct = rxStruct;
  IlEnterCriticalFlagAccess();
  ilRxTimerFlags[0] |= (vuint8) 0x01;
  IlLeaveCriticalFlagAccess();
  return kCanCopyData;
}


#endif

#ifdef IL_ENABLE_RX
vuint8 IlMsgVIU_FR_3D3PreCopy(CanRxInfoStructPtr rxStruct)
{
  rxStruct = rxStruct;
  IlEnterCriticalFlagAccess();
  ilRxTimerFlags[0] |= (vuint8) 0x02;
  IlLeaveCriticalFlagAccess();
  return kCanCopyData;
}


#endif

#ifdef IL_ENABLE_RX
vuint8 IlMsgVIU_FR_3D1PreCopy(CanRxInfoStructPtr rxStruct)
{
  rxStruct = rxStruct;
  IlEnterCriticalFlagAccess();
  ilRxTimerFlags[0] |= (vuint8) 0x04;
  IlLeaveCriticalFlagAccess();
  return kCanCopyData;
}


#endif

#ifdef IL_ENABLE_RX
vuint8 IlMsgVIU_FR_2F7PreCopy(CanRxInfoStructPtr rxStruct)
{
  rxStruct = rxStruct;
  IlEnterCriticalFlagAccess();
  ilRxTimerFlags[0] |= (vuint8) 0x08;
  IlLeaveCriticalFlagAccess();
  return kCanCopyData;
}


#endif

#ifdef IL_ENABLE_RX
vuint8 IlMsgVIU_FR_2EFPreCopy(CanRxInfoStructPtr rxStruct)
{
  rxStruct = rxStruct;
  IlEnterCriticalFlagAccess();
  ilRxTimerFlags[0] |= (vuint8) 0x10;
  IlLeaveCriticalFlagAccess();
  return kCanCopyData;
}


#endif

#ifdef IL_ENABLE_RX
vuint8 IlMsgVIU_FR_2ECPreCopy(CanRxInfoStructPtr rxStruct)
{
  rxStruct = rxStruct;
  IlEnterCriticalFlagAccess();
  ilRxTimerFlags[0] |= (vuint8) 0x20;
  IlLeaveCriticalFlagAccess();
  return kCanCopyData;
}


#endif

#ifdef IL_ENABLE_RX
vuint8 IlMsgVIU_FR_288PreCopy(CanRxInfoStructPtr rxStruct)
{
  rxStruct = rxStruct;
  IlEnterCriticalFlagAccess();
  ilRxTimerFlags[0] |= (vuint8) 0x40;
  IlLeaveCriticalFlagAccess();
  return kCanCopyData;
}
#endif
#ifdef IL_ENABLE_RX
vuint8 IlMsgVIU_FR_1C3PreCopy(CanRxInfoStructPtr rxStruct)
{
  rxStruct = rxStruct;
  IlEnterCriticalFlagAccess();
  ilRxTimerFlags[0] |= (vuint8) 0x80;
  IlLeaveCriticalFlagAccess();
  return kCanCopyData;
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Implementation Rx Timeout Indication Functions
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_RX) && (defined(IL_ENABLE_RX_TIMEOUT) || defined(IL_ENABLE_RX_EXT_TIMEOUT))
static void IlMsgVIU_FR_3EDTimeoutIndication(void)
{
  ApplVIU_FR_3EDMsgTimeout();
}


#endif

#if defined(IL_ENABLE_RX) && (defined(IL_ENABLE_RX_TIMEOUT) || defined(IL_ENABLE_RX_EXT_TIMEOUT))
static void IlMsgVIU_FR_3D3TimeoutIndication(void)
{
  ApplVIU_FR_3D3MsgTimeout();
}


#endif

#if defined(IL_ENABLE_RX) && (defined(IL_ENABLE_RX_TIMEOUT) || defined(IL_ENABLE_RX_EXT_TIMEOUT))
static void IlMsgVIU_FR_3D1TimeoutIndication(void)
{
  ApplVIU_FR_3D1MsgTimeout();
}


#endif

#if defined(IL_ENABLE_RX) && (defined(IL_ENABLE_RX_TIMEOUT) || defined(IL_ENABLE_RX_EXT_TIMEOUT))
static void IlMsgVIU_FR_2F7TimeoutIndication(void)
{
  ApplVIU_FR_2F7MsgTimeout();
}
#endif
#if defined(IL_ENABLE_RX) && (defined(IL_ENABLE_RX_TIMEOUT) || defined(IL_ENABLE_RX_EXT_TIMEOUT))
static void IlMsgVIU_FR_2EFTimeoutIndication(void)
{
  ApplVIU_FR_2EFMsgTimeout();
}


#endif

#if defined(IL_ENABLE_RX) && (defined(IL_ENABLE_RX_TIMEOUT) || defined(IL_ENABLE_RX_EXT_TIMEOUT))
static void IlMsgVIU_FR_2ECTimeoutIndication(void)
{
  ApplVIU_FR_2ECMsgTimeout();
}


#endif

#if defined(IL_ENABLE_RX) && (defined(IL_ENABLE_RX_TIMEOUT) || defined(IL_ENABLE_RX_EXT_TIMEOUT))
static void IlMsgVIU_FR_288TimeoutIndication(void)
{
  ApplVIU_FR_288MsgTimeout();
}


#endif

#if defined(IL_ENABLE_RX) && (defined(IL_ENABLE_RX_TIMEOUT) || defined(IL_ENABLE_RX_EXT_TIMEOUT))
static void IlMsgVIU_FR_1C3TimeoutIndication(void)
{
  ApplVIU_FR_1C3MsgTimeout();
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
  IlGetTxConfirmationFlags(0) &= (vuint8) 0xF0;
  CanGlobalInterruptRestore();
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Get Rx Signal Access for signals greater 8bit and smaller or equal 32bit
 ----------------------------------------------------------------------------- */

#ifdef IL_ENABLE_RX
vuint32 IlGetRxCdcTotMilg(void)
{
  vuint32 rc;
  IlEnterCriticalCdcTotMilg();
  rc = ((vuint32) VIU_FR_2EF.VIU_FR_2EF.CdcTotMilg_0);
  rc |= ((vuint32) VIU_FR_2EF.VIU_FR_2EF.CdcTotMilg_1) << 8;
  rc |= ((vuint32) VIU_FR_2EF.VIU_FR_2EF.CdcTotMilg_2) << 16;
  IlLeaveCriticalCdcTotMilg();
  return rc;
}
#endif
/* Handle:   27,Name:                      EspVehSpd,Size: 13,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxEspVehSpd(void)
{
  vuint16 rc;
  IlEnterCriticalEspVehSpd();
  rc = ((vuint16) VIU_FR_1C3.VIU_FR_1C3.EspVehSpd_0);
  rc |= ((vuint16) VIU_FR_1C3.VIU_FR_1C3.EspVehSpd_1) << 8;
  IlLeaveCriticalEspVehSpd();
  return rc;
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Set Tx Signal Access for signals smaller or equal 8bit, SendType cyclic or none
 ----------------------------------------------------------------------------- */

/* Handle:    0,Name:         VRHCP_WakeUp_BYTE3BIT0,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxVRHCP_WakeUp_BYTE3BIT0(vuint8 sigData)
{
  IlEnterCriticalVRHCP_WakeUp_BYTE3BIT0();
  VRHCU_6F9.VRHCU_6F9.VRHCP_WakeUp_BYTE3BIT0 = sigData;
  IlLeaveCriticalVRHCP_WakeUp_BYTE3BIT0();
}


#endif

/* Handle:    1,Name:       VRHCP_NotSleep_BYTE7BIT0,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxVRHCP_NotSleep_BYTE7BIT0(vuint8 sigData)
{
  IlEnterCriticalVRHCP_NotSleep_BYTE7BIT0();
  VRHCU_6F9.VRHCU_6F9.VRHCP_NotSleep_BYTE7BIT0 = sigData;
  IlLeaveCriticalVRHCP_NotSleep_BYTE7BIT0();
}


#endif

/* Handle:    2,Name:       VRHCP_NotSleep_BYTE7BIT1,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxVRHCP_NotSleep_BYTE7BIT1(vuint8 sigData)
{
  IlEnterCriticalVRHCP_NotSleep_BYTE7BIT1();
  VRHCU_6F9.VRHCU_6F9.VRHCP_NotSleep_BYTE7BIT1 = sigData;
  IlLeaveCriticalVRHCP_NotSleep_BYTE7BIT1();
}


#endif

/* Handle:    3,Name:       VRHCP_NotSleep_BYTE7BIT2,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxVRHCP_NotSleep_BYTE7BIT2(vuint8 sigData)
{
  IlEnterCriticalVRHCP_NotSleep_BYTE7BIT2();
  VRHCU_6F9.VRHCU_6F9.VRHCP_NotSleep_BYTE7BIT2 = sigData;
  IlLeaveCriticalVRHCP_NotSleep_BYTE7BIT2();
}


#endif

/* Handle:    4,Name:             VrhcuDTC1_HighByte,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxVrhcuDTC1_HighByte(vuint8 sigData)
{
  IlEnterCriticalVrhcuDTC1_HighByte();
  VRHCU_6EE.VRHCU_6EE.VrhcuDTC1_HighByte = sigData;
  IlLeaveCriticalVrhcuDTC1_HighByte();
}


#endif

/* Handle:    5,Name:             VrhcuDTC1_MiddByte,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxVrhcuDTC1_MiddByte(vuint8 sigData)
{
  IlEnterCriticalVrhcuDTC1_MiddByte();
  VRHCU_6EE.VRHCU_6EE.VrhcuDTC1_MiddByte = sigData;
  IlLeaveCriticalVrhcuDTC1_MiddByte();
}


#endif

/* Handle:    6,Name:              VrhcuDTC1_LowByte,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxVrhcuDTC1_LowByte(vuint8 sigData)
{
  IlEnterCriticalVrhcuDTC1_LowByte();
  VRHCU_6EE.VRHCU_6EE.VrhcuDTC1_LowByte = sigData;
  IlLeaveCriticalVrhcuDTC1_LowByte();
}


#endif

/* Handle:    7,Name:               VrhcuDTC1_Status,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxVrhcuDTC1_Status(vuint8 sigData)
{
  IlEnterCriticalVrhcuDTC1_Status();
  VRHCU_6EE.VRHCU_6EE.VrhcuDTC1_Status = sigData;
  IlLeaveCriticalVrhcuDTC1_Status();
}


#endif

/* Handle:    8,Name:             VrhcuDTC2_HighByte,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxVrhcuDTC2_HighByte(vuint8 sigData)
{
  IlEnterCriticalVrhcuDTC2_HighByte();
  VRHCU_6EE.VRHCU_6EE.VrhcuDTC2_HighByte = sigData;
  IlLeaveCriticalVrhcuDTC2_HighByte();
}


#endif

/* Handle:    9,Name:             VrhcuDTC2_MiddByte,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxVrhcuDTC2_MiddByte(vuint8 sigData)
{
  IlEnterCriticalVrhcuDTC2_MiddByte();
  VRHCU_6EE.VRHCU_6EE.VrhcuDTC2_MiddByte = sigData;
  IlLeaveCriticalVrhcuDTC2_MiddByte();
}


#endif

/* Handle:   10,Name:              VrhcuDTC2_LowByte,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxVrhcuDTC2_LowByte(vuint8 sigData)
{
  IlEnterCriticalVrhcuDTC2_LowByte();
  VRHCU_6EE.VRHCU_6EE.VrhcuDTC2_LowByte = sigData;
  IlLeaveCriticalVrhcuDTC2_LowByte();
}


#endif

/* Handle:   11,Name:               VrhcuDTC2_Status,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxVrhcuDTC2_Status(vuint8 sigData)
{
  IlEnterCriticalVrhcuDTC2_Status();
  VRHCU_6EE.VRHCU_6EE.VrhcuDTC2_Status = sigData;
  IlLeaveCriticalVrhcuDTC2_Status();
}


#endif

/* Handle:   12,Name:               VrhcuRequestACOn,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxVrhcuRequestACOn(vuint8 sigData)
{
  IlEnterCriticalVrhcuRequestACOn();
  VRHCU_3F3.VRHCU_3F3.VrhcuRequestACOn = sigData;
  IlLeaveCriticalVrhcuRequestACOn();
}


#endif

/* Handle:   13,Name:               VrhcuRefrAcpTemp,Size:  7,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxVrhcuRefrAcpTemp(vuint8 sigData)
{
  IlEnterCriticalVrhcuRefrAcpTemp();
  VRHCU_3F3.VRHCU_3F3.VrhcuRefrAcpTemp = sigData;
  IlLeaveCriticalVrhcuRefrAcpTemp();
}


#endif

/* Handle:   14,Name:                     Vrhcupower,Size:  7,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxVrhcupower(vuint8 sigData)
{
  IlEnterCriticalVrhcupower();
  VRHCU_3F3.VRHCU_3F3.Vrhcupower = sigData;
  IlLeaveCriticalVrhcupower();
}


#endif

/* Handle:   15,Name:                   VrhcuOffReas,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxVrhcuOffReas(vuint8 sigData)
{
  IlEnterCriticalVrhcuOffReas();
  VRHCU_3F3.VRHCU_3F3.VrhcuOffReas = sigData;
  IlLeaveCriticalVrhcuOffReas();
}


#endif

/* Handle:   16,Name:                   FridgeWorkSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxFridgeWorkSt(vuint8 sigData)
{
  IlEnterCriticalFridgeWorkSt();
  VRHCU_3EE.VRHCU_3EE.FridgeWorkSt = sigData;
  IlLeaveCriticalFridgeWorkSt();
}


#endif

/* Handle:   17,Name:              FridgeUVLedWorkSt,Size:  5,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxFridgeUVLedWorkSt(vuint8 sigData)
{
  IlEnterCriticalFridgeUVLedWorkSt();
  VRHCU_3EE.VRHCU_3EE.FridgeUVLedWorkSt = sigData;
  IlLeaveCriticalFridgeUVLedWorkSt();
}


#endif

/* Handle:   18,Name:                   FridgeDoorSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxFridgeDoorSt(vuint8 sigData)
{
  IlEnterCriticalFridgeDoorSt();
  VRHCU_3EE.VRHCU_3EE.FridgeDoorSt = sigData;
  IlLeaveCriticalFridgeDoorSt();
}


#endif

/* Handle:   19,Name:               FridgeHeatTempSt,Size:  5,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxFridgeHeatTempSt(vuint8 sigData)
{
  IlEnterCriticalFridgeHeatTempSt();
  VRHCU_3EE.VRHCU_3EE.FridgeHeatTempSt = sigData;
  IlLeaveCriticalFridgeHeatTempSt();
}


#endif

/* Handle:   20,Name:                   FridgeModeSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxFridgeModeSt(vuint8 sigData)
{
  IlEnterCriticalFridgeModeSt();
  VRHCU_3EE.VRHCU_3EE.FridgeModeSt = sigData;
  IlLeaveCriticalFridgeModeSt();
}


#endif

/* Handle:   21,Name:               FridgeCoolTempSt,Size:  5,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxFridgeCoolTempSt(vuint8 sigData)
{
  IlEnterCriticalFridgeCoolTempSt();
  VRHCU_3EE.VRHCU_3EE.FridgeCoolTempSt = sigData;
  IlLeaveCriticalFridgeCoolTempSt();
}


#endif

/* Handle:   22,Name:               FridgeDoorWarnSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxFridgeDoorWarnSt(vuint8 sigData)
{
  IlEnterCriticalFridgeDoorWarnSt();
  VRHCU_3EE.VRHCU_3EE.FridgeDoorWarnSt = sigData;
  IlLeaveCriticalFridgeDoorWarnSt();
}


#endif

/* Handle:   23,Name:                    FridgeErrSt,Size:  5,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxFridgeErrSt(vuint8 sigData)
{
  IlEnterCriticalFridgeErrSt();
  VRHCU_3EE.VRHCU_3EE.FridgeErrSt = sigData;
  IlLeaveCriticalFridgeErrSt();
}


#endif

/* Handle:   24,Name:                FridgeHeatActSt,Size:  7,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxFridgeHeatActSt(vuint8 sigData)
{
  IlEnterCriticalFridgeHeatActSt();
  VRHCU_3EE.VRHCU_3EE.FridgeHeatActSt = sigData;
  IlLeaveCriticalFridgeHeatActSt();
}


#endif

/* Handle:   25,Name:                   FridgeQFunSt,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxFridgeQFunSt(vuint8 sigData)
{
  IlEnterCriticalFridgeQFunSt();
  VRHCU_3EE.VRHCU_3EE.FridgeQFunSt = sigData;
  IlLeaveCriticalFridgeQFunSt();
}


#endif

/* Handle:   26,Name:                FridgeChdLockSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxFridgeChdLockSt(vuint8 sigData)
{
  IlEnterCriticalFridgeChdLockSt();
  VRHCU_3EE.VRHCU_3EE.FridgeChdLockSt = sigData;
  IlLeaveCriticalFridgeChdLockSt();
}


#endif

/* Handle:   27,Name:                   EgySaveModSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxEgySaveModSt(vuint8 sigData)
{
  IlEnterCriticalEgySaveModSt();
  VRHCU_3EE.VRHCU_3EE.EgySaveModSt = sigData;
  IlLeaveCriticalEgySaveModSt();
}


#endif

/* Handle:   28,Name:                  FridgestuffSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxFridgestuffSt(vuint8 sigData)
{
  IlEnterCriticalFridgestuffSt();
  VRHCU_3EE.VRHCU_3EE.FridgestuffSt = sigData;
  IlLeaveCriticalFridgestuffSt();
}


#endif

/* Handle:   29,Name:                  FridgeUVLedSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxFridgeUVLedSt(vuint8 sigData)
{
  IlEnterCriticalFridgeUVLedSt();
  VRHCU_3EE.VRHCU_3EE.FridgeUVLedSt = sigData;
  IlLeaveCriticalFridgeUVLedSt();
}


#endif

/* Handle:   30,Name:           FridgeDoorWarnTimeSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxFridgeDoorWarnTimeSt(vuint8 sigData)
{
  IlEnterCriticalFridgeDoorWarnTimeSt();
  VRHCU_3EE.VRHCU_3EE.FridgeDoorWarnTimeSt = sigData;
  IlLeaveCriticalFridgeDoorWarnTimeSt();
}


#endif

/* Handle:   31,Name:             ContinueWorkTimeSt,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxContinueWorkTimeSt(vuint8 sigData)
{
  IlEnterCriticalContinueWorkTimeSt();
  VRHCU_3EE.VRHCU_3EE.ContinueWorkTimeSt = sigData;
  IlLeaveCriticalContinueWorkTimeSt();
}


#endif



#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 CanTransmitHandle V_MEMROM2 IlTxIndirection[kIlNumberOfTxObjects] = 
{
  0 /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  1 /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  3 /* ID: 0x000003f3, Handle: 2, VRHCU_3F3 [BC] */, 
  4 /* ID: 0x000003ee, Handle: 3, VRHCU_3EE [BC] */
};
#endif


/* -----------------------------------------------------------------------------
    &&&~ CAN handle to Il start stop handle
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX) && defined(C_ENABLE_CAN_CANCEL_NOTIFICATION)
V_MEMROM0 V_MEMROM1 IlStartStopHnd V_MEMROM2 IlCanHndToIlHnd[kIlCanNumberOfTxObjects] = 
{
  { 0, 1 } /* start - stop  ID: 0x000006f9, VRHCU_6F9 [BC] */, 
  { 1, 2 } /* start - stop  ID: 0x000006ee, VRHCU_6EE [BC] */, 
  { 0, 0 } /* no Il message */, 
  { 2, 3 } /* start - stop  ID: 0x000003f3, VRHCU_3F3 [BC] */, 
  { 3, 4 } /* start - stop  ID: 0x000003ee, VRHCU_3EE [BC] */, 
  { 0, 0 } /* no Il message */
};
#endif




/* -----------------------------------------------------------------------------
    &&&~ TxTypes for interaction layer tx messages 
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 IlTxType[kIlNumberOfTxObjects] = 
{
  kTxSendCyclic | kTxQueueInit /* ID: 0x000006f9, Handle: 0, VRHCU_6F9 [BC] */, 
  kTxSendCyclic | kTxQueueInit /* ID: 0x000006ee, Handle: 1, VRHCU_6EE [BC] */, 
  kTxSendCyclic | kTxQueueInit /* ID: 0x000003f3, Handle: 2, VRHCU_3F3 [BC] */, 
  kTxSendCyclic | kTxQueueInit /* ID: 0x000003ee, Handle: 3, VRHCU_3EE [BC] */
};
#endif




