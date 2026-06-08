/*******************************************************************************
|  File Name:  STD_SrAdCtr_Cfg.h
|  Description:  Implementation of the Sensor Ctr Config Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           xiayajun               CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2018-06-21    01.00.00     XYJ       Creation
| 2019-12-27       /         XJW       Modified for AC-DI18
|******************************************************************************/
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justified> NO fluence */
/* polyspace:begin<MISRA-C3:5.6:Not a defect:Justified> NO fluence */
#if !defined (_STD_SRADCTR_CFG_H)
/* polyspace<MISRA-C3:21.1:Not a defect:Justified> NO fluence */
#define _STD_SRADCTR_CFG_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "SysTypes.h"
#include "STD_AdcM.h"
#include "STD_BtrM.h"
#include "STD_SrM.h"
#include "STD_SrCfg.h"


//#include "STD_SysM.h"       /*Get ECU sleep little mode*/
//#include "Icu.h"          Read Air Quality sensor output Period Time of pwm
/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define SRADCTR_CODE_RAM    

#define SRCTRCFG_AD_LINE_CLASS                      (SRCFG_DISABLE)
#define SRCTRCFG_ENABLE                 (SRCFG_ENABLE)  
#define SRCTRCFG_AD_TABLE_CLASS             (SRCFG_ENABLE)
#if( 1 )

/* Control MainFunction cycle */
#define  SRCTR_TASK10MS_PERIOD                      (10U)/*10ms*/

/* Diag MainFunction cycle */
#define SRDIAG_TASK50MS_PERIOD                      (10u)

/* DTC filter times */
#define SRDIAG_FILTER_CNT                           (uint16)( 1000u / SRDIAG_TASK50MS_PERIOD )

#define SRADCTR_GetCurrentAdValue                       ADCM_GetCurrentValue
#define SRADCTR_GetValidAdValue                         ADCM_GetValidValue
#define SRCTR_GetSysBatteryModeAStatus                  BTRCTR_GetLoadBatteryModeAStatus
#define SRCTR_GetRTCSleepStatus                         SYSM_GetRtcSleepStatus

#define SRCTRCFG_PULL_UP                (0u)
#define SRCTRCFG_PULL_DOWN              (1u)
#define SRCTRCFG_TABLE_TYPE_RES         (0u)
#define SRCTRCFG_TABLE_TYPE_VOLT        (1u)

/*NO.0***********************Temp TS1*********************************For Test*/
#if 1
#define SRCTRCFG_TEMP_DAT1_AD_PRECISION             (4096u)//(3520u)
#define SRCTRCFG_TEMP_DAT1_TABLE_TYPE               (SRCTRCFG_TABLE_TYPE_RES)
#define SRCTRCFG_TEMP_DAT1_PULL_STA                 (SRCTRCFG_PULL_UP)
#define SRCTRCFG_TEMP_DAT1_PULL_UP_RES              (10000u)
#define SRCTRCFG_TEMP_DAT1_AD_CH                    (ADCMCFG_TS1_AD_CH)      /*ADCM CH also ADCF CH*/
#define SRCTRCFG_TEMP_DAT1_OPEN_THRESHOLD           (3440u) /*450K*/
#define SRCTRCFG_TEMP_DAT1_SHORT_THRESHOLD          (65u)
#define SRCTRCFG_TEMP_DAT1_RT_SIZE                  (148u)
#define SRCTRCFG_TEMP_DAT1_RT_ADDRESS               (&KaSRCTR_dw_DatSensorRes_TS1[0u])
#define SRCTRCFG_TEMP_DAT1_RT2_ADDRESS              (NULL)
#define SRDIAG_TEMP_DAT1_DTC_BITMASK                (1u)                    /*dtc bit at KaSRM_dw_Uint32SetTable[]*/
#define SRDIAG_TEMP_DAT1_OPEN_THRESHOLD             (3440u)	/*450K*/
#define SRDIAG_TEMP_DAT1_SHORT_THRESHOLD            (65u)   /*200*/
#define SRDIAG_TEMP_DAT1_MIN_TEMPERATURE            (-400)
#define SRDIAG_TEMP_DAT1_MAX_TEMPERATURE            (1060)
#endif 
/*NO.1***********************Temp TS2*********************************For Test*/
#if 1
#define SRCTRCFG_TEMP_DAT2_AD_PRECISION             (4096u)//(3520u)
#define SRCTRCFG_TEMP_DAT2_TABLE_TYPE               (SRCTRCFG_TABLE_TYPE_RES)
#define SRCTRCFG_TEMP_DAT2_PULL_STA                 (SRCTRCFG_PULL_UP)
#define SRCTRCFG_TEMP_DAT2_PULL_UP_RES              (2000u)
#define SRCTRCFG_TEMP_DAT2_AD_CH                    (ADCMCFG_TS2_AD_CH)      /*ADCM CH also ADCF CH*/
#define SRCTRCFG_TEMP_DAT2_OPEN_THRESHOLD           (3440u) /*450K*/
#define SRCTRCFG_TEMP_DAT2_SHORT_THRESHOLD          (65u)
#define SRCTRCFG_TEMP_DAT2_RT_SIZE                  (148u)
#define SRCTRCFG_TEMP_DAT2_RT_ADDRESS               (&KaSRCTR_dw_DatSensorRes_TS2[0u])
#define SRCTRCFG_TEMP_DAT2_RT2_ADDRESS              (NULL)
#define SRDIAG_TEMP_DAT2_DTC_BITMASK                (1u)                    /*dtc bit at KaSRM_dw_Uint32SetTable[]*/
#define SRDIAG_TEMP_DAT2_OPEN_THRESHOLD             (3440u)	/*450K*/
#define SRDIAG_TEMP_DAT2_SHORT_THRESHOLD            (65u)   /*200*/
#define SRDIAG_TEMP_DAT2_MIN_TEMPERATURE            (-400)
#define SRDIAG_TEMP_DAT2_MAX_TEMPERATURE            (1060)
#endif 

