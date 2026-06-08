/* -----------------------------------------------------------------------------
  Filename:    ccl_par.h
  Description: Toolversion: 02.03.18.01.80.01.04.01.00.00
               
               Serial Number: CBD1800104
               Customer Info: Wenzhou Changjiang Automobile Electronic System Co.,Ltd.?CAEA)
                              Package: CBD_Vector_SLP2
                              Micro: FS32K146
                              Compiler: GNU 9.2.0
               
               
               Generator Fwk   : GENy 
               Generator Module: Ccl__core
               
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

#if !defined(__CCL_PAR_H__)
#define __CCL_PAR_H__

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "v_cfg.h"
#include "v_def.h"
#include "can_inc.h"
#include "ccl_inc.h"

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/
#ifndef NM_OK
  #define NM_OK 0
#endif

#if !defined ( DRV_API_CALLBACK_TYPE )
  #define DRV_API_CALLBACK_TYPE
#endif


#define CCL_USE_REQUEST_SETEXTEMCCOM_FCT /* SetExtEmcComRequest routines are enabled in the CCL module */ 

#define CCL_USE_REQUEST_SETEXTCOM_FCT /* SetExtComRequest routines are enabled in the CCL module */ 

#define CCL_USE_REQUEST_SETINTCOM_FCT /* SetIntComRequest routines are enabled in the CCL module */ 

#define CCL_USE_REQUEST_CLEARCOM_FCT /* ClearComRequest routines are enabled in the CCL module */ 

#define CCL_DISABLE_WAKEUP_EV

#define CCL_DISABLE_SLEEP_COND

#define CCL_ENABLE_STOP_TIMEOUT


V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 cclNmWakeUpAble;
V_MEMROM0 extern V_MEMROM1 vuint16 V_MEMROM2 cclMinNmActivationTimerValue[1];
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 cclNmType[1];
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 cclStartIndex[1];
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 cclStopIndex[1];
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 cclUserOffset[kCclNumberOfUser];
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 cclUserMask[kCclNumberOfUser];
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 cclUserChannel[kCclNumberOfUser];
/*** prototypes ***/
extern void CclInitPowerOnFct(void);
extern void CclInitFct(void);
extern void CclSystemShutdownFct(void);
extern void CclNmSleepReqFct(vuint8 network);
extern vuint8 CclNmActiveReqFct(vuint8 network);
extern void CclNmPrepareSleepReqFct(void);
extern void CclInitTrcvFct(void);
extern void CclWakeUpTrcvFct(void);
extern void CclSleepTrcvFct(void);
extern void CclConfigTrcvIntFct(void);
extern void CclClearTrcvIntFct(void);
extern void CclDisableTrcvIntFct(void);
extern void CclEnableTrcvIntFct(void);
extern vuint8 CclCheckTrcvIntFct(void);

extern void CclExtEmcComReqFct(void);
extern void CclExtCanComReqFct(void);
extern void CclIntComReqFct(void);
extern void CclComRelFct(void);

extern void CCL_API_CALLBACK_TYPE CbkWakeupValidationNotification(void);
extern void CCL_API_CALLBACK_TYPE CbkWakeupbyBus(void);
extern void CCL_API_CALLBACK_TYPE CbkFirstCommunicationRequest(void);
extern void CCL_API_CALLBACK_TYPE CbkBusSleep(void);


#endif /* __CCL_PAR_H__ */
