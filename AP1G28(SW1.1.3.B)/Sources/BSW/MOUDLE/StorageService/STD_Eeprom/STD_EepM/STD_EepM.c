/* polyspace<MISRA-C3:1.1:Not a defect:Justified> Normal. */
/*******************************************************************************
|  File Name:  STD_EepM.c
|  Description:  Implementation of the EepM Management
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
| 2018-07-23    01.00.00     XYJ       Creation
| 2019-03-01	01.00.01	 CXL	   EEPM_ClearAllFunction write default data
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_EepM.h"
#include "STD_EepIf_Cfg.h"
#include "STD_WdgM.h"
#include "fee_config.h"
#include "STD_Lib.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#if (EEP_MODULE_EN == EEP_ENABLE)
/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef struct
{
	boolean bReadAllOkStatus;
	boolean bSleepReqStatus;
	uint16 usCurrWriteBankId;
	uint16 usWriteTimeOutCnt;
} StructEepMType;
/*******************************************************************************
|    Global NVM KAM Declaration
|******************************************************************************/
static Eep_WriteResultType EEPM_CODE_KAM ucEepWriteBankFlagArray[EEP_BANK_MAX_NUM];	/*bank data updata flag*/
/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/
static StructEepMType EEPM_CODE_RAM stEepM;
/*******************************************************************************
|    Table Definition
|******************************************************************************/

/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/
static void EEPM_UpdataKamFromStorage(void);
static uint8 EEPM_KamCalibration(void);
static void EEPM_ClearAllFunction(void);
static void EEPM_UpdataBankKam( uint16 BankId);
static void EEPM_PrepareWrite( void );
static void EEPM_SetBankWriteFlag(uint16 BankId,Eep_WriteResultType WriteStatus);
static void EEPM_SleepStatustDetect(void);
/*******************************************************************************
|    Function Source Code
|******************************************************************************/

/*code*/

/*******************************************************************************
Name			: EepM_Init
Syntax			: void EepM_Init(void)
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None						:-
Parameters(out) : None						:-
Return value	: None						:-
Description		: NVM \ FEE \ FLS \ APP  initialize
Call By			: -
|******************************************************************************/
void EEPM_Init(void)
{
#if (EEPIF_TYPE_DFLASH_ENABLE == EEPIF_ENABLE)
    Fls_Init( &Fls_ConfigSetPC );
    Fee_Init();
    NvM_Init();
    Fee_EnableFss();
#else
    MemIf_StatusType LeEepM_u_FeeStatus = MEMIF_UNINIT;
    EepIf_ApiFun[0u].DrvInit(&FEEGenConfig);/*PRQA S 3671*/
    do
    {
    	EepIf_ApiFun[0u].DrvMainFunction();
    	LeEepM_u_FeeStatus = Fee_GetStatus();
    }while(MEMIF_IDLE != LeEepM_u_FeeStatus);
#endif
}

/*******************************************************************************
Name			: EepM_InitMemory
Syntax			: void EepM_InitMemory( void )
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None						:-
Parameters(out) : None						:-
Return value	: None						:-
Description		: NVM flag initialize
Call By			: -
|******************************************************************************/
void EEPM_InitMemory( void )
{
	EepIf_ApiFun[0u].MidInitMemory();/*PRQA S 3671*/
	/*EepIf_ApiFun[0u].DrvInitMemory();*//*PRQA S 3671*/
	EEPCFG_InitRamMemory();
	LIB_SetMemory( (uint8 *)(&stEepM), 0u, (uint16)(sizeof(stEepM) / sizeof(uint8)));/*PRQA S 0310*/
}
/*******************************************************************************
Name			: EepM_InitKamMemory
Syntax			: void EepM_InitKamMemory( void )
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None						:-
Parameters(out) : None						:-
Return value	: None						:-
Description		: Initialize KAM Data
Call By			: EcuM
|******************************************************************************/
void EEPM_InitKamMemory( void )
{
	EEPCFG_InitKamMemory();
	LIB_SetMemory( (uint8 *)(&ucEepWriteBankFlagArray), 0u, (uint16)(sizeof(ucEepWriteBankFlagArray) / sizeof(uint8)));/*PRQA S 0310*/
}

