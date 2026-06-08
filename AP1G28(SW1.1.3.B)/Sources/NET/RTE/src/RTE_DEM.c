/*******************************************************************************
||  File Name: RTE_DEM.c
||  Description: Implementation of the AUTOSAR DEM Interface
||-------------------------------------------------------------------------------
||  (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
||     All rights are reserved by CAEA.
||-------------------------------------------------------------------------------
|| Initials      Name                   Company
|| --------      ---------------------  -----------------------------------------
||                                    CAEA
||-------------------------------------------------------------------------------
||               R E V I S I O N   H I S T O R Y
||-------------------------------------------------------------------------------
|| Date          Version      Author    Description
|| ------------  --------     -------   -----------------------------------------
|| 2025.10.20     V1.0         SSS                                               
||
||******************************************************************************/

/*******************************************************************************
||    Other Header File Inclusion
||******************************************************************************/ 
#include "RTE_DEM.h"
#include "RTE_CAN.h"
#include "STD_AdcMCfg.h"
#include "STD_AdcM.h"
#include "CanApp.h"
#include "NmStack_Types.h"   
#include "CANNm.h"
#include "STD_BtrCtr.h"
#include "STD_BtrDiag.h"
#include "Fault_Diagnosis.h"
#include "CanApp.h"
/*******************************************************************************
||    Macro Definition
||******************************************************************************/

/*******************************************************************************
||    Enum Definition
||******************************************************************************/

/*******************************************************************************
||    Typedef Definition
||******************************************************************************/

/*******************************************************************************
||    Global variables Declaration
||******************************************************************************/

/*******************************************************************************
||    static local variables Declaration
||******************************************************************************/

/*******************************************************************************
||    static Local Functions Declaration
||******************************************************************************/

/*******************************************************************************
||    Extern variables and functions declaration
||******************************************************************************/
uint8 SeCanApp_u_LastFlag =0;		
uint8 SeCanApp_u_CurrentFlag = 0;

uint8 Can_GetBusOffDtc(void)
{ 
	uint8 LeCanApp_u_RetVal = 0u;
	
	if( RTE_NET_Can_BusOff())
	{
		SeCanApp_u_CurrentFlag = 1;  //busoff
	}
	else
	{
		SeCanApp_u_CurrentFlag = 0;
	}
	
	
	if( ( SeCanApp_u_CurrentFlag != SeCanApp_u_LastFlag) && (SeCanApp_u_CurrentFlag ==0) )
	{
			SeCanApp_u_LastFlag = 1;
			LeCanApp_u_RetVal =1;
	}
	else
	{		
		SeCanApp_u_LastFlag = SeCanApp_u_CurrentFlag;
		LeCanApp_u_RetVal =0;
	}
	
	
	return LeCanApp_u_RetVal;
}


uint8 Can_GetWakeCondition_3s(void)
{ 
	uint8 LeCanApp_u_RetVal = 0u;
	Nm_StateType  DEM_u_NMSt;
	Nm_ModeType   DEM_u_NMMode;
	static	uint16 LeCanApp_u_Counter = 0u;
	
	
	
	CanNm_GetState(0U,&DEM_u_NMSt,&DEM_u_NMMode);
	
	if(DEM_u_NMMode == NM_MODE_NETWORK)
	{
		LeCanApp_u_Counter++;
		if(LeCanApp_u_Counter >300)
		{
			LeCanApp_u_RetVal = 1;
			LeCanApp_u_Counter = 301;
		}
		else
		{
			LeCanApp_u_RetVal = 0;
		}
		
	}
	else
	{	LeCanApp_u_Counter =0;
		LeCanApp_u_RetVal = 0;
	}


    return LeCanApp_u_RetVal;
}






uint8 Can_GetBusOffDtcCondition(void)
{ 
	uint8 LeCanApp_u_RetVal = 0u;
	
	//if((0 != RTE_NET_Can_BusOff())

    return LeCanApp_u_RetVal;
}




/********************************** DEM Initialization **********************************/
/*******************************************************************************
*Function            : void RTE_NET_Dem_Init(void)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : DEM module initialization
|******************************************************************************/
void RTE_NET_Dem_Init(void)
{
    /* DEM initialization implementation */
}

