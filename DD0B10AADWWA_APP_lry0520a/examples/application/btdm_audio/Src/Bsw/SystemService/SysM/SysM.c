/*******************************************************************************
|  File Name:  SysM.c
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
#include "SysM.h"
#include "Rte_BtrM.h"
#include "BtrM_Cfg.h"
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
|    STATIC local KAM variables Declaration
|******************************************************************************/

/*******************************************************************************
|    STATIC local variables Declaration
|******************************************************************************/

static TsSysM_h_CtrStr TsSysM_h_Ctr;
static LibFilterStruct TsSysM_h_EnSts;

/*******************************************************************************
|    Table Const Definition
|******************************************************************************/

/*******************************************************************************
|    STATIC Local Functions Declaration
|******************************************************************************/
static void SysM_EnStsJudge(void);
static void SysM_StateMachine(void);
static uint8 SysM_SleepFlagJudge(void);
static uint8 SysM_SleepState(void);
static uint8 SysM_CModeSleepJudge(void);
/*******************************************************************************
|    Function Source Code
|******************************************************************************/

/*******************************************************************************
Name            : SysM_InitMemory
Syntax          : void SysM_InitMemory(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : Initialize Ram Data
Call By         : EcuM
|******************************************************************************/
void SysM_InitMemory(void)
{	
    LIB_SetMemory((uint8 *)(&TsSysM_h_Ctr), 0u, (uint16)(sizeof(TsSysM_h_Ctr)/sizeof(uint8)));
    LIB_SetMemory((uint8 *)(&TsSysM_h_EnSts), 0u, (uint16)(sizeof(TsSysM_h_EnSts)/sizeof(uint8)));

    TsSysM_h_EnSts.ucValidStatus = TRUE;
}

/*******************************************************************************
Name            : SysM_MainFunction
Syntax          : void SysM_MainFunction(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : main function
Call By         : Task
|******************************************************************************/
void SysM_MainFunction(void)
{   
	if(0u == SysM_CModeSleepJudge())
	{
    SysM_EnStsJudge();
    SysM_StateMachine();
    SysM_SysPower();
	}
	else
	{
		;
	}
}

