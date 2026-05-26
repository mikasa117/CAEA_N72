#include "Can_Trcv.h"
#include "Dio_If.h"
#include "CanAppCfg.h"
#include "CanApp.h"
#include "Rte_BtrM.h"
#include "STD_BtrM.h"
 #include "SysM.h"
/* Static variables */

uint8 SeCanTrcv_u_CurrentMode;
static uint8 SeCanTrcv_u_ModeCDisabled = 0u;  /* C模式禁用标志：1=C模式拉低收发器，0=正常 */
uint16 SeCanTrcv_u_ModeCCheckDelay = 0u;  /* C模式检查延迟计数器，用于等待快发完成（全局变量，供外部访问） */

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
uint8 GetCanTrcv_CurrentMode(void)
{
	return SeCanTrcv_u_CurrentMode;
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

void CanTrcv_WakeUpTrcv(void)
{
	
			gpio_write_pin(GPIOB, GPIO_PIN_8, GPIO_PIN_CLEAR);
		SeCanTrcv_u_ModeCCheckDelay = 600u;	

		
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
void CanTrcv_WakeupClearFlag(void)
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
void CanTrcv_EnableWakeup(void)
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
void CanTrcv_DummyFun(void)
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
void CanTrcv_DisableWakeup(void)
{

}

/*******************************************************************************
Name			: CanTrcv_MainFunction
Syntax			: void CanTrcv_MainFunction(void)
Sync/Async		: Synchronous
Reentrancy		: Non-reentrant
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: CAN收发器主函数，周期性检查C模式并控制收发器引脚
              C模式下拉低收发器引脚，物理禁止CAN通讯
Call By			: 周期性调用
History
<No.>    <author>    <time>    <description>
2025-10-19  初始版本  实现C模式下硬件层收发器控制
|******************************************************************************/ 
void CanTrcv_MainFunction(void)
{
	/* 延迟计数器递减 */
    if(SeCanTrcv_u_ModeCCheckDelay > 0u)
    {
        SeCanTrcv_u_ModeCCheckDelay--;
        return;  /* 延迟期间跳过C模式检查，保证快发不被打断 */
    }
	uint8_t ucBatValue = 0;
	Rte_Read_BtrM_BtrM_VoltageMode(&ucBatValue);
		//printf("STD_BTRM_MODE is %d\r\n",ucBatValue);
     /* C模式检查（延迟结束后才执行） */
//		printf("STD_BTRM_MODE is %d\r\n",CanApp_GetENACC());
		//if(CanApp_GetENACC() < 932u
			if(ucBatValue == STD_BTRM_MODE_C)
     {
         /* 真实C模式下，拉低收发器引脚，完全禁止CAN通讯 */
//				if((CanApp_GetENACC() > 2850u)||(CanApp_GetENACC() < 932u))
			 if((CanApp_GetENACC() < 932u))
				{
					gpio_write_pin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET); 
					SeCanTrcv_u_ModeCDisabled = 1u;  /* 记录是C模式导致的standby */
					//printf("STD_BTRM_MODE is \r\n");
					//printf("STD_BTRM_MODE :%d\r\n",CanApp_GetENACC());
				}else
				if(CanApp_GetENACC() > 2850u)
				{
						gpio_write_pin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
				
				}else{
					if(CanApp_GetENACC() > 1018u)
					{
						gpio_write_pin(GPIOB, GPIO_PIN_8, GPIO_PIN_CLEAR);
					}
					
				}
			 
			 
         
     }
     else //if(CanApp_GetENACC() > 1015u)
     {
         /* 非C模式下，仅当是C模式导致的standby才恢复 */
         if(SeCanTrcv_u_ModeCDisabled == 1u)
         {
             /* 恢复收发器引脚，允许通讯 */
					
					 gpio_write_pin(GPIOB, GPIO_PIN_8, GPIO_PIN_CLEAR);
             SeCanTrcv_u_ModeCDisabled = 0u;  /* 清除标志 */
         }
         /* 正常休眠导致的standby不处理，不干扰休眠流程 */
     }
//		 else
//		{
//			gpio_write_pin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
//		}
}
/*******************************************************************************
Name			:
Syntax			:
Sync/Async		: Synchronous
Reentrancy		: Non-reentrant
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: 
Call By			:
History
<No.>    <author>    <time>    <description>
2025-10-19  初始版本
|******************************************************************************/ 
void CanTrcv_DisableTrcv(void)
{
//	gpio_write_pin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
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
uint8 CanTrcv_CheckWakeup(void)
{
	return 1u;
}