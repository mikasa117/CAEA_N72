/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Hll Erzeugungsgangnummer: 1 */

/* STARTSINGLE_OF_MULTIPLE */

#ifndef  CAN_HL_H
# define  CAN_HL_H

# if defined( C_KOMMENTAR_VECTOR )
/* ***************************************************************************
 |
 |                  SINGLE SOURCE fuer interne Verwendung
 |
 |    *****          N I C H T   A U S L I E F E R N       *****
 |
 |
 |************************************************************************** */
# endif

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
 *  Compiler: see module file
 *
 *  \file     CAN_DEF.H
 *  \brief    Interface header file of the CAN-Driver
 *  \details  Declaration of functions, variables, and constants as user API.
 *
 *********************************************************************************************************************/

/* ***************************************************************************
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ------------------------------------
| Ht           Heike Honert              Vector Informatik GmbH
| Bir          Holger Birke              Vector Informatik GmbH
| Rse          Robert Schelkle           Vector Informatik GmbH
| Rli          Roman Linder              Vector Informatik GmbH
| Yoe          Yacine Ould Boukhitine    Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver       Author  Description
| ---------  ---  ------ -- --------------------------------------------------
| 2012-01-09  1.00.00  Rse    - ESCAN00056163: Initial version: Hll - Flexcan3 - Imx6 - QCC - High-End - QNX
| 2012-09-20  1.01.00  Rse    - ESCAN00062414: Support workaround for erratum ERR005829
| 2013-01-30  1.02.00  Rse    - ESCAN00065347: Support platform MPC5700
|                             - ESCAN00064665: CANbedded only: CAN messages will not be sent any more
|                             - ESCAN00066667: Support workaround for erratum e5769
|                             - ESCAN00067035: Inconsistent combination of receive handle and receive information (id, dlc, data) is indicated to upper layer
| 2013-05-21  1.03.00  Rse    - ESCAN00067478: Support FlexCAN2 derivatives for RxFifo usage
|                             - ESCAN00067660: Support the feature Mirror Mode
| 2013-07-22  1.04.00  Rse    - ESCAN00069229: Support CAN message retransmit feature for FBL driver
|                             - ESCAN00070121: Support Vybrid with FlexCAN3
| 2013-11-21  1.05.00  Rse    - ESCAN00072129: ASR4 only: change BusOff behavior to ensure recovery time of 128x11 recessive bits
|                             - ESCAN00072322: AR4-328: Predefined Runtime Measurement Points
| 2013-12-09  1.06.00  Rse    - ESCAN00072515: AutoSar only: Can_SetControllerMode(controller, CAN_T_STOP) returns CAN_OK instead of CAN_NOT_OK
|                             - ESCAN00072597: CANbedded only: Retransmit does not work if more than 22 RxFullCAN objects are used
| 2014-01-08  1.07.00  Rse    - ESCAN00072828: CANbedded only: Compiler error: identifier "canCanInterruptCounter" is undefined
|                             - ESCAN00072863: Support Cancel in Hardware with Transmission Abort feature
|                             - ESCAN00072869: Support new interface for Bus Mirroring
| 2014-01-30  1.07.01  Rse    - ESCAN00073299: Parity check only available for Vybrid and MPC5700 derivatives
| 2014-02-06  1.07.02  Rse    - Some minor MISRA improvements
|                      Rse    - ESCAN00073889: CANbedded only: Compiler error: struct has unknown field
| 2014-03-24  1.07.03  Rse    - ESCAN00074424: Indication function is called twice for the reception of one BasicCAN message
| 2014-04-16  1.08.00  Rse    - ESCAN00075110: BusOff notification is called twice for one single BusOff event (FlexCAN2)
|                             - ESCAN00075955: Remove obsolete workaround implementation for e5769
|                             - ESCAN00075964: Delete unnecessary interrupt locks
|                             - ESCAN00075507: IAR Compiler warning: the order of volatile accesses is undefined
| 2014-06-24  1.09.00  Rse    - ESCAN00076588: CAN clock settings are invalid after reinitialization, error frames occur continuously on the bus
|                             - ESCAN00076653: Implement proper mode switch to init (FREEZE) mode in CAN controller initialization process
|                             - ESCAN00076657: MAXMB value is obsolete
|                             - ESCAN00077049: CANbedded only: Support Tx FullCAN Send Delay (External PIA)
|                             - ESCAN00077083: CANbedded only: LowLevel Message is not transmitted
|                             - ESCAN00077485: OS Exception when CAN driver is handled in User Mode
| 2014-08-13  1.10.00  Rse    - ESCAN00077825: Support derivative MPC5748G CUT2
| 2014-11-10  1.10.01  Rse    - ESCAN00079385: Compiler warning: argument of type "volatile uint32 *" is incompatible with parameter of type "volatile uint16 *"
| 2014-11-27  2.00.00  Rse    - ESCAN00078072: Support full functionality for CAN-FD (Mode 2)
|                             - ESCAN00079900: CANbedded only: Extended ID message with dominant SRR-Bit does not receive
|                             - ESCAN00079901: Support ComStackLib tables for ASR403 R11
|                             - ESCAN00079494: Add loop checks for mode switching in CAN Controller initialization process
| 2015-01-21  2.00.01  Rse    - ESCAN00080716: Standard CAN message is sent as CAN-FD message with baudrate switch
| 2015-04-09  2.00.02  Was    - ESCAN00082335: Update to Core 5.00.02, R11 (Vybrid)
| 2015-05-02  2.01.00  Rse    - ESCAN00082800: Support CANbedded compatibility
| 2015-09-02  2.02.00  Zam    - ESCAN00084930: Support Extended CAN RAM Check feature
| 2015-10-14  2.03.00  Pl     - ESCAN00085860: Support S32K with FlexCAN3
| 2015-12-03  3.00.00  Rse    - ESCAN00086974: Support R14 and process 3.0
| 2016-03-17  3.01.00  Rse    - ESCAN00088969: Support Extended RAM check for MSR403
| 2016-05-30  3.01.01  Rse    - ESCAN00090210: Compiler error: parse error near ';'
| 2016-06-20  3.01.02  Rse    - Update HL-ASR 5.04.01 for issue 89754
| 2016-08-03  3.01.03  Rse    - ESCAN00091088: Callback that indicates corrupt CAN Controller is called erroneously
| 2016-08-25  3.02.00  Rse    - ESCAN00091626: Support R14 for Arm32 platforms
|                             - ESCAN00092139: Support ISO CAN-FD
|                             - ESCAN00092218: Support possibility to use a non-CAN-FD baudrate on a CAN-FD channel
|                             - ESCAN00092333: Support asymmetric mailboxes
| 2016-10-26  3.02.01  Rse    - ESCAN00092531: Linker Error: undefined symbol found 'Can_GetCanNumberOfMaxMailboxes'
| 2016-12-12  3.02.02  Rli    - ESCAN00093255: CAN FD FULL support for Little Endian Architectures
| 2017-03-30  3.02.03  Rli    - ESCAN00094552: Compiler error: identifier Controller not declared
| 2017-04-11  4.00.00  Rse    - ESCAN00094734: Beta support of RI2.0
| 2017-11-30  4.00.01  Yoe    - ESCAN00097612: Beta support of RI2.0 for Arm32Flexcan3
| 2018-02-26  4.01.00  Rli    - ESCAN00098508: Final support of RI2.0 for Arm32Flexcan3
| 2018-03-07  4.01.01  Rli    - ESCAN00098514: add MISRA relevant changes
|************************************************************************** */
/* ***************************************************************************
|
|    ************    Version and change information of      **********
|    ************    high level part only                   **********
|
|    Please find the version number of the whole module in the previous
|    file header.
|
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ------------------------------------
| Ht           Heike Honert              Vector Informatik GmbH
| Pl           Georg Pfluegel            Vector Informatik GmbH
| Vg           Frank Voorburg            Vector CANtech, Inc.
| An           Ahmad Nasser              Vector CANtech, Inc.
| Ml           Patrick Markl             Vector Informatik GmbH
| Seu          Eugen Stripling           Vector Informatik GmbH
| Uce          Cengiz Uenver             Vector Informatik GmbH
| Tkr          Torsten Kercher           Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------ -----------------------------------------------------
| ---------  ---  ------ -- --------------------------------------------------
| 24-Jan-01  0.02      Ht     - derived from C16x V3.3
| 18-Apr-01  1.00      Pl     - adaption for ARM7 TDMI
| 26-Apr-01  1.01      Ht     - adaption to LI 1.2
|                             - changed from code doupling to indexed
| 19-Jun-01            Ht     - define of CanSetActive/Passive changed
| 31-Oct-01  1.02      Ht     - support hash search
|                      Vg     - adaption for PowerPC
| 07-Nov-01  1.03      Ht     - remove some comments
| 12-Nov-01  1.04      Fz     - no changes
| 02-Jan-02  1.05      Ht     - ESCAN00002009: support of polling mode improved
| 12-Feb-02  1.06      Pl     - ESCAN00002279: - now it is possible to use only the error-task without the tx-task
|                                              - support of the makro  REENTRANT
|                                              - support of the makro C_HL_ENABLE_RX_INFO_STRUCT_PTR
|                                              - For better performance for the T89C51C there is a switch-case
|                                                instruction for direct call of the PreTransmitfunction
|                                              - insert Prototyp for CanErrorTask
| 18-Mai-02  1.07       Ht    - support Hash search with FullCAN controller
|                             - ESCAN00002707: Reception could went wrong if IL and Hash Search
|                             - ESCAN00002893: adaption to LI 1.3
| 29-Mai-02  1.08       Ht    - ESCAN00003028: Transmission could fail in Polling mode
|                             - ESCAN00003082: call Can_LL_TxEnd() in CanMsgTransmit()
|                             - ESCAN00003083: Hash search with extended ID
|                             - ESCAN00003084: Support C_COMP_METROWERKS_PPC
|                             - ESCAN00002164: Temporary vaiable "i" not defined in function CanBasicCanMsgReceived
|                             - ESCAN00003085: support C_HL_ENABLE_IDTYPE_IN_ID
| 25-Jun     1.08.01    Vg    - Declared localInterruptOldFlag in CanRxTask()
|                             - Corrected call to CanWakeUp for multichannel
| 11-Jul-02  1.08.02    Ht    - ESCAN00003203: Hash Search routine does not work will with extended IDs
|                             - ESCAN00003205: Support of ranges could went wrong on some platforms
| 08-Aug-02  1.08.03    Ht    - ESCAN00003447: Transmission without databuffer and pretransmit-function
| 08-Aug-02  1.08.04    An      no changes
| 09-Sep-02  1.09       Ht    - ESCAN00003837: code optimication with KernelBuilder
| 2002-12-12 1.10       Ht    -                support Dummy functions for indirect function call
| 2003-02-04 1.11       Ht    -                optimization for polling mode
|                       Fz    - ESCAN00004600: Flags changed for V850 aFCAN only
| 2003-03-19 1.12       Ht    - ESCAN00005153: Wrong number of Indication bytes for V850 aFCAN only
|                             - ESCAN00005152: optimization of CanInit() in case of Direct Tx Objects
|                             - ESCAN00005143: CompilerWarning about function prototype
|                                              CanHL_ReceivedRxHandle() and CanHL_IndRxHandle
|                             - ESCAN00005130: Wrong result of Heash Search on second or higher channel
| 2003-05-12 1.13       Ht    - ESCAN00005624: support CantxMsgDestroyed for multichannel system
|                             - ESCAN00005209: Support confirmation and indication flags for EasyCAN4
|                             - ESCAN00004721: Change data type of Handle in CanRxInfoStruct
| 2003-06-18 1.20       Ht    - ESCAN00005908: support features of RI1.4
|                             - Support FJ16LX-Workaround for multichannel system
|                             - ESCAN00005671: Dynamic ID in extended ID system could fail
|                             - ESCAN00005863: Notification about cancelation failes in case of CanTxMsgDestroyed
| 2003-06-30 1.21       Ht   - ESCAN00006117: Common Confirmation Function: Write access to wrong memory location
|                            - ESCAN00006008: CanCanInterruptDisable in case of polling
|                            - ESCAN00006118: Optimization for Mixed ID and ID type in Own Register or ID type in ID Register
|                            - ESCAN00006063: Undesirable hardware dependency for
|                                             CAN_HL (CanLL_RxBasicTxIdReceived)
| 2003-09-10 1.22       Ht   - ESCAN00006853: Support V_MEMROM0
|                            - ESCAN00006854: suppress some Compiler warnings
|                            - ESCAN00006856: support CanTask if only Wakeup in polling mode
|                            - ESCAN00006857: variable newDLC not defined in case of Variable DataLen
| 2003-10-14 1.23       Ht   - ESCAN00006858: support BrsTime for internal runtime measurement
|                            - ESCAN00006860: support Conditional Msg Receive
|                            - ESCAN00006865: support "Cancel in HW" with CanTask
|                            - ESCAN00006866: support Direct Tx Objects
|                            - ESCAN00007109: support new memory qualifier for const data and pointer to const
| 2004-01-05 1.24       Ml   - ESCAN00007206: no changes
|                       Ml   - ESCAN00007254: several changes
| 2004-02-06 1.25       Ml   - ESCAN00007281: no changes
|                       Ml   - removed compiler warnings
| 2004-02-21 1.26       Ml   - ESCAN00007670: CAN RAM check
|                       Ml   - ESCAN00007671: no changes
|                       Ml   - ESCAN00007764: no changes
|                       Ml   - ESCAN00007681: no changes
|                       Ml   - ESCAN00007272: no changes
|                       Ml   - ESCAN00008064: encapsulated CanRxHashId in case of array dimension == 0
| 2004-04-16 1.27       Ml   - ESCAN00008204: Optimized CanRxActualId for different ID modes
|                       Ml   - ESCAN00008160: encapsulated functions declared by tool in case of multichannel
|                       Ml   - ESCAN00008266: changed name of parameter of function CanTxGetActHandle
|                       Fz   - ESCAN00008272: Compiler error due to missing array canPollingTaskActive
| 2004-05-10 1.28       Fz   - ESCAN00008328: Compiler error if cancel in hardware is active
|                            - ESCAN00008363: Hole closed when TX in interrupt and cancel in HW is used
|                            - ESCAN00008365: Switch C_ENABLE_APPLCANPREWAKEUP_FCT added
|                            - ESCAN00008391: Wrong parameter macro used in call of
|                                             CanLL_WakeUpHandling
| 2004-05-24 1.29       Ht   - ESCAN00008441: Interrupt not restored in case of internal error if TX Polling is used
| 2004-09-21 1.30       Ht   - ESCAN00008824: check of reference implementation version added
|                            - ESCAN00008825: No call of ApplCanMsgCancelNotification during CanInit()
|                            - ESCAN00008826: Support asssertions for "Conditional Message Received"
|                       Ml   - ESCAN00008752: Added function qualifier macros
|                       Ht   - ESCAN00008823: compiler error due to array size 0
|                            - ESCAN00008977: label without instructions
|                            - ESCAN00009485: Message via Normal Tx Object will not be sent
|                            - ESCAN00009497: support of CommonCAN and RX queue added
| 2004-09-28 1.31       Ht   - ESCAN00009703: unresolved functions CAN_POLLING_IRQ_DISABLE/RESTORE()
| 2004-11-25 1.32       Ht   - move fix for ESCAN00007671 to CAN-LL of DrvCan_MpcToucanHll
|                            - ESCAN00010350: Dynamic Tx messages are send always with Std. ID
|                            - ESCAN00010388: ApplCanMsgConfirmed will only be called if realy transmitted
|                       Ml   - ESCAN00009931: The HardwareLoopCheck should have a channelparameter in multichannel systems.
|                            - ESCAN00010093: lint warning: function type inconsistent "CanCheckMemory"
|                        Ht  - ESCAN00010811: remove Misra and compiler warnings
|                            - ESCAN00010812: support Multi ECU
|                            - ESCAN00010526: CAN interrupts will be disabled accidently
|                            - ESCAN00010584: ECU may crash or behave strange with Rx queue active
| 2005-01-20 1.33       Ht   - ESCAN00010877: ApplCanMsgTransmitConf() is called erronemous
| 2005-03-03 1.34       Ht   - ESCAN00011139: Improvement/Correction of C_ENABLE_MULTI_ECU_CONFIG
|                            - ESCAN00011511: avoid PC-Lint warnings
|                            - ESCAN00011512: copy DLC in case of variable Rx Datalen
|                            - ESCAN00010847: warning due to missing brakets in can_par.c at CanChannelObject
| 2005-05-23 1.35       Ht   - ESCAN00012445: compiler error "V_MEMROMO undefined"in case of multi ECU
|                            - ESCAN00012350: Compiler Error "Illegal token channel"
| 2005-07-06 1.36       Ht   - ESCAN00012153: Compile Error: missing declaration of variable i
|                            - ESCAN00012460: Confirmation of LowLevel message will run into assertion (C_ENABLE_MULTI_ECU_PHYS enabled)
|                            - support Testpoints for CanTestKit
| 2005-07-14 1.37       Ht   - ESCAN00012892: compile error due to missing logTxObjHandle
|                            - ESCAN00012998: Compile Error: missing declaration of txHandle in CanInit()
|                            - support Testpoints for CanTestKit for FullCAN controller
| 2005-10-05 1.38       Ht   - ESCAN00013597: Linker error: Undefined symbol 'CanHL_IndRxHandle'
| 2005-11-10 1.39.00    Ht   - ESCAN00014331: Compile error due to missing 'else' in function CanTransmit
| 2005-04-26 2.00.00    Ht   - ESCAN00016698: support RI1.5
|                            - ESCAN00014770: Cosmic compiler reports truncating assignement
|                            - ESCAN00016191: Compiler warning about unused variable in CanTxTask
| 2007-01-23 2.01.00    Ht   - ESCAN00017279: Usage of SingleGlobalInterruptDisable lead to assertion in OSEK
|                            - ESCAN00017148: Compile error in higher layer due to missing declaration of CanTxMsgHandleToChannel
| 2007-03-14 2.02.00   Ht    - ESCAN00019825: error directives added and misra changes
|                            - ESCAN00019827: adaption to never version of VStdLib.
|                            - ESCAN00019619: V_CALLBACK_1 and V_CALLBACK_2 not defined
|                            - ESCAN00019953: Handling of FullCAN reception in interrupt instead of polling or vice versa.
|                            - ESCAN00019958: CanDynTxObjSetId() or CanDynTxObjSetExtId() will run into assertion
| 2007-03-26 2.03.00  Ht     - ESCAN00019988: Compile warnings in can_drv.c
|                            - ESCAN00018831: polling mode: function prototype without function implemenation (CanRxFullCANTask + CanRxBasicCANTask)
| 2007-04-20 2.04.00  dH     - ESCAN00020299: user assertion fired irregularly due to unknown parameter (in case of CommonCAN)
| 2007-05-02 2.05.00  Ht     - ESCAN00021069: Handling of canStatus improved, usage of preprocessor defines unified
|                            - ESCAN00021070: support relocation of HW objects in case of Multiple configuration
|                            - ESCAN00021166: Compiler Warnings: canHwChannel & canReturnCode not used in CanGetStatus
|                            - ESCAN00021223: CanCanInterruptDisabled called during Sleepmode in CanWakeupTask
|                            - ESCAN00022048: Parameter of ApplCancorruptMailbox is hardware channel instead of logical channel - Error directive added
| 2007-11-12 2.06.00  Ht     - ESCAN00023188: support CAN Controller specific polling sequence for BasicCAN objects
|                            - ESCAN00023208: Compile issue about undefined variable kCanTxQueuePadBits in the CAN driver in Bit based Tx queue
| 2008-10-20 2.07.00  Ht     - ESCAN00023010: support disabled mailboxes in case of extended RAM check
|                            - ESCAN00025706: provide C_SUPPORTS_MULTI_ECU_PHYS
|                            - ESCAN00026120: compiler warnings found on DrvCan_V85xAfcanHll RI 1.5     ##Ht: reviewed 2008-09-03
|                            - ESCAN00026322: ApplCanMsgNotMatched not called in special configuration
|                            - ESCAN00026413: Add possibility to reject remote frames received by FullCAN message objects
|                            - ESCAN00028758: CAN HL must support QNX
|                            - ESCAN00029788: CommonCAN for Driver which support only one Tx object improved (CanInit()).
|                            - ESCAN00029889: Compiler warning about uninitialized variable canHwChannel in CanCanInterruptDisable/Restore()
|                            - ESCAN00029891: Compiler warning: variable "rxHandle" was set but never used
|                            - ESCAN00029929: Support Extended ID Masking for Tx Fullcan messages
|                            - ESCAN00030371: Improvements (assertions, misra)
|                            - ESCAN00027931: Wrong check of "queueBitPos" size
| 2009-04-08 2.08.00  Ht     - ESCAN00034492: no automatic remove of CanCanInterruptDisable/Restore
|                            - ESCAN00031816: CANRANGExIDTYPE can be removed and direct expression used
|                            - ESCAN00032027: CanMsgTransmit shall support tCanMsgTransmitStruct pointer accesses to far RAM
|                            - ESCAN00034488: Postfix for unsigned const in perprocessor directives are not supported by all Compiler (ARM-Compiler 1.2)
| 2009-06-04 2.08.01  Ht     - ESCAN00035426: Compiler warning about truncation in CanGetStatus removed
| 2009-10-21 2.09.00  Ht     - ESCAN00036258: Compiler warning about "CanHL_ReceivedRxHandle" was declared but never referenced
|                            - ESCAN00038642: Support reentrant functions for compiler with own keyword
|                            - ESCAN00038645: support new switch C_ENABLE_UPDATE_BASE_ADDRESS
| 2010-02-01 2.10.00  Ht     - ESCAN00036260: Support configuartion without static Tx messages and only one channel (remove compiler warning)
|                            - ESCAN00040478: Handle update of virtual CanBaseAdress in accordance to QNX documentation
|                            - ESCAN00039235: Compiler Warning: Narrowing or Signed-to-Unsigned type conversion
| 2010-07-22 2.11.00  Ht     - ESCAN00044221: support Retransmit functionality for FBL
|                            - ESCAN00044222: internal changes: improve readability and
|                                             change CAN_CAN_INTERRUPT_... macros to avoid preprocessor errors for some compiler
|                            - ESCAN00044174: TxBitQueue only - compiler warning occurs about: condition is always true
| 2010-10-22 2.12.00  Ht - ESCAN00046326: support  C_COMP_KEIL_XC800 and  C_COMP_TI_TMS320
| 2011-05-17 2.13.00  Ht - ESCAN00048965: Add assertion check txMsgStruct for NULL-Pointer value in CanMsgTransmit() API
|                        - ESCAN00050948: support retransmit macro if kCanHwTxStartIndex != 0.
| 2012-04-23 2.14.00  Ht - ESCAN00053779: Linker error: CanBaseAddressRequest() and CanBaseAddressActivate() are not available
|                        - ESCAN00056617: remove brackets in macro CanInterruptDisable/Restore()
|                        - ESCAN00058520: support CommonCAN in combination with RAM check
|                        - ESCAN00058521: support C_COMP_KEIL_SLC8051_CCAN
|                        - ESCAN00058522: some  message will be not be received via BasicCAN if index search and multichannel are active
|                        - ESCAN00058104: compiler warning occurs about: comparison between signed and unsigned
| 2012-04-23 2.14.01  Ht - ESCAN00058636: some BasicCAN messages will not be received with linear search
| 2012-05-11 2.15.00  Seu - ESCAN00058891: Add switch C_HL_ENABLE_PRETRANSMIT_SWITCH_COMMENT
| 2012-07-02 2.15.01  Ht  - ESCAN00058586: Compiler warning: comparison is always true due to limited range of data type
|                         - ESCAN00059562: Compile error: Size of array CanRxMsgIndirection is zero if index search and no Rx FullCANs are used
|                         - ESCAN00059736: Compiler warning: pointless comparison of unsigned integer with zero
| 2012-10-30 2.15.02  Ht  - ESCAN00061829: Compiler error:  about(CAN_HL_HW_RX_BASIC/FULL_STARTINDEX(canHwChannel) == 0)
|                         - ESCAN00057831: Compiler warning: "canCanInterruptOldStatus" was declared but never referenced
|                         - ESCAN00057832: Compiler warning: "canCanInterruptCounter" was set but never referenced
|                         - ESCAN00062667: Verify Identity during CanOnline and Misra improvement
| 2013-05-27 2.16.00  Ht  - ESCAN00067627: support more than 255 HW objects
| 2014-04-08 2.17.00  Ht  - ESCAN00074874: internal change: support possibility to reject transmit request before request in HW has to be set
| 2014-07-22 2.18.00  Uce - ESCAN00076820: added Misra deviation comments
|                     Ht  - ESCAN00076413: remove compiler warning - comparison is always true due to limited range of data type
| 2015-02-12 2.19.00  Ht  - ESCAN00015288: support dynamic Rx objects
| 2015-08-25 2.20.00  Ht  - ESCAN00081628: reception of wrong dynamic Rx message notified or endless loop in basicCAN reception handling
|                         - ESCAN00085313: support extended ID masking for dynamic Rx messages via Rx BasicCAN object
| 2016-03-07 2.21.00  Ht  - ESCAN00089020: support compatibility macros CAN_HL_INFO_..
|                         - ESCAN00089023: Dynamic Rx objects can only be initialized during CanInitPowerOn()
| 2016-11-03 3.00.00  Tkr - ESCAN00094214: Beta support of RI2.0 and CAN-FD
| 2017-11-16 3.01.00  Tkr - ESCAN00097695: Final support of RI2.0 and CAN-FD
|
|    ************    Version and change information of      **********
|    ************    high level part only                   **********
|
|    Please find the version number of the whole module in the previous
|    File header.
|
|************************************************************************** */

