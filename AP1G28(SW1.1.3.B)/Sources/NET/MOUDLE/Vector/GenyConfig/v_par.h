/* -----------------------------------------------------------------------------
  Filename:    v_par.h
  Description: Toolversion: 02.03.18.01.80.01.04.01.00.00
               
               Serial Number: CBD1800104
               Customer Info: Wenzhou Changjiang Automobile Electronic System Co.,Ltd.?CAEA)
                              Package: CBD_Vector_SLP2
                              Micro: FS32K146
                              Compiler: GNU 9.2.0
               
               
               Generator Fwk   : GENy 
               Generator Module: GenTool_GenyVcfgNameDecorator
               
               Configuration   : E:\work\ChangAn\AP1G28AACXWA\APP\config\Geny\GENy1.gny
               
               ECU: 
                       TargetSystem: Hw_S32Cpu
                       Compiler:     GNU
                       Derivates:    S32K144
               
               Channel "VRHCU":
                       Databasefile: E:\work\ChangAn\AP1G28AACXWA\APP\config\inputfile\1VIUF1_CAN_CX810Õû³µÍ¨ÐÅÐ­Òé£¨¸ßµÍ¹²°æ£©V4.4.0_20250907£¨ÏµÁÐ»¯Æ½Ì¨£©.dbc
                       Bussystem:    CAN
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

#if !defined(__V_PAR_H__)
#define __V_PAR_H__

/* -----------------------------------------------------------------------------
    &&&~ BaseEnv_PHF_Includes
 ----------------------------------------------------------------------------- */

#include "v_cfg.h"
#include "v_def.h"


/* -----------------------------------------------------------------------------
    &&&~ GENy Version Information
 ----------------------------------------------------------------------------- */

#define VGEN_DELIVERY_VERSION_BYTE_0         0x02
#define VGEN_DELIVERY_VERSION_BYTE_1         0x03
#define VGEN_DELIVERY_VERSION_BYTE_2         0x18
#define VGEN_DELIVERY_VERSION_BYTE_3         0x01
#define VGEN_DELIVERY_VERSION_BYTE_4         0x80
#define VGEN_DELIVERY_VERSION_BYTE_5         0x01
#define VGEN_DELIVERY_VERSION_BYTE_6         0x04
#define VGEN_DELIVERY_VERSION_BYTE_7         0x01
#define VGEN_DELIVERY_VERSION_BYTE_8         0x00
#define VGEN_DELIVERY_VERSION_BYTE_9         0x00
#define kGENyVersionNumberOfBytes            10
/* ROM CATEGORY 4 START */
V_MEMROM0 extern  V_MEMROM1 vuint8 V_MEMROM2 kGENyVersion[kGENyVersionNumberOfBytes];
/* ROM CATEGORY 4 END */



typedef struct tDBCVersionTag
{
  vuint8 kYear;
  vuint8 kMonth;
  vuint8 kWeek;
  vuint8 kDay;
  vuint32 kNumber;
} tDBCVersion;
V_MEMROM0 extern  V_MEMROM1 tDBCVersion V_MEMROM2 kDBCVersion[1];

#endif /* __V_PAR_H__ */
