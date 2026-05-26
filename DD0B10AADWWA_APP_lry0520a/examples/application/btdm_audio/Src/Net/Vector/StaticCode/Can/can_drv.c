/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Hll Erzeugungsgangnummer: 1 */

/* STARTSINGLE_OF_MULTIPLE */

#if defined( C_KOMMENTAR_VECTOR )
/* ***************************************************************************
 |
 |                  SINGLE SOURCE fuer interne Verwendung
 |
 |    *****          N I C H T   A U S L I E F E R N       *****
 |
 |
 |************************************************************************** */
#endif

/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/** Project Name: DrvCan_Arm32Flexcan3Hll
 *
 *  \file     CAN_DRV.C
 *  \brief    Implementation of the CAN driver
 *  \details  see functional description below
 *
 *********************************************************************************************************************/


#define C_DRV_INTERNAL



/* *********************************************************************** */
/* Include files                                                           */
/* *********************************************************************** */
#include "can_cfg.h"
#include "can_inc.h"
#include "CanDrv.h"
# include "v_def.h"
# include "can_cfg.h"
# include "Can_Main.h"
# include "can_par.h"

#define C_ENABLE_RX_BASICCAN_OBJECTS

/* *********************************************************************** */
/* Version check                                                           */
/* *********************************************************************** */
#if( DRVCAN_IMXFLEXCAN3HLL_VERSION != 0x0401)
# error "Source and Header file are inconsistent!"
#endif
#if( DRVCAN_IMXFLEXCAN3HLL_RELEASE_VERSION != 0x01)
# error "Source and Header file are inconsistent!"
#endif

#if( C_VERSION_REF_IMPLEMENTATION != 0x200)
# error "Generated Data and CAN driver source file are inconsistent!"
#endif

#if( DRVCAN__COREHLL_VERSION != 0x0301)
# error "Source and Header file are inconsistent!"
#endif
#if( DRVCAN__COREHLL_RELEASE_VERSION != 0x00)
# error "Source and Header file are inconsistent!"
#endif

#if ( ( DRVCAN__HLLTXQUEUEBIT_VERSION != 0x0106) )
# error "TxQueue Source and Header Version inconsistent!"
#endif
#if ( ( DRVCAN__HLLTXQUEUEBIT_RELEASE_VERSION != 0x05) )
# error "TxQueue Source and Header Version inconsistent!"
#endif

#if defined( DRVCAN__HLLTXQUEUEBIT_VERSION )
# if ( ( DRVCAN__HLLTXQUEUEBIT_VERSION != 0x0106) || \
       ( DRVCAN__HLLTXQUEUEBIT_RELEASE_VERSION != 0x05)  )
#  error "TxQueue Version inconsistent!"
# endif

/* defines to satisfy MISRA checker tool */
# define DRVCAN__HLLTXQUEUEBYTE_VERSION 0x0000
# define DRVCAN__HLLTXQUEUEBYTE_RELEASE_VERSION 0x00

#else
# if defined( DRVCAN__HLLTXQUEUEBYTE_VERSION )
#  if ( ( DRVCAN__HLLTXQUEUEBYTE_VERSION != 0x0104) || \
       ( DRVCAN__HLLTXQUEUEBYTE_RELEASE_VERSION != 0x00)  )
#   error "TxQueue Version inconsistent!"
#  endif
# else
#  error "No TxQueue available"
# endif

/* defines to satisfy MISRA checker tool */
# define DRVCAN__HLLTXQUEUEBIT_VERSION 0x0000
# define DRVCAN__HLLTXQUEUEBIT_RELEASE_VERSION 0x00

#endif

/* *********************************************************************** */
/* Defines                                                                 */
/* *********************************************************************** */

/* return values */
#define kCanHlFinishRx                                     ((vuint8)0x00)
#define kCanHlContinueRx                                   ((vuint8)0x01)

#define  CANHL_TX_QUEUE_BIT

#if defined (MISRA_CHECK)
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG_RESET",        0277,0303      /* MD_Can_0277_negation,MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG_SET",          0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG",              0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_READ_PROTECTED_REG",               0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG_RESET_32BIT",  0277,0303      /* MD_Can_0277_negation,MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG_SET_32BIT",    0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG_32BIT",        0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_READ_PROTECTED_REG_32BIT",         0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_CanInterruptDisable",            0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_CanInterruptRestore",            0277,0303,0306 /* MD_Can_0277_negation,MD_Can_0303_HWaccess,MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pFlexCAN",                             0303,0306      /* MD_Can_0303_HWaccess,MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pCanRxMask",                           0303,0306      /* MD_Can_0303_HWaccess,MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pRXFIFO",                              0303,0306      /* MD_Can_0303_HWaccess,MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pCanParityCheck",                      0303           /* MD_Can_0303_HWaccess,MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pCanFDRegister",                       0303           /* MD_Can_0303_HWaccess,MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "LOCAL_MAILBOX_ACCESS",                 0303           /* MD_Can_0303_HWaccess,MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "GLOBAL_MAILBOX_ACCESS",                0303           /* MD_Can_0303_HWaccess,MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanBswap32",                           0303           /* MD_Can_0303_HWaccess,MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_TxIsObjFree",                    0303,0306      /* MD_Can_0303_HWaccess,MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsSleep",                      0303,0306,3689 /* MD_Can_0303_HWaccess,MD_Can_0306_HWaccess,MD_Can_3689 */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsStop",                       0303,0306      /* MD_Can_0303_HWaccess,MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsBusOff",                     0303,0306      /* MD_Can_0303_HWaccess,MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsPassive",                    0303,0306      /* MD_Can_0303_HWaccess,MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsWarning",                    0303,0306      /* MD_Can_0303_HWaccess,MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualIdType",                    0488,0489,3689 /* MD_Can_0488_LL,MD_Can_0489_LL,MD_Can_3689 */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualIdType",                    0488,0489      /* MD_Can_0488_LL,MD_Can_0489_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_DECODE_DLI",                       0489           /* MD_Can_0489_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualDLC",                       0489           /* MD_Can_0489_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualExtId",                     0488,0310,3305 /* MD_Can_0488_LL,MD_Can_0310,MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualStdId",                     0488,0310,3305 /* MD_Can_0488_LL,MD_Can_0310,MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualId",                        0488,0310,3305 /* MD_Can_0488_LL,MD_Can_0310,MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualFdType",                    0310,3305      /* MD_Can_0310,MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualIdRaw0",                    0310,3305      /* MD_Can_0310,MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualStdId",                     0488,0310      /* MD_Can_0488_LL,MD_Can_0310 */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualExtId",                     0488,0310      /* MD_Can_0488_LL,MD_Can_0310 */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualData",                      0488           /* MD_Can_0488_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "assertUser",                           0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "assertHardware",                       0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_TxIsRetransmitPossible",         0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_RX_INDEX_TBL",                     0310,3305      /* MD_Can_0310,MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CANRANGE0IDTYPE",                      3689           /* MD_Can_3689 */
# pragma PRQA_MACRO_MESSAGES_OFF "CANRANGE1IDTYPE",                      3689           /* MD_Can_3689 */
# pragma PRQA_MACRO_MESSAGES_OFF "CANRANGE2IDTYPE",                      3689           /* MD_Can_3689 */
# pragma PRQA_MACRO_MESSAGES_OFF "CANRANGE3IDTYPE",                      3689           /* MD_Can_3689 */
#endif

/* Define chiphardware                     */
/* Constants concerning can chip registers */
/* Bitmasks of FlexCAN module configuration register CANx_MCR */
//#define kFlexCAN_MDIS      ((vuint16)0x8000u)     /* Module Disable: shut down FlexCAN clocks */
//#define kFlexCAN_FRZ       ((vuint16)0x4000u)     /* Freeze Enable: allow entering the freeze mode */
//#define kFlexCAN_FEN       ((vuint16)0x2000u)     /* FIFO enable */
//#define kFlexCAN_HALT      ((vuint16)0x1000u)     /* Halt FlexCAN: request entering the freeze mode */
//#define kFlexCAN_NOT_RDY   ((vuint16)0x0800u)     /* Not Ready: FlexCAN is in DISABLE, DOZE or STOP mode */
//#define kFlexCAN_WAK_MSK   ((vuint16)0x0400u)     /* Wakeup Interrupt Mask: enable wakeup interrupt generation */
//#define kFlexCAN_SOFT_RST  ((vuint16)0x0200u)     /* Soft Reset: reset FlexCAN internal state and some memory mapped registers */
//#define kFlexCAN_FRZ_ACK   ((vuint16)0x0100u)     /* Freeze Mode Acknowledge */
//#define kFlexCAN_SUPV      ((vuint16)0x0080u)     /* Supervisor Mode */
//#define kFlexCAN_SLF_WAK   ((vuint16)0x0040u)     /* FlexCAN Self Wakeup by CAN bus activity */
//#define kFlexCAN_WRN_EN    ((vuint16)0x0020u)     /* Warning Interrupt Enable */
//#define kFlexCAN_LPM_ACK   ((vuint16)0x0010u)     /* Low Power Mode Acknowledge */
//#define kFlexCAN_WAK_SRC   ((vuint16)0x0008u)     /* Wakeup Source: enable filtered Rx input signal */
//#define kFlexCAN_DOZE      ((vuint16)0x0004u)     /* Doze Mode Enable: allow MCU to switch FlexCAN into DOZE low power mode */
//#define kFlexCAN_NOT_DOZE  ((vuint16)0xFFFBu)     /* Doze Mode Disable: do not allow MCU to switch FlexCAN into DOZE low power mode */
//#define kFlexCAN_SRX_DIS   ((vuint16)0x0002u)     /* Self Reception Disable */
//#define kFlexCAN_IRMQ      ((vuint16)0x0001u)     /* Backwards Compatibility Configuration: enable Individual Rx Masks and queue feature */
//
//#define kFlexCAN_LPPRIO_EN ((vuint16)0x2000u)     /* Local Priority Enable */
//#define kFlexCAN_AEN       ((vuint16)0x1000u)     /* Abort Enable: enables transmit abort feature */
//#define kFlexCAN_FDEN      ((vuint16)0x0800u)     /* CAN FD operation enable */
//#define kFlexCAN_IDAM      ((vuint16)0x0300u)     /* ID Acceptance Mode */
//#define kFlexCAN_MAXMB     ((vuint16)0x003Fu)     /* Maximum Number of Message Buffers: maximum number of used message buffers = MAXMB+1 */
//
///* Bitmasks of FlexCAN module configuration register CANx_CTRL1 */
//#define kFlexCAN_BOFF_MSK  ((vuint32)0x00008000u)   /* FlexCAN BusOff interrupt mask */
//#define kFlexCAN_LOM       ((vuint32)0x00000008u)   /* FlexCAN Listen Only Mode */
//#define kFlexCAN_CLK_SRC   ((vuint32)0x00002000u)   /* FlexCAN clock source mask */
//#define kFlexCAN_BOFF_REC  ((vuint32)0x00000040u)   /* FlexCAN auto BusOff recovery */
//#define kFlexCAN_SMP       ((vuint32)0x00000080u)   /* FlexCAN sampling mode */
//
///* Bitmasks of FlexCAN module configuration register CANx_ESR */
//#define kFlexCAN_WAKE_INT   (vuint32)0x00000001u     /* Wake Up interrupt flag */
//#define kFlexCAN_ERR_INT    (vuint32)0x00000002u     /* Error interrupt flag */
//#define kFlexCAN_BOFF_INT   (vuint32)0x00000004u     /* Bus Off interrupt flag */
//#define kFlexCAN_FCS_BOFF   (vuint32)0x00000020u     /* Fault Confinement State value for BusOff */
//#define kFlexCAN_FCS_EP     (vuint32)0x00000010u     /* Fault Confinement State value for ErrorPassive */
//#define kFlexCAN_FCS        (vuint32)0x00000030u     /* Fault Confinement State */
//#define kFlexCAN_RXTX_WARN  (vuint32)0x00000300u
//#define kFlexCAN_STATUS_INT (kFlexCAN_BOFF_INT | kFlexCAN_ERR_INT | kFlexCAN_WAKE_INT)
//
//#define kFlexCAN_MCR               (kFlexCAN_MDIS | kFlexCAN_FRZ | kFlexCAN_HALT | kFlexCAN_NOT_RDY | kFlexCAN_FRZ_ACK | kFlexCAN_LPM_ACK)
//#define kFlexCAN_FREEZE_MODE       (kFlexCAN_FRZ | kFlexCAN_HALT | kFlexCAN_NOT_RDY | kFlexCAN_FRZ_ACK) /* FlexCAN in FREEZE mode: FRZ, HALT, NOT_RDY and FRZ_ACK bit are set */
//#define kFlexCAN_STOP_MODE         (kFlexCAN_NOT_RDY | kFlexCAN_LPM_ACK) /* FlexCAN in STOP powerdown mode: NOT_RDY and LPM_ACK bits set */
//#define kFlexCAN_DISABLE_MODE      (kFlexCAN_MDIS | kFlexCAN_NOT_RDY | kFlexCAN_LPM_ACK) /* FlexCAN in DISABLE powerdown mode: MDIS, NOT_RDY and LPM_ACK bit are set */
//#define kFlexCAN_NORMAL_MODE       ((vuint16)0x0000u) /* relevant bits for mode states must all be negated for NORMAL mode */
///* FlexCAN is DISABLED, independent from FREEZE mode:
//  -> MDIS and LPM_ACK bit are necessary to identify DISABLE mode
//  -> NOT_RDY must not be checked because it also influenced by FREEZE mode
//*/
//#define kFlexCAN_DISABLE_ONLY_BITS (kFlexCAN_MDIS | kFlexCAN_LPM_ACK)
//#define kNotFlexCAN_MCR_CFG_BTIS   (kFlexCAN_MCR | kFlexCAN_SOFT_RST | kFlexCAN_SUPV) /* user configurable bits are '0', not changeable bits are '1' */
//
//#define kNotFlexCANErrBoff ((vuint32)0xFFFF3FFFu)
//
//#define CANSFR_CLEAR      ((vuint32)0x00000000u)
//#define CANSFR_SET        ((vuint32)0xFFFFFFFFu)
//
///* Macros to access the CODE-bits in the control/status word ------------------*/
//#define kCodeMask         ((vuint16)0x0F00u)     /* Mask to access the CODE in the control/status word */
//#define kNotDlcMask       ((vuint16)0xFF00u)
//#define kNotCodeMask      ((vuint16)0xF0FFu)
//
///* Code definitions for receive objects */
//#define kRxCodeEmpty      ((vuint16)0x0400u)    /* Message buffer is active and empty */
//#define kRxCodeClear      ((vuint16)0x00F0u)    /* Mask to clear control register but leave the ID type */
//#define kRxCodeOverrun    ((vuint16)0x0600u)    /* Second frame was received into a full buffer */
//#define kRxCodeBusy       ((vuint16)0x0100u)    /* Receive buffer locked */
//
///* Code definitions for transmit objects */
//#define kTxCodeTransmit     ((vuint16)0x0C40u)     /* transmit request in nominal bit rate  */
//#define kTxCodeTransmitFD   ((vuint16)0xCC40u)     /* transmit request for CAN-FD: EDL (extended data length) and BRS (bit rate switch) bit must be set */
//#define kNotIDEMask         ((vuint16)0xFF0Fu)
//#define kTxDlcMask          ((vuint16)0x006Fu)     /* Mask to access the DLC in the control/status word */
//#define kTxCodeFree         ((vuint16)0x0800u)     /* Transmit object free */
//#define kTxCodeAbort        ((vuint16)0x0900u)     /* Abort message transmission */
//
//#if defined( C_ENABLE_EXTENDED_ID )
//# define kTxCodeInactive  ((vuint16)0x0820u)  /* Transmit object inactive for extended or mixed IDs */
//#else
//# define kTxCodeInactive  ((vuint16)0x0800u)  /* Transmit object inactive for standard IDs */
//#endif
//
///* Code definitions for Rx FiFo ---------------------------- */
//#define kRxFIFO_OVERRUN     (vuint32)0x00000080u
//#define kRxFIFO_WARN        (vuint32)0x00000040u
//#define kRxFIFO_NEWMSG      (vuint32)0x00000020u
//#define kRxFIFO_EXT         (vuint32)0x40000000u
//#define kRxFIFO_REM         (vuint32)0x80000000u
//#define kRxFIFO_MASK        (vuint32)0xC0000000u
//#if !defined( C_FLEXCAN_RXFIFO_MAXLOOP )
//# define C_FLEXCAN_RXFIFO_MAXLOOP  6
//#endif
//
///* Code definitions for ctrl2 register ------------------- */
//#define kFlexCAN_ECRWRE         (vuint32)0x20000000u
//#define kFlexCAN_MRP            (vuint32)0x00040000u
//#define kFlexCAN_RRS            (vuint32)0x00020000u
//#define kFlexCAN_EACEN          (vuint32)0x00010000u
//#define kFlexCAN_TASD_DEFAULT   (vuint32)0x00800000u
//#define kFlexCAN_STFCNTEN       (vuint32)0x00001000u
//
///* Code definitions for mecr  register ------------------- */
//#define kFlexCAN_ECRWRDIS       (vuint32)0x80000000u
//
//#define kExtIDBit               (vuint32)0x80000000u
//
//#if !defined( C_MASK_EXT_ID )
//# define C_MASK_EXT_ID ((vuint32)0xDFFFFFFFu)
//#endif
//
//#define kCanRxMaskStd     ((vuint32)0xDFFC0000u)
//#if defined( C_ENABLE_EXTENDED_ID )
//# if defined( C_ENABLE_RX_MASK_EXT_ID )
//#  define kCanRxMaskExt   ((vuint32)C_MASK_EXT_ID)
//# else
//#  define kCanRxMaskExt   ((vuint32)0xDFFFFFFFu)
//# endif
//#endif

#if defined( C_ENABLE_EXTENDED_ID )
# define CAN_MSGID(x) (vuint32)(x)
#else
# define CAN_MSGID(x) ((vuint32)(x) << 16)
#endif

#define kCanRxFifoIntUnmask   ((vuint32)0xFFFFFF00u)

#define kCanMaskAll32 0xFFFFFFFFUL
#define kCanMaskAll16 0xFFFFu

/* all bits of CAN[MCR].MCR except mode and reserved bits */
//#define kCanRamCheckMaskMCR         0x24EBu
//
//#if defined ( C_ENABLE_MB96TO127 ) || defined ( C_ENABLE_MB64TO95 )
//# define maxmbMask                  0x007Fu
//#else
//# define maxmbMask                  0x003Fu
//#endif
//
///* all bits of CAN[MCR].MAXMB except unused/reserved bits */
//#if defined( C_ENABLE_CAN_FD_USED )
//# define kCanRamCheckMaskMAXMB      (0x3300u | kFlexCAN_FDEN | maxmbMask)
//#else
//# define kCanRamCheckMaskMAXMB      (0x3300u | maxmbMask)
//#endif
//
//#define kCanRamCheckMailboxControl  0x0F7Fu
//
//#define CanBswap32(x)                   (vuint32)  (( ((vuint32)((x) & 0xFF000000UL)) >> 24) | \
//                                                    ( ((vuint32)((x) & 0x00FF0000UL)) >>  8) | \
//                                                    ( ((vuint32)((x) & 0x0000FF00UL)) <<  8) | \
//                                                    ( ((vuint32)((x) & 0x000000FFUL)) << 24))      /* swap b4-b3-b2-b1 to b1-b2-b3-b4 */

/* FlexCAN LL Init Transition States */
#define kCanLLStateInitStart                    0
#define CanLLStateInitSoftResetStart            1
#define CanLLStateInitSoftResetWaitEnd          2

/* FlexCAN LL Transition States */
#define kCanLLStateStart                        0
#define kCanLLStateRequested                    1

/* *********************************************************************** */
/* macros                                                                  */
/* *********************************************************************** */

#if !(defined( C_HL_DISABLE_RX_INFO_STRUCT_PTR ) || defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR ))
# define C_HL_ENABLE_RX_INFO_STRUCT_PTR
#endif

#if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
# define CAN_HL_P_RX_INFO_STRUCT(channel)                  (pCanRxInfoStruct)
# define CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)           (pCanRxInfoStruct->Handle)
#else
# define CAN_HL_P_RX_INFO_STRUCT(channel)                  (&canRxInfoStruct[channel])
# define CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)           (canRxInfoStruct[channel].Handle)
#endif

/* disabled - lint -emacro( (572, 778), C_RANGE_MATCH) */

#if defined( C_SINGLE_RECEIVE_CHANNEL )
# if (kCanNumberOfUsedCanRxIdTables == 1)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, mask, code) \
                  (  ((idRaw0) & (tCanRxId0)~MK_RX_RANGE_MASK_IDSTD0(mask)) == MK_RX_RANGE_CODE_IDSTD0(code) )
#  define C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, mask, code) \
                  (  ((idRaw0) & (tCanRxId0)~MK_RX_RANGE_MASK_IDEXT0(mask)) == MK_RX_RANGE_CODE_IDEXT0(code) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 2)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDSTD0(mask)) == MK_RX_RANGE_CODE_IDSTD0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDSTD1(mask)) == MK_RX_RANGE_CODE_IDSTD1(code) ) )
#  define C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDEXT0(mask)) == MK_RX_RANGE_CODE_IDEXT0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDEXT1(mask)) == MK_RX_RANGE_CODE_IDEXT1(code) ) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 3)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDSTD0(mask)) == MK_RX_RANGE_CODE_IDSTD0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDSTD1(mask)) == MK_RX_RANGE_CODE_IDSTD1(code) ) && \
                    ( ((idRaw2) & (tCanRxId2)~ MK_RX_RANGE_MASK_IDSTD2(mask)) == MK_RX_RANGE_CODE_IDSTD2(code) ) )
#  define C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDEXT0(mask)) == MK_RX_RANGE_CODE_IDEXT0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDEXT1(mask)) == MK_RX_RANGE_CODE_IDEXT1(code) ) && \
                    ( ((idRaw2) & (tCanRxId2)~ MK_RX_RANGE_MASK_IDEXT2(mask)) == MK_RX_RANGE_CODE_IDEXT2(code) ) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 4)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDSTD0(mask)) == MK_RX_RANGE_CODE_IDSTD0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDSTD1(mask)) == MK_RX_RANGE_CODE_IDSTD1(code) ) && \
                    ( ((idRaw2) & (tCanRxId2)~ MK_RX_RANGE_MASK_IDSTD2(mask)) == MK_RX_RANGE_CODE_IDSTD2(code) ) && \
                    ( ((idRaw3) & (tCanRxId3)~ MK_RX_RANGE_MASK_IDSTD3(mask)) == MK_RX_RANGE_CODE_IDSTD3(code) ) )
#  define C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDEXT0(mask)) == MK_RX_RANGE_CODE_IDEXT0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDEXT1(mask)) == MK_RX_RANGE_CODE_IDEXT1(code) ) && \
                    ( ((idRaw2) & (tCanRxId2)~ MK_RX_RANGE_MASK_IDEXT2(mask)) == MK_RX_RANGE_CODE_IDEXT2(code) ) && \
                    ( ((idRaw3) & (tCanRxId3)~ MK_RX_RANGE_MASK_IDEXT3(mask)) == MK_RX_RANGE_CODE_IDEXT3(code) ) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 5)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDSTD0(mask)) == MK_RX_RANGE_CODE_IDSTD0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDSTD1(mask)) == MK_RX_RANGE_CODE_IDSTD1(code) ) && \
                    ( ((idRaw2) & (tCanRxId2)~ MK_RX_RANGE_MASK_IDSTD2(mask)) == MK_RX_RANGE_CODE_IDSTD2(code) ) && \
                    ( ((idRaw3) & (tCanRxId3)~ MK_RX_RANGE_MASK_IDSTD3(mask)) == MK_RX_RANGE_CODE_IDSTD3(code) ) && \
                    ( ((idRaw4) & (tCanRxId4)~ MK_RX_RANGE_MASK_IDSTD4(mask)) == MK_RX_RANGE_CODE_IDSTD4(code) ) )
#  define C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDEXT0(mask)) == MK_RX_RANGE_CODE_IDEXT0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDEXT1(mask)) == MK_RX_RANGE_CODE_IDEXT1(code) ) && \
                    ( ((idRaw2) & (tCanRxId2)~ MK_RX_RANGE_MASK_IDEXT2(mask)) == MK_RX_RANGE_CODE_IDEXT2(code) ) && \
                    ( ((idRaw3) & (tCanRxId3)~ MK_RX_RANGE_MASK_IDEXT3(mask)) == MK_RX_RANGE_CODE_IDEXT3(code) ) && \
                    ( ((idRaw4) & (tCanRxId4)~ MK_RX_RANGE_MASK_IDEXT4(mask)) == MK_RX_RANGE_CODE_IDEXT4(code) ) )
# endif
#else /* C_MULTIPLE_RECEIVE_CHANNEL */

# if (kCanNumberOfUsedCanRxIdTables == 1)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH( CAN_RX_IDRAW_PARA, mask, code)    \
                                (  ((idRaw0) & (tCanRxId0)~((mask).Id0)) == ((code).Id0) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 2)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH( CAN_RX_IDRAW_PARA, mask, code)    \
                                ( ( ((idRaw0) & (tCanRxId0)~((mask).Id0)) == ((code).Id0) ) &&\
                                  ( ((idRaw1) & (tCanRxId1)~((mask).Id1)) == ((code).Id1) ) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 3)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH( CAN_RX_IDRAW_PARA, mask, code)    \
                                ( ( ((idRaw0) & (tCanRxId0)~((mask).Id0)) == ((code).Id0) ) &&\
                                  ( ((idRaw1) & (tCanRxId1)~((mask).Id1)) == ((code).Id1) ) &&\
                                  ( ((idRaw2) & (tCanRxId2)~((mask).Id2)) == ((code).Id2) ) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 4)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH( CAN_RX_IDRAW_PARA, mask, code)    \
                                ( ( ((idRaw0) & (tCanRxId0)~((mask).Id0)) == ((code).Id0) ) &&\
                                  ( ((idRaw1) & (tCanRxId1)~((mask).Id1)) == ((code).Id1) ) &&\
                                  ( ((idRaw2) & (tCanRxId2)~((mask).Id2)) == ((code).Id2) ) &&\
                                  ( ((idRaw3) & (tCanRxId3)~((mask).Id3)) == ((code).Id3) ) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 5)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH( CAN_RX_IDRAW_PARA, mask, code)    \
                                ( ( ((idRaw0) & (tCanRxId0)~((mask).Id0)) == ((code).Id0) ) &&\
                                  ( ((idRaw1) & (tCanRxId1)~((mask).Id1)) == ((code).Id1) ) &&\
                                  ( ((idRaw2) & (tCanRxId2)~((mask).Id2)) == ((code).Id2) ) &&\
                                  ( ((idRaw3) & (tCanRxId3)~((mask).Id3)) == ((code).Id3) ) &&\
                                  ( ((idRaw4) & (tCanRxId4)~((mask).Id4)) == ((code).Id4) ) )
# endif
#endif

#if (kCanNumberOfUsedCanRxIdTables == 1)
# define CAN_RX_IDRAW_PARA                                 idRaw0
#endif
#if (kCanNumberOfUsedCanRxIdTables == 2)
# define CAN_RX_IDRAW_PARA                                 idRaw0, idRaw1
#endif
#if (kCanNumberOfUsedCanRxIdTables == 3)
# define CAN_RX_IDRAW_PARA                                 idRaw0, idRaw1, idRaw2
#endif
#if (kCanNumberOfUsedCanRxIdTables == 4)
# define CAN_RX_IDRAW_PARA                                 idRaw0, idRaw1, idRaw2, idRaw3
#endif
#if (kCanNumberOfUsedCanRxIdTables == 5)
# define CAN_RX_IDRAW_PARA                                 idRaw0, idRaw1, idRaw2, idRaw3, idRaw4
#endif

#if defined( C_SINGLE_RECEIVE_CHANNEL )
# define channel                                           ((CanChannelHandle)0)
# define canHwChannel                                      ((CanChannelHandle)0)
# define CAN_HL_HW_CHANNEL_STARTINDEX(channel)             ((CanChannelHandle)0)
# define CAN_HL_HW_CHANNEL_STOPINDEX(channel)              ((CanChannelHandle)0)
# define CAN_HL_MB_MSG_TRANSMIT_INDEX(canHwChannel)        (kCanMailboxMsgTransmitIndex)
# if defined( C_KOMMENTAR_VECTOR_RI14 )
/* ##RI-1.2: Priority of hardware transmit objects */
# endif
# define CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel)           (kCanMailboxTxNormalIndex)

/* Offset which has to be added to change the hardware Tx handle into a logical handle, which is unique over all channels */
/*        Tx-mailbox-Handle - CAN_HL_MB_TX_STARTINDEX(canHwChannel) + CAN_HL_LOG_MB_TX_STARTINDEX(canHwChannel) */
# define CAN_HL_TX_OFFSET_MB_TO_LOG(canHwChannel)          ((vsintx)0-(vsintx)kCanMailboxTxStartIndex)
/* ESCAN00062667 */

# define CAN_HL_TX_STARTINDEX(channel)                     ((CanTransmitHandle)0)
# define CAN_HL_TX_STAT_STARTINDEX(channel)                ((CanTransmitHandle)0)
# define CAN_HL_TX_DYN_ROM_STARTINDEX(channel)             (kCanNumberOfTxStatObjects)
# define CAN_HL_TX_DYN_RAM_STARTINDEX(channel)             ((CanTransmitHandle)0)
/* # define CAN_HL_RX_STARTINDEX(channel)                     ((CanReceiveHandle)0) */
/* index to access the ID tables - Basic index only for linear search
   for hash search this is the start index of the ??? */
# define CAN_HL_RX_BASIC_STARTINDEX(channel)               ((CanReceiveHandle)0)
# define CAN_HL_RX_DYN_RAM_STARTINDEX(channel)             ((CanReceiveHandle)0)
# define CAN_HL_RX_DYN_RAM_BASIC_STARTINDEX(channel)       (kCanNumberOfRxDynFullCANObjects)
# define CAN_HL_RX_DYN_RAM_FULL_STARTINDEX(channel)        ((CanReceiveHandle)0)
# if defined( C_SEARCH_HASH ) || \
     defined( C_SEARCH_INDEX )
#  define CAN_HL_RX_FULL_STARTINDEX(canHwChannel)          ((CanReceiveHandle)0)
#  define CAN_HL_RX_DYN_ROM_STARTINDEX(channel)            (kCanNumberOfRxStatFullCANObjects)
# else
#  define CAN_HL_RX_FULL_STARTINDEX(canHwChannel)          (kCanNumberOfRxBasicCANObjects)
#  define CAN_HL_RX_DYN_ROM_STARTINDEX(channel)            (kCanNumberOfRxStatObjects)
# endif
# define CAN_HL_INIT_OBJ_STARTINDEX(channel)               ((vuint8)0)
# define CAN_HL_LOG_MB_TX_STARTINDEX(canHwChannel)         ((CanObjectHandle)0)
# define CAN_HL_MB_TX_STARTINDEX(canHwChannel)             ((CanObjectHandle)kCanMailboxTxStartIndex)
/* ESCAN00076413 */

# define CAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel)        (kCanMailboxRxFullStartIndex)
# define CAN_HL_MB_RX_FULL_DYN_STARTINDEX(canHwChannel)    (kCanMailboxRxDynFullStartIndex)
# define CAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel)       (kCanMailboxRxBasicStartIndex)
# define CAN_HL_MB_UNUSED_STARTINDEX(canHwChannel)         (kCanMailboxUnusedStartIndex)

# define CAN_HL_TX_STOPINDEX(channel)                      (kCanNumberOfTxObjects)
# define CAN_HL_TX_STAT_STOPINDEX(channel)                 (kCanNumberOfTxStatObjects)
# define CAN_HL_TX_DYN_ROM_STOPINDEX(channel)              (kCanNumberOfTxObjects)
# define CAN_HL_TX_DYN_RAM_STOPINDEX(channel)              (kCanNumberOfTxDynObjects)
/* # define CAN_HL_RX_STOPINDEX(channel)                      (kCanNumberOfRxObjects) */
# define CAN_HL_RX_BASIC_STOPINDEX(channel)                (kCanNumberOfRxBasicCANObjects)
# define CAN_HL_RX_DYN_RAM_STOPINDEX(channel)              (kCanNumberOfRxDynObjects)
# define CAN_HL_RX_DYN_RAM_BASIC_STOPINDEX(channel)        (kCanNumberOfRxDynObjects)
# if defined( C_SEARCH_HASH ) || \
     defined( C_SEARCH_INDEX )
#  define CAN_HL_RX_FULL_STOPINDEX(canHwChannel)           (kCanNumberOfRxFullCANObjects)
# else
#  define CAN_HL_RX_FULL_STOPINDEX(canHwChannel)           (kCanNumberOfRxBasicCANObjects+kCanNumberOfRxFullCANObjects)
# endif
# define CAN_HL_INIT_OBJ_STOPINDEX(channel)                (kCanNumberOfInitObjects)
# define CAN_HL_LOG_MB_TX_STOPINDEX(canHwChannel)          (kCanNumberOfTxMailboxes)
# define CAN_HL_MB_TX_STOPINDEX(canHwChannel)              (kCanMailboxTxStartIndex     +kCanNumberOfTxMailboxes)
# define CAN_HL_MB_RX_FULL_STOPINDEX(canHwChannel)         (kCanMailboxRxFullStartIndex +kCanNumberOfRxFullMailboxes)
# define CAN_HL_MB_RX_BASIC_STOPINDEX(canHwChannel)        (kCanMailboxRxBasicStartIndex+kCanNumberOfRxBasicMailboxes)
# define CAN_HL_MB_UNUSED_STOPINDEX(canHwChannel)          (kCanMailboxUnusedStartIndex +kCanNumberOfUnusedMailboxes)

# define CAN_HL_MB_INDIRECTION_STARTINDEX(canHwChannel)           (kCanHwObjToMailboxIndirectionStartIndex)
# define CAN_HL_MB_TX_INDIRECTION_STARTINDEX(canHwChannel)        (kCanHwObjToMailboxIndirectionTxStartIndex)
# define CAN_HL_MB_RX_FULL_INDIRECTION_STARTINDEX(canHwChannel)   (kCanHwObjToMailboxIndirectionRxFullStartIndex)
# define CAN_HL_MB_RX_BASIC_INDIRECTION_STARTINDEX(canHwChannel)  (kCanHwObjToMailboxIndirectionRxBasicStartIndex)

# define CAN_HL_HW_STARTINDEX(canHwChannel)                (kCanHwObjStartIndex)
# define CAN_HL_HW_TX_STARTINDEX(canHwChannel)             (kCanHwTxStartIndex)
# define CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel)        (kCanHwRxFullStartIndex)
# define CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel)       (kCanHwRxBasicStartIndex)
#else
#  define canHwChannel                                     channel   /* brackets are not allowed here due to compiler error with Renesas HEW compiler for SH2 */
#  define CAN_HL_HW_CHANNEL_STARTINDEX(channel)            (channel)
#  define CAN_HL_HW_CHANNEL_STOPINDEX(channel)             (channel)

# define CAN_HL_MB_MSG_TRANSMIT_INDEX(canHwChannel)       (Can_MailboxMsgTransmitIndex[canHwChannel])
# if defined( C_KOMMENTAR_VECTOR_RI14 )
/* ##RI-1.2: Priority of hardware transmit objects */
# endif
# define CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel)          (Can_MailboxTxNormalIndex[canHwChannel])
/* Offset which has to be added to change the hardware Tx handle into a logical handle, which is unique over all channels */
/*        Tx-mailbox-Handle - CAN_HL_MB_TX_STARTINDEX(canHwChannel) + CAN_HL_LOG_MB_TX_STARTINDEX(canHwChannel) */
# define CAN_HL_TX_OFFSET_MB_TO_LOG(canHwChannel)         (CanTxOffsetMailboxToLog[canHwChannel])

# define CAN_HL_TX_STARTINDEX(channel)                     (CanTxStartIndex[channel])
# define CAN_HL_TX_STAT_STARTINDEX(channel)                (CanTxStartIndex[channel])
# define CAN_HL_TX_DYN_ROM_STARTINDEX(channel)             (CanTxDynRomStartIndex[channel])
# define CAN_HL_TX_DYN_RAM_STARTINDEX(channel)             (CanTxDynRamStartIndex[channel])
/* # define CAN_HL_RX_STARTINDEX(channel)                     (CanRxStartIndex[(channel)]) */
/* index to access the ID tables - Basic index only for linear search */
# define CAN_HL_RX_BASIC_STARTINDEX(channel)               (CanRxBasicStartIndex[channel])
# define CAN_HL_RX_FULL_STARTINDEX(canHwChannel)           (CanRxFullStartIndex[canHwChannel])
# define CAN_HL_RX_DYN_ROM_STARTINDEX(channel)             (CanRxDynRomStart[channel])
# define CAN_HL_RX_DYN_RAM_STARTINDEX(channel)             (CanRxDynRamFullStart[channel])
# define CAN_HL_RX_DYN_RAM_BASIC_STARTINDEX(channel)       (CanRxDynRamBasicStart[channel])
# define CAN_HL_RX_DYN_RAM_FULL_STARTINDEX(channel)        (CanRxDynRamFullStart[channel])
# define CAN_HL_INIT_OBJ_STARTINDEX(channel)               (CanInitObjectStartIndex[channel])
# define CAN_HL_LOG_MB_TX_STARTINDEX(canHwChannel)         (CanLogMailboxTxStartIndex[canHwChannel])
# define CAN_HL_MB_TX_STARTINDEX(canHwChannel)             (Can_MailboxTxStartIndex[canHwChannel])
# define CAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel)        (Can_MailboxRxFullStartIndex[canHwChannel])
# define CAN_HL_MB_RX_FULL_DYN_STARTINDEX(canHwChannel)    (Can_MailboxRxDynFullStartIndex[canHwChannel])
# define CAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel)       (Can_MailboxRxBasicStartIndex[canHwChannel])
# define CAN_HL_MB_UNUSED_STARTINDEX(canHwChannel)         (Can_MailboxUnusedStartIndex[canHwChannel])

# define CAN_HL_TX_STOPINDEX(channel)                      (CanTxStartIndex[(channel) + 1])
# define CAN_HL_TX_STAT_STOPINDEX(channel)                 (CanTxDynRomStartIndex[channel])
# define CAN_HL_TX_DYN_ROM_STOPINDEX(channel)              (CanTxStartIndex[(channel) + 1])
# define CAN_HL_TX_DYN_RAM_STOPINDEX(channel)              (CanTxDynRamStartIndex[(channel) + 1])
/* # define CAN_HL_RX_STOPINDEX(channel)                      (CanRxStartIndex[(channel) + 1]) */
/* index to access the ID tables - Basic index only for linear search */
# define CAN_HL_RX_BASIC_STOPINDEX(channel)                (CanRxFullStartIndex[CAN_HL_HW_CHANNEL_STARTINDEX(channel)])
# if defined( C_KOMMENTAR_VECTOR )
# endif /* C_KOMMENTAR_VECTOR */
# define CAN_HL_RX_DYN_RAM_STOPINDEX(channel)              (CanRxDynRamFullStart[(channel) + 1])
# define CAN_HL_RX_DYN_RAM_BASIC_STOPINDEX(channel)        (CanRxDynRamFullStart[(channel) + 1])
# define CAN_HL_INIT_OBJ_STOPINDEX(channel)                (CanInitObjectStartIndex[(channel) + 1])
# define CAN_HL_LOG_MB_TX_STOPINDEX(canHwChannel)          (CanLogMailboxTxStartIndex[(canHwChannel) +1])
# define CAN_HL_MB_TX_STOPINDEX(canHwChannel)              (Can_MailboxTxStopIndex[canHwChannel])
# define CAN_HL_MB_RX_FULL_STOPINDEX(canHwChannel)         (Can_MailboxRxFullStopIndex[canHwChannel])
# define CAN_HL_MB_RX_BASIC_STOPINDEX(canHwChannel)        (Can_MailboxRxBasicStopIndex[canHwChannel])
# define CAN_HL_MB_UNUSED_STOPINDEX(canHwChannel)          (Can_MailboxUnusedStopIndex[canHwChannel])

# define CAN_HL_MB_INDIRECTION_STARTINDEX(canHwChannel)          (Can_HwObjToMailboxIndirectionStartIndex[canHwChannel])
# define CAN_HL_MB_TX_INDIRECTION_STARTINDEX(canHwChannel)       (Can_HwObjToMailboxIndirectionTxStartIndex[canHwChannel])
# define CAN_HL_MB_RX_FULL_INDIRECTION_STARTINDEX(canHwChannel)  (Can_HwObjToMailboxIndirectionRxFullStartIndex[canHwChannel])
# define CAN_HL_MB_RX_BASIC_INDIRECTION_STARTINDEX(canHwChannel) (Can_HwObjToMailboxIndirectionRxBasicStartIndex[canHwChannel])

# define CAN_HL_HW_STARTINDEX(canHwChannel)                (Can_HwObjStartIndex[canHwChannel])
# define CAN_HL_HW_TX_STARTINDEX(canHwChannel)             (Can_HwTxStartIndex[canHwChannel])
# define CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel)        (Can_HwRxFullStartIndex[canHwChannel])
# define CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel)       (Can_HwRxBasicStartIndex[canHwChannel])
#endif

#if defined( C_SINGLE_RECEIVE_CHANNEL )

# define CANRANGE0ACCMASK(i)                               C_RANGE0_ACC_MASK
# define CANRANGE0ACCCODE(i)                               C_RANGE0_ACC_CODE
# define CANRANGE1ACCMASK(i)                               C_RANGE1_ACC_MASK
# define CANRANGE1ACCCODE(i)                               C_RANGE1_ACC_CODE
# define CANRANGE2ACCMASK(i)                               C_RANGE2_ACC_MASK
# define CANRANGE2ACCCODE(i)                               C_RANGE2_ACC_CODE
# define CANRANGE3ACCMASK(i)                               C_RANGE3_ACC_MASK
# define CANRANGE3ACCCODE(i)                               C_RANGE3_ACC_CODE

# define APPL_CAN_MSG_RECEIVED( i )                        (APPL_CAN_MSGRECEIVED( i ))

# define APPLCANRANGE0PRECOPY( i )                         (ApplCanRange0Precopy( i ))
# define APPLCANRANGE1PRECOPY( i )                         (ApplCanRange1Precopy( i ))
# define APPLCANRANGE2PRECOPY( i )                         (ApplCanRange2Precopy( i ))
# define APPLCANRANGE3PRECOPY( i )                         (ApplCanRange3Precopy( i ))

# define APPL_CAN_BUSOFF( i )                              (ApplCanBusOff())
# define APPL_CAN_WAKEUP( i )                              (ApplCanWakeUp())

# if defined( C_KOMMENTAR_VECTOR_LI13 )
/* ##LI-: 1.2    CAN-Offline */
# endif
# if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
#  define APPLCANCANCELNOTIFICATION( i, j )                (APPL_CAN_CANCELNOTIFICATION( j ))
# else
#  define APPLCANCANCELNOTIFICATION( i, j )
# endif
# if defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
#  define APPLCANMSGCANCELNOTIFICATION( i )                (APPL_CAN_MSGCANCELNOTIFICATION())
# else
#  define APPLCANMSGCANCELNOTIFICATION( i )
# endif

# define CAN_RX_INDEX_TBL(channel, id)                      (CanRxIndexTbl[id])

#else

# define CANRANGE0ACCMASK(i)                               (CanChannelObject[i].RangeMask[0])
# define CANRANGE0ACCCODE(i)                               (CanChannelObject[i].RangeCode[0])
# define CANRANGE1ACCMASK(i)                               (CanChannelObject[i].RangeMask[1])
# define CANRANGE1ACCCODE(i)                               (CanChannelObject[i].RangeCode[1])
# define CANRANGE2ACCMASK(i)                               (CanChannelObject[i].RangeMask[2])
# define CANRANGE2ACCCODE(i)                               (CanChannelObject[i].RangeCode[2])
# define CANRANGE3ACCMASK(i)                               (CanChannelObject[i].RangeMask[3])
# define CANRANGE3ACCCODE(i)                               (CanChannelObject[i].RangeCode[3])

/* generated id type of the range */
# define CANRANGE0IDTYPE(i)                                (CanChannelObject[i].RangeIdType[0])
# define CANRANGE1IDTYPE(i)                                (CanChannelObject[i].RangeIdType[1])
# define CANRANGE2IDTYPE(i)                                (CanChannelObject[i].RangeIdType[2])
# define CANRANGE3IDTYPE(i)                                (CanChannelObject[i].RangeIdType[3])

# define APPL_CAN_MSG_RECEIVED( i )                        (CanChannelObject[(i)->Channel].ApplCanMsgReceivedFct(i))

# define APPLCANRANGE0PRECOPY( i )                         (CanChannelObject[(i)->Channel].ApplCanRangeFct[0](i))
# define APPLCANRANGE1PRECOPY( i )                         (CanChannelObject[(i)->Channel].ApplCanRangeFct[1](i))
# define APPLCANRANGE2PRECOPY( i )                         (CanChannelObject[(i)->Channel].ApplCanRangeFct[2](i))
# define APPLCANRANGE3PRECOPY( i )                         (CanChannelObject[(i)->Channel].ApplCanRangeFct[3](i))

# define APPL_CAN_BUSOFF( i )                              (CanChannelObject[i].ApplCanBusOffFct(i))
# define APPL_CAN_WAKEUP( i )                              (CanChannelObject[i].ApplCanWakeUpFct(i))

# if defined( C_KOMMENTAR_VECTOR_LI13 )
/* ##LI-: 1.2    CAN-Offline */
# endif
# if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
#  define APPLCANCANCELNOTIFICATION( i, j )                (CanChannelObject[i].ApplCanCancelNotificationFct( j ))
# else
#  define APPLCANCANCELNOTIFICATION( i, j )
# endif

# if defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
#  define APPLCANMSGCANCELNOTIFICATION( i )                (CanChannelObject[i].ApplCanMsgTransmitCancelNotifyFct( i ))
# else
#  define APPLCANMSGCANCELNOTIFICATION( i )
# endif

# define CAN_RX_INDEX_TBL(channel, id)                     (CanRxIndexTbl[channel][id])

#endif

#if defined ( C_ENABLE_CAN_CAN_INTERRUPT_CONTROL )
# define CAN_CAN_INTERRUPT_DISABLE(channel)                (CanCanInterruptDisable(CAN_CHANNEL_CANPARA_ONLY))
# define CAN_CAN_INTERRUPT_RESTORE(channel)                (CanCanInterruptRestore(CAN_CHANNEL_CANPARA_ONLY))
#else
# define CAN_CAN_INTERRUPT_DISABLE(channel)
# define CAN_CAN_INTERRUPT_RESTORE(channel)
#endif

/* mask for range enable status */
#define kCanRange0                                         ((vuint16)1)
#define kCanRange1                                         ((vuint16)2)
#define kCanRange2                                         ((vuint16)4)
#define kCanRange3                                         ((vuint16)8)

/* derive RxDataLen for DLC check and Datacopying according the configuration */
# define CanGetDerivedRxDataLen(rxHandle)                  (CanGetRxDataLen(rxHandle))

/* Assertions ---------------------------------------------------------------- */
/* lint -function(exit, ApplCanFatalError) */

/* lint -emacro( (506), assertUser) */
#if defined( C_ENABLE_USER_CHECK )
# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define assertUser(p, c, e)                              if (!(p))   {ApplCanFatalError(e);}
# else
#  define assertUser(p, c, e)                              if (!(p))   {ApplCanFatalError((c), (e));}
# endif
#else
# define assertUser(p, c, e)
#endif

/* lint -emacro( (506), assertGen) */
#if defined( C_ENABLE_GEN_CHECK )
# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define assertGen(p, c, e)                               if (!(p))   {ApplCanFatalError(e);}
# else
#  define assertGen(p, c, e)                               if (!(p))   {ApplCanFatalError((c), (e));}
# endif
#else
# define assertGen(p, c, e)
#endif

/* lint -emacro( (506), assertHardware) */
#if defined( C_ENABLE_HARDWARE_CHECK )
# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define assertHardware(p, c, e)                          if (!(p))   {ApplCanFatalError(e);}
# else
#  define assertHardware(p, c, e)                          if (!(p))   {ApplCanFatalError((c), (e));}
# endif
#else
# define assertHardware(p, c, e)
#endif

/* lint -emacro( (506), assertInternal) */
#if defined( C_ENABLE_INTERNAL_CHECK )
# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define assertInternal(p, c, e)                          if (!(p))   {ApplCanFatalError(e);}
# else
#  define assertInternal(p, c, e)                          if (!(p))   {ApplCanFatalError((c), (e));}
# endif
#else
# define assertInternal(p, c, e)
#endif

#if !defined( CAN_DUMMY_STATEMENT )
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )
#  define CAN_DUMMY_STATEMENT(x)                           (x) = (x)
# else
#  define CAN_DUMMY_STATEMENT(x)
# endif
#endif
#if defined( C_SINGLE_RECEIVE_CHANNEL )
# define CAN_CHANNEL_DUMMY_STATEMENT
# define CAN_HW_CHANNEL_DUMMY_STATEMENT
# define CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT
#else
# define CAN_CHANNEL_DUMMY_STATEMENT                       CAN_DUMMY_STATEMENT(channel)
# define CAN_HW_CHANNEL_DUMMY_STATEMENT                    CAN_DUMMY_STATEMENT(canHwChannel)
#  define CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT       CAN_DUMMY_STATEMENT(channel)
#endif

#if defined( C_ENABLE_TRANSMIT_QUEUE )
#if defined( C_CPUTYPE_32BIT )
# define kCanTxQueueShift     5
#endif

/* mask used to get the flag index from the handle */
# define kCanTxQueueMask      (((vuint8)1 << kCanTxQueueShift) - (vuint8)1)

#if defined( C_SINGLE_RECEIVE_CHANNEL )
# define CAN_HL_TXQUEUE_PADBITS(channel)             ((CanTransmitHandle)0)
# define CAN_HL_TXQUEUE_STARTINDEX(channel)          ((CanSignedTxHandle)0)
# define CAN_HL_TXQUEUE_STOPINDEX(channel)           ((CanSignedTxHandle)kCanTxQueueSize)
#else
# define CAN_HL_TXQUEUE_PADBITS(channel)             ((CanTransmitHandle)CanTxQueuePadBits[(channel)])
# define CAN_HL_TXQUEUE_STARTINDEX(channel)          (CanTxQueueStartIndex[(channel)])
# define CAN_HL_TXQUEUE_STOPINDEX(channel)           (CanTxQueueStartIndex[(channel) + (CanChannelHandle)1])
#endif

#endif

#if defined(C_ENABLE_HW_LOOP_TIMER)
# define CanHL_ApplCanTimerStart(loop)   ApplCanTimerStart(CAN_CHANNEL_CANPARA_FIRST (loop))
# define CanHL_ApplCanTimerLoop(loop)    if (ApplCanTimerLoop(CAN_CHANNEL_CANPARA_FIRST (loop)) == 0) { break; }
# define CanHL_ApplCanTimerEnd(loop)     ApplCanTimerEnd(CAN_CHANNEL_CANPARA_FIRST (loop))
#else
# define CanHL_ApplCanTimerStart(loop)
# define CanHL_ApplCanTimerLoop(loop)
# define CanHL_ApplCanTimerEnd(loop)
# endif

/* Compatibility macros for LL--------------------------------------------------------- */
# if defined( C_ENABLE_ACCESS_PROTECTED_REG_BY_APPL )
#  define CAN_WRITE_PROTECTED_REG8(area, regPtr, val)          ApplCanWriteProtectedRegister8((regPtr), (vuint8)0xFFu, (val))
#  define CAN_WRITE_PROTECTED_REG16(area, regPtr, val)         ApplCanWriteProtectedRegister16((regPtr), (vuint16)0xFFFFu, (val))
#  define CAN_WRITE_PROTECTED_REG32(area, regPtr, val)         ApplCanWriteProtectedRegister32((regPtr), (vuint32)0xFFFFFFFFUL, (val))
#  define CAN_WRITE_PROTECTED_REG8_RESET(area, regPtr, bits)   ApplCanWriteProtectedRegister8((regPtr), (bits), (vuint8)0x00u)
#  define CAN_WRITE_PROTECTED_REG16_RESET(area, regPtr, bits)  ApplCanWriteProtectedRegister16((regPtr), (bits), (vuint16)0x0000u)
#  define CAN_WRITE_PROTECTED_REG32_RESET(area, regPtr, bits)  ApplCanWriteProtectedRegister32((regPtr), (bits), (vuint32)0x00000000UL)
#  define CAN_WRITE_PROTECTED_REG8_SET(area, regPtr, bits)     ApplCanWriteProtectedRegister8((regPtr), (bits), (bits))
#  define CAN_WRITE_PROTECTED_REG16_SET(area, regPtr, bits)    ApplCanWriteProtectedRegister16((regPtr), (bits), (bits))
#  define CAN_WRITE_PROTECTED_REG32_SET(area, regPtr, bits)    ApplCanWriteProtectedRegister32((regPtr), (bits), (bits))
#  define CAN_READ_PROTECTED_REG8(area, regPtr)                ApplCanReadProtectedRegister8((regPtr))
#  define CAN_READ_PROTECTED_REG16(area, regPtr)               ApplCanReadProtectedRegister16((regPtr))
#  define CAN_READ_PROTECTED_REG32(area, regPtr)               ApplCanReadProtectedRegister32((regPtr))
# else
#  define CAN_WRITE_PROTECTED_REG8(area, regPtr, val)          *(regPtr) = (val)
#  define CAN_WRITE_PROTECTED_REG16(area, regPtr, val)         *(regPtr) = (val)
#  define CAN_WRITE_PROTECTED_REG32(area, regPtr, val)         *(regPtr) = (val)
#  define CAN_WRITE_PROTECTED_REG8_RESET(area, regPtr, bits)   *(regPtr) &= (vuint8)~(bits)
#  define CAN_WRITE_PROTECTED_REG16_RESET(area, regPtr, bits)  *(regPtr) &= (vuint16)~(bits)
#  define CAN_WRITE_PROTECTED_REG32_RESET(area, regPtr, bits)  *(regPtr) &= (vuint32)~(bits)
#  define CAN_WRITE_PROTECTED_REG8_SET(area, regPtr, bits)     *(regPtr) |= (bits)
#  define CAN_WRITE_PROTECTED_REG16_SET(area, regPtr, bits)    *(regPtr) |= (bits)
#  define CAN_WRITE_PROTECTED_REG32_SET(area, regPtr, bits)    *(regPtr) |= (bits)
#  define CAN_READ_PROTECTED_REG8(area, regPtr)                *(regPtr)
#  define CAN_READ_PROTECTED_REG16(area, regPtr)               *(regPtr)
#  define CAN_READ_PROTECTED_REG32(area, regPtr)               *(regPtr)
# endif

#define CanHL_WriteReg8(ch, regPtr, val, readMask)                    *(regPtr) = (val)
#define CanHL_WriteReg16(ch, regPtr, val, readMask)                   *(regPtr) = (val)
#define CanHL_WriteReg32(ch, regPtr, val, readMask)                   *(regPtr) = (val)
# define CanHL_WriteProtectedReg8(ch, area, regPtr, val, readMask)    CAN_WRITE_PROTECTED_REG8(area, regPtr, val)
# define CanHL_WriteProtectedReg16(ch, area, regPtr, val, readMask)   CAN_WRITE_PROTECTED_REG16(area, regPtr, val)
# define CanHL_WriteProtectedReg32(ch, area, regPtr, val, readMask)   CAN_WRITE_PROTECTED_REG32(area, regPtr, val)

#if defined( C_ENABLE_CAN_FD_USED )
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
#  define CAN_HL_IS_CH_CANFD(channel)        ((CanFdUsage[channel] != C_CAN_FD_NONE) ? kCanTrue : kCanFalse)
# else
#  define CAN_HL_IS_CH_CANFD(channel)        kCanTrue
# endif
#endif
#if defined( C_ENABLE_CAN_FD_FULL )
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
#  define CAN_HL_IS_CH_CANFD_FULL(channel)   ((CanFdUsage[channel] == C_CAN_FD_MODE2) ? kCanTrue : kCanFalse)
# else
#  define CAN_HL_IS_CH_CANFD_FULL(channel)   kCanTrue
# endif
#endif

#if defined( C_ENABLE_CAN_FD_FULL )
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
#  define CAN_HL_MAX_LEN(channel)            ((CAN_HL_IS_CH_CANFD_FULL(channel) == kCanTrue) ? (vuint8)64 : (vuint8)8)
# else
#  define CAN_HL_MAX_LEN(channel)            (vuint8)64
# endif
#else
# define CAN_HL_MAX_LEN(channel)             (vuint8)8
#endif

#if !defined( C_CAN_FD_PADDING_VALUE )
# define C_CAN_FD_PADDING_VALUE              0x00u
#endif

#if defined( C_ENABLE_HW_LOOP_TIMER )
# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define   APPLCANTIMERSTART(x)   ApplCanTimerStart(x)
#  define   APPLCANTIMERLOOP(x)    ApplCanTimerLoop(x)
#  define   APPLCANTIMEREND(x)     ApplCanTimerEnd(x)
# else
#  define   APPLCANTIMERSTART(x)   ApplCanTimerStart(channel, (x))
#  define   APPLCANTIMERLOOP(x)    ApplCanTimerLoop(channel, (x))
#  define   APPLCANTIMEREND(x)     ApplCanTimerEnd(channel, (x))
# endif
#else
# define   APPLCANTIMERSTART(x)
# define   APPLCANTIMERLOOP(x)     (vuint8)(1)
# define   APPLCANTIMEREND(x)
#endif

#if defined ( C_ENABLE_USER_MODE_APPL )
# define CAN_WRITE_PROTECTED_REG(reg, val)              ApplCanWriteProtectedRegister(&(reg), (vuint16)0xFFFFu, (val))
# define CAN_WRITE_PROTECTED_REG_RESET(reg, bits)       ApplCanWriteProtectedRegister(&(reg), (bits), (vuint16)0x0000u)
# define CAN_WRITE_PROTECTED_REG_SET(reg, bits)         ApplCanWriteProtectedRegister(&(reg), (bits), (bits))
# define CAN_READ_PROTECTED_REG(reg)                    ApplCanReadProtectedRegister(&(reg))
# define CAN_WRITE_PROTECTED_REG_RESET_32BIT(reg, bits) ApplCanWriteProtectedRegister32(&(reg), (bits), (vuint32)0x00000000u)
# define CAN_WRITE_PROTECTED_REG_SET_32BIT(reg, bits)   ApplCanWriteProtectedRegister32(&(reg), (bits), (bits))
# define CAN_READ_PROTECTED_REG_32BIT(reg)              ApplCanReadProtectedRegister32(&(reg))
#else
# define CAN_WRITE_PROTECTED_REG(reg, val)              (reg) = (val)
# define CAN_WRITE_PROTECTED_REG_RESET(reg, bits)       (reg) &= (vuint16)(~(bits))
# define CAN_WRITE_PROTECTED_REG_SET(reg, bits)         (reg) |= (bits)
# define CAN_READ_PROTECTED_REG(reg)                    (reg)
# define CAN_WRITE_PROTECTED_REG_RESET_32BIT(reg, bits) (reg) &= (vuint32)(~(bits))
# define CAN_WRITE_PROTECTED_REG_SET_32BIT(reg, bits)   (reg) |= (bits)
# define CAN_READ_PROTECTED_REG_32BIT(reg)              (reg)
#endif

  /* dummy area */
# define CAN_AREA(ch) 0

#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
    defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
    defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )

# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )

//#  define   CAN_DISABLE_RXTX_INTERRUPT_0TO31(canFlagPtr) (canFlagPtr)->flags1 = pFlexcan->imask1; pFlexcan->imask1 = 0
//#  define   CAN_RESTORE_RXTX_INTERRUPT_0TO31(canFlag)    pFlexcan->imask1 = (canFlag).flags1

#  if defined ( C_ENABLE_MB32TO63 )
#   define   CAN_DISABLE_RXTX_INTERRUPT_32TO63(canFlagPtr) (canFlagPtr)->flags2 = pFlexcan->imask2; pFlexcan->imask2 = 0
#   define   CAN_RESTORE_RXTX_INTERRUPT_32TO63(canFlag)    pFlexcan->imask2 = (canFlag).flags2
#  else
#   define   CAN_DISABLE_RXTX_INTERRUPT_32TO63(canFlagPtr)
#   define   CAN_RESTORE_RXTX_INTERRUPT_32TO63(canFlag)
#  endif

#  if defined ( C_ENABLE_MB64TO95 )
#   define   CAN_DISABLE_RXTX_INTERRUPT_64TO95(canFlagPtr) (canFlagPtr)->flags3 = pFlexcan->imask3; pFlexcan->imask3 = 0
#   define   CAN_RESTORE_RXTX_INTERRUPT_64TO95(canFlag)    pFlexcan->imask3 = (canFlag).flags3
#  else
#   define   CAN_DISABLE_RXTX_INTERRUPT_64TO95(canFlagPtr)
#   define   CAN_RESTORE_RXTX_INTERRUPT_64TO95(canFlag)
#  endif

#  if defined ( C_ENABLE_MB96TO127 )
#   define   CAN_DISABLE_RXTX_INTERRUPT_96TO127(canFlagPtr) (canFlagPtr)->flags4 = pFlexcan->imask4; pFlexcan->imask4 = 0
#   define   CAN_RESTORE_RXTX_INTERRUPT_96TO127(canFlag)    pFlexcan->imask4 = (canFlag).flags4
#  else
#   define   CAN_DISABLE_RXTX_INTERRUPT_96TO127(canFlagPtr)
#   define   CAN_RESTORE_RXTX_INTERRUPT_96TO127(canFlag)
#  endif
# else
#  define   CAN_DISABLE_RXTX_INTERRUPT_0TO31(canFlagPtr)
#  define   CAN_RESTORE_RXTX_INTERRUPT_0TO31(canFlag)
#  define   CAN_DISABLE_RXTX_INTERRUPT_32TO63(canFlagPtr)
#  define   CAN_RESTORE_RXTX_INTERRUPT_32TO63(canFlag)
#  define   CAN_DISABLE_RXTX_INTERRUPT_64TO95(canFlagPtr)
#  define   CAN_RESTORE_RXTX_INTERRUPT_64TO95(canFlag)
#  define   CAN_DISABLE_RXTX_INTERRUPT_96TO127(canFlagPtr)
#  define   CAN_RESTORE_RXTX_INTERRUPT_96TO127(canFlag)
# endif

# if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
//HYT #  define CAN_DISABLE_BUSOFF_INTERRUPT(canFlagPtr)  (canFlagPtr)->canctrl1 = pFlexcan->control1; pFlexcan->control1 &= kNotFlexCANErrBoff
//HYT #  define CAN_RESTORE_BUSOFF_INTERRUPT(canFlag)     pFlexcan->control1 |= (vuint32)((canFlag).canctrl1 & (vuint32)(~kNotFlexCANErrBoff))
# else
#  define CAN_DISABLE_BUSOFF_INTERRUPT(canFlagPtr)
#  define CAN_RESTORE_BUSOFF_INTERRUPT(canFlag)
# endif
# if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
#  define CAN_DISABLE_WAKEUP_INTERRUPT(canFlagPtr)  (canFlagPtr)->canmcr = CAN_READ_PROTECTED_REG(pFlexcan->canmcr); CAN_WRITE_PROTECTED_REG_RESET(pFlexcan->canmcr, kFlexCAN_WAK_MSK)
#  define CAN_RESTORE_WAKEUP_INTERRUPT(canFlag)     CAN_WRITE_PROTECTED_REG_SET(pFlexcan->canmcr, (vuint16)((canFlag).canmcr & kFlexCAN_WAK_MSK))
# else
#  define CAN_DISABLE_WAKEUP_INTERRUPT(canFlagPtr)
#  define CAN_RESTORE_WAKEUP_INTERRUPT(canFlag)
# endif

#else
# define CanLL_CanInterruptDisable(x,y)
# define CanLL_CanInterruptRestore(x,y)
#endif   /* C_ENABLE_CAN_..._INTERRUPT */

# define CanLL_TxIsObjFree(canHwChannel, txObjHandle) ((GLOBAL_MAILBOX_ACCESS((canHwChannel), (txObjHandle), control) & kCodeMask) == kTxCodeFree)

#if defined( C_ENABLE_FLEXCAN_STOP_MODE )
# define CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY)  ((CAN_READ_PROTECTED_REG((pFlexCAN(canHwChannel))->canmcr) & kFlexCAN_MCR) == kFlexCAN_STOP_MODE)
#else
//# define CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY)  ((CAN_READ_PROTECTED_REG((pFlexCAN(canHwChannel))->canmcr) & kFlexCAN_MCR) == kFlexCAN_DISABLE_MODE)
#endif

//#define CanLL_HwIsStop(CAN_HW_CHANNEL_CANPARA_ONLY) ((CAN_READ_PROTECTED_REG((pFlexCAN(canHwChannel))->canmcr) & kFlexCAN_MCR) == kFlexCAN_FREEZE_MODE)

//#define CanLL_HwIsBusOff(CAN_HW_CHANNEL_CANPARA_ONLY) (((pFlexCAN(canHwChannel))->estat & kFlexCAN_FCS_BOFF) != 0)

#if defined( C_ENABLE_EXTENDED_STATUS )
#  define CanLL_HwIsPassive(CAN_HW_CHANNEL_CANPARA_ONLY) (((pFlexCAN(canHwChannel))->estat & kFlexCAN_FCS) == kFlexCAN_FCS_EP)
#  define CanLL_HwIsWarning(CAN_HW_CHANNEL_CANPARA_ONLY) (((pFlexCAN(canHwChannel))->estat & kFlexCAN_RXTX_WARN) != 0)
#endif /* C_ENABLE_EXTENDED_STATUS */

# define CAN_WAKEUP(channel)   (void)CanWakeUp( CAN_CHANNEL_CANPARA_ONLY )

# if defined ( C_ENABLE_TX_FULLCAN_DELAYED_START )
#  define CanGetMailboxDelayed(canHwChannel,hwobject)    (((canLL_canDelayedFullCANTxRequest[canHwChannel][(vuint8)(hwobject >>5)] >> ((vuint32)(hwobject & 0x001Fu))) & ((vuint32) 1)) == 1)
#  define CanSetMailboxDelayed(canHwChannel,hwobject)      (canLL_canDelayedFullCANTxRequest[canHwChannel][(vuint8)(hwobject >>5)] |=  (vuint32)(((vuint32) 1) << (vuint32)(hwobject & 0x001Fu)))
#  define CanClearMailboxDelayed(canHwChannel,hwobject)    (canLL_canDelayedFullCANTxRequest[canHwChannel][(vuint8)(hwobject >>5)] &= (vuint32)~(((vuint32) 1) << (vuint32)(hwobject & 0x001Fu)))
# endif

/* *********************************************************************** */
/* Defines / data types / structs / unions                                 */
/* *********************************************************************** */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
#endif

/* Define CAN Chip hardware; segment must be located in locator file    */
/* register layout of the can chip                                      */
/* Structure describing CAN receive buffer. */

typedef struct
{
  CanInitHandle            initObject;
  CanObjectHandle          mailboxHandle;
  CanObjectHandle          hwObjHandle;
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
  tCanRxId0                idRaw0;
# if( kCanNumberOfUsedCanRxIdTables > 1 )
  tCanRxId1                idRaw1;
# endif
# if( kCanNumberOfUsedCanRxIdTables > 2 )
  tCanRxId2                idRaw2;
# endif
# if( kCanNumberOfUsedCanRxIdTables > 3 )
  tCanRxId3                idRaw3;
# endif
# if( kCanNumberOfUsedCanRxIdTables > 4 )
  tCanRxId4                idRaw4;
# endif
  tCanIdType               idType;
#endif
  vuint8                   isInitOk;
} tCanInitInfoStruct;
typedef tCanInitInfoStruct *CanInitInfoStructPtr;

#if defined( C_ENABLE_CAN_TRANSMIT )
typedef struct
{
  CanObjectHandle          mailboxHandle;
  CanObjectHandle          hwObjHandle;
  CanObjectHandle          logTxObjHandle;
  tCanTxId0                idRaw0;
#if( kCanNumberOfUsedCanTxIdTables > 1 )
  tCanTxId1                idRaw1;
#endif
#if( kCanNumberOfUsedCanTxIdTables > 2 )
  tCanTxId2                idRaw2;
#endif
#if( kCanNumberOfUsedCanTxIdTables > 3 )
  tCanTxId3                idRaw3;
#endif
#if( kCanNumberOfUsedCanTxIdTables > 4 )
  tCanTxId4                idRaw4;
#endif
#if defined( C_ENABLE_MIXED_ID )
  tCanIdType               idType;
#endif
  tCanDlc                  dlcRaw;
#if defined( C_ENABLE_PRETRANSMIT_FCT )
  CanTxInfoStruct          txStruct;
#endif
#if defined( C_ENABLE_COPY_TX_DATA )
  TxDataPtr                CanMemCopySrcPtr;
#endif
#if defined( C_ENABLE_CAN_FD_USED )
  tCanFdType               fdType;
  tCanFdBrsType            fdBrsType;
#endif
#if defined( C_ENABLE_CAN_FD_FULL ) && defined( C_ENABLE_COPY_TX_DATA )
  vuint8                   messageLen;
  vuint8                   frameLen;
  vuint8                   paddingVal;
#endif
} tCanTxTransmissionInfoStruct;
typedef tCanTxTransmissionInfoStruct *CanTxTransmissionInfoStructPtr;
#endif

#if defined( C_ENABLE_MSG_TRANSMIT )
typedef struct
{
  CanObjectHandle          mailboxHandle;
  CanObjectHandle          hwObjHandle;
  CanObjectHandle          logTxObjHandle;
  CanMsgTransmitStructPtr  txMsgStruct;
} tCanTxMsgTransmissionInfoStruct;
typedef tCanTxMsgTransmissionInfoStruct *CanTxMsgTransmissionInfoStructPtr;
#endif

#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
typedef struct
{
  CanObjectHandle          mailboxHandle;
  CanObjectHandle          hwObjHandle;
  CanChipMsgPtr            pChipMsgObj;
  CanChipDataPtr           pChipData;
#if defined( C_ENABLE_OVERRUN )
  vuint8                   isOverrun;
#endif
} tCanRxBasicInfoStruct;
typedef tCanRxBasicInfoStruct *CanRxBasicInfoStructPtr;
#endif

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
typedef struct
{
  CanObjectHandle          mailboxHandle;
  CanObjectHandle          hwObjHandle;
  CanChipMsgPtr            pChipMsgObj;
  CanChipDataPtr           pChipData;
#if defined( C_ENABLE_FULLCAN_OVERRUN )
  vuint8                   isOverrun;
#endif
} tCanRxFullInfoStruct;
typedef tCanRxFullInfoStruct *CanRxFullInfoStructPtr;
#endif

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )  || \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
typedef struct
{
  RxDataPtr                dest;
  CanChipDataPtr           src;
  vuint8                   len;
} tCanRxCopyInfoStruct;
typedef tCanRxCopyInfoStruct *CanRxCopyInfoStructPtr;
#endif

#if defined( C_ENABLE_RX_QUEUE )
typedef struct
{
  CanMsgTransmitStructPtr  dest;
  CanRxInfoStructPtr       src;
} tCanRxQueueCopyInfoStruct;
typedef tCanRxQueueCopyInfoStruct *CanRxQueueCopyInfoStructPtr;

typedef struct
{
  tCanRxInfoStruct         localCanRxInfoStruct;
} tCanRxQueueRxInfoStruct;
typedef tCanRxQueueRxInfoStruct *CanRxQueueRxInfoStructPtr;
#endif

#if defined( C_ENABLE_CANCEL_IN_HW )
typedef struct
{
  CanObjectHandle          mailboxHandle;
  CanObjectHandle          hwObjHandle;
  CanObjectHandle          logTxObjHandle;
  CanTransmitHandle        canHandleCurTxObj; /* PRQA S 0781 */ /* MD_Can_0781 */
} tCanTxCancellationInfoStruct;
typedef tCanTxCancellationInfoStruct *CanTxCancellationInfoStructPtr;
#endif

typedef struct
{
  CanObjectHandle          mailboxHandle;
  CanObjectHandle          hwObjHandle;
  CanObjectHandle          logTxObjHandle;
#if defined( C_ENABLE_CAN_TX_CONF_FCT ) || defined( C_ENABLE_CAN_TX_CONF_MSG_ACCESS )
  CanTxInfoStructPtr       txInfoStructConf;
#endif
} tCanTxConfirmationInfoStruct;
typedef tCanTxConfirmationInfoStruct *CanTxConfirmationInfoStructPtr;

#if defined( C_ENABLE_TX_POLLING ) || \
    (defined( C_ENABLE_RX_FULLCAN_OBJECTS ) &&  defined( C_ENABLE_RX_FULLCAN_POLLING )) || \
    (defined( C_ENABLE_RX_BASICCAN_POLLING ) &&  defined( C_ENABLE_RX_BASICCAN_OBJECTS ))
typedef struct
{
  CanObjectHandle          mailboxHandle;
  CanObjectHandle          hwObjHandle;
} tCanTaskInfoStruct;
typedef tCanTaskInfoStruct *CanTaskInfoStructPtr;
#endif

/* *********************************************************************** */
/* Constants                                                               */
/* *********************************************************************** */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
/* ROM CATEGORY 1 START */
/* lookup table for setting the flags in the queue */
/* PRQA  S 1281 QAC_Can_1281 */ /* MD_Can_1281 */
V_MEMROM0 static V_MEMROM1 tCanQueueElementType V_MEMROM2 CanShiftLookUp[1 << kCanTxQueueShift] =
{
#if defined( C_CPUTYPE_32BIT )
   (tCanQueueElementType)0x00000001, (tCanQueueElementType)0x00000002, (tCanQueueElementType)0x00000004, (tCanQueueElementType)0x00000008,
   (tCanQueueElementType)0x00000010, (tCanQueueElementType)0x00000020, (tCanQueueElementType)0x00000040, (tCanQueueElementType)0x00000080
#endif

#if defined( C_CPUTYPE_32BIT )
 , (tCanQueueElementType)0x00000100, (tCanQueueElementType)0x00000200, (tCanQueueElementType)0x00000400, (tCanQueueElementType)0x00000800,
   (tCanQueueElementType)0x00001000, (tCanQueueElementType)0x00002000, (tCanQueueElementType)0x00004000, (tCanQueueElementType)0x00008000
#endif

#if defined( C_CPUTYPE_32BIT )
 , (tCanQueueElementType)0x00010000, (tCanQueueElementType)0x00020000, (tCanQueueElementType)0x00040000, (tCanQueueElementType)0x00080000,
   (tCanQueueElementType)0x00100000, (tCanQueueElementType)0x00200000, (tCanQueueElementType)0x00400000, (tCanQueueElementType)0x00800000,
   (tCanQueueElementType)0x01000000, (tCanQueueElementType)0x02000000, (tCanQueueElementType)0x04000000, (tCanQueueElementType)0x08000000,
   (tCanQueueElementType)0x10000000, (tCanQueueElementType)0x20000000, (tCanQueueElementType)0x40000000, (tCanQueueElementType)0x80000000
#endif
};
/* PRQA  L:QAC_Can_1281 */

/* returns the highest pending flag from the lower nibble */
V_MEMROM0 static V_MEMROM1 vsint8 V_MEMROM2 CanGetHighestFlagFromNibble[16] =        /* PRQA S 3218 */ /* MD_Can_3218 */
{
  (vsint8)-1,                /* (vsint8)0xFF - changed due to misra; cast due to R32C */
  0x00,
  0x01, 0x01,
  0x02, 0x02, 0x02, 0x02,
  0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03
};
/* ROM CATEGORY 1 END */
#endif

#if defined(C_ENABLE_CAN_FD_FULL)
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanDlcToFrameLenght[16] =
{
  /* 00..07 */  0,  1,  2,  3,  4,  5,  6,  7,
  /* 08..15 */  8, 12, 16, 20, 24, 32, 48, 64
};

V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanMessageLengthToDlc[65] =
{
  /* 00..07 */  0,  1,  2,  3,  4,  5,  6,  7,
  /* 08..15 */  8,  9,  9,  9,  9, 10, 10, 10,
  /* 16..23 */ 10, 11, 11, 11, 11, 12, 12, 12,
  /* 24..31 */ 12, 13, 13, 13, 13, 13, 13, 13,
  /* 32..39 */ 13, 14, 14, 14, 14, 14, 14, 14,
  /* 40..47 */ 14, 14, 14, 14, 14, 14, 14, 14,
  /* 48..55 */ 14, 15, 15, 15, 15, 15, 15, 15,
  /* 56..63 */ 15, 15, 15, 15, 15, 15, 15, 15,
  /* 64     */ 15
};
#endif

/* Global constants with CAN driver main and subversion */
/* ROM CATEGORY 4 START */
V_DEF_CONST(V_NONE, vuint8, CONST) kCanMainVersion   = (vuint8)(( DRVCAN_IMXFLEXCAN3HLL_VERSION ) >> 8);  /*lint !e572 !e778*/
V_DEF_CONST(V_NONE, vuint8, CONST) kCanSubVersion    = (vuint8)(DRVCAN_IMXFLEXCAN3HLL_VERSION & (vuint16)0x00FF);
V_DEF_CONST(V_NONE, vuint8, CONST) kCanBugFixVersion = (vuint8)(DRVCAN_IMXFLEXCAN3HLL_RELEASE_VERSION );
/* ROM CATEGORY 4 END */

#define CanBitMask(x)      ((vuint32)((vuint32)0x01 << ((x) & (0x1F))))
#define CanInvBitMask(x)   ((vuint32)~((vuint32)0x01 << ((x) & (0x1F))))

#if defined( C_ENABLE_CAN_RAM_CHECK )
/* test bit patterns for (Extended) RAM check */
V_DEF_CONST(CAN_STATIC, vuint32, CONST) ramCheckPattern32[3] =                 /* PRQA S 3218 */ /* MD_Can_3218 */
{
  0xAAAAAAAAu, 0x55555555u, 0x00000000u
};
#endif

/* *********************************************************************** */
/* external declarations                                                   */
/* *********************************************************************** */

#if !defined( CANDRV_SET_CODE_TEST_POINT )
# define CANDRV_SET_CODE_TEST_POINT(x)
#else
extern vuint8 tscCTKTestPointState[CTK_MAX_TEST_POINT];       /* PRQA S 3447 */ /* MD_Can_3447 */
#endif

/* *********************************************************************** */
/* global data definitions                                                 */
/* *********************************************************************** */

/* RAM CATEGORY 1 START */
#if defined( C_KOMMENTAR_VECTOR_LI13 )
/* ##LI-: 2.2    Information for higher layers (e.g. TP) if the current pre-copy is called within a range or message specific. */
#endif
volatile CanReceiveHandle canRxHandle[kCanNumberOfChannels];        /* PRQA S 1514,3408 */ /* MD_Can_3218,MD_Can_3447 */
/* RAM CATEGORY 1 END */

/* RAM CATEGORY 3 START */
#if defined( C_ENABLE_CONFIRMATION_FCT ) && \
    defined( C_ENABLE_DYN_TX_OBJECTS )   && \
    defined( C_ENABLE_TRANSMIT_QUEUE )
CanTransmitHandle          confirmHandle[kCanNumberOfChannels];
#endif
/* RAM CATEGORY 3 END */

/* RAM CATEGORY 1 START */
#if defined( C_ENABLE_CONFIRMATION_FLAG )
/* Msg(4:0750) A union type has been used. MISRA Rules 110 - no change */
V_MEMRAM0 volatile V_MEMRAM1_NEAR union CanConfirmationBits V_MEMRAM2_NEAR CanConfirmationFlags;       /* PRQA S 0759 */ /* MD_Can_0750 */
#endif

#if defined( C_ENABLE_INDICATION_FLAG )
/* Msg(4:0750) A union type has been used. MISRA Rules 110 - no change */
V_MEMRAM0 volatile V_MEMRAM1_NEAR union CanIndicationBits   V_MEMRAM2_NEAR CanIndicationFlags;         /* PRQA S 0759 */ /* MD_Can_0750 */
#endif
/* RAM CATEGORY 1 END */

/* RAM CATEGORY 1 START */
#if defined( C_ENABLE_VARIABLE_RX_DATALEN )
/* ##RI1.4 - 3.31: Dynamic Receive DLC */
volatile vuint8 canVariableRxDataLen[kCanNumberOfRxObjects];
#endif
/* RAM CATEGORY 1 END */

/* RAM CATEGORY 1 START */
CanChipDataPtr canRDSRxPtr[kCanNumberOfChannels];                  /* PRQA S 1514 */ /* MD_Can_3218 */
/* RAM CATEGORY 1 END */
/* RAM CATEGORY 1 START */
CanChipDataPtr canRDSTxPtr[kCanNumberOfTxMailboxes];          /* PRQA S 1514 */ /* MD_Can_3218 */
/* RAM CATEGORY 1 END */

# if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) || defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/* RAM CATEGORY 1 START*/
V_DEF_VAR(CAN_STATIC, tCanRxMsgBuffer, VAR_NOINIT) canRxMsgBuffer[kCanNumberOfHwChannels]; /* PRQA S 3218 */ /* MD_Can_3218 */
/* RAM CATEGORY 1 END*/
# endif
# if defined( C_CPUTYPE_LITTLEENDIAN ) && defined(C_ENABLE_PRETRANSMIT_FCT)
/* RAM CATEGORY 1 START*/
V_DEF_VAR(CAN_STATIC, tCanTxMsgBuffer, VAR_NOINIT) canTxMsgBuffer[kCanNumberOfTxObjects]; /* PRQA S 3218 */ /* MD_Can_3218 */
/* RAM CATEGORY 1 END*/
# endif

/* *********************************************************************** */
/* local data definitions                                                  */
/* *********************************************************************** */

/* support for CAN driver features : */
/* RAM CATEGORY 1 START */
static volatile CanTransmitHandle canHandleCurTxObj[kCanNumberOfTxMailboxes]; /* PRQA S 0781 */ /* MD_Can_0781 */


/* RAM CATEGORY 1 END */

/* RAM CATEGORY 2 START */
#if defined( C_ENABLE_ECU_SWITCH_PASS )
static vuint8 canPassive[kCanNumberOfChannels];
#endif
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
#if defined( C_ENABLE_CAN_RAM_CHECK )
static vuint8 canComStatus[kCanNumberOfChannels]; /* stores the decision of the App after the last CAN RAM check */
#endif

#if defined( C_ENABLE_DYN_TX_OBJECTS )
static volatile vuint8 canTxDynObjReservedFlag[kCanNumberOfTxDynObjects];

# if defined( C_ENABLE_DYN_TX_ID )
static tCanTxId0 canDynTxId0[kCanNumberOfTxDynObjects];
#  if (kCanNumberOfUsedCanTxIdTables > 1)
static tCanTxId1 canDynTxId1[kCanNumberOfTxDynObjects];
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 2)
static tCanTxId2 canDynTxId2[kCanNumberOfTxDynObjects];
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 3)
static tCanTxId3 canDynTxId3[kCanNumberOfTxDynObjects];
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 4)
static tCanTxId4 canDynTxId4[kCanNumberOfTxDynObjects];
#  endif
#  if defined( C_ENABLE_MIXED_ID )
static tCanIdType                 canDynTxIdType[kCanNumberOfTxDynObjects];
#  endif
#  if defined( C_ENABLE_CAN_FD_USED )
static tCanFdType                 canDynTxFdType[kCanNumberOfTxDynObjects];
#  endif
# endif

# if defined( C_ENABLE_DYN_TX_DLC )
static tCanDlc                    canDynTxDLC[kCanNumberOfTxDynObjects];
#  if defined( C_ENABLE_CAN_FD_FULL ) && (defined( C_ENABLE_PRETRANSMIT_FCT ) || defined( C_ENABLE_COPY_TX_DATA ))
static vuint8                     canDynTxMessageLength[kCanNumberOfTxDynObjects];
#  endif
# endif
# if defined( C_ENABLE_DYN_TX_DATAPTR )
static TxDataPtr                  canDynTxDataPtr[kCanNumberOfTxDynObjects];
# endif
# if defined( C_ENABLE_CONFIRMATION_FCT )
# endif
#endif /* C_ENABLED_DYN_TX_OBJECTS */

#if defined( C_ENABLE_TX_MASK_EXT_ID )
static tCanTxId0 canTxMask0[kCanNumberOfChannels];
# if (kCanNumberOfUsedCanTxIdTables > 1)
static tCanTxId1 canTxMask1[kCanNumberOfChannels];
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
static tCanTxId2 canTxMask2[kCanNumberOfChannels];
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
static tCanTxId3 canTxMask3[kCanNumberOfChannels];
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
static tCanTxId4 canTxMask4[kCanNumberOfChannels];
# endif
#endif

#if defined( C_ENABLE_VARIABLE_DLC )
static tCanDlc canTxDLC_RAM[kCanNumberOfTxObjects];
#endif

static volatile vuint8 canStatus[kCanNumberOfChannels];

# if defined( C_ENABLE_PART_OFFLINE )
static vuint8 canTxPartOffline[kCanNumberOfChannels];
# endif
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 1 START */
#if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) && !defined (C_ENABLE_OSEK_CAN_INTCTRL)
static vsintx          canCanInterruptCounter[kCanNumberOfChannels];        /* lint !e551 */
# if defined( C_HL_ENABLE_CAN_IRQ_DISABLE )
static tCanLLCanIntOld canCanInterruptOldStatus[kCanNumberOfHwChannels];
# endif
#endif
/* RAM CATEGORY 1 END */

/* RAM CATEGORY 4 START */
static CanInitHandle lastInitObject[kCanNumberOfChannels];
/* RAM CATEGORY 4 END */

#if defined( C_ENABLE_TX_POLLING )          || \
    defined( C_ENABLE_RX_FULLCAN_POLLING )  || \
    defined( C_ENABLE_RX_BASICCAN_POLLING ) || \
    defined( C_ENABLE_ERROR_POLLING )       || \
    defined( C_ENABLE_WAKEUP_POLLING )
/* RAM CATEGORY 2 START */
static vuint8 canPollingTaskActive[kCanNumberOfChannels];
/* RAM CATEGORY 2 END */
#endif

/* RAM CATEGORY 1 START */
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )  || \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
static tCanRxInfoStruct        canRxInfoStruct[kCanNumberOfChannels];
#endif
#if defined( C_ENABLE_CAN_TX_CONF_FCT )
/* ##RI-1.10 Common Callbackfunction in TxInterrupt */
static tCanTxConfInfoStruct    txInfoStructConf[kCanNumberOfChannels]; /* PRQA S 0781 */ /* MD_Can_0781 */
#endif

#if defined( C_ENABLE_COND_RECEIVE_FCT )
static volatile vuint8 canMsgCondRecState[kCanNumberOfChannels];
#endif

#if defined( C_ENABLE_RX_QUEUE )
static tCanRxQueue canRxQueue;         /* the rx queue (buffer and queue variables) */
#endif
/* RAM CATEGORY 1 END */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
/* RAM CATEGORY 1 START */
static volatile tCanQueueElementType canTxQueueFlags[kCanTxQueueSize];
/* RAM CATEGORY 1 END */
#endif

# if defined (C_ENABLE_TX_FULLCAN_DELAYED_START)
/* RAM CATEGORY 1 START*/
V_DEF_VAR(CAN_STATIC volatile, CANSFR_TYPE, VAR_NOINIT) canLL_canDelayedFullCANTxRequest[kCanNumberOfChannels][2];
/* RAM CATEGORY 1 END*/
# endif /* C_ENABLE_TX_FULLCAN_DELAYED_START */

/* Can LL Init State variable */
V_DEF_VAR(CAN_STATIC volatile, vuint8, VAR_NOINIT) canLL_canInitState[kCanNumberOfChannels];
V_DEF_VAR(CAN_STATIC volatile, vuint8, VAR_NOINIT) canLL_canStartState[kCanNumberOfChannels];
#if defined(C_ENABLE_STOP)
V_DEF_VAR(CAN_STATIC volatile, vuint8, VAR_NOINIT) canLL_canStopState[kCanNumberOfChannels];
#endif
#if defined(C_ENABLE_SLEEP_WAKEUP)
V_DEF_VAR(CAN_STATIC volatile, vuint8, VAR_NOINIT) canLL_canSleepState[kCanNumberOfChannels];
V_DEF_VAR(CAN_STATIC volatile, vuint8, VAR_NOINIT) canLL_canWakeUpState[kCanNumberOfChannels];
#endif

/* *********************************************************************** */
/*  local prototypes                                                       */
/* *********************************************************************** */
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )  || \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
# if defined( C_ENABLE_RX_QUEUE )
/* CODE CATEGORY 1 START */
static vuint8 CanHL_ReceivedRxHandleQueue(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 1 END */
# endif
/* CODE CATEGORY 1 START */
# if ( kCanNumberOfRxObjects > 0 )
#  if defined( C_ENABLE_RX_QUEUE )
static vuint8 CanHL_ReceivedRxHandle( CAN_CHANNEL_CANTYPE_FIRST tCanRxInfoStruct *pCanRxInfoStruct );
#  else
static vuint8 CanHL_ReceivedRxHandle( CAN_CHANNEL_CANTYPE_ONLY );
#  endif
# endif /* ( kCanNumberOfRxObjects > 0 ) */
/* CODE CATEGORY 1 END */
# if defined( C_ENABLE_INDICATION_FLAG ) || \
     defined( C_ENABLE_INDICATION_FCT )
/* CODE CATEGORY 1 START */
static void CanHL_IndRxHandle( CanReceiveHandle rxHandle );
/* CODE CATEGORY 1 END */
# endif
#endif
#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/* CODE CATEGORY 1 START */
void CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle rxObjHandle);
/* CODE CATEGORY 1 END */
# if defined( C_ENABLE_RX_BASICCAN_POLLING )
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanBasicCanMsgReceivedPolling(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle rxObjHandle);
/* CODE CATEGORY 1 END */
# endif
#endif
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/* CODE CATEGORY 1 START */
static void CanFullCanMsgReceived(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle rxObjHandle);
/* CODE CATEGORY 1 END */
# if defined( C_ENABLE_RX_FULLCAN_POLLING )
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanFullCanMsgReceivedPolling(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle rxObjHandle);
/* CODE CATEGORY 1 END */
# endif
#endif

/* CODE CATEGORY 1 START */
void CanHL_TxConfirmation(CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txMailboxHandle, CanObjectHandle txObjHandle);
/* CODE CATEGORY 1 END */
# if defined( C_ENABLE_TX_POLLING )
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanHL_TxConfirmationPolling(CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txMailboxHandle, CanObjectHandle txObjHandle);
/* CODE CATEGORY 1 END */
# endif
# if defined( C_ENABLE_CAN_TRANSMIT )
/* CODE CATEGORY 1 START */
static vuint8 CanCopyDataAndStartTransmission(CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txMailboxHandle, CanTransmitHandle txHandle)  C_API_3;   /* lint !e14 !e31 */
/* CODE CATEGORY 1 END */
# endif /* C_ENABLE_CAN_TRANSMIT */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
# if defined( C_KOMMENTAR_VECTOR_LI13 )
/* ##LI-: 1.2    CAN-Offline */
# endif
/* CODE CATEGORY 4 START */
static void CanDelQueuedObj( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 4 END */
# if defined( C_ENABLE_TX_POLLING )
/* CODE CATEGORY 2 START */
static void CanHL_RestartTxQueue( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 2 END */
# endif
#endif

/* CODE CATEGORY 2 START */
static void CanHL_ErrorHandling( CAN_HW_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 2 END */

#if defined( C_ENABLE_VARIABLE_RX_DATALEN )
/* CODE CATEGORY 1 START */
static void CanSetVariableRxDatalen ( CanReceiveHandle rxHandle, vuint8 dataLen );
/* CODE CATEGORY 1 END */
#endif



static uint32_t cpu_sr;
void EnableAllInterrupts(void)
{
	GLOBAL_INT_RESTORE_V2(cpu_sr);
}

void DisableAllInterrupts(void)
{
	cpu_sr = GLOBAL_INT_DISABLE_V2();
}

/**********************************************************************************************************************
 *  CanLL_InitBegin()
 *********************************************************************************************************************/
/*! \brief         Starts the channel initialization
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] localInfo           Pointer to local variables of CanInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
CAN_LOCAL_INLINE vuint8 CanLL_InitBegin( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitInfoStructPtr localInfo );
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitBeginSetRegisters()
 *********************************************************************************************************************/
/*! \brief         Performs the channel register initialization
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] localInfo           Pointer to local variables of CanInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
CAN_LOCAL_INLINE vuint8 CanLL_InitBeginSetRegisters( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitInfoStructPtr localInfo );
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitMailboxTx()
 *********************************************************************************************************************/
/*! \brief         Initializes a transmit mailbox
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] localInfo           Pointer to local variables of CanInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
CAN_LOCAL_INLINE vuint8 CanLL_InitMailboxTx( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitInfoStructPtr localInfo );
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_InitMailboxRxFullCan()
 *********************************************************************************************************************/
/*! \brief         Initializes a receive FullCAN mailbox
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] localInfo           Pointer to local variables of CanInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
CAN_LOCAL_INLINE vuint8 CanLL_InitMailboxRxFullCan( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitInfoStructPtr localInfo );
/* CODE CATEGORY 4 END */

#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_InitMailboxRxBasicCan()
 *********************************************************************************************************************/
/*! \brief         Initializes a receive BasicCAN mailbox
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] localInfo           Pointer to local variables of CanInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
CAN_LOCAL_INLINE vuint8 CanLL_InitMailboxRxBasicCan( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitInfoStructPtr localInfo );
/* CODE CATEGORY 4 END */

#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

/**********************************************************************************************************************
 *  CanLL_InitEndSetRegisters()
 *********************************************************************************************************************/
/*! \brief         Finishes the channel register initialization
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] localInfo           Pointer to local variables of CanInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
CAN_LOCAL_INLINE vuint8 CanLL_InitEndSetRegisters( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitInfoStructPtr localInfo );
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitEnd()
 *********************************************************************************************************************/
/*! \brief         Finishes the channel initialization
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] localInfo           Pointer to local variables of CanInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
CAN_LOCAL_INLINE vuint8 CanLL_InitEnd( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitInfoStructPtr localInfo );
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_CAN_RAM_CHECK )
/**********************************************************************************************************************
 *  CanLL_InitIsMailboxCorrupt()
 *********************************************************************************************************************/
/*! \brief         Performs the RAM check for a mailbox
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] localInfo           Pointer to local variables of CanInit()
 *  \return        kCanFalse           Mailbox is not corrupt
 *                 kCanTrue            Mailbox is considered corrupt or failure occured
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
static vuint8 CanLL_InitIsMailboxCorrupt( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitInfoStructPtr localInfo );
/* CODE CATEGORY 4 END */
#endif

/**********************************************************************************************************************
 *  CanLL_InitPowerOn()
 *********************************************************************************************************************/
/*! \brief         Performs the hardware specific global module initialization
 *  \details       Called by CanInitPowerOn()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
CAN_LOCAL_INLINE vuint8 CanLL_InitPowerOn( void );
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitPowerOnChannelSpecific()
 *********************************************************************************************************************/
/*! \brief         Performs the channel dependent hardware specific global module initialization
 *  \details       Called by CanInitPowerOn()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
CAN_LOCAL_INLINE vuint8 CanLL_InitPowerOnChannelSpecific( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */

#if ((defined( C_ENABLE_CAN_TRANSMIT ) && defined( C_ENABLE_CAN_CANCEL_TRANSMIT )) ||  defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )) && defined( C_ENABLE_CANCEL_IN_HW )
/* CODE CATEGORY 3 START */
CAN_LOCAL_INLINE void CanLL_TxCancelInHw(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxCancellationInfoStructPtr localInfo);
/* CODE CATEGORY 3 END */
#endif
#if defined (C_ENABLE_CAN_TRANSMIT)
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanLL_TxBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanLL_TxSetMailbox(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
# if defined( C_ENABLE_PRETRANSMIT_FCT )
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanLL_TxSetTxStruct(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
# endif
# if defined( C_ENABLE_PRETRANSMIT_FCT )
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanLL_TxPretransmitCopyToCan(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
# endif
# if defined( C_ENABLE_COPY_TX_DATA )
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanLL_TxCopyToCan(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
# endif
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE vuint8 CanLL_TxStart(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanLL_TxEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
#endif
#if defined( C_ENABLE_TX_POLLING )
/* CODE CATEGORY 2 START */
CAN_LOCAL_INLINE vuint8 CanLL_TxIsGlobalConfPending(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
/* CODE CATEGORY 2 START */
CAN_LOCAL_INLINE void CanLL_TxProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskInfoStructPtr localInfo);
/* CODE CATEGORY 2 END */
#endif
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanLL_TxConfBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
#if (defined( C_ENABLE_TX_OBSERVE ) || defined( C_ENABLE_CAN_TX_CONF_FCT )) && defined( C_ENABLE_CANCEL_IN_HW )
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE vuint8 CanLL_TxConfIsMsgTransmitted(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
#endif
#if defined( C_ENABLE_CAN_TX_CONF_FCT ) && defined( C_ENABLE_CAN_TX_CONF_MSG_ACCESS )
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanLL_TxConfSetTxConfStruct(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
#endif
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanLL_TxConfEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
#if defined( C_ENABLE_MSG_TRANSMIT )
/* CODE CATEGORY 2 START */
CAN_LOCAL_INLINE void CanLL_TxBeginMsgTransmit(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxMsgTransmissionInfoStructPtr localInfo);
/* CODE CATEGORY 2 END */
/* CODE CATEGORY 2 START */
CAN_LOCAL_INLINE void CanLL_TxCopyMsgTransmit(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxMsgTransmissionInfoStructPtr localInfo);
/* CODE CATEGORY 2 END */
/* CODE CATEGORY 2 START */
CAN_LOCAL_INLINE vuint8 CanLL_TxStartMsgTransmit(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxMsgTransmissionInfoStructPtr localInfo);
/* CODE CATEGORY 2 END */
/* CODE CATEGORY 2 START */
CAN_LOCAL_INLINE void CanLL_TxEndMsgTransmit(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxMsgTransmissionInfoStructPtr localInfo);
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_MSG_TRANSMIT */

#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE vuint8 CanLL_RxBasicMsgReceivedBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanLL_RxBasicReleaseObj(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanLL_RxBasicMsgReceivedEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
# if defined( C_ENABLE_RX_BASICCAN_POLLING )
/* CODE CATEGORY 2 START */
CAN_LOCAL_INLINE vuint8 CanLL_RxBasicIsGlobalIndPending(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
/* CODE CATEGORY 2 START */
CAN_LOCAL_INLINE void CanLL_RxBasicProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskInfoStructPtr localInfo);
/* CODE CATEGORY 2 END */
# endif /* C_ENABLE_RX_BASICCAN_POLLING */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE vuint8 CanLL_RxFullMsgReceivedBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanLL_RxFullReleaseObj(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanLL_RxFullMsgReceivedEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
# if defined( C_ENABLE_RX_FULLCAN_POLLING )
/* CODE CATEGORY 2 START */
CAN_LOCAL_INLINE vuint8 CanLL_RxFullIsGlobalIndPending(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
/* CODE CATEGORY 2 START */
CAN_LOCAL_INLINE void CanLL_RxFullProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskInfoStructPtr localInfo);
/* CODE CATEGORY 2 END */
# endif /* C_ENABLE_RX_FULLCAN_POLLING */
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */
#if (defined( C_ENABLE_RX_FULLCAN_OBJECTS ) || defined( C_ENABLE_RX_BASICCAN_OBJECTS )) && ( kCanNumberOfRxObjects > 0 ) && defined( C_ENABLE_COPY_RX_DATA )
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanLL_RxCopyFromCan(CAN_CHANNEL_CANTYPE_FIRST CanRxCopyInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
#endif

/* CODE CATEGORY 2 START */
CAN_LOCAL_INLINE void CanLL_ErrorHandlingBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
/* CODE CATEGORY 2 START */
CAN_LOCAL_INLINE vuint8 CanLL_BusOffOccured(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
/* CODE CATEGORY 2 START */
CAN_LOCAL_INLINE void CanLL_ErrorHandlingEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
#if defined( C_ENABLE_EXTENDED_STATUS )
/* CODE CATEGORY 3 START */
CAN_LOCAL_INLINE void CanLL_GetStatusBegin(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 3 END */
#endif
#if defined( C_ENABLE_SLEEP_WAKEUP ) && defined( C_ENABLE_WAKEUP_POLLING )
/* CODE CATEGORY 2 START */
CAN_LOCAL_INLINE vuint8 CanLL_WakeUpOccured(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
#endif
#if defined( C_ENABLE_SLEEP_WAKEUP )
/* CODE CATEGORY 4 START */
CAN_LOCAL_INLINE void CanLL_WakeUpHandling(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#endif
/* CODE CATEGORY 4 START */
static vuint8 CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST vuint8 mode, vuint8 busOffRecovery);
/* CODE CATEGORY 4 END */
#if defined( C_ENABLE_STOP )
/* CODE CATEGORY 4 START */
CAN_LOCAL_INLINE void CanLL_StopReinit(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#endif
#if defined( C_ENABLE_RX_QUEUE )
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanLL_RxQueueCopyMsgObj(CAN_CHANNEL_CANTYPE_FIRST CanRxQueueCopyInfoStructPtr localInfo);
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 2 START */
CAN_LOCAL_INLINE void CanLL_RxQueueSetRxInfoStructExtension(CAN_CHANNEL_CANTYPE_FIRST CanRxQueueRxInfoStructPtr localInfo);
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_RX_QUEUE */

#if defined( C_ENABLE_CAN_CAN_INTERRUPT_CONTROL ) && !defined( C_ENABLE_OSEK_CAN_INTCTRL ) && defined( C_HL_ENABLE_CAN_IRQ_DISABLE )
/************************************************************************************************************
 *  CanLL_CanInterruptDisable()
 ***********************************************************************************************************/
/*! \brief         Disables CAN interrupts.
 *  \details       Stores current state and disables the individual CAN interrupt sources.
 *  \param[in]     canHwChannel              CAN channel
 *  \param[out]    localInterruptOldFlagPtr  Pointer to global variable that holds the interrupt state
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        ...
 *  \pre           -
 ***********************************************************************************************************/
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanLL_CanInterruptDisable(CAN_HW_CHANNEL_CANTYPE_FIRST tCanLLCanIntOldPtr localInterruptOldFlagPtr);
/* CODE CATEGORY 1 END */

/************************************************************************************************************
 *  CanLL_CanInterruptRestore()
 ***********************************************************************************************************/
/*! \brief         Restores CAN interrupts.
 *  \details       Restores the previous state of the individual CAN interrupt sources.
 *  \param[in]     canHwChannel              CAN channel
 *  \param[in]     localInterruptOldFlag     Global variable that holds the interrupt state
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        ...
 *  \pre           -
 ***********************************************************************************************************/
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanLL_CanInterruptRestore(CAN_HW_CHANNEL_CANTYPE_FIRST tCanLLCanIntOld localInterruptOldFlag);
/* CODE CATEGORY 1 END */
#endif

#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
    defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
    defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 2 START */
/************************************************************************************************************
 *  CanLL_CanInterruptDisable()
 ***********************************************************************************************************/
/*! \brief         disable CAN interrupt
 *  \details       saves the current status (enable or disable) of all
 *                 CAN interrupts to localInterruptOldFlagPtr
 *                 and disables all CAN interrupts  (RX, TX, error, wakeup).
 *  \param[in]     canHwChannel              CAN HW controller
 *  \param[out]    localInterruptOldFlagPtr  get old interrupt state to be restored
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptDisable(CAN_HW_CHANNEL_CANTYPE_FIRST tCanLLCanIntOldPtr localInterruptOldFlagPtr);

/************************************************************************************************************
 *  CanLL_CanInterruptRestore()
 **********************************************************************************************************/
/*! \brief         enable CAN interrupt
 *  \details       restores all CAN interrupts (RX, TX, error, wakeup).
 *  \param[in]     canHwChannel              CAN HW controller
 *  \param[in]     localInterruptOldFlag     old interrupt state to be restored
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptRestore(CAN_HW_CHANNEL_CANTYPE_FIRST tCanLLCanIntOld localInterruptOldFlag);
/* CODE CATEGORY 2 END */
#endif
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_SetFlexCANToInitMode()
 ***********************************************************************************************************/
/*! \brief         Set FlexCAN Controller to INIT mode.
 *  \details       Sets the FlexCAN Controller from any mode to INIT mode.
 *  \param[in]     Controller     CAN controller (Controller must be in valid range). \n
 *                                (only if not using "Optimize for one controller")
 *  \return        kCanRequested: FlexCAN successfully set to init mode
 *  \return        kCanFailed:    FlexCAN failure
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_SetFlexCANToInitMode(CAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_ExecuteSoftReset()
 ***********************************************************************************************************/
/*! \brief         Perform FlexCAN soft-reset
 *  \details       Triggers the FlexCAN Controller to perform internal soft-reset.
 *  \param[in]     Controller     CAN controller (Controller must be in valid range). \n
 *                                (only if not using "Optimize for one controller")
 *  \return        kCanRequested: SoftReset ongoing
 *  \return        kCanOk:        SoftReset successfully finished
 *  \return        kCanFailed:    transition failure
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_ExecuteSoftReset(CAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */

/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_Start()
 ***********************************************************************************************************/
/*! \brief         Perform FlexCAN start mode
 *  \details       Request start mode to FlexCAN Controller and control the transition.
 *  \param[in]     Controller     CAN controller (Controller must be in valid range). \n
 *                                (only if not using "Optimize for one controller")
 *  \return        kCanRequested: Transition to START ongoing
 *  \return        kCanOk:        Transition to START successfully finished
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_Start(CAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */

#if defined(C_ENABLE_STOP)
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_Stop()
 ***********************************************************************************************************/
/*! \brief         Perform FlexCAN stop mode
 *  \details       Request stop mode to FlexCAN Controller and control the transition.
 *  \param[in]     Controller     CAN controller (Controller must be in valid range). \n
 *                                (only if not using "Optimize for one controller")
 *  \return        kCanRequested: Transition to STOP ongoing
 *  \return        kCanOk:        Transition to STOP successfully finished
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_Stop(CAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#endif
#if defined(C_ENABLE_SLEEP_WAKEUP)
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_Sleep()
 ***********************************************************************************************************/
/*! \brief         Perform FlexCAN sleep mode
 *  \details       Request sleep mode to FlexCAN Controller and control the transition.
 *  \param[in]     Controller     CAN controller (Controller must be in valid range). \n
 *                                (only if not using "Optimize for one controller")
 *  \return        kCanRequested: Transition to SLEEP ongoing
 *  \return        kCanOk:        Transition to SLEEP successfully finished
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_Sleep(CAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_WakeUp()
 ***********************************************************************************************************/
/*! \brief         Perform a wake-up to FlexCAN from sleep mode
 *  \details       Request started mode to FlexCAN Controller and control the transition.
 *  \param[in]     Controller     CAN controller (Controller must be in valid range). \n
 *                                (only if not using "Optimize for one controller")
 *  \return        kCanRequested: Transition to START ongoing
 *  \return        kCanOk:        Transition to START successfully finished
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_WakeUp(CAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#endif
#if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT )
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_HandleBusOff()
 ***********************************************************************************************************/
/*! \brief         Handle BusOff recovery
 *  \details       Call CanInit and set BusOff flag to FALSE if BusOff recovery was successful
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \pre           Interrupts are disabled.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_BUSOFF_RECOVERY_COMPLIANT
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_HandleBusOff(CAN_CHANNEL_CANTYPE_ONLY);

/************************************************************************************************************
 *  CanLL_HandleStartProcess()
 ***********************************************************************************************************/
/*! \brief         Handle START process
 *  \details       Call CanInit and set BusOff flag to FALSE if BusOff recovery was successful
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \return        kCanOk (CAN_OK)          transition to START was finished successfully
 *  \return        kCanFailes (CAN_NOT_OK)  transition to START was not yet finished successfully
 *  \pre           Interrupts are disabled.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_BUSOFF_RECOVERY_COMPLIANT
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanLL_HandleStartProcess(CAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#endif

#if defined( C_ENABLE_CAN_RAM_CHECK )
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_InitIsMailboxCorrupt()
 ***********************************************************************************************************/
/*! \brief         RAM check
 *  \details       check the current mailbox at index hwObjHandle by write and read back patterns.
 *  \param[in]     Controller          CAN controller
 *  param[in,out]  localInfo           Pointer to local variables of CanInit()
 *  \return        kCanTrue:    Mailbox is corrupt
 *  \return        kCanFalse:   Mailbox is not corrupt
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RAM_CHECK
************************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_InitIsMailboxCorrupt(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitInfoStructPtr localInfo);
/* CODE CATEGORY 4 END */
#endif
#if defined ( V_CPU_S32 )
# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanLL_ComputeMailboxInterrupt()
 ***********************************************************************************************************/
/*! \brief         Computes Mailbox interrupt.
 *  \details       Determines the index of the Mailbox that notified an interrupt and call
 *                 CanLL_ComputeInterruptType.
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \param[in]     iFlags        Interrupt Flags that should be used for computation.
 *  \param[in]     iMask         Interrupt Mask that determines which iFlags are considered in interrupt context.
 *  \param[in]     startIndex    Index of first Mailbox that is part of the corresponding iFlags/iMask values.
 *  \pre           -
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanLL_ComputeMailboxInterrupt(CAN_HW_CHANNEL_CANTYPE_FIRST vuint32 iFlags, vuint32 iMask, CanObjectHandle startIndex);
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanLL_ComputeInterruptType()
 ***********************************************************************************************************/
/*! \brief         Computes the communication type of the notified Mailbox interrupt (Tx/Rx FullCAN/BasicCAN).
 *  \details       Determines which communication event occurred and calls internal notification function.
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \param[in]     index         Index of the Mailbox that notified an interrupt.
 *  \pre           -
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ComputeInterruptType(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle index);
/* CODE CATEGORY 1 END */
# endif
#endif

/* *********************************************************************** */
/*  Error Check                                                            */
/* *********************************************************************** */

/* *************** error check for Organi process ************************ */

/* *************** error check for not supported feature  ****************** */
#if defined( ERROR_C_ENABLE_MSG_TRANSMIT )
# error "Low Level Message Transmit is not supported with this CAN driver implementation"
#endif

#if defined( ERROR_C_ENABLE_INDIVIDUAL_POLLING )
# error "Individual polling is not supported with this CAN driver implementation"
#endif

#if defined( ERROR_C_ENABLE_MULTIPLE_BASICCAN )
# error "Multiple Basic CAN is not supported with this CAN driver implementation"
#endif

#if defined( ERROR_C_ENABLE_RX_QUEUE )
# error "Rx Queue is not supported with this CAN driver implementation"
#endif

#if defined( C_ENABLE_COMMON_CAN )
# error "Common CAN is not supported with this CAN driver implementation"
#endif

#if defined( C_ENABLE_MULTI_ECU_CONFIG )
# error "Multiple Configuration is not supported with this CAN driver implementation"
#endif

#if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
# error "Extended RAM Check is not supported with this CAN driver implementation"
#endif

#if (VSTDLIB__COREHLL_VERSION  <  0x0213 )
# error "Incompatible version of VStdLib. Core Version 2.13.00 or higher is necessary."
#endif

#if (kCanNumberOfHwChannels > 255)
#  error "Too many CAN channels. This driver can only handle up to 255 channels"
#endif

#if defined( C_SEARCH_HASH )
# if !defined( kHashSearchListCountEx )
#  error "kHashSearchListCountEx not defined"
# endif
# if !defined( kHashSearchMaxStepsEx )
#  error "kHashSearchMaxStepsEx not defined"
# endif
# if !defined( kHashSearchListCount )
#  error "kHashSearchListCount not defined"
# endif
# if !defined( kHashSearchMaxSteps )
#  error "kHashSearchMaxSteps not defined"
# endif
# if ( (kHashSearchMaxStepsEx < 1) ||(kHashSearchMaxStepsEx > 32768) )
#  error "kHashSearchMaxStepsEx has ilegal value"
# endif
# if ( kHashSearchListCountEx > 32768 )
#  error "Hash table for extended ID is too large"
# endif
# if ( (kHashSearchMaxSteps < 1) ||(kHashSearchMaxSteps > 32768) )
#  error "kHashSearchMaxStepsEx has ilegal value"
# endif
# if ( kHashSearchListCount > 32768 )
#  error "Hash table for standard ID is too large"
# endif
# if !defined( C_ENABLE_EXTENDED_ID) && (kHashSearchListCountEx > 0)
#  error "kHashSearchListCountEx has to be 0 in this configuration"
# endif
# if defined( C_ENABLE_EXTENDED_ID) && !defined( C_ENABLE_MIXED_ID) &&(kHashSearchListCount > 0)
#  error "kHashSearchListCount has to be 0 in this configuration"
# endif
#endif

#if defined( C_ENABLE_RX_QUEUE )
# if !defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
#  error "RX-Queue requires C_HL_ENABLE_RX_INFO_STRUCT_PTR"
# endif
#endif

#if defined( C_SEARCH_INDEX ) && defined( C_ENABLE_EXTENDED_ID )
# error "Index search is not possible with extended ID's"
#endif

#if defined ( CAN_POLLING_IRQ_DISABLE ) || defined ( CAN_POLLING_IRQ_RESTORE )
# error "Feature has changed - use C_DISABLE_CAN_CAN_INTERRUPT_CONTROL to remove the CAN interrupt disabling"
#endif

#if defined( C_ENABLE_CAN_TX_CONF_MSG_ACCESS ) && defined( C_ENABLE_ECU_SWITCH_PASS )
# error "Access to transmitted message is not supported in combination with passive mode"
#endif

#if defined( C_ENABLE_CAN_FD_FULL ) && !defined( C_ENABLE_CAN_FD_USED )
# error "CAN-FD Mode2 requires CAN-FD to be enabled"
#endif

#if defined( C_ENABLE_CAN_FD_FULL ) && defined( C_ENABLE_VARIABLE_DLC )
# error "CanTransmitVarDLC() is not supported in combination with CAN-FD Mode2."
#endif

/* *********************************************************************** */
/*  Functions                                                              */
/* *********************************************************************** */

/* **************************************************************************
| NAME:             CanInit
| CALLED BY:        CanInitPowerOn(), Network management
| PRECONDITIONS:    none
| INPUT PARAMETERS: Handle to initstructure
| RETURN VALUES:    none
| DESCRIPTION:      initialization with a specified init structure
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanInit( CAN_CHANNEL_CANTYPE_FIRST CanInitHandle initObject )
{
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif
  assertUser((initObject + CAN_HL_INIT_OBJ_STARTINDEX(channel)) < CAN_HL_INIT_OBJ_STOPINDEX(channel), channel, kErrorInitObjectHdlTooLarge); /* PRQA S 3689 */ /* MD_Can_3689 */

  lastInitObject[channel] = initObject; /* PRQA S 3689 */ /* MD_Can_3689 */

  CanReInit(CAN_CHANNEL_CANPARA_FIRST kCanExecuteRamCheck, kCanExecuteModeTransition);
}
/* CODE CATEGORY 4 END */

/* **************************************************************************
| NAME:             CanReInit
| CALLED BY:        CanInit(), CanStop(), CanEnableChannelCommunication(), Network management
| PRECONDITIONS:    none
| INPUT PARAMETERS: suppression of RAM check and mode transition during initialization
| RETURN VALUES:    none
| DESCRIPTION:      initialization of chip-hardware
|                   initialization of receive and transmit message objects
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanReInit( CAN_CHANNEL_CANTYPE_FIRST vuint8 suppressRamCheck, vuint8 suppressModeTransition )
{
#if defined( C_ENABLE_CAN_RAM_CHECK )
  vuint8                 canRamCheckStatus;
  vuint8                 localMailboxIsCorrupt;
#endif
  CanObjectHandle        mailboxHandle; /* PRQA S 0781 */ /* MD_Can_0781 */
#if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION ) || \
    defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
  CanTransmitHandle      txHandle;
#endif
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
  CanReceiveHandle       rxHandle;
#endif
  CanObjectHandle        logTxObjHandle; /* PRQA S 0781 */ /* MD_Can_0781 */
  vuint8                 localReturnCode;

  tCanInitInfoStruct initInfo;

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif

#if defined( C_ENABLE_CAN_RAM_CHECK )
  canRamCheckStatus = kCanOk;
#endif
  initInfo.initObject = lastInitObject[channel] + CAN_HL_INIT_OBJ_STARTINDEX(channel); /* PRQA S 3689 */ /* MD_Can_3689 */

  {
    initInfo.isInitOk = kCanTrue;

    /* begin the channel initialization */
    if (CanLL_InitBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initInfo) != kCanOk)
    {
      initInfo.isInitOk = kCanFalse;
    }

    if (initInfo.isInitOk == kCanTrue)
    {
      /* transit to initialization mode */
      localReturnCode = CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST kCanModeInit, kCanContinueBusOffRecovery);
      if (localReturnCode == kCanRequested)
      {
        CanHL_ApplCanTimerStart(kCanLoopInit);
        do
        {
          localReturnCode = CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST kCanModeInit, kCanContinueBusOffRecovery);
          CanHL_ApplCanTimerLoop(kCanLoopInit);
        } while (localReturnCode != kCanOk);
        CanHL_ApplCanTimerEnd(kCanLoopInit);
      }
      if (localReturnCode != kCanOk)
      {
        initInfo.isInitOk = kCanFalse;
      }
    }

    if (initInfo.isInitOk == kCanTrue)
    {

      /* begin the initialization of the channel registers */
      if (CanLL_InitBeginSetRegisters(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initInfo) != kCanOk)
      {
        initInfo.isInitOk = kCanFalse;
      }
    }

    if (initInfo.isInitOk == kCanTrue)
    {
      /* init Tx mailboxes -------------------------------------------------------- */
      {
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
        assertGen( ((vsintx)CAN_HL_MB_TX_STOPINDEX(canHwChannel) + CAN_HL_TX_OFFSET_MB_TO_LOG(canHwChannel))              /* PRQA S 3689 */ /* MD_Can_3689 */
                   == (vsintx)CAN_HL_LOG_MB_TX_STOPINDEX(canHwChannel), channel, kErrorHwToLogTxObjCalculation);          /* PRQA S 3689 */ /* MD_Can_3689 */ /* ESCAN00062667 */
        assertGen( ((vsintx)CAN_HL_MB_TX_STARTINDEX(canHwChannel) + CAN_HL_TX_OFFSET_MB_TO_LOG(canHwChannel))             /* PRQA S 3689 */ /* MD_Can_3689 */
                   == (vsintx)CAN_HL_LOG_MB_TX_STARTINDEX(canHwChannel), channel, kErrorHwToLogTxObjCalculation);         /* PRQA S 3689 */ /* MD_Can_3689 */ /* ESCAN00062667 */
        assertGen( CAN_HL_LOG_MB_TX_STARTINDEX(canHwChannel) <= CAN_HL_LOG_MB_TX_STOPINDEX(canHwChannel), channel, kErrorHwToLogTxObjCalculation);  /* PRQA S 3689 */ /* MD_Can_3689 */
#endif

        for (mailboxHandle=CAN_HL_MB_TX_STARTINDEX(canHwChannel); mailboxHandle<CAN_HL_MB_TX_STOPINDEX(canHwChannel); mailboxHandle++ )   /* PRQA S 3689,3355,3357 */ /* MD_Can_3689,MD_Can_13.7,MD_Can_13.7 */  /* lint !e661 */
        {
          logTxObjHandle = (CanObjectHandle)((vsintx)mailboxHandle + CAN_HL_TX_OFFSET_MB_TO_LOG(canHwChannel));  /* PRQA S 3689 */ /* MD_Can_3689 */   /* lint !e661 */
          initInfo.mailboxHandle = mailboxHandle;
          initInfo.hwObjHandle = Can_Mailbox[mailboxHandle].HwObjHandle;

#if defined( C_KOMMENTAR_VECTOR_LI13 )
/* ##LI-: 1.2    CAN-Offline */
#endif
#if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION ) || \
    defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
          if((canStatus[channel] & kCanHwIsInit) == kCanHwIsInit)      /* PRQA S 3689 */ /* MD_Can_3689 */ /* lint !e661 */
          {
            /* inform application, if a pending transmission is canceled */
            txHandle = canHandleCurTxObj[logTxObjHandle];

# if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
            if( txHandle < kCanNumberOfTxObjects )
            {
              APPLCANCANCELNOTIFICATION(channel, txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
            }
# endif
# if defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
            if( txHandle == kCanBufferMsgTransmit )
            {
              APPLCANMSGCANCELNOTIFICATION(channel); /* PRQA S 3689 */ /* MD_Can_3689 */
            }
# endif
          }
#endif

          canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;                   /* MsgObj is free */

# if defined( C_ENABLE_CAN_RAM_CHECK )
          /* perform the mailbox RAM check */
          {
            localMailboxIsCorrupt = CanLL_InitIsMailboxCorrupt(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initInfo);
          }
# endif /* C_ENABLE_CAN_RAM_CHECK */

          /* initialize the mailbox */
          (void) CanLL_InitMailboxTx(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initInfo);

# if defined( C_ENABLE_CAN_RAM_CHECK )
          if (localMailboxIsCorrupt == kCanTrue)
          {
#  if defined( C_ENABLE_NOTIFY_CORRUPT_MAILBOX )
            ApplCanCorruptMailbox(CAN_CHANNEL_CANPARA_FIRST mailboxHandle);
#  endif
            canRamCheckStatus = kCanFailed;
          }

# endif /* C_ENABLE_CAN_RAM_CHECK */
        } /* iterate mailboxHandles */
      }

      /* init unused mailboxes ---------------------------------------------------- */
      /* unused objects are not individually disabled */

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
      /* init Rx FullCAN mailboxes ------------------------------------- */
      {

        for (mailboxHandle=CAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel); mailboxHandle<CAN_HL_MB_RX_FULL_STOPINDEX(canHwChannel); mailboxHandle++ ) /* PRQA S 3689,3355,3357 */ /* MD_Can_3689,MD_Can_13.7,MD_Can_13.7 */
        {
          initInfo.mailboxHandle = mailboxHandle;
          initInfo.hwObjHandle	 = Can_Mailbox[mailboxHandle].HwObjHandle;

#  if defined( C_ENABLE_CAN_RAM_CHECK )
          /* perform the mailbox RAM check */
          {
            localMailboxIsCorrupt = CanLL_InitIsMailboxCorrupt(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initInfo);
          }
#  endif /* C_ENABLE_CAN_RAM_CHECK */

          /* brackets to avoid lint info 834 */
          rxHandle = (mailboxHandle-CAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel))+CAN_HL_RX_FULL_STARTINDEX(canHwChannel); /* PRQA S 3689 */ /* MD_Can_3689 */
          initInfo.idRaw0 = CanGetRxId0(rxHandle);
#  if (kCanNumberOfUsedCanRxIdTables > 1)
          initInfo.idRaw1 = CanGetRxId1(rxHandle);
#  endif
#  if (kCanNumberOfUsedCanRxIdTables > 2)
          initInfo.idRaw2 = CanGetRxId2(rxHandle);
#  endif
#  if (kCanNumberOfUsedCanRxIdTables > 3)
          initInfo.idRaw3 = CanGetRxId3(rxHandle);
#  endif
#  if (kCanNumberOfUsedCanRxIdTables > 4)
          initInfo.idRaw4 = CanGetRxId4(rxHandle);
#  endif
          initInfo.idType = CanGetRxIdType(rxHandle);

          /* initialize the mailbox */
          (void) CanLL_InitMailboxRxFullCan(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initInfo);

#  if defined( C_ENABLE_CAN_RAM_CHECK )
          if (localMailboxIsCorrupt == kCanTrue)
          {
#   if defined( C_ENABLE_NOTIFY_CORRUPT_MAILBOX )
            ApplCanCorruptMailbox(CAN_CHANNEL_CANPARA_FIRST mailboxHandle);
#   endif
            canRamCheckStatus = kCanFailed;
          }

#  endif /* C_ENABLE_CAN_RAM_CHECK */
        } /* iterate mailboxHandles */
      }
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
      /* init Rx BasicCAN mailboxes ------------------------------------ */
      for (mailboxHandle=CAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel); mailboxHandle<CAN_HL_MB_RX_BASIC_STOPINDEX(canHwChannel); mailboxHandle++ ) /* PRQA S 3689,3355,3357 */ /* MD_Can_3689,MD_Can_13.7,MD_Can_13.7 */
      {
        initInfo.mailboxHandle = mailboxHandle;
        initInfo.hwObjHandle = Can_Mailbox[mailboxHandle].HwObjHandle;

#  if defined( C_ENABLE_CAN_RAM_CHECK )
        /* perform the mailbox RAM check */
        {
          localMailboxIsCorrupt = CanLL_InitIsMailboxCorrupt(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initInfo);
        }
#  endif /* C_ENABLE_CAN_RAM_CHECK */

        /* initialize the mailbox */
        (void) CanLL_InitMailboxRxBasicCan(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initInfo);

#  if defined( C_ENABLE_CAN_RAM_CHECK )
        if (localMailboxIsCorrupt == kCanTrue)
        {
#   if defined( C_ENABLE_NOTIFY_CORRUPT_MAILBOX )
          ApplCanCorruptMailbox(CAN_CHANNEL_CANPARA_FIRST mailboxHandle);
#   endif
          canRamCheckStatus = kCanFailed;
        }

#  endif /* C_ENABLE_CAN_RAM_CHECK */
      } /* iterate mailboxHandles */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined( C_ENABLE_INIT_POST_PROCESS )
      /* The post processing function is called within the initialization mode of the CAN controller.
         The application can directly overwrite existing configuration in the CAN controller.
         Example: overwriting the baudrate settings with dynamic values, necessary macros are provided in the LL part */
      ApplCanInitPostProcessing( CAN_CHANNEL_CANPARA_ONLY );
#endif

      /* finish the initialization of the channel registers */
      if (CanLL_InitEndSetRegisters(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initInfo) != kCanOk)
      {
        initInfo.isInitOk = kCanFalse;
      }
    } /* initInfo.isInitOk == kCanTrue */

    {
      if (suppressModeTransition == kCanFalse)
      {
        if (initInfo.isInitOk == kCanTrue)
        {
          /* transit to start mode */
          localReturnCode = CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST kCanModeStart, kCanFinishBusOffRecovery);

          if (localReturnCode == kCanRequested)
          {
            CanHL_ApplCanTimerStart(kCanLoopStart);
            do
            {
              localReturnCode = CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST kCanModeStart, kCanFinishBusOffRecovery);
              CanHL_ApplCanTimerLoop(kCanLoopStart);
            } while (localReturnCode != kCanOk);
            CanHL_ApplCanTimerEnd(kCanLoopStart);
          }
          if (localReturnCode != kCanOk)
          {
            initInfo.isInitOk = kCanFalse;
          }
        }
      }
    }

    /* finish the channel initialization */
    (void) CanLL_InitEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initInfo);
    CanDrv_Init();

  } /* end of loop over all hw channels */

#if defined( C_ENABLE_TX_OBSERVE )
# if defined( C_KOMMENTAR_VECTOR_RI14 )
/* ##RI-1.1: Object parameters for Tx-Observe functions */
# endif
  ApplCanInit( CAN_CHANNEL_CANPARA_FIRST CAN_HL_LOG_MB_TX_STARTINDEX(canHwChannel), CAN_HL_LOG_MB_TX_STOPINDEX(canHwChannel) ); /* PRQA S 3689 */ /* MD_Can_3689 */
#endif
#if defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )
  APPL_CAN_MSGTRANSMITINIT( CAN_CHANNEL_CANPARA_ONLY );
#endif

#if defined( C_ENABLE_CAN_RAM_CHECK )
  if(canRamCheckStatus == kCanFailed)
  {
    /* the application decides whether the communication shall be disabled */
    if (ApplCanMemCheckFailed(CAN_CHANNEL_CANPARA_ONLY) == kCanDisableCommunication)
    {
      canComStatus[channel] = kCanDisableCommunication; /* PRQA S 3689 */ /* MD_Can_3689 */
    }
  }
#endif

  CAN_DUMMY_STATEMENT(suppressRamCheck); /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* END OF CanInit */
/* CODE CATEGORY 4 END */

/* **************************************************************************
| NAME:             CanInitPowerOn
| CALLED BY:        Application
| PRECONDITIONS:    This function must be called by the application before
|                   any other CAN driver function
|                   Interrupts must be disabled
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Initialization of the CAN chip
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanInitPowerOn( void )
{

#if defined( C_ENABLE_VARIABLE_DLC )        || \
    defined( C_ENABLE_DYN_TX_OBJECTS )      || \
    defined( C_ENABLE_CONFIRMATION_FLAG )
  CanTransmitHandle txHandle;
#endif
#if defined( C_ENABLE_VARIABLE_RX_DATALEN ) || \
    defined( C_ENABLE_INDICATION_FLAG )
  CanReceiveHandle rxHandle;
#endif
  CAN_CHANNEL_CANTYPE_LOCAL

  VStdInitPowerOn();

#if defined( C_ENABLE_VARIABLE_DLC )
  for (txHandle = 0; txHandle < kCanNumberOfTxObjects; txHandle++)
  {
    assertGen(XT_TX_DLC(CanGetTxDlc(txHandle))<(vuint8)9, kCanAllChannels, kErrorTxROMDLCTooLarge);
    canTxDLC_RAM[txHandle] = CanGetTxDlc(txHandle);
  }
#endif

#if defined( C_ENABLE_DYN_TX_OBJECTS )
  /* Reset dynamic transmission object management -------------------------- */
  for (txHandle = 0; txHandle < kCanNumberOfTxDynObjects; txHandle++)
  {
    /* Reset management information */
    canTxDynObjReservedFlag[txHandle] = 0;
  }
#endif /* C_ENABLE_DYN_TX_OBJECTS */

#if defined( C_ENABLE_VARIABLE_RX_DATALEN )
  for (rxHandle = 0; rxHandle < kCanNumberOfRxObjects; rxHandle++)
  {
# if defined( C_ENABLE_VARIABLE_RX_DATALEN )
    /* Initialize the array with generated dlc ---------------------- */
    canVariableRxDataLen[rxHandle] = CanGetRxDataLen(rxHandle);
# endif
  }
#endif /* defined( C_ENABLE_VARIABLE_RX_DATALEN ) || defined( C_ENABLE_DYN_RX_OBJECTS ) */

#if defined( C_ENABLE_INDICATION_FLAG )
  for (rxHandle = 0; rxHandle < kCanNumberOfIndBytes; rxHandle++) {
    CanIndicationFlags._c[rxHandle] = 0;
  }
#endif

#if defined( C_ENABLE_CONFIRMATION_FLAG )
  for (txHandle = 0; txHandle < kCanNumberOfConfBytes; txHandle++) {
    CanConfirmationFlags._c[txHandle] = 0;
  }
#endif

#if defined( C_ENABLE_RX_QUEUE )
  CanDeleteRxQueue();
#endif

#if defined( C_ENABLE_TRANSMIT_QUEUE )
#endif

  /* LowLevel specific initialization */
  if (CanLL_InitPowerOn() == kCanOk)
  {
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    for (channel=0; channel<kCanNumberOfChannels; channel++)
#endif
    {
#if defined( C_ENABLE_CAN_RAM_CHECK )
      canComStatus[channel] = kCanEnableCommunication;
#endif
      canStatus[channel] = kCanStatusInit;

      /* LowLevel specific initialization */
      if (CanLL_InitPowerOnChannelSpecific(CAN_CHANNEL_CANPARA_ONLY) == kCanOk)
      {
#if defined( C_ENABLE_CAN_TX_CONF_FCT )
        txInfoStructConf[channel].Channel = channel;
#endif
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )  || \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
        canRxInfoStruct[channel].Channel = channel;
#endif

#if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) && !defined (C_ENABLE_OSEK_CAN_INTCTRL)
        canCanInterruptCounter[channel] = 0;
#endif

#if defined( C_ENABLE_TX_POLLING )          || \
      defined( C_ENABLE_RX_FULLCAN_POLLING )  || \
      defined( C_ENABLE_RX_BASICCAN_POLLING ) || \
      defined( C_ENABLE_ERROR_POLLING )       || \
      defined( C_ENABLE_WAKEUP_POLLING )
        canPollingTaskActive[channel] = 0;
#endif

#if defined( C_ENABLE_DYN_TX_OBJECTS )   && \
    defined( C_ENABLE_CONFIRMATION_FCT ) && \
    defined( C_ENABLE_TRANSMIT_QUEUE )
        /* Reset dynamic transmission object management -------------------------- */
        confirmHandle[channel] = kCanBufferFree;
#endif

#if defined( C_ENABLE_TX_MASK_EXT_ID )
        canTxMask0[channel] = 0;
# if (kCanNumberOfUsedCanTxIdTables > 1)
        canTxMask1[channel] = 0;
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
        canTxMask2[channel] = 0;
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
        canTxMask3[channel] = 0;
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
        canTxMask4[channel] = 0;
# endif
#endif

#if defined( C_ENABLE_ECU_SWITCH_PASS )
        canPassive[channel]             = 0;
#endif

#if defined( C_ENABLE_PART_OFFLINE )
        canTxPartOffline[channel]       = kCanTxPartInit;
#endif
#if defined( C_ENABLE_COND_RECEIVE_FCT )
        canMsgCondRecState[channel]     = kCanTrue;
#endif

        canRxHandle[channel] = kCanRxHandleNotUsed;

        {
#if defined( C_ENABLE_TRANSMIT_QUEUE )
          /* clear all Tx queue flags */
# if defined( C_KOMMENTAR_VECTOR_LI13 )
/* ##LI-: 1.2    CAN-Offline */
# endif
          CanDelQueuedObj( CAN_CHANNEL_CANPARA_ONLY );
#endif

          CanInit( CAN_CHANNEL_CANPARA_FIRST 0 );

          /* canStatus is only set to init and online, if CanInit() is called for this channel. */
#if defined( C_KOMMENTAR_VECTOR_LI13 )
/* ##LI-: 1.2    CAN-Offline */
#endif
          canStatus[channel]              |= (kCanHwIsInit | kCanTxOn);
        }
      } /* CanLL_InitPowerOnChannelSpecific() == kCanOk */
    } /* iterate channels */
  } /* CanLL_InitPowerOn() == kCanOk */
}
/* END OF CanInitPowerOn */
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
/* **********************************************************************
* NAME:               CanDelQueuedObj
* CALLED BY:
* PRECONDITIONS:
* PARAMETER:          notify: if set to 1 for every deleted obj the appl is notified
* RETURN VALUE:       -
* DESCRIPTION:        Resets the bits with are set to 0 in mask
*                     Clearing the Transmit-queue
*********************************************************************** */
/* CODE CATEGORY 4 START */
static void CanDelQueuedObj( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3
{
  CanSignedTxHandle     queueElementIdx;
  #if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
  CanSignedTxHandle     elementBitIdx;
  CanTransmitHandle     txHandle;
  tCanQueueElementType  elem;
  #endif

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(channel < kCanNumberOfChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);
# endif

  #  if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
  if((canStatus[channel] & kCanHwIsInit) == kCanHwIsInit) /* PRQA S 3689 */ /* MD_Can_3689 */
  {
    CAN_CAN_INTERRUPT_DISABLE(CAN_CHANNEL_CANPARA_ONLY);        /* avoid interruption by CanHL_TxConfirmation */
    for(queueElementIdx = CAN_HL_TXQUEUE_STARTINDEX(channel); queueElementIdx < CAN_HL_TXQUEUE_STOPINDEX(channel); queueElementIdx++) /* PRQA S 3689 */ /* MD_Can_3689 */
    {
      elem = canTxQueueFlags[queueElementIdx];
      if(elem != (tCanQueueElementType)0) /* is there any flag set in the queue element? */
      {
        /* iterate through all flags and notify application for every scheduled transmission */
        for(elementBitIdx = ((CanSignedTxHandle)1 << kCanTxQueueShift) - (CanSignedTxHandle)1; elementBitIdx >= (CanSignedTxHandle)0; elementBitIdx--)
        {
          if( ( elem & CanShiftLookUp[elementBitIdx] ) != (tCanQueueElementType)0)
          {
            txHandle = (CanTransmitHandle)((((CanTransmitHandle)queueElementIdx << kCanTxQueueShift) + (CanTransmitHandle)elementBitIdx) - CAN_HL_TXQUEUE_PADBITS(channel)); /* PRQA S 3689 */ /* MD_Can_3689 */ /* ESCAN00039235 */
            APPLCANCANCELNOTIFICATION(channel, txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
          }
        }
        canTxQueueFlags[queueElementIdx] = (tCanQueueElementType)0;
      }
    }
    CAN_CAN_INTERRUPT_RESTORE(CAN_CHANNEL_CANPARA_ONLY);
  }
  else
  #  endif
  {
    for(queueElementIdx = CAN_HL_TXQUEUE_STARTINDEX(channel); queueElementIdx < CAN_HL_TXQUEUE_STOPINDEX(channel); queueElementIdx++) /* PRQA S 3689 */ /* MD_Can_3689 */
    {
      canTxQueueFlags[queueElementIdx] = (tCanQueueElementType)0;
    }
  }

}
/* CODE CATEGORY 4 END */
#endif

#if defined( C_ENABLE_CAN_TRANSMIT )
# if defined( C_ENABLE_CAN_CANCEL_TRANSMIT )
/* CODE CATEGORY 3 START */
/* **************************************************************************
| NAME:             CanCancelTransmit
| CALLED BY:        Application
| PRECONDITIONS:    none
| INPUT PARAMETERS: Tx-Msg-Handle
| RETURN VALUES:    none
| DESCRIPTION:      delete on Msg-Object
************************************************************************** */
# if defined( C_KOMMENTAR_VECTOR_LI13 )
/* ##LI-: 1.2    CAN-Offline */
# endif
C_API_1 void C_API_2 CanCancelTransmit( CanTransmitHandle txHandle )
{
  CanDeclareGlobalInterruptOldStatus
  CAN_CHANNEL_CANTYPE_LOCAL
  CanObjectHandle        logTxObjHandle; /* PRQA S 0781 */ /* MD_Can_0781 */
# if defined( C_ENABLE_CANCEL_IN_HW )
  tCanTxCancellationInfoStruct txCancellationInfo;
# endif

# if defined( C_ENABLE_TRANSMIT_QUEUE )
  CanSignedTxHandle queueElementIdx; /* index for accessing the tx queue */
  CanSignedTxHandle elementBitIdx;  /* bit index within the tx queue element */
  CanTransmitHandle queueBitPos;  /* physical bitposition of the handle */
# endif

  if (txHandle < kCanNumberOfTxObjects)         /* legal txHandle ? */
  {
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    channel = CanGetChannelOfTxObj(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

# if defined( C_ENABLE_MULTI_ECU_PHYS )
    assertUser(((CanTxIdentityAssignment[txHandle] & V_ACTIVE_IDENTITY_MSK) != (tVIdentityMsk)0 ), channel, kErrorDisabledTxMessage);    /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

    CanNestedGlobalInterruptDisable();
# if defined( C_ENABLE_TRANSMIT_QUEUE )
    #if defined( C_ENABLE_INTERNAL_CHECK ) &&\
        defined( C_MULTIPLE_RECEIVE_CHANNEL )
    if (sizeof(queueBitPos) == 1) /* PRQA S 3325 */ /* MD_Can_3201 */
    { /* PRQA S 3201 */ /* MD_Can_3201 */
      assertInternal( ((vuint16)((vuint16)kCanNumberOfTxObjects + (vuint16)CanTxQueuePadBits[kCanNumberOfChannels-1]) <= 256u), kCanAllChannels, kErrorTxQueueTooManyHandle) /*lint !e572 !e506*/
    }
    else
    {
      if (((sizeof(tCanTxQueuePadBits) == 1) && (kCanNumberOfTxObjects > (65536 - 256))) || (sizeof(tCanTxQueuePadBits) > 1)) /* PRQA S 3325 */ /* MD_Can_3201 */
      { /* PRQA S 3201 */ /* MD_Can_3201 */
        assertInternal( ((vuint32)((vuint32)kCanNumberOfTxObjects + (vuint32)CanTxQueuePadBits[kCanNumberOfChannels-1]) <= 65536u), kCanAllChannels, kErrorTxQueueTooManyHandle) /*lint !e572 !e506*/
      }
    }
    #endif
    queueBitPos  = txHandle + CAN_HL_TXQUEUE_PADBITS(channel);
    queueElementIdx = (CanSignedTxHandle)(queueBitPos >> kCanTxQueueShift); /* get the queue element where to set the flag */
    elementBitIdx  = (CanSignedTxHandle)(queueBitPos & kCanTxQueueMask);   /* get the flag index wihtin the queue element */
    if( (canTxQueueFlags[queueElementIdx] & CanShiftLookUp[elementBitIdx]) != (tCanQueueElementType)0 )
    {
      canTxQueueFlags[queueElementIdx] &= (tCanQueueElementType)~CanShiftLookUp[elementBitIdx]; /* clear flag from the queue */
      APPLCANCANCELNOTIFICATION(channel, txHandle);
    }
# endif

# if defined( C_ENABLE_TX_FULLCAN_OBJECTS )
    logTxObjHandle = (CanObjectHandle)((vsintx)CanGetTxMailbox(txHandle) + CAN_HL_TX_OFFSET_MB_TO_LOG(canHwChannel));
# else
    logTxObjHandle = (CanObjectHandle)((vsintx)CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_MB_TO_LOG(canHwChannel));
# endif/* C_ENABLE_TX_FULLCAN_OBJECTS */
    if (canHandleCurTxObj[logTxObjHandle] == txHandle)
    {
      canHandleCurTxObj[logTxObjHandle] = kCanBufferCancel;

      /* ##RI1.4 - 1.6: CanCancelTransmit and CanCancelMsgTransmit */
# if defined( C_ENABLE_CANCEL_IN_HW )
#  if defined( C_ENABLE_TX_FULLCAN_OBJECTS )
      txCancellationInfo.mailboxHandle = CanGetTxMailbox(txHandle);
#  else
      txCancellationInfo.mailboxHandle = CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel);
#  endif /* C_ENABLE_TX_FULLCAN_OBJECTS */
      txCancellationInfo.hwObjHandle = Can_Mailbox[txCancellationInfo.mailboxHandle].HwObjHandle;
      txCancellationInfo.logTxObjHandle = logTxObjHandle;
      txCancellationInfo.canHandleCurTxObj = canHandleCurTxObj[logTxObjHandle];

      CanLL_TxCancelInHw(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txCancellationInfo);

      canHandleCurTxObj[logTxObjHandle] = txCancellationInfo.canHandleCurTxObj;
# endif /* C_ENABLE_CANCEL_IN_HW */
      APPLCANCANCELNOTIFICATION(channel, txHandle);
    }

    CanNestedGlobalInterruptRestore();
  } /* if (txHandle < kCanNumberOfTxObjects) */
}
/* CODE CATEGORY 3 END */
# endif /* defined( C_ENABLE_CAN_CANCEL_TRANSMIT ) */

#endif /* if defined( C_ENABLE_CAN_TRANSMIT ) */

#if defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )
/* **************************************************************************
| NAME:             CanCancelMsgTransmit
| CALLED BY:        Application
| PRECONDITIONS:    none
| INPUT PARAMETERS: none or channel
| RETURN VALUES:    none
| DESCRIPTION:      delete on Msg-Object
************************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 void C_API_2 CanCancelMsgTransmit( CAN_CHANNEL_CANTYPE_ONLY )
{
  CanDeclareGlobalInterruptOldStatus
  CanObjectHandle  logTxObjHandle; /* PRQA S 0781 */ /* MD_Can_0781 */
# if defined( C_ENABLE_CANCEL_IN_HW )
  tCanTxCancellationInfoStruct txCancellationInfo;
# endif

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);    /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

  logTxObjHandle = (CanObjectHandle)((vsintx)CAN_HL_MB_MSG_TRANSMIT_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_MB_TO_LOG(canHwChannel));    /* PRQA S 3689 */ /* MD_Can_3689 */

  CanNestedGlobalInterruptDisable();
  if (canHandleCurTxObj[logTxObjHandle] == kCanBufferMsgTransmit)
  {
    canHandleCurTxObj[logTxObjHandle] = kCanBufferCancel;

    /* ##RI1.4 - 1.6: CanCancelTransmit and CanCancelMsgTransmit */
# if defined( C_ENABLE_CANCEL_IN_HW )
    txCancellationInfo.mailboxHandle = CAN_HL_MB_MSG_TRANSMIT_INDEX(canHwChannel); /* PRQA S 3689 */ /* MD_Can_3689 */
    txCancellationInfo.hwObjHandle = Can_Mailbox[txCancellationInfo.mailboxHandle].HwObjHandle;
    txCancellationInfo.logTxObjHandle = logTxObjHandle;
    txCancellationInfo.canHandleCurTxObj = canHandleCurTxObj[logTxObjHandle];

    CanLL_TxCancelInHw(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txCancellationInfo);

    canHandleCurTxObj[logTxObjHandle] = txCancellationInfo.canHandleCurTxObj;
# endif
    APPLCANMSGCANCELNOTIFICATION(channel); /* PRQA S 3689 */ /* MD_Can_3689 */
  }
  CanNestedGlobalInterruptRestore();
}
/* CODE CATEGORY 3 END */
#endif

#if defined( C_ENABLE_CAN_TRANSMIT )
# if defined( C_ENABLE_VARIABLE_DLC )
/* CODE CATEGORY 2 START */
/* **************************************************************************
| NAME:             CanTransmitVarDLC
| CALLED BY:        Netmanagement, application
| PRECONDITIONS:    Can driver must be initialized
| INPUT PARAMETERS: Handle to Tx message, DLC of Tx message
| RETURN VALUES:    kCanTxFailed: transmit failed
|                   kCanTxOk    : transmit was succesful
| DESCRIPTION:      If the CAN driver is not ready for send, the application
|                   decide, whether the transmit request is repeated or not.
************************************************************************** */
C_API_1 vuint8 C_API_2 CanTransmitVarDLC(CanTransmitHandle txHandle, vuint8 dlc) C_API_3
{
  assertUser(dlc < (vuint8)9, kCanAllChannels, kErrorTxDlcTooLarge);
  assertUser(txHandle < kCanNumberOfTxObjects, kCanAllChannels, kErrorTxHdlTooLarge);

  canTxDLC_RAM[ txHandle ] = (tCanDlc)((canTxDLC_RAM[ txHandle ] & CanLL_DlcMask) | MK_TX_DLC(dlc)); /* PRQA S 3689 */ /* MD_Can_3689 */

  return CanTransmit( txHandle );
} /* END OF CanTransmitVarDLC */
/* CODE CATEGORY 2 END */
# endif /* C_ENABLE_VARIABLE_DLC */

/* **************************************************************************
| NAME:             CanTransmit
| CALLED BY:        application
| PRECONDITIONS:    Can driver must be initialized
| INPUT PARAMETERS: Handle of the transmit object to be send
| RETURN VALUES:    kCanTxFailed: transmit failed
|                   kCanTxOk    : transmit was succesful
| DESCRIPTION:      If the CAN driver is not ready for send, the application
|                   decide, whether the transmit request is repeated or not.
************************************************************************** */
/* CODE CATEGORY 2 START */

C_API_1 vuint8 C_API_2 CanTransmit(CanTransmitHandle txHandle) C_API_3   /* lint !e14 !e31 */
{
  CanDeclareGlobalInterruptOldStatus

# if !defined( C_ENABLE_TX_POLLING )          ||\
     !defined( C_ENABLE_TRANSMIT_QUEUE )      ||\
     defined( C_ENABLE_TX_FULLCAN_OBJECTS )   ||\
     defined( C_ENABLE_INDIVIDUAL_POLLING )
  CanObjectHandle      txMailboxHandle;
  CanObjectHandle      logTxObjHandle; /* PRQA S 0781 */ /* MD_Can_0781 */
  vuint8               rc;
# endif /* ! C_ENABLE_TX_POLLING  || ! C_ENABLE_TRANSMIT_QUEUE || C_ENABLE_TX_FULLCAN_OBJECTS || C_ENABLE_INDIVIDUAL_POLLING */
  CAN_CHANNEL_CANTYPE_LOCAL

# if defined( C_ENABLE_TRANSMIT_QUEUE )
  CanSignedTxHandle queueElementIdx; /* index for accessing the tx queue */
  CanSignedTxHandle elementBitIdx;  /* bit index within the tx queue element */
  CanTransmitHandle queueBitPos;  /* physical bitposition of the handle */
# endif

  assertUser(txHandle<kCanNumberOfTxObjects, kCanAllChannels, kErrorTxHdlTooLarge);

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle);    /* PRQA S 3689 */ /* MD_Can_3689 */ /* lint !e661 */
# endif

# if defined( C_ENABLE_MULTI_ECU_PHYS )
  assertUser(((CanTxIdentityAssignment[txHandle] & V_ACTIVE_IDENTITY_MSK) != (tVIdentityMsk)0 ), channel, kErrorDisabledTxMessage);    /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

  /* test offline ---------------------------------------------------------- */
  if ( (canStatus[channel] & kCanTxOn) != kCanTxOn )           /* transmit path switched off */
  {
    return kCanTxFailed;
  }

# if defined( C_ENABLE_PART_OFFLINE )
  if ( (canTxPartOffline[channel] & CanTxSendMask[txHandle]) != (vuint8)0)  /* PRQA S 3689 */ /* MD_Can_3689 */ /* lint !e661 */ /* CAN off ? */
  {
    return (kCanTxPartOffline);
  }
# endif

# if defined( C_ENABLE_CAN_RAM_CHECK )
  if(canComStatus[channel] == kCanDisableCommunication) /* PRQA S 3689 */ /* MD_Can_3689 */
  {
    return(kCanCommunicationDisabled);
  }
# endif

# if defined( C_ENABLE_SLEEP_WAKEUP )
  assertUser(!CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanSleep);
# endif
  assertUser(!CanLL_HwIsStop(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanStop);

  /* passive mode ---------------------------------------------------------- */
# if defined( C_ENABLE_ECU_SWITCH_PASS )
  if ( canPassive[channel] != (vuint8)0)                             /*  set passive ? */
  {
#  if defined( C_ENABLE_CAN_TX_CONF_FCT ) || \
      defined( C_ENABLE_CONFIRMATION_FCT )
    CAN_CAN_INTERRUPT_DISABLE(channel);      /* avoid CAN Rx interruption */
#  endif

#  if defined( C_ENABLE_CAN_TX_CONF_FCT )
/* ##RI-1.10 Common Callbackfunction in TxInterrupt */
    txInfoStructConf[channel].Handle  = txHandle;
    APPL_CAN_TX_CONFIRMATION(&txInfoStructConf[channel]);
#  endif

#  if defined( C_ENABLE_CONFIRMATION_FLAG )       /* set transmit ready flag  */
#   if C_SECURITY_LEVEL > 20
    CanNestedGlobalInterruptDisable();
#   endif
    CanConfirmationFlags._c[CanGetConfirmationOffset(txHandle)] |= CanGetConfirmationMask(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */    /* lint !e661 */
#   if C_SECURITY_LEVEL > 20
    CanNestedGlobalInterruptRestore();
#   endif
#  endif

#  if defined( C_ENABLE_CONFIRMATION_FCT )
    {
      if ( CanGetApplConfirmationPtr(txHandle) != V_NULL ) /* PRQA S 3689 */ /* MD_Can_3689 */
      {
         (CanGetApplConfirmationPtr(txHandle))(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */ /* call completion routine  */
      }
    }
#  endif /* C_ENABLE_CONFIRMATION_FCT */

#  if defined( C_ENABLE_CAN_TX_CONF_FCT ) || \
      defined( C_ENABLE_CONFIRMATION_FCT )
    CAN_CAN_INTERRUPT_RESTORE(channel);
#  endif

    return kCanTxOk;
  }
# endif

   /* can transmit enabled ================================================== */

   /* ----------------------------------------------------------------------- */
   /* ---  transmit queue with one objects ---------------------------------- */
   /* ---  transmit using fullcan objects ----------------------------------- */
   /* ----------------------------------------------------------------------- */

# if !defined( C_ENABLE_TX_POLLING )          ||\
     !defined( C_ENABLE_TRANSMIT_QUEUE )      ||\
     defined( C_ENABLE_TX_FULLCAN_OBJECTS )   ||\
     defined( C_ENABLE_INDIVIDUAL_POLLING )
#   if defined( C_ENABLE_TX_FULLCAN_OBJECTS )
  txMailboxHandle = CanGetTxMailbox(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */  /* lint !e661 */
#   else
  txMailboxHandle = CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel);
#   endif
  logTxObjHandle = (CanObjectHandle)((vsintx)txMailboxHandle + CAN_HL_TX_OFFSET_MB_TO_LOG(canHwChannel));
# endif /* ! C_ENABLE_TX_POLLING  || ! C_ENABLE_TRANSMIT_QUEUE || C_ENABLE_TX_FULLCAN_OBJECTS || C_ENABLE_INDIVIDUAL_POLLING */

  CanNestedGlobalInterruptDisable();

  /* test offline after interrupt disable ---------------------------------- */
  if ( (canStatus[channel] & kCanTxOn) != kCanTxOn )                /* transmit path switched off */
  {
    CanNestedGlobalInterruptRestore();
    return kCanTxFailed;
  }

# if defined( C_ENABLE_TRANSMIT_QUEUE )
#  if defined( C_ENABLE_TX_FULLCAN_OBJECTS )  ||\
      !defined( C_ENABLE_TX_POLLING )         ||\
      defined( C_ENABLE_INDIVIDUAL_POLLING )
  if (
#   if defined( C_ENABLE_TX_FULLCAN_OBJECTS )
       (txMailboxHandle == CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel))                                   /* disabled - lint !e774 */
#   endif
#   if defined( C_ENABLE_TX_FULLCAN_OBJECTS )  &&\
       ( !defined( C_ENABLE_TX_POLLING )         ||\
          defined( C_ENABLE_INDIVIDUAL_POLLING ) )
     &&
#   endif

#   if defined( C_ENABLE_TX_POLLING )
#    if defined( C_ENABLE_INDIVIDUAL_POLLING )
       ( ( Can_Mailbox[txMailboxHandle].HwObjPolling != (vuint8)0 )       /* Object is used in polling mode! */
                         || (canHandleCurTxObj[logTxObjHandle] != kCanBufferFree) )    /* MsgObj used?  */
#    else
        /* write always to queue; transmission is started out of TxTask */
#    endif
#   else
       ( canHandleCurTxObj[logTxObjHandle] != kCanBufferFree)    /* MsgObj used?  */
#   endif
     )
#  endif /*  ( C_ENABLE_TX_FULLCAN_OBJECTS )  || !( C_ENABLE_TX_POLLING ) || ( C_ENABLE_INDIVIDUAL_POLLING ) */

    {
      /* tx object 0 used -> set msg in queue: ----------------------------- */
      queueBitPos  = txHandle + CAN_HL_TXQUEUE_PADBITS(channel);
      queueElementIdx = (CanSignedTxHandle)(queueBitPos >> kCanTxQueueShift); /* get the queue element where to set the flag */
      elementBitIdx  = (CanSignedTxHandle)(queueBitPos & kCanTxQueueMask);   /* get the flag index wihtin the queue element */
      canTxQueueFlags[queueElementIdx] |= CanShiftLookUp[elementBitIdx];
      CanNestedGlobalInterruptRestore();
      return kCanTxOk;
  }
# endif /* C_ENABLE_TRANSMIT_QUEUE */

# if !defined( C_ENABLE_TX_POLLING )          ||\
     !defined( C_ENABLE_TRANSMIT_QUEUE )      ||\
     defined( C_ENABLE_TX_FULLCAN_OBJECTS )   ||\
     defined( C_ENABLE_INDIVIDUAL_POLLING )

#  if defined( C_ENABLE_TRANSMIT_QUEUE )    && \
      ( defined( C_ENABLE_TX_FULLCAN_OBJECTS )  ||\
        !defined( C_ENABLE_TX_POLLING )         ||\
        defined( C_ENABLE_INDIVIDUAL_POLLING )  )
  else
#  endif
  {
  /* check for transmit message object free --------------------------------- */
    if (   ( canHandleCurTxObj[logTxObjHandle] != kCanBufferFree )    /* MsgObj used?  */
//暂时屏蔽不涉及邮�		  || ( !CanLL_TxIsObjFree(canHwChannel, Can_Mailbox[txMailboxHandle].HwObjHandle) )

      /* hareware-txObject is not free -------------------------------------- */
       )  /* end of if question */

    {  /* object used */
      /* tx object n used, quit with error */
      CanNestedGlobalInterruptRestore();
      return kCanTxFailed;
    }
  }

  /* Obj, pMsgObject points to is free, transmit msg object: ---------------- */
  canHandleCurTxObj[logTxObjHandle] = txHandle; /* Save hdl of msgObj to be transmitted */
  CanNestedGlobalInterruptRestore();

  rc = CanCopyDataAndStartTransmission( CAN_CHANNEL_CANPARA_FIRST txMailboxHandle, txHandle);

#  if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
  if ( rc == kCanTxNotify)
  {
    rc = kCanTxFailed;      /* ignore notification if calls of CanCopy.. is performed within CanTransmit */
  }
#  endif

  return(rc);

# else /* ! C_ENABLE_TX_POLLING  || ! C_ENABLE_TRANSMIT_QUEUE || C_ENABLE_TX_FULLCAN_OBJECTS || C_ENABLE_INDIVIDUAL_POLLING */
#  if defined( C_KOMMENTAR_VECTOR )
  /* ##Ht: which Compiler needs this? It is not Tasking C16x */
  /*   return kCanTxFailed;                      compiler-dummy  */
#  endif
# endif /* ! C_ENABLE_TX_POLLING  || ! C_ENABLE_TRANSMIT_QUEUE || C_ENABLE_TX_FULLCAN_OBJECTS || C_ENABLE_INDIVIDUAL_POLLING */
}
/* END OF CanTransmit */
/* CODE CATEGORY 2 END */

/* **************************************************************************
| NAME:             CanCopyDataAndStartTransmission
| CALLED BY:        CanTransmit, CanHL_RestartTxQueue and CanHL_TxConfirmation
| PRECONDITIONS:    - Can driver must be initialized
|                   - canTxCurHandle[logTxObjHandle] must be set
|                   - the hardwareObject (txObjHandle) must be free
| INPUT PARAMETERS: txHandle: Handle of the transmit object to be send
|                   txObjHandle:  Nr of the HardwareObjects to use
| RETURN VALUES:    kCanTxFailed: transmit failed
|                   kCanTxOk    : transmit was succesful
| DESCRIPTION:      If the CAN driver is not ready for send, the application
|                   decide, whether the transmit request is repeated or not.
************************************************************************** */
/* CODE CATEGORY 1 START */
static vuint8 CanCopyDataAndStartTransmission( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txMailboxHandle, CanTransmitHandle txHandle) C_API_3   /* lint !e14 !e31 */
{
   CanDeclareGlobalInterruptOldStatus
   vuint8               rc;
   CanObjectHandle      logTxObjHandle;  /* PRQA S 0781 */ /* MD_Can_0781 */


#  if defined( C_ENABLE_COPY_TX_DATA )
   TxDataPtr   CanMemCopySrcPtr;   /* PRQA S 0781 */ /* MD_Can_0781 */
#  endif
# if defined( C_ENABLE_DYN_TX_OBJECTS )
   CanTransmitHandle    dynTxObj;
# endif   /* C_ENABLE_DYN_TX_OBJECTS */
# if defined( C_ENABLE_PRETRANSMIT_FCT )
   CanTxInfoStruct      txStruct;  /* PRQA S 0781 */ /* MD_Can_0781 */
# endif
   tCanTxTransmissionInfoStruct txInfo;


# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
   assertInternal(channel < kCanNumberOfChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);
# endif
   assertInternal(txHandle < kCanNumberOfTxObjects, kCanAllChannels, kErrorInternalTxHdlTooLarge);

# if defined( C_ENABLE_DYN_TX_OBJECTS )
#  if ( kCanNumberOfTxStatObjects == 0)
   dynTxObj = txHandle;               /* only dynamic messages are used */
#  else  /* ( kCanNumberOfTxStatObjects == 0) */
   /* dynamic and static messages are in the system */
   if (txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel))  /* PRQA S 3689 */ /* MD_Can_3689 */
   {
     dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel);    /* PRQA S 3382,0291,3689 */ /* MD_Can_3382,MD_Can_0291,MD_Can_3689 */
   }
   else
   {
     dynTxObj = kCanTxHandleNotUsed;
   }
#  endif  /* ( kCanNumberOfTxStatObjects == 0) */
# endif  /* C_ENABLE_DYN_TX_OBJECTS */

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
   assertInternal(txMailboxHandle >= CAN_HL_MB_TX_STARTINDEX(canHwChannel), channel, kErrorTxObjHandleWrong);     /* PRQA S 3689 */ /* MD_Can_3689 */
#  else
#   if (kCanMailboxTxStartIndex != 0)
   assertInternal(txMailboxHandle >= CAN_HL_MB_TX_STARTINDEX(canHwChannel), channel, kErrorTxObjHandleWrong);
#   endif
#  endif
   assertInternal(txMailboxHandle < CAN_HL_MB_TX_STOPINDEX(canHwChannel), channel, kErrorTxObjHandleWrong);      /* PRQA S 3689 */ /* MD_Can_3689 */
   logTxObjHandle = (CanObjectHandle)((vsintx)txMailboxHandle + CAN_HL_TX_OFFSET_MB_TO_LOG(canHwChannel));       /* PRQA S 3689 */ /* MD_Can_3689 */

   assertHardware(CanLL_TxIsObjFree(canHwChannel, Can_Mailbox[txMailboxHandle].HwObjHandle), channel, kErrorTxBufferBusy);  /* PRQA S 3689 */ /* MD_Can_3689 */

   txInfo.mailboxHandle = txMailboxHandle;
   txInfo.hwObjHandle = Can_Mailbox[txMailboxHandle].HwObjHandle;
   txInfo.logTxObjHandle = logTxObjHandle;

   CanLL_TxBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txInfo);

   /* set id and dlc  -------------------------------------------------------- */
   {
# if defined( C_ENABLE_DYN_TX_DLC ) || \
      defined( C_ENABLE_DYN_TX_ID )
     if (dynTxObj < kCanNumberOfTxDynObjects)
     {          /* set dynamic part of dynamic objects ---------------------- */
#  if defined( C_ENABLE_DYN_TX_ID )
        txInfo.idRaw0 = canDynTxId0[dynTxObj];
#   if (kCanNumberOfUsedCanTxIdTables > 1)
        txInfo.idRaw1 = canDynTxId1[dynTxObj];
#   endif
#   if (kCanNumberOfUsedCanTxIdTables > 2)
        txInfo.idRaw2 = canDynTxId2[dynTxObj];
#   endif
#   if (kCanNumberOfUsedCanTxIdTables > 3)
        txInfo.idRaw3 = canDynTxId3[dynTxObj];
#   endif
#   if (kCanNumberOfUsedCanTxIdTables > 4)
        txInfo.idRaw4 = canDynTxId4[dynTxObj];
#   endif
#   if defined( C_ENABLE_CAN_FD_USED )
        txInfo.fdType = canDynTxFdType[dynTxObj];
#   endif
#  endif
#  if defined( C_ENABLE_DYN_TX_DLC )
        txInfo.dlcRaw = canDynTxDLC[dynTxObj];
#   if defined( C_ENABLE_CAN_FD_FULL ) && defined( C_ENABLE_COPY_TX_DATA )
        txInfo.messageLen = canDynTxMessageLength[dynTxObj];
#   endif
#  endif
     }
     else
     {           /* set part of static objects assocciated the dynamic -------- */
#  if defined( C_ENABLE_DYN_TX_ID )
#   if defined( C_ENABLE_TX_MASK_EXT_ID )
#    if defined( C_ENABLE_MIXED_ID )
        if (CanGetTxIdType(txHandle)==kCanIdTypeStd)  /* PRQA S 3689 */ /* MD_Can_3689 */
        {
          txInfo.idRaw0 = CanGetTxId0(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#     if (kCanNumberOfUsedCanTxIdTables > 1)
          txInfo.idRaw1 = CanGetTxId1(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#     endif
#     if (kCanNumberOfUsedCanTxIdTables > 2)
          txInfo.idRaw2 = CanGetTxId2(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#     endif
#     if (kCanNumberOfUsedCanTxIdTables > 3)
          txInfo.idRaw3 = CanGetTxId3(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
#     endif
#     if (kCanNumberOfUsedCanTxIdTables > 4)
          txInfo.idRaw4 = CanGetTxId4(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#     endif
        }
        else
#    endif
        {
        	  /* mask extened ID */
          txInfo.idRaw0 = (CanGetTxId0(txHandle)|canTxMask0[channel]);  /* PRQA S 3689 */ /* MD_Can_3689 */
#    if (kCanNumberOfUsedCanTxIdTables > 1)
          txInfo.idRaw1 = (CanGetTxId1(txHandle)|canTxMask1[channel]);  /* PRQA S 3689 */ /* MD_Can_3689 */
#    endif
#    if (kCanNumberOfUsedCanTxIdTables > 2)
          txInfo.idRaw2 = (CanGetTxId2(txHandle)|canTxMask2[channel]);  /* PRQA S 3689 */ /* MD_Can_3689 */
#    endif
#    if (kCanNumberOfUsedCanTxIdTables > 3)
          txInfo.idRaw3 = (CanGetTxId3(txHandle)|canTxMask3[channel]);  /* PRQA S 3689 */ /* MD_Can_3689 */
#    endif
#    if (kCanNumberOfUsedCanTxIdTables > 4)
          txInfo.idRaw4 = (CanGetTxId4(txHandle)|canTxMask4[channel]);  /* PRQA S 3689 */ /* MD_Can_3689 */
#    endif
        }
#   else
        txInfo.idRaw0 = CanGetTxId0(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#    if (kCanNumberOfUsedCanTxIdTables > 1)
        txInfo.idRaw1 = CanGetTxId1(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#    endif
#    if (kCanNumberOfUsedCanTxIdTables > 2)
        txInfo.idRaw2 = CanGetTxId2(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
#    endif
#    if (kCanNumberOfUsedCanTxIdTables > 3)
        txInfo.idRaw3 = CanGetTxId3(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#    endif
#    if (kCanNumberOfUsedCanTxIdTables > 4)
        txInfo.idRaw4 = CanGetTxId4(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#    endif
#   endif
#   if defined( C_ENABLE_CAN_FD_USED )
        txInfo.fdType = kCanFdTypeClassic; //JJH CanGetTxFdType(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
#   endif
#  endif

#  if defined( C_ENABLE_DYN_TX_DLC )
#   if defined( C_ENABLE_VARIABLE_DLC )
        /* init DLC, RAM */
        txInfo.dlcRaw = canTxDLC_RAM[txHandle];  /* PRQA S 3689 */ /* MD_Can_3689 */
#   else
         /* init DLC, ROM */
        txInfo.dlcRaw = CanGetTxDlc(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#    if defined( C_ENABLE_CAN_FD_FULL ) && defined( C_ENABLE_COPY_TX_DATA )
        txInfo.messageLen = CanGetTxMessageLength(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#    endif
#   endif
#  endif
     }
# endif
     /* set static part commen for static and dynamic objects ---------------- */
# if defined( C_ENABLE_DYN_TX_ID )
# else
#  if defined( C_ENABLE_TX_MASK_EXT_ID )
#   if defined( C_ENABLE_MIXED_ID )
     if (CanGetTxIdType(txHandle)==kCanIdTypeStd)  /* PRQA S 3689 */ /* MD_Can_3689 */
     {
       txInfo.idRaw0 = CanGetTxId0(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#    if (kCanNumberOfUsedCanTxIdTables > 1)
       txInfo.idRaw1 = CanGetTxId1(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#    endif
#    if (kCanNumberOfUsedCanTxIdTables > 2)
       txInfo.idRaw2 = CanGetTxId2(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#    endif
#    if (kCanNumberOfUsedCanTxIdTables > 3)
       txInfo.idRaw3 = CanGetTxId3(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#    endif
#    if (kCanNumberOfUsedCanTxIdTables > 4)
       txInfo.idRaw4 = CanGetTxId4(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#    endif
     }
     else
#   endif
     {
    	 /* mask extened ID */
       txInfo.idRaw0 = (CanGetTxId0(txHandle)|canTxMask0[channel]);  /* PRQA S 3689 */ /* MD_Can_3689 */
#   if (kCanNumberOfUsedCanTxIdTables > 1)
       txInfo.idRaw1 = (CanGetTxId1(txHandle)|canTxMask1[channel]);  /* PRQA S 3689 */ /* MD_Can_3689 */
#   endif
#   if (kCanNumberOfUsedCanTxIdTables > 2)
       txInfo.idRaw2 = (CanGetTxId2(txHandle)|canTxMask2[channel]); /* PRQA S 3689 */ /* MD_Can_3689 */
#   endif
#   if (kCanNumberOfUsedCanTxIdTables > 3)
       txInfo.idRaw3 = (CanGetTxId3(txHandle)|canTxMask3[channel]); /* PRQA S 3689 */ /* MD_Can_3689 */
#   endif
#   if (kCanNumberOfUsedCanTxIdTables > 4)
       txInfo.idRaw4 = (CanGetTxId4(txHandle)|canTxMask4[channel]);  /* PRQA S 3689 */ /* MD_Can_3689 */
#   endif
     }
#  else
     txInfo.idRaw0 = CanGetTxId0(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#   if (kCanNumberOfUsedCanTxIdTables > 1)
     txInfo.idRaw1 = CanGetTxId1(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#   endif
#   if (kCanNumberOfUsedCanTxIdTables > 2)
     txInfo.idRaw2 = CanGetTxId2(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#   endif
#   if (kCanNumberOfUsedCanTxIdTables > 3)
     txInfo.idRaw3 = CanGetTxId3(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#   endif
#   if (kCanNumberOfUsedCanTxIdTables > 4)
     txInfo.idRaw4 = CanGetTxId4(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#   endif
#  endif
#  if defined( C_ENABLE_CAN_FD_USED )
     txInfo.fdType = CanGetTxFdType(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
# endif
# if defined( C_ENABLE_DYN_TX_DLC )
# else
#  if defined( C_ENABLE_VARIABLE_DLC )
     /* init DLC, RAM */
     txInfo.dlcRaw = canTxDLC_RAM[txHandle];  /* PRQA S 3689 */ /* MD_Can_3689 */
#  else
     /* init DLC, ROM */
     txInfo.dlcRaw = CanGetTxDlc(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#   if defined( C_ENABLE_CAN_FD_FULL ) && defined( C_ENABLE_COPY_TX_DATA )
     txInfo.messageLen = CanGetTxMessageLength(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#   endif
#  endif
# endif

# if defined( C_ENABLE_MIXED_ID )
#   if defined( C_ENABLE_DYN_TX_DLC ) || \
       defined( C_ENABLE_DYN_TX_ID )
     if (dynTxObj < kCanNumberOfTxDynObjects)
     {                       /* set dynamic part of dynamic objects */
#    if defined( C_ENABLE_DYN_TX_ID )
       txInfo.idType = canDynTxIdType[dynTxObj];
#    else
       txInfo.idType = CanGetTxIdType(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
#    endif
     }
     else
     {
       txInfo.idType = CanGetTxIdType(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
     }
#   else
#   endif
# endif

# if defined( C_ENABLE_CAN_FD_USED )
#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
     assertGen(((txInfo.fdType == kCanFdTypeClassic) || (CAN_HL_IS_CH_CANFD(channel) == kCanTrue)), channel, kErrorWrongCanFdFlag);  /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
#  if defined( C_ENABLE_CAN_FD_SUPPRESS_BRS )
     txInfo.fdBrsType = kCanFdBrsTypeFalse;
#  else
     if (txInfo.fdType == kCanFdTypeFd)
     {
       txInfo.fdBrsType = kCanFdBrsTypeTrue;
     }
     else
     {
       txInfo.fdBrsType = kCanFdBrsTypeFalse;
     }
#  endif
# endif

# if defined( C_ENABLE_CAN_FD_FULL ) && defined( C_ENABLE_COPY_TX_DATA )
     assertGen(txInfo.messageLen <= CAN_HL_MAX_LEN(channel), channel, kErrorTxROMDLCTooLarge);  /* PRQA S 3689 */ /* MD_Can_3689 */
     txInfo.frameLen = CAN_DLC2LEN(CAN_LEN2DLC(txInfo.messageLen));  /* PRQA S 3689 */ /* MD_Can_3689 */
     assertGen(txInfo.frameLen <= Can_Mailbox[txMailboxHandle].HwObjMaxDataLen, channel, kErrorTxROMDLCTooLarge);
     txInfo.paddingVal = (vuint8)C_CAN_FD_PADDING_VALUE;
# endif
   }

   CanLL_TxSetMailbox(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txInfo);

   /* call pretransmit function ----------------------------------------------- */
# if defined( C_ENABLE_PRETRANSMIT_FCT )

   /* pointer needed for other modules */
   CanLL_TxSetTxStruct(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txInfo);
   txStruct = txInfo.txStruct;

   canRDSTxPtr[logTxObjHandle] = txStruct.pChipData;  /* PRQA S 3689 */ /* MD_Can_3689 */
   txStruct.Handle = txHandle;

   {
	   /* Is there a PreTransmit function ? ------------------------------------- */
    if ( CanGetApplPreTransmitPtr(txHandle) != V_NULL )     /* PRQA S 3689 */ /* MD_Can_3689 */  /* if PreTransmit exists */
    {
      if ( (CanGetApplPreTransmitPtr(txHandle)) (txStruct) == kCanNoCopyData)   /* PRQA S 3689 */ /* MD_Can_3689 */
      {
        CanLL_TxPretransmitCopyToCan(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txInfo);

        /* Do not copy the data - already done by the PreTransmit-function */
               /* --- start transmission --- */
        goto startTransmission;
      }
    }
   }
# endif /* C_ENABLE_PRETRANSMIT_FCT */

   /* copy data --------------------------------------------------------------- */
# if defined( C_ENABLE_COPY_TX_DATA )
#  if defined( C_ENABLE_DYN_TX_DATAPTR )
   if (dynTxObj < kCanNumberOfTxDynObjects)
   {
      CanMemCopySrcPtr = canDynTxDataPtr[dynTxObj];
   }
   else
#  endif
   {
     CanMemCopySrcPtr = CanGetTxDataPtr(txHandle);   /* PRQA S 3689 */ /* MD_Can_3689 */
   }
   /* copy via index in MsgObj data field, copy always 8 bytes ----------- */
   if ( CanMemCopySrcPtr != V_NULL )   /* copy if buffer exists */
   {
#  if C_SECURITY_LEVEL > 10
     CanNestedGlobalInterruptDisable();
#  endif

     txInfo.CanMemCopySrcPtr = CanMemCopySrcPtr;
     CanLL_TxCopyToCan(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txInfo);

#  if C_SECURITY_LEVEL > 10
     CanNestedGlobalInterruptRestore();
#  endif
   }
# endif /* ( C_ENABLE_COPY_TX_DATA ) */

   CANDRV_SET_CODE_TEST_POINT(0x10A);

# if defined( C_ENABLE_PRETRANSMIT_FCT )
   /* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
startTransmission:
# endif

/*  test offline and handle and start transmission ------------------------*/
   CanNestedGlobalInterruptDisable();
   /* If CanTransmit was interrupted by a re-initialization or CanOffline */
   /* no transmitrequest of this action should be started      */
   if ((canHandleCurTxObj[logTxObjHandle] == txHandle) && ((canStatus[channel] & kCanTxOn) == kCanTxOn)) /* PRQA S 3689 */ /* MD_Can_3689 */
   {
//     rc = CanLL_TxStart(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txInfo);
	   if(txHandle == CanTxTxDynamicMsg0)
	   {
		  rc= CanDrv_SendStdFrame(CanGetTxId0(0u),CanGetTxDataPtr(txHandle), CanGetTxDlc(txHandle));
	   }
	   else
	   {
		  rc= CanDrv_SendStdFrame(CanGetTxId0(txHandle),CanGetTxDataPtr(txHandle), CanGetTxDlc(txHandle));
	   }
     {
# if defined( C_ENABLE_TX_OBSERVE )
#  if defined( C_KOMMENTAR_VECTOR_RI14 )
    	 /* ##RI-1.1: Object parameters for Tx-Observe functions */
#  endif
       ApplCanTxObjStart( CAN_CHANNEL_CANPARA_FIRST logTxObjHandle );
# endif
       /* explicit set of rc to kCanTxOk not necessary, because kCanTxOk and kCanOk are identical (return of CanLL_TxStart) */
     }
   }
   else
   {
# if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
     if (canHandleCurTxObj[logTxObjHandle] == txHandle) /* PRQA S 3689 */ /* MD_Can_3689 */
     {
    	 /* only CanOffline was called on higher level */
       rc = kCanTxNotify;
     }
     else
# endif
     {
       rc = kCanTxFailed;
     }
     assertInternal((canHandleCurTxObj[logTxObjHandle] == txHandle) || (canHandleCurTxObj[logTxObjHandle] == kCanBufferFree),  /* PRQA S 3689 */ /* MD_Can_3689 */
                                                                                       channel, kErrorTxHandleWrong);
     canHandleCurTxObj[logTxObjHandle] = kCanBufferFree; /* PRQA S 3689 */ /* MD_Can_3689 */ /* release TxHandle (CanOffline) */
   }

   CanNestedGlobalInterruptRestore();

   CanLL_TxEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txInfo);

   return (rc);

}
/* END OF CanCopyDataAndStartTransmission */
/* CODE CATEGORY 1 END */

#endif /* if defined( C_ENABLE_CAN_TRANSMIT ) */

#if defined( C_ENABLE_TX_POLLING ) || \
    defined( C_ENABLE_RX_FULLCAN_POLLING )  || \
    defined( C_ENABLE_RX_BASICCAN_POLLING ) || \
    defined( C_ENABLE_ERROR_POLLING ) || \
    defined( C_ENABLE_WAKEUP_POLLING )
/* **************************************************************************
| NAME:             CanTask
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      - cyclic Task,
|                   - polling error bus off
|                   - polling Tx objects
|                   - polling Rx objects
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanTask(void)
{
  CAN_CHANNEL_CANTYPE_LOCAL

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  for (channel = 0; channel < kCanNumberOfChannels; channel++)
# endif
  {
    {
# if defined( C_ENABLE_ERROR_POLLING )
      CanErrorTask(CAN_CHANNEL_CANPARA_ONLY);
# endif

# if defined( C_ENABLE_SLEEP_WAKEUP )
#  if defined( C_ENABLE_WAKEUP_POLLING )
      CanWakeUpTask(CAN_CHANNEL_CANPARA_ONLY);
#  endif
# endif

# if defined( C_ENABLE_TX_POLLING )
      CanTxTask(CAN_CHANNEL_CANPARA_ONLY);
# endif

# if defined( C_ENABLE_RX_FULLCAN_POLLING ) && \
     defined( C_ENABLE_RX_FULLCAN_OBJECTS )
      CanRxFullCANTask(CAN_CHANNEL_CANPARA_ONLY);
# endif

# if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && \
    defined( C_ENABLE_RX_BASICCAN_POLLING )
      CanRxBasicCANTask(CAN_CHANNEL_CANPARA_ONLY);
# endif
    }
  }
}
/* CODE CATEGORY 2 END */
#endif

#if defined( C_ENABLE_ERROR_POLLING )
/* **************************************************************************
| NAME:             CanErrorTask
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      - cyclic Task,
|                   - polling error status
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanErrorTask( CAN_CHANNEL_CANTYPE_ONLY )
{

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion);     /* PRQA S 3689 */ /* MD_Can_3689 */

  if (canPollingTaskActive[channel] == (vuint8)0) /* PRQA S 3689 */ /* MD_Can_3689 */ /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

    {
# if defined( C_ENABLE_SLEEP_WAKEUP )
      if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY) )
# endif
      {
        CAN_CAN_INTERRUPT_DISABLE(channel);
        CanHL_ErrorHandling(CAN_HW_CHANNEL_CANPARA_ONLY);
        CAN_CAN_INTERRUPT_RESTORE(channel);
      }
    }

    canPollingTaskActive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
  }
}
/* CODE CATEGORY 2 END */
#endif

#if defined( C_ENABLE_SLEEP_WAKEUP )
# if defined( C_ENABLE_WAKEUP_POLLING )
/* **************************************************************************
| NAME:             CanWakeUpTask
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      - cyclic Task,
|                   - polling CAN wakeup event
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanWakeUpTask(CAN_CHANNEL_CANTYPE_ONLY)
{
  CanDeclareGlobalInterruptOldStatus

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#  endif
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion);    /* PRQA S 3689 */ /* MD_Can_3689 */

  if (canPollingTaskActive[channel] == (vuint8)0)  /* PRQA S 3689 */ /* MD_Can_3689 */ /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

    if (CanLL_WakeUpOccured(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY) == kCanTrue)
    {
      CANDRV_SET_CODE_TEST_POINT(0x111);
      CanNestedGlobalInterruptDisable();          /* ESCAN00021223 */
      CanLL_WakeUpHandling(CAN_CHANNEL_CANPARA_ONLY);
      CanNestedGlobalInterruptRestore();          /* ESCAN00021223 */
    }
    canPollingTaskActive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
  }
}
/* CODE CATEGORY 2 END */
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* C_ENABLE_SLEEP_WAKEUP */

#if defined( C_ENABLE_TX_POLLING )
/* **************************************************************************
| NAME:             CanTxTask
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      - cyclic Task,
|                   - polling Tx objects
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanTxTask( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3
{
  CanObjectHandle      txMailboxHandle;
  tCanTaskInfoStruct   taskInfo;

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion);    /* PRQA S 3689 */ /* MD_Can_3689 */

  if (canPollingTaskActive[channel] == (vuint8)0)  /* PRQA S 3689 */ /* MD_Can_3689 */ /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

# if defined( C_ENABLE_SLEEP_WAKEUP )
    if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY) )
# endif
    {
      /* --  polling Tx objects ---------------------------------------- */

# if defined( C_ENABLE_TX_POLLING )
      /* check for global confirmation Pending and may be reset global pending confirmation */
      if (CanLL_TxIsGlobalConfPending(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY) == kCanTrue)
      {
        for ( txMailboxHandle = CAN_HL_MB_TX_STARTINDEX(canHwChannel); txMailboxHandle < CAN_HL_MB_TX_STOPINDEX(canHwChannel); txMailboxHandle++ ) /* PRQA S 3689 */ /* MD_Can_3689 */
        {
#  if defined( C_ENABLE_INDIVIDUAL_POLLING )
          if ( Can_Mailbox[txMailboxHandle].HwObjPolling != (vuint8)0 )
#  endif
          {
            taskInfo.mailboxHandle = txMailboxHandle;
            taskInfo.hwObjHandle = Can_Mailbox[txMailboxHandle].HwObjHandle;

            /* check and process pending confirmations for a dedicated mailbox */
            CanLL_TxProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &taskInfo);
          } /* if individual polling & object has to be polled */
        }
      }
# endif /* ( C_ENABLE_TX_POLLING ) */

# if defined( C_ENABLE_TRANSMIT_QUEUE )
      CanHL_RestartTxQueue( CAN_CHANNEL_CANPARA_ONLY );
# endif /*  C_ENABLE_TRANSMIT_QUEUE */

    } /* if ( CanLL_HwIsSleep... ) */

    canPollingTaskActive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
  }

}
/* END OF CanTxTask */
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_TX_POLLING */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
# if defined( C_ENABLE_TX_POLLING )
/* **************************************************************************
| NAME:             CanHL_RestartTxQueue
| CALLED BY:        CanTxTask, via CanLL (TxMsgDestroyed)
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      start transmission if queue entry exists and HW is free
************************************************************************** */
/* CODE CATEGORY 2 START */
static void CanHL_RestartTxQueue( CAN_CHANNEL_CANTYPE_ONLY )
{
  CanTransmitHandle    txHandle;
#  if  defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
  vuint8             rc;
#  endif
  CanDeclareGlobalInterruptOldStatus

  CanSignedTxHandle         queueElementIdx;    /* use as signed due to loop */
  CanSignedTxHandle         elementBitIdx;
  tCanQueueElementType             elem;

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(channel < kCanNumberOfChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);
#  endif

  if (canHandleCurTxObj[(vsintx)CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_MB_TO_LOG(canHwChannel)] == kCanBufferFree) /* PRQA S 3689 */ /* MD_Can_3689 */
  {
    /* PRQA S 3689 2 */ /* MD_Can_3689 */
    for(queueElementIdx = CAN_HL_TXQUEUE_STOPINDEX(channel) - (CanSignedTxHandle)1;
                             queueElementIdx >= CAN_HL_TXQUEUE_STARTINDEX(channel); queueElementIdx--)
    {
      elem = canTxQueueFlags[queueElementIdx];
      if(elem != (tCanQueueElementType)0) /* is there any flag set in the queue element? */
      {

        /* Transmit Queued Objects */
        /* start the bitsearch */
        #if defined( C_CPUTYPE_32BIT )
        if((elem & (tCanQueueElementType)0xFFFF0000) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
        {
          if((elem & (tCanQueueElementType)0xFF000000) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
          {
            if((elem & (tCanQueueElementType)0xF0000000) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 28] + 28;
            }
            else /* 0x0F000000 */
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 24] + 24;
            }
          }
          else
          {
            if((elem & (tCanQueueElementType)0x00F00000) != (tCanQueueElementType)0)
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 20] + 20;
            }
            else /* 0x000F0000 */
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 16] + 16;
            }
          }
        }
        else
        #endif
        {
        #if defined( C_CPUTYPE_32BIT )
          if((elem & (tCanQueueElementType)0x0000FF00) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
          {
            if((elem & (tCanQueueElementType)0x0000F000) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 12] + 12;
            }
            else /* 0x00000F00 */
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 8] + 8;
            }
          }
          else
        #endif
          {
            if((elem & (tCanQueueElementType)0x000000F0) != (tCanQueueElementType)0)
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 4] + 4;
            }
            else /* 0x0000000F */
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem];
            }
          }
        }
        /* PRQA S 3689 1 */ /* MD_Can_3689 */
        txHandle = (CanTransmitHandle)((((CanTransmitHandle)queueElementIdx << kCanTxQueueShift) + (CanTransmitHandle)elementBitIdx) - CAN_HL_TXQUEUE_PADBITS(channel));
        {

            CanNestedGlobalInterruptDisable();
            if (canHandleCurTxObj[(vsintx)CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_MB_TO_LOG(canHwChannel)] == kCanBufferFree) /* PRQA S 3689 */ /* MD_Can_3689 */
            {
              if ( (canTxQueueFlags[queueElementIdx] & CanShiftLookUp[elementBitIdx]) != (tCanQueueElementType)0 )
              {
                canTxQueueFlags[queueElementIdx] &= (tCanQueueElementType)~CanShiftLookUp[elementBitIdx]; /* clear flag from the queue */
                /* Save hdl of msgObj to be transmitted */
                canHandleCurTxObj[(vsintx)CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_MB_TO_LOG(canHwChannel)] = txHandle; /* PRQA S 3689 */ /* MD_Can_3689 */
                CanNestedGlobalInterruptRestore();
#  if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
                rc = CanCopyDataAndStartTransmission(CAN_CHANNEL_CANPARA_FIRST CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel), txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
                if ( rc == kCanTxNotify)
                {
                  APPLCANCANCELNOTIFICATION(channel, txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
                }
#  else
                (void)CanCopyDataAndStartTransmission(CAN_CHANNEL_CANPARA_FIRST CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel), txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
                return;
              }

            }
            CanNestedGlobalInterruptRestore();
            return;
        }
      }
    }
  }
}
/* End of CanHL_RestartTxQueue */
/* CODE CATEGORY 2 END */
# endif
#endif /*  C_ENABLE_TRANSMIT_QUEUE */

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) && \
    defined( C_ENABLE_RX_FULLCAN_POLLING )
/* **************************************************************************
| NAME:             CanRxFullCANTask
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      - cyclic Task,
|                   - polling Rx FullCAN objects
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxFullCANTask(CAN_CHANNEL_CANTYPE_ONLY) C_API_3
{
  CanObjectHandle     rxMailboxHandle;
  tCanTaskInfoStruct  taskInfo;

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion); /* PRQA S 3689 */ /* MD_Can_3689 */

  if (canPollingTaskActive[channel] == (vuint8)0)  /* PRQA S 3689 */ /* MD_Can_3689 */ /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

    {
# if defined( C_ENABLE_SLEEP_WAKEUP )
      if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY) )
# endif
      {
        /* --  polling fullcan Rx objects ---------------------------------------- */

        /* check for global fullCan Rx indication pending and may be reset global */
        /* indication pending */
        if (CanLL_RxFullIsGlobalIndPending(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY) == kCanTrue)
        {
          for (rxMailboxHandle=CAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel); rxMailboxHandle<CAN_HL_MB_RX_FULL_STOPINDEX(canHwChannel); rxMailboxHandle++ ) /* PRQA S 3689 */ /* MD_Can_3689 */
          {
# if defined( C_ENABLE_INDIVIDUAL_POLLING )
            if ( Can_Mailbox[rxMailboxHandle].HwObjPolling != (vuint8)0 )
# endif
            {
              taskInfo.mailboxHandle = rxMailboxHandle;
              taskInfo.hwObjHandle = Can_Mailbox[rxMailboxHandle].HwObjHandle;

              /* check and process pending indications for a dedicated mailbox */
              CanLL_RxFullProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &taskInfo);
            }  /* if individual polling & object has to be polled */
          } /* for ( rxMailboxHandle ) */
        } /* if (global pending) */
      } /* if ( CanLL_HwIsSleep ... )  */
    }  /* for (all associated HW channel) */
    canPollingTaskActive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
  }

}
/* END OF CanRxTask */
/* CODE CATEGORY 2 END */
#endif /*  C_ENABLE_RX_FULLCAN_OBJECTS && C_ENABLE_RX_FULLCAN_POLLING */

#if defined( C_ENABLE_RX_BASICCAN_POLLING ) && \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/* **************************************************************************
| NAME:             CanRxBasicCANTask
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      - cyclic Task,
|                   - polling Rx BasicCAN objects
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxBasicCANTask(CAN_CHANNEL_CANTYPE_ONLY) C_API_3
{
  CanObjectHandle     rxMailboxHandle;
  tCanTaskInfoStruct  taskInfo;

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion); /* PRQA S 3689 */ /* MD_Can_3689 */

  if (canPollingTaskActive[channel] == (vuint8)0)  /* PRQA S 3689 */ /* MD_Can_3689 */ /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

# if defined( C_ENABLE_SLEEP_WAKEUP )
    if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY) )
# endif
    {

      if (CanLL_RxBasicIsGlobalIndPending(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY) == kCanTrue)
      {
        for (rxMailboxHandle=CAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel); rxMailboxHandle<CAN_HL_MB_RX_BASIC_STOPINDEX(canHwChannel); rxMailboxHandle++ ) /* PRQA S 3689 */ /* MD_Can_3689 */
        {
# if defined( C_ENABLE_INDIVIDUAL_POLLING )
          if ( Can_Mailbox[rxMailboxHandle].HwObjPolling != (vuint8)0 )
# endif
          {
            taskInfo.mailboxHandle = rxMailboxHandle;
            taskInfo.hwObjHandle = Can_Mailbox[rxMailboxHandle].HwObjHandle;

            /* check and process pending indications for a dedicated mailbox */
            CanLL_RxBasicProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &taskInfo);
          } /* if individual polling & object has to be polled */
        }
      }
    } /* if ( CanLL_HwIsSleep... )  */

    canPollingTaskActive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
  }

}
/* END OF CanRxTask */
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_RX_BASICCAN_POLLING && C_ENABLE_RX_BASICCAN_OBJECTS */

/* **************************************************************************
| NAME:             CanHL_ErrorHandling
| CALLED BY:        CanISR(), CanErrorTask()
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      - error interrupt (busoff, error warning, ...)
************************************************************************** */
/* CODE CATEGORY 2 START */
static void CanHL_ErrorHandling( CAN_HW_CHANNEL_CANTYPE_ONLY )
{

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);
#endif

  CanLL_ErrorHandlingBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY);

  /* check for status register (bus error) */
  if (CanLL_BusOffOccured(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY) == kCanTrue)
  {
    /* ==BUS OFF ERROR========================= */
    APPL_CAN_BUSOFF( CAN_CHANNEL_CANPARA_ONLY );     /* PRQA S 3689 */ /* MD_Can_3689 */ /* call application specific function */
  }

  CanLL_ErrorHandlingEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY);

} /* END OF CanHL_ErrorHandling */
/* CODE CATEGORY 2 END */

#if defined( C_ENABLE_INDIVIDUAL_POLLING )
# if defined( C_ENABLE_TX_POLLING )
/* **************************************************************************
| NAME:             CanTxObjTask()
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: CAN_HW_CHANNEL_CANTYPE_FIRST
|                   CanObjectHandle txObjHandle
| RETURN VALUES:    none
| DESCRIPTION:      Polling special Object
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanTxObjTask(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle mailboxHandle)      /* PRQA S 1330 */ /* MD_Can_1330 */
{
  tCanTaskInfoStruct taskInfo;

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#  endif
  assertUser(mailboxHandle < CAN_HL_MB_TX_STOPINDEX(canHwChannel), channel, kErrorHwHdlTooLarge); /* PRQA S 3689 */ /* MD_Can_3689 */
  /* avoid compiler warning: comparison is always true; ESCAN00076413 */
#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(mailboxHandle >= CAN_HL_MB_TX_STARTINDEX(canHwChannel), channel, kErrorHwHdlTooSmall);   /* PRQA S 3689 */ /* MD_Can_3689 */ /* lint !e568 */
#  else
#   if (kCanMailboxTxStartIndex != 0)
  assertUser(mailboxHandle >= CAN_HL_MB_TX_STARTINDEX(canHwChannel), channel, kErrorHwHdlTooSmall);   /* PRQA S 3689 */ /* MD_Can_3689 */ /* lint !e568 */
#   endif
#  endif

  assertUser(Can_Mailbox[mailboxHandle].HwObjPolling != (vuint8)0, channel, kErrorHwObjNotInPolling); /* PRQA S 3689 */ /* MD_Can_3689 */
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion); /* PRQA S 3689 */ /* MD_Can_3689 */

  if (canPollingTaskActive[channel] == (vuint8)0) /* PRQA S 3689 */ /* MD_Can_3689 */ /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

#  if defined( C_ENABLE_SLEEP_WAKEUP )
    if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY) )
#  endif
    {
      taskInfo.mailboxHandle = mailboxHandle;
      taskInfo.hwObjHandle = Can_Mailbox[mailboxHandle].HwObjHandle; /* PRQA S 3689 */ /* MD_Can_3689 */

      /* check and process pending confirmations for a dedicated mailbox */
      CanLL_TxProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &taskInfo);

#  if defined( C_ENABLE_TRANSMIT_QUEUE )
      if ( mailboxHandle == CAN_HL_MB_TX_NORMAL_INDEX(channel) ) /* PRQA S 3689 */ /* MD_Can_3689 */
      {
        CanHL_RestartTxQueue( CAN_CHANNEL_CANPARA_ONLY );
      }
#  endif /*  C_ENABLE_TRANSMIT_QUEUE */
    }

    canPollingTaskActive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
  }
}
/* CanTxObjTask */
/* CODE CATEGORY 2 END */
# endif /* defined( C_ENABLE_INDIVIDUAL_POLLING ) && defined( C_ENABLE_TX_POLLING ) */

# if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) && \
    defined( C_ENABLE_RX_FULLCAN_POLLING )
/* **************************************************************************
| NAME:             CanRxFullCANObjTask()
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: CAN_HW_CHANNEL_CANTYPE_FIRST
|                   CanObjectHandle rxObjHandle
| RETURN VALUES:    none
| DESCRIPTION:      Polling special Object
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxFullCANObjTask(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle)      /* PRQA S 1330 */ /* MD_Can_1330 */
{
  tCanTaskInfoStruct taskInfo;

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#  endif
  assertUser(rxMailboxHandle < CAN_HL_MB_RX_FULL_STOPINDEX(canHwChannel), channel, kErrorHwHdlTooLarge); /* PRQA S 3689 */ /* MD_Can_3689 */
  /* avoid compiler warning: comparison is always true; ESCAN00059736 */
#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(rxMailboxHandle >= CAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel), channel, kErrorHwHdlTooSmall); /* PRQA S 3689 */ /* MD_Can_3689 */ /* lint !e568 */
#  else
#   if (kCanMailboxRxFullStartIndex != 0)
  assertUser(rxMailboxHandle >= CAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel), channel, kErrorHwHdlTooSmall);  /* lint !e568 */
#   endif
#  endif
  assertUser(Can_Mailbox[rxMailboxHandle].HwObjPolling != (vuint8)0, channel, kErrorHwObjNotInPolling); /* PRQA S 3689 */ /* MD_Can_3689 */
  assertUser((canPollingTaskActive[channel] == 0), channel, kErrorPollingTaskRecursion); /* PRQA S 3689 */ /* MD_Can_3689 */

  if (canPollingTaskActive[channel] == (vuint8)0) /* PRQA S 3689 */ /* MD_Can_3689 */ /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

#  if defined( C_ENABLE_SLEEP_WAKEUP )
    if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY) )
#  endif
    {
      taskInfo.mailboxHandle = rxMailboxHandle;
      taskInfo.hwObjHandle = Can_Mailbox[rxMailboxHandle].HwObjHandle; /* PRQA S 3689 */ /* MD_Can_3689 */

      /* check and process pending indications for a dedicated mailbox */
      CanLL_RxFullProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &taskInfo);
    }
    canPollingTaskActive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
  }
}
/* CanRxFullCANObjTask */
/* CODE CATEGORY 2 END */
# endif

# if defined( C_ENABLE_RX_BASICCAN_POLLING ) && \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/* **************************************************************************
| NAME:             CanRxBasicCANObjTask()
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: CAN_HW_CHANNEL_CANTYPE_FIRST
|                   CanObjectHandle rxObjHandle
| RETURN VALUES:    none
| DESCRIPTION:      Polling special Object
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxBasicCANObjTask(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle)        /* PRQA S 1330 */ /* MD_Can_1330 */
{
  tCanTaskInfoStruct taskInfo;

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#  endif
  assertUser(rxMailboxHandle < CAN_HL_MB_RX_BASIC_STOPINDEX(canHwChannel), channel, kErrorHwHdlTooLarge); /* PRQA S 3689 */ /* MD_Can_3689 */
  /* avoid compiler warning: comparison is always true; ESCAN00059736 */
#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(rxMailboxHandle >= CAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel), channel, kErrorHwHdlTooSmall); /* PRQA S 3689 */ /* MD_Can_3689 */ /* lint !e568 */
#  else
#   if (kCanMailboxRxBasicStartIndex != 0)
  assertUser(rxMailboxHandle >= CAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel), channel, kErrorHwHdlTooSmall);  /* lint !e568 */
#   endif
#  endif
  assertUser(Can_Mailbox[rxMailboxHandle].HwObjPolling != (vuint8)0, channel, kErrorHwObjNotInPolling); /* PRQA S 3689 */ /* MD_Can_3689 */
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion); /* PRQA S 3689 */ /* MD_Can_3689 */

  if (canPollingTaskActive[channel] == (vuint8)0) /* PRQA S 3689 */ /* MD_Can_3689 */ /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

#  if defined( C_ENABLE_SLEEP_WAKEUP )
    if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY) )
#  endif
    {
      taskInfo.mailboxHandle = rxMailboxHandle;
      taskInfo.hwObjHandle = Can_Mailbox[rxMailboxHandle].HwObjHandle; /* PRQA S 3689 */ /* MD_Can_3689 */

      /* check and process pending indications for a dedicated mailbox */
      CanLL_RxBasicProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &taskInfo);
    }
    canPollingTaskActive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
  }
}
/* CanRxBasicCANObjTask */
/* CODE CATEGORY 2 END */
# endif
#endif /* C_ENABLE_INDIVIDUAL_POLLING */

#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/* **************************************************************************
| NAME:             CanBasicCanMsgReceived
| CALLED BY:        CanISR()
| PRECONDITIONS:
| INPUT PARAMETERS: internal can chip number, rxMailboxHandle, rxObjHandle
| RETURN VALUES:    none
| DESCRIPTION:      - basic can receive
************************************************************************** */
/* CODE CATEGORY 1 START */
void CanBasicCanMsgReceived( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle rxObjHandle)
{


# if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
  tCanRxInfoStruct    *pCanRxInfoStruct;
# endif

# if ( !defined( C_SEARCH_HASH ) && \
       !defined( C_SEARCH_INDEX ) )  ||\
     defined( C_ENABLE_RANGE_0 ) || \
     defined( C_ENABLE_RANGE_1 ) || \
     defined( C_ENABLE_RANGE_2 ) || \
     defined( C_ENABLE_RANGE_3 )
  tCanRxId0 idRaw0; /* PRQA S 0781 */ /* MD_Can_0781 */
#  if (kCanNumberOfUsedCanRxIdTables > 1)
  tCanRxId1 idRaw1; /* PRQA S 0781 */ /* MD_Can_0781 */
#  endif
#  if (kCanNumberOfUsedCanRxIdTables > 2)
  tCanRxId2 idRaw2; /* PRQA S 0781 */ /* MD_Can_0781 */
#  endif
#  if (kCanNumberOfUsedCanRxIdTables > 3)
  tCanRxId3 idRaw3; /* PRQA S 0781 */ /* MD_Can_0781 */
#  endif
#  if (kCanNumberOfUsedCanRxIdTables > 4)
  tCanRxId4 idRaw4; /* PRQA S 0781 */ /* MD_Can_0781 */
#  endif
# endif

# if defined( C_SEARCH_HASH )
#  if (kCanNumberOfRxBasicCANObjects > 0)
#   if (kHashSearchListCountEx > 0)
  vuint32          idExt;
#    if (kHashSearchListCountEx > 1)
  vuint32          winternExt;        /* prehashvalue         */
#    endif
#   endif
#   if (kHashSearchListCount > 0)
  vuint16          idStd;
#    if (kHashSearchListCount > 1)
  vuint16          winternStd;        /* prehashvalue         */
#    endif
#   endif
#   if (((kHashSearchListCountEx > 1) && (kHashSearchMaxStepsEx > 1)) ||\
        ((kHashSearchListCount > 1)   && (kHashSearchMaxSteps > 1)))
  vuint16          i_increment;    /* delta for next step  */
  vsint16          count;
#   endif
#  endif /* kCanNumberOfRxBasicCANObjects > 0 */
# endif

  tCanRxBasicInfoStruct rxInfo;

# if defined( C_ENABLE_GENERIC_PRECOPY ) || \
    defined( C_ENABLE_PRECOPY_FCT )     || \
    defined( C_ENABLE_COPY_RX_DATA )    || \
    defined( C_ENABLE_INDICATION_FLAG ) || \
    defined( C_ENABLE_INDICATION_FCT )  || \
    defined( C_ENABLE_DLC_CHECK )       || \
    defined( C_ENABLE_NOT_MATCHED_FCT )
#  if (kCanNumberOfRxBasicCANObjects > 0)

  CanReceiveHandle         rxHandle;
  vuint8                   canRxHandleFound;

  rxHandle = kCanRxHandleNotUsed; /* PRQA S 3198 */ /* MD_Can_3198 */

#  endif /* kCanNumberOfRxBasicCANObjects > 0 */
# endif

  CANDRV_SET_CODE_TEST_POINT(0x100);

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);
# endif
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(rxMailboxHandle >= CAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel), channel, kErrorMailboxHandleWrong); /* PRQA S 3689 */ /* MD_Can_3689 */
# else
#  if (kCanMailboxRxBasicStartIndex != 0)
  assertInternal(rxMailboxHandle >= CAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel), channel, kErrorMailboxHandleWrong);
#  endif
# endif
  assertInternal(rxMailboxHandle < CAN_HL_MB_RX_BASIC_STOPINDEX(canHwChannel), channel, kErrorMailboxHandleWrong); /* PRQA S 3689 */ /* MD_Can_3689 */

  rxInfo.mailboxHandle = rxMailboxHandle;
  rxInfo.hwObjHandle = rxObjHandle;


  if (CanLL_RxBasicMsgReceivedBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxInfo) == kCanFailed)
    {
      goto finishBasicCan;
    }

# if defined( C_KOMMENTAR_VECTOR_LI13 )
/* ##LI-: 2.2    Information for higher layers (e.g. TP) if the current pre-copy is called within a range or message specific. */
# endif
# if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )

          pCanRxInfoStruct =  &canRxInfoStruct[channel];
          pCanRxInfoStruct->pChipMsgObj = rxInfo.pChipMsgObj;
          pCanRxInfoStruct->pChipData = rxInfo.pChipData;
          canRDSRxPtr[channel] = pCanRxInfoStruct->pChipData;

# else
          canRxInfoStruct[channel].pChipMsgObj = rxInfo.pChipMsgObj;
          canRxInfoStruct[channel].pChipData = rxInfo.pChipData;
          canRDSRxPtr[channel] = canRxInfoStruct[channel].pChipData;
# endif
  CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)    =   kCanRxHandleNotUsed;

# if defined( C_ENABLE_CAN_RAM_CHECK )
  if(canComStatus[channel] == kCanDisableCommunication) /* PRQA S 3689 */ /* MD_Can_3689 */
  {
    goto finishBasicCan; /* PRQA S 3689 */ /* MD_Can_3689 */ /* ignore reception */
  }

# endif

#  if defined( C_ENABLE_OVERRUN )
  if (rxInfo.isOverrun == kCanTrue)
  {
    ApplCanOverrun( CAN_CHANNEL_CANPARA_ONLY );
  }
#  endif

  /* ************************** reject messages with illegal DLC ******************************************* */
# if defined( C_ENABLE_CAN_FD_FULL )
  /* DLC of classic CAN frames must not be greater than 8 */
  if ((CanRxActualDLC( CAN_HL_P_RX_INFO_STRUCT(channel) ) > (vuint8)8u) && (CanRxActualFdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) != kCanFdTypeFd))
# else

  /* DLC must never be greater than 8 */
  if (CanRxActualDLC( CAN_HL_P_RX_INFO_STRUCT(channel) ) > (vuint8)8u)
# endif
  {
    goto finishBasicCan;
  }

# if defined( C_HL_ENABLE_REJECT_ILLEGAL_DLC )
#  if defined( C_ENABLE_CAN_FD_FULL )
  /* Frame lenght must not be greater than (min) size of hardware object */
  if (CanRxActualDLC( CAN_HL_P_RX_INFO_STRUCT(channel) ) > Can_Mailbox[rxMailboxHandle].HwObjMaxDataLen) /* PRQA S 3689 */ /* MD_Can_3689 */
  {
    goto finishBasicCan;
  }
#  endif
# endif /* C_HL_ENABLE_REJECT_ILLEGAL_DLC */

# if defined( C_ENABLE_COND_RECEIVE_FCT )
  /* ************************** conditional message receive function  ************************************** */
  if(canMsgCondRecState[channel] == kCanTrue)
  {
    ApplCanMsgCondReceived( CAN_HL_P_RX_INFO_STRUCT(channel) );
  }
# endif

# if defined( C_ENABLE_RECEIVE_FCT )
  /* ************************** call ApplCanMsgReceived() ************************************************** */
  if (APPL_CAN_MSG_RECEIVED( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanNoCopyData)
  {
    goto finishBasicCan;
  }
# endif

# if ( !defined( C_SEARCH_HASH ) && \
       !defined( C_SEARCH_INDEX ) ) || \
     defined( C_ENABLE_RANGE_0 ) || \
     defined( C_ENABLE_RANGE_1 ) || \
     defined( C_ENABLE_RANGE_2 ) || \
     defined( C_ENABLE_RANGE_3 )
  /* ************************** calculate idRaw for filtering ********************************************** */
#  if defined( C_ENABLE_EXTENDED_ID )
#   if defined( C_ENABLE_MIXED_ID )
  if (CanRxActualIdType(CAN_HL_P_RX_INFO_STRUCT(channel)) == kCanIdTypeExt)
#   endif
  {
#   if defined( C_ENABLE_RX_MASK_EXT_ID )
    idRaw0 = CanRxActualIdRaw0( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID0( C_MASK_EXT_ID);
#    if (kCanNumberOfUsedCanRxIdTables > 1)
    idRaw1 = CanRxActualIdRaw1( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID1(C_MASK_EXT_ID);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 2)
    idRaw2 = CanRxActualIdRaw2( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID2(C_MASK_EXT_ID);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 3)
    idRaw3 = CanRxActualIdRaw3( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID3(C_MASK_EXT_ID);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 4)
    idRaw4 = CanRxActualIdRaw4( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID4(C_MASK_EXT_ID);
#    endif
#   else
    idRaw0 = CanRxActualIdRaw0( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID0(0x1FFFFFFF);
#    if (kCanNumberOfUsedCanRxIdTables > 1)
    idRaw1 = CanRxActualIdRaw1( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID1(0x1FFFFFFF);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 2)
    idRaw2 = CanRxActualIdRaw2( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID2(0x1FFFFFFF);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 3)
    idRaw3 = CanRxActualIdRaw3( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID3(0x1FFFFFFF);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 4)
    idRaw4 = CanRxActualIdRaw4( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID4(0x1FFFFFFF);
#    endif
#   endif /*  C_ENABLE_RX_MASK_EXT_ID */
  }
#   if defined( C_ENABLE_MIXED_ID )
  else
  {
    idRaw0 = CanRxActualIdRaw0( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID0(0x7FF);
#    if (kCanNumberOfUsedCanRxIdTables > 1)
    idRaw1 = CanRxActualIdRaw1( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID1(0x7FF);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 2)
    idRaw2 = CanRxActualIdRaw2( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID2(0x7FF);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 3)
    idRaw3 = CanRxActualIdRaw3( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID3(0x7FF);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 4)
    idRaw4 = CanRxActualIdRaw4( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID4(0x7FF);
#    endif
  }
#   endif
#  else /* C_ENABLE_EXTENDED_ID */
  {
  //   idRaw0 = CanRxActualIdRaw0( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID0(0x7FF);
    idRaw0 =  (rxMsg.RxHeandle.Identifier << 2) & (0x7FF << 2);
#   if (kCanNumberOfUsedCanRxIdTables > 1)
    idRaw1 = CanRxActualIdRaw1( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID1(0x7FF);
#   endif
#   if (kCanNumberOfUsedCanRxIdTables > 2)
    idRaw2 = CanRxActualIdRaw2( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID2(0x7FF);
#   endif
#   if (kCanNumberOfUsedCanRxIdTables > 3)
    idRaw3 = CanRxActualIdRaw3( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID3(0x7FF);
#   endif
#   if (kCanNumberOfUsedCanRxIdTables > 4)
    idRaw4 = CanRxActualIdRaw4( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID4(0x7FF);
#   endif
  }
#  endif /* C_ENABLE_EXTENDED_ID */
# endif /* ( !defined( C_SEARCH_HASH ) && ...  defined( C_ENABLE_RANGE_3 ) */

  /* ***************** Range filtering ****************************************************************** */

  {
#  if defined( C_ENABLE_RANGE_0 )
#   if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    if ( (CanChannelObject[channel].RangeActiveFlag & kCanRange0) != (vuint16)0 ) /* PRQA  S 3689 */ /* MD_Can_3689 */
    {
#    if defined( C_ENABLE_MIXED_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == CANRANGE0IDTYPE(channel))
#    endif
      {
        if ( C_RANGE_MATCH( CAN_RX_IDRAW_PARA, CANRANGE0ACCMASK(channel), CANRANGE0ACCCODE(channel)) ) /* PRQA  S 3689 */ /* MD_Can_3689 */
#   else /* C_SINGLE_RECEIVE_CHANNEL) */
    {
#    if (C_RANGE0_IDTYPE == kCanIdTypeStd )
#     if defined( C_ENABLE_MIXED_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeStd)
#     endif
      {
        if ( C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, CANRANGE0ACCMASK(channel), CANRANGE0ACCCODE(channel)) )
#    else /* C_RANGE_0_IDTYPE == kCanIdTypeExt */
#     if defined( C_ENABLE_MIXED_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeExt)
#     endif
      {
        if ( C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, CANRANGE0ACCMASK(channel), CANRANGE0ACCCODE(channel)) )
#    endif
#   endif
        {
#   if defined( C_ENABLE_RX_QUEUE_RANGE )
          if (CanRxQueueRange0[channel] == kCanTrue) /* PRQA  S 3689 */ /* MD_Can_3689 */
          {
            pCanRxInfoStruct->Handle      = kCanRxHandleRange0;
            (void)CanHL_ReceivedRxHandleQueue( CAN_CHANNEL_CANPARA_ONLY );
            goto finishBasicCan;
          }
          else
#   endif /* C_ENABLE_RX_QUEUE */
          {
            if (APPLCANRANGE0PRECOPY( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanNoCopyData)
            {
              goto finishBasicCan;
            }
          }
        }
      }
    }
#  endif /* C_ENABLE_RANGE_0 */

#  if defined( C_ENABLE_RANGE_1 )
#   if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    if ( (CanChannelObject[channel].RangeActiveFlag & kCanRange1) != (vuint16)0 ) /* PRQA  S 3689 */ /* MD_Can_3689 */
    {
#    if defined( C_ENABLE_MIXED_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == CANRANGE1IDTYPE(channel))
#    endif
      {
        if ( C_RANGE_MATCH( CAN_RX_IDRAW_PARA, CANRANGE1ACCMASK(channel), CANRANGE1ACCCODE(channel)) ) /* PRQA  S 3689 */ /* MD_Can_3689 */
#   else /* C_SINGLE_RECEIVE_CHANNEL) */
    {
#    if (C_RANGE1_IDTYPE == kCanIdTypeStd )
#     if defined( C_ENABLE_MIXED_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeStd)
#     endif
      {
        if ( C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, CANRANGE1ACCMASK(channel), CANRANGE1ACCCODE(channel)) )
#    else /* C_RANGE_1_IDTYPE == kCanIdTypeExt */
#     if defined( C_ENABLE_MIXED_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeExt)
#     endif
      {
        if ( C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, CANRANGE1ACCMASK(channel), CANRANGE1ACCCODE(channel)) )
#    endif
#   endif
        {
#   if defined( C_ENABLE_RX_QUEUE_RANGE )
          if (CanRxQueueRange1[channel] == kCanTrue) /* PRQA  S 3689 */ /* MD_Can_3689 */
          {
            pCanRxInfoStruct->Handle      = kCanRxHandleRange1;
            (void)CanHL_ReceivedRxHandleQueue( CAN_CHANNEL_CANPARA_ONLY );
            goto finishBasicCan;
          }
          else
#   endif /* C_ENABLE_RX_QUEUE */
          {
            if (APPLCANRANGE1PRECOPY( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanNoCopyData)
            {
              goto finishBasicCan;
            }
          }
        }
      }
    }
#  endif /* C_ENABLE_RANGE_1 */

#  if defined( C_ENABLE_RANGE_2 )
#   if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    if ( (CanChannelObject[channel].RangeActiveFlag & kCanRange2) != (vuint16)0 ) /* PRQA  S 3689 */ /* MD_Can_3689 */
    {
#    if defined( C_ENABLE_MIXED_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == CANRANGE2IDTYPE(channel))
#    endif
      {
        if ( C_RANGE_MATCH( CAN_RX_IDRAW_PARA, CANRANGE2ACCMASK(channel), CANRANGE2ACCCODE(channel)) ) /* PRQA  S 3689 */ /* MD_Can_3689 */
#   else /* C_SINGLE_RECEIVE_CHANNEL) */
    {
#    if (C_RANGE2_IDTYPE == kCanIdTypeStd )
#     if defined( C_ENABLE_MIXED_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeStd)
#     endif
      {
        if ( C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, CANRANGE2ACCMASK(channel), CANRANGE2ACCCODE(channel)) )
#    else /* C_RANGE_2_IDTYPE == kCanIdTypeExt */
#     if defined( C_ENABLE_MIXED_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeExt)
#     endif
      {
        if ( C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, CANRANGE2ACCMASK(channel), CANRANGE2ACCCODE(channel)) )
#    endif
#   endif
        {
#   if defined( C_ENABLE_RX_QUEUE_RANGE )
          if (CanRxQueueRange2[channel] == kCanTrue) /* PRQA  S 3689 */ /* MD_Can_3689 */
          {
            pCanRxInfoStruct->Handle      = kCanRxHandleRange2;
            (void)CanHL_ReceivedRxHandleQueue( CAN_CHANNEL_CANPARA_ONLY );
            goto finishBasicCan;
          }
          else
#   endif /* C_ENABLE_RX_QUEUE */
          {
            if (APPLCANRANGE2PRECOPY( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanNoCopyData)
            {
              goto finishBasicCan;
            }
          }
        }
      }
    }
#  endif /* C_ENABLE_RANGE_2 */

#  if defined( C_ENABLE_RANGE_3 )
#   if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    if ( (CanChannelObject[channel].RangeActiveFlag & kCanRange3) != (vuint16)0 ) /* PRQA  S 3689 */ /* MD_Can_3689 */
    {
#    if defined( C_ENABLE_MIXED_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == CANRANGE3IDTYPE(channel))
#    endif
      {
        if ( C_RANGE_MATCH( CAN_RX_IDRAW_PARA, CANRANGE3ACCMASK(channel), CANRANGE3ACCCODE(channel)) ) /* PRQA  S 3689 */ /* MD_Can_3689 */
#   else /* C_SINGLE_RECEIVE_CHANNEL) */
    {
#    if (C_RANGE3_IDTYPE == kCanIdTypeStd )
#     if defined( C_ENABLE_MIXED_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeStd)
#     endif
      {
        if ( C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, CANRANGE3ACCMASK(channel), CANRANGE3ACCCODE(channel)) )
#    else /* C_RANGE_3_IDTYPE == kCanIdTypeExt */
#     if defined( C_ENABLE_MIXED_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeExt)
#     endif
      {
        if ( C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, CANRANGE3ACCMASK(channel), CANRANGE3ACCCODE(channel)) )
#    endif
#   endif
        {
#   if defined( C_ENABLE_RX_QUEUE_RANGE )
          if (CanRxQueueRange3[channel] == kCanTrue) /* PRQA  S 3689 */ /* MD_Can_3689 */
          {
            pCanRxInfoStruct->Handle      = kCanRxHandleRange3;
            (void)CanHL_ReceivedRxHandleQueue( CAN_CHANNEL_CANPARA_ONLY );
            goto finishBasicCan;
          }
          else
#   endif /* C_ENABLE_RX_QUEUE */
          {
            if (APPLCANRANGE3PRECOPY( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanNoCopyData)
            {
              goto finishBasicCan;
            }
          }
        }
      }
    }
#  endif /* C_ENABLE_RANGE_3 */

  }

# if defined( C_ENABLE_GENERIC_PRECOPY ) || \
    defined( C_ENABLE_PRECOPY_FCT )     || \
    defined( C_ENABLE_COPY_RX_DATA )    || \
    defined( C_ENABLE_INDICATION_FLAG ) || \
    defined( C_ENABLE_INDICATION_FCT )  || \
    defined( C_ENABLE_DLC_CHECK )       || \
    defined( C_ENABLE_NOT_MATCHED_FCT )
#  if (kCanNumberOfRxBasicCANObjects > 0)

  canRxHandleFound = kCanFalse;

  /* search the received id in ROM table: */

#   if defined( C_SEARCH_LINEAR )
  /* ************* Linear search ********************************************* */
  {
    for (rxHandle = CAN_HL_RX_BASIC_STARTINDEX(channel); rxHandle < CAN_HL_RX_BASIC_STOPINDEX(channel); rxHandle++)
    {
      if( idRaw0 == CanGetRxId0(rxHandle) )
      {
#    if (kCanNumberOfUsedCanRxIdTables > 1)
        if( idRaw1 == CanGetRxId1(rxHandle) )
#    endif
        {
#    if (kCanNumberOfUsedCanRxIdTables > 2)
          if( idRaw2 == CanGetRxId2(rxHandle) )
#    endif
          {
#    if (kCanNumberOfUsedCanRxIdTables > 3)
            if( idRaw3 == CanGetRxId3(rxHandle) )
#    endif
            {
#    if (kCanNumberOfUsedCanRxIdTables > 4)
              if( idRaw4 == CanGetRxId4(rxHandle) )
#    endif
              {
#    if defined( C_ENABLE_MIXED_ID )
                /* verify ID type, if not already done with the ID raw */
                if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == CanGetRxIdType(rxHandle))
#    endif
                {
                  /* message found in id table */
#    if defined( C_ENABLE_RX_MSG_INDIRECTION )
                  rxHandle = CanRxMsgIndirection[rxHandle];       /* indirection for special sort-algoritms */
#    endif
                  canRxHandleFound = kCanTrue;
                  break;    /* exit loop with index rxHandle */
                }
              }
            }
          }
        }
      }
    } /* for (rxHandle ....) */
  }
#   endif /* defined( C_SEARCH_LINEAR ) */

#   if defined( C_SEARCH_HASH )
  /* ************* Hash search ********************************************** */
  {
#    if defined( C_ENABLE_EXTENDED_ID )
  /* one or more Extended ID listed */
#     if defined( C_ENABLE_MIXED_ID )
    if((CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) )) == kCanIdTypeExt)
#     endif
    {
#     if (kHashSearchListCountEx > 0)
    /* hash table has at least one entry */
    /* calculate the logical ID */
#      if defined( C_ENABLE_RX_MASK_EXT_ID )
      idExt          = (CanRxActualId( CAN_HL_P_RX_INFO_STRUCT(channel) ) &  C_MASK_EXT_ID ) | ((vuint32)channel << 29);
#      else
      idExt          = CanRxActualId( CAN_HL_P_RX_INFO_STRUCT(channel) ) | ((vuint32)channel << 29);
#      endif

#      if (kHashSearchListCountEx == 1)
      rxHandle       = (CanReceiveHandle)0;
#      else
      winternExt     = idExt + kHashSearchRandomNumberEx;
      rxHandle       = (CanReceiveHandle)(winternExt % kHashSearchListCountEx);
#      endif /* (kHashSearchListCountEx == 1) */

#      if ((kHashSearchListCountEx == 1) || (kHashSearchMaxStepsEx == 1))
      if (idExt == CanRxHashIdEx[rxHandle])
      {
        rxHandle = CanRxMsgIndirection[rxHandle+kHashSearchListCount];
        canRxHandleFound = kCanTrue;
      }
#      else /* (kHashSearchListCountEx == 1) || (kHashSearchMaxStepsEx == 1) */

      i_increment = (vuint16)((winternExt % (kHashSearchListCountEx - 1)) + (vuint8)1);          /* ST10-CCAN Keil compiler complains without cast */

      for (count = (vsint16)kHashSearchMaxStepsEx; count != (vsint16)0; count--)
      {
        if (idExt == CanRxHashIdEx[rxHandle])
        {
          rxHandle = CanRxMsgIndirection[rxHandle+kHashSearchListCount];
          canRxHandleFound = kCanTrue;
          break;
        }
        else
        {
          rxHandle += i_increment;
          if( rxHandle >= (vuint16)kHashSearchListCountEx )
          {
            rxHandle -= kHashSearchListCountEx;
          }
        }
      }
#      endif /* (kHashSearchListCountEx == 1) || (kHashSearchMaxStepsEx == 1) */
#     endif /* (kHashSearchListCountEx > 0) */
    }

#     if defined( C_ENABLE_MIXED_ID )
    else /* if((CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) )) == kCanIdTypeStd)  */
#     endif
#    endif /* If defined( C_ENABLE_EXTENDED_ID ) */

#    if defined( C_ENABLE_MIXED_ID ) || !defined( C_ENABLE_EXTENDED_ID )
    {
#     if (kHashSearchListCount > 0)
    /* hash table has at least one entry */
      idStd          = ((vuint16)CanRxActualId( CAN_HL_P_RX_INFO_STRUCT(channel) ) | ((vuint16)channel << 11)); /* calculate the logical ID */

#      if (kHashSearchListCount == 1)
      rxHandle       = (CanReceiveHandle)0;
#      else
      winternStd     = idStd + kHashSearchRandomNumber;
      rxHandle       = (CanReceiveHandle)(winternStd % kHashSearchListCount);
#      endif /* (kHashSearchListCount == 1) */

#      if ((kHashSearchListCount == 1)  || (kHashSearchMaxSteps == 1))
      if (idStd == CanRxHashId[rxHandle])
      {
        rxHandle = CanRxMsgIndirection[rxHandle];
        canRxHandleFound = kCanTrue;
      }
#      else /* ((kHashSearchListCount == 1)  || (kHashSearchMaxSteps == 1)) */

      i_increment = (vuint16)((winternStd % (kHashSearchListCount - 1)) + (vuint8)1);

      for (count = (vsint16)kHashSearchMaxSteps; count != (vsint16)0; count--)
      {
        if (idStd == CanRxHashId[rxHandle])
        {
          rxHandle = CanRxMsgIndirection[rxHandle];
          canRxHandleFound = kCanTrue;
          break;
        }
        else
        {
          rxHandle += i_increment;
          if( rxHandle >= (vuint16)kHashSearchListCount )
          {
            rxHandle -= kHashSearchListCount;
          }
        }
      }
#      endif /* ((kHashSearchListCount == 1)  || (kHashSearchMaxSteps == 1)) */
#     endif /* (kHashSearchListCount > 0) */
    }
#    endif /* defined( C_ENABLE_MIXED_ID ) || !defined( C_ENABLE_EXTENDED_ID ) */
  }
#   endif /* defined( C_SEARCH_HASH ) */

#   if defined( C_SEARCH_INDEX )
  /* ************* index search *********************************************** */
  /* extended ID is not supported with index search */
  {
    rxHandle = CAN_RX_INDEX_TBL(channel, (vuint16)(CanRxActualId( CAN_HL_P_RX_INFO_STRUCT(channel)))); /* PRQA S 3689 */ /* MD_Can_3689 */
    if ( rxHandle < kCanNumberOfRxObjects)     /*  match in index search detected */
    {
      canRxHandleFound = kCanTrue;
    }
  }
#   endif /* defined( C_SEARCH_INDEX ) */

  if (canRxHandleFound == kCanTrue)
  {
    /* This code is reached for
       - hash search, HIT  in static Rx objects
       - hash search, MISS in static Rx objects but HIT in the dynamic objects
       - linear search, always (HIT/MISS in static or HIT in dynamic search) so search result must be evaluated */
    /* ************************** handle filtered message ************************************************** */
    assertInternal((rxHandle < kCanNumberOfRxObjects), kCanAllChannels, kErrorRxHandleWrong);  /* PRQA S 3201,3355,3356,3359 */ /* MD_Can_3201,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */ /* legal rxHandle ? */

    CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel) = rxHandle;

#  if defined( C_ENABLE_RX_QUEUE )
    if (CanHL_ReceivedRxHandleQueue( CAN_CHANNEL_CANPARA_ONLY ) == kCanHlContinueRx)
#  else
    if (CanHL_ReceivedRxHandle( CAN_CHANNEL_CANPARA_ONLY ) == kCanHlContinueRx)
#  endif
    {
#  if defined( C_ENABLE_INDICATION_FLAG ) || \
          defined( C_ENABLE_INDICATION_FCT )
      CanLL_RxBasicReleaseObj(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxInfo);

      CanHL_IndRxHandle( rxHandle );

      CanLL_RxBasicMsgReceivedEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxInfo);

      return;
#  endif
    }
  }
#  if defined( C_ENABLE_NOT_MATCHED_FCT )
  else
  {
    /* nothing found, neither static nor dynamic receive object, leave the function */
    ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
  }
#  endif

# else /* kCanNumberOfRxBasicCANObjects > 0 */
#  if defined( C_ENABLE_NOT_MATCHED_FCT )
  ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#  endif
# endif /* kCanNumberOfRxBasicCANObjects > 0 */

# endif

# if defined( C_KOMMENTAR_VECTOR )
  /* goto to avoid compiler warning about label without goto, if no other goto is active */
  /* detected with DrvCan_TricoreMultican and Tasking compiler */
# endif
  goto finishBasicCan;     /* to avoid compiler warning */

/* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
finishBasicCan:


/* make receive buffer free */
CanLL_RxBasicReleaseObj(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxInfo);
CanLL_RxBasicMsgReceivedEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxInfo);


  return;
}
/* end of BasicCan */
/* CODE CATEGORY 1 END */

# if defined( C_ENABLE_RX_BASICCAN_POLLING )
/* **************************************************************************
| NAME:             CanBasicCanMsgReceivedPolling
| CALLED BY:        CanTask()
| PRECONDITIONS:
| INPUT PARAMETERS: internal can chip number, rxMailboxHandle, rxObjHandle
| RETURN VALUES:    none
| DESCRIPTION:      - basic can receive
************************************************************************** */
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanBasicCanMsgReceivedPolling( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle rxObjHandle)
{
  CANDRV_SET_CODE_TEST_POINT(0x108);

  CAN_CAN_INTERRUPT_DISABLE(channel);
  CanBasicCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxMailboxHandle, rxObjHandle );
  CAN_CAN_INTERRUPT_RESTORE(channel);
}
/* CODE CATEGORY 1 END */
# endif
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/* **************************************************************************
| NAME:             CanFullCanMsgReceived
| CALLED BY:        CanISR()
| PRECONDITIONS:
| INPUT PARAMETERS: internal can chip number, rxMailboxHandle, rxObjHandle
| RETURN VALUES:    none
| DESCRIPTION:      - full can receive
************************************************************************** */

/* CODE CATEGORY 1 START */
static void CanFullCanMsgReceived( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle rxObjHandle )
{
  CanReceiveHandle   rxHandle;

# if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
  tCanRxInfoStruct    *pCanRxInfoStruct;
# endif

  tCanRxFullInfoStruct rxInfo;

  CANDRV_SET_CODE_TEST_POINT(0x101);

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);
# endif
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(rxMailboxHandle >= CAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel), channel, kErrorMailboxHandleWrong); /* PRQA S 3689 */ /* MD_Can_3689 */
# else
#  if (kCanMailboxRxFullStartIndex != 0)
  assertInternal(rxMailboxHandle >= CAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel), channel, kErrorMailboxHandleWrong);
#  endif
# endif
  assertInternal(rxMailboxHandle < CAN_HL_MB_RX_FULL_STOPINDEX(canHwChannel), channel, kErrorMailboxHandleWrong); /* PRQA S 3689 */ /* MD_Can_3689 */

  rxInfo.mailboxHandle = rxMailboxHandle;
  rxInfo.hwObjHandle = rxObjHandle;
  if (CanLL_RxFullMsgReceivedBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxInfo) == kCanFailed)
  {
    goto finishRxFullCan;
  }

# if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
  /* pointer needed for other modules */
  /* PRQA S 3689 5 */ /* MD_Can_3689 */
  pCanRxInfoStruct =  &canRxInfoStruct[channel];
  pCanRxInfoStruct->pChipMsgObj = rxInfo.pChipMsgObj;
  pCanRxInfoStruct->pChipData = rxInfo.pChipData;
  canRDSRxPtr[channel] = pCanRxInfoStruct->pChipData;
# else
  canRxInfoStruct[channel].pChipMsgObj = rxInfo.pChipMsgObj;
  canRxInfoStruct[channel].pChipData = rxInfo.pChipData;
  canRDSRxPtr[channel] = canRxInfoStruct[channel].pChipData;
# endif

# if defined( C_ENABLE_CAN_RAM_CHECK )
  if(canComStatus[channel] == kCanDisableCommunication) /* PRQA S 3689 */ /* MD_Can_3689 */
  {
    goto finishRxFullCan; /* PRQA S 3689 */ /* MD_Can_3689 */ /* ignore reception */
  }
# endif

#  if defined( C_ENABLE_FULLCAN_OVERRUN )
  if (rxInfo.isOverrun == kCanTrue)
  {
     ApplCanFullCanOverrun( CAN_CHANNEL_CANPARA_ONLY );
  }
#  endif

  /* ************************** reject messages with illegal DLC ******************************************* */
# if defined( C_ENABLE_CAN_FD_FULL )
  /* DLC of classic CAN frames must not be greater than 8 */
  if ((CanRxActualDLC( CAN_HL_P_RX_INFO_STRUCT(channel) ) > (vuint8)8u) && (CanRxActualFdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) != kCanFdTypeFd))
# else
  /* DLC must never be greater than 8 */
  if (CanRxActualDLC( CAN_HL_P_RX_INFO_STRUCT(channel) ) > (vuint8)8u)
# endif
  {
    goto finishRxFullCan;
  }

# if defined( C_HL_ENABLE_REJECT_ILLEGAL_DLC )
#  if defined( C_ENABLE_CAN_FD_FULL )
  /* Frame lenght must not be greater than (min) size of hardware object */
  if (CanRxActualDLC( CAN_HL_P_RX_INFO_STRUCT(channel) ) > Can_Mailbox[rxMailboxHandle].HwObjMaxDataLen)
  {
    goto finishRxFullCan;
  }
#  endif
# endif /* C_HL_ENABLE_REJECT_ILLEGAL_DLC */

# if defined( C_ENABLE_COND_RECEIVE_FCT )
  /* ************************** conditional message receive function  ************************************** */
  if(canMsgCondRecState[channel] == kCanTrue)
  {
    ApplCanMsgCondReceived( CAN_HL_P_RX_INFO_STRUCT(channel) );
  }
# endif

# if defined( C_ENABLE_RECEIVE_FCT )
  /* ************************** call ApplCanMsgReceived() ************************************************** */
  if (APPL_CAN_MSG_RECEIVED( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanNoCopyData)
  {
     goto finishRxFullCan;
  }
# endif

  /* calculate the message handle to access the generated data for the received message */

  /* brackets to avoid lint info 834 */
  rxHandle = (rxMailboxHandle - CAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel)) /* PRQA S 3382,3689 */ /* MD_Can_3382,MD_Can_3689 */
# if defined( C_SEARCH_HASH )
                         + kHashSearchListCount
                         + kHashSearchListCountEx
# endif
                         + CAN_HL_RX_FULL_STARTINDEX(canHwChannel); /* PRQA S 3382 */ /* MD_Can_3382 */

# if defined( C_ENABLE_RX_MSG_INDIRECTION ) || \
     defined( C_SEARCH_HASH ) || \
     defined( C_SEARCH_INDEX )
  rxHandle = CanRxMsgIndirection[rxHandle]; /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

  assertInternal((rxHandle < kCanNumberOfRxObjects), kCanAllChannels, kErrorRxHandleWrong);  /* legal rxHandle ? */

  CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel) = rxHandle;

# if defined( C_ENABLE_RX_QUEUE )
  if (CanHL_ReceivedRxHandleQueue( CAN_CHANNEL_CANPARA_ONLY) == kCanHlContinueRx)
# else
  if (CanHL_ReceivedRxHandle( CAN_CHANNEL_CANPARA_ONLY ) == kCanHlContinueRx)
# endif
  {
# if defined( C_ENABLE_INDICATION_FLAG ) || \
        defined( C_ENABLE_INDICATION_FCT )
    CanLL_RxFullReleaseObj(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxInfo);

    CanHL_IndRxHandle( rxHandle );

    CanLL_RxFullMsgReceivedEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxInfo);

    return;
# endif
  }

# if defined( C_KOMMENTAR_VECTOR )
  /* goto to avoid compiler warning about label without goto, if no other goto is active */
  /* detected with DrvCan_TricoreMultican and Tasking compiler */
# endif
  goto finishRxFullCan;     /* to avoid compiler warning */

/* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
finishRxFullCan:

  /* make receive buffer free */
  CanLL_RxFullReleaseObj(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxInfo);
  CanLL_RxFullMsgReceivedEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxInfo);

  return;
}
/* CODE CATEGORY 1 END */

# if defined( C_ENABLE_RX_FULLCAN_POLLING )
/* **************************************************************************
| NAME:             CanFullCanMsgReceivedPolling
| CALLED BY:        CanTask()
| PRECONDITIONS:
| INPUT PARAMETERS: internal can chip number, rxMailboxHandle, rxObjHandle
| RETURN VALUES:    none
| DESCRIPTION:      - full can receive
************************************************************************** */
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanFullCanMsgReceivedPolling( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle rxObjHandle )
{
  CANDRV_SET_CODE_TEST_POINT(0x109);

  CAN_CAN_INTERRUPT_DISABLE(channel);
  CanFullCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxMailboxHandle, rxObjHandle );
  CAN_CAN_INTERRUPT_RESTORE(channel);
}
/* CODE CATEGORY 1 END */
# endif
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */


#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )  || \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
# if ( kCanNumberOfRxObjects > 0 )
/* **************************************************************************
| NAME:             CanHL_ReceivedRxHandle
| CALLED BY:        CanBasicCanMsgReceived, CanFullCanMsgReceived
| PRECONDITIONS:
| INPUT PARAMETERS: Handle of received Message to access generated data
| RETURN VALUES:    none
| DESCRIPTION:      DLC-check, Precopy and copy of Data for received message
************************************************************************** */
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_RX_QUEUE )
static vuint8 CanHL_ReceivedRxHandle( CAN_CHANNEL_CANTYPE_FIRST tCanRxInfoStruct *pCanRxInfoStruct )
{
#  else
static vuint8 CanHL_ReceivedRxHandle( CAN_CHANNEL_CANTYPE_ONLY )
{
#  endif
#  if !defined( C_ENABLE_RX_QUEUE ) &&\
    defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
  tCanRxInfoStruct    *pCanRxInfoStruct;
#  endif

#  if defined( C_ENABLE_COPY_RX_DATA )
  tCanRxCopyInfoStruct rxCopyInfo;

#   if C_SECURITY_LEVEL > 20
  CanDeclareGlobalInterruptOldStatus
#   endif
#  endif

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(channel < kCanNumberOfChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);
# endif

#  if !defined( C_ENABLE_RX_QUEUE ) &&\
    defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
  pCanRxInfoStruct =  &canRxInfoStruct[channel]; /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif

#  if defined( C_ENABLE_MULTI_ECU_PHYS )
  if ( (CanRxIdentityAssignment[CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)] & V_ACTIVE_IDENTITY_MSK) == (tVIdentityMsk)0 )
  {
    /* message is not a receive message in the active indentity */
    CANDRV_SET_CODE_TEST_POINT(0x10B);
    return  kCanHlFinishRx;
  }
#  endif


#  if defined( C_ENABLE_DLC_CHECK )
#   if defined( C_ENABLE_DLC_CHECK_MIN_DATALEN )
  if ( (CanGetRxMinDataLen(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel))) > CanRxActualDLC( CAN_HL_P_RX_INFO_STRUCT(channel) ) )
#   else
  if ( (CanGetDerivedRxDataLen(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel))) > CanRxActualDLC( CAN_HL_P_RX_INFO_STRUCT(channel) ) )
#   endif
  {
    /* ##RI1.4 - 2.7: Callbackfunction-DLC-Check */
#   if defined( C_ENABLE_DLC_FAILED_FCT )
    ApplCanMsgDlcFailed( CAN_HL_P_RX_INFO_STRUCT(channel) );
#   endif  /* C_ENABLE_DLC_FAILED_FCT */
    return  kCanHlFinishRx;
  }
#  endif

#  if defined( C_ENABLE_VARIABLE_RX_DATALEN )
  CanSetVariableRxDatalen (CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel), CanRxActualDLC( CAN_HL_P_RX_INFO_STRUCT(channel)));
#  endif

#  if defined( C_ENABLE_GENERIC_PRECOPY )
  if ( APPL_CAN_GENERIC_PRECOPY( CAN_HL_P_RX_INFO_STRUCT(channel) ) != kCanCopyData)
  {
    return kCanHlFinishRx;
  }
#  endif

#  if defined( C_ENABLE_PRECOPY_FCT )
  if ( CanGetApplPrecopyPtr(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)) != V_NULL )    /* precopy routine */
  {
    /* canRxHandle in indexed drivers only for consistancy check in higher layer modules */
    canRxHandle[channel] = CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel); /* PRQA S 3689 */ /* MD_Can_3689 */

    if ( CanGetApplPrecopyPtr(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel))( CAN_HL_P_RX_INFO_STRUCT(channel) )==kCanNoCopyData )
    {  /* precopy routine returns kCanNoCopyData:   */
      return  kCanHlFinishRx;
    }                      /* do not copy data check next irpt */
  }
#  endif

#  if defined( C_ENABLE_COPY_RX_DATA )
  /* no precopy or precopy returns kCanCopyData : copy data -- */
  /* copy via index ------------------------------------------- */
  if ( CanGetRxDataPtr(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)) != V_NULL )      /* copy if buffer exists */
  {
    /* copy data --------------------------------------------- */
#   if C_SECURITY_LEVEL > 20
    CanNestedGlobalInterruptDisable();
#   endif
    CANDRV_SET_CODE_TEST_POINT(0x107);

    rxCopyInfo.dest = CanGetRxDataPtr(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel));
#   if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
    rxCopyInfo.src = pCanRxInfoStruct->pChipData;
#   else
    rxCopyInfo.src = canRxInfoStruct[channel].pChipData;
#   endif
#   if defined( C_ENABLE_COPY_RX_DATA_WITH_DLC )
    if ( CanRxActualDLC( CAN_HL_P_RX_INFO_STRUCT(channel)) < CanGetDerivedRxDataLen(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)) )
    {
      rxCopyInfo.len = CanRxActualDLC(CAN_HL_P_RX_INFO_STRUCT(channel));
    }
    else
#   endif /* C_ENABLE_COPY_RX_DATA_WITH_DLC */
    {
      rxCopyInfo.len = CanGetDerivedRxDataLen(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel) );
    }
    CanLL_RxCopyFromCan(CAN_CHANNEL_CANPARA_FIRST &rxCopyInfo);

#   if C_SECURITY_LEVEL > 20
    CanNestedGlobalInterruptRestore();
#   endif
  }
#  endif /* ( C_ENABLE_COPY_RX_DATA ) */

  CANDRV_SET_CODE_TEST_POINT(0x105);
  return kCanHlContinueRx;
} /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */
/* end of CanReceivceRxHandle() */
/* CODE CATEGORY 1 END */


#  if defined( C_ENABLE_INDICATION_FLAG ) || \
     defined( C_ENABLE_INDICATION_FCT )
/* **************************************************************************
| NAME:             CanHL_IndRxHandle
| CALLED BY:        CanBasicCanMsgReceived, CanFullCanMsgReceived
| PRECONDITIONS:
| INPUT PARAMETERS: Handle of received Message to access generated data
| RETURN VALUES:    none
| DESCRIPTION:      DLC-check, Precopy and copy of Data for received message
************************************************************************** */
/* CODE CATEGORY 1 START */
static void CanHL_IndRxHandle( CanReceiveHandle rxHandle )
{
#   if defined( C_ENABLE_INDICATION_FLAG )
#    if C_SECURITY_LEVEL > 20
  CanDeclareGlobalInterruptOldStatus
#    endif
#   endif

#   if defined( C_ENABLE_INDICATION_FLAG )
#    if C_SECURITY_LEVEL > 20
  CanNestedGlobalInterruptDisable();
#    endif
  CanIndicationFlags._c[CanGetIndicationOffset(rxHandle)] |= CanGetIndicationMask(rxHandle);
#    if C_SECURITY_LEVEL > 20
  CanNestedGlobalInterruptRestore();
#    endif
#   endif

#   if defined( C_ENABLE_INDICATION_FCT )
  if ( CanGetApplIndicationPtr(rxHandle) != V_NULL )
  {
    CanGetApplIndicationPtr(rxHandle)(rxHandle);  /* call IndicationRoutine */
  }
#   endif
}
/* CODE CATEGORY 1 END */
#  endif /* C_ENABLE_INDICATION_FLAG || C_ENABLE_INDICATION_FCT  */
# endif /* ( kCanNumberOfRxObjects > 0 ) */
#endif

/* **************************************************************************
| NAME:             CanHL_TxConfirmation
| CALLED BY:        CanISR()
| PRECONDITIONS:
| INPUT PARAMETERS: - internal can chip number
|                   - interrupt ID
| RETURN VALUES:    none
| DESCRIPTION:      - full can transmit
************************************************************************** */
/* CODE CATEGORY 1 START */
// void CanHL_TxConfirmation( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle txMailboxHandle, CanObjectHandle txObjHandle)
void CanHL_TxConfirmation( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle txMailboxHandle, CanObjectHandle txObjHandle)
{
  CanObjectHandle       logTxObjHandle; /* PRQA S 0781 */ /* MD_Can_0781 */
  CanTransmitHandle     txHandle;

#if defined( C_ENABLE_TRANSMIT_QUEUE )
  CanSignedTxHandle         queueElementIdx;    /* use as signed due to loop */
  CanSignedTxHandle         elementBitIdx;
  tCanQueueElementType             elem;
  CanDeclareGlobalInterruptOldStatus
#else
# if defined( C_ENABLE_CONFIRMATION_FLAG )
#  if C_SECURITY_LEVEL > 20
  CanDeclareGlobalInterruptOldStatus
#  endif
# endif
#endif

#if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION ) && \
    defined( C_ENABLE_TRANSMIT_QUEUE )
  vuint8 rc;
#endif

  tCanTxConfirmationInfoStruct txConfInfo;

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);
# endif

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(txMailboxHandle >= CAN_HL_MB_TX_STARTINDEX(canHwChannel), channel, kErrorMailboxHandleWrong); /* PRQA S 3689 */ /* MD_Can_3689 */
# else
#  if (kCanMailboxTxStartIndex != 0)
  assertInternal(txMailboxHandle >= CAN_HL_MB_TX_STARTINDEX(canHwChannel), channel, kErrorMailboxHandleWrong);
#  endif
# endif
  assertInternal(txMailboxHandle < CAN_HL_MB_TX_STOPINDEX(canHwChannel), channel, kErrorMailboxHandleWrong); /* PRQA S 3689 */ /* MD_Can_3689 */
  logTxObjHandle = (CanObjectHandle)((vsintx)txMailboxHandle + CAN_HL_TX_OFFSET_MB_TO_LOG(canHwChannel)); /* PRQA S 3689 */ /* MD_Can_3689 */
  txHandle = canHandleCurTxObj[logTxObjHandle];           /* get saved handle */ /* PRQA S 3689 */ /* MD_Can_3689 */

  {
    txConfInfo.mailboxHandle = txMailboxHandle;
    txConfInfo.hwObjHandle = txObjHandle;
    txConfInfo.logTxObjHandle = logTxObjHandle;
//    CanLL_TxConfBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txConfInfo);

    /* check associated transmit handle */
    if (txHandle == kCanBufferFree)
    {
      assertInternal (0, channel, kErrorTxHandleWrong);          /* lint !e506 !e774 */
      goto finishCanHL_TxConfirmation;
    }

#if defined( C_ENABLE_TX_OBSERVE ) || \
    defined( C_ENABLE_CAN_TX_CONF_FCT )
# if defined( C_ENABLE_CANCEL_IN_HW )
    if (CanLL_TxConfIsMsgTransmitted(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txConfInfo) == kCanTrue)
# endif
    {
# if defined( C_ENABLE_TX_OBSERVE )
      {
#  if defined( C_KOMMENTAR_VECTOR_RI14 )
/* ##RI-1.1: Object parameters for Tx-Observe functions */
#  endif
        ApplCanTxObjConfirmed( CAN_CHANNEL_CANPARA_FIRST logTxObjHandle );
      }
# endif

# if defined( C_ENABLE_CAN_TX_CONF_FCT )
/* ##RI-1.10 Common Callbackfunction in TxInterrupt */
        txInfoStructConf[channel].Handle  = txHandle; /* PRQA S 3689 */ /* MD_Can_3689 */
#  if defined( C_ENABLE_CAN_TX_CONF_MSG_ACCESS )
        txConfInfo.txInfoStructConf = &txInfoStructConf[channel]; /* PRQA S 3689 */ /* MD_Can_3689 */
        CanLL_TxConfSetTxConfStruct(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txConfInfo);
#  endif
        APPL_CAN_TX_CONFIRMATION(&txInfoStructConf[channel]); /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
    }
#endif /* defined( C_ENABLE_TX_OBSERVE ) || defined( C_ENABLE_CAN_TX_CONF_FCT ) */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
# if defined( C_ENABLE_TX_FULLCAN_OBJECTS )  || \
     defined( C_ENABLE_MSG_TRANSMIT )
    if (txMailboxHandle != CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel)) /* PRQA S 3689 */ /* MD_Can_3689 */
    {
      canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;                 /* free msg object of FullCAN or LowLevel Tx obj. */ /* PRQA S 3689 */ /* MD_Can_3689 */
    }
# endif
#else
    canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;                   /* free msg object if queue is not used */ /* PRQA S 3689 */ /* MD_Can_3689 */
#endif

    if (txHandle != kCanBufferCancel)
    {
#if defined( C_ENABLE_MSG_TRANSMIT )
      if (txMailboxHandle == CAN_HL_MB_MSG_TRANSMIT_INDEX(canHwChannel)) /* PRQA S 3689 */ /* MD_Can_3689 */
      {
# if defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )
        APPL_CAN_MSGTRANSMITCONF( CAN_CHANNEL_CANPARA_ONLY );
# endif

        goto finishCanHL_TxConfirmation;
      }
#endif

#if defined( C_ENABLE_MULTI_ECU_PHYS )
      assertInternal(((CanTxIdentityAssignment[txHandle] & V_ACTIVE_IDENTITY_MSK) != (tVIdentityMsk)0 ),
                                                                channel, kErrorInternalDisabledTxMessage);
#endif

#if defined( C_ENABLE_CONFIRMATION_FLAG )       /* set transmit ready flag  */
# if C_SECURITY_LEVEL > 20
      CanNestedGlobalInterruptDisable();
# endif
      CanConfirmationFlags._c[CanGetConfirmationOffset(txHandle)] |= CanGetConfirmationMask(txHandle);
# if C_SECURITY_LEVEL > 20
      CanNestedGlobalInterruptRestore();
# endif
#endif

#if defined( C_ENABLE_CONFIRMATION_FCT )
      {
        if ( CanGetApplConfirmationPtr(txHandle) != V_NULL )
        {
          (CanGetApplConfirmationPtr(txHandle))(txHandle);   /* call completion routine  */
        }
      }
#endif /* C_ENABLE_CONFIRMATION_FCT */

    } /* end if kCanBufferCancel */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
# if defined( C_ENABLE_TX_FULLCAN_OBJECTS ) ||\
     defined( C_ENABLE_MSG_TRANSMIT )
    if (txMailboxHandle == CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel)) /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
    {
      CanNestedGlobalInterruptDisable();                /* ESCAN00008914 */

      /* PRQA S 3689 2 */ /* MD_Can_3689 */
      for(queueElementIdx = CAN_HL_TXQUEUE_STOPINDEX(channel) - (CanSignedTxHandle)1;
                               queueElementIdx >= CAN_HL_TXQUEUE_STARTINDEX(channel); queueElementIdx--)
      {
        elem = canTxQueueFlags[queueElementIdx];
        if(elem != (tCanQueueElementType)0) /* is there any flag set in the queue element? */
        {

          CanNestedGlobalInterruptRestore();

          /* start the bitsearch */
          #if defined( C_CPUTYPE_32BIT )
          if((elem & (tCanQueueElementType)0xFFFF0000) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
          {
            if((elem & (tCanQueueElementType)0xFF000000) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
            {
              if((elem & (tCanQueueElementType)0xF0000000) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 28] + 28;
              }
              else /* 0x0F000000 */
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 24] + 24;
              }
            }
            else
            {
              if((elem & (tCanQueueElementType)0x00F00000) != (tCanQueueElementType)0)
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 20] + 20;
              }
              else /* 0x000F0000 */
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 16] + 16;
              }
            }
          }
          else
          #endif
          {
          #if defined( C_CPUTYPE_32BIT )
            if((elem & (tCanQueueElementType)0x0000FF00) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
            {
              if((elem & (tCanQueueElementType)0x0000F000) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 12] + 12;
              }
              else /* 0x00000F00 */
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 8] + 8;
              }
            }
            else
          #endif
            {
              if((elem & (tCanQueueElementType)0x000000F0) != (tCanQueueElementType)0)
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 4] + 4;
              }
              else /* 0x0000000F */
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem];
              }
            }
          }
          /* PRQA S 3689 1 */ /* MD_Can_3689 */
          txHandle = (CanTransmitHandle)((((CanTransmitHandle)queueElementIdx << kCanTxQueueShift) + (CanTransmitHandle)elementBitIdx) - CAN_HL_TXQUEUE_PADBITS(channel));
          {

              /* compute the logical message handle */
              CanNestedGlobalInterruptDisable();

              if ( (canTxQueueFlags[queueElementIdx] & CanShiftLookUp[elementBitIdx]) != (tCanQueueElementType)0 )
              {
                canTxQueueFlags[queueElementIdx] &= (tCanQueueElementType)~CanShiftLookUp[elementBitIdx]; /* clear flag from the queue */

                CanNestedGlobalInterruptRestore();
                canHandleCurTxObj[logTxObjHandle] = txHandle; /* Save hdl of msgObj to be transmitted */ /* PRQA S 3689 */ /* MD_Can_3689 */
# if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
                rc = CanCopyDataAndStartTransmission( CAN_CHANNEL_CANPARA_FIRST txMailboxHandle, txHandle );
                if ( rc == kCanTxNotify)
                {
                  APPLCANCANCELNOTIFICATION(channel, txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
                }
# else /* C_ENABLE_CAN_CANCEL_NOTIFICATION */
                (void)CanCopyDataAndStartTransmission( CAN_CHANNEL_CANPARA_FIRST txMailboxHandle, txHandle );
# endif /* C_ENABLE_CAN_CANCEL_NOTIFICATION */

                goto finishCanHL_TxConfirmation;
              }
              /* meanwhile, the queue is empty. E.g. due to CanOffline on higher level */
              canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;  /* free msg object if queue is empty */ /* PRQA S 3689 */ /* MD_Can_3689 */
              CanNestedGlobalInterruptRestore();
              goto finishCanHL_TxConfirmation;

          }
          /* no entry found in Queue */
# if defined( CANHL_TX_QUEUE_BIT )
# else
          CanNestedGlobalInterruptDisable();                /* lint !e527 ESCAN00008914 */
                                                 /* unreachable in case of Bit-Queue */
# endif
        }
      }

      canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;  /* free msg object if queue is empty */ /* PRQA S 3689 */ /* MD_Can_3689 */
      CanNestedGlobalInterruptRestore();                 /* ESCAN00008914 */
    }
#endif
  /* check for next msg object in queue and transmit it */

/* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
finishCanHL_TxConfirmation:

    CanLL_TxConfEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txConfInfo);
  }
  return;
}
/* END OF CanTxInterrupt */
/* CODE CATEGORY 1 END */

#if defined( C_ENABLE_TX_POLLING )
/* CODE CATEGORY 1 START */
CAN_LOCAL_INLINE void CanHL_TxConfirmationPolling( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle txMailboxHandle, CanObjectHandle txObjHandle )
{
  CANDRV_SET_CODE_TEST_POINT(0x110);

  CAN_CAN_INTERRUPT_DISABLE(channel);
  CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST txMailboxHandle, txObjHandle);
  CAN_CAN_INTERRUPT_RESTORE(channel);
}
/* CODE CATEGORY 1 END */
#endif

#if defined( C_ENABLE_ECU_SWITCH_PASS )
/* **********************************************************************
* NAME:               CanSetActive
* CALLED BY:          application
* PRECONDITIONS:      none
* PARAMETER:          none or channel
* RETURN VALUE:       none
* DESCRIPTION:        Set the CAN driver into active mode
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetActive( CAN_CHANNEL_CANTYPE_ONLY )
{
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif

  canPassive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
} /* END OF CanSetActive */
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:               CanSetPassive
* CALLED BY:          application
* PRECONDITIONS:      none
* PARAMETER:          none or channel
* RETURN VALUE:       none
* DESCRIPTION:        Set the can driver into passive mode
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetPassive( CAN_CHANNEL_CANTYPE_ONLY )
{
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif

  canPassive[channel] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

# if defined( C_ENABLE_TRANSMIT_QUEUE )
  /* clear all Tx queue flags: */
#  if defined( C_KOMMENTAR_VECTOR_LI13 )
/* ##LI-: 1.2    CAN-Offline */
#  endif
  CanDelQueuedObj( CAN_CHANNEL_CANPARA_ONLY );
# endif

} /* END OF CanSetPassive */
/* CODE CATEGORY 4 END */
#endif /* IF defined( C_ENABLE_ECU_SWITCH_PASS ) */

#if defined( C_ENABLE_OFFLINE )
/* **********************************************************************
* NAME:               CanOnline( CanChannelHandle channel )
* CALLED BY:          netmanagement
* PRECONDITIONS:      none
* PARAMETER:          none or channel
* RETURN VALUE:       none
* DESCRIPTION:        Switch on transmit path
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanOnline(CAN_CHANNEL_CANTYPE_ONLY)
{
  CanDeclareGlobalInterruptOldStatus

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif
  {

    CanNestedGlobalInterruptDisable();

    canStatus[channel] |= kCanTxOn; /* PRQA S 3689 */ /* MD_Can_3689 */

#   if defined( C_ENABLE_ONLINE_OFFLINE_CALLBACK_FCT )
    APPL_CAN_ONLINE(CAN_CHANNEL_CANPARA_ONLY);
#   endif
    CanNestedGlobalInterruptRestore();
  }

}
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:               CanOffline( CanChannelHandle channel )
* CALLED BY:          netmanagement
* PRECONDITIONS:      none
* PARAMETER:          none or channel
* RETURN VALUE:       none
* DESCRIPTION:        Switch off transmit path
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanOffline(CAN_CHANNEL_CANTYPE_ONLY) C_API_3
{
  CanDeclareGlobalInterruptOldStatus

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif

  CanNestedGlobalInterruptDisable();

  canStatus[channel] &= kCanTxNotOn; /* PRQA S 3689 */ /* MD_Can_3689 */

# if defined( C_ENABLE_ONLINE_OFFLINE_CALLBACK_FCT )
  APPL_CAN_OFFLINE(CAN_CHANNEL_CANPARA_ONLY);
# endif
  CanNestedGlobalInterruptRestore();

# if defined( C_ENABLE_TRANSMIT_QUEUE )
  CanDelQueuedObj( CAN_CHANNEL_CANPARA_ONLY );
# endif

}
/* CODE CATEGORY 4 END */
#endif /* if defined( C_ENABLE_OFFLINE ) */

#if defined( C_ENABLE_PART_OFFLINE )
/* **********************************************************************
* NAME:               CanSetPartOffline
* CALLED BY:          application
* PRECONDITIONS:      none
* PARAMETER:          (channel), sendGroup
* RETURN VALUE:       none
* DESCRIPTION:        Switch partial off transmit path
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetPartOffline(CAN_CHANNEL_CANTYPE_FIRST vuint8 sendGroup)
{
  CanDeclareGlobalInterruptOldStatus

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif

  CanNestedGlobalInterruptDisable();
  canTxPartOffline[channel] |= sendGroup;  /* PRQA S 3689 */ /* MD_Can_3689 */ /* set offlinestate and Save for use of CanOnline/CanOffline */
  CanNestedGlobalInterruptRestore();
}
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:               CanSetPartOnline
* CALLED BY:          application
* PRECONDITIONS:      none
* PARAMETER:          (channel), invSendGroup
* RETURN VALUE:       none
* DESCRIPTION:        Switch partial on transmit path
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetPartOnline(CAN_CHANNEL_CANTYPE_FIRST vuint8 invSendGroup)
{
  CanDeclareGlobalInterruptOldStatus

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif

  CanNestedGlobalInterruptDisable();
  canTxPartOffline[channel] &= invSendGroup; /* PRQA S 3689 */ /* MD_Can_3689 */
  CanNestedGlobalInterruptRestore();
}
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:               CanGetPartMode
* CALLED BY:          application
* PRECONDITIONS:      none
* PARAMETER:          none or channel
* RETURN VALUE:       canTxPartOffline
* DESCRIPTION:        return status of partoffline-Mode
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanGetPartMode(CAN_CHANNEL_CANTYPE_ONLY)
{
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif

  return canTxPartOffline[channel]; /* PRQA S 3689 */ /* MD_Can_3689 */
}
/* CODE CATEGORY 4 END */
#endif

/* **************************************************************************
| NAME:             CanGetStatus
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none or channel
| RETURN VALUES:    Bit coded status (more than one status can be set):
|                   kCanTxOn
|                   kCanHwIsStop
|                   kCanHwIsInit
|                   kCanHwIsInconsistent
|                   kCanHwIsWarning
|                   kCanHwIsPassive
|                   kCanHwIsBusOff
|                   kCanHwIsSleep
| DESCRIPTION:      returns the status of the transmit path and the CAN hardware.
|                   Only one of the statusbits Sleep, Busoff, Passive, Warning is set.
|                   Sleep has the highest priority, error warning the lowerst.
************************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 vuint8 C_API_2 CanGetStatus( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3
{
#if defined( C_ENABLE_EXTENDED_STATUS )
#endif

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif

#if defined( C_ENABLE_EXTENDED_STATUS )
  CanLL_GetStatusBegin(CAN_CHANNEL_CANPARA_ONLY);

# if defined( C_ENABLE_SLEEP_WAKEUP )
  /* *************************** verify Sleep mode *********************************** */
  if ( CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY) )  { return ( VUINT8_CAST ( canStatus[channel] | kCanHwIsSleep ) ); } /* PRQA S 3689 */ /* MD_Can_3689 */

# endif

  /* *************************** verify Stop mode *********************************** */
  if ( CanLL_HwIsStop(CAN_HW_CHANNEL_CANPARA_ONLY) )  { return ( VUINT8_CAST ( canStatus[channel] | kCanHwIsStop ) ); } /* PRQA S 3689 */ /* MD_Can_3689 */

  /* *************************** verify Busoff *********************************** */
  if ( CanLL_HwIsBusOff(CAN_HW_CHANNEL_CANPARA_ONLY) )  { return ( VUINT8_CAST ( canStatus[channel] | kCanHwIsBusOff ) ); } /* PRQA S 3689 */ /* MD_Can_3689 */

  /* *************************** verify Error Passive **************************** */
  {
    if ( CanLL_HwIsPassive(CAN_HW_CHANNEL_CANPARA_ONLY) )  { return ( VUINT8_CAST ( canStatus[channel] | kCanHwIsPassive ) ); } /* PRQA S 3689 */ /* MD_Can_3689 */
  }

  /* *************************** verify Error Warning **************************** */
  {
    if ( CanLL_HwIsWarning(CAN_HW_CHANNEL_CANPARA_ONLY) )  { return ( VUINT8_CAST ( canStatus[channel] | kCanHwIsWarning ) ); } /* PRQA S 3689 */ /* MD_Can_3689 */
  }
#endif
  return ( VUINT8_CAST (canStatus[channel] & kCanTxOn) ); /* PRQA S 3689 */ /* MD_Can_3689 */

} /* END OF CanGetStatus */
/* CODE CATEGORY 3 END */

/* **************************************************************************
| NAME:             CanSleep
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none or channel
| RETURN VALUES:    kCanOk, if CanSleep was successfull
|                   kCanFailed, if function failed
|                   kCanNotSupported, if this function is not supported
| DESCRIPTION:      disable CAN
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanSleep(CAN_CHANNEL_CANTYPE_ONLY)
{
#if defined( C_ENABLE_SLEEP_WAKEUP )
  vuint8         canReturnCode;
#endif

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif
#if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) && !defined (C_ENABLE_OSEK_CAN_INTCTRL)
  assertUser((canCanInterruptCounter[channel] == (vsintx)0), channel, kErrorDisabledCanInt);    /* PRQA S 3689 */ /* MD_Can_3689 */
#endif

#if defined( C_ENABLE_COND_RECEIVE_FCT )
  /* this has to be done, even if SLEEP_WAKEUP is not enabled */
  canMsgCondRecState[channel] = kCanTrue;
#endif

#if defined( C_ENABLE_SLEEP_WAKEUP )
  assertUser((canStatus[channel] & kCanTxOn) != kCanTxOn, channel, kErrorCanOnline); /* PRQA S 3689 */ /* MD_Can_3689 */

  {
    assertUser(!CanLL_HwIsStop(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanStop); /* PRQA S 3689 */ /* MD_Can_3689 */

    canReturnCode = CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST kCanModeSleep, kCanFinishBusOffRecovery);

    if (canReturnCode == kCanRequested)
    {
      CanHL_ApplCanTimerStart(kCanLoopSleep);
      do
      {
        canReturnCode = CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST kCanModeSleep, kCanFinishBusOffRecovery);
        CanHL_ApplCanTimerLoop(kCanLoopSleep);
      } while (canReturnCode != kCanOk);
      CanHL_ApplCanTimerEnd(kCanLoopSleep);
    }

  }
  return canReturnCode;
#else
  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
  return kCanNotSupported;
#endif
}
/* END OF CanSleep */
/* CODE CATEGORY 4 END */

/* **************************************************************************
| NAME:             CanWakeUp
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none or channel
| RETURN VALUES:    kCanOk, if CanWakeUp was successfull
|                   kCanFailed, if function failed
|                   kCanNotSupported, if this function is not supported
| DESCRIPTION:      enable CAN
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanWakeUp( CAN_CHANNEL_CANTYPE_ONLY )
{
#if defined( C_ENABLE_SLEEP_WAKEUP )
  vuint8         canReturnCode;

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif
#if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) && !defined (C_ENABLE_OSEK_CAN_INTCTRL)
  assertUser((canCanInterruptCounter[channel] == (vsintx)0), channel, kErrorDisabledCanInt);    /* PRQA S 3689 */ /* MD_Can_3689 */
#endif

  {
    canReturnCode = CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST kCanModeWakeupStart, kCanFinishBusOffRecovery);

    if (canReturnCode == kCanRequested)
    {
      CanHL_ApplCanTimerStart(kCanLoopWakeup);
      do
      {
        canReturnCode = CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST kCanModeWakeupStart, kCanFinishBusOffRecovery);
        CanHL_ApplCanTimerLoop(kCanLoopWakeup);
      } while (canReturnCode != kCanOk);
      CanHL_ApplCanTimerEnd(kCanLoopWakeup);
    }

  }
  return canReturnCode;
#else
  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
  return kCanNotSupported;
#endif /* C_ENABLE_SLEEP_WAKEUP */
}
/* END OF CanWakeUp */
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_STOP )
/* **************************************************************************
| NAME:             CanStop
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    kCanOk, if success
|                   kCanFailed, if function failed
|                   kCanNotSupported, if this function is not supported
| DESCRIPTION:      stop CAN-controller
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanStop( CAN_CHANNEL_CANTYPE_ONLY )
{
  vuint8         canReturnCode;

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif
  assertUser((canStatus[channel] & kCanTxOn) != kCanTxOn, channel, kErrorCanOnline);   /* PRQA S 3689 */ /* MD_Can_3689 */

  {
# if defined( C_ENABLE_SLEEP_WAKEUP )
    assertUser(!CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanSleep); /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

    canReturnCode = CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST kCanModeStop, kCanFinishBusOffRecovery);

    if (canReturnCode == kCanRequested)
    {
      CanHL_ApplCanTimerStart(kCanLoopStop);
      do
      {
        canReturnCode = CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST kCanModeStop, kCanFinishBusOffRecovery);
        CanHL_ApplCanTimerLoop(kCanLoopStop);
      } while (canReturnCode != kCanOk);
      CanHL_ApplCanTimerEnd(kCanLoopStop);
    }

    if ( canReturnCode == kCanOk )
    {
      CanLL_StopReinit(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY);
    }

  }
  return canReturnCode;
}
/* CODE CATEGORY 4 END */

/* **************************************************************************
| NAME:             CanStart
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    kCanOk, if success
|                   kCanFailed, if function failed
|                   kCanNotSupported, if this function is not supported
| DESCRIPTION:      restart CAN-controller
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanStart( CAN_CHANNEL_CANTYPE_ONLY )
{
  vuint8         canReturnCode;

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif

  {
    canReturnCode = CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST kCanModeStart, kCanFinishBusOffRecovery);

    if (canReturnCode == kCanRequested)
    {
      CanHL_ApplCanTimerStart(kCanLoopStart);
      do
      {
        canReturnCode = CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST kCanModeStart, kCanFinishBusOffRecovery);
        CanHL_ApplCanTimerLoop(kCanLoopStart);
      } while (canReturnCode != kCanOk);
      CanHL_ApplCanTimerEnd(kCanLoopStart);
    }

  }
  return canReturnCode;
}
/* CODE CATEGORY 4 END */
#endif /* if defined( C_ENABLE_STOP ) */

#if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL)
/* **************************************************************************
| NAME:             CanCanInterruptDisable
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      disables CAN interrupts and stores old interrupt status
************************************************************************** */
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 CanCanInterruptDisable( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3
{
# if defined (C_ENABLE_OSEK_CAN_INTCTRL)

  {
    OsCanCanInterruptDisable(CAN_HW_CHANNEL_CANPARA_ONLY);
  }
# else /* defined (C_ENABLE_OSEK_CAN_INTCTRL) */

  CanDeclareGlobalInterruptOldStatus
#  if defined( C_HL_ENABLE_CAN_IRQ_DISABLE )
#  endif

  /* local variable must reside on stack or registerbank, switched */
  /* in interrupt level                                            */
  /* disable global interrupt                                      */
#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#  endif
  assertUser(canCanInterruptCounter[channel]<(vsint8)0x7f, kCanAllChannels, kErrorIntDisableTooOften);    /* PRQA S 3689 */ /* MD_Can_3689 */

  CanNestedGlobalInterruptDisable();
  if (canCanInterruptCounter[channel] == (vsintx)0) /* PRQA S 3689 */ /* MD_Can_3689 */ /* if 0 then save old interrupt status */
  {
#  if defined( C_HL_ENABLE_CAN_IRQ_DISABLE )
    {
#   if defined( C_ENABLE_SLEEP_WAKEUP )
      assertUser(!CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanSleep); /* PRQA S 3689 */ /* MD_Can_3689 */
#   endif

      CanLL_CanInterruptDisable(CAN_HW_CHANNEL_CANPARA_FIRST &canCanInterruptOldStatus[canHwChannel]); /* PRQA S 3689 */ /* MD_Can_3689 */
    }
#  endif
#  if defined( C_ENABLE_INTCTRL_ADD_CAN_FCT )
    ApplCanAddCanInterruptDisable(channel);
#  endif
  }
  canCanInterruptCounter[channel]++;     /* PRQA S 3689 */ /* MD_Can_3689 */ /* common for all platforms */

  CanNestedGlobalInterruptRestore();
# endif /* C_ENABLE_OSEK_CAN_INTCTRL */
}
/* END OF CanCanInterruptDisable */
/* CODE CATEGORY 1 END */

/* **************************************************************************
| NAME:             CanCanInterruptRestore
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      restores the old interrupt status of the CAN interrupt if
|                   canCanInterruptCounter[channel] is zero
************************************************************************** */
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 CanCanInterruptRestore( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3
{
# if defined (C_ENABLE_OSEK_CAN_INTCTRL)

  {
    OsCanCanInterruptRestore(CAN_HW_CHANNEL_CANPARA_ONLY);
  }
# else /* defined (C_ENABLE_OSEK_CAN_INTCTRL) */

  CanDeclareGlobalInterruptOldStatus
#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#  endif
  assertUser(canCanInterruptCounter[channel]>(vsintx)0, kCanAllChannels, kErrorIntRestoreTooOften);   /* PRQA S 3689 */ /* MD_Can_3689 */

  CanNestedGlobalInterruptDisable();
  /* restore CAN interrupt */
  canCanInterruptCounter[channel]--; /* PRQA S 3689 */ /* MD_Can_3689 */

  if (canCanInterruptCounter[channel] == (vsintx)0)   /* PRQA S 3689 */ /* MD_Can_3689 */ /* restore interrupt if canCanInterruptCounter=0 */
  {
#  if defined( C_HL_ENABLE_CAN_IRQ_DISABLE )
    {
#   if defined( C_ENABLE_SLEEP_WAKEUP )
      assertUser(!CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanSleep); /* PRQA S 3689 */ /* MD_Can_3689 */
#   endif

      CanLL_CanInterruptRestore(CAN_HW_CHANNEL_CANPARA_FIRST canCanInterruptOldStatus[canHwChannel]); /* PRQA S 3689 */ /* MD_Can_3689 */
    }
#  endif

#  if defined( C_ENABLE_INTCTRL_ADD_CAN_FCT )
    ApplCanAddCanInterruptRestore(channel);
#  endif
  }
  CanNestedGlobalInterruptRestore();
# endif /* defined (C_ENABLE_OSEK_CAN_INTCTRL) */
}
/* END OF CanCanInterruptRestore */
/* CODE CATEGORY 1 END */
#endif /* defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) */

#if defined( C_ENABLE_MSG_TRANSMIT )
/* **********************************************************************
* NAME:               CanMsgTransmit
* CALLED BY:          CanReceivedFunction
* PRECONDITIONS:      Called in Receive Interrupt
* PARAMETER:          Pointer to message buffer data block; This can either be
*                     a RAM structure data block or the receive buffer in the
*                     CAN chip
* RETURN VALUE:       The return value says that a transmit request was successful
*                     or not
* DESCRIPTION:        Transmit functions for gateway issues (with dynamic
*                     messages). If the transmit buffer is not free, the message
*                     is inserted in the FIFO ring buffer.
*********************************************************************** */
/* Msg(4:3673) The object addressed by the pointer "txMsgStruct" is not modified in this function.
   The use of "const" should be considered to indicate that it never changes. MISRA Rule 81 - no change */
/* CODE CATEGORY 2 START */
# if defined ( V_ENABLE_USED_GLOBAL_VAR )
/* txMsgStruct is located in far memory */
C_API_1 vuint8 C_API_2 CanMsgTransmit( CAN_CHANNEL_CANTYPE_FIRST V_MEMRAM1_FAR tCanMsgTransmitStruct V_MEMRAM2_FAR V_MEMRAM3_FAR *txMsgStruct )       /* PRQA S 3673 */ /* MD_Can_3673 */
{
# else
C_API_1 vuint8 C_API_2 CanMsgTransmit( CAN_CHANNEL_CANTYPE_FIRST tCanMsgTransmitStruct *txMsgStruct )       /* PRQA S 3673 */ /* MD_Can_3673 */
{
# endif
  CanDeclareGlobalInterruptOldStatus
  vuint8                   rc;
  CanObjectHandle          txMailboxHandle;
  CanObjectHandle          logTxObjHandle; /* PRQA S 0781 */ /* MD_Can_0781 */

  tCanTxMsgTransmissionInfoStruct txInfo;

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif

  assertUser( (txMsgStruct != V_NULL), channel, kErrorNullPointerParameter);

  CanNestedGlobalInterruptDisable();

  /* --- test on CAN transmit switch --- */
  if ( (canStatus[channel] & kCanTxOn) != kCanTxOn ) /* PRQA S 3689 */ /* MD_Can_3689 */                /* transmit path switched off */
  {
    CanNestedGlobalInterruptRestore();
    return kCanTxFailed;
  }

# if defined( C_ENABLE_CAN_RAM_CHECK )
  if(canComStatus[channel] == kCanDisableCommunication) /* PRQA S 3689 */ /* MD_Can_3689 */
  {
    CanNestedGlobalInterruptRestore();
    return(kCanCommunicationDisabled);
  }
# endif

# if defined( C_ENABLE_SLEEP_WAKEUP )
  assertUser(!CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanSleep); /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
  assertUser(!CanLL_HwIsStop(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanStop); /* PRQA S 3689 */ /* MD_Can_3689 */

  /* --- check on passive state --- */
# if defined( C_ENABLE_ECU_SWITCH_PASS )
  if ( canPassive[channel] != (vuint8)0) /* PRQA S 3689 */ /* MD_Can_3689 */                            /*  set passive ? */
  {
    CanNestedGlobalInterruptRestore();
#  if defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )
    APPL_CAN_MSGTRANSMITCONF( CAN_CHANNEL_CANPARA_ONLY );
#  endif
    return (kCanTxOk);
  }
# endif /* C_ENABLE_ECU_SWITCH_PASS */

  /* calculate index for canHandleCurTxObj (logical object handle) */
  logTxObjHandle = (CanObjectHandle)((vsintx)CAN_HL_MB_MSG_TRANSMIT_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_MB_TO_LOG(canHwChannel)); /* PRQA S 3689 */ /* MD_Can_3689 */

  /* check for transmit message object free --------------------------------- */
  /* MsgObj used?  */
  if (( canHandleCurTxObj[logTxObjHandle] != kCanBufferFree ))
  {
    CanNestedGlobalInterruptRestore();
    return kCanTxFailed;
  }

  /* Obj, pMsgObject points to is free, transmit msg object: ---------------- */
  /* Save hdl of msgObj to be transmitted */
  canHandleCurTxObj[logTxObjHandle] = kCanBufferMsgTransmit;
  CanNestedGlobalInterruptRestore();

  txMailboxHandle = CAN_HL_MB_MSG_TRANSMIT_INDEX(canHwChannel); /* PRQA S 3689 */ /* MD_Can_3689 */
  assertHardware(CanLL_TxIsObjFree(canHwChannel, Can_Mailbox[txMailboxHandle].HwObjHandle), channel, kErrorTxBufferBusy); /* PRQA S 3689 */ /* MD_Can_3689 */

  txInfo.mailboxHandle = txMailboxHandle;
  txInfo.hwObjHandle = Can_Mailbox[txMailboxHandle].HwObjHandle;
  txInfo.logTxObjHandle = logTxObjHandle;
  txInfo.txMsgStruct = txMsgStruct;

  CanLL_TxBeginMsgTransmit(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txInfo);

  CanNestedGlobalInterruptDisable();
  /* Copy all data into transmit object */

  /* If CanTransmit was interrupted by a re-initialization or CanOffline */
  /* no transmitrequest of this action should be started      */
  if ((canHandleCurTxObj[logTxObjHandle] == kCanBufferMsgTransmit) &&
                                   ( (canStatus[channel] & kCanTxOn) == kCanTxOn ) ) /* PRQA S 3689 */ /* MD_Can_3689 */
  {
     CanLL_TxCopyMsgTransmit(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txInfo);

     rc = CanLL_TxStartMsgTransmit(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txInfo);

     {
# if defined( C_ENABLE_TX_OBSERVE )
#  if defined( C_KOMMENTAR_VECTOR_RI14 )
/* ##RI-1.1: Object parameters for Tx-Observe functions */
#  endif
       ApplCanTxObjStart( CAN_CHANNEL_CANPARA_FIRST logTxObjHandle );
# endif
       /* explicit set of rc to kCanTxOk not necessary, because kCanTxOk and kCanOk are identical (return of CanLL_TxStartMsgTransmit) */
     }
  }
  else
  {
    /* release TxHandle (CanOffline) */
    canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;  /* PRQA S 3689 */ /* MD_Can_3689 */
    rc = kCanTxFailed;
  }

  CanNestedGlobalInterruptRestore();

  CanLL_TxEndMsgTransmit(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txInfo);

  return rc;
}
/* end of CanMsgTransmit() */
/* CODE CATEGORY 2 END */
#endif

#if defined( C_ENABLE_DYN_TX_OBJECTS )
/* **********************************************************************
* NAME:           CanGetDynTxObj
* PARAMETER:      txHandle - Handle of the dynamic object to reserve
* RETURN VALUE:   kCanNoTxDynObjAvailable (0xFF) -
*                   object not available
*                 0..F0 -
*                   Handle to dynamic transmission object
* DESCRIPTION:    Function reserves and return a handle to a dynamic
*                   transmission object
*
*                 To use dynamic transmission, an application must get
*                 a dynamic object from CAN-driver.
*                 Before transmission, application must set all attributes
*                 (id, dlc, data, confirmation function/flag, pretransmission
*                 etc. - as configurated).
*                 Application can use a dynamic object for one or many
*                 transmissions (as it likes) - but finally, it must
*                 release the dynamic object by calling CanReleaseDynTxObj.
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 CanTransmitHandle C_API_2 CanGetDynTxObj(CanTransmitHandle txHandle ) C_API_3
{
  CanTransmitHandle nTxDynObj;
  CanDeclareGlobalInterruptOldStatus
  CAN_CHANNEL_CANTYPE_LOCAL

  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* lint !e568 */
# endif

  nTxDynObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel); /* PRQA S 3382, 0291 */ /* MD_Can_3382,MD_Can_0291 */

  CanNestedGlobalInterruptDisable();
  if ( canTxDynObjReservedFlag[nTxDynObj] != (vuint8)0) /* PRQA S 3689 */ /* MD_Can_3689 */
  {
    CanNestedGlobalInterruptRestore();
    return kCanNoTxDynObjAvailable;
  }
  /*  Mark dynamic object as used  */
  canTxDynObjReservedFlag[nTxDynObj] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

# if defined( C_ENABLE_CONFIRMATION_FLAG )
  CanConfirmationFlags._c[CanGetConfirmationOffset(txHandle)] &=          /* PRQA S 3689 */ /* MD_Can_3689 */
                            (vuint8)(~CanGetConfirmationMask(txHandle));  /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
  CanNestedGlobalInterruptRestore();

  /* Initialize dynamic object */
# if defined( C_ENABLE_DYN_TX_DATAPTR )
  canDynTxDataPtr[nTxDynObj] = V_NULL;  /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

  return (txHandle);
}
/* CODE CATEGORY 3 END */

/* **********************************************************************
* NAME:           CanReleaseDynTxObj
* PARAMETER:      hTxObj -
*                   Handle of dynamic transmission object
* RETURN VALUE:   --
* DESCRIPTION:    Function releases dynamic transmission object
*                   which was reserved before (calling CanGetDynTxObj)
*
*                 After a transmission of one or more messages is finished,
*                 application must free the reserved resource, formally the
*                 dynamic transmission object calling this function.
*
*                 As the number of dynamic transmission object is limited,
*                 application should not keep unused dynamic transmission
*                 objects for a longer time.
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 vuint8 C_API_2 CanReleaseDynTxObj(CanTransmitHandle txHandle) C_API_3
{
  CanTransmitHandle dynTxObj;
  CAN_CHANNEL_CANTYPE_LOCAL
# if defined( C_ENABLE_TRANSMIT_QUEUE )
  CanSignedTxHandle queueElementIdx; /* index for accessing the tx queue */
  CanSignedTxHandle elementBitIdx;  /* bit index within the tx queue element */
  CanTransmitHandle queueBitPos;  /* physical bitposition of the handle */
# endif

  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* lint !e568 */
# endif

  dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel);  /* PRQA S 3382,0291 */ /* MD_Can_3382,MD_Can_0291 */

  assertInternal((canTxDynObjReservedFlag[dynTxObj] != (vuint8)0), channel, kErrorReleasedUnusedDynObj);  /* PRQA S 3689 */ /* MD_Can_3689 */

# if defined( C_ENABLE_TRANSMIT_QUEUE )
  #if defined( C_ENABLE_INTERNAL_CHECK ) &&\
      defined( C_MULTIPLE_RECEIVE_CHANNEL )
  if (sizeof(queueBitPos) == 1) /* PRQA S 3325 */ /* MD_Can_3201 */
  { /* PRQA S 3201 */ /* MD_Can_3201 */
    assertInternal( ((vuint16)((vuint16)kCanNumberOfTxObjects + (vuint16)CanTxQueuePadBits[kCanNumberOfChannels-1]) <= 256u), kCanAllChannels, kErrorTxQueueTooManyHandle) /*lint !e572 !e506*/
  }
  else
  {
    if (((sizeof(tCanTxQueuePadBits) == 1) && (kCanNumberOfTxObjects > (65536 - 256))) || (sizeof(tCanTxQueuePadBits) > 1)) /* PRQA S 3325 */ /* MD_Can_3201 */
    { /* PRQA S 3201 */ /* MD_Can_3201 */
      assertInternal( ((vuint32)((vuint32)kCanNumberOfTxObjects + (vuint32)CanTxQueuePadBits[kCanNumberOfChannels-1]) <= 65536u), kCanAllChannels, kErrorTxQueueTooManyHandle) /*lint !e572 !e506*/
    }
  }
  #endif
  queueBitPos  = txHandle + CAN_HL_TXQUEUE_PADBITS(channel);
  queueElementIdx = (CanSignedTxHandle)(queueBitPos >> kCanTxQueueShift); /* get the queue element where to set the flag */
  elementBitIdx  = (CanSignedTxHandle)(queueBitPos & kCanTxQueueMask);   /* get the flag index wihtin the queue element */
  if( (canTxQueueFlags[queueElementIdx] & CanShiftLookUp[elementBitIdx]) != (tCanQueueElementType)0 )
  {
  }
  else
# endif
  {
    if (
# if defined( C_ENABLE_CONFIRMATION_FCT ) && \
    defined( C_ENABLE_TRANSMIT_QUEUE )
         (confirmHandle[channel] == txHandle) ||       /* confirmation active ? */
# endif
         (canHandleCurTxObj[(vsintx)CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_MB_TO_LOG(canHwChannel)] != txHandle) )
    {
      /*  Mark dynamic object as not used  */
      canTxDynObjReservedFlag[dynTxObj] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
      return(kCanDynReleased);
    }
  }
  return(kCanDynNotReleased);
}
/* CODE CATEGORY 3 END */
#endif /* C_ENABLE_DYN_TX_OBJECTS */

#if defined( C_ENABLE_DYN_TX_ID )
# if !defined( C_ENABLE_EXTENDED_ID ) ||\
     defined( C_ENABLE_MIXED_ID )
/* **********************************************************************
* NAME:           CanDynTxObjSetId
* PARAMETER:      hTxObj -
*                   Handle of dynamic transmission object
*                 id -
*                   Id (standard-format) to register with dynamic object
* RETURN VALUE:   --
* DESCRIPTION:    Function registers submitted id (standard format)
*                 with dynamic object referenced by handle.
*********************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetId(CanTransmitHandle txHandle, vuint16 id) C_API_3
{
  CanTransmitHandle dynTxObj;

  CAN_CHANNEL_CANTYPE_LOCAL

  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif

  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* lint !e568 */
# endif
  assertUser(id <= (vuint16)0x7FF, channel, kErrorWrongId);

  dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel); /* PRQA S 3382,0291 */ /* MD_Can_3382,MD_Can_0291 */

#  if defined( C_ENABLE_MIXED_ID )
  canDynTxIdType[dynTxObj]  = kCanIdTypeStd;        /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
#  if defined( C_ENABLE_CAN_FD_USED )
  canDynTxFdType[dynTxObj] = kCanFdTypeClassic;     /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif

  canDynTxId0[dynTxObj] = MK_STDID0(id);     /* PRQA S 3689 */ /* MD_Can_3689 */
#  if (kCanNumberOfUsedCanTxIdTables > 1)
  canDynTxId1[dynTxObj] = MK_STDID1(id);     /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 2)
  canDynTxId2[dynTxObj] = MK_STDID2(id);     /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 3)
  canDynTxId3[dynTxObj] = MK_STDID3(id);     /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 4)
  canDynTxId4[dynTxObj] = MK_STDID4(id);     /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
}
/* CODE CATEGORY 2 END */

#  if defined(C_ENABLE_CAN_FD_USED)
/* **********************************************************************
* NAME:           CanDynTxObjSetFdId
* PARAMETER:      hTxObj -
*                   Handle of dynamic transmission object
*                 id -
*                   Id (standard-format) to register with dynamic object
* RETURN VALUE:   --
* DESCRIPTION:    Function registers submitted id (standard and FD format)
*                 with dynamic object referenced by handle.
*********************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetFdId(CanTransmitHandle txHandle, vuint16 id) C_API_3
{
  CanTransmitHandle dynTxObj;

  CAN_CHANNEL_CANTYPE_LOCAL

  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif

  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* lint !e568 */
# endif
  assertUser(id <= (vuint16)0x7FF, channel, kErrorWrongId);
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(CAN_HL_IS_CH_CANFD(channel)==kCanTrue, channel, kErrorNoCanFd);
# endif

  dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel); /* PRQA S 3382,0291 */ /* MD_Can_3382,MD_Can_0291 */

#  if defined( C_ENABLE_MIXED_ID )
  canDynTxIdType[dynTxObj]  = kCanIdTypeStd; /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
  canDynTxFdType[dynTxObj] = kCanFdTypeFd;   /* PRQA S 3689 */ /* MD_Can_3689 */

  canDynTxId0[dynTxObj] = MK_STDID0(id);     /* PRQA S 3689 */ /* MD_Can_3689 */
#  if (kCanNumberOfUsedCanTxIdTables > 1)
  canDynTxId1[dynTxObj] = MK_STDID1(id);     /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 2)
  canDynTxId2[dynTxObj] = MK_STDID2(id);     /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 3)
  canDynTxId3[dynTxObj] = MK_STDID3(id);     /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 4)
  canDynTxId4[dynTxObj] = MK_STDID4(id);     /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
}
/* CODE CATEGORY 2 END */
#  endif /* C_ENABLE_CAN_FD_USED */
# endif /* !defined( C_ENABLE_EXTENDED_ID ) || defined( C_ENABLE_MIXED_ID ) */
#endif /* C_ENABLE_DYN_TX_ID */

#if defined( C_ENABLE_DYN_TX_ID ) && \
    defined( C_ENABLE_EXTENDED_ID )
/* **********************************************************************
* NAME:           CanDynTxObjSetExtId32
* PARAMETER:      hTxObj -
*                   Handle of dynamic transmission object
*                 id -
*                   Id (extended-format) to register with dynamic object
* RETURN VALUE:   --
* DESCRIPTION:    Function registers submitted id (extended format)
*                 with dynamic object referenced by handle.
*********************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetExtId32(CanTransmitHandle txHandle, vuint32 id) C_API_3
{
  CanTransmitHandle dynTxObj;
  CAN_CHANNEL_CANTYPE_LOCAL

  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* lint !e568 */
# endif
  assertUser(id <= (vuint32)0x1FFFFFFF, channel, kErrorWrongId);

  dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel); /* PRQA S 3382,0291 */ /* MD_Can_3382,MD_Can_0291 */

# if defined( C_ENABLE_MIXED_ID )
  canDynTxIdType[dynTxObj] = kCanIdTypeExt;      /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
#  if defined( C_ENABLE_CAN_FD_USED )
  canDynTxFdType[dynTxObj] = kCanFdTypeClassic;  /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif

  canDynTxId0[dynTxObj]      = MK_EXTID0(id);    /* PRQA S 3689 */ /* MD_Can_3689 */
# if (kCanNumberOfUsedCanTxIdTables > 1)
  canDynTxId1[dynTxObj]      = MK_EXTID1(id);    /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
  canDynTxId2[dynTxObj]      = MK_EXTID2(id);    /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
  canDynTxId3[dynTxObj]      = MK_EXTID3(id);    /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
  canDynTxId4[dynTxObj]      = MK_EXTID4(id);    /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
}
/* CODE CATEGORY 2 END */

# if defined(C_ENABLE_CAN_FD_USED)
/* **********************************************************************
* NAME:           CanDynTxObjSetFdExtId32
* PARAMETER:      hTxObj -
*                   Handle of dynamic transmission object
*                 id -
*                   Id (extended-format) to register with dynamic object
* RETURN VALUE:   --
* DESCRIPTION:    Function registers submitted id (extended and FD format)
*                 with dynamic object referenced by handle.
*********************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetFdExtId32(CanTransmitHandle txHandle, vuint32 id) C_API_3
{
  CanTransmitHandle dynTxObj;
  CAN_CHANNEL_CANTYPE_LOCAL

  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* lint !e568 */
# endif
  assertUser(id <= (vuint16)0x1FFFFFFF, channel, kErrorWrongId);
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(CAN_HL_IS_CH_CANFD(channel)==kCanTrue, channel, kErrorNoCanFd);
# endif

  dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel); /* PRQA S 3382,0291 */ /* MD_Can_3382,MD_Can_0291 */

# if defined( C_ENABLE_MIXED_ID )
  canDynTxIdType[dynTxObj] = kCanIdTypeExt;      /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
  canDynTxFdType[dynTxObj] = kCanFdTypeFd;       /* PRQA S 3689 */ /* MD_Can_3689 */

  canDynTxId0[dynTxObj]      = MK_EXTID0(id);    /* PRQA S 3689 */ /* MD_Can_3689 */
# if (kCanNumberOfUsedCanTxIdTables > 1)
  canDynTxId1[dynTxObj]      = MK_EXTID1(id);    /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
  canDynTxId2[dynTxObj]      = MK_EXTID2(id);    /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
  canDynTxId3[dynTxObj]      = MK_EXTID3(id);    /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
  canDynTxId4[dynTxObj]      = MK_EXTID4(id);    /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
}
/* CODE CATEGORY 2 END */
# endif /* C_ENABLE_CAN_FD_USED */
#endif

#if defined( C_ENABLE_DYN_TX_DLC )
/* **********************************************************************
* NAME:           CanDynTxObjSetMessageLength
* PARAMETER:      hTxObj -
*                   Handle of dynamic transmission object
*                 messageLen -
*                   message length to register with dynamic object
* RETURN VALUE:   --
* DESCRIPTION:    Function registers data length code with
*                 dynamic object referenced by submitted handle.
*********************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetMessageLength(CanTransmitHandle txHandle, vuint8 messageLength) C_API_3
{
  CanTransmitHandle dynTxObj;
  CAN_CHANNEL_CANTYPE_LOCAL

  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* lint !e568 */
# endif
  assertUser(messageLength <= CAN_HL_MAX_LEN(channel), channel, kErrorTxDlcTooLarge); /* PRQA S 3689 */ /* MD_Can_3689 */

  if (messageLength > CAN_HL_MAX_LEN(channel))
  {
    messageLength = CAN_HL_MAX_LEN(channel);
  }

  dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel); /* PRQA S 3382,0291 */ /* MD_Can_3382,MD_Can_0291 */

# if defined( C_ENABLE_EXTENDED_ID )
  canDynTxDLC[dynTxObj] = MK_TX_DLC_EXT(CAN_LEN2DLC(messageLength)); /* PRQA S 3689 */ /* MD_Can_3689 */
# else
  canDynTxDLC[dynTxObj] = MK_TX_DLC(CAN_LEN2DLC(messageLength));     /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
# if defined( C_ENABLE_CAN_FD_FULL ) && (defined( C_ENABLE_PRETRANSMIT_FCT ) || defined( C_ENABLE_COPY_TX_DATA ))
  canDynTxMessageLength[dynTxObj] = messageLength;     /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
}
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_DYN_TX_DLC */

#if defined( C_ENABLE_DYN_TX_DATAPTR )
/* **********************************************************************
* NAME:           CanDynTxObjSetDataPtr
* PARAMETER:      hTxObj -
*                   Handle of dynamic transmission object
*                 pData -
*                   data reference to be stored in data buffer of dynamic object
* RETURN VALUE:   --
* DESCRIPTION:    Functions stores reference to data registered with
*                 dynamic object.
*
*                 The number of byte copied is (always) 8. The number of
*                 relevant (and consequently evaluated) byte is to be
*                 taken from function CanDynObjGetDLC.
*********************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetDataPtr(CanTransmitHandle txHandle, void* pData) C_API_3
{
  CanTransmitHandle dynTxObj;
  CAN_CHANNEL_CANTYPE_LOCAL

  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* lint !e568 */
# endif

  dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel);  /* PRQA S 3382,0291 */ /* MD_Can_3382,MD_Can_0291 */

  canDynTxDataPtr[dynTxObj] = pData; /* PRQA S 3689 */ /* MD_Can_3689 */
}
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_DYN_TX_DATAPTR */

#if defined( C_ENABLE_TX_MASK_EXT_ID )
/* **********************************************************************
* NAME:               CanSetTxIdExtHi
* CALLED BY:
* PRECONDITIONS:      CanInitPower should already been called.
* PARAMETER:          new source address for the 29-bit CAN-ID
* RETURN VALUE:       -
* DESCRIPTION:        Sets the source address in the lower 8 bit of the
*                     29-bit CAN identifier.
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtHi( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif
  assertUser(mask <= (vuint8)0x1F, channel, kErrorWrongMask);

  canTxMask0[channel] = (canTxMask0[channel] & MK_EXTID0(0x00FFFFFFUL)) | MK_EXTID0((vuint32)mask<<24);
# if (kCanNumberOfUsedCanTxIdTables > 1)
  canTxMask1[channel] = (canTxMask1[channel] & MK_EXTID1(0x00FFFFFFUL)) | MK_EXTID1((vuint32)mask<<24);
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
  canTxMask2[channel] = (canTxMask2[channel] & MK_EXTID2(0x00FFFFFFUL)) | MK_EXTID2((vuint32)mask<<24);
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
  canTxMask3[channel] = (canTxMask3[channel] & MK_EXTID3(0x00FFFFFFUL)) | MK_EXTID3((vuint32)mask<<24);
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
  canTxMask4[channel] = (canTxMask4[channel] & MK_EXTID4(0x00FFFFFFUL)) | MK_EXTID4((vuint32)mask<<24);
# endif
}
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:               CanSetTxIdExtMidHi
* CALLED BY:
* PRECONDITIONS:      CanInitPower should already been called.
* PARAMETER:          new source address for the 29-bit CAN-ID
* RETURN VALUE:       -
* DESCRIPTION:        Sets the source address in the lower 8 bit of the
*                     29-bit CAN identifier.
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtMidHi( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif

  canTxMask0[channel] = (canTxMask0[channel] & MK_EXTID0(0xFF00FFFFUL)) | MK_EXTID0((vuint32)mask<<16);   /* lint !e572 */
# if (kCanNumberOfUsedCanTxIdTables > 1)
  canTxMask1[channel] = (canTxMask1[channel] & MK_EXTID1(0xFF00FFFFUL)) | MK_EXTID1((vuint32)mask<<16);   /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
  canTxMask2[channel] = (canTxMask2[channel] & MK_EXTID2(0xFF00FFFFUL)) | MK_EXTID2((vuint32)mask<<16);   /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
  canTxMask3[channel] = (canTxMask3[channel] & MK_EXTID3(0xFF00FFFFUL)) | MK_EXTID3((vuint32)mask<<16);   /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
  canTxMask4[channel] = (canTxMask4[channel] & MK_EXTID4(0xFF00FFFFUL)) | MK_EXTID4((vuint32)mask<<16);   /* lint !e572 */
# endif
}
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:               CanSetTxIdExtMidLo
* CALLED BY:
* PRECONDITIONS:      CanInitPower should already been called.
* PARAMETER:          new source address for the 29-bit CAN-ID
* RETURN VALUE:       -
* DESCRIPTION:        Sets the source address in the lower 8 bit of the
*                     29-bit CAN identifier.
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtMidLo( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif

  canTxMask0[channel] = (canTxMask0[channel] & MK_EXTID0(0xFFFF00FFUL)) | MK_EXTID0((vuint32)mask<<8);    /* lint !e572 */
# if (kCanNumberOfUsedCanTxIdTables > 1)
  canTxMask1[channel] = (canTxMask1[channel] & MK_EXTID1(0xFFFF00FFUL)) | MK_EXTID1((vuint32)mask<<8);    /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
  canTxMask2[channel] = (canTxMask2[channel] & MK_EXTID2(0xFFFF00FFUL)) | MK_EXTID2((vuint32)mask<<8);    /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
  canTxMask3[channel] = (canTxMask3[channel] & MK_EXTID3(0xFFFF00FFUL)) | MK_EXTID3((vuint32)mask<<8);    /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
  canTxMask4[channel] = (canTxMask4[channel] & MK_EXTID4(0xFFFF00FFUL)) | MK_EXTID4((vuint32)mask<<8);    /* lint !e572 */
# endif
}
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:               CanSetTxIdExtLo
* CALLED BY:
* PRECONDITIONS:      CanInitPower should already been called.
* PARAMETER:          new source address for the 29-bit CAN-ID
* RETURN VALUE:       -
* DESCRIPTION:        Sets the source address in the lower 8 bit of the
*                     29-bit CAN identifier.
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtLo( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif

  canTxMask0[channel] = (canTxMask0[channel] & MK_EXTID0(0xFFFFFF00UL)) | MK_EXTID0((vuint32)mask);     /* lint !e572 */
# if (kCanNumberOfUsedCanTxIdTables > 1)
  canTxMask1[channel] = (canTxMask1[channel] & MK_EXTID1(0xFFFFFF00UL)) | MK_EXTID1((vuint32)mask);     /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
  canTxMask2[channel] = (canTxMask2[channel] & MK_EXTID2(0xFFFFFF00UL)) | MK_EXTID2((vuint32)mask);     /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
  canTxMask3[channel] = (canTxMask3[channel] & MK_EXTID3(0xFFFFFF00UL)) | MK_EXTID3((vuint32)mask);     /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
  canTxMask4[channel] = (canTxMask4[channel] & MK_EXTID4(0xFFFFFF00UL)) | MK_EXTID4((vuint32)mask);    /* lint !e572 */
# endif
}
/* CODE CATEGORY 4 END */
#endif

#if defined( C_ENABLE_TX_OBSERVE )
# if defined( C_KOMMENTAR_VECTOR_RI14 )
/* ##RI-1.1: Object parameters for Tx-Observe functions */
# endif
/* **********************************************************************
* NAME:               CanTxGetActHandle
* CALLED BY:
* PRECONDITIONS:
* PARAMETER:          logical hardware object handle
* RETURN VALUE:       handle of the message in the assigned mailbox
* DESCRIPTION:        get transmit handle of the message, which is currently
*                     in the mailbox txHwObject.
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 CanTransmitHandle C_API_2 CanTxGetActHandle( CanObjectHandle logicalTxHdl ) C_API_3
{
  assertUser(logicalTxHdl < kCanNumberOfTxMailboxes, kCanAllChannels, kErrorTxHwHdlTooLarge);

  return (canHandleCurTxObj[logicalTxHdl]);  /* PRQA S 3689 */ /* MD_Can_3689 */     /* lint !e661 */
}
/* CODE CATEGORY 3 END */
#endif

#if defined( C_ENABLE_VARIABLE_RX_DATALEN )
/* **********************************************************************
* NAME:               CanSetVariableRxDatalen
* CALLED BY:
* PRECONDITIONS:
* PARAMETER:          rxHandle: Handle of receive Message for which the datalen has
*                               to be changed
*                     dataLen:  new number of bytes, which have to be copied to the
*                               message buffer.
* RETURN VALUE:       -
* DESCRIPTION:        change the dataLen of a receive message to copy a
*                     smaller number of bytes than defined in the database.
*                     the dataLen can only be decreased. If the parameter
*                     dataLen is bigger than the statically defined value
*                     the statically defined value will be set.
*********************************************************************** */
/* CODE CATEGORY 1 START */
static void CanSetVariableRxDatalen (CanReceiveHandle rxHandle, vuint8 dataLen)
{
  assertInternal(rxHandle < kCanNumberOfRxObjects, kCanAllChannels, kErrorRxHandleWrong);  /* legal rxHandle ? */
  /* assertion for dataLen not necessary due to runtime check */

  if (dataLen < CanGetDerivedRxDataLen(rxHandle))
  {
    canVariableRxDataLen[rxHandle]=dataLen;
  }
  else
  {
    canVariableRxDataLen[rxHandle] = CanGetDerivedRxDataLen(rxHandle);
  }
}
/* CODE CATEGORY 1 END */
#endif

#if defined( C_ENABLE_COND_RECEIVE_FCT )
/* **********************************************************************
* NAME:               CanSetMsgReceivedCondition
* CALLED BY:          Application
* PRECONDITIONS:
* PARAMETER:          -.
* RETURN VALUE:       -
* DESCRIPTION:        The service function CanSetMsgReceivedCondition()
*                     enables the calling of ApplCanMsgCondReceived()
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 void C_API_2 CanSetMsgReceivedCondition( CAN_CHANNEL_CANTYPE_ONLY )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((channel < kCanNumberOfChannels), kCanAllChannels, kErrorChannelHdlTooLarge);
# endif

  canMsgCondRecState[channel] = kCanTrue;
}
/* CODE CATEGORY 3 END */

/* **********************************************************************
* NAME:               CanResetMsgReceivedCondition
* CALLED BY:          Application
* PRECONDITIONS:
* PARAMETER:          -
* RETURN VALUE:       -
* DESCRIPTION:        The service function CanResetMsgReceivedCondition()
*                     disables the calling of ApplCanMsgCondReceived()
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 void C_API_2 CanResetMsgReceivedCondition( CAN_CHANNEL_CANTYPE_ONLY )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((channel < kCanNumberOfChannels), kCanAllChannels, kErrorChannelHdlTooLarge);
# endif

  canMsgCondRecState[channel] = kCanFalse;
}
/* CODE CATEGORY 3 END */

/* **********************************************************************
* NAME:               CanGetMsgReceivedCondition
* CALLED BY:          Application
* PRECONDITIONS:
* PARAMETER:          -
* RETURN VALUE:       status of Conditional receive function:
*                     kCanTrue : Condition is set -> ApplCanMsgCondReceived
*                                will be called
*                     kCanFalse: Condition is not set -> ApplCanMsgCondReceived
*                                will not be called
* DESCRIPTION:        The service function CanGetMsgReceivedCondition()
*                     returns the status of the condition for calling
*                     ApplCanMsgCondReceived()
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 vuint8 C_API_2 CanGetMsgReceivedCondition( CAN_CHANNEL_CANTYPE_ONLY )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((channel < kCanNumberOfChannels), kCanAllChannels, kErrorChannelHdlTooLarge);
# endif

  return( canMsgCondRecState[channel] );
}
/* CODE CATEGORY 3 END */
#endif

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
/* **********************************************************************
* NAME:           ApplCanChannelDummy
* PARAMETER:      channel
*                 current receive channel
* RETURN VALUE:   ---
* DESCRIPTION:    dummy-function for unused Callback-functions
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 void C_API_2 ApplCanChannelDummy( CanChannelHandle channel )
{
  CAN_DUMMY_STATEMENT(channel); /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 3 END */
#endif /* C_MULTIPLE_RECEIVE_CHANNEL */

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
/* **********************************************************************
* NAME:           ApplCanRxStructPtrDummy
* PARAMETER:      rxStruct
*                 pointer of CanRxInfoStruct
* RETURN VALUE:   kCanCopyData
* DESCRIPTION:    dummy-function for unused Callback-functions
*********************************************************************** */
/* CODE CATEGORY 1 START */
C_API_1 vuint8 C_API_2 ApplCanRxStructPtrDummy( CanRxInfoStructPtr rxStruct )
{
  CAN_DUMMY_STATEMENT(rxStruct); /* PRQA S 3199 */ /* MD_Can_3199_dummy */
  return kCanCopyData;
}
/* CODE CATEGORY 1 END */

/* **********************************************************************
* NAME:           ApplCanTxHandleDummy
* PARAMETER:      txHandle
*                 transmit handle
* RETURN VALUE:   ---
* DESCRIPTION:    dummy-function for unused Callback-functions
*********************************************************************** */
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 ApplCanTxHandleDummy( CanTransmitHandle txHandle )
{
  CAN_DUMMY_STATEMENT(txHandle); /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 1 END */
#endif /* C_MULTIPLE_RECEIVE_CHANNEL || C_HL_ENABLE_DUMMY_FCT_CALL */

#if defined( C_ENABLE_RX_QUEUE )
/* **********************************************************************
* NAME:               CanHL_ReceivedRxHandleQueue
* CALLED BY:          CanBasicCanMsgReceived, CanFullCanMsgReceived
* Preconditions:      none
* PARAMETER:          none
* RETURN VALUE:       none
* DESCRIPTION:        Writes receive data into queue or starts further
*                     processing for this message
*********************************************************************** */
/* CODE CATEGORY 1 START */
static vuint8 CanHL_ReceivedRxHandleQueue(CAN_CHANNEL_CANTYPE_ONLY)
{
  CanDeclareGlobalInterruptOldStatus
  tCanRxInfoStruct    *pCanRxInfoStruct;

  tCanRxQueueCopyInfoStruct rxQueueCopyInfo;

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(channel < kCanNumberOfChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);
# endif

  /* Rx Queue is supported with C_HL_ENABLE_RX_INFO_STRUCT_PTR only! */
  pCanRxInfoStruct =  &canRxInfoStruct[channel]; /* PRQA S 3689 */ /* MD_Can_3689 */

  /* if C_ENABLE_APPLCANPRERXQUEUE is not set, a macro ApplCanPreRxQueue has to be provided by the tool */
  /* in case of ranges, ApplCanPreRxQueue has to return kCanCopyData! */
# if defined( C_ENABLE_APPLCANPRERXQUEUE )
  if(ApplCanPreRxQueue(CAN_HL_P_RX_INFO_STRUCT(channel)) == kCanCopyData)
# endif
  {
    /* Disable the interrupts because nested interrupts can take place -
      CAN interrupts of all channels have to be disabled here */
    CanNestedGlobalInterruptDisable();
    if(canRxQueue.canRxQueueCount < kCanRxQueueSize)   /* Queue full ? */
    {
      if (canRxQueue.canRxQueueWriteIndex == (kCanRxQueueSize - 1) )
      {
        canRxQueue.canRxQueueWriteIndex = 0;
      }
      else
      {
        canRxQueue.canRxQueueWriteIndex++;
      }
      canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueWriteIndex].Channel = channel;
      canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueWriteIndex].Handle  = pCanRxInfoStruct->Handle;

      rxQueueCopyInfo.dest = (CanMsgTransmitStructPtr)&canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueWriteIndex].CanChipMsgObj;
      rxQueueCopyInfo.src = pCanRxInfoStruct;

      CanLL_RxQueueCopyMsgObj(CAN_CHANNEL_CANPARA_FIRST &rxQueueCopyInfo);

      canRxQueue.canRxQueueCount++;
    }
# if defined( C_ENABLE_RXQUEUE_OVERRUN_NOTIFY )
    else
    {
      ApplCanRxQueueOverrun();
    }
# endif
    CanNestedGlobalInterruptRestore();
  }
# if defined( C_ENABLE_APPLCANPRERXQUEUE )
  else
  {
    /* Call the application call-back functions and set flags */
#  if defined( C_ENABLE_RX_QUEUE_RANGE )
    if (pCanRxInfoStruct->Handle < kCanNumberOfRxObjects )
#  endif
    {
      return CanHL_ReceivedRxHandle(CAN_CHANNEL_CANPARA_FIRST pCanRxInfoStruct);
    }
  }
# endif
  return kCanHlFinishRx;
}
/* CODE CATEGORY 1 END */

/* **********************************************************************
* NAME:               CanHandleRxMsg
* CALLED BY:          Application
* Preconditions:      none
* PARAMETER:          none
* RETURN VALUE:       none
* DESCRIPTION:        Calls PreCopy and/or Indication, if existent and
*                     set the indication flag
*********************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanHandleRxMsg(void)
{
  CanDeclareGlobalInterruptOldStatus
  CAN_CHANNEL_CANTYPE_LOCAL
  tCanRxInfoStruct        localCanRxInfoStruct; /* PRQA S 0781 */ /* MD_Can_0781 */

  tCanRxQueueRxInfoStruct rxQueueRxInfo;

  while ( canRxQueue.canRxQueueCount != (vuintx)0 )
  {

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    channel = canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueReadIndex].Channel;
# endif

    CAN_CAN_INTERRUPT_DISABLE( channel );

    /* Call the application call-back functions and set flags */
    localCanRxInfoStruct.Handle      = canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueReadIndex].Handle;
    localCanRxInfoStruct.pChipData   = (CanChipDataPtr)&(canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueReadIndex].CanChipMsgObj.DataFld[0]);
    canRDSRxPtr[channel] = localCanRxInfoStruct.pChipData;
    localCanRxInfoStruct.pChipMsgObj = (CanChipMsgPtr) &(canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueReadIndex].CanChipMsgObj); /* PRQA S 0310 */ /* MD_Can_0310 */
    localCanRxInfoStruct.Channel     = channel;

    rxQueueRxInfo.localCanRxInfoStruct = localCanRxInfoStruct;
    CanLL_RxQueueSetRxInfoStructExtension(CAN_CHANNEL_CANPARA_FIRST &rxQueueRxInfo);
    localCanRxInfoStruct = rxQueueRxInfo.localCanRxInfoStruct;

# if defined( C_ENABLE_RX_QUEUE_RANGE )
    switch (localCanRxInfoStruct.Handle)
    {
#  if defined( C_ENABLE_RANGE_0 )
      case kCanRxHandleRange0: (void)APPLCANRANGE0PRECOPY( &localCanRxInfoStruct ); break;
#  endif
#  if defined( C_ENABLE_RANGE_1 )
      case kCanRxHandleRange1: (void)APPLCANRANGE1PRECOPY( &localCanRxInfoStruct ); break;
#  endif
#  if defined( C_ENABLE_RANGE_2 )
      case kCanRxHandleRange2: (void)APPLCANRANGE2PRECOPY( &localCanRxInfoStruct ); break;
#  endif
#  if defined( C_ENABLE_RANGE_3 )
      case kCanRxHandleRange3: (void)APPLCANRANGE3PRECOPY( &localCanRxInfoStruct ); break;
#  endif
      default:
#  if defined( C_ENABLE_INDICATION_FLAG ) || \
      defined( C_ENABLE_INDICATION_FCT )
             if( CanHL_ReceivedRxHandle( CAN_CHANNEL_CANPARA_FIRST &localCanRxInfoStruct ) == kCanHlContinueRx )
             {
               CanHL_IndRxHandle(localCanRxInfoStruct.Handle);
             }
#  else
             (void) CanHL_ReceivedRxHandle( CAN_CHANNEL_CANPARA_FIRST &localCanRxInfoStruct );
#  endif
             break;
   }
# else
#  if defined( C_ENABLE_INDICATION_FLAG ) || \
      defined( C_ENABLE_INDICATION_FCT )
    if( CanHL_ReceivedRxHandle( CAN_CHANNEL_CANPARA_FIRST &localCanRxInfoStruct ) == kCanHlContinueRx )
    {
      CanHL_IndRxHandle(localCanRxInfoStruct.Handle);
    }
#  else
    (void) CanHL_ReceivedRxHandle( CAN_CHANNEL_CANPARA_FIRST &localCanRxInfoStruct );
#  endif
# endif

    CAN_CAN_INTERRUPT_RESTORE( channel );

    CanNestedGlobalInterruptDisable();
    if (canRxQueue.canRxQueueReadIndex == (kCanRxQueueSize - 1) )
    {
      canRxQueue.canRxQueueReadIndex = 0;
    }
    else
    {
      canRxQueue.canRxQueueReadIndex++;
    }
    canRxQueue.canRxQueueCount--;
    CanNestedGlobalInterruptRestore();
  }
  return;
}
/* end of CanHandleRxMsg() */
/* CODE CATEGORY 2 END */

/* **********************************************************************
* NAME:               CanDeleteRxQueue
* CALLED BY:          Application, CAN driver
* Preconditions:      none
* PARAMETER:          none
* RETURN VALUE:       none
* DESCRIPTION:        delete receive queue
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanDeleteRxQueue(void)
{
  CanDeclareGlobalInterruptOldStatus

  CanNestedGlobalInterruptDisable();
  canRxQueue.canRxQueueWriteIndex  = (vuintx)0xFFFFFFFF; /* PRQA S 1281 */ /* MD_Can_1281 */
  canRxQueue.canRxQueueReadIndex   = 0;
  canRxQueue.canRxQueueCount       = 0;
  CanNestedGlobalInterruptRestore();
} /* end of CanDeleteRxQueue() */
/* CODE CATEGORY 4 END */

#endif /* C_ENABLE_RX_QUEUE */

# if defined( C_ENABLE_MEMCOPY_SUPPORT )
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanCopyToCan
****************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanCopyToCan(CanChipDataPtr dst, V_DEF_P2VAR_PARA(V_NONE, void, AUTOMATIC, APPL_VAR) src, vuint8 len) C_API_3 /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8 canllidx;

  /* ----- Implementation ----------------------------------------------- */
  for(canllidx=0; canllidx<len; canllidx++)
  {
    dst[canllidx] = ((V_DEF_P2VAR_PARA(V_NONE, vuint8, AUTOMATIC, APPL_VAR))src)[canllidx];
  }
}
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanCopyFromCan
****************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanCopyFromCan(V_DEF_P2VAR_PARA(V_NONE, void, AUTOMATIC, APPL_VAR) dst, CanChipDataPtr src, vuint8 len) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8 canllidx;
  /* ----- Implementation ----------------------------------------------- */
  for(canllidx=0; canllidx<len; canllidx++)
  {
    ((V_DEF_P2VAR_PARA(V_NONE, vuint8, AUTOMATIC, APPL_VAR))dst)[canllidx] = src[canllidx];
  }
}
/* CODE CATEGORY 1 END */
# endif
# if defined( C_ENABLE_TX_FULLCAN_DELAYED_START )
/************************************************************************
| NAME:               CanTxFullCanDelayedStart
| CALLED BY:          Application
| Preconditions:      none
| PARAMETER:          none
| RETURN VALUE:       none
| Description:        This function requests the transmission for hardware
|                     objects which are pending to be send.
*************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanTxFullCanDelayedStart(CAN_CHANNEL_CANTYPE_ONLY)
{
  CanDeclareGlobalInterruptOldStatus
  vuint8 txObjHandle;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(hwChHandle);
  /* Tx is only possible on the first hwChannel of the common CAN channel */
  CanChannelHandle hwChHandle = CAN_HL_HW_CHANNEL_STARTINDEX(channel);

  /* Disable global interrupts */
  CanNestedGlobalInterruptDisable();

  /* Tx FullCANs are sorted by their priority so the ID with the highest priority has the lowest txObjHandle */
  for(txObjHandle = Can_Mailbox[CAN_HL_MB_TX_STARTINDEX(hwChHandle)].HwObjHandle; txObjHandle <= Can_Mailbox[CAN_HL_MB_TX_STOPINDEX(hwChHandle) -1].HwObjHandle; txObjHandle++)
  {
    if (CanGetMailboxDelayed(channel,txObjHandle))
    {
      LOCAL_MAILBOX_ACCESS(hwChHandle, txObjHandle, control) |= kTxCodeTransmit; /* start tx of the message */
#  if defined (C_ENABLE_WORKAROUND_ERR005829)
      /* set the reserved mailbox twice to CodeInactive. This workaround is recommended by freescale. */
      LOCAL_MAILBOX_ACCESS(hwChHandle, INDEX_RSVD_MB(hwChHandle), control) |= kTxCodeInactive;
      LOCAL_MAILBOX_ACCESS(hwChHandle, INDEX_RSVD_MB(hwChHandle), control) |= kTxCodeInactive;
#  endif
    }
  }
  /* Clear the internal Tx fullcan pendings */
  canLL_canDelayedFullCANTxRequest[channel][0] = 0;
  canLL_canDelayedFullCANTxRequest[channel][1] = 0;
  /* Restore global interrupts */
  CanNestedGlobalInterruptRestore();
}
/* CODE CATEGORY 1 END */
# endif /* C_ENABLE_TX_FULLCAN_DELAYED_START */
# if defined ( C_ENABLE_DRIVER_STATUS )
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanGetDriverStatus
****************************************************************************/
V_DEF_FUNC_API(V_NONE, vuint8, CODE) CanGetDriverStatus(CAN_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Development Error Checks ------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
#   error "Not supported"
}
/* CODE CATEGORY 4 END */
# endif /* C_ENABLE_DRIVER_STATUS         */

#if defined( C_SINGLE_RECEIVE_CHANNEL )
# define CanPhysToLogChannel_0
# define CanPhysToLogChannelIndex_0
# define CanPhysToLogChannel_1
# define CanPhysToLogChannelIndex_1
# define CanPhysToLogChannel_2
# define CanPhysToLogChannelIndex_2
# define CanPhysToLogChannel_3
# define CanPhysToLogChannelIndex_3
#else
# define CanPhysToLogChannel_0       kCanPhysToLogChannelIndex_0
# define CanPhysToLogChannelIndex_0  kCanPhysToLogChannelIndex_0,
# define CanPhysToLogChannel_1       kCanPhysToLogChannelIndex_1
# define CanPhysToLogChannelIndex_1  kCanPhysToLogChannelIndex_1,
# define CanPhysToLogChannel_2       kCanPhysToLogChannelIndex_2
# define CanPhysToLogChannelIndex_2  kCanPhysToLogChannelIndex_2,
# define CanPhysToLogChannel_3       kCanPhysToLogChannelIndex_3
# define CanPhysToLogChannelIndex_3  kCanPhysToLogChannelIndex_3,
#endif

/* ISR functions */

#if defined( V_CPU_IMX ) || defined( V_CPU_VYBRID )
#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
    defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
    defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
# if defined( kCanPhysToLogChannelIndex_0 )
/****************************************************************************
| NAME:             CanIsr_0()
****************************************************************************/
/*!
 * \internal
 *  - #10 call interrupt handler
 * \endinternal
 */
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsr_0 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
void CanIsr_0( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined( CAN_USE_PHYSTOLOG_MAPPING )
  CanInterrupt(Can_GetPhysToLogChannel(0)); /* call Interrupthandling with identity dependend logical channel */
#  else
  CanInterrupt(CanPhysToLogChannel_0); /* call Interrupthandling with logical channel */
#  endif
} /* END OF CanIsr */
/* CODE CATEGORY 1 END */
# endif /* (kCanPhysToLogChannelIndex_0) */
# if defined( kCanPhysToLogChannelIndex_1 )
/****************************************************************************
| NAME:             CanIsr_1()
****************************************************************************/
/*!
 * \internal
 *  - #10 call interrupt handler
 * \endinternal
 */
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsr_1 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
void CanIsr_1( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined( CAN_USE_PHYSTOLOG_MAPPING )
  CanInterrupt(Can_GetPhysToLogChannel(1)); /* call Interrupthandling with identity dependend logical channel */
#  else
  CanInterrupt(CanPhysToLogChannel_1); /* call Interrupthandling with logical channel */
#  endif
} /* END OF CanIsr */
/* CODE CATEGORY 1 END */
# endif /* (kCanPhysToLogChannelIndex_1) */
# if defined( kCanPhysToLogChannelIndex_2 )
/****************************************************************************
| NAME:             CanIsr_2()
****************************************************************************/
/*!
 * \internal
 *  - #10 call interrupt handler
 * \endinternal
 */
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsr_2 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
void CanIsr_2( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined( CAN_USE_PHYSTOLOG_MAPPING )
  CanInterrupt(Can_GetPhysToLogChannel(2)); /* call Interrupthandling with identity dependend logical channel */
#  else
  CanInterrupt(CanPhysToLogChannel_2); /* call Interrupthandling with logical channel */
#  endif
} /* END OF CanIsr */
/* CODE CATEGORY 1 END */
# endif /* (kCanPhysToLogChannelIndex_2) */
# if defined( kCanPhysToLogChannelIndex_3 )
/****************************************************************************
| NAME:             CanIsr_3()
****************************************************************************/
/*!
 * \internal
 *  - #10 call interrupt handler
 * \endinternal
 */
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_3Cat)
#    if (osdIsrCanIsr_3Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsr_3 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_3Cat)
#    if (osdIsrCanIsr_3Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
void CanIsr_3( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined( CAN_USE_PHYSTOLOG_MAPPING )
  CanInterrupt(Can_GetPhysToLogChannel(3)); /* call Interrupthandling with identity dependend logical channel */
#  else
  CanInterrupt(CanPhysToLogChannel_3); /* call Interrupthandling with logical channel */
#  endif
} /* END OF CanIsr */
/* CODE CATEGORY 1 END */
# endif /* (kCanPhysToLogChannelIndex_3) */
#endif /* C_ENABLE_CAN_RXTX_INTERRUPT || C_ENABLE_CAN_BUSOFF_INTERRUPT || C_ENABLE_CAN_WAKEUP_INTERRUPT */
#endif /* V_CPU_IMX */

#if defined( V_CPU_S32 )
#if defined( kCanPhysToLogChannelIndex_0 )
# if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/****************************************************************************
| NAME:             CanBusOffIsr_0()
****************************************************************************/
/*!
 * \internal
 *  - #10 call interrupt handler
 * \endinternal
 */
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanBusOffIsr_0 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
void CanBusOffIsr_0( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined( CAN_USE_PHYSTOLOG_MAPPING )
  CanBusOffInterrupt(Can_GetPhysToLogChannel(0)); /* call Interrupthandling with identity dependend logical channel */
#  else
  CanBusOffInterrupt(CanPhysToLogChannel_0); /* call Interrupthandling with logical channel */
#  endif
} /* END OF CanBusOffIsr */
/* CODE CATEGORY 1 END */
# endif /* C_ENABLE_CAN_BUSOFF_INTERRUPT */

# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/****************************************************************************
| NAME:             CanMailboxIsr_0()
****************************************************************************/
/*!
 * \internal
 *  - #10 call interrupt handler
 * \endinternal
 */
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMailboxIsr_0 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
void CanMailboxIsr_0( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined( CAN_USE_PHYSTOLOG_MAPPING )
  CanMailboxInterrupt(Can_GetPhysToLogChannel(0)); /* call Interrupthandling with identity dependend logical channel */
#  else
  CanMailboxInterrupt(CanPhysToLogChannel_0); /* call Interrupthandling with logical channel */
#  endif
} /* END OF CanMailboxIsr */
/* CODE CATEGORY 1 END */
# endif /* C_ENABLE_CAN_RXTX_INTERRUPT */
#endif /* (kCanPhysToLogChannelIndex_0) */
#if defined( kCanPhysToLogChannelIndex_1 )
# if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/****************************************************************************
| NAME:             CanBusOffIsr_1()
****************************************************************************/
/*!
 * \internal
 *  - #10 call interrupt handler
 * \endinternal
 */
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanBusOffIsr_1 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
void CanBusOffIsr_1( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined( CAN_USE_PHYSTOLOG_MAPPING )
  CanBusOffInterrupt(Can_GetPhysToLogChannel(1)); /* call Interrupthandling with identity dependend logical channel */
#  else
  CanBusOffInterrupt(CanPhysToLogChannel_1); /* call Interrupthandling with logical channel */
#  endif
} /* END OF CanBusOffIsr */
/* CODE CATEGORY 1 END */
# endif /* C_ENABLE_CAN_BUSOFF_INTERRUPT */

# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/****************************************************************************
| NAME:             CanMailboxIsr_1()
****************************************************************************/
/*!
 * \internal
 *  - #10 call interrupt handler
 * \endinternal
 */
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMailboxIsr_1 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
void CanMailboxIsr_1( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined( CAN_USE_PHYSTOLOG_MAPPING )
  CanMailboxInterrupt(Can_GetPhysToLogChannel(1)); /* call Interrupthandling with identity dependend logical channel */
#  else
  CanMailboxInterrupt(CanPhysToLogChannel_1); /* call Interrupthandling with logical channel */
#  endif
} /* END OF CanMailboxIsr */
/* CODE CATEGORY 1 END */
# endif /* C_ENABLE_CAN_RXTX_INTERRUPT */
#endif /* (kCanPhysToLogChannelIndex_1) */
#if defined( kCanPhysToLogChannelIndex_2 )
# if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/****************************************************************************
| NAME:             CanBusOffIsr_2()
****************************************************************************/
/*!
 * \internal
 *  - #10 call interrupt handler
 * \endinternal
 */
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanBusOffIsr_2 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
void CanBusOffIsr_2( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined( CAN_USE_PHYSTOLOG_MAPPING )
  CanBusOffInterrupt(Can_GetPhysToLogChannel(2)); /* call Interrupthandling with identity dependend logical channel */
#  else
  CanBusOffInterrupt(CanPhysToLogChannel_2); /* call Interrupthandling with logical channel */
#  endif
} /* END OF CanBusOffIsr */
/* CODE CATEGORY 1 END */
# endif /* C_ENABLE_CAN_BUSOFF_INTERRUPT */

# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/****************************************************************************
| NAME:             CanMailboxIsr_2()
****************************************************************************/
/*!
 * \internal
 *  - #10 call interrupt handler
 * \endinternal
 */
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMailboxIsr_2 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
void CanMailboxIsr_2( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined( CAN_USE_PHYSTOLOG_MAPPING )
  CanMailboxInterrupt(Can_GetPhysToLogChannel(2)); /* call Interrupthandling with identity dependend logical channel */
#  else
  CanMailboxInterrupt(CanPhysToLogChannel_2); /* call Interrupthandling with logical channel */
#  endif
} /* END OF CanMailboxIsr */
/* CODE CATEGORY 1 END */
# endif /* C_ENABLE_CAN_RXTX_INTERRUPT */
#endif /* (kCanPhysToLogChannelIndex_2) */
#if defined( kCanPhysToLogChannelIndex_3 )
# if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/****************************************************************************
| NAME:             CanBusOffIsr_3()
****************************************************************************/
/*!
 * \internal
 *  - #10 call interrupt handler
 * \endinternal
 */
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_3Cat)
#    if (osdIsrCanIsr_3Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanBusOffIsr_3 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_3Cat)
#    if (osdIsrCanIsr_3Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
void CanBusOffIsr_3( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined( CAN_USE_PHYSTOLOG_MAPPING )
  CanBusOffInterrupt(Can_GetPhysToLogChannel(3)); /* call Interrupthandling with identity dependend logical channel */
#  else
  CanBusOffInterrupt(CanPhysToLogChannel_3); /* call Interrupthandling with logical channel */
#  endif
} /* END OF CanBusOffIsr */
/* CODE CATEGORY 1 END */
# endif /* C_ENABLE_CAN_BUSOFF_INTERRUPT */

# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/****************************************************************************
| NAME:             CanMailboxIsr_3()
****************************************************************************/
/*!
 * \internal
 *  - #10 call interrupt handler
 * \endinternal
 */
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_3Cat)
#    if (osdIsrCanIsr_3Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMailboxIsr_3 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_3Cat)
#    if (osdIsrCanIsr_3Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
void CanMailboxIsr_3( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined( CAN_USE_PHYSTOLOG_MAPPING )
  CanMailboxInterrupt(Can_GetPhysToLogChannel(3)); /* call Interrupthandling with identity dependend logical channel */
#  else
  CanMailboxInterrupt(CanPhysToLogChannel_3); /* call Interrupthandling with logical channel */
#  endif
} /* END OF CanMailboxIsr */
/* CODE CATEGORY 1 END */
# endif /* C_ENABLE_CAN_RXTX_INTERRUPT */
#endif /* (kCanPhysToLogChannelIndex_3) */
#endif

#if defined( V_CPU_IMX ) || defined( V_CPU_VYBRID )
#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
    defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
    defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* **************************************************************************
| NAME:             CanInterrupt<Name>
| CALLED BY:        CanIsr<Name>_<physicalChannelIndex>()
| PRECONDITIONS:
| INPUT PARAMETERS: canHwChannel
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service functions according to the CAN controller
|                   interrupt structure
|                   - check for the interrupt reason ( interrupt source )
|                   - work appropriate interrupt:
|                     + status/error interrupt (BUSOFF, wakeup, error warning)
|                     + basic can receive
|                     + full can receive
|                     + can transmit
|
|                   If an RX-Interrupt occurs while the CAN controller is in Sleep mode,
|                   a wakeup has to be generated.
|
|                   If an TX-Interrupt occurs while the CAN controller is in Sleep mode,
|                   an assertion has to be called and the interrupt has to be ignored.
|
|                   The name of BrsTimeStrt...() and BrsTimeStop...() can be adapted to
|                   really used name of the interrupt functions.
|
************************************************************************** */
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
  CanObjectHandle  index;
  CanObjectHandle mailboxHandle;
  vuint32  iFlags;
  vuint32  iMask1;
# if defined ( C_ENABLE_MB32TO63 )
  vuint32  iMask2;
# endif
# if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
#  if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  vuint8 fifoLoopCnt = 0;
#  endif
# endif
#endif

#if defined( C_ENABLE_CAN_RXTX_INTERRUPT ) || defined( C_ENABLE_CAN_WAKEUP_INTERRUPT ) || defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
#endif

#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
  iMask1 = pFlexCANLocal->imask1
  # if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
# else
  & kCanRxFifoIntUnmask
# endif
  ;
# if defined ( C_ENABLE_MB32TO63 )
  iMask2 = pFlexCANLocal->imask2;
# endif
#endif

#if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
  if((pFlexCANLocal->estat & kFlexCAN_WAKE_INT) != 0)
  {
    CanLL_WakeUpHandling(CAN_HW_CHANNEL_CANPARA_ONLY);
  }
#endif

#if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
  {
    if((pFlexCANLocal->estat & kFlexCAN_BOFF_INT) != 0)
    {
      CanHL_ErrorHandling( CAN_HW_CHANNEL_CANPARA_ONLY );
    }
  }
#endif

#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )

# if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
#  if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
#   if defined(C_ENABLE_INDIVIDUAL_POLLING)
    /* additional check is necessary to ensure only objects configured for interrupt are processed here */
  if (Can_GetCanHwObjIndivPolling(canHwChannel, 0) == 0)
#   endif
  {
    while(((pFlexCANLocal->iflag1 & kRxFIFO_NEWMSG) != 0) && (fifoLoopCnt < C_FLEXCAN_RXFIFO_MAXLOOP))
    {
      fifoLoopCnt++;
      CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST Can_HwObjToMailboxIndirection[CAN_HL_MB_INDIRECTION_STARTINDEX(canHwChannel) + 0], 0);
    }
  }
#  endif
# endif  /* C_ENABLE_RX_BASICCAN_OBJECTS */

  iFlags = pFlexCANLocal->iflag1 & iMask1;
  index = 0;
  while(iFlags != 0)
  {
    while((iFlags & (vuint32)0xFF) == 0)
    {
      iFlags >>= 8;
      index += (CanObjectHandle)8;
    }
    if((iFlags & (vuint32)0x0F) == 0)
    {
      iFlags >>= 4;
      index += (CanObjectHandle)4;
    }
    while((iFlags & (vuint32)0x01) == 0)
    {
      iFlags >>= 1;
      index++;
    }

    mailboxHandle = Can_HwObjToMailboxIndirection[CAN_HL_MB_INDIRECTION_STARTINDEX(canHwChannel) + index];
# if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
#  if !defined( C_ENABLE_RX_FULLCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
    if((mailboxHandle >= CAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel)) && (mailboxHandle < CAN_HL_MB_RX_FULL_STOPINDEX(canHwChannel)))
    {
      CanFullCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST mailboxHandle, index);
    }
#  endif
# endif

# if !defined( C_ENABLE_TX_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
    if((mailboxHandle >= CAN_HL_MB_TX_STARTINDEX(canHwChannel)) && (mailboxHandle < CAN_HL_MB_TX_STOPINDEX(canHwChannel)))
    {
      {
        CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST mailboxHandle, index);
      }
    }
# endif

    index++;
    iFlags = (pFlexCANLocal->iflag1 & iMask1) >> index;
  }

# if defined ( C_ENABLE_MB32TO63 )
  iFlags = pFlexCANLocal->iflag2 & iMask2;
# endif

  index = 32;
  while(iFlags != 0)
  {
    while((iFlags & (vuint32)0xFF) == 0)
    {
      iFlags >>= 8;
      index += (CanObjectHandle)8;
    }
    if((iFlags & (vuint32)0x0F) == 0)
    {
      iFlags >>= 4;
      index += (CanObjectHandle)4;
    }
    while((iFlags & (vuint32)0x01) == 0)
    {
      iFlags >>= 1;
      index++;
    }

    mailboxHandle = Can_HwObjToMailboxIndirection[CAN_HL_MB_INDIRECTION_STARTINDEX(canHwChannel) + index];
# if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
#  if !defined( C_ENABLE_RX_FULLCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
    if((mailboxHandle >= CAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel)) && (mailboxHandle < CAN_HL_MB_RX_FULL_STOPINDEX(canHwChannel)))
    {
      CanFullCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST mailboxHandle, index);
    }
#  endif
# endif

# if !defined( C_ENABLE_TX_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
    if((mailboxHandle >= CAN_HL_MB_TX_STARTINDEX(canHwChannel)) && (mailboxHandle < CAN_HL_MB_TX_STOPINDEX(canHwChannel)))
    {
      {
        CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST mailboxHandle, index);
      }
    }
# endif

    index++;
# if defined ( C_ENABLE_MB32TO63 )
    iFlags = (pFlexCANLocal->iflag2 & iMask2) >> (index-32);
# endif
  }
#endif /* C_ENABLE_CAN_RXTX_INTERRUPT */

} /* end of CanInterrupt */ /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */
/* CODE CATEGORY 1 END */
#endif
#endif /* V_CPU_IMX */ /* V_CPU_VYBRID */

#if defined( V_CPU_S32 )
#if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/****************************************************************************
| NAME:             CanBusOffInterrupt
****************************************************************************/
/*!
 * \internal
 *  - #10 Call internal indication function if BUSOFF occurred
 * \endinternal
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanBusOffInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY )        /* PRQA S 1330 */ /* MD_Can_1330 */
{

  /* #10 Call internal indication function if BUSOFF occurred */
  CanHL_ErrorHandling( CAN_HW_CHANNEL_CANPARA_ONLY );

}
/* CODE CATEGORY 1 END */
#endif
#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/****************************************************************************
| NAME:             CanMailboxInterrupt
****************************************************************************/
/*!
 * \internal
 *  - #10 Check if pending interrupt is caused due to a BasicCAN reception:
 *     if true call internal indication function.
 *  - #20 Call mailbox interrupt computation function for Mailboxes 0 to 31
 *  - #30 Call mailbox interrupt computation function for Mailboxes 32 to 63
 *  - #40 Call mailbox interrupt computation function for Mailboxes 64 to 95
 *  - #50 Call mailbox interrupt computation function for Mailboxes 96 to 127
 * \endinternal
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMailboxInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY )       /* PRQA S 1330 */ /* MD_Can_1330 */
{
#if !defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
# if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
#  if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  vuint8 fifoLoopCnt;
#  endif
# endif
#endif

 // tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

#if !defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
# if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
#  if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  /* #10 Check if pending interrupt is caused due to a BasicCAN reception:
       if true call internal indication function. */
  fifoLoopCnt = 0;

#   if defined(C_ENABLE_INDIVIDUAL_POLLING)
  /* additional check is necessary to ensure only objects configured for interrupt are processed here */
  if (Can_GetCanHwObjIndivPolling(canHwChannel, 0) == 0)
#   endif
  {
//HYT     while(((pFlexCANLocal->iflag1 & kRxFIFO_NEWMSG) != 0) && (fifoLoopCnt < C_FLEXCAN_RXFIFO_MAXLOOP))
//    {
//      fifoLoopCnt++;
//      CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST Can_HwObjToMailboxIndirection[CAN_HL_MB_INDIRECTION_STARTINDEX(canHwChannel) + 0], 0);
//    }
  }
#  endif
# endif
#endif

  /* #20 Call mailbox interrupt computation function for Mailboxes 0 to 31 */
 // CanLL_ComputeMailboxInterrupt(CAN_HW_CHANNEL_CANPARA_FIRST pFlexCANLocal->iflag1, pFlexCANLocal->imask1, 0);
#if defined ( C_ENABLE_MB32TO63 )
  /* #30 Call mailbox interrupt computation function for Mailboxes 32 to 63 */
  CanLL_ComputeMailboxInterrupt(CAN_HW_CHANNEL_CANPARA_FIRST pFlexCANLocal->iflag2, pFlexCANLocal->imask2, 32);
#endif
#if defined ( C_ENABLE_MB64TO95 )
# if defined ( C_ENABLE_ASYM_MAILBOXES )
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64)
# endif
  {
    /* #40 Call mailbox interrupt computation function for Mailboxes 64 to 95 */
    CanLL_ComputeMailboxInterrupt(CAN_HW_CHANNEL_CANPARA_FIRST pFlexCANLocal->iflag3, pFlexCANLocal->imask3, 64);
  }
#endif
#if defined ( C_ENABLE_MB96TO127 )
  /* #50 Call mailbox interrupt computation function for Mailboxes 96 to 127 */
  CanLL_ComputeMailboxInterrupt(CAN_HW_CHANNEL_CANPARA_FIRST pFlexCANLocal->iflag4, pFlexCANLocal->imask4, 96);
#endif

}
#endif
#endif /* V_CPU_MPC5700 */

/* PRQA S 3673 QAC_Can_3673 */ /* MD_Can_3673 */
/**********************************************************************************************************************
 *  CanLL_InitBegin
 *********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitBegin( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitInfoStructPtr localInfo )
{

#if defined (C_ENABLE_TX_FULLCAN_DELAYED_START)
/* clear delayed FullCAN TX pending requests */
  canLL_canDelayedFullCANTxRequest[channel][0] = 0;
  canLL_canDelayedFullCANTxRequest[channel][1] = 0;
#endif /* C_ENABLE_TX_FULLCAN_DELAYED_START */

  /* set can init state */
  canLL_canInitState[canHwChannel] = kCanLLStateInitStart;

  CAN_DUMMY_STATEMENT(localInfo); /* PRQA S 3199 */ /* MD_Can_3199_dummy */

  return(kCanOk);
}
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitBeginSetRegisters
 *********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitBeginSetRegisters( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitInfoStructPtr localInfo )
{
  vuint16 tmpCANmaxmb,tmpCANmcr;
  vuint32 tmpCANctrl2,tmpCANcontrol1;
//  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

  /* configure CAN[MCR].MAXMB register value */
  //tmpCANmaxmb = (vuint16)(Can_Mailbox[CAN_HL_MB_TX_STOPINDEX(canHwChannel) - 1].HwObjHandle)
#if defined( C_ENABLE_CANCEL_IN_HW )
  /* set AEN bit to enable Abort feature (Cancel in Hardware) */
  | kFlexCAN_AEN
#endif
  ;
#if defined( C_ENABLE_CAN_FD_USED )
  if (CAN_HL_IS_CH_CANFD(channel) == kCanTrue)
  {
    /* set FDEN bit to enable CAN FD */
    tmpCANmaxmb |= kFlexCAN_FDEN;
  }
#endif
  /* write configured value to register */
  //CAN_WRITE_PROTECTED_REG(pFlexCANLocal->canmaxmb, tmpCANmaxmb);

  /* configure CAN[MCR].MCR register value */
  //HYT   tmpCANmcr = CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kNotFlexCAN_MCR_CFG_BTIS;
  /* set IRMQ bit to allow individual buffer masking configuration */
  //HYT   tmpCANmcr |= kFlexCAN_IRMQ
#if defined( C_ENABLE_REJECT_SELF_RX_BY_HW )
  /* set SRXDIS bit to disable self-reception feature */
  //HYT   | kFlexCAN_SRX_DIS
#endif
#if defined( C_ENABLE_GLITCH_FILTER )
  /* set WAK_SRC bit to integrate low-pass filter to protect the FLEXCAN_RX input from spurious wake up */
  | kFlexCAN_WAK_SRC
#endif
#if !defined( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  /* set FEN bit to enable RX FIFO */
  //HYT   | kFlexCAN_FEN
#endif
#if defined( C_ENABLE_SLEEP_WAKEUP ) && defined( C_ENABLE_FLEXCAN_STOP_MODE )
  /* set SLFWAK bit to enable wakeup by bus */
  | kFlexCAN_SLF_WAK
#endif
  ;
#if (defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) && !defined (C_ENABLE_OSEK_CAN_INTCTRL))
# if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
  if(Can_GetCanInterruptCounter(channel) == 0)
  {
    tmpCANmcr |= kFlexCAN_WAK_MSK; /* set WAK_MSK for wakeup interrupts */
  }
# endif
#endif
  /* write configured value to register */
  //CAN_WRITE_PROTECTED_REG(pFlexCANLocal->canmcr, tmpCANmcr);

  /* configure CAN[CTRL1] register value */
#if defined( C_ENABLE_EXTENDED_BITTIMING )
  tmpCANcontrol1 = Can_GetControl1OfInitObject(localInfo->initObject) & kFlexCAN_CLK_SRC;
#else
  tmpCANcontrol1 = Can_GetControl1OfInitObject(localInfo->initObject);
#endif
#if defined( C_ENABLE_FLEXCAN_SAMPLING_MODE )
  tmpCANcontrol1 |= kFlexCAN_SMP;
#endif
#if defined( C_ENABLE_FLEXCAN_AUTO_RECOVERY )
  tmpCANcontrol1 &= (vuint32)(~kFlexCAN_BOFF_REC); /* PRQA S 0277 */ /* MD_Can_0277_negation */
#else
  //HYT   tmpCANcontrol1 |= kFlexCAN_BOFF_REC;
#endif
#if (defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) && !defined (C_ENABLE_OSEK_CAN_INTCTRL))
# if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
  if(Can_GetCanInterruptCounter(channel) == 0)
  {
	  //HYT     tmpCANcontrol1 |= kFlexCAN_BOFF_MSK;
  }
# endif
#endif
  //pFlexCANLocal->control1 = tmpCANcontrol1;

#if defined( C_ENABLE_EXTENDED_BITTIMING )
  /* configure CAN[CBT] register value (extended bit timing) */
  pFlexCANLocal->cbt = Can_GetCBTOfInitObject(localInfo->initObject);
#endif

#if defined( C_ENABLE_CAN_FD_USED )
  if (CAN_HL_IS_CH_CANFD(channel) == kCanTrue)
  {
    /* configure CAN[FDCTRL] register value (CAN FD control) */
    pCanFDRegister(canHwChannel)->fdctrl = Can_GetFDCTRLOfInitObjectFD(localInfo->initObject);

    /* configure CAN[FDCBT] register value (CAN FD bit timing) */
    pCanFDRegister(canHwChannel)->fdcbt = Can_GetFDCBTOfInitObjectFD(localInfo->initObject);
  }
#endif

#if !defined ( C_ENABLE_FLEXCAN2_DERIVATIVE )
  /* configure CAN[CTRL2] register value */
  //HYT   tmpCANctrl2 = kFlexCAN_MRP | kFlexCAN_RRS | kFlexCAN_EACEN
#  if !defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  //HYT   | RFFN_VALUE(canHwChannel)
#  endif
#if defined( V_CPU_VYBRID )
# if defined ( C_ENABLE_FLEXCAN_PARITY_CHECK_AVAILABLE )
  | kFlexCAN_ECRWRE
# endif
#endif
# if defined( C_ENABLE_TASD )
  | Can_GetTASDOfInitObject(localInfo->initObject)
# else
  //HYT   | kFlexCAN_TASD_DEFAULT
# endif
  ;
# if defined( C_ENABLE_CAN_FD_USED )
#  if defined (C_ENABLE_ISO_CANFD)
  if (CAN_HL_IS_CH_CANFD(channel) == kCanTrue)
  {
    tmpCANctrl2 |= kFlexCAN_STFCNTEN;
  }
#  endif
# endif
 // pFlexCANLocal->ctrl2 = tmpCANctrl2;
#endif

#if defined( V_CPU_VYBRID )
# if defined ( C_ENABLE_FLEXCAN_PARITY_CHECK_AVAILABLE )
  /* enable write on MECR register */
  pCanParityCheck(canHwChannel)->mecr &= (vuint32)(~kFlexCAN_ECRWRDIS);
  /* configuration of MECR register */
#  if !defined ( C_ENABLE_FLEXCAN_PARITY_CHECK )
  /* disable parity check functionality (not supported but enabled by default) */
  pCanParityCheck(canHwChannel)->mecr = (vuint32)0x00000300;
#  endif
  /* disable write on MECR register */
  pCanParityCheck(canHwChannel)->mecr |= kFlexCAN_ECRWRDIS;
# endif
#endif

#if defined( C_ENABLE_GLITCH_FILTER )
  /* configure glitch filter register value */
  pCanGlitchFilter(canHwChannel)->gfwR = GLITCH_FILTER_WIDTH(canHwChannel);
#endif

  return(kCanOk);
}
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitMailboxTx
 *********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxTx( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitInfoStructPtr localInfo )
{
#if !defined ( C_ENABLE_CAN_FD_FULL )
//  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
#endif

  {
//HYT LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control) = kTxCodeInactive; /* set transmit object inactive */
  }

  return(kCanOk);
}
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_InitMailboxRxFullCan
 *********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxRxFullCan( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitInfoStructPtr localInfo )
{
# if !defined ( C_ENABLE_CAN_FD_FULL )
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
# endif
  tCanRxMaskPtr pIndivRxMask = pCanRxMask(canHwChannel); /* pointer to FlexCAN individual receive mask registers */

  LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, msgID) = CAN_MSGID(localInfo->idRaw0);
  LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control) = kRxCodeEmpty | (vuint16)(localInfo->idType); /* set ID type and set mailbox ready for receive */

  /* initialize individual mask values for each FullCAN mailbox */
# if defined( C_ENABLE_EXTENDED_ID )
#  if defined( C_ENABLE_MIXED_ID )
  if((LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control) & (vuint16)kCanIdTypeExt) != 0)
  {
    pIndivRxMask->indivRxMask[localInfo->hwObjHandle] = kCanRxMaskExt;
  }
  else
  {
    pIndivRxMask->indivRxMask[localInfo->hwObjHandle] = kCanRxMaskStd;
  }
#  else
  pIndivRxMask->indivRxMask[localInfo->hwObjHandle] = kCanRxMaskExt;
#  endif
# else
  pIndivRxMask->indivRxMask[localInfo->hwObjHandle] = kCanRxMaskStd;
# endif

  return(kCanOk);
}
/* CODE CATEGORY 4 END */

#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_InitMailboxRxBasicCan
 *********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxRxBasicCan( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitInfoStructPtr localInfo )
{
# if !defined ( C_ENABLE_CAN_FD_FULL )
//  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
# endif
  vuint8 filterHandle;
# if !defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  vuint32 locMsgIDMask;
  tRXFIFOPtr pRxFIFO = pRXFIFO(canHwChannel);
# endif
  tCanRxMaskPtr pIndivRxMask = pCanRxMask(canHwChannel); /* pointer to FlexCAN individual receive mask registers */

# if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  filterHandle = (vuint8)(Can_GetInitBasicCanIndex(localInfo->initObject) + (localInfo->hwObjHandle - Can_Mailbox[CAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel)].HwObjHandle)); /* calculate BasicCan offset */
  LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, msgID) = Can_GetInitCodeOfInitBasicCan(filterHandle) & (vuint32)0x1FFFFFFF;
  pIndivRxMask->indivRxMask[localInfo->hwObjHandle] = (Can_GetInitMaskOfInitBasicCan(filterHandle) & (vuint32)0x1FFFFFFF) | 0xC0000000u;
#  if defined(C_ENABLE_EXTENDED_ID)
#   if defined(C_ENABLE_MIXED_ID)
  if((Can_GetInitCodeOfInitBasicCan(filterHandle) & kExtIDBit) == 0)
  {
    LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control) = kRxCodeEmpty; /* configure mailbox as receive message buffer */
  }
  else
#   endif
  {
    LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control) = (kRxCodeEmpty | (vuint16)kCanIdTypeExt); /* configure mailbox as receive message buffer */
  }
#  else
  LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control) = kRxCodeEmpty; /* configure mailbox as receive message buffer */
#  endif

  /* shadow buffer implementation: next filterHandle must be used */
  filterHandle += 1;
  LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle + 1, msgID) = Can_GetInitCodeOfInitBasicCan(filterHandle) & (vuint32)0x1FFFFFFF;
  pIndivRxMask->indivRxMask[localInfo->hwObjHandle + 1] = (Can_GetInitMaskOfInitBasicCan(filterHandle) & (vuint32)0x1FFFFFFF) | 0xC0000000u;
#  if defined(C_ENABLE_EXTENDED_ID)
#   if defined(C_ENABLE_MIXED_ID)
  if((Can_GetInitCodeOfInitBasicCan(filterHandle) & kExtIDBit) == 0)
  {
    LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle + 1, control) = kRxCodeEmpty; /* configure mailbox as receive message buffer */
  }
  else
#   endif
  {
    LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle + 1, control) = (kRxCodeEmpty | (vuint16)kCanIdTypeExt); /* configure mailbox as receive message buffer */
  }
#  else
  LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle + 1, control) = kRxCodeEmpty; /* configure mailbox as receive message buffer */
#  endif
# else /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
  for(filterHandle = 0; filterHandle < NUMBER_OF_FILTERS(canHwChannel); filterHandle++)
  {
    if (filterHandle < NUMBER_OF_FULL_CONFIGURABLE_FILTERS(canHwChannel))  /* PRQA S 3355,3358 */ /* MD_Can_13.7,MD_Can_13. */
    {
      /* initialize individual masks for Rx Fifo */
      locMsgIDMask = Can_GetInitMaskOfInitBasicCan(Can_GetInitBasicCanIndex(localInfo->initObject) + filterHandle) & (vuint32)0x1FFFFFFF;
      //HYT       pIndivRxMask->indivRxMask[filterHandle] = (vuint32)((locMsgIDMask << 1) | kRxFIFO_MASK); /* bits REM and EXT must always match */
    }

    /* initialize Id table for Rx Fifo */
    locMsgIDMask = Can_GetInitCodeOfInitBasicCan(Can_GetInitBasicCanIndex(localInfo->initObject) + filterHandle) & (vuint32)0x1FFFFFFF;

    /* if Extended Id */
//HYT    if((Can_GetInitCodeOfInitBasicCan(Can_GetInitBasicCanIndex(localInfo->initObject) + filterHandle) & kExtIDBit) != 0)
//    {
//      pRxFIFO->rxIDTAB[filterHandle] = (vuint32)((locMsgIDMask << 1) | kRxFIFO_EXT);
//    }
//    else
//    {
//      pRxFIFO->rxIDTAB[filterHandle] = (vuint32)(locMsgIDMask << 1);
//    }
  }
# endif /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */

# if !defined ( C_ENABLE_FLEXCAN2_DERIVATIVE )
#  if !defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  /* set global mask register for Rx Fifo to 'must match' */
  //HYT  pFlexCANLocal->rxfgmask = (kRxFIFO_MASK | (vuint32)0x3FFFFFFE); /* bits REM and EXT must always match */
#  endif
# endif

  return(kCanOk);
}
/* CODE CATEGORY 4 END */

#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

/**********************************************************************************************************************
 *  CanLL_InitEndSetRegisters
 *********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitEndSetRegisters( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitInfoStructPtr localInfo )
{
  vuint32 tmpCANimask1;
 // tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

#if defined ( C_ENABLE_FLEXCAN2_DERIVATIVE )
  /* read timestamp to unlock the RxFifo to ensure correct receive behaviour after initialization process */
  Can_GetRxMsgBuffer(canHwChannel).timestamp = LOCAL_MAILBOX_ACCESS(canHwChannel, Can_Mailbox[CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel)].HwObjHandle, timestamp);
  /* clear BusOff, Error and WakeUp interrupt flags: Workaround for ESCAN00032346 */
  pFlexCANLocal->estat = (CANSFR_TYPE)kFlexCAN_STATUS_INT;
#endif

#if (defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) && !defined (C_ENABLE_OSEK_CAN_INTCTRL))
  if(Can_GetCanInterruptCounter(channel) == 0)
  {
    /* configure CAN[IMASK1] register value */
    tmpCANimask1 =  CAN_INT_MASK1(canHwChannel)
# if !defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
    & kCanRxFifoIntUnmask
# endif
    ;
# if !defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
#  if defined (C_ENABLE_RX_BASICCAN_OBJECTS) && !defined(C_ENABLE_RX_BASICCAN_POLLING)
    //HYT    tmpCANimask1 |= kRxFIFO_NEWMSG; /* enable Rx FIFO interrupt */
#  elif defined (C_ENABLE_RX_BASICCAN_OBJECTS) && defined (C_ENABLE_INDIVIDUAL_POLLING)
    if ((CAN_INT_MASK1(canHwChannel) & (vuint32)0x01) == (vuint32)0x01) /* PRQA S 3325 */ /* MD_Can_3325 */
    { /* PRQA S 3201 */ /* MD_Can_3201 */
      tmpCANimask1 |= kRxFIFO_NEWMSG; /* enable Rx FIFO interrupt */
    }
#  endif
# endif
  //  pFlexCANLocal->imask1 = tmpCANimask1;

# if defined ( C_ENABLE_MB32TO63 )
    pFlexCANLocal->imask2 = CAN_INT_MASK2(canHwChannel);
# endif
# if defined ( C_ENABLE_MB64TO95 )
#  if defined ( C_ENABLE_ASYM_MAILBOXES )
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64)
#  endif
  {
    pFlexCANLocal->imask3 = CAN_INT_MASK3(canHwChannel);
  }
# endif
# if defined ( C_ENABLE_MB96TO127 )
    pFlexCANLocal->imask4 = CAN_INT_MASK4(canHwChannel);
# endif
  }
#endif

  CAN_DUMMY_STATEMENT(localInfo); /* PRQA S 3199 */ /* MD_Can_3199_dummy */

  return(kCanOk);
}
/* CODE CATEGORY 4 END */
/**********************************************************************************************************************
 *  CanLL_InitEnd
 *********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitEnd( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitInfoStructPtr localInfo )
{
  /*nothing to do */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
  CAN_DUMMY_STATEMENT(localInfo); /* PRQA S 3199 */ /* MD_Can_3199_dummy */
  return(kCanOk);
}
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_CAN_RAM_CHECK )
/**********************************************************************************************************************
 *  CanLL_InitIsMailboxCorrupt
 *********************************************************************************************************************/
/* CODE CATEGORY 4 START */
 V_DEF_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_InitIsMailboxCorrupt( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitInfoStructPtr localInfo )
 {
   /* ----- Local Variables ---------------------------------------------- */
   vuint8    result,idx,wordLength,i;

# if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
#  if defined( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  CanObjectHandle hwObjCount;
#  endif
  CanObjectHandle hwObjHandle; /* PRQA S 0781 */ /* MD_Can_0781 */
# endif

# if defined ( C_ENABLE_CAN_FD_FULL )
# else
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
# endif

   /* ----- Implementation ----------------------------------------------- */
   result = kCanFalse;

# if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
   hwObjHandle = localInfo->hwObjHandle;
#  if defined( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
#   if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
  if ( (localInfo->mailboxHandle >= CAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel)) && (localInfo->mailboxHandle < CAN_HL_MB_RX_BASIC_STOPINDEX(canHwChannel)) )
#   else
  if ( localInfo->mailboxHandle < CAN_HL_MB_RX_BASIC_STOPINDEX(canHwChannel) )
#   endif
#  endif
# endif
  {
# if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
#  if defined( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
    for (hwObjCount = 0; hwObjCount < Can_Mailbox[localInfo->mailboxHandle].HwObjCount; hwObjCount++)
#  endif
# endif
    {
      /* #10 DLC and IDE register check */
      LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = (vuint16)0x0055;
      if((LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) & (vuint16)0x007F) != (vuint16)0x0055)
      {
        result = kCanTrue;
      }
      LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = (vuint16)0x002A;
      if((LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) & (vuint16)0x007F) != (vuint16)0x002A)
      {
        result = kCanTrue;
      }
      LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = (vuint16)0x0000;
      if((LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) & (vuint16)0x007F) != (vuint16)0x0000)
      {
        result = kCanTrue;
      }

     /* #20 Iterate test patterns */
      for(i = 0; i < 3; i++)
      {
        /* #30 ID register check */
        LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, msgID) = ramCheckPattern32[i];
        if((LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, msgID) != ramCheckPattern32[i]))
        {
          result = kCanTrue;
        }
        /* #40 Data register check */
# if defined ( C_ENABLE_CAN_FD_FULL )
        wordLength = CANFD_MAILBOX_MAX_WORD_LENGTH(canHwChannel);
# else
        wordLength = 2; /* check 8 data bytes */
# endif
        for (idx=0; idx<wordLength; idx++)
        {
          LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, data[idx]) = ramCheckPattern32[i];
          if(LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, data[idx]) != ramCheckPattern32[i])
          {
            result = kCanTrue;
          }
        }
      }
# if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
#  if defined( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
      hwObjHandle++;
#  endif
# endif
    }
  }

  return result;
}
/* CODE CATEGORY 4 END */
#endif /* C_ENABLE_CAN_RAM_CHECK */

/**********************************************************************************************************************
 *  CanLL_InitPowerOn
 *********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitPowerOn(void)
{
#if defined(C_ENABLE_SLEEP_WAKEUP) && !defined(C_ENABLE_FLEXCAN_STOP_MODE)
  /* dummy call of empty function */
  CAN_CHANNEL_CANTYPE_LOCAL
# if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  channel = 0; /* PRQA S 3198 */ /* MD_Can_3198 */
# endif
  CanLL_WakeUpHandling(CAN_CHANNEL_CANPARA_ONLY);
#endif
 return (kCanOk);
}
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitPowerOnChannelSpecific
 *********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitPowerOnChannelSpecific(CAN_CHANNEL_CANTYPE_ONLY)
{

  canLL_canInitState[channel] = kCanLLStateInitStart;
  canLL_canStartState[channel] = kCanLLStateStart;
#if defined(C_ENABLE_STOP)
  canLL_canStopState[channel] = kCanLLStateStart;
#endif
#if defined(C_ENABLE_SLEEP_WAKEUP)
  canLL_canSleepState[channel] = kCanLLStateStart;
  canLL_canWakeUpState[channel] = kCanLLStateStart;
#endif

  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
 return (kCanOk);
}
/* CODE CATEGORY 4 END */

#if ((defined( C_ENABLE_CAN_TRANSMIT ) && defined( C_ENABLE_CAN_CANCEL_TRANSMIT )) ||  defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )) && defined( C_ENABLE_CANCEL_IN_HW )
/**********************************************************************************************************************
 *  CanLL_TxCancelInHw
 *********************************************************************************************************************/
/* CODE CATEGORY 3 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxCancelInHw(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxCancellationInfoStructPtr localInfo)
{
# if defined( C_ENABLE_TX_FULLCAN_DELAYED_START )
  /* Only fullcans are considered */
  if ( (localInfo->hwObjHandle != Can_Mailbox[CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel)].HwObjHandle)
#  if defined ( C_ENABLE_MSG_TRANSMIT )
  && (localInfo->hwObjHandle != Can_Mailbox[CAN_HL_MB_MSG_TRANSMIT_INDEX(canHwChannel)].HwObjHandle)
#  endif
  )
  {
    CanDeclareGlobalInterruptOldStatus

    /* Disable global interrupts */
    CanNestedGlobalInterruptDisable();
    /* Check whether the cancelled tx object has the internal delayed flag set,
       if yes -> the Tx is not requested yet (in HW) and the appropriate canHandleCurTxObj[logTxObjHandle] is set to kCanBufferCancel here
                 and it has to be not sent by CanTxFullCanDelayedStart()
       if no  -> the Tx is already requested - Tx or Abort acknowledge will come as usual */
    if (CanGetMailboxDelayed(channel, localInfo->hwObjHandle))
    { /* the Tx is not requested yet */
      /* Clear the pending Tx fullcan object from internal delayed Tx flags */
      CanClearMailboxDelayed(channel, localInfo->hwObjHandle);
      /* free the canHandleCurTxObj[logTxObjHandle]. This must be done here, because the Tx is not requested in HW and NO TxACK nor AbACK will come, where
         the semaphore would be freed */
      canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;
    }
    else
    {
      GLOBAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control) = kTxCodeAbort;
    }

    /* Enable global interrupts */
    CanNestedGlobalInterruptRestore();
  }
  else
  {
    GLOBAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control) = kTxCodeAbort;
  }
# else /* C_ENABLE_TX_FULLCAN_DELAYED_START */
  GLOBAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control) = kTxCodeAbort;
# endif /* C_ENABLE_TX_FULLCAN_DELAYED_START */
}
/* CODE CATEGORY 3 END */
#endif

#if defined( C_ENABLE_CAN_TRANSMIT )
/**********************************************************************************************************************
 *  CanLL_TxBegin
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionInfoStructPtr localInfo)
{
  /* CanLL_TxBegin: nothing to do here */
  CAN_DUMMY_STATEMENT(localInfo); /* PRQA S 3199 */ /* MD_Can_3199_dummy */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_TxSetMailbox
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxSetMailbox(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionInfoStructPtr localInfo)
{
# if !defined ( C_ENABLE_CAN_FD_FULL )
//  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
# endif
  vuint16 tmpControlVal;

# if defined( C_ENABLE_EXTENDED_ID )
  LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, msgID) = (vuint32)(localInfo->idRaw0);
# else
//  LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, msgID) = (vuint32)(localInfo->idRaw0) << 16;
# endif
  //HYT  tmpControlVal = (vuint16)(((vuint16)localInfo->dlcRaw & kTxDlcMask) | kTxCodeFree); /* write IDE,SRR and DLC */

# if defined( C_ENABLE_MIXED_ID )
#  if defined( C_ENABLE_DYN_TX_DLC ) || \
     defined( C_ENABLE_DYN_TX_ID )
  tmpControlVal &= kNotIDEMask; /* clear IDE and SRR bit */
  tmpControlVal |= (vuint16)(localInfo->idType);
#  endif
# endif

# if defined(C_ENABLE_CAN_FD_USED)
  tmpControlVal |= (vuint16)(localInfo->fdType | localInfo->fdBrsType);
# endif

 // LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control) = tmpControlVal;
}
/* CODE CATEGORY 1 END */

# if defined( C_ENABLE_PRETRANSMIT_FCT )
/**********************************************************************************************************************
 *  CanLL_TxSetTxStruct
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxSetTxStruct(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionInfoStructPtr localInfo)
{
# if !defined ( C_ENABLE_CAN_FD_FULL )
  //tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
# endif

/* get pointer to DLC and ID field in message object */
//  localInfo->txStruct.pChipMsgObj = (CanChipMsgPtr)&(LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control)); /* PRQA S 0310,3689 */ /* MD_Can_0310,MD_Can_3689_LL_objHandle */
/* get pointer to datafield in message object */
# if defined( C_CPUTYPE_LITTLEENDIAN )
 // localInfo->txStruct.pChipData = (CanChipDataPtr)&(canTxMsgBuffer[localInfo->logTxObjHandle].data[0]); /* PRQA S 0310 */ /* MD_Can_0310 */
# endif
}
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_PRETRANSMIT_FCT )
/**********************************************************************************************************************
 *  CanLL_TxPretransmitCopyToCan
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxPretransmitCopyToCan(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionInfoStructPtr localInfo)
{
# if defined( C_CPUTYPE_LITTLEENDIAN )
#  if defined ( C_ENABLE_CAN_FD_FULL )
  vuint32     canTxData;
  vuint8      idx, bidx, wordlength;
#  else
  //tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  vuint32     canTxBuf[2];
#  endif
# endif

# if defined( C_CPUTYPE_LITTLEENDIAN )
#  if defined ( C_ENABLE_CAN_FD_FULL )
  wordlength = CANFD_MAILBOX_MAX_WORD_LENGTH(canHwChannel);
  bidx = 0;
  for (idx=0; idx<wordlength; idx++)
  {
  	canTxData = ((vuint32)(localInfo->txStruct.pChipData[bidx]) << 24) | ((vuint32)(localInfo->txStruct.pChipData[bidx+1]) << 16) | ((vuint32)(localInfo->txStruct.pChipData[bidx+2]) << 8) | ((vuint32)(localInfo->txStruct.pChipData[bidx+3]));
    LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, data[idx]) = canTxData;
    bidx += 4;
  }
#  else
  ((vuint8*)canTxBuf)[0] = localInfo->txStruct.pChipData[3]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)canTxBuf)[1] = localInfo->txStruct.pChipData[2]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)canTxBuf)[2] = localInfo->txStruct.pChipData[1]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)canTxBuf)[3] = localInfo->txStruct.pChipData[0]; /* PRQA S 0310 */ /* MD_Can_0310 */
 // LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, data[0]) = canTxBuf[0];
  ((vuint8*)canTxBuf)[4] = localInfo->txStruct.pChipData[7]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)canTxBuf)[5] = localInfo->txStruct.pChipData[6]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)canTxBuf)[6] = localInfo->txStruct.pChipData[5]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)canTxBuf)[7] = localInfo->txStruct.pChipData[4]; /* PRQA S 0310 */ /* MD_Can_0310 */
 // LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, data[1]) = canTxBuf[1];
#  endif
# endif

  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 1 END */
# endif /* C_ENABLE_PRETRANSMIT_FCT */

# if defined( C_ENABLE_COPY_TX_DATA )
/**********************************************************************************************************************
 *  CanLL_TxCopyToCan
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxCopyToCan(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionInfoStructPtr localInfo)
{
#  if defined ( C_ENABLE_CAN_FD_FULL )
  vuint32     canFDTxBuf[16];
#  else
  //tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  vuint32     canTxBuf[2];
#  endif

#  if defined(C_ENABLE_CAN_FD_FULL)
  /* copy FD data into tx message object */
#   if defined( C_CPUTYPE_LITTLEENDIAN )
  {
    vuint8 idx, dataWordLen;
    vuint8 widx;
    for (idx = 0; idx < localInfo->messageLen; idx += 4)
    {
      ((vuint8*)canFDTxBuf)[idx+3] = localInfo->CanMemCopySrcPtr[idx]; /* PRQA S 0310 */ /* MD_Can_0310 */
      ((vuint8*)canFDTxBuf)[idx+2] = localInfo->CanMemCopySrcPtr[idx+1]; /* PRQA S 0310 */ /* MD_Can_0310 */
      ((vuint8*)canFDTxBuf)[idx+1] = localInfo->CanMemCopySrcPtr[idx+2]; /* PRQA S 0310 */ /* MD_Can_0310 */
      ((vuint8*)canFDTxBuf)[idx] = localInfo->CanMemCopySrcPtr[idx+3]; /* PRQA S 0310 */ /* MD_Can_0310 */
    }
    widx = idx - localInfo->messageLen;
    while (widx > 0)
    {
      ((vuint8*)canFDTxBuf)[(idx+widx)-5] = localInfo->paddingVal; /* PRQA S 0310 */ /* MD_Can_0310 */
      widx--;
    }
    while (idx < localInfo->frameLen)
    {
      ((vuint8*)canFDTxBuf)[idx+3] = localInfo->paddingVal; /* PRQA S 0310 */ /* MD_Can_0310 */
      ((vuint8*)canFDTxBuf)[idx+2] = localInfo->paddingVal; /* PRQA S 0310 */ /* MD_Can_0310 */
      ((vuint8*)canFDTxBuf)[idx+1] = localInfo->paddingVal; /* PRQA S 0310 */ /* MD_Can_0310 */
      ((vuint8*)canFDTxBuf)[idx] = localInfo->paddingVal; /* PRQA S 0310 */ /* MD_Can_0310 */
      idx+=4;
    }
    dataWordLen = (localInfo->frameLen + 3) >> 2;
    for (idx = 0; idx < dataWordLen; idx++)
    {
      LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, data[idx]) = canFDTxBuf[idx]; /* PRQA S 3353 */ /* MD_Can_3353_LL_canFDTxBuf */
    }
  }
#   endif
#  else

  /* copy data into tx message object */
#   if defined( C_CPUTYPE_LITTLEENDIAN )
  ((vuint8*)canTxBuf)[0] = localInfo->CanMemCopySrcPtr[3]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)canTxBuf)[1] = localInfo->CanMemCopySrcPtr[2]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)canTxBuf)[2] = localInfo->CanMemCopySrcPtr[1]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)canTxBuf)[3] = localInfo->CanMemCopySrcPtr[0]; /* PRQA S 0310 */ /* MD_Can_0310 */
 // LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, data[0]) = canTxBuf[0];
  ((vuint8*)canTxBuf)[4] = localInfo->CanMemCopySrcPtr[7]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)canTxBuf)[5] = localInfo->CanMemCopySrcPtr[6]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)canTxBuf)[6] = localInfo->CanMemCopySrcPtr[5]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)canTxBuf)[7] = localInfo->CanMemCopySrcPtr[4]; /* PRQA S 0310 */ /* MD_Can_0310 */
 // LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, data[1]) = canTxBuf[1];
#   endif
#  endif
}
/* CODE CATEGORY 1 END */
# endif

/**********************************************************************************************************************
 *  CanLL_TxStart
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_TxStart(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionInfoStructPtr localInfo)
{
# if !defined ( C_ENABLE_CAN_FD_FULL )
//  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
# endif

#  if defined (C_ENABLE_TX_FULLCAN_DELAYED_START)
  /* if transmission request is a Tx FullCAN - store transmit request */
  if (localInfo->hwObjHandle != Can_Mailbox[CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel)].HwObjHandle)
  {
    CanSetMailboxDelayed(channel, localInfo->hwObjHandle);
  }
  else
  /* if transmission request is a Tx Normal - send as usual */
#  endif /* C_ENABLE_TX_FULLCAN_DELAYED_START */
  {
	  //HYT    LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control) |= kTxCodeTransmit; /* start tx of the message */
# if defined (C_ENABLE_WORKAROUND_ERR005829)
    /* set the reserved mailbox twice to CodeInactive. This workaround is recommended by freescale. */
    LOCAL_MAILBOX_ACCESS(canHwChannel, INDEX_RSVD_MB(canHwChannel), control) |= kTxCodeInactive;
    LOCAL_MAILBOX_ACCESS(canHwChannel, INDEX_RSVD_MB(canHwChannel), control) |= kTxCodeInactive;
# endif
  }

  return(kCanOk);
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_TxEnd
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionInfoStructPtr localInfo)
{
  /* #10 nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
  CAN_DUMMY_STATEMENT(localInfo); /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 1 END */
#endif /* C_ENABLE_CAN_TRANSMIT */

#if defined( C_ENABLE_TX_POLLING )
/**********************************************************************************************************************
 *  CanLL_TxIsGlobalConfPending
 *********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_TxIsGlobalConfPending(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint32 iFlags;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  vuint8 retVal = kCanFalse;

  iFlags = pFlexCANLocal->iflag1 & CAN_TX_POLL_MASK1(canHwChannel);
#if defined ( C_ENABLE_MB32TO63 )
  iFlags |= pFlexCANLocal->iflag2 & CAN_TX_POLL_MASK2(canHwChannel);
#endif
#if defined ( C_ENABLE_MB64TO95 )
# if defined ( C_ENABLE_ASYM_MAILBOXES )
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64)
# endif
  {
    iFlags |= pFlexCANLocal->iflag3 & CAN_TX_POLL_MASK3(canHwChannel);
  }
#endif
#if defined ( C_ENABLE_MB96TO127 )
  iFlags |= pFlexCANLocal->iflag4 & CAN_TX_POLL_MASK4(canHwChannel);
#endif

  if(iFlags != 0)
  {
    retVal = kCanTrue;
  }

  return retVal;
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_TxProcessPendings
 *********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskInfoStructPtr localInfo)
{
  vuint32 iFlags = 0;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

  if (localInfo->hwObjHandle < 32)
  {
    iFlags = pFlexCANLocal->iflag1;
  }
#if defined ( C_ENABLE_MB32TO63 )
  else
  {
    if (localInfo->hwObjHandle < 64)
    {
      iFlags = pFlexCANLocal->iflag2;
    }
# if defined ( C_ENABLE_MB64TO95 )
    else
    {
      if (localInfo->hwObjHandle < 96)
      {
        iFlags = pFlexCANLocal->iflag3;
      }
#  if defined ( C_ENABLE_MB96TO127 )
      else
      {
        iFlags = pFlexCANLocal->iflag4;
      }
#  endif
    }
# endif
  }
#endif

  if( ((iFlags & CanBitMask(localInfo->hwObjHandle)) != 0)
  )
  {
    CanHL_TxConfirmationPolling(CAN_HW_CHANNEL_CANPARA_FIRST Can_HwObjToMailboxIndirection[CAN_HL_MB_INDIRECTION_STARTINDEX(canHwChannel) + localInfo->hwObjHandle], localInfo->hwObjHandle);
  }
}
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_TX_POLLING */

/**********************************************************************************************************************
 *  CanLL_TxConfBegin
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxConfBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationInfoStructPtr localInfo)
{
//  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

  if (localInfo->hwObjHandle < 32)
  {
 //   pFlexCANLocal->iflag1 = CanBitMask(localInfo->hwObjHandle); /* clear pending interrupt flag */
  }
#if defined ( C_ENABLE_MB32TO63 )
  else
  {
    if (localInfo->hwObjHandle < 64)
    {
      pFlexCANLocal->iflag2 = CanBitMask(localInfo->hwObjHandle); /* clear pending interrupt flag */
    }
  # if defined ( C_ENABLE_MB64TO95 )
    else
    {
      if (localInfo->hwObjHandle < 96)
      {
        pFlexCANLocal->iflag3 = CanBitMask(localInfo->hwObjHandle); /* clear pending interrupt flag */
      }
#  if defined ( C_ENABLE_MB96TO127 )
      else
      {
        pFlexCANLocal->iflag4 = CanBitMask(localInfo->hwObjHandle); /* clear pending interrupt flag */
      }
#  endif
    }
# endif
  }
#endif
}
/* CODE CATEGORY 1 END */

#if (defined( C_ENABLE_TX_OBSERVE ) || defined( C_ENABLE_CAN_TX_CONF_FCT )) && defined( C_ENABLE_CANCEL_IN_HW )
/**********************************************************************************************************************
 *  CanLL_TxConfIsMsgTransmitted
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_TxConfIsMsgTransmitted(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationInfoStructPtr localInfo)
{
  vuint8 isMsgTransmitted;

  isMsgTransmitted = (vuint8)CanLL_TxIsObjFree(canHwChannel, localInfo->hwObjHandle); /* PRQA S 3689 */ /* MD_Can_3689_LL_objHandle */
  if (!isMsgTransmitted)
  {
    GLOBAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control) = kTxCodeFree; /* PRQA S 3689 */ /* MD_Can_3689_LL_objHandle */
  }

  return isMsgTransmitted;
}
/* CODE CATEGORY 1 END */
#endif

#if defined( C_ENABLE_CAN_TX_CONF_FCT ) && defined( C_ENABLE_CAN_TX_CONF_MSG_ACCESS )
/**********************************************************************************************************************
 *  CanLL_TxConfSetTxConfStruct
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxConfSetTxConfStruct(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationInfoStructPtr localInfo)
{
#if defined (C_ENABLE_ECU_SWITCH_PASS)
#else
  localInfo->txInfoStructConf->pChipMsgObj = (CanChipDataPtr)&(GLOBAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, data[0])); /* PRQA S 0310 */ /* MD_Can_0310 */
  localInfo->txInfoStructConf->pChipData = (CanChipMsgPtr)&(GLOBAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control)); /* PRQA S 0310 */ /* MD_Can_0310 */
#endif
}
/* CODE CATEGORY 1 END */
#endif

/**********************************************************************************************************************
 *  CanLL_TxConfEnd
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxConfEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationInfoStructPtr localInfo)
{
  /* CanLL_TxConfEnd: nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
  CAN_DUMMY_STATEMENT(localInfo); /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 1 END */

#if defined( C_ENABLE_MSG_TRANSMIT )
/**********************************************************************************************************************
 *  CanLL_TxBeginMsgTransmit
 *********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxBeginMsgTransmit(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxMsgTransmissionInfoStructPtr localInfo)
{
  /* CanLL_TxBeginMsgTransmit: nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
  CAN_DUMMY_STATEMENT(localInfo); /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_TxCopyMsgTransmit
 *********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxCopyMsgTransmit(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxMsgTransmissionInfoStructPtr localInfo)
{
# if defined(C_ENABLE_CAN_FD_FULL)
  vuint32     canFDTxBuf[16];
  vuint8      messageLen; /* PRQA S 0781 */ /* MD_Can_0781 */
  vuint8      frameLen; /* PRQA S 0781 */ /* MD_Can_0781 */
# else
  vuint32     canTxBuf[2];
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
# endif

# if defined(C_ENABLE_CAN_FD_FULL)
  messageLen = (vuint8)((localInfo->txMsgStruct)->TimeStamp);
  frameLen = (vuint8)CAN_DLC2LEN((localInfo->txMsgStruct)->DlcRaw); /* PRQA S 0781 */ /* MD_Can_0781 */

  assertUser(messageLen <= CAN_HL_MAX_LEN(channel), channel, kErrorTxDlcTooLarge);
# endif

#if defined(C_ENABLE_CAN_FD_USED)
  LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control) = (vuint16)(((vuint16)((localInfo->txMsgStruct)->DlcRaw) & (kTxDlcMask | kCanFdTypeFd | kCanFdBrsTypeTrue)) | kTxCodeFree);
# else
  LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control) = (vuint16)(((vuint16)((localInfo->txMsgStruct)->DlcRaw) & kTxDlcMask) | kTxCodeFree);
# endif
  LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, msgID) = (vuint32)((localInfo->txMsgStruct)->IdRaw);

# if defined(C_ENABLE_CAN_FD_FULL)
   /* copy FD data into tx message object */
#  if defined( C_CPUTYPE_LITTLEENDIAN )
  {
    vuint8 idx, dataWordLen;
    vuint8 widx;
    for (idx = 0; idx < messageLen; idx += 4)
    {
      ((vuint8*)canFDTxBuf)[idx+3] = (localInfo->txMsgStruct)->DataFld[idx]; /* PRQA S 0310 */ /* MD_Can_0310 */
      ((vuint8*)canFDTxBuf)[idx+2] = (localInfo->txMsgStruct)->DataFld[idx+1]; /* PRQA S 0310 */ /* MD_Can_0310 */
      ((vuint8*)canFDTxBuf)[idx+1] = (localInfo->txMsgStruct)->DataFld[idx+2]; /* PRQA S 0310 */ /* MD_Can_0310 */
      ((vuint8*)canFDTxBuf)[idx] = (localInfo->txMsgStruct)->DataFld[idx+3]; /* PRQA S 0310 */ /* MD_Can_0310 */
    }
    widx = idx - messageLen; /* PRQA S 0291 */ /* MD_Can_0291_LL */
    while (widx > 0)
    {
      ((vuint8*)canFDTxBuf)[(idx+widx)-5] = (vuint8)C_CAN_FD_PADDING_VALUE; /* PRQA S 0310 */ /* MD_Can_0310 */
      widx--;
    }
    while (idx < frameLen)
    {
      ((vuint8*)canFDTxBuf)[idx+3] = (vuint8)C_CAN_FD_PADDING_VALUE; /* PRQA S 0310 */ /* MD_Can_0310 */
      ((vuint8*)canFDTxBuf)[idx+2] = (vuint8)C_CAN_FD_PADDING_VALUE; /* PRQA S 0310 */ /* MD_Can_0310 */
      ((vuint8*)canFDTxBuf)[idx+1] = (vuint8)C_CAN_FD_PADDING_VALUE; /* PRQA S 0310 */ /* MD_Can_0310 */
      ((vuint8*)canFDTxBuf)[idx] = (vuint8)C_CAN_FD_PADDING_VALUE; /* PRQA S 0310 */ /* MD_Can_0310 */
      idx+=4;
    }
    dataWordLen = (frameLen + 3) >> 2;
    for (idx = 0; idx < dataWordLen; idx++)
    {
      LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, data[idx]) = canFDTxBuf[idx]; /* PRQA S 3353 */ /* MD_Can_3353_LL_canFDTxBuf */
    }
  }
#  endif
# else
#  if defined( C_CPUTYPE_LITTLEENDIAN )
  ((vuint8*)canTxBuf)[0] = (localInfo->txMsgStruct)->DataFld[3]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)canTxBuf)[1] = (localInfo->txMsgStruct)->DataFld[2]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)canTxBuf)[2] = (localInfo->txMsgStruct)->DataFld[1]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)canTxBuf)[3] = (localInfo->txMsgStruct)->DataFld[0]; /* PRQA S 0310 */ /* MD_Can_0310 */
  LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, data[0]) = canTxBuf[0];
  ((vuint8*)canTxBuf)[4] = (localInfo->txMsgStruct)->DataFld[7]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)canTxBuf)[5] = (localInfo->txMsgStruct)->DataFld[6]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)canTxBuf)[6] = (localInfo->txMsgStruct)->DataFld[5]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)canTxBuf)[7] = (localInfo->txMsgStruct)->DataFld[4]; /* PRQA S 0310 */ /* MD_Can_0310 */
  LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, data[1]) = canTxBuf[1];
#  endif
# endif
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_TxStartMsgTransmit
 *********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_TxStartMsgTransmit(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxMsgTransmissionInfoStructPtr localInfo)
{
#if !defined (C_ENABLE_CAN_FD_FULL)
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
#endif

  LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control) |= kTxCodeTransmit; /* start tx of the message */
#if defined (C_ENABLE_WORKAROUND_ERR005829)
  /* set the reserved mailbox twice to CodeInactive. This workaround is recommended by freescale. */
  LOCAL_MAILBOX_ACCESS(canHwChannel, INDEX_RSVD_MB(canHwChannel), control) |= kTxCodeInactive;
  LOCAL_MAILBOX_ACCESS(canHwChannel, INDEX_RSVD_MB(canHwChannel), control) |= kTxCodeInactive;
#endif

  return(kCanOk);
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_TxEndMsgTransmit
 *********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxEndMsgTransmit(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxMsgTransmissionInfoStructPtr localInfo)
{
  /* CanLL_TxEndMsgTransmit: nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
  CAN_DUMMY_STATEMENT(localInfo); /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_MSG_TRANSMIT */

#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_RxBasicMsgReceivedBegin
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxBasicMsgReceivedBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicInfoStructPtr localInfo)
{
//  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  vuint8 retVal = kCanTrue;


#if defined( C_CPUTYPE_LITTLEENDIAN )
# if defined ( C_ENABLE_CAN_FD_FULL )
# else
  vuint32 canRxBuf[2];
# endif
#endif
#if defined ( C_ENABLE_CAN_FD_FULL )
  vuint8 idx;
#endif
#if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
# if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanDeclareGlobalInterruptOldStatus
# endif
  vuint8 loopResult = 1; /* PRQA S 3197 */ /* MD_Can_3197_LL */
#endif

#if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
# if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanNestedGlobalInterruptDisable();
# endif
  Can_GetRxMsgBuffer(canHwChannel).control = LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control);
  if ((Can_GetRxMsgBuffer(canHwChannel).control & kRxCodeBusy) == kRxCodeBusy)
  {
    APPLCANTIMERSTART(kCanLoopMsgReception); /* start hw loop timer */
    do
    { /* Check busy state of receive object */
      Can_GetRxMsgBuffer(canHwChannel).control = LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control);
      loopResult = APPLCANTIMERLOOP(kCanLoopMsgReception);
    }while(((Can_GetRxMsgBuffer(canHwChannel).control & kRxCodeBusy) == kRxCodeBusy) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
    APPLCANTIMEREND(kCanLoopMsgReception); /* stop hw loop timer */
  }
#else /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
 // Can_GetRxMsgBuffer(canHwChannel).control = LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control);
  Can_GetRxMsgBuffer(canHwChannel).control =  rxMsg.RxHeandle.DLC;

#endif /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */

  /* copy id and data to RAM buffer */
//  Can_GetRxMsgBuffer(canHwChannel).msgID = LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, msgID);
  Can_GetRxMsgBuffer(canHwChannel).msgID =  rxMsg.RxHeandle.Identifier;
#if defined( C_CPUTYPE_LITTLEENDIAN )
# if defined ( C_ENABLE_CAN_FD_FULL )
  for (idx=0; idx<CANFD_MAILBOX_MAX_WORD_LENGTH(canHwChannel); idx++)
  {
    Can_GetRxMsgBuffer(canHwChannel).data[idx] = CanBswap32(LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, data[idx])); /* PRQA S 0310 */ /* MD_Can_0310 */
  }
# else

  //  canRxBuf[0] = LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, data[0]);       /* PRQA S 3689 */ /* MD_Can_3689_LL_objHandle */
	//  canRxBuf[1] = LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, data[1]);       /* PRQA S 3689 */ /* MD_Can_3689_LL_objHandle */
  ((vuint8*)Can_GetRxMsgBuffer(canHwChannel).data)[0] = rxMsg.RxData[0]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)Can_GetRxMsgBuffer(canHwChannel).data)[1] = rxMsg.RxData[1]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)Can_GetRxMsgBuffer(canHwChannel).data)[2] = rxMsg.RxData[2]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)Can_GetRxMsgBuffer(canHwChannel).data)[3] = rxMsg.RxData[3]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)Can_GetRxMsgBuffer(canHwChannel).data)[4] = rxMsg.RxData[4]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)Can_GetRxMsgBuffer(canHwChannel).data)[5] = rxMsg.RxData[5]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)Can_GetRxMsgBuffer(canHwChannel).data)[6] = rxMsg.RxData[6]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)Can_GetRxMsgBuffer(canHwChannel).data)[7] = rxMsg.RxData[7]; /* PRQA S 0310 */ /* MD_Can_0310 */
# endif
#endif

#if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  if (localInfo->hwObjHandle < 32)
  {
    pFlexCANLocal->iflag1 = CanBitMask(localInfo->hwObjHandle); /* clear pending interrupt flag  */
  }
# if defined ( C_ENABLE_MB32TO63 )
  else
  {
    if (localInfo->hwObjHandle < 64)
    {
      pFlexCANLocal->iflag2 = CanBitMask(localInfo->hwObjHandle); /* clear pending interrupt flag  */
    }
#  if defined ( C_ENABLE_MB64TO95 )
    else
    {
      if (localInfo->hwObjHandle < 96)
      {
        pFlexCANLocal->iflag3 = CanBitMask(localInfo->hwObjHandle); /* clear pending interrupt flag  */
      }
#   if defined ( C_ENABLE_MB96TO127 )
      else
      {
        pFlexCANLocal->iflag4 = CanBitMask(localInfo->hwObjHandle); /* clear pending interrupt flag  */
      }
#   endif
    }
#  endif
  }
# endif

  /* to unlock only the current receive buffer the timestamp of another not-Rx message object must be read
   * reading the global timer results in a global unlock of all receive buffers */
  Can_GetRxMsgBuffer(canHwChannel).timestamp = LOCAL_MAILBOX_ACCESS(canHwChannel, Can_Mailbox[CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel)].HwObjHandle, timestamp); /* unlock current receive buffer */

# if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanNestedGlobalInterruptRestore();
# endif

# if defined( C_ENABLE_HW_LOOP_TIMER )
  if (loopResult == 0)
  {
    retVal = kCanFailed;
  }
# endif
#else /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */

//    pFlexCANLocal->iflag1 = (vuint32)kRxFIFO_NEWMSG; /* clear RxFIFO pending interrupt flag after message is stored! */
#endif /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */

  /* CanLL_RxBasicGetCANObjPtr */
  localInfo->pChipMsgObj = (CanChipMsgPtr) &(Can_GetRxMsgBuffer(canHwChannel).control); /* PRQA S 0310 */ /* MD_Can_0310 */ /* SBSW_CAN_HL29 */

  /* CanLL_RxBasicGetCANDataPtr */
  localInfo->pChipData = (CanChipDataPtr) &(Can_GetRxMsgBuffer(canHwChannel).data[0]); /* PRQA S 0310 */ /* MD_Can_0310 */ /* SBSW_CAN_HL29 */

#if defined( C_ENABLE_OVERRUN )
# if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  if((Can_GetRxMsgBuffer(canHwChannel).control & kCodeMask) == kRxCodeOverrun)
  {
# else
  if((pFlexCANLocal->iflag1 & kRxFIFO_OVERRUN) != 0)
  {
    pFlexCANLocal->iflag1 = kRxFIFO_OVERRUN | kRxFIFO_WARN; /* clear warning and overflow flag */
# endif
    localInfo->isOverrun = (vuint8)kCanTrue;
  }
  else
  {
    localInfo->isOverrun = (vuint8)kCanFalse;
  }
#endif

  return (retVal);
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_RxBasicReleaseObj
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxBasicReleaseObj(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicInfoStructPtr localInfo)
{
  /* #10 nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
  CAN_DUMMY_STATEMENT(localInfo); /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_RxBasicMsgReceivedEnd
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxBasicMsgReceivedEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicInfoStructPtr localInfo)
{
  /* #10 nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
  CAN_DUMMY_STATEMENT(localInfo); /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 1 END */

# if defined( C_ENABLE_RX_BASICCAN_POLLING )
/**********************************************************************************************************************
 *  CanLL_RxBasicIsGlobalIndPending
 *********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxBasicIsGlobalIndPending(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 retVal = kCanFalse;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
#if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  vuint32 iFlags;

  iFlags = pFlexCANLocal->iflag1 & CAN_RXBASIC_POLL_MASK1(canHwChannel);
# if defined ( C_ENABLE_MB32TO63 )
  iFlags |= pFlexCANLocal->iflag2 & CAN_RXBASIC_POLL_MASK2(canHwChannel);
# endif
# if defined ( C_ENABLE_MB64TO95 )
#  if defined ( C_ENABLE_ASYM_MAILBOXES )
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64)
#  endif
  {
    iFlags |= pFlexCANLocal->iflag3 & CAN_RXBASIC_POLL_MASK3(canHwChannel);
  }
# endif
# if defined ( C_ENABLE_MB96TO127 )
  iFlags |= pFlexCANLocal->iflag4 & CAN_RXBASIC_POLL_MASK4(canHwChannel);
# endif
  if(iFlags != 0)
  {
#else /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
  if ((pFlexCANLocal->iflag1 & kRxFIFO_NEWMSG) != 0)
  {
#endif /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
    retVal = kCanTrue;
  }

  return retVal;
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_RxBasicProcessPendings
 *********************************************************************************************************************/
/* CODE CATEGORY 2 START */
 V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxBasicProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskInfoStructPtr localInfo)
 {
   tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
 #  if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
   vuint32 iFlags = 0;
   CanObjectHandle hwObjCount;
   CanObjectHandle hwObjHandle; /* PRQA S 0781 */ /* MD_Can_0781 */
 #  else
   vuint8 fifoLoopCnt=0;
 #  endif

 #  if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
   for (hwObjCount = 0; hwObjCount < Can_Mailbox[localInfo->mailboxHandle].HwObjCount; hwObjCount++)
   {
     hwObjHandle = localInfo->hwObjHandle + hwObjCount;
     if ((hwObjHandle) < 32)
     {
       iFlags = pFlexCANLocal->iflag1;
     }
   #   if defined ( C_ENABLE_MB32TO63 )
     else
     {
       if ((hwObjHandle) < 64)
       {
         iFlags = pFlexCANLocal->iflag2;
       }
   #    if defined ( C_ENABLE_MB64TO95 )
       else
       {
         if ((hwObjHandle) < 96)
         {
           iFlags = pFlexCANLocal->iflag3;
         }
   #     if defined ( C_ENABLE_MB96TO127 )
         else
         {
           iFlags = pFlexCANLocal->iflag4;
         }
   #     endif
       }
   #    endif
     }
   #   endif

     if((iFlags & CanBitMask(hwObjHandle)) != 0)
     {
       localInfo->hwObjHandle = hwObjHandle;
       CanBasicCanMsgReceivedPolling(CAN_HW_CHANNEL_CANPARA_FIRST localInfo->mailboxHandle, hwObjHandle);
     }
   }
 #  else /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
   while(((pFlexCANLocal->iflag1 & kRxFIFO_NEWMSG) != 0) && (fifoLoopCnt < C_FLEXCAN_RXFIFO_MAXLOOP))
   {
     fifoLoopCnt++;
     CanBasicCanMsgReceivedPolling(CAN_HW_CHANNEL_CANPARA_FIRST localInfo->mailboxHandle, localInfo->hwObjHandle);
   }
 #  endif /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
 }
/* CODE CATEGORY 2 END */
# endif /* C_ENABLE_RX_BASICCAN_POLLING */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_RxFullMsgReceivedBegin
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxFullMsgReceivedBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullInfoStructPtr localInfo)
{
#if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanDeclareGlobalInterruptOldStatus
#endif
#if defined( C_CPUTYPE_LITTLEENDIAN )
# if defined ( C_ENABLE_CAN_FD_FULL )
# else
  vuint32 canRxBuf[2];
# endif
#endif
#if defined ( C_ENABLE_CAN_FD_FULL )
  vuint8 idx;
#endif
  vuint8 retVal = kCanOk;
  vuint8 loopResult = 1; /* PRQA S 3197 */ /* MD_Can_3197_LL */
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

#if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanNestedGlobalInterruptDisable();
#endif

  Can_GetRxMsgBuffer(canHwChannel).control = LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control);
  if ((Can_GetRxMsgBuffer(canHwChannel).control & kRxCodeBusy) == kRxCodeBusy)
  {
    APPLCANTIMERSTART(kCanLoopMsgReception); /* start hw loop timer */
    do
    { /* Check busy state of receive object */
      Can_GetRxMsgBuffer(canHwChannel).control = LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, control);
      loopResult = APPLCANTIMERLOOP(kCanLoopMsgReception);
    }while(((Can_GetRxMsgBuffer(canHwChannel).control & kRxCodeBusy) == kRxCodeBusy) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
    APPLCANTIMEREND(kCanLoopMsgReception); /* stop hw loop timer */
  }

  if (localInfo->hwObjHandle < 32)
  {
    pFlexCANLocal->iflag1 = CanBitMask(localInfo->hwObjHandle); /* clear pending interrupt flag  */
  }
#if defined ( C_ENABLE_MB32TO63 )
  else
  {
    if (localInfo->hwObjHandle < 64)
    {
      pFlexCANLocal->iflag2 = CanBitMask(localInfo->hwObjHandle); /* clear pending interrupt flag  */
    }
# if defined ( C_ENABLE_MB64TO95 )
    else
    {
      if (localInfo->hwObjHandle < 96)
      {
        pFlexCANLocal->iflag3 = CanBitMask(localInfo->hwObjHandle); /* clear pending interrupt flag  */
      }
#  if defined ( C_ENABLE_MB96TO127 )
      else
      {
        pFlexCANLocal->iflag4 = CanBitMask(localInfo->hwObjHandle); /* clear pending interrupt flag  */
      }
#  endif
    }
# endif
  }
#endif

  /* copy id and data to RAM buffer */
  Can_GetRxMsgBuffer(canHwChannel).msgID = LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, msgID); /* PRQA S 3689 */ /* MD_Can_3689_LL_objHandle */
#if defined( C_CPUTYPE_LITTLEENDIAN )
# if defined ( C_ENABLE_CAN_FD_FULL )
  for (idx=0; idx<CANFD_MAILBOX_MAX_WORD_LENGTH(canHwChannel); idx++)
  {
    Can_GetRxMsgBuffer(canHwChannel).data[idx] = CanBswap32(LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, data[idx])); /* PRQA S 0310 */ /* MD_Can_0310 */
  }
# else
  canRxBuf[0] = LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, data[0]);       /* PRQA S 3689 */ /* MD_Can_3689_LL_objHandle */
  canRxBuf[1] = LOCAL_MAILBOX_ACCESS(canHwChannel, localInfo->hwObjHandle, data[1]);       /* PRQA S 3689 */ /* MD_Can_3689_LL_objHandle */
  ((vuint8*)Can_GetRxMsgBuffer(canHwChannel).data)[0] = ((vuint8*)canRxBuf)[3]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)Can_GetRxMsgBuffer(canHwChannel).data)[1] = ((vuint8*)canRxBuf)[2]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)Can_GetRxMsgBuffer(canHwChannel).data)[2] = ((vuint8*)canRxBuf)[1]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)Can_GetRxMsgBuffer(canHwChannel).data)[3] = ((vuint8*)canRxBuf)[0]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)Can_GetRxMsgBuffer(canHwChannel).data)[4] = ((vuint8*)canRxBuf)[7]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)Can_GetRxMsgBuffer(canHwChannel).data)[5] = ((vuint8*)canRxBuf)[6]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)Can_GetRxMsgBuffer(canHwChannel).data)[6] = ((vuint8*)canRxBuf)[5]; /* PRQA S 0310 */ /* MD_Can_0310 */
  ((vuint8*)Can_GetRxMsgBuffer(canHwChannel).data)[7] = ((vuint8*)canRxBuf)[4]; /* PRQA S 0310 */ /* MD_Can_0310 */
# endif
#endif
  /* to unlock only the current receive buffer the timestamp of another not-Rx message object must be read
   * reading the global timer results in a global unlock of all receive buffers */
  Can_GetRxMsgBuffer(canHwChannel).timestamp = LOCAL_MAILBOX_ACCESS(canHwChannel, Can_Mailbox[CAN_HL_MB_TX_NORMAL_INDEX(canHwChannel)].HwObjHandle, timestamp); /* unlock current receive buffer */

#if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanNestedGlobalInterruptRestore();
#endif

#if defined( C_ENABLE_HW_LOOP_TIMER )
  if (loopResult == 0)
  {
    retVal = kCanFailed;
  }
#endif

  /* CanLL_RxFullGetCANObjPtr */
  localInfo->pChipMsgObj = (CanChipMsgPtr) &(Can_GetRxMsgBuffer(canHwChannel).control); /* PRQA S 0310 */ /* MD_Can_0310 */ /* SBSW_CAN_HL30 */

  /* CanLL_RxFullGetCANDataPtr */
  localInfo->pChipData = (CanChipDataPtr) &(Can_GetRxMsgBuffer(canHwChannel).data[0]); /* PRQA S 0310 */ /* MD_Can_0310 */ /* SBSW_CAN_HL30 */

#if defined( C_ENABLE_FULLCAN_OVERRUN )
  if ((Can_GetRxMsgBuffer(canHwChannel).control & kCodeMask) == kRxCodeOverrun)
  {
    localInfo->isOverrun = kCanTrue;
  }
  else
  {
    localInfo->isOverrun = kCanFalse;
  }
#endif

  return (retVal);
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_RxFullReleaseObj
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
 V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxFullReleaseObj(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullInfoStructPtr localInfo)
{
  /* #10 nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
  CAN_DUMMY_STATEMENT(localInfo); /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_RxFullMsgReceivedEnd
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxFullMsgReceivedEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullInfoStructPtr localInfo)
{
  /* #10 nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
  CAN_DUMMY_STATEMENT(localInfo); /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 1 END */

# if defined( C_ENABLE_RX_FULLCAN_POLLING )
/**********************************************************************************************************************
 *  CanLL_RxFullIsGlobalIndPending
 *********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxFullIsGlobalIndPending(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint32 iFlags;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  vuint8 retVal = kCanFalse;

  iFlags = pFlexCANLocal->iflag1 & CAN_RXFULL_POLL_MASK1(canHwChannel);
#if defined ( C_ENABLE_MB32TO63 )
  iFlags |= pFlexCANLocal->iflag2 & CAN_RXFULL_POLL_MASK2(canHwChannel);
#endif
#if defined ( C_ENABLE_MB64TO95 )
# if defined ( C_ENABLE_ASYM_MAILBOXES )
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64)
# endif
  {
    iFlags |= pFlexCANLocal->iflag3 & CAN_RXFULL_POLL_MASK3(canHwChannel);
  }
#endif
#if defined ( C_ENABLE_MB96TO127 )
  iFlags |= pFlexCANLocal->iflag4 & CAN_RXFULL_POLL_MASK4(canHwChannel);
#endif

  if(iFlags != 0)
  {
    retVal = kCanTrue;
  }

  return retVal;
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_RxFullProcessPendings
 *********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxFullProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskInfoStructPtr localInfo)
{
  vuint32 iFlags = 0;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

  if (localInfo->hwObjHandle < 32)
  {
    iFlags = pFlexCANLocal->iflag1;
  }
#if defined ( C_ENABLE_MB32TO63 )
  else
  {
    if (localInfo->hwObjHandle < 64)
    {
      iFlags = pFlexCANLocal->iflag2;
    }
# if defined ( C_ENABLE_MB64TO95 )
    else
    {
      if (localInfo->hwObjHandle < 96)
      {
        iFlags = pFlexCANLocal->iflag3;
      }
#  if defined ( C_ENABLE_MB96TO127 )
      else
      {
        iFlags = pFlexCANLocal->iflag4;
      }
  #  endif
    }
# endif
  }
#endif

  if((iFlags & CanBitMask(localInfo->hwObjHandle)) != 0)
  {
    CanFullCanMsgReceivedPolling(CAN_HW_CHANNEL_CANPARA_FIRST Can_HwObjToMailboxIndirection[CAN_HL_MB_INDIRECTION_STARTINDEX(canHwChannel) + localInfo->hwObjHandle], localInfo->hwObjHandle);
  }
}
/* CODE CATEGORY 2 END */
# endif /* C_ENABLE_RX_FULLCAN_POLLING */
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

#if (defined( C_ENABLE_RX_FULLCAN_OBJECTS ) || defined( C_ENABLE_RX_BASICCAN_OBJECTS )) && ( kCanNumberOfRxObjects > 0 ) && defined( C_ENABLE_COPY_RX_DATA )
/**********************************************************************************************************************
 *  CanLL_RxCopyFromCan
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxCopyFromCan(CAN_CHANNEL_CANTYPE_FIRST CanRxCopyInfoStructPtr localInfo)
{
  vuint8 canllidx;
  for(canllidx=0; canllidx<localInfo->len; canllidx++)
  {
    localInfo->dest[canllidx] = localInfo->src[canllidx];
  }

  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 1 END */
#endif

/**********************************************************************************************************************
 *  CanLL_ErrorHandlingBegin
 *********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ErrorHandlingBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  /* #10 nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_BusOffOccured
 *********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_BusOffOccured(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
//  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  vuint8 retVal = kCanTrue;

//  if((pFlexCANLocal->estat & kFlexCAN_BOFF_INT) != 0)
//  {
//    pFlexCANLocal->estat = (CANSFR_TYPE)(kFlexCAN_BOFF_INT | kFlexCAN_ERR_INT); /* clear busoff and error interrupt flags */
//
//    retVal = kCanTrue;
//  }

  return retVal;
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_ErrorHandlingEnd
 *********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ErrorHandlingEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  /* #10 nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 2 END */

#if defined( C_ENABLE_EXTENDED_STATUS )
/**********************************************************************************************************************
 *  CanLL_GetStatusBegin
 *********************************************************************************************************************/
/* CODE CATEGORY 3 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_GetStatusBegin(CAN_CHANNEL_CANTYPE_ONLY)
{
  /* #10 nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 3 END */
#endif

#if defined( C_ENABLE_SLEEP_WAKEUP ) && defined( C_ENABLE_WAKEUP_POLLING )
/**********************************************************************************************************************
 *  CanLL_WakeUpOccured
 *********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_WakeUpOccured(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 retVal = kCanFalse;

  /*if((pFlexCAN(canHwChannel)->estat & kFlexCAN_WAKE_INT) != 0)
  {
    retVal = kCanTrue;
  }*/

  /* 始终返回没有唤醒中断 */
  retVal = kCanFalse;

  return retVal;
}
/* CODE CATEGORY 2 END */
#endif

#if defined( C_ENABLE_SLEEP_WAKEUP )
/**********************************************************************************************************************
 *  CanLL_WakeUpHandling
 *********************************************************************************************************************/
 /* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_WakeUpHandling(CAN_CHANNEL_CANTYPE_ONLY)
{
# if defined( C_ENABLE_FLEXCAN_STOP_MODE )
  /* ----- Local Variables ---------------------------------------------- */
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

  /* ----- Implementation ----------------------------------------------- */
  /* notify the application here and call WAKEUP handling */
#  if defined( C_ENABLE_APPLCANPREWAKEUP_FCT )
  /* #10 application callout to handle wakeup preconditions like transceiver mode */
  ApplCanPreWakeUp(CAN_CHANNEL_CANPARA_ONLY);
#  endif

  /*pFlexCANLocal->estat = kFlexCAN_WAKE_INT;*/ /* clear pending wakeup interrupt flag */

  /* #20 if hardware does not wake up automatically call wakeup handling and go to start */
  /* In case of CommonCAN, it might be necessary to call CanWakeUp() / CAN_WAKEUP() even if the hardware
     wakes up automatically to make sure all associated HW channels are awaken. */
  CAN_WAKEUP( channel ); /* PRQA S 0277 */ /* MD_Can_0277_negation */
  /* #30 call wakeup indication */
  APPL_CAN_WAKEUP( channel );
# else
  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
}
/* CODE CATEGORY 4 END */
#endif

/**********************************************************************************************************************
 *  CanLL_ModeTransition
 *********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST vuint8 mode, vuint8 busOffRecovery)
{
  vuint8 retVal = kCanFailed;

  switch(mode)
  {
    case kCanModeInit:
      if (canLL_canInitState[canHwChannel] == kCanLLStateInitStart)
      {
        retVal = CanLL_SetFlexCANToInitMode(CAN_HW_CHANNEL_CANPARA_ONLY);
      }
      else
      {
        retVal = CanLL_ExecuteSoftReset(CAN_HW_CHANNEL_CANPARA_ONLY);
      }
      break;

#if defined(C_ENABLE_SLEEP_WAKEUP)
    case kCanModeSleep:
      retVal = CanLL_Sleep(CAN_HW_CHANNEL_CANPARA_ONLY);
      break;

    case kCanModeWakeupStart:
      retVal = CanLL_WakeUp(CAN_HW_CHANNEL_CANPARA_ONLY);
      break;

#endif /* C_ENABLE_SLEEP_WAKEUP */

#if defined(C_ENABLE_STOP)
    case kCanModeStop:
      retVal = CanLL_Stop(CAN_HW_CHANNEL_CANPARA_ONLY);
      break;
#endif /* C_ENABLE_STOP */

    case kCanModeStart:
      retVal = CanLL_Start(CAN_HW_CHANNEL_CANPARA_ONLY);
      break;

    default:
      /* retVal is kCanFailed */
      break;
  }

  CAN_DUMMY_STATEMENT(busOffRecovery); /* PRQA S 3199 */ /* MD_Can_3199_dummy */
  return retVal;
}
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_STOP )
/**********************************************************************************************************************
 *  CanLL_StopReinit
 *********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_StopReinit(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint16          hwObjHandle; /* PRQA S 0781 */ /* MD_Can_0781 */
  CanObjectHandle  mailboxHandle; /* PRQA S 0781 */ /* MD_Can_0781 */
  CanObjectHandle  logTxObjHandle; /* PRQA S 0781 */ /* MD_Can_0781 */
//  tFlexCANPtr      pFlexCANLocal;
#if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION ) || defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
  CanTransmitHandle txHandle;
#endif
#if defined ( C_ENABLE_RX_BASICCAN_OBJECTS )
# if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
# else
  vuint8 fifoLoopCnt=0;
# endif
#endif

//  pFlexCANLocal = pFlexCAN(canHwChannel);
  /*pFlexCANLocal->iflag1 = CANSFR_SET;*/ /* clear pending Rx/Tx interrupts */
#if defined ( C_ENABLE_MB32TO63 )
  /*pFlexCANLocal->iflag2 = CANSFR_SET;*/ /* clear pending Rx/Tx interrupts */
#endif
#if defined ( C_ENABLE_MB64TO95 )
# if defined ( C_ENABLE_ASYM_MAILBOXES )
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64)
# endif
  {
    /*pFlexCANLocal->iflag3 = CANSFR_SET;*/ /* clear pending Rx/Tx interrupts */
  }
#endif
#if defined ( C_ENABLE_MB96TO127 )
  /*pFlexCANLocal->iflag4 = CANSFR_SET;*/ /* clear pending Rx/Tx interrupts */
#endif

  /*pFlexCANLocal->estat = (vuint32)kFlexCAN_STATUS_INT;*/ /* clear pending BusOff and error interrupts */

#if !defined( C_ENABLE_FLEXCAN_AUTO_RECOVERY )
  /*pFlexCANLocal->control1 &= (vuint32)(~kFlexCAN_BOFF_REC);*/ /* PRQA S 0277 */ /* MD_Can_0277_negation */
#endif

  for(mailboxHandle = CAN_HL_MB_TX_STARTINDEX(canHwChannel); mailboxHandle < CAN_HL_MB_TX_STOPINDEX(canHwChannel); mailboxHandle++)
  {
    logTxObjHandle = (CanObjectHandle)((vsintx)mailboxHandle + CAN_HL_TX_OFFSET_MB_TO_LOG(canHwChannel));
    hwObjHandle = Can_Mailbox[mailboxHandle].HwObjHandle;

#if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION ) || defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
    /* inform application, if a pending transmission is canceled */
    txHandle = canHandleCurTxObj[logTxObjHandle];
# if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
    if(txHandle < kCanNumberOfTxObjects)
    {
      APPLCANCANCELNOTIFICATION(channel, txHandle);
    }
# endif
# if defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
    if(txHandle == kCanBufferMsgTransmit)
    {
      APPLCANMSGCANCELNOTIFICATION(channel);
    }
# endif
#endif
    canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;

    /*LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = kTxCodeInactive;*/ /* set mailbox inactive */
  }

#if defined ( C_ENABLE_RX_FULLCAN_OBJECTS )
  for(mailboxHandle = CAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel); mailboxHandle < CAN_HL_MB_RX_FULL_STOPINDEX(canHwChannel); mailboxHandle++)
  {
    hwObjHandle = Can_Mailbox[mailboxHandle].HwObjHandle;
    /*LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) &= kRxCodeClear;*/ /* clear control register and do not change the ID type */
    /*LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) |= kRxCodeEmpty;*/ /* set mailbox ready for receive */
  }
#endif

#if defined ( C_ENABLE_RX_BASICCAN_OBJECTS )
# if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
for(mailboxHandle = CAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel); mailboxHandle < CAN_HL_MB_RX_BASIC_STOPINDEX(canHwChannel); mailboxHandle++)
{
  hwObjHandle = Can_Mailbox[mailboxHandle].HwObjHandle;
  /*LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) &= kRxCodeClear;*/ /* clear control register and do not change the ID type */
  /*LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) |= kRxCodeEmpty;*/ /* set mailbox ready for receive */

  /* shadow buffer */
  /*LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle + 1, control) &= kRxCodeClear;*/ /* clear control register and do not change the ID type */
  /*LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle + 1, control) |= kRxCodeEmpty;*/ /* set mailbox ready for receive */
}
# else
/*while(((pFlexCANLocal->iflag1 & kRxFIFO_NEWMSG) != 0) && (fifoLoopCnt < 6))
{
  pFlexCANLocal->iflag1 = (vuint32)kRxFIFO_NEWMSG;*/ /* clear RxFIFO pending interrupts */
  fifoLoopCnt = 0; /* 直接设置�，跳过循�*/
/*}*/
# endif
#endif
}
/* CODE CATEGORY 4 END */
#endif

#if defined( C_ENABLE_RX_QUEUE )
/**********************************************************************************************************************
 *  CanLL_RxQueueCopyMsgObj
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxQueueCopyMsgObj(CAN_CHANNEL_CANTYPE_FIRST CanRxQueueCopyInfoStructPtr localInfo)
{
  vuint8 idx;
  vuint8 objLen;
# if defined(C_ENABLE_CAN_FD_FULL)
  objLen = CanRxActualDLC(localInfo->src) + 8;
#else
  objLen = 16;
# endif
  for (idx = 0; idx < objLen; idx++)
  {
    ((CanChipDataPtr)(localInfo->dest))[idx] = ((CanChipDataPtr)localInfo->src->pChipMsgObj)[idx]; /* PRQA S 0310 */ /* MD_Can_0310 */
  }
  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_RxQueueSetRxInfoStructExtension
 *********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxQueueSetRxInfoStructExtension(CAN_CHANNEL_CANTYPE_FIRST CanRxQueueRxInfoStructPtr localInfo)
{
  /* #10 nothing to do here */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
  CAN_DUMMY_STATEMENT(localInfo); /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_RX_QUEUE */

#if defined( C_ENABLE_CAN_CAN_INTERRUPT_CONTROL ) && !defined( C_ENABLE_OSEK_CAN_INTCTRL ) && defined( C_HL_ENABLE_CAN_IRQ_DISABLE )
/**********************************************************************************************************************
 *  CanLL_CanInterruptDisable
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptDisable(CAN_HW_CHANNEL_CANTYPE_FIRST tCanLLCanIntOldPtr localInterruptOldFlagPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  //tFlexCANPtr pFlexcan = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */ /* PRQA S 781 */ /* MD_Can_Asr_0781 */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Disable RxTx interrupts */
  //CAN_DISABLE_RXTX_INTERRUPT_0TO31(localInterruptOldFlagPtr);
  //CAN_DISABLE_RXTX_INTERRUPT_32TO63(localInterruptOldFlagPtr);
#if defined (C_ENABLE_ASYM_MAILBOXES)
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64) /* PRQA S 3325 */ /* MD_Can_3325 */
#endif
  { /* PRQA S 3201 */ /* MD_Can_3201 */
    //CAN_DISABLE_RXTX_INTERRUPT_64TO95(localInterruptOldFlagPtr);
  }
 // CAN_DISABLE_RXTX_INTERRUPT_96TO127(localInterruptOldFlagPtr);

  /* #20 Disable BusOff interrupts */
  //HYT   CAN_DISABLE_BUSOFF_INTERRUPT(localInterruptOldFlagPtr);

  /* #30 Disable WakeUp interrupts */
  //CAN_DISABLE_WAKEUP_INTERRUPT(localInterruptOldFlagPtr);
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_CanInterruptRestore
 *********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptRestore(CAN_HW_CHANNEL_CANTYPE_FIRST tCanLLCanIntOld localInterruptOldFlag)
{
  /* ----- Local Variables ---------------------------------------------- */
  //tFlexCANPtr pFlexcan = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */ /* PRQA S 781 */ /* MD_Can_Asr_0781 */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Disable RxTx interrupts */
  //CAN_RESTORE_RXTX_INTERRUPT_0TO31(localInterruptOldFlag);
  //CAN_RESTORE_RXTX_INTERRUPT_32TO63(localInterruptOldFlag);
#if defined (C_ENABLE_ASYM_MAILBOXES)
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64)  /* PRQA S 3325 */ /* MD_Can_3325 */
#endif
  { /* PRQA S 3201 */ /* MD_Can_3201 */
    //CAN_RESTORE_RXTX_INTERRUPT_64TO95(localInterruptOldFlag);
  }
  //CAN_RESTORE_RXTX_INTERRUPT_96TO127(localInterruptOldFlag);

  /* #20 Restore BusOff interrupts */
  //HYT   CAN_RESTORE_BUSOFF_INTERRUPT(localInterruptOldFlag);

  /* #30 Restore WakeUp interrupts */
  //CAN_RESTORE_WAKEUP_INTERRUPT(localInterruptOldFlag);
}
#endif
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_SetFlexCANToInitMode
****************************************************************************/
/*!
 * \internal
 *  - #10 Check if FlexCAN is DISABLED or in a NON_BUSOFF state
 *    - #20 Check if FlexCAN is ENABLED
 *      - #30 Enter FREEZE mode (INIT mode) of FlexCAN
 *      - #40 Enter DISABLE mode of FlexCAN for clock selection
 *      - #50 Set FlexCAN clock source
 *      - #60 Leave DISABLE mode of FlexCAN
 * \endinternal
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_SetFlexCANToInitMode(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8 loopResult = 1; /* PRQA S 3197 */ /* MD_Can_3197_LL */
  vuint8 returnCode = kCanOk; /* PRQA S 3197 */ /* MD_Can_3197_LL */
  //tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  CanInitHandle initObject = lastInitObject[channel] + CAN_HL_INIT_OBJ_STARTINDEX(channel); /* PRQA S 781, 3689 */ /* MD_Can_0781, MD_Can_3689 */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if FlexCAN is DISABLED or in a NON_BUSOFF state */
  /*if (((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_DISABLE_MODE) == kFlexCAN_DISABLE_MODE)
    || ((CAN_READ_PROTECTED_REG_32BIT(pFlexCANLocal->estat) & kFlexCAN_FCS_BOFF) == 0))*/
  if (1) /* 始终进入此分支 */
  {
    /* #20 Check if FlexCAN is ENABLED */
    /*if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_DISABLE_ONLY_BITS) == 0)*/
    if (1) /* 始终进入此分支 */
    {
      /* #30 Enter FREEZE mode (INIT mode) of FlexCAN */
      /*CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);
      CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_HALT);
      if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) != kFlexCAN_FREEZE_MODE)*/
      if (1) /* 始终进入此分支 */
      {
        APPLCANTIMERSTART(kCanLoopEnterFreezeModeInit); /* start hw loop timer */
        do
        { /* wait for FRZACK */
          loopResult = APPLCANTIMERLOOP(kCanLoopEnterFreezeModeInit);
          /* 直接假设循环只执行一次 */
          loopResult = 0; /* 强制退出循环 */
        }while(/*((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) != kFlexCAN_FREEZE_MODE) &&*/ (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
        APPLCANTIMEREND(kCanLoopEnterFreezeModeInit); /* stop hw loop timer */
        if (loopResult == 0) /* PRQA S 3356,3359 */ /* MD_Can_13.7,MD_Can_13.7 */
        { /* PRQA S 3201 */ /* MD_Can_3201 */
          returnCode = kCanFailed; /* PRQA S 3198 */ /* MD_Can_3198 */
        }
      }

      /* #40 Enter DISABLE mode of FlexCAN for clock selection */
      /*CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_MDIS);*/ /* disable FlexCAN module before clock selection */
      /*if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) != kFlexCAN_LPM_ACK)*/
      if (1) /* 始终进入此分支 */
      {
        APPLCANTIMERSTART(kCanLoopEnterDisableModeInit); /* start hw loop timer */
        do{
          /* wait for FlexCAN is disabled */
          loopResult = APPLCANTIMERLOOP(kCanLoopEnterDisableModeInit);
          /* 直接假设循环只执行一次 */
          loopResult = 0; /* 强制退出循环 */
        }while(/*((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) != kFlexCAN_LPM_ACK) &&*/ (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
        APPLCANTIMEREND(kCanLoopEnterDisableModeInit);  /* stop hw loop timer */
        if (loopResult == 0) /* PRQA S 3356,3359 */ /* MD_Can_13.7,MD_Can_13.7 */
        { /* PRQA S 3201 */ /* MD_Can_3201 */
          returnCode = kCanFailed; /* PRQA S 3198 */ /* MD_Can_3198 */
        }
      }
    }

    /* #50 Set FlexCAN clock source */
    /*if((Can_GetControl1OfInitObject(initObject) & kFlexCAN_CLK_SRC) != 0)
    {
      CAN_WRITE_PROTECTED_REG_SET_32BIT(pFlexCANLocal->control1, kFlexCAN_CLK_SRC);
    }
    else
    {
      CAN_WRITE_PROTECTED_REG_RESET_32BIT(pFlexCANLocal->control1, kFlexCAN_CLK_SRC);
    }*/

    /* #60 Leave DISABLE mode of FlexCAN */
    /*CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS);*/ /* clear MDIS bit */
    /*if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) == kFlexCAN_LPM_ACK)*/
    if (1) /* 始终进入此分支 */
    {
      APPLCANTIMERSTART(kCanLoopLeaveDisableModeInit); /* start hw loop timer */
      do{
       /* wait for FlexCAN is enabled */
        loopResult = APPLCANTIMERLOOP(kCanLoopLeaveDisableModeInit);
        /* 直接假设循环只执行一次 */
        loopResult = 0; /* 强制退出循环 */
      }while(/*((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) == kFlexCAN_LPM_ACK) &&*/ (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
      APPLCANTIMEREND(kCanLoopLeaveDisableModeInit);  /* stop hw loop timer */
      if (loopResult == 0) /* PRQA S 3356,3359 */ /* MD_Can_13.7,MD_Can_13.7 */
      { /* PRQA S 3201 */ /* MD_Can_3201 */
        returnCode = kCanFailed; /* PRQA S 3198 */ /* MD_Can_3198 */
      }
    }
  }

  canLL_canInitState[canHwChannel] = CanLLStateInitSoftResetStart;
  returnCode = kCanRequested;

  return (returnCode);
}  /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_ExecuteSoftReset
****************************************************************************/
/*!
 * \internal
 *  - #10 Request start mode of FlexCAN
 *  - #20 Wait for soft reset confirmation from hardware
 *  - #30 Reset SUPV bit to grant access to CAN register (except MCR register) in User Mode
 * \endinternal
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_ExecuteSoftReset(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 returnCode = kCanOk; /* PRQA S 3197 */ /* MD_Can_3197_LL */
  //tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

  /* ----- Implementation ----------------------------------------------- */
  /* *********************************************************************** */
  /* Perform FlexCAN soft reset.                                             */
  /* Please note: the soft reset cannot be applied while clocks are          */
  /* shut down: low power mode or clocks are not enabled.                    */
  /* Please check clock settings if soft reset cannot be finalized.          */
  /* *********************************************************************** */
  if (canLL_canInitState[canHwChannel] == CanLLStateInitSoftResetStart)
  {
    /* #10 Execute SoftReset of FlexCAN */
    /*CAN_WRITE_PROTECTED_REG(pFlexCANLocal->canmcr, kFlexCAN_SOFT_RST);*/
    canLL_canInitState[canHwChannel] = CanLLStateInitSoftResetWaitEnd;
    returnCode = kCanRequested;
  }
  else if (canLL_canInitState[canHwChannel] == CanLLStateInitSoftResetWaitEnd)
  {
    /*if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_SOFT_RST) == kFlexCAN_SOFT_RST)*/
    if (0) /* 跳过等待 */
    {
      /* #20 Wait for soft reset confirmation from hardware */
      returnCode = kCanRequested;
    }
    else
    {
      /* #30 Reset SUPV bit to grant access to CAN register (except MCR register) in User Mode */
      /* set all CAN register except the MCR register in unrestricted memory space directly after soft reset */
      /*CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_SUPV);*/
      canLL_canInitState[canHwChannel] = kCanLLStateInitStart;
      returnCode = kCanOk;
    }
  }
  else
  {
    /* never reached */
    returnCode = kCanFailed;
  }
  canLL_canInitState[canHwChannel] = kCanLLStateInitStart;
  returnCode = kCanOk;

  return (returnCode);
}
/* CODE CATEGORY 4 END */

/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_Start
****************************************************************************/
/*!
 * \internal
 *  - #10 Request start mode of FlexCAN
 *  - #20 Wait for start mode is reached
 * \endinternal
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_Start(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 returnCode = kCanOk; /* PRQA S 3197 */ /* MD_Can_3197_LL */
  //tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

  /* ----- Implementation ----------------------------------------------- */
  /* *********************************************************************** */
  /* Request start mode of FlexCAN                                           */
  /* Wait for start mode is reached                     .                    */
  /* *********************************************************************** */
  if (canLL_canStartState[canHwChannel] == kCanLLStateStart)
  {
    /* #10 Request start mode of FlexCAN */
    /*CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_HALT);*/ /* clear HALT bit */
    /*CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);*/  /* clear FRZ bit */
    canLL_canStartState[canHwChannel] = kCanLLStateRequested;
    returnCode = kCanRequested;
  }
  else
  {
    /*  #20 Wait for start mode is reached */
    /*if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) != (vuint16)0)*/
    if (0) /* 跳过等待 */
    {
      returnCode = kCanRequested;
    }
    else
    {
      canLL_canStartState[canHwChannel] = kCanLLStateStart;
      returnCode = kCanOk;
    }
  }
  return (returnCode);
}
/* CODE CATEGORY 4 END */
#if defined(C_ENABLE_STOP)
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_Stop
****************************************************************************/
/*!
 * \internal
 *  - #10 Request stop mode of FlexCAN
 *  - #20 Wait for stop mode is reached
 * \endinternal
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_Stop(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 returnCode = kCanOk; /* PRQA S 3197 */ /* MD_Can_3197_LL */
  //tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

  /* ----- Implementation ----------------------------------------------- */
  /* *********************************************************************** */
  /* Request stop mode of FlexCAN                                           */
  /* Wait for stop mode is reached                     .                    */
  /* *********************************************************************** */
  if (canLL_canStopState[canHwChannel] == kCanLLStateStart)
  {
    /* #10 Request stop mode of FlexCAN */
    /*CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS);*/ /* clear MDIS bit */
    /*CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);*/  /* set FRZ bit */
    /*CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_HALT);*/ /* set HALT bit */
    canLL_canStopState[canHwChannel] = kCanLLStateRequested;
    returnCode = kCanRequested;
  }
  else
  {
    /*  #20 Wait for stop mode is reached */
    /*if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) != kFlexCAN_FREEZE_MODE)*/
    if (0) /* 跳过等待 */
    {
      returnCode = kCanRequested;
    }
    else
    {
      canLL_canStopState[canHwChannel] = kCanLLStateStart;
      returnCode = kCanOk;
    }
  }
  return (returnCode);
}
/* CODE CATEGORY 4 END */
#endif
#if defined(C_ENABLE_SLEEP_WAKEUP)
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_Sleep
****************************************************************************/
/*!
 * \internal
 *  - #10 Request sleep mode of FlexCAN
 *  - #20 Wait for sleep mode is reached
 * \endinternal
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_Sleep(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 returnCode = kCanOk; /* PRQA S 3197 */ /* MD_Can_3197_LL */

# if defined( C_ENABLE_FLEXCAN_STOP_MODE )
  returnCode = ApplCanEnterLowPowerMode(CanHwLogToPhys[canHwChannel]);
  canLL_canSleepState[canHwChannel] = kCanLLStateStart;
  returnCode = kCanOk;
# else
  //tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

  /* ----- Implementation ----------------------------------------------- */
  /* *********************************************************************** */
  /* Request sleep mode of FlexCAN                                           */
  /* Wait for sleep mode is reached                     .                    */
  /* *********************************************************************** */
  if (canLL_canSleepState[canHwChannel] == kCanLLStateStart)
  {
    /* #10 Request sleep mode of FlexCAN */
    /*CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_HALT);*/ /* clear HALT bit */
    /*CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);*/  /* clear FRZ bit */
    /*CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_MDIS);*/   /* request the DISABLE mode */
    canLL_canSleepState[canHwChannel] = kCanLLStateRequested;
    returnCode = kCanRequested;
  }
  else
  {
    /*  #20 Wait for sleep mode is reached */
    /*if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) != kFlexCAN_DISABLE_MODE)*/
    if (0) /* 跳过等待 */
    {
      returnCode = kCanRequested;
    }
    else
    {
      canLL_canSleepState[canHwChannel] = kCanLLStateStart;
      returnCode = kCanOk;
    }
  }
# endif
  return (returnCode);
}
/* CODE CATEGORY 4 END */

/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_WakeUp
****************************************************************************/
/*!
 * \internal
 *  - #10 Request start mode of FlexCAN
 *  - #20 Wait for start mode is reached
 * \endinternal
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_WakeUp(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 returnCode = kCanOk; /* PRQA S 3197 */ /* MD_Can_3197_LL */

# if defined( C_ENABLE_FLEXCAN_STOP_MODE )
  returnCode =  ApplCanLeaveLowPowerMode(CanHwLogToPhys[canHwChannel]);
  canLL_canWakeUpState[canHwChannel] = kCanLLStateStart;
  returnCode = kCanOk;
# else
  //tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

  /* ----- Implementation ----------------------------------------------- */
  /* *********************************************************************** */
  /* Request sleep mode of FlexCAN                                           */
  /* Wait for sleep mode is reached                     .                    */
  /* *********************************************************************** */
  if (canLL_canWakeUpState[canHwChannel] == kCanLLStateStart)
  {
    /* #10 Request start mode of FlexCAN */
    /*CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS);*/ /* quit DISABLE mode and switch into NORMAL mode */
    /*CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_HALT);*/ /* clear HALT bit */
    /*CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);*/  /* clear FRZ bit  */
    canLL_canWakeUpState[canHwChannel] = kCanLLStateRequested;
    returnCode = kCanRequested;
  }
  else
  {
    /*  #20 Wait for start mode is reached */
    /*if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) != (vuint16)0)*/
    if (0) /* 跳过等待 */
    {
      returnCode = kCanRequested;
    }
    else
    {
      canLL_canWakeUpState[canHwChannel] = kCanLLStateStart;
      returnCode = kCanOk;
    }
  }
# endif
  return (returnCode);
}
/* CODE CATEGORY 4 END */
#endif
#if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT )
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_HandleBusOff
****************************************************************************/
/*!
 * \internal
 *  - #10 Call CanInit and set BusOff flag to FALSE if BusOff recovery was successful
 * \endinternal
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_HandleBusOff(CAN_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call CanInit and set BusOff flag to FALSE if BusOff recovery was successful */
  if (!(CanLL_HwIsBusOff(channel)))
  {
    Can_SetIsBusOff(channel,FALSE);
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
    CanInit(channel, Can_GetLastInitObject(channel)); /* SBSW_CAN_HL18 */
#   else
    CanInit(Can_GetLastInitObject(channel)); /* SBSW_CAN_HL18 */
# endif
  }
}

/****************************************************************************
| NAME:             CanLL_HandleStartProcess
****************************************************************************/
/*!
 * \internal
 *  - #10 Check if START mode was not yet requested
 *    - #20 Request START mode
 *  - Else
 *    - #30 Set result to OK if START mode was reached successfully
 * \endinternal
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanLL_HandleStartProcess(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType result = kCanFailed;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if START mode was not yet requested */
  if (!Can_IsStartModeRequested(canHwChannel))
  {
    /* #20 Request START mode */
    /* request NORMAL mode - considered as CanStart mode */
    /*CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS);*/ /* clear MDIS bit */
    /*CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_HALT);*/ /* clear HALT bit */
    /*CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);*/  /* clear FRZ bit  */

    /* the transition CanStop - CanStart does also leave a potential BusOff state */
# if !defined( C_ENABLE_FLEXCAN_AUTO_RECOVERY )
    /*pFlexCANLocal->control1 |= kFlexCAN_BOFF_REC;*/
# endif

    Can_SetStartModeRequested(canHwChannel, TRUE);
  }
  else
  {
    /* #30 Set result to OK if START mode was reached successfully */
    /* check if NORMAL mode is reached - considered as CanStart mode */
    /*if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) == kFlexCAN_NORMAL_MODE)*/
    if (1) /* 始终进入此分*/
    {
      result = kCanOk;
      Can_SetStartModeRequested(canHwChannel, FALSE);
    }
  }

  return result;
}
/* CODE CATEGORY 4 END */
#endif

#if defined ( V_CPU_S32 )
# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanLL_ComputeMailboxInterrupt
****************************************************************************/
/*!
 * \internal
 *  - #10 For all active pending interrupts
 *    - #20 Compute index of active interrupt
 *    - #30 Call computation of interrupt type
 * \endinternal
 */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanLL_ComputeMailboxInterrupt(CAN_HW_CHANNEL_CANTYPE_FIRST vuint32 iFlags, vuint32 iMask, CanObjectHandle startIndex)
{
  vuint32 activeInterrupts;
  CanObjectHandle index;

  activeInterrupts = iFlags & iMask;
  index = startIndex;
  /* #10 For all active pending interrupts */
  while(activeInterrupts != 0)
  {
    /* #20 Compute index of active interrupt */
    while((activeInterrupts & (vuint32)0xFF) == 0)
    {
      activeInterrupts >>= 8;
      index += (CanObjectHandle)8;
    }
    if((activeInterrupts & (vuint32)0x0F) == 0)
    {
      activeInterrupts >>= 4;
      index += (CanObjectHandle)4;
    }
    while((activeInterrupts & (vuint32)0x01) == 0)
    {
      activeInterrupts >>= 1;
      index++;
    }

    /* #30 Call computation of interrupt type */
    CanLL_ComputeInterruptType(CAN_HW_CHANNEL_CANPARA_FIRST index);

    index++;
    activeInterrupts = (iFlags & iMask) >> (index-startIndex);
  }
}
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanLL_ComputeInterruptType
****************************************************************************/
/*!
 * \internal
 *  - #10 Check if pending interrupt is caused due to a FullCAN reception:
 *     if true call internal indication function.
 *  - #20 Check if pending interrupt is caused due to a BasicCAN reception:
 *     if true call internal indication function.
 *  - #30 Check if pending interrupt is caused due to a successful transmission:
 *     if true call internal indication function.
 * \endinternal
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ComputeInterruptType(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle index)
{
  CanObjectHandle mailboxHandle; /* PRQA S 0781 */ /* MD_Can_0781 */

  mailboxHandle = Can_HwObjToMailboxIndirection[CAN_HL_MB_INDIRECTION_STARTINDEX(canHwChannel) + index];
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
# if !defined( C_ENABLE_RX_FULLCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  /* #10 Check if pending interrupt is caused due to a FullCAN reception:
      if true call internal indication function. */
#  if defined (C_SINGLE_RECEIVE_CHANNEL)
#   if (kCanMailboxRxFullStartIndex == 0)
  if((mailboxHandle < CAN_HL_MB_RX_FULL_STOPINDEX(canHwChannel)))
#   else
  if((mailboxHandle >= CAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel)) && (mailboxHandle < CAN_HL_MB_RX_FULL_STOPINDEX(canHwChannel)))
#   endif
#  else
  if((mailboxHandle >= CAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel)) && (mailboxHandle < CAN_HL_MB_RX_FULL_STOPINDEX(canHwChannel)))
#  endif
  {
//	  CanFullCanMsgReceived(0, (stCanDrv_RxFrameType *)&RFIDx(0u,0u));
  }
# endif
#endif

#if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
# if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
#  if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  /* #20 Check if pending interrupt is caused due to a BasicCAN reception:
      if true call internal indication function. */
#   if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
  if((mailboxHandle >= CAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel)) && (mailboxHandle < CAN_HL_MB_RX_BASIC_STOPINDEX(canHwChannel)))
#   else
  if(mailboxHandle < CAN_HL_MB_RX_BASIC_STOPINDEX(canHwChannel))
#   endif
  {
    CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST mailboxHandle, index);
  }
#  endif
# endif
#endif

#if !defined( C_ENABLE_TX_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  /* #30 Check if pending interrupt is caused due to a successful transmission:
      if true call internal indication function. */
  if((mailboxHandle >= CAN_HL_MB_TX_STARTINDEX(canHwChannel)) && (mailboxHandle < CAN_HL_MB_TX_STOPINDEX(canHwChannel)))
  {
    {
      CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST mailboxHandle, index);
    }
  }
#endif
  CAN_DUMMY_STATEMENT(mailboxHandle); /* PRQA S 3199 */ /* MD_Can_3199_dummy */
}
/* CODE CATEGORY 1 END */
# endif
#endif
/* PRQA  L:QAC_Can_3673 */


