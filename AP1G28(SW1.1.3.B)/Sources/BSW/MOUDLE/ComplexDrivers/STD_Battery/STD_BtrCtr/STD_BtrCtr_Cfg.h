/*******************************************************************************
|  File Name:  STD_BtrCtrCfg.h
|  Description:  Battery Control Layer, include System Battery Mode, Load Battery
|  Mode and so on.
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XZS           Zhangsheng Xia         CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2017-02-22    01.00.00     XZS       Creation
| 2017-06-30    01.01.00     CHY       Optimize function Configuration
| 2017-08-18    01.02.00     LSG       Add Net bus voltage function
| 2018-05-18    01.03.00     LSG       Synchronize function name called from STD_Lib
| 2018-07-30    01.04.00     LSG       Synchronize with new framework
| 2019-01-14    01.05.00     LSG       1)Optimize function Configuration 2)Rename MotorBattery LoadBattery
|******************************************************************************/

#if !defined (_STD_BTRCTRCFG_H)
#define _STD_BTRCTRCFG_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
//#include "SysTypes.h"

#include "STD_Lib.h"
#include "STD_AdcM.h"
//#include "Mcal_App.h"
/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define BTRCTR_CODE_RAM	//__attribute__ ((section(".BSW_RAM_DATA")))
#define BTRCTR_CODE_KAM	//__attribute__ ((section(".BSW_KAM_DATA")))

#define BTRCTR_DISABLE                                  (0u)
#define BTRCTR_ENABLE                                   (1u)

/*config Bat C mode*/
#define BTRCTR_SYS_BATTERY_MODE_C_ENABLE                BTRCTR_ENABLE
#define BTRCTR_SYS_BATTERY_LOW_VOL_ENABLE               BTRCTR_ENABLE

/*config Bat D mode*/
#define BTRCTR_SYS_BATTERY_MODE_D_ENABLE                BTRCTR_DISABLE


/*config motor class*/
#define BTRCTR_LOAD_BATTERY_ENABLE                      BTRCTR_ENABLE
#define BTRCTR_LOAD_BATTERY_LOW_VOL_ENABLE              BTRCTR_ENABLE

#define BTRCTR_CANVOLENABLE                             BTRCTR_DISABLE/*���ߵ�ѹʹ��*/

#define BTRCTR_GetBatteryAdValue()                      ADCM_GetCurrentValue((uint8)ADCMCFG_KL30_AD_CH)
#define BTRCTR_GetLoadBatAdValue()                      ADCM_GetCurrentValue((uint8)ADCMCFG_KL30_AD_CH)

#define BTRCTR_TASK_PERIOD                              ((uint16)5u)
#define	BTRCTR_5msTASK_PERIOD							(5u)

#define BTRCTR_FILTER_10MS                              (uint8)((uint16)10u/BTRCTR_TASK_PERIOD)
#define BTRCTR_FILTER_20MS                              (uint8)((uint16)20u/BTRCTR_TASK_PERIOD)
#define BTRCTR_FILTER_40MS                              (uint8)((uint16)40u/BTRCTR_TASK_PERIOD)
#define BTRCTR_FILTER_100MS                             (uint8)((uint16)100u/BTRCTR_TASK_PERIOD)
#define BTRCTR_FILTER_500MS                             (uint8)((uint16)500u/BTRCTR_TASK_PERIOD)
#define BTRCTR_FILTER_200MS                             (uint8)((uint16)190u/BTRCTR_TASK_PERIOD)
#define BTRCTR_FILTER_1200MS                             (uint8)((uint16)1200u/BTRCTR_TASK_PERIOD)

#define BTRCTR_FILTER_1000MS                            (uint8)((uint16)1000u/BTRCTR_TASK_PERIOD)

#define BTRCTR_FILTER_TIME_FAST                         BTRCTR_FILTER_40MS
#define BTRCTR_FILTER_TIME_NORMAL                       BTRCTR_FILTER_500MS
#define BTRCTR_FILTER_TIME_LONG                         BTRCTR_FILTER_1200MS

#define BTRCTR_LOAD_FILTER_TIME_FAST                   BTRCTR_FILTER_40MS
#define BTRCTR_LOAD_FILTER_TIME_ABNORMAL               BTRCTR_FILTER_500MS    /*units:mSec; typeSize:16; Low bound:0; Upper Bound:65535; Bench Value:300; MAUs:; Address:0x7F0011; Description:XXXXXXXX; Transform Equation:XXXXXXXX;*/
#define BTRCTR_LOAD_FILTER_TIME_NORMAL                 BTRCTR_FILTER_500MS

