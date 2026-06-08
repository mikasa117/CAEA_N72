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
#include "STD_Lib.h"
#include "CanNm.h"
#include "CAEA_Types.h"
#include "Appl_Can_Callback.h"
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
static uint8 ApplCan_GetAppMsgKeepAliveStatus(void);

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

    TsSysM_h_EnSts.ucValidStatus = CAEA_TRUE;
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
    if(TRUE != BTRCTR_GetSysBatteryModeCStatus())
    { 
        SysM_EnStsJudge();
        SysM_StateMachine();
        SysM_SysPower();
        ApplCan_GetAppMsgKeepAliveStatus();
    }
    else
    {
        ;
    }
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
    if(e_u_enad < SYSM_EN_AD_INVALID)
    {
        TsSysM_h_EnSts.ucStatus = CAEA_FALSE;
    }
    else
    {
        TsSysM_h_EnSts.ucStatus = CAEA_TRUE;
    }
#elif (SYSM_EN_SOURCE == SYSM_EN_TYPE_IO)
    TsSysM_h_EnSts.ucStatus = SYSM_GET_EN_STS();
#endif

    //filt time bases on EN status
    if(CAEA_TRUE == TsSysM_h_EnSts.ucValidStatus)
    {
        (void)LIB_StatusFilter(&TsSysM_h_EnSts, SYSM_EN_INVALID_FILTCNT);
    }
    else
    {
        (void)LIB_StatusFilter(&TsSysM_h_EnSts, SYSM_EN_VALID_FILTCNT);
    }

#if(SYSM_NET_CONTROL_EN == CAEA_TRUE)
    if(CAEA_TRUE == SYSM_NET_SLEEP())
    {
#if (TEST_SOFTWARE_FUNC_EXHIBITION == TEST_SOFTWARE_FUNC_ENABLE)
                 
#else
        TsSysM_h_EnSts.ucValidStatus = CAEA_FALSE;
#endif
    }
    else
    {}
