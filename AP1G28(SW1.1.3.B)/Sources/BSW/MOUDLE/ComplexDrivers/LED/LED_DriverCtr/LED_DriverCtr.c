/*******************************************************************************
|  File Name:  LED_DriverCtr.c
|  Description:  
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| WCj           Chaojian Wang         CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2026-04-18    01.00.00     WCj       Creation
|
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "LED_DriverCtr.h"


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
static LedFaultModeEnum TeLEDCTR_e_SysLedMode;


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
Name              : LED_DRV_CTR_InitMemory
Syntax            : void LED_DRV_CTR_InitMemory(void)
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      : None
Description       :
Call By           : 
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/

void LED_DRV_CTR_InitMemory(void)
{
    TeLEDCTR_e_SysLedMode = LED_FAULT_FREE;
}

/*******************************************************************************
Name              : LED_DRV_CTR_InitMemory
Syntax            : void LED_DRV_CTR_InitMemory(void)
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      : None
Description       :
Call By           : 
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/

void LED_DRV_CTR_FaultDetection(void)
{
    uint8 fault1 = 1u;
    uint8 fault2 = 1u;
    fault1 = LEDCTR_GetFault1Value();
    fault2 = LEDCTR_GetFault2Value();
    if (fault1 == 1 && fault2 == 1)
    {
        TeLEDCTR_e_SysLedMode = LED_FAULT_FREE;
    }
    else if (fault1 == 0 && fault2 == 0)
    {
        TeLEDCTR_e_SysLedMode = LED_SHORT_FUALT;
    }
    else if (fault1 == 0 && fault2 != 0)
    {
        TeLEDCTR_e_SysLedMode = LED_NOT_SHORT_FAULT;
    }
    else
    {
    }
}
/*******************************************************************************
Name              : LED_DRV_CTR_GetFaultMode
Syntax            : void LED_DRV_CTR_GetFaultMode(void)
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      : None
Description       :
Call By           :
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
LedFaultModeEnum LED_DRV_CTR_GetFaultMode(void)
{
    return TeLEDCTR_e_SysLedMode;
}

/*EOF*/
