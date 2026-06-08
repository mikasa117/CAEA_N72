/*******************************************************************************
|  File Name:  PwmCtrl.c
|  Description:  Implementation of the PwmCtrl Config Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
|               wcj                    CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 2025-11-09    1.0.0        wcj        Create 
| 
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
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
|    Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Global Variable with extern linkage
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/

/******************************************************************************
|    Static Function Prototypes
|******************************************************************************/

/*******************************************************************************
| Function name     : void NtcCtrl_Init(void)
| Called by         : void Ecum_InitMemery(void)
| Preconditions     : -
| Input Parameters  : -
| Return Value      : -
| Description       : Initialize NtcCtrl module
| History
| <No.>   <author>    <time>      <description>
| 1       wcj         251109      first version        
|******************************************************************************/
void PwmCtrl_SetDutyCycle(PWMCTRL_INTERFACE_Type pwmctrl_interface_type_s, uint32 dutyCycle)
{
    PwmCtrl_Cfg_SetDutyCycle(pwmctrl_interface_type_s, dutyCycle);
}

/*******************************************************************************
| Function name     : void NtcCtrl_Init(void)
| Called by         : void Ecum_InitMemery(void)
| Preconditions     : -
| Input Parameters  : -
| Return Value      : -
| Description       : Initialize NtcCtrl module
| History
| <No.>   <author>    <time>      <description>
| 1       wcj         251109      first version        
|******************************************************************************/
void PwmCtrl_DRV_SetLdok(uint32 instance)
{
    EtmrIf_DRV_SetLdok(instance);
}
/*******************************************************************************
| Function name     : void PwmCtrl_DRV_ClearLdok(void)
| Called by         : void PwmCtrl_DRV_ClearLdok(void)
| Preconditions     : -
| Input Parameters  : -
| Return Value      : -
| Description       : Initialize NtcCtrl module
| History
| <No.>   <author>    <time>      <description>
| 1       wcj         251109      first version        
|******************************************************************************/
void PwmCtrl_DRV_ClearLdok(uint32 instance)
{
    EtmrIf_DRV_ClearLdok(instance);
}
/*EOF*/
