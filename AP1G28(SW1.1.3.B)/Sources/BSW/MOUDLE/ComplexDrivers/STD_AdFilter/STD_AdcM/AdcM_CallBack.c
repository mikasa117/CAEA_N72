/* polyspace<MISRA-C3:1.1:Not a defect:Other> No fluence */
/*******************************************************************************
|  File Name:  SwCpid_CallBack.c
|  Description:  Implementation of the Switch Config Management
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


/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_AdcM.h"
#include "STD_Lib.h"
//#include "STD_EcvdM.h"
#include "CAEA_Types.h"
#include <STD_AdcIf.h>
#include "adc_driver.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/
/*define ADC1 hardware Channels*/
#define ADCB_HW_USB_OTG2_CH                  0x00u

#define ADCB_HW_TFT_NTC_CH  				0x1
#define ADCB_HW_BATTERY_CH  			    0x15
#define ADCB_HW_IG_ON_CH  			    	0x0

/*ADC1*/
#define ADCB1_PA_BUS_I_AD_CH  				0x0
#define ADCB1_PA_W_I_AD_CH  			    0x1
#define ADCB1_PA_V_I_AD_CH  			    0x2
#define ADCB1_FAN_I_AD_CH  			    	0x3
/*ADC0*/
#define ADCB0_KL30_AD_CH  				    0x0
#define ADCB0_HALL_5V_AD_CH  				0x1
#define ADCB0_COMP_12V_AD_CH  				0x6
#define ADCB0_COMP_12V_IS_AD_CH  			0x7
#define ADCB0_FAN_12V_AD_CH  			    0x2
#define ADCB0_TS3_AD_CH  			        0x3
#define ADCB0_PCB_TEMP_AD_CH  			    0x4
#define ADCB0_VCC_46V_AD_CH  			    0x5
#define ADCB0_HW_12V_IS_AD_CH  			    0x0c
#define ADCB0_HW_12V_AD_CH  			    0x0d
#define ADCB0_HF_12V_AD_CH  			    0x8
#define ADCB0_HF_12V_IS_AD_CH  			    0x9
#define ADCB0_TS1_AD_CH  			        0x0a
#define ADCB0_TS2_AD_CH  			        0x0b



#define ADCB_HW_ADC0_NUM                    (ADCMCFG_CH_MAX_NUM - ADCMCFG_KL30_AD_CH)
#define ADCB_HW_ADC1_NUM                    ADCMCFG_KL30_AD_CH
#define ADCB_HW_ADC_NUM                     (ADCMCFG_CH_MAX_NUM)

#define ADCB_HW_LVDS_3V3_CH             0x03u
#define ADCB_HW_LVDS_1V2_CH             0x02u
#define ADCB_HW_OSD_3V3_CH              0x0Au
#define ADCB_HW_OSD_1V5_CH              0x0Bu

#define ADCB_HW_ADC2_NUM        0U
#define ADCB_VALID_ADC2_NUM     (ADCB_HW_ADC2_NUM)
#define ADCB_SAMPLE_ADC2_MAX_NUM            (ADCB_HW_ADC2_NUM)



/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef void (*pAdCB_Set5180DselType)(void);/*PRQA S 3448*/

typedef struct
{
    uint8 ucAdFilterCh;
    uint8 ucAdHwCh;
    uint16 *pDataAdd;
    pAdCB_Set5180DselType pSet5180Dsel;
} AdCBSampleAdc1Cfg_Struct;/*PRQA S 3448*/

typedef struct
{
    uint8 ucAdFilterCh;
    uint8 ucAdHwCh;
    uint16 *pDataAdd;
    /* polyspace<MISRA-C3:2.3:Not a defect:Justified> No fluence */
} AdCBSampleAdc2Cfg_Struct;


typedef struct
{
    uint8 ucLoopIdx;
    uint8 ucChanIdx;
    uint8 ucConvOk;
    uint8 ucEvdcCnt;
} AdCBSample_Struct;

/*******************************************************************************
|    Static local KAM variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/
static uint16 ADCM_CODE_RAM AdCBSampleAdValue[ADCB_HW_ADC0_NUM];
static uint16 ADCM_CODE_RAM AdCBSampleAdValue1[ADCB_HW_ADC1_NUM];

static uint8 ucChanGroupIdx;
static AdCBSample_Struct ADCM_CODE_RAM stAdCBSample;
static AdCBSample_Struct ADCM_CODE_RAM stAdCBSample2;

/*******************************************************************************
|    Table Const Definition
|******************************************************************************/

/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/
static void ADCB_Adc0Sampling(void);
static void ADCB_Adc1Sampling(void);

