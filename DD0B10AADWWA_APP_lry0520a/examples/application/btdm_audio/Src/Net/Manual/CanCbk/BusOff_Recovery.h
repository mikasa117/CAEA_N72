/*******************************************************************************
 * BusOff Recovery Module - 从Vector NmCbdWrp协议栈提取的BusOff恢复逻辑
 * 
 * 功能：实现快慢恢复算法
 * - 前10次BusOff使用快恢复(100ms)
 * - 之后使用慢恢复(1000ms)
 * 
 * 基于Vector NmCbdWrp v3.08协议栈
 ******************************************************************************/

#ifndef BUSOFF_RECOVERY_H
#define BUSOFF_RECOVERY_H

/*******************************************************************************
 *  头文件包含
 ******************************************************************************/
#include "v_cfg.h"
#include "v_def.h"
#include "can_inc.h"

/*******************************************************************************
 *  配置参数 - 与nmcbdwrp_cfg.h保持一致
 ******************************************************************************/
/* 慢恢复时间: 200 × 5ms = 1000ms */
#define BUSOFF_RECOVERY_TIME_SLOW        200u

/* 快恢复时间: 20 × 5ms = 100ms */
#define BUSOFF_RECOVERY_TIME_FAST        20u

/* 快恢复阈值: 前10次使用快恢复 */
#define BUSOFF_THRESHOLD                 10u

/* 定时器关闭值 */
#define BUSOFF_TIMER_OFF                 ((vuint16)0u)

/*******************************************************************************
 *  外部变量声明
 ******************************************************************************/

/*******************************************************************************
 *  函数原型
 ******************************************************************************/

/**
 * @brief BusOff恢复模块初始化
 * @note  在系统初始化时调用一次
 */
extern void BusOff_Init(void);

/**
 * @brief BusOff恢复周期任务
 * @note  在5ms周期任务中调用
 */
extern void BusOff_Task(void);

/**
 * @brief BusOff事件处理函数
 * @note  在BusOff中断中调用
 */
extern void BusOff_Handler(CAN_HandleTypeDef *hcan);

/**
 * @brief 获取BusOff状态
 * @return TRUE=处于BusOff恢复中, FALSE=正常
 */
extern boolean BusOff_IsRecovering(void);

/**
 * @brief BusOff开始回调(应用层实现)
 */
extern void ApplBusOffStart(void);

/**
 * @brief BusOff结束回调(应用层实现)
 */
extern void ApplBusOffEnd(void);
extern void BusOff_ResetThresholdCounter(void);
extern void CbdWrpBusOff(void);

#endif /* BUSOFF_RECOVERY_H */