void EEPM_MainFunction( void )
{
	if((uint8)FALSE == EEPM_GetSysLowVoltageStatus())
	{
		EEPM_PrepareWrite();
#if (EEP_TYPE_DFLASH_ENABLE == EEPIF_ENABLE)
		NvM_MainFunction();
		Fee_MainFunction();
		Fls_MainFunction();
#else
		EepIf_ApiFun[0u].MidMainFunction();/*PRQA S 3671*/
		EepIf_ApiFun[0u].DrvMainFunction();/*PRQA S 3671*/
#endif
	}
	else
	{
	}
	EEPM_SleepStatustDetect();
}

void EEPM_SetUp( uint8 fblUpdataFlag,uint8 kamValidStatus)
{
	uint16 loopCount = 0u;
	uint8  TempReStatus = E_OK;
	uint8  TempKamStatus = kamValidStatus;

	if(((uint8)TRUE != fblUpdataFlag)&&((uint8)TRUE == TempKamStatus))
	{
		TempReStatus = EEPM_KamCalibration();
		if((uint8)E_NOT_OK == TempReStatus)
		{
			TempKamStatus = FALSE;
		}
	}

	if(((uint8)TRUE == fblUpdataFlag)||((uint8)TRUE != TempKamStatus))
	{
		loopCount = 0u;
		stEepM.bReadAllOkStatus = FALSE;
		EepIf_ApiFun[0u].MidReadAll();/*PRQA S 3671*/
		while( ( ( uint8 )TRUE != stEepM.bReadAllOkStatus ) && (loopCount < (uint16)EEP_READALL_LOOP_MAX_CNT))
		{
		#if(WDGM_EN_CLASS == WDGM_ENABLE)
			WDGM_Trigger();
		#endif
#if (EEP_TYPE_DFLASH_ENABLE == EEPIF_ENABLE)
			NvM_MainFunction();
			Fee_MainFunction();
			Fls_MainFunction();
#else
			EepIf_ApiFun[0u].MidMainFunction();/*PRQA S 3671*/
			EepIf_ApiFun[0u].DrvMainFunction();/*PRQA S 3671*/
#endif
			loopCount++;
		}

		if((uint8)TRUE == fblUpdataFlag)
		{
		#if(WDGM_EN_CLASS == WDGM_ENABLE)
			WDGM_Trigger();
		#endif
			EEPM_ClearAllFunction();
		}
		else
		{
			;
		}
		EEPM_UpdataKamFromStorage();
	}
	else
	{
	}
}

static void EEPM_PrepareWrite( void )
{
	uint16 TempBankId;

	if((uint8)TRUE == EepIf_ApiFun[0u].MidGetIdleStatus())/*PRQA S 3671*/
	{
		if(EEP_WRITE_PENDING == ucEepWriteBankFlagArray[stEepM.usCurrWriteBankId])
		{
			EEPM_SetBankWriteFlag(stEepM.usCurrWriteBankId, EEP_WRITE_OK);
		}
		else
		{}
		for(TempBankId = 0u; TempBankId < (uint16)EEP_BANK_MAX_NUM; TempBankId++ )
        {
			if(EEP_WRITE_REQ == ucEepWriteBankFlagArray[TempBankId])
			{
				LIB_Copy(stEepBankCfg[TempBankId].ucRamAdd,stEepBankCfg[TempBankId].ucKam1Add, stEepBankCfg[TempBankId].usLength);

				if((uint8)E_OK == EepIf_ApiFun[0u].MidWriteBank(TempBankId,stEepBankCfg[TempBankId].ucRamAdd))/*PRQA S 3671*/
				{
					EEPM_SetBankWriteFlag(TempBankId, EEP_WRITE_PENDING);
					stEepM.usWriteTimeOutCnt = EEP_WRITE_TIMEOUT_MAX_TIMER;
					stEepM.bSleepReqStatus = FALSE;
				}
				else
				{
				}
				stEepM.usCurrWriteBankId = TempBankId;
				break;

			}
			else
			{}
		}
	}
}

