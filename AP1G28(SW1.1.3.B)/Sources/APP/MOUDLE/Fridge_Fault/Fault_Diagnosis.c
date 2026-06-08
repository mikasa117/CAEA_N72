/*******************************************************************************
||  File Name: Fault_Diagnosis.c
||  Description: Implementation of the AUTOSAR Fridge Fault
||-------------------------------------------------------------------------------
||  (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
||     All rights are reserved by CAEA.
||-------------------------------------------------------------------------------
|| Initials      Name                   Company
|| --------      ---------------------  -----------------------------------------
|| 	                               CAEA
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
#include "Fault_Diagnosis.h"
#include "Fridge_Basic_Control.h"
#include "HwIO.h"
#include "Fridge_Application_Config.h"
#include  "STD_AdcM.h"
#include  "STD_AdcMCfg.h"
#include "STD_BtrCtr.h"
#include "Mcal_App.h"
#include "LED_DriverM.h"
#include "HallM.h"
#include "AMP_AdCtr.h"
/*******************************************************************************
||    Macro Definition
||******************************************************************************/
/* Fault detect run in 5ms task */
/* 压缩机供电电压欠压故障 */
#define THR_FLT_COMP_UV                  (500/5)    /* COMP under voltage */
#define THR_FLT_COMP_UV_R                (500/5)    /* COMP under voltage */
#define THR_FLT_COMP_UV_RC               0          /* COMP under voltage */
#define THR_FLT_COMP_UV_RTC              0          /* COMP under voltage */

#define FridgeFault_COMP_UV              8500          /* COMP under voltage, 8.5V */
#define FridgeFault_COMP_UV_REC          9000          /* COMP under voltage, 9.0V */

/* 压缩机供电电压过压故障 */
#define THR_FLT_COMP_OV                  (500/5)    /* COMP under voltage */
#define THR_FLT_COMP_OV_R                (500/5)    /* COMP under voltage */
#define THR_FLT_COMP_OV_RC               0          /* COMP under voltage */
#define THR_FLT_COMP_OV_RTC              0          /* COMP under voltage */

#define FridgeFault_COMP_OV              16500          /* COMP under voltage, 16.5V */
#define FridgeFault_COMP_OV_REC          16000          /* COMP under voltage, 16.0V */

/* 压缩机过流故障 */
#define THR_FLT_COMP_OC                  (30000/5)  /* COMP over current */
#define THR_FLT_COMP_OC_R                (30000/5)  /* COMP over current */
#define THR_FLT_COMP_OC_RC               0          /* COMP over current */
#define THR_FLT_COMP_OC_RTC              0          /* COMP over current */

#define FridgeFault_COMP_OP              90000          /* COMP over power, 90W */
#define FridgeFault_COMP_OP_REC          85000          /* COMP over power, 85W */

/* 压缩机过热故障 */
#define THR_FLT_COMP_OT                  (3000/5)   /* COMP over temperature */
#define THR_FLT_COMP_OT_R                (3000/5)   /* COMP over temperature */
#define THR_FLT_COMP_OT_RC               0          /* COMP over temperature */
#define THR_FLT_COMP_OT_RTC              0          /* COMP over temperature */

#define FridgeFault_COMP_OT              130         /* COMP over temperature, 90+40�� */
#define FridgeFault_COMP_OT_REC          125         /* COMP over temperature, 85+40�� */

/* 压缩机相电流过流故障，内部故障 */
#define THR_FLT_COMP_OC_PHASE            (0/5)   	/* COMP over phase current */
#define THR_FLT_COMP_OC_PHASE_R          (0/5)   	/* COMP over phase current */
#define THR_FLT_COMP_OC_PHASE_RC         0          /* COMP over phase current */
#define THR_FLT_COMP_OC_PHASE_RTC        0          /* COMP over phase current */

#define FridgeFault_COMP_OC_PHASE        21.21        /* COMP over phase current,15.0A*1.414 */
#define FridgeFault_COMP_OC_PHASE_Cnt    480          /* COMP over phase current,30ms/62.5us */

/* 压缩机相电流缺相故障，内部故障 */
#define THR_FLT_COMP_LC_PHASE            (0/5)   	/* COMP lack phase current */
#define THR_FLT_COMP_LC_PHASE_R          (0/5)   	/* COMP lack phase current */
#define THR_FLT_COMP_LC_PHASE_RC         0          /* COMP lack phase current */
#define THR_FLT_COMP_LC_PHASE_RTC        0          /* COMP lack phase current */

#define FridgeFault_COMP_LC_PHASE        0.282        /* COMP lack phase current,0.2A*1.414 */
#define FridgeFault_COMP_LC_PHASE_Cnt    32000        /* COMP lack phase current,2s/62.5us */

/* 压缩机超速故障，内部故障 */
#define THR_FLT_COMP_OS                  (0/5)   	/* COMP over speed */
#define THR_FLT_COMP_OS_R                (0/5)   	/* COMP over speed */
#define THR_FLT_COMP_OS_RC               0          /* COMP over speed */
#define THR_FLT_COMP_OS_RTC              0          /* COMP over speed */

#define FridgeFault_COMP_OS        		 4000        /* COMP over speed,4000rpm */
#define FridgeFault_COMP_OS_Cnt    		 2000        /* COMP over speed,2s/1ms */

/* 压缩机低速故障，内部故障 */
#define THR_FLT_COMP_US                  (0/5)   	/* COMP under speed */
#define THR_FLT_COMP_US_R                (0/5)   	/* COMP under speed */
#define THR_FLT_COMP_US_RC               0          /* COMP under speed */
#define THR_FLT_COMP_US_RTC              0          /* COMP under speed */

#define FridgeFault_COMP_US        		 1500        /* COMP under speed,1500rpm */
#define FridgeFault_COMP_US_Cnt    		 2000        /* COMP under speed,2s/1ms */

/* 压缩机堵转故障，内部故障 */
#define THR_FLT_COMP_STALL               (0/5)   	/* COMP stall */
#define THR_FLT_COMP_STALL_R             (0/5)   	/* COMP stall */
#define THR_FLT_COMP_STALL_RC            0          /* COMP stall */
#define THR_FLT_COMP_STALL_RTC           0          /* COMP stall */

#define FridgeFault_COMP_Stall_Current   16.97        /* COMP stall,12.0A*1.414 */
#define FridgeFault_COMP_Stall_Speed  	 500          /* COMP stall,500rpm */
#define FridgeFault_COMP_Stall_Cnt   	 25           /* COMP stall,5s/200ms */

/* 压缩机启动失败故障 */
#define THR_FLT_COMP_STARTF              (0/5)   	/* COMP start up fail */
#define THR_FLT_COMP_STARTF_R            (0/5)   	/* COMP start up fail */
#define THR_FLT_COMP_STARTF_RC           0          /* COMP start up fail */
#define THR_FLT_COMP_STARTF_RTC          0          /* COMP start up fail */

// #define FridgeFault_COMP_OT              120         /* COMP over temperature, 80+40�� */
// #define FridgeFault_COMP_OT_REC          110         /* COMP over temperature, 70+40�� */

/* 风扇过流故障 */
#define THR_FLT_FAN_OC                    (30/5)    /* FAN over current */
#define THR_FLT_FAN_OC_R                  (30/5)    /* FAN over current */
#define THR_FLT_FAN_OC_RC                 0          /* FAN over current */
#define THR_FLT_FAN_OC_RTC                0          /* FAN over current */