static const AdCBSampleAdc1Cfg_Struct AdCBSampleAdc1CfgArray[ADCB_HW_ADC_NUM] =
	{
		/*ADC1*/
		{(uint8)ADCMCFG_PA_BUS_I_AD_CH,     (uint8)ADCB1_PA_BUS_I_AD_CH,     &(AdCBSampleAdValue1[ADCMCFG_PA_BUS_I_AD_CH])},
		{(uint8)ADCMCFG_PA_W_I_AD_CH,       (uint8)ADCB1_PA_W_I_AD_CH,       &(AdCBSampleAdValue1[ADCMCFG_PA_W_I_AD_CH])},
		{(uint8)ADCMCFG_PA_V_I_AD_CH,       (uint8)ADCB1_PA_V_I_AD_CH,       &(AdCBSampleAdValue1[ADCMCFG_PA_V_I_AD_CH])},
		//{(uint8)ADCMCFG_FAN_I_AD_CH,        (uint8)ADCB1_FAN_I_AD_CH,        &(AdCBSampleAdValue1[3u])},
		/*ADC0*/
		{(uint8)ADCMCFG_KL30_AD_CH,         (uint8)ADCB0_KL30_AD_CH,         &(AdCBSampleAdValue[ADCMCFG_KL30_AD_CH-ADCMCFG_KL30_AD_CH])},
		{(uint8)ADCMCFG_HALL_5V_AD_CH,      (uint8)ADCB0_HALL_5V_AD_CH,      &(AdCBSampleAdValue[ADCMCFG_HALL_5V_AD_CH-ADCMCFG_KL30_AD_CH])},
		//{(uint8)ADCMCFG_COMP_12V_AD_CH,     (uint8)ADCB0_COMP_12V_AD_CH,     &(AdCBSampleAdValue[ADCMCFG_COMP_12V_AD_CH-ADCMCFG_KL30_AD_CH])},
		{(uint8)ADCMCFG_COMP_12V_IS_AD_CH,  (uint8)ADCB0_COMP_12V_IS_AD_CH,  &(AdCBSampleAdValue[ADCMCFG_COMP_12V_IS_AD_CH -ADCMCFG_KL30_AD_CH])},

		{(uint8)ADCMCFG_FAN_12V_AD_CH,      (uint8)ADCB0_FAN_12V_AD_CH,      &(AdCBSampleAdValue[ADCMCFG_FAN_12V_AD_CH-ADCMCFG_KL30_AD_CH])},
		{(uint8)ADCMCFG_TS3_AD_CH,          (uint8)ADCB0_TS3_AD_CH,          &(AdCBSampleAdValue[ADCMCFG_TS3_AD_CH-ADCMCFG_KL30_AD_CH])},
		{(uint8)ADCMCFG_PCB_TEMP_AD_CH,     (uint8)ADCB0_PCB_TEMP_AD_CH,     &(AdCBSampleAdValue[ADCMCFG_PCB_TEMP_AD_CH-ADCMCFG_KL30_AD_CH])},
		{(uint8)ADCMCFG_VCC_46V_AD_CH,      (uint8)ADCB0_VCC_46V_AD_CH,      &(AdCBSampleAdValue[ADCMCFG_VCC_46V_AD_CH-ADCMCFG_KL30_AD_CH])},

		{(uint8)ADCMCFG_HW_12V_IS_AD_CH,    (uint8)ADCB0_HW_12V_IS_AD_CH,    &(AdCBSampleAdValue[ADCMCFG_HW_12V_IS_AD_CH-ADCMCFG_KL30_AD_CH])},
		//{(uint8)ADCMCFG_HW_12V_AD_CH,       (uint8)ADCB0_HW_12V_AD_CH,       &(AdCBSampleAdValue[ADCMCFG_HW_12V_AD_CH-ADCMCFG_KL30_AD_CH])},
		//{(uint8)ADCMCFG_HF_12V_AD_CH,       (uint8)ADCB0_HF_12V_AD_CH,       &(AdCBSampleAdValue[ADCMCFG_HF_12V_AD_CH-ADCMCFG_KL30_AD_CH])},
		{(uint8)ADCMCFG_HF_12V_IS_AD_CH,    (uint8)ADCB0_HF_12V_IS_AD_CH,    &(AdCBSampleAdValue[ADCMCFG_HF_12V_IS_AD_CH-ADCMCFG_KL30_AD_CH])},
		{(uint8)ADCMCFG_TS1_AD_CH,          (uint8)ADCB0_TS1_AD_CH,          &(AdCBSampleAdValue[ADCMCFG_TS1_AD_CH-ADCMCFG_KL30_AD_CH])},
		{(uint8)ADCMCFG_TS2_AD_CH,          (uint8)ADCB0_TS2_AD_CH,          &(AdCBSampleAdValue[ADCMCFG_TS2_AD_CH-ADCMCFG_KL30_AD_CH])},

};
/*******************************************************************************
|    Function Source Code
|******************************************************************************/

