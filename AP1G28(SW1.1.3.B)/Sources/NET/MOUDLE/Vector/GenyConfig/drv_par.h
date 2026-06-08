/* -----------------------------------------------------------------------------
  Filename:    drv_par.h
  Description: Toolversion: 02.03.18.01.80.01.04.01.00.00
               
               Serial Number: CBD1800104
               Customer Info: Wenzhou Changjiang Automobile Electronic System Co.,Ltd.?CAEA)
                              Package: CBD_Vector_SLP2
                              Micro: FS32K146
                              Compiler: GNU 9.2.0
               
               
               Generator Fwk   : GENy 
               Generator Module: GenTool_GenyDriverBase
               
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

#if !defined(__DRV_PAR_H__)
#define __DRV_PAR_H__

/* -----------------------------------------------------------------------------
    &&&~ Signal Structures
 ----------------------------------------------------------------------------- */

typedef struct _c_VIU_FR_288_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 2;
  vbittype BcmPwrStsFb : 2;
  vbittype unused6 : 4;
} _c_VIU_FR_288_msgType;
typedef struct _c_VIU_FR_1C3_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype EspVehSpd_1 : 5;
  vbittype EspVehSpdVld : 1;
  vbittype unused4 : 2;
  vbittype EspVehSpd_0 : 8;
} _c_VIU_FR_1C3_msgType;
typedef struct _c_VIU_FR_2EC_msgTypeTag
{
  vbittype unused0 : 2;
  vbittype VcuVehGearPosnVld : 1;
  vbittype VcuGearPosn : 3;
  vbittype unused1 : 2;
} _c_VIU_FR_2EC_msgType;
typedef struct _c_VIU_FR_2EF_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype CdcTotMilg_2 : 8;
  vbittype CdcTotMilg_1 : 8;
  vbittype CdcTotMilg_0 : 8;
} _c_VIU_FR_2EF_msgType;
typedef struct _c_VIU_FR_2F7_msgTypeTag
{
  vbittype TboxLocalTiYear : 8;
  vbittype TboxLocalTiMth : 4;
  vbittype unused0 : 4;
  vbittype TboxLocalTiDate : 5;
  vbittype unused1 : 3;
  vbittype TboxLocalTiHr : 5;
  vbittype unused2 : 3;
  vbittype TboxLocalTiMins : 6;
  vbittype unused3 : 2;
  vbittype TboxLocalTiSec : 6;
  vbittype TboxLocalTiVld : 1;
  vbittype unused4 : 1;
} _c_VIU_FR_2F7_msgType;
typedef struct _c_VIU_FR_3ED_msgTypeTag
{
  vbittype FridgeQFunReq : 4;
  vbittype FridgeModeReq : 2;
  vbittype FridgeWorkReq : 2;
  vbittype FridgeUnlockCtrl : 2;
  vbittype FridgeHeatTempReq : 5;
  vbittype unused0 : 1;
  vbittype FridgeChdLockReq : 2;
  vbittype FridgeCoolTempReq : 5;
  vbittype unused1 : 1;
  vbittype FridgeUVLedReq : 2;
  vbittype FridgeUVLedWorkTimeSet : 5;
  vbittype unused2 : 1;
  vbittype ContinueWorkSw : 2;
  vbittype EgySaveModReq : 2;
  vbittype FridgeDoorWarnTimeSet : 3;
  vbittype unused3 : 1;
  vbittype ContinueWorkTimeSet : 8;
  vbittype unused4 : 4;
  vbittype VrhcuONReas : 2;
  vbittype VrhcuExOffReas : 2;
} _c_VIU_FR_3ED_msgType;
typedef struct _c_VRHCU_3EE_msgTypeTag
{
  vbittype FridgeWorkSt : 2;
  vbittype FridgeUVLedWorkSt : 5;
  vbittype unused0 : 1;
  vbittype FridgeDoorSt : 2;
  vbittype FridgeHeatTempSt : 5;
  vbittype unused1 : 1;
  vbittype FridgeModeSt : 2;
  vbittype FridgeCoolTempSt : 5;
  vbittype unused2 : 1;
  vbittype FridgeDoorWarnSt : 2;
  vbittype FridgeErrSt : 5;
  vbittype unused3 : 1;
  vbittype FridgeHeatActSt : 7;
  vbittype unused4 : 1;
  vbittype FridgeQFunSt : 4;
  vbittype FridgeChdLockSt : 2;
  vbittype EgySaveModSt : 2;
  vbittype FridgestuffSt : 2;
  vbittype FridgeUVLedSt : 2;
  vbittype FridgeDoorWarnTimeSt : 2;
  vbittype unused5 : 2;
  vbittype ContinueWorkTimeSt : 8;
} _c_VRHCU_3EE_msgType;
typedef struct _c_VRHCU_6F9_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype VRHCP_WakeUp_BYTE3BIT0 : 1;
  vbittype unused3 : 7;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 8;
  vbittype VRHCP_NotSleep_BYTE7BIT0 : 1;
  vbittype VRHCP_NotSleep_BYTE7BIT1 : 1;
  vbittype VRHCP_NotSleep_BYTE7BIT2 : 1;
  vbittype unused7 : 5;
} _c_VRHCU_6F9_msgType;
typedef struct _c_VRHCU_3F3_msgTypeTag
{
  vbittype VrhcuRequestACOn : 1;
  vbittype VrhcuRefrAcpTemp : 7;
  vbittype Vrhcupower : 7;
  vbittype unused0 : 1;
  vbittype VrhcuOffReas : 2;
  vbittype unused1 : 6;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 8;
} _c_VRHCU_3F3_msgType;
typedef struct _c_VRHCU_6EE_msgTypeTag
{
  vbittype VrhcuDTC1_HighByte : 8;
  vbittype VrhcuDTC1_MiddByte : 8;
  vbittype VrhcuDTC1_LowByte : 8;
  vbittype VrhcuDTC1_Status : 8;
  vbittype VrhcuDTC2_HighByte : 8;
  vbittype VrhcuDTC2_MiddByte : 8;
  vbittype VrhcuDTC2_LowByte : 8;
  vbittype VrhcuDTC2_Status : 8;
} _c_VRHCU_6EE_msgType;
typedef struct _c_VIU_FR_3D1_msgTypeTag
{
  vbittype unused0 : 4;
  vbittype DcdcOperSts : 4;
} _c_VIU_FR_3D1_msgType;
typedef struct _c_VIU_FR_3D3_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 4;
  vbittype BcuOperMod : 4;
} _c_VIU_FR_3D3_msgType;
typedef struct _c_NMm_VRHCU_msgTypeTag
{
  vbittype srcNodeID_VRHCU : 8;
  vbittype RMR_VRHCU : 1;
  vbittype unused0 : 2;
  vbittype NMCSR_VRHCU : 1;
  vbittype AWU_VRHCU : 1;
  vbittype unused1 : 1;
  vbittype PNI_VRHCU : 1;
  vbittype unused2 : 1;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 7;
  vbittype NMSI_VRHCU : 1;
  vbittype unused7 : 8;
  vbittype FunctionID_VRHCU : 8;
} _c_NMm_VRHCU_msgType;