#define FridgeFault_FAN_OC                1000        /* FAN over current, 1000mA */

/* 风扇欠流故障 */
#define THR_FLT_FAN_UC                    (3000/5)    /* FAN over current */
#define THR_FLT_FAN_UC_R                  (3000/5)    /* FAN over current */
#define THR_FLT_FAN_UC_RC                 0          /* FAN over current */
#define THR_FLT_FAN_UC_RTC                0          /* FAN over current */

#define FridgeFault_FAN_UC                10        /* FAN over current, 10mA */

/* 加热膜过流故障 */
#define THR_FLT_FILM_OC                   (30/5)    /* FILM short circuit */
#define THR_FLT_FILM_OC_R                 (30/5)    /* FILM short circuit */
#define THR_FLT_FILM_OC_RC                0          /* FILM short circuit */
#define THR_FLT_FILM_OC_RTC               0          /* FILM short circuit */

#define FridgeFault_FILM_OC               10000          /* FILM short circuit, 10A */

/* 加热膜欠流故障 */
#define THR_FLT_FILM_UC                   (30/5)    /* FILM short circuit */
#define THR_FLT_FILM_UC_R                 (30/5)    /* FILM short circuit */
#define THR_FLT_FILM_UC_RC                0          /* FILM short circuit */
#define THR_FLT_FILM_UC_RTC               0          /* FILM short circuit */

#define FridgeFault_FILM_UC               100          /* FILM short circuit, 0.1A */

/* 加热丝过流故障 */
#define THR_FLT_STRIP_OC                  (30/5)    /* STRIP short circuit */
#define THR_FLT_STRIP_OC_R                (30/5)    /* STRIP short circuit */
#define THR_FLT_STRIP_OC_RC               0          /* STRIP short circuit */
#define THR_FLT_STRIP_OC_RTC              0          /* STRIP short circuit */

#define FridgeFault_STRIP_OC              2000          /* STRIP short circuit, 2A */

/* 加热丝欠流故障 */
#define THR_FLT_STRIP_UC                  (30/5)    /* STRIP short circuit */
#define THR_FLT_STRIP_UC_R                (30/5)    /* STRIP short circuit */
#define THR_FLT_STRIP_UC_RC               0          /* STRIP short circuit */
#define THR_FLT_STRIP_UC_RTC              0          /* STRIP short circuit */

#define FridgeFault_STRIP_UC              10          /* STRIP short circuit, 0.01A */

/* 内胆处感温探头故障 */
#define THR_FLT_LINER_TS                 (5000/5)   /* LINER temperature sensor fault */
#define THR_FLT_LINER_TS_R               (5000/5)   /* LINER temperature sensor fault */
#define THR_FLT_LINER_TS_RC              0          /* LINER temperature sensor fault */
#define THR_FLT_LINER_TS_RTC             0          /* LINER temperature sensor fault */

#define FridgeFault_LINER_TS_OPEN           120          /* LINER temperature sensor fault, 80+40�� */
#define FridgeFault_LINER_TS_OPEN_REC       118          /* LINER temperature sensor fault, 78+40�� */
#define FridgeFault_LINER_TS_SC             5            /* LINER temperature sensor fault, -35+40�� */
#define FridgeFault_LINER_TS_SC_REC         7            /* LINER temperature sensor fault, -33+40�� */

/* 冷凝器感温探头故障 */
#define THR_FLT_CONDENSER_TS                 (5000/5)   /* LINER temperature sensor fault */
#define THR_FLT_CONDENSER_TS_R               (5000/5)   /* LINER temperature sensor fault */
#define THR_FLT_CONDENSER_TS_RC              0          /* LINER temperature sensor fault */
#define THR_FLT_CONDENSER_TS_RTC             0          /* LINER temperature sensor fault */

#define FridgeFault_CONDENSER_TS_OPEN           140          /* LINER temperature sensor fault, 100+40�� */
#define FridgeFault_CONDENSER_TS_OPEN_REC       138          /* LINER temperature sensor fault, 98+40�� */
#define FridgeFault_CONDENSER_TS_SC             5            /* LINER temperature sensor fault, -35+40�� */
#define FridgeFault_CONDENSER_TS_SC_REC         7            /* LINER temperature sensor fault, -33+40�� */

/* 制冷照明灯过流故障 */
#define THR_FLT_WLED_OC                 (2000/5)   	/* LED fault */
#define THR_FLT_WLED_OC_R               (2000/5)   	/* LED fault */
#define THR_FLT_WLED_OC_RC              0          	/* LED fault */
#define THR_FLT_WLED_OC_RTC             0          	/* LED fault */

/* 制冷照明灯欠流故障 */
#define THR_FLT_WLED_UC                 (2000/5)   	/* LED fault */
#define THR_FLT_WLED_UC_R               (2000/5)   	/* LED fault */
#define THR_FLT_WLED_UC_RC              0          	/* LED fault */
#define THR_FLT_WLED_UC_RTC             0          	/* LED fault */

/* 制热照明灯过流故障 */
#define THR_FLT_ALED_OC                 (2000/5)   	/* LED fault */
#define THR_FLT_ALED_OC_R               (2000/5)   	/* LED fault */
#define THR_FLT_ALED_OC_RC              0          	/* LED fault */
#define THR_FLT_ALED_OC_RTC             0          	/* LED fault */

/* 制热照明灯欠流故障 */
#define THR_FLT_ALED_UC                 (2000/5)   	/* LED fault */
#define THR_FLT_ALED_UC_R               (2000/5)   	/* LED fault */
#define THR_FLT_ALED_UC_RC              0          	/* LED fault */
#define THR_FLT_ALED_UC_RTC             0          	/* LED fault */

/* 杀菌灯过流故障 */
#define THR_FLT_UVLED_OC                 (2000/5)   /* LED fault */
#define THR_FLT_UVLED_OC_R               (2000/5)   /* LED fault */
#define THR_FLT_UVLED_OC_RC              0         	/* LED fault */
#define THR_FLT_UVLED_OC_RTC             0          /* LED fault */

/* 杀菌灯欠流故障 */
#define THR_FLT_UVLED_UC                 (2000/5)  	/* LED fault */
#define THR_FLT_UVLED_UC_R               (2000/5)   /* LED fault */
#define THR_FLT_UVLED_UC_RC              0          /* LED fault */
#define THR_FLT_UVLED_UC_RTC             0          /* LED fault */

/* 霍尔传感器供电电压欠压故障 */
#define THR_FLT_HALL_UVOL                 (5000/5)   		/* Hall fault */
#define THR_FLT_HALL_UVOL_R               (5000/5)   		/* Hall fault */
#define THR_FLT_HALL_UVOL_RC              0          		/* Hall fault */
#define THR_FLT_HALL_UVOL_RTC             0          		/* Hall fault */

#define FridgeFault_HALL_5V_UVOL          2522          /* HALL 5V Voltage(AD count)： 4.5V */
#define FridgeFault_HALL_5V_UVOL_REC      2578          /* HALL 5V Voltage(AD count)： 4.6V */

/* 霍尔传感器供电电压过压故障 */
#define THR_FLT_HALL_OVOL                 (5000/5)   		/* Hall fault */
#define THR_FLT_HALL_OVOL_R               (5000/5)   		/* Hall fault */
#define THR_FLT_HALL_OVOL_RC              0          		/* Hall fault */
#define THR_FLT_HALL_OVOL_RTC             0          		/* Hall fault */

