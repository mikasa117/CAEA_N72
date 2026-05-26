/* -----------------------------------------------------------------------------
  Filename:    il_par.h
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

#include "v_def.h"
#if !defined(__IL_PAR_H__)
#define __IL_PAR_H__
#include "fr30xx.h"
#include "il_cfg.h"
#include "drv_par.h"
/* -----------------------------------------------------------------------------
    &&&~ Typedefs
 ----------------------------------------------------------------------------- */
typedef volatile uint8_t   vuint8_t;
#if defined(IL_ENABLE_TX)
typedef vuint8 IltTxCounter;
#endif

#if defined(IL_ENABLE_TX)
typedef vuint8 IltTxUpdateCounter;
#endif

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT)
typedef vuint8 IltTxTimeoutCounter;
#endif

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
typedef vuint16 IltRxTimeoutCounter;
#endif

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_SECURE_EVENT)
typedef vuint8 IltTxRepetitionCounter;
#endif



/* -----------------------------------------------------------------------------
    &&&~ Message Handles
 ----------------------------------------------------------------------------- */

#define IlRxMsgHndPMS_VIN                    0
#define IlRxMsgHndIPK_TotalOdometer          1
#define IlRxMsgHndTBOX_DateTime_Info         2
#define IlRxMsgHndEHB_Status                 3
#define IlTxMsgHndMMI_Status_Info            0
#define IlTxMsgHndTTS_Status                 1
#define IlTxMsgHndMMI_TextMMData             2
#define IlTxMsgHndMMI_TextBTData             3


/* -----------------------------------------------------------------------------
    &&&~ Signal Handles
 ----------------------------------------------------------------------------- */

#define IlRxSigHndPMS_VINMessageNum_S        IlRxMsgHndPMS_VIN
#define IlRxSigHndPMS_VINCode1_8_15_S        IlRxMsgHndPMS_VIN
#define IlRxSigHndPMS_VINCode2_9_16_S        IlRxMsgHndPMS_VIN
#define IlRxSigHndPMS_VINCode3_10_17_S       IlRxMsgHndPMS_VIN
#define IlRxSigHndPMS_VINCode4_11_S          IlRxMsgHndPMS_VIN
#define IlRxSigHndPMS_VINCode5_12_S          IlRxMsgHndPMS_VIN
#define IlRxSigHndPMS_VINCode6_13_S          IlRxMsgHndPMS_VIN
#define IlRxSigHndPMS_VINCode7_14_S          IlRxMsgHndPMS_VIN
#define IlRxSigHndIPK_IPKTotalOdometer       IlRxMsgHndIPK_TotalOdometer
#define IlRxSigHndTBOX_Second                IlRxMsgHndTBOX_DateTime_Info
#define IlRxSigHndTBOX_Minute                IlRxMsgHndTBOX_DateTime_Info
#define IlRxSigHndTBOX_Hour                  IlRxMsgHndTBOX_DateTime_Info
#define IlRxSigHndTBOX_Month                 IlRxMsgHndTBOX_DateTime_Info
#define IlRxSigHndTBOX_Day                   IlRxMsgHndTBOX_DateTime_Info
#define IlRxSigHndTBOX_Year                  IlRxMsgHndTBOX_DateTime_Info
#define IlRxSigHndEHB_VehicleSpeedInvalid    IlRxMsgHndEHB_Status
#define IlRxSigHndEHB_VehicleSpeed           IlRxMsgHndEHB_Status
#define IlTxSigHndMMI_RightSwStatus          IlTxMsgHndMMI_Status_Info
#define IlTxSigHndMMI_LeftSwStatus           IlTxMsgHndMMI_Status_Info
#define IlTxSigHndMMI_UpSwStatus             IlTxMsgHndMMI_Status_Info
#define IlTxSigHndMMI_DownSwStatus           IlTxMsgHndMMI_Status_Info
#define IlTxSigHndMMI_ConfirmSwStatus        IlTxMsgHndMMI_Status_Info
#define IlTxSigHndMMI_ReturnSwStatus         IlTxMsgHndMMI_Status_Info
#define IlTxSigHndMMI_WorkMode               IlTxMsgHndMMI_Status_Info
#define IlTxSigHndTTS_BluetoothFunction      IlTxMsgHndTTS_Status
#define IlTxSigHndTTS_BluetoothConnect       IlTxMsgHndTTS_Status
#define IlTxSigHndMMI_TextMultDataFrame      IlTxMsgHndMMI_TextMMData
#define IlTxSigHndMMI_TextBTDataFrame        IlTxMsgHndMMI_TextBTData


