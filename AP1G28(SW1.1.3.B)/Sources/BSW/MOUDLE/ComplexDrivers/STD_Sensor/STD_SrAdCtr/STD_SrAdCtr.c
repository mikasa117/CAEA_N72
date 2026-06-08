/* polyspace<MISRA-C3:1.1:Not a defect:Justified> NO fluence */
/*******************************************************************************
|  File Name:  STD_SrAdCtr.c
|  Description:  Implementation of the Sensor Ctr Management
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
| 2018-06-21    01.00.00     XYJ       Creation
|
|******************************************************************************/


/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_SrAdCtr.h"
#include "STD_SrAdCtr_Cfg.h"
//#include "fsl_gpio.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#if (SRM_TYPE_AD_TABLE_CLASS == SRM_ENABLE)
/*Sensor Resister table -40 index,and 85 index*/
/*#define SRADCTR_RES_TABLE_NUM_INDEX						(0u)*/
/*#define SRADCTR_RES_TABLE_RESMAX_INDEX				(1u)*/
/*#define SRADCTR_RES_TABLE_RESMIN_INDEX 	ResTablePtr[SRADCTR_RES_TABLE_NUM_INDEX]*/

/*#define SRADCTR_RES_TABLE_POSITIVE85_INDEX				(125u)*/
//#define OK_3v3                          (0u)
#define SRADCTR_NO_ERROR				(0u)
#define SRADCTR_SHORT_TO_GND			(1u)
#define SRADCTR_OPEN_OR_SHORT_TO_BAT	(2u)

/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Static local KAM variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/
/* polyspace<MISRA-C3:2.5:Not a defect:Justified> NO fluence */
#define STD_SRADCTR_START_SEC_VAR_RAM
#include "STD_MemMap.h"

 sint16 TEST_NTC;
 //uint8 OK_3V3;
static sint16 SRADCTR_CODE_RAM ssSrAdTableValidValue[SRADCTR_TABLE_CH_MAX_NUM];
static LibFilterStruct SRADCTR_CODE_RAM stSrAdTableDiag[SRADCTR_TABLE_CH_MAX_NUM];

#if (SRCFG_ENABLE == SRCTRCFG_AD_LINE_CLASS)
static sint16 SRADCTR_CODE_RAM ssSrAdLineValidValue[SRADCTR_LINE_CH_MAX_NUM];
static LibFilterStruct SRADCTR_CODE_RAM stSrAdLineDiag[SRADCTR_LINE_CH_MAX_NUM];
#endif
/* polyspace<MISRA-C3:2.5:Not a defect:Justified> NO fluence */
#define STD_SRADCTR_STOP_SEC_VAR_RAM
/* polyspace<MISRA-C3:20.1:Not a defect:Justified> NO fluence */
#include "STD_MemMap.h"


/*******************************************************************************
|    Table Const Definition
|******************************************************************************/
static sint16 SRADCTR_ResLookUpTableConvTemp(uint8 CtrChannel, uint32 SensorRes);
static sint16 SRADCTR_LookUpTable1Conv2Table2( uint8 CtrChannel, uint32 Target);
static void SRADCTR_TableConvert( uint8 CtrChannel );

static void SRADCTR_TableDiag( uint8 CtrChannel );
#if (SRCFG_ENABLE == SRCTRCFG_AD_LINE_CLASS)
static void SRADCTR_LineConvert(  uint8 CtrChannel	);
static void SRADCTR_LineDiag( uint8 CtrChannel );
#endif
/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/

/*******************************************************************************
Name			: SRCTR_InitMemory
Syntax			: void SRCTR_InitMemory( void )
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None					:-
Parameters(out) : None					:-
Return value	: None					:-
Description		: Initializes the module Ram memory.
Call By			: EcuM
|******************************************************************************/
void SRADCTR_InitMemory( void )
{/* polyspace<MISRA-C3:10.3:Not a defect:Justified> NO fluence */
    LIB_SetMemory( (uint8 *)&ssSrAdTableValidValue, 0u, sizeof(ssSrAdTableValidValue) / sizeof(uint8));/*PRQA S 0310*/
    /* polyspace<MISRA-C3:10.3:Not a defect:Justified> NO fluence */
    LIB_SetMemory( (uint8 *)&stSrAdTableDiag, 0u, sizeof(stSrAdTableDiag) / sizeof(uint8));/*PRQA S 0310*/
#if (SRCFG_ENABLE == SRCTRCFG_AD_LINE_CLASS)
	LIB_SetMemory( (uint8 *)&ssSrAdLineValidValue, 0u, sizeof(ssSrAdLineValidValue) / sizeof(uint8));/*PRQA S 0310*/
	LIB_SetMemory( (uint8 *)&stSrAdLineDiag, 0u, sizeof(stSrAdLineDiag) / sizeof(uint8));/*PRQA S 0310*/
#endif
}