/* PRQA S 0857 QAC_Can_0857 */ /* MD_Can_0857 */
/* PRQA S 0828 QAC_Can_0828 */ /* MD_Can_0828 */
/* PRQA S 3453 QAC_Can_3453 */ /* MD_Can_3453 */
/* PRQA S 0850 QAC_Can_0850 */ /* MD_Can_0850 */

/* *********************************************************************** */
/* Version                  (abcd: Main version ab Sub Version cd )        */
/* *********************************************************************** */
/* ##V_CFG_MANAGEMENT ##CQProject : DrvCan_ImxFlexcan3Hll CQComponent : Implementation */
#define DRVCAN_IMXFLEXCAN3HLL_VERSION 0x0401u
#define DRVCAN_IMXFLEXCAN3HLL_RELEASE_VERSION 0x01u

/* ##V_CFG_MANAGEMENT ##CQProject : DrvCan__coreHll CQComponent : Implementation */
# define DRVCAN__COREHLL_VERSION                 0x0301
# define DRVCAN__COREHLL_RELEASE_VERSION         0x00
#define DRVCAN__HLLTXQUEUEBIT_VERSION 0x0106
#define DRVCAN__HLLTXQUEUEBIT_RELEASE_VERSION 0x05

/* *********************************************************************** */
/* Include                                                                 */
/* *********************************************************************** */

# include "v_def.h"
# include "can_cfg.h"
#include "driver_can.h"
#include "CanDrv.h"
/* *********************************************************************** */
/* Defines                                                                 */
/* *********************************************************************** */

/* *********************************************************************** */
/* Default switches                                                        */
/* Automatic define settings, depending on user configuration in can_cfg.h */
/* *********************************************************************** */
# if defined( C_ENABLE_MULTICHANNEL_API )
#  define C_MULTIPLE_RECEIVE_CHANNEL
#  define MULTIPLE_RECEIVE_CHANNEL
# else
#  define C_SINGLE_RECEIVE_CHANNEL
# endif

# if ( kCanNumberOfTxObjects > 0 )
#  if !(defined( C_ENABLE_CAN_TRANSMIT ) || defined( C_DISABLE_CAN_TRANSMIT ))
#   define C_ENABLE_CAN_TRANSMIT
#  endif
# endif

# if !(defined( C_ENABLE_OFFLINE ) || defined( C_DISABLE_OFFLINE ))
#  define C_ENABLE_OFFLINE
# endif

# if !(defined( C_ENABLE_STOP ) || defined( C_DISABLE_STOP ))
#  define C_ENABLE_STOP
# endif

# if !(defined( C_ENABLE_CAN_CAN_INTERRUPT_CONTROL ) || defined( C_DISABLE_CAN_CAN_INTERRUPT_CONTROL ))
#  define C_ENABLE_CAN_CAN_INTERRUPT_CONTROL
# endif

# if !(defined( C_ENABLE_CAN_CANCEL_TRANSMIT ) || defined( C_DISABLE_CAN_CANCEL_TRANSMIT ))
#  if defined( C_ENABLE_CAN_TRANSMIT )
#   define C_ENABLE_CAN_CANCEL_TRANSMIT
#  endif
# endif

# if !defined( kCanNumberOfHwChannels )
/* compatibility for older tool versions */
#  define kCanNumberOfHwChannels                 kCanNumberOfChannels
# endif

#define C_HL_DISABLE_OVERRUN_IN_STATUS

#define C_HL_DISABLE_HW_RANGES_FILTER

#define C_HL_ENABLE_IDTYPE_IN_DLC

#define C_HL_DISABLE_DUMMY_FCT_CALL

#define C_HL_DISABLE_TX_MSG_DESTROYED

#define C_HL_DISABLE_CANCEL_IN_HW_TASK

#define C_HL_DISABLE_HW_EXIT_TRANSMIT 

#define C_HL_DISABLE_ADJUST_RXHANDLE

#define C_HL_DISABLE_REJECT_UNWANTED_IDTYPE

#define C_HL_DISABLE_REJECT_REMOTE_FRAME

#define C_HL_DISABLE_REJECT_REMOTE_FRAME_FULLCAN

#define C_HL_ENABLE_REJECT_ILLEGAL_DLC

#define C_HL_DISABLE_COPROCESSOR_SUPPORT

# if !( defined (C_ENABLE_DRIVER_STATUS) || defined (C_DISABLE_DRIVER_STATUS))
#  define C_DISABLE_DRIVER_STATUS
# endif

#define C_HL_DISABLE_RETRANSMIT_FCT

#define C_HL_ENABLE_RETRANSMIT_CONF_ISR

#define C_HL_DISABLE_AVOID_REENTRANT_APPLCANCANCELNOTIFICATION

/* Possibility to disable the prototypes of interrupt service routines in the driver header file */
# if !(defined ( C_ENABLE_ISR_PROTOTYPE ) || defined ( C_DISABLE_ISR_PROTOTYPE ) )
#  define C_ENABLE_ISR_PROTOTYPE
# endif

#define C_DISABLE_TX_ACTUAL_MACROS

#define CAN_HL_HW_LAYOUT_TXBASIC_FIRST

#if !defined( C_ENABLE_REJECT_SELF_RX_BY_HW ) && !defined( C_DISABLE_REJECT_SELF_RX_BY_HW )
/* rejection of reception from self sent frames performed by hardware */
# define C_ENABLE_REJECT_SELF_RX_BY_HW
#endif

#if !defined( C_ENABLE_FLEXCAN_AUTO_RECOVERY ) && !defined( C_DISABLE_FLEXCAN_AUTO_RECOVERY )
# define C_DISABLE_FLEXCAN_AUTO_RECOVERY
#endif

#if defined ( C_ENABLE_CAN_FD_USED )
# if !defined( C_ENABLE_CLASSIC_MAILBOX_LAYOUT ) && !defined( C_DISABLE_CLASSIC_MAILBOX_LAYOUT )
#  define C_ENABLE_CLASSIC_MAILBOX_LAYOUT
# endif
#endif

# if defined( C_ENABLE_TX_POLLING )
#  if !(defined( C_ENABLE_ERROR_POLLING ) || defined( C_DISABLE_ERROR_POLLING ))
#   define C_ENABLE_ERROR_POLLING
#  endif
# endif

# if !(defined( C_ENABLE_TASK_RECURSION_CHECK ) || defined( C_DISABLE_TASK_RECURSION_CHECK ))
#  define C_ENABLE_TASK_RECURSION_CHECK
# endif

# if defined( C_ENABLE_MULTI_ECU_PHYS )
#  define C_SUPPORTS_MULTI_ECU_PHYS
# endif

#if defined( C_ENABLE_CAN_FD_USED ) && !defined( C_ENABLE_CAN_FD_FULL )
#  define C_ENABLE_CAN_FD_BRS
#endif

/* *********************************************************************** */
/* return values                                                           */
/* *********************************************************************** */

/* general return values */
# define kCanFailed                              ((vuint8)0x00)
# define kCanOk                                  ((vuint8)0x01)
# define kCanNotSupported                        ((vuint8)0x02)
# define kCanRequested                           ((vuint8)0x03)

# define kCanFalse                               ((vuint8)0x00)
# define kCanTrue                                ((vuint8)0x01)

/* return values for precopy-routines */
# define kCanNoCopyData                          ((vuint8)0x00)
# define kCanCopyData                            ((vuint8)0x01)

/* Bitmask of return value of CanGetStatus() */
# if defined( C_KOMMENTAR_VECTOR_LI13 )
/* ##LI-: 1.2    CAN-Offline */
# endif
# define kCanTxOff                               ((vuint8)0x00)
# define kCanStatusInit                          ((vuint8)0x00)
# define kCanTxOn                                ((vuint8)0x01)
# define kCanTxNotOn                             ((vuint8)0xFE)              /* internal use only */
# define kCanHwIsStop                            ((vuint8)0x02)
# define kCanHwIsInit                            ((vuint8)0x04)
# define kCanHwIsInconsistent                    ((vuint8)0x08)              /* used of for common CAN */
# define kCanHwIsWarning                         ((vuint8)0x10)
# define kCanHwIsPassive                         ((vuint8)0x20)
# define kCanHwIsBusOff                          ((vuint8)0x40)
# define kCanHwIsSleep                           ((vuint8)0x80)

/* CanTransmit return values ----------------------------------------------- */
# define kCanTxFailed                            kCanFailed      /* Tx path switched off or no sending possible */
# define kCanTxOk                                kCanOk          /* msg transmitted or in queue                 */
# define kCanTxPartOffline                       ((vuint8)0x02)  /* Tx path switched part off or           */
# define kCanCommunicationDisabled               ((vuint8)0x03)  /* if application has disabled com after memory check */

# if defined( C_DRV_INTERNAL )
#  define kCanTxNotify                           ((vuint8)0x05)  /* internal returncode only - not used for the API */
# endif

/* CanGetDynTxObj return values ----------------------------------------------- */
# define kCanNoTxDynObjAvailable                 ((CanTransmitHandle)0xFFFFFFFFU)

/* CanReleaseDynTxObj return values ------------------------------------------- */
# define kCanDynReleased                         ((vuint8)0x00)
# define kCanDynNotReleased                      ((vuint8)0x01)

/* ApplCanMemCheckFailed return values ---------------------------------------- */
# define kCanDisableCommunication                ((vuint8)0x00)
# define kCanEnableCommunication                 ((vuint8)0x01)

/* return values of CanRxActualIdType */
#define kCanIdTypeStd         (0x00u)
#define kCanIdTypeExt         (0x20u) /* Attention: The SRR bit has to be considered for the transmission of Extended CAN frames, but must be without any effect on the reception side !
                                         ********** In Extended format it must be set to '1' for transmission.
                                                    For the Rx side it will be stored with the value received on the CAN bus, either recessive or dominant. */
#define kCanFdTypeFdByte      (0xC0u)
#if defined( C_ENABLE_CAN_FD_USED )
# define kCanFdTypeFd                            (0x8000u)
# define kCanFdTypeClassic                       (0x0000u) /* usually 0x00, Fd-Flag not set */
# define kCanFdBrsTypeTrue                       (0x4000u)
# define kCanFdBrsTypeFalse                      (0x0000u) /* usually 0x00, Brs-Flag not set */
#endif

/* return values of CanGetDriverStatus */
#define kCanDriverBusoff                0x01u             /* CAN driver is in recovery phase after BUSOFF */
#define kCanDriverBusoffInit            0x02u             /* Driver finished recovery and needs to be initialized */
#define kCanDriverNormal                0x03u             /* Driver completed recovery and is in normal mode */

/* *********************************************************************** */
/* parameter values                                                        */
/* *********************************************************************** */
/* parameters for partial offline */
# define kCanTxPartInit                          ((vuint8)0x00)

/* paramater for assertions */
# define kCanAllChannels                         ((CanChannelHandle)0xFFU)
/* used for generated tables */
# define kCanChannelNotUsed                      ((CanChannelHandle)0xFFU)

# if defined( C_KOMMENTAR_VECTOR_LI13 )
/* ##LI-: 2.2    Information for higher layers (e.g. TP) if the current pre-copy is called within a range or message specific. */
# endif
/* canRxHandle does not contain a certain message handle or entry in table is not used */
# define kCanRxHandleNotUsed                     ((CanReceiveHandle)  0xFFFFFFFFU)
# define kCanTxHandleNotUsed                     ((CanTransmitHandle) 0xFFFFFFFFU)

# if defined( C_DRV_INTERNAL )
#  define kCanRxHandleRange0                     ((CanReceiveHandle)  0xFFFFFFF0U)
#  define kCanRxHandleRange1                     ((CanReceiveHandle)  0xFFFFFFF1U)
#  define kCanRxHandleRange2                     ((CanReceiveHandle)  0xFFFFFFF2U)
#  define kCanRxHandleRange3                     ((CanReceiveHandle)  0xFFFFFFF3U)

/* entries for generated table CanHwMsgTransmitIndex[], CanHwTxNormalIndex[] - unused in case of CommonCan */
/* table entry does not contain a HW object assignment */
#  define kCanObjectHandleNotUsed                ((CanObjectHandle)0xFFFFFFFFU)
# endif

# if defined( C_KOMMENTAR_VECTOR_RI14 )
/* ##RI-1.1: Object parameters for Tx-Observe functions */
# endif
/* status of transmit objects */
# define kCanBufferFree                          ((CanTransmitHandle)0xFFFFFFFFU)   /* mark a transmit object is free */
# define kCanBufferCancel                        ((CanTransmitHandle)0xFFFFFFFEU)   /* mark a transmit object as canceled */
# define kCanBufferMsgDestroyed                  ((CanTransmitHandle)0xFFFFFFFDU)   /* mark a transmit object as destroyed */
# define kCanBufferMsgTransmit                   ((CanTransmitHandle)0xFFFFFFFCU)   /* mark a transmit object as used by CanMsgTransmit */
# define kCanBufferRetransmit                    ((CanTransmitHandle)0xFFFFFFFBU)   /* mark a transmit object as used by CanRetransmit */
/* valid transmit message handle:   0x0 to kCanNumberOfTxObjects   */

/* configure dynamic receive object to interrupt or polling mode (individual polling, for FullCAN only) */
# define kCanRxDynObjInt                         ((vuint8)0x00)
# define kCanRxDynObjPoll                        ((vuint8)0x01)

/* indirection from hwObjHandle to mailboxHandle */
# define kCanMailboxNotUsed                       ((CanObjectHandle)0xFFFFFFFFU)   /* hwObjHandle is not associated with any mailbox */


/* re-initialization */
# define kCanExecuteRamCheck                     kCanFalse
# define kCanSuppressRamCheck                    kCanTrue
# define kCanExecuteModeTransition               kCanFalse
# define kCanSuppressModeTransition              kCanTrue

/* mode transitions */
# define kCanModeInit                            ((vuint8)0x00)
# define kCanModeSleep                           ((vuint8)0x01)
# define kCanModeWakeupStart                     ((vuint8)0x02)
# define kCanModeStop                            ((vuint8)0x03)
# define kCanModeStart                           ((vuint8)0x04)

# define kCanContinueBusOffRecovery              ((vuint8)0x00)
# define kCanFinishBusOffRecovery                ((vuint8)0x01)

/* CAN-FD usage */
# define C_CAN_FD_NONE                           ((vuint8)0x00)
# define C_CAN_FD_MODE1                          ((vuint8)0x01)
# define C_CAN_FD_MODE2                          ((vuint8)0x02)

/* parameter for ApplCanTimerStart(),-End(), -Loop() */
#define kCanLoopLeaveDisableModeInit  ((vuint8)0x00)
#define kCanLoopEnterDisableModeInit  ((vuint8)0x01)
#define kCanLoopMsgReception          ((vuint8)0x02)
#define kCanLoopEnterFreezeModeInit   ((vuint8)0x03)

#  define kCanLoopInit         ((vuint8)0x04U)
#  define kCanLoopStart        ((vuint8)0x05U)
#  define kCanLoopStop         ((vuint8)0x06U)
#  define kCanLoopSleep        ((vuint8)0x07U)
#  define kCanLoopWakeup       ((vuint8)0x8U)

/* *********************************************************************** */
/* macros                                                                  */
/* *********************************************************************** */

# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define CAN_CHANNEL_CANTYPE_ONLY                   void                                  /* PRQA S 3460 */ /* MD_Can_3460 */
#  define CAN_CHANNEL_CANTYPE_FIRST
#  define CAN_CHANNEL_CANTYPE_LOCAL
#  define CAN_CHANNEL_CANPARA_ONLY
#  define CAN_CHANNEL_CANPARA_FIRST
#  define CAN_HW_CHANNEL_CANTYPE_ONLY                void                                  /* PRQA S 3460 */ /* MD_Can_3460 */
#  define CAN_HW_CHANNEL_CANTYPE_FIRST
#  define CAN_HW_CHANNEL_CANTYPE_LOCAL
#  define CAN_HW_CHANNEL_CANPARA_ONLY
#  define CAN_HW_CHANNEL_CANPARA_FIRST
#  define CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY    void                                  /* PRQA S 3460 */ /* MD_Can_3460 */
#  define CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST
#  define CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY
#  define CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST
# else
#  define CAN_CHANNEL_CANTYPE_ONLY                   CanChannelHandle channel
#  define CAN_CHANNEL_CANTYPE_FIRST                  CanChannelHandle channel,
#  define CAN_CHANNEL_CANTYPE_LOCAL                  CanChannelHandle channel;             /* PRQA S 3412 */ /* MD_Can_3412 */
#  define CAN_CHANNEL_CANPARA_ONLY                   channel
#  define CAN_CHANNEL_CANPARA_FIRST                  channel,
#  define CAN_HW_CHANNEL_CANTYPE_ONLY                CanChannelHandle canHwChannel
#  define CAN_HW_CHANNEL_CANTYPE_FIRST               CanChannelHandle canHwChannel,
#  define CAN_HW_CHANNEL_CANTYPE_LOCAL               CanChannelHandle canHwChannel;        /* PRQA S 3412 */ /* MD_Can_3412 */
#  define CAN_HW_CHANNEL_CANPARA_ONLY                canHwChannel
#  define CAN_HW_CHANNEL_CANPARA_FIRST               canHwChannel,
#   define CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY   CanChannelHandle channel
#   define CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST  CanChannelHandle channel,
#   define CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY   channel
#   define CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST  channel,
# endif

# if defined( C_DRV_INTERNAL )
/* macros to fill struct elements RangeMask and RangeCode of type tCanChannelObject - used by generation tool only */
#  if (kCanNumberOfUsedCanRxIdTables == 1)
#   define MK_RX_RANGE_MASK_IDSTD(i)             {MK_RX_RANGE_MASK_IDSTD0(i)}
#   define MK_RX_RANGE_CODE_IDSTD(i)             {MK_RX_RANGE_CODE_IDSTD0(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 2)
#   define MK_RX_RANGE_MASK_IDSTD(i)             {MK_RX_RANGE_MASK_IDSTD0(i), MK_RX_RANGE_MASK_IDSTD1(i)}
#   define MK_RX_RANGE_CODE_IDSTD(i)             {MK_RX_RANGE_CODE_IDSTD0(i), MK_RX_RANGE_CODE_IDSTD1(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 3)
#   define MK_RX_RANGE_MASK_IDSTD(i)             {MK_RX_RANGE_MASK_IDSTD0(i), MK_RX_RANGE_MASK_IDSTD1(i), MK_RX_RANGE_MASK_IDSTD2(i)}
#   define MK_RX_RANGE_CODE_IDSTD(i)             {MK_RX_RANGE_CODE_IDSTD0(i), MK_RX_RANGE_CODE_IDSTD1(i), MK_RX_RANGE_CODE_IDSTD2(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 4)
#   define MK_RX_RANGE_MASK_IDSTD(i)             {MK_RX_RANGE_MASK_IDSTD0(i), MK_RX_RANGE_MASK_IDSTD1(i), MK_RX_RANGE_MASK_IDSTD2(i), MK_RX_RANGE_MASK_IDSTD3(i)}
#   define MK_RX_RANGE_CODE_IDSTD(i)             {MK_RX_RANGE_CODE_IDSTD0(i), MK_RX_RANGE_CODE_IDSTD1(i), MK_RX_RANGE_CODE_IDSTD2(i), MK_RX_RANGE_CODE_IDSTD3(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 5)
#   define MK_RX_RANGE_MASK_IDSTD(i)             {MK_RX_RANGE_MASK_IDSTD0(i), MK_RX_RANGE_MASK_IDSTD1(i), MK_RX_RANGE_MASK_IDSTD2(i), MK_RX_RANGE_MASK_IDSTD3(i), MK_RX_RANGE_MASK_IDSTD4(i)}
#   define MK_RX_RANGE_CODE_IDSTD(i)             {MK_RX_RANGE_CODE_IDSTD0(i), MK_RX_RANGE_CODE_IDSTD1(i), MK_RX_RANGE_CODE_IDSTD2(i), MK_RX_RANGE_CODE_IDSTD3(i), MK_RX_RANGE_CODE_IDSTD4(i)}
#  endif

