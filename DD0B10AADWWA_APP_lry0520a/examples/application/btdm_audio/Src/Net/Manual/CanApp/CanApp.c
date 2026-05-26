 /*******************************************************************************
|  File Name:  CanApp.c
|  Description:  Implementation of the CAN Application Layer
|-------------------------------------------------------------------------------
|  Revision History
|  Date        Version    Author    Description
|  ---------------------------------------------------------------------------
|  2024-03-19  1.0       Auto      Initial version
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Can_Trcv.h"
#include "CanApp.h"
#include "CanAppCfg.h"
#include "Adc_If.h"
#include "can_par.h"
#include "il_inc.h"
#include "ccl_inc.h"
#include "Appl_Can_Callback.h"
#include "NmControl.h"
#include "Rte_Hmi.h"
#include "Rte_Can.h"
#include "DID_Callback.h"
#include "Rte_BtrM.h"
#include "STD_BtrM.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/*******************************************************************************
|    Enum Definition
|******************************************************************************/
//#define CeCanApp_u_SleepNotAllowed          0U
//#define CeCanApp_u_SleepAllowed             0x01U
#define CeCanApp_u_CheckSumLen3             0x03U
#define CeCanApp_u_CheckSumLen6             0x06U
#define CeCanApp_u_CheckSumLen7             0x07U
#define CeCanApp_u_BusOffThreshold          10U
#define NMStatus_NETON                      1U
/*Can Config Data*/
#define ConfigData_SeatHeating              SeCanApp_u_ConfigData.Byte[0].Bit0
#define ConfigData_SeatVentilating          SeCanApp_u_ConfigData.Byte[0].Bit1
#define ConfigData_ION                      SeCanApp_u_ConfigData.Byte[0].Bit2
#define ConfigData_PM2_5                    SeCanApp_u_ConfigData.Byte[0].Bit3
#define ConfigData_ThreeRowIndependentAC    SeCanApp_u_ConfigData.Byte[0].Bit4
#define ConfigData_Fragrance                SeCanApp_u_ConfigData.Byte[0].Bit5
#define ConfigData_APA                      SeCanApp_u_ConfigData.Byte[0].Bit6
#define ConfigData_LDW                      SeCanApp_u_ConfigData.Byte[0].Bit7
#define ConfigData_SCU                      SeCanApp_u_ConfigData.Byte[1].Bit0
#define ConfigData_LKA                      SeCanApp_u_ConfigData.Byte[1].Bit1
#define ConfigData_PLG                      SeCanApp_u_ConfigData.Byte[1].Bit2
#define ConfigData_AUTODefog                SeCanApp_u_ConfigData.Byte[1].Bit3
#define ConfigData_CWC                      SeCanApp_u_ConfigData.Byte[1].Bit4
#define ConfigData_FrontWindshieldHeating   SeCanApp_u_ConfigData.Byte[1].Bit5
#define CanApp_Debug                        0   //zqy
/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

uint8_t MMI_TextMMDatabuff[8];
uint8_t MMI_TextBTDatabuff[8];
static uint16_t vin_live_timeout_timer = 0;
static uint8_t VIN_Vaule_1;
static uint8_t VIN_Vaule_2;
static uint8_t VIN_Vaule_3;
extern void CclComStop(void);
extern void CclComStart(void);
boolean BusNmMsg = 0;
uint8 SeCanApp_u_WakeupFlag = 0;
/*******************************************************************************
|    Global variables Declaration
|******************************************************************************/
/*******************************Tx Messages variable definitions Start*******************************/
static uint8 SeCanApp_u_MouseTxPhase = 0xFFu;

static uint8 SeCanApp_u_TxOk_Flag;

static uint8 Can_IGN_Flag;

// Message monitoring variables
static uint8  SeCanApp_u_MsgPresentSts[VeCanApp_e_MsgMaxNum];
static uint8  SeCanApp_u_MsgReceiveSts[VeCanApp_e_MsgMaxNum];