/*******************************************************************************
Name			: SRCTR_MainFunction
Syntax			: void SRCTR_MainFunction( void )
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None					:-
Parameters(out) : None					:-
Return value	: None					:-
Description		: control module main function, 10ms cycle.
Call By			: Task
|******************************************************************************/
void SRADCTR_ConvMainFunction( void )
{
    uint8 TempChannel;

    for(TempChannel = 0u; TempChannel < (uint8)SRADCTR_TABLE_CH_MAX_NUM; TempChannel++)
    {
        SRADCTR_TableConvert( TempChannel );
    }
#if (SRCFG_ENABLE == SRCTRCFG_AD_LINE_CLASS)
    for(TempChannel = 0u; TempChannel < (uint8)SRADCTR_LINE_CH_MAX_NUM; TempChannel++)
    {
        SRADCTR_LineConvert( TempChannel );
    }
#endif
}

/*******************************************************************************
Name			: SRCTR_AdTableConvert
Syntax			: void SRCTR_AdTableConvert( void )
Sync/Async		: sync
Reentrancy		:
Parameters(in)	: None					:-
Parameters(out) : None					:-
Return value	: None					:-
Description		: calculate sensor temperature.
Call By			: SRCTR_MainFunction
|******************************************************************************/
static void SRADCTR_TableConvert( uint8 CtrChannel )
{

	static uint16 	TempLastAdValue = 0xFFFFu;
    uint32 			ResValue = 0u;
    uint16 			ADValue = 0u;
    uint8  	TempChannel = CtrChannel;
    uint8  	TempAdChannel = (uint8)stSrCtrAdTableCfg[TempChannel].ucHwAdChannel;
	uint8  	TempRTCSleepStatus = 0u;
/* polyspace<DEFECT:DEAD_CODE:Not a defect:Justified> This is a pre-compiled problem. *//* polyspace<MISRA-C3:2.1:Not a defect:Justified> NO fluence *//* polyspace<MISRA-C3:14.3:Not a defect:Justified> NO fluence */
    if ( (uint8)TRUE == TempRTCSleepStatus )		/*sleep little mode*/
    {
        ADValue = SRADCTR_GetCurrentAdValue( TempAdChannel );
    }
    else
    {
        ADValue = SRADCTR_GetValidAdValue( TempAdChannel );
    }

    if(TempLastAdValue != ADValue)
    {
        TempLastAdValue = ADValue;

        if (ADValue >= stSrCtrAdTableCfg[ TempChannel ].usPrecision)
        {
            ADValue = stSrCtrAdTableCfg[ TempChannel ].usPrecision - (uint16)1;
        }

        if ((uint8)SRCTRCFG_TABLE_TYPE_RES != stSrCtrAdTableCfg[TempChannel].usTableTypeVoltOrRes)
        {
            if (NULL != stSrCtrAdTableCfg[TempChannel].pulResTable2)
            {
                if ((uint8)SRCTRCFG_PULL_UP != stSrCtrAdTableCfg[TempChannel].usPullUpOrDnSta)
                {
                    ssSrAdTableValidValue[TempChannel] = SRADCTR_LookUpTable1Conv2Table2(TempChannel, (uint32)ADValue);
                }
                else
                {
                    ssSrAdTableValidValue[TempChannel] = SRADCTR_LookUpTable1Conv2Table2(TempChannel, ((uint32)stSrCtrAdTableCfg[TempChannel].usPrecision - (uint32)1 - (uint32)ADValue));
                }
            }
            else
            {

            }
        }
        else
        {
            if (NULL != stSrCtrAdTableCfg[TempChannel].pulResTable2)
            {

            }
            else
            {
                if ((uint8)SRCTRCFG_PULL_UP != stSrCtrAdTableCfg[TempChannel].usPullUpOrDnSta)
                {
                    ResValue = (((uint32)stSrCtrAdTableCfg[ TempChannel ].usPullUpOrDnRes ) * (uint32)(stSrCtrAdTableCfg[TempChannel].usPrecision - (uint32)ADValue)) / (uint32)ADValue;
                    ssSrAdTableValidValue[TempChannel] = SRADCTR_ResLookUpTableConvTemp(TempChannel, ResValue);
                }
                else
                {
                    ResValue = ( ( uint32 )ADValue * ( uint32 )stSrCtrAdTableCfg[ TempChannel ].usPullUpOrDnRes ) / ( uint32 )( stSrCtrAdTableCfg[ TempChannel ].usPrecision - (uint32)ADValue );
                    ssSrAdTableValidValue[TempChannel] = SRADCTR_ResLookUpTableConvTemp( TempChannel, ResValue);
                    //TEST_NTC=ResValue;
                    TEST_NTC=ssSrAdTableValidValue[TempChannel];
                }
            }
        }
    }

}

