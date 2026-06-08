/* polyspace<MISRA-C3:1.1:Low:Justified> NO fluence */
/*******************************************************************************
|  File Name:  Mcal_App.c
|  Description:  Implementation of the Mcal_App Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| ZTW           TingWei Zhang          CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2014-09-28    01.00.00     ZTW       Creation
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
/* polyspace:begin<MISRA-C3:10.3:Not a defect:Justified> Normal. */
/* polyspace:begin<MISRA-C3:11.9:Not a defect:Justified> Normal. */
#include "Mcal_App.h"

//#include "can_config.h"
//#include "flexcan_driver.h"
#include "sdk_project_config.h"

#include "STD_AdcM.h"
//#include "STD_SrPwmCtr.h"

#include "STD_EepM.h"
//#include "STD_EcuM.h"
//#include "STD_EcuM_CallOut.h"
//#include "STD_Os.h"
//#include "STD_SMM.h"
//#include "STD_SysM.h"
//#include "STD_WdgM.h"
#include "RTE_CAN.h"
//#include "STD_WdgM.h"
//#include "STD_EncodeCtr.h"
//#include "STD_RamM.h"
//#include "adc_driver.h"
#include "Task.h"
#include "STD_FlsIf.h"
//#include "HwIO.h"
#include "STD_McuIf_Cfg.h"
#include "motor.h"
#include "Fridge_Application_Config.h"

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
|    Global variables Declaration
|******************************************************************************/

/*******************************************************************************
|    static local variables Declaration
|******************************************************************************/
#if (MCAL_MCM_IRQn_EN == MCAL_ENABLE)
static  TsMcalApp_h_PECCError MCAL_CODE_RAM stMcalAppMCMError;
#endif

#if (MCAL_ERM_double_fault_IRQn_EN == MCAL_ENABLE)
/* use to store the memory ECC error details,e.g. memory type, address and ECC type */
/* polyspace<MISRA-C3:8.9:Not a defect:Justified> Normal. */

#endif

static uint16 MCAL_CODE_RAM usMcalAppRtcSleepTickCnt = 0u;
static uint8 MCAL_CODE_RAM ucMcalAppIGNWakeupStatus = 0u;
static uint8 MCAL_CODE_RAM ucMcalAppCOMWakeupStatus = 0u;
static uint8 MCAL_CODE_RAM ucMcalAppI2cPowerStatus = 0u;
static uint8 ucMcalAppI2cReset = 0u;
static uint8 MCAL_CODE_RAM ucMcalAppStandbyWakeupStatus = 0u;
static uint8 MCAL_CODE_RAM ucMcalAppStandbyEnterStatus = 0u;
/* polyspace<MISRA-C3:8.9:Not a defect:Justified> Normal. */
//static uint8 MCAL_CODE_KAM scMcalAppSRAMEccFlag;
/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/

#if	(MCAL_WDOG_EWM_IRQn_EN	== MCAL_ENABLE)
static void MCALAPP_CallBackWdg_IRQHandler(void);
#endif

#if (MCAL_RTC_IRQn_EN	== MCAL_ENABLE)
static void MCALAPP_CallBackRtc_IRQHandler(void);
#endif

#if	(MCAL_LPIT1_Ch0_IRQn_EN	== MCAL_ENABLE)
static void MCALAPP_CallBackLpitCh0_IRQHandler(void);

#endif

#if	(MCAL_LPIT1_Ch1_IRQn_EN	== MCAL_ENABLE)
static void MCALAPP_CallBackLpitCh1_IRQHandler(void);
#endif
#if	(MCAL_LPIT1_Ch2_IRQn_EN	== MCAL_ENABLE)
static void MCALAPP_CallBackLpitCh2_IRQHandler(void);
#endif
#if	(MCAL_LPIT1_Ch3_IRQn_EN	== MCAL_ENABLE)
static void MCALAPP_CallBackLpitCh3_IRQHandler(void);
#endif
#if	(MCAL_ADC0_IRQn_EN	== MCAL_ENABLE)
static void MCALAPP_CallBackADC0_IRQHandler(void);
#endif
#if	(MCAL_ADC1_IRQn_EN	== MCAL_ENABLE)
static void MCALAPP_CallBackADC1_IRQHandler(void);
#endif
#if	(MCAL_LPTMR0_IRQn_EN == MCAL_ENABLE)
static void MCALAPP_CallBackLPTMR_IRQHandler(void);
#endif
#if	(MCAL_PORTA_IRQn_EN == MCAL_ENABLE)
static void MCALAPP_CallBackPortA_IRQHandler(void);
#endif
#if	(MCAL_PORTB_IRQn_EN == MCAL_ENABLE)
static void MCALAPP_CallBackPortB_IRQHandler(void);
#endif
#if	(MCAL_PORTC_IRQn_EN == MCAL_ENABLE)
static void MCALAPP_CallBackPortC_IRQHandler(void);
#endif

