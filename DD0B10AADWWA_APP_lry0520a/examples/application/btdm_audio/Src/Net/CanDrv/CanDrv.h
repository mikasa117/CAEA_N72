/*******************************************************************************
|  File Name:  CanDrv.h
|  Description:  Implementation of the base Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Zhejiang Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| CHP           Chen Haopeng           CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 2021-08-09    00.00.01     CHP       Creation
|
|******************************************************************************/
#ifndef _CAN_DRV_H_
#define _CAN_DRV_H_
/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include <stdint.h>
#include "Vector_Platform_Types.h"
#include "driver_can.h"
#include "fr30xx.h"
/* 添加Vector CAN驱动头文件引用 */
#include "can_def.h"  /* Vector CAN驱动定义 */


#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
|    Compile Option or configuration Section
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
// CAN配置常量
#define kCanNumberOfTxObjects 6  										// 发送对象数量

#define     CANDRV_RNC0                   ( 9U )    //CAN channnal 0 receive Rule num < 128
#define     CANDRV_RNC1                   ( 0U )    //CAN channnal 1 receive Rule num < 128
#define     CANDRV_RNC2                   ( 0U )    //CAN channnal 2 receive Rule num < 128
#define     CANDRV_RNC3                   ( 0U )    //CAN channnal 3 receive Rule num < 128
#define     CANDRV_RNC4                   ( 0U )    //CAN channnal 4 receive Rule num < 128
#define     CANDRV_RNC5                   ( 0U )    //CAN channnal 5 receive Rule num < 128
#define     CANDRV_CFG_RN   ( CANDRV_RNC0 + CANDRV_RNC1 + CANDRV_RNC2 + CANDRV_RNC3 + CANDRV_RNC4 + CANDRV_RNC5 )

#define     CanDrv_CAN1TxConfirmation             CanHL_TxConfirmation

/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef struct CanxRxHeandleAndDataTypeDef{
	
	struct_CANRxHeaderDef_t RxHeandle;
	uint8_t RxData[8];
	
}CanxRxHeandleAndDataTypeDef_Can1;
/*******************************************************************************
|    Table Definition
|******************************************************************************/
extern CanxRxHeandleAndDataTypeDef_Can1 rxMsg;
/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/
// 标准CAN帧收发API
extern void CanDrv_Init(void);
extern void  CanDrv_DeInit(void);
extern int  CanDrv_SendStdFrame(uint32_t id, uint8_t* data, uint8_t len);



#ifdef __cplusplus
}
#endif



#endif // _CAN_DRV_H_
