
/*******************************************************************************
|  File Name:  DTC_Callback.c
|  Description:  Implementation of the System sofeware DTC Control Service
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           YaJun Xia           CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2018-6-16    01.00.00     XYJ       Creation

|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "DTC_Callback.h"
#include "BusOff_Recovery.h"
//#include "CAEA_Types.h"
//#include "STD_BtrDiag.h"
#include "STD_BtrM.h"
#include "Rte_Can.h"
#include "CanApp.h"
#include "il_par.h"
//#include "Flash_If.h"
//#include "Dms_Diag.h"
//#include "Spi_Comm.h"
//#include "Dms_Diag.h"
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
|    Global variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/
void  DTC_ReadVehicleNetConfig(void)
{
	//Eep_ReadData(EEP_DID_F110_ADDR,DID0xF110Buf,8u);
}

/**********************U300616 -> Diagnose undervoltage faults*******************/
uint8 DTC_Callback_0xF006_16(void)
{
	static uint8 TempBatterySts = 0u;
	static uint8 F006_16_counter0 = 0u; 
	static uint16 F006_16_counter1 = 0u; 
	

	if(adc_if_get_validValue(adc_cl_bat)<VOLTAGE_LOW_THRESHOLD)
	{
		F006_16_counter0++;
		F006_16_counter1= 0u ;
		if(F006_16_counter0>4u)
		{
			TempBatterySts = 1u;
			F006_16_counter0 = 6u;
		}
	}
	else if(adc_if_get_validValue(adc_cl_bat) > VOLTAGE_RECOVERY_LOW )
	{
		F006_16_counter1++;
		F006_16_counter0 = 0u;
		if(F006_16_counter1>20u)
		{
		  TempBatterySts = 0u;
			F006_16_counter1 = 22u;
		}
	}
	else
	{
	  F006_16_counter0 = 0u;
		F006_16_counter1 = 0u;
	}
		
	return TempBatterySts;
}

/**********************U300617 -> Diagnose overvoltage faults*******************/
uint8 DTC_Callback_0xF006_17(void)
{
	static uint8 TempBatterySts = 0u;
  static uint8 F006_17_counter0 = 0u; 
	static uint16 F006_17_counter1 = 0u; 
  if(adc_if_get_validValue(adc_cl_bat)>VOLTAGE_HIGH_THRESHOLD)
	{
		F006_17_counter0++;
		F006_17_counter1= 0u ;
		if(F006_17_counter0>4u)
		{
		  TempBatterySts = 1u;
			F006_17_counter0 = 6u;
		}
	}
	else if(adc_if_get_validValue(adc_cl_bat) < VOLTAGE_RECOVERY_HIGH )
	{
		F006_17_counter1++;
		F006_17_counter0 = 0u;
		if(F006_17_counter1>20u)
		{
	  TempBatterySts = 0u;
			F006_17_counter1 = 22u;
		}
	}
 else
 	{
	   F006_17_counter0 = 0u;
	 	 F006_17_counter1 = 0u;
	 }
	return TempBatterySts;
}

/**********************U007300 -> CAN bus off*******************/
uint8 DTC_Callback_0xC073_00(void)
{
	uint8 LeRteDem_u_Result = 0u;


	if((adc_if_get_validValue(adc_cl_bat)<VOLTAGE_LOW_THRESHOLD)|| (adc_if_get_validValue(adc_cl_bat)>VOLTAGE_HIGH_THRESHOLD))  
	{
		return 0;
	}
	
	
	if (TRUE == CanCbk_GetBusOffDtcConditionState())
	{
		LeRteDem_u_Result = 1u;
	}
	else
	{
		LeRteDem_u_Result = 0u;
	}

	return LeRteDem_u_Result;
}

/**********************B13E153 -> The MIC is not inserted.*******************/
uint8 DTC_Callback_0x93E1_53(void)
{
	uint8 LeRteDem_u_Result = 0u;

	
	if((adc_if_get_validValue(adc_cl_bat)<VOLTAGE_LOW_THRESHOLD)|| (adc_if_get_validValue(adc_cl_bat)>VOLTAGE_HIGH_THRESHOLD))  
	{
		return 0;
	}
	
	
 if(adc_if_get_validValue(adc_cl_mic_8v_cs) < MIC_CURRENT_LOW)
	{
		LeRteDem_u_Result = 1u;
	}
	else if((adc_if_get_validValue(adc_cl_mic_8v_cs) > MIC_CURRENT_HIGH0 )&&(adc_if_get_validValue(adc_cl_mic_8v_cs) < MIC_CURRENT_HIGH1))
	{
	  LeRteDem_u_Result = 0u;
	}
	else
	{
		;
	}
	return LeRteDem_u_Result;
	
}


/*EOF*/
