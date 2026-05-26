/* -----------------------------------------------------------------------------
  Filename:    il_cfg.h
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

#if !defined(__IL_CFG_H__)
#define __IL_CFG_H__

/* -----------------------------------------------------------------------------
    &&&~ Version
 ----------------------------------------------------------------------------- */

#define IL_VECTORDLL_VERSION                 0x0120u
#define IL_VECTORDLL_RELEASE_VERSION         0x01u
#define IL_IMPLEMENTATION_VERSION            0x0202


/* -----------------------------------------------------------------------------
    &&&~ Switches
 ----------------------------------------------------------------------------- */

#define IL_DISABLE_SYS_INIT_FCT
#define IL_ENABLE_TX
#define IL_DISABLE_SYS_SIGNAL_INIT_FCT
#if defined(IL_ENABLE_TX)
#define IL_DISABLE_TX_SIGNAL_START_FCT
#define IL_DISABLE_TX_SIGNAL_STOP_FCT
#define IL_DISABLE_TX_CONFIRMATION_FLAG
#define IL_DISABLE_TX_TIMEOUT_FLAG
#define IL_ENABLE_TX_DEFAULTVALUE
#define IL_DISABLE_TX_UPDATE_BITS
#if defined(IL_ENABLE_TX_DEFAULTVALUE)
#define IL_DISABLE_TX_START_DEFAULTVALUE
#define IL_DISABLE_TX_STOP_DEFAULTVALUE
#endif

#define IL_DISABLE_TX_TIMEOUT
#define IL_DISABLE_TX_SEND_ON_INIT
#define IL_DISABLE_TX_FAST_ON_START
#define IL_ENABLE_TX_SECURE_EVENT	//JJH Don't change
#define IL_DISABLE_TX_CYCLIC_EVENT
#define IL_ENABLE_TX_POLLING
#define IL_DISABLE_TX_INTERRUPT
#define IL_DISABLE_TX_VARYING_TIMEOUT
//#define IL_ENABLE_TX_MODE_SIGNALS
#endif

#define IL_DISABLE_TX_STARTSTOP_CYCLIC
#define IL_DISABLE_SYS_ARGCHECK
#define IL_DISABLE_SYS_TESTDEBUG
#define IL_ENABLE_RX
#define IL_DISABLE_SYS_TX_START_FCT
#define IL_DISABLE_SYS_TX_STOP_FCT
#define IL_DISABLE_SYS_TX_REPETITIONS_ARE_ACTIVE_FCT
#define IL_DISABLE_SYS_TX_SIGNALS_ARE_ACTIVE_FCT
#define IL_ENABLE_SYS_RX_RESET_TIMEOUT_FLAGS_ON_ILRXRELEASE
#define IL_DISABLE_RELOAD_CYCLE_TIMER_ON_TRANSMISSION_REQUEST
#if defined(IL_ENABLE_RX)
#define IL_DISABLE_RX_SIGNAL_START_FCT
#define IL_DISABLE_RX_SIGNAL_STOP_FCT
#define IL_DISABLE_RX_INDICATION_FLAG
#define IL_DISABLE_RX_TIMEOUT_FLAG
#define IL_DISABLE_RX_FIRSTVALUE_FLAG
#define IL_DISABLE_RX_DATACHANGED_FLAG
#define IL_ENABLE_RX_DEFAULTVALUE
#if defined(IL_ENABLE_RX_DEFAULTVALUE)
#define IL_DISABLE_RX_START_DEFAULTVALUE
#define IL_DISABLE_RX_STOP_DEFAULTVALUE
#endif

#define IL_ENABLE_RX_TIMEOUT
#define IL_DISABLE_RX_POLLING
#define IL_ENABLE_RX_INTERRUPT
#define IL_DISABLE_RX_TIMEOUT_DELAY
#define IL_DISABLE_RX_MODE_SIGNALS
#endif

#define IL_DISABLE_SYS_RX_START_FCT
#define IL_DISABLE_SYS_RX_STOP_FCT
#define IL_DISABLE_TX_DYNAMIC_CYCLETIME
#define IL_DISABLE_TX_DYNAMIC_DELAYTIME
#define IL_DISABLE_TX_DYNAMIC_START_DELAYTIME
#define IL_DISABLE_SYS_MULTI_ECU_PHYS
#if defined(IL_ENABLE_TX)
#define IL_DISABLE_TX_VARYING_REPETITION
#endif

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
#define IL_DISABLE_RX_DYNAMIC_TIMEOUT
#endif



/* -----------------------------------------------------------------------------
    &&&~ OEM
 ----------------------------------------------------------------------------- */

#define IL_TYPE_VECTOR


/* -----------------------------------------------------------------------------
    &&&~ Constants
 ----------------------------------------------------------------------------- */

#define kIlNumberOfChannels                  1
#define kIlNumberOfTxObjects                 4
#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT)
#define kIlNumberOfTxTimeoutCounters         0
#endif

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
#define kIlNumberOfRxTimeoutCounters         4
#endif

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
#define kIlNoRxTimeoutSupervision            0xFFFF
#endif

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_CONFIRMATION_FLAG)
#define kIlNumberOfTxConfirmationFlags       0
#endif

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT_FLAG)
#define kIlNumberOfTxTimeoutFlags            0
#endif

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
#define kIlNumberOfTimerFlagBytes            1
#endif

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_SECURE_EVENT) && defined(IL_DISABLE_TX_VARYING_REPETITION)
#define kIlNumberOfTxRepetitions             1
#endif

#define kIlTxCycleTime                       5
#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT) && defined(IL_DISABLE_TX_VARYING_TIMEOUT)
#define kIlTxTimeout                         0
#endif

#define kIlNumberOfRxObjects                 4
#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_INDICATION_FLAG)
#define kIlNumberOfRxIndicationFlags         0
#endif

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT_FLAG)
#define kIlNumberOfRxTimeoutFlags            0
#endif

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_FIRSTVALUE_FLAG)
#define kIlNumberOfRxFirstvalueFlags         0
#endif

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_DATACHANGED_FLAG)
#define kIlNumberOfRxDataChangedFlags        0
#endif

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_INDICATION_FLAG)
#define kIlNumberOfRxIndicationBits          0
#endif

#define kIlRxCycleTime                       5
#define kIlCanNumberOfRxObjects              4
#define kIlCanNumberOfTxObjects              6
#define kIlNumberOfIdentities                1


/* -----------------------------------------------------------------------------
    &&&~ Compatiblility
 ----------------------------------------------------------------------------- */

#define kIlNumberOfNodes                     1


/* -----------------------------------------------------------------------------
    &&&~ AUTOSAR Published Information
 ----------------------------------------------------------------------------- */

#define COM_AR_MAJOR_VERSION                 2
#define COM_AR_MINOR_VERSION                 0
#define COM_AR_PATCH_VERSION                 0



#endif /* __IL_CFG_H__ */
