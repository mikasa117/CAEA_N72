/*******************************************************************************
|  File Name:  STD_EvMCfg.h
|  Description:  Implementation of the EvM Config Management
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
|
|******************************************************************************/

#if !defined (_STD_EVMCFG_H)
#define _STD_EVMCFG_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Std_Types.h"
#include "fee_config.h"
#include "fee.h"
#include "STD_Lib.h"
//#include "STD_Crc.h"
#include "STD_EepM.h"
#include "STD_FlsIf.h"
/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/

#define EVM_DISABLE                          (0u)
#define EVM_ENABLE                           (1u)

#define EVM_MODULE_EN			EVM_ENABLE

#if (EVM_MODULE_EN == EVM_ENABLE)

#define EVM_CODE_RAM	//__attribute__ ((section(".BSW_RAM_DATA")))
/*config Block backup function*/
#define	EVM_BANK_BACKUP_CLASS		EVM_ENABLE

/*EEPROm NvM total ID num*/
#define	EVM_BANK_ID_MAX_NUM		    (8u)

/*the corresponding Block length of EEPROM ID*/
/*the corresponding Bank length*/
#define EVM_BANK0_DATA_LEN						(94u)
#define EVM_BANK1_DATA_LEN						(94u)
#define EVM_BANK2_DATA_LEN						(94u)
#define EVM_BANK3_DATA_LEN						(94u)
#define EVM_BANK4_DATA_LEN						(94u)
#define EVM_BANK5_DATA_LEN						(94u)
#define EVM_BANK6_DATA_LEN						(94u)
#define EVM_BANK7_DATA_LEN						(94u)




#define EVM_BANK0_START_ADD						(0u)
#define EVM_BANK1_START_ADD						(EVM_BANK0_DATA_LEN+2u)
#define EVM_BANK2_START_ADD						(EVM_BANK1_START_ADD+EVM_BANK1_DATA_LEN+2u)
#define EVM_BANK3_START_ADD						(EVM_BANK2_START_ADD+EVM_BANK2_DATA_LEN+2u)
#define EVM_BANK4_START_ADD						(EVM_BANK3_START_ADD+EVM_BANK3_DATA_LEN+2u)
#define EVM_BANK5_START_ADD						(EVM_BANK4_START_ADD+EVM_BANK4_DATA_LEN+2u)
#define EVM_BANK6_START_ADD						(EVM_BANK5_START_ADD+EVM_BANK5_DATA_LEN+2u)
#define EVM_BANK7_START_ADD						(EVM_BANK6_START_ADD+EVM_BANK6_DATA_LEN+2u)
#define EVM_BACKUP_START_ADD					(EVM_BANK7_START_ADD+EVM_BANK7_DATA_LEN+2u)

#define	EVM_BANK_MAX_LEN			(94u + 2u)
/*Eeprom NVM ID offset*/
#define	EVM_BANK_ID_OFFSET				(0x0u)

#define EVM_SERVICE_READALL			(12u)

#define	EVM_BANK_FLAG_OFF			(0x00u)
#define	EVM_BANK_BACKUP_ON			(0x01u)
#define	EVM_BANK_CLEAR_ON			(0x02u)

/*Eep Init Value*/
#define	EVMCFG_Value_0		            (0x0u)
#define	EVMCFG_Value_FF					(0xFFu)

#define	EVM_WR_MAX_TIMER				(0x3u)

#define EVM_DrvRead                Fee_Read
#define EVM_DrvWrite(x,y)                    Fee_Write(x,y)
#define EVM_DrvGetJobResult             Fee_GetJobResult
#define EVM_BACKUP_START_ID				0U

/*#define EVM_MultiCallBack(serv, res)  	EEPM_MultiBlockCallbackFunction((serv), (res))*/ /*  if Multi Block Callback is configured  */
/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
/* EvRam block descriptor type */
typedef struct
{
    uint8 *ucRamDataAddr;
    const uint8 *ucRomDataAddr;
    uint8 ucFlag;
    uint16	usBankId;
    uint16	usBankLength;
    uint32 ulStartAddress;
} EvM_BankCfgType;


/*******************************************************************************
|    Table Definition
|******************************************************************************/

/*******************************************************************************
|    Global KAM with extern linkage
|******************************************************************************/

/*******************************************************************************
|    Table Const Definition
|******************************************************************************/
extern const EvM_BankCfgType EvM_BankCfgTable[EVM_BANK_ID_MAX_NUM];

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/

#endif/*(EVM_MODULE_EN == EVM_ENABLE)*/
#endif

/*EOF*/
