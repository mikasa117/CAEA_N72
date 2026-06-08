/*******************************************************************************
|  File Name:  Task.c
|  Description:  Implementation of the UartIf Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| zy           yuanzheng               CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2019-09-04    01.00.00     zy       Creation
|
|******************************************************************************/


/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Task.h"
//#include "Platform_Types.h"
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
|    STATIC local KAM variables Declaration
|******************************************************************************/

/*******************************************************************************
|    STATIC local variables Declaration
|******************************************************************************/
static volatile uint8  SeTask_u_Tick;
static volatile uint8  SeTask_u_5msATaskCnt;
static volatile uint8  SeTask_u_5msBTaskCnt;
static volatile uint8  SeTask_u_5msCTaskCnt;
static volatile uint8  SeTask_u_5msDTaskCnt;
static volatile uint8  SeTask_u_1msTaskCnt;


static uint8  SeTask_u_5msC_Extend;
static uint8  SeTask_u_5msD_Extend;
static uint8  SeTask_u_10msC_Extend;
static uint8  SeTask_u_10msD_Extend;
/*******************************************************************************
Name			: void Task_InitMemory(void)
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: -
Call By			: ECUCFG.C
|******************************************************************************/
void Task_InitMemory(void)
{
    SeTask_u_Tick = 0u;

    SeTask_u_5msATaskCnt = 0u;
    SeTask_u_5msBTaskCnt = 0u;
    SeTask_u_5msCTaskCnt = 0u;
    SeTask_u_5msDTaskCnt = 0u;
    SeTask_u_1msTaskCnt = 0u;

    SeTask_u_5msC_Extend = TASK_10msA;
    SeTask_u_5msD_Extend = TASK_10msC;
    SeTask_u_10msC_Extend = TASK_20msA;
    SeTask_u_10msD_Extend = TASK_50msA;


}
/*******************************************************************************
Name			: void Task_TickHandler_motor(void)
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: -
Call By			: tick interrupt
|******************************************************************************/
void Task_TickHandler_100us(void)
{
    TaskCfg_MainFunc_100us();
}
/*******************************************************************************
Name			: void Task_TickHandler(void)
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: -
Call By			: tick interrupt
|******************************************************************************/
void Task_TickHandler(void)
{
    SeTask_u_Tick++;
    if((uint8)TASKCFG_COUNTER_MAX == SeTask_u_Tick)
    {
        SeTask_u_Tick = 0u;
    }

    switch(SeTask_u_Tick)
    {
    case TASKCFG_5msA_RUN_TICK:
        SeTask_u_5msATaskCnt++;
        break;
    case TASKCFG_5msB_RUN_TICK:
        SeTask_u_5msBTaskCnt++;
        break;
    case TASKCFG_5msC_RUN_TICK:
        SeTask_u_5msCTaskCnt++;
        break;
    case TASKCFG_5msD_RUN_TICK:
        SeTask_u_5msDTaskCnt++;
        break;
    default:
        break;
    }

#if TASKCFG_USE_1ms
    if((uint8)0u == (SeTask_u_Tick % TASKCFG_1ms_TASK_CYCLE) )
    {
        SeTask_u_1msTaskCnt++;
    }
#endif

}
/*******************************************************************************
Name			: void Task_MainFunc(void)
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: -
Call By			:
|******************************************************************************/
void Task_MainFunction(void)
{
    uint8 uDelta;
    uint8 uTick;
    if(SeTask_u_5msATaskCnt > (uint8)0)
    {
        SeTask_u_5msATaskCnt--;
        uTick = SeTask_u_Tick;

#if TASKCFG_USE_5msA
        TaskCfg_MainFunc_5msA();
#endif

        /* judge if task run out of duration */
        uDelta = SeTask_u_Tick - uTick;
        if(((uint8)TASKCFG_5msA_DURATION)  <= uDelta)
        {
            TaskCfg_TimeOut();
        }
    }

    if(SeTask_u_5msBTaskCnt > (uint8)0)
    {
        SeTask_u_5msBTaskCnt--;
        uTick = SeTask_u_Tick;

#if TASKCFG_USE_5msB
        TaskCfg_MainFunc_5msB();
#endif

        /* judge if task run out of duration */
        uDelta = SeTask_u_Tick - uTick;
        if(((uint8)TASKCFG_5msB_DURATION)  <= uDelta)
        {
            TaskCfg_TimeOut();
        }
    }

    if(SeTask_u_5msCTaskCnt > (uint8)0)
    {
        SeTask_u_5msCTaskCnt--;
        uTick = SeTask_u_Tick;

#if TASKCFG_USE_5msC
        if((uint8)TASK_10msA == SeTask_u_5msC_Extend)
        {
            TaskCfg_MainFunc_10msA();
            SeTask_u_5msC_Extend = TASK_10msB;
        }
        else
        {
            TaskCfg_MainFunc_10msB();
            SeTask_u_5msC_Extend = TASK_10msA;
        }
#endif

        /* judge if task run out of duration */
        uDelta = SeTask_u_Tick - uTick;
        if(((uint8)TASKCFG_5msC_DURATION)  <= uDelta)
        {
            TaskCfg_TimeOut();
        }
    }

    if(SeTask_u_5msDTaskCnt > (uint8)0)
    {
        SeTask_u_5msDTaskCnt--;
        uTick = SeTask_u_Tick;

#if TASKCFG_USE_5msD
        if((uint8)TASK_10msC == SeTask_u_5msD_Extend)
        {
            SeTask_u_5msD_Extend = TASK_10msD;
#if TASKCFG_USE_20ms
            if((uint8)TASK_20msA == SeTask_u_10msC_Extend)
            {
                TaskCfg_MainFunc_20msA();
                SeTask_u_10msC_Extend = TASK_20msB;
            }
            else
            {
                TaskCfg_MainFunc_20msB();
                SeTask_u_10msC_Extend = TASK_20msA;
            }
#else
            TaskCfg_MainFunc_10msC();
#endif
        }
        else
        {
            SeTask_u_5msD_Extend = TASK_10msC;

#if TASKCFG_USE_50ms
            if((uint8)TASK_50msA == SeTask_u_10msD_Extend)
            {
                TaskCfg_MainFunc_50msA();
                SeTask_u_10msD_Extend = TASK_50msB;
            }
            else if((uint8)TASK_50msB == SeTask_u_10msD_Extend)
            {
                TaskCfg_MainFunc_50msB();
                SeTask_u_10msD_Extend = TASK_50msC;
            }
            else if((uint8)TASK_50msC == SeTask_u_10msD_Extend)
            {
                TaskCfg_MainFunc_50msC();
                SeTask_u_10msD_Extend = TASK_50msD;
            }
            else if((uint8)TASK_50msD == SeTask_u_10msD_Extend)
            {
                TaskCfg_MainFunc_50msD();
                SeTask_u_10msD_Extend = TASK_50msE;
            }
            else
            {
                TaskCfg_MainFunc_50msE();
                SeTask_u_10msD_Extend = TASK_50msA;
            }
#else
            TaskCfg_MainFunc_10msD();
#endif
        }
#endif
        /* judge if task run out of duration */
        uDelta = SeTask_u_Tick - uTick;
        if(((uint8)TASKCFG_5msD_DURATION)  <= uDelta)
        {
            TaskCfg_TimeOut();
        }
    }



#if TASKCFG_USE_1ms
    if(SeTask_u_1msTaskCnt > (uint8)0)
    {
        SeTask_u_1msTaskCnt--;
        TaskCfg_MainFunc_1ms();
    }
#endif

}







