/*******************************************************************************
|  File Name:  Can_Main.c
|  Description:  Implementation of the Dem_DTC_Detection Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| 
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date        Version   Author  Description
| ----------  --------  ------  ------------------------------------------------
| 2016-10-11  V1.0      chenf   first implementation

|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Can_Trcv.h"
#include "Vector_Platform_Types.h"
#include "v_inc.h"
#include "ccl.h"
#include "ccl_inc.h"
#include "CanApp.h"
#include "Appl_Ccl_Callback.h"
#include "NmControl.h"
#include "CanAppCfg.h"
#include "Appl_Can_Callback.h"

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
|    Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|    static Local Functions Declaration
|******************************************************************************/

/*******************************************************************************
|    static Local Functions Declaration
|******************************************************************************/

/*******************************************************************************
Name			:
Syntax			: 
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		:
Call By			:
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE ApplCclBusOffEnd(void)
{ 
	CanApp_u_SetBusOffStaus(FALSE);
	/*IlSendOnInitMsg();*/
}
/*******************************************************************************
Name			:
Syntax			: 
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		:
Call By			:
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE ApplCclBusOffStart(void)
{
	CanApp_u_SetBusOffStaus(TRUE);
	SetCanApp_BusOffOccurNumInc();
}
/*******************************************************************************
Name			:
Syntax			: 
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		:
Call By			:
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE ApplCclComStart(void)
{
	
}
/*******************************************************************************
Name			:
Syntax			: 
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		:
Call By			:
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE ApplCclComStop(void)
{ 

}
/*******************************************************************************
Name			:
Syntax			: 
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		:
Call By			:
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE ApplCclComWait(void)
{
	CanApp_u_SetBusOffStaus(FALSE);
	SetCanApp_BusOffOccurNumClr();

}
/*******************************************************************************
Name			:
Syntax			: 
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		:
Call By			:
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE ApplCclComResume(void)
{

}
/*******************************************************************************
Name			:
Syntax			: 
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		:
Call By			:
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
vuint8 ApplCclCanStandby( vuint8 sleepResult)
{
	vuint8 rval;
	switch( sleepResult )
	{
		case kCanFailed:
			/* CanSleep() failed => try again */
			rval = kCclRepeatCanSleep;
		break;
		default:
			rval = kCclNoRepeatCanSleep;
	}
	return( rval );
	
}
/*******************************************************************************
Name			:
Syntax			: 
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		:
Call By			:
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE ApplCclInit(void)
{ 

}
/*******************************************************************************
Name			:
Syntax			: 
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		:
Call By			:
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE CbkWakeupValidationNotification(void)
{

}
/*******************************************************************************
Name			:
Syntax			: 
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		:
Call By			:
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE CbkWakeupbyBus(void)
{

}
/*******************************************************************************
Name			:
Syntax			: 
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		:
Call By			:
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE CbkFirstCommunicationRequest(void)
{
	extern uint8 SeCanTrcv_u_ModeCCheckDelay;
	
	/* 回滚：不在此处强唤醒收发器，避免与NM状态机打架 */
 	
 	CanApp_u_SetNetWorkStaus(1U);
 	
 	/* 检查唤醒源：区分主动唤醒和被动唤醒 */
 	uint8 wakeupSource = ApplCanGetWakeupSource();
	
	if(wakeupSource == 2U)  /* 2 = 被动唤醒(CAN总线唤醒) */
	{

		
		/* 被动唤醒时，保持初始延迟20u(100ms)，避免覆盖导致延迟不足 */
		if(SeCanTrcv_u_ModeCCheckDelay < 20u)
		{
			/* 只有当延迟已经很小时才重新设置为20u */
//			SeCanTrcv_u_ModeCCheckDelay = 10u;
		}
		/* 保持唤醒源=2，不修改 */
	}
	else  /* 主动唤醒(IGN或其他) */
	{

		/* 保持C模式检查延迟=40(已在CanTrcv_WakeUpTrcv中设置) */
		
		/* 根据IGN状态设置唤醒源（使用实时电压判断，避免滤波延迟） */
    
		if(1)
		//if(PWM_GetHwIgnStatus() != TRUE)  // 0:IGN ON  1:IGN OFF
		{
			ApplCanSetWakeupSource(1U); /*IGN WAKEUP*/
		}
		else
		{
			ApplCanSetWakeupSource(3U); /*Other positive WAKEUP*/
		}
	}
}
/*******************************************************************************
Name			:
Syntax			: 
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		:
Call By			:
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE CbkBusSleep(void)
{
	/* NM进入BusSleep：置网络状态为0并确保RMR清零，便于进入深睡 */
	CanApp_u_SetNetWorkStaus(0U);
}
/*******************************************************************************
Name			:
Syntax			: 
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		:
Call By			:
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
//void ApplCclCbdWrpStateChange(NetworkHandleType nmChannelHandle, Nm_StateType nmPreviousState, Nm_StateType nmCurrentState )
//{

//}
/*******************************************************************************
Name			:
Syntax			: 
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		:
Call By			:
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE CanTask(void)
{}