#define FridgeFault_HALL_5V_OVOL          3082          /* HALL 5V Voltage(AD count)： 5.5V */
#define FridgeFault_HALL_5V_OVOL_REC      3026          /* HALL 5V Voltage(AD count)： 5.4V */

/* 板载温度过高故障 */
#define THR_FLT_PCB_TS                 (5000/5)   		/* PCB Temperature fault */
#define THR_FLT_PCB_TS_R               (5000/5)   		/* PCB Temperature fault */
#define THR_FLT_PCB_TS_RC              0          		/* PCB Temperature fault */
#define THR_FLT_PCB_TS_RTC             0          		/* PCB Temperature fault */

#define FridgeFault_PCB_OverTemp             160u          /* PCB Temperature： 120℃ */
#define FridgeFault_PCB_RecoverTemp          140u          /* PCB fault recovery temperature： 100℃ */


#define Comp_Intinal_Fault_Enable       	 true		   /* Enable Comp Intinal Fault Detection */
#define Comp_Intinal_Fault_Disable       	 false		   /* Disable Comp Intinal Fault Detection */

/* when the fault or warning happened, the corresponding fault bit is asserted*/
#define FAULT_COMBINED_SET(x) {FAULT_Combined |= ((uint32)0x01) << x;}
#define FAULT_COMBINED_CLR(x) {FAULT_Combined &= ~(((uint32)0x01) << x);}
/*******************************************************************************
||    Enum Definition
||******************************************************************************/

/*******************************************************************************
||    Typedef Definition
||******************************************************************************/
static boolean FridgeFault_Compressor_UnderVoltage(void);
static boolean FridgeFault_Compressor_OverCurrent(void);
static boolean FridgeFault_Compressor_OverTemp(void);
static boolean FridgeFault_Fan_OverCurrent(void);
static boolean FridgeFault_Film_ShortCircuit(void);
static boolean FridgeFault_Strip_ShortCircuit(void);
static boolean FridgeFault_Liner_TempSensor(void);
static boolean FridgeFault_PCB_OverTempera(void);

static boolean FridgeFault_Compressor_OverVoltage(void);		/* DQ 4/16 */
static boolean FridgeFault_Compressor_StartupFail(void);		/* DQ 4/16 */
static boolean FridgeFault_Fan_UnderCurrent(void);				/* DQ 4/16 */
static boolean FridgeFault_Film_UnderCurrent(void);				/* DQ 4/16 */
static boolean FridgeFault_Strip_UnderCurrent(void);			/* DQ 4/16 */
static boolean FridgeFault_Condenser_TempSensor(void);			/* DQ 4/16 */
static boolean FridgeFault_WLED_OverCurrent(void);				/* DQ 4/16 */
static boolean FridgeFault_WLED_UnderCurrent(void);				/* DQ 4/16 */
static boolean FridgeFault_ALED_OverCurrent(void);				/* DQ 4/16 */
static boolean FridgeFault_ALED_UnderCurrent(void);				/* DQ 4/16 */
static boolean FridgeFault_UVLED_OverCurrent(void);				/* DQ 4/16 */
static boolean FridgeFault_UVLED_UnderCurrent(void);			/* DQ 4/16 */
static boolean FridgeFault_HALL_Under_Voltage(void);			/* DQ 4/16 */
static boolean FridgeFault_HALL_Over_Voltage(void);				/* DQ 4/16 */

static boolean FridgeFault_Compressor_Phase_Over_Current(void); /* DQ 4/28 */
static boolean FridgeFault_Compressor_Phase_Lack_Current(void); /* DQ 4/28 */
static boolean FridgeFault_Compressor_Over_Speed(void);			/* DQ 4/28 */
static boolean FridgeFault_Compressor_Under_Speed(void);		/* DQ 4/28 */
static boolean FridgeFault_Compressor_Stall(void);				/* DQ 4/28 */

