/*
 * @Author: liuranyang liuranyang@cncaea.cn
 * @Date: 2026-01-28 21:33:35
 * @LastEditors: liuranyang liuranyang@cncaea.cn
 * @LastEditTime: 2026-03-20 20:54:37
 * @FilePath: \FR30xxC-SDK-v0.3.1\examples\application\btdm_audio\Src\Bsw\SystemService\task.c
 * @Description: 默认设置
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

//#include "uds_task.h"
//#include "can_app.h"
#include "Appl_Can_Callback.h"
#include "Switch.h"
#include "adc_if.h"
#include "STD_BtrM.h"
#include "SysM.h"
#include "Hmi.h"
#include "Can_Main.h"
#include "CanDem.h"
#include "driver_wdt.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define TASK_5MS_PRIO            8
#define TASK_5MS_STACK_SIZE      ( configMINIMAL_STACK_SIZE * 2 )

#define TASK_10MSA_PRIO          7
#define TASK_10MSA_STACK_SIZE    ( configMINIMAL_STACK_SIZE * 2 )

#define TASK_10MSB_PRIO          ( tskIDLE_PRIORITY + 4 )
#define TASK_10MSB_STACK_SIZE    ( configMINIMAL_STACK_SIZE * 2 )

#define TASK_20MS_PRIO           ( tskIDLE_PRIORITY + 3 )
#define TASK_20MS_STACK_SIZE     ( configMINIMAL_STACK_SIZE * 2 )

#define TASK_50MS_PRIO           ( tskIDLE_PRIORITY + 2 )
#define TASK_50MS_STACK_SIZE     ( configMINIMAL_STACK_SIZE * 2 )

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static void prvQueue5msTask( void *pvParameters );
static void prvQueue10msATask( void *pvParameters );
static void prvQueue10msBTask( void *pvParameters );
static void prvQueue20msTask( void *pvParameters );
static void prvQueue50msTask( void *pvParameters );
static void test_task(void *p);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* ========================================================================== */
/*                        Application Local Functions                         */
/* ========================================================================== */


/**
 * @description: TaskDealCfg5msTask
 * @return {*}
 */
void TaskDealCfg5msTask(void)
{
    /* printf("TaskDealCfg5msTask\r\n"); */
	 CanMain_5msAMainFunction();
	 CanMain_5msBMainFunction();
}

/**
 * @description: TaskDealCfg10msATask
 * @return {*}
 */
void TaskDealCfg10msATask(void)
{
    /* printf("TaskDealCfg10msATask\r\n"); */
    BtrM_MainFunction();
    CanMain_10msAMainFunction();
}

/**
 * @description: TaskDealCfg10msBTask
 * @return {*}
 */
void TaskDealCfg10msBTask(void)
{
    Switch_MainFuction();
    SysM_MainFunction();
    Hmi_MainFunction();
    CanMain_10msBMainFunction();
    ApplCanDiagReqTimerTask();
}

/**
 * @description: TaskDealCfg20msTask
 * @return {*}
 */
void TaskDealCfg20msTask(void)
{
    static uint8 Cnt2 = 0;
    if(Cnt2 < 100)
    {
        Cnt2++;
    }
    else
    {
        CanDem_SetConditionstatuts_ontooff();
    }
    /* printf("TaskDealCfg20msTask\r\n"); */
	CanMain_20msMainFunction();
}

/**
 * @description: TaskDealCfg50msTask
 * @return {*}
 */
void TaskDealCfg50msTask(void)
{
   	CanMain_50msMainFunction();
    wdt_feed(WDT);
}

void AppTaskCreate(void)
{
    xTaskCreate((TaskFunction_t)prvQueue5msTask,
                (const char *)"5msATASK",
                (const configSTACK_DEPTH_TYPE)TASK_5MS_STACK_SIZE, 
                (void * const)NULL,
                (UBaseType_t)TASK_5MS_PRIO,
                (TaskHandle_t * const)NULL );
    
    xTaskCreate((TaskFunction_t)prvQueue10msATask,
                (const char *)"10msATASK",
                (const configSTACK_DEPTH_TYPE)TASK_10MSA_STACK_SIZE, 
                (void * const)NULL,
                (UBaseType_t)TASK_10MSA_PRIO,
                (TaskHandle_t * const)NULL );
    
    xTaskCreate((TaskFunction_t)prvQueue10msBTask,
                (const char *)"10msBTASK",
                (const configSTACK_DEPTH_TYPE)TASK_10MSB_STACK_SIZE, 
                (void * const)NULL,
                (UBaseType_t)TASK_10MSB_PRIO,
                (TaskHandle_t * const)NULL );
    
    xTaskCreate((TaskFunction_t)prvQueue20msTask,
                (const char *)"20msTASK",
                (const configSTACK_DEPTH_TYPE)TASK_20MS_STACK_SIZE, 
                (void * const)NULL,
                (UBaseType_t)TASK_20MS_PRIO,
                (TaskHandle_t * const)NULL );
    
    xTaskCreate((TaskFunction_t)prvQueue50msTask,
                (const char *)"50msTASK",
                (const configSTACK_DEPTH_TYPE)TASK_50MS_STACK_SIZE, 
                (void * const)NULL,
                (UBaseType_t)TASK_50MS_PRIO,
                (TaskHandle_t * const)NULL );
    
    xTaskCreate(test_task, "test_task", 128, NULL, MONITOR_TASK_PRIORITY, NULL);
}

static void prvQueue5msTask( void *pvParameters )
{
	(void)pvParameters;
	for( ;; )
	{
        TaskDealCfg5msTask();
        /* 5ms任务 */
        vTaskDelay(pdMS_TO_TICKS(5u));
	}
}

static void prvQueue10msATask( void *pvParameters )
{
	(void)pvParameters;
	for( ;; )
	{
        TaskDealCfg10msATask();
        /* 10ms任务A */
        vTaskDelay(pdMS_TO_TICKS(10u));
	}
}

static void prvQueue10msBTask( void *pvParameters )
{
	(void)pvParameters;
	for( ;; )
	{
        TaskDealCfg10msBTask();
        /* 10ms任务B */
        vTaskDelay(pdMS_TO_TICKS(10u));
	}
}

static void prvQueue20msTask( void *pvParameters )
{
	(void)pvParameters;
	for( ;; )
	{
        TaskDealCfg20msTask();
        /* 20ms任务 */
        vTaskDelay(pdMS_TO_TICKS(20u));
	}
}

static void prvQueue50msTask( void *pvParameters )
{
	(void)pvParameters;
	for( ;; )
	{
        TaskDealCfg50msTask();
        /* 50ms任务 */
        vTaskDelay(pdMS_TO_TICKS(50u));
	}
}

static void test_task(void *p)
{
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1));
    }
} 