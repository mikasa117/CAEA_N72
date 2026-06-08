/*******************************************************************************
|  File Name:  SysM_Cfg.c
|  Description:  Implementation of the System Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| CHP           Chen Haopeng           CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 2021-05-18    00.00.01     CHP       Creation
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "SysM_Cfg.h"
#include "Etmr_If.h"
#include "STD_AdcIf.h"
#include "STD_WdgIf.h"
#include "sdk_project_config.h"
#include "Fridge_Basic_Control.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
uint16  VeSysM_Record_Time;
uint16  VeSysM_Status;
/*******************************************************************************
|    STATIC local KAM variables Declaration
|******************************************************************************/

/*******************************************************************************
|    STATIC local variables Declaration
|******************************************************************************/
static void SysM_SysPowerUp(void);
static void SysM_SysPowerDown(void);
/*******************************************************************************
|    Table Const Definition
|******************************************************************************/
const TsSysMCfg_h_SleepJudge CaSysM_SleepJudge_Table[SYSMCFG_SLEEP_MAX] =
{
    /*item                           flag                                   func*/
    {SYSMCFG_SLEEP_APP_MODE,        (uint8)TRUE,                            &FridgeMode_SleepContitionCheck},
    {SYSMCFG_SLEEP_EEP,             (uint8)TRUE,                            &EEPM_GetSleepRequestStatus}
};
/*******************************************************************************
|    STATIC Local Functions Declaration
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/

/*******************************************************************************
Name            : SysM_SysPowerOn
Syntax          : void SysM_SysPowerOn(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : set some IO
Call By         : SysM_StateMachine
|******************************************************************************/
void SysM_SysPowerOn(void)
{
    HwIO_MCU_Hold_on_EN();
}

/*******************************************************************************
Name            : SysM_SysPowerOff
Syntax          : void SysM_SysPowerOff(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : set some IO
Call By         : SysM_StateMachine
|******************************************************************************/
void SysM_SysPowerOff(void)
{
    HwIO_MCU_Hold_on_DEN();
}

/*******************************************************************************
Name            : SysM_Set_SysPowerStatus
Syntax          : void SysM_SysPowerOff(uint8 e_u_Status)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : System Power Status
Description     : Return System Power Status
Call By         : SysM_StateMachine
|******************************************************************************/
void SysM_Set_SysPowerStatus(uint8 e_u_Status)
{
    VeSysM_Status = e_u_Status;
}

/*******************************************************************************
Name            : SysM_Get_SysPowerStatus
Syntax          : uint8 SysM_Get_SysPowerStatus(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : System Power Status
Description     : Return System Power Status
Call By         : SysM_StateMachine
|******************************************************************************/
uint8 SysM_Get_SysPowerStatus(void)
{
    return VeSysM_Status;
}

/*******************************************************************************
Name            : SysM_SysPower
Syntax          : void SysM_SysPower(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : System Power Control
Call By         : SysM_StateMachine
|******************************************************************************/
void SysM_SysPower(void)
{
    uint8 e_u_SysMmode;
    
    e_u_SysMmode = (uint8)SysM_GetSysSTA();
    
    if(e_u_SysMmode == SYSM_STA_MCUCLOSE)
    {
        SysM_SysPowerDown();
    }
    else if(VeSysM_Status == SYSM_STATUS_POWERUP )
    {
        SysM_SysPowerUp();
    }
    else
    {
        ;
    }
}

/*******************************************************************************
Name            : SysM_SysMCUDeinit
Syntax          : void SysM_SysMCUDeinit(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : System Deinit
Call By         : SysM_SysPowerDown
|******************************************************************************/
void SysM_MCUDeinit(void)
{
    EtmrIf_DeInit();
    AdcIf_DeInit();
    WdgIf_DeInit();
    TMU_DRV_Deinit(0);
    pTMR_DRV_Deinit(0);
    FLASH_DRV_Deinit(0);
    FLEXCAN_DRV_Deinit(1);
    eTMR_DRV_DeinitPwm(0);
    eTMR_DRV_DeinitPwm(2);
    eTMR_DRV_DeinitPwm(3);
    eTMR_DRV_Deinit(0);
    eTMR_DRV_Deinit(2);
    eTMR_DRV_Deinit(3);
    DMA_DRV_Deinit();
    EtmrIf_DRV_ClearLdok(ETMR_INST_2);
    EtmrIf_DRV_ClearLdok(ETMR_INST_3);
}

/*******************************************************************************
Name            : SysM_SysPowerUp
Syntax          : void SysM_SysPowerUp(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : System Power Up Control
Call By         : SysM_StateMachine
|******************************************************************************/
static void SysM_SysPowerUp(void)
{
    if(VeSysM_Record_Time < 0x100u)
    {
        VeSysM_Record_Time ++;
    }
    
    if(VeSysM_Record_Time < (10/SYSM_TASK_PERIOD))
    {
        HwIO_MCU_LIN_SLPn_ON();
        HwIO_HALL_5V_EN_ON();
    }
    else if(VeSysM_Record_Time == (15/SYSM_TASK_PERIOD))
    {
        //HwIO_MCU_HW_12V_EN_High();
        //HwIO_MCU_HF_12V_EN_High();
        HwIO_MCU_LEDDRV_EN_ON();
    }
    else if(VeSysM_Record_Time == (20/SYSM_TASK_PERIOD))
    {
        //HwIO_COMP_12V_EN_ON();
        //HwIO_VCC_48V_EN_High();
    }
    else if(VeSysM_Record_Time == (30/SYSM_TASK_PERIOD))
    {

        //HwIO_MCU_PD_SLPn_Enable();
        VeSysM_Status = SYSM_STATUS_POWERUP_END;
    }
    else
    {
        ;
    }
}

/*******************************************************************************
Name            : SysM_SysPowerDown
Syntax          : void SysM_SysPowerDown(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : System Power Down Control
Call By         : SysM_StateMachine
|******************************************************************************/
static void SysM_SysPowerDown(void)
{
    if(VeSysM_Record_Time < 0x200u)
    {
        VeSysM_Record_Time ++;
    }
    
    /* Evaluate from highest to lowest to avoid early branches shadowing later stages */
    if(VeSysM_Record_Time >= (50/SYSM_TASK_PERIOD + 256u))
    {
        HwIO_MCU_LIN_SLPn_OFF();
        HwIO_MCU_CAN_STBn_Low();
        HwIO_MCU_CAN_EN_ON();
        VeSysM_Status = SYSM_STATUS_POWERDOWN_END;
    }
    else if(VeSysM_Record_Time >= (40/SYSM_TASK_PERIOD + 256u))
    {
        HwIO_HALL_5V_EN_OFF();
    }
    else if(VeSysM_Record_Time >= (30/SYSM_TASK_PERIOD + 256u))
    {
        HwIO_MCU_LEDDRV_EN_OFF();
        //HwIO_MCU_HF_12V_EN_Low();
        //HwIO_MCU_HW_12V_EN_Low();
    }
    else if(VeSysM_Record_Time >= (20/SYSM_TASK_PERIOD + 256u))
    {
        HwIO_COMP_12V_EN_OFF();
    }
    else if(VeSysM_Record_Time >= (10/SYSM_TASK_PERIOD + 256u))
    {
        HwIO_VCC_46V_EN_OFF();
    }
    else if(VeSysM_Record_Time >= (5/SYSM_TASK_PERIOD + 256u))
    {
        HwIO_MCU_PD_SLPn_Disable();
    }
    else
    {
        ;
    }
}

/*EOF*/
