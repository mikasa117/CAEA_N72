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

#if !defined(__DRV_PAR_H__)
#define __DRV_PAR_H__

#include "v_inc.h"

/* -----------------------------------------------------------------------------
    &&&~ Signal Structures
 ----------------------------------------------------------------------------- */

typedef struct _c_Func_DiagReq_msgTypeTag
{
  vbittype Func_DiagResp_7 : 8;
  vbittype Func_DiagResp_6 : 8;
  vbittype Func_DiagResp_5 : 8;
  vbittype Func_DiagResp_4 : 8;
  vbittype Func_DiagResp_3 : 8;
  vbittype Func_DiagResp_2 : 8;
  vbittype Func_DiagResp_1 : 8;
  vbittype Func_DiagResp_0 : 8;
} _c_Func_DiagReq_msgType;
typedef struct _c_EHB_Status_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype EHB_VehicleSpeed_1 : 8;
  vbittype unused1 : 2;
  vbittype EHB_VehicleSpeedInvalid : 1;
  vbittype EHB_VehicleSpeed_0 : 5;
} _c_EHB_Status_msgType;
typedef struct _c_TBOX_DateTime_Info_msgTypeTag
{
  vbittype TBOX_Second : 8;
  vbittype TBOX_Minute : 8;
  vbittype TBOX_Hour : 8;
  vbittype TBOX_Month : 8;
  vbittype TBOX_Day : 8;
  vbittype TBOX_Year : 8;
} _c_TBOX_DateTime_Info_msgType;
typedef struct _c_IPK_TotalOdometer_msgTypeTag
{
  vbittype IPK_IPKTotalOdometer_2 : 8;
  vbittype IPK_IPKTotalOdometer_1 : 8;
  vbittype IPK_IPKTotalOdometer_0 : 8;
} _c_IPK_TotalOdometer_msgType;
typedef struct _c_BTM_DiagResp_msgTypeTag
{
  vbittype BTM_DiagResp_7 : 8;
  vbittype BTM_DiagResp_6 : 8;
  vbittype BTM_DiagResp_5 : 8;
  vbittype BTM_DiagResp_4 : 8;
  vbittype BTM_DiagResp_3 : 8;
  vbittype BTM_DiagResp_2 : 8;
  vbittype BTM_DiagResp_1 : 8;
  vbittype BTM_DiagResp_0 : 8;
} _c_BTM_DiagResp_msgType;
typedef struct _c_BTM_DiagReq_msgTypeTag
{
  vbittype BTM_DiagReq_7 : 8;
  vbittype BTM_DiagReq_6 : 8;
  vbittype BTM_DiagReq_5 : 8;
  vbittype BTM_DiagReq_4 : 8;
  vbittype BTM_DiagReq_3 : 8;
  vbittype BTM_DiagReq_2 : 8;
  vbittype BTM_DiagReq_1 : 8;
  vbittype BTM_DiagReq_0 : 8;
} _c_BTM_DiagReq_msgType;
typedef struct _c_TTS_Status_msgTypeTag
{
  vbittype unused0 : 4;
  vbittype TTS_BluetoothFunction : 1;
  vbittype TTS_BluetoothConnect : 1;
  vbittype unused1 : 2;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 8;
  vbittype unused7 : 8;
  vbittype unused8 : 8;
} _c_TTS_Status_msgType;
typedef struct _c_MMI_Status_Info_msgTypeTag
{
  vbittype MMI_RightSwStatus : 2;
  vbittype MMI_LeftSwStatus : 2;
  vbittype MMI_UpSwStatus : 2;
  vbittype MMI_DownSwStatus : 2;
  vbittype MMI_ConfirmSwStatus : 2;
  vbittype MMI_ReturnSwStatus : 2;
  vbittype MMI_WorkMode : 2;
  vbittype unused0 : 2;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 8;
} _c_MMI_Status_Info_msgType;
typedef struct _c_MMI_TextBTData_msgTypeTag
{
  vbittype MMI_TextBTDataFrame_7 : 8;
  vbittype MMI_TextBTDataFrame_6 : 8;
  vbittype MMI_TextBTDataFrame_5 : 8;
  vbittype MMI_TextBTDataFrame_4 : 8;
  vbittype MMI_TextBTDataFrame_3 : 8;
  vbittype MMI_TextBTDataFrame_2 : 8;
  vbittype MMI_TextBTDataFrame_1 : 8;
  vbittype MMI_TextBTDataFrame_0 : 8;
} _c_MMI_TextBTData_msgType;
typedef struct _c_MMI_TextMMData_msgTypeTag
{
  vbittype MMI_TextMultDataFrame_7 : 8;
  vbittype MMI_TextMultDataFrame_6 : 8;
  vbittype MMI_TextMultDataFrame_5 : 8;
  vbittype MMI_TextMultDataFrame_4 : 8;
  vbittype MMI_TextMultDataFrame_3 : 8;
  vbittype MMI_TextMultDataFrame_2 : 8;
  vbittype MMI_TextMultDataFrame_1 : 8;
  vbittype MMI_TextMultDataFrame_0 : 8;
} _c_MMI_TextMMData_msgType;
typedef struct _c_PMS_VIN_msgTypeTag
{
  vbittype PMS_VINMessageNum_S : 8;
  vbittype PMS_VINCode1_8_15_S : 8;
  vbittype PMS_VINCode2_9_16_S : 8;
  vbittype PMS_VINCode3_10_17_S : 8;
  vbittype PMS_VINCode4_11_S : 8;
  vbittype PMS_VINCode5_12_S : 8;
  vbittype PMS_VINCode6_13_S : 8;
  vbittype PMS_VINCode7_14_S : 8;
} _c_PMS_VIN_msgType;