/*******************************************************************************
Name			: SRCTR_GetValidValue
Syntax			: sint16 SRCTR_GetValidValue( uint8 ucChannel )
Sync/Async		: Async
Reentrancy		:
Parameters(in)	: ucChannel				:sensor channel
Parameters(out) : None					:-
Return value	: SensorValidValue		:sensor valid value
Description		: Get Sensor valid value
Call By			: RTE
|******************************************************************************/
sint16 SRADCTR_TableGetValidValue( uint8 CtrChannel )
{
	sint16 ReValidValue = 0;
	if(CtrChannel < (uint8)SRADCTR_TABLE_CH_MAX_NUM)
	{
		ReValidValue = ssSrAdTableValidValue[CtrChannel];
	}
    return ReValidValue;
}

/*******************************************************************************
Name			: SRCTR_ResConvTemp
Syntax			: sint16 SRCTR_ResConvTemp( uint32 SensorRes, const uint32 *ResTablePtr, uint16 TableLength )
Sync/Async		: Sync
Reentrancy		:
Parameters(in)	: SensorRes				:sensor resister value
Parameters(in)	: ResTablePtr			:sensor resister table address
Parameters(in)	: TableLength			:sensor resister table length
Parameters(out) : None					:-
Return value	: TempReturnValue		:sensor current temperature
Description		: calculate sensor current temperature
Call By			: SRCTR_GetTemperature
|******************************************************************************/
static sint16 SRADCTR_ResLookUpTableConvTemp( uint8 CtrChannel, uint32 SensorRes)
{
    uint16       SearchReturnValue = 0u;
    sint16       TempReturnValue = 0 ;
    uint32       Tmp = 0u;
	uint16 TableLength = (uint16)stSrCtrAdTableCfg[ CtrChannel ].pulResTable[0u];

    if ( SensorRes >= stSrCtrAdTableCfg[ CtrChannel ].pulResTable[1u] )/*PRQA S 0491*/
    {
        TempReturnValue = stSrCtrAdTableCfg[CtrChannel].MinTempValue;
    }
    else if ( SensorRes <= stSrCtrAdTableCfg[ CtrChannel ].pulResTable[TableLength] )/*PRQA S 0491*/
    {
        TempReturnValue = stSrCtrAdTableCfg[CtrChannel].MaxTempVlaue;
    }
    else
    {
		SearchReturnValue = LIB_BinarySearch(&(stSrCtrAdTableCfg[CtrChannel].pulResTable[1u]), TableLength, SensorRes ) + (uint16)1u;/*PRQA S 0491*/

		if ( SensorRes == stSrCtrAdTableCfg[ CtrChannel ].pulResTable[ SearchReturnValue ] )/*PRQA S 0491*/
		{
			TempReturnValue = (sint16)((((sint16)SearchReturnValue - (sint16)1u) * 10) + stSrCtrAdTableCfg[CtrChannel].MinTempValue);
		}
		else if (SensorRes > stSrCtrAdTableCfg[CtrChannel].pulResTable[SearchReturnValue])/*PRQA S 0491*/
		{
			Tmp = ((uint32)SearchReturnValue - (uint32)1u) * 10u;
			Tmp -= ((uint32)10 * (SensorRes - stSrCtrAdTableCfg[CtrChannel].pulResTable[SearchReturnValue])) / (stSrCtrAdTableCfg[CtrChannel].pulResTable[SearchReturnValue - (uint16)1] - stSrCtrAdTableCfg[CtrChannel].pulResTable[SearchReturnValue]);/*PRQA S 0491*/
			TempReturnValue = (sint16)Tmp;
            TempReturnValue += (stSrCtrAdTableCfg[CtrChannel].MinTempValue);
		}
		else
		{
			Tmp = ((uint32)SearchReturnValue - (uint32)1u) * 10u;
			Tmp += ((uint32)10 * (stSrCtrAdTableCfg[CtrChannel].pulResTable[SearchReturnValue] - SensorRes)) / (stSrCtrAdTableCfg[CtrChannel].pulResTable[SearchReturnValue] - stSrCtrAdTableCfg[CtrChannel].pulResTable[SearchReturnValue + (uint16)1]);/*PRQA S 0491*/
			TempReturnValue = (sint16)Tmp;
            TempReturnValue += (stSrCtrAdTableCfg[CtrChannel].MinTempValue);
		}
    }
    return TempReturnValue;	/*-400~850*/
}

