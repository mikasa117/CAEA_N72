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

static uint8 SysM_AlwaysTrue(void)  { return (uint8)TRUE;  }
/*******************************************************************************
|    Table Const Definition
|******************************************************************************/
const TsSysMCfg_h_SleepJudge CaSysM_SleepJudge_Table[SYSMCFG_SLEEP_MAX] =
{
    /*item                           flag                         func*/
    {SYSMCFG_SLEEP_APP_MODE,        (uint8)TRUE,              &SysM_AlwaysTrue},
    {SYSMCFG_SLEEP_EEP,             (uint8)TRUE,              &SysM_AlwaysTrue}
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
    gpio_write_pin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);//MCU_Hold_on_High();
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
    gpio_write_pin(GPIOB, GPIO_PIN_9, GPIO_PIN_CLEAR);//MCU_Hold_on_Low();
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
        gpio_write_pin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);//KL30_AD_EN_High();
    }
		else if(VeSysM_Record_Time < (20/SYSM_TASK_PERIOD))
    {
        gpio_write_pin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);//MIC_8V_EN_EN_High();
    }
    else if(VeSysM_Record_Time == (30/SYSM_TASK_PERIOD))
    {
				VeSysM_Status = SYSM_STATUS_POWERUP_END;
				printf("wakeup\r\n");
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
    if(VeSysM_Record_Time < 0x100u)
    {
        VeSysM_Record_Time ++;
    }
    
    /* Evaluate from highest to lowest to avoid early branches shadowing later stages */
		if(VeSysM_Record_Time >= (30/SYSM_TASK_PERIOD + 20u))
		{
			VeSysM_Status = SYSM_STATUS_POWERDOWN_END;
			//printf("sleep\r\n");
		}
    else if(VeSysM_Record_Time >= (20/SYSM_TASK_PERIOD + 20u))
    {
			gpio_write_pin(GPIOB, GPIO_PIN_0, GPIO_PIN_CLEAR);//MIC_8V_EN_EN_Low();
    }
    else if(VeSysM_Record_Time >= (10/SYSM_TASK_PERIOD + 20u))
    {
			gpio_write_pin(GPIOA, GPIO_PIN_4, GPIO_PIN_CLEAR);//KL30_AD_EN_Low();
    }
    else
    {
        ;
    }
}

/*EOF*/
