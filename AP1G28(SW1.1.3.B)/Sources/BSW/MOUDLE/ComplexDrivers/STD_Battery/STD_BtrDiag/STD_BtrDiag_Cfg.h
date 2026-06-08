/*******************************************************************************
|  File Name:  STD_BtrDiag_Cfh.h
|  Description:  Implementation of the Battery voltage Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| LSG           SiGuang Li             CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2017-07-26    01.00.00     LSG       Creation
|
|******************************************************************************/
#ifndef _STD_BTRDIAG_CFG_H
#define _STD_BTRDIAG_CFG_H


/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Std_Types.h"
#include "STD_AdcM.h"
#include "STD_Lib.h"

/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define BTRDIAG_CODE_RAM	//__attribute__ ((section(".BSW_RAM_DATA")))

#define BTRDIAG_GetBatteryValidValue()	ADCM_GetValidValue((uint8)ADCMCFG_KL30_AD_CH)

#define	BTRDIAG_TASK_PERIOD				       	(10U)

#define BTRDIAG_FILTER_200MS					(200U/BTRDIAG_TASK_PERIOD)

#define BTRDIAG_VOLTAGE_FILTER_TIME				BTRDIAG_FILTER_200MS

/*config Battery Sampling Precision*/
#define BTRDIAG_SAMPLE_PRECISION_10BIT_ENABLE		(0u)
#define BTRDIAG_SAMPLE_PRECISION_12BIT_ENABLE		(1u)

#if (1u == BTRDIAG_SAMPLE_PRECISION_10BIT_ENABLE)

#define BTRDIAG_THRESHOLD_LOW_BATTERY_IN		327U	/*8.5V*/
#define BTRDIAG_THRESHOLD_HIGH_BATTERY_IN		634U	/*16.5V*/
#define BTRDIAG_THRESHOLD_LOW_BATTERY_OUT       347U    /*8.0V*/
#define BTRDIAG_THRESHOLD_HIGH_BATTERY_OUT      617U    /*16.0V*/

#else
//(KL30-0.05)*154.83
#define BTRDIAG_THRESHOLD_LOW_BATTERY_IN		1308u  //1306u	/*8.5V*/
#define BTRDIAG_THRESHOLD_HIGH_BATTERY_IN		2547u  //2535u	/*16.5V*/
#define BTRDIAG_THRESHOLD_LOW_BATTERY_OUT       1385u  //1383u   /*9.0V*/
#define BTRDIAG_THRESHOLD_HIGH_BATTERY_OUT      2469u  //2458u   /*16.0V*/

#endif



/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Global Variable with extern linkage
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/


#endif

