/*******************************************************************************
|  File Name:  EvMCfg.c
|  Description:  Implementation of the EvMCfg Management
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
| 2016-09-30    01.00.00     XYJ       Creation
| 2019-03-01    01.00.01     CXL       Add QAC
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_EvMCfg.h"
#include "STD_EepCfg.h"
#include "STD_Crc.h"
#if (EVM_MODULE_EN == EVM_ENABLE)
/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Global NVM KAM Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Table Const Definition
|******************************************************************************/
const EvM_BankCfgType EvM_BankCfgTable[EVM_BANK_ID_MAX_NUM] =/*PRQA S 3211*/
{
    { /*0*/
        ucEepBank0RamArray /*  pointer to the RAM data buffer  */ ,
        ucEepBank0RomArray /*  pointer to the ROM buffer  */ ,
        EVM_BANK_FLAG_OFF/*block backup flag,clear flag*/,
        FEE_BLOCK_1 /*  NV block Base number (defined by FEE/EA)  */ ,
        EVM_BANK0_DATA_LEN/*  Length of the block in bytes */ ,
		EVM_BANK0_START_ADD,
    },
    { /*1*/
        ucEepBank1RamArray /*  pointer to the RAM data buffer  */ ,
        ucEepBank1RomArray /*  pointer to the ROM buffer  */ ,
        EVM_BANK_FLAG_OFF /*block backup flag,clear flag*/,
        FEE_BLOCK_2 /*  NV block Base number (defined by FEE/EA)  */ ,
        EVM_BANK1_DATA_LEN/*  Length of the block in bytes */ ,
		EVM_BANK1_START_ADD,
    },
    { /*2*/
        ucEepBank2RamArray /*  pointer to the RAM data buffer  */ ,
        ucEepBank2RomArray /*  pointer to the ROM buffer  */ ,
        EVM_BANK_FLAG_OFF/*block backup flag,clear flag*/,
        FEE_BLOCK_3 /*  NV block Base number (defined by FEE/EA)  */ ,
        EVM_BANK2_DATA_LEN /*  Length of the block in bytes*/ ,
		EVM_BANK2_START_ADD,
    },
    { /*3*/
        ucEepBank3RamArray /*  pointer to the RAM data buffer  */ ,
        ucEepBank3RomArray /*  pointer to the ROM buffer  */ ,
        EVM_BANK_FLAG_OFF/*block backup flag,clear flag*/,
        FEE_BLOCK_4 /*  NV block Base number (defined by FEE/EA)  */ ,
        EVM_BANK3_DATA_LEN/*  Length of the block in bytes  */ ,
		EVM_BANK3_START_ADD,
    },
    { /*4*/
        ucEepBank4RamArray /*  pointer to the RAM data buffer  */ ,
        ucEepBank4RomArray /*  pointer to the ROM buffer  */ ,
        EVM_BANK_FLAG_OFF /*block backup flag,clear flag*/,
        FEE_BLOCK_5 /*  NV block Base number (defined by FEE/EA)  */ ,
        EVM_BANK4_DATA_LEN /*  Length of the block in bytes  */ ,
		EVM_BANK4_START_ADD,
    },
    { /*5*/
        ucEepBank5RamArray /*  pointer to the RAM data buffer  */ ,
        ucEepBank5RomArray /*  pointer to the ROM buffer  */ ,
        EVM_BANK_FLAG_OFF /*block backup flag,clear flag*/,
        FEE_BLOCK_6 /*  NV block Base number (defined by FEE/EA)  */ ,
        EVM_BANK5_DATA_LEN /*  Length of the block in bytes */ ,
		EVM_BANK5_START_ADD,
    },
	{ /*6*/
		ucEepBank6RamArray /*  pointer to the RAM data buffer  */ ,
		ucEepBank6RomArray /*  pointer to the ROM buffer  */ ,
		EVM_BANK_FLAG_OFF /*block backup flag,clear flag*/,
		FEE_BLOCK_7 /*  NV block Base number (defined by FEE/EA)  */ ,
		EVM_BANK6_DATA_LEN /*  Length of the block in bytes */ ,
		EVM_BANK6_START_ADD,
	},
    { /*7*/
		ucEepBank7RamArray /*  pointer to the RAM data buffer  */ ,
		ucEepBank7RomArray /*  pointer to the ROM buffer  */ ,
		EVM_BANK_FLAG_OFF /*block backup flag,clear flag*/,
		FEE_BLOCK_8 /*  NV block Base number (defined by FEE/EA)  */ ,
		EVM_BANK7_DATA_LEN /*  Length of the block in bytes */ ,
		EVM_BANK7_START_ADD,
    },


};
/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/

/*******************************************************************************
|    Extern variables and functions declaration
|******************************************************************************/

/*******************************************************************************
|    Extern variables and functions declaration
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/

#endif/*(EVM_MODULE_EN == EVM_ENABLE)	*/

/*EOF*/
