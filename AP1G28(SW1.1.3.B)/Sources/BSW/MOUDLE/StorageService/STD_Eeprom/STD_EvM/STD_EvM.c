/* polyspace<MISRA-C3:1.1:Not a defect:Justified> Normal. */
/*******************************************************************************
|  File Name:  EvM.c
|  Description:  Implementation of the EvM Management
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
#include "STD_EvM.h"
#include "STD_EepM.h"
#include "STD_Lib.h"
#include "STD_Crc.h"
#if (EVM_MODULE_EN == EVM_ENABLE)
/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define EVM_MODE_IDLE						(uint8)(0x00u)
#define EVM_MODE_READALL				(uint8)(0x01u)
#define EVM_MODE_WRITE_BANK			(uint8)(0x02u)

#define EVM_CTR_IDLE								(uint8)(0x00u)
#define EVM_CTR_READ_BANK						(uint8)(0x01u)
#define EVM_CTR_WRITE_BANK					(uint8)(0x02u)
#define EVM_CTR_READ_BACKUP_BANK		(uint8)(0x03u)
#define EVM_CTR_WRITE_BACKUP_BANK		(uint8)(0x04u)
#define EVM_CTR_FINISH							(uint8)(0x05u)
/* defines for internal flags, controlled via API) */
/* polyspace<MISRA-C3:2.5:Not a defect:Justified> Normal. */
#define EVM_APIFLAG_IDLE							(uint8)(0x00u)
#define EVM_APIFLAG_WRITE_BANK_SET		(uint8)(0x01u)
#define EVM_APIFLAG_READ_ALL_SET			(uint8)(0x02u)

#define EVM_READ_STEP0					(uint8)(0x00u)
#define EVM_READ_STEP1					(uint8)(0x01u)
#define EVM_READ_STEP2					(uint8)(0x02u)

#define EVM_WRITE_STEP0					(uint8)(0x00u)
#define EVM_WRITE_STEP1					(uint8)(0x01u)
#define EVM_WRITE_STEP2					(uint8)(0x02u)
/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

typedef struct
{
    uint8 ucMode;
    uint8 ucCtrStatus;
    uint8 ucApiFlag;/* API flags - which are accessible from API */
    uint8 ucBuff[EVM_BANK_MAX_LEN];
    uint8 ucReReadCnt;
    uint8 ucReadBankStep;
    uint8 ucReWriteCnt;
    uint8 ucWriteBankStep;
    uint16 usWriteBankId;
    uint16 usReadBankId;
} StructEvMType;
/*******************************************************************************
|    Global NVM KAM Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/

static StructEvMType EVM_CODE_RAM stEvM;

/*******************************************************************************
|    Table Definition
|******************************************************************************/

/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/

/*******************************************************************************
|    Extern variables and functions declaration
|******************************************************************************/

/*******************************************************************************
|    Extern variables and functions declaration
|******************************************************************************/
static uint8 EVM_CheckBankId( uint16 BankID);
static void EVM_ModeIdleHandle( void );
static void EVM_SetIdle( void );
static void EVM_ModeReadAllHandle( void );
static void EVM_ModeWriteBankHandle( void );
static void EVM_InternalReadBank( void );
static void EVM_InternalWriteBank( void );
#if (EVM_BANK_BACKUP_CLASS == EVM_ENABLE)
static void EVM_InternalReadBackUpBank( void );
static void EVM_InternalWriteBackUpBank( void );
#endif

/*******************************************************************************
|    Function Source Code
|******************************************************************************/

/*code*/
/*******************************************************************************
Name			: EVM_CheckBankId
Syntax			: static Std_ReturnType EvM_CheckBlockId( uint16 NvmDataID)
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None						:-
Parameters(out) : None						:-
Return value	: None						:-
Description		: initialize
Call By			: -
|******************************************************************************/
static uint8 EVM_CheckBankId( uint16 BankID)
{
    uint8 	reVal = FALSE;
    uint16 	TempBankId;
    uint16 	TempBankArrayId;
/* polyspace<DEFECT:USELESS_IF:Not a defect:Justified> Normal. */
    /* polyspace<MISRA-C3:14.3:Not a defect:Justified> Normal. */
    if(BankID >= (uint16)EVM_BANK_ID_OFFSET)
    {
        if(BankID == 0u)
        {
            BankID = 1u;
        }
        else
        {}
        TempBankId = BankID  + (uint16)EVM_BANK_ID_OFFSET;
        TempBankArrayId = TempBankId;
        TempBankId <<= 4u;
        if(EvM_BankCfgTable[TempBankArrayId].usBankId == TempBankId)
        {
            reVal = TRUE;
        }
        else
        {
        }
    }
    return reVal;
}
/*******************************************************************************
Name			: EvM_Init
Syntax			: void EvM_Init(void)
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None						:-
Parameters(out) : None						:-
Return value	: None						:-
Description		: initialize
Call By			: -
|******************************************************************************/
void EVM_InitMemory(void)
{
	LIB_SetMemory( (uint8 *)(&stEvM), 0u, (uint16)(sizeof(stEvM) / sizeof(uint8)));/*PRQA S 0310*/
}