static sint16 SRADCTR_LookUpTable1Conv2Table2( uint8 CtrChannel, uint32 Target)
{
    uint16 SearchReturnValue;
    sint16 TempReturnValue;

    if (Target >= stSrCtrAdTableCfg[CtrChannel].pulResTable[1u])/*PRQA S 0491*/
    {
        TempReturnValue = stSrCtrAdTableCfg[CtrChannel].MaxTempVlaue;
    }
    else if (Target <= stSrCtrAdTableCfg[CtrChannel].pulResTable[stSrCtrAdTableCfg[CtrChannel].pulResTable[0u]])/*PRQA S 0491*/
    {
        TempReturnValue = stSrCtrAdTableCfg[CtrChannel].MinTempValue;
    }
    else
    {
        SearchReturnValue = LIB_BinarySearch(&(stSrCtrAdTableCfg[CtrChannel].pulResTable[1u]), (uint16)stSrCtrAdTableCfg[CtrChannel].pulResTable[0u], Target) + (uint16)1u;/*PRQA S 0491*/

        if (Target == stSrCtrAdTableCfg[CtrChannel].pulResTable[SearchReturnValue])/*PRQA S 0491*/
        {
            TempReturnValue = (sint16)stSrCtrAdTableCfg[CtrChannel].pulResTable2[SearchReturnValue];/*PRQA S 0491*/
        }
        else if (Target > stSrCtrAdTableCfg[CtrChannel].pulResTable[SearchReturnValue])/*PRQA S 0491*/
        {/* polyspace<MISRA-C3:10.8:Not a defect:Justified> NO fluence */
            TempReturnValue = (sint16)(((uint32)(stSrCtrAdTableCfg[CtrChannel].pulResTable2[SearchReturnValue - (uint16)1] - stSrCtrAdTableCfg[CtrChannel].pulResTable2[SearchReturnValue]) \
                    * (uint32)(Target - stSrCtrAdTableCfg[CtrChannel].pulResTable[SearchReturnValue])) \
                    / (uint32)(stSrCtrAdTableCfg[CtrChannel].pulResTable[SearchReturnValue - (uint16)1] - stSrCtrAdTableCfg[CtrChannel].pulResTable[SearchReturnValue]));/*PRQA S 0491*/
            TempReturnValue = TempReturnValue + (sint16)stSrCtrAdTableCfg[CtrChannel].pulResTable2[SearchReturnValue];/*PRQA S 0491*/
        }
        else
        {/* polyspace<MISRA-C3:10.8:Not a defect:Justified> NO fluence */
            TempReturnValue = (sint16)(((uint32)(stSrCtrAdTableCfg[CtrChannel].pulResTable2[SearchReturnValue] - stSrCtrAdTableCfg[CtrChannel].pulResTable2[SearchReturnValue + (uint16)1]) \
                    * (uint32)(stSrCtrAdTableCfg[CtrChannel].pulResTable[SearchReturnValue] - Target))	 \
                    / (uint32)(stSrCtrAdTableCfg[CtrChannel].pulResTable[SearchReturnValue] - stSrCtrAdTableCfg[CtrChannel].pulResTable[SearchReturnValue + (uint16)1]));/*PRQA S 0491*/
            TempReturnValue =  (sint16)stSrCtrAdTableCfg[CtrChannel].pulResTable2[SearchReturnValue] - TempReturnValue;/*PRQA S 0491*/
        }
    }

    return (TempReturnValue);
}