/*NO.1***********************PCB TEMP*********************************For Test*/
#if 1
#define SRCTRCFG_TEMP_DAT3_AD_PRECISION             (4096u)//(3520u)
#define SRCTRCFG_TEMP_DAT3_TABLE_TYPE               (SRCTRCFG_TABLE_TYPE_RES)
#define SRCTRCFG_TEMP_DAT3_PULL_STA                 (SRCTRCFG_PULL_UP)
#define SRCTRCFG_TEMP_DAT3_PULL_UP_RES              (10000U)
#define SRCTRCFG_TEMP_DAT3_AD_CH                    (ADCMCFG_PCB_TEMP_AD_CH)      /*ADCM CH also ADCF CH*/
#define SRCTRCFG_TEMP_DAT3_OPEN_THRESHOLD           (3440u) /*450K*/
#define SRCTRCFG_TEMP_DAT3_SHORT_THRESHOLD          (65u)
#define SRCTRCFG_TEMP_DAT3_RT_SIZE                  (207u)
#define SRCTRCFG_TEMP_DAT3_RT_ADDRESS               (&KaSRCTR_dw_DatSensorRes_PCB_TEMP[0u])
#define SRCTRCFG_TEMP_DAT3_RT2_ADDRESS              (NULL)
#define SRDIAG_TEMP_DAT3_DTC_BITMASK                (1u)                    /*dtc bit at KaSRM_dw_Uint32SetTable[]*/
#define SRDIAG_TEMP_DAT3_OPEN_THRESHOLD             (3440u)	/*450K*/
#define SRDIAG_TEMP_DAT3_SHORT_THRESHOLD            (65u)   /*200*/
#define SRDIAG_TEMP_DAT3_MIN_TEMPERATURE            (-550)
#define SRDIAG_TEMP_DAT3_MAX_TEMPERATURE            (1500)
#endif 