/*******************************************************************************
Name			: EvM_GetIdleStatus
Syntax			: Std_ReturnType EvM_GetIdleStatus(void)
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(in)	: None
Parameters(out)     : None						:-
Return value	: Std_ReturnType			    :E_OK		ENvM idle
									 E_NOT_OK	ENvM busy
Description		: Starts a write block asynchronously.
Call By			: -
|******************************************************************************/
uint8 EVM_GetIdleStatus(void)
{
    uint8 reVal = FALSE;
    if((EVM_MODE_IDLE == stEvM.ucMode) && (EVM_CTR_IDLE == stEvM.ucCtrStatus))
    {
        reVal = TRUE;
    }
    return reVal;
}
/*******************************************************************************
Name			: EvM_ReadAll
Syntax			: void EvM_ReadAll(void)
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: NvmDataID					:Read Data ID
Parameters(in)	: NvmData					:the address of read data
Parameters(out) : None						:-
Return value	: None
Description		: app read all block eeprom data
Call By			: -
|******************************************************************************/
void EVM_ReadAll(void)
{
    stEvM.ucApiFlag |= (uint8)EVM_APIFLAG_READ_ALL_SET;
    stEvM.usReadBankId = 0u;
}

/*******************************************************************************
Name			: EvM_WriteBlock
Syntax			: Std_ReturnType EvM_WriteBlock( uint16 NvmDataID, uint8 *NvmData )
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: NvmDataID					:the write data ID
Parameters(in)	: NvmData					:the address of write data
Parameters(out) : None						:-
Return value	: Std_ReturnType			    :E_OK		Nvm accept store order
											 E_NOT_OK	Nvm didnot accept store order
Description		: Starts a write block asynchronously.
Call By			: -
|******************************************************************************/
uint8 EVM_WriteBank( uint16 BankID, const uint8 *BankData )
{
    uint8 	reVal = E_NOT_OK;
    uint16 	crcValue;
    uint16 	ucLen;

    if((EVM_MODE_IDLE == stEvM.ucMode) && (EVM_CTR_IDLE == stEvM.ucCtrStatus))
    {
        if((uint8)TRUE == EVM_CheckBankId(BankID))
        {
        	stEvM.ucApiFlag |= EVM_APIFLAG_WRITE_BANK_SET;
            stEvM.usWriteBankId = BankID - (uint16)EVM_BANK_ID_OFFSET;
            ucLen = (uint16)EvM_BankCfgTable[stEvM.usWriteBankId].usBankLength;
            crcValue = CRC_CalculateCRC16(BankData, (uint32)ucLen, 0u, TRUE);
           /* polyspace<MISRA-C3:11.8:Not a defect:Justified> Normal. */
            LIB_Copy(stEvM.ucBuff, (uint8 *)BankData, ucLen);/*PRQA S 0311*/
            stEvM.ucBuff[ucLen] = ((uint8)(crcValue >> 8u));
            /* polyspace<DEFECT:UINT_CONV_OVFL:Not a defect:Justified> Normal. */
            stEvM.ucBuff[ucLen + (uint16)1u] = ((uint8)(crcValue));
            reVal = E_OK;
        }
    }
    else
    {}
    return reVal;
}
/*******************************************************************************
Name			: EvM_MngIdle
Syntax			: static void EvM_MngIdle( void )
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(in)	: None
Parameters(out) : None						:-
Return value	: None
Description		: ENvM manage the idle mode
Call By			: -
|******************************************************************************/
static void EVM_ModeIdleHandle( void )
{
    if( (stEvM.ucApiFlag & (uint8)EVM_APIFLAG_READ_ALL_SET) == (uint8)EVM_APIFLAG_READ_ALL_SET)
    {
    	stEvM.ucApiFlag  = stEvM.ucApiFlag & (uint8)(~EVM_APIFLAG_READ_ALL_SET);
        stEvM.ucMode =  (uint8)EVM_MODE_READALL;
    }
    else if( (stEvM.ucApiFlag & (uint8)EVM_APIFLAG_WRITE_BANK_SET) == (uint8)EVM_APIFLAG_WRITE_BANK_SET)
    {
    	stEvM.ucApiFlag  = stEvM.ucApiFlag & (uint8)(~EVM_APIFLAG_WRITE_BANK_SET);
        stEvM.ucMode =  (uint8)EVM_MODE_WRITE_BANK;
    }
    else
    {
        stEvM.ucMode =  (uint8)EVM_MODE_IDLE;
        stEvM.ucCtrStatus =  (uint8)EVM_CTR_IDLE;
    }
}

