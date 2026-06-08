/*
 * EcuM.c
 *
 *  Created on: 20251029
 *      Author: WCj
 */
/*******************************************************************************
|  File Name :  EcuM.c
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
#include "EcuM.h"




/*
void EcuM_PowerON(void);
void EcuM_PowerOFF(void);
*/
 /*******************************************************************************
Name			: Ecum_InitMemery
Syntax			: void Ecum_InitMemery(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
void Ecum_InitMemery(void)
{
	EcuMCfg_InitOne();
	EcuMCfg_InitTwo();
	EcuMCfg_InitThree();
	EcuMCfg_InitFour();
	EcuMCfg_InitOver();
}
 /*******************************************************************************
Name			: EcuM_SleepMainFunction
Syntax			: void EcuM_SleepMainFunction(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
void EcuM_SleepMainFunction(void)
{
	//SysPwr_MainFunction();

}