#if	(MCAL_PORTD_IRQn_EN == MCAL_ENABLE)
static void MCALAPP_CallBackPortD_IRQHandler(void);
#endif

#if	(MCAL_PORTE_IRQn_EN == MCAL_ENABLE)
static void MCALAPP_CallBackPortE_IRQHandler(void);
#endif

/*******************************************************************************
|	 Global Function Prototypes
|******************************************************************************/
/******************************************************************************
 *锟斤拷锟斤拷锟斤拷锟斤拷  : void MCALAPP_InitMemory(void)

 *锟斤拷锟斤拷      : void

 *锟斤拷锟斤拷�: void

 *锟斤拷锟斤拷      : 锟斤拷始锟斤拷锟节达�
 *锟洁辑时锟斤�
 锟斤拷锟斤拷
 *锟斤拷注      :
 ********************************************************************************/
void MCALAPP_InitMemory(void)
{
	usMcalAppRtcSleepTickCnt = 0u;
	ucMcalAppIGNWakeupStatus = 0u;
	ucMcalAppCOMWakeupStatus = 0u;

	ucMcalAppI2cPowerStatus = 0u;
	ucMcalAppI2cReset = 0u;
	ucMcalAppStandbyWakeupStatus = 0u;
	ucMcalAppStandbyEnterStatus = 0u;
}


/******************************************************************************
 *锟斤拷锟斤拷锟斤拷锟斤拷  : void MCALAPP_StartGpt(void)
 
 *锟斤拷锟斤拷      : void

 *锟斤拷锟斤拷� : void

 *锟斤拷锟斤拷      :  锟斤拷始通锟矫硷拷时锟斤�
 *锟洁辑时锟斤�
 锟斤拷锟斤拷
 *锟斤拷注      :
 ********************************************************************************/
void MCALAPP_StartGpt(void)
{
#if	(MCALAPP_LPIT1_Ch0_EN == MCAL_ENABLE)
	GPTIF_StartLPITTimer(GPTIF_LPIT1_Ch0_ID);
#endif
#if	(MCALAPP_LPIT1_Ch1_EN == MCAL_ENABLE)
	//GPTIF_StartLPITTimer(GPTIF_LPIT1_Ch1_ID);
#endif
#if	(MCALAPP_LPIT1_Ch2_EN == MCAL_ENABLE)
	GPTIF_StartLPITTimer(GPTIF_LPIT1_Ch2_ID);
#endif
#if	(MCALAPP_LPIT1_Ch3_EN == MCAL_ENABLE)
	GPTIF_StartLPITTimer(GPTIF_LPIT1_Ch3_ID);
#endif

    if (RCU->RSSR & RCU_RSSR_WDG_MASK)
    {
        /* Clear all reset flags. */
        RCU->RSSR = RCU->RSSR;
    }
    
#if	(MCAL_ADC0_IRQn_EN	== MCAL_ENABLE)
//	GPTIF_StartPDBTimer(INST_PTU1);
#endif
#if	(MCAL_ADC1_IRQn_EN	== MCAL_ENABLE)
//	GPTIF_StartPDBTimer(INST_PTU1);
#endif
}
/******************************************************************************
* Function Name : void MCALAPP_PeripheralInit( void )
* Description   : This function initializes the Mcal PeripheralInit
* Argument      : none
* Return Value  : none
******************************************************************************/
void MCALAPP_PeripheralInit(void)
{
	PortIf_Init();
    EEPM_Init();
	//DioIf_Init();
	
	AdcIf_Init();
	//AdcIf_1_ConfigGropChannel();
    FlsIf_Init();
}

/******************************************************************************
 *锟斤拷锟斤拷锟斤拷锟斤拷  : void MCALAPP_PeripheralDInit(void)

 *锟斤拷锟斤拷      : void

 *锟斤拷锟斤拷�: void

 *锟斤拷锟斤拷      : 锟斤拷围锟斤拷锟斤拷始锟斤拷

 *锟洁辑时锟斤�
 锟斤拷锟斤拷
 *锟斤拷注      :
 ********************************************************************************/
uint8 CAN1_ORed_IRQnxx;
uint8 CAN1_Error_IRQnxx;
uint8 CAN1_ORed_0_15_MB_IRQnxx;
uint8 CAN1_ORed_16_31_MB_IRQnxx;
void MCALAPP_PeripheralDeInit(void)
{
	//AdcIf_DeInit();
	//DioIf_DeInit();
}