/* -----------------------------------------------------------------------------
    &&&~ Signal value names
 ----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
    &&&~ Message Unions
 ----------------------------------------------------------------------------- */

typedef union _c_TxDynamicMsg0_bufTag
{
  vuint8 _c[8];
} _c_TxDynamicMsg0_buf;
typedef union _c_VIU_FR_288_bufTag
{
  vuint8 _c[6];
  _c_VIU_FR_288_msgType VIU_FR_288;
} _c_VIU_FR_288_buf;
typedef union _c_VIU_FR_1C3_bufTag
{
  vuint8 _c[6];
  _c_VIU_FR_1C3_msgType VIU_FR_1C3;
} _c_VIU_FR_1C3_buf;
typedef union _c_VIU_FR_2EC_bufTag
{
  vuint8 _c[1];
  _c_VIU_FR_2EC_msgType VIU_FR_2EC;
} _c_VIU_FR_2EC_buf;
typedef union _c_VIU_FR_2EF_bufTag
{
  vuint8 _c[4];
  _c_VIU_FR_2EF_msgType VIU_FR_2EF;
} _c_VIU_FR_2EF_buf;
typedef union _c_VIU_FR_2F7_bufTag
{
  vuint8 _c[6];
  _c_VIU_FR_2F7_msgType VIU_FR_2F7;
} _c_VIU_FR_2F7_buf;
typedef union _c_VIU_FR_3ED_bufTag
{
  vuint8 _c[7];
  _c_VIU_FR_3ED_msgType VIU_FR_3ED;
} _c_VIU_FR_3ED_buf;
typedef union _c_VRHCU_3EE_bufTag
{
  vuint8 _c[8];
  _c_VRHCU_3EE_msgType VRHCU_3EE;
} _c_VRHCU_3EE_buf;
typedef union _c_VRHCU_6F9_bufTag
{
  vuint8 _c[8];
  _c_VRHCU_6F9_msgType VRHCU_6F9;
} _c_VRHCU_6F9_buf;
typedef union _c_VRHCU_3F3_bufTag
{
  vuint8 _c[8];
  _c_VRHCU_3F3_msgType VRHCU_3F3;
} _c_VRHCU_3F3_buf;
typedef union _c_VRHCU_6EE_bufTag
{
  vuint8 _c[8];
  _c_VRHCU_6EE_msgType VRHCU_6EE;
} _c_VRHCU_6EE_buf;
typedef union _c_VIU_FR_3D1_bufTag
{
  vuint8 _c[1];
  _c_VIU_FR_3D1_msgType VIU_FR_3D1;
} _c_VIU_FR_3D1_buf;
typedef union _c_VIU_FR_3D3_bufTag
{
  vuint8 _c[6];
  _c_VIU_FR_3D3_msgType VIU_FR_3D3;
} _c_VIU_FR_3D3_buf;
typedef union _c_NMm_VRHCU_bufTag
{
  vuint8 _c[8];
  _c_NMm_VRHCU_msgType NMm_VRHCU;
} _c_NMm_VRHCU_buf;


