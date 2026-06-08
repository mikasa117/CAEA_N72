/*******************************************************************************
|  File Name:  STD_AdcIf.c
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
| 2018-05-23    01.00.00     XYJ       Creation
|******************************************************************************/
#ifndef _MCAL_ADCIF_H_
#define _MCAL_ADCIF_H_

/*******************************************************************************
|	 Other Header File Inclusion
|******************************************************************************/

#include "STD_AdcIf_Cfg.h"
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
|	 Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|	 Global Variable with extern linkage
|******************************************************************************/

/*******************************************************************************
|	 Global Function Prototypes
|******************************************************************************/

extern void AdcIf_Init(void);
extern void AdcIf_DeInit(void);
extern void AdcIf_0_Start(void);
extern void AdcIf_0_ConfigGropChannel(uint8 HwChannels);
extern void AdcIf_1_ConfigGropChannel(void);
extern uint8 AdcIf_0_GetGropConvCompleteFlag(void);
extern uint8 AdcIf_1_GetGropConvCompleteFlag(void);
extern void AdcIf_0_GetGropChannelResult(uint16 * const pConvResult);
extern void AdcIf_1_GetGropChannelResult(uint16 * const pConvResult);

#endif /* _MCAL_ADCIF_H_ */

