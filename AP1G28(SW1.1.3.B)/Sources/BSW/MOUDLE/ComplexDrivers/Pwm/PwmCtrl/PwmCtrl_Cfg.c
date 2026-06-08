/*******************************************************************************
|  File Name:  PwmCtrl_Cfg.c
|  Description:  Implementation of the PwmCtrl Config Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
|               wcj                    CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 2025-11-09    1.0.0        wcj        Create 
| 
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "PwmCtrl_Cfg.h"
#include "etmr_common.h"

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
|    Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Global Variable with extern linkage
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/

/******************************************************************************
|    Static Function Prototypes
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/

void PwmCtrl_Cfg_SetDutyCycle(PWMCTRL_INTERFACE_Type pwmctrl_interface_type_s, uint32 dutyCycle)
{
    PWMCTRL_INTERFACE_Type pwmctrl_interface_type_t = pwmctrl_interface_type_s;
    uint32 instance = 0u;
    uint8 channel = 0u;
    uint32 dutyCycle_temp;
    if (dutyCycle == 1000)
    {
        dutyCycle_temp = 0x8000u;
    }
    else
    {
        dutyCycle_temp = (uint32)(0x8000u * dutyCycle / 1000u);
    }
    if (pwmctrl_interface_type_t < PWMCTRL_ALL)
    {
        switch (pwmctrl_interface_type_t)
        {
        case PWMCTRL_PD_HW:
            instance = ETMR_INST_0;
            channel = 0u;
            if (dutyCycle_temp == 0x8000u)
            {
                EtmrIf_UpdatePwmChannel_100(instance, channel);
            }
            else
            {
                EtmrIf_UpdatePwmChannel(instance, channel, dutyCycle_temp);
            }

            break;
        case PWMCTRL_PD_HV:
            instance = ETMR_INST_0;
            channel = 2u;
            if (dutyCycle_temp == 0x8000u)
            {
                EtmrIf_UpdatePwmChannel_100(instance, channel);
            }
            else
            {
                EtmrIf_UpdatePwmChannel(instance, channel, dutyCycle_temp);
            }
            break;
        case PWMCTRL_PD_HU:
            instance = ETMR_INST_0;
            channel = 4u;
            if (dutyCycle_temp == 0x8000u)
            {
                EtmrIf_UpdatePwmChannel_100(instance, channel);
            }
            else
            {
                EtmrIf_UpdatePwmChannel(instance, channel, dutyCycle_temp);
            }
            break;
        case PWMCTRL_HF_12V:
            instance = ETMR_INST_2;
            channel = 1u;
            if (dutyCycle_temp == 0x8000u)
            {
                EtmrIf_DRV_ClearLdok(ETMR_INST_2);
                EtmrIf_UpdatePwmChannel_100(instance, channel);
                EtmrIf_DRV_SetLdok(ETMR_INST_2);
            }
            else
            {
                EtmrIf_DRV_ClearLdok(ETMR_INST_2);
                EtmrIf_UpdatePwmChannel(instance, channel, dutyCycle_temp);
                EtmrIf_DRV_SetLdok(ETMR_INST_2);
            }
            break;
        case PWMCTRL_HW_12V:
            instance = ETMR_INST_2;
            channel = 2u;
            if (dutyCycle_temp == 0x8000u)
            {
                EtmrIf_DRV_ClearLdok(ETMR_INST_2);
                EtmrIf_UpdatePwmChannel_100(instance, channel);
                EtmrIf_DRV_SetLdok(ETMR_INST_2);
            }
            else
            {
                EtmrIf_DRV_ClearLdok(ETMR_INST_2);
                EtmrIf_UpdatePwmChannel(instance, channel, dutyCycle_temp);
                EtmrIf_DRV_SetLdok(ETMR_INST_2);
            }
            break;
        case PWMCTRL_FAN_12V:
            instance = ETMR_INST_2;
            channel = 3u;
            if (dutyCycle_temp == 0x8000u)
            {
                EtmrIf_DRV_ClearLdok(ETMR_INST_2);
                EtmrIf_UpdatePwmChannel_100(instance, channel);
                EtmrIf_DRV_SetLdok(ETMR_INST_2);
            }
            else
            {
                EtmrIf_DRV_ClearLdok(ETMR_INST_2);
                EtmrIf_UpdatePwmChannel(instance, channel, dutyCycle_temp);
                EtmrIf_DRV_SetLdok(ETMR_INST_2);
            }
            break;
        case PWMCTRL_MCU_ALED:
            instance = ETMR_INST_3;
            channel = 0u;
            if (dutyCycle_temp == 0x8000u)
            {
                EtmrIf_DRV_ClearLdok(ETMR_INST_3);
                EtmrIf_UpdatePwmChannel_100(instance, channel);
                EtmrIf_DRV_SetLdok(ETMR_INST_3);
            }
            else
            {
                EtmrIf_DRV_ClearLdok(ETMR_INST_3);
                EtmrIf_UpdatePwmChannel(instance, channel, dutyCycle_temp);
                EtmrIf_DRV_SetLdok(ETMR_INST_3);
            }
            break;
        case PWMCTRL_MCU_WLED:
            instance = ETMR_INST_3;
            channel = 1u;
            if (dutyCycle_temp == 0x8000u)
            {
                EtmrIf_DRV_ClearLdok(ETMR_INST_3);
                EtmrIf_UpdatePwmChannel_100(instance, channel);
                EtmrIf_DRV_SetLdok(ETMR_INST_3);
            }
            else
            {
                EtmrIf_DRV_ClearLdok(ETMR_INST_3);
                EtmrIf_UpdatePwmChannel(instance, channel, dutyCycle_temp);
                EtmrIf_DRV_SetLdok(ETMR_INST_3);
            }
            break;
        case PWMCTRL_MCU_UVCLED:
            instance = ETMR_INST_3;
            channel = 2u;
            if (dutyCycle_temp == 0x8000u)
            {
                EtmrIf_DRV_ClearLdok(ETMR_INST_3);
                EtmrIf_UpdatePwmChannel_100(instance, channel);
                EtmrIf_DRV_SetLdok(ETMR_INST_3);
            }
            else
            {
                EtmrIf_DRV_ClearLdok(ETMR_INST_3);
                EtmrIf_UpdatePwmChannel(instance, channel, dutyCycle_temp);
                EtmrIf_DRV_SetLdok(ETMR_INST_3);
            }
            break;
        default:
            break;
        }
    }
    else
    {
    }
}
