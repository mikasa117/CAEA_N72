/* -----------------------------------------------------------------------------
  Filename:    can_cfg.h
  Description: Toolversion: 02.03.18.01.80.01.04.01.00.00
               
               Serial Number: CBD1800104
               Customer Info: Wenzhou Changjiang Automobile Electronic System Co.,Ltd.?CAEA)
                              Package: CBD_Vector_SLP2
                              Micro: FS32K146
                              Compiler: GNU 9.2.0
               
               
               Generator Fwk   : GENy 
               Generator Module: DrvCan__base
               
               Configuration   : D:\2.OV_eclipse+Jlink\program\CFG\N72\cfg\N72.gny
               
               ECU: 
                       TargetSystem: Hw_S32Cpu
                       Compiler:     GNU
                       Derivates:    S32K146
               
               Channel "Channel0":
                       Databasefile: D:\2.OV_eclipse+Jlink\program\CFG\N72\cfg\DD0B66BACWWA.dbc
                       Bussystem:    CAN
                       Manufacturer: Vector
                       Node:         DMM

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

#if !defined(__CAN_CFG_H__)
#define __CAN_CFG_H__

#include "v_cfg.h"
#define HW_IMXFLEXCAN3CPUCANDLL_VERSION      0x0203u
#define HW_IMXFLEXCAN3CPUCANDLL_RELEASE_VERSION 0x01u

#define HW__BASECPUCANDLL_VERSION            0x0302u
#define HW__BASECPUCANDLL_RELEASE_VERSION    0x01u

#define DRVCAN__BASEDLL_VERSION              0x0326u
#define DRVCAN__BASEDLL_RELEASE_VERSION      0x00u

#define DRVCAN__BASERI14DLL_VERSION          0x0209u
#define DRVCAN__BASERI14DLL_RELEASE_VERSION  0x02u

#define DRVCAN__BASERI15DLL_VERSION          0x0109u
#define DRVCAN__BASERI15DLL_RELEASE_VERSION  0x01u

#define DRVCAN__BASERI20DLL_VERSION          0x0101u
#define DRVCAN__BASERI20DLL_RELEASE_VERSION  0x00u

#define DRVCAN__BASEHLLDLL_VERSION           0x0307u
#define DRVCAN__BASEHLLDLL_RELEASE_VERSION   0x00u

#define DRVCAN__BASERI14HLLDLL_VERSION       0x0208u
#define DRVCAN__BASERI14HLLDLL_RELEASE_VERSION 0x00u

#define DRVCAN__BASERI15HLLDLL_VERSION       0x0103u
#define DRVCAN__BASERI15HLLDLL_RELEASE_VERSION 0x00u

#define DRVCAN__BASERI20HLLDLL_VERSION       0x0102u
#define DRVCAN__BASERI20HLLDLL_RELEASE_VERSION 0x02u

#define CAN_DRV_IMXDLL_VERSION               0x0202u
#define CAN_DRV_IMXDLL_RELEASE_VERSION       0x00u


#define kCanNumberOfChannels                 1
#define kCanNumberOfHwChannels               1
#define kCanNumberOfPhysChannels             1
#define C_DISABLE_MEMCOPY_SUPPORT
#define C_DISABLE_OSEK_OS
#define C_DISABLE_VARIABLE_DLC
#define C_DISABLE_DLC_FAILED_FCT
#define C_DISABLE_VARIABLE_RX_DATALEN
#define C_DISABLE_MULTI_ECU_CONFIG
#define C_DISABLE_MULTI_ECU_PHYS
#define C_DISABLE_EXTENDED_ID
#define C_DISABLE_MIXED_ID
#define C_ENABLE_RECEIVE_FCT
#define APPL_CAN_MSGRECEIVED                 ApplCanMsgReceived

#define C_DISABLE_ECU_SWITCH_PASS
#define C_ENABLE_TRANSMIT_QUEUE
#define C_DISABLE_OVERRUN
#define C_DISABLE_INTCTRL_BY_APPL
#define C_DISABLE_COMMON_CAN
#define C_DISABLE_USER_CHECK
#define C_DISABLE_HARDWARE_CHECK
#define C_DISABLE_GEN_CHECK
#define C_DISABLE_INTERNAL_CHECK
#define C_DISABLE_DYN_RX_OBJECTS
#define C_ENABLE_DYN_TX_OBJECTS
#define C_ENABLE_DYN_TX_ID
#define C_ENABLE_DYN_TX_DLC
#define C_DISABLE_DYN_TX_DATAPTR
#define C_DISABLE_DYN_TX_PRETRANS_FCT
#define C_DISABLE_DYN_TX_CONF_FCT
#define C_DISABLE_EXTENDED_STATUS
#define C_DISABLE_TX_OBSERVE
#define C_DISABLE_HW_LOOP_TIMER
#define C_DISABLE_NOT_MATCHED_FCT
#define C_SECURITY_LEVEL                     30

#define C_DISABLE_MULTICHANNEL_API
#define C_ENABLE_PART_OFFLINE
#define C_DISABLE_MSG_TRANSMIT
#define C_DISABLE_MSG_TRANSMIT_CONF_FCT

#define C_ENABLE_RANGE_0
#define C_ENABLE_RANGE_1
#define C_DISABLE_RANGE_2
#define C_DISABLE_RANGE_3
#define ApplCanBusOff                        CbdWrpBusOff

#define ApplCanRange0Precopy                 TpPrecopyNormalDiagPhys
#define ApplCanRange1Precopy                 TpPrecopyExtendedDiagPhys
#define kCanNumberOfTxObjects                6
#define kCanNumberOfTxStatObjects            5
#define kCanNumberOfTxDynObjects             1
#define kCanNumberOfRxObjects                6
#define kCanNumberOfRxStatFullCANObjects     0
#define kCanNumberOfRxStatBasicCANObjects    6
#define kCanNumberOfRxDynFullCANObjects      0
#define kCanNumberOfRxDynBasicCANObjects     0
#define kCanNumberOfRxDynObjects             0
#define kCanNumberOfRxStatObjects            6
#define kCanNumberOfConfFlags                6
#define kCanNumberOfIndFlags                 2
#define kCanNumberOfConfirmationFlags        1
#define kCanNumberOfIndicationFlags          1
#define kCanNumberOfInitObjects              1
#define kCanExtNumberOfInitObjects           0
#define kCanHwRxDynFullStartIndex            8
#define C_SEARCH_LINEAR

#define C_ENABLE_RX_MSG_INDIRECTION

#define C_ENABLE_CONFIRMATION_FLAG
#define C_ENABLE_INDICATION_FLAG
#define C_ENABLE_PRETRANSMIT_FCT
#define C_ENABLE_CONFIRMATION_FCT
#define C_ENABLE_INDICATION_FCT
#define C_ENABLE_PRECOPY_FCT
#define C_ENABLE_COPY_TX_DATA
#define C_ENABLE_COPY_RX_DATA
#define C_ENABLE_DLC_CHECK
#define C_ENABLE_DLC_CHECK_MIN_DATALEN

#define C_ENABLE_GENERIC_PRECOPY
#define APPL_CAN_GENERIC_PRECOPY             IlCanGenericPrecopy

#define C_SEND_GRP_NONE                      0x00u
#define C_SEND_GRP_ALL                       0xFFu
#define C_SEND_GRP_IL                        0x01u
#define C_SEND_GRP_USER1                     0x02u
#define C_SEND_GRP_USER2                     0x04u
#define C_SEND_GRP_USER3                     0x08u
#define C_SEND_GRP_USER4                     0x10u
#define C_SEND_GRP_USER5                     0x20u
#define C_SEND_GRP_USER6                     0x40u
#define C_SEND_GRP_USER7                     0x80u
#define C_ENABLE_CAN_CANCEL_NOTIFICATION
#define APPL_CAN_CANCELNOTIFICATION          IlCanCancelNotification

#define kCanPhysToLogChannelIndex_0
#define C_RANGE0_ACC_MASK                    0x000u
#define C_RANGE1_ACC_MASK                    0x000u

#define C_RANGE0_ACC_CODE                    0x000u
#define C_RANGE1_ACC_CODE                    0x000u

#define C_DISABLE_RX_FULLCAN_OBJECTS
#define C_ENABLE_RX_BASICCAN_OBJECTS
#define kCanNumberOfRxFullCANObjects         0
#define kCanNumberOfRxFullMailboxes          0

#define kCanNumberOfRxBasicCANObjects        6
#define kCanNumberOfRxBasicMailboxes         1

#define kCanInitObj1                         0
#define C_ENABLE_COND_RECEIVE_FCT

#define C_DISABLE_TX_MASK_EXT_ID
#define C_DISABLE_RX_MASK_EXT_ID
#define C_MASK_EXT_ID                        0xFFFFFFFFu

#define C_ENABLE_CAN_CAN_INTERRUPT_CONTROL
#define C_DISABLE_CAN_TX_CONF_MSG_ACCESS
#define C_DISABLE_CAN_TX_CONF_FCT

#define C_DISABLE_TX_POLLING
#define C_DISABLE_RX_BASICCAN_POLLING
#define C_DISABLE_RX_FULLCAN_POLLING
#define C_DISABLE_ERROR_POLLING
#define C_DISABLE_WAKEUP_POLLING
#define C_DISABLE_MULTIPLE_BASICCAN
#define C_DISABLE_FULLCAN_OVERRUN
#define C_DISABLE_OSEK_OS_INTCAT2
#define C_DISABLE_COPY_RX_DATA_WITH_DLC
#define kCanTxQueueBytes                     4
#define kCanNumberOfMaxBasicCAN              8
#define kCanNumberOfHwObjPerBasicCan         1
#define C_DISABLE_CAN_RAM_CHECK
#define C_ENABLE_SLEEP_WAKEUP
#define C_DISABLE_CANCEL_IN_HW
#define C_DISABLE_ONLINE_OFFLINE_CALLBACK_FCT

#define C_DISABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION

#define C_RANGE0_IDTYPE                      kCanIdTypeStd
#define C_RANGE1_IDTYPE                      kCanIdTypeStd
#define kCanChannel_Channel0                 0
#define C_DISABLE_INTCTRL_ADD_CAN_FCT
#if defined(C_SINGLE_RECEIVE_BUFFER) || defined(C_MULTIPLE_RECEIVE_BUFFER)
#error "DrvCan__baseRI1.5 doesn't support Single/Multiple Receive Buffer API for the callback 'ApplCanMsgReceived'!"
#endif

#define C_DISABLE_RETRANSMIT
#define kCanNumberOfUsedCanTxIdTables        1
#define kCanNumberOfUsedCanRxIdTables        1
#define kCanNumberOfTxMailboxes              1

#define kCanNumberOfUnusedMailboxes          0

#define kCanNumberOfTxDirectObjects          0

#define C_DISABLE_TX_FULLCAN_OBJECTS


#define C_DISABLE_RX_QUEUE
#define C_DISABLE_APPLCANPRERXQUEUE
#define C_DISABLE_RX_QUEUE_RANGE
#define C_DISABLE_RXQUEUE_OVERRUN_NOTIFY

/* -----------------------------------------------------------------------------
    &&&~ RI20
 ----------------------------------------------------------------------------- */

