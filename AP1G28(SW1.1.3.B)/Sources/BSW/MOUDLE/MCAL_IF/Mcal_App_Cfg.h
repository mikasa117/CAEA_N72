/*******************************************************************************
|  File Name:  Mcal_APP_Cfg.h
|  Description:  Implementation of the STD_AdcIf Config Management
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
| 2018-06-11    01.00.00     XYJ       Creation
|******************************************************************************/

#ifndef _MCAL_APP_CFG_H_
#define _MCAL_APP_CFG_H_


/*******************************************************************************
|	 Other Header File Inclusion
|******************************************************************************/
#include "STD_AdcIf.h"
//#include "STD_DioIf.h"
//#include "STD_GptIf.h"
#include "STD_McuIf.h"
#include "STD_PortIf.h"
//#include "STD_PwmIf.h"
//#include "STD_WdgIf.h"
//#include "SysTypes.h"

//#include "STD_SpiIf.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define MCAL_CODE_RAM	//__attribute__ ((section(".BSW_RAM_DATA")))
#define MCAL_CODE_KAM	//__attribute__ ((section(".BSW_KAM_DATA")))

#define MCAL_DISABLE	(0u)
#define MCAL_ENABLE	(1u)

#define MCALAPP_LPIT1_Ch0_EN		MCAL_ENABLE
#define MCALAPP_LPIT1_Ch1_EN		MCAL_ENABLE
#define MCALAPP_LPIT1_Ch2_EN		MCAL_DISABLE
#define MCALAPP_LPIT1_Ch3_EN		MCAL_DISABLE

#define MCAL_WDOG_EWM_IRQn_EN 		MCAL_DISABLE
#define MCAL_RTC_IRQn_EN 			MCAL_DISABLE
#define	MCAL_LPIT1_Ch0_IRQn_EN		MCAL_ENABLE
#define	MCAL_LPIT1_Ch1_IRQn_EN		MCAL_ENABLE
#define	MCAL_LPIT1_Ch2_IRQn_EN		MCAL_DISABLE
#define	MCAL_LPIT1_Ch3_IRQn_EN		MCAL_DISABLE
#define	MCAL_ADC0_IRQn_EN			MCAL_DISABLE
#define	MCAL_ADC1_IRQn_EN			MCAL_ENABLE
#define	MCAL_LPTMR0_IRQn_EN			MCAL_DISABLE
#define	MCAL_PORTA_IRQn_EN			MCAL_ENABLE
#define	MCAL_PORTB_IRQn_EN			MCAL_DISABLE
#define	MCAL_PORTC_IRQn_EN			MCAL_DISABLE/* KL15 CAN_RX */
#define	MCAL_PORTD_IRQn_EN			MCAL_DISABLE
#define	MCAL_PORTE_IRQn_EN			MCAL_DISABLE

#define	MCAL_ERM_double_fault_IRQn_EN MCAL_DISABLE
#define MCAL_ETMR0_CH0_CH1_EN         MCAL_ENABLE
#define	MCAL_MCM_IRQn_EN			  MCAL_DISABLE
#define	MCAL_FTFC_Fault_IRQn_EN		  MCAL_DISABLE
#define MCAL_ETMR0_VOERFLOW_EN      MCAL_ENABLE
#define MCAL_MONITOR_EN		        MCAL_DISABLE

#define MCAL_WKU_RTC_IRQ                0u
#define MCAL_WKU_RTC_Seconds_IRQ        1u
#define MCAL_WKU_lpTMR0_IRQ             2u
#define MCAL_WKU_ACMP0_IRQ              3u

#define INST_PTMR     0
#define GPTIF_LPIT1_Ch0_ID	(0u)
#define GPTIF_LPIT1_Ch1_ID	(1u)
#define GPTIF_LPIT1_Ch2_ID	(2u)
#define GPTIF_LPIT1_Ch3_ID	(3u)
#define GPTIF_StartLPITTimer(CtrChannel)	pTMR_DRV_StartTimerChannels(INST_PTMR,(CtrChannel))
#define GPTIF_LPITClearTimerInterruptFlag(CtrChannel)	pTMR_DRV_ClearInterruptFlagTimerChannels(INST_PTMR, (CtrChannel))
/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|	 Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|	 Global Variable with extern linkage
|******************************************************************************/

/*******************************************************************************
|	 Global Function Prototypes
|******************************************************************************/



#endif /* _MCAL_APP_CFG_H_ */
