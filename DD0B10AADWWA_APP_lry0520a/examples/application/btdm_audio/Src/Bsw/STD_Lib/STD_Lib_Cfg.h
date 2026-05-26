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
#define _STD_LIB_CFG_H      /* polyspace MISRA-C3:21.1 [Justified:Low] "Preventing duplicate compilation" */

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/

/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define STD_LIB_DISABLE                 (STD_OFF)            /* polyspace MISRA-C3:2.5 [Justified:Low] "Platform reservation macro definition" */
#define STD_LIB_ENABLE                  (STD_ON)

#define STD_LIBCFG_SETMEMORY            STD_ON
#define STD_LIBCFG_COMPARE              STD_ON
#define STD_LIBCFG_COMPARER             STD_OFF
#define STD_LIBCFG_COPY                 STD_ON
#define STD_LIBCFG_COPYR                STD_OFF    
#define STD_LIBCFG_BUBBLESORT           STD_OFF
#define STD_LIBCFG_CALCULATEAVERAGE     STD_ON
#define STD_LIBCFG_READDATA             STD_OFF
#define STD_LIBCFG_STATUSFILTER         STD_ON
#define STD_LIBCFG_IIRFILTER            STD_OFF
#define STD_LIBCFG_BINARYSEARCH         STD_OFF
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