#endif

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
    uint8 e_u_sleepflag;
	Nm_StateType  pApplCan_u_NMSt;
	Nm_ModeType   pApplCan_u_NMMode;

    CanNm_GetState(0U,&pApplCan_u_NMSt,&pApplCan_u_NMMode);
    switch(TsSysM_h_Ctr.e_u_State)
    {
        case SYSM_STA_INIT:
            SysM_SysPowerOn();
            SysM_Set_SysPowerStatus(SYSM_STATUS_POWERUP);
            if(TsSysM_h_Ctr.e_u_InitTimerCnt < SYSM_TIME_INIT2RUN)
            {
                TsSysM_h_Ctr.e_u_InitTimerCnt++;
                if(((pApplCan_u_NMSt != NM_STATE_BUS_SLEEP) || (1u == ApplCan_GetAppMsgKeepAliveStatus())) && (CanApp_u_GetBusOffStaus() != TRUE))
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
            if(TsSysM_h_Ctr.e_u_TimerCnt < SYSM_TIME_PRESLEEP_LIMIT)
            {
                TsSysM_h_Ctr.e_u_TimerCnt++;
                if(((pApplCan_u_NMSt != NM_STATE_BUS_SLEEP) || (1u == ApplCan_GetAppMsgKeepAliveStatus())) && (CanApp_u_GetBusOffStaus() != TRUE))
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
            if((CAEA_FALSE == TsSysM_h_EnSts.ucValidStatus) || \
               ((NM_STATE_BUS_SLEEP == pApplCan_u_NMSt) && (0u == ApplCan_GetAppMsgKeepAliveStatus())))
            {
                TsSysM_h_Ctr.e_u_PreSleepTimerCnt = 0u;
                TsSysM_h_Ctr.e_u_State = SYSM_STA_PRESLEEP;

                if(CanApp_HoldWakeupMode_Flag() == 1)
                {
                    TsSysM_h_Ctr.e_u_State = SYSM_STA_RUN;
                }
                else
                {
                    ;
                }
            }
            else
            {;}

            break;

        case SYSM_STA_PRESLEEP:
            if(TsSysM_h_Ctr.e_u_PreSleepTimerCnt < SYSM_TIME_PRESLEEP_TIMEOUT)
            {
                TsSysM_h_Ctr.e_u_PreSleepTimerCnt++;
            }
            else
            {;}

            if(((pApplCan_u_NMSt != NM_STATE_BUS_SLEEP) || (1u == ApplCan_GetAppMsgKeepAliveStatus())) && (CanApp_u_GetBusOffStaus() != TRUE))
            {
                TsSysM_h_Ctr.e_u_State = SYSM_STA_RUN;
            }
            else 
            {;}
            
            //if all modules done or time up, sleep.
            e_u_sleepflag = SysM_SleepFlagJudge();
            if(((CAEA_TRUE == e_u_sleepflag) && (SYSM_TIME_PRESLEEP_LIMIT <= TsSysM_h_Ctr.e_u_PreSleepTimerCnt))\
            || (SYSM_TIME_PRESLEEP_TIMEOUT <= TsSysM_h_Ctr.e_u_PreSleepTimerCnt))
            {
				TsSysM_h_Ctr.e_u_PreSleepTimerCnt = 0u;
				TsSysM_h_Ctr.e_u_State = SYSM_STA_MCUCLOSE;
            }
            else
            {;}

            break;

		case SYSM_STA_MCUCLOSE:
            if(TsSysM_h_Ctr.e_u_PreSleepTimerCnt < SYSM_TIME_MCU_TIMEOUT)
            {
                TsSysM_h_Ctr.e_u_PreSleepTimerCnt++;
            }
            else
            {
                if(SYSM_STATUS_POWERDOWN_END == SysM_Get_SysPowerStatus())
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
            if(TsSysM_h_Ctr.e_u_TimerCnt < SYSM_TIME_SLEEP)
            {
                TsSysM_h_Ctr.e_u_TimerCnt++;
            }
            else
            {
                SYSM_MCU_RESET();
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
    uint8 e_u_return = CAEA_TRUE;
    uint8 e_u_index;
    uint8 e_u_flag;

    for(e_u_index = 0u; e_u_index < (uint8)SYSMCFG_SLEEP_MAX; e_u_index++)
    {
        e_u_flag = (uint8)(CaSysM_SleepJudge_Table[e_u_index].p_FlagGetFunc());
        if(e_u_flag != CaSysM_SleepJudge_Table[e_u_index].e_u_Flag)
        {
            e_u_return = CAEA_FALSE;
        }
        else
        {
            ;
        }
    }

    return e_u_return;
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

/*******************************************************************************
Name            : void SysM_ClrTimeCnt(void)
Syntax          : void SysM_ClrTimeCnt(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : Clear Time Counter
Call By         : SysM_MainFunction
|******************************************************************************/
void SysM_ClrTimeCnt(void)
{
	Nm_StateType  pApplCan_u_NMSt;
	Nm_ModeType   pApplCan_u_NMMode;

	CanNm_GetState(0U,&pApplCan_u_NMSt,&pApplCan_u_NMMode);

	if(NM_STATE_PREPARE_BUS_SLEEP == pApplCan_u_NMSt)
	{
		//CanNm_RstBusSleepTimer();
	}
    TsSysM_h_Ctr.e_u_TimerCnt = 0;
}

uint8 ApplCan_GetAppMsgKeepAliveStatus(void)
{
    /* Timing exceeds 200 times (10ms task=2s)  */
    if(ApplCan_u_AppMsgKeepAliveTimer < 200u)
    {
        ApplCan_u_AppMsgKeepAliveTimer++;
        return 1u;   /* valid, maintain wake-up */
    }
    return 0u;       /* invalid, can sleep */
}


/*EOF*/