//#define BTRCTR_IGON_FILTER_TIME 200u  // 1000ms/5ms周期
//#define BTRCTR_IGON_FILTER_3MINTIME 4u  // 20/5ms周期

/*config Battery Sampling Precision*/
#define BTRCTR_SAMPLE_PRECISION_10BIT_ENABLE		(0u)
#define BTRCTR_SAMPLE_PRECISION_12BIT_ENABLE		(1u)
#if (1u == BTRCTR_SAMPLE_PRECISION_10BIT_ENABLE)
/*Step Sys Battery*/
#define	BTRCTR_SYS_BATTERY_A2B_UP_VOLT					(uint16)(636u)		/*16.5V(3.10V),2695U/637U/580U*/
#define	BTRCTR_SYS_BATTERY_A2B_DOWN_VOLT				(uint16)(328u)		/*8.5V(1.59V),1384U/314U/268U*/

#define	BTRCTR_SYS_BATTERY_B2A_DOWN_VOLT				(uint16)(617u)		/*16.0V(3.00V),2613U/617U/560U*/
#define	BTRCTR_SYS_BATTERY_B2A_UP_VOLT					(uint16)(347u)		/*9.0V(1.69V),1466U/334U/285U*/

#define	BTRCTR_SYS_BATTERY_C2B_DOWN_VOLT				(uint16)(694u)		/*18(3.38V),3023U/718U/665U*/
#define	BTRCTR_SYS_BATTERY_C2B_UP_VOLT					(uint16)(270u)		/*7V(1.31V),1057U/235U/254U*/

#define	BTRCTR_SYS_BATTERY_B2C_UP_VOLT					(uint16)(713u)		/*18.5V(3.47V),3097U/738U/683U*/
#define	BTRCTR_SYS_BATTERY_B2C_DOWN_VOLT				(uint16)(251u)		/*6.5V(1.22V),983U/216U/233U*/

#define	BTRCTR_SYS_THRESHOLD_LOW_BATTERY_IN				(uint16)(347u)            /*9V*/
#define	BTRCTR_SYS_THRESHOLD_LOW_BATTERY_OUT        	(uint16)(365u)            /*9.5V*/
#define BTRCTR_LOAD_THRESHOLD_LOW_BATTERY_IN            (uint16)(348u)            /*9V*/
#define BTRCTR_LOAD_THRESHOLD_LOW_BATTERY_OUT           (uint16)(365u)            /*9.5V*/

/*Step Motor  Battery*/
#define	BTRCTR_LOAD_BATTERY_B2A_UP_VOLT				(uint16)(397u)		/*10.3V(1.93V),1057U/235U/254U*/
#define	BTRCTR_LOAD_BATTERY_B2A_DOWN_VOLT			(uint16)(609u) 		/*15.8V(2.97V),983U/216U/233U*/

#define	BTRCTR_LOAD_BATTERY_A2B_UP_VOLT				(uint16)(628u)		/*16.3V(3.06V),1057U/235U/254U*/
#define	BTRCTR_LOAD_BATTERY_A2B_DOWN_VOLT			(uint16)(378u) 		/*9.8V(1.84V),983U/216U/233U*/

#else

/******************/
//(KL30-0.05)*154.83
#define BTRCTR_SYS_BATTERY_A2B_UP_VOLT                  (2547u)     /* (16.5-0.05)*154.83 */
#define BTRCTR_SYS_BATTERY_A2B_DOWN_VOLT                (1308u)     /* (8.5 -0.05)*154.83 */

#if (BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_MODE_D_ENABLE)
#define BTRCTR_SYS_BATTERY_A2D_DOWN_VOLT                (2469u)     /* (16.0-0.05)*154.83 */
#define BTRCTR_SYS_BATTERY_A2D_UP_VOLT                  (1664u)     /* (10.8V  -0.05)*154.83 */

#define BTRCTR_SYS_BATTERY_D2A_DOWN_VOLT                (1541u)     /* (10.0-0.05)*154.83 */
#define BTRCTR_SYS_BATTERY_D2B_UP_VOLT                  (2547u)     /* (16.5-0.05)*154.83 */
#endif 

