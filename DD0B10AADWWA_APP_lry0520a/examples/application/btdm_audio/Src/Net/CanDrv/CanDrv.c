/*******************************************************************************
|  File Name:
|  Description:
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Zhejiang Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| FSL           fengshulin           CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2023-02-02    01.00.00     fsl       Creation
|
|******************************************************************************/
/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "fr30xx.h"
#include <string.h>

#include "CanDrv.h"
#include "can_par.h"
#include "can_def.h"
#include "can_cfg.h"
#include "BusOff_Recovery.h"



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
|    Static local variables Declaration
|******************************************************************************/
static CAN_HandleTypeDef CAN1_Handle;
static uint32_t Can1Buffer[4352];


CanxRxHeandleAndDataTypeDef_Can1 rxMsg;

/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/
static void RxFIFO0_New_Message_handle(CAN_HandleTypeDef *hcan);
static void Transmission_Completed_handle(CAN_HandleTypeDef *hcan);
/*******************************************************************************
|    Extern functions declaration
|******************************************************************************/

/*******************************************************************************
|    Extern variables declaration
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/
void CanDrv_Init(void)
{
	  struct_CANInit_t canInit;
    struct_RAMConfig_t ramConfig;
		uint32_t ram_size;
    GPIO_InitTypeDef GPIO_Handle;
	  struct_FilterCfg_t FilterCfg;
	
	    /* init GPIO CLOCK */  
	   __SYSTEM_GPIO_CLK_SELECT_COREH();
		 __SYSTEM_GPIOB_CLK_ENABLE();

//		GPIO_Handle.Pin  = GPIO_PIN_8;
//		GPIO_Handle.Mode = GPIO_MODE_OUTPUT_PP;
//		GPIO_Handle.Pull = GPIO_PULLUP;
//		gpio_init(GPIOB, &GPIO_Handle);
//	
//	  //pin Output low Level 
//    gpio_write_pin(GPIOB, GPIO_PIN_8, GPIO_PIN_CLEAR); 

    __SYSTEM_MCAN1_CLK_ENABLE();

    GPIO_Handle.Pin       = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_Handle.Mode      = GPIO_MODE_AF_PP;
    GPIO_Handle.Pull      = GPIO_PULLUP;
    GPIO_Handle.Alternate = GPIO_FUNCTION_5;
    gpio_init(GPIOB, &GPIO_Handle);
    
    CAN1_Handle.CANx = CAN1;
   
    CAN1_Handle.Init.Prescaler     = 3;
    CAN1_Handle.Init.SyncJumpWidth = 1;
    CAN1_Handle.Init.TimeSeg1      = 12;
    CAN1_Handle.Init.TimeSeg2      = 1;
		
    can_init(&CAN1_Handle);

    CAN1_Handle.RAMConfig.StartAddress = (uint32_t)Can1Buffer;
    CAN1_Handle.RAMConfig.StandardIDFilterNums = 128; 
    CAN1_Handle.RAMConfig.TxFIFOQueueNums       = 32;
    CAN1_Handle.RAMConfig.TxDedicatedBufferNums = 0;
    CAN1_Handle.RAMConfig.RxFIFO0Nums           = 64;
    CAN1_Handle.RAMConfig.DataBufferSize = CAN_DATA_BUFFER_SIZE_64_BYTE;
    ram_size = can_message_ram_init(&CAN1_Handle);

    /* ---------------------- standard ID filter ---------------------- */
    /* Single ID filter */
    /* 配置接收过滤器 */
		/* 范围滤波器：从SFID1到SFID2 (SFID2 >= SFID1) */
    FilterCfg.FilterType  = CAN_FILTER_RANGE_FILTER;
    FilterCfg.ProcessMode = FILTER_PROCESS_SET_PRIORITY_AND_STORE_IN_RxFIFO0;
    FilterCfg.FilterID_1 = 0x100;
    FilterCfg.FilterID_2 = 0x7FF;
    can_add_standard_filter(&CAN1_Handle, FilterCfg, 0);
		
		CAN1_Handle.RxFIFO0_New_Message_Callback = RxFIFO0_New_Message_handle;
    CAN1_Handle.Transmission_Completed_Callback = Transmission_Completed_handle;
    // 在现有的回调函数设置后面添加
    CAN1_Handle.Bus_Off_Callback = BusOff_Handler;

		
	  can_int_select_line(&CAN1_Handle, INT_RxFIFO0_NEW_MESSAGE, CAN_INT_LINE0);
    can_int_select_line(&CAN1_Handle, INT_TRANSMISSION_COMPLETED, CAN_INT_LINE0);
    // 确保BusOff中断已经分配到正确的中断线
    can_int_select_line(&CAN1_Handle, INT_BUS_OFF_STATUS, CAN_INT_LINE0);

		
		can_int_enable(&CAN1_Handle, INT_RxFIFO0_NEW_MESSAGE);
    can_int_enable(&CAN1_Handle, INT_TRANSMISSION_COMPLETED);
		
		can_int_enable(&CAN1_Handle, INT_BUS_OFF_STATUS);
		
		NVIC_EnableIRQ(CAN1_Line0_IRQn);

}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/
static void RxFIFO0_New_Message_handle(CAN_HandleTypeDef *hcan)
{
	    uint32_t fifoFillLevel;
	
	    fifoFillLevel = can_get_rxfifo0_fill_level(&CAN1_Handle);
	
	    while(fifoFillLevel>0)
			{
					/* 从FIFO0读取消息 */
					can_get_rxfifo0_message(&CAN1_Handle, &rxMsg.RxHeandle, rxMsg.RxData);
					CanBasicCanMsgReceived(0, 0);
				
					fifoFillLevel = can_get_rxfifo0_fill_level(&CAN1_Handle);
			}

}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/
static void Transmission_Completed_handle(CAN_HandleTypeDef *hcan)
{
   // 发送完成回调
   CanDrv_CAN1TxConfirmation(1,8);
	BusOff_ResetThresholdCounter();
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/
void CanDrv_DeInit(void)
{

}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/
int CanDrv_SendStdFrame(uint32_t id, uint8_t* data, uint8_t len)
{
    struct_CANTxHeaderDef_t txHeader;
		uint8_t temp_data[8];
		uint8_t actual_len =0;
		txHeader.IdType = CAN_ID_STANDARD;         	// 标准帧
		txHeader.Identifier = id & 0x7FF;					 	// 11位标准ID
	  txHeader.FrameType = CAN_DATA_FRAME;
    txHeader.FormatMode = CAN_CLASSICAL_FRAME;	// classical CAN
    txHeader.DLC = len; 												// DLC
    txHeader.BitRateSwitch = 0; 								/* 不启用BRS */

    // 创建临时缓冲区确保数据正确拷贝
     if (data != NULL) 
		 {
       actual_len = (len > 8) ? 8 : len;  // 确保长度不超过8字节
       memcpy(temp_data, data, actual_len);
     }

    if (can_add_tx_message(&CAN1_Handle,txHeader,temp_data) == 0u) 
		{
        return 1;
    }
    return 0;
}
/*******************************************************************************
|  Function Name    :CAN中断处理函数
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/
void can1_line0_irq(void)
{
    /* 调用CAN中断处理 */
    can_IRQHandler(&CAN1_Handle);
}


