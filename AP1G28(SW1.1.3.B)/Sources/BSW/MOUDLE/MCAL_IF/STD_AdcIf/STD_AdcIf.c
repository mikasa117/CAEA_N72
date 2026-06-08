//#include "adc_config.h"
//#include "adc_driver.h"
#include "interrupt_manager.h"
#include <STD_AdcIf.h>
#include "sdk_project_config.h"

void AdcIf_Init(void)
{
	CIM->CTRL |= CIM_CTRL_ADC1_TRIG_SEL(1);
	/* ADC 通道初始*/
    ADC_DRV_ConfigConverter(INST_ADCONV0, &adc_config0);
	ADC_DRV_ConfigConverter(INST_ADCONV1, &adc_config1);
}

void AdcIf_DeInit(void)
{
	/* ADC 去初始化*/
    ADC_DRV_Reset(INST_ADCONV0);
	ADC_DRV_Reset(INST_ADCONV1);
}
void AdcIf_0_Start(void)
{
	ADC_DRV_Start(INST_ADCONV0);
}
//void AdcIf_0_ConfigGropChannel(uint8 HwChannels)
void AdcIf_0_ConfigGropChannel(uint8 ucChaGroupIdx_t)
{
	// adc_config0.sequenceConfig.channels[0u] = (adc_inputchannel_t)HwChannels;
	if (ucChaGroupIdx_t == 0u)
	{
		/* ADC */
		ADC_DRV_ConfigConverter(INST_ADCONV0, &adc_config0);
		/* ADC */
		//INT_SYS_EnableIRQ(INST_ADCONV0_IRQ);
		/* ADC */
		ADC_DRV_Start(INST_ADCONV0);
	}
	else if (ucChaGroupIdx_t == 2u)
	{
		/* ADC */
		ADC_DRV_ConfigConverter(INST_ADCONV0, &adc_config2);
		/* ADC */
		//INT_SYS_EnableIRQ(INST_ADCONV0_IRQ);
		/* ADC */
		ADC_DRV_Start(INST_ADCONV0);
	}
	else
	{
	}
}
void AdcIf_1_ConfigGropChannel(void)
{
	/* ADC */
	ADC_DRV_ConfigConverter(INST_ADCONV1, &adc_config1);
	/* ADC */
	INT_SYS_EnableIRQ(INST_ADCONV1_IRQ);
	/* ADC */
    ADC_DRV_Start(INST_ADCONV1);
}
uint8 AdcIf_0_GetGropConvCompleteFlag(void)
{
    return ((uint8)ADC_DRV_GetEndOfSequenceFlag(INST_ADCONV0));
}
uint8 AdcIf_1_GetGropConvCompleteFlag(void)
{
    return ((uint8)ADC_DRV_GetEndOfSequenceFlag(INST_ADCONV1));
}

void AdcIf_0_GetGropChannelResult(uint16 * const pConvResult)
{
	/* */
	*(pConvResult) = ADC_DRV_ReadFIFO(INST_ADCONV0);
	//ADC_DRV_ClearEoseqFlagCmd(0);
}
void AdcIf_1_GetGropChannelResult(uint16 * const pConvResult)
{
	/* */
	*(pConvResult) = ADC_DRV_ReadFIFO(INST_ADCONV1);
}