/* FAULT Var */ 
FAULT_STATE_T FAULT_States[FLT_ID_MAX] = {

    /* 压缩机供电电压欠压故障 */
    {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_COMP_UV,            /* uw16ThresholdCnt */
		THR_FLT_COMP_UV_R,          /* uw16ThresholdCnt */
		THR_FLT_COMP_UV_RC,         /* uw16RecoverCnt */
		THR_FLT_COMP_UV_RTC,        /* uw16RecoverTargetCnt */
        FridgeFault_Compressor_UnderVoltage  /* fpTestRoutine */
    }, 

    /* 压缩机供电电压过压故障 */
    {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_COMP_OV,            /* uw16ThresholdCnt */
		THR_FLT_COMP_OV_R,          /* uw16ThresholdCnt */
		THR_FLT_COMP_OV_RC,         /* uw16RecoverCnt */
		THR_FLT_COMP_OV_RTC,        /* uw16RecoverTargetCnt */
        FridgeFault_Compressor_OverVoltage  /* fpTestRoutine */
    }, 

    /* 压缩机过流故障 */
    {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_COMP_OC,            /* uw16ThresholdCnt */
		THR_FLT_COMP_OC_R,          /* uw16ThresholdCnt */
		THR_FLT_COMP_OC_RC,         /* uw16RecoverCnt */
		THR_FLT_COMP_OC_RTC,        /* uw16RecoverTargetCnt */
        FridgeFault_Compressor_OverCurrent  /* fpTestRoutine */
    },

    /* 压缩机过热故障 */
    {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_COMP_OT,            /* uw16ThresholdCnt */
		THR_FLT_COMP_OT_R,          /* uw16ThresholdCnt */
		THR_FLT_COMP_OT_RC,         /* uw16RecoverCnt */
		THR_FLT_COMP_OT_RTC,        /* uw16RecoverTargetCnt */
        FridgeFault_Compressor_OverTemp  /* fpTestRoutine */
    },

	/* 压缩机相电流过流故障，内部故障 */
    {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_COMP_STARTF,        /* uw16ThresholdCnt */
		THR_FLT_COMP_STARTF_R,      /* uw16ThresholdCnt */
		THR_FLT_COMP_STARTF_RC,     /* uw16RecoverCnt */
		THR_FLT_COMP_STARTF_RTC,    /* uw16RecoverTargetCnt */
        FridgeFault_Compressor_Phase_Over_Current  /* fpTestRoutine */
    }, 

	/* 压缩机相电流缺相故障，内部故障 */
    {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_COMP_STARTF,        /* uw16ThresholdCnt */
		THR_FLT_COMP_STARTF_R,      /* uw16ThresholdCnt */
		THR_FLT_COMP_STARTF_RC,     /* uw16RecoverCnt */
		THR_FLT_COMP_STARTF_RTC,    /* uw16RecoverTargetCnt */
        FridgeFault_Compressor_Phase_Lack_Current  /* fpTestRoutine */
    }, 

	/* 压缩机超速故障，内部故障 */
    {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_COMP_STARTF,        /* uw16ThresholdCnt */
		THR_FLT_COMP_STARTF_R,      /* uw16ThresholdCnt */
		THR_FLT_COMP_STARTF_RC,     /* uw16RecoverCnt */
		THR_FLT_COMP_STARTF_RTC,    /* uw16RecoverTargetCnt */
        FridgeFault_Compressor_Over_Speed  /* fpTestRoutine */
    }, 

	/* 压缩机低速故障，内部故障 */
    {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_COMP_STARTF,        /* uw16ThresholdCnt */
		THR_FLT_COMP_STARTF_R,      /* uw16ThresholdCnt */
		THR_FLT_COMP_STARTF_RC,     /* uw16RecoverCnt */
		THR_FLT_COMP_STARTF_RTC,    /* uw16RecoverTargetCnt */
        FridgeFault_Compressor_Under_Speed  /* fpTestRoutine */
    }, 

	/* 压缩机堵转故障，内部故障 */
    {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_COMP_STARTF,        /* uw16ThresholdCnt */
		THR_FLT_COMP_STARTF_R,      /* uw16ThresholdCnt */
		THR_FLT_COMP_STARTF_RC,     /* uw16RecoverCnt */
		THR_FLT_COMP_STARTF_RTC,    /* uw16RecoverTargetCnt */
        FridgeFault_Compressor_Stall  /* fpTestRoutine */
    }, 

    /* 压缩机启动失败故障 */
    {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_COMP_STARTF,        /* uw16ThresholdCnt */
		THR_FLT_COMP_STARTF_R,      /* uw16ThresholdCnt */
		THR_FLT_COMP_STARTF_RC,     /* uw16RecoverCnt */
		THR_FLT_COMP_STARTF_RTC,    /* uw16RecoverTargetCnt */
        FridgeFault_Compressor_StartupFail  /* fpTestRoutine */
    }, 

    /* 风扇过流故障 */
    {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_FAN_OC,             /* uw16ThresholdCnt */
		THR_FLT_FAN_OC_R,           /* uw16ThresholdCnt */
		THR_FLT_FAN_OC_RC,          /* uw16RecoverCnt */
		THR_FLT_FAN_OC_RTC,         /* uw16RecoverTargetCnt */
        FridgeFault_Fan_OverCurrent   /* fpTestRoutine */ 
    },

    /* 风扇欠流故障 */
    {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_FAN_UC,              /* uw16ThresholdCnt */
		THR_FLT_FAN_UC_R,            /* uw16ThresholdCnt */
		THR_FLT_FAN_UC_RC,           /* uw16RecoverCnt */
		THR_FLT_FAN_UC_RTC,          /* uw16RecoverTargetCnt */
        FridgeFault_Fan_UnderCurrent   /* fpTestRoutine */ 
    },

    /* 加热膜过流故障 */
    {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_FILM_OC,             /* uw16ThresholdCnt */
		THR_FLT_FILM_OC_R,           /* uw16ThresholdCnt */
		THR_FLT_FILM_OC_RC,          /* uw16RecoverCnt */
		THR_FLT_FILM_OC_RTC,         /* uw16RecoverTargetCnt */
        FridgeFault_Film_ShortCircuit  /* fpTestRoutine */
    },

    /* 加热膜欠流故障 */
    {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_FILM_UC,             /* uw16ThresholdCnt */
		THR_FLT_FILM_UC_R,           /* uw16ThresholdCnt */
		THR_FLT_FILM_UC_RC,          /* uw16RecoverCnt */
		THR_FLT_FILM_UC_RTC,         /* uw16RecoverTargetCnt */
        FridgeFault_Film_UnderCurrent  /* fpTestRoutine */
    },

    /* 加热丝过流故障 */
    {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_STRIP_OC,            /* uw16ThresholdCnt */
		THR_FLT_STRIP_OC_R,          /* uw16ThresholdCnt */
		THR_FLT_STRIP_OC_RC,         /* uw16RecoverCnt */
		THR_FLT_STRIP_OC_RTC,        /* uw16RecoverTargetCnt */
        FridgeFault_Strip_ShortCircuit  /* fpTestRoutine */ 
    },

    /* 加热丝欠流故障 */
    {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_STRIP_UC,            /* uw16ThresholdCnt */
		THR_FLT_STRIP_UC_R,          /* uw16ThresholdCnt */
		THR_FLT_STRIP_UC_RC,         /* uw16RecoverCnt */
		THR_FLT_STRIP_UC_RTC,        /* uw16RecoverTargetCnt */
        FridgeFault_Strip_UnderCurrent  /* fpTestRoutine */ 
    },

    /* 内胆处感温探头故障 */
    {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_LINER_TS,           /* uw16ThresholdCnt */
		THR_FLT_LINER_TS_R,         /* uw16ThresholdCnt */
		THR_FLT_LINER_TS_RC,        /* uw16RecoverCnt */
		THR_FLT_LINER_TS_RTC,       /* uw16RecoverTargetCnt */
        FridgeFault_Liner_TempSensor  /* fpTestRoutine */
    },

    /* 冷凝器感温探头故障 */
    {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_CONDENSER_TS,           /* uw16ThresholdCnt */
		THR_FLT_CONDENSER_TS_R,         /* uw16ThresholdCnt */
		THR_FLT_CONDENSER_TS_RC,        /* uw16RecoverCnt */
		THR_FLT_CONDENSER_TS_RTC,       /* uw16RecoverTargetCnt */
        FridgeFault_Condenser_TempSensor  /* fpTestRoutine */
    },

	 /* 制冷照明灯过流故障 */
	 {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_WLED_OC,           	/* uw16ThresholdCnt */
		THR_FLT_WLED_OC_R,         	/* uw16ThresholdCnt */
		THR_FLT_WLED_OC_RC,        	/* uw16RecoverCnt */
		THR_FLT_WLED_OC_RTC,       	/* uw16RecoverTargetCnt */
        FridgeFault_WLED_OverCurrent  /* fpTestRoutine */
    },

	 /* 制冷照明灯欠流故障  */
	 {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_WLED_UC,           	/* uw16ThresholdCnt */
		THR_FLT_WLED_UC_R,         	/* uw16ThresholdCnt */
		THR_FLT_WLED_UC_RC,        	/* uw16RecoverCnt */
		THR_FLT_WLED_UC_RTC,       	/* uw16RecoverTargetCnt */
        FridgeFault_WLED_UnderCurrent  /* fpTestRoutine */
    },

	 /* 制热照明灯过流故障 */
	 {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_ALED_OC,           	/* uw16ThresholdCnt */
		THR_FLT_ALED_OC_R,         	/* uw16ThresholdCnt */
		THR_FLT_ALED_OC_RC,        	/* uw16RecoverCnt */
		THR_FLT_ALED_OC_RTC,       	/* uw16RecoverTargetCnt */
        FridgeFault_ALED_OverCurrent  /* fpTestRoutine */
    },

	 /* 制热照明灯欠流故障  */
	 {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_ALED_UC,           	/* uw16ThresholdCnt */
		THR_FLT_ALED_UC_R,         	/* uw16ThresholdCnt */
		THR_FLT_ALED_UC_RC,        	/* uw16RecoverCnt */
		THR_FLT_ALED_UC_RTC,       	/* uw16RecoverTargetCnt */
        FridgeFault_ALED_UnderCurrent  /* fpTestRoutine */
    },

	 /* 杀菌灯过流故障 */
	 {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_UVLED_OC,           	/* uw16ThresholdCnt */
		THR_FLT_UVLED_OC_R,         	/* uw16ThresholdCnt */
		THR_FLT_UVLED_OC_RC,        	/* uw16RecoverCnt */
		THR_FLT_UVLED_OC_RTC,       	/* uw16RecoverTargetCnt */
        FridgeFault_UVLED_OverCurrent  /* fpTestRoutine */
    },

	 /* 杀菌灯欠流故障  */
	 {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_UVLED_UC,           	/* uw16ThresholdCnt */
		THR_FLT_UVLED_UC_R,         	/* uw16ThresholdCnt */
		THR_FLT_UVLED_UC_RC,        	/* uw16RecoverCnt */
		THR_FLT_UVLED_UC_RTC,       	/* uw16RecoverTargetCnt */
        FridgeFault_UVLED_UnderCurrent  /* fpTestRoutine */
    },

	 /* 霍尔传感器供电电压欠压故障 */
	 {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_HALL_UVOL,           	/* uw16ThresholdCnt */
		THR_FLT_HALL_UVOL_R,         	/* uw16ThresholdCnt */
		THR_FLT_HALL_UVOL_RC,        	/* uw16RecoverCnt */
		THR_FLT_HALL_UVOL_RTC,       	/* uw16RecoverTargetCnt */
        FridgeFault_HALL_Under_Voltage  /* fpTestRoutine */
    },

	 /* 霍尔传感器供电电压过压故障 */
	 {
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_HALL_OVOL,           	/* uw16ThresholdCnt */
		THR_FLT_HALL_OVOL_R,         	/* uw16ThresholdCnt */
		THR_FLT_HALL_OVOL_RC,        	/* uw16RecoverCnt */
		THR_FLT_HALL_OVOL_RTC,       	/* uw16RecoverTargetCnt */
        FridgeFault_HALL_Over_Voltage  /* fpTestRoutine */
    },

	/* 板载温度过高故障 */
	{
        FALSE,                      /* bTestEn */
        FALSE,                      /* bFailed */
        FALSE,                      /* bPreFailed */
        FALSE,                      /* bFaultInject */
        0,                          /* uw16DebounceCnt */
        THR_FLT_PCB_TS,           	/* uw16ThresholdCnt */
		THR_FLT_PCB_TS_R,         	/* uw16ThresholdCnt */
		THR_FLT_PCB_TS_RC,        	/* uw16RecoverCnt */
		THR_FLT_PCB_TS_RTC,       	/* uw16RecoverTargetCnt */
        FridgeFault_PCB_OverTempera  /* fpTestRoutine */
    },
};
/*******************************************************************************
||    Global variables Declaration
||******************************************************************************/
uint32 FAULT_Combined = 0;
/*******************************************************************************
||    static local variables Declaration
||******************************************************************************/
#define DEBUG_FAULT
#ifdef DEBUG_FAULT
uint8 Fault_test_flag;
uint8 Fault_test_flag1;
uint8 Fault_test_flag2;
uint8 Fault_test_flag3;
uint8 Fault_test_flag4;
uint8 Fault_test_flag5;
uint8 Fault_test_flag6;
#endif

