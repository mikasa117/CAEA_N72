/*******************************************************************************
|  File Name:  McuIf_Cfg.h
|  Description:  Implementation of the McuIf Config Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           XiaYaJun          CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 2018-05-23    01.00.00     XYJ       Creation
|******************************************************************************/
#ifndef _MCAL_MCUIF_CFG_H_
#define _MCAL_MCUIF_CFG_H_


/*******************************************************************************
|	 Other Header File Inclusion
|******************************************************************************/
//#include "Std_Types.h"
//#include "system_YTM32B1MC0.h"
//#include "power_manager.h"
#include "YTM32B1ME0/startup/system_YTM32B1ME0.h"
#include "clock_config.h"
//#include "rcu_driver.h"
//#include "rcu_hw_access.h"
#include "device_registers.h"


/*******************************************************************************
|    Macro Definition
|******************************************************************************/

#define MCUIF_MODE_RUN   	    0     /*!< Run mode. */
#define MCUIF_MODE_SLEEP  	    1     /*!< Sleep mode.  */
#define MCUIF_MODE_DEEPSLEEP  	2     /*!< Deepsleep mode.  */
#define MCUIF_MODE_STANDBY  	3     /*!< Standby mode.  */

#define MCUIF_POWER_MODES 	4

/*mmark*/
#define MCUIF_LowVoltDetectResetS		RESET_REASON_POR_LVD/*!< High voltage detect reset */
//#define MCUIF_LossOfClkResetS			RCU_RESET_REASON_DEEPSLEEPACK/*!< Loss of clock reset */
//#define MCUIF_LossOfLockResetS			RCU_RESET_REASON_CORELOCK/*!< Loss of lock reset */
#define MCUIF_WatchDogResetS			RESET_REASON_WDG/*!< Watch dog reset */
#define MCUIF_ExternalPinResetS			RESET_REASON_PIN/*!< External pin reset */
//#define MCUIF_PowerOnResetS				RCM_POWER_ON/*!< Power on reset */
#define MCUIF_SJtagResetS				RESET_REASON_DEBUG /*!< JTAG generated reset */
#define MCUIF_CoreLockUpResetS			RESET_REASON_CORELOCK/*!< core lockup reset */
#define MCUIF_SoftwareResetS			RESET_REASON_SOFTWARE_RESET/*!< Software reset */
//#define MCUIF_SMDM_APResetS				RCM_SMDM_AP/*!< MDM-AP system reset */
#define MCUIF_StopModeAckErrorResetS	RESET_REASON_DEEPSLEEPACK/*!< Stop mode ack error reset */

#define MCUIF_WDOG_EWM_IRQn 	WDG_IRQn /**< Single interrupt vector for WDOG and EWM */
#define MCUIF_LPIT0_Ch0_IRQn 	pTMR0_Ch0_IRQn/**< LPIT0 channel 0 overflow interrupt */
#define MCUIF_LPIT0_Ch1_IRQn 	pTMR0_Ch1_IRQn/**< LPIT0 channel 1 overflow interrupt */
#define MCUIF_LPIT0_Ch2_IRQn 	pTMR_Ch2_IRQn/**< LPIT0 channel 2 overflow interrupt */
#define MCUIF_LPIT0_Ch3_IRQn 	pTMR_Ch3_IRQn/**< LPIT0 channel 3 overflow interrupt */
#define MCUIF_LPTMR0_IRQn 		lpTMR0_IRQn/**< LPTIMER interrupt request */
#define MCUIF_ADC0_IRQn         ADC0_IRQn
#define MCUIF_ADC1_IRQn         ADC1_IRQn
#define MCUIF_PORTA_IRQn 		GPIOA_IRQn/**< Port A pin detect interrupt */
#define MCUIF_PORTB_IRQn 		GPIOB_IRQn/**< Port B pin detect interrupt */
#define MCUIF_PORTC_IRQn 		GPIOC_IRQn/**< Port C pin detect interrupt */
#define MCUIF_PORTD_IRQn 		GPIOD_IRQn/**< Port D pin detect interrupt */
#define MCUIF_PORTE_IRQn 		GPIOE_IRQn/**< Port E pin detect interrupt */



/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
//typedef rcu_source_names_t	McuIf_ResetSrcType;
typedef IRQn_Type McuIf_IRQnType;


/*******************************************************************************
|	 Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|	 Global Variable with extern linkage
|******************************************************************************/

/*******************************************************************************
|	 Global Function Prototypes
|******************************************************************************/


#endif /* _MCAL_MCUIF_CFG_H_ */