/* -----------------------------------------------------------------------------
    &&&~ Critical section macros for signals
 ----------------------------------------------------------------------------- */

#define IlEnterCriticalMMI_RightSwStatus()   CanGlobalInterruptDisable()
#define IlLeaveCriticalMMI_RightSwStatus()   CanGlobalInterruptRestore()
#define IlEnterCriticalMMI_LeftSwStatus()    CanGlobalInterruptDisable()
#define IlLeaveCriticalMMI_LeftSwStatus()    CanGlobalInterruptRestore()
#define IlEnterCriticalMMI_UpSwStatus()      CanGlobalInterruptDisable()
#define IlLeaveCriticalMMI_UpSwStatus()      CanGlobalInterruptRestore()
#define IlEnterCriticalMMI_DownSwStatus()    CanGlobalInterruptDisable()
#define IlLeaveCriticalMMI_DownSwStatus()    CanGlobalInterruptRestore()
#define IlEnterCriticalMMI_ConfirmSwStatus() CanGlobalInterruptDisable()
#define IlLeaveCriticalMMI_ConfirmSwStatus() CanGlobalInterruptRestore()
#define IlEnterCriticalMMI_ReturnSwStatus()  CanGlobalInterruptDisable()
#define IlLeaveCriticalMMI_ReturnSwStatus()  CanGlobalInterruptRestore()
#define IlEnterCriticalMMI_WorkMode()        CanGlobalInterruptDisable()
#define IlLeaveCriticalMMI_WorkMode()        CanGlobalInterruptRestore()
#define IlEnterCriticalTTS_BluetoothFunction() CanGlobalInterruptDisable()
#define IlLeaveCriticalTTS_BluetoothFunction() CanGlobalInterruptRestore()
#define IlEnterCriticalTTS_BluetoothConnect() CanGlobalInterruptDisable()
#define IlLeaveCriticalTTS_BluetoothConnect() CanGlobalInterruptRestore()
#define IlEnterCriticalMMI_TextMultDataFrame() CanGlobalInterruptDisable()
#define IlLeaveCriticalMMI_TextMultDataFrame() CanGlobalInterruptRestore()
#define IlEnterCriticalMMI_TextBTDataFrame() CanGlobalInterruptDisable()
#define IlLeaveCriticalMMI_TextBTDataFrame() CanGlobalInterruptRestore()
#define IlEnterCriticalPMS_VINMessageNum_S() CanGlobalInterruptDisable()
#define IlLeaveCriticalPMS_VINMessageNum_S() CanGlobalInterruptRestore()
#define IlEnterCriticalPMS_VINCode1_8_15_S() CanGlobalInterruptDisable()
#define IlLeaveCriticalPMS_VINCode1_8_15_S() CanGlobalInterruptRestore()
#define IlEnterCriticalPMS_VINCode2_9_16_S() CanGlobalInterruptDisable()
#define IlLeaveCriticalPMS_VINCode2_9_16_S() CanGlobalInterruptRestore()
#define IlEnterCriticalPMS_VINCode3_10_17_S() CanGlobalInterruptDisable()
#define IlLeaveCriticalPMS_VINCode3_10_17_S() CanGlobalInterruptRestore()
#define IlEnterCriticalPMS_VINCode4_11_S()   CanGlobalInterruptDisable()
#define IlLeaveCriticalPMS_VINCode4_11_S()   CanGlobalInterruptRestore()
#define IlEnterCriticalPMS_VINCode5_12_S()   CanGlobalInterruptDisable()
#define IlLeaveCriticalPMS_VINCode5_12_S()   CanGlobalInterruptRestore()
#define IlEnterCriticalPMS_VINCode6_13_S()   CanGlobalInterruptDisable()
#define IlLeaveCriticalPMS_VINCode6_13_S()   CanGlobalInterruptRestore()
#define IlEnterCriticalPMS_VINCode7_14_S()   CanGlobalInterruptDisable()
#define IlLeaveCriticalPMS_VINCode7_14_S()   CanGlobalInterruptRestore()
#define IlEnterCriticalIPK_IPKTotalOdometer() CanGlobalInterruptDisable()
#define IlLeaveCriticalIPK_IPKTotalOdometer() CanGlobalInterruptRestore()
#define IlEnterCriticalTBOX_Second()         CanGlobalInterruptDisable()
#define IlLeaveCriticalTBOX_Second()         CanGlobalInterruptRestore()
#define IlEnterCriticalTBOX_Minute()         CanGlobalInterruptDisable()
#define IlLeaveCriticalTBOX_Minute()         CanGlobalInterruptRestore()
#define IlEnterCriticalTBOX_Hour()           CanGlobalInterruptDisable()
#define IlLeaveCriticalTBOX_Hour()           CanGlobalInterruptRestore()
#define IlEnterCriticalTBOX_Month()          CanGlobalInterruptDisable()
#define IlLeaveCriticalTBOX_Month()          CanGlobalInterruptRestore()
#define IlEnterCriticalTBOX_Day()            CanGlobalInterruptDisable()
#define IlLeaveCriticalTBOX_Day()            CanGlobalInterruptRestore()
#define IlEnterCriticalTBOX_Year()           CanGlobalInterruptDisable()
#define IlLeaveCriticalTBOX_Year()           CanGlobalInterruptRestore()
#define IlEnterCriticalEHB_VehicleSpeedInvalid() CanGlobalInterruptDisable()
#define IlLeaveCriticalEHB_VehicleSpeedInvalid() CanGlobalInterruptRestore()
#define IlEnterCriticalEHB_VehicleSpeed()    CanGlobalInterruptDisable()
#define IlLeaveCriticalEHB_VehicleSpeed()    CanGlobalInterruptRestore()


