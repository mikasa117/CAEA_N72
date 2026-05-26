/* -----------------------------------------------------------------------------
  Filename:    drv_par.c
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
                       Databasefile: E:\Bluetooth\DBC\N72��ĿBTM_20260117.dbc
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

#include "v_inc.h"
#include "can_inc.h"

#include "drv_par.h"
/* -----------------------------------------------------------------------------
    &&&~ Message Buffers
 ----------------------------------------------------------------------------- */

/* RAM CATEGORY 2 START */
/* PRQA  S 0759 QAC_Can_0759 */ /* MD_Can_0759 */
V_MEMRAM0 V_MEMRAM1 _c_Func_DiagReq_buf V_MEMRAM2 Func_DiagReq;
V_MEMRAM0 V_MEMRAM1 _c_TxDynamicMsg0_buf V_MEMRAM2 TxDynamicMsg0;
V_MEMRAM0 V_MEMRAM1 _c_EHB_Status_buf V_MEMRAM2 EHB_Status;
V_MEMRAM0 V_MEMRAM1 _c_TBOX_DateTime_Info_buf V_MEMRAM2 TBOX_DateTime_Info;
V_MEMRAM0 V_MEMRAM1 _c_IPK_TotalOdometer_buf V_MEMRAM2 IPK_TotalOdometer;
V_MEMRAM0 V_MEMRAM1 _c_BTM_DiagResp_buf V_MEMRAM2 BTM_DiagResp;
V_MEMRAM0 V_MEMRAM1 _c_BTM_DiagReq_buf V_MEMRAM2 BTM_DiagReq;
V_MEMRAM0 V_MEMRAM1 _c_TTS_Status_buf V_MEMRAM2 TTS_Status;
V_MEMRAM0 V_MEMRAM1 _c_MMI_Status_Info_buf V_MEMRAM2 MMI_Status_Info;
V_MEMRAM0 V_MEMRAM1 _c_MMI_TextBTData_buf V_MEMRAM2 MMI_TextBTData;
V_MEMRAM0 V_MEMRAM1 _c_MMI_TextMMData_buf V_MEMRAM2 MMI_TextMMData;
V_MEMRAM0 V_MEMRAM1 _c_PMS_VIN_buf V_MEMRAM2 PMS_VIN;
/* PRQA  L:QAC_Can_0759 */

/* RAM CATEGORY 2 END */







