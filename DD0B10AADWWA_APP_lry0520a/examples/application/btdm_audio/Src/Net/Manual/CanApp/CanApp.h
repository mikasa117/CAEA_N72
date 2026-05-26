#ifndef CANAPP_H
#define CANAPP_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Vector_Platform_Types.h"
#include "CanDrv.h"
#include "adc_if.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
# define CanAppInterruptDisable()  __asm volatile ("cpsid i" : : : "memory");
# define CanAppInterruptEnable()   __asm volatile ("cpsie i" : : : "memory");



#define CeCanApp_u_SleepNotAllowed   0U
#define CeCanApp_u_SleepAllowed      1U
#define NMStatus_NETON               1U
#define CeCanApp_e_DataMaxsize    8u
#define CeCanAppSecurityKey1

#define CanApp_EnACC_VALID            (uint16)990u  	//6.5V
#define CanApp_EnACC_INVALID          (uint16)610u    //6.0V
#define CanApp_GetENACC()             adc_if_get_validValue(adc_cl_acc) // AD Value


extern boolean BusNmMsg;
/*******************************************************************************
|    Enum Definition
|******************************************************************************/
typedef enum {
  VeCanApp_e_PMS_VIN = 0U,     			            	/*0x610*/
	VeCanApp_e_IPK_TotalOdometer = 1U,        			/*0x3F1*/
	VeCanApp_e_TBOX_DateTime_Info = 2U,             /*0x3E0*/
  VeCanApp_e_EHB_Status = 3U,     				    		/*0x125*/
    
    
  


	VeCanApp_e_MsgMaxNum = 4U

} TeCanApp_e_MsgIdType;

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

typedef enum
{
    Can_NetWorkStatus_Sleep = 0U,
    Can_NetWorkStatus_Normal = 1U
}TeCanApp_e_NetWorkStatusType;

/*can config define Type*/
typedef struct _c_Config_ByteTypeTag
{
    uint8 Bit0 : 1;
    uint8 Bit1 : 1;
    uint8 Bit2 : 1;
    uint8 Bit3 : 1;
    uint8 Bit4 : 1;
    uint8 Bit5 : 1;
    uint8 Bit6 : 1;
    uint8 Bit7 : 1;
} _c_Config_ByteType;

typedef union _c_ConfigData_bufTag
{
    uint8 ConfigData[CeCanApp_e_DataMaxsize];
    _c_Config_ByteType Byte[CeCanApp_e_DataMaxsize];
} _c_ConfigData_buf;

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/


/*******************************************************************************
|    Global variables Declaration
|******************************************************************************/
extern uint16 SeCanApp_w_DiagRequest_timer;
extern uint8 SeDid_u_CAEA_FEC;
extern uint8 SeCanApp_u_WakeupFlag;
extern uint8 SeCanApp_u_WakeupBy0x55Flag;
extern uint8 SeCanApp_u_WakeupBy0x55Data;


extern void ApplCanSetInformationCANFlag(void);

/*******************************************************************************
|    static local variables Declaration
|******************************************************************************/


/*******************************************************************************
|    static Local Functions Declaration
|******************************************************************************/
extern void INT_SYS_DisableIRQGlobal(void);
extern void INT_SYS_EnableIRQGlobal(void);

extern void CanApp_Set28RxStop(uint8 LeCanApp_u_28RxStop);

extern void CanApp_ClrBusSlientCount(void);
extern uint8 CanApp_GetBusSlientFlag(void);
extern void CanApp_NmTxEnable(void);
extern void CanApp_NmTxDisable(void);
extern void CanApp_NmRxEnable(void);
extern void CanApp_NmRxDisable(void);
extern void CanApp_DiagTxEnable(void);
extern void CanApp_DiagTxDisable(void);
extern void CanApp_DiagRxEnable(void);
extern void CanApp_DiagRxDisable(void);

extern void NmMsgReCheck(void);
/* 唤醒源管理相关函数 */
extern void CanApp_CheckWakeupSource(void);
extern void CanApp_ProcessNMStateFlags(void);
extern void CanApp_WakeupSourceManager(void);