// Network management variables
static uint8  SeCanApp_u_BusOffStaus;
static uint8  SeCanApp_BusOffOccurNum;
static uint8  SeCanApp_u_NetWorkStaus;
static uint8  SeCanApp_u_ReqNetFlag;
static uint8  SeCanApp_u_ConfigSuccesFlag;
static uint8  SeCanApp_u_BCM_10_1_ReceiveFlag;
static uint8  SeCanApp_u_BCM_10_2_ReceiveFlag;
static uint8  SeCanApp_u_BCM_10_3_ReceiveFlag;
static _c_ConfigData_buf SeCanApp_u_ConfigData;
static uint8  SeCanApp_u_28RxAppStopFlag;
static uint8  SeCanApp_u_NmReqNetFlag;
static uint16 SeCanApp_w_NmReqNetCount;
static uint8  SeCanApp_u_BusSlientFlag;
static uint32 SeCanApp_dw_BusSlientCount;

/* NM */
static uint8 SeCanApp_u_MsgBCM_NMTimeCnt;
static uint8 SeCanApp_u_MsgBCM_NMEventCnt;
 uint8 SeCanApp_u_WakeupRequest = 0U; // 0 = No request, 1 = Request active
 

uint16_t VIN_count_1;
uint16_t VIN_count_2;
uint16_t VIN_count_3;
/*******************************Rx Messages variable definitions Start*******************************/


/******************************N72**************************************************/
//EHB_Status (0x125) variables
static float  SeCanApp_u_EHB_VehicleSpeed;
static uint8_t  SeCanApp_u_EHB_VehicleSpeedInvalid;

//IPK_TotalOdometer (0x3F1) variables
static uint32_t  SeCanApp_u_IPK_IPKTotalOdometer;

//PMS_VIN (0x610) variables
static uint8_t  SeCanApp_u_PMS_VINCode7_14_S;
static uint8_t  SeCanApp_u_PMS_VINCode6_13_S;
static uint8_t  SeCanApp_u_PMS_VINCode5_12_S;
static uint8_t  SeCanApp_u_PMS_VINCode4_11_S;
static uint8_t  SeCanApp_u_PMS_VINCode3_10_17_S;
static uint8_t  SeCanApp_u_PMS_VINCode2_9_16_S;
static uint8_t  SeCanApp_u_PMS_VINCode1_8_15_S;
static uint8_t  SeCanApp_u_PMS_VINMessageNum_S;

//TBOX_DateTime_Info (0x3E0) variables
static uint8_t  SeCanApp_u_TBOX_Second;
static uint8_t  SeCanApp_u_TBOX_Minute;
static uint8_t  SeCanApp_u_TBOX_Hour;
static uint8_t  SeCanApp_u_TBOX_Day;
static uint8_t  SeCanApp_u_TBOX_Month;
static uint16_t  SeCanApp_u_TBOX_Year;

// Message monitoring variables
static uint8_t  SeCanApp_u_MsgPresentSts[VeCanApp_e_MsgMaxNum];
static uint8_t  SeCanApp_u_MsgReceiveSts[VeCanApp_e_MsgMaxNum];

// Network management variables
static uint8_t  SeCanApp_u_BusOffStaus;


static uint8_t  SeCanApp_u_28RxAppStopFlag;
static void CanApp_SignalRecMainFunc(void);

static uint8 SeCanApp_u_NmRxEnFlag;
static uint8 SeCanApp_u_NmTxEnFlag;
static uint8 SeCanApp_u_DiagRxEnFlag;
static uint8 SeCanApp_u_DiagTxEnFlag;

static uint16_t CanAppSetAccLastValue = 0u;
/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/
static void CanApp_SignalRecMainFunc(void);
static void CanApp_CheckPositiveWakeup(void);

static void Can_SetNmFlag(void);
static void Can_ClearNmFlag(void);
static void VIN_clear(void);
/*******************************************************************************
|    Global Function Implementation
|******************************************************************************/

