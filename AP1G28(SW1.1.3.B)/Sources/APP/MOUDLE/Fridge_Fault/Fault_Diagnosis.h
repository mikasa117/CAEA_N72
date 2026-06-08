/*******************************************************************************
||  File Name: Fault_Diagnosis.h
||  Description: Header file for AUTOSAR Fridge Fault
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

#ifndef FRIDGE_DIAGNOSIS_H
#define FRIDGE_DIAGNOSIS_H
#include "CAEA_Types.h"
#include "stdint.h"
#include "Typedef.h"
#include "Platform_Types.h"
#include "stdbool.h"
/*******************************************************************************
||    Other Header File Inclusion
||******************************************************************************/ 

/*******************************************************************************
||    Macro Definition
||******************************************************************************/
#define FLT_TEST_FAULTCombind()                     ((FAULT_Combined) != 0)
#define FLT_TEST_COMP_UNDERVOL()                    (((FAULT_Combined)&((uint32)0x01<<FLT_F_COMP_UNDER_VOL)) != 0)  
#define FLT_TEST_COMP_OVERCURRENT()                 (((FAULT_Combined)&((uint32)0x01<<FLT_F_COMP_OVER_CURRENT)) != 0)   
#define FLT_TEST_COMP_OVERTEMP()                    (((FAULT_Combined)&((uint32)0x01<<FLT_F_COMP_OVER_TEMP)) != 0) 
#define FLT_TEST_FAN_FAULT()                        (((FAULT_Combined)&((uint32)0x01<<FLT_F_FAN_FAULT)) != 0)  
#define FLT_TEST_HEAT_FILM_FAULT()                  (((FAULT_Combined)&((uint32)0x01<<FLT_F_HEAT_FILM_FAULT)) != 0)  
#define FLT_TEST_HEAT_STRIP_FAULT()                 (((FAULT_Combined)&((uint32)0x01<<FLT_F_HEAT_STRIP_FAULT)) != 0)  
#define FLT_TEST_LINER_TEMPSENSOR()                 (((FAULT_Combined)&((uint32)0x01<<FLT_F_LINER_TEMP_SENSOR)) != 0) 

/* DQ 4/16 */
#define FLT_TEST_COMP_OVERVOL()                     (((FAULT_Combined)&((uint32)0x01<<FLT_F_COMP_OVER_VOL)) != 0) 
#define FLT_TEST_COMP_STARTUP_FAIL()                (((FAULT_Combined)&((uint32)0x01<<FLT_F_COMP_STARTUP_FAIL)) != 0) 
#define FLT_TEST_FAN_UC_FAULT()                     (((FAULT_Combined)&((uint32)0x01<<FLT_F_FAN_UC_FAULT)) != 0) 
#define FLT_TEST_HEAT_FILM_UC_FAULT()               (((FAULT_Combined)&((uint32)0x01<<FLT_F_HEAT_FILM_UC_FAULT)) != 0) 
#define FLT_TEST_HEAT_STRIP_UC_FAULT()              (((FAULT_Combined)&((uint32)0x01<<FLT_F_HEAT_STRIP_UC_FAULT)) != 0) 
#define FLT_TEST_CONDENSER_TEMP_SENSOR()            (((FAULT_Combined)&((uint32)0x01<<FLT_F_CONDENSER_TEMP_SENSOR)) != 0) 
#define FLT_TEST_WLED_OVER_CURRENT()                (((FAULT_Combined)&((uint32)0x01<<FLT_F_WLED_OVER_CURRENT)) != 0) 
#define FLT_TEST_WLED_UNDER_CURRENT()               (((FAULT_Combined)&((uint32)0x01<<FLT_F_WLED_UNDER_CURRENT)) != 0) 
#define FLT_TEST_ALED_OVER_CURRENT()                (((FAULT_Combined)&((uint32)0x01<<FLT_F_ALED_OVER_CURRENT)) != 0) 
#define FLT_TEST_ALED_UNDER_CURRENT()               (((FAULT_Combined)&((uint32)0x01<<FLT_F_ALED_UNDER_CURRENT)) != 0) 
#define FLT_TEST_UVLED_OVER_CURRENT()               (((FAULT_Combined)&((uint32)0x01<<FLT_F_UVLED_OVER_CURRENT)) != 0) 
#define FLT_TEST_UVLED_UNDER_CURRENT()              (((FAULT_Combined)&((uint32)0x01<<FLT_F_UVLED_UNDER_CURRENT)) != 0) 
#define FLT_TEST_HALL_UNDER_VOL_FAULT()             (((FAULT_Combined)&((uint32)0x01<<FLT_F_HALL_UNDER_VOL_FAULT)) != 0) 
#define FLT_TEST_HALL_OVER_VOL_FAULT()              (((FAULT_Combined)&((uint32)0x01<<FLT_F_HALL_OVER_VOL_FAULT)) != 0) 
#define FLT_TEST_PCB_OVER_TEMP()                    (((FAULT_Combined)&((uint32)0x01<<FLT_F_PCB_OVER_TEMP)) != 0) 