void SRADCTR_DiagMainFunction( void )
{
    uint8 TempChannel;

    for(TempChannel = 0u; TempChannel < (uint8)SRADCTR_TABLE_CH_MAX_NUM; TempChannel++)
    {
        SRADCTR_TableDiag( TempChannel );
    }
#if (SRCFG_ENABLE == SRCTRCFG_AD_LINE_CLASS)
	for(TempChannel = 0u; TempChannel < (uint8)SRADCTR_LINE_CH_MAX_NUM; TempChannel++)
    {
        SRADCTR_LineDiag( TempChannel );
    }
#endif
}

static void SRADCTR_TableDiag( uint8 CtrChannel )
{
	uint8 	TempChannel = CtrChannel;
	/* polyspace<MISRA-C3:D4.5:Not a defect:Justified> NO fluence */
    uint16      	AdValue = 0u;

    AdValue = SRADCTR_GetValidAdValue( (uint8)stSrCtrAdTableCfg[TempChannel].ucHwAdChannel );

    if ( AdValue < stSrCtrAdTableCfg[ TempChannel ].ShortThreshold )
    {
        /*Short to Gnd*/
        stSrAdTableDiag[TempChannel].ucStatus = SRADCTR_SHORT_TO_GND;
    }
    else if ( AdValue > stSrCtrAdTableCfg[ TempChannel ].OpenThreshold )
    {
        /*Open or short to battery */
        stSrAdTableDiag[TempChannel].ucStatus = SRADCTR_OPEN_OR_SHORT_TO_BAT;
    }
    else
    {
        /*Clear dtc count value */
        stSrAdTableDiag[TempChannel].ucStatus = SRADCTR_NO_ERROR;
    }

    if((uint8)TRUE == LIB_StatusFilter(&(stSrAdTableDiag[TempChannel]), SRDIAG_FILTER_CNT))
    {
    }
}

uint32 SRADCTR_TableGetOpenShortStatus( void )
{/* polyspace<MISRA-C3:D4.5:Not a defect:Justified> NO fluence */
    uint8 	Channel = 0u;
    uint32 	DtcBits = 0u;

    for ( Channel = 0u; Channel < (uint8)SRADCTR_TABLE_CH_MAX_NUM; Channel++ )
    {
        if ( (uint8)SRADCTR_NO_ERROR == stSrAdTableDiag[ Channel ].ucValidStatus)
        {
            LIB_SET_UINT32_BIT(DtcBits, stSrCtrAdTableCfg[ Channel ].DtcBitMask );
        }
    }

    return DtcBits;
}

uint8 SRADCTR_TableGetValidStatus(  uint8 CtrChannel  )
{
    uint8 ValidStatus = 0u;

    if ( (uint8)SRADCTR_NO_ERROR == stSrAdTableDiag[ CtrChannel ].ucValidStatus)
    {
        ValidStatus = 1u;
    }

    return ValidStatus;
}

uint8 SRADCTR_TableGetShortGndStatus( SRADCTR_Table_CH_Enum ucChannel )
{
    uint8 SensorDtcStatus = FALSE;

	if ((uint8)SRADCTR_SHORT_TO_GND == stSrAdTableDiag[ ucChannel ].ucValidStatus)
	{
		SensorDtcStatus = TRUE;
	}

    return SensorDtcStatus;
}

uint8 SRADCTR_TableGetOpenOrShortBatStatus( SRADCTR_Table_CH_Enum ucChannel )
{
    uint8 SensorDtcStatus = FALSE;

	if ((uint8)SRADCTR_OPEN_OR_SHORT_TO_BAT == stSrAdTableDiag[ ucChannel ].ucValidStatus)
	{
		SensorDtcStatus = TRUE;
	}

    return SensorDtcStatus;
}

uint8 SRADCTR_TableErrValue( SRADCTR_Table_CH_Enum ucChannel )
{
    return stSrAdTableDiag[ ucChannel ].ucValidStatus;
}

