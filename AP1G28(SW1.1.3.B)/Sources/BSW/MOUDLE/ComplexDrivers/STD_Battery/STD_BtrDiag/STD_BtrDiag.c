/*******************************************************************************
|  File Name:  STD_BtrDtc.c
|  Description:  Implementation of the Battery voltage Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| LSG           SiGuang Li             CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2017-07-26    01.00.00     LSG       Creation
|
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_BtrDiag.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define BTRDIAG_ERROR_NONE			(0x00u)
#define BTRDIAG_ERROR_LOW_VOL		(0x01u)
#define BTRDIAG_ERROR_HIGH_VOL		(0x02u)
/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef struct
{
    LibFilterStruct stVolDtc;

} BtrDiagStruct;
/*******************************************************************************
|    Global variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/
#define STD_BTRDIAG_START_SEC_VAR_RAM
#include "STD_MemMap.h"

static BtrDiagStruct BTRDIAG_CODE_RAM stBtrDiag;

#define STD_BTRDIAG_STOP_SEC_VAR_RAM
#include "STD_MemMap.h"
/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/

/*******************************************************************************
|    Extern variables and functions declaration
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/

/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/

/*******************************************************************************
|    Extern variables and functions declaration
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/


/*******************************************************************************
Name              : BTRDTC_InitMemory
Syntax            : void BTRDTC_InitMemory(void)
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      : None
Description       :
Call By           : STD_BtrM.c
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
void BTRDIAG_InitMemory(void)
{
    LIB_SetMemory( (uint8 *)&stBtrDiag, 0u, sizeof(stBtrDiag) / sizeof(uint8));/*PRQA S 0310*/
}


/*******************************************************************************
Name              : BTRDTC_MainFunction
Syntax            : void BTRDTC_MainFunction(void)
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      : None
Description       :
Call By           : STD_BtrM.c
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
void BTRDIAG_MainFunction(void)
{
    
    uint16 TempatteryValidValue = BTRDIAG_GetBatteryValidValue();
    if(TempatteryValidValue < (uint16)BTRDIAG_THRESHOLD_LOW_BATTERY_IN)
    {
        stBtrDiag.stVolDtc.ucStatus = BTRDIAG_ERROR_LOW_VOL;
    }
    else if(TempatteryValidValue > (uint16)BTRDIAG_THRESHOLD_HIGH_BATTERY_IN)
    {
        stBtrDiag.stVolDtc.ucStatus = BTRDIAG_ERROR_HIGH_VOL;
    }
    else if((TempatteryValidValue >= BTRDIAG_THRESHOLD_LOW_BATTERY_OUT)
		&& (TempatteryValidValue <= BTRDIAG_THRESHOLD_HIGH_BATTERY_OUT))
    {
        stBtrDiag.stVolDtc.ucStatus  = BTRDIAG_ERROR_NONE;
    }
	else
	{}

    if((uint8)TRUE == LIB_StatusFilter(&(stBtrDiag.stVolDtc), BTRDIAG_VOLTAGE_FILTER_TIME))
    {
    }
}

/*******************************************************************************
Name              : BTRDTC_GetLowVolDtcStatus
Syntax            : uint8 BTRDTC_GetLowVolDtcStatus(void)
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      : None
Description       :
Call By           : Dtc.c
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
uint8 BTRDIAG_GetLowVolDtcStatus(void)
{
    uint8 TempLowVolDtcStatus=0u;
    if( (uint8)BTRDIAG_ERROR_LOW_VOL == stBtrDiag.stVolDtc.ucValidStatus )
	{
		TempLowVolDtcStatus=1u;
	}
	else
	{
		TempLowVolDtcStatus=0u;
	}
    return (TempLowVolDtcStatus);
}

/*******************************************************************************
Name              : BTRDTC_GetHighVolDtcStatus
Syntax            : uint8 BTRDTC_GetHighVolDtcStatus(void)
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      : None
Description       :
Call By           : Dtc.c
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
uint8 BTRDIAG_GetHighVolDtcStatus(void)
{
    uint8 TempHighVolDtcStatus=0u;
    if( (uint8)BTRDIAG_ERROR_HIGH_VOL == stBtrDiag.stVolDtc.ucValidStatus )
	{
		TempHighVolDtcStatus=1u;
	}
	else
	{
		TempHighVolDtcStatus=0u;
	}
    return (TempHighVolDtcStatus);
}


/*EOF*/

