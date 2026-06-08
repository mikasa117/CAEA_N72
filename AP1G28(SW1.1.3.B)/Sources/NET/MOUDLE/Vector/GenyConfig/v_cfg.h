/* -----------------------------------------------------------------------------
  Filename:    v_cfg.h
  Description: Toolversion: 02.03.18.01.80.01.04.01.00.00
               
               Serial Number: CBD1800104
               Customer Info: Wenzhou Changjiang Automobile Electronic System Co.,Ltd.?CAEA)
                              Package: CBD_Vector_SLP2
                              Micro: FS32K146
                              Compiler: GNU 9.2.0
               
               
               Generator Fwk   : GENy 
               Generator Module: GenTool_GenyVcfgNameDecorator
               
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

#if !defined(__V_CFG_H__)
#define __V_CFG_H__

#ifndef VGEN_GENY
#define VGEN_GENY
#endif

#ifndef GENy
#define GENy
#endif

#ifndef SUPPLIER_CANBEDDED
#define SUPPLIER_CANBEDDED                   30
#endif

/* -----------------------------------------------------------------------------
    &&&~ Version
 ----------------------------------------------------------------------------- */

#ifndef VERSIONNUMBER
#define VERSIONNUMBER                        0x11
#endif



/* -----------------------------------------------------------------------------
    &&&~ General Switches
 ----------------------------------------------------------------------------- */

#ifndef V_OSTYPE_NONE
#define V_OSTYPE_NONE
#endif



/* -----------------------------------------------------------------------------
    &&&~ Processor specific
 ----------------------------------------------------------------------------- */

#ifndef C_CPUTYPE_32BIT
#define C_CPUTYPE_32BIT
#endif


#ifndef V_CPUTYPE_BITARRAY_32BIT
#define V_CPUTYPE_BITARRAY_32BIT
#endif


#ifndef C_CPUTYPE_LITTLEENDIAN
#define C_CPUTYPE_LITTLEENDIAN
#endif


#ifndef C_CPUTYPE_BITORDER_LSB2MSB
#define C_CPUTYPE_BITORDER_LSB2MSB
#endif


#ifndef V_DISABLE_USE_DUMMY_FUNCTIONS
#define V_DISABLE_USE_DUMMY_FUNCTIONS
#endif


#ifndef V_ENABLE_USE_DUMMY_STATEMENT
#define V_ENABLE_USE_DUMMY_STATEMENT
#endif


#ifndef C_COMP_GNU_S32_FLEXCAN3
#define C_COMP_GNU_S32_FLEXCAN3
#endif


#ifndef V_CPU_S32
#define V_CPU_S32
#endif

#ifndef V_COMP_GNU
#define V_COMP_GNU
#endif

#ifndef V_COMP_GNU_S32
#define V_COMP_GNU_S32
#endif

#ifndef V_PROCESSOR_S32K146
#define V_PROCESSOR_S32K146
#endif


#ifndef C_PROCESSOR_S32K146
#define C_PROCESSOR_S32K146
#endif




/* -----------------------------------------------------------------------------
    &&&~ Used Modules
 ----------------------------------------------------------------------------- */

#define VGEN_ENABLE_DIAG_CANDESC_UDS
#define VGEN_ENABLE_CCL
#ifndef VGEN_ENABLE_VSTDLIB
#define VGEN_ENABLE_VSTDLIB
#endif

#ifndef VSTD_ENABLE_APPL_INTCTRL
#define VSTD_ENABLE_APPL_INTCTRL
#endif

void INT_SYS_DisableIRQGlobal(void);
void INT_SYS_EnableIRQGlobal(void);
#ifndef VStdUserNestedDisable
#define VStdUserNestedDisable                INT_SYS_DisableIRQGlobal
#endif

#ifndef VStdUserNestedRestore
#define VStdUserNestedRestore                INT_SYS_EnableIRQGlobal
#endif

#ifndef VSTD_DISABLE_DEBUG_SUPPORT
#define VSTD_DISABLE_DEBUG_SUPPORT
#endif

