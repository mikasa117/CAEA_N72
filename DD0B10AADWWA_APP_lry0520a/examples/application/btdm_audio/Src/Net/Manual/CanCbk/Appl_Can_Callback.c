/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Can_Trcv.h"
#include "Vector_Platform_Types.h"
#include "BusOff_Recovery.h"
#include "v_inc.h"
#include "ccl.h"
#include "ccl_inc.h"
#include "CanApp.h"
// #include "Appl_Can_Callback.h"
#include "Adc_If.h"
#include "CanAppCfg.h"
#include "can_def.h"
#include "drv_par.h"
#include "CanApp.h"
#include "Can_par.h"
#include "CanAppCfg.h"
#include "Appl_Can_Callback.h"
#include "ccl_inc.h"
#include "Can_Trcv.h"
#include "NmControl.h"
#include "Dio_If.h"
#include "Rte_Can.h"
#include "CanApp.h"
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
static uint8 ApplCanWakeupSource = 0x00u;
static uint8 ApplCanBussleepToRepeatFlag = 0x00u;
static uint8 ApplCanSWakeUpNegtiveFlag = 0x01u;
static uint8 ApplCanSWakeUpPositiveFlag = 0x00u;


uint8 ApplCanSWakeUpChgFlag = 0x00u;
 uint8 ApplCanFastTxProtectTimer = 0u;  /* 快发保护计时器，防止C模式干扰 */


static uint16 ApplCan_BusWakeupTimeout_ms = 0; // 用于倒计时的静态变量

/* 的状态标志位 */
static uint8 ApplCanInformationCANFlag = 0x00u;      /* Information_CAN标志 */
static uint8 ApplCanDiagnosisServiceFlag = 0x00u;    /* Diagnosis service标志 */
static uint8 ApplCanWakeupReasonsFlag = 0x00u;       /* Wakeup reasons标志 */

/* TWait_DiagReq 5s延时计时器相关变量 */
static uint32 ApplCanDiagReqTimer = 0u;              /* 诊断请求计时器 */
static uint8 ApplCanDiagReqTimerActive = 0u;         /* 计时器激活标志 */
#define DIAG_REQ_WAIT_TIME_MS    500u               /* 延时时间 */
#define TASK_CYCLE_MS            10u                 /* 任务周期10ms */
#define DIAG_REQ_WAIT_CYCLES     (DIAG_REQ_WAIT_TIME_MS / TASK_CYCLE_MS)  /* 500个周期 */

/* Information_CAN超时清除计时器 */
static uint32 InformationCANTimer = 0u;
#define INFORMATION_CAN_TIMEOUT_CYCLES 1u  /* 超时 (10ms*1) */



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

vuint8  ApplCanMsgReceived(CanRxInfoStructPtr rxStruct)
{
	vuint8 currentRetVal = kCanCopyData;

   return currentRetVal;
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
vuint8 Pretransmit_DMM_StatusInfo(CanTxInfoStruct ctis)
{
	// 在发送前计算E2E校验，确保第一帧就有正确的校验值
	DMM_CalculateChecksum();
	return kCanCopyData;
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
vuint8 Pretransmit_NmMsg(CanTxInfoStruct ctis)
{
	return kCanCopyData;
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
void ApplCanSetWakeupSource(vuint8 LeCan_u_Temp)
{
	/* Update stored wakeup source */
	ApplCanWakeupSource = LeCan_u_Temp;
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
uint8 ApplCanGetCanBusWakeupValid(void)
{
	return 0;
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
uint8 ApplCanGetNMBussleepToRepeatFlag(void)
{
	return ApplCanBussleepToRepeatFlag;
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
uint8 ApplCanGetWakeupSource(void)
{
	return ApplCanWakeupSource;
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
void ApplCanClearNMBussleepToRepeatFlag(void)
{
	ApplCanBussleepToRepeatFlag = 0U;
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
void ApplCanClearWakeupSource(void)
{
	ApplCanWakeupSource = 0U;
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
void ApplCanSetNMBussleepToRepeatFlag(vuint8 LeCan_u_Temp)
{
	ApplCanBussleepToRepeatFlag = LeCan_u_Temp;
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
void ApplCanSetWakeUpPositiveFlag(void)
{
	ApplCanSWakeUpPositiveFlag = TRUE;
	ApplCanSWakeUpNegtiveFlag = FALSE;


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
void ApplCanSetWakeUpNegtiveFlag(void)
{
	ApplCanSWakeUpPositiveFlag = FALSE;
	ApplCanSWakeUpNegtiveFlag = TRUE;


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
/*设置诊断服务标志 */
void ApplCanSetDiagnosisServiceFlag(void)
{
	ApplCanDiagnosisServiceFlag = 0x01u;
	/* 启动5s延时计时器 */
	ApplCanDiagReqTimer = DIAG_REQ_WAIT_CYCLES;
	ApplCanDiagReqTimerActive = 1u;

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
/* 清除诊断服务标志 */
void ApplCanClearDiagnosisServiceFlag(void)
{
	ApplCanDiagnosisServiceFlag = 0x00u;
	/* 停止5s延时计时器 */
	ApplCanDiagReqTimer = 0u;
	ApplCanDiagReqTimerActive = 0u;

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
/*设置Information_CAN标志 */
void ApplCanSetInformationCANFlag(void)
{
	ApplCanInformationCANFlag = 0x01u;
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
/* 清除Information_CAN标志 */
void ApplCanClearInformationCANFlag(void)
{
	ApplCanInformationCANFlag = 0x00u;
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
/* TWait_DiagReq 5s延时计时器任务函数 */
void ApplCanDiagReqTimerTask(void)
{
    if(ApplCanDiagReqTimerActive) {
        if(ApplCanDiagReqTimer > 0u) {
            ApplCanDiagReqTimer--;
            
            if(ApplCanDiagReqTimer == 0u) {
                /* 5s延时到达，向网络管理模块发送网络请求 */

                // CclRequestCommunication(0U);

                
                /* 停用计时器 */
                ApplCanDiagReqTimerActive = 0u;
                
                /* 清除诊断服务标志 */
                ApplCanDiagnosisServiceFlag = 0x00u;
                

            }
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
void TxAckCbk_MREBL_1(CanTransmitHandle txObject)
{
	CanApp_SetTxOkF();

}

/*==========================================================================
 *  Function:  ApplCanMsgCondReceived
 *  Purpose :  Wrapper for conditional CAN message reception.
 *            The Vector driver may call this callback when a message
 *            satisfies a configured condition (e.g. wake‑up filter).
 *            We forward the call to the existing ApplCanMsgReceived
 *            implementation so that all message handling (diagnostic,
 *            wake‑up source classification, timer start, etc.) stays
 *            in one place.
 *==========================================================================*/
//void C_CALLBACK_2 ApplCanMsgCondReceived(CanRxInfoStructPtr rxStruct)
//{
//    /* Defensive check – driver should never pass NULL, but we guard anyway */
//    if (rxStruct == NULL) {
//        return;
//    }


//    ApplCanMsgReceived(rxStruct);
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
void TxAckCbk_MMI_TextMMData(CanTransmitHandle txObject)
{
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
void TxAckCbk_BTM_DiagResp(CanTransmitHandle txObject)
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
void TxAckCbk_MMI_Status_Info(CanTransmitHandle txObject)
{
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
void TxAckCbk_TTS_Status(CanTransmitHandle txObject)
{
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
void TxAckCbk_MMI_TextBTData(CanTransmitHandle txObject)
{
	SetCanApp_BusOffOccurNumClr();
}