/* -----------------------------------------------------------------------------
    &&&~ Declaration Confirmation Functions
 ----------------------------------------------------------------------------- */

/* Application signal confirmation callback functions */


/* -----------------------------------------------------------------------------
    &&&~ Declaration Indication Functions
 ----------------------------------------------------------------------------- */

/* Application signal indication callback functions */


/* -----------------------------------------------------------------------------
    &&&~ Declaration Rx Timeout Indication Functions
 ----------------------------------------------------------------------------- */

extern void ApplPMS_VIN_TimeoutMsgTimeout(void);
extern void ApplIPK_TotalOdometer_TimeoutMsgTimeout(void);
extern void ApplTBOX_DateTime_Info_TimeoutMsgTimeout(void);
extern void ApplEHB_Status_TimeoutMsgTimeout(void);


/* -----------------------------------------------------------------------------
    &&&~ Declaration User Timeout Functions
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT)
#endif



/* -----------------------------------------------------------------------------
    &&&~ Get Rx Signal Access for signals smaller or equal 8bit
 ----------------------------------------------------------------------------- */

/* Handle:    0,Name:            PMS_VINMessageNum_S,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxPMS_VINMessageNum_S()         (PMS_VIN.PMS_VIN.PMS_VINMessageNum_S)
#endif

/* Handle:    1,Name:            PMS_VINCode1_8_15_S,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxPMS_VINCode1_8_15_S()         (PMS_VIN.PMS_VIN.PMS_VINCode1_8_15_S)
#endif

/* Handle:    2,Name:            PMS_VINCode2_9_16_S,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxPMS_VINCode2_9_16_S()         (PMS_VIN.PMS_VIN.PMS_VINCode2_9_16_S)
#endif

/* Handle:    3,Name:           PMS_VINCode3_10_17_S,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxPMS_VINCode3_10_17_S()        (PMS_VIN.PMS_VIN.PMS_VINCode3_10_17_S)
#endif

/* Handle:    4,Name:              PMS_VINCode4_11_S,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxPMS_VINCode4_11_S()           (PMS_VIN.PMS_VIN.PMS_VINCode4_11_S)
#endif

/* Handle:    5,Name:              PMS_VINCode5_12_S,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxPMS_VINCode5_12_S()           (PMS_VIN.PMS_VIN.PMS_VINCode5_12_S)
#endif

/* Handle:    6,Name:              PMS_VINCode6_13_S,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxPMS_VINCode6_13_S()           (PMS_VIN.PMS_VIN.PMS_VINCode6_13_S)
#endif

/* Handle:    7,Name:              PMS_VINCode7_14_S,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxPMS_VINCode7_14_S()           (PMS_VIN.PMS_VIN.PMS_VINCode7_14_S)
#endif

/* Handle:    9,Name:                    TBOX_Second,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTBOX_Second()                 (TBOX_DateTime_Info.TBOX_DateTime_Info.TBOX_Second)
#endif

/* Handle:   10,Name:                    TBOX_Minute,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTBOX_Minute()                 (TBOX_DateTime_Info.TBOX_DateTime_Info.TBOX_Minute)
#endif

/* Handle:   11,Name:                      TBOX_Hour,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTBOX_Hour()                   (TBOX_DateTime_Info.TBOX_DateTime_Info.TBOX_Hour)
#endif

/* Handle:   12,Name:                     TBOX_Month,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTBOX_Month()                  (TBOX_DateTime_Info.TBOX_DateTime_Info.TBOX_Month)
#endif

/* Handle:   13,Name:                       TBOX_Day,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTBOX_Day()                    (TBOX_DateTime_Info.TBOX_DateTime_Info.TBOX_Day)
#endif

/* Handle:   14,Name:                      TBOX_Year,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTBOX_Year()                   (TBOX_DateTime_Info.TBOX_DateTime_Info.TBOX_Year)
#endif

/* Handle:   15,Name:        EHB_VehicleSpeedInvalid,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxEHB_VehicleSpeedInvalid()     (EHB_Status.EHB_Status.EHB_VehicleSpeedInvalid)
#endif



/* -----------------------------------------------------------------------------
    &&&~ Get Rx Signal Access for signals greater 8bit and smaller or equal 32bit
 ----------------------------------------------------------------------------- */

