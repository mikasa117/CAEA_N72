/* polyspace<MISRA-C3:1.1:Not a defect:Justified> NO fluence */
/*******************************************************************************
|  File Name:  STD_DioIf.c
|  Description:  Implementation of the STD_DioIf Config Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           XiaYaJun          CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 2018-05-23    01.00.00     XYJ       Creation
|******************************************************************************/
/* polyspace:begin<MISRA-C3:11.4:Not a defect:Justified> Normal */
/*******************************************************************************
|	 Other Header File Inclusion
|******************************************************************************/


#include "STD_PortIf.h"
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
|	 Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|	 Global Variable with extern linkage
|******************************************************************************/

/*******************************************************************************
|	 Global Function Prototypes
|******************************************************************************/

/******************************************************************************
* Function Name : void PortIf_Init( void )
* Description   : This function initializes the Port
* Argument      : none
* Return Value  : none
******************************************************************************/
void PortIf_Init(void)
{
    /* polyspace:begin<MISRA-C3:10.3:Not a defect:Justified> Normal. */
	(void)PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
}


/****************************************************************************************
 *��������  : void PortIf_SetPinMode(uint8 ChannelId, PortIf_MuxType e_e_Mux)

 *����      : Ƶ��Id��uint8 ChannelId,ģʽ���ͣ� PortIf_MuxType e_e_Mux

 *����ֵ    : void

 *����      : ��������ģʽ

 *�༭ʱ��  :
 ����
 *��ע      :
 *****************************************************************************************/
void PortIf_SetPinMode(uint8 ChannelId, PortIf_MuxType e_e_Mux)
{
	#if 0
	const uint8 TempPort = ChannelId>>5u;
	switch (TempPort)
	{
		case (uint8)0x00:
			PINS_DRV_SetMuxModeSel(PCTRLA, (uint32)ChannelId & (uint32)0x1fu, e_e_Mux);
			break;
		case (uint8)0x01:
			PINS_DRV_SetMuxModeSel(PCTRLB, (uint32)ChannelId & (uint32)0x1fu, e_e_Mux);
			break;
		case (uint8)0x02:
			PINS_DRV_SetMuxModeSel(PCTRLC, (uint32)ChannelId & (uint32)0x1fu, e_e_Mux);
			break;
		case (uint8)0x03:
			PINS_DRV_SetMuxModeSel(PCTRLD, (uint32)ChannelId & (uint32)0x1fu, e_e_Mux);
			break;
		case (uint8)0x04:
			PINS_DRV_SetMuxModeSel(PCTRLE, (uint32)ChannelId & (uint32)0x1fu, e_e_Mux);
			break;
		default:
			break;
	}
			#endif 
}


/****************************************************************************************
 *��������  : void PortIf_SetPinDirection(uint8 ChannelId,uint8 CtrDirection)

 *����      : Ƶ��Id��uint8 ChannelId,���� uint8 CtrDirection

 *����ֵ    : void

 *����      : �������ŷ���
 
 *�༭ʱ��  :
 ����
 *��ע      :
 *****************************************************************************************/
void PortIf_SetPinDirection(uint8 ChannelId,uint8 CtrDirection)
{
	#if 0
	const uint8 TempPort = ChannelId>>5u;
	switch (TempPort)
	{
		case (uint8)0x00:
			PINS_DRV_SetPinDirection(GPIOA, (uint32)ChannelId & (uint32)0x1fu, CtrDirection);
			break;
		case (uint8)0x01:
			PINS_DRV_SetPinDirection(GPIOB, (uint32)ChannelId & (uint32)0x1fu, CtrDirection);
			break;
		case (uint8)0x02:
			PINS_DRV_SetPinDirection(GPIOC, (uint32)ChannelId & (uint32)0x1fu, CtrDirection);
			break;
		case (uint8)0x03:
			PINS_DRV_SetPinDirection(GPIOD, (uint32)ChannelId & (uint32)0x1fu, CtrDirection);
			break;
		case (uint8)0x04:
			PINS_DRV_SetPinDirection(GPIOE, (uint32)ChannelId & (uint32)0x1fu, CtrDirection);
			break;
		default:
			break;
	}
			#endif 
}

/****************************************************************************************
 *��������  : PortIf_PinsChanType PortIf_GetPinsDirection(uint8 PortId)

 *����      : �˿�Id��uint8 PortId

 *����ֵ    : PortIf_PinsChanType

 *����      : ��ȡ���ŷ���
 
 *�༭ʱ��  :
 ����
 *��ע      :
 *****************************************************************************************/
PortIf_PinsChanType PortIf_GetPinsDirection(uint8 PortId)
{

	PortIf_PinsChanType LePort_dw_rt=0;
	//const uint8         TempPort = PortId;
	#if 0
	switch (TempPort)
	{
		case (uint8)0x00:
			LePort_dw_rt = PINS_DRV_GetPinsDirection(GPIOA);
			break;
		case (uint8)0x01:
			LePort_dw_rt = PINS_DRV_GetPinsDirection(GPIOB);
			break;
		case (uint8)0x02:
			LePort_dw_rt = PINS_DRV_GetPinsDirection(GPIOC);
			break;
		case (uint8)0x03:
			LePort_dw_rt = PINS_DRV_GetPinsDirection(GPIOD);
			break;
		case (uint8)0x04:
			LePort_dw_rt = PINS_DRV_GetPinsDirection(GPIOE);
			break;
		default:	LePort_dw_rt = 0u;
			break;
	}
	#endif 
	return LePort_dw_rt;

}

void PortIf_SetPinPull(uint8 ChannelId, port_pull_config_t pullConfig)
{
	#if 0
    const uint8 TempPort = ChannelId>>5u;
    switch (TempPort)
    {
        case (uint8)0x00:
            PINS_DRV_SetPullSel(PCTRLA,(uint32)ChannelId & (uint32)0x1fu,pullConfig);
            break;
        case (uint8)0x01:
           PINS_DRV_SetPullSel(PCTRLB,(uint32)ChannelId & (uint32)0x1fu,pullConfig);
            break;
        case (uint8)0x02:
            PINS_DRV_SetPullSel(PCTRLC,(uint32)ChannelId & (uint32)0x1fu,pullConfig);
            break;
        case (uint8)0x03:
            PINS_DRV_SetPullSel(PCTRLD,(uint32)ChannelId & (uint32)0x1fu,pullConfig);
           break;
        case (uint8)0x04:
            PINS_DRV_SetPullSel(PCTRLE,(uint32)ChannelId & (uint32)0x1fu,pullConfig);
            break;
        default:
            break;
	}
			#endif 
}
/*EOF*/
/* polyspace:end<MISRA-C3:10.3:Not a defect:Justified> Normal. */
/* polyspace:end<MISRA-C3:11.4:Not a defect:Justified> Normal */

