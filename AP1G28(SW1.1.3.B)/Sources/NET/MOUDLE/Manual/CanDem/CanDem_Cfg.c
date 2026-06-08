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
#include "CAEA_Types.h"
#include "CanDem.h"
#include "CanDem_Cfg.h"
#include "CanDem_Callback.h"
#include "STD_EepM.h"
#include "RTE_DEM.h"

uint8 SeDem_u_BswCallbackDTC[CanDem_u_DtcNumber];


//#pragma section text Code_CanDem_Cfg

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

}

/*******************************************************************************
Name                        :   CanDem_InitMemoryKAM
Syntax                  : None  
Sync/Async          : Synchronous
Reentrancy          :   None
Parameters(in)  : None
Parameters(out) : None
Return value        : None
Description         :   None
Call By                 :   None
History
<No.>    <author>    <time>    <description>

|******************************************************************************/ 
void CanDem_Cfg_InitMemoryKAM(void)
{

}

const DTCHandler_Type SsDEM_h_MoniEnCodHandler[CanDem_u_SysEnCondNumber] = 
{
  &RTE_NET_Dem_GetIgnStatus,
  &RTE_NET_Dem_GetBatteryMode,
  &RTE_NET_Dem_GetDTC_85EN,
  &RTE_NET_Dem_GetNFirstPowerOn,
  &RTE_NET_Dem_GetBusOffSta,
};

const uint8  CaDEM_u_MoniEnTime[CanDem_u_SysEnCondNumber] =
{
  2200U/CanDem_u_EnTimeBase, /*3000 For IGN*/
  20U/CanDem_u_EnTimeBase, /*Voltage Level*/
  20U/CanDem_u_EnTimeBase, /*85 status*/
  20U/CanDem_u_EnTimeBase, /*3000ms DTC EN status*/
  20U/CanDem_u_EnTimeBase, /*1000ms BusOff status*/
};



const DebounceTimeTable_Type SsDem_e_DebounceTimeTable[5] =
{
    /*       e_w_DtcTimeQuick        e_w_DtcTimePass            e_w_DtcTimeFail*/ 
    { 10U/CanDem_u_TimeBase,  500U/CanDem_u_TimeBase,     500U/CanDem_u_TimeBase },/*Battery low/high DTC Debounce*/
    { 10U/CanDem_u_TimeBase,  10U/CanDem_u_TimeBase,      10U/CanDem_u_TimeBase },
    { 10U/CanDem_u_TimeBase,  120000U/CanDem_u_TimeBase,  10U/CanDem_u_TimeBase },
    { 10U/CanDem_u_TimeBase,  1000U/CanDem_u_TimeBase,    1000U/CanDem_u_TimeBase },
    { 10U/CanDem_u_TimeBase,  3000U/CanDem_u_TimeBase,    3000U/CanDem_u_TimeBase }
};