#  if (kCanNumberOfUsedCanRxIdTables == 1)
#   define MK_RX_RANGE_MASK_IDEXT(i)             {MK_RX_RANGE_MASK_IDEXT0(i)}
#   define MK_RX_RANGE_CODE_IDEXT(i)             {MK_RX_RANGE_CODE_IDEXT0(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 2)
#   define MK_RX_RANGE_MASK_IDEXT(i)             {MK_RX_RANGE_MASK_IDEXT0(i), MK_RX_RANGE_MASK_IDEXT1(i)}
#   define MK_RX_RANGE_CODE_IDEXT(i)             {MK_RX_RANGE_CODE_IDEXT0(i), MK_RX_RANGE_CODE_IDEXT1(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 3)
#   define MK_RX_RANGE_MASK_IDEXT(i)             {MK_RX_RANGE_MASK_IDEXT0(i), MK_RX_RANGE_MASK_IDEXT1(i), MK_RX_RANGE_MASK_IDEXT2(i)}
#   define MK_RX_RANGE_CODE_IDEXT(i)             {MK_RX_RANGE_CODE_IDEXT0(i), MK_RX_RANGE_CODE_IDEXT1(i), MK_RX_RANGE_CODE_IDEXT2(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 4)
#   define MK_RX_RANGE_MASK_IDEXT(i)             {MK_RX_RANGE_MASK_IDEXT0(i), MK_RX_RANGE_MASK_IDEXT1(i), MK_RX_RANGE_MASK_IDEXT2(i), MK_RX_RANGE_MASK_IDEXT3(i)}
#   define MK_RX_RANGE_CODE_IDEXT(i)             {MK_RX_RANGE_CODE_IDEXT0(i), MK_RX_RANGE_CODE_IDEXT1(i), MK_RX_RANGE_CODE_IDEXT2(i), MK_RX_RANGE_CODE_IDEXT3(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 5)
#   define MK_RX_RANGE_MASK_IDEXT(i)             {MK_RX_RANGE_MASK_IDEXT0(i), MK_RX_RANGE_MASK_IDEXT1(i), MK_RX_RANGE_MASK_IDEXT2(i), MK_RX_RANGE_MASK_IDEXT3(i), MK_RX_RANGE_MASK_IDEXT4(i)}
#   define MK_RX_RANGE_CODE_IDEXT(i)             {MK_RX_RANGE_CODE_IDEXT0(i), MK_RX_RANGE_CODE_IDEXT1(i), MK_RX_RANGE_CODE_IDEXT2(i), MK_RX_RANGE_CODE_IDEXT3(i), MK_RX_RANGE_CODE_IDEXT4(i)}
#  endif
# endif

/* calculate size of cond/ind-flags */
#  define kCanNumberOfConfBytes                  ((kCanNumberOfConfFlags + 7)/8)
# define kCanNumberOfConfWords                   ((kCanNumberOfConfFlags + 15)/16)
# define kCanNumberOfConfDWords                  ((kCanNumberOfConfFlags + 31)/32)
#  define kCanNumberOfIndBytes                   ((kCanNumberOfIndFlags + 7)/8)
# define kCanNumberOfIndWords                    ((kCanNumberOfIndFlags + 15)/16)
# define kCanNumberOfIndDWords                   ((kCanNumberOfIndFlags + 31)/32)

/* Macros for CAN message access within ApplCanMsgReceived() or PreCopy() function */

# if defined( C_KOMMENTAR_VECTOR )
/*  optimization is possible, because the IdType is always checked before the first call of a Callback and before the first use of CanRxActualId. */
# endif
# if defined( C_ENABLE_EXTENDED_ID )
#  if defined( C_ENABLE_MIXED_ID )
#   define CanRxActualId(rxStruct)               ((CanRxActualIdType(rxStruct) == kCanIdTypeExt) ?      \
                                                 CanRxActualExtId(rxStruct) : ((vuint32)CanRxActualStdId(rxStruct)))         /* returns vuint32 */
#  else
#   define CanRxActualId(rxStruct)               (CanRxActualExtId(rxStruct))                                                /* returns vuint32 */
#  endif
# else
#  define CanRxActualId(rxStruct)                (CanRxActualStdId(rxStruct))                                                /* returns vuint16 */
# endif

/* Macros for CAN Status */
# define CanHwIsOk(state)                        (((state) & (kCanHwIsWarning |     \
                                                    kCanHwIsPassive |     \
                                                    kCanHwIsBusOff) )    ? 0 : 1)
# define CanHwIsWarning(state)                   (((state) & kCanHwIsWarning)      ? 1 : 0)
# define CanHwIsPassive(state)                   (((state) & kCanHwIsPassive)      ? 1 : 0)
# define CanHwIsBusOff(state)                    (((state) & kCanHwIsBusOff)       ? 1 : 0)
# define CanHwIsWakeup(state)                    (((state) & kCanHwIsSleep)        ? 0 : 1)
# define CanHwIsSleep(state)                     (((state) & kCanHwIsSleep)        ? 1 : 0)
# define CanHwIsStop(state)                      (((state) & kCanHwIsStop)         ? 1 : 0)
# define CanHwIsStart(state)                     (((state) & kCanHwIsStop)         ? 0 : 1)
# define CanIsOnline(state)                      (((state) & kCanTxOn)             ? 1 : 0)
# define CanIsOffline(state)                     (((state) & kCanTxOn)             ? 0 : 1)
# define CanHwIsInconsistent(state)              (((state) & kCanHwIsInconsistent) ? 1 : 0)

#  if defined( C_DRV_INTERNAL )
#   define CanGetTxId0(i)                        (CanTxId0[i])
#   define CanGetTxId1(i)                        (CanTxId1[i])
#   define CanGetTxId2(i)                        (CanTxId2[i])
#   define CanGetTxId3(i)                        (CanTxId3[i])
#   define CanGetTxId4(i)                        (CanTxId4[i])
#   if defined( C_ENABLE_CAN_FD_USED )
#    define CanGetTxFdType(i)                    (CanTxFdType[i])
#   endif
#   if defined( C_ENABLE_EXTENDED_ID )
#    if defined( C_ENABLE_MIXED_ID )
#      if defined( C_HL_ENABLE_IDTYPE_IN_DLC )
#       define CanGetTxIdType(i)                 (CanTxDLC[i] & kCanIdTypeExt)
#      else
#       define CanGetTxIdType(i)                 (CanTxIdType[i] & kCanIdTypeExt)
#      endif
#    else
#     define CanGetTxIdType(i)                   (kCanIdTypeExt)
#    endif
#   else
#    define CanGetTxIdType(i)                    (kCanIdTypeStd)
#   endif
#  endif /* C_DRV_INTERNAL */

#  define CanGetTxDlc(i)                         (CanTxDLC[i])
#  if defined( C_ENABLE_CAN_FD_FULL )
#   define CanGetTxMessageLength(i)              (CanTxMessageLength[i])
#  endif
#  define CanGetTxDataPtr(i)                     (CanTxDataPtr[i])
#  define CanGetConfirmationOffset(i)            (CanConfirmationOffset[i])
#  define CanGetConfirmationMask(i)              (CanConfirmationMask[i])
#  define CanGetTxMailbox(i)                     (CanTxMailbox[i])
#  define CanGetTxSendMask(i)                    (CanTxSendMask[i])
#  define CanGetApplPreTransmitPtr(i)            (CanTxApplPreTransmitPtr[i])
#  define CanGetApplConfirmationPtr(i)           (CanTxApplConfirmationPtr[i])
#  define CanGetChannelOfTxObj(i)                (CanTxMsgHandleToChannel[i])
											
#  if defined( C_DRV_INTERNAL )
#   define CanGetRxId0(i)                        (CanRxId0[i])
#   define CanGetRxId1(i)                        (CanRxId1[i])
#   define CanGetRxId2(i)                        (CanRxId2[i])
#   define CanGetRxId3(i)                        (CanRxId3[i])
#   define CanGetRxId4(i)                        (CanRxId4[i])
#   if defined( C_ENABLE_EXTENDED_ID )
#    if defined( C_ENABLE_MIXED_ID )
#      define CanGetRxIdType(i)                  (CanRxIdType[i] & kCanIdTypeExt)
#    else
#     define CanGetRxIdType(i)                   (kCanIdTypeExt)
#    endif
#   else
#    define CanGetRxIdType(i)                    (kCanIdTypeStd)
#   endif
#  endif /* C_DRV_INTERNAL */

#  define CanGetRxDataLen(i)                     (CanRxDataLen[i])
#  define CanGetRxMinDataLen(i)                  (CanRxMinDataLen[i])
#  define CanGetRxDataPtr(i)                      (CanRxDataPtr[i])
#  define CanGetIndicationOffset(i)              (CanIndicationOffset[i])
#  define CanGetIndicationMask(i)                (CanIndicationMask[i])
#  define CanGetApplPrecopyPtr(i)                (CanRxApplPrecopyPtr[i])
#  define CanGetApplIndicationPtr(i)             (CanRxApplIndicationPtr[i])

# if defined( C_ENABLE_CAN_FD_USED )
#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
#   define CanGetFdMode(ch)                      (CanFdUsage[ch])
#  else
#   define CanGetFdMode(ch)                      (C_CAN_FD_USAGE)
#  endif
# else
#  define CanGetFdMode(ch)                       (C_CAN_FD_NONE)
# endif

# if defined( C_ENABLE_CONFIRMATION_FCT ) && \
    defined( C_ENABLE_DYN_TX_OBJECTS )  && \
    defined( C_ENABLE_TRANSMIT_QUEUE )
  /* set confirmation active for CanReleaseDynTxObj() */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#   define CanConfirmStart(txHandle)             {confirmHandle[0] = (txHandle);}                 /* PRQA S 3458 */ /* MD_Can_3458 */
#   define CanConfirmEnd()                       {confirmHandle[0] = kCanTxHandleNotUsed;}        /* PRQA S 3458 */ /* MD_Can_3458 */
#  else
#   define CanConfirmStart(channel, txHandle)    {confirmHandle[channel] = (txHandle);}           /* PRQA S 3458 */ /* MD_Can_3458 */
#   define CanConfirmEnd(channel)                {confirmHandle[channel] = kCanTxHandleNotUsed;}  /* PRQA S 3458 */ /* MD_Can_3458 */
#  endif
# endif

# if defined( C_ENABLE_PART_OFFLINE )
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#   define CanPartOffline(sendGroup)             (CanSetPartOffline( sendGroup))
#   define CanPartOnline(sendGroup)              (CanSetPartOnline( (vuint8)~(vuint8)(sendGroup)) )
#  else
#   define CanPartOffline(channel, sendGroup)    (CanSetPartOffline((channel), (sendGroup)))
#   define CanPartOnline(channel,  sendGroup)    (CanSetPartOnline((channel), (vuint8)~(vuint8)(sendGroup)) )
#  endif
# else
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#   define CanPartOffline(sendGroup)
#   define CanPartOnline(sendGroup)
#  else
#   define CanPartOffline(channel, sendGroup)
#   define CanPartOnline(channel, sendGroup)
#  endif
# endif

# if defined( C_ENABLE_DYN_TX_ID )
#  define CanDynTxObjSetExtId(txHandle, idExtHi, idExtLo)    CanDynTxObjSetExtId32((txHandle), (vuint32)(((vuint32)(idExtHi)<<16) | (vuint32)(idExtLo)))
#  define CanDynTxObjSetFdExtId(txHandle, idExtHi, idExtLo)  CanDynTxObjSetFdExtId32((txHandle), (vuint32)(((vuint32)(idExtHi)<<16) | (vuint32)(idExtLo)))
# endif

# if defined( C_ENABLE_DYN_TX_DLC )
#  define CanDynTxObjSetDlc(txHandle, dlc)                   CanDynTxObjSetMessageLength((txHandle), (dlc))
# endif

/* provide interface for interrupt disable and restore functions */
# define CanGlobalInterruptDisable               VStdSuspendAllInterrupts
# define CanGlobalInterruptRestore               VStdResumeAllInterrupts

//# define CanGlobalInterruptDisable               DisableAllInterrupts
//# define CanGlobalInterruptRestore               EnableAllInterrupts

# if ( C_SECURITY_LEVEL == 0 )
#  define CanDeclareGlobalInterruptOldStatus
#  define CanPutGlobalInterruptOldStatus(x)
#  define CanGetGlobalInterruptOldStatus(x)
#  define CanNestedGlobalInterruptDisable()
#  define CanNestedGlobalInterruptRestore()
# else  /* C_SECURITY_LEVEL == 0 */
#  define CanDeclareGlobalInterruptOldStatus     VStdDeclareGlobalInterruptOldStatus
#  define CanPutGlobalInterruptOldStatus(x)      VStdPutGlobalInterruptOldStatus(x)
#  define CanGetGlobalInterruptOldStatus(x)      VStdGetGlobalInterruptOldStatus(x)
#  if (VSTDLIB__COREHLL_VERSION  <  0x0216 )
#   define CanNestedGlobalInterruptDisable()     VStdNestedGlobalInterruptDisable()
#   define CanNestedGlobalInterruptRestore()     VStdNestedGlobalInterruptRestore()
#  else
#   define CanNestedGlobalInterruptDisable()     VStdGlobalInterruptDisable()
#   define CanNestedGlobalInterruptRestore()     VStdGlobalInterruptRestore()
#  endif
# endif /* C_SECURITY_LEVEL == 0 */

/* provide support for multiple callbacks */
#if !defined( APPL_CAN_GENERIC_PRECOPY )
# define APPL_CAN_GENERIC_PRECOPY                          ApplCanGenericPrecopy
#endif
#if !defined( APPL_CAN_TX_CONFIRMATION )
# define APPL_CAN_TX_CONFIRMATION                          ApplCanTxConfirmation
#endif
#if !defined( APPL_CAN_MSGTRANSMITCONF )
# define APPL_CAN_MSGTRANSMITCONF                          ApplCanMsgTransmitConf
#endif
#if !defined( APPL_CAN_MSGTRANSMITINIT )
# define APPL_CAN_MSGTRANSMITINIT                          ApplCanMsgTransmitInit
#endif
#if !defined( APPL_CAN_ONLINE )
# define APPL_CAN_ONLINE                                   ApplCanOnline
#endif
#if !defined( APPL_CAN_OFFLINE )
# define APPL_CAN_OFFLINE                                  ApplCanOffline
#endif
#if !defined( APPL_CAN_MSGRECEIVED )
# define APPL_CAN_MSGRECEIVED                              ApplCanMsgReceived
#endif
#if !defined( APPL_CAN_CANCELNOTIFICATION )
# define APPL_CAN_CANCELNOTIFICATION                       ApplCanCancelNotification
#endif
#if !defined( APPL_CAN_MSGCANCELNOTIFICATION )
# define APPL_CAN_MSGCANCELNOTIFICATION                    ApplCanMsgCancelNotification
#endif

#if defined(C_ENABLE_CAN_FD_FULL)
# define CAN_DLC2LEN(dlc)              CanDlcToFrameLenght[(dlc) & 0x0F]
# define CAN_LEN2DLC(len)              CanMessageLengthToDlc[len]
#else
# define CAN_DLC2LEN(dlc)              (dlc)
# define CAN_LEN2DLC(len)              (len)
#endif

#if defined( C_CPUTYPE_32BIT )
# define kCanTxQueueSize      ((kCanTxQueueBytes + 3) >> 2)
#endif

#define txErrCMask      (vuint32)0x000000FFu
#define rxErrCMask      (vuint32)0x0000FF00u
#define txErrCFastMask  (vuint32)0x00FF0000u
#define rxErrCFastMask  (vuint32)0xFF000000u

#if defined( C_ENABLE_VARIABLE_DLC )
# define CanLL_DlcMask            0xF0U
#endif

/* macros to set DLC and ID in RX-,TX-structures -------------------------- */
/* MK... macros are used by the generation tool to fill the RX and TX structures */
/* In case the IDE bit is located in the ID registers, this bit has to be handled as must match.
   In general, this is done by setting the IDE bit to 0 in the .._MASK_.. macros.
*/

#define MK_RX_RANGE_MASK_IDSTD0(id)   ((vuint32)MK_STDID0(id))
#define MK_RX_RANGE_MASK_IDSTD1(id)   ( MK_STDID1(id) )
#define MK_RX_RANGE_MASK_IDSTD2(id)   ( MK_STDID2(id) )
#define MK_RX_RANGE_MASK_IDSTD3(id)   ( MK_STDID3(id) )
#define MK_RX_RANGE_MASK_IDSTD4(id)   ( MK_STDID4(id) )

#define MK_RX_RANGE_CODE_IDSTD0(id)   ((vuint32)MK_STDID0(id))
#define MK_RX_RANGE_CODE_IDSTD1(id)   ( MK_STDID1(id) )
#define MK_RX_RANGE_CODE_IDSTD2(id)   ( MK_STDID2(id) )
#define MK_RX_RANGE_CODE_IDSTD3(id)   ( MK_STDID3(id) )
#define MK_RX_RANGE_CODE_IDSTD4(id)   ( MK_STDID4(id) )

#define MK_RX_RANGE_MASK_IDEXT0(id)   ((vuint32)MK_EXTID0(id))
#define MK_RX_RANGE_MASK_IDEXT1(id)   ( MK_EXTID1(id) )
#define MK_RX_RANGE_MASK_IDEXT2(id)   ( MK_EXTID2(id) )
#define MK_RX_RANGE_MASK_IDEXT3(id)   ( MK_EXTID3(id) )
#define MK_RX_RANGE_MASK_IDEXT4(id)   ( MK_EXTID4(id) )

#define MK_RX_RANGE_CODE_IDEXT0(id)   ((vuint32)MK_EXTID0(id))
#define MK_RX_RANGE_CODE_IDEXT1(id)   ( MK_EXTID1(id) )
#define MK_RX_RANGE_CODE_IDEXT2(id)   ( MK_EXTID2(id) )
#define MK_RX_RANGE_CODE_IDEXT3(id)   ( MK_EXTID3(id) )
#define MK_RX_RANGE_CODE_IDEXT4(id)   ( MK_EXTID4(id) )

#if defined( C_ENABLE_EXTENDED_ID ) 
# define MK_STDID0(id)                 ((vuint32)(((vuint32)(id) & (vuint32)0x07FF) << 18))
#else
# define MK_STDID0(id)                 ((vuint16)(((vuint16)(id) & (vuint16)0x07FF) << 2))
#endif
#define MK_STDID1(id)            (id)
#define MK_STDID2(id)            (id)
#define MK_STDID3(id)            (id)
#define MK_STDID4(id)            (id)

#define MK_EXTID0(id)            ((vuint32)((vuint32)(id) & (vuint32)0x1FFFFFFF))
#define MK_EXTID1(id)            ((id))
#define MK_EXTID2(id)            ((id))
#define MK_EXTID3(id)            ((id))
#define MK_EXTID4(id)            ((id))

#define MK_TX_DLC(dlc)       ((tCanDlc)((vuint8)(dlc) & (vuint8)0x0F))
#define MK_TX_DLC_EXT(dlc)   ((tCanDlc)(((vuint8)(dlc) & (vuint8)0x0F) | (vuint8)kCanIdTypeExt))

/* extract  DLC from register format to logical format */
#define XT_TX_DLC(dlc)       ((vuint8)((vuint8)(dlc) & (vuint8)0x0F))

#if defined( C_SINGLE_RECEIVE_CHANNEL )
/* Bus-Off functions */
#  define CanResetBusOffStart(a)  (CanReInit(kCanSuppressRamCheck, kCanExecuteModeTransition))
#  define CanResetBusOffEnd(a)
/* Bus-Sleep functions */
# define CanResetBusSleep(a)     (CanReInit(kCanExecuteRamCheck, kCanExecuteModeTransition))

#else
/* Bus-Off functions */
#  define CanResetBusOffStart(ch, a)  (CanReInit((ch), kCanSuppressRamCheck, kCanExecuteModeTransition))
#  define CanResetBusOffEnd(ch, a)
/* Bus-Sleep functions */
# define CanResetBusSleep(ch, a)     (CanReInit((ch), kCanExecuteRamCheck, kCanExecuteModeTransition))
#endif

/* The macros CanRxActualIdRawx() have to provide the register context of the ID registers.
   It is not necessary to mask any bits. These macros are for internal use only and masking
   will be done in can_hls.c
*/
#if defined( C_ENABLE_EXTENDED_ID )
  #define CanRxActualIdRaw0(rxStruct)      ((vuint32)(*((CanChipMsgPtr32)((rxStruct)->pChipMsgObj + 4))))
  #define CanRxActualIdRaw1(rxStruct)   0
  #define CanRxActualIdRaw2(rxStruct)   0
  #define CanRxActualIdRaw3(rxStruct)   0
  #define CanRxActualIdRaw4(rxStruct)   0
#else
# if defined( C_CPUTYPE_LITTLEENDIAN )  
  #define CanRxActualIdRaw0(rxStruct)     ((vuint16)(*((CanChipMsgPtr16)((rxStruct)->pChipMsgObj + 4)) & (vuint16)0x1FFF))
# endif
  #define CanRxActualIdRaw1(rxStruct)    0
  #define CanRxActualIdRaw2(rxStruct)    0
  #define CanRxActualIdRaw3(rxStruct)    0
  #define CanRxActualIdRaw4(rxStruct)    0
#endif

/* Macros for CAN message access within ApplCanMsgReceived() or PreCopy() function */
#if defined( C_ENABLE_EXTENDED_ID )
# if defined( C_CPUTYPE_LITTLEENDIAN )  
#  define CanRxActualIdExtHi(rxStruct)        ((vuint8)(*((CanChipMsgPtr)((rxStruct)->pChipMsgObj + 7)) & (vuint8)0x1F))
#  define CanRxActualIdExtMidHi(rxStruct)     ((vuint8)(*((CanChipMsgPtr)((rxStruct)->pChipMsgObj + 6))))
#  define CanRxActualIdExtMidLo(rxStruct)     ((vuint8)(*((CanChipMsgPtr)((rxStruct)->pChipMsgObj + 5))))                                         
#  define CanRxActualIdExtLo(rxStruct)        ((vuint8)(*((CanChipMsgPtr)((rxStruct)->pChipMsgObj + 4))))
# endif
#endif

#if defined( C_ENABLE_EXTENDED_ID ) 
# define XT_ID(id)         ((vuint16)(((vuint32)(id) & (vuint32)0x1FFC0000) >> 18))
#else
# define XT_ID(id)         ((vuint16)(((vuint16)(id) & 0x1FFF)))
#endif
#define XT_EXTID(id)       ((vuint32)((vuint32)(id) & (vuint32)0x1FFFFFFF))

