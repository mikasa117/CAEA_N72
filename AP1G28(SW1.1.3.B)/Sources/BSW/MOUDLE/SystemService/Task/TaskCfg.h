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
#ifndef _TASK_CFG_H_
#define _TASK_CFG_H_

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "CAEA_Types.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
/*shortest cycle is 5ms, tick is 500us, 5ms/500us = 10 ticks, so there are 10 ticks in one cycle*/
#define TASKCFG_INT_TICK_TIME   500u       //500us
#define TASKCFG_TIME(x)  ((x)/TASKCFG_INT_TICK_TIME)

#define TASKCFG_FALSE    0U
#define TASKCFG_TRUE     1U

#define TASKCFG_1ms_TASK_CYCLE       TASKCFG_TIME(1000u)
#define TASKCFG_5ms_TASK_CYCLE       TASKCFG_TIME(5000u)

#define TASKCFG_1ms_DURATION         TASKCFG_TIME(500u)  //duration is 1000us

#define TASKCFG_5msA_RUN_TICK        TASKCFG_TIME(0u)  //start run tick is at 0us
#define TASKCFG_5msA_DURATION        TASKCFG_TIME(1000u)  //duration is 1000us

#define TASKCFG_5msB_RUN_TICK        TASKCFG_TIME(1000u)  //start run tick is at 1500us
#define TASKCFG_5msB_DURATION        TASKCFG_TIME(1500u)  //duration is 1500us

#define TASKCFG_5msC_RUN_TICK        TASKCFG_TIME(2500u)  //start run tick is at 300us
#define TASKCFG_5msC_DURATION        TASKCFG_TIME(1500u)  //duration is 1500us. used to extend 10msA and 10msB

#define TASKCFG_5msD_RUN_TICK        TASKCFG_TIME(4000u)   //start run tick is at 4500us
#define TASKCFG_5msD_DURATION        TASKCFG_TIME(1000u)    //duration is 1000us. used to extend (10ms C or 20msAB)&&(10msD or 50msABCDE)

#define TASKCFG_BASIC_TASK_CYCLE     TASKCFG_5ms_TASK_CYCLE
#define TASKCFG_COUNTER_MAX          TASKCFG_BASIC_TASK_CYCLE

#define TASKCFG_USE_5msA             ((TASKCFG_5msA_RUN_TICK + TASKCFG_5msA_DURATION) <= TASKCFG_COUNTER_MAX)
#define TASKCFG_USE_5msB             ((TASKCFG_5msB_RUN_TICK + TASKCFG_5msB_DURATION) <= TASKCFG_COUNTER_MAX)
#define TASKCFG_USE_5msC             ((TASKCFG_5msC_RUN_TICK + TASKCFG_5msC_DURATION) <= TASKCFG_COUNTER_MAX)
#define TASKCFG_USE_5msD             ((TASKCFG_5msD_RUN_TICK + TASKCFG_5msD_DURATION) <= TASKCFG_COUNTER_MAX)

#define TASKCFG_USE_1ms              TASKCFG_TRUE
#define TASKCFG_USE_20ms             TASKCFG_TRUE  //inherited from 5msD. if set false, 10msC will be used
#define TASKCFG_USE_50ms             TASKCFG_TRUE  //inherited from 5msD. if set false, 10msD will be used

#define TASKTIME_TEST                0

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/
extern void TaskCfg_TimeOut(void);

extern void TaskCfg_MainFunc_100us(void);
#if TASKCFG_USE_1ms
extern void TaskCfg_MainFunc_1ms(void);
#endif

#if TASKCFG_USE_5msA
extern void TaskCfg_MainFunc_5msA(void);
#endif


#if TASKCFG_USE_5msB
extern void TaskCfg_MainFunc_5msB(void);
#endif

#if TASKCFG_USE_5msC
extern void TaskCfg_MainFunc_10msA(void);
extern void TaskCfg_MainFunc_10msB(void);
#endif


#if TASKCFG_USE_5msD

#if TASKCFG_USE_20ms
extern void TaskCfg_MainFunc_20msA(void);
extern void TaskCfg_MainFunc_20msB(void);
#else
void TaskCfg_MainFunc_10msC(void);
#endif

#if TASKCFG_USE_50ms
extern void TaskCfg_MainFunc_50msA(void);
extern void TaskCfg_MainFunc_50msB(void);
extern void TaskCfg_MainFunc_50msC(void);
extern void TaskCfg_MainFunc_50msD(void);
extern void TaskCfg_MainFunc_50msE(void);
#else
extern void TaskCfg_MainFunc_10msD(void);
#endif

#endif





#endif
