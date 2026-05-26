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
#include "Appl_Il_CallBack.h"
#include "nmcbdwrp_cfg.h"
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
|    Static local variables Declaration
|******************************************************************************/

/* -----------------------------------------------------------------------------
    &&&~ Extern declarations of confirmation functions
 ----------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
    &&&~ Extern declarations of indication functions
 ----------------------------------------------------------------------------- */

/*******************************************************************************
Name			:
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: -
Call By			:
|******************************************************************************/
void IlMsgPMS_VINInd(CanReceiveHandle rcvObject)
{
	rcvObject = rcvObject;
	SetCanApp_MsgReceiveSts(VeCanApp_e_PMS_VIN);
	SetCanApp_MsgCurrentPresent(VeCanApp_e_PMS_VIN,1U);
  CanApp_SetVinLiveTimeoutTtimer(500u); // 500 * 10ms = 5s window
}
/*******************************************************************************
Name			:
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: -
Call By			:
|******************************************************************************/
void IlMsgIPK_TotalOdometerInd(CanReceiveHandle rcvObject)
{
	rcvObject = rcvObject;
	SetCanApp_MsgReceiveSts(VeCanApp_e_IPK_TotalOdometer);
	SetCanApp_MsgCurrentPresent(VeCanApp_e_IPK_TotalOdometer,1U);
}
/*******************************************************************************
Name			:
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: -
Call By			:
|******************************************************************************/
void IlMsgTBOX_DateTime_InfoInd(CanReceiveHandle rcvObject)
{
	rcvObject = rcvObject;
	SetCanApp_MsgReceiveSts(VeCanApp_e_TBOX_DateTime_Info);
	SetCanApp_MsgCurrentPresent(VeCanApp_e_TBOX_DateTime_Info,1U);
}

/*******************************************************************************
Name			:
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: -
Call By			:
|******************************************************************************/
void IlMsgEHB_StatusInd(CanReceiveHandle rcvObject)
{
	rcvObject = rcvObject;
	SetCanApp_MsgReceiveSts(VeCanApp_e_EHB_Status);
	SetCanApp_MsgCurrentPresent(VeCanApp_e_EHB_Status,1U);
}
/*******************************************************************************
Name			:
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: -
Call By			:
|******************************************************************************/
void ApplPMS_VIN_TimeoutMsgTimeout(void)
{
	SetCanApp_MsgCurrentPresent(VeCanApp_e_PMS_VIN,0U);
}
/*******************************************************************************
Name			:
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: -
Call By			:
|******************************************************************************/
void ApplIPK_TotalOdometer_TimeoutMsgTimeout(void)
{
	SetCanApp_MsgCurrentPresent(VeCanApp_e_IPK_TotalOdometer,0U);
}
/*******************************************************************************
Name			:
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: -
Call By			:
|******************************************************************************/
void ApplTBOX_DateTime_Info_TimeoutMsgTimeout(void)
{
	SetCanApp_MsgCurrentPresent(VeCanApp_e_TBOX_DateTime_Info,0U);
}
/*******************************************************************************
Name			:
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: -
Call By			:
|******************************************************************************/
void ApplEHB_Status_TimeoutMsgTimeout(void)
{
	SetCanApp_MsgCurrentPresent(VeCanApp_e_EHB_Status,0U);
}


/* -----------------------------------------------------------------------------
    &&&~ Extern declarations of Timeout functions
 ----------------------------------------------------------------------------- */


