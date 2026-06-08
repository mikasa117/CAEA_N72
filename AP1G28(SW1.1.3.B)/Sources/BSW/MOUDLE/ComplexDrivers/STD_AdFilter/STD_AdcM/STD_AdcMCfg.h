/*******************************************************************************
|  File Name:  AdcMcfg.h
|  Description:  Implementation of the Adc Config Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           YaJun Xia          CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2016-10-18    01.00.00     XYJ       Creation
|
|******************************************************************************/
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Other> No fluence */
/* polyspace:begin<MISRA-C3:5.6:Not a defect:Other> No fluence */
#if !defined (_STD_ADCM_CFG_H)
/* polyspace<MISRA-C3:21.1:Not a defect:Other> No fluence */
#define _STD_ADCM_CFG_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
/* polyspace<MISRA-C3:1.1:Not a defect:Justified> Normal. */
#include "Typedef.h"


/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define ADCM_CODE_RAM   //__attribute__ ((section(".BSW_RAM_DATA")))

#define ADCMCFG_ENABLE                              (1u)
#define ADCMCFG_DISABLE                             (0u)

#ifndef NULL
#define NULL ((void*)0)
#endif

#define ADCMCFG_CALLBACK_EN     (ADCMCFG_ENABLE)

/*NO.0***********************TEMP DAT1*********************************/
#define ADCMCFG_BATTERY_ENABLE                ADCMCFG_ENABLE/*Front Left Upper */
#define ADCMCFG_BATTERY_COLLECT_NUM           (4u)
#define ADCMCFG_BATTERY_S_OFFSET              (0u)


#define ADCMCFG_TFT_ENABLE                   ADCMCFG_ENABLE
#define ADCMCFG_TFT_COLLECT_NUM               (4u)
#define ADCMCFG_TFT_S_OFFSET                  (1u)

#define ADCMCFG_TFT1_ENABLE                   ADCMCFG_DISABLE
#define ADCMCFG_TFT1_COLLECT_NUM               (4u)
#define ADCMCFG_TFT1_S_OFFSET                  (2u)

#define ADCMCFG_IGON_ENABLE                   ADCMCFG_ENABLE
#define ADCMCFG_IGON_COLLECT_NUM               (4u)
#define ADCMCFG_IGON_S_OFFSET                  (3u)

/*adc1*/
#define ADCMCFG_PA_BUS_I_ENABLE                ADCMCFG_ENABLE/*Front Left Upper */
#define ADCMCFG_PA_BUS_I_COLLECT_NUM           (4u)
#define ADCMCFG_PA_BUS_I_S_OFFSET              (0u)

#define ADCMCFG_PA_W_I_ENABLE                  ADCMCFG_ENABLE
#define ADCMCFG_PA_W_I_COLLECT_NUM             (4u)
#define ADCMCFG_PA_W_I_S_OFFSET                (1u)

#define ADCMCFG_PA_V_I_ENABLE                  ADCMCFG_ENABLE
#define ADCMCFG_PA_V_I_COLLECT_NUM             (4u)
#define ADCMCFG_PA_V_I_S_OFFSET                (2u)

#define ADCMCFG_FAN_I_ENABLE                   ADCMCFG_DISABLE
#define ADCMCFG_FAN_I_COLLECT_NUM              (4u)
#define ADCMCFG_FAN_I_S_OFFSET                 (3u)

/*adc0*/

#define ADCMCFG_KL30_ENABLE                    ADCMCFG_ENABLE
#define ADCMCFG_KL30_COLLECT_NUM               (4u)
#define ADCMCFG_KL30_S_OFFSET                  (1u)

#define ADCMCFG_HALL_5V_ENABLE                 ADCMCFG_ENABLE
#define ADCMCFG_HALL_5V_COLLECT_NUM            (4u)
#define ADCMCFG_HALL_5V_S_OFFSET               (0u)

#define ADCMCFG_COMP_12V_ENABLE                 ADCMCFG_DISABLE
#define ADCMCFG_COMP_12V_COLLECT_NUM            (4u)
#define ADCMCFG_COMP_12V_S_OFFSET               (0u)

#define ADCMCFG_COMP_12V_IS_ENABLE              ADCMCFG_ENABLE
#define ADCMCFG_COMP_12V_IS_COLLECT_NUM         (4u)
#define ADCMCFG_COMP_12V_IS_S_OFFSET            (0u)
   
#define ADCMCFG_FAN_12V_ENABLE                  ADCMCFG_ENABLE
#define ADCMCFG_FAN_12V_COLLECT_NUM            (4u)
#define ADCMCFG_FAN_12V_S_OFFSET               (0u)

#define ADCMCFG_TS3_ENABLE                     ADCMCFG_ENABLE
#define ADCMCFG_TS3_COLLECT_NUM                (4u)
#define ADCMCFG_TS3_S_OFFSET                   (0u)