#define CanRxActualExtId(rxStruct)        (XT_EXTID(CanRxActualIdRaw0(rxStruct)))
#define CanRxActualStdId(rxStruct)        (XT_ID(CanRxActualIdRaw0(rxStruct)))
//#define CanRxActualStdId(rxStruct)        (rxMsg.RxHeader.Id)
#define CanRxActualData(rxStruct,i)       ((vuint8)*((CanChipDataPtr)((rxStruct)->pChipData + (i))))
#if defined( C_CPUTYPE_LITTLEENDIAN )  
# define CanRxActualDLC(rxStruct)         CAN_DLC2LEN((vuint8)(*((CanChipMsgPtr)((rxStruct)->pChipMsgObj)) & (vuint8)0x0F))
# define CanRxActualIdType(rxStruct)      ((vuint8)(*((CanChipMsgPtr)((rxStruct)->pChipMsgObj)) & (vuint8)kCanIdTypeExt))
# define CanRxActualFdType(rxStruct)      ((vuint16)(*((CanChipMsgPtr16)((rxStruct)->pChipMsgObj)) & (vuint16)kCanFdTypeFd))
#endif

/* support reading the error counters */
# if defined( C_SINGLE_RECEIVE_CHANNEL )
//#   define CanRxActualErrorCounter()   ((vuint8)(((pFlexCAN(0)->ecr) & rxErrCMask) >> 8))
//#   define CanTxActualErrorCounter()   ((vuint8)((pFlexCAN(0)->ecr) & txErrCMask))
# else
#   define CanRxActualErrorCounter(x)  ((vuint8)(((pFlexCAN(x)->ecr) & rxErrCMask) >> 8))
#   define CanTxActualErrorCounter(x)  ((vuint8)((pFlexCAN(x)->ecr) & txErrCMask))
# endif

/* Macros for CAN message access within GenericConfirmation() function */
#if defined( C_CPUTYPE_LITTLEENDIAN )
# if defined( C_ENABLE_EXTENDED_ID ) 
#  define CanTxActualStdId(txStruct)     (XT_ID((vuint32)(*((CanChipMsgPtr32)((txStruct)->pChipMsgObj + 2)))))
# else
#  define CanTxActualStdId(txStruct)     (XT_ID(((vuint16)(*((CanChipMsgPtr16)((txStruct)->pChipMsgObj + 4)) & (vuint16)0x1FFF))))
# endif
# define CanTxActualExtId(txStruct)      (XT_EXTID((vuint32)(*((CanChipMsgPtr32)((txStruct)->pChipMsgObj + 2)))))
#endif
#define CanTxActualDLC(txStruct)          CanRxActualDLC(txStruct)
#define CanTxActualIdType(txStruct)       CanRxActualIdType(txStruct)
#define CanTxActualData(txStruct,i)       CanRxActualData(txStruct,i)
#define CanTxActualFdType(txStruct)       CanRxActualFdType(txStruct)

/* Macros for CAN message access within PreTransmit() function */
#if defined( C_ENABLE_CAN_FD_USED )  /* ##visrse TODO check where activeley set/celar fd flag */
#if defined( C_CPUTYPE_LITTLEENDIAN )
# if defined( C_ENABLE_EXTENDED_ID )
#  define CanTxWriteActId(txStruct,id)      *((CanChipMsgPtr32)((txStruct).pChipMsgObj + 2)) = MK_STDID0(id); \
                                            *((CanChipMsgPtr)((txStruct).pChipMsgObj)) &= (vuint8)0x0F                           /* PRQA S 3412 */ /* MD_Can_3412 */
                                            
#  define CanTxWriteActFdId(txStruct,id)    *((CanChipMsgPtr32)((txStruct).pChipMsgObj + 2)) = MK_STDID0(id); \
                                            *((CanChipMsgPtr)((txStruct).pChipMsgObj)) |= (vuint8)kCanFdTypeFdByte; \
                                            *((CanChipMsgPtr)((txStruct).pChipMsgObj)) &= (vuint8)0x0F                           /* PRQA S 3412 */ /* MD_Can_3412 */

#  define CanTxWriteActExtId(txStruct,id)   *((CanChipMsgPtr32)((txStruct).pChipMsgObj + 2)) = MK_EXTID0(id); \
                                            *((CanChipMsgPtr)((txStruct).pChipMsgObj)) |= (vuint8)kCanIdTypeExt                  /* PRQA S 3412 */ /* MD_Can_3412 */

#  define CanTxWriteActFdExtId(txStruct,id) *((CanChipMsgPtr32)((txStruct).pChipMsgObj + 2)) = MK_EXTID0(id); \
                                            *((CanChipMsgPtr)((txStruct).pChipMsgObj)) |= ((vuint8)kCanIdTypeExt | (vuint8)kCanFdTypeFdByte)    /* PRQA S 3412 */ /* MD_Can_3412 */
# else
#  define CanTxWriteActId(txStruct,id)      *((CanChipMsgPtr16)((txStruct).pChipMsgObj + 4)) = MK_STDID0(id); \
                                            *((CanChipMsgPtr)((txStruct).pChipMsgObj)) &= (vuint8)0x0F                           /* PRQA S 3412 */ /* MD_Can_3412 */
                                            
#  define CanTxWriteActFdId(txStruct,id)    *((CanChipMsgPtr16)((txStruct).pChipMsgObj + 4)) = MK_STDID0(id); \
                                            *((CanChipMsgPtr)((txStruct).pChipMsgObj)) |= (vuint8)kCanFdTypeFdByte; \
                                            *((CanChipMsgPtr)((txStruct).pChipMsgObj)) &= (vuint8)0x0F                           /* PRQA S 3412 */ /* MD_Can_3412 */
                                            
# endif
#endif /* C_CPUTYPE_LITTLEENDIAN */
#else /* C_ENABLE_CAN_FD_USED */
#if defined( C_CPUTYPE_LITTLEENDIAN )
# if defined( C_ENABLE_EXTENDED_ID )
#  define CanTxWriteActId(txStruct,id)      *((CanChipMsgPtr32)((txStruct).pChipMsgObj + 2)) = MK_STDID0(id); \
                                            *((CanChipMsgPtr)((txStruct).pChipMsgObj)) &= (vuint8)0x0F                               /* PRQA S 3412 */ /* MD_Can_3412 */

#  define CanTxWriteActExtId(txStruct,id)   *((CanChipMsgPtr32)((txStruct).pChipMsgObj + 2)) = MK_EXTID0(id); \
                                            *((CanChipMsgPtr)((txStruct).pChipMsgObj)) |= (vuint8)kCanIdTypeExt                      /* PRQA S 3412 */ /* MD_Can_3412 */
# else
#  define CanTxWriteActId(txStruct,id)      *((CanChipMsgPtr16)((txStruct).pChipMsgObj + 4)) = MK_STDID0(id); \
                                            *((CanChipMsgPtr)((txStruct).pChipMsgObj)) &= (vuint8)0x0F                               /* PRQA S 3412 */ /* MD_Can_3412 */
# endif
#endif /* C_CPUTYPE_LITTLEENDIAN */
#endif /* C_ENABLE_CAN_FD_USED */
#if defined( C_CPUTYPE_LITTLEENDIAN )
# define CanTxWriteActDLC(txStruct,len)     *((CanChipMsgPtr)((txStruct).pChipMsgObj)) &= (vuint8)kCanIdTypeExt; \
                                            *((CanChipMsgPtr)((txStruct).pChipMsgObj)) |= ((vuint8)(len) & (vuint8)0x0F)             /* PRQA S 3412 */ /* MD_Can_3412 */
#endif

/* Macros to fill variables of the type tCanMsgTransmitStruct */
#if defined( C_ENABLE_CAN_FD_USED ) /* ##visrse TODO check where activeley set/celar fd flag */
# if defined ( C_ENABLE_EXTENDED_ID )
#  define CanMsgTransmitSetStdId(pCanMsgTransmitStruct, id)     (pCanMsgTransmitStruct)->IdRaw =  MK_STDID0(id); \
                                                                (pCanMsgTransmitStruct)->DlcRaw &= (vuint16)0x3F0F                   /* PRQA S 3412 */ /* MD_Can_3412 */
#  if defined( C_ENABLE_CAN_FD_SUPPRESS_BRS )
#   define CanMsgTransmitSetFdStdId(pCanMsgTransmitStruct, id)  (pCanMsgTransmitStruct)->IdRaw =  MK_STDID0(id); \
                                                                (pCanMsgTransmitStruct)->DlcRaw &= (vuint16)0x3F0F; \
                                                                (pCanMsgTransmitStruct)->DlcRaw |= (vuint16)kCanFdTypeFd | (vuint16)kCanFdBrsTypeTrue   /* PRQA S 3412 */ /* MD_Can_3412 */
#  else
#   define CanMsgTransmitSetFdStdId(pCanMsgTransmitStruct, id)  (pCanMsgTransmitStruct)->IdRaw =  MK_STDID0(id); \
                                                                (pCanMsgTransmitStruct)->DlcRaw &= (vuint16)0x3F0F; \
                                                                (pCanMsgTransmitStruct)->DlcRaw |= (vuint16)kCanFdTypeFd | (vuint16)kCanFdBrsTypeFalse  /* PRQA S 3412 */ /* MD_Can_3412 */
#  endif
# else
#  define CanMsgTransmitSetStdId(pCanMsgTransmitStruct, id)     (pCanMsgTransmitStruct)->IdRaw =  ((vuint32)MK_STDID0(id) << 16 ); \
                                                                (pCanMsgTransmitStruct)->DlcRaw &= (vuint16)0x3F0F                   /* PRQA S 3412 */ /* MD_Can_3412 */
#  if defined( C_ENABLE_CAN_FD_SUPPRESS_BRS )
#   define CanMsgTransmitSetFdStdId(pCanMsgTransmitStruct, id)  (pCanMsgTransmitStruct)->IdRaw =  ((vuint32)MK_STDID0(id) << 16 ); \
                                                                (pCanMsgTransmitStruct)->DlcRaw &= (vuint16)0x3F0F; \
                                                                (pCanMsgTransmitStruct)->DlcRaw |= (vuint16)kCanFdTypeFd | (vuint16)kCanFdBrsTypeTrue   /* PRQA S 3412 */ /* MD_Can_3412 */
#  else
#   define CanMsgTransmitSetFdStdId(pCanMsgTransmitStruct, id)  (pCanMsgTransmitStruct)->IdRaw =  ((vuint32)MK_STDID0(id) << 16 ); \
                                                                (pCanMsgTransmitStruct)->DlcRaw &= (vuint16)0x3F0F; \
                                                                (pCanMsgTransmitStruct)->DlcRaw |= (vuint16)kCanFdTypeFd | (vuint16)kCanFdBrsTypeFalse  /* PRQA S 3412 */ /* MD_Can_3412 */
#  endif
# endif
# define CanMsgTransmitSetExtId(pCanMsgTransmitStruct, id)      (pCanMsgTransmitStruct)->IdRaw = MK_EXTID0(id); \
                                                                (pCanMsgTransmitStruct)->DlcRaw &= (vuint16)0x3F0F; \
                                                                (pCanMsgTransmitStruct)->DlcRaw |= (vuint16)kCanIdTypeExt            /* PRQA S 3412 */ /* MD_Can_3412 */
# if defined( C_ENABLE_CAN_FD_SUPPRESS_BRS )
#  define CanMsgTransmitSetFdExtId(pCanMsgTransmitStruct, id)   (pCanMsgTransmitStruct)->IdRaw = MK_EXTID0(id); \
                                                                (pCanMsgTransmitStruct)->DlcRaw &= (vuint16)0x3F0F; \
                                                                (pCanMsgTransmitStruct)->DlcRaw |= (vuint16)kCanIdTypeExt | (vuint16)kCanFdTypeFd | (vuint16)kCanFdBrsTypeTrue  /* PRQA S 3412 */ /* MD_Can_3412 */
# else
#  define CanMsgTransmitSetFdExtId(pCanMsgTransmitStruct, id)   (pCanMsgTransmitStruct)->IdRaw = MK_EXTID0(id); \
                                                                (pCanMsgTransmitStruct)->DlcRaw &= (vuint16)0x3F0F; \
                                                                (pCanMsgTransmitStruct)->DlcRaw |= (vuint16)kCanIdTypeExt | (vuint16)kCanFdTypeFd | (vuint16)kCanFdBrsTypeFalse  /* PRQA S 3412 */ /* MD_Can_3412 */
# endif
#else
# if defined ( C_ENABLE_EXTENDED_ID )
#  define CanMsgTransmitSetStdId(pCanMsgTransmitStruct, id)     (pCanMsgTransmitStruct)->IdRaw =  MK_STDID0(id); \
                                                                (pCanMsgTransmitStruct)->DlcRaw &= (vuint16)0xFF0F                   /* PRQA S 3412 */ /* MD_Can_3412 */
# else
#  define CanMsgTransmitSetStdId(pCanMsgTransmitStruct, id)     (pCanMsgTransmitStruct)->IdRaw =  ((vuint32)MK_STDID0(id) << 16 ); \
                                                                (pCanMsgTransmitStruct)->DlcRaw &= (vuint16)0xFF0F                   /* PRQA S 3412 */ /* MD_Can_3412 */
# endif
# define CanMsgTransmitSetExtId(pCanMsgTransmitStruct, id)      (pCanMsgTransmitStruct)->IdRaw = MK_EXTID0(id); \
                                                                (pCanMsgTransmitStruct)->DlcRaw &= (vuint16)0xFF0F; \
                                                                (pCanMsgTransmitStruct)->DlcRaw |= (vuint16)kCanIdTypeExt            /* PRQA S 3412 */ /* MD_Can_3412 */
#endif
# define CanMsgTransmitSetDlc(pCanMsgTransmitStruct, len)       (pCanMsgTransmitStruct)->DlcRaw &= (vuint16)0xFF20; \
                                                                (pCanMsgTransmitStruct)->DlcRaw |= ((vuint16)CAN_LEN2DLC(len) & (vuint16)0x000F); \
                                                                (pCanMsgTransmitStruct)->TimeStamp = (vuint16)(len)                  /* PRQA S 3412 */ /* MD_Can_3412 */

# define CanMsgTransmitSetData(pCanMsgTransmitStruct, dataByte, msgData) (pCanMsgTransmitStruct)->DataFld[(dataByte)]=(msgData)

/* macros for buffer access */
#define StartRxReadSync()          (VStdSuspendAllInterrupts())
#define EndRxReadSync()            (VStdResumeAllInterrupts())

#define StartRxWriteSync()         (VStdSuspendAllInterrupts())
#define EndRxWriteSync()           (VStdResumeAllInterrupts())

#define StartTxReadSync()
#define EndTxReadSync()

#define StartTxWriteSync()         (VStdSuspendAllInterrupts())
#define EndTxWriteSync()           (VStdResumeAllInterrupts())

#define StartRxWriteCANSync()
#define EndRxWriteCANSync()

#define StartRxReadCANSync()
#define EndRxReadCANSync()

#define StartRxFullCANReadSync(Obj)  (VStdSuspendAllInterrupts())
#define EndRxFullCANReadSync(Obj)    (VStdResumeAllInterrupts())

#define StartRxFullCANWriteSync(obj) (VStdSuspendAllInterrupts())
#define EndRxFullCANWriteSync(obj)   (VStdResumeAllInterrupts())

/* macros for flag access */
#define CanStartFlagWriteSync()    (VStdSuspendAllInterrupts())
#define CanEndFlagWriteSync()      (VStdResumeAllInterrupts())

/* *********************************************************************** */
/* error codes                                                             */
/* *********************************************************************** */
/* error numbers for User Assertions 0x00-0x1f - hardware independed */
# define kErrorTxDlcTooLarge                     ((vuint8)0x01)
# define kErrorTxHdlTooLarge                     ((vuint8)0x02)
# define kErrorIntRestoreTooOften                ((vuint8)0x03)
# define kErrorIntDisableTooOften                ((vuint8)0x04)
# define kErrorChannelHdlTooLarge                ((vuint8)0x05)
# define kErrorInitObjectHdlTooLarge             ((vuint8)0x06)
# if defined( C_KOMMENTAR_VECTOR_RI14 )
/* ##RI-1.1: Object parameters for Tx-Observe functions */
# endif
# define kErrorTxHwHdlTooLarge                   ((vuint8)0x07)
# define kErrorHwObjNotInPolling                 ((vuint8)0x08)
# define kErrorHwHdlTooSmall                     ((vuint8)0x09)
# define kErrorHwHdlTooLarge                     ((vuint8)0x0A)

# define kErrorAccessedInvalidDynObj             ((vuint8)0x0B)
# define kErrorAccessedStatObjAsDyn              ((vuint8)0x0C)
# define kErrorDynObjReleased                    ((vuint8)0x0D)

# define kErrorPollingTaskRecursion              ((vuint8)0x0E)
# define kErrorDisabledChannel                   ((vuint8)0x0F)
# define kErrorDisabledTxMessage                 ((vuint8)0x10)
# define kErrorDisabledCanInt                    ((vuint8)0x11)

# define kErrorCanSleep                          ((vuint8)0x12)
# define kErrorCanOnline                         ((vuint8)0x13)
# define kErrorCanStop                           ((vuint8)0x14)
# define kErrorWrongMask                         ((vuint8)0x15)
# define kErrorWrongId                           ((vuint8)0x16)
# define kErrorNullPointerParameter              ((vuint8)0x17)
# define kErrorRxHdlTooLarge                     ((vuint8)0x18)
# define kErrorNoCanFd                           ((vuint8)0x19)
# define kErrorRxDlcTooLarge                     ((vuint8)0x1A)
/* error numbers for User Assertions 0x20-0x3f - hardware depended */

/* error numbers for Gentool Assertions 0x40-0x5f */
# define kErrorTxROMDLCTooLarge                  ((vuint8)0x40)
# define kErrorWrongHwTxObjHandle                ((vuint8)0x41)
# define kErrorHwToLogTxObjCalculation           ((vuint8)0x42)
# define kErrorWrongCanFdFlag                    ((vuint8)0x43)

/* error numbers for Generation tool Assertions 0x60-0x7f - hardware depended */

/* error numbers for Hardware Assertions 0x80-0x9f */
# define kErrorTxBufferBusy                      ((vuint8)0x80)

/* error numbers for Hardware Assertions 0xa0-0xbf - hardware depended */

/* error numbers for Internal Assertions 0xc0-0xdf */
# define kErrorTxHandleWrong                     ((vuint8)0xC0)
# define kErrorInternalTxHdlTooLarge             ((vuint8)0xC1)
# define kErrorRxHandleWrong                     ((vuint8)0xC2)
# define kErrorTxObjHandleWrong                  ((vuint8)0xC3)
# define kErrorReleasedUnusedDynObj              ((vuint8)0xC4)
# define kErrorTxQueueTooManyHandle              ((vuint8)0xC5)
# define kErrorInternalChannelHdlTooLarge        ((vuint8)0xC6)
# define kErrorInternalDisabledChannel           ((vuint8)0xC7)
# define kErrorInternalDisabledTxMessage         ((vuint8)0xC8)
# define kErrorMailboxHandleWrong                ((vuint8)0xC9)

/* error numbers for Internal Assertions 0xe0-0xff - hardware depended */

/* *********************************************************************** */
/* DummyFunction                                                           */
/* *********************************************************************** */
# if defined( C_DRV_INTERNAL )
#  define CAN_RECEIVE_FCT_DUMMY                  ApplCanRxStructPtrDummy
#  define CAN_RANGE_FCT_DUMMY                    ApplCanRxStructPtrDummy
#  define CAN_BUSOFF_FCT_DUMMY                   ApplCanChannelDummy
#   define CAN_INDICATION_FCT_DUMMY              V_NULL
#   define CAN_PRECOPY_FCT_DUMMY                 V_NULL
#   define CAN_CONFIRMATION_FCT_DUMMY            V_NULL
#   define CAN_PRETRANSMIT_FCT_DUMMY             V_NULL
# endif

# if defined( C_NO_COMPATIBILITY )
# else
/* *********************************************************************** */
/* compatibility defines                                                   */
/* *********************************************************************** */

#  define CAN_TX_DLC(i)                          (CanGetTxDlc(i))
#  define CAN_TX_DATA_PTR(i)                     (CanGetTxDataPtr(i))
#  define CAN_CONFIRMATION_OFFSET(i)             (CanGetConfirmationOffset(i))
#  define CAN_CONFIRMATION_MASK(i)               (CanGetConfirmationMask(i))

#  define CAN_RX_DATA_LEN(i)                     (CanGetRxDataLen(i))
#  define CAN_RX_DATA_PTR(i)                     (CanGetRxDataPtr(i))
#  define CAN_INDICATION_OFFSET(i)               (CanGetIndicationOffset(i))
#  define CAN_INDICATION_MASK(i)                 (CanGetIndicationMask(i))

#  define CanInterruptDisable()                  VStdSuspendAllInterrupts()
#  define CanInterruptRestore()                  VStdResumeAllInterrupts()

#  define ApplCanReceiveDummy0                   ApplCanRxStructPtrDummy
#  define ApplCanReceiveDummy1                   ApplCanChannelDummy

#  define CanGetTxDirectMsg                      (CanGetTxMailbox)

#  define canRxDlcRam                            (canVariableRxDataLen)

#  define CAN_START_INDEX_INIT_OBJ(i)            (CanInitObjectStartIndex[i])
#  define CAN_START_INDEX_TX_OBJ(i)              (CanTxStartIndex[i])
#  define CAN_START_INDEX_RX_OBJ(i)              (CanRxStartIndex[i])

#if defined(CAN_GEN_COM_STACK_LIB) /* == CAN_MSR403 */
#else /* without ComStackLib */

# define Can_GetBaseAddressOfHwChannelData(Index)                       CanHwChannelData[(Index)].CanBaseAddress
# define Can_GetInterruptMask1OfHwChannelData(Index)                    CanHwChannelData[(Index)].CanInterruptMask1
# define Can_GetInterruptMask2OfHwChannelData(Index)                    CanHwChannelData[(Index)].CanInterruptMask2
# define Can_GetInterruptMask3OfHwChannelData(Index)                    CanHwChannelData[(Index)].CanInterruptMask3
# define Can_GetInterruptMask4OfHwChannelData(Index)                    CanHwChannelData[(Index)].CanInterruptMask4

# define Can_GetRxBasicPollingMask1OfHwChannelData(Index)               CanHwChannelData[(Index)].CanRxBasicPollingMask1
# define Can_GetRxBasicPollingMask2OfHwChannelData(Index)               CanHwChannelData[(Index)].CanRxBasicPollingMask2
# define Can_GetRxBasicPollingMask3OfHwChannelData(Index)               CanHwChannelData[(Index)].CanRxBasicPollingMask3
# define Can_GetRxBasicPollingMask4OfHwChannelData(Index)               CanHwChannelData[(Index)].CanRxBasicPollingMask4

