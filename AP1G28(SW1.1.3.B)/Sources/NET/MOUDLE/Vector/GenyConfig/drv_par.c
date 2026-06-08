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

#include "v_inc.h"
#include "can_inc.h"

#include "drv_par.h"
/* -----------------------------------------------------------------------------
    &&&~ Message Buffers
 ----------------------------------------------------------------------------- */

/* RAM CATEGORY 2 START */
/* PRQA  S 0759 QAC_Can_0759 */ /* MD_Can_0759 */
V_MEMRAM0 V_MEMRAM1 _c_TxDynamicMsg0_buf V_MEMRAM2 TxDynamicMsg0;
V_MEMRAM0 V_MEMRAM1 _c_VIU_FR_288_buf V_MEMRAM2 VIU_FR_288;
V_MEMRAM0 V_MEMRAM1 _c_VIU_FR_1C3_buf V_MEMRAM2 VIU_FR_1C3;
V_MEMRAM0 V_MEMRAM1 _c_VIU_FR_2EC_buf V_MEMRAM2 VIU_FR_2EC;
V_MEMRAM0 V_MEMRAM1 _c_VIU_FR_2EF_buf V_MEMRAM2 VIU_FR_2EF;
V_MEMRAM0 V_MEMRAM1 _c_VIU_FR_2F7_buf V_MEMRAM2 VIU_FR_2F7;
V_MEMRAM0 V_MEMRAM1 _c_VIU_FR_3ED_buf V_MEMRAM2 VIU_FR_3ED;
V_MEMRAM0 V_MEMRAM1 _c_VRHCU_3EE_buf V_MEMRAM2 VRHCU_3EE;
V_MEMRAM0 V_MEMRAM1 _c_VRHCU_6F9_buf V_MEMRAM2 VRHCU_6F9;
V_MEMRAM0 V_MEMRAM1 _c_VRHCU_3F3_buf V_MEMRAM2 VRHCU_3F3;
V_MEMRAM0 V_MEMRAM1 _c_VRHCU_6EE_buf V_MEMRAM2 VRHCU_6EE;
V_MEMRAM0 V_MEMRAM1 _c_VIU_FR_3D1_buf V_MEMRAM2 VIU_FR_3D1;
V_MEMRAM0 V_MEMRAM1 _c_VIU_FR_3D3_buf V_MEMRAM2 VIU_FR_3D3;
V_MEMRAM0 V_MEMRAM1 _c_NMm_VRHCU_buf V_MEMRAM2 NMm_VRHCU;
/* PRQA  L:QAC_Can_0759 */

/* RAM CATEGORY 2 END */





