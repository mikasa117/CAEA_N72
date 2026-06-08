/*******************************************************************************
|  File Name:  STD_AdcF_Cfg.h
|  Description:  Implementation of the Adc Config Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           YaJun Xia          CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2016-10-18    01.00.00     XYJ       Creation
|
|******************************************************************************/

#if !defined (_STD_ADCF_CFG_H)
/* polyspace<MISRA-C3:2.5:Not a defect:Other> No fluence *//* polyspace<MISRA-C3:21.1:Not a defect:Other> No fluence */
#define _STD_ADCF_CFG_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Typedef.h"
#include "STD_AdcMCfg.h"
/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define ADCF_CODE_RAM	//__attribute__ ((section(".BSW_RAM_DATA")))
/* polyspace<MISRA-C3:2.5:Not a defect:Other> No fluence */
#define ADCFCFG_DISABLE                      		(0u)
#define ADCFCFG_ENABLE			            		(1u)

/*max collect num*/
#define	ADCFCFG_AD_INIT_VALUE					    (0xFFFFu)

/*config the method class*/
#define	ADCFCFG_CLASS_BUDDLE_MIDDLE		    		ADCFCFG_ENABLE
#define	ADCFCFG_CLASS_BUDDLE_AVERAGE		    	ADCFCFG_ENABLE
#define	ADCFCFG_CLASS_SIMPLE_AVERAGE		    	ADCFCFG_ENABLE
#define	ADCFCFG_CLASS_FAST_AVERAGE		    		ADCFCFG_ENABLE

#define	ADCFCFG_COLLECT_MAX_NUM	            		(6u)
#define	ADCFCFG_CH_MAX_NUM 							ADCMCFG_CH_MAX_NUM

/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Table Definition
|******************************************************************************/
/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/

#endif
/*EOF*/