# define Can_GetRxFullPollingMask1OfHwChannelData(Index)                CanHwChannelData[(Index)].CanRxFullPollingMask1
# define Can_GetRxFullPollingMask2OfHwChannelData(Index)                CanHwChannelData[(Index)].CanRxFullPollingMask2
# define Can_GetRxFullPollingMask3OfHwChannelData(Index)                CanHwChannelData[(Index)].CanRxFullPollingMask3
# define Can_GetRxFullPollingMask4OfHwChannelData(Index)                CanHwChannelData[(Index)].CanRxFullPollingMask4

# define Can_GetTxPollingMask1OfHwChannelData(Index)                    CanHwChannelData[(Index)].CanTxPollingMask1
# define Can_GetTxPollingMask2OfHwChannelData(Index)                    CanHwChannelData[(Index)].CanTxPollingMask2
# define Can_GetTxPollingMask3OfHwChannelData(Index)                    CanHwChannelData[(Index)].CanTxPollingMask3
# define Can_GetTxPollingMask4OfHwChannelData(Index)                    CanHwChannelData[(Index)].CanTxPollingMask4

# define Can_GetRFFNOfHwChannelData(Index)                              CanHwChannelData[(Index)].CanRFFN
# define Can_GetReservedMBOfHwChannelData(Index)                        CanHwChannelData[(Index)].CanReservedMB
# define Can_GetNumberOfFullConfigurableFiltersOfHwChannelData(Index)   CanHwChannelData[(Index)].CanNumberOfFullConfigurableFilters
# define Can_GetNumberOfFiltersOfHwChannelData(Index)                   CanHwChannelData[(Index)].CanNumberOfFilters
# define Can_GetGlitchFilterOfHwChannelData(Index)                      CanHwChannelData[(Index)].CanGlitchFilter
# define Can_GetFDMailboxMaxWordLengthOfHwChannelData(Index)            CanHwChannelData[(Index)].CanFdMailboxMaxWordLength
# define Can_GetNumberOfMaxMailboxesOfHwChannelData(Index)              CanHwChannelData[(Index)].CanNumberOfMaxMailboxes

# define Can_GetFDHwChannelIndirection(Index)                           CanFDHwChannelIndirection[(Index)]
# define Can_GetFDMailboxMapping(Index)                                 CanFDMailboxMapping[(Index)]

# define Can_GetInitBasicCanIndex(Index)                                CanInitBasicCanIndex[(Index)]
# define Can_GetInitCodeOfInitBasicCan(Index)                           CanInitBasicCan[(Index)].CanInitCode
# define Can_GetInitMaskOfInitBasicCan(Index)                           CanInitBasicCan[(Index)].CanInitMask

# define Can_GetControl1OfInitObject(Index)                             CanInitObject[(Index)].CanControl1
# define Can_GetCBTOfInitObject(Index)                                  CanInitObject[(Index)].CanCBT
# define Can_GetTASDOfInitObject(Index)                                 CanInitObject[(Index)].CanTASD
# define Can_GetFDCBTOfInitObjectFD(Index)                              CanInitObjectFD[(Index)].CanFDCBT
# define Can_GetFDCTRLOfInitObjectFD(Index)                             CanInitObjectFD[(Index)].CanFDCTRL

# define Can_GetProtectedAreaId(Index)                                  CanProtectedAreaId[(Index)]

# define Can_GetRxMsgBuffer(Index)                                      canRxMsgBuffer[(Index)]

# define Can_GetStartModeRequested(Index)           startModeRequested[(Index)]
# define Can_SetStartModeRequested(Index, Value)    startModeRequested[(Index)] = (Value)

#  define Can_GetCanInterruptCounter(Index)          canCanInterruptCounter[(Index)]
#  define Can_GetCanHwObjIndivPolling(ch, Index)     Can_Mailbox[Can_HwObjToMailboxIndirection[CAN_HL_MB_INDIRECTION_STARTINDEX(ch)+Index]].HwObjPolling /* PRQA S 3410,3453 */ /* MD_Can_3410, MD_Can_3453 */
#  define Can_GetPhysToLogChannel(Index)             CanPhysToLogChannel[V_ACTIVE_IDENTITY_LOG][(Index)]

#endif

/* *********************************************************************** */
/* end of compatibility defines                                            */
/* *********************************************************************** */
# endif /* C_NO_COMPATIBILITY */

/* *********************************************************************** */
/* Memory qualifier                                                        */
/* *********************************************************************** */
/* memory qualifier for the CAN controller registers */

#define MEMORY_CAN

/* *********************************************************************** */
/* data types                                                              */
/* *********************************************************************** */

/* declare data type for the queue */
#if defined( C_CPUTYPE_32BIT )
typedef vuint32 tCanQueueElementType;
#endif

#if !defined( tCanTxQueuePadBits )
# define tCanTxQueuePadBits vuint8
#endif
#if defined( C_ENABLE_SLEEP_WAKEUP )
# if defined( C_ENABLE_FLEXCAN_STOP_MODE )
#  if defined( C_ENABLE_WAKEUP_POLLING )
#   define C_DISABLE_CAN_WAKEUP_INTERRUPT
#  else
#   define C_ENABLE_CAN_WAKEUP_INTERRUPT
#  endif
# else
#  if defined( C_ENABLE_WAKEUP_POLLING )
#   error "FlexCAN wakeup polling only possible if STOP mode is used!"
#  endif
# endif
#endif

#if defined( C_ENABLE_ERROR_POLLING )
# define C_DISABLE_CAN_BUSOFF_INTERRUPT
#else
# define C_ENABLE_CAN_BUSOFF_INTERRUPT
#endif

#if (defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_RX_BASICCAN_POLLING )) || \
    (defined( C_ENABLE_RX_FULLCAN_OBJECTS ) && !defined( C_ENABLE_RX_FULLCAN_POLLING ))   || \
    (!defined( C_ENABLE_TX_POLLING )) || (defined( C_ENABLE_INDIVIDUAL_POLLING ))
# define C_ENABLE_CAN_RXTX_INTERRUPT
#else
# define C_DISABLE_CAN_RXTX_INTERRUPT
#endif

#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
    defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
    defined( C_ENABLE_WAKEUP_INTERRUPT )
# define C_HL_ENABLE_CAN_IRQ_DISABLE   
#else
# define C_HL_DISABLE_CAN_IRQ_DISABLE   
#endif 

/* data types for driver function parameters */
V_DEF_VAR_TYPE(V_NONE, vuint16) CanInitHandle;
#if defined( CAN_GEN_COM_STACK_LIB )
#else
V_DEF_VAR_TYPE(V_NONE, vuint16) CanChannelHandle;
#endif

/* CanObjectHandle has to be unsigned! */
V_DEF_VAR_TYPE(V_NONE, vuint16) CanObjectHandle;

V_DEF_VAR_TYPE(V_NONE, vuint16) CanTransmitHandle;
V_DEF_VAR_TYPE(V_NONE, vuint16) CanReceiveHandle;

/* define data type of local signed variables for message handles */
V_DEF_VAR_TYPE(V_NONE, vsintx) CanSignedTxHandle;

V_DEF_VAR_TYPE(V_NONE, vsintx) CanSignedRxHandle;

/* pointer to msgObj & data may point to RAM or CAN cell depend on RX or TX and feature C_ENABLE_HWBUFFER */
/* so the pointers have to be the same for all (far or nothing / far also works for RAM) */
V_DEF_P2SFR_CAN_TYPE(volatile, vuint8)  CanChipDataPtr;
V_DEF_P2SFR_CAN_TYPE(volatile, vuint8)  CanChipMsgPtr;
V_DEF_P2SFR_CAN_TYPE(volatile, vuint8)  CanChipDataPtr8;
V_DEF_P2SFR_CAN_TYPE(volatile, vuint8)  CanChipMsgPtr8;
V_DEF_P2SFR_CAN_TYPE(volatile, vuint16) CanChipDataPtr16;
V_DEF_P2SFR_CAN_TYPE(volatile, vuint16) CanChipMsgPtr16;
V_DEF_P2SFR_CAN_TYPE(volatile, vuint32) CanChipDataPtr32;
V_DEF_P2SFR_CAN_TYPE(volatile, vuint32) CanChipMsgPtr32;

/* up to 5 tables can be defined for the transmission ID. The type and how 
   many tables are needed depends on the CPU bus type and on the ID registers 
   of the CAN controller. E.g. a CPU with a 16-Bit bus and 2 byte ID registers 
   for standard ID needs 1 table and tCanRxId0 of type vuint16. The same CPU
   with 5 byte ID registers for extended ID needs in this case 3 tables and
   tCanRxId0 = vuint16, tCanRxId1 = vuint16 and tCanRxId2 = vuint16. */
#if defined( C_ENABLE_EXTENDED_ID )
V_DEF_VAR_TYPE(V_NONE, vuint32) tCanTxId0;
/* unused by this driver: 
typedef vuint8          tCanTxId1;
typedef vuint8          tCanTxId2;
typedef vuint8          tCanTxId3;
typedef vuint8          tCanTxId4;
*/
#else
V_DEF_VAR_TYPE(V_NONE, vuint16) tCanTxId0;
/* unused by this driver: 
typedef vuint8          tCanTxId1;
typedef vuint8          tCanTxId2;
typedef vuint8          tCanTxId3;
typedef vuint8          tCanTxId4;
*/
#endif

/* type of variable for ID type kCanIdTypeExt or kCanIdTypeStd will be assigned to 
   a variable of this type */
V_DEF_VAR_TYPE(V_NONE, vuint8) tCanIdType;

/* up to 3 tables can be defined for the reception ID. The type and how many
   tables are needed depends on the CPU bus type and on the ID registers of
   the CAN controller. E.g. a CPU with a 16-Bit bus and 2 byte ID registers 
   for standard ID needs 1 table and tCanRxId0 of type vuint16. The same CPU
   with 5 byte ID registers for extended ID needs in this case 3 tables and 
   tCanRxId0 = vuint16, tCanRxId1 = vuint16 and tCanRxId2 = vuint16. */
# if defined C_ENABLE_EXTENDED_ID
V_DEF_VAR_TYPE(V_NONE, vuint32) tCanRxId0;
# else
V_DEF_VAR_TYPE(V_NONE, vuint16) tCanRxId0;
# endif
/* unused by this driver: 
typedef vuint16          tCanRxId1;
typedef vuint16          tCanRxId2;
typedef vuint16          tCanRxId3;
typedef vuint16          tCanRxId4;
*/

typedef vuint8           tCanDlc;

/* stucture of the CAN message object used by CanMsgTransmit() and RxQueue */
typedef struct
{
  vuint16 DlcRaw;
  vuint16 TimeStamp;
  vuint32 IdRaw;
#if defined(C_ENABLE_CAN_FD_FULL)
  vuint8        DataFld[64];
#else
  vuint8        DataFld[8];
#endif
}tCanMsgTransmitStruct;

#if defined( C_ENABLE_CAN_FD_USED )
/* types of the variables that hold the FD flag / BRS flag information */
typedef vuint16          tCanFdType;
typedef vuint16          tCanFdBrsType;
#endif

/* structure with entry for the generated initialisation array */
typedef struct 
{
  vuint32  CanControl1;   /* Control 1 register */
#if defined ( C_ENABLE_EXTENDED_BITTIMING )
  vuint32 CanCBT;         /* CAN Bit Timing Register (CAN_CBT) */
#endif
#if defined( C_ENABLE_TASD )
  vuint32  CanTASD;        /* TASD register */
#endif
}tCanInitObject;

typedef struct 
{
  vuint32 CanFDCBT;
  vuint32 CanFDCTRL;
}tCanInitObjectFD;

typedef struct 
{
  vuint32 CanInitMask;  /* Mask Register */
  vuint32 CanInitCode;  /* Code Register */
}tCanInitBasicCan;

typedef struct
{
  vuint32 CanBaseAddress;
  vuint32 CanInterruptMask1;
#if defined ( C_ENABLE_MB32TO63 ) 
  vuint32 CanInterruptMask2;
#endif
#if defined ( C_ENABLE_MB64TO95 ) 
  vuint32 CanInterruptMask3;
#endif
#if defined ( C_ENABLE_MB96TO127 ) 
  vuint32 CanInterruptMask4;
#endif
#if defined (C_ENABLE_CLASSIC_MAILBOX_LAYOUT)
# if defined ( C_ENABLE_RX_BASICCAN_OBJECTS ) && defined ( C_ENABLE_RX_BASICCAN_POLLING )
  vuint32 CanRxBasicPollingMask1;
#if defined ( C_ENABLE_MB32TO63 )   
  vuint32 CanRxBasicPollingMask2;
#endif  
#  if defined ( C_ENABLE_MB64TO95 ) 
  vuint32 CanRxBasicPollingMask3;
#  endif
#  if defined ( C_ENABLE_MB96TO127 ) 
  vuint32 CanRxBasicPollingMask4;
#  endif
# endif
#endif
#if defined ( C_ENABLE_RX_FULLCAN_OBJECTS ) && defined ( C_ENABLE_RX_FULLCAN_POLLING )
  vuint32 CanRxFullPollingMask1;
#if defined ( C_ENABLE_MB32TO63 )   
  vuint32 CanRxFullPollingMask2;
#endif  
# if defined ( C_ENABLE_MB64TO95 ) 
  vuint32 CanRxFullPollingMask3;
# endif
# if defined ( C_ENABLE_MB96TO127 ) 
  vuint32 CanRxFullPollingMask4;
# endif
#endif
#if defined( C_ENABLE_TX_POLLING )
  vuint32 CanTxPollingMask1;
#if defined ( C_ENABLE_MB32TO63 )   
  vuint32 CanTxPollingMask2;
#endif  
# if defined ( C_ENABLE_MB64TO95 ) 
  vuint32 CanTxPollingMask3;
# endif
# if defined ( C_ENABLE_MB96TO127 ) 
  vuint32 CanTxPollingMask4;
# endif
#endif
  vuint32 CanRFFN;
  vuint8  CanNumberOfFilters;
  vuint8  CanNumberOfFullConfigurableFilters;
#if defined( C_ENABLE_GLITCH_FILTER )
  vuint8  CanGlitchFilter;
#endif
#if defined ( C_ENABLE_CAN_FD_FULL )
  vuint8  CanFdMailboxMaxWordLength;
#endif
#if defined( C_ENABLE_WORKAROUND_ERR005829 )
  vuint8  CanReservedMB;
#endif
  vuint8  CanNumberOfMaxMailboxes;
}tCanHwChannelData;

#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
    defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
    defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
typedef struct
{
  vuint32 flags1;
# if defined ( C_ENABLE_MB32TO63 ) 
  vuint32 flags2;
# endif  
# if defined ( C_ENABLE_MB64TO95 ) 
  vuint32 flags3;
# endif
# if defined ( C_ENABLE_MB96TO127 ) 
  vuint32 flags4;
# endif
  vuint32 canctrl1;  
  vuint16 canmcr;
}tCanLLCanIntOld;

V_DEF_P2VAR_TYPE(V_NONE, tCanLLCanIntOld, VAR_NOINIT) tCanLLCanIntOldPtr;
#endif

typedef struct
{
  vuint16 control;   /* control, status and DLC */
  vuint16 timestamp; /* time stamp */
  vuint32 msgID;     /* message ID */ 
#if defined ( C_ENABLE_CAN_FD_FULL )
  vuint32 data[16];   /* message data */
#else
  vuint32 data[2];   /* message data */
#endif
}tCanRxMsgBuffer;

typedef struct
{
#if defined ( C_ENABLE_CAN_FD_FULL )
  vuint32 data[16];   /* message data */
#else
  vuint32 data[2];
#endif
}tCanTxMsgBuffer;

#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
    defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
    defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )    
V_DEF_VAR_TYPE(V_NONE, tCanLLCanIntOld)              tCanIntOld;
V_DEF_P2VAR_TYPE(V_NONE, tCanLLCanIntOld, V_NONE)  tCanIntOldPtr;
#endif

typedef volatile struct
{
#if defined( C_CPUTYPE_LITTLEENDIAN )
  vuint16  timestamp; /* timestamp: reading timestamp unlocks the current locked mailbox */
  vuint16  control;   /* control, status and DLC */
#endif
  vuint32  msgID;     /* message ID */
#if defined( C_ENABLE_CAN_FD_FULL )
  vuint32  data[16];  /* message data */ 
#else
  vuint32  data[2];   /* message data */
#endif
}tCanMsgObj;
typedef volatile struct
{
#if defined( C_CPUTYPE_LITTLEENDIAN )
  vuint16  canmaxmb;       /* 00 Maximum Message Buffer */
  vuint16  canmcr;         /* 02 Module Configuration Register */
#endif  
  vuint32  control1;       /* 04 CAN Control 1: PRESDIV, RJW, PSEG1, PSEG2, BOFF_MSK, ERR_MSK, CLK_SRC, LPB, TWRN_MSK, RWRN_MSK, SMP, BOFF_REC, T_SYNC, LBUF, LOM and PROPSEG */
  vuint32  timer;          /* 08 Timer */
  vuint32  rsv1;           /* 0C Reserved */
  vuint32  rxmgmask;       /* 10 Rx Global Mask */
  vuint32  rx14mask;       /* 14 Rx 14 Mask */
  vuint32  rx15mask;       /* 18 Rx 15 Mask */
  vuint32  ecr;            /* 1C Error Counter */
  vuint32  estat;          /* 20 Error / Status */
  vuint32  imask2;         /* 24 Interrupt Mask 2 (MB 32 - 63) Register */
  vuint32  imask1;         /* 28 Interrupt Mask 1 (MB  0 - 31) Register */
  vuint32  iflag2;         /* 2C Interrupt Flag 2 (MB 32 - 63) Register */
  vuint32  iflag1;         /* 30 Interrupt Flag 1 (MB  0 - 31) Register */
  vuint32  ctrl2;          /* 34 CAN Control 2: WRMFRZ, RFEN, TASD, MRP, RRS, EACEN */
  vuint32  esr2;           /* 38 IMB, VPS, LPTM */
  vuint32  rsv4[2];        /* 3C - 44 Reserved */
  vuint32  crcr;           /* 44 TXCRC, MBCRC */
  vuint32  rxfgmask;       /* 48 Rx FiFo global mask */
  vuint32  rxfir;          /* 4C Rx FiFo information Register */
  vuint32  cbt;            /* 50 CAN Bit Timing Register */
  vuint32  rsv5[5];        /* 54 - 68 Reserved */
  vuint32  imask4;         /* 68 Interrupt Mask 4 (MB 96 - 127) Register */
  vuint32  imask3;         /* 6C Interrupt Mask 3 (MB 64 -  95) Register */
  vuint32  iflag4;         /* 70 Interrupt Flag 4 (MB 96 - 127) Register */
  vuint32  iflag3;         /* 74 Interrupt Flag 3 (MB 64 -  95) Register */
  vuint32  rsv6[2];        /* 78 - 80 Reserved */
#if defined ( C_ENABLE_MB96TO127 ) /* PRQA S 0883 */ /* MD_Can_0883 */
  tCanMsgObj canObject[128];  /* Buffer for 128 messages */
#elif defined ( C_ENABLE_MB64TO95 )
  tCanMsgObj canObject[96];  /* Buffer for 96 messages */
#elif defined ( C_ENABLE_MB32TO63 )
  tCanMsgObj canObject[64];  /* Buffer for 64 messages */
#else
  tCanMsgObj canObject[32];  /* Buffer for 32 messages */
#endif
}tFlexCAN;

V_DEF_P2SFR_CAN_TYPE(V_NONE, tFlexCAN) tFlexCANPtr;

#if defined( C_SINGLE_RECEIVE_CHANNEL )
//#   define pFlexCAN(x)     ((tFlexCANPtr)((vuint32)(kCanBaseAddress))) /* PRQA S 3453 */ /* MD_Can_3453 */
#else
#   define pFlexCAN(x)    ((tFlexCANPtr)((vuint32)Can_GetBaseAddressOfHwChannelData(x))) /* PRQA S 3453 */ /* MD_Can_3453 */
#endif

typedef volatile struct
{
#if defined ( C_ENABLE_MB96TO127 )
  vuint32 indivRxMask[128]; /* Individual Receive Masks */  
#elif defined ( C_ENABLE_MB64TO95 )
  vuint32 indivRxMask[96]; /* Individual Receive Masks */  
#else
  vuint32 indivRxMask[64]; /* Individual Receive Masks */  
#endif
}tCanRxMask;
V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanRxMask) tCanRxMaskPtr;

typedef volatile struct
{
  vuint32  rxCODE;
  vuint32  rxID;     
  vuint32  rxDATA[2];
  vuint32  rxRSVD[20];
  vuint32  rxIDTAB[128]; 
}tRXFIFO;

typedef volatile struct
{
  vuint32  gfwR;
}tGlitchFilter;

typedef volatile struct
{
  vuint32  mecr;
  vuint32  errIaR;
  vuint32  errIdpR;
  vuint32  errIppR;
  vuint32  rErrAddressR;
  vuint32  rErrDataR;
  vuint32  rErrSyndromR;
  vuint32  errStatusR;
}tParityCheck;

typedef volatile struct
{
  vuint32  fdctrl;
  vuint32  fdcbt;
  vuint32  fdcrc;
}tCanFDRegister;

V_DEF_P2SFR_CAN_TYPE(V_NONE, tRXFIFO) tRXFIFOPtr;
V_DEF_P2SFR_CAN_TYPE(V_NONE, tGlitchFilter) tGlitchFilterPtr;
V_DEF_P2SFR_CAN_TYPE(V_NONE, tParityCheck) tParityCheckPtr;
V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanFDRegister) tCanFDRegisterPtr;

