#ifndef BtrM_H_
#define BtrM_H_
/* polyspace<MISRA-C3:1.1:Not a defect:Justify with annotations> The high number of macros is due to inclusion of microcontroller's header. */
/**
 * \file       STD_BtrM.h
 * \author     wujie
 * \brief      Header file for the Battery Manager.
 *
 * \par        Platform File
 *
 *
 * \copyright (c) 2019 CAEA, all rights reserved.
 */

/*------------------------------------------------------------------------------
 Information for the configuration management-system:
 -------------------------------------------------------------------------------
 (Will be generated automatically during Check-In into SVN)
 $Revision: 751 $
 $Date: 2024-04-15 09:17:06 +0800 (周一, 15 4月 2024) $
 $Author: xieshangfeng $
 -------------------------------------------------------------------------------
                R E V I S I O N   H I S T O R Y
 -------------------------------------------------------------------------------


------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                           Includes                                         */
/*----------------------------------------------------------------------------*/
#include "BtrM_Cfg.h"
#include "Rte_BtrM.h"

/*----------------------------------------------------------------------------*/
/*                         Defines and macros                                 */
/*----------------------------------------------------------------------------*/
/**
* @addtogroup macros_enum
* @{
*/

#define BTRM_DEFAULT_VALUE  ((uint8)0u)

/*Power State Machine */
#define BTRM_INIT           ((uint8)0u)
#define BTRM_NORMAL         ((uint8)1u)

/* Version - BCD coded version number - Main- and Sub-Version - Release-Version */
#define SYSSERVICE_ASR4BTRM_VERSION                                  0x0101u
#define SYSSERVICE_ASR4BTRM_RELEASE_VERSION                          0x02u

/* vendor and module identification */
/*#define BTRM_VENDOR_ID                                               (30u)*/   /* Vector Informatik GmbH */
#define BTRM_MODULE_ID                                               (0x0102u)
/*#define BTRM_INSTANCE_ID                                             (0u)*/
 
/* Component Version Information */
#define BTRM_SW_MAJOR_VERSION                                        (SYSSERVICE_ASR4BTRM_VERSION >> 8)
#define BTRM_SW_MINOR_VERSION                                        (SYSSERVICE_ASR4BTRM_VERSION & 0x00FFu)
#define BTRM_SW_PATCH_VERSION                                        (SYSSERVICE_ASR4BTRM_RELEASE_VERSION)

/* ----------Error Codes in Development-Mode------------------------------- */
/* polyspace<MISRA-C3:2.5:Not a defect:Justify with annotations> not affect */
#define BTRM_E_UNINIT                                                (0x10u)
#define BTRM_E_NULL_POINTER                                          (0x12u)

/* Vector extensions to the standard error codes  SWS -------------------------------*/
#define BTRM_E_NO_ERROR                                              (0x00u)

/*For STD_BtrM*/
/*\brief Power Mode A*/
#define STD_BTRM_MODE_A (0U)
/*\brief Power Mode B*/
#define STD_BTRM_MODE_B (1U)
/*\brief Power Mode C*/
#define STD_BTRM_MODE_C (2U)
#define STD_BTRM_MODE_B_TO_A  (3U)
#define STD_BTRM_MODE_B_TO_C  (4U)

/** @} *//* Macros_Enum definition */

/*----------------------------------------------------------------------------*/
/*                              Data types                                    */
/*----------------------------------------------------------------------------*/
/**
* @addtogroup Typedefs
* @{
*/



/** @} *//* Typedefs definition */

/*----------------------------------------------------------------------------*/
/*                External declaration of global RAM-Variables                */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                External declaration of global ROM-Variables                */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*               External declaration of global EEPROM-Variables              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                  External declaration of global functions                  */
/*----------------------------------------------------------------------------*/
extern void BtrM_Init(void);
extern uint8 BtrM_GetVersioninfo(Std_VersionInfoType  *tVersioninfoStruct);
#endif
/*EOF*/



