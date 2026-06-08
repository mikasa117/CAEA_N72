/*******************************************************************************
|  File Name:  PwmM_.c
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
| 2026-4-15    01.00.00     WCj       Creation
|
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "PwmM.h"
#include "PwmCtrl.h"
#include "PwmCtrl_Cfg.h"
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
Name              : PwmM_set_HF_12V_DutyCycle
Syntax            : void PwmM_set_HF_12V_DutyCycle(void)
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
void PwmM_set_HF_12V_DutyCycle(uint32 dutyCycle)
{
    PwmCtrl_SetDutyCycle(PWMCTRL_HF_12V, dutyCycle);
}
/*******************************************************************************
Name              : PwmM_set_HW_12V_DutyCycle
Syntax            : void PwmM_set_HW_12V_DutyCycle(void)
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
void PwmM_set_HW_12V_DutyCycle(uint32 dutyCycle)
{
    PwmCtrl_SetDutyCycle(PWMCTRL_HW_12V, dutyCycle);
}
/*******************************************************************************
Name              : PwmM_set_FAN_12V_DutyCycle
Syntax            : void PwmM_set_FAN_12V_DutyCycle(void)
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
void PwmM_set_FAN_12V_DutyCycle(uint32 dutyCycle)
{
    PwmCtrl_SetDutyCycle(PWMCTRL_FAN_12V, dutyCycle);
}

/*******************************************************************************
Name              : PwmM_set_MCU_ALED_DutyCycle
Syntax            : void PwmM_set_MCU_ALED_DutyCycle(void)
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
void PwmM_set_MCU_ALED_DutyCycle(uint32 dutyCycle)
{
    PwmCtrl_SetDutyCycle(PWMCTRL_MCU_ALED, dutyCycle);
}
/*******************************************************************************
Name              : PwmM_set_MCU_WLED_DutyCycle
Syntax            : void PwmM_set_MCU_WLED_DutyCycle(void)
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
void PwmM_set_MCU_WLED_DutyCycle(uint32 dutyCycle)
{
    PwmCtrl_SetDutyCycle(PWMCTRL_MCU_WLED, dutyCycle);
}
/*******************************************************************************
Name              : PwmM_set_MCU_UVCLED_DutyCycle
Syntax            : void PwmM_set_MCU_UVCLED_DutyCycle(void)
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
void PwmM_set_MCU_UVCLED_DutyCycle(uint32 dutyCycle)
{
    PwmCtrl_SetDutyCycle(PWMCTRL_MCU_UVCLED, dutyCycle);
}


/*EOF*/