static void EEPM_SleepStatustDetect(void)
{
    uint8 TempBankId;
    uint8 LeEEPM_u_BlockBusy = FALSE;/*0901: add write req flag*/
    for(TempBankId = 0u; TempBankId < (uint16)EEP_BANK_MAX_NUM; TempBankId++ )
    {
        if((EEP_WRITE_REQ == ucEepWriteBankFlagArray[TempBankId])
            || (EEP_WRITE_PENDING == ucEepWriteBankFlagArray[TempBankId]))
	    {
            LeEEPM_u_BlockBusy = TRUE;
            break;
        }
	}
	if(((uint8)TRUE == EepIf_ApiFun[0u].MidGetIdleStatus())&&(LeEEPM_u_BlockBusy == FALSE))/*PRQA S 3671*/
	{
		stEepM.bSleepReqStatus = TRUE;
	}
	else
	{
		/*if(FALSE == PwrM_GetIgnPowerModeStatus())*/
		{
			if(stEepM.usWriteTimeOutCnt > (uint16)0u)
			{
				stEepM.usWriteTimeOutCnt--;
				if(stEepM.usWriteTimeOutCnt == (uint16)EEP_WRITE_CLEAR_MIN_TIMER)
				{
					stEepM.bSleepReqStatus = FALSE;
					EEPM_SetBankWriteFlag(stEepM.usCurrWriteBankId, EEP_WRITE_FAILED);

				}
				else
				{
				}
			}
			else
			{
				stEepM.bSleepReqStatus = TRUE;
			}
		}
	}
}

static void EEPM_SetBankWriteFlag(uint16 BankId,Eep_WriteResultType WriteStatus)
{
	switch( WriteStatus )
	{
		case EEP_WRITE_NONE:
		ucEepWriteBankFlagArray[BankId] = EEP_WRITE_NONE;
		break;

		case EEP_WRITE_OK:
		if(EEP_WRITE_REQ != ucEepWriteBankFlagArray[BankId])
		{
			ucEepWriteBankFlagArray[BankId] = EEP_WRITE_OK;
		}
		break;

		case EEP_WRITE_FAILED:
		if(EEP_WRITE_REQ != ucEepWriteBankFlagArray[BankId])
		{
			ucEepWriteBankFlagArray[BankId] = EEP_WRITE_FAILED;
		}
		break;

		case EEP_WRITE_PENDING:
		ucEepWriteBankFlagArray[BankId] = EEP_WRITE_PENDING;
		break;

		case EEP_WRITE_REQ:
		ucEepWriteBankFlagArray[BankId] = EEP_WRITE_REQ;
		break;

		default:
		ucEepWriteBankFlagArray[BankId] = EEP_WRITE_NONE;
		break;
	}
}

/*******************************************************************************
Name			: EepM_UpdataKamFromStorage
Syntax			: static void EepM_UpdataKamFromStorage(void)
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: -							:-
Parameters(out) : None						:-
Return value	: None
Description		: Updata Kam A\B\C From Eeprom
Call By			: -
|******************************************************************************/
static void EEPM_UpdataKamFromStorage(void)
{
	uint16 TempBankId;
	uint8 *pAddress1 = NULL;
#if (EEP_KAM_BACKUP_CLASS == EEP_ENABLE)
	uint8 *pAddress2 = NULL;
	uint8 *pAddress3 = NULL;
#endif

	for(TempBankId = 0u; TempBankId< (uint16)EEP_BANK_MAX_NUM; TempBankId++ )
	{
		pAddress1 = stEepBankCfg[TempBankId].ucKam1Add;
		if((stEepBankCfg[TempBankId].ucRamAdd[0] == (uint8)EEP_BANK_RAM_FLAG)||(stEepBankCfg[TempBankId].ucRamAdd[0] == (uint8)EEP_BANK_ROM_DEFAULT_FLAG))/*PRQA S 0491*/
		{
			LIB_Copy(pAddress1,stEepBankCfg[TempBankId].ucRamAdd, stEepBankCfg[TempBankId].usLength);
	#if (EEP_KAM_BACKUP_CLASS == EEP_ENABLE)
			if((stEepBankCfg[TempBankId].ucFlag & (uint8)EEP_BANK_KAM_BACKUP_ON) == (uint8)EEP_BANK_KAM_BACKUP_ON)
			{
				pAddress2 = stEepBankCfg[TempBankId].ucKam2Add;
				pAddress3 = stEepBankCfg[TempBankId].ucKam3Add;
				LIB_Copy(pAddress2,pAddress1, stEepBankCfg[TempBankId].usLength);
				LIB_Copy(pAddress3,pAddress1, stEepBankCfg[TempBankId].usLength);
			}
	#endif
		}
	}
}