/* -----------------------------------------------------------------------------
    &&&~ Signal value names
 ----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
    &&&~ Message Unions
 ----------------------------------------------------------------------------- */

typedef union _c_Func_DiagReq_bufTag
{
  vuint8 _c[8];
  _c_Func_DiagReq_msgType Func_DiagReq;
} _c_Func_DiagReq_buf;
typedef union _c_TxDynamicMsg0_bufTag
{
  vuint8 _c[8];
} _c_TxDynamicMsg0_buf;
typedef union _c_EHB_Status_bufTag
{
  vuint8 _c[3];
  _c_EHB_Status_msgType EHB_Status;
} _c_EHB_Status_buf;
typedef union _c_TBOX_DateTime_Info_bufTag
{
  vuint8 _c[6];
  _c_TBOX_DateTime_Info_msgType TBOX_DateTime_Info;
} _c_TBOX_DateTime_Info_buf;
typedef union _c_IPK_TotalOdometer_bufTag
{
  vuint8 _c[3];
  _c_IPK_TotalOdometer_msgType IPK_TotalOdometer;
} _c_IPK_TotalOdometer_buf;
typedef union _c_BTM_DiagResp_bufTag
{
  vuint8 _c[8];
  _c_BTM_DiagResp_msgType BTM_DiagResp;
} _c_BTM_DiagResp_buf;
typedef union _c_BTM_DiagReq_bufTag
{
  vuint8 _c[8];
  _c_BTM_DiagReq_msgType BTM_DiagReq;
} _c_BTM_DiagReq_buf;
typedef union _c_TTS_Status_bufTag
{
  vuint8 _c[8];
  _c_TTS_Status_msgType TTS_Status;
} _c_TTS_Status_buf;
typedef union _c_MMI_Status_Info_bufTag
{
  vuint8 _c[8];
  _c_MMI_Status_Info_msgType MMI_Status_Info;
} _c_MMI_Status_Info_buf;
typedef union _c_MMI_TextBTData_bufTag
{
  vuint8 _c[8];
  _c_MMI_TextBTData_msgType MMI_TextBTData;
} _c_MMI_TextBTData_buf;
typedef union _c_MMI_TextMMData_bufTag
{
  vuint8 _c[8];
  _c_MMI_TextMMData_msgType MMI_TextMMData;
} _c_MMI_TextMMData_buf;
typedef union _c_PMS_VIN_bufTag
{
  vuint8 _c[8];
  _c_PMS_VIN_msgType PMS_VIN;
} _c_PMS_VIN_buf;


/* -----------------------------------------------------------------------------
    &&&~ Message Buffers
 ----------------------------------------------------------------------------- */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_Func_DiagReq_buf V_MEMRAM2 Func_DiagReq;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TxDynamicMsg0_buf V_MEMRAM2 TxDynamicMsg0;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_EHB_Status_buf V_MEMRAM2 EHB_Status;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TBOX_DateTime_Info_buf V_MEMRAM2 TBOX_DateTime_Info;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_IPK_TotalOdometer_buf V_MEMRAM2 IPK_TotalOdometer;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_BTM_DiagResp_buf V_MEMRAM2 BTM_DiagResp;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_BTM_DiagReq_buf V_MEMRAM2 BTM_DiagReq;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TTS_Status_buf V_MEMRAM2 TTS_Status;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_MMI_Status_Info_buf V_MEMRAM2 MMI_Status_Info;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_MMI_TextBTData_buf V_MEMRAM2 MMI_TextBTData;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_MMI_TextMMData_buf V_MEMRAM2 MMI_TextMMData;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_PMS_VIN_buf V_MEMRAM2 PMS_VIN;
/* RAM CATEGORY 2 END */







/* end Fileversion check */

#endif /* __DRV_PAR_H__ */