/* Handle:    8,Name:           IPK_IPKTotalOdometer,Size: 24,UsedBytes:  3,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint32 IlGetRxIPK_IPKTotalOdometer(void);
#endif

/* Handle:   16,Name:               EHB_VehicleSpeed,Size: 13,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxEHB_VehicleSpeed(void);
#endif



/* -----------------------------------------------------------------------------
    &&&~ Set Tx Signal Access for signals smaller or equal 8bit, SendType cyclic or none
 ----------------------------------------------------------------------------- */

/* Handle:    0,Name:              MMI_RightSwStatus,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxMMI_RightSwStatus(vuint8 sigData);
#endif

/* Handle:    1,Name:               MMI_LeftSwStatus,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxMMI_LeftSwStatus(vuint8 sigData);
#endif

/* Handle:    2,Name:                 MMI_UpSwStatus,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxMMI_UpSwStatus(vuint8 sigData);
#endif

/* Handle:    3,Name:               MMI_DownSwStatus,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxMMI_DownSwStatus(vuint8 sigData);
#endif

/* Handle:    4,Name:            MMI_ConfirmSwStatus,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxMMI_ConfirmSwStatus(vuint8 sigData);
#endif

/* Handle:    5,Name:             MMI_ReturnSwStatus,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxMMI_ReturnSwStatus(vuint8 sigData);
#endif

/* Handle:    6,Name:                   MMI_WorkMode,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxMMI_WorkMode(vuint8 sigData);
#endif

/* Handle:    7,Name:          TTS_BluetoothFunction,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxTTS_BluetoothFunction(vuint8 sigData);
#endif

/* Handle:    8,Name:           TTS_BluetoothConnect,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxTTS_BluetoothConnect(vuint8 sigData);
#endif



/* -----------------------------------------------------------------------------
    &&&~ Set Tx Signal Access extern decl
 ----------------------------------------------------------------------------- */

/* Handle:    9,Name:          MMI_TextMultDataFrame,Size: 64,UsedBytes:  8,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxMMI_TextMultDataFrame(vuint8* pData);
#endif

/* Handle:   10,Name:            MMI_TextBTDataFrame,Size: 64,UsedBytes:  8,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxMMI_TextBTDataFrame(vuint8* pData);
#endif



/* -----------------------------------------------------------------------------
    &&&~ AUTOSAR Signal API
 ----------------------------------------------------------------------------- */

#if ((COM_AR_MAJOR_VERSION == 1) && (COM_AR_MINOR_VERSION == 0) && (COM_AR_PATCH_VERSION == 0))
typedef vuint8 Com_ReturnType;
#define COM_OK                               (Com_ReturnType) 0
#define Com_SendSignal(x, y)                 (ComIlPut##x((y)), COM_OK)
#define Com_ReceiveSignal(x, y)              (ComIlGet##x((y)), COM_OK)
#define Com_SendSignalGroup(x)               (ComIlPut##x(), COM_OK)
#define Com_ReceiveSignalGroup(x)            (ComIlGet##x(), COM_OK)
#define Com_ReceiveShadowSignal(x, y)        (ComIlGet##x((y)), COM_OK)
#define Com_UpdateShadowSignal(x, y)         (ComIlPut##x((y)), COM_OK)
#else
#if ((COM_AR_MAJOR_VERSION == 2) && (COM_AR_MINOR_VERSION == 0) && (COM_AR_PATCH_VERSION == 0))
#define Com_SendSignal(x, y)                 (ComIlPut##x((y)), E_OK)
#define Com_ReceiveSignal(x, y)              (ComIlGet##x((y)), E_OK)
#define Com_SendSignalGroup(x)               (ComIlPut##x(), E_OK)
#define Com_ReceiveSignalGroup(x)            (ComIlGet##x(), E_OK)
#define Com_ReceiveShadowSignal(x, y)        (ComIlGet##x((y)), E_OK)
#define Com_UpdateShadowSignal(x, y)         (ComIlPut##x((y)), E_OK)
#endif

