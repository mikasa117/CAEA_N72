#ifndef BTRM_CFG_H
#define BTRM_CFG_H
/* polyspace<MISRA-C3:1.1:Not a defect:Justify with annotations> The high number of macros is due to inclusion of microcontroller's header. */
/**
 * \file       BtrM.h
 * \author     wujie
 * \brief      Header file for the config parameter of Battery Manager module.
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
 $Revision: 363 $
 $Date: 2023-12-19 14:49:58 +0800 (周二, 19 12月 2023) $
 $Author: xieshangfeng $
 -------------------------------------------------------------------------------
                R E V I S I O N   H I S T O R Y
 -------------------------------------------------------------------------------


------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                           Includes                                         */
/*----------------------------------------------------------------------------*/
#include "STD_TypesDef.h"

/*----------------------------------------------------------------------------*/
/*                         Defines and macros                                 */
/*----------------------------------------------------------------------------*/
/**
* @addtogroup macros_enum
* @{
*/
/** \brief Super fast filter configuration */
#define BTRM_SUPER_FAST_FILTER     (STD_OFF)
/** \brief Fast Power mode filter times*/
#define BTRM_FAST_FILTER_TIME      3U
/** \brief Nornal Power mode change filter times*/
#define BTRM_SLOW_FILTER_TIME      (uint8)120U

/** \brief power sample channel*/
#define BTRM_SAMPLING_CHANNEL    (uint8)0U

/*For STD_BtrM*/
/*\brief Power Mode A*/
#define STD_BTRM_MODE_A (0U)
/*\brief Power Mode B*/
#define STD_BTRM_MODE_B (1U)
/*\brief Power Mode C*/
#define STD_BTRM_MODE_C (2U)

/** \brief hysteresis voltage of transmit A to B mode in high area */
#define BTRM_A_TO_B_MODE_UPPER 2579U    //-------16.5V
/** \brief hysteresis voltage of transmit A to B mode in low area*/
#define BTRM_A_TO_B_MODE_LOWER 1326U    //-------8.5V
/** \brief hysteresis voltage of transmit B to A mode in high area*/
#define BTRM_B_TO_A_MODE_UPPER 2501U    //-------16V
/** \brief hysteresis voltage of transmit B to A mode in low area*/
#define BTRM_B_TO_A_MODE_LOWER 1380U    //-------9V

/** \brief Support Power C Mode */
#define BTRM_SUPPORT_C_MODE STD_ON
#if (BTRM_SUPPORT_C_MODE == STD_ON)
/** \brief hysteresis voltage of transmit C to B mode in high area*/
#define BTRM_C_TO_B_MODE_UPPER 2814U    //-------18V
/** \brief hysteresis voltage of transmit C to B mode in low area*/
#define BTRM_C_TO_B_MODE_LOWER 1013U     //-------6.5V
/** \brief hysteresis voltage of transmit B to C mode in high area*/
#define BTRM_B_TO_C_MODE_UPPER 2885U    //-------18.5V
/** \brief hysteresis voltage of transmit B to C mode in low area*/
#define BTRM_B_TO_C_MODE_LOWER 935U     //-------6V 
#endif

#define BTRM_INITMODE       STD_BTRM_MODE_B

#define BTRM_LOW_VOL_DETECT                    STD_OFF
#if ( (defined RDPT_EEPM) || (BTRM_LOW_VOL_DETECT == STD_ON) )
#define BTRM_LOAD_THRESHOLD_LOW_BATTERY_IN     914
#define BTRM_LOAD_THRESHOLD_LOW_BATTERY_OUT    964
#endif

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

#endif
/*EOF*/