#if (SRCFG_ENABLE == SRCTRCFG_AD_LINE_CLASS)
static void SRADCTR_LineConvert(  uint8 CtrChannel  )
{
	static uint16 	TempLastAdValue = 0xFFFFu;
	uint8 			TempRTCSleepStatus = SRCTR_GetRTCSleepStatus();
	uint16 			ADValue = 0u;
	uint8 			TempChannel = CtrChannel;
	uint8 			TempAdChannel = (uint8)stSrCtrAdLineCfg[TempChannel].ucHwAdChannel;

	if ( (uint8)TRUE == TempRTCSleepStatus )		/*sleep little mode*/
	{
	    ADValue = SRADCTR_GetCurrentAdValue( TempAdChannel );
	}
	else
	{
	    ADValue = SRADCTR_GetValidAdValue( TempAdChannel );
	}

	if(TempLastAdValue != ADValue)
	{
	    TempLastAdValue = ADValue;
	    ssSrAdLineValidValue[TempChannel] = ( sint16 )(  ( (uint32)( ADValue - stSrCtrAdLineCfg[ TempChannel ].usAdMin ) * stSrCtrAdLineCfg[ TempChannel ].usTagMax )
	                                    / (stSrCtrAdLineCfg[ TempChannel ].usAdMax - stSrCtrAdLineCfg[ TempChannel ].usAdMin) );
	}
}

static void SRADCTR_LineDiag( uint8 CtrChannel )
{
    uint8  TempChannel = CtrChannel;
    uint16 AdValue = 0u;

    AdValue = SRADCTR_GetValidAdValue( (uint8)stSrCtrAdLineCfg[TempChannel].ucHwAdChannel );

    if ( AdValue <= stSrCtrAdLineCfg[ TempChannel ].ShortThreshold )
    {
        /*Short to Gnd*/
		stSrAdLineDiag[TempChannel].ucStatus = SRADCTR_SHORT_TO_GND;
    }
    else if ( AdValue >= stSrCtrAdLineCfg[ TempChannel ].OpenThreshold )
    {
        /*Open or short to battery */
        stSrAdLineDiag[TempChannel].ucStatus = SRADCTR_OPEN_OR_SHORT_TO_BAT;
    }
    else
    {
        /*Clear dtc count value */
        stSrAdLineDiag[TempChannel].ucStatus = SRADCTR_NO_ERROR;
    }

    if((uint8)TRUE == LIB_StatusFilter(&(stSrAdLineDiag[TempChannel]), SRDIAG_FILTER_CNT))
    {
    }
}

sint16 SRADCTR_LineGetValidValue( SRADCTR_Line_CH_Enum CtrChannel )
{
	sint16 ReValidValue = 0;
	if(CtrChannel < SRADCTR_LINE_CH_MAX_NUM)
	{
		ReValidValue = ssSrAdLineValidValue[CtrChannel];
	}
    return ReValidValue;
}

uint8 SRADCTR_LineGetValidStatus(  SRADCTR_Line_CH_Enum CtrChannel  )
{
    uint8 ValidStatus = 0u;

    if ( (uint8)SRADCTR_NO_ERROR == stSrAdLineDiag[ CtrChannel ].ucValidStatus)
    {
        ValidStatus = 1u;
    }

    return ValidStatus;
}

uint8 SRADCTR_LineGetShortGndStatus( SRADCTR_Line_CH_Enum ucChannel )
{
    uint8 SensorDtcStatus = FALSE;

	if ( (uint8)SRADCTR_SHORT_TO_GND == stSrAdLineDiag[ ucChannel ].ucValidStatus)
	{
		SensorDtcStatus = TRUE;
	}

    return SensorDtcStatus;
}

uint8 SRADCTR_LineGetOpenOrShortBatStatus( SRADCTR_Line_CH_Enum ucChannel )
{
    uint8 SensorDtcStatus = FALSE;

	if ( (uint8)SRADCTR_OPEN_OR_SHORT_TO_BAT == stSrAdLineDiag[ ucChannel ].ucValidStatus)
	{
		SensorDtcStatus = TRUE;
	}

    return SensorDtcStatus;
}
#endif/*SRCTRCFG_AD_LINE_CLASS*/

#endif

/*EOF*/
