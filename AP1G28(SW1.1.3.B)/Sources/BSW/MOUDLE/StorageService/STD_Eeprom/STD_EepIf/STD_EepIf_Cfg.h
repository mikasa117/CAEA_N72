/*******************************************************************************
|  File Name:  STD_EepIfCfg.c
|  Description:  Implementation of the Eeprom Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           xiayajun               CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2018-07-23    01.00.00     XYJ       Creation
|
|******************************************************************************/

#if !defined (_STD_EEPIF_CFG_H)
#define _STD_EEPIF_CFG_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "SysTypes.h"
#include "Fee.h"
/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define EEPIF_DISABLE	(0u)
#define EEPIF_ENABLE	(1u)

#define EEPIF_MODULE_EN			EEPIF_ENABLE

#if (EEPIF_MODULE_EN == EEPIF_ENABLE)

#define EEPIF_NUM_OF_DEVICES		(1u)

/*eeprom storage type Enable*/
#define EEPIF_TYPE_DFLASH_ENABLE				EEPIF_DISABLE
#define EEPIF_TYPE_EXT_EEP_ENABLE				EEPIF_DISABLE
#define EEPIF_TYPE_FLEXMEM_ENABLE				EEPIF_ENABLE
/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef void (*pEepIf_InitType)(void);
typedef void (*pEepIf_InitDrvType)(const Fee_ModuleUserConfig_t * ConfigPtr);
typedef void (*pEepIf_MainType)(void);
typedef void (*pEepIf_ReadAllType)(void);
typedef uint8 (*pEepIf_WriteBankType)(uint16 BankID, const uint8 *BankData);
typedef uint8 (*pEepIf_GetIdleStatusType)(void);

typedef struct
{
    pEepIf_InitType				MidInitMemory;
    pEepIf_MainType				MidMainFunction;
    pEepIf_ReadAllType			MidReadAll;
    pEepIf_WriteBankType 		MidWriteBank;
	pEepIf_GetIdleStatusType	MidGetIdleStatus;

	pEepIf_InitDrvType				DrvInit;
	/*pEepIf_InitType				DrvInitMemory;*/
	pEepIf_MainType				DrvMainFunction;
}EepIf_ApiType;


/*******************************************************************************
|    Global Variable with extern linkage
|******************************************************************************/

extern const EepIf_ApiType EepIf_ApiFun[EEPIF_NUM_OF_DEVICES];

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/

#endif/*(EEPIF_MODULE_EN == EEPIF_ENABLE)*/
#endif