void MCALAPP_SetInterruptsPriority(void)
{
    INT_SYS_SetPriority(MCUIF_LPIT0_Ch0_IRQn, 4);
#if (MCAL_LPIT1_Ch1_IRQn_EN == MCAL_ENABLE)
    INT_SYS_SetPriority(MCUIF_LPIT0_Ch1_IRQn, 2);
#endif
    INT_SYS_SetPriority(MCUIF_ADC1_IRQn, 0);
    //INT_SYS_SetPriority(MCUIF_ADC0_IRQn, 4);

    INT_SYS_SetPriority(CAN1_ORed_IRQn, 3);
    INT_SYS_SetPriority(CAN1_Error_IRQn, 3);
    INT_SYS_SetPriority(CAN1_ORed_0_15_MB_IRQn, 3);
    INT_SYS_SetPriority(CAN1_ORed_16_31_MB_IRQn, 3);

    CAN1_ORed_IRQnxx=INT_SYS_GetPriority(CAN1_ORed_IRQn);
    CAN1_Error_IRQnxx=INT_SYS_GetPriority(CAN1_Error_IRQn);
    CAN1_ORed_0_15_MB_IRQnxx=INT_SYS_GetPriority(CAN1_ORed_0_15_MB_IRQn);
    CAN1_ORed_16_31_MB_IRQnxx=INT_SYS_GetPriority(CAN1_ORed_16_31_MB_IRQn);
    /**/
    INT_SYS_SetPriority(CAN1_Wake_Up_IRQn, 3);
    INT_SYS_SetPriority(CAN1_ORed_32_47_MB_IRQn, 3);
    INT_SYS_SetPriority(CAN1_ORed_16_31_MB_IRQn, 3);





    INT_SYS_SetPriority(MCUIF_PORTA_IRQn, 3);
}

/******************************************************************************
 *锟斤拷锟斤拷锟斤拷锟斤拷  : void MCALAPP_EnableInterrupts(void)
 
 *锟斤拷锟斤拷      : void

 *锟斤拷锟斤拷�: void

 *锟斤拷锟斤拷      :  使锟杰斤拷锟斤拷锟叫讹拷

 *锟洁辑时锟斤�
 锟斤拷锟斤拷
 *锟斤拷注      :
 ********************************************************************************/
void MCALAPP_EnableInterrupts(void)
{
	/*Register interrupt*/
#if	(MCAL_WDOG_EWM_IRQn_EN	== MCAL_ENABLE)
	McuIf_EnableIRQ(MCUIF_WDOG_EWM_IRQn);
#endif
#if (MCAL_RTC_IRQn_EN	== MCAL_ENABLE)
	McuIf_EnableIRQ(MCUIF_RTC_IRQn);
#endif
#if	(MCAL_LPIT1_Ch0_IRQn_EN	== MCAL_ENABLE)
	McuIf_EnableIRQ(MCUIF_LPIT0_Ch0_IRQn);
#endif
#if	(MCAL_LPIT1_Ch1_IRQn_EN	== MCAL_ENABLE)
	McuIf_EnableIRQ(MCUIF_LPIT0_Ch1_IRQn);
#endif
#if	(MCAL_LPIT1_Ch2_IRQn_EN	== MCAL_ENABLE)
	McuIf_EnableIRQ(MCUIF_LPIT0_Ch2_IRQn);
#endif
#if	(MCAL_LPIT1_Ch3_IRQn_EN	== MCAL_ENABLE)
	McuIf_EnableIRQ(MCUIF_LPIT0_Ch3_IRQn);
#endif
#if	(MCAL_ADC0_IRQn_EN	== MCAL_ENABLE)
	McuIf_EnableIRQ(MCUIF_ADC0_IRQn);
#endif
#if	(MCAL_ADC1_IRQn_EN	== MCAL_ENABLE)
	McuIf_EnableIRQ(MCUIF_ADC1_IRQn);
#endif
#if	(MCAL_LPTMR0_IRQn_EN == MCAL_ENABLE)
	/*McuIf_EnableIRQ(MCUIF_LPTMR0_IRQn);*//*For Little Sleep Wakeup*/
#endif
#if	(MCAL_PORTA_IRQn_EN == MCAL_ENABLE)
	McuIf_EnableIRQ(MCUIF_PORTA_IRQn);
#endif
#if	(MCAL_PORTB_IRQn_EN == MCAL_ENABLE)
	McuIf_EnableIRQ(MCUIF_PORTB_IRQn);
#endif
#if	(MCAL_PORTC_IRQn_EN == MCAL_ENABLE)
	McuIf_EnableIRQ(MCUIF_PORTC_IRQn);
#endif
#if	(MCAL_PORTD_IRQn_EN == MCAL_ENABLE)
	McuIf_EnableIRQ(MCUIF_PORTD_IRQn);
#endif
#if	(MCAL_PORTE_IRQn_EN == MCAL_ENABLE)
	McuIf_EnableIRQ(MCUIF_PORTE_IRQn);/*For Sleep Wakeup*/
#endif
}


