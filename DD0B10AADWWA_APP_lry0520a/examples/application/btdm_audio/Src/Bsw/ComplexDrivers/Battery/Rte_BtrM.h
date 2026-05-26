#ifndef RTE_BTRM_H_
#define RTE_BTRM_H_
/**
 * \file       Rte_BtrM.h
 * \author     RDPT
 * \brief      RTE Header file for module BtrM.
 *
 * \par        Platform File
 *
 *Creation by standard tool
 * \copyright (c) 2026 CAEA, all rights reserved.
 */

/*------------------------------------------------------------------------------
 Information for the configuration management-system:
 -------------------------------------------------------------------------------
 (Will be generated automatically during Check-In into SVN)
 $Revision: 245 $
 $Date: 2023-10-16 16:17:55 +0800 (周一, 16 10月 2023) $
 $Author: xieshangfeng $
 -------------------------------------------------------------------------------
                R E V I S I O N   H I S T O R Y
 -------------------------------------------------------------------------------
  Date           Version        Author          Description
 -------------------------------------------------------------------------------
2026-01-19    01.00.00   RDPT   Creation by standard tool

------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                                  Includes                                  */
/*----------------------------------------------------------------------------*/
#include "STD_TypesDef.h"
#include "adc_if.h"
/*----------------------------------------------------------------------------*/
/*                             Defines and macros                             */
/*----------------------------------------------------------------------------*/
/**
* @addtogroup macros_enum
* @{
*/
/* Write VoltageMode To RTE */
#define Rte_Write_BtrM_BtrM_VoltageMode(data)                      ((Rte_BtrM_VoltageMode = (data)),((Std_ReturnType)E_OK))
/* Read VoltageMode From RTE */
#define Rte_Read_BtrM_BtrM_VoltageMode(data)                      ((*(data) = Rte_BtrM_VoltageMode),((Std_ReturnType)E_OK))
/* Read AdcConvRes From RTE */
#define Rte_Read_BtrM_EcuIfAdc_AdcConvRes(instance,data)                      ((*(data) = adc_if_get_validValue(adc_cl_bat)),((Std_ReturnType)E_OK))


/** @} *//* Macros_Enum definition */

/*----------------------------------------------------------------------------*/
/*                                 Data types                                 */
/*----------------------------------------------------------------------------*/
/* \brief BtrM_ModeType Typedef */
typedef uint8 BtrM_ModeType;

/* Declaration Rte_AdcM_AdcConvRes variable */
/* polyspace<MISRA-C3:8.6:Not a defect:Justified> not affect ,Rte Standardization module */
//extern AdcM_EcuIfAdcConvResType Rte_AdcM_AdcConvRes;

/*----------------------------------------------------------------------------*/
/*                External declaration of global RAM-Variables                */
/*----------------------------------------------------------------------------*/
/* Declaration Rte_BtrM_VoltageMode variable */
/* polyspace<MISRA-C3:8.6:Not a defect:Justified> not affect ,Rte Standardization module */
extern BtrM_ModeType Rte_BtrM_VoltageMode;

/*----------------------------------------------------------------------------*/
/*                External declaration of global ROM-Variables                */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*                  External declaration of global functions                  */
/*----------------------------------------------------------------------------*/

/**
* @ingroup interface_functions
* @{
*/


extern void BtrM_MainFunction(void);
/** @} */ /* interface_functions */

#endif /* RTE_BTRM_H_ */
/*EOF*/



