/*******************************************************************************
|  File Name:  STD_MemMap.h
|  Description:  Implementation of the Memery Map File
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
| 2016-11-30    01.00.00     XYJ       Creation
|
|******************************************************************************/


/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_Compiler.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/
/*#define _GREENHILLS_C_MPC560XB_*/
//#define _CODEWARRIOR_C_MPC560XB_
/* polyspace<MISRA-C3:5.4:Not a defect:Justified> Normal */
/* polyspace<MISRA-C3:21.1:Not a defect:Justified> Normal */
/* polyspace<MISRA-C3:2.5:Not a defect:Justified> Normal */
/*#define _GNU_C_Compiler_S32KXX_*/
#if ((MCU_TYPE & MCU_RENESAS_RL78) == MCU_RENESAS_RL78)
#ifdef STD_BSW_START_SEC_KAM
#undef STD_BSW_START_SEC_KAM
#pragma section bss APP_KAM_DATA
#endif

#ifdef STD_BSW_STOP_SEC_KAM
#undef STD_BSW_STOP_SEC_KAM
#pragma section
#endif
#endif
/**************************************************************************************************/
/********************************************* GREENHILLS *****************************************/
/**************************************************************************************************/

/*EOF*/