// 电流阈值设置
float phase_current_max = FridgeFault_COMP_OC_PHASE;
float phase_current_min = FridgeFault_COMP_LC_PHASE;
uint16_t phase_current_max_count = FridgeFault_COMP_OC_PHASE_Cnt;
uint16_t phase_current_min_count = FridgeFault_COMP_LC_PHASE_Cnt;
// 转速阈值设置
uint16_t comp_speed_min = FridgeFault_COMP_US;
uint16_t comp_speed_max = FridgeFault_COMP_OS;
uint16_t comp_speed_count = FridgeFault_COMP_OS_Cnt;
// 堵转阈值设置
uint16_t comp_speed_stall = FridgeFault_COMP_Stall_Speed;
float phase_current_stall = FridgeFault_COMP_Stall_Current;
uint16_t comp_stall_count = FridgeFault_COMP_Stall_Cnt;

/*******************************************************************************
||    static Local Functions Declaration
||******************************************************************************/
void FridgeFault_Test_Enable(void);
void FridgeFault_Detection_Routine(void);  
/*******************************************************************************
||    Extern variables and functions declaration
||******************************************************************************/

/********************************** Fault Initialization **********************************/
/*******************************************************************************
*Function    	    : void FridgeFault_Init(void)
*ReturnValue 	    : void
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : None
*Description		: Init Fault Vars
|******************************************************************************/
void FridgeFault_Init(void) 
{
    FAULT_Combined = 0;

	/* 压缩机内部故障,初始化阶段需要设置参数 */
	#if 0
	// 电压阈值设置
	void voltageProtectThresholdSet(float boVol_min, float boVol_max, uint16_t boVol_cnt, float runVol_min, float runVol_max, uint16_t runVol_cnt);
	#endif

	// 电流阈值设置
	currentProtectThresholdSet(phase_current_max, phase_current_max_count, phase_current_min, phase_current_min_count);
	// 转速阈值设置
	speedProtectThresholdSet(comp_speed_min, comp_speed_max, comp_speed_count);
	// 堵转阈值设置
	stallProtectThresholdSet(comp_speed_stall, phase_current_stall, comp_stall_count);
}