void ADCB_InitMemory(void)
{
	LIB_SetMemory((uint8 *)(&stAdCBSample), (uint8)0u, (uint16)(sizeof(stAdCBSample) / sizeof(uint8)));	  /*PRQA S 0310*/
	LIB_SetMemory((uint8 *)(&stAdCBSample2), (uint8)0u, (uint16)(sizeof(stAdCBSample2) / sizeof(uint8))); /*PRQA S 0310*/
	ucChanGroupIdx = 0u;
	AdcIf_0_ConfigGropChannel(ucChanGroupIdx);
	AdcIf_1_ConfigGropChannel();
}

void ADCB0_SamplingCallBack(void)
{
	ADCB_Adc0Sampling();
}
void ADCB1_SamplingCallBack(void)
{
	ADCB_Adc1Sampling();
}
static void ADCB_Adc0Sampling(void)/*PRQA S 3006*/
{
	if (ADCB_HW_ADC_NUM > stAdCBSample.ucChanIdx)/* PRQA S 1251 */
	{
		stAdCBSample.ucConvOk = AdcIf_0_GetGropConvCompleteFlag();
		if ((uint8) TRUE == stAdCBSample.ucConvOk)
		{

			if (ucChanGroupIdx == 0u)
			{
				for (stAdCBSample.ucChanIdx = ADCB_HW_ADC1_NUM; stAdCBSample.ucChanIdx < (ADCB_HW_ADC1_NUM + 8u); stAdCBSample.ucChanIdx++)
				{
					AdcIf_0_GetGropChannelResult(AdCBSampleAdc1CfgArray[stAdCBSample.ucChanIdx].pDataAdd);
					ADCM_CallbackSampleValue(AdCBSampleAdc1CfgArray[stAdCBSample.ucChanIdx].ucAdFilterCh,
											 AdCBSampleAdc1CfgArray[stAdCBSample.ucChanIdx].pDataAdd[0u]);
				}
				ADC_DRV_ClearEoseqFlagCmd(0);
				ucChanGroupIdx = 2u;
				AdcIf_0_ConfigGropChannel(ucChanGroupIdx);
			}
			else if (ucChanGroupIdx == 2u)
			{

				for (stAdCBSample.ucChanIdx = (ADCB_HW_ADC1_NUM + 8u); stAdCBSample.ucChanIdx < ADCB_HW_ADC_NUM; stAdCBSample.ucChanIdx++)
				{
					AdcIf_0_GetGropChannelResult(AdCBSampleAdc1CfgArray[stAdCBSample.ucChanIdx].pDataAdd);
					ADCM_CallbackSampleValue(AdCBSampleAdc1CfgArray[stAdCBSample.ucChanIdx].ucAdFilterCh,
											 AdCBSampleAdc1CfgArray[stAdCBSample.ucChanIdx].pDataAdd[0u]);
				}
				if (stAdCBSample.ucChanIdx >= ADCB_HW_ADC_NUM)
				{
					stAdCBSample.ucChanIdx = ADCB_HW_ADC1_NUM;
				}
				ADC_DRV_ClearEoseqFlagCmd(0);
				ucChanGroupIdx = 0u;
				AdcIf_0_ConfigGropChannel(ucChanGroupIdx);
			}
			else
			{
				AdcIf_0_ConfigGropChannel(ucChanGroupIdx);
			}
		}
		else
		{
			AdcIf_0_ConfigGropChannel(ucChanGroupIdx);
		}
	}
	else
	{
	}

}
static void ADCB_Adc1Sampling(void) /*PRQA S 3006*/
{
#if 0
	stAdCBSample2.ucConvOk = AdcIf_1_GetGropConvCompleteFlag();
	if ((uint8)TRUE == stAdCBSample2.ucConvOk)
	{
		ADC_DRV_ClearEoseqFlagCmd(INST_ADCONV1);
		for (stAdCBSample2.ucChanIdx = 0; stAdCBSample2.ucChanIdx < ADCB_HW_ADC1_NUM; stAdCBSample2.ucChanIdx++)
		{
			AdcIf_1_GetGropChannelResult(AdCBSampleAdc1CfgArray[stAdCBSample2.ucChanIdx].pDataAdd);
			ADCM_CallbackSampleValue(AdCBSampleAdc1CfgArray[stAdCBSample2.ucChanIdx].ucAdFilterCh,
									 AdCBSampleAdc1CfgArray[stAdCBSample2.ucChanIdx].pDataAdd[0u]);
		}
		stAdCBSample2.ucChanIdx = 0;
		AdcIf_1_ConfigGropChannel();
	}
	else
	{
		AdcIf_1_ConfigGropChannel();
	}
#endif
}

/*EOF*/
