/*******************************************************************************
|  File Name:  Std_Lib_Cfg.h
|  Description:  Implementation of the Lib Config Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           YaJun Xia              CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2018-05-16    01.00.00     LSG       Creation
|
|******************************************************************************/

#if!defined (_STD_LIB_CFG_H)
#define _STD_LIB_CFG_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define STD_LIB_DISABLE                 (0U)
#define STD_LIB_ENABLE                  (1U)

#define STD_LIBCFG_SETMEMORY            STD_LIB_ENABLE
#define STD_LIBCFG_COMPARE              STD_LIB_ENABLE
#define STD_LIBCFG_COMPARER             STD_LIB_ENABLE
#define STD_LIBCFG_COPY                 STD_LIB_ENABLE
#define STD_LIBCFG_COPYR                STD_LIB_ENABLE    
#define STD_LIBCFG_BUBBLESORT           STD_LIB_ENABLE
#define STD_LIBCFG_CALCULATEAVERAGE     STD_LIB_ENABLE
#define STD_LIBCFG_READDATA             STD_LIB_ENABLE
#define STD_LIBCFG_STATUSFILTER         STD_LIB_ENABLE
#define STD_LIBCFG_BINARYSEARCH         STD_LIB_ENABLE
/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Table Definition
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/

#endif
/*EOF*/