/*******************************************************************************
Name			: EvM_SetIdle
Syntax			: static void EvM_SetIdle( void )
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(in)	: None
Parameters(out) : None						:-
Return value	: None
Description		: ENvM manage the idle mode
Call By			: -
|******************************************************************************/
static void EVM_SetIdle( void )
{
    stEvM.ucMode = EVM_MODE_IDLE;
    stEvM.ucCtrStatus = EVM_CTR_IDLE;

    stEvM.usReadBankId = 0u;
}
/*******************************************************************************
Name			: EvM_MngReadAll
Syntax			: static void EvM_MngReadAll( void )
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(in)	: None
Parameters(out) : None						:-
Return value	: None
Description		: ENvM manage the read all mode
Call By			: -
|******************************************************************************/
static void EVM_ModeReadAllHandle( void )
{
	if(EVM_CTR_FINISH == stEvM.ucCtrStatus)
	{
		stEvM.usReadBankId++;
		stEvM.ucCtrStatus = EVM_CTR_IDLE;
	}

    if(EVM_CTR_IDLE == stEvM.ucCtrStatus)
    {
        if(stEvM.usReadBankId < (uint16)EVM_BANK_ID_MAX_NUM)
        {
            stEvM.ucCtrStatus = (uint8)EVM_CTR_READ_BANK;
            stEvM.ucReReadCnt = 0u;
        }
        else
        {
        	EEPM_MultiBlockCallbackFunction(EVM_SERVICE_READALL, 1u);
            EVM_SetIdle();
        }
    }
}
/*******************************************************************************
Name			: EvM_MngWriteBlock
Syntax			: static void EvM_MngWriteBlock( void )
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(in)	: None
Parameters(out) : None						:-
Return value	: None
Description		: ENvM manage the write block mode
Call By			: -
|******************************************************************************/
STATIC void EVM_ModeWriteBankHandle( void )
{
    if(stEvM.ucCtrStatus != EVM_CTR_WRITE_BACKUP_BANK)
    {
        stEvM.ucCtrStatus =  (uint8)EVM_CTR_WRITE_BANK;
    }
}