/********************************** DTC Callback Functions **********************************/
/*******************************************************************************
*Function            : uint8 RTE_NET_Dem_Callback_DTC_E6B8_87(void)
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : U26B887-Lost communication with the VIU_FR controller
|******************************************************************************/
uint8 RTE_NET_Dem_Callback_DTC_E6B8_87(void)
{
    uint8 LeRteDem_u_Result = 0u;

	//if((1 == BTRCTR_GetLoadBatteryModeAStatus()) &&(0 ==RTE_NET_Can_BusOff()) &&(0 == RTE_NET_Can_Timeout_0x3ED_Msg()) &&(1 ==Can_GetWakeCondition_3s()))
	if((1 == BTRCTR_GetLoadBatteryModeAStatus()) &&(0 ==RTE_NET_Can_BusOff()) &&(0 == RTE_NET_Can_Timeout_0x3ED_Msg()))
    {
		LeRteDem_u_Result = 1;
	}
	else
	{
		LeRteDem_u_Result = 0u;
	}

	return LeRteDem_u_Result;
}

/*******************************************************************************
*Function            : RTE_NET_Dem_Callback_DTC_E6BB_88
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : U26BB88-Monitoring VRHCU Communication status(Bus Off)
|******************************************************************************/
uint8 RTE_NET_Dem_Callback_DTC_E6BB_88(void)
{
	uint8 LeCanApp_u_RetVal = 0u;
	if((CanCbk_GetBusOffDtcConditionState() == 1)&&(1U == BTRCTR_GetLoadBatteryModeAStatus() ))
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
*Function            : uint8 RTE_NET_Dem_Callback_DTC_97F8_16(void)
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : B17F816-Monitoring Vehicle Power(Low Voltage<=8.5V)
|******************************************************************************/
uint8 RTE_NET_Dem_Callback_DTC_97F8_16(void)
{
	uint8 LeDEM_u_RetVal = 0u;
	static uint8 BTRDIAG_GetLowVol_Counter = 0;
	
	if(1 == BTRDIAG_GetLowVolDtcStatus())
	{
		BTRDIAG_GetLowVol_Counter++;
		if(BTRDIAG_GetLowVol_Counter > 25)
		{
			LeDEM_u_RetVal =1;
			BTRDIAG_GetLowVol_Counter = 26;
		}
		else
		{
			LeDEM_u_RetVal =0;
		}
	}
	else
	{
		BTRDIAG_GetLowVol_Counter = 0;
		LeDEM_u_RetVal =0;
	}
	
	
    return LeDEM_u_RetVal;
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Dem_Callback_DTC_97F8_17(void)
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : B17F817-Monitoring Vehicle Power(High Voltage>=16.5V)
|******************************************************************************/
uint8 RTE_NET_Dem_Callback_DTC_97F8_17(void)
{
	uint8 LeDEM_u_RetVal = 0u;
	static uint8 BTRDIAG_HighLowVol_Counter = 0;
	
	
	if(1 == BTRDIAG_GetHighVolDtcStatus())
	{
		BTRDIAG_HighLowVol_Counter++;
		if(BTRDIAG_HighLowVol_Counter > 25)
		{
			LeDEM_u_RetVal =1;
			BTRDIAG_HighLowVol_Counter = 26;
		}
		else
		{
			LeDEM_u_RetVal =0;
		}	
	}
	else
	{
		BTRDIAG_HighLowVol_Counter = 0;
		LeDEM_u_RetVal =0;
	}
	
    return LeDEM_u_RetVal;
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Dem_Callback_DTC_97F8_06(void)
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : B17FA16-Detect faults of the refrigerator
                      (Compressor interface continuous output under voltage fault)
|******************************************************************************/
uint8 RTE_NET_Dem_Callback_DTC_97F8_06(void)
{
	
    uint8 LeRteDem_u_Result = 0u;

	if((1 == BTRCTR_GetLoadBatteryModeAStatus()) &&(0 ==RTE_NET_Can_BusOff()) &&(1 == FLT_TEST_COMP_OVERCURRENT()))
    {
		LeRteDem_u_Result = 1;
	}
	else
	{
		LeRteDem_u_Result = 0u;
	}

	return LeRteDem_u_Result;
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Dem_Callback_DTC_97FB_18(void)
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : B17FA12-Detect faults of the refrigerator
                      (Compressor phase current exceeds 15A)
|******************************************************************************/

uint8 RTE_NET_Dem_Callback_DTC_97FB_18(void)
{

    uint8 LeRteDem_u_Result = 0u;

	if((1 == BTRCTR_GetLoadBatteryModeAStatus()) &&(0 ==RTE_NET_Can_BusOff()) &&(1 == FLT_TEST_FAN_UC_FAULT()))
    {
		LeRteDem_u_Result = 1;
	}
	else
	{
		LeRteDem_u_Result = 0u;
	}

	return LeRteDem_u_Result;
}
/*******************************************************************************
*Function            : uint8 RTE_NET_Dem_Callback_DTC_97FB_19(void)
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : B17FA12-Detect faults of the refrigerator
                      (Compressor phase current exceeds 15A)
|******************************************************************************/
uint8 RTE_NET_Dem_Callback_DTC_97FB_19(void)
{
    uint8 LeRteDem_u_Result = 0u;

	if((1 == BTRCTR_GetLoadBatteryModeAStatus()) &&(0 ==RTE_NET_Can_BusOff()) &&(1 == FLT_TEST_FAN_FAULT()))
    {
		LeRteDem_u_Result = 1;
	}
	else
	{
		LeRteDem_u_Result = 0u;
	}

	return LeRteDem_u_Result;
}
/*******************************************************************************
*Function            : uint8 RTE_NET_Dem_Callback_DTC_97F8_4B(void)
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : B17FA12-Detect faults of the refrigerator
                      (Compressor phase current exceeds 15A)
|******************************************************************************/
uint8 RTE_NET_Dem_Callback_DTC_97F8_4B(void)
{

    uint8 LeRteDem_u_Result = 0u;

	if((1 == BTRCTR_GetLoadBatteryModeAStatus()) &&(0 ==RTE_NET_Can_BusOff()) &&(1 == FLT_TEST_PCB_OVER_TEMP()))
    {
		LeRteDem_u_Result = 1;
	}
	else
	{
		LeRteDem_u_Result = 0u;
	}

	return LeRteDem_u_Result;
}
/*******************************************************************************
*Function            : uint8 RTE_NET_Dem_Callback_DTC_97FC_19(void)
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : B17FA12-Detect faults of the refrigerator
                      (Compressor phase current exceeds 15A)
|******************************************************************************/
uint8 RTE_NET_Dem_Callback_DTC_97FC_19(void)
{

    uint8 LeRteDem_u_Result = 0u;

	if((1 == BTRCTR_GetLoadBatteryModeAStatus()) &&(0 ==RTE_NET_Can_BusOff()) &&(1 == FLT_TEST_HEAT_FILM_FAULT()))
    {
		LeRteDem_u_Result = 1;
	}
	else
	{
		LeRteDem_u_Result = 0u;
	}

	return LeRteDem_u_Result;
}
/*******************************************************************************
*Function            : uint8 RTE_NET_Dem_Callback_DTC_97FC_18(void)
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : B17FA12-Detect faults of the refrigerator
                      (Compressor phase current exceeds 15A)
|******************************************************************************/
uint8 RTE_NET_Dem_Callback_DTC_97FC_18(void)
{

    uint8 LeRteDem_u_Result = 0u;

	if((1 == BTRCTR_GetLoadBatteryModeAStatus()) &&(0 ==RTE_NET_Can_BusOff()) &&(1 == FLT_TEST_HEAT_FILM_UC_FAULT()))
    {
		LeRteDem_u_Result = 1;
	}
	else
	{
		LeRteDem_u_Result = 0u;
	}

	return LeRteDem_u_Result;
}
/*******************************************************************************
*Function            : uint8 RTE_NET_Dem_Callback_DTC_97FD_19(void)
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : B17FA12-Detect faults of the refrigerator
                      (Compressor phase current exceeds 15A)
|******************************************************************************/
uint8 RTE_NET_Dem_Callback_DTC_97FD_19(void)
{

    uint8 LeRteDem_u_Result = 0u;

	if((1 == BTRCTR_GetLoadBatteryModeAStatus()) &&(0 ==RTE_NET_Can_BusOff()) &&(1 == FLT_TEST_HEAT_STRIP_FAULT()))
    {
		LeRteDem_u_Result = 1;
	}
	else
	{
		LeRteDem_u_Result = 0u;
	}

	return LeRteDem_u_Result;
}
/*******************************************************************************
*Function            : uint8 RTE_NET_Dem_Callback_DTC_97FD_18(void)
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : B17FA12-Detect faults of the refrigerator
                      (Compressor phase current exceeds 15A)
|******************************************************************************/
uint8 RTE_NET_Dem_Callback_DTC_97FD_18(void)
{

    uint8 LeRteDem_u_Result = 0u;

	if((1 == BTRCTR_GetLoadBatteryModeAStatus()) &&(0 ==RTE_NET_Can_BusOff()) &&(1 == FLT_TEST_HEAT_STRIP_UC_FAULT()))
    {
		LeRteDem_u_Result = 1;
	}
	else
	{
		LeRteDem_u_Result = 0u;
	}

	return LeRteDem_u_Result;
}
/*******************************************************************************
*Function            : uint8 RTE_NET_Dem_Callback_DTC_97F8_09(void)
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : B17FA12-Detect faults of the refrigerator
                      (Compressor phase current exceeds 15A)
|******************************************************************************/
uint8 RTE_NET_Dem_Callback_DTC_97F8_09(void)
{

    uint8 LeRteDem_u_Result = 0u;

	if((1 == BTRCTR_GetLoadBatteryModeAStatus()) &&(0 ==RTE_NET_Can_BusOff()) &&(1 == FLT_TEST_LINER_TEMPSENSOR()))
    {
		LeRteDem_u_Result = 1;
	}
	else
	{
		LeRteDem_u_Result = 0u;
	}

	return LeRteDem_u_Result;
}
/*******************************************************************************
*Function            : uint8 RTE_NET_Dem_Callback_DTC_97F9_09(void)
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : B17FA12-Detect faults of the refrigerator
                      (Compressor phase current exceeds 15A)
|******************************************************************************/
uint8 RTE_NET_Dem_Callback_DTC_97F9_09(void)
{

    uint8 LeRteDem_u_Result = 0u;

	if((1 == BTRCTR_GetLoadBatteryModeAStatus()) &&(0 ==RTE_NET_Can_BusOff()) &&(1 == FLT_TEST_CONDENSER_TEMP_SENSOR()))
    {
		LeRteDem_u_Result = 1;
	}
	else
	{
		LeRteDem_u_Result = 0u;
	}

	return LeRteDem_u_Result;
}
/*******************************************************************************
*Function            : uint8 RTE_NET_Dem_Callback_DTC_97F8_71(void)
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : B17FA12-Detect faults of the refrigerator
                      (Compressor phase current exceeds 15A)
|******************************************************************************/
uint8 RTE_NET_Dem_Callback_DTC_97F8_71(void)
{

    uint8 LeRteDem_u_Result = 0u;

	if((1 == BTRCTR_GetLoadBatteryModeAStatus()) &&(0 ==RTE_NET_Can_BusOff()) &&(1 == FLT_TEST_COMP_STARTUP_FAIL()))
    {
		LeRteDem_u_Result = 1;
	}
	else
	{
		LeRteDem_u_Result = 0u;
	}

	return LeRteDem_u_Result;
}
/*******************************************************************************
*Function            : uint8 RTE_NET_Dem_Callback_DTC_97F8_49(void)
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : B17FA12-Detect faults of the refrigerator
                      (Compressor phase current exceeds 15A)
|******************************************************************************/
uint8 RTE_NET_Dem_Callback_DTC_97F8_49(void)
{

    uint8 LeRteDem_u_Result = 0u;

	if((1 == BTRCTR_GetLoadBatteryModeAStatus()) &&(0 ==RTE_NET_Can_BusOff()) &&((1 == FLT_TEST_WLED_UNDER_CURRENT()) || (1 == FLT_TEST_WLED_OVER_CURRENT())))
    {
		LeRteDem_u_Result = 1;
	}
	else
	{
		LeRteDem_u_Result = 0u;
	}

	return LeRteDem_u_Result;
}
/*******************************************************************************
*Function            : uint8 RTE_NET_Dem_Callback_DTC_97F9_49(void)
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : B17FA12-Detect faults of the refrigerator
                      (Compressor phase current exceeds 15A)
|******************************************************************************/
uint8 RTE_NET_Dem_Callback_DTC_97F9_49(void)
{

    uint8 LeRteDem_u_Result = 0u;

	if((1 == BTRCTR_GetLoadBatteryModeAStatus()) &&(0 ==RTE_NET_Can_BusOff()) &&((1 == FLT_TEST_ALED_UNDER_CURRENT()) || (1 == FLT_TEST_ALED_OVER_CURRENT())))
    {
		LeRteDem_u_Result = 1;
	}
	else
	{
		LeRteDem_u_Result = 0u;
	}

	return LeRteDem_u_Result;
}
/*******************************************************************************
*Function            : uint8 RTE_NET_Dem_Callback_DTC_97FA_49(void)
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : B17FA12-Detect faults of the refrigerator
                      (Compressor phase current exceeds 15A)
|******************************************************************************/
uint8 RTE_NET_Dem_Callback_DTC_97FA_49(void)
{

    uint8 LeRteDem_u_Result = 0u;

	if((1 == BTRCTR_GetLoadBatteryModeAStatus()) &&(0 ==RTE_NET_Can_BusOff()) &&((1 == FLT_TEST_UVLED_UNDER_CURRENT()) || (1 == FLT_TEST_UVLED_OVER_CURRENT())))
    {
		LeRteDem_u_Result = 1;
	}
	else
	{
		LeRteDem_u_Result = 0u;
	}

	return LeRteDem_u_Result;
}
/*******************************************************************************
*Function            : uint8 RTE_NET_Dem_Callback_DTC_97FA_09(void)
*ReturnValue         : uint8
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : uint8                        :DTC status (0=OK, 1=Error)
*Description         : B17FA12-Detect faults of the refrigerator
                      (Compressor phase current exceeds 15A)
|******************************************************************************/
uint8 RTE_NET_Dem_Callback_DTC_97FA_09(void)
{

    uint8 LeRteDem_u_Result = 0u;

	if((1 == BTRCTR_GetLoadBatteryModeAStatus()) &&(0 ==RTE_NET_Can_BusOff()) &&((FLT_TEST_HALL_UNDER_VOL_FAULT()  ) || (FLT_TEST_HALL_OVER_VOL_FAULT() )))
    {
		LeRteDem_u_Result = 1;
	}
	else
	{
		LeRteDem_u_Result = 0u;
	}

	return LeRteDem_u_Result;
}
/********************************** DEM Main Functions **********************************/
/*******************************************************************************
*Function            : void RTE_NET_Dem_10msMainFunction(void)
*ReturnValue         : void
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : None
*Description         : DEM 10ms main function
|******************************************************************************/
void RTE_NET_Dem_10msMainFunction(void)
{
   Can_GetBusOffDtc();
   Can_GetWakeCondition_3s();
}

/*******************************************************************************
*Function            : void RTE_NET_Dem_20msMainFunction(void)
*ReturnValue         : void
*Parameters(in)      : None
*Parameters(in)      : None
*Parameters(out)     : None                        
*Return value        : None
*Description         : DEM 20ms main function
|******************************************************************************/
void RTE_NET_Dem_20msMainFunction(void)
{
    /* DEM 20ms main function implementation */
}

uint8 RTE_NET_Dem_GetIgnStatus(void)
{
    uint8 LeDEM_u_DtcIndex = CanDEM_u_Zero;
	
	if(2 == RTE_NET_Can_Read_BcmPwrStsFb())
	{
		LeDEM_u_DtcIndex = 1;
	}
	else
	{
		LeDEM_u_DtcIndex = 0;
						  
	}
	

    return LeDEM_u_DtcIndex;
}

uint8 RTE_NET_Dem_GetBatteryMode(void)/*9-16V*/
{
  /*  uint16 e_u_ADValue;
    static uint8 SysBatteryMode = CanDem_MODE_B;
    e_u_ADValue = ADCM_GetValidValue(ADCMCFG_KL30_AD_CH);
    
    if(SysBatteryMode == CanDem_MODE_B) 
    {
        if( (e_u_ADValue <= (uint16)CAN_DEM_BATTERYH_ON) \
                && (e_u_ADValue >= (uint16)CAN_DEM_BATTERYL_ON))    
        {
            SysBatteryMode = CanDem_MODE_A;
        }
    }
    else
    {
        if( (e_u_ADValue <= (uint16)CAN_DEM_BATTERYL_OFF) \
                || (e_u_ADValue >= (uint16)CAN_DEM_BATTERYH_OFF))
        {
            SysBatteryMode = CanDem_MODE_B;
        }
    }
    
    return SysBatteryMode;*/
    
    return TRUE;

}



uint8 RTE_NET_Dem_GetDTC_85EN(void)
{
    uint8 e_u_Temp = CanDem_GetDTCSetting();
    return e_u_Temp;
}

uint8 RTE_NET_Dem_GetNFirstPowerOn(void)
{
  /*  uint8 e_u_Temp;
    e_u_Temp = CanMain_GetDTCENFlag();*/
    
    return TRUE;
}

uint8 RTE_NET_Dem_GetBusOffSta(void)
{
   // uint8 LeDEM_u_DtcIndex = RTE_NET_Can_BusOff();

    return (uint8)(1);
}

