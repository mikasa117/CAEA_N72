/* -----------------------------------------------------------------------------
  Filename:    nmcbdwrp_cfg.h
  Description: Toolversion: 02.03.18.01.80.01.04.01.00.00
               
               Serial Number: CBD1800104
               Customer Info: Wenzhou Changjiang Automobile Electronic System Co.,Ltd.?CAEA)
                              Package: CBD_Vector_SLP2
                              Micro: FS32K146
                              Compiler: GNU 9.2.0
               
               
               Generator Fwk   : GENy 
               Generator Module: Nm_AsrNmCANbeddedWrapper
               
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

#if !defined(__NMCBDWRP_CFG_H__)
#define __NMCBDWRP_CFG_H__

/* Version */
#define NM_ASRNMCANWRAPPEREXTDLL_VERSION     0x0331u
#define NM_ASRNMCANWRAPPEREXTDLL_RELEASE_VERSION 0x00u
/* Instance properties */
#define kCbdWrpNumberOfChannels              1
#define kCbdWrpNumberOfCanChannels           1
/* Module options */
#define CBDWRP_DISABLE_ASR_ERROR_REPORT
#define CBDWRP_DISABLE_ASSERTIONS
#define CBDWRP_DISABLE_EARLY_BUSOFF_REINIT
#define CBDWRP_ENABLE_ASRNM_BUSOFF_SUPPORT
#define CBDWRP_DISABLE_TESTDEBUG
#define CBDWRP_DISABLE_RESET_BUSOFF_THRESHOLD_COUNTER_ON_ANY_TX_CONFIRMATION
#define CBDWRP_DISABLE_FASTBUSOFFRECOVERY_CHANGE_CALLBACK
#define CBDWRP_DISABLE_EXTERNAL_CANONLINE_HANDLING
#define CBDWRP_DISABLE_BUSOFF_NOTIFICATION_CALLBACK
/* Channel specific parameters */
#define kCbdWrpBusOffRecoveryTime            200
#define kCbdWrpBusOffRecoveryTimeFast        10
#define kCbdWrpBusOffThreshold               10
#define kCbdWrpNotifyBusOffThreshold         0
#define kCbdWrpCycleTime                     5
/* --------------------- Configuration Data Prototypes --------------------- */
#if defined ( CBDWRP_ADAPTATION_LAYER )
#else
# if ( kCbdWrpNumberOfChannels > 1u )
/* BusOff recovery time parameters. */
extern V_MEMROM0 V_MEMROM1 vuint16 V_MEMROM2 CbdWrpBusOffRecoveryTime[kCbdWrpNumberOfChannels];
extern V_MEMROM0 V_MEMROM1 vuint16 V_MEMROM2 CbdWrpBusOffRecoveryTimeFast[kCbdWrpNumberOfChannels];
extern V_MEMROM0 V_MEMROM1 vuint8  V_MEMROM2 CbdWrpBusOffThreshold[kCbdWrpNumberOfChannels];
extern V_MEMROM0 V_MEMROM1 vuint8  V_MEMROM2 CbdWrpCycleTime[kCbdWrpNumberOfChannels];
extern V_MEMROM0 V_MEMROM1 vuint8  V_MEMROM2 CbdWrpNotifyBusOffThreshold[kCbdWrpNumberOfChannels];
# endif
#endif

#if ( kCbdWrpNumberOfChannels != kCbdWrpNumberOfCanChannels )
/* CAN to local NM channel */
extern V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanNm_CanToNmChannelInd[kCbdWrpNumberOfCanChannels];
# if defined ( CBDWRP_ADAPTATION_LAYER )
# else
/* Local NM to CAN channel */
extern V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanNm_NmToCanChannelInd[kCbdWrpNumberOfChannels];
# endif
#endif

#if defined ( NM_ASRNMCANWRAPPEREXT_SOURCE ) || defined ( __NMCBDWRP_PAR_C__ )
/* --------------------- Module Data Prototypes --------------------- */
# if defined ( CBDWRP_ADAPTATION_LAYER )
# else
/* BusOff recovery timer. */
extern V_MEMRAM0 V_MEMRAM1 vuint16 V_MEMRAM2 cbdWrpBusOffRecTimer[kCbdWrpNumberOfChannels];
extern V_MEMRAM0 V_MEMRAM1 vuint8  V_MEMRAM2 cbdWrpBusOffThresholdCounter[kCbdWrpNumberOfChannels];
extern V_MEMRAM0 V_MEMRAM1 vuint8  V_MEMRAM2 cbdWrpNotifyBusOffThresholdCounter[kCbdWrpNumberOfChannels];

#  if defined ( CBDWRP_ENABLE_EARLY_BUSOFF_REINIT )
/* Indication Flag that the CAN Driver is in BusOff state */
extern V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 cbdWrpDrvCanIsBusOff[kCbdWrpNumberOfChannels];
#  endif
# endif
#endif

#endif /* __NMCBDWRP_CFG_H__ */