/* -----------------------------------------------------------------------------
    &&&~ Message Buffers
 ----------------------------------------------------------------------------- */

/* RAM CATEGORY 2 START */
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TxDynamicMsg0_buf V_MEMRAM2 TxDynamicMsg0;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_VIU_FR_288_buf V_MEMRAM2 VIU_FR_288;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_VIU_FR_1C3_buf V_MEMRAM2 VIU_FR_1C3;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_VIU_FR_2EC_buf V_MEMRAM2 VIU_FR_2EC;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_VIU_FR_2EF_buf V_MEMRAM2 VIU_FR_2EF;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_VIU_FR_2F7_buf V_MEMRAM2 VIU_FR_2F7;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_VIU_FR_3ED_buf V_MEMRAM2 VIU_FR_3ED;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_VRHCU_3EE_buf V_MEMRAM2 VRHCU_3EE;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_VRHCU_6F9_buf V_MEMRAM2 VRHCU_6F9;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_VRHCU_3F3_buf V_MEMRAM2 VRHCU_3F3;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_VRHCU_6EE_buf V_MEMRAM2 VRHCU_6EE;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_VIU_FR_3D1_buf V_MEMRAM2 VIU_FR_3D1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_VIU_FR_3D3_buf V_MEMRAM2 VIU_FR_3D3;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_NMm_VRHCU_buf V_MEMRAM2 NMm_VRHCU;
/* RAM CATEGORY 2 END */






#endif /* __DRV_PAR_H__ */