/*NO.0***********************Temp Front Left Upper*********************************For Test*/
#if 0
#define SRCTRCFG_TEMP_DAT1_AD_PRECISION             (4096u)//(3520u)
#define SRCTRCFG_TEMP_DAT1_TABLE_TYPE               (SRCTRCFG_TABLE_TYPE_RES)
#define SRCTRCFG_TEMP_DAT1_PULL_STA                 (SRCTRCFG_PULL_UP)
#define SRCTRCFG_TEMP_DAT1_PULL_UP_RES              (10000u)
#define SRCTRCFG_TEMP_DAT1_AD_CH                    (ADCMCFG_TS1_AD_CH)      /*ADCM CH also ADCF CH*/
#define SRCTRCFG_TEMP_DAT1_OPEN_THRESHOLD           (3440u) /*450K*/
#define SRCTRCFG_TEMP_DAT1_SHORT_THRESHOLD          (65u)
#define SRCTRCFG_TEMP_DAT1_RT_SIZE                  (167u)
#define SRCTRCFG_TEMP_DAT1_RT_ADDRESS               (&KaSRCTR_dw_DatSensorRes[0u])
#define SRCTRCFG_TEMP_DAT1_RT2_ADDRESS              (NULL)
#define SRDIAG_TEMP_DAT1_DTC_BITMASK                (1u)                    /*dtc bit at KaSRM_dw_Uint32SetTable[]*/
#define SRDIAG_TEMP_DAT1_OPEN_THRESHOLD             (3440u)	/*450K*/
#define SRDIAG_TEMP_DAT1_SHORT_THRESHOLD            (65u)   /*200*/
#define SRDIAG_TEMP_DAT1_MIN_TEMPERATURE            (-400)
#define SRDIAG_TEMP_DAT1_MAX_TEMPERATURE            (1250)
#endif 
/*NO.1***********************Temp Front Left Below*********************************below unused*/
/*
#define SRCTRCFG_TEMP_DAT2_AD_PRECISION             (4096u)
#define SRCTRCFG_TEMP_DAT2_TABLE_TYPE               (SRCTRCFG_TABLE_TYPE_RES)
#define SRCTRCFG_TEMP_DAT2_PULL_STA                 (SRCTRCFG_PULL_UP)
#define SRCTRCFG_TEMP_DAT2_PULL_UP_RES              (10000u)
#define SRCTRCFG_TEMP_DAT2_AD_CH                    (ADCMCFG_TEMP_DAT2_CH)
#define SRCTRCFG_TEMP_DAT2_OPEN_THRESHOLD           (4012u)
#define SRCTRCFG_TEMP_DAT2_SHORT_THRESHOLD          (80u)
#define SRCTRCFG_TEMP_DAT2_RT_SIZE                  (127u)
#define SRCTRCFG_TEMP_DAT2_RT_ADDRESS               (&KaSRCTR_dw_DatSensorRes[0u])
#define SRCTRCFG_TEMP_DAT2_RT2_ADDRESS              (NULL)
#define SRDIAG_TEMP_DAT2_DTC_BITMASK                (2u)
#define SRDIAG_TEMP_DAT2_OPEN_THRESHOLD             (4012u)
#define SRDIAG_TEMP_DAT2_SHORT_THRESHOLD            (80u)
#define SRDIAG_TEMP_DAT2_MIN_TEMPERATURE            (-400)
#define SRDIAG_TEMP_DAT2_MAX_TEMPERATURE            (850)
*/
/*NO.2***********************Temp Front Right Upper*********************************/
#if 0
#define SRCTRCFG_TEMP_DAT3_AD_PRECISION             (4096u)
#define SRCTRCFG_TEMP_DAT3_TABLE_TYPE               (SRCTRCFG_TABLE_TYPE_RES)
#define SRCTRCFG_TEMP_DAT3_PULL_STA                 (SRCTRCFG_PULL_UP)
#define SRCTRCFG_TEMP_DAT3_PULL_UP_RES              (10000u)
#define SRCTRCFG_TEMP_DAT3_AD_CH                    (ADCMCFG_TEMP_DAT3_CH)
#define SRCTRCFG_TEMP_DAT3_OPEN_THRESHOLD           (4012u)
#define SRCTRCFG_TEMP_DAT3_SHORT_THRESHOLD          (80u)
#define SRCTRCFG_TEMP_DAT3_RT_SIZE                  (127u)
#define SRCTRCFG_TEMP_DAT3_RT_ADDRESS               (&KaSRCTR_dw_DatSensorRes[0u])
#define SRCTRCFG_TEMP_DAT3_RT2_ADDRESS              (NULL)
#define SRDIAG_TEMP_DAT3_DTC_BITMASK                (3u)
#define SRDIAG_TEMP_DAT3_OPEN_THRESHOLD             (4012u)
#define SRDIAG_TEMP_DAT3_SHORT_THRESHOLD            (80u)
#define SRDIAG_TEMP_DAT3_MIN_TEMPERATURE            (-400)
#define SRDIAG_TEMP_DAT3_MAX_TEMPERATURE            (850)
#endif 
/*NO.3***********************Temp Front Right Below*********************************/
#define SRCTRCFG_TEMP_DAT4_AD_PRECISION             (4096u)
#define SRCTRCFG_TEMP_DAT4_TABLE_TYPE               (SRCTRCFG_TABLE_TYPE_RES)
#define SRCTRCFG_TEMP_DAT4_PULL_STA                 (SRCTRCFG_PULL_UP)
#define SRCTRCFG_TEMP_DAT4_PULL_UP_RES              (10000u)
#define SRCTRCFG_TEMP_DAT4_AD_CH                    (ADCMCFG_TEMP_DAT4_CH)
#define SRCTRCFG_TEMP_DAT4_OPEN_THRESHOLD           (4012u)
#define SRCTRCFG_TEMP_DAT4_SHORT_THRESHOLD          (80u)
#define SRCTRCFG_TEMP_DAT4_RT_SIZE                  (127u)
#define SRCTRCFG_TEMP_DAT4_RT_ADDRESS               (&KaSRCTR_dw_DatSensorRes[0u])
#define SRCTRCFG_TEMP_DAT4_RT2_ADDRESS              (NULL)
#define SRDIAG_TEMP_DAT4_DTC_BITMASK                (4u)
#define SRDIAG_TEMP_DAT4_OPEN_THRESHOLD             (4012u)
#define SRDIAG_TEMP_DAT4_SHORT_THRESHOLD            (80u)
#define SRDIAG_TEMP_DAT4_MIN_TEMPERATURE            (-400)
#define SRDIAG_TEMP_DAT4_MAX_TEMPERATURE            (850)
/*NO.4***********************Temp Rear Middle Upper *********************************/
#define SRCTRCFG_TEMP_DAT5_AD_PRECISION             (4096u)
#define SRCTRCFG_TEMP_DAT5_TABLE_TYPE               (SRCTRCFG_TABLE_TYPE_RES)
#define SRCTRCFG_TEMP_DAT5_PULL_STA                 (SRCTRCFG_PULL_UP)
#define SRCTRCFG_TEMP_DAT5_PULL_UP_RES              (10000u)
#define SRCTRCFG_TEMP_DAT5_AD_CH                    (ADCMCFG_TEMP_DAT5_CH)
#define SRCTRCFG_TEMP_DAT5_OPEN_THRESHOLD           (4012u)
#define SRCTRCFG_TEMP_DAT5_SHORT_THRESHOLD          (80u)
#define SRCTRCFG_TEMP_DAT5_RT_SIZE                  (127u)
#define SRCTRCFG_TEMP_DAT5_RT_ADDRESS               (&KaSRCTR_dw_DatSensorRes[0u])
#define SRCTRCFG_TEMP_DAT5_RT2_ADDRESS              (NULL)
#define SRDIAG_TEMP_DAT5_DTC_BITMASK                (5u)
#define SRDIAG_TEMP_DAT5_OPEN_THRESHOLD             (4012u)
#define SRDIAG_TEMP_DAT5_SHORT_THRESHOLD            (80u)
#define SRDIAG_TEMP_DAT5_MIN_TEMPERATURE            (-400)
#define SRDIAG_TEMP_DAT5_MAX_TEMPERATURE            (850)
/*NO.5***********************Temp Rear Middle Below*********************************/
#define SRCTRCFG_TEMP_DAT6_AD_PRECISION             (4096u)
#define SRCTRCFG_TEMP_DAT6_TABLE_TYPE               (SRCTRCFG_TABLE_TYPE_RES)
#define SRCTRCFG_TEMP_DAT6_PULL_STA                 (SRCTRCFG_PULL_UP)
#define SRCTRCFG_TEMP_DAT6_PULL_UP_RES              (10000u)
#define SRCTRCFG_TEMP_DAT6_AD_CH                    (ADCMCFG_TEMP_DAT6_CH)
#define SRCTRCFG_TEMP_DAT6_OPEN_THRESHOLD           (4012u)
#define SRCTRCFG_TEMP_DAT6_SHORT_THRESHOLD          (80u)
#define SRCTRCFG_TEMP_DAT6_RT_SIZE                  (127u)
#define SRCTRCFG_TEMP_DAT6_RT_ADDRESS               (&KaSRCTR_dw_DatSensorRes[0u])
#define SRCTRCFG_TEMP_DAT6_RT2_ADDRESS              (NULL)
#define SRDIAG_TEMP_DAT6_DTC_BITMASK                (6u)
#define SRDIAG_TEMP_DAT6_OPEN_THRESHOLD             (4012u)
#define SRDIAG_TEMP_DAT6_SHORT_THRESHOLD            (80u)
#define SRDIAG_TEMP_DAT6_MIN_TEMPERATURE            (-400)
#define SRDIAG_TEMP_DAT6_MAX_TEMPERATURE            (850)

