#include "STD_DioIf.h"
#include "sdk_project_config.h"
#include "STD_Lib.h"

void DioIf_Init(void)
{

}

void DioIf_DeInit(void)
{
}


void DioIf_WriteChannel(uint8 ChannelId,uint8 Level)
{
	const uint8 TempPort = ChannelId>>5;
	switch(TempPort)
	{
		case (uint8)0x00:
				PINS_DRV_WritePin(GPIOA,(pins_channel_type_t)ChannelId&(pins_channel_type_t)0x1f,Level);
		break;
		case (uint8)0x01:
				PINS_DRV_WritePin(GPIOB,(pins_channel_type_t)ChannelId&(pins_channel_type_t)0x1f,Level);
		break;
		case (uint8)0x02:
				PINS_DRV_WritePin(GPIOC,(pins_channel_type_t)ChannelId&(pins_channel_type_t)0x1f,Level);
		break;
		case (uint8)0x03:
				PINS_DRV_WritePin(GPIOD,(pins_channel_type_t)ChannelId&(pins_channel_type_t)0x1f,Level);
		break;
		case (uint8)0x04:
				PINS_DRV_WritePin(GPIOE,(pins_channel_type_t)ChannelId&(pins_channel_type_t)0x1f,Level);
		break;
		default:
				break;
	}
}
uint8 DioIf_ReadChannel(uint8 ChannelId)
{
	const uint8 TempChannelId = ChannelId;
	const uint8 TempPort = ChannelId>>5;
	uint8       TempResult = 0u;
	uint32      TempRegResult = 0u;

	switch(TempPort)
	{
		case (uint8)0x00:
				TempRegResult = PINS_DRV_ReadPins(GPIOA);
		break;
		case (uint8)0x01:
				TempRegResult = PINS_DRV_ReadPins(GPIOB);
		break;
		case (uint8)0x02:
				TempRegResult = PINS_DRV_ReadPins(GPIOC);
		break;
		case (uint8)0x03:
				TempRegResult = PINS_DRV_ReadPins(GPIOD);
		break;
		case (uint8)0x04:
				TempRegResult = PINS_DRV_ReadPins(GPIOE);
		break;
		default:
				TempRegResult = 0u;
				break;


	}
/*	TempResult = ((uint8)((uint32)TempRegResult>>((uint8)ChannelId & (uint8)0x1fu)));*/
	TempResult = LIB_GET_UINT32_BIT((uint32)TempRegResult, ((uint8)TempChannelId & (uint8)0x1fu));
    return (uint8)(TempResult);
}