#define ADCMCFG_PCB_TEMP_ENABLE                ADCMCFG_ENABLE
#define ADCMCFG_PCB_TEMP_COLLECT_NUM           (4u)
#define ADCMCFG_PCB_TEMP_S_OFFSET              (0u)

#define ADCMCFG_VCC_48V_ENABLE                 ADCMCFG_ENABLE
#define ADCMCFG_VCC_48V_COLLECT_NUM            (4u)
#define ADCMCFG_VCC_48V_S_OFFSET               (0u)

#define ADCMCFG_HW_12V_IS_ENABLE                ADCMCFG_ENABLE
#define ADCMCFG_HW_12V_IS_COLLECT_NUM           (4u)
#define ADCMCFG_HW_12V_IS_S_OFFSET              (0u)

#define ADCMCFG_HW_12V_ENABLE                   ADCMCFG_DISABLE
#define ADCMCFG_HW_12V_COLLECT_NUM             (4u)
#define ADCMCFG_HW_12V_S_OFFSET                (0u)

#define ADCMCFG_HF_12V_ENABLE                  ADCMCFG_DISABLE
#define ADCMCFG_HF_12V_COLLECT_NUM             (4u)
#define ADCMCFG_HF_12V_S_OFFSET                (0u)

#define ADCMCFG_HF_12V_IS_ENABLE               ADCMCFG_ENABLE
#define ADCMCFG_HF_12V_IS_COLLECT_NUM          (4u)
#define ADCMCFG_HF_12V_IS_S_OFFSET             (0u)

#define ADCMCFG_TS1_ENABLE                     ADCMCFG_ENABLE
#define ADCMCFG_TS1_COLLECT_NUM                (4u)
#define ADCMCFG_TS1_S_OFFSET                   (0u)

#define ADCMCFG_TS2_ENABLE                     ADCMCFG_ENABLE
#define ADCMCFG_TS2_COLLECT_NUM                (4u)
#define ADCMCFG_TS2_S_OFFSET                   (0u)

/*******************************************************************************
|    Enum Definition
|******************************************************************************/
/*
EN					153.9*x
BATTERY				233.1*x
DCDC				620.5*x
LCM��OSD��LVDS		1087*x
*/
#if 0
typedef enum
{
#if (ADCMCFG_BATTERY_ENABLE == ADCMCFG_ENABLE)
    ADCMCFG_BATTERY_CH,
#endif
#if (ADCMCFG_TFT_ENABLE == ADCMCFG_ENABLE)
    ADCMCFG_TFT_NTC_CH,
#endif
#if (ADCMCFG_TFT1_ENABLE == ADCMCFG_ENABLE)
    ADCMCFG_TFT1_NTC_CH,
#endif
#if (ADCMCFG_IGON_ENABLE == ADCMCFG_ENABLE)
    ADCMCFG_IGON_CH,
#endif
    ADCMCFG_CH_MAX_NUM
        /* polyspace<MISRA-C3:2.3:Not a defect:Justified> No fluence */
} AdCfg_ChanEnumType;
 #endif
typedef enum
{
    /*ADC1*/
    ADCMCFG_PA_BUS_I_AD_CH = 0u,
    ADCMCFG_PA_W_I_AD_CH,
    ADCMCFG_PA_V_I_AD_CH,
    //ADCMCFG_FAN_I_AD_CH,
    /*ADC0*/
    ADCMCFG_KL30_AD_CH,
    ADCMCFG_HALL_5V_AD_CH,
    //ADCMCFG_COMP_12V_AD_CH,
    ADCMCFG_COMP_12V_IS_AD_CH,
    ADCMCFG_FAN_12V_AD_CH,
    ADCMCFG_TS3_AD_CH,
    ADCMCFG_PCB_TEMP_AD_CH,
    ADCMCFG_VCC_46V_AD_CH,
    ADCMCFG_HW_12V_IS_AD_CH,
    //ADCMCFG_HW_12V_AD_CH,
    //ADCMCFG_HF_12V_AD_CH,
    ADCMCFG_HF_12V_IS_AD_CH,
    ADCMCFG_TS1_AD_CH,
    ADCMCFG_TS2_AD_CH,

    ADCMCFG_CH_MAX_NUM
    /* polyspace<MISRA-C3:2.3:Not a defect:Justified> No fluence */
} AdCfg_ChanEnumType;
/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef void (*pFunFilterProcessType)(uint8 ucChannel, uint16 ucinsertValue);
/* ENvRam block descriptor type */
typedef struct
{
    uint8 e_u_CollectNum;
    uint8 e_u_StartOffset;
    pFunFilterProcessType   e_p_FunFilterProcess;
} TsADCF_h_CfgType;
/*******************************************************************************
|    Table Definition
|******************************************************************************/


extern const TsADCF_h_CfgType stAdcM_CfgTable[ADCMCFG_CH_MAX_NUM];


/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/

#endif
/* polyspace:end<MISRA-C3:2.5:Not a defect:Other> No fluence */
/* polyspace:end<MISRA-C3:5.6:Not a defect:Other> No fluence */
/*EOF*/
