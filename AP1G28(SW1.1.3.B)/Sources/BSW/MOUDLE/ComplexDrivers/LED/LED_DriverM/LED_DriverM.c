/*******************************************************************************
|  File Name:  LED_DriverM.c
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
#include "HwIO.h"
//#include "STD_DioIf.h"
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
Name              : LED_DRV_M_EN_On
Syntax            : void LED_DRV_M_EN_On(void)
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

void LED_DRV_M_EN_On(void)
{
    HwIO_MCU_LEDDRV_EN_ON();
}

/*******************************************************************************
Name              : LED_DRV_M_EN_Off
Syntax            : void LED_DRV_M_EN_Off(void)
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

void LED_DRV_M_EN_Off(void)
{
    HwIO_MCU_LEDDRV_EN_OFF();
}
/*******************************************************************************
Name              : LED_DRV_M_InitMemory
Syntax            : void LED_DRV_M_InitMemory(void)
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
void LED_DRV_M_InitMemory(void)
{
    LED_DRV_CTR_InitMemory();
}

/*******************************************************************************
Name              : LED_DRV_M_5msMainFunction
Syntax            : void LED_DRV_M_5msMainFunction( void )
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      :
Description       :
Call By           :
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
void LED_DRV_M_5msMainFunction(void)
{
    LED_DRV_CTR_FaultDetection();
}

/*******************************************************************************
Name              : LED_DRV_M_GetFaultMode
Syntax            : uint8 LED_DRV_M_GetFaultMode(void)
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      :
Description       :
Call By           :
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
uint8 LED_DRV_M_GetFaultMode(void)
{
    uint8 rtn = 0;
    rtn = (uint8)LED_DRV_CTR_GetFaultMode();
    return rtn;
}

/*EOF*/
