/*******************************************************************************
|  File Name:  
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
#include "tp_cfg.h"
#include "Appl_Tp_Callback.h"
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

static CanRxInfoStructPtr TpCbkRxMsgInformation;


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
vuint8 PreMessageFitter(CanRxInfoStructPtr rxStruct)
{
  vuint8 Appl_tp_u_return;
  vuint16 Appl_tp_w_StdId;
  static vuint16 Appl_tp_w_PreStdId = (vuint16)0x000;
  Appl_tp_w_StdId = CanRxActualStdId(rxStruct);
  if((*(rxStruct->pChipData)) == (vuint8)0x30U)
  {
    if(Appl_tp_w_StdId == (vuint16)0x7DF)
    {
      Appl_tp_u_return = 0U;
    }
#if (PRO_U1EI21_L == PROJECT_MR)
    else if(Appl_tp_w_StdId == (vuint16)0x761)
#else
    else if(Appl_tp_w_StdId == (vuint16)0x7A2)
#endif
    {
      if(Appl_tp_w_PreStdId == (vuint16)0x7DF)
      {
#if (PRO_U1EI21_L == PROJECT_MR)
        Appl_tp_w_StdId = (vuint16)0x761;
#else
	    Appl_tp_w_StdId = (vuint16)0x7A2;
#endif
      }
      Appl_tp_u_return = 1U;
    }
    else
    {
      Appl_tp_u_return = 1U;
    }
  }
  else
  {
    Appl_tp_u_return = 1U;
  }
  Appl_tp_w_PreStdId = Appl_tp_w_StdId;
#if (PRO_U1EI21_L == PROJECT_MR)
  TpTxSetChannelID((vuint8)0x00, (vuint16)0x769, (vuint16)Appl_tp_w_StdId);
#else
  TpTxSetChannelID((vuint8)0x00, (vuint16)0x7AA, (vuint16)Appl_tp_w_StdId);
#endif
  return Appl_tp_u_return;
}
/*******************************************************************************
Name			:
Syntax			: 
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None
Description		:
Call By			:
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
t_ta_type TargetAddrFitter(vuint8 tpCurrentTargetAddress)
{
    t_ta_type ReturnValue = kTpNone;    
#if (PRO_U1EI21_L == PROJECT_MR)
	if(0x04u == tpCurrentTargetAddress)
#else
	if(0xA2u == tpCurrentTargetAddress)
#endif
	{
		ReturnValue = kTpPhysical;	
	}
	else if(0xDFu == tpCurrentTargetAddress)
	{
		ReturnValue = kTpFunctional;		
	}
	else
	{
		ReturnValue = kTpNone;	
	}
	return ReturnValue;
	
}









