/*******************************************************************************
|  File Name:  STD_SrM.c
|  Description:  Implementation of the Sensor Management
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

#include "STD_SrM.h"
/*#include "CpidServ.h"*/

#if (SRM_ENABLE == SRM_EN_CLASS)
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
|    Static local KAM variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Table Const Definition
|******************************************************************************/

/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/

/*******************************************************************************
Name			: SRM_InitMemory
Syntax			: void SRM_InitMemory( void )
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None					:-
Parameters(out) : None					:-
Return value	: None					:-
Description		: Initializes the module Ram memory.
Call By			: EcuM
|******************************************************************************/
void SRM_InitMemory( void )
{
#if (SRM_TYPE_AD_TABLE_CLASS == SRM_ENABLE)	
    SRADCTR_InitMemory();
#endif
#if (SRM_TYPE_PWM_CLASS == SRM_ENABLE)
    SRPWMCTR_InitMemory();
#endif
#if (SRM_CPID_EN_CLASS == SRCFG_ENABLE)
    SRCPID_InitMemory();
#endif
}

/*******************************************************************************
Name			: SRM_MainFunction
Syntax			: void SRM_MainFunction( void )
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None					:-
Parameters(out) : None					:-
Return value	: None					:-
Description		: the module master function.
Call By			: TASK
|******************************************************************************/
void SRM_5msMainFunction( void )
{
    uint8 TempBtrModeAStatus = FALSE;

    TempBtrModeAStatus = SRCFG_GetBatteryModeAStatus();
    if ((uint8)1u == TempBtrModeAStatus)
    {
#if (SRM_TYPE_AD_TABLE_CLASS == SRM_ENABLE)		
        SRADCTR_ConvMainFunction();
#endif
    }
    else
    {}
}

void SRM_10msMainFunction( void )
{
    uint8 TempBtrModeAStatus = FALSE;

    TempBtrModeAStatus = SRCFG_GetBatteryModeAStatus();
    if ((uint8)1u == TempBtrModeAStatus)
    {
#if (SRM_TYPE_PWM_CLASS == SRM_ENABLE)
        SRPWMCTR_MainFunction();
#endif
#if (SRM_TYPE_AD_TABLE_CLASS == SRM_ENABLE)
        SRADCTR_DiagMainFunction();
#endif
    }
    else
    {}
}

sint16 SRM_GetValidValue( SRCFG_CH_Enum AppChannel )
{
	uint8  TempCtrChan	= 0u;
    sint16 SensorValidValue = 0x0000;

    if ( SRCFG_CH_MAX_NUM > AppChannel )
    {
#if (SRM_CPID_EN_CLASS == SRCFG_ENABLE)

        if ( (uint8)SRCFG_ENABLE == SRCPID_GetEnableStatus( AppChannel ) )
        {
            SensorValidValue = (sint16)SRCPID_GetValidValue( AppChannel );
        }
        else
#endif
        {
/* polyspace<DEFECT:USELESS_WRITE:Low:Justified> This is a pre-compiled problem. */
        	TempCtrChan = stSrMChanCfgArray[AppChannel].SensorChan;
			SensorValidValue = stSrMChanCfgArray[AppChannel].GetValidValue(TempCtrChan);/*PRQA S 3671*/
        }
    }
/* polyspace<DEFECT:NON_INIT_VAR:Low:Justified> This is a pre-compiled problem. */
    return SensorValidValue;
}

/*1= not error    0 = short to GND or  short to battery */
uint8 SRM_GetValidStatus( SRCFG_CH_Enum AppChannel )
{
	uint8 TempCtrChan	= 0u;
	uint8 ValidStatus = 0u;

	if ( SRCFG_CH_MAX_NUM > AppChannel )
    {
/* polyspace<DEFECT:USELESS_WRITE:Low:Justified> This is a pre-compiled problem. */
		TempCtrChan = stSrMChanCfgArray[AppChannel].SensorChan;
		ValidStatus = stSrMChanCfgArray[AppChannel].GetValidStatus(TempCtrChan);/*PRQA S 3671*/
	}
/* polyspace<DEFECT:NON_INIT_VAR:Low:Justified> This is a pre-compiled problem. */
	return ValidStatus;
}
#endif


/*EOF*/
