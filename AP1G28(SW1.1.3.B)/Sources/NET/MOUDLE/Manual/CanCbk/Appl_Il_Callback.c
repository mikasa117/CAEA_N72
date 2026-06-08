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
/*******************************************************************************
Name            :
Reentrancy        : None
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : -
Call By            :
|******************************************************************************/
void IlMsgVIU_FR_1C3Ind(CanReceiveHandle rcvObject)
{
    rcvObject = rcvObject;
    SetCanApp_MsgCurrentPresent(VeCanApp_e_VIU_FR_1C3,1U);
    SetCanApp_MsgReceiveSts(VeCanApp_e_VIU_FR_1C3);
}
/*******************************************************************************
Name            :
Reentrancy        : None
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : -
Call By            :
|******************************************************************************/
void IlMsgVIU_FR_288Ind(CanReceiveHandle rcvObject)
{
    rcvObject = rcvObject;
    SetCanApp_MsgCurrentPresent(VeCanApp_e_VIU_FR_288,1U);
    SetCanApp_MsgReceiveSts(VeCanApp_e_VIU_FR_288);
}
/*******************************************************************************
Name            :
Reentrancy        : None
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : -
Call By            :
|******************************************************************************/
void IlMsgVIU_FR_2ECInd(CanReceiveHandle rcvObject)
{
    rcvObject = rcvObject;
    SetCanApp_MsgCurrentPresent(VeCanApp_e_VIU_FR_2EC,1U);
    SetCanApp_MsgReceiveSts(VeCanApp_e_VIU_FR_2EC);
}
/*******************************************************************************
Name            :
Reentrancy        : None
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : -
Call By            :
|******************************************************************************/
void IlMsgVIU_FR_2F7Ind(CanReceiveHandle rcvObject)
{
    rcvObject = rcvObject;
    SetCanApp_MsgCurrentPresent(VeCanApp_e_VIU_FR_2F7,1U);
    SetCanApp_MsgReceiveSts(VeCanApp_e_VIU_FR_2F7);
}
/*******************************************************************************
Name            :
Reentrancy        : None
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : -
Call By            :
|******************************************************************************/
void IlMsgVIU_FR_2EFInd(CanReceiveHandle rcvObject)
{
    rcvObject = rcvObject;
    SetCanApp_MsgCurrentPresent(VeCanApp_e_VIU_FR_2EF,1U);
    SetCanApp_MsgReceiveSts(VeCanApp_e_VIU_FR_2EF);
}
/*******************************************************************************
Name            :
Reentrancy        : None
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : -
Call By            :
|******************************************************************************/
void IlMsgVIU_FR_3D1Ind(CanReceiveHandle rcvObject)
{
    rcvObject = rcvObject;
    SetCanApp_MsgCurrentPresent(VeCanApp_e_VIU_FR_3D1,1U);
    SetCanApp_MsgReceiveSts(VeCanApp_e_VIU_FR_3D1);
}
/*******************************************************************************
Name            :
Reentrancy        : None
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : -
Call By            :
|******************************************************************************/
void IlMsgVIU_FR_3D3Ind(CanReceiveHandle rcvObject)
{
    rcvObject = rcvObject;
    SetCanApp_MsgCurrentPresent(VeCanApp_e_VIU_FR_3D3,1U);
    SetCanApp_MsgReceiveSts(VeCanApp_e_VIU_FR_3D3);
}
/*******************************************************************************
Name            :
Reentrancy        : None
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : -
Call By            :
|******************************************************************************/
void IlMsgVIU_FR_3EDInd(CanReceiveHandle rcvObject)
{
    rcvObject = rcvObject;
    SetCanApp_MsgCurrentPresent(VeCanApp_e_VIU_FR_3ED,1U);
    SetCanApp_MsgReceiveSts(VeCanApp_e_VIU_FR_3ED);
}

/************************ time out *******************************/
/*******************************************************************************
Name            :
Reentrancy        : None
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : -
Call By            :
|******************************************************************************/
void ApplVIU_FR_1C3MsgTimeout(void)
{
    SetCanApp_MsgCurrentPresent(VeCanApp_e_VIU_FR_1C3,0U);
}
/*******************************************************************************
Name            :
Reentrancy        : None
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : -
Call By            :
|******************************************************************************/
void ApplVIU_FR_288MsgTimeout(void)
{
    SetCanApp_MsgCurrentPresent(VeCanApp_e_VIU_FR_288,0U);
    IlGetRxBcmPwrStsFb() = CanMsg_BcmPwrStsFb_OFF;
}
/*******************************************************************************
Name            :
Reentrancy        : None
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : -
Call By            :
|******************************************************************************/
void ApplVIU_FR_2ECMsgTimeout(void)
{
    SetCanApp_MsgCurrentPresent(VeCanApp_e_VIU_FR_2EC,0U);
}
/*******************************************************************************
Name            :
Reentrancy        : None
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : -
Call By            :
|******************************************************************************/
void ApplVIU_FR_2F7MsgTimeout(void)
{
    SetCanApp_MsgCurrentPresent(VeCanApp_e_VIU_FR_2F7,0U);
}
/*******************************************************************************
Name            :
Reentrancy        : None
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : -
Call By            :
|******************************************************************************/
void ApplVIU_FR_2EFMsgTimeout(void)
{
    SetCanApp_MsgCurrentPresent(VeCanApp_e_VIU_FR_2EF,0U);
}
/*******************************************************************************
Name            :
Reentrancy        : None
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : -
Call By            :
|******************************************************************************/
void ApplVIU_FR_3D1MsgTimeout(void)
{
    SetCanApp_MsgCurrentPresent(VeCanApp_e_VIU_FR_3D1,0U);
}
/*******************************************************************************
Name            :
Reentrancy        : None
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : -
Call By            :
|******************************************************************************/
void ApplVIU_FR_3D3MsgTimeout(void)
{
    SetCanApp_MsgCurrentPresent(VeCanApp_e_VIU_FR_3D3,0U);
}
/*******************************************************************************
Name            :
Reentrancy        : None
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        : -
Call By            :
|******************************************************************************/
void ApplVIU_FR_3EDMsgTimeout(void)
{
    SetCanApp_MsgCurrentPresent(VeCanApp_e_VIU_FR_3ED,0U);
}
/* polyspace:end<MISRA-C3:17.8:Not a defect:Justified> NO fluence */