/*******************************************************************************
Name			: EepM_KamCalibration
Syntax			: uint8 EepM_KamCalibration(void)
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: -							:-
Parameters(out) : None						:-
Return value	: None
Description		: Kam A\B\C calibration
Call By			: -
|******************************************************************************/
static uint8 EEPM_KamCalibration(void)
{
	uint8  RetStatus = E_OK;
#if (EEP_KAM_BACKUP_CLASS == EEP_ENABLE)
	uint8  bKam12EqualStatus = TRUE;
	uint8  bKam13EqualStatus = TRUE;
	uint8  bKam23EqualStatus = TRUE;
	uint8* pAddress1 = NULL;
	uint8* pAddress2 = NULL;
	uint8* pAddress3 = NULL;
	uint16 TempBankId = 0u;

	for(TempBankId = 0u; TempBankId< (uint16)EEP_BANK_MAX_NUM; TempBankId++ )
	{
		if((stEepBankCfg[TempBankId].ucFlag & (uint8)EEP_BANK_KAM_BACKUP_ON) == (uint8)EEP_BANK_KAM_BACKUP_ON)
		{
			pAddress1 = stEepBankCfg[TempBankId].ucKam1Add;
			pAddress2 = stEepBankCfg[TempBankId].ucKam2Add;
			pAddress3 = stEepBankCfg[TempBankId].ucKam3Add;

			bKam12EqualStatus = LIB_Compare(pAddress1,pAddress2,stEepBankCfg[TempBankId].usLength);
			bKam13EqualStatus = LIB_Compare(pAddress1,pAddress3,stEepBankCfg[TempBankId].usLength);
			bKam23EqualStatus = LIB_Compare(pAddress2,pAddress3,stEepBankCfg[TempBankId].usLength);

			if(((uint8)TRUE == bKam12EqualStatus) && ((uint8)FALSE == bKam23EqualStatus))
			{
				LIB_Copy(pAddress3,pAddress1, stEepBankCfg[TempBankId].usLength);
			}
			else if(((uint8)TRUE == bKam13EqualStatus) && ((uint8)FALSE == bKam23EqualStatus))
			{
				LIB_Copy(pAddress2,pAddress1, stEepBankCfg[TempBankId].usLength);
			}
			else if(((uint8)FALSE == bKam12EqualStatus) && ((uint8)TRUE == bKam23EqualStatus))
			{
				LIB_Copy(pAddress1,pAddress2, stEepBankCfg[TempBankId].usLength);
			}
			else if(((uint8)FALSE == bKam12EqualStatus) && ((uint8)FALSE == bKam23EqualStatus) && ((uint8)FALSE == bKam13EqualStatus))
			{
				pAddress1[0] = 0x00u;/*PRQA S 0491*/
				pAddress2[0] = 0x00u;/*PRQA S 0491*/
				pAddress3[0] = 0x00u;/*PRQA S 0491*/
				RetStatus = E_NOT_OK;
			}
			else
			{
			}
		}
		else
		{
		}
	}
#endif
	return RetStatus;
}