#if defined( C_SINGLE_RECEIVE_CHANNEL )
#   define pRXFIFO(x)           ((tRXFIFOPtr)((vuint32)(kCanBaseAddress) + (vuint32)0x0080)) /* PRQA S 3453 */ /* MD_Can_3453 */
#   define pCanRxMask(x)        ((tCanRxMaskPtr)((vuint32)(kCanBaseAddress) + (vuint32)0x0880)) /* PRQA S 3453 */ /* MD_Can_3453 */
#   define pCanGlitchFilter(x)  ((tGlitchFilterPtr)((vuint32)(kCanBaseAddress) + (vuint32)0x09E0)) /* PRQA S 3453 */ /* MD_Can_3453 */
#   define pCanParityCheck(x)   ((tParityCheckPtr)((vuint32)(kCanBaseAddress) + (vuint32)0x0AE0)) /* PRQA S 3453 */ /* MD_Can_3453 */
#   define pCanFDRegister(x)    ((tCanFDRegisterPtr)((vuint32)(kCanBaseAddress) + (vuint32)0x0C00)) /* PRQA S 3453 */ /* MD_Can_3453 */
#else /* C_SINGLE_RECEIVE_CHANNEL */
#  define pRXFIFO(x)           ((tRXFIFOPtr)((vuint32)Can_GetBaseAddressOfHwChannelData(x) + (vuint32)0x0080)) /* PRQA S 3453 */ /* MD_Can_3453 */
#  define pCanRxMask(x)        ((tCanRxMaskPtr)((vuint32)Can_GetBaseAddressOfHwChannelData(x) + (vuint32)0x0880)) /* PRQA S 3453 */ /* MD_Can_3453 */
#  define pCanGlitchFilter(x)  ((tGlitchFilterPtr)((vuint32)Can_GetBaseAddressOfHwChannelData(x) + (vuint32)0x09E0)) /* PRQA S 3453 */ /* MD_Can_3453 */
#  define pCanParityCheck(x)   ((tParityCheckPtr)((vuint32)Can_GetBaseAddressOfHwChannelData(x) + (vuint32)0x0AE0)) /* PRQA S 3453 */ /* MD_Can_3453 */
#  define pCanFDRegister(x)    ((tCanFDRegisterPtr)((vuint32)Can_GetBaseAddressOfHwChannelData(x) + (vuint32)0x0C00)) /* PRQA S 3453 */ /* MD_Can_3453 */
#endif /* C_SINGLE_RECEIVE_CHANNEL */

#if defined ( C_SINGLE_RECEIVE_CHANNEL )
#  define CAN_INT_MASK1(x) kCanIntMask1 /* PRQA S 3453 */ /* MD_Can_3453 */
#  if defined ( C_ENABLE_MB32TO63 )
#  define CAN_INT_MASK2(x) kCanIntMask2 /* PRQA S 3453 */ /* MD_Can_3453 */
#  endif
#  if defined ( C_ENABLE_MB64TO95 )
#   define CAN_INT_MASK3(x) kCanIntMask3 /* PRQA S 3453 */ /* MD_Can_3453 */
#  endif
#  if defined ( C_ENABLE_MB96TO127 ) 
#   define CAN_INT_MASK4(x) kCanIntMask4 /* PRQA S 3453 */ /* MD_Can_3453 */
#  endif
#  if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && defined( C_ENABLE_RX_BASICCAN_POLLING )
#   define CAN_RXBASIC_POLL_MASK1(x) kCanRxBasicPollingMask1 /* PRQA S 3453 */ /* MD_Can_3453 */
#   if defined ( C_ENABLE_MB32TO63 )
#    define CAN_RXBASIC_POLL_MASK2(x) kCanRxBasicPollingMask2 /* PRQA S 3453 */ /* MD_Can_3453 */
#   endif
#   if defined ( C_ENABLE_MB64TO95 )
#    define CAN_RXBASIC_POLL_MASK3(x) kCanRxBasicPollingMask3 /* PRQA S 3453 */ /* MD_Can_3453 */
#   endif
#   if defined ( C_ENABLE_MB96TO127 )
#    define CAN_RXBASIC_POLL_MASK4(x) kCanRxBasicPollingMask4 /* PRQA S 3453 */ /* MD_Can_3453 */
#   endif
#  endif
#  if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) && defined( C_ENABLE_RX_FULLCAN_POLLING )
#   define CAN_RXFULL_POLL_MASK1(x) kCanRxFullPollingMask1 /* PRQA S 3453 */ /* MD_Can_3453 */
#   if defined ( C_ENABLE_MB32TO63 )
#    define CAN_RXFULL_POLL_MASK2(x) kCanRxFullPollingMask2 /* PRQA S 3453 */ /* MD_Can_3453 */
#   endif
#   if defined ( C_ENABLE_MB64TO95 )
#    define CAN_RXFULL_POLL_MASK3(x) kCanRxFullPollingMask3 /* PRQA S 3453 */ /* MD_Can_3453 */
#   endif
#   if defined ( C_ENABLE_MB96TO127 )
#    define CAN_RXFULL_POLL_MASK4(x) kCanRxFullPollingMask4 /* PRQA S 3453 */ /* MD_Can_3453 */
#   endif
#  endif
#  if defined( C_ENABLE_TX_POLLING )
#   define CAN_TX_POLL_MASK1(x) kCanTxPollingMask1 /* PRQA S 3453 */ /* MD_Can_3453 */
#   if defined ( C_ENABLE_MB32TO63 )
#    define CAN_TX_POLL_MASK2(x) kCanTxPollingMask2 /* PRQA S 3453 */ /* MD_Can_3453 */
#   endif
#   if defined ( C_ENABLE_MB64TO95 )
#    define CAN_TX_POLL_MASK3(x) kCanTxPollingMask3 /* PRQA S 3453 */ /* MD_Can_3453 */
#   endif
#   if defined ( C_ENABLE_MB96TO127 )
#    define CAN_TX_POLL_MASK4(x) kCanTxPollingMask4 /* PRQA S 3453 */ /* MD_Can_3453 */
#   endif
#  endif
#  define RFFN_VALUE(x) kCanRFFN /* PRQA S 3453 */ /* MD_Can_3453 */
#  define NUMBER_OF_FILTERS(x) kCanNumberOfFilters /* PRQA S 3453 */ /* MD_Can_3453 */
#  define NUMBER_OF_FULL_CONFIGURABLE_FILTERS(x) kCanNumberOfFullConfigurableFilters /* PRQA S 3453 */ /* MD_Can_3453 */
#  if defined( C_ENABLE_GLITCH_FILTER )
#   define GLITCH_FILTER_WIDTH(x) (vuint32)kCanGlitchFilter /* PRQA S 3453 */ /* MD_Can_3453 */
#  endif
#  if defined ( C_ENABLE_CAN_FD_FULL )
#   define CANFD_MAILBOX_MAX_WORD_LENGTH(x) kCanFDMailboxMaxWordLength /* PRQA S 3453 */ /* MD_Can_3453 */
#  endif
#  if defined( C_ENABLE_WORKAROUND_ERR005829 )
#   define INDEX_RSVD_MB(x) kCanReservedMB /* PRQA S 3453 */ /* MD_Can_3453 */
#  endif
#  if defined ( C_ENABLE_ASYM_MAILBOXES )
#   define NUMBER_OF_MAX_MAILBOXES(x) kCanNumberOfMaxMailboxes /* PRQA S 3453 */ /* MD_Can_3453 */
#  endif
#else /* C_SINGLE_RECEIVE_CHANNEL */
# define CAN_INT_MASK1(x) Can_GetInterruptMask1OfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
# if defined ( C_ENABLE_MB32TO63 )
#  define CAN_INT_MASK2(x) Can_GetInterruptMask2OfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
# endif
# if defined ( C_ENABLE_MB64TO95 )
#  define CAN_INT_MASK3(x) Can_GetInterruptMask3OfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
# endif
# if defined ( C_ENABLE_MB96TO127 )
#  define CAN_INT_MASK4(x) Can_GetInterruptMask4OfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
# endif
# if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && defined( C_ENABLE_RX_BASICCAN_POLLING )
#  define CAN_RXBASIC_POLL_MASK1(x) Can_GetRxBasicPollingMask1OfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
#  if defined ( C_ENABLE_MB32TO63 )
#   define CAN_RXBASIC_POLL_MASK2(x) Can_GetRxBasicPollingMask2OfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
#  endif
#  if defined ( C_ENABLE_MB64TO95 )
#   define CAN_RXBASIC_POLL_MASK3(x) Can_GetRxBasicPollingMask3OfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
#  endif
#  if defined ( C_ENABLE_MB96TO127 )
#   define CAN_RXBASIC_POLL_MASK4(x) Can_GetRxBasicPollingMask4OfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
#  endif
# endif
# if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) && defined( C_ENABLE_RX_FULLCAN_POLLING )
#  define CAN_RXFULL_POLL_MASK1(x) Can_GetRxFullPollingMask1OfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
#  if defined ( C_ENABLE_MB32TO63 )
#   define CAN_RXFULL_POLL_MASK2(x) Can_GetRxFullPollingMask2OfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
#  endif
#  if defined ( C_ENABLE_MB64TO95 )
#   define CAN_RXFULL_POLL_MASK3(x) Can_GetRxFullPollingMask3OfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
#  endif
#  if defined ( C_ENABLE_MB96TO127 )
#   define CAN_RXFULL_POLL_MASK4(x) Can_GetRxFullPollingMask4OfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
#  endif
# endif
# if defined( C_ENABLE_TX_POLLING )
#  define CAN_TX_POLL_MASK1(x) Can_GetTxPollingMask1OfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
#  if defined ( C_ENABLE_MB32TO63 )
#  define CAN_TX_POLL_MASK2(x) Can_GetTxPollingMask2OfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
#  endif
#  if defined ( C_ENABLE_MB64TO95 )
#   define CAN_TX_POLL_MASK3(x) Can_GetTxPollingMask3OfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
#  endif
#  if defined ( C_ENABLE_MB96TO127 )
#   define CAN_TX_POLL_MASK4(x) Can_GetTxPollingMask4OfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
#  endif
# endif
# define RFFN_VALUE(x) Can_GetRFFNOfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
# define NUMBER_OF_FILTERS(x) Can_GetNumberOfFiltersOfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
# define NUMBER_OF_FULL_CONFIGURABLE_FILTERS(x) Can_GetNumberOfFullConfigurableFiltersOfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
# if defined( C_ENABLE_GLITCH_FILTER )
#  define GLITCH_FILTER_WIDTH(x) (vuint32)Can_GetGlitchFilterOfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
# endif
# if defined ( C_ENABLE_CAN_FD_FULL )
#  define CANFD_MAILBOX_MAX_WORD_LENGTH(x) Can_GetFDMailboxMaxWordLengthOfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
# endif
# if defined( C_ENABLE_WORKAROUND_ERR005829 )
#  define INDEX_RSVD_MB(x) Can_GetReservedMBOfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
# endif
# if defined ( C_ENABLE_ASYM_MAILBOXES )
#  define NUMBER_OF_MAX_MAILBOXES(x) Can_GetNumberOfMaxMailboxesOfHwChannelData(x) /* PRQA S 3453 */ /* MD_Can_3453 */
# endif
#endif /* C_SINGLE_RECEIVE_CHANNEL */

#if defined ( C_ENABLE_CAN_FD_FULL )
# define LOCAL_MAILBOX_ACCESS(hwCh, hwObjHandle, structMember)     ((tCanMsgObj*)(Can_GetFDMailboxMapping(Can_GetFDHwChannelIndirection((hwCh))+(hwObjHandle))))->structMember /* PRQA S 3410,3453 */ /* MD_Can_3410, MD_Can_3453 */
# define GLOBAL_MAILBOX_ACCESS(hwCh, hwObjHandle, structMember)    ((tCanMsgObj*)(Can_GetFDMailboxMapping(Can_GetFDHwChannelIndirection((hwCh))+(hwObjHandle))))->structMember /* PRQA S 3410,3453 */ /* MD_Can_3410, MD_Can_3453 */
#else
//# define LOCAL_MAILBOX_ACCESS(hwCh, hwObjHandle, structMember)      pFlexCANLocal->canObject[(hwObjHandle)].structMember /* PRQA S 3410,3453 */ /* MD_Can_3410, MD_Can_3453 */
//# define GLOBAL_MAILBOX_ACCESS(hwCh, hwObjHandle, structMember)     pFlexCAN((hwCh))->canObject[(hwObjHandle)].structMember /* PRQA S 3410,3453 */ /* MD_Can_3410, MD_Can_3453 */
#endif

#define CANSFR_TYPE        vuint32

typedef struct
{
  CanChipDataPtr     pChipData;
  CanTransmitHandle  Handle;
/* CPU-specific part */
  CanChipMsgPtr   pChipMsgObj;
} tCanTxInfoStruct;

/* ##RI-1.10 Common Callbackfunction in TxInterrupt */
typedef struct
{
  CanChannelHandle   Channel;
  CanTransmitHandle  Handle;
/* CPU-specific part */
# if defined( C_ENABLE_CAN_TX_CONF_MSG_ACCESS )
  CanChipDataPtr  pChipData;
  CanChipMsgPtr   pChipMsgObj;
# endif
} tCanTxConfInfoStruct;

typedef struct
{
  CanChannelHandle  Channel;
  CanChipMsgPtr     pChipMsgObj;
  CanChipDataPtr    pChipData;
  CanReceiveHandle  Handle;
/* CPU-specific part */
} tCanRxInfoStruct;

typedef tCanRxInfoStruct          *CanRxInfoStructPtr;
typedef tCanTxInfoStruct          CanTxInfoStruct;
/* ##RI-1.10 Common Callbackfunction in TxInterrupt */
typedef tCanTxConfInfoStruct      *CanTxInfoStructPtr;
typedef tCanMsgTransmitStruct     *CanMsgTransmitStructPtr;

/* types of application functions called by driver --------------------------- */
typedef C_CALLBACK_1 vuint8   (C_CALLBACK_2 *ApplCanMsgRcvFct)    (CanRxInfoStructPtr rxStruct);
typedef C_CALLBACK_1 vuint8   (C_CALLBACK_2 *ApplRangeFct)        (CanRxInfoStructPtr rxStruct);
typedef C_CALLBACK_1 vuint8   (C_CALLBACK_2 *ApplPrecopyFct)      (CanRxInfoStructPtr rxStruct);
typedef C_CALLBACK_1 void     (C_CALLBACK_2 *ApplIndicationFct)   (CanReceiveHandle rxObject);
typedef C_CALLBACK_1 void     (C_CALLBACK_2 *ApplConfirmationFct) (CanTransmitHandle txObject);
typedef C_CALLBACK_1 vuint8   (C_CALLBACK_2 *ApplPreTransmitFct)  (CanTxInfoStruct txStruct);
typedef C_CALLBACK_1 void     (C_CALLBACK_2 *ApplChannelFct)      (CAN_CHANNEL_CANTYPE_ONLY);

typedef struct
{
  tCanRxId0           Id0;
# if (kCanNumberOfUsedCanRxIdTables > 1)
  tCanRxId1           Id1;
# endif
# if (kCanNumberOfUsedCanRxIdTables > 2)
  tCanRxId2           Id2;
# endif
# if (kCanNumberOfUsedCanRxIdTables > 3)
  tCanRxId3           Id3;
# endif
# if (kCanNumberOfUsedCanRxIdTables > 4)
  tCanRxId4           Id4;
# endif
} tCanStructRxIdType;

# if defined( C_DRV_INTERNAL )
typedef struct
{
  ApplChannelFct      ApplCanWakeUpFct;
  ApplCanMsgRcvFct    ApplCanMsgReceivedFct;
  ApplRangeFct        ApplCanRangeFct[4];
  ApplChannelFct      ApplCanBusOffFct;
  ApplConfirmationFct ApplCanCancelNotificationFct;
  ApplChannelFct      ApplCanMsgTransmitCancelNotifyFct;
  tCanStructRxIdType  RangeMask[4];
  tCanStructRxIdType  RangeCode[4];
  vuint16             RangeActiveFlag;
  tCanIdType          RangeIdType[4];
} tCanChannelObject;
# endif

/* datatypes for indication and confirmation flags */
# if defined( C_ENABLE_CONFIRMATION_FLAG )
union CanConfirmationBits
{    /* PRQA S 0750 */ /* MD_Can_0750 */
  vuint8         _c[kCanNumberOfConfBytes];
#  if defined( V_CPUTYPE_BITARRAY_32BIT )
#   if kCanNumberOfConfFlags > 16
  struct _c_bits32 w[kCanNumberOfConfDWords];
#   elif kCanNumberOfConfFlags > 8
  struct _c_bits16 w[kCanNumberOfConfWords];
#   else
  struct _c_bits8  w[1];
#   endif
#  else
#   if kCanNumberOfConfFlags > 8
  struct _c_bits16 w[kCanNumberOfConfWords];
#   else
  struct _c_bits8  w[1];
#   endif
#  endif
};
# endif

# if defined( C_ENABLE_INDICATION_FLAG )
union CanIndicationBits
{    /* PRQA S 0750 */ /* MD_Can_0750 */
  vuint8         _c[kCanNumberOfIndBytes];
#  if defined( V_CPUTYPE_BITARRAY_32BIT )
#   if kCanNumberOfIndFlags > 16
  struct _c_bits32 w[kCanNumberOfIndDWords];
#   elif kCanNumberOfIndFlags > 8
  struct _c_bits16 w[kCanNumberOfIndWords];
#   else
  struct _c_bits8  w[1];
#   endif
#  else
#   if kCanNumberOfIndFlags > 8
  struct _c_bits16 w[kCanNumberOfIndWords];
#   else
  struct _c_bits8 w[1];
#   endif
#  endif
};
# endif

# if defined( C_ENABLE_RX_QUEUE )
/* struct for receive-Queue. Should correspond to t_MsgObject */
typedef struct
{
  CanReceiveHandle      Handle;
  CanChannelHandle      Channel;
  tCanMsgTransmitStruct CanChipMsgObj;
}
tCanRxQueueObject;

/* the queue */
typedef struct
{
  tCanRxQueueObject canRxQueueBuf[kCanRxQueueSize];  /* buffer for msg and handle */
  volatile vuintx   canRxQueueWriteIndex;            /* index in canRxQueueBuf */
  volatile vuintx   canRxQueueReadIndex;             /* index in canRxQueueBuf */
  volatile vuintx   canRxQueueCount;                 /* count of messages in canRxQueueBuf  */
}
tCanRxQueue;
# endif

typedef struct
{
  CanObjectHandle HwObjHandle;
  CanObjectHandle HwObjCount;
# if defined( C_ENABLE_CAN_FD_FULL )
  vuint8 HwObjMaxDataLen;
# endif
# if defined( C_ENABLE_INDIVIDUAL_POLLING )
  vuint8 HwObjPolling;
# endif
} tCanMailbox;

/* *********************************************************************** */
/* CAN-Hardware Data Definitions                                           */
/* *********************************************************************** */

/* *********************************************************************** */
/* External Declarations                                                   */
/* *********************************************************************** */

/*  CAN driver version */
/* ROM CATEGORY 4 START */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kCanMainVersion;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kCanSubVersion;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kCanBugFixVersion;
/* ROM CATEGORY 4 END */

# if defined( C_ENABLE_PRECOPY_FCT )
/* RAM CATEGORY 1 START */
extern volatile CanReceiveHandle canRxHandle[kCanNumberOfChannels];
/* RAM CATEGORY 1 END */
# endif

# if defined( C_ENABLE_CONFIRMATION_FLAG )
/* RAM CATEGORY 1 START */
V_MEMRAM0 extern volatile V_MEMRAM1_NEAR union CanConfirmationBits V_MEMRAM2_NEAR CanConfirmationFlags;              /* PRQA S 0759 */ /* MD_Can_0750 */
/* RAM CATEGORY 1 END */
# endif

# if defined( C_ENABLE_INDICATION_FLAG )
/* RAM CATEGORY 1 START */
V_MEMRAM0 extern volatile V_MEMRAM1_NEAR union CanIndicationBits   V_MEMRAM2_NEAR CanIndicationFlags;                /* PRQA S 0759 */ /* MD_Can_0750 */
/* RAM CATEGORY 1 END */
# endif

# if defined( C_ENABLE_CONFIRMATION_FCT ) && \
    defined( C_ENABLE_DYN_TX_OBJECTS )  && \
    defined( C_ENABLE_TRANSMIT_QUEUE )
/* RAM CATEGORY 3 START */
extern CanTransmitHandle          confirmHandle[kCanNumberOfChannels];
/* RAM CATEGORY 3 END */
# endif

/* ##RI1.4 - 3.31: Dynamic Receive DLC */
# if defined( C_ENABLE_VARIABLE_RX_DATALEN )
#  if ( kCanNumberOfRxObjects > 0 )
/* RAM CATEGORY 1 START */
extern volatile vuint8 canVariableRxDataLen[kCanNumberOfRxObjects];
/* RAM CATEGORY 1 END */
#  endif
# endif

/* RAM CATEGORY 1 START */
extern CanChipDataPtr canRDSRxPtr[kCanNumberOfChannels];
/* RAM CATEGORY 1 END */
/* RAM CATEGORY 1 START */
extern CanChipDataPtr canRDSTxPtr[kCanNumberOfTxMailboxes];
/* RAM CATEGORY 1 END */

#if defined(C_ENABLE_CAN_FD_FULL)
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 CanDlcToFrameLenght[16];
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 CanMessageLengthToDlc[65];
#endif

