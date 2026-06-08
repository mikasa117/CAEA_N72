/* -----------------------------------------------------------------------------
  Filename:    nmcbdwrp_par.c
  Description: Toolversion: 02.03.18.01.80.01.04.01.00.00
               
               Serial Number: CBD1800104
               Customer Info: Wenzhou Changjiang Automobile Electronic System Co.,Ltd.?CAEA)
                              Package: CBD_Vector_SLP2
                              Micro: FS32K146
                              Compiler: GNU 9.2.0
               
               
               Generator Fwk   : GENy 
               Generator Module: Nm_AsrNmCANbeddedWrapper
               
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

#define __NMCBDWRP_PAR_C__
/* Includes */
#include "v_cfg.h"
#include "v_def.h"
#include "nmcbdwrp_cfg.h"
/* Channel specific parameters */
/* Channel indirection */
/* --------------------- Module Data Prototypes --------------------- */
#if defined CBDWRP_ADAPTATION_LAYER
#else
/* BusOff recovery timer. */
V_MEMRAM0 V_MEMRAM1 vuint16 V_MEMRAM2 cbdWrpBusOffRecTimer[kCbdWrpNumberOfChannels];
V_MEMRAM0 V_MEMRAM1 vuint8  V_MEMRAM2 cbdWrpBusOffThresholdCounter[kCbdWrpNumberOfChannels];
V_MEMRAM0 V_MEMRAM1 vuint8  V_MEMRAM2 cbdWrpNotifyBusOffThresholdCounter[kCbdWrpNumberOfChannels];

# if defined ( CBDWRP_ENABLE_EARLY_BUSOFF_REINIT )
/* Indication Flag that the CAN Driver is in BusOff state */
V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 cbdWrpDrvCanIsBusOff[kCbdWrpNumberOfChannels];
# endif
#endif