/*******************************************************************************
Name			: EvM_HandleReadBlock
Syntax			: static void EvM_HandleReadBlock( void )
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(in)	: None
Parameters(out) : None						:-
Return value	: None
Description		: ENvM handle read block
Call By			: -
|******************************************************************************/
static void EVM_InternalReadBank( void )
{
    uint16 	crcValue1;
    uint16 	crcValue2;
    uint16 	len = 0u;
    uint16 	LenIdx;
    uint8 	EepJobResult;

    switch(stEvM.ucReadBankStep)
    {
    case EVM_READ_STEP0:
    	len = EvM_BankCfgTable[stEvM.usReadBankId].usBankLength + (uint16)2u;
    	(void)FlsIf_Read(EvM_BankCfgTable[stEvM.usReadBankId].usBankId, 0U, stEvM.ucBuff,(uint16)len);
        stEvM.ucReadBankStep =  (uint8)EVM_READ_STEP1;
        break;

    case EVM_READ_STEP1:
        EepJobResult = (uint8)EVM_DrvGetJobResult();
        if( (uint8)EVM_JOB_OK == EepJobResult)
        {
            len = EvM_BankCfgTable[stEvM.usReadBankId].usBankLength;
            crcValue1 = CRC_CalculateCRC16 (stEvM.ucBuff, (uint32)len , (uint16)0u, (uint8)TRUE);
            crcValue2 = stEvM.ucBuff[len];
            crcValue2 <<= 8u;
            crcValue2 += stEvM.ucBuff[len + (uint16)1u];

            if(crcValue1 == crcValue2)
            {
                LIB_Copy(EvM_BankCfgTable[stEvM.usReadBankId].ucRamDataAddr, stEvM.ucBuff, len);
                stEvM.ucCtrStatus = EVM_CTR_FINISH;
                stEvM.ucReadBankStep = EVM_READ_STEP0;
            }
            else
            {
                for(LenIdx = 0u; LenIdx < len; LenIdx++)
                {
                    if( (stEvM.ucBuff[LenIdx] != (uint8)EVMCFG_Value_0) && (stEvM.ucBuff[LenIdx] != (uint8)EVMCFG_Value_FF))
                    {
                        break;
                    }
                    else
                    {
                    }
                }
                if(LenIdx == len)
                {
                    stEvM.ucCtrStatus = EVM_CTR_FINISH;
                    stEvM.ucReadBankStep = EVM_READ_STEP0;
                    /*Copy data form rom*/
                  /* polyspace<MISRA-C3:11.8:Not a defect:Justified> Normal. */
                    LIB_Copy((uint8 *)EvM_BankCfgTable[stEvM.usReadBankId].ucRamDataAddr, (uint8 *)EvM_BankCfgTable[stEvM.usReadBankId].ucRomDataAddr, len);/*PRQA S 0311*/
                }
                else
                {
                    stEvM.ucReadBankStep = EVM_READ_STEP2;
                }
            }
        }
        else if((uint8)EVM_JOB_FAILED == EepJobResult)
        {
            stEvM.ucReadBankStep = EVM_READ_STEP2;
        }
        else
        {}

        break;

    case EVM_READ_STEP2:
        if(stEvM.ucReReadCnt < (uint8)EVM_WR_MAX_TIMER)
        {
            stEvM.ucReReadCnt++;
        }
        else
        {
            stEvM.ucReReadCnt = 0u;
#if (EVM_BANK_BACKUP_CLASS == EVM_ENABLE)
            if( ( EvM_BankCfgTable[stEvM.usReadBankId].ucFlag & (uint8)EVM_BANK_BACKUP_ON ) == (uint8)EVM_BANK_BACKUP_ON )
            {
                stEvM.ucCtrStatus =  (uint8)EVM_CTR_READ_BACKUP_BANK;
            }
            else
            {
                stEvM.ucCtrStatus = EVM_CTR_FINISH;
                len = EvM_BankCfgTable[stEvM.usReadBankId].usBankLength;
/* polyspace<MISRA-C3:11.8:Not a defect:Justified> Normal. */
                LIB_Copy((uint8 *)EvM_BankCfgTable[stEvM.usReadBankId].ucRamDataAddr, (uint8 *)EvM_BankCfgTable[stEvM.usReadBankId].ucRomDataAddr, len);/*PRQA S 0311*/
            }
#else
            stEvM.ucCtrStatus = EVM_CTR_FINISH;
            len = EvM_BankCfgTable[stEvM.usReadBankId].usBankLength;
            LIB_Copy((uint8 *)EvM_BankCfgTable[stEvM.usReadBankId].ucRamDataAddr, (uint8 *)EvM_BankCfgTable[stEvM.usReadBankId].ucRomDataAddr, len);
#endif
        }
        stEvM.ucReadBankStep =  (uint8)EVM_READ_STEP0;
        break;

    default:
        stEvM.ucReadBankStep =  (uint8)EVM_READ_STEP0;
        break;
    }
}
/*******************************************************************************
Name			: EvM_InternalWriteBank
Syntax			: static void EvM_InternalWriteBank( void )
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(in)	: None
Parameters(out) : None						:-
Return value	: None
Description		: ENvM handle write block
Call By			: -
|******************************************************************************/
static void EVM_InternalWriteBank( void )
{
	uint16 	len = 0u;
    uint8 	EepJobResult;
    switch(stEvM.ucWriteBankStep)
    {
    case EVM_WRITE_STEP0:
        len = EvM_BankCfgTable[stEvM.usWriteBankId].usBankLength + (uint16)2u;
        (void)Fee_Write(EvM_BankCfgTable[stEvM.usWriteBankId].usBankId, stEvM.ucBuff);
        stEvM.ucWriteBankStep =  EVM_WRITE_STEP1;
        break;

    case EVM_WRITE_STEP1:
        EepJobResult = (uint8)EVM_DrvGetJobResult();
        if((uint8)EVM_JOB_OK == EepJobResult)
        {
            EVM_SetIdle();
            stEvM.ucWriteBankStep =  EVM_WRITE_STEP0;
        }
        else if((uint8)EVM_JOB_FAILED == EepJobResult)
        {
            stEvM.ucWriteBankStep =  EVM_WRITE_STEP2;
        }
        else
        {}
        break;

    case EVM_WRITE_STEP2:
        if(stEvM.ucReWriteCnt < (uint8)EVM_WR_MAX_TIMER)
        {
            stEvM.ucReWriteCnt++;
        }
        else
        {
            EVM_SetIdle();
            stEvM.ucReWriteCnt = 0u;
        }
        stEvM.ucWriteBankStep =  EVM_WRITE_STEP0;
        break;
    default:
        stEvM.ucWriteBankStep =  EVM_WRITE_STEP0;
        break;
    }
#if (EVM_BANK_BACKUP_CLASS == EVM_ENABLE)
    if(EVM_CTR_IDLE == stEvM.ucCtrStatus)
    {
        if( (EvM_BankCfgTable[stEvM.usWriteBankId].ucFlag & (uint8)EVM_BANK_BACKUP_ON ) == (uint8)EVM_BANK_BACKUP_ON)
        {
            stEvM.ucCtrStatus =  (uint8)EVM_CTR_WRITE_BACKUP_BANK;
            stEvM.ucMode =  (uint8)EVM_MODE_WRITE_BANK;
        }
        else
        {}
    }
#endif
}
#if (EVM_BANK_BACKUP_CLASS == EVM_ENABLE)
/*******************************************************************************
Name			: EvM_HandleReadBackUpBlock
Syntax			: static void EvM_HandleReadBackUpBlock( void )
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(in)	: None
Parameters(out) : None						:-
Return value	: None
Description		: ENvM handle read back up block
Call By			: -
|******************************************************************************/
static void EVM_InternalReadBackUpBank( void )
{
    uint16 	crcValue1;
    uint16 	crcValue2;
    uint16 	len;
    uint8 	EepJobResult;

    switch(stEvM.ucReadBankStep)
    {
    case EVM_READ_STEP0:
    	len = EvM_BankCfgTable[stEvM.usReadBankId].usBankLength +(uint16)2u;
        (void)FlsIf_Read((EvM_BankCfgTable[stEvM.usReadBankId].usBankId + EVM_BACKUP_START_ID), 0U, stEvM.ucBuff,(uint32)len);
        stEvM.ucReadBankStep = EVM_READ_STEP1;
        break;

    case EVM_READ_STEP1:
        EepJobResult = (uint8)EVM_DrvGetJobResult();
        if((uint8)EVM_JOB_OK == EepJobResult)
        {
            len = EvM_BankCfgTable[stEvM.usReadBankId].usBankLength;
            crcValue1 = CRC_CalculateCRC16 (stEvM.ucBuff, (uint32)len , (uint16)0u, (uint8)TRUE);
            crcValue2 = stEvM.ucBuff[len];
            crcValue2 <<= 8u;
            crcValue2 += stEvM.ucBuff[len + (uint16)1u];

            if(crcValue1 == crcValue2)
            {
                LIB_Copy(EvM_BankCfgTable[stEvM.usReadBankId].ucRamDataAddr, stEvM.ucBuff, len);
                stEvM.ucCtrStatus =  EVM_CTR_FINISH;
                stEvM.ucReadBankStep = EVM_READ_STEP0;
            }
            else
            {
                stEvM.ucReadBankStep = EVM_READ_STEP2;
            }
        }
        else if((uint8)EVM_JOB_FAILED == EepJobResult)
        {
            stEvM.ucReadBankStep = EVM_READ_STEP2;
        }
        else
        {}
        break;

    case EVM_READ_STEP2:
        if(stEvM.ucReReadCnt < (uint8)EVM_WR_MAX_TIMER)
        {
            stEvM.ucReReadCnt++;
        }
        else
        {
            stEvM.ucCtrStatus = EVM_CTR_FINISH;
            stEvM.ucReReadCnt = 0u;
            len = EvM_BankCfgTable[stEvM.usReadBankId].usBankLength;
         /* polyspace<MISRA-C3:11.8:Not a defect:Justified> Normal. */
            LIB_Copy((uint8 *)EvM_BankCfgTable[stEvM.usReadBankId].ucRamDataAddr, (uint8 *)EvM_BankCfgTable[stEvM.usReadBankId].ucRomDataAddr, len);/*PRQA S 0311*/
        }

        stEvM.ucReadBankStep = EVM_READ_STEP0;
        break;

    default:
        stEvM.ucReadBankStep = EVM_READ_STEP0;
        break;
    }
}
/*******************************************************************************
Name			: EVM_InternalWriteBackUpBank
Syntax			: static void EVM_InternalWriteBackUpBank( void )
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(in)	: None
Parameters(out) : None						:-
Return value	: None
Description		: ENvM handle write back up block
Call By			: -
|******************************************************************************/
static void EVM_InternalWriteBackUpBank( void )
{
    uint8 	EepJobResult;
    uint16 	len;
    switch(stEvM.ucWriteBankStep)
    {
    case EVM_WRITE_STEP0:
    	len = EvM_BankCfgTable[stEvM.usWriteBankId].usBankLength + (uint16)2u;
        (void)FlsIf_Write((EvM_BankCfgTable[stEvM.usWriteBankId].usBankId + EVM_BACKUP_START_ID), stEvM.ucBuff);
        stEvM.ucWriteBankStep = EVM_WRITE_STEP1;
        break;

    case EVM_WRITE_STEP1:
        EepJobResult = (uint8)EVM_DrvGetJobResult();
        if((uint8)EVM_JOB_OK == EepJobResult)
        {
            EVM_SetIdle();
            stEvM.ucWriteBankStep = EVM_WRITE_STEP0;
        }
        else if((uint8)EVM_JOB_FAILED == EepJobResult)
        {
            stEvM.ucWriteBankStep = EVM_WRITE_STEP2;
        }
        else
        {}
        break;

    case EVM_WRITE_STEP2:
        if(stEvM.ucReWriteCnt < (uint8)EVM_WR_MAX_TIMER)
        {
            stEvM.ucReWriteCnt++;
        }
        else
        {
            EVM_SetIdle();
            stEvM.ucReWriteCnt = 0u;
        }

        stEvM.ucWriteBankStep = EVM_WRITE_STEP0;
        break;

    default:
        stEvM.ucWriteBankStep = EVM_WRITE_STEP0;
        break;
    }
}
#endif
/****************************************************************************************
Name			:EvM_MainFunction
Syntax			:void EvM_MainFunction( void )
Sync/Async		:Synchronous
Reentrancy		:
Parameters(in)	:None						:-
Parameters(out) :None						:-
Return value	:None						:-
Description		:Main Function
Call By			:
*****************************************************************************************/
void EVM_MainFunction( void )
{
    switch(stEvM.ucMode)
    {
    case EVM_MODE_IDLE:
        EVM_ModeIdleHandle();
        break;
    case EVM_MODE_READALL:
        EVM_ModeReadAllHandle();
        break;

    case EVM_MODE_WRITE_BANK:
        EVM_ModeWriteBankHandle();
        break;

    default:
        stEvM.ucMode = EVM_MODE_IDLE;
        break;
    }

    switch(stEvM.ucCtrStatus)
    {
    case EVM_CTR_READ_BANK:
        EVM_InternalReadBank();
        break;

    case EVM_CTR_WRITE_BANK:
        EVM_InternalWriteBank();
        break;
#if (EVM_BANK_BACKUP_CLASS == EVM_ENABLE)
    case EVM_CTR_READ_BACKUP_BANK:
        EVM_InternalReadBackUpBank();
        break;

    case EVM_CTR_WRITE_BACKUP_BANK:
        EVM_InternalWriteBackUpBank();
        break;
#endif
    default:
        stEvM.ucCtrStatus = EVM_CTR_IDLE;
        break;
    }
}

#endif/*(EVM_MODULE_EN == EVM_ENABLE)	*/
/*EOF*/