/******************************************************************************
 *锟斤拷锟斤拷锟斤拷锟斤拷  : void MCALAPP_DisableInterrupts(void)
 
 *锟斤拷锟斤拷      : void

 *锟斤拷锟斤拷�: void

 *锟斤拷锟斤拷      :  锟斤拷使锟杰斤拷锟斤拷锟叫讹�
 *锟洁辑时锟斤�
 锟斤拷锟斤拷
 *锟斤拷注      :
 ********************************************************************************/
void MCALAPP_DisableInterrupts(void)
{
	/*Register interrupt*/
#if	(MCAL_WDOG_EWM_IRQn_EN	== MCAL_ENABLE)
	McuIf_DisableIRQ(MCUIF_WDOG_EWM_IRQn);
#endif
#if (MCAL_RTC_IRQn_EN	== MCAL_ENABLE)
	McuIf_DisableIRQ(MCUIF_RTC_IRQn);
#endif
#if	(MCAL_LPIT1_Ch0_IRQn_EN	== MCAL_ENABLE)
	McuIf_DisableIRQ(MCUIF_LPIT0_Ch0_IRQn);
#endif
#if	(MCAL_LPIT1_Ch1_IRQn_EN	== MCAL_ENABLE)
	McuIf_DisableIRQ(MCUIF_LPIT0_Ch1_IRQn);
#endif
#if	(MCAL_LPIT1_Ch2_IRQn_EN	== MCAL_ENABLE)
	McuIf_DisableIRQ(MCUIF_LPIT0_Ch2_IRQn);
#endif
#if	(MCAL_LPIT1_Ch3_IRQn_EN	== MCAL_ENABLE)
	McuIf_DisableIRQ(MCUIF_LPIT0_Ch3_IRQn);
#endif

#if	(MCAL_LPTMR0_IRQn_EN == MCAL_ENABLE)
	McuIf_DisableIRQ(MCUIF_LPTMR0_IRQn);
#endif
#if	(MCAL_PORTA_IRQn_EN == MCAL_ENABLE)
	McuIf_DisableIRQ(MCUIF_PORTA_IRQn);
#endif
#if	(MCAL_PORTB_IRQn_EN == MCAL_ENABLE)
	McuIf_DisableIRQ(MCUIF_PORTB_IRQn);
#endif
#if	(MCAL_PORTC_IRQn_EN == MCAL_ENABLE)
	//McuIf_DisableIRQ(MCUIF_PORTC_IRQn);
#endif
#if	(MCAL_PORTD_IRQn_EN == MCAL_ENABLE)
	McuIf_DisableIRQ(MCUIF_PORTD_IRQn);
#endif
#if	(MCAL_PORTE_IRQn_EN == MCAL_ENABLE)
	McuIf_DisableIRQ(MCUIF_PORTE_IRQn);
#endif
}


/******************************************************************************
 *锟斤拷锟斤拷锟斤拷锟斤拷  : void MCALAPP_SetProgrammableInterrupts(void)
 
 *锟斤拷锟斤拷      : void

 *锟斤拷锟斤拷�: void

 *锟斤拷锟斤拷      :  锟斤拷锟矫可憋拷锟斤拷卸锟锟洁辑时锟斤拷  :
 锟斤拷锟斤拷
 *锟斤拷注      :
 ********************************************************************************/