/* DQ 4/28 */
#define FLT_TEST_COMP_OVER_PHASE_CURRENT()          (((FAULT_Combined)&((uint32)0x01<<FLT_F_COMP_OVER_PHASE_CURRENT)) != 0) 
#define FLT_TEST_COMP_LACK_PHASE_CURRENT()          (((FAULT_Combined)&((uint32)0x01<<FLT_F_COMP_LACK_PHASE_CURRENT)) != 0) 
#define FLT_TEST_COMP_OVER_SPEED()                  (((FAULT_Combined)&((uint32)0x01<<FLT_F_COMP_OVER_SPEED)) != 0) 
#define FLT_TEST_COMP_UNDER_SPEED()                 (((FAULT_Combined)&((uint32)0x01<<FLT_F_COMP_UNDER_SPEED)) != 0) 
#define FLT_TEST_COMP_STALL()                       (((FAULT_Combined)&((uint32)0x01<<FLT_F_COMP_STALL)) != 0) 

/*******************************************************************************
||    Enum Definition
||******************************************************************************/
typedef unsigned char (*FLT_TEST_FP)(void);
/*******************************************************************************
||    Typedef Definition
||******************************************************************************/
typedef enum {
    FLT_F_COMP_UNDER_VOL = 0,       /* 压缩机供电电压欠压故障 */
    FLT_F_COMP_OVER_VOL,            /* 压缩机供电电压过压故障 4/16 */
    FLT_F_COMP_OVER_CURRENT,        /* 压缩机过流故障 */
    FLT_F_COMP_OVER_TEMP,           /* 压缩机过热故障 */
    FLT_F_COMP_OVER_PHASE_CURRENT,  /* 压缩机相电流过流故障，内部故障 4/28 */
    FLT_F_COMP_LACK_PHASE_CURRENT,  /* 压缩机相电流缺相故障，内部故障 4/28 */
    FLT_F_COMP_OVER_SPEED,          /* 压缩机超速故障，内部故障 4/28 */
    FLT_F_COMP_UNDER_SPEED,         /* 压缩机低速故障，内部故障 4/28 */
    FLT_F_COMP_STALL,               /* 压缩机堵转故障，内部故障 4/28 */
    FLT_F_COMP_STARTUP_FAIL,        /* 压缩机启动失败故障，内部故障 4/28 */
    FLT_F_FAN_FAULT,                /* 风扇过流故障 */
    FLT_F_FAN_UC_FAULT,             /* 风扇欠流故障 4/16 */
    FLT_F_HEAT_FILM_FAULT,          /* 加热膜过流故障 */
    FLT_F_HEAT_FILM_UC_FAULT,       /* 加热膜欠流故障 4/16 */
    FLT_F_HEAT_STRIP_FAULT,         /* 加热丝过流故障 */
    FLT_F_HEAT_STRIP_UC_FAULT,      /* 加热丝欠流故障 4/16 */
    FLT_F_LINER_TEMP_SENSOR,        /* 内胆处感温探头故障 */
    FLT_F_CONDENSER_TEMP_SENSOR,    /* 冷凝器感温探头故障 4/16 */
    FLT_F_WLED_OVER_CURRENT,        /* 制冷照明灯过流故障 */
    FLT_F_WLED_UNDER_CURRENT,       /* 制冷照明灯欠流故障 */
    FLT_F_ALED_OVER_CURRENT,        /* 制热照明灯过流故障 4/16 */
    FLT_F_ALED_UNDER_CURRENT,       /* 制热照明灯欠流故障 4/16 */
    FLT_F_UVLED_OVER_CURRENT,       /* 杀菌灯过流故障 4/16 */
    FLT_F_UVLED_UNDER_CURRENT,      /* 杀菌灯欠流故障 4/16 */   
    FLT_F_HALL_UNDER_VOL_FAULT,     /* 霍尔传感器供电电压欠压故障 */
    FLT_F_HALL_OVER_VOL_FAULT,      /* 霍尔传感器供电电压过压故障 4/16 */
    FLT_F_PCB_OVER_TEMP,            /* 板载温度过高故障 */
    FLT_ID_MAX
} FAULT_ID_T;