/*******************************************************************************
Name            : SysM_CModeSleepJudge
Syntax          : void SysM_CModeSleepJudge(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : En check
Call By         : SysM_MainFunction
|******************************************************************************/
static uint8 SysM_CModeSleepJudge(void)
{
	uint8 ucBatMode = 0;
	uint8 uCModeSleepFlag = 0;
	static uint8 uCnt = 0;
	
  Rte_Read_BtrM_BtrM_VoltageMode(&ucBatMode);
	
	if(STD_BTRM_MODE_C == ucBatMode)
	{
		if(uCnt >= 5u)
		{
			uCModeSleepFlag = 1;
			uCnt = 0;
		}
		else
		{
			uCnt++;
		}
	}
	else
	{
		//uCModeSleepFlag = 0u;
		uCnt = 0;
	}
	
	if(1u == uCModeSleepFlag)
	{
		SysM_SysPowerOff();
		
		if(STD_BTRM_MODE_C != ucBatMode)
		{
			uCModeSleepFlag = 0;
			//SYSM_MCU_RESET();
		}
		else
		{
			;
		}
	}
	else
	{
		;
	}
	
	return uCModeSleepFlag;
}
/*******************************************************************************
Name            : SysM_EnStsJudge
Syntax          : void SysM_EnStsJudge(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : En check
Call By         : SysM_MainFunction
|******************************************************************************/
static void SysM_EnStsJudge(void)
{	
#if (SYSM_EN_SOURCE == SYSM_EN_TYPE_AD)
    uint16 e_u_enad = SYSM_GET_EN_ADC();
    if(TRUE == TsSysM_h_EnSts.ucValidStatus)
    {
        if (e_u_enad <= SYSM_EN_AD_INVALID)
        {
            TsSysM_h_EnSts.ucStatus = Sys_Allow_Sleep;
						TsSysM_h_EnSts.ucValidStatus = FALSE;
        }
        else
        {
            TsSysM_h_EnSts.ucStatus = Sys_NotAllow_Sleep; 
						TsSysM_h_EnSts.ucValidStatus = TRUE;
        }
    }
    else
    {
        if (e_u_enad >= SYSM_EN_AD_VALID)
        {
            TsSysM_h_EnSts.ucStatus = Sys_NotAllow_Sleep;
						TsSysM_h_EnSts.ucValidStatus = TRUE;
        }
        else
        {
            TsSysM_h_EnSts.ucStatus = Sys_Allow_Sleep; 
						TsSysM_h_EnSts.ucValidStatus = FALSE;
        }
    }
#elif (SYSM_EN_SOURCE == SYSM_EN_TYPE_IO)
    TsSysM_h_EnSts.ucStatus = SYSM_GET_EN_STS();
#endif

    //filt time bases on EN status
    if(TRUE == TsSysM_h_EnSts.ucValidStatus)
    {
        (void)LIB_StatusFilter(&TsSysM_h_EnSts, SYSM_EN_INVALID_FILTCNT);
    }
    else
    {
        (void)LIB_StatusFilter(&TsSysM_h_EnSts, SYSM_EN_VALID_FILTCNT);
    }

#if(SYSM_NET_CONTROL_EN == TRUE)
    if(TRUE == SYSM_NET_SLEEP())
    {
#if (TEST_SOFTWARE_FUNC_EXHIBITION == TEST_SOFTWARE_FUNC_ENABLE)
                 
#else
        TsSysM_h_EnSts.ucValidStatus = FALSE;
#endif
    }
    else
    {}
#endif
}
/*******************************************************************************
Name            : SysM_SleepState
Syntax          : static void SysM_SleepState(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : Sleep State 
Call By         : SysM_StateMachine
|******************************************************************************/
static uint8 SysM_SleepState(void) 
{
	return (uint8)TsSysM_h_EnSts.ucStatus; 
}