/* *********************************************************************** */
/* Data structures filled with data by parameter generating tool           */
/* *********************************************************************** */
# if defined( C_DRV_INTERNAL )
/* structures for init and common objects ----------------------- */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#  else
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 tCanChannelObject   V_MEMROM2 CanChannelObject[kCanNumberOfChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 4 START */
V_MEMROM0 extern V_MEMROM1 vuint8              V_MEMROM2 CanInitObjectStartIndex[kCanNumberOfChannels+1];
/* ROM CATEGORY 4 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanTransmitHandle   V_MEMROM2 CanTxDynRomStartIndex[kCanNumberOfChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanTransmitHandle   V_MEMROM2 CanTxDynRamStartIndex[kCanNumberOfChannels+1];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle    V_MEMROM2 CanRxBasicStartIndex[kCanNumberOfChannels+1];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle    V_MEMROM2 CanRxFullStartIndex[kCanNumberOfHwChannels+1];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 2 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanLogMailboxTxStartIndex[kCanNumberOfHwChannels+1];
/* ROM CATEGORY 2 END */

/* ROM CATEGORY 2 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 Can_MailboxTxStartIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 2 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 Can_MailboxRxFullStartIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 Can_MailboxRxBasicStartIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 4 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 Can_MailboxUnusedStartIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 4 END */
/* ROM CATEGORY 2 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 Can_MailboxTxStopIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 2 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 Can_MailboxRxFullStopIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 Can_MailboxRxBasicStopIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 4 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 Can_MailboxUnusedStopIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 4 END */

/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 Can_MailboxMsgTransmitIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
#   if defined( C_KOMMENTAR_VECTOR_RI14 )
/* ##RI-1.2: Priority of hardware transmit objects */
#   endif
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 Can_MailboxTxNormalIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 vsintx              V_MEMROM2 CanTxOffsetMailboxToLog[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */

#   if defined( C_ENABLE_HW_OBJ_BASICCAN_TBL )
/* ROM CATEGORY 2 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanNumberOfHwObjPerBasicCan[kCanNumberOfChannels];
/* ROM CATEGORY 2 END */
#   endif

#  endif  /* C_SINGLE_RECEIVE_CHANNEL */

# endif /* C_DRV_INTERNAL */

# if defined( C_SINGLE_RECEIVE_CHANNEL )
# else
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanTransmitHandle   V_MEMROM2 CanTxStartIndex[kCanNumberOfChannels+1];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 2 START */
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle    V_MEMROM2 CanRxStartIndex[kCanNumberOfChannels+1];
/* ROM CATEGORY 2 END */
# endif

/* ROM generated */

# if ( kCanNumberOfTxObjects > 0 )
#   if defined( C_DRV_INTERNAL )
/* structures for transmit objects ----------------------- */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 tCanTxId0 V_MEMROM2       CanTxId0[kCanNumberOfTxObjects];
#    if (kCanNumberOfUsedCanTxIdTables > 1)
V_MEMROM0 extern V_MEMROM1 tCanTxId1 V_MEMROM2       CanTxId1[kCanNumberOfTxObjects];
#    endif
#    if (kCanNumberOfUsedCanTxIdTables > 2)
V_MEMROM0 extern V_MEMROM1 tCanTxId2 V_MEMROM2       CanTxId2[kCanNumberOfTxObjects];
#    endif
#    if (kCanNumberOfUsedCanTxIdTables > 3)
V_MEMROM0 extern V_MEMROM1 tCanTxId3 V_MEMROM2       CanTxId3[kCanNumberOfTxObjects];
#    endif
#    if (kCanNumberOfUsedCanTxIdTables > 4)
V_MEMROM0 extern V_MEMROM1 tCanTxId4 V_MEMROM2       CanTxId4[kCanNumberOfTxObjects];
#    endif

#    if defined( C_ENABLE_MIXED_ID )
#    endif
/* ROM CATEGORY 1 END */
#   endif /* C_DRV_INTERNAL */

/* ROM CATEGORY 2 START */
#   if defined( C_ENABLE_PART_OFFLINE )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2          CanTxSendMask[kCanNumberOfTxObjects];
#   endif
/* ROM CATEGORY 2 END */

/* ROM CATEGORY 1 START */
#   if defined( C_ENABLE_CAN_FD_USED )
V_MEMROM0 extern V_MEMROM1 tCanFdType V_MEMROM2      CanTxFdType[kCanNumberOfTxObjects];
#   endif
#   if defined( C_ENABLE_CAN_FD_FULL )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2          CanTxMessageLength[kCanNumberOfTxObjects];
#   endif
V_MEMROM0 extern V_MEMROM1 tCanDlc V_MEMROM2         CanTxDLC[kCanNumberOfTxObjects];
V_MEMROM0 extern V_MEMROM1 TxDataPtr V_MEMROM2       CanTxDataPtr[kCanNumberOfTxObjects];

#   if defined( C_ENABLE_CONFIRMATION_FLAG )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2          CanConfirmationOffset[kCanNumberOfTxObjects];
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2          CanConfirmationMask[kCanNumberOfTxObjects];
#   endif
#   if defined( C_ENABLE_CONFIRMATION_FCT )
V_MEMROM0 extern V_MEMROM1 ApplConfirmationFct V_MEMROM2 CanTxApplConfirmationPtr[kCanNumberOfTxObjects];
#   endif
#   if defined( C_ENABLE_PRETRANSMIT_FCT )
V_MEMROM0 extern V_MEMROM1 ApplPreTransmitFct  V_MEMROM2 CanTxApplPreTransmitPtr[kCanNumberOfTxObjects];
#   endif
/* ROM CATEGORY 1 END */

#   if defined( C_ENABLE_TX_FULLCAN_OBJECTS )
/* ROM CATEGORY 2 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle V_MEMROM2 CanTxMailbox[kCanNumberOfTxObjects];
/* ROM CATEGORY 2 END */
#   endif

#   if defined( C_SINGLE_RECEIVE_CHANNEL )
#   else
#    if ( kCanNumberOfTxObjects > 0 )
/* ROM CATEGORY 2 START */
V_MEMROM0 extern V_MEMROM1 CanChannelHandle    V_MEMROM2 CanTxMsgHandleToChannel[kCanNumberOfTxObjects];
/* ROM CATEGORY 2 END */
#    endif
#   endif /* C_SINGLE_RECEIVE_CHANNEL */

#   if defined( C_ENABLE_MULTI_ECU_PHYS )
/* ROM CATEGORY 4 START */
V_MEMROM0 extern V_MEMROM1 tVIdentityMsk V_MEMROM2      CanTxIdentityAssignment[kCanNumberOfTxObjects];
/* ROM CATEGORY 4 END */
#   endif

#  if defined( C_ENABLE_TRANSMIT_QUEUE )
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
/* ROM CATEGORY 1 START */
/* pad bits added before the current channel position */
V_MEMROM0 extern  V_MEMROM1 tCanTxQueuePadBits V_MEMROM2 CanTxQueuePadBits[kCanNumberOfChannels];

/* start / stop indices for the element search */
V_MEMROM0 extern V_MEMROM1 CanSignedTxHandle V_MEMROM2 CanTxQueueStartIndex[kCanNumberOfChannels + 1];
/* ROM CATEGORY 1 END */
#endif
#  endif

# endif /* ( kCanNumberOfTxObjects > 0 ) */

/* structures for basic and full can receive objects ----------------------- */

# if ( kCanNumberOfRxObjects > 0 )
#  if defined( C_DRV_INTERNAL )
/* ROM CATEGORY 1 START */
#   if defined( C_SEARCH_HASH ) ||\
      defined( C_SEARCH_INDEX )
#    if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
V_MEMROM0 extern V_MEMROM1 tCanRxId0 V_MEMROM2       CanRxId0[kCanNumberOfRxFullCANObjects+kCanNumberOfRxDynBasicCANObjects];
#     if (kCanNumberOfUsedCanRxIdTables > 1)
V_MEMROM0 extern V_MEMROM1 tCanRxId1 V_MEMROM2       CanRxId1[kCanNumberOfRxFullCANObjects+kCanNumberOfRxDynBasicCANObjects];
#     endif
#     if (kCanNumberOfUsedCanRxIdTables > 2)
V_MEMROM0 extern V_MEMROM1 tCanRxId2 V_MEMROM2       CanRxId2[kCanNumberOfRxFullCANObjects+kCanNumberOfRxDynBasicCANObjects];
#     endif
#     if (kCanNumberOfUsedCanRxIdTables > 3)
V_MEMROM0 extern V_MEMROM1 tCanRxId3 V_MEMROM2       CanRxId3[kCanNumberOfRxFullCANObjects+kCanNumberOfRxDynBasicCANObjects];
#     endif
#     if (kCanNumberOfUsedCanRxIdTables > 4)
V_MEMROM0 extern V_MEMROM1 tCanRxId4 V_MEMROM2       CanRxId4[kCanNumberOfRxFullCANObjects+kCanNumberOfRxDynBasicCANObjects];
#     endif

#     if defined( C_ENABLE_MIXED_ID )
V_MEMROM0 extern V_MEMROM1 tCanIdType V_MEMROM2      CanRxIdType[kCanNumberOfRxFullCANObjects+kCanNumberOfRxDynBasicCANObjects];
#     endif
#    endif /* C_ENABLE_RX_FULLCAN_OBJECTS */
#   else   /* C_SEARCH_HASH */
V_MEMROM0 extern V_MEMROM1 tCanRxId0 V_MEMROM2       CanRxId0[kCanNumberOfRxObjects];
#    if (kCanNumberOfUsedCanRxIdTables > 1)
V_MEMROM0 extern V_MEMROM1 tCanRxId1 V_MEMROM2       CanRxId1[kCanNumberOfRxObjects];
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 2)
V_MEMROM0 extern V_MEMROM1 tCanRxId2 V_MEMROM2       CanRxId2[kCanNumberOfRxObjects];
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 3)
V_MEMROM0 extern V_MEMROM1 tCanRxId3 V_MEMROM2       CanRxId3[kCanNumberOfRxObjects];
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 4)
V_MEMROM0 extern V_MEMROM1 tCanRxId4 V_MEMROM2       CanRxId4[kCanNumberOfRxObjects];
#    endif

#    if defined( C_ENABLE_MIXED_ID )
V_MEMROM0 extern V_MEMROM1 tCanIdType V_MEMROM2      CanRxIdType[kCanNumberOfRxObjects];
#    endif
#   endif  /* C_SEARCH_HASH */

#   if defined( C_SEARCH_HASH )
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle V_MEMROM2     CanRxMsgIndirection[kHashSearchListCount + kHashSearchListCountEx + kCanNumberOfRxFullCANObjects + kCanNumberOfRxDynBasicCANObjects];
#   else
#    if defined( C_SEARCH_INDEX )
 /*  Size of array CanRxMsgIndirection is zero if index search and no Rx FullCANs are used; ESCAN00059562 */
#     if defined (C_ENABLE_RX_FULLCAN_OBJECTS)
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle V_MEMROM2     CanRxMsgIndirection[kCanNumberOfRxFullCANObjects + kCanNumberOfRxDynBasicCANObjects];
#     endif
#    else
#     if defined( C_ENABLE_RX_MSG_INDIRECTION )
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle V_MEMROM2     CanRxMsgIndirection[kCanNumberOfRxObjects];
#     endif
#    endif
#   endif

#   if defined( C_SEARCH_HASH )
#    if defined( C_ENABLE_EXTENDED_ID )
#     if( kHashSearchListCountEx > 0)
V_MEMROM0 extern V_MEMROM1 vuint32 V_MEMROM2              CanRxHashIdEx[kHashSearchListCountEx];
#     endif /* (kHashSearchListCountEx > 0) */
#     if defined( C_ENABLE_MIXED_ID )
#      if( kHashSearchListCount > 0)
V_MEMROM0 extern V_MEMROM1 vuint16 V_MEMROM2              CanRxHashId[kHashSearchListCount];
#      endif
#     endif
#    else
#     if( kHashSearchListCount > 0)
V_MEMROM0 extern V_MEMROM1 vuint16 V_MEMROM2              CanRxHashId[kHashSearchListCount];
#     endif
#    endif
#   endif

#   if defined( C_SEARCH_INDEX )
#    if defined( C_SINGLE_RECEIVE_CHANNEL )
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle V_MEMROM2     CanRxIndexTbl[2048];
#    else
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle V_MEMROM2     CanRxIndexTbl[kCanNumberOfChannels][2048];
#    endif
#   endif
#   if defined( C_ENABLE_MULTI_ECU_PHYS )
V_MEMROM0 extern V_MEMROM1 tVIdentityMsk V_MEMROM2        CanRxIdentityAssignment[kCanNumberOfRxObjects];
#   endif

#   if defined( C_ENABLE_RX_QUEUE_RANGE )
#    if defined( C_ENABLE_RANGE_0 )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2               CanRxQueueRange0[kCanNumberOfChannels];
#    endif
#    if defined( C_ENABLE_RANGE_1 )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2               CanRxQueueRange1[kCanNumberOfChannels];
#    endif
#    if defined( C_ENABLE_RANGE_2 )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2               CanRxQueueRange2[kCanNumberOfChannels];
#    endif
#    if defined( C_ENABLE_RANGE_3 )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2               CanRxQueueRange3[kCanNumberOfChannels];
#    endif
#   endif
/* ROM CATEGORY 1 END */

/* ROM CATEGORY 4 START */
#   if defined( C_ENABLE_MULTIPLE_BASICCAN ) && \
       defined( C_ENABLE_GEN_CHECK )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2               CanNumberOfBasicCAN[kCanNumberOfChannels];
#   endif
/* ROM CATEGORY 4 END */

#  endif /* C_DRV_INTERNAL */

/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 vuint8               V_MEMROM2 CanRxDataLen[kCanNumberOfRxObjects];
#   if defined( C_ENABLE_DLC_CHECK_MIN_DATALEN )
V_MEMROM0 extern V_MEMROM1 vuint8               V_MEMROM2 CanRxMinDataLen[kCanNumberOfRxObjects];
#   endif
V_MEMROM0 extern V_MEMROM1 RxDataPtr            V_MEMROM2 CanRxDataPtr[kCanNumberOfRxObjects];

#   if defined( C_ENABLE_PRECOPY_FCT )
V_MEMROM0 extern V_MEMROM1 ApplPrecopyFct       V_MEMROM2 CanRxApplPrecopyPtr[kCanNumberOfRxObjects];
#   endif
#   if defined( C_ENABLE_INDICATION_FLAG )
V_MEMROM0 extern V_MEMROM1 vuint8               V_MEMROM2 CanIndicationOffset[kCanNumberOfRxObjects];
V_MEMROM0 extern V_MEMROM1 vuint8               V_MEMROM2 CanIndicationMask[kCanNumberOfRxObjects];
#   endif
#   if defined( C_ENABLE_INDICATION_FCT )
V_MEMROM0 extern V_MEMROM1 ApplIndicationFct    V_MEMROM2 CanRxApplIndicationPtr[kCanNumberOfRxObjects];
#   endif
/* ROM CATEGORY 1 END */
# endif /* ( kCanNumberOfRxObjects > 0 ) */

# if defined( C_SINGLE_RECEIVE_CHANNEL )
# else
#  if defined( C_ENABLE_CAN_FD_USED )
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 vuint8               V_MEMROM2 CanFdUsage[kCanNumberOfChannels];
/* ROM CATEGORY 1 END */
#  endif
# endif

# if defined( C_DRV_INTERNAL )
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 tCanMailbox          V_MEMROM2 Can_Mailbox[kCanNumberOfMailboxes];
V_MEMROM0 extern V_MEMROM1 CanObjectHandle      V_MEMROM2 Can_HwObjToMailboxIndirection[kCanNumberOfHwObjToMailboxIndirections];

# if defined( C_SINGLE_RECEIVE_CHANNEL )
# else
V_MEMROM0 extern V_MEMROM1 CanObjectHandle      V_MEMROM2 Can_HwObjStartIndex[kCanNumberOfHwChannels];
V_MEMROM0 extern V_MEMROM1 CanObjectHandle      V_MEMROM2 Can_HwTxStartIndex[kCanNumberOfHwChannels];
V_MEMROM0 extern V_MEMROM1 CanObjectHandle      V_MEMROM2 Can_HwRxFullStartIndex[kCanNumberOfHwChannels];
V_MEMROM0 extern V_MEMROM1 CanObjectHandle      V_MEMROM2 Can_HwRxBasicStartIndex[kCanNumberOfHwChannels];

V_MEMROM0 extern V_MEMROM1 CanObjectHandle      V_MEMROM2 Can_HwObjToMailboxIndirectionStartIndex[kCanNumberOfHwChannels];
V_MEMROM0 extern V_MEMROM1 CanObjectHandle      V_MEMROM2 Can_HwObjToMailboxIndirectionTxStartIndex[kCanNumberOfHwChannels];
V_MEMROM0 extern V_MEMROM1 CanObjectHandle      V_MEMROM2 Can_HwObjToMailboxIndirectionRxFullStartIndex[kCanNumberOfHwChannels];
V_MEMROM0 extern V_MEMROM1 CanObjectHandle      V_MEMROM2 Can_HwObjToMailboxIndirectionRxBasicStartIndex[kCanNumberOfHwChannels]; /* PRQA S 0777 */ /* MD_Can_0777 */
#  endif
/* ROM CATEGORY 1 END */
# endif

/* structure used on initialization CAN chip -------------------------------*/
/* ROM CATEGORY 4 START */
V_DEF_CONST(extern, tCanInitObject, CONST_PBCFG) CanInitObject[kCanNumberOfInitObjects];
/* ROM CATEGORY 4 END */
/* ROM CATEGORY 4 START */
V_DEF_CONST(extern, tCanInitObjectFD, CONST_PBCFG) CanInitObjectFD[kCanNumberOfInitObjects];
/* ROM CATEGORY 4 END */
/* ROM CATEGORY 4 START*/
V_DEF_CONST(extern, tCanInitBasicCan, CONST_PBCFG) CanInitBasicCan[kCanNumberOfTotalFilters];
/* ROM CATEGORY 4 END*/
/* ROM CATEGORY 4 START*/
V_DEF_CONST(extern, vuint16, CONST_PBCFG) CanInitBasicCanIndex[kCanNumberOfInitObjects];
/* ROM CATEGORY 4 END*/
/* ROM CATEGORY 1 START */
V_DEF_CONST(extern, tCanHwChannelData, CONST_PBCFG) CanHwChannelData[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_DEF_CONST(extern, vuint32, CONST_PBCFG) CanFDMailboxMapping[]; /* PRQA S 3684 */ /* MD_Can_3684 */
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_DEF_CONST(extern, vuint32, CONST_PBCFG) CanFDHwChannelIndirection[]; /* PRQA S 3684 */ /* MD_Can_3684 */
/* ROM CATEGORY 1 END */
#if defined( C_ENABLE_SLEEP_WAKEUP ) && defined( C_ENABLE_FLEXCAN_STOP_MODE )
/* ROM CATEGORY 4 START*/
V_DEF_CONST(extern, vuint8, CONST) CanHwLogToPhys[kCanNumberOfHwChannels];
/* ROM CATEGORY 4 END*/
#endif

/* *********************************************************************** */
/* Callback functions                                                      */
/* *********************************************************************** */

# if defined( C_ENABLE_INTCTRL_ADD_CAN_FCT )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanAddCanInterruptRestore(CanChannelHandle channel) C_API_3;
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanAddCanInterruptDisable(CanChannelHandle channel) C_API_3;
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_HARDWARE_CHECK ) || \
    defined( C_ENABLE_USER_CHECK )     || \
    defined( C_ENABLE_GEN_CHECK )      || \
    defined( C_ENABLE_INTERNAL_CHECK )
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanFatalError(CAN_CHANNEL_CANTYPE_FIRST vuint8 errorNumber) C_API_3;
/* CODE CATEGORY 4 END */
# endif

