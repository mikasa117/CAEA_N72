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
#include "v_inc.h"
#include "ccl.h"
#include "CanApp.h"
#include "Appl_Can_Callback.h"
//#include "STD_PowerMode_Cfg.h"
#include "NmStack_Types.h"
#include "ComStack_Types.h"
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
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE ApplCclBusOffEnd(void)
{ 
    CanApp_u_SetBusOffStaus(FALSE);
    IlSendOnInitMsg();
}
/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE ApplCclBusOffStart(void)
{
    CanApp_u_SetBusOffStaus(TRUE);
    SetCanApp_BusOffOccurNumInc();
}
/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/

void CCL_API_CALLBACK_TYPE ApplCclComStart(void)
{
    
}
/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE ApplCclComStop(void)
{ 
    
}
/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE ApplCclComWait(void)
{
    CanApp_u_SetBusOffStaus(FALSE);
    SetCanApp_BusOffOccurNumClr();
}
/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE ApplCclComResume(void)
{

}
/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :
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
        break;
    }
    return( rval );
    
}
/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE ApplCclInit(void)
{ 

}
/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/

void CCL_API_CALLBACK_TYPE CbkWakeupValidationNotification(void)
{

}
/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE CbkWakeupbyBus(void)
{
    /*CanApp_InitMemory();*/
    CanApp_u_SetNetWorkStaus(1U);
    ApplCanSetWakeupFlag();

}
/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE CbkFirstCommunicationRequest(void)
{
    CanApp_u_SetNetWorkStaus(1U);
}
/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CCL_API_CALLBACK_TYPE CbkBusSleep(void)
{
    CanApp_u_SetNetWorkStaus(0U);
    CanApp_SetWakeUpSource_Nm(0U);
    ApplCanClearWakeupFlag();
}

void ApplCclCbdWrpStateChange(NetworkHandleType nmChannelHandle, Nm_StateType nmPreviousState, Nm_StateType nmCurrentState )
{
    if(0u != nmChannelHandle)
    {
    
    }
    if((NM_STATE_BUS_SLEEP == nmPreviousState) && (NM_STATE_REPEAT_MESSAGE == nmCurrentState))
    {
        CanApp_EnableRequestCommunication();
        ApplCanSetNMBussleepToRepeatFlag(1U);

        if(1U == CanApp_GetAwakeSource_Nm())
        {
            CanApp_SetWakeUpSource_Nm(1U);
        }
    }
    else
    {}
    if (NM_STATE_BUS_SLEEP == nmCurrentState)
    {
        CanApp_DisableRequestCommunication();
    }
    if((NM_STATE_PREPARE_BUS_SLEEP == nmCurrentState) && (0u != CanApp_GetDiagReqNet()))
    {
        DescInit(0);
    }
}