#define C_DISABLE_CAN_FD_USED
#define C_DISABLE_CAN_FD_FULL
#define kCanMaxRxMailboxDataLen              8
#define kCanMaxTxMailboxDataLen              8
#define kCanNumberOfMailboxes                2
#define kCanNumberOfHwObjToMailboxIndirections 9
#define kCanMailboxTxNormalIndex             1
#define kCanMailboxTxStartIndex              1
#define kCanMailboxRxFullStartIndex          kCanMailboxNotUsed
#define kCanMailboxRxBasicStartIndex         0
#define kCanMailboxUnusedStartIndex          kCanMailboxNotUsed
#define kCanHwObjStartIndex                  0
#define kCanHwObjToMailboxIndirectionStartIndex 0
#define C_CAN_FD_USAGE                       C_CAN_FD_NONE
#define C_DISABLE_CAN_FD_HW_BUFFER_OPTIMIZATION
#define C_DISABLE_NESTED_INTERRUPTS
#define C_DISABLE_MULTI_ECU_RELOCATE_HWOBJ


#define C_DISABLE_INDIVIDUAL_POLLING
#define kCanBaseAddress                      0x10190000u
#define kCanIntMask1                         0x0101u
#define kCanRxBasicPollingMask1              0x00u
#define kCanRxFullPollingMask1               0x00u
#define kCanTxPollingMask1                   0x00u
#define kCanNumberOfFilters                  0x08u
#define kCanRFFN                             0x00u
#define kCanNumberOfFullConfigurableFilters  0x08u
#define kCanNumberOfMaxMailboxes             0x20u
#define kCanNumberOfTotalFilters             8
#define C_ENABLE_INTERRUPT
#define C_DISABLE_TASD
#define C_DISABLE_GLITCH_FILTER
#define C_DISABLE_FLEXCAN_STOP_MODE
#define C_DISABLE_WORKAROUND_ERR005829
#define C_DISABLE_FLEXCAN_PARITY_CHECK_AVAILABLE
#define C_DISABLE_FLEXCAN2_DERIVATIVE
#define C_DISABLE_MB32TO63
#define C_DISABLE_MB64TO95
#define C_DISABLE_MB96TO127
#define C_ENABLE_ASYM_MAILBOXES
#define C_DISABLE_EXTENDED_BITTIMING



#endif /* __CAN_CFG_H__ */