# if defined( C_SINGLE_RECEIVE_CHANNEL )
/* these two functions are declared by the tool in case of multichannel */
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanBusOff(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanWakeUp(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif
# if defined( C_ENABLE_APPLCANPREWAKEUP_FCT )
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanPreWakeUp(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif
# if defined( C_ENABLE_OVERRUN )
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanOverrun ( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
# endif
# if defined( C_ENABLE_FULLCAN_OVERRUN )
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanFullCanOverrun ( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
# endif

/* Range precopy/ generic precopy functions ****************************** */
# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  if defined( C_ENABLE_RANGE_0 )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanRange0Precopy( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
#  endif
#  if defined( C_ENABLE_RANGE_1 )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanRange1Precopy( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
#  endif
#  if defined( C_ENABLE_RANGE_2 )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanRange2Precopy( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
#  endif
#  if defined( C_ENABLE_RANGE_3 )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanRange3Precopy( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
#  endif
# endif

# if defined( C_ENABLE_COND_RECEIVE_FCT )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanMsgCondReceived( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_CAN_RAM_CHECK )
#  if defined( C_ENABLE_NOTIFY_CORRUPT_MAILBOX )
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanCorruptMailbox(CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle mailboxHandle);
/* CODE CATEGORY 4 END */
#  endif  /* defined( C_ENABLE_NOTIFY_CORRUPT_MAILBOX ) */
/* CODE CATEGORY 4 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanMemCheckFailed(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif  /* defined ( C_ENABLE_CAN_RAM_CHECK ) */

# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  if defined( C_ENABLE_RECEIVE_FCT )
/* in case of multiple CAN channels this function is declared by the tool */
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 APPL_CAN_MSGRECEIVED(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */
#  endif
# endif

/* ##RI1.4 - 2.7: Callbackfunction-DLC-Check */
# if defined( C_ENABLE_DLC_FAILED_FCT )
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanMsgDlcFailed( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 4 END */
# endif  /* C_ENABLE_DLC_FAILED_FCT */

# if defined( C_ENABLE_GENERIC_PRECOPY )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 APPL_CAN_GENERIC_PRECOPY( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_NOT_MATCHED_FCT )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanMsgNotMatched( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_CAN_TX_CONF_FCT )
/* ##RI-1.10 Common Callbackfunction in TxInterrupt */
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_TX_CONFIRMATION(CanTxInfoStructPtr txStruct);
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_TX_OBSERVE )
#  if defined( C_KOMMENTAR_VECTOR_RI14 )
/* ##RI-1.1: Object parameters for Tx-Observe functions */
#  endif
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanTxObjStart( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txHwObject );
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanTxObjConfirmed( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txHwObject );
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanInit( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txHwObjectFirstUsed, CanObjectHandle txHwObjectFirstUnused);
/* CODE CATEGORY 4 END */
# endif

# if defined( C_ENABLE_HW_LOOP_TIMER )
/* CODE CATEGORY 2 START */
C_CALLBACK_1 void     C_CALLBACK_2 ApplCanTimerStart(CAN_CHANNEL_CANTYPE_FIRST vuint8 source);
/* CODE CATEGORY 2 END */
/* CODE CATEGORY 2 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanTimerLoop (CAN_CHANNEL_CANTYPE_FIRST vuint8 source);
/* CODE CATEGORY 2 END */
/* CODE CATEGORY 2 START */
C_CALLBACK_1 void     C_CALLBACK_2 ApplCanTimerEnd  (CAN_CHANNEL_CANTYPE_FIRST vuint8 source);
/* CODE CATEGORY 2 END */
# endif

# if defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_MSGTRANSMITCONF(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_MSGTRANSMITINIT(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif

# if defined( C_SINGLE_RECEIVE_CHANNEL )
/* in case of multichannel these two functions are declared by the tool */
#  if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
/* CODE CATEGORY 3 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_CANCELNOTIFICATION( CanTransmitHandle txHandle );
/* CODE CATEGORY 3 END */
#  endif
#  if defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
/* CODE CATEGORY 3 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_MSGCANCELNOTIFICATION( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 3 END */
#  endif
# endif

# if defined( C_ENABLE_RX_QUEUE )
#  if defined( C_ENABLE_APPLCANPRERXQUEUE )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanPreRxQueue( CanRxInfoStructPtr pCanRxInfoStruct );
/* CODE CATEGORY 1 END */
#  endif
#  if defined( C_ENABLE_RXQUEUE_OVERRUN_NOTIFY )
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanRxQueueOverrun( void );
/* CODE CATEGORY 4 END */
#  endif
# endif

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
/* CODE CATEGORY 3 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanChannelDummy( CanChannelHandle channel );
/* CODE CATEGORY 3 END */
# endif
# if defined( C_MULTIPLE_RECEIVE_CHANNEL ) 
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanTxHandleDummy( CanTransmitHandle txHandle );
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanRxStructPtrDummy( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
# endif
# if defined( C_ENABLE_ONLINE_OFFLINE_CALLBACK_FCT )
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_OFFLINE( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_ONLINE( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
# endif

# if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) &&\
     defined (C_ENABLE_OSEK_CAN_INTCTRL)
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 OsCanCanInterruptDisable( CAN_HW_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 OsCanCanInterruptRestore( CAN_HW_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_INIT_POST_PROCESS )
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanInitPostProcessing( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
# endif

# if defined( C_ENABLE_ACCESS_PROTECTED_REG_BY_APPL )
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanWriteProtectedRegister8(CanChipMsgPtr8 regPtr, vuint8 mask, vuint8 value);
C_CALLBACK_1 void C_CALLBACK_2 ApplCanWriteProtectedRegister16(CanChipMsgPtr16 regPtr, vuint16 mask, vuint16 value);
C_CALLBACK_1 void C_CALLBACK_2 ApplCanWriteProtectedRegister32(CanChipMsgPtr32 regPtr, vuint32 mask, vuint32 value);
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanReadProtectedRegister8(CanChipMsgPtr8 regPtr);
C_CALLBACK_1 vuint16 C_CALLBACK_2 ApplCanReadProtectedRegister16(CanChipMsgPtr16 regPtr);
C_CALLBACK_1 vuint32 C_CALLBACK_2 ApplCanReadProtectedRegister32(CanChipMsgPtr32 regPtr);
/* CODE CATEGORY 4 END */
# endif

#if defined ( C_ENABLE_USER_MODE_APPL )
/************************************************************************************************************
 *  ApplCanReadProtectedRegister()
 ***********************************************************************************************************/
/*! \brief         Callback to read 16bit of protected register.
 *  \details       Application function which is called by the CAN driver to read 16bit of special 
 *                 protected register when CAN driver runs in user mode.
 *  \param[in]     addr   Address of the register which has to be read
 *  \return        Returns the value of the register that was read
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_USER_MODE_APPL (defined via user configuration file)
 *  \notes         None AUTOSAR API
***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC_CBK(V_NONE, vuint16, APPL_CODE) ApplCanReadProtectedRegister(V_DEF_P2VAR_PARA(volatile, vuint16, AUTOMATIC, APPL_VAR) addr);
/* CODE CATEGORY 4 END */
/************************************************************************************************************
 *  ApplCanReadProtectedRegister32()
 ***********************************************************************************************************/
/*! \brief         Callback to read 32bit of protected register.
 *  \details       Application function which is called by the CAN driver to read 32bit of special 
 *                 protected register when CAN driver runs in user mode.
 *  \param[in]     addr   Address of the register which has to be read
 *  \return        Returns the value of the register that was read
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_USER_MODE_APPL (defined via user configuration file)
 *  \notes         None AUTOSAR API
***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC_CBK(V_NONE, vuint32, APPL_CODE) ApplCanReadProtectedRegister32(V_DEF_P2VAR_PARA(volatile, vuint32, AUTOMATIC, APPL_VAR) addr);
/* CODE CATEGORY 4 END */
/************************************************************************************************************
 *  ApplCanWriteProtectedRegister()
 ***********************************************************************************************************/
/*! \brief         Callback to write 16bit of protected register.
 *  \details       Application function which is called by the CAN driver to write 16bit of special 
 *                 protected register when CAN driver runs in user mode.
 *  \param[in]     addr   Address of the register which has to be written
 *  \param[in]     mask   The mask specifies the bits of the register to be written
 *  \param[in]     val    The value which has to be written to the register
 *  \return        Returns the value of the register that was read
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_USER_MODE_APPL (defined via user configuration file)
 *  \notes         None AUTOSAR API
***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC_CBK(V_NONE, void, APPL_CODE) ApplCanWriteProtectedRegister(V_DEF_P2VAR_PARA(volatile, vuint16, AUTOMATIC, APPL_VAR) addr, vuint16 mask, vuint16 val);
/* CODE CATEGORY 4 END */
/************************************************************************************************************
 *  ApplCanWriteProtectedRegister32()
 ***********************************************************************************************************/
/*! \brief         Callback to write 32bit of protected register.
 *  \details       Application function which is called by the CAN driver to write 32bit of special 
 *                 protected register when CAN driver runs in user mode.
 *  \param[in]     addr   Address of the register which has to be written
 *  \param[in]     mask   The mask specifies the bits of the register to be written
 *  \param[in]     val    The value which has to be written to the register
 *  \return        Returns the value of the register that was read
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_USER_MODE_APPL (defined via user configuration file)
 *  \notes         None AUTOSAR API
***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC_CBK(V_NONE, void, APPL_CODE) ApplCanWriteProtectedRegister32(V_DEF_P2VAR_PARA(volatile, vuint32, AUTOMATIC, APPL_VAR) addr, vuint32 mask, vuint32 val);
/* CODE CATEGORY 4 END */
#endif
# if defined( C_ENABLE_SLEEP_WAKEUP ) && defined( C_ENABLE_FLEXCAN_STOP_MODE )
/* CODE CATEGORY 4 START */ 
V_DEF_FUNC_CBK(V_NONE, vuint8, APPL_CODE) ApplCanEnterLowPowerMode(vuint8 physChannelIndex);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */ 
V_DEF_FUNC_CBK(V_NONE, vuint8, APPL_CODE) ApplCanLeaveLowPowerMode(vuint8 physChannelIndex);
/* CODE CATEGORY 4 END */
# endif /* C_ENABLE_SLEEP_WAKEUP */

/* *********************************************************************** */
/* function prototypes                                                     */
/* *********************************************************************** */

/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanInitPowerOn( void );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanInit( CAN_CHANNEL_CANTYPE_FIRST CanInitHandle initObject );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanReInit( CAN_CHANNEL_CANTYPE_FIRST vuint8 suppressRamCheck, vuint8 suppressModeTransition );
/* CODE CATEGORY 4 END */

# if defined( C_ENABLE_CAN_TRANSMIT )
/* CODE CATEGORY 2 START */
C_API_1 vuint8 C_API_2 CanTransmit(CanTransmitHandle txHandle) C_API_3;
/* CODE CATEGORY 2 END */
#  if defined( C_ENABLE_VARIABLE_DLC )
/* CODE CATEGORY 2 START */
C_API_1 vuint8 C_API_2 CanTransmitVarDLC( CanTransmitHandle txHandle, vuint8 dlc) C_API_3;
/* CODE CATEGORY 2 END */
#  endif
/* CODE CATEGORY 3 START */
C_API_1 void C_API_2 CanCancelTransmit( CanTransmitHandle txHandle );
/* CODE CATEGORY 3 END */
# endif

# if defined( C_ENABLE_MSG_TRANSMIT )
/* CODE CATEGORY 2 START */

#  if defined ( V_ENABLE_USED_GLOBAL_VAR )
/* txMsgStruct is located in far memory */
C_API_1 vuint8 C_API_2 CanMsgTransmit( CAN_CHANNEL_CANTYPE_FIRST V_MEMRAM1_FAR tCanMsgTransmitStruct V_MEMRAM2_FAR V_MEMRAM3_FAR *txMsgStruct );
#  else
C_API_1 vuint8 C_API_2 CanMsgTransmit( CAN_CHANNEL_CANTYPE_FIRST tCanMsgTransmitStruct *txMsgStruct);
#  endif

/* CODE CATEGORY 2 END */
#  if defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )
/* CODE CATEGORY 3 START */
C_API_1 void C_API_2 CanCancelMsgTransmit( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 3 END */
#  endif
# endif  /* defined( C_ENABLE_MSG_TRANSMIT ) */

# if defined( C_ENABLE_OFFLINE )
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanOnline( CAN_CHANNEL_CANTYPE_ONLY );           /* switch CanStatus to On */
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanOffline( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 4 END */
# endif

# if defined( C_ENABLE_PART_OFFLINE )
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetPartOffline( CAN_CHANNEL_CANTYPE_FIRST vuint8 sendGroup);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetPartOnline( CAN_CHANNEL_CANTYPE_FIRST vuint8 invSendGroup);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanGetPartMode( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
# endif

/* CODE CATEGORY 3 START */
C_API_1 vuint8 C_API_2 CanGetStatus( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 3 END */

/* CanSleep functions */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanSleep( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanWakeUp( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */

# if defined( C_ENABLE_ECU_SWITCH_PASS )
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetActive(  CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetPassive( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
# else
#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
#   define    CanSetActive( channel )            /* remove calls to setActive/Passive */
#   define    CanSetPassive( channel )
#  else
#   define    CanSetActive( )                    /* remove calls to setActive/Passive */
#   define    CanSetPassive( )
#  endif
# endif

# if defined( C_ENABLE_STOP )
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanStart( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanStop( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
# endif

# if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL)
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 CanCanInterruptDisable( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 CanCanInterruptRestore( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_TX_POLLING ) || \
    defined( C_ENABLE_RX_FULLCAN_POLLING )  || \
    defined( C_ENABLE_RX_BASICCAN_POLLING ) || \
    defined( C_ENABLE_ERROR_POLLING ) || \
    defined( C_ENABLE_WAKEUP_POLLING ) 
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanTask(void);
/* CODE CATEGORY 2 END */
# endif
# if defined( C_ENABLE_TX_POLLING ) 
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanTxTask( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 2 END */
# endif
# if defined( C_ENABLE_TX_POLLING ) && \
     defined( C_ENABLE_INDIVIDUAL_POLLING )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanTxObjTask(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle);
/* CODE CATEGORY 2 END */
# endif
# if defined( C_ENABLE_ERROR_POLLING )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanErrorTask( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 2 END */
# endif
# if defined( C_ENABLE_SLEEP_WAKEUP )
#  if defined( C_ENABLE_WAKEUP_POLLING )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanWakeUpTask(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
#  endif
# endif
# if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) && \
     defined( C_ENABLE_RX_FULLCAN_POLLING )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxFullCANTask(CAN_CHANNEL_CANTYPE_ONLY) C_API_3;
/* CODE CATEGORY 2 END */
#  if defined( C_ENABLE_INDIVIDUAL_POLLING )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxFullCANObjTask(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle);
/* CODE CATEGORY 2 END */
#  endif
# endif
# if defined( C_ENABLE_RX_BASICCAN_POLLING ) && \
     defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxBasicCANTask(CAN_CHANNEL_CANTYPE_ONLY) C_API_3;
/* CODE CATEGORY 2 END */
#  if defined( C_ENABLE_INDIVIDUAL_POLLING )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxBasicCANObjTask(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle);
/* CODE CATEGORY 2 END */
#  endif
# endif

# if defined( C_ENABLE_DYN_TX_OBJECTS )
/* CODE CATEGORY 3 START */
C_API_1 CanTransmitHandle C_API_2 CanGetDynTxObj(CanTransmitHandle txHandle ) C_API_3;
/* CODE CATEGORY 3 END */
/* CODE CATEGORY 3 START */
C_API_1 vuint8          C_API_2 CanReleaseDynTxObj(CanTransmitHandle txHandle) C_API_3;
/* CODE CATEGORY 3 END */

#  if defined( C_ENABLE_DYN_TX_ID )
#   if !defined( C_ENABLE_EXTENDED_ID ) ||\
     defined( C_ENABLE_MIXED_ID )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetId(CanTransmitHandle txHandle, vuint16 id) C_API_3;
/* CODE CATEGORY 2 END */
#    if defined(C_ENABLE_CAN_FD_USED)
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetFdId(CanTransmitHandle txHandle, vuint16 id) C_API_3;
/* CODE CATEGORY 2 END */
#    endif
#   endif
#   if defined( C_ENABLE_EXTENDED_ID )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetExtId32(CanTransmitHandle txHandle, vuint32 id) C_API_3;
/* CODE CATEGORY 2 END */
#    if defined(C_ENABLE_CAN_FD_USED)
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetFdExtId32(CanTransmitHandle txHandle, vuint32 id) C_API_3;
/* CODE CATEGORY 2 END */
#    endif
#   endif
#  endif
#  if defined( C_ENABLE_DYN_TX_DLC )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetMessageLength(CanTransmitHandle txHandle, vuint8 messageLength) C_API_3;
/* CODE CATEGORY 2 END */
#  endif
#  if defined( C_ENABLE_DYN_TX_DATAPTR )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetDataPtr(CanTransmitHandle txHandle, void* pData) C_API_3;
/* CODE CATEGORY 2 END */
#  endif

# endif /* defined( C_ENABLE_DYN_TX_OBJECTS ) */

# if defined( C_ENABLE_TX_MASK_EXT_ID )
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtHi( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtMidHi( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtMidLo( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtLo( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask );
/* CODE CATEGORY 4 END */
# endif

# if defined( C_ENABLE_TX_OBSERVE )
#  if defined( C_KOMMENTAR_VECTOR_RI14 )
/* ##RI-1.1: new service function for Tx-Observe */
#  endif
/* CODE CATEGORY 3 START */
C_API_1 CanTransmitHandle C_API_2 CanTxGetActHandle( CanObjectHandle logicalTxHdl ) C_API_3;
/* CODE CATEGORY 3 END */
# endif

# if defined( C_ENABLE_COND_RECEIVE_FCT )
/* CODE CATEGORY 3 START */
C_API_1 void     C_API_2 CanSetMsgReceivedCondition( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 3 END */
/* CODE CATEGORY 3 START */
C_API_1 void     C_API_2 CanResetMsgReceivedCondition( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 3 END */
/* CODE CATEGORY 3 START */
C_API_1 vuint8 C_API_2 CanGetMsgReceivedCondition( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 3 END */
# endif

# if defined( C_ENABLE_RX_QUEUE )
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanDeleteRxQueue(void);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanHandleRxMsg(void);
/* CODE CATEGORY 2 END */
# endif

/* Additional API for QNX */

# if defined ( C_ENABLE_MEMCOPY_SUPPORT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanCopyToCan()
 ***********************************************************************************************************/
/*! \brief         Copy CAN data
 *  \details       copy CAN data from application RAM to CAN registers.
 *  \param[out]    dst   pointer to CAN buffer
 *  \param[in]     src   pointer to source buffer
 *  \param[in]     len   number of bytes to copy
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_MEMCOPY_SUPPORT
***********************************************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanCopyToCan(CanChipDataPtr dst, V_DEF_P2VAR_PARA(V_NONE, void, AUTOMATIC, APPL_VAR) src, vuint8 len) C_API_3;
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanCopyFromCan()
 ***********************************************************************************************************/
/*! \brief         Copy CAN data
 *  \details       copy CAN data from CAN registers to application RAM.
 *  \param[out]    dst   pointer to destination buffer
 *  \param[in]     src   pointer to CAN buffer
 *  \param[in]     len   number of bytes to copy
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_MEMCOPY_SUPPORT
***********************************************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanCopyFromCan(V_DEF_P2VAR_PARA(V_NONE, void, AUTOMATIC, APPL_VAR) dst, CanChipDataPtr src, vuint8 len);
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_TX_FULLCAN_DELAYED_START )
/* CODE CATEGORY 1 START*/
V_DEF_FUNC_API(V_NONE, void, CODE) CanTxFullCanDelayedStart(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 1 END*/
# endif /* C_ENABLE_TX_FULLCAN_DELAYED_START */

# if defined ( C_ENABLE_DRIVER_STATUS )
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanGetDriverStatus()
 ***********************************************************************************************************/
/*! \brief         Get driver status
 *  \details       provide the current state of the BUSOFF recovery. \n
 *                 This allows to call CanResetBusOffEnd more early to be able to receive messages \n
 *                 as soon as possible after BUSOFF.
 *  \param[in]     channel               CAN controller
 *  \return        kCanDriverBusoff:     CAN Driver is in state BUSOFF, 
 *                                       INIT mode is not reached jet.
 *  \return        kCanDriverBusoffInit: INIT mode is reached, CanResetBusoffEnd
 *                                       can be processed without delay on entry. 
 *  \return        kCanDriverNormal:     INIT mode is already left. CanResetBusoffEnd
 *                                       can be processed without delay on entry 
 *                                       (if not already performed). 
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_DRIVER_STATUS
***********************************************************************************************************/
V_DEF_FUNC_API(V_NONE, vuint8, CODE) CanGetDriverStatus(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif

#if defined( V_CPU_IMX ) || defined( V_CPU_VYBRID ) 
# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
     defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
     defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanInterrupt()
 ***********************************************************************************************************/
/*! \brief         Handles all interrupt events.
 *  \details       Checks interrupt events and calls the indication or confirmation function.
 *  \param[in]     Controller          CAN controller (configuration dependent)
 *  \context       ISR1|ISR2
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT || C_ENABLE_CAN_BUSOFF_INTERRUPT || C_ENABLE_CAN_WAKEUP_INTERRUPT
 *  \pre           -
 ***********************************************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 1 END */
# endif
#endif

#if defined( V_CPU_S32 )
# if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanBusOffInterrupt()
 ***********************************************************************************************************/
/*! \brief         Handles BUSOFF interrupt events.
 *  \details       Calls error handling.
 *  \param[in]     Controller          CAN controller (configuration dependent)
 *  \context       ISR1|ISR2
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_BUSOFF_INTERRUPT
 *  \pre           -
 ***********************************************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanBusOffInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 1 END */
# endif
# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanMailboxInterrupt()
 ***********************************************************************************************************/
/*! \brief         Handles transmission and reception interrupt events.
 *  \details       Checks interrupt events and calls the indication or confirmation function.
 *  \param[in]     Controller          CAN controller (configuration dependent)
 *  \context       ISR1|ISR2
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT
 *  \pre           -
 ***********************************************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanMailboxInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 1 END */
# endif
#endif

/* Possibility to disable the prototypes of interrupt service routines in the driver configuration header file.  */

#if defined (C_ENABLE_ISR_PROTOTYPE)
# if defined(C_ENABLE_OSEK_OS)&&\
     defined(C_ENABLE_OSEK_OS_INTCAT2)
/* ISR prototypes must be provided by OSEK header file */
# else

#if defined( V_CPU_IMX ) || defined( V_CPU_VYBRID )
# if defined( kCanPhysToLogChannelIndex_0 )
#  if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
      defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
      defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanIsr_0()
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for events on CAN_0.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT || C_ENABLE_CAN_BUSOFF_INTERRUPT || C_ENABLE_CAN_WAKEUP_INTERRUPT
 *  \pre           -
 ***********************************************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanIsr_0( void );
/* CODE CATEGORY 1 END */
#  endif
# endif /* kCanPhysToLogChannelIndex_0 */ 
# if defined( kCanPhysToLogChannelIndex_1 )
#  if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
      defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
      defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanIsr_1()
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for events on CAN_1.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT || C_ENABLE_CAN_BUSOFF_INTERRUPT || C_ENABLE_CAN_WAKEUP_INTERRUPT
 *  \pre           -
 ***********************************************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanIsr_1( void );
/* CODE CATEGORY 1 END */
#  endif
# endif /* kCanPhysToLogChannelIndex_1 */ 
# if defined( kCanPhysToLogChannelIndex_2 )
#  if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
      defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
      defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanIsr_2()
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for events on CAN_2.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT || C_ENABLE_CAN_BUSOFF_INTERRUPT || C_ENABLE_CAN_WAKEUP_INTERRUPT
 *  \pre           -
 ***********************************************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanIsr_2( void );
/* CODE CATEGORY 1 END */
#  endif
# endif /* kCanPhysToLogChannelIndex_2 */ 
# if defined( kCanPhysToLogChannelIndex_3 )
#  if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
      defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
      defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanIsr_3()
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for events on CAN_3.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT || C_ENABLE_CAN_BUSOFF_INTERRUPT || C_ENABLE_CAN_WAKEUP_INTERRUPT
 *  \pre           -
 ***********************************************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanIsr_3( void );
/* CODE CATEGORY 1 END */
#  endif
# endif /* kCanPhysToLogChannelIndex_3 */ 
#endif /* V_CPU_IMX */

#if defined( V_CPU_S32 )
# if defined( kCanPhysToLogChannelIndex_0 )
#  if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanBusOffIsr_0()
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for BUSOFF event on CAN_0.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_BUSOFF_INTERRUPT
 *  \pre           -
 ***********************************************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanBusOffIsr_0( void );
/* CODE CATEGORY 1 END */
#  endif
#  if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanMailboxIsr_0()
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for transmission and reception events on CAN_0.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT
 *  \pre           -
 ***********************************************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanMailboxIsr_0( void );
/* CODE CATEGORY 1 END */
#  endif
# endif /* kCanPhysToLogChannelIndex_0 */ 
# if defined( kCanPhysToLogChannelIndex_1 )
#  if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanBusOffIsr_1()
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for BUSOFF event on CAN_1.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_BUSOFF_INTERRUPT
 *  \pre           -
 ***********************************************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanBusOffIsr_1( void );
/* CODE CATEGORY 1 END */
#  endif
#  if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanMailboxIsr_1()
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for transmission and reception events on CAN_1.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT
 *  \pre           -
 ***********************************************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanMailboxIsr_1( void );
/* CODE CATEGORY 1 END */
#  endif
# endif /* kCanPhysToLogChannelIndex_1 */ 
# if defined( kCanPhysToLogChannelIndex_2 )
#  if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanBusOffIsr_2()
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for BUSOFF event on CAN_2.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_BUSOFF_INTERRUPT
 *  \pre           -
 ***********************************************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanBusOffIsr_2( void );
/* CODE CATEGORY 1 END */
#  endif
#  if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanMailboxIsr_2()
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for transmission and reception events on CAN_2.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT
 *  \pre           -
 ***********************************************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanMailboxIsr_2( void );
/* CODE CATEGORY 1 END */
#  endif
# endif /* kCanPhysToLogChannelIndex_2 */ 
# if defined( kCanPhysToLogChannelIndex_3 )
#  if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanBusOffIsr_3()
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for BUSOFF event on CAN_3.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_BUSOFF_INTERRUPT
 *  \pre           -
 ***********************************************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanBusOffIsr_3( void );
/* CODE CATEGORY 1 END */
#  endif
#  if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/* CODE CATEGORY 1 START */
/************************************************************************************************************
 *  CanMailboxIsr_3()
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for transmission and reception events on CAN_3.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_ENABLE_CAN_RXTX_INTERRUPT
 *  \pre           -
 ***********************************************************************************************************/
V_DEF_FUNC_API(V_NONE, void, CODE) CanMailboxIsr_3( void );
/* CODE CATEGORY 1 END */
#  endif
# endif /* kCanPhysToLogChannelIndex_3 */ 
#endif /* V_CPU_MPC5700 */

# endif
#endif /* C_ENABLE_ISR_PROTOTYPE */

#if !defined( C_ENABLE_PROTECTED_RX_PROCESS ) && !defined( C_DISABLE_PROTECTED_RX_PROCESS )
# if ( C_SECURITY_LEVEL > 10 )
#  define C_ENABLE_PROTECTED_RX_PROCESS
# endif
#endif

extern void CanBasicCanMsgReceived( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle rxObjHandle);
extern void CanHL_TxConfirmation( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle txMailboxHandle, CanObjectHandle txObjHandle);

extern  void EnableAllInterrupts(void);
extern  void DisableAllInterrupts(void);
#endif /* CAN_DEF_H */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Hll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Hll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Hll Erzeugungsgangnummer: 1 */