void MCALAPP_SetProgrammableInterrupts(void)
{
	/*Register interrupt*/
#if	(MCAL_WDOG_EWM_IRQn_EN	== MCAL_ENABLE)
	INT_SYS_InstallHandler(MCUIF_WDOG_EWM_IRQn, &MCALAPP_CallBackWdg_IRQHandler, (isr_t *)0);
#endif
#if	(MCAL_LPIT1_Ch0_IRQn_EN	== MCAL_ENABLE)
	INT_SYS_InstallHandler(MCUIF_LPIT0_Ch0_IRQn,&MCALAPP_CallBackLpitCh0_IRQHandler,(isr_t*)0);
#endif
#if	(MCAL_LPIT1_Ch1_IRQn_EN	== MCAL_ENABLE)
	INT_SYS_InstallHandler(MCUIF_LPIT0_Ch1_IRQn,&MCALAPP_CallBackLpitCh1_IRQHandler,(isr_t*)0);
#endif
#if	(MCAL_LPIT1_Ch2_IRQn_EN	== MCAL_ENABLE)
	INT_SYS_InstallHandler(MCUIF_LPIT0_Ch2_IRQn,&MCALAPP_CallBackLpitCh2_IRQHandler,(isr_t*)0);
#endif
#if	(MCAL_LPIT1_Ch3_IRQn_EN	== MCAL_ENABLE)
	INT_SYS_InstallHandler(MCUIF_LPIT0_Ch3_IRQn,&MCALAPP_CallBackLpitCh3_IRQHandler,(isr_t*)0);
#endif
#if	(MCAL_LPTMR0_IRQn_EN == MCAL_ENABLE)
	INT_SYS_InstallHandler(MCUIF_LPTMR0_IRQn, &MCALAPP_CallBackLPTMR_IRQHandler, (isr_t *)0);
#endif
#if	(MCAL_ADC0_IRQn_EN	== MCAL_ENABLE)
	INT_SYS_InstallHandler(MCUIF_ADC0_IRQn,&MCALAPP_CallBackADC0_IRQHandler,(isr_t*)0);
#endif
#if	(MCAL_ADC1_IRQn_EN	== MCAL_ENABLE)
	INT_SYS_InstallHandler(MCUIF_ADC1_IRQn,&MCALAPP_CallBackADC1_IRQHandler,(isr_t*)0);
#endif
#if	(MCAL_PORTA_IRQn_EN == MCAL_ENABLE)
	INT_SYS_InstallHandler(MCUIF_PORTA_IRQn, &MCALAPP_CallBackPortA_IRQHandler, (isr_t *)0);
#endif
#if	(MCAL_PORTB_IRQn_EN == MCAL_ENABLE)
	INT_SYS_InstallHandler(MCUIF_PORTB_IRQn, &MCALAPP_CallBackPortB_IRQHandler, (isr_t *)0);
#endif
#if	(MCAL_PORTC_IRQn_EN == MCAL_ENABLE)
	INT_SYS_InstallHandler(MCUIF_PORTC_IRQn, &MCALAPP_CallBackPortC_IRQHandler, (isr_t *)0);/*IGN*/
#endif
#if	(MCAL_PORTD_IRQn_EN == MCAL_ENABLE)
	INT_SYS_InstallHandler(MCUIF_PORTD_IRQn, &MCALAPP_CallBackPortD_IRQHandler, (isr_t *)0);
#endif
#if	(MCAL_PORTE_IRQn_EN == MCAL_ENABLE)
	INT_SYS_InstallHandler(MCUIF_PORTE_IRQn, &MCALAPP_CallBackPortE_IRQHandler, (isr_t *)0);/*IGN */
#endif

}

#if	(MCAL_WDOG_EWM_IRQn_EN	== MCAL_ENABLE)

static void MCALAPP_CallBackWdg_IRQHandler(void)
{
	
}
#endif

#if (MCAL_RTC_IRQn_EN	== MCAL_ENABLE)
static void MCALAPP_CallBackRtc_IRQHandler(void)
{

}
#endif

#if	(MCAL_LPIT1_Ch0_IRQn_EN	== MCAL_ENABLE)

/******************************************************************************
 *锟斤拷锟斤拷锟斤拷锟斤拷  : static void MCALAPP_CallBackLpitCh0_IRQHandler(void)
 
 *锟斤拷锟斤拷      : void

 *锟斤拷锟斤拷�: void

 *锟斤拷锟斤拷      :  锟截碉拷Ch0锟斤拷锟斤拷嗉憋拷�
 锟斤拷锟斤拷
 *锟斤拷注      :
 ********************************************************************************/
static void MCALAPP_CallBackLpitCh0_IRQHandler(void)/*500us*/
{
#if	(MCAL_MONITOR_EN	== MCAL_ENABLE)
	SMM_RecordEnterIntCount( 0u );
#endif
    GPTIF_LPITClearTimerInterruptFlag(GPTIF_LPIT1_Ch0_ID);
	Task_TickHandler();
#if(WDGM_EN_CLASS == WDGM_ENABLE)
	//WDGM_CallBack_IRQHandler();
#endif
	//ENCODECTR_CallBackHandler();

#if	(MCAL_MONITOR_EN	== MCAL_ENABLE)
	SMM_CalculateIntRunTime( 0u );
#endif
}
#endif

#if	(MCAL_LPIT1_Ch1_IRQn_EN	== MCAL_ENABLE)
extern volatile uint32_t syscoun;
extern volatile uint32_t _syscoun;
extern volatile uint32_t syscount;
extern void task_1ms(void);
static void MCALAPP_CallBackLpitCh1_IRQHandler(void)/*100us*/
{
#if	(MCAL_MONITOR_EN	== MCAL_ENABLE)
	SMM_RecordEnterIntCount( 1u );
#endif
	GPTIF_LPITClearTimerInterruptFlag(GPTIF_LPIT1_Ch1_ID);
    
	if ((syscoun != _syscoun) && ((syscoun & 0xF) == 0)) 
	{
            _syscoun = syscoun;
            syscount++;
            task_1ms();
	}

#if	(MCAL_MONITOR_EN	== MCAL_ENABLE)
	SMM_CalculateIntRunTime( 1u );
#endif
}
#endif

