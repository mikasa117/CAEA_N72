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
#include "TaskCfg.h"
#include "YTM32B1ME0.h"
#include "pins_driver.h"
#include "STD_AdcM.h"
#include "STD_BtrM.h"
#include "Can_Main.h"
#include "SysM.h"
//#include "STD_EepM.h"
//#include "NtcM.h"
#include "STD_WdgM.h"
//#include "SpiIf.h"
//#include "Gateway.h"
//#include "Can_Trcv.h"
#include "Fridge_Application_Config.h"
#include "Fridge_Basic_Control.h"
#include "DID_Callback.h"
#include "HallM.h"
#include "STD_SrM.h"
#include "Fault_Diagnosis.h"
#include "LED_DriverM.h"
#if TASKTIME_TEST
#include "HwIO.h"
#endif
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

/*******************************************************************************
Name			: void TaskCfg_TimeOut(void)
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: task run timeout
Call By			: task.c
|******************************************************************************/
void TaskCfg_TimeOut(void)
{
    //while(1){}
}

/*******************************************************************************
Name			: void TaskCfg_MainFunc_100us(void)
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: 100us task
Call By			: task.c
|******************************************************************************/
void TaskCfg_MainFunc_100us(void)
{
    #if TASKTIME_TEST
    static uint8_t status = 0u;
	if (status == 0u)
    {
        status = 1u;
        //PINS_DRV_SetPins(GPIOB, 1 << 5);
        HwIO_HALL_5V_EN_ON();
    }
    else
    {
        status = 0u;
        //PINS_DRV_ClearPins(GPIOB, 1 << 5);
        HwIO_HALL_5V_EN_OFF();
    }
	#endif 

}
/*******************************************************************************
Name			: void TaskCfg_MainFunc_1ms(void)
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: 1ms task
Call By			: task.c
|******************************************************************************/
#if TASKCFG_USE_1ms

void TaskCfg_MainFunc_1ms(void)
{
    //ADCM_ADC0_StartFunction();
    ADCM_MainFunction();
    
}
#endif/*#if TASKCFG_USE_1ms*/

/*******************************************************************************
Name			: void TaskCfg_MainFunc_5msA(void)
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: 5msA task
Call By			: task.c
|******************************************************************************/
#if TASKCFG_USE_5msA

void TaskCfg_MainFunc_5msA(void)
{
    Fridge_Application_Function();
    FridgeCtrl_Basic_Control_Function();
    BTRM_MainFunction();

    FridgeFault_Detection_MainFunction();
}
#endif/*#if TASKCFG_USE_5msA*/

/*******************************************************************************
Name			: void TaskCfg_MainFunc_5msB(void)
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: 5msB task
Call By			: task.c
|******************************************************************************/
#if TASKCFG_USE_5msB
void TaskCfg_MainFunc_5msB(void)
{	
    CanMain_5msBMainFunction();
    SysM_MainFunction();
    SRM_5msMainFunction();
    ADCB0_SamplingCallBack();
    LED_DRV_M_5msMainFunction();
}
#endif/*#if TASKCFG_USE_5msB*/

/*******************************************************************************
Name			: void TaskCfg_MainFunc_10ms(void)
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: 10ms task, inherited from 5msC
Call By			: task.c
|******************************************************************************/
#if TASKCFG_USE_5msC


void TaskCfg_MainFunc_10msA(void)
{

    CanMain_10msAMainFunction();
	CUS_NVR_WriteDID();   //GGL 2025.1202
    SRM_10msMainFunction();
}


void TaskCfg_MainFunc_10msB(void)
{
	EEPM_MainFunction();
    CanMain_10msBMainFunction();
    
    HALL_M_MainFunction();

    
}
#endif/*#if TASKCFG_USE_5msC*/



/***********************below task is inherited from 5msD**********************/

#if TASKCFG_USE_5msD
/*******************************************************************************
Name			: void TaskCfg_MainFunc_20ms(void)
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: 20ms task, inherited from 10msC
Call By			: task.c
|******************************************************************************/

void TaskCfg_MainFunc_20msA(void)
{
    WDGM_Trigger();
    CanMain_20msMainFunction();
}


void TaskCfg_MainFunc_20msB(void)
{

    
    
}


/*******************************************************************************
Name			: void TaskCfg_MainFunc_50ms(void)
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: 50ms task,inherited from 10msD
Call By			: task.c
|******************************************************************************/
//static uint8 Cnt50msA=0;
extern uint8 Touch_PressStaPWMSwitch;
volatile uint32 CompTaskCnt;
extern void task_100ms(void);

void TaskCfg_MainFunc_50msA(void)
{	
	CompTaskCnt =CompTaskCnt%2;
	if ((CompTaskCnt%2)==0)
	{
		task_100ms();
	}
	CompTaskCnt++;
}


void TaskCfg_MainFunc_50msB(void)
{

     	//CanApp_Msg0X2F8_TxFunc();
}

void TaskCfg_MainFunc_50msC(void)
{


}

void TaskCfg_MainFunc_50msD(void)
{

}

void TaskCfg_MainFunc_50msE(void)
{
    #if TASKTIME_TEST
    static uint8 uc50mscnt = 0;
    if (uc50mscnt < 15)
    {
        uc50mscnt++;
    }
    
    if (uc50mscnt >= 10)
    {
        uc50mscnt=17;
        //HwIO_COMP_12V_EN_ON();
        //HwIO_VCC_48V_EN_High();
        //HwIO_MCU_PD_SLPn_Enable();
        //HwIO_HALL_5V_EN_ON();
    }
#endif 
}

#endif/*#if TASKCFG_USE_5msD*/