static void EEPM_ClearAllFunction(void)
{
	uint32 loopCount = 0U;
	uint16 TempBankId;
	uint8  bWriteReqFlag = FALSE;
	uint16 i;

	for(TempBankId = 0u; TempBankId< (uint16)EEP_BANK_MAX_NUM; TempBankId++ )
	{
		if( (stEepBankCfg[TempBankId].ucFlag & (uint8)EEP_BANK_CLEAR_ON) == (uint8)EEP_BANK_CLEAR_ON)
		{
			if(EEP_BANK_RAM_FLAG != stEepBankCfg[TempBankId].ucRamAdd[0u])/*PRQA S 0491*/
			{
				stEepBankCfg[TempBankId].ucRamAdd[0u] = EEP_BANK_RAM_FLAG;/*PRQA S 0491*/
				LIB_Copy(&(stEepBankCfg[TempBankId].ucRamAdd[1u]),&(stEepBankCfg[TempBankId].ucRomDataAddr[1u]), (stEepBankCfg[TempBankId].usLength-1u));
				bWriteReqFlag = TRUE;
			}
			else
			{
				for(i = 1u;i< (stEepBankCfg[TempBankId].usLength - 1u); i++)
				{
					if(stEepBankCfg[TempBankId].ucRomDataAddr[i] != stEepBankCfg[TempBankId].ucRamAdd[i])
					{
						stEepBankCfg[TempBankId].ucRamAdd[i] = stEepBankCfg[TempBankId].ucRomDataAddr[i];
						bWriteReqFlag = TRUE;
					}
					else
					{}
				}
			}
/* polyspace<MISRA-C3:13.5:Not a defect:Justified> Normal. */
			if(((uint8)TRUE == bWriteReqFlag)&&( (uint8)TRUE == EepIf_ApiFun[0u].MidGetIdleStatus() ))
			{
				if((uint8)E_OK == EepIf_ApiFun[0u].MidWriteBank(TempBankId,stEepBankCfg[TempBankId].ucRamAdd))
				{
					loopCount = 0u;
					do
					{
				#if(WDGM_EN_CLASS == WDGM_ENABLE)
						WDGM_Trigger();
				#endif
#if (EEP_TYPE_DFLASH_ENABLE == EEPIF_ENABLE)
						NvM_MainFunction();
						Fee_MainFunction();
						Fls_MainFunction();
#else
						EepIf_ApiFun[0u].MidMainFunction();
						EepIf_ApiFun[0u].DrvMainFunction();
#endif
						loopCount++;
					}
					while(((uint8)TRUE != EepIf_ApiFun[0u].MidGetIdleStatus())&&(loopCount < 100000u));
				}
				else
				{}
				bWriteReqFlag = FALSE;
			}
		}
		else{}
	}
}
/*******************************************************************************
Name			: EepM_AppReadBlock
Syntax			: void EepM_AppReadBlock( NvmDataIDType NvmDataID, NvmDataType NvmData[] )
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: NvmDataID					:Read Data ID
Parameters(in)	: NvmData					:the address of read data
Parameters(out) : None						:-
Return value	: Std_ReturnType			:E_OK		the read data is valid
											:E_NOT_OK	the read data is invalid
Description		: Dem read Nvm data
Call By			: -
|******************************************************************************/
uint8 EEPM_AppReadBlock( uint16 BlockID, uint8 ReadData[] )
{
	const uint16 	TempBlockId = BlockID;
	uint16 			TempBankId = 0u;
	uint8*			pAddress1 = NULL;
	uint8 			ReVal = FALSE;


	if( TempBlockId < (uint16)EEP_BLOCK_MAX_NUM )
	{
		TempBankId = stEepBlockCfg[TempBlockId].ucBankId;
		pAddress1 = stEepBankCfg[TempBankId].ucKam1Add;
		if((pAddress1[0] == (uint8)EEP_BANK_RAM_FLAG) || (pAddress1[0] == (uint8)EEP_BANK_ROM_DEFAULT_FLAG))/*PRQA S 0491*/
		{
		    /* polyspace<MISRA-C3:18.4:Not a defect:Justified> Normal. */
			pAddress1 = stEepBankCfg[TempBankId].ucKam1Add + stEepBlockCfg[TempBlockId].usAddOffset;/*PRQA S 0488*/
			LIB_Copy(ReadData,pAddress1, stEepBlockCfg[TempBlockId].usLength);
			ReVal = TRUE;
		}
	}
	else
	{
	}

	return ReVal;
}
/*******************************************************************************
Name			: EepM_AppWriteBlock
Syntax			: void EepM_AppWriteBlock( NvmDataIDType NvmDataID, const NvmDataType *NvmData )
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: NvmDataID					:the write data ID
Parameters(in)	: NvmData					:the address of write data
Parameters(out) : None						:-
Return value	: Std_ReturnType			    :E_OK		Nvm accept store order
											 E_NOT_OK	Nvm didnot accept store order
Description		: Dem store Nvm data
Call By			: -
|******************************************************************************/
void EEPM_AppWriteBlock( uint16 BlockID, const uint8 WriteData[] )
{
	uint16 			TempIdx;
	const uint16 	TempBlockId = BlockID;
	uint8 			TempWriteReqFlag = FALSE;

	uint8 			TempBankId = 0u;
	uint8*			pAddress1 = NULL;

	if( TempBlockId < (uint16)EEP_BLOCK_MAX_NUM )
	{
		TempBankId = stEepBlockCfg[TempBlockId].ucBankId;
		pAddress1 = stEepBankCfg[TempBankId].ucKam1Add;

		if(EEP_BANK_RAM_FLAG != pAddress1[0u])/*PRQA S 0491*/
		{
		    /* polyspace<MISRA-C3:18.4:Not a defect:Justified> Normal. */
			pAddress1 = stEepBankCfg[TempBankId].ucKam1Add + stEepBlockCfg[TempBlockId].usAddOffset;/*PRQA S 0488*/
			LIB_Copy(pAddress1,WriteData, stEepBlockCfg[TempBlockId].usLength);
			TempWriteReqFlag = TRUE;
		}
		else
		{
		    /* polyspace<MISRA-C3:18.4:Not a defect:Justified> Normal. */
			pAddress1 = stEepBankCfg[TempBankId].ucKam1Add + stEepBlockCfg[TempBlockId].usAddOffset;/*PRQA S 0488*/
			for( TempIdx = 0u; TempIdx < ( stEepBlockCfg[TempBlockId].usLength ); TempIdx++ )
			{
				/* polyspace<DEFECT:OUT_BOUND_PTR:Not a defect:Justified> Normal. */
				if(pAddress1[TempIdx] !=  WriteData[TempIdx])/*PRQA S 0491*/
				{
					pAddress1[TempIdx] =  WriteData[TempIdx];/*PRQA S 0491*/
					TempWriteReqFlag = TRUE;
				}
				else
				{
				}
			}
		}

		if((uint8)TRUE == TempWriteReqFlag)
		{
			EEPM_UpdataBankKam((uint16)TempBankId);
			EEPM_SetBankWriteFlag((uint16)TempBankId, EEP_WRITE_REQ);
		}
		else
		{
			/*Request Same data with Kam set OK Flag*/
			/*EEPM_SetBankWriteFlag((uint16)TempBankId, EEP_WRITE_OK);*/
		}
	}
	else
	{
	}
}

