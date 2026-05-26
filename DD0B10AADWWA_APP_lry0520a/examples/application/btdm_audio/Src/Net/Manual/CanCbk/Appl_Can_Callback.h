/**|******************************************************************************/
#ifndef APPL_CAN_CALLBACK_H
#define APPL_CAN_CALLBACK_H
/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Std_Types.h"
#include "v_def.h"
#include "can_def.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define CeCanCbk_u_BasicNMID    (vuint16)0x400
#define CeCanCbk_u_MaxNMID      (vuint16)0x47F

#define CeCanCbk_u_DiagPhyID    (vuint16)0x761
#define CeCanCbk_u_DiagFunID    (vuint16)0x7DF
#define APPL_CAN_WAKEUP_TIMEOUT_MS 3000 // 定义3秒的静默超时时间 (3000ms)

#define CeCanCbk_u_NmMsgDataLen   4u

/* Function declarations for CAN callbacks */

/* CAN消息接收处理函数 */
extern vuint8 ApplCanMsgReceived(CanRxInfoStructPtr rxStruct);

/* NM消息发送前处理函数 */
extern vuint8 Pretransmit_NmMsg(CanTxInfoStruct ctis);

extern vuint8 Pretransmit_DMM_StatusInfo(CanTxInfoStruct ctis);
/* 唤醒源设置函数 */
extern void ApplCanSetWakeupSource(vuint8 LeCan_u_Temp);

/* CAN总线唤醒有效性检查函数 */
extern uint8 ApplCanGetCanBusWakeupValid(void);

/* NM总线睡眠到重复标志设置函数 */
extern void ApplCanSetNMBussleepToRepeatFlag(vuint8 LeCan_u_Temp);

/* NM总线睡眠到重复标志读取函数 */
extern uint8 ApplCanGetNMBussleepToRepeatFlag(void);

/* 唤醒源读取函数 */
extern uint8 ApplCanGetWakeupSource(void);

/* 标志位清除函数 */
extern void ApplCanClearNMBussleepToRepeatFlag(void);
extern void ApplCanClearWakeupSource(void);

/* 唤醒正标志设置函数 */
extern void ApplCanSetWakeUpPositiveFlag(void);

/* 唤醒负标志设置函数 */
extern void ApplCanSetWakeUpNegtiveFlag(void);

/* 5s诊断函数声明 */
extern void ApplCanSetDiagnosisServiceFlag(void);
extern void ApplCanClearDiagnosisServiceFlag(void);
extern void ApplCanClearInformationCANFlag(void);
extern void ApplCanDiagReqTimerTask(void);  /* TWait_DiagReq 5s延时计时器任务函数 */

extern void TxAckCbk_BTM_DiagResp(CanTransmitHandle txObject);

/* DMM状态信息发送确认回调 */
extern void TxAckCbk_MMI_Status_Info(CanTransmitHandle txObject);

/* DMM开发消息发送确认回调函数 */
extern void TxAckCbk_TTS_Status(CanTransmitHandle txObject);
extern void TxAckCbk_MMI_TextMMData(CanTransmitHandle txObject);
extern void TxAckCbk_MMI_TextBTData(CanTransmitHandle txObject);

//extern void TxAckCbk_DMM_DevelopMessage_141(CanTransmitHandle txObject);

extern void ApplCan_Task_10ms(void);


#endif /* APPL_CAN_CALLBACK_H */ 
