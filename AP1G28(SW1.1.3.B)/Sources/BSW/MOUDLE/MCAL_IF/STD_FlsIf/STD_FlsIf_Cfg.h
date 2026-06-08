/*******************************************************************************
|  File Name:  FlsIf_Cfg.h
|  Description:  Implementation of the Flash Config Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           XiaYaJun          CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 2018-05-23    01.00.00     XYJ       Creation
|******************************************************************************/

/*******************************************************************************
|	 Other Header File Inclusion
|******************************************************************************/
#ifndef _MCAL_FLSIF_CFG_H_
#define _MCAL_FLSIF_CFG_H_

#include "SysTypes.h"
//#include "flash_driver.h"
#include "fee_config.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define FLSIF_CODE_RAM  // __attribute__ ((section(".BSW_RAM_DATA")))
/*******************************************************************************
|    Enum Definition
|******************************************************************************/
typedef enum
{
    /* Generic error codes */
    FLSIF_SUCCESS	= 0x000U,    /*!< Generic operation success status */
	FLSIF_ERROR     = 0x001U,    /*!< Generic operation failure status */
	FLSIF_BUSY      = 0x002U,    /*!< Generic operation busy status */
	FLSIF_TIMEOUT   = 0x003U,    /*!< Generic operation timeout status */
	FLSIF_UNSUPPORTED = 0x004U,    /*!< Generic operation unsupported status */
}FlsIf_JobResultType;
/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|	 Global Variable with extern linkage
|******************************************************************************/

/*******************************************************************************
|	 Global Function Prototypes
|******************************************************************************/


#endif /* _MCAL_FLSIF_CFG_H_ */