#define BTRCTR_SYS_BATTERY_B2A_DOWN_VOLT                (2469u)     /* (16.0-0.05)*154.83 */
#define BTRCTR_SYS_BATTERY_B2A_UP_VOLT                  (1386u)     /* (9V  -0.05)*154.83 */

#define	BTRCTR_SYS_BATTERY_C2B_DOWN_VOLT				(2702u)		/* (17.5-0.05)*154.83 */
#define	BTRCTR_SYS_BATTERY_C2B_UP_VOLT					(1076u)		/* (7V  -0.05)*154.83 */


#define	BTRCTR_SYS_BATTERY_B2C_UP_VOLT					(2779u)		/* (18  -0.05)*154.83 */
#define	BTRCTR_SYS_BATTERY_B2C_DOWN_VOLT				(999u)		/* (6.5V-0.05)*154.83 */

#define	BTRCTR_SYS_THRESHOLD_LOW_BATTERY_IN				(999u)      /* (6.5V-0.05)*154.83 */
#define	BTRCTR_SYS_THRESHOLD_LOW_BATTERY_OUT        	(1076u)     /* (7V  -0.05)*154.83 */
#define BTRCTR_THRESHOLD_HIGH_BATTERY_IN                (2856u)     /* (18.5V-0.05)*154.83 */
#define BTRCTR_THRESHOLD_HIGH_BATTERY_OUT               (2779u)     /* (18V -0.05)*154.83 */

/******************************/
#define	BTRCTR_LOAD_THRESHOLD_LOW_BATTERY_IN			(uint16)(1386u)            /*9V*/
#define	BTRCTR_LOAD_THRESHOLD_LOW_BATTERY_OUT        	(uint16)(1463u)            /*9.5V*/

/*Step Motor  Battery,,, used for CANNet in C62X  */
#define	BTRCTR_LOAD_BATTERY_B2A_UP_VOLT				    (BTRCTR_SYS_BATTERY_B2A_UP_VOLT)
#define	BTRCTR_LOAD_BATTERY_B2A_DOWN_VOLT			    (BTRCTR_SYS_BATTERY_B2A_DOWN_VOLT)

#define	BTRCTR_LOAD_BATTERY_A2B_UP_VOLT				    (BTRCTR_SYS_BATTERY_A2B_UP_VOLT)
#define	BTRCTR_LOAD_BATTERY_A2B_DOWN_VOLT			    (BTRCTR_SYS_BATTERY_A2B_DOWN_VOLT)

//IGON AD
//#define BTRCTR_GetIGONAdValue()                         1
//#define BTRCTR_IGON_VALID_MIN                           (1228u)  /* IGON有效最低AD值 */
//#define BTRCTR_IGON_VALID_MAX                           (2768u)  /* IGON有效最高AD值 */
#endif

/*Battery Value from CAN*/
#if(BTRCTR_ENABLE == BTRCTR_CANVOLENABLE)

#define BTRCTR_GetCanBatteryVoltageValue                CAN_GetBatteryVoltageValue

#define CeBTRCTR_w_BATT_RES_VALUE                       (400U)      /*unit (K Ohm)*/
#define CeBTRCTR_w_GND_RES_VALUE                        (93U)       /*unit (K Ohm)*/
#define CeBTRCTR_u_ReferenceVol                         (5U)        /*unit: V*/
#define CeBTRCTR_u_ADCResolution                        (1023U)     /*8bit:256U   10bit:1024U  12bit:4096U */
#define CeBTRCTR_w_Volt2ADPara                          (uint32)((CeBTRCTR_u_ADCResolution * CeBTRCTR_w_GND_RES_VALUE) / ((CeBTRCTR_w_GND_RES_VALUE + CeBTRCTR_w_BATT_RES_VALUE)  * CeBTRCTR_u_ReferenceVol))

#define BTRCTR_VOLTAGE2AD(TempVoltageValue)             (uint16)((TempVoltageValue * CeBTRCTR_w_Volt2ADPara) / 10U)/*��ѹתADֵ*/
#define CANVOLT2REALVOL(TempCanVoltageValue)            (uint16)(TempCanVoltageValue + 30U)/*���ߵ�ѹת(��ʵ��ѹ*10)*/
#define CANVOLTAGE2AD(TempCanVoltageValue)              (uint16)(BTRCTR_VOLTAGE2AD((CANVOLT2REALVOL(TempCanVoltageValue))))/*���ߵ�ѹתADֵ*/

#endif
/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Table Definition
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/

#endif
/*EOF*/
