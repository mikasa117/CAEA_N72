/*******************************************************************************
 * BusOff Recovery Module - 从Vector NmCbdWrp协议栈提取的BusOff恢复逻辑
 * 
 * 基于Vector NmCbdWrp v3.08协议栈
 * 
 * 核心算法来源: NmCbdWrp.c中的CbdWrpInit, CbdWrpTask, CbdWrpBusOff函数
 ******************************************************************************/

/*******************************************************************************
 *  头文件包含
 ******************************************************************************/
#include "BusOff_Recovery.h"
#include "can_def.h"
#include "Rte_BtrM.h"
#include "STD_BtrM.h"
#include "CanApp.h"
/* 注: 不再需要il_def.h，BusOff回调改用CCL层函数(CclBusOffStart/End) */

/*******************************************************************************
 *  全局变量定义
 ******************************************************************************/
/* BusOff恢复定时器 */
vuint16 busOffRecTimer = BUSOFF_TIMER_OFF;

static uint8 busoffflag;
static uint8 BusoffSlowFlag;
/* BusOff阈值计数器 */
vuint8 busOffThresholdCounter = BUSOFF_THRESHOLD;

/*******************************************************************************
 *  函数实现
 ******************************************************************************/

/**
 * @brief BusOff恢复模块初始化
 * @note  原型来自NmCbdWrp.c的CbdWrpInit函数
 *        只初始化BusOff恢复变量，不改变CAN在线/离线状态
 */
void BusOff_Init(void)
{
    /* 初始化BusOff恢复变量 */
    busOffRecTimer = BUSOFF_TIMER_OFF;
    busOffThresholdCounter = BUSOFF_THRESHOLD;
    
    /* 注意：不调用CanOffline()，
     * CAN的在线/离线状态由CCL模块管理 */
}

/**
 * @brief BusOff恢复周期任务
 * @note  原型来自NmCbdWrp.c的CbdWrpTask函数
 *        在5ms周期任务中调用
 */

void BusOff_Task(void)
{
    vuint16 busOffTimer;
    
    /* 读取定时器值 - 保证一致性 */
    CanGlobalInterruptDisable();
    busOffTimer = busOffRecTimer;
    CanGlobalInterruptRestore();
    
    /* BusOff恢复处理 */
    if(busOffTimer != BUSOFF_TIMER_OFF)
    {
        /* 递减恢复定时器 */
        busOffRecTimer--;
        
//			if((busoffflag == 0)&&(BusoffSlowFlag == 1) )
//			{
//				busOffRecTimer = 0;
//			}
        /* 恢复完成? */
        if(busOffRecTimer == 0u)
        {
            /* 完成CAN驱动BusOff处理 */
            CanGlobalInterruptDisable();
            CanResetBusOffEnd(0u);
            CanGlobalInterruptRestore();
            
            /* 重新启用发送路径 */
            CanOnline();
            
            /* 通知应用层BusOff恢复结束 */
            ApplBusOffEnd();


        }
    }
//		busoffflag = 0;
}

/**
 * @brief BusOff事件处理函数
 * @note  原型来自NmCbdWrp.c的CbdWrpBusOff函数
 *        在BusOff中断中调用
 */
void BusOff_Handler(CAN_HandleTypeDef *hcan)
{
		busoffflag = 1;
		/* 仅在没有进行中的恢复时处理 */
    if(busOffRecTimer == BUSOFF_TIMER_OFF)
    {
        /* 关闭发送路径 */
        CanOffline();
        
        /* 清空发送队列并开始BusOff恢复 */
        CanGlobalInterruptDisable();
        CanResetBusOffStart(0u);
        CanGlobalInterruptRestore();
        
        /* 通知应用层BusOff开始 */
        ApplBusOffStart();
        
        /* BusOff恢复算法 - 快慢恢复 */
        if(busOffThresholdCounter > 0u)
        {
            /* 快恢复 - 递减阈值计数器 */
            busOffThresholdCounter--;
            busOffRecTimer = BUSOFF_RECOVERY_TIME_FAST;
//					BusoffSlowFlag = 0;
        }
        else
        {
            /* 慢恢复 - 阈值计数器已耗尽 */
            busOffRecTimer = BUSOFF_RECOVERY_TIME_SLOW;
//					BusoffSlowFlag = 1;

        }
    }	
}

/**
 * @brief 获取BusOff状态
 * @return TRUE=处于BusOff恢复中, FALSE=正常
 */
boolean BusOff_IsRecovering(void)
{
    return (busOffRecTimer != BUSOFF_TIMER_OFF) ? TRUE : FALSE;
}

/**
 * @brief 重置BusOff阈值计数器
 * @note  成功发送报文后调用，重置快恢复计数
 */
void BusOff_ResetThresholdCounter(void)
{
    busOffThresholdCounter = BUSOFF_THRESHOLD;
}

/*******************************************************************************
 *  应用层回调函数(弱定义，可被覆盖)
 ******************************************************************************/
#if !defined(APPL_BUSOFF_CALLBACKS_EXTERNAL)

/* 声明CCL层函数 */
extern void CclBusOffStart(void);
extern void CclBusOffEnd(void);

__attribute__((weak)) void ApplBusOffStart(void)
{
    /* 应用层可覆盖此函数 */
    /* 调用CCL层BusOff开始处理 - 会调用IlTxStop/IlRxStop */
    CclBusOffStart();
}

__attribute__((weak)) void ApplBusOffEnd(void)
{
    /* 应用层可覆盖此函数 */
    /* 调用CCL层BusOff结束处理 - 会调用IlTxStart/IlRxStart */
    CclBusOffEnd();
}

void CbdWrpBusOff(void)
{

}

#endif /* APPL_BUSOFF_CALLBACKS_EXTERNAL */

