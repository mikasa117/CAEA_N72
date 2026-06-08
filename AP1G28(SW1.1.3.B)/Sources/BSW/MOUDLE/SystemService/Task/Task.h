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
#ifndef _TASK_H_
#define _TASK_H_

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "TaskCfg.h"


/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define TASK_10msA                 (1u)
#define TASK_10msB                 (2u)
#define TASK_10msC                 (3u)
#define TASK_10msD                 (4u)
#define TASK_20msA                 (5u)
#define TASK_20msB                 (6u)
#define TASK_50msA                 (7u)
#define TASK_50msB                 (8u)
#define TASK_50msC                 (9u)
#define TASK_50msD                 (10u)
#define TASK_50msE                 (11u)
#define TASK_100msA                (12u)
#define TASK_100msB                (13u)

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/
extern void Task_InitMemory(void);
extern void Task_TickHandler(void);
extern void Task_TickHandler_100us(void);
extern void Task_MainFunction(void);

#endif


