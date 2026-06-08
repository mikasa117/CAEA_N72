/*
 * EcuM_Cfg.c
 *
 *  Created on: 20251029
 *      Author: WCj
 */
/*******************************************************************************
|  File Name :  EcuM_Cfg.c
|  Description:
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA)
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
|               ECC  			CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
| 2025-10-29    1.0.1    WCj
 *******************************************************************************/
#include "EcuM_Cfg.h"
#include "STD_McuIf.h"
#include "Mcal_App.h"
#include "Etmr_If.h"
 //#include "STD_DioIf.h"
//#include "STD_PortIf.h"
#include "STD_AdcM.h"
#include "STD_AdcIf.h"
#include "STD_BtrM.h"
#include "STD_EepM.h"
#include "Task.h"
#include "SysM.h"
//#include "STD_Interface.h"
#include "STD_WdgM.h"
#include "Can_Main.h"
//#include "flexcan_driver.h"
#include "ptmr_driver.h"
//#include "NtcM.h"
//#include "Gateway.h"
//#include "trng_config.h"
//#include "trng_driver.h"
#include "DID_Callback.h"
#include "RCU_RSSR_If.h"
#include "HallM.h"
#include "STD_SrM.h"
#include "Fridge_Basic_Control.h"
#include "LED_DriverM.h"
/******************************************************************************
* Function Name : void EcuMCfg_InitOne( void )
* Description   : This function initializes the Mcal
* Argument      : none
* Return Value  : none
******************************************************************************/
void EcuMCfg_InitOne(void)/**/
{
    (void)McuIf_ClockInit();
    
    /*RCU RSSR Register*/
    RCU_RSSR_IF_Get_HistoryRegFlag();
    RCU_RSSR_IF_Clear_HistoryFlag();

    MCALAPP_SetProgrammableInterrupts();
    //LIB_ENTER_EXCLUSIVE_AREA_0();/*PRQA S 3138*/
    //MCALAPP_DisableInterrupts();
    MCALAPP_PeripheralInit();
#if 0
    LIB_EXIT_EXCLUSIVE_AREA_0();


    (void)DMA_DRV_Init(&dmaState,&dmaController_InitConfig,dmaChnState,dmaChnConfigArray,NUM_OF_CONFIGURED_DMA_CHANNEL);
    (void)SPI_DRV_SlaveInit(0,&spi_SlaveConfig0_State,&spi_SlaveConfig0);
    (void)CLOCK_SYS_GetCurrentConfiguration();
#endif
    pTMR_DRV_Init(0, &PTMR_Config);
    pTMR_DRV_InitChannel(0, pTMR0_CH0, &ptmr_channel_0);
    pTMR_DRV_InitChannel(0, pTMR0_CH1, &ptmr_channel_1);


    EtmrIf_Init();

    TMU_DRV_Init(0,&tmu_config0);
    MCALAPP_StartGpt();

    WDGM_Init();
    SysM_InitMemory();
	FLASH_DRV_Init(0, &flash_config0, &flash_config0_State);   //ggl
	
#if 0
    //WDGM_SetMode(WDGM_MODE_SLOW);

    SpiIf_Init();
#endif
    Task_InitMemory();
   
}
/******************************************************************************
* Function Name : void EcuMCfg_InitTwo( void )
* Description   : This function initializes the ComplexDrvs
* Argument      : none
* Return Value  : none
******************************************************************************/
void EcuMCfg_InitTwo(void)/**/
{
    
	EEPM_InitMemory();
    EEPM_SetUp(CAEA_FALSE,CAEA_FALSE);
    ADCM_InitMemory();
    BTRM_InitMemory();
    BTRM_InitKamMemory();
    SRM_InitMemory();
    HALL_M_InitMemory();
    HALL_M_InitKamMemory();
    LED_DRV_M_InitMemory();
    #if 0
    
    EEPM_InitMemory();
	EEPM_SetUp(CAEA_FALSE,CAEA_FALSE);
    NtcM_Init();
    #endif 
}
/******************************************************************************
* Function Name : void EcuMCfg_InitThree( void )
* Description   : This function initializes the Communication
* Argument      : none
* Return Value  : none
******************************************************************************/
void EcuMCfg_InitThree(void)/**/
{
    CanMain_InitMemory(0u);
    CanMain_InitMemory(1u);
    #if 0
    TRNG_DRV_Init(TRNG_INST,TRNG_ENTROPY_DELAY);
  //  EEPM_SetUp(CAEA_FALSE,CAEA_FALSE);
    Gateway_InitMemory();

	WDGM_Trigger();
	//uUpdateFlag = UartSys_GetUpdateFlag();
	/* have read all data from data flash */
#endif 
}
/******************************************************************************
* Function Name : void EcuMCfg_InitFour( void )
* Description   : This function initializes the UART Service
* Argument      : none
* Return Value  : none
******************************************************************************/
void EcuMCfg_InitFour(void)/**/
{
    /* Fridge Basic Control Init Function */
    FridgeCtrl_Initialization();
}
/******************************************************************************
* Function Name : void EcuMCfg_InitOver( void )
* Description   : This function Start the gpt
* Argument      : none
* Return Value  : none
******************************************************************************/
void EcuMCfg_InitOver(void)/**/
{
    LIB_ENTER_EXCLUSIVE_AREA_0();
    MCALAPP_SetInterruptsPriority();
    MCALAPP_EnableInterrupts();
    LIB_EXIT_EXCLUSIVE_AREA_0();/*PRQA S 3138*/
}