typedef struct {
    boolean    bTestEn;
    boolean    bFailed;
    boolean    bPreFailed;
    boolean    bFaultInject;
    uint32     uw16DebounceCnt;
    uint32     uw16ThresholdCnt;
    uint32     uw16ThresholdCnt_R;
    uint32     uw16RecoverCnt;
    uint32     uw16RecoverTargetCnt;
    FLT_TEST_FP fpTestRoutine;
} FAULT_STATE_T;
/*******************************************************************************
||    Global variables Declaration
||******************************************************************************/

/*******************************************************************************
||    Extern variables and functions declaration
||******************************************************************************/
extern uint32 FAULT_Combined;
extern void FridgeFault_Detection_MainFunction(void);
extern void FridgeFault_Init(void);
extern void FridgeFault_Clear(void);

/* 压缩机内部故障检测 */
/*  // 电压阈值设置
extern void voltageProtectThresholdSet(float boVol_min, float boVol_max, uint16_t boVol_cnt, float runVol_min, float runVol_max, uint16_t runVol_cnt);
// 电压保护开关设置
extern void voltageProtectSet(bool isOpen);
// 功率保护开关  p.s. 当电压保护为开时，功率保护开关才有作用;当电压保护为关时，功率保护恒关 
extern void voltagePowerProtectSet(bool isOpen);    */

// 电流阈值设置
extern void currentProtectThresholdSet(float cur_max, uint16_t curOver_cnt, float cur_min, uint16_t curShort_cnt);
// 电流保护开关设置
extern void currentProtectSet(bool isOpen);
// 转速阈值设置
extern void speedProtectThresholdSet(uint16_t speed_min, uint16_t speed_max, uint16_t speed_cnt);
// 转速保护开关设置
extern void speedProtectSet(bool isOpen);
// 堵转阈值设置
extern void stallProtectThresholdSet(uint16_t speedErr_min, float curErr_max, uint16_t stallErr_cnt);
// 堵转保护开关设置
extern void stallProtectSet(bool isOpen);

// 获取错误信息
uint32_t getErrorInfo();

// 电压阈值设置
extern void voltageProtectThresholdSet(float boVol_min, float boVol_max, uint16_t boVol_cnt, float runVol_min, float runVol_max, uint16_t runVol_cnt);
// 电压保护开关设置
extern void voltageProtectSet(bool isOpen);
// 功率保护开关  p.s. 当电压保护为开时，功率保护开关才有作用;当电压保护为关时，功率保护恒关 
extern void voltagePowerProtectSet(bool isOpen); 

#endif /* FRIDGE_DIAGNOSIS_H */