const DtcInfo_Type DsDem_h_ManagementUnit[CanDem_u_DtcNumber] =
{   
                /*DTCHandler              DTCNum               FailType                 EepID                             DebounceIndex   DtcEnCond  Monitor_Rate  DtcOperationCycleId   Agingtimes  DtcSupport*/ 

         { &RTE_NET_Dem_Callback_DTC_E6B8_87,   (uint16)0xE6B8U,    (uint8)0x87U,    (uint8)EEP_BLOCK_E6B8_87_ID,          0x01U,          0x1FU,      0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},

         { &RTE_NET_Dem_Callback_DTC_E6BB_88,   (uint16)0xE6BBU,    (uint8)0x88U,    (uint8)EEP_BLOCK_E6BB_88_ID,          0x01U,          0x1FU,      0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},

         { &RTE_NET_Dem_Callback_DTC_97F8_16,   (uint16)0x97F8U,    (uint8)0x16U,    (uint8)EEP_BLOCK_97F8_16_ID,          0x01U,          0x1FU,      0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},
                                                                            
         { &RTE_NET_Dem_Callback_DTC_97F8_17,   (uint16)0x97F8U,    (uint8)0x17U,    (uint8)EEP_BLOCK_97F8_17_ID,          0x01U,          0x1FU,      0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},
        
         { &RTE_NET_Dem_Callback_DTC_97F8_06,   (uint16)0x97F8U,    (uint8)0x06U,    (uint8)EEP_BLOCK_97F8_06_ID,          0x01U,          0x1FU ,     0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},
        
         { &RTE_NET_Dem_Callback_DTC_97FB_18,   (uint16)0x97FBU,    (uint8)0x18U,    (uint8)EEP_BLOCK_97FB_18_ID,          0x01U,          0x1FU,      0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},     

         { &RTE_NET_Dem_Callback_DTC_97FB_19,   (uint16)0x97FBU,    (uint8)0x19U,    (uint8)EEP_BLOCK_97FB_19_ID,          0x01U,          0x1FU,      0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},
                                             
         { &RTE_NET_Dem_Callback_DTC_97F8_4B,   (uint16)0x97F8U,    (uint8)0x4BU,    (uint8)EEP_BLOCK_97F8_4B_ID,          0x01U,          0x1FU,      0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},

         { &RTE_NET_Dem_Callback_DTC_97FC_19,   (uint16)0x97FCU,    (uint8)0x19U,    (uint8)EEP_BLOCK_97FC_19_ID,          0x01U,          0x1FU,      0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},

         { &RTE_NET_Dem_Callback_DTC_97FC_18,   (uint16)0x97FCU,    (uint8)0x18U,    (uint8)EEP_BLOCK_97FC_18_ID,          0x01U,          0x1FU,      0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},

         { &RTE_NET_Dem_Callback_DTC_97FD_19,   (uint16)0x97FDU,    (uint8)0x19U,    (uint8)EEP_BLOCK_97FD_19_ID,          0x01U,          0x1FU,      0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},        
          
         { &RTE_NET_Dem_Callback_DTC_97FD_18,   (uint16)0x97FDU,    (uint8)0x18U,    (uint8)EEP_BLOCK_97FD_18_ID,          0x01U,          0x1FU,      0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},     
         
         { &RTE_NET_Dem_Callback_DTC_97F8_09,   (uint16)0x97F8U,    (uint8)0x09U,    (uint8)EEP_BLOCK_97F8_09_ID,          0x01U,          0x1FU,      0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},
                                                                            
         { &RTE_NET_Dem_Callback_DTC_97F9_09,   (uint16)0x97F9U,    (uint8)0x09U,    (uint8)EEP_BLOCK_97F9_09_ID,          0x01U,          0x1FU,      0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},
                                                                           
         { &RTE_NET_Dem_Callback_DTC_97F8_71,   (uint16)0x97F8U,    (uint8)0x71U,    (uint8)EEP_BLOCK_97F8_71_ID,          0x01U,          0x1FU,      0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},
                                                                            
         { &RTE_NET_Dem_Callback_DTC_97F8_49,   (uint16)0x97F8U,    (uint8)0x49U,    (uint8)EEP_BLOCK_97F8_49_ID,          0x01U,          0x1FU,      0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},
                                                                       
         { &RTE_NET_Dem_Callback_DTC_97F9_49,   (uint16)0x97F9U,    (uint8)0x49U,    (uint8)EEP_BLOCK_97F9_49_ID,          0x01U,          0x1FU,      0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},
        
         { &RTE_NET_Dem_Callback_DTC_97FA_49,   (uint16)0x97FAU,    (uint8)0x49U,    (uint8)EEP_BLOCK_97FA_49_ID,          0x01U,          0x1FU ,     0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},
         
         { &RTE_NET_Dem_Callback_DTC_97FA_09,   (uint16)0x97FAU,    (uint8)0x09U,    (uint8)EEP_BLOCK_97FA_09_ID,          0x01U,          0x1FU ,     0x01U,      OpCycle_POWER,        AgingCounter,    TRUE},

};