/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
void CanApp_MainFunction(void)
{

	if(SeCanApp_u_28RxAppStopFlag == FALSE)
	{
		CanApp_SignalRecMainFunc();
	}
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
void CanApp_ResetPowerModeLost(void)
{
#if (TEST_SOFTWARE_FUNC_EXHIBITION == TEST_SOFTWARE_FUNC_ENABLE)
    
#else
	SeCanApp_u_PowerMode = 3U;
	SeCanApp_u_PowerMode_LostCnt = 0u;
#endif
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
void CanApp_MainFunction_10ms(void)
{
    CanApp_CheckPositiveWakeup();

    if (vin_live_timeout_timer > 0)
    {
        vin_live_timeout_timer--;
        if (vin_live_timeout_timer == 0)
        {
            VIN_clear();
        }
    }
} 
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
void can_Hmi_20ms(void)
{
	
	if(Rte_Hmi_Get_TextBTData((uint8_t *)&MMI_TextBTData._c[0]) == 1){
				memcpy(MMI_TextBTDatabuff, CanTxDataPtr[4], sizeof(MMI_TextMMDatabuff));
			}else{
				memcpy(&MMI_TextBTData, MMI_TextBTDatabuff, sizeof(MMI_TextMMDatabuff));
			}
			
			if(Rte_Hmi_Get_TextMMData((uint8_t *)&MMI_TextMMData._c[0]) == 1){
				memcpy(MMI_TextMMDatabuff, CanTxDataPtr[3], sizeof(MMI_TextMMDatabuff));
			}else{
				memcpy(&MMI_TextMMData, MMI_TextMMDatabuff, sizeof(MMI_TextMMDatabuff));
			}
} 
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
//返回值为1则VIN码正确

uint8_t VIN_compare(void)
{

	if(SeCanApp_u_PMS_VINMessageNum_S == 1)
		{
				if((SeCanApp_u_PMS_VINCode7_14_S   == DID0xF190DefaultValue[6]) &&
				(SeCanApp_u_PMS_VINCode6_13_S   == DID0xF190DefaultValue[5]) &&
				(SeCanApp_u_PMS_VINCode5_12_S   == DID0xF190DefaultValue[4]) &&
				(SeCanApp_u_PMS_VINCode4_11_S   == DID0xF190DefaultValue[3]) &&
				(SeCanApp_u_PMS_VINCode3_10_17_S   == DID0xF190DefaultValue[2]) &&
				(SeCanApp_u_PMS_VINCode2_9_16_S   == DID0xF190DefaultValue[1]) &&
				(SeCanApp_u_PMS_VINCode1_8_15_S   ==DID0xF190DefaultValue[0] ))
				{
					VIN_Vaule_1 = 1;
					VIN_count_1 = 500u;
				}else
				{
					VIN_Vaule_1 = 0;
				}
		
		}else if(SeCanApp_u_PMS_VINMessageNum_S == 2)
					{
						if((SeCanApp_u_PMS_VINCode7_14_S   == DID0xF190DefaultValue[13]) &&
            (SeCanApp_u_PMS_VINCode6_13_S   == DID0xF190DefaultValue[12]) &&
            (SeCanApp_u_PMS_VINCode5_12_S   == DID0xF190DefaultValue[11]) &&
            (SeCanApp_u_PMS_VINCode4_11_S   == DID0xF190DefaultValue[10]) &&
            (SeCanApp_u_PMS_VINCode3_10_17_S   == DID0xF190DefaultValue[9]) &&
            (SeCanApp_u_PMS_VINCode2_9_16_S   == DID0xF190DefaultValue[8]) &&
            (SeCanApp_u_PMS_VINCode1_8_15_S   ==DID0xF190DefaultValue[7]))
						{
								VIN_count_2 = 500u;
								VIN_Vaule_2 = 1;
						}else
						{
								VIN_Vaule_2 = 0;
						}
					}
    else if(SeCanApp_u_PMS_VINMessageNum_S == 3)
					{
						if((SeCanApp_u_PMS_VINCode3_10_17_S   == DID0xF190DefaultValue[16]) &&
            (SeCanApp_u_PMS_VINCode2_9_16_S   == DID0xF190DefaultValue[15]) &&
            (SeCanApp_u_PMS_VINCode1_8_15_S   ==DID0xF190DefaultValue[14]))
					{
            VIN_count_3 = 500u;
            VIN_Vaule_3 = 1;
					}else
						{
            VIN_Vaule_3 = 0;
						}
				  }
				else
					{
					return 0;
					}
		if(VIN_count_1 == 0u)
		{
			VIN_Vaule_1 = 0;
		}
		else
		{
			VIN_count_1--;
		}
			
		if(VIN_count_2 == 0u)
		{
			VIN_Vaule_2 = 0;
		}
		else
		{
			VIN_count_2--;
		}
		if(VIN_count_3 == 0u)
		{
			VIN_Vaule_3 = 0;
		}
		else
		{
			VIN_count_3--;
		}
	if(VIN_Vaule_1 && VIN_Vaule_2 && VIN_Vaule_3)
	{

		return 1;
	}
	return 0;

}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
static void VIN_clear(void)
{
    VIN_Vaule_1 = 0;
    VIN_Vaule_2 = 0;
    VIN_Vaule_3 = 0;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
void CanApp_SetVinLiveTimeoutTtimer(uint16_t TimeCountData)
{
	vin_live_timeout_timer = TimeCountData;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CanApp_InitMemory(void)
{
    uint8 i;
    //uint8 LeCanApp_u_index;
        

    for(i = 0u;i <(uint8)VeCanApp_e_MsgMaxNum;i++)
    {
        SeCanApp_u_MsgPresentSts[i] = 1u; //LKC 20200514
        SeCanApp_u_MsgReceiveSts[i] = 0u;
    }
     
		Can_IGN_Flag = 0u;
    SeCanApp_BusOffOccurNum =0u;
    SeCanApp_u_BCM_10_1_ReceiveFlag = 0u;
    SeCanApp_u_BCM_10_2_ReceiveFlag = 0u;
    SeCanApp_u_BCM_10_3_ReceiveFlag = 0u;
	
		SeCanApp_u_28RxAppStopFlag = 0u;
		SeCanApp_u_BusSlientFlag = 0U;
    SeCanApp_dw_BusSlientCount = 350U;  /* 350 × 10ms = 3.5s，与 kCclEmcWakeUpTime 一致 */
    
  //  SeCanApp_u_ConfigSuccesFlag = Appl_DID_GetConfigurStatus();
    VStdMemClr( &SeCanApp_u_ConfigData.Byte[0], CeCanApp_e_DataMaxsize );
    CanApp_u_SetBusOffStaus(0U);    
    CanApp_u_SetNetWorkStaus(1U);
    CanApp_SetPositiveReqNet(0U);     
	
		SeCanApp_u_MsgBCM_NMEventCnt = (uint8)0;
		SeCanApp_u_MsgBCM_NMTimeCnt = (uint8)0;
		SeCanApp_u_ReqNetFlag = 0U;
	
		SeCanApp_u_NmRxEnFlag = 1U;
		SeCanApp_u_NmTxEnFlag = 1U;
		
		SeCanApp_u_DiagRxEnFlag = 1U;
		SeCanApp_u_DiagTxEnFlag = 1U;
//    IlTxStart();
//    IlRxStart();
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CanApp_InitMemoryKAM(void)
{

}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CanApp_Set28RxStop(uint8 LeCanApp_u_28RxStop)
{
    /* Set diagnostic message request flag*/
    SeCanApp_u_28RxAppStopFlag = LeCanApp_u_28RxStop;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
uint16 CanApp_GetNmReqNetFlag(void)
{
    /*Get Delay 6 seconds counter*/
    return SeCanApp_w_NmReqNetCount;   
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CanApp_ClrBusSlientCount(void)
{
     SeCanApp_dw_BusSlientCount = 350u;  /* 与初始值保持一致 */
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
uint8 CanApp_GetBusSlientFlag(void)
{
     return SeCanApp_u_BusSlientFlag;   
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CanApp_SetPositiveReqNet(uint8 LeCanApp_u_ReqNetFlag)
{
    /* Gets the ECU wake condition 0:release 1:request */
    SeCanApp_u_ReqNetFlag = LeCanApp_u_ReqNetFlag;
}
uint8 CanApp_GetPositiveReqNetFlag(void)
{
    return SeCanApp_u_ReqNetFlag;
}

/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
static void CanApp_CheckPositiveWakeup(void)
{
	uint8_t ucBatValue = 0;
	Rte_Read_BtrM_BtrM_VoltageMode(&ucBatValue);
//	if(ucBatValue == STD_BTRM_MODE_C)
//	{
//		return;
//	}
	/* IGN 网络请求逻辑 */
//	printf("CanApp_GetENACC :%d\r\n",CanApp_GetENACC());
	if((CanApp_GetENACC() > 600u)&&(CanApp_GetENACC() < 2830u))
//	if(ucBatValue != STD_BTRM_MODE_C)
//	if(CanApp_GetENACC() > 1015u)
//	if((CanApp_GetENACC() > 600u))
	{
		/* 只在状态变化时请求通讯 */
		SetCan_IGN_Flag(1u);
		if(0xAAU != SeCanApp_u_WakeupFlag)
		{
			CclComStart();
			CclSet_IgnRequest();  
			gpio_write_pin(GPIOB, GPIO_PIN_8, GPIO_PIN_CLEAR);
			SeCanApp_u_WakeupFlag = 0xAAU;
			CanApp_u_SetNetWorkStaus(1U);
		}
	}
	else 
	if((CanApp_GetENACC() < 600u)||(CanApp_GetENACC() > 2897u))
	{
		SetCan_IGN_Flag(0u);
		if(0xAAU == SeCanApp_u_WakeupFlag)
		{
			CclRel_IgnRequest();		
			CclComStop();
			SeCanApp_u_WakeupFlag = 0U;
		}
	}
	else
	{

	}
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
uint8 GetCan_IGN_Flag(void)
{
	return Can_IGN_Flag;
}

/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void SetCan_IGN_Flag(uint8 LeCanSignal_u_Idx)
{
    Can_IGN_Flag = LeCanSignal_u_Idx;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CanApp_NmTxEnable(void)
{
    SeCanApp_u_NmTxEnFlag = 1u;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
void CanApp_NmTxDisable(void)
{
    SeCanApp_u_NmTxEnFlag = 0u;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
void CanApp_NmRxEnable(void)
{
    SeCanApp_u_NmRxEnFlag = 1u;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
void CanApp_NmRxDisable(void)
{
    SeCanApp_u_NmRxEnFlag = 0u;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
void CanApp_DiagTxEnable(void)
{
    SeCanApp_u_DiagTxEnFlag = 1u;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
void CanApp_DiagTxDisable(void)
{
    SeCanApp_u_DiagTxEnFlag = 0u;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
void CanApp_DiagRxEnable(void)
{
    SeCanApp_u_DiagRxEnFlag = 1u;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
void CanApp_DiagRxDisable(void)
{
    SeCanApp_u_DiagRxEnFlag = 0u;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CanApp_u_SetBusOffStaus(uint8 LeCanSignal_u_Idx)
{
    SeCanApp_u_BusOffStaus = LeCanSignal_u_Idx;
} 
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
uint8 CanApp_u_GetBusOffStaus(void)
{  
    return SeCanApp_u_BusOffStaus;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CanApp_u_SetNetWorkStaus(uint8 LeCanSignal_u_Idx)
{ 
    SeCanApp_u_NetWorkStaus = LeCanSignal_u_Idx;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
uint8 CanApp_u_GetNetWorkStaus(void)
{
    return SeCanApp_u_NetWorkStaus;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
uint8 GetCanApp_u_NetWorkSleepAllowed(void)
{
    uint8 LeCanApp_u_NetWorkSleep = CeCanApp_u_SleepNotAllowed;
    uint8 wakeupSource = ApplCanGetWakeupSource();

    return LeCanApp_u_NetWorkSleep;
}
/*******************************************************************************
Name			:
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: -Check if there are NM messages on the  bus
Call By			:
|******************************************************************************/
void NmMsgReCheck(void)
{
	vuint16 NmCheckCanId;
	NmCheckCanId =(vuint16)rxMsg.RxHeandle.Identifier;
    uint8 NmCheckcount;
  if((CeCanCbk_u_BasicNMID <= NmCheckCanId)&&(CeCanCbk_u_MaxNMID >= NmCheckCanId))

    {
       Can_SetNmFlag();
       NmCheckcount=200u;
 	}
     if(NmCheckcount>0u)
    {
 	   NmCheckcount--;
    }
    else
    {
	   Can_ClearNmFlag();
    }
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
void Can_SetNmFlag(void)
{
	BusNmMsg = 1u;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
void Can_ClearNmFlag(void)
{
	BusNmMsg = 0u;
}
/*******************************************************************************
Name			:
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: -
Call By			:
|******************************************************************************/
static void CanApp_SignalRecMainFunc(void)
{
	//uint8 utemp;

	if( NMStatus_NETON == CanApp_u_GetNetWorkStaus() )
	{
		/**0x125**/
     if(0u !=SeCanApp_u_MsgPresentSts[VeCanApp_e_EHB_Status])
     {
         if(1u == SeCanApp_u_MsgReceiveSts[VeCanApp_e_EHB_Status])
         {
             SeCanApp_u_MsgReceiveSts[VeCanApp_e_EHB_Status] = 0u;
            CanGlobalInterruptDisable();
            SeCanApp_u_EHB_VehicleSpeed   = ((float)IlGetRxEHB_VehicleSpeed()*0.05625);
            SeCanApp_u_EHB_VehicleSpeedInvalid   = IlGetRxEHB_VehicleSpeedInvalid();
//            printf("can_app");
//            printf("SeCanApp_u_EHB_VehicleSpeedInvalid=%d,",SeCanApp_u_EHB_VehicleSpeedInvalid );


            CanGlobalInterruptRestore();
         }
     }
     else
     {
         ;
     }
    /**0x3F1**/
     if(0u !=SeCanApp_u_MsgPresentSts[VeCanApp_e_IPK_TotalOdometer])
     {
         if(1u == SeCanApp_u_MsgReceiveSts[VeCanApp_e_IPK_TotalOdometer])
         {
            SeCanApp_u_MsgReceiveSts[VeCanApp_e_IPK_TotalOdometer] = 0u;
            CanGlobalInterruptDisable();

            SeCanApp_u_IPK_IPKTotalOdometer   = IlGetRxIPK_IPKTotalOdometer();


            CanGlobalInterruptRestore();
         }
     }
     else
     {
         ;
     }
    /**0x610**/
     if(0u !=SeCanApp_u_MsgPresentSts[VeCanApp_e_PMS_VIN])
     {
         if(1u == SeCanApp_u_MsgReceiveSts[VeCanApp_e_PMS_VIN])
         {
             SeCanApp_u_MsgReceiveSts[VeCanApp_e_PMS_VIN] = 0u;
            CanGlobalInterruptDisable();

            SeCanApp_u_PMS_VINCode7_14_S   = IlGetRxPMS_VINCode7_14_S();
            SeCanApp_u_PMS_VINCode6_13_S   = IlGetRxPMS_VINCode6_13_S();
            SeCanApp_u_PMS_VINCode5_12_S   = IlGetRxPMS_VINCode5_12_S();
            SeCanApp_u_PMS_VINCode4_11_S   = IlGetRxPMS_VINCode4_11_S();
            SeCanApp_u_PMS_VINCode3_10_17_S   = IlGetRxPMS_VINCode3_10_17_S();
            SeCanApp_u_PMS_VINCode2_9_16_S   = IlGetRxPMS_VINCode2_9_16_S();
            SeCanApp_u_PMS_VINCode1_8_15_S   = IlGetRxPMS_VINCode1_8_15_S();
            SeCanApp_u_PMS_VINMessageNum_S   = IlGetRxPMS_VINMessageNum_S();



            CanGlobalInterruptRestore();
         }
     }
     else
     {
         ;
     }

    /**0x3E0**/
     if(0u !=SeCanApp_u_MsgPresentSts[VeCanApp_e_TBOX_DateTime_Info])
     {
         if(1u == SeCanApp_u_MsgReceiveSts[VeCanApp_e_TBOX_DateTime_Info])
         {
             SeCanApp_u_MsgReceiveSts[VeCanApp_e_TBOX_DateTime_Info] = 0u;
            CanGlobalInterruptDisable();


            SeCanApp_u_TBOX_Second  = (uint8_t)((float)IlGetRxTBOX_Second()*0.25);
            SeCanApp_u_TBOX_Minute   = IlGetRxTBOX_Minute();
            SeCanApp_u_TBOX_Hour  = IlGetRxTBOX_Hour();
            SeCanApp_u_TBOX_Month   = IlGetRxTBOX_Month();
            SeCanApp_u_TBOX_Day  = (uint8_t)((float)IlGetRxTBOX_Day()*0.25);
            SeCanApp_u_TBOX_Year   = (uint16_t)(IlGetRxTBOX_Year()+1985);


            CanGlobalInterruptRestore();
         }
     }
     else
     {
         ;
     }
	}
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void SetCanApp_BusOffOccurNumInc(void)
{
  SeCanApp_BusOffOccurNum++;
  if((uint8)CeCanApp_u_BusOffThreshold <= SeCanApp_BusOffOccurNum)
  {
      SeCanApp_BusOffOccurNum = CeCanApp_u_BusOffThreshold;
  }
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void SetCanApp_BusOffOccurNumClr(void)
{
  SeCanApp_BusOffOccurNum = 0u;
}
/*******************************************************************************
Name      : GetCanApp_BusOffOccurNum
Syntax      : uint8 GetCanApp_BusOffOccurNum(void)
Sync/Async    : Synchronous
Reentrancy    : Reentrant
Parameters(in)  : None
Parameters(out) : None
Return value  : uint8 - Current bus off occurrence number
Description    : Get current bus off occurrence number
Call By      : External modules
History      :Added for bus off recovery logic
|******************************************************************************/
uint8 GetCanApp_BusOffOccurNum(void)
{
  return SeCanApp_BusOffOccurNum;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void SetCanApp_MsgReceiveSts( TeCanApp_e_MsgIdType LeCanApp_u_MsgIndex )
{
  SeCanApp_u_MsgReceiveSts[LeCanApp_u_MsgIndex] = 1u;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void SetCanApp_MsgCurrentPresent( TeCanApp_e_MsgIdType LeCanApp_u_MsgIndex,uint8 LeCanApp_u_MsgSts)
{
    SeCanApp_u_MsgPresentSts[LeCanApp_u_MsgIndex] = LeCanApp_u_MsgSts;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
uint8 GetCanApp_u_MsgTimeout( TeCanApp_e_MsgIdType LeCanApp_u_MsgIndex )
{
    uint8 retval;
    
    if((uint8)0x01u == SeCanApp_u_MsgPresentSts[LeCanApp_u_MsgIndex]  )
    {
        retval = 0x00u;
    }
    else
    {
        retval = 0x01u;
    }
    
    return ( retval );
}

/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
uint8 CanCbk_GetBusOffDtcConditionState(void)/*BusOff */
{ 
    uint8 LeCanApp_u_RetVal = 0u;
    if((uint8)CeCanApp_u_BusOffThreshold <= SeCanApp_BusOffOccurNum )
    {
        LeCanApp_u_RetVal = 1;
    }
    else
    {
        LeCanApp_u_RetVal = 0;
    }
    return LeCanApp_u_RetVal;
}

/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CanApp_NetTask (void)
{
	
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
uint8 CanApp_GetConfigSuccesFlag(void)
{ 
    return SeCanApp_u_ConfigSuccesFlag;
} 



/******************************N72**************************************************/
//EHB_Status (0x125) variables

float  GetCanApp_u_EHB_VehicleSpeed(void){
    return SeCanApp_u_EHB_VehicleSpeed;}
uint8_t  GetCanApp_u_EHB_VehicleSpeedInvalid(void){
    return SeCanApp_u_EHB_VehicleSpeedInvalid;}

//IPK_TotalOdometer (0x3F1) variables
uint32_t  GetCanApp_u_IPK_IPKTotalOdometer(void){
    return SeCanApp_u_IPK_IPKTotalOdometer;}

//PMS_VIN (0x610) variables
uint8_t  GetCanApp_u_PMS_VINCode7_14_S(void){
    return SeCanApp_u_PMS_VINCode7_14_S;}
uint8_t  GetCanApp_u_PMS_VINCode6_13_S(void){
    return SeCanApp_u_PMS_VINCode6_13_S;}
uint8_t  GetCanApp_u_PMS_VINCode5_12_S(void){
    return SeCanApp_u_PMS_VINCode5_12_S;}
uint8_t  GetCanApp_u_PMS_VINCode4_11_S(void){
    return SeCanApp_u_PMS_VINCode4_11_S;}
uint8_t  GetCanApp_u_PMS_VINCode3_10_17_S(void){
    return SeCanApp_u_PMS_VINCode3_10_17_S;}
uint8_t  GetCanApp_u_PMS_VINCode2_9_16_S(void){
    return SeCanApp_u_PMS_VINCode2_9_16_S;}
uint8_t  GetCanApp_u_PMS_VINCode1_8_15_S(void){
    return SeCanApp_u_PMS_VINCode1_8_15_S;}
uint8_t  GetCanApp_u_PMS_VINMessageNum_S(void){
    return SeCanApp_u_PMS_VINMessageNum_S;}

//TBOX_DateTime_Info (0x3E0) variables
uint8_t  GetCanApp_u_TBOX_Second(void){
    return SeCanApp_u_TBOX_Second;}
uint8_t  GetCanApp_u_TBOX_Minute(void){
    return SeCanApp_u_TBOX_Minute;}
uint8_t  GetCanApp_u_TBOX_Hour(void){
    return SeCanApp_u_TBOX_Hour;}
uint8_t  GetCanApp_u_TBOX_Day(void){
    return SeCanApp_u_TBOX_Day;}
uint8_t  GetCanApp_u_TBOX_Month(void){
    return SeCanApp_u_TBOX_Month;}
uint16_t  GetCanApp_u_TBOX_Year(void){
    return SeCanApp_u_TBOX_Year;}


/******************Write Signals*********************************/
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
void CanApp_SetMouseTxPhaseMax(void)
{
    SeCanApp_u_MouseTxPhase = 0xFFu;
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
void SetCanApp_ClearTimeOut(void)
{
    uint8 i;
    for(i = 0u;i <(uint8)VeCanApp_e_MsgMaxNum;i++)
    {
        SeCanApp_u_MsgPresentSts[i] = 1u; //LKC 20200514
        SeCanApp_u_MsgReceiveSts[i] = 0u;
    }
}
/*******************************************************************************
Name      :
Syntax      :
Sync/Async    : Synchronous
Reentrancy    :
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    :
Call By      :
History
<No.>    <author>    <time>    <description>
|******************************************************************************/
void CanApp_SetTxOkF(void)
{
	SeCanApp_u_TxOk_Flag =TRUE;
}

/*!
 * @brief Counter to manage the nested callings of global disable/enable interrupt.
 */
static int32_t g_interruptDisableCount = 0;
/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_DisableIRQGlobal
 * Description   : Disable system interrupt
 * This function will disable the global interrupt by calling the core API
 * Implements INT_SYS_DisableIRQGlobal_Activity
 *
 *END**************************************************************************/
void INT_SYS_DisableIRQGlobal(void)
{
    /* Disable the global interrupt */
    CanAppInterruptDisable();

    /* Update counter*/
    g_interruptDisableCount++;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_EnableIRQGlobal
 * Description   : Enable system interrupt
 * This function will enable the global interrupt by calling the core API
 * Implements INT_SYS_EnableIRQGlobal_Activity
 *
 *END**************************************************************************/
void INT_SYS_EnableIRQGlobal(void)
{
    /* Check and update */
    if (g_interruptDisableCount > 0)
    {
        g_interruptDisableCount--;

        if (g_interruptDisableCount <= 0)
        {
            /* Enable the global interrupt */
						CanAppInterruptEnable();
        }
    }
}