#if	(MCAL_LPIT1_Ch2_IRQn_EN	== MCAL_ENABLE)
static void MCALAPP_CallBackLpitCh2_IRQHandler(void)/*500us*/
{
	static uint8 timecut;
#if	(MCAL_MONITOR_EN	== MCAL_ENABLE)
	SMM_RecordEnterIntCount( 2u );
#endif

	GPTIF_LPITClearTimerInterruptFlag(GPTIF_LPIT1_Ch2_ID);

	if(ucMcalAppI2cReset==1u)
	{
	    if((ucMcalAppI2cPowerStatus==0u)&&(timecut==0u))
	    {
		    ucMcalAppI2cPowerStatus=1u;
		   /* PwmIf_SetDutyCycleAndPeriod(HW_PWM_INDPWM,295u,200000u);70.5锛咃�khz*/
	    }
	    else
	    {}

	    timecut++;
	
	    if((ucMcalAppI2cPowerStatus==1u)&&(timecut==12u))
	    {
//		    PwmIf_SetDutyCycleAndPeriod(HW_PWM_BLKPWM,1000u,200u);/*0锛咃�hz*/
		    timecut=0u;
		    ucMcalAppI2cReset = 0u;
	    }
	    else
	    {}
	}



#if	(MCAL_MONITOR_EN	== MCAL_ENABLE)
	SMM_CalculateIntRunTime( 2u );
#endif
}
#endif

#if	(MCAL_LPIT1_Ch3_IRQn_EN	== MCAL_ENABLE)
static void MCALAPP_CallBackLpitCh3_IRQHandler(void)/*1000us*/
{
	GPTIF_LPITClearTimerInterruptFlag(GPTIF_LPIT1_Ch3_ID);
}
#endif

#if	(MCAL_ADC0_IRQn_EN	== MCAL_ENABLE)
static void MCALAPP_CallBackADC0_IRQHandler(void)
{
#if	(MCAL_MONITOR_EN	== MCAL_ENABLE)
	SMM_RecordEnterIntCount( 3u );
#endif
//	GPTIF_PDBClearTimerInterruptFlag();
	//GPTIF_ADCClearInterruptFlag();
	ADCB0_SamplingCallBack();
#if	(MCAL_MONITOR_EN	== MCAL_ENABLE)
	SMM_CalculateIntRunTime( 3u );
#endif
}
#endif
#if	(MCAL_ADC1_IRQn_EN	== MCAL_ENABLE)
// volatile uint32_t Current_DC = 0;
// volatile uint32_t ADC_FANCUR = 0;
// volatile uint32_t MCU_SO = 0;
// volatile uint32_t ADC_FAN = 0;
volatile uint32_t Current_C = 0;
volatile uint32_t Current_B = 0;
volatile uint32_t Current_A = 0;
volatile uint32_t Current_BUS = 0;
volatile uint32_t ADC_BAT_BLDC = 0;
volatile uint32_t ADC_BAT_Present = 0;
static void MCALAPP_CallBackADC1_IRQHandler(void)
{
#if (MCAL_MONITOR_EN == MCAL_ENABLE)
    SMM_RecordEnterIntCount(3u);
#endif
//	GPTIF_PDBClearTimerInterruptFlag();
// GPTIF_ADCClearInterruptFlag();
// ADCB1_SamplingCallBack();
#if (MCAL_MONITOR_EN == MCAL_ENABLE)
    SMM_CalculateIntRunTime(3u);
#endif

    NVIC_SetPendingIRQ(pTMR0_Ch1_IRQn);

    ADC_DRV_ClearEoseqFlagCmd(1);

    //    PINS_DRV_WritePin(GPIOC,16,1);  //test

    Current_B = ADC1->FIFO & 0xFFF;   // ib
    Current_A = ADC1->FIFO & 0xFFF;   // ia
    Current_BUS = ADC1->FIFO & 0xFFF; // ibus

	//ADC_BAT_BLDC = 893; /* 25V=1861 */ /* 46V=3425 */

    //ADC_BAT_BLDC = FridgeAppl_FridgeCompVoltage_Calculate();  /* 根据AD采样回来的电压值进行FOC运算 */
    //ADC_BAT_BLDC = ADC_BAT_BLDC+50;

    ADC_BAT_Present = FridgeAppl_FridgeCompVoltage_Calculate();

    if(ADC_BAT_Present > 400u)
    {
        ADC_BAT_BLDC = ADC_BAT_Present;
    }


    //ADCB0_SamplingCallBack();


    

    //	    Current_A	= ADC0->FIFO & 0xFFF;  // ia
    //		  ADC_BAT_BLDC = ADC0->FIFO & 0xFFF;  // vdc
    //	    //Current_DC	= ADC0->FIFO & 0xFFF;  // Current_U
    //	    ADC_FANCUR	= ADC0->FIFO & 0xFFF;  // Current_V
    //	    MCU_SO 		= ADC0->FIFO & 0xFFF;  // Current_W
    //		  ADC_FAN 	= ADC0->FIFO & 0xFFF;  // Voltage_U

    //    foc_ctrl(Current_BUS, Current_A, Current_B, ADC_BAT_BLDC, Current_C, 0, 0, 2, 4);		//正转
    foc_ctrl(Current_BUS, Current_B, Current_A, ADC_BAT_BLDC, Current_C, 0, 2, 0, 4);	//反转

    //    PINS_DRV_WritePin(GPIOC,16,0);  //test
}
#endif