/********************************** Fault Test Enable **********************************/
/*******************************************************************************
*Function    	    : void FridgeFault_Test_Enable(void)
*ReturnValue 	    : void
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : None
*Description		: Fault Test Enable
|******************************************************************************/
uint32 FaultTest = 0;
void FridgeFault_Test_Enable(void)   
{
	FaultTest = getErrorInfo();
    /* Fault Test Enable */
	/* 压缩机故障 */
    if(TRUE == COMP_Enable_Flag)
    {
		FAULT_States[FLT_F_COMP_UNDER_VOL].bTestEn = TRUE;
		FAULT_States[FLT_F_COMP_OVER_VOL].bTestEn = TRUE;
		FAULT_States[FLT_F_COMP_OVER_TEMP].bTestEn = TRUE;
	    FAULT_States[FLT_F_COMP_OVER_CURRENT].bTestEn = TRUE;
		FAULT_States[FLT_F_COMP_STARTUP_FAIL].bTestEn = TRUE;

		/* 压缩机内部故障诊断 */
		currentProtectSet(Comp_Intinal_Fault_Enable);
		speedProtectSet(Comp_Intinal_Fault_Enable);
		stallProtectSet(Comp_Intinal_Fault_Enable);

		// voltageProtectSet(Comp_Intinal_Fault_Enable);
		// voltagePowerProtectSet(Comp_Intinal_Fault_Enable);
    }
    else
    {
		FAULT_States[FLT_F_COMP_UNDER_VOL].bTestEn = FALSE;
		FAULT_States[FLT_F_COMP_OVER_VOL].bTestEn = FALSE;
		FAULT_States[FLT_F_COMP_OVER_TEMP].bTestEn = FALSE;
	    FAULT_States[FLT_F_COMP_OVER_CURRENT].bTestEn = FALSE;
		FAULT_States[FLT_F_COMP_STARTUP_FAIL].bTestEn = FALSE;

		/* 压缩机内部故障诊断 */
		currentProtectSet(Comp_Intinal_Fault_Disable);
		speedProtectSet(Comp_Intinal_Fault_Disable);
		stallProtectSet(Comp_Intinal_Fault_Disable);
    }

	/* 风扇故障 */
    if((TRUE == Fan_FaultDetectEnable_Flag))
    {
	    // FAULT_States[FLT_F_FAN_FAULT].bTestEn = TRUE;
		FAULT_States[FLT_F_FAN_UC_FAULT].bTestEn = TRUE;
    }
    else
    {
	    // FAULT_States[FLT_F_FAN_FAULT].bTestEn = FALSE;
		FAULT_States[FLT_F_FAN_UC_FAULT].bTestEn = FALSE;
    }

	/* 加热膜故障 */
    if((TRUE == Film_FaultDetectEnable_Flag))
    {
        FAULT_States[FLT_F_HEAT_FILM_FAULT].bTestEn = TRUE;
		FAULT_States[FLT_F_HEAT_FILM_UC_FAULT].bTestEn = TRUE;
    }
    else
    {
        FAULT_States[FLT_F_HEAT_FILM_FAULT].bTestEn = FALSE;
		FAULT_States[FLT_F_HEAT_FILM_UC_FAULT].bTestEn = FALSE;
    }
	
	/* 加热丝故障 */
	if(TRUE == Strip_FaultDetectEnable_Flag)
	{
    	FAULT_States[FLT_F_HEAT_STRIP_FAULT].bTestEn = TRUE;
		FAULT_States[FLT_F_HEAT_STRIP_UC_FAULT].bTestEn = TRUE;
	}
	else
	{
    	FAULT_States[FLT_F_HEAT_STRIP_FAULT].bTestEn = FALSE;
		FAULT_States[FLT_F_HEAT_STRIP_UC_FAULT].bTestEn = FALSE;
	}

	/* 制冷照明灯故障 */
	if(TRUE == WLed_FaultDetectEnable_Flag)
	{
		FAULT_States[FLT_F_WLED_OVER_CURRENT].bTestEn 	= TRUE;
		FAULT_States[FLT_F_WLED_UNDER_CURRENT].bTestEn 	= TRUE;
	}
	else
	{
		FAULT_States[FLT_F_WLED_OVER_CURRENT].bTestEn 	= FALSE;
		FAULT_States[FLT_F_WLED_UNDER_CURRENT].bTestEn 	= FALSE;
	}

	/* 制热照明灯故障 */
	if(TRUE == ALed_FaultDetectEnable_Flag)
	{
		FAULT_States[FLT_F_ALED_OVER_CURRENT].bTestEn 	= TRUE;
		FAULT_States[FLT_F_ALED_UNDER_CURRENT].bTestEn 	= TRUE;
	}
	else
	{
		FAULT_States[FLT_F_ALED_OVER_CURRENT].bTestEn 	= FALSE;
		FAULT_States[FLT_F_ALED_UNDER_CURRENT].bTestEn 	= FALSE;
	}

	/* 杀菌灯故障 */
	if(TRUE == UVLED_FaultDetectEnable_Flag)
	{
		FAULT_States[FLT_F_UVLED_OVER_CURRENT].bTestEn 	= TRUE;
		FAULT_States[FLT_F_UVLED_UNDER_CURRENT].bTestEn = TRUE;
	}
	else
	{
		FAULT_States[FLT_F_UVLED_OVER_CURRENT].bTestEn 	= FALSE;
		FAULT_States[FLT_F_UVLED_UNDER_CURRENT].bTestEn = FALSE;
	}

	/* 温度传感器故障 */
    FAULT_States[FLT_F_LINER_TEMP_SENSOR].bTestEn = TRUE;
	FAULT_States[FLT_F_CONDENSER_TEMP_SENSOR].bTestEn = TRUE;

	/* 霍尔传感器故障 */
	FAULT_States[FLT_F_HALL_UNDER_VOL_FAULT].bTestEn = TRUE;
	FAULT_States[FLT_F_HALL_OVER_VOL_FAULT].bTestEn = TRUE;

	/* 板载温度过高故障 */
	FAULT_States[FLT_F_PCB_OVER_TEMP].bTestEn 	= TRUE;
}

/********************************** Fault Detection Routine **********************************/
/*******************************************************************************
*Function    	    : void FridgeFault_Detection_Routine(void)
*ReturnValue 	    : void
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : None
*Description		: Fault Detection Routine
|******************************************************************************/
void FridgeFault_Detection_Routine(void)   
{
	/* Fault Routines */
	/* 使能故障诊断检测函数 */
	#if 0
	if (FAULT_States[FLT_F_COMP_UNDER_VOL].bTestEn) 
	{
	   /* Do the test */
	   (*FAULT_States[FLT_F_COMP_UNDER_VOL].fpTestRoutine)();               
	}
	#endif

	for(uint8 i = 0u;i < FLT_ID_MAX;i++)
	{
		if (FAULT_States[i].bTestEn) 
		{
		/* Do the test */
		(*FAULT_States[i].fpTestRoutine)();               
		}
	}
}

/********************************** Fault Clear **********************************/
/*******************************************************************************
*Function    	    : void FridgeFault_Clear(void)
*ReturnValue 	    : void
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : None
*Description		: Fault Clear
|******************************************************************************/
void FridgeFault_Clear(void)   
{
    uint16 i;
    FAULT_Combined = 0;

    /* Clear fault */
    for (i = 0; i < FLT_ID_MAX; i++) {
        FAULT_States[i].bFailed = FALSE;
        FAULT_States[i].bPreFailed = FALSE;
        FAULT_States[i].uw16DebounceCnt = 0;
    }
}

