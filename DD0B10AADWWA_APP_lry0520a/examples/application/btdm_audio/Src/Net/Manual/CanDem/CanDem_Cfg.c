
/*******************************************************************************
|  (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company

| --------      ---------------------  -----------------------------------------
| psp           panshouping            CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 2017-10-14    0.01         psp       DEM Config
|******************************************************************************/
#include "DTC_Callback.h"
#include "CanDem.h"
#include "CanDem_Cfg.h"
#include "CanDem_Callback.h"

/*******************************************************************************
Name                        :   CanDem_InitMemory
Syntax                  :
Sync/Async          : Synchronous
Reentrancy          :
Parameters(in)  : None
Parameters(out) : None
Return value        : None
Description         :   Intialize variables
Call By                 :   DTC_Callback_ReadEeprom
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CanDem_Cfg_InitMemory(void)
{
	;
}


const DTCHandler_Type SsDEM_h_MoniEnCodHandler[CanDem_u_SysEnCondNumber] =
{
	&CanDem_GetIgnStatus,//bit0
	&CanDem_GetBatteryMode,
	&CanDem_GetDTC_85EN,
	&CanDem_GetPowerModeOn,
	&CanDem_GetBusOffState,
	&CanDem_GetSPIComState,
};


const uint8  CaDEM_u_MoniEnTime[CanDem_u_SysEnCondNumber] =
{
	3000U/CanDem_u_EnTimeBase, 	/*3000 for IGN*/
	500U/CanDem_u_EnTimeBase, 	/*500ms for Voltage Level*/
	20U/CanDem_u_EnTimeBase, 	/*20ms for 85 status*/
	0U/CanDem_u_EnTimeBase, 	/*Power Mode status*/
	20U/CanDem_u_EnTimeBase, 	/*20ms for DTC BusOff*/
	20U/CanDem_u_EnTimeBase, 	/*20ms for SPI communication*/
};


const DebounceTimeTable_Type SsDem_e_DebounceTimeTable[9u] =
{
    /*   e_w_DtcTimeQuick        	e_w_DtcTimePass            	e_w_DtcTimeFail*/
	{ 20U/CanDem_u_TimeBase, 	 0U/CanDem_u_TimeBase,      0U/CanDem_u_TimeBase },	 /* CAN bus off &Lost communication with MMI *&Invalid Data Received From MMI DTC Debounce*/
  { 20U/CanDem_u_TimeBase, 	 2800U/CanDem_u_TimeBase,   800U/CanDem_u_TimeBase},	/*Battery low & High DTC Debounce*/
  { 20U/CanDem_u_TimeBase, 	 0U/CanDem_u_TimeBase,    	0U/CanDem_u_TimeBase },	/*SPI communication failure DTC Debounce*/
  { 20U/CanDem_u_TimeBase, 	 50U/CanDem_u_TimeBase, 		5000U/CanDem_u_TimeBase },	/*camera failure DTC Debounce*/
	{ 20U/CanDem_u_TimeBase, 	 5000U/CanDem_u_TimeBase, 	5000U/CanDem_u_TimeBase },	/*Camrea image & LED & Sensor power error DTC Debounce */
	{ 20U/CanDem_u_TimeBase, 	 2000U/CanDem_u_TimeBase, 	2000U/CanDem_u_TimeBase },	/*PMIC output power error DTC Debounce*/
	{ 20U/CanDem_u_TimeBase, 	 20U/CanDem_u_TimeBase, 		500U/CanDem_u_TimeBase },	/*Invalid Data Received From MMI DTC Debounce*/
	{ 20U/CanDem_u_TimeBase, 	 20U/CanDem_u_TimeBase, 		250U/CanDem_u_TimeBase },	/*Invalid Data Received From EHB DTC Debounce  & Lost communication with EHB DTC Debounce*/
	{ 20U/CanDem_u_TimeBase, 	 20U/CanDem_u_TimeBase, 		20U/CanDem_u_TimeBase },	/*Software versions & Flash block error*/
};


const DtcInfo_Type DsDem_h_ManagementUnit[CanDem_u_DtcNumber] =
{
/*           DTCHandler               DTCNum            FailType               EepID          						DebounceIndex     DtcEnCond   Monitor_Rate  DtcOperationCycleId     Agingtimes   DtcSupport*/
	{ &DTC_Callback_0xF006_16,    (uint16)0xF006,     (uint8)0x16,     0x1601,      0x01U,          0x05U,      0x01U,        OpCycle_IGN,         AgingCounter,    TRUE},
	{ &DTC_Callback_0xF006_17,    (uint16)0xF006,     (uint8)0x17,     0x1602,      0x01U,          0x05U,      0x01U,        OpCycle_IGN,         AgingCounter,    TRUE},
	{ &DTC_Callback_0xC073_00,    (uint16)0xC073,     (uint8)0x00,     0x1603,      0x00U,          0x07U,      0x01U,        OpCycle_IGN,         AgingCounter,    TRUE},
	{ &DTC_Callback_0x93E1_53,    (uint16)0x93E1,     (uint8)0x53,     0x1604,	  	0x02U,          0x17U,      0x01U,        OpCycle_IGN,         AgingCounter,    TRUE},
	};