#if	(MCAL_LPTMR0_IRQn_EN == MCAL_ENABLE)
static void MCALAPP_CallBackLPTMR_IRQHandler(void)
{
	GPTIF_LPTMRClearCompareFlag();
}
#endif

#if	(MCAL_PORTA_IRQn_EN == MCAL_ENABLE)
static void MCALAPP_CallBackPortA_IRQHandler(void)
{
    if(0u != (PINS_DRV_GetPortIntFlag(GPIOA)& (uint32)0x1000)) /*CAN_RX */
    {
        RteCan_CanBusWakeupInt();
        PINS_DRV_SetPinIntSel(GPIOA, 12, PCTRL_DMA_INT_DISABLED);

        if((uint8)TRUE == ucMcalAppCOMWakeupStatus)
        {
            ucMcalAppStandbyWakeupStatus = (uint8)0xE5;
            if((uint8)0xE5 == ucMcalAppStandbyEnterStatus)
            {
                McuIf_SoftwareReset();
            }
        }
    }
    PINS_DRV_ClearPortIntFlagCmd(GPIOA);
}
#endif

#if	(MCAL_PORTB_IRQn_EN == MCAL_ENABLE)
static void MCALAPP_CallBackPortB_IRQHandler(void)
{
	IcuIf_ClearPortIntFlagCmd(ICU_PORT_B_ID);
}
#endif


#if	(MCAL_PORTC_IRQn_EN == MCAL_ENABLE)
static void MCALAPP_CallBackPortC_IRQHandler(void)
{
	if(0u != (PINS_DRV_GetPortIntFlag(GPIOC) & (uint32)0x80))/*KL15 PTC 7*/
	{
		if((uint8)TRUE == ucMcalAppIGNWakeupStatus)
		{
			ECUM_CheckWakeup( ECUM_WKSOURCE_ICU );
		}
	}
	else
	{
	}
	PINS_DRV_ClearPortIntFlagCmd(GPIOC);
}


#endif

#if	(MCAL_PORTD_IRQn_EN == MCAL_ENABLE)
static void MCALAPP_CallBackPortD_IRQHandler(void)
{
	IcuIf_ClearPortIntFlagCmd(ICU_PORT_D_ID);
}
#endif

#if	(MCAL_PORTE_IRQn_EN == MCAL_ENABLE)
static void MCALAPP_CallBackPortE_IRQHandler(void)
{
	if((uint8)TRUE == ucMcalAppIGNWakeupStatus)
	{
		ECUM_CheckWakeup( ECUM_WKSOURCE_ICU );
	}
}
#endif

#if (MCAL_ERM_double_fault_IRQn_EN == MCAL_ENABLE)
void MCALAPP_CallBackERMDoubleFault_IRQHandler(void)
{
    scMcalAppSRAMEccFlag = 0xA5u;
    (void)EMU_DRV_ClearInterruptFlagDoubleBit(0u, 0u);
    (void)EMU_DRV_ClearInterruptFlagDoubleBit(0u, 1u);
    WDGM_SetTrigerReset();
}
#endif

