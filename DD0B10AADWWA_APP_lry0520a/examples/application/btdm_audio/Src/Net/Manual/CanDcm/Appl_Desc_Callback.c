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
#include <NET/Manual/CanDcm/Appl_Desc_Callback.h>
#include "Vector_Platform_Types.h"
#include "v_inc.h"
#include "tp_cfg.h"
#include "desc.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#if (PRO_U1EI21_L == PROJECT_MR)
#define kNormalAddressingTxId        (vuint16)0x761
#define kNormalAddressingPhysRxId    (vuint16)0x769
#else
#define kNormalAddressingTxId        (vuint16)0x7AA
#define kNormalAddressingPhysRxId    (vuint16)0x7A2
#endif
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
|    Extern variables and functions declaration
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/
canuint8* DispatcherDescGetBuffer(canuint8 tpChannel, canuint16 datLen)
{
	vuint8* retPtr = V_NULL;
	retPtr = DescGetBuffer(tpChannel,datLen);
	if(retPtr != V_NULL)
	{
		if((TpRxGetAddressingFormat(tpChannel) == (uint16)kTpNormalAddressing))
		{
			TpRxSetTransmitID(0U, kNormalAddressingTxId); /* set diag respone ID */
		}
	}
	return retPtr;
}

void DispatcherDescPhysReqInd(canuint8 tpChannel, canuint16 datLen)
{
    vuint8 addressingType= (TpRxGetAddressingFormat(tpChannel));
	
    DescPhysReqInd(tpChannel, datLen);    
	/*Set CAN IDs for the Response*/
    if((addressingType == kTpNormalAddressing))
    {
        TpTxSetChannelID(0, kNormalAddressingTxId, kNormalAddressingPhysRxId); 
    }
}