/********************************** Fault Detection Functions **********************************/
/*******************************************************************************
*Function    	    : uint8 FridgeFault_Compressor_UnderVoltage(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: 压缩机供电电压欠压故障
|******************************************************************************/
static boolean FridgeFault_Compressor_UnderVoltage(void)
{
	uint16 i = FLT_F_COMP_UNDER_VOL;
   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   { 
      if (FridgeAppl_FridgeComp12V_LG_Voltage() <= FridgeFault_COMP_UV) 
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (FridgeAppl_FridgeComp12V_LG_Voltage() >= FridgeFault_COMP_UV_REC) 
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_Compressor_OverVoltage(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: 压缩机供电电压过压故障
|******************************************************************************/
static boolean FridgeFault_Compressor_OverVoltage(void)
{
	uint16 i = FLT_F_COMP_OVER_VOL;
   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   { 
      if (FridgeAppl_FridgeComp12V_LG_Voltage() >= FridgeFault_COMP_OV) 
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (FridgeAppl_FridgeComp12V_LG_Voltage() <= FridgeFault_COMP_OV_REC) 
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;
}


/*******************************************************************************
*Function    	    : uint8 FridgeFault_Compressor_OverCurrent(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: 压缩机过流故障
|******************************************************************************/
uint32 Comp_BusCurrent;	
uint32 Comp_BusPower; 
static boolean FridgeFault_Compressor_OverCurrent(void)
{
	uint16 i = FLT_F_COMP_OVER_CURRENT;
	uint16 Comp_BusVoltage;
	// uint32 Comp_BusCurrent;	
	// uint32 Comp_BusPower; 

	Comp_BusVoltage = FridgeAppl_FridgeComp12V_LG_Voltage();	//mV
	Comp_BusCurrent = AMP_AdCtr_Get_COMP_12V_Value();	//mA 
	Comp_BusPower = (uint32)Comp_BusVoltage*Comp_BusCurrent/1000;	//mW
 
   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (Comp_BusPower >= FridgeFault_COMP_OP) 
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (Comp_BusPower <= FridgeFault_COMP_OP_REC) 
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_Compressor_OverTemp(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: 压缩机过热故障
|******************************************************************************/
static boolean FridgeFault_Compressor_OverTemp(void)
{
	uint16 i = FLT_F_COMP_OVER_TEMP;
	sint16 FridgeCompTemp_Calculate;

	FridgeCompTemp_Calculate = FridgeCtrl_CompTemp_Feedback_Function();     //总的offset：40

   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (FridgeCompTemp_Calculate >= FridgeFault_COMP_OT) 
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (FridgeCompTemp_Calculate <= FridgeFault_COMP_OT_REC)
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_Compressor_Phase_Over_Current(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: 压缩机相电流过流故障，内部故障
|******************************************************************************/
static boolean FridgeFault_Compressor_Phase_Over_Current(void)
{
	uint16 i = FLT_F_COMP_OVER_PHASE_CURRENT;
	uint32 Comp_Intenal_Fault;

	Comp_Intenal_Fault = (getErrorInfo() << 28) >> 3;

   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (0u != Comp_Intenal_Fault) 
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (0u == Comp_Intenal_Fault) 
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;

	return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_Compressor_Phase_Lack_Current(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: 压缩机相电流缺相故障，内部故障
|******************************************************************************/
static boolean FridgeFault_Compressor_Phase_Lack_Current(void)
{
	uint16 i = FLT_F_COMP_LACK_PHASE_CURRENT;
	uint32 Comp_Intenal_Fault;

	Comp_Intenal_Fault = (getErrorInfo() << 27) >> 4;

   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (0u != Comp_Intenal_Fault)
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (0u == Comp_Intenal_Fault)
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;

	return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_Compressor_Over_Speed(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: 压缩机超速故障，内部故障
|******************************************************************************/
static boolean FridgeFault_Compressor_Over_Speed(void)
{
	uint16 i = FLT_F_COMP_OVER_SPEED;
	uint32 Comp_Intenal_Fault;

	Comp_Intenal_Fault = (getErrorInfo() << 21) >> 10;

   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (0u != Comp_Intenal_Fault)
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (0u == Comp_Intenal_Fault)
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;

	return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_Compressor_Under_Speed(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: 压缩机低速故障，内部故障
|******************************************************************************/
static boolean FridgeFault_Compressor_Under_Speed(void)
{
	uint16 i = FLT_F_COMP_UNDER_SPEED;
	uint32 Comp_Intenal_Fault;

	Comp_Intenal_Fault = (getErrorInfo() << 20) >> 11;

   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (0u != Comp_Intenal_Fault)
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (0u == Comp_Intenal_Fault)
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;

	return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_Compressor_Stall(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: 压缩机堵转故障，内部故障
|******************************************************************************/
static boolean FridgeFault_Compressor_Stall(void)
{
	uint16 i = FLT_F_COMP_STALL;
	uint32 Comp_Intenal_Fault;

	Comp_Intenal_Fault = (getErrorInfo() << 18) >> 13;

   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (0u != Comp_Intenal_Fault)
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (0u == Comp_Intenal_Fault)
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;

	return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_Compressor_StartupFail(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: 压缩机启动失败故障
|******************************************************************************/
static boolean FridgeFault_Compressor_StartupFail(void)
{
	uint16 i = FLT_F_COMP_STARTUP_FAIL;
	uint32 Comp_Intenal_Fault;

	Comp_Intenal_Fault = (getErrorInfo() << 17) >> 14;

   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (0u != Comp_Intenal_Fault)
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (0u == Comp_Intenal_Fault)
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;

	return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_Fan_OverCurrent(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: 风扇过流故障
|******************************************************************************/
static boolean FridgeFault_Fan_OverCurrent(void)
{
	uint16 i = FLT_F_FAN_FAULT;
   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (FridgeAppl_FridgeFAN_Value() >= FridgeFault_FAN_OC) 
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (FridgeAppl_FridgeFAN_Value() < FridgeFault_FAN_OC) 
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_Fan_UnderCurrent(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: 风扇欠流故障
|******************************************************************************/
static boolean FridgeFault_Fan_UnderCurrent(void)
{
	uint16 i = FLT_F_FAN_UC_FAULT;
   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (FridgeAppl_FridgeFAN_Value() <= FridgeFault_FAN_UC) 
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (FridgeAppl_FridgeFAN_Value() > FridgeFault_FAN_UC) 
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_Film_ShortCircuit(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: 加热膜过流故障
|******************************************************************************/
static boolean FridgeFault_Film_ShortCircuit(void)
{
	uint16 i = FLT_F_HEAT_FILM_FAULT;
   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (FridgeAppl_FridgeHeatFilm_Value() >= FridgeFault_FILM_OC)
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (FridgeAppl_FridgeHeatFilm_Value() < FridgeFault_FILM_OC)
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_Film_UnderCurrent(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: 加热膜欠流故障
|******************************************************************************/
static boolean FridgeFault_Film_UnderCurrent(void)
{
	uint16 i = FLT_F_HEAT_FILM_UC_FAULT;
   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (FridgeAppl_FridgeHeatFilm_Value() <= FridgeFault_FILM_UC)
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (FridgeAppl_FridgeHeatFilm_Value() > FridgeFault_FILM_UC)
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_Strip_ShortCircuit(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: 加热丝过流故障
|******************************************************************************/
static boolean FridgeFault_Strip_ShortCircuit(void)
{
	uint16 i = FLT_F_HEAT_STRIP_FAULT;
   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (FridgeAppl_FridgeHeatWire_Value() >= FridgeFault_STRIP_OC) 
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (FridgeAppl_FridgeHeatWire_Value() < FridgeFault_STRIP_OC)
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_Strip_UnderCurrent(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: 加热丝欠流故障
|******************************************************************************/
static boolean FridgeFault_Strip_UnderCurrent(void)
{
	uint16 i = FLT_F_HEAT_STRIP_UC_FAULT;
   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (FridgeAppl_FridgeHeatWire_Value() <= FridgeFault_STRIP_UC) 
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (FridgeAppl_FridgeHeatWire_Value() > FridgeFault_STRIP_UC)
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_Liner_TempSensor(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: 内胆处感温探头故障
|******************************************************************************/
static boolean FridgeFault_Liner_TempSensor(void)
{
	uint16 i = FLT_F_LINER_TEMP_SENSOR;
	sint16 FridgeTEMP_Calculate;

	FridgeTEMP_Calculate = FridgeCtrl_Temp_Feedback_Function();		//offset:40

   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if ((FridgeTEMP_Calculate > FridgeFault_LINER_TS_OPEN)||(FridgeTEMP_Calculate < FridgeFault_LINER_TS_SC))
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if ((FridgeTEMP_Calculate <= FridgeFault_LINER_TS_OPEN_REC)&&(FridgeTEMP_Calculate >= FridgeFault_LINER_TS_SC_REC))
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_Condenser_TempSensor(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: 冷凝器感温探头故障
|******************************************************************************/
static boolean FridgeFault_Condenser_TempSensor(void)
{
	uint16 i = FLT_F_CONDENSER_TEMP_SENSOR;
	sint16 FridgeTEMP_Calculate;

	FridgeTEMP_Calculate = FridgeCtrl_CompTemp_Feedback_Function();		//offset:40

   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if ((FridgeTEMP_Calculate > FridgeFault_CONDENSER_TS_OPEN)||(FridgeTEMP_Calculate < FridgeFault_CONDENSER_TS_SC))
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if ((FridgeTEMP_Calculate <= FridgeFault_CONDENSER_TS_OPEN_REC)&&(FridgeTEMP_Calculate >= FridgeFault_CONDENSER_TS_SC_REC))
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_WLED_OverCurrent(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :LED Over Current Fault
*Description		: 制冷照明灯过流故障
|******************************************************************************/
static boolean FridgeFault_WLED_OverCurrent(void)
{
	uint16 i = FLT_F_WLED_OVER_CURRENT;
	uint8 WLED_GetFault;

	WLED_GetFault = LED_DRV_M_GetFaultMode();
 
   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (1u == WLED_GetFault)
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (0u == WLED_GetFault)
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
		else
		{
			/* Reset Passed */
			FAULT_States[i].uw16DebounceCnt = 0;
		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_WLED_UnderCurrent(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :LED Over Current Fault
*Description		: 制冷照明灯欠流故障
|******************************************************************************/
static boolean FridgeFault_WLED_UnderCurrent(void)
{
	uint16 i = FLT_F_WLED_UNDER_CURRENT;
	uint8 WLED_GetFault;

	WLED_GetFault = LED_DRV_M_GetFaultMode();

   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (2u == WLED_GetFault) 
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (0u == WLED_GetFault) 
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
		else
		{
			/* Reset Passed */
			FAULT_States[i].uw16DebounceCnt = 0;
		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_ALED_OverCurrent(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :LED Over Current Fault
*Description		: 制热照明灯过流故障
|******************************************************************************/
static boolean FridgeFault_ALED_OverCurrent(void)
{
	uint16 i = FLT_F_ALED_OVER_CURRENT;
	uint8 ALED_GetFault;

	ALED_GetFault = LED_DRV_M_GetFaultMode();

   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (1u == ALED_GetFault)
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (0u == ALED_GetFault)
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
		else
		{
			/* Reset Passed */
			FAULT_States[i].uw16DebounceCnt = 0;
		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_ALED_UnderCurrent(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :LED Over Current Fault
*Description		: 制热照明灯欠流故障
|******************************************************************************/
static boolean FridgeFault_ALED_UnderCurrent(void)
{
	uint16 i = FLT_F_ALED_UNDER_CURRENT;
	uint8 ALED_GetFault;

	ALED_GetFault = LED_DRV_M_GetFaultMode();

   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (2u == ALED_GetFault)
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (0u == ALED_GetFault)
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
		else
		{
			/* Reset Passed */
			FAULT_States[i].uw16DebounceCnt = 0;
		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_UVLED_OverCurrent(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :LED Over Current Fault
*Description		: 杀菌灯过流故障
|******************************************************************************/
static boolean FridgeFault_UVLED_OverCurrent(void)
{
	uint16 i = FLT_F_UVLED_OVER_CURRENT;
	uint8 UVLED_GetFault;

	UVLED_GetFault = LED_DRV_M_GetFaultMode();

   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (1u == UVLED_GetFault)
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (0u == UVLED_GetFault)
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
		else
		{
			/* Reset Passed */
			FAULT_States[i].uw16DebounceCnt = 0;
		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_UVLED_UnderCurrent(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :LED Over Current Fault
*Description		: 杀菌灯欠流故障
|******************************************************************************/
static boolean FridgeFault_UVLED_UnderCurrent(void)
{
	uint16 i = FLT_F_UVLED_UNDER_CURRENT;
	uint8 UVLED_GetFault;

	UVLED_GetFault = LED_DRV_M_GetFaultMode();

   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (2u == UVLED_GetFault)
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (0u == UVLED_GetFault)
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
		else
		{
			/* Reset Passed */
			FAULT_States[i].uw16DebounceCnt = 0;
		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_HALL_Under_Voltage(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :LED Over Current Fault
*Description		: 霍尔传感器供电电压欠压故障
|******************************************************************************/
static boolean FridgeFault_HALL_Under_Voltage(void)
{
	uint16 i = FLT_F_HALL_UNDER_VOL_FAULT;
	uint16 HALL_5VAD_Value1;

	HALL_5VAD_Value1 = FridgeAppl_FridgeHALL_5VAD_Value();

   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (HALL_5VAD_Value1 <= FridgeFault_HALL_5V_UVOL)
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (HALL_5VAD_Value1 >= FridgeFault_HALL_5V_UVOL_REC)
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
		else
		{
			/* Reset Passed */
			FAULT_States[i].uw16DebounceCnt = 0;
		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_HALL_Over_Voltage(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :LED Over Current Fault
*Description		: 霍尔传感器供电电压过压故障
|******************************************************************************/
static boolean FridgeFault_HALL_Over_Voltage(void)
{
	uint16 i = FLT_F_HALL_OVER_VOL_FAULT;
	uint16 HALL_5VAD_Value2;

	HALL_5VAD_Value2 = FridgeAppl_FridgeHALL_5VAD_Value();


   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (HALL_5VAD_Value2 >= FridgeFault_HALL_5V_OVOL)
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (HALL_5VAD_Value2 <= FridgeFault_HALL_5V_OVOL_REC)
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
		else
		{
			/* Reset Passed */
			FAULT_States[i].uw16DebounceCnt = 0;
		}		
   	}
   	return FAULT_States[i].bFailed;
}

/*******************************************************************************
*Function    	    : uint8 FridgeFault_PCB_OverTempera(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :PCB Temperature > 120
*Description		: 板载温度过高故障
|******************************************************************************/
static boolean FridgeFault_PCB_OverTempera(void)
{
	uint16 i = FLT_F_PCB_OVER_TEMP;
	uint16 PCBTemperature;

	PCBTemperature = ((uint16)FridgeAppl_PCBTemperature_Value()/10) + 40;

   /* Do the test */
   if( FAULT_States[i].bFailed != TRUE )
   {
      if (PCBTemperature >= FridgeFault_PCB_OverTemp) 
      {
    	/* Test failed */
    	FAULT_States[i].uw16DebounceCnt++;
    	/* Debouncing */
    	if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt) 
    	{
    		/* Assert fault */
    		FAULT_States[i].bFailed = TRUE;
    		FAULT_States[i].uw16DebounceCnt = 0;
    		FAULT_COMBINED_SET(i);
    	}
      }
      else 
      {
    	    /* Test Passed */
    		FAULT_States[i].uw16DebounceCnt = 0;
      }
   }
   else
   	{	   
        if (PCBTemperature <= FridgeFault_PCB_RecoverTemp)
   		{
   			/* Test failed */
   			FAULT_States[i].uw16DebounceCnt++;
   			/* Debouncing */
   			if (FAULT_States[i].uw16DebounceCnt >= FAULT_States[i].uw16ThresholdCnt_R) 
   			{
   				/* Reset fault */
   				FAULT_States[i].bFailed = FALSE;
   				FAULT_States[i].uw16DebounceCnt = 0;
   				FAULT_COMBINED_CLR(i);
   			}		
   		}
   		else
   		{
   			/* Reset Passed */
   			FAULT_States[i].uw16DebounceCnt = 0;
   		}		
   	}
   	return FAULT_States[i].bFailed;
}

/********************************** Fault Detection Main Functions **********************************/
/*******************************************************************************
*Function    	    : void FridgeFault_Detection_MainFunction(void)
*ReturnValue 	    : void
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : None
*Description		: Fridge fault detection main function
|******************************************************************************/
void FridgeFault_Detection_MainFunction(void)
{
    /* Fridge fault detection main function */
    FridgeFault_Test_Enable();
    FridgeFault_Detection_Routine();
}