/*******************************************************************************
|    Enum Definition
|******************************************************************************/
typedef enum
{ /*������ͨ��:AD������� */
#if (SRCFG_TEMP_TS1_NTC_ENABLE == SRCFG_ENABLE)
  SRADCTR_TABLE_TEMP_TS1_NTC_CH,
#endif
#if (SRCFG_TEMP_TS2_NTC_ENABLE == SRCFG_ENABLE)
  SRADCTR_TABLE_TEMP_TS2_NTC_CH,
#endif
#if (SRCFG_TEMP_TFT_NTC_ENABLE == SRCFG_ENABLE)
  SRADCTR_TABLE_TEMP_TFT_NTC_CH,
#endif
	
#if (SRCFG_TEMP_PCB_NTC_ENABLE == SRCFG_ENABLE)
  SRADCTR_TABLE_TEMP_PCB_NTC_CH,
#endif

#if (SRCFG_TEMP_DAT2_ENABLE == SRCFG_ENABLE)
  SRADCTR_TABLE_TEMP_DAT2_CH,
#endif

#if (SRCFG_TEMP_DAT3_ENABLE == SRCFG_ENABLE)
  SRADCTR_TABLE_TEMP_DAT3_CH,
#endif

#if (SRCFG_TEMP_DAT4_ENABLE == SRCFG_ENABLE)
  SRADCTR_TABLE_TEMP_DAT4_CH,
#endif

#if (SRCFG_TEMP_DAT5_ENABLE == SRCFG_ENABLE)
  SRADCTR_TABLE_TEMP_DAT5_CH,
#endif

#if (SRCFG_TEMP_DAT6_ENABLE == SRCFG_ENABLE)
  SRADCTR_TABLE_TEMP_DAT6_CH,
#endif

#if (SRCFG_TEMP_HUMIDITY_ENABLE == SRCFG_ENABLE)
  SRADCTR_TABLE_TEMP_HUMIDITY_CH,
#endif

#if (SRCFG_TEMP_INCAR_ENABLE == SRCFG_ENABLE)
  SRADCTR_TABLE_TEMP_INCAR_CH,
#endif

#if (SRCFG_TEMP_AMB_ENABLE == SRCFG_ENABLE)
  SRADCTR_TABLE_TEMP_AMB_CH,
#endif
#if (SRCFG_TEMP_PCAT_ENABLE == SRCFG_ENABLE)
  SRADCTR_TABLE_TEMP_PCAT_CH,
#endif

#if (SRCFG_TEMP_WINDSCREEN_ENABLE == SRCFG_ENABLE)
  SRADCTR_TABLE_TEMP_WINDSCREEN_CH,
#endif

#if (SRCFG_TEMP_EVAP_ENABLE == SRCFG_ENABLE)
  SRADCTR_TABLE_TEMP_EVAP_CH,
#endif

#if (SRCFG_SOLAR_L_INDENSITY_WH_ENABLE == SRCFG_ENABLE)
  SRADCTR_SOLAR_L_INDENSITY_WH_CH,
#endif

#if (SRCFG_SOLAR_R_INDENSITY_WH_ENABLE == SRCFG_ENABLE)
  SRADCTR_SOLAR_R_INDENSITY_WH_CH,
#endif

  SRADCTR_TABLE_CH_MAX_NUM
} SRADCTR_Table_CH_Enum;

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef struct
{
    AdCfg_ChanEnumType ucHwAdChannel;
    uint16 usPrecision;
    uint8  usTableTypeVoltOrRes;
    uint8  usPullUpOrDnSta;
    uint16 usPullUpOrDnRes;
   /* const */uint32 *pulResTable;
    /*const*/ uint32 *pulResTable2;
    uint16 DtcBitMask;
    uint16 OpenThreshold;
    uint16 ShortThreshold;
    sint16 MinTempValue;
    sint16 MaxTempVlaue;

} SrCtrAdTableCfg_Struct;

typedef struct
{
    AdCfg_ChanEnumType ucHwAdChannel;
    uint16 usPrecision;
    uint8  usPullUpOrDnSta;
    uint16 usPullUpOrDnRes;
    uint16 usAdMin;
    uint16 usAdMax;
    uint16 usTagMax;
    uint16 DtcBitMask;
    uint16 OpenThreshold;
    uint16 ShortThreshold;
    /* polyspace<MISRA-C3:2.3:Not a defect:Justified> NO fluence */
} SrCtrAdLineCfg_Struct;
/*******************************************************************************
|    Table Definition
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/
extern SrCtrAdTableCfg_Struct stSrCtrAdTableCfg[SRADCTR_TABLE_CH_MAX_NUM];
#if (SRCFG_ENABLE == SRCTRCFG_AD_LINE_CLASS)
extern const SrCtrAdLineCfg_Struct stSrCtrAdLineCfg[SRADCTR_LINE_CH_MAX_NUM ];
#endif
#endif

#endif
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justified> NO fluence */
/* polyspace:end<MISRA-C3:5.6:Not a defect:Justified> NO fluence */
/*EOF*/