/*******************************************************************************
Name            : SysM_StateMachine
Syntax          : static void SysM_StateMachine(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : State Machine
Call By         : SysM_MainFunction
|******************************************************************************/
static void SysM_StateMachine(void) 
{	
  switch (TsSysM_h_Ctr.e_u_State) 
  {
		case SYSM_STA_INIT:
			SysM_SysPowerOn();
			SysM_Set_SysPowerStatus(SYSM_STATUS_POWERUP);
			if(TsSysM_h_Ctr.e_u_InitTimerCnt < SYSM_TIME_INIT2RUN) 
			{
				TsSysM_h_Ctr.e_u_InitTimerCnt++;
				if (SYSM_EN_AD_VALID <= SYSM_GET_EN_ADC())
				{
					TsSysM_h_Ctr.e_u_InitTimerCnt = 0u;
					TsSysM_h_Ctr.e_u_State = SYSM_STA_RUN;
				} 
				else 
				{;}
			} 
			else 
			{
				TsSysM_h_Ctr.e_u_InitTimerCnt = 0u;
				TsSysM_h_Ctr.e_u_State = SYSM_STA_READYSLEEP;
			}

			break;

		case SYSM_STA_READYSLEEP:
			if (TsSysM_h_Ctr.e_u_TimerCnt < SYSM_TIME_PRESLEEP_LIMIT) 
			{
				TsSysM_h_Ctr.e_u_TimerCnt++;
				if(SYSM_EN_AD_VALID <= SYSM_GET_EN_ADC())
				{
				TsSysM_h_Ctr.e_u_State = SYSM_STA_RUN;
				} 
				else
				{;}
			} 
			else 
			{
				TsSysM_h_Ctr.e_u_TimerCnt = 0u;
				TsSysM_h_Ctr.e_u_PreSleepTimerCnt = 0u;
				TsSysM_h_Ctr.e_u_State = SYSM_STA_PRESLEEP;
			}

			break;

		case SYSM_STA_RUN:
			if (FALSE == TsSysM_h_EnSts.ucValidStatus) 
			{
				TsSysM_h_Ctr.e_u_PreSleepTimerCnt = 0u;
				TsSysM_h_Ctr.e_u_State = SYSM_STA_PRESLEEP;
			} 
			else 
			{;}

			break;

		case SYSM_STA_PRESLEEP:
			if (TsSysM_h_Ctr.e_u_PreSleepTimerCnt < SYSM_TIME_PRESLEEP_TIMEOUT) 
			{
				TsSysM_h_Ctr.e_u_PreSleepTimerCnt++;
			} 
			else 
			{
				;
			}

			if (Sys_NotAllow_Sleep == SysM_SleepState())
			{
				TsSysM_h_Ctr.e_u_State = SYSM_STA_RUN;
			} 
			else 
			{;}

			// if all modules done or time up, sleep.
			if (((TRUE == SysM_SleepFlagJudge()) &&(SYSM_TIME_PRESLEEP_LIMIT <= TsSysM_h_Ctr.e_u_PreSleepTimerCnt)) || \
			(SYSM_TIME_PRESLEEP_TIMEOUT <= TsSysM_h_Ctr.e_u_PreSleepTimerCnt)) 
			{
				TsSysM_h_Ctr.e_u_PreSleepTimerCnt = 0u;
				TsSysM_h_Ctr.e_u_State = SYSM_STA_MCUCLOSE;
			} 
			else 
			{;}

			break;

		case SYSM_STA_MCUCLOSE:
			if (TsSysM_h_Ctr.e_u_PreSleepTimerCnt < SYSM_TIME_MCU_TIMEOUT) 
			{
				TsSysM_h_Ctr.e_u_PreSleepTimerCnt++;
			} 
			else 
			{
				if (SYSM_STATUS_POWERDOWN_END == SysM_Get_SysPowerStatus()) 
				{
					SysM_SysPowerOff();
					TsSysM_h_Ctr.e_u_PreSleepTimerCnt = 0u;
					TsSysM_h_Ctr.e_u_State = SYSM_STA_POWEROFF;
				} 
				else 
				{;}
			}

			break;

		case SYSM_STA_POWEROFF:
			if (TsSysM_h_Ctr.e_u_TimerCnt < SYSM_TIME_SLEEP) 
			{
				TsSysM_h_Ctr.e_u_TimerCnt++;
			} 
			else 
			{
				if(SYSM_GET_EN_ADC() < SYSM_EN_AD_VALID)
				{
					__WFI();
				}
				else
				{
					SYSM_MCU_RESET();
				}
			}

			break;

		default:
			break;
  }
}

/*******************************************************************************
Name            : SysM_SleepFlagJudge
Syntax          : uint8 SysM_SleepFlagJudge(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : 0-1u
Description     : sleep judge
Call By         : SysM_StateMachine
|******************************************************************************/
static uint8 SysM_SleepFlagJudge(void) 
{
#if 0
    uint8 e_u_return = TRUE;
    uint8 e_u_index;
    uint8 e_u_flag;

    for(e_u_index = 0u; e_u_index < (uint8)SYSMCFG_SLEEP_MAX; e_u_index++)
    {
        e_u_flag = (uint8)(CaSysM_SleepJudge_Table[e_u_index].p_FlagGetFunc());
        if(e_u_flag != CaSysM_SleepJudge_Table[e_u_index].e_u_Flag)
        {
            e_u_return = FALSE;
        }
        else
        {
            ;
        }
    }

    return e_u_return;
#endif

  return TRUE;
}

/*******************************************************************************
Name            : SysM_GetSysSTA
Syntax          : uint8 SysM_GetSysSTA(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : uint8
Description     : return state
Call By         : other modules
|******************************************************************************/
uint8 SysM_GetSysSTA(void) 
{ 
	return (uint8)TsSysM_h_Ctr.e_u_State; 
}

/*EOF*/