extern void CanApp_u_SetBusOffStaus(uint8 LeCanSignal_u_Idx);
extern uint8 CanApp_u_GetBusOffStaus(void);
extern void CanApp_u_SetNetWorkStaus(uint8 LeCanSignal_u_Idx);
extern uint8 CanApp_u_GetNetWorkStaus(void);
extern void CanApp_SetPositiveReqNet(uint8 LeCanApp_u_ReqNetFlag);
extern uint8 CanApp_GetPositiveReqNetFlag(void);
extern void SetCanApp_BusOffOccurNumInc(void);
extern void SetCanApp_BusOffOccurNumClr(void);
extern uint8 GetCanApp_BusOffOccurNum(void);
extern void SetCanApp_MsgReceiveSts( TeCanApp_e_MsgIdType LeCanApp_u_MsgIndex );
extern uint8 GetCanApp_u_MsgTimeout( TeCanApp_e_MsgIdType LeCanApp_u_MsgIndex );
extern void SetCanApp_MsgCurrentPresent( TeCanApp_e_MsgIdType LeCanApp_u_MsgIndex,uint8 LeCanApp_u_MsgSts);
extern uint8 GetCanApp_u_NetWorkSleepAllowed(void);
extern  void CanApp_InitMemoryKAM(void);
extern  void CanApp_InitMemory(void);
extern  void CanApp_MainFunction(void);
extern void CanApp_ResetPowerModeLost(void);
extern void CanApp_MainFunction_10ms(void);
extern uint8 CanCbk_GetBusOffDtcConditionState(void);/*BusOff */
extern uint8 CanApp_GetConfigSuccesFlag(void);
extern void can_Hmi_20ms(void);
extern void CanApp_SetVinLiveTimeoutTtimer(uint16_t TimeCountData);
extern void SetCan_IGN_Flag(uint8 LeCanSignal_u_Idx);
extern uint8 GetCan_IGN_Flag(void);
/**********************N72******************/
/******************************Receive signal list**************************************************/
//EHB_Status (0x125) variables
extern float  GetCanApp_u_EHB_VehicleSpeed(void);
extern uint8_t  GetCanApp_u_EHB_VehicleSpeedInvalid(void);

//IPK_TotalOdometer (0x3F1) variables
extern uint32_t  GetCanApp_u_IPK_IPKTotalOdometer(void);

//PMS_VIN (0x610) variables
extern uint8_t  GetCanApp_u_PMS_VINCode7_14_S(void);
extern uint8_t  GetCanApp_u_PMS_VINCode6_13_S(void);
extern uint8_t  GetCanApp_u_PMS_VINCode5_12_S(void);
extern uint8_t  GetCanApp_u_PMS_VINCode4_11_S(void);
extern uint8_t  GetCanApp_u_PMS_VINCode3_10_17_S(void);
extern uint8_t  GetCanApp_u_PMS_VINCode2_9_16_S(void);
extern uint8_t  GetCanApp_u_PMS_VINCode1_8_15_S(void);
extern uint8_t  GetCanApp_u_PMS_VINMessageNum_S(void);

//TBOX_DateTime_Info (0x3E0) variables
extern uint8_t  GetCanApp_u_TBOX_Second(void);
extern uint8_t  GetCanApp_u_TBOX_Minute(void);
extern uint8_t  GetCanApp_u_TBOX_Hour(void);
extern uint8_t  GetCanApp_u_TBOX_Day(void);
extern uint8_t  GetCanApp_u_TBOX_Month(void);
extern uint16_t  GetCanApp_u_TBOX_Year(void);
extern uint8_t VIN_compare(void);

#if 0
/* NM CMD */
extern uint8 GetCanApp_NM_Command(void);
extern uint8 GetCanApp_NM_AwakeCommand(void);
extern uint8 GetCanApp_NM_SleepCommand(void);
extern void CanApp_NMMsgIndication_Callback(void);
#endif
extern void SetCanApp_ClearTimeOut(void);
extern void CanApp_SetTxOkF(void);
extern uint8 SeCanApp_u_WakeupRequest;
#endif
