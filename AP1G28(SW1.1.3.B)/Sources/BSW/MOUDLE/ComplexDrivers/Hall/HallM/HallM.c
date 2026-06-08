/*******************************************************************************
|  File Name:  HallM_.c
|  Description:  Implementation of the Battery voltage Management
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
| 2025-11-29    01.00.00     WCj       Creation
|
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "HallM.h"
#include "STD_DioIf.h"
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
Name              : HALL_M_InitMemory
Syntax            : void HALL_M_InitMemory(void)
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
void HALL_M_InitMemory(void)
{
    HALL_CTR_InitMemory();
}

/*******************************************************************************
Name              : HALL_M_InitKamMemory
Syntax            : void HALL_M_InitKamMemory( void )
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
void HALL_M_InitKamMemory( void )
{
    HALL_CTR_InitKamMemory() ;
}


/*******************************************************************************
Name              : HALL_M_MainFunction
Syntax            : void HALL_M_MainFunction( void )
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
void HALL_M_MainFunction(void)
{
    HALL_CTR_ModeFunction();

}

/*******************************************************************************
Name              : HALL_M_GetHALL_SwitchStatus
Syntax            : uint8 HALL_M_GetHALL_SwitchStatus(void)
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
uint8 HALL_M_GetHALL_SwitchStatus(void)
{
    uint8_t Rtn = 0;
	Rtn = DioIf_ReadChannel(HW_DIO_HALL_MCU_PWM);
	return Rtn;
}

/*EOF*/