static void EEPM_UpdataBankKam( uint16 BankId)
{
	const uint16 	TempBankId = BankId;
	uint8*			pAddress1 = NULL;
#if (EEP_KAM_BACKUP_CLASS == EEP_ENABLE)
	uint8*			pAddress2 = NULL;
	uint8*			pAddress3 = NULL;
#endif
	if( TempBankId <= (uint16)EEP_BANK_MAX_NUM )
	{
		pAddress1 = stEepBankCfg[TempBankId].ucKam1Add;
		pAddress1[0] = EEP_BANK_RAM_FLAG;/*PRQA S 0491*/
#if (EEP_KAM_BACKUP_CLASS == EEP_ENABLE)
		if((stEepBankCfg[TempBankId].ucFlag & (uint8)EEP_BANK_KAM_BACKUP_ON) == (uint8)EEP_BANK_KAM_BACKUP_ON)
		{
			pAddress2 = stEepBankCfg[TempBankId].ucKam2Add;
			pAddress3 = stEepBankCfg[TempBankId].ucKam3Add;
			LIB_Copy(pAddress2,pAddress1, stEepBankCfg[TempBankId].usLength);
			LIB_Copy(pAddress3,pAddress1, stEepBankCfg[TempBankId].usLength);
		}
#endif
		/*pAddress2 = stEepBankCfg[TempBankId].ucRamAdd;
		LIB_Copy(pAddress2,pAddress1, stEepBankCfg[TempBankId].usLength);*/
	}
	else
	{
	}
}

Eep_WriteResultType EEPM_GetBlockWriteStatus(uint16 BlockkId)
{
	uint16 BankId = 0u;

	if (BlockkId < (uint16)EEP_BLOCK_MAX_NUM )
	{
		BankId = stEepBlockCfg[BlockkId].ucBankId;
	}
	else
	{
	}

	return ucEepWriteBankFlagArray[BankId];
}

uint8 EEPM_GetSleepRequestStatus( void )
{
    return stEepM.bSleepReqStatus;
}

void EEPM_MultiBlockCallbackFunction( uint8 ServiceId, uint8 JobResult )
{
    volatile const uint8 	ucJobResult = JobResult;
    const uint8 			ucServiceId = ServiceId;

    if ( ucJobResult == (uint8)0u )
    {
        ;
    }
    else
    {
        ;
    }

    if ( ucServiceId == (uint8)EEPM_SERVICE_READALL )/*NVM_READ_ALL = 12u; Service ID NvM_ReadAll() */
    {
    	stEepM.bReadAllOkStatus = TRUE;
    }
    else
    {
        ;
    }
}

#endif/*(EEP_MODULE_EN == EEP_ENABLE)*/
/*EOF*/
