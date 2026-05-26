#ifndef STD_TYPESDEF_H_
#define STD_TYPESDEF_H_
/* polyspace<MISRA-C3:1.1:Not a defect:Justify with annotations> The high number of macros is due to inclusion of microcontroller's header. */
/**
 * \file       STD_TypesDef.h
 * \author     wujie
 * \brief      Implementation file for define standard type
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
 $Revision: 238 $
 $Date: 2023-10-16 14:51:37 +0800 (周一, 16 10月 2023) $
 $Author: xieshangfeng $
 -------------------------------------------------------------------------------
                R E V I S I O N   H I S T O R Y
 -------------------------------------------------------------------------------
  Date           Version        Author       Description
 -------------------------------------------------------------------------------
 2019.9.2       01.00.00       Jerry        Creation

------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                           Includes                                         */
/*----------------------------------------------------------------------------*/
#if (1 == 0)
#include "Std_Types.h"
#else
/*----------------------------------------------------------------------------*/
/*                         Defines and macros                                 */
/*----------------------------------------------------------------------------*/
/**
* @addtogroup macros_enum
* @{
*/

/** \brief This standard return value is returned when the given command is accepted.*/
#define E_OK                              (0x00U)

/** \brief This standard return value is returned when the given command is rejected.*/
#define E_NOT_OK                          (0x01U)

/** \brief Symbol which defines an MCU electrical signal state of low voltage (usually 0V).*/
#define STD_LOW                           (0x00U)

/** \brief Symbol which defines an MCU electrical signal state of high voltage (usually 3.3V or 5V).*/
#define STD_HIGH                          (0x01U)

/** \brief Symbol which defines an MCU electrical signal state of low voltage (usually 0V).*/
#define STD_LOW                           (0x00U)

/** \brief Symbol which defines a logical state of active.*/
#define STD_ACTIVE                        (0x01U)

/** \brief Symbol which defines a logical state of idle.*/
#define STD_IDLE                          (0x00U)

/** \brief Symbol used to deactivate functionality in statically configurable modules.*/
#define STD_OFF                           (0x00U)

/** \brief Symbol used to activate functionality in statically configurable modules.*/
#define STD_ON                            (0x01U)

/** \brief Symbol used as false value of boolean type*/
#ifndef FALSE
#define FALSE (0U)
#endif

/** \brief Symbol used as true value of boolean type*/
#ifndef TRUE
#define TRUE  (1U)
#endif




#define ENALBE      STD_ON
#define DISABLE     STD_OFF

/*Data Null*/
#ifndef  NULL
#define  NULL 0
#endif
/* NULL_PTR define with a void pointer to zero definition*/
#ifndef  NULL_PTR
#define  NULL_PTR ((void*) 0)
#endif

/** \brief don't have communication */
#define NO_COMM  (0U)
/** \brief Equipe LIN communication*/
#define LIN_COMM (1U)
/** \brief Equipe CAN communication*/
#define CAN_COMM (2U)


/** \brief if the ECU have communication functionality, set it to related bus type*/
#define COMMUMNICATION_PROTOCOL NO_COMM

/** @} *//* Macros_Enum definition */

/*----------------------------------------------------------------------------*/
/*                              Data types                                    */
/*----------------------------------------------------------------------------*/
/**
* @addtogroup Typedefs
* @{
*/

typedef signed char     sint8;
typedef signed short    sint16;
typedef signed long     sint32;
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned long   uint32;

/** \brief AUTOSAR standard return type. Possible values are {E_OK, E_NOT_OK}.*/
typedef uint8                             Std_ReturnType;

/** \brief OSEK compliant status type. Possible values are {E_OK, E_NOT_OK}.*/
typedef unsigned char                     StatusType;

/** \brief This type shall be used to request the version of a BSW module using the <Module name>_GetVersionInfo() function.*/
typedef struct
{
    /** \brief Vendor ID member of AUTOSAR struct Std_VersionInfoType.*/
    uint16 vendorID;

    /** \brief Module ID member of AUTOSAR struct Std_VersionInfoType.*/
    uint16 moduleID;

    /** \brief Software major version member of AUTOSAR struct Std_VersionInfoType.*/
    uint8 sw_major_version;

    /** \brief Software minor version member of AUTOSAR struct Std_VersionInfoType.*/
    uint8 sw_minor_version;

    /** \brief Software patch version member of AUTOSAR struct Std_VersionInfoType.*/
    uint8 sw_patch_version;
} Std_VersionInfoType;

#endif
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