#if (MCAL_MCM_IRQn_EN == MCAL_ENABLE)
void MCALAPP_CallBackMCM_IRQHandler(void)
{
    uint8 ucMcalAppPEELOC = McmIf_GetPEELOCValue();

    if (NCE_SRAM_L == ucMcalAppPEELOC)
    {
        if (McmIf_GetENCInterruptFlag((uint8)0x1))
        {
            McmIf_ClearENCInterruptFlag((uint8)0x1);    /* w1c to clean Non-Correctable ECC error flag on SRAM_L */
            stMcalAppMCMError.Location = NCE_SRAM_L;
        }

        stMcalAppMCMError.EFaddr = McmIf_GetFaultAddress();    /* record address */
    }

    if (NCE_SRAM_U == ucMcalAppPEELOC)
    {
        if (McmIf_GetENCInterruptFlag((uint8)0x2))
        {
            McmIf_ClearENCInterruptFlag((uint8)0x2);    /* w1c to clean Non-Correctable ECC error flag on SRAM_U */
            stMcalAppMCMError.Location = NCE_SRAM_U;
        }

        stMcalAppMCMError.EFaddr = McmIf_GetFaultAddress();    /* record address */
    }

    if (SBE_SRAM_L == ucMcalAppPEELOC)
    {
        if (McmIf_GetE1BInterruptFlag((uint8)0x1))
        {
            McmIf_ClearE1BInterruptFlag((uint8)0x1);    /* w1c to clean 1-bit correctable ECC error flag on SRAM_L */
            stMcalAppMCMError.Location = SBE_SRAM_L;
        }

        stMcalAppMCMError.EFaddr = McmIf_GetFaultAddress();    /* record address */
    }

    if (SBE_SRAM_U == ucMcalAppPEELOC)
    {
        if (McmIf_GetE1BInterruptFlag((uint8)0x2))
        {
            McmIf_ClearE1BInterruptFlag((uint8)0x2);    /* w1c to clean 1-bit correctable ECC error flag on SRAM_U */
            stMcalAppMCMError.Location = SBE_SRAM_U;
        }

        stMcalAppMCMError.EFaddr = McmIf_GetFaultAddress();    /* record address */
    }

#if (MCMIF_CACHEPARITY_EN == MCMIF_ENABLE)
    if (PC_Tag_ParityError == ucMcalAppPEELOC)
    {
        if (McmIf_GetPEInterruptFlag((uint8)0x4))
        {
            McmIf_ClearPEInterruptFlag((uint8)0x4);    /* w1c to clean PC Tag Parity Error flag */
            stMcalAppMCMError.Location = PC_Tag_ParityError;
        }

        stMcalAppMCMError.EFaddr = McmIf_GetFaultAddress();    /* record address */
        SystemSoftwareReset();
    }

    if (PC_Data_ParityError == ucMcalAppPEELOC)
    {
        if (McmIf_GetPEInterruptFlag((uint8)0x8))
        {
            McmIf_ClearPEInterruptFlag((uint8)0x8);    /* w1c to clean PC Data Parity Error flag */
            stMcalAppMCMError.Location = PC_Data_ParityError;
        }

        stMcalAppMCMError.EFaddr = McmIf_GetFaultAddress();    /* record address */
        SystemSoftwareReset();
    }
#endif

    stMcalAppMCMError.Reg_MCM_LMFATR = McmIf_GetFaultAttribute();

    stMcalAppMCMError.Data_Hword = McmIf_GetFaultDataHigh();
    stMcalAppMCMError.Data_Lword = McmIf_GetFaultDataLow();

#if (RAMTSTIF_EIM_EN == RAMTSTIF_ENABLE)
    /* disable the EIM to inject ECC errors to SRAM */
    EIM_DRV_Deinit(INST_EIM1);
#endif

    if ((NCE_SRAM_L == ucMcalAppPEELOC) || (NCE_SRAM_U == ucMcalAppPEELOC))
    {
        RamTstIf_MCMECCISR();
    }
}
#endif

#if (MCAL_FTFC_Fault_IRQn_EN == MCAL_ENABLE)
void MCALAPP_CallBackFTFCFault_IRQHandler(void)
{
    if (TRUE == FLASH_DRV_GetDoubleBitFaultFlag())
    {
        /* clear the interrupt flag */
        FLASH_DRV_ClearDoubleBitFaultFlag();

        /* check whether the double-bit ECC fault us caused by emulation test */
        if (FTFx_FERCNFG_FDFD_MASK == (FTFx_FERCNFG & FTFx_FERCNFG_FDFD_MASK))
        {
            /* disable the the emulation and end the test */
            FLASH_DRV_ForceDoubleBitFaultDetectCmd(FALSE);
        }

        FlsTstIf_DoubleBitFaultISR();
    }
}
#endif

void MCALAPP_EnableCOMWakeup(void)
{
    /* Add implementation of EcuM_EnableWakeupSources() */
    ucMcalAppStandbyWakeupStatus = FALSE;
    ucMcalAppCOMWakeupStatus = TRUE;
    PINS_DRV_SetMuxModeSel(PCTRLA,12U,PCTRL_MUX_AS_GPIO);/*GPIO Mode*/
    PINS_DRV_ClearPortIntFlagCmd(GPIOA);
    PINS_DRV_SetPinIntSel(GPIOA,12U,PCTRL_INT_EITHER_EDGE);
    McuIf_EnableIRQ(MCUIF_PORTA_IRQn);
}

void MCALAPP_DisableCOMWakeup(void)
{
    /* Add implementation of EcuM_EnableWakeupSources() */
    PINS_DRV_SetPinIntSel(GPIOA,12,PCTRL_DMA_INT_DISABLED);
    PINS_DRV_SetPinIntSel(GPIOA, (uint32)12, PCTRL_MUX_ALT3);
    ucMcalAppCOMWakeupStatus = FALSE;
    if(((uint8)FALSE == ucMcalAppIGNWakeupStatus)&&((uint8)FALSE == ucMcalAppCOMWakeupStatus))
    {
        McuIf_DisableIRQ(MCUIF_PORTA_IRQn);
    }
}