#endif

/* -----------------------------------------------------------------------------
    &&&~ Set Tx Signals
 ----------------------------------------------------------------------------- */

#define ComIlPutMMI_RightSwStatus(x)         IlPutTxMMI_RightSwStatus(*(x))
#define ComIlPutMMI_LeftSwStatus(x)          IlPutTxMMI_LeftSwStatus(*(x))
#define ComIlPutMMI_UpSwStatus(x)            IlPutTxMMI_UpSwStatus(*(x))
#define ComIlPutMMI_DownSwStatus(x)          IlPutTxMMI_DownSwStatus(*(x))
#define ComIlPutMMI_ConfirmSwStatus(x)       IlPutTxMMI_ConfirmSwStatus(*(x))
#define ComIlPutMMI_ReturnSwStatus(x)        IlPutTxMMI_ReturnSwStatus(*(x))
#define ComIlPutMMI_WorkMode(x)              IlPutTxMMI_WorkMode(*(x))
#define ComIlPutTTS_BluetoothFunction(x)     IlPutTxTTS_BluetoothFunction(*(x))
#define ComIlPutTTS_BluetoothConnect(x)      IlPutTxTTS_BluetoothConnect(*(x))
#define ComIlPutMMI_TextMultDataFrame(x)     IlPutTxMMI_TextMultDataFrame((x))
#define ComIlPutMMI_TextBTDataFrame(x)       IlPutTxMMI_TextBTDataFrame((x))


/* -----------------------------------------------------------------------------
    &&&~ Get Rx Signals
 ----------------------------------------------------------------------------- */

#define ComIlGetPMS_VINMessageNum_S(x)       (*(x) = IlGetRxPMS_VINMessageNum_S())
#define ComIlGetPMS_VINCode1_8_15_S(x)       (*(x) = IlGetRxPMS_VINCode1_8_15_S())
#define ComIlGetPMS_VINCode2_9_16_S(x)       (*(x) = IlGetRxPMS_VINCode2_9_16_S())
#define ComIlGetPMS_VINCode3_10_17_S(x)      (*(x) = IlGetRxPMS_VINCode3_10_17_S())
#define ComIlGetPMS_VINCode4_11_S(x)         (*(x) = IlGetRxPMS_VINCode4_11_S())
#define ComIlGetPMS_VINCode5_12_S(x)         (*(x) = IlGetRxPMS_VINCode5_12_S())
#define ComIlGetPMS_VINCode6_13_S(x)         (*(x) = IlGetRxPMS_VINCode6_13_S())
#define ComIlGetPMS_VINCode7_14_S(x)         (*(x) = IlGetRxPMS_VINCode7_14_S())
#define ComIlGetIPK_IPKTotalOdometer(x)      (*(x) = IlGetRxIPK_IPKTotalOdometer())
#define ComIlGetTBOX_Second(x)               (*(x) = IlGetRxTBOX_Second())
#define ComIlGetTBOX_Minute(x)               (*(x) = IlGetRxTBOX_Minute())
#define ComIlGetTBOX_Hour(x)                 (*(x) = IlGetRxTBOX_Hour())
#define ComIlGetTBOX_Month(x)                (*(x) = IlGetRxTBOX_Month())
#define ComIlGetTBOX_Day(x)                  (*(x) = IlGetRxTBOX_Day())
#define ComIlGetTBOX_Year(x)                 (*(x) = IlGetRxTBOX_Year())
#define ComIlGetEHB_VehicleSpeedInvalid(x)   (*(x) = IlGetRxEHB_VehicleSpeedInvalid())
#define ComIlGetEHB_VehicleSpeed(x)          (*(x) = IlGetRxEHB_VehicleSpeed())





/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 528447840
      #error "The magic number of the generated file <E:\Bluetooth\code\Generate_code\N72_260119\il_par.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 528447840
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __IL_PAR_H__ */
