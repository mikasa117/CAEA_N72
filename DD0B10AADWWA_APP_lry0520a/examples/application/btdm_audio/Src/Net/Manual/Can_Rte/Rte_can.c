#include "Rte_Can.h"
#include "Canapp.h"
//#include "Can_Drv.h"





/****************** Receive *********************/


//EHB_Status (0x125) variables

float  Rte_Read_EHB_VehicleSpeed(void)
{

    return GetCanApp_u_EHB_VehicleSpeed();

}
uint8_t  Rte_Read_EHB_VehicleSpeedInvalid(void)
{

    return GetCanApp_u_EHB_VehicleSpeedInvalid();

}

//IPK_TotalOdometer (0x3F1) variables
uint32_t  Rte_Read_IPK_IPKTotalOdometer(void)
{
    return GetCanApp_u_IPK_IPKTotalOdometer();
}

//PMS_VIN (0x610) variables 
uint8_t  Rte_Read_PMS_VINCode7_14_S(void)
{
    return GetCanApp_u_PMS_VINCode7_14_S();
}
uint8_t  Rte_Read_PMS_VINCode6_13_S(void)
{
    return GetCanApp_u_PMS_VINCode6_13_S();
}
uint8_t  Rte_Read_PMS_VINCode5_12_S(void)
{
    return GetCanApp_u_PMS_VINCode5_12_S();
}
uint8_t  Rte_Read_PMS_VINCode4_11_S(void)
{
    return GetCanApp_u_PMS_VINCode4_11_S();
}
uint8_t  Rte_Read_PMS_VINCode3_10_17_S(void)
{
    return GetCanApp_u_PMS_VINCode3_10_17_S();
}
uint8_t  Rte_Read_PMS_VINCode2_9_16_S(void)
{
    return GetCanApp_u_PMS_VINCode2_9_16_S();
}
uint8_t  Rte_Read_PMS_VINCode1_8_15_S(void)
{
    return GetCanApp_u_PMS_VINCode1_8_15_S();
}
uint8_t  Rte_Read_PMS_VINMessageNum_S(void)
{
    return GetCanApp_u_PMS_VINMessageNum_S();
}

//TBOX_DateTime_Info (0x3E0) variables
uint8_t  Rte_Read_TBOX_Second(void)
{
    return GetCanApp_u_TBOX_Second();
}
uint8_t  Rte_Read_TBOX_Minute(void)
{
    return GetCanApp_u_TBOX_Minute();
}
uint8_t  Rte_Read_TBOX_Hour(void)
{
    return GetCanApp_u_TBOX_Hour();
}
uint8_t  Rte_Read_TBOX_Day(void)
{
    return GetCanApp_u_TBOX_Day();
}
uint8_t  Rte_Read_TBOX_Month(void)
{
    return GetCanApp_u_TBOX_Month();
}
uint16_t  Rte_Read_TBOX_Year(void)
{
    return GetCanApp_u_TBOX_Year();
}


/****************** write *********************/

//MMI_Status_Info (0x2A4) variables
void RteCan_Write_MMI_WorkMode( uint32_t LeRteCan_u_Value )
{ 
    IlPutTxMMI_WorkMode(LeRteCan_u_Value);
}
void RteCan_Write_MMI_ReturnSwStatus( uint32_t LeRteCan_u_Value )
{ 
    IlPutTxMMI_ReturnSwStatus(LeRteCan_u_Value);
}
void RteCan_Write_MMI_ConfirmSwStatus( uint32_t LeRteCan_u_Value )
{ 
    IlPutTxMMI_ConfirmSwStatus(LeRteCan_u_Value);
}
void RteCan_Write_MMI_DownSwStatus( uint32_t LeRteCan_u_Value )
{ 
    IlPutTxMMI_DownSwStatus(LeRteCan_u_Value);
}
void RteCan_Write_MMI_UpSwStatus( uint32_t LeRteCan_u_Value )
{ 
    IlPutTxMMI_UpSwStatus(LeRteCan_u_Value);
}
void RteCan_Write_MMI_LeftSwStatus( uint32_t LeRteCan_u_Value )
{ 
    IlPutTxMMI_LeftSwStatus(LeRteCan_u_Value);
}
void RteCan_Write_MMI_RightSwStatus( uint32_t LeRteCan_u_Value )
{ 
    IlPutTxMMI_RightSwStatus(LeRteCan_u_Value);
}

//MMI_TextBTData (0x0F9) variables
void RteCan_Write_MMI_TextBTDataFrame( vuint8* LeRteCan_u_Value )
{ 
    IlPutTxMMI_TextBTDataFrame(LeRteCan_u_Value);
}

//MMI_TextMMData (0x0FB) variables
void RteCan_Write_MMI_TextMultDataFrame( vuint8* LeRteCan_u_Value )
{ 
		IlPutTxMMI_TextMultDataFrame(LeRteCan_u_Value);
	
    
}

//TTS_Status (0x249) variables
void RteCan_Write_TTS_BluetoothFunction( uint32_t LeRteCan_u_Value )
{ 
    IlPutTxTTS_BluetoothFunction(LeRteCan_u_Value);
}
void RteCan_Write_TTS_BluetoothConnect( uint32_t LeRteCan_u_Value )
{ 
    IlPutTxTTS_BluetoothConnect(LeRteCan_u_Value);
}
