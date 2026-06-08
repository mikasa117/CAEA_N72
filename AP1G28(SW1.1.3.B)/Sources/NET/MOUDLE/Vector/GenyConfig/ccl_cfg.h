/* -----------------------------------------------------------------------------
  Filename:    ccl_cfg.h
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

#if !defined(__CCL_CFG_H__)
#define __CCL_CFG_H__

#include "can_inc.h"
#include "il_inc.h"
#include "Nm.h"
#include "CanNm.h"
#include "NmCbdWrp.h"
#include "tpmc.h"
#include "desc.h"
#include "appdesc.h"
/***************************************************************************/ 
/* Version                  (abcd: Main version ab Sub Version cd )        */ 
/***************************************************************************/ 

#define CCL_DLL_VERSION  0x0201
#define CCL_DLL_BUGFIX_VERSION  0x00
#define CCL__COREDLL_VERSION                 0x0311u
#define CCL__COREDLL_RELEASE_VERSION         0x33u
/***************************************************************************/ 
/* Defines                                                                 */ 
/***************************************************************************/ 

#define C_ENABLE_CCL 

#define CCL_DISABLE_ERROR_HOOK  /* CclFatalError function is disabled */ 

#define CCL_DISABLE_DEBUG /* disables the debug mode and switches the assertions to on */ 

#define CCL_DISABLE_EMC_WAKEUP

#define CCL_ENABLE_NMASR_WAKEUP_VALIDATION

#define CCL_DISABLE_WAKEUP_REG
#define CCL_ENABLE_INTERNAL_REQUEST
#define CCL_ENABLE_EXTERNAL_REQUEST
#define CCL_ENABLE_SLEEP_REPETITION

#define CCL_ENABLE_CANBEDDED_HANDLING
#define CCL_DISABLE_SCHEDULE_TASK
#define CCL_ENABLE_CONTAINER_TASK
#define CCL_DISABLE_STOP_MODE_ECU
#define CCL_DISABLE_POWER_DOWN_MODE_ECU
#define CCL_ENABLE_CUSTOMER_MODE_ECU
#define CCL_DISABLE_NET_STATE_RESTRICTION

#define CCL_ENABLE_TRCV_PORT_INT

#define CCL_ENABLE_TRCV_PORT_EDGE_TRIGGER

#define CCL_ENABLE_SYSTEM_SHUTDOWN

#define CCL_ENABLE_SW_COM_STATE

#define CCL_DISABLE_MISSING_ACK_HANDLING

#define kCclNrOfSystemChannels 1

#define kCclNrOfChannels 1  /* number of used channels */

#define kCclNrOfNetworks 1  /* number of used networks */ 

#define CCL_DISABLE_MULTIPLE_NODES  /* no multiple nodes */ 

#define CCL_ENABLE_BUSOFF_START

#define CCL_ENABLE_BUSOFF_END

#define CCL_ENABLE_BUSSTART

#define kCclNetReqTableSize 1  /* size of network request tabless */
#define kCclNumberOfUser 2
#define kCclEmcWakeUpTime 350   /* value depends on the CCL cycle time */
#define kCclCycleTime 10


/* Communication Handles */
#define CCL_CommunicationRequest    1
/***************************************************************************/ 
/* Macros                                                                  */ 
/***************************************************************************/ 


  /* *** Communication Request access macros *** */
#define CclSet_CommunicationRequest()                                     CclRequestCommunication(CCL_CommunicationRequest)


  /* *** Release Communication access macros *** */
#define CclRel_CommunicationRequest()                                     CclReleaseCommunication(CCL_CommunicationRequest)

extern void CclComStart(void);
extern void CclComStop(void);
extern void CclComWait(void);
extern void CclComResume(void);
extern void CCL_API_CALLBACK_TYPE ApplCclComStart(void);
extern void CCL_API_CALLBACK_TYPE ApplCclComStop(void);
extern void CCL_API_CALLBACK_TYPE ApplCclComWait(void);
extern void CCL_API_CALLBACK_TYPE ApplCclComResume(void);
extern void CclBusOffStart(void);
extern void CclBusOffEnd(void);
extern void CCL_API_CALLBACK_TYPE ApplCclBusOffStart(void);
extern void CCL_API_CALLBACK_TYPE ApplCclBusOffEnd(void);
extern void CCL_API_CALLBACK_TYPE ApplCclInit(void);
extern void CCL_API_CALL_TYPE  Ccl_5_0msTaskCont(void); 
extern void CCL_API_CALL_TYPE  Ccl_10_0msTaskCont(void);

#endif /* __CCL_CFG_H__ */