#ifndef VSTD_ENABLE_LIBRARY_FUNCTIONS
#define VSTD_ENABLE_LIBRARY_FUNCTIONS
#endif


#define VGEN_ENABLE_CAN_DRV
#define C_ENABLE_CAN_CHANNELS
#define V_BUSTYPE_CAN
#define VGEN_ENABLE_IL_VECTOR
#define VGEN_ENABLE_NM_ASR_IF
#define VGEN_ENABLE_NM_ASRNMCANWRAPPEREXT
#define VGEN_ENABLE_NM_ASR_CAN
#define VGEN_ENABLE_TP_ISO_MC


#ifndef kVNumberOfIdentities
#define kVNumberOfIdentities                 1
#endif

#ifndef tVIdentityMsk
#define tVIdentityMsk                        vuint8
#endif

#ifndef kVIdentityIdentity_0
#define kVIdentityIdentity_0                 (vuint8) 0
#endif

#ifndef VSetActiveIdentity
#define VSetActiveIdentity(identityLog)
#endif

#ifndef V_ACTIVE_IDENTITY_MSK
#define V_ACTIVE_IDENTITY_MSK                1
#endif

#ifndef V_ACTIVE_IDENTITY_LOG
#define V_ACTIVE_IDENTITY_LOG                0
#endif


#define DIAG_API_CALL_TYPE
#define DIAG_API_CALLBACK_TYPE
#define DIAG_INTERNAL_CALL_TYPE
/* -----------------------------------------------------------------------------
    &&&~ Paging support
 ----------------------------------------------------------------------------- */

#define CCL_API_CALL_TYPE
#define CCL_API_CALLBACK_TYPE
#define CCL_INTERNAL_CALL_TYPE


#define TP_API_CALL_TYPE
#define TP_API_CALLBACK_TYPE
#define TP_INTERNAL_CALL_TYPE

/* -----------------------------------------------------------------------------
    &&&~ ExtendedAsrVersionCheck
 ----------------------------------------------------------------------------- */

/* V_SUPPRESS_EXTENDED_VERSION_CHECK */


/* -----------------------------------------------------------------------------
    &&&~ Optimization
 ----------------------------------------------------------------------------- */

#ifndef V_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define V_ATOMIC_BIT_ACCESS_IN_BITFIELD      STD_OFF
#endif

#ifndef V_ATOMIC_VARIABLE_ACCESS
#define V_ATOMIC_VARIABLE_ACCESS             16
#endif




#ifndef VGEN_ENABLE_VSTDLIB
/* Diag_CanDesc requires VSTDLIB */
#define VGEN_ENABLE_VSTDLIB
#endif

#ifndef C_CLIENT_VECTOR
#define C_CLIENT_VECTOR
#endif

#ifndef __VRHCU__
#define __VRHCU__
#endif

/* -----------------------------------------------------------------------------
    &&&~ Compatibility defines for ComSetCurrentECU
 ----------------------------------------------------------------------------- */

#ifndef kComNumberOfNodes
#define kComNumberOfNodes                    kVNumberOfIdentities
#endif

#ifndef ComSetCurrentECU
#define ComSetCurrentECU                     VSetActiveIdentity
#endif

#ifndef comMultipleECUCurrent
#define comMultipleECUCurrent                vActiveIdentityLog
#endif



#define C_VERSION_REF_IMPLEMENTATION         0x200u


#ifndef VGEN_ENABLE_VSTDLIB
/* DrvCan__baseRi15 requires VSTDLIB */
#define VGEN_ENABLE_VSTDLIB
#endif

#ifndef VGEN_ENABLE_VSTDLIB
#define VGEN_ENABLE_VSTDLIB
#endif


#ifndef VGEN_ENABLE_VSTDLIB
/* TpMC requires VSTDLIB */
#define VGEN_ENABLE_VSTDLIB
#endif



#endif /* __V_CFG_H__ */
