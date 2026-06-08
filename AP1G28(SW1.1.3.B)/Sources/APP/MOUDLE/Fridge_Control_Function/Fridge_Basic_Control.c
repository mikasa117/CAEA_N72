/*******************************************************************************
||  File Name: Fridge_Basic_Control.c
||  Description: Implementation of the AUTOSAR Fridge Control Function
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
#include "Fridge_Basic_Control.h"
#include "Fault_Diagnosis.h"
#include "RTE_APP.h"
#include "Fridge_Application_Config.h"
#include <stdint.h>
#include "stdbool.h"
#include "DID_Callback.h"
#include "STD_EepM.h"
#include "NmStack_Types.h"
#include "CanNm.h"
#include "Fault_Diagnosis.h"
#include "motor.h"
#include "HwIO.h"
#include "YTM32B1ME0.h"
#include "amb_cfg.h"
#include "Mcal_App.h"
/*******************************************************************************
||    Macro Definition
||******************************************************************************/

/*******************************************************************************
||    Enum Definition
||******************************************************************************/

/*******************************************************************************
||    Typedef Definition
||******************************************************************************/


typedef enum {
    FridgeSM_Init			= 0, 
    FridgeSM_Cool			= 1, 
    FridgeSM_Heat			= 2, 
    FridgeSM_Fault			= 3, 
    FridgeSM_Sleep		= 4,
    FridgeSM_WorkStaeOff	= 5, 
    FridgeSM_Idle			= 6, 
} Fridge_StateMachineType;

typedef enum {
    FridgeHeatSM_Init		= 0, 
    FridgeHeatSM_Run		= 1, 
    FridgeHeatSM_Stop		= 2, 
    FridgeHeatSM_Fault	= 3, 
    FridgeHeatSM_RunFro   = 4, 
} FridgeHeat_StateMachineType;

typedef enum {
    FridgeCoolSM_Init		= 0, 
    FridgeCoolSM_Run		= 1, 
    FridgeCoolSM_Stop		= 2, 
    FridgeCoolSM_Fault	= 3, 
    FridgeCoolSM_RunFro   = 4, 
    FridgeCoolSM_Restart   = 5, 
    FridgeCoolSM_Start   = 6,
} FridgeCool_StateMachineType;

typedef enum 
{
    FRIDGE_COOL_MODE = 0x96,   /* 制冷模式 */
    FRIDGE_HEAT_MODE = 0xA5    /* 制热模式 */
} FridgeModeType;

typedef struct
{
    uint16 FridgeAppDataPresence;
	FridgeModeType FridgeModeStroed;
	uint8 FridgeHeatTemoretureStroed;
	uint8 FridgeCoolTemoretureStroed;
	uint8 FridgeWorkstate;   
	uint8 FridgeQuickSetStroed;
	uint8 FridgeUVLed;
    uint8 Current_Mode_SourceStroed;
    uint8 FridgeUVLedWorkTimeSetStroed;
    uint8 FridgeDoorWarnTimeSetStroed;
    uint8 ContinueWorkTimeSetStroed;
    uint8 ContinueWorkSw;
	/*off vehilce */

	
}FridgeStoreInfo_Type;

typedef union _c_FridgeAppStore_bufTag
{
  uint8 _c[91];
  FridgeStoreInfo_Type FridgeStoreInfoTmp;
} _c_FridgeAppStore_buf;



/*UV led*/
uint8 FridgeUVLedSM;
uint8 FridgeUVLedState;
#define FridgeUVLedSM_Init (uint8)0
#define FridgeUVLedSM_Start (uint8)1
#define FridgeUVLedSM_Run (uint8)2
#define FridgeUVLedSM_Pause (uint8)3
#define FridgeUVLedSM_Off (uint8)4
#define FridgeUVLedSM_Failure (uint8)5
   
#define FridgeApplSleepMaxTime 600    /*3s*/
#define FridgeApplTaskcyc 5     /*5ms */
#define FridgeApplSleepMaxCnt (FridgeApplSleepMaxTime/FridgeApplTaskcyc)

/**/
Fridge_StateMachineType FridgeSMGlo;
//uint8 FridgeTargetTempteureCurrent;
static _c_FridgeAppStore_buf FridgeAppStore_buf;
uint8 FridgeApplSleepFlag;
uint16 FridgeApplSleepCnt;

/*heat*/
#define FridgeHeat_DeltaTempture 1//3

#define FridgeHeat_ContiWorkTimeMax  30/*minites*/
#define FridgeHeat_ContiWorkcntMax (FridgeHeat_ContiWorkTimeMax*60*1000/FridgeApplTaskcyc)
uint32 FridgeHeat_ContiWorkCnt;

#define FridgeHeat_FrozenTimeMax 5   /*minites*/
#define FridgeHeat_FrozencntMax (FridgeHeat_FrozenTimeMax*60*1000/FridgeApplTaskcyc)
uint32 FridgeHeat_FrozenkCnt;

#define FridgeHeat_HeatMaxFault 5
uint8 FridgeHeat_FaultCnt;

FridgeHeat_StateMachineType FridgeHeat_SMGlo;

/*Cool*/
#define FridgeCool_DeltaTempture 1//3

#define FridgeCool_ContiWorkTimeMax  20/*minites*/
#define FridgeCool_ContiWorkcntMax (FridgeCool_ContiWorkTimeMax*60*1000/FridgeApplTaskcyc)
uint32 FridgeCool_ContiWorkCnt;

#define FridgeCool_FrozenTimeMax 5   /*minites*/
#define FridgeCool_FrozencntMax (FridgeCool_FrozenTimeMax*60*1000/FridgeApplTaskcyc)
uint32 FridgeCool_FrozenkCnt;

#define FridgeCool_CoolMaxFault 5
uint8 FridgeCool_FaultCnt;

FridgeCool_StateMachineType FridgeCool_SMGlo;

/* Compress */
#define FridgeComp_FieldWeakOpen TRUE
#define FridgeComp_FieldWeakClose FALSE
#define FridgeComp_FieldWeakOpenTimeMax  20  /*20s*/
#define FridgeComp_FieldWeakOpencntMax  (FridgeComp_FieldWeakOpenTimeMax*1000/FridgeApplTaskcyc)
uint32 FridgeComp_FieldWeakCnt;

/* 启动上油策略 */
#define FridgeComp_StartupTimeMax  20  /*20s*/
#define FridgeComp_StartupcntMax  (FridgeComp_FieldWeakOpenTimeMax*1000/FridgeApplTaskcyc)
#define FridgeComp_StartupCmdTimeMax  5  /*50s*/
#define FridgeComp_StartupCmdcntMax  (FridgeComp_FieldWeakOpenTimeMax*1000/FridgeApplTaskcyc)
uint32 FridgeComp_Startupcnt;
uint16 FridgeComp_StartupCmd = 2600;
uint32 FridgeComp_StartupCmdcnt;

/* Heat Strip */
#define FridgeStrip_WorkTemp   55   /*15℃+40*/

#define FridgeStrip_WorkTimeMax   20   /*minites*/
#define FridgeStrip_WorkcntMax (FridgeStrip_WorkTimeMax*60*1000/FridgeApplTaskcyc)
#define FridgeStrip_StopTimeMax   5   /*minites*/
#define FridgeStrip_StopcntMax (FridgeStrip_StopTimeMax*60*1000/FridgeApplTaskcyc)
uint8 FridgeStrip_Enable_Flag = 0;
uint8 FridgeStrip_Work_Flag = 1; /* 口宽加热丝周期工作标志位 */
uint32 FridgeStrip_Work_Count;
uint32 FridgeStrip_Stop_Count;
uint32 FridgeStrip_Delay1h_Count;

/* 压缩机重启策略 */
#define FridgeCool_StartupTimeMax 10   /*s*/
#define FridgeCool_StartupcntMax (FridgeCool_StartupTimeMax*1000/FridgeApplTaskcyc)
uint32 FridgeCool_StartupCnt;

#define FridgeCool_StartupErrorTimeMax 2   /*s*/
#define FridgeCool_StartupErrorcntMax (FridgeCool_StartupErrorTimeMax*1000/FridgeApplTaskcyc)
uint8 FridgeCool_StartupErrorFlag;
uint32 FridgeCool_StartupErrorCnt;

#define FridgeCool_CompReStartTime 20   /*启动失败重启次数*/
#define FridgeCool_CompReStartTimeMax 10   /*s*/
#define FridgeCool_CompReStartcntMax (FridgeCool_CompReStartTimeMax*1000/FridgeApplTaskcyc)
uint8 FridgeCool_CompRestartFlag;
uint32 FridgeCool_CompRestartCnt;
static uint8 uVrhcuOffReas = 0;



/******************************************************** */
typedef enum {
    Index_HealWire			= 0,  	
    Index_Fan,			  			
    Index_TotalNum
} Fridge_StateMachineIndexType;

typedef unsigned char (*FridgePeriSMFunc)(void);
typedef struct {
    uint16 FridgePeriErrCntThre;
    uint16 FridgePeriFaultCntThre;
    FridgePeriSMFunc fpPeriRoutine_Fault1;
    FridgePeriSMFunc fpPeriRoutine_Fault2;
    FridgePeriSMFunc fpPeriRoutine_Enable;
    FridgePeriSMFunc fpPeriRoutine_Disable;
} FridgePeriSM_ActionType;

#define FridgePeriErrCntTime 2000    /*2s*/
#define FridgePeriErrCntTimeCnt (FridgeApplSleepMaxTime/FridgeApplTaskcyc)

uint8 FLT_TEST_HEAT_STRIP_FAULT_Warp(void);
uint8 FLT_TEST_HEAT_STRIP_UC_FAULT_Warp(void);
uint8 FLT_TEST_FAN_FAULT_Warp(void);
uint8 FLT_TEST_FAN_UC_FAULT_Warp(void);

FridgePeriSM_ActionType FridgePeriSM_Action[Index_TotalNum]=
{
    {FridgePeriErrCntTimeCnt,3,FLT_TEST_HEAT_STRIP_FAULT_Warp,FLT_TEST_HEAT_STRIP_UC_FAULT_Warp,FridgeAppl_Heater_Strip_Ctrl_Enable,FridgeAppl_Heater_Strip_Ctrl_Disable},
    {FridgePeriErrCntTimeCnt,3,FLT_TEST_FAN_FAULT_Warp,FLT_TEST_FAN_UC_FAULT_Warp,FridgeAppl_Fan_Ctrl_Enable,FridgeAppl_Fan_Ctrl_Disable}
};

typedef enum {
    FridgePeriSM_Init			= 0, 
    FridgePeriSM_Run			= 1, 
    FridgePeriSM_Stop			= 2, 
    FridgePeriSM_Recovery		= 3, 
    FridgePeriSM_Fault		    = 4,
    FridgePeriSM_Idle			= 5, 
} Fridge_PeriStateMachineType;

Fridge_PeriStateMachineType FridgePeriSMGlo[Index_TotalNum];
uint8 FridgePeriRequest[Index_TotalNum];
uint16 FridgePeriErrCnt[Index_TotalNum];
uint16 FridgePeriFaultCnt[Index_TotalNum];

void FridgePeriSMAppl_Init(void);
void FridgePeriApplCtrl_Mainfunction(void);



/*IO control*/
Fridge_OutControlStateType Fridge_OutControlState[OutputControlObj_MaxNum];


typedef Std_ReturnType (*IoControlFuncVoid)(void);
typedef Std_ReturnType (*IoControlFunc)(uint16 iopara);

typedef struct {
    IoControlFunc fpIoControl_Enable;
    IoControlFuncVoid fpIoControl_Disable;
} IoControl_ActionType;



Std_ReturnType CompressorControlEnable(uint16 IoControlPara);
Std_ReturnType CompressorControlDisable(void);

IoControl_ActionType FridgeOutputControl_Action[OutputControlObj_MaxNum]=
{
    /*OutputControlObj_Compressor*/{CompressorControlEnable,CompressorControlDisable},
    /*OutputControlObj_ALed*/{FridgeAppl_ALed_Ctrl_Enable,FridgeAppl_ALed_Ctrl_Disable},
    /*OutputControlObj_WLed*/{FridgeAppl_WLed_Ctrl_Enable,FridgeAppl_WLed_Ctrl_Disable},
    /*OutputControlObj_UvLed*/{FridgeAppl_UVLed_Ctrl_Enable,FridgeAppl_UVLed_Ctrl_Disable},
    /*OutputControlObj_Fan*/{FridgeAppl_Fan_Ctrl_Enable,FridgeAppl_Fan_Ctrl_Disable},
    /*OutputControlObj_HeatWire*/{FridgeAppl_Heater_Strip_Ctrl_Enable,FridgeAppl_Heater_Strip_Ctrl_Disable},
    /*OutputControlObj_HeatFilm*/{FridgeAppl_Heater_Film_Ctrl_Enable,FridgeAppl_Heater_Film_Ctrl_Disable}
};

void FridgeApp_IoControlInit(void);

InputControl_StateType InputControl_State[InputControlObj_MaxNum];

/*CoolExecute*/
#define CoolStartStep1Timer     1000u/FridgeApplTaskcyc     //5ms Task
#define CoolStartStep2Timer     300u/FridgeApplTaskcyc      //5ms Task
#define CoolStartStop1Timer     35000u/FridgeApplTaskcyc    //5ms Task
#define CoolStartStop2Timer     1000u/FridgeApplTaskcyc     //5ms Task
#define CoolStartStop3Timer     200u/FridgeApplTaskcyc      //5ms Task

FridgeCoolExecute_StateMachineType FridgeCoolExecute_SMGlo;

typedef enum {
    FridgeCoolExecute_Run	  =0xA5u, 
    FridgeCoolExecute_Stop  =0x96u,
} FridgeCompressor_StateType;

FridgeCompressor_StateType FridgeCompressor_Request;

FridgeCoolExecute_StateMachineType FridgeCoolExecute_SMGlo;
static uint16 CoolExecuteStartCnt;

FridgeFaultType FridgeErrStSingal = 0u;

/*******************************************************************************
||    Global variables Declaration
||******************************************************************************/
/*calibration data*/
volatile const uint16 FridgeApplCompressorStartSpeed=3000;
volatile const uint16 FridgeApplCompressorStopSpeed=2700;
volatile const uint16 FridgeApplCompressorFwSpeed=3200;
volatile const uint16 FridgeApplCompressorSpeed=3000;//3000;
volatile const uint16 FridgeApplUVLed=50;
volatile const uint16 FridgeApplFanCtrl=100;
volatile const uint16 FridgeApplWireCtrl=100;
volatile const uint16 FridgeHeaterFilmCtrl=100;
volatile const uint16 FridgeWLedCtrlCtrl=50;
volatile const uint16 FridgeALedCtrlCtrl=50;



uint8 FridgeModeSt_Flag;
uint8 FridgeDoorStatus_Flag;
uint32 Count_DoorWarn;  /* 门未关报警计数器 */
uint8 FridgeDoorWarnTime_Flag;
sint16 FridgeHeatTempReq;
sint16 FridgeCoolTempReq;
sint16 FridgeTEMP;
sint16 FridgeCompTemp;
uint8 Current_Mode_Source;
uint8 FridgeCoolTempSet;
uint8 FridgeHeatTempSet;

#define CompressOnDelayTimeMin  1//2  /*1 minites*/
#define CompressOnDelayTime   (CompressOnDelayTimeMin*60*1000/FridgeApplTaskcyc)
uint8 CompressOnDelayFlag;
uint32 CompressOnDelayCnt;

void FridgeApp_DiagnosticsInit(void);
//uint8 FirstOpenFridge_Flag; 
/*******************************************************************************
||    static local variables Declaration
||******************************************************************************/

/*******************************************************************************
||    static Local Functions Declaration
||******************************************************************************/
static uint8 FridgeCtrl_CANSignal_Control(void);
static uint8 FridgeCtrl_Fault_Diagnosis(void);
static void FridgeCtrl_Status_Feedback_Function(void);
static uint8 FridgeCtrl_Door_Status_Feedback_Function(void);
sint16 FridgeCtrl_Temp_Feedback_Function(void);
sint16 FridgeCtrl_CompTemp_Feedback_Function(void);
void FridgeMode_ReadbackLastInfo(FridgeStoreInfo_Type* StoreInfopapra);
void FridgeMode_WritebackLastInfo(FridgeStoreInfo_Type* StoreInfopapra);
void FridgeMode_StoreCurrentInfo(FridgeStoreInfo_Type* StoreInfopapra);
Std_ReturnType FridgeMode_HeatContitionCheck(void);
void FridgeAppl_HeatExecute(bool ExecutePara);
void FridgeAppl_HeatDiagnostic(void);
void FridgeAppl_CoolExecute(bool ExecutePara);
void FridgeAppl_CoolDiagnostic(void);
Std_ReturnType FridgeMode_ReadCurrentTempreture(uint8* TemprePara);
Std_ReturnType FridgeMode_CoolContitionCheck(void);
uint8 FridgeMode_SleepContitionCheck(void);
uint8 FridgeMode_Extern_SleepContitionCheck(void);
void FridgeMode_HeatInit(void);
void FridgeApplHeat_Mainfunction(void);
void FridgeMode_CoolInit(void);
void FridgeApplCool_Mainfunction(uint8 CoolCmdPara);
void FridgeSMAppl_Init(void);
void FridgeApplCtrl_Mainfunction(void);
void FridgeCtrl_Memory_Init(void);
Std_ReturnType FridgeWork_StatusContitionCheck(void);
void FridgeCtrl_CanSignalInit(void);

static void FridgeCtrl_CanSingalDeal_SwitchControl(void);
static void FridgeCtrl_CanSingalDeal_CoolingorHeatingMode(void);
static void FridgeCtrl_CanSingalDeal_Door(void);
static void FridgeCtrl_CanSingalDeal_QuickMode(void);
static void FridgeCtrl_CanSingalDeal_UV(void);
static void FridgeCtrl_CanSingalDeal_GetOffCar(void);
static void FridgeCtrl_CanSingalDeal_AbnormalTermination(void);

uint8 FridgeCtrl_Heat_Strip_Control(void);

/*******************************************************************************
||    Extern variables and functions declaration
||******************************************************************************/

/********************************** Fridge Initialization **********************************/
/*******************************************************************************
*Function    	    : void FridgeCtrl_Initialization(void)
*ReturnValue 	    : void
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : None
*Description		: Fridge Basic Control Init Function
|******************************************************************************/
extern volatile uint32 _syscoun;
extern volatile uint32 syscount;
extern volatile uint32 CompTaskCnt;
extern void motor_start(void);    
extern uint32_t getErrorInfo(); 
extern void motor_stop(void);  
extern void motor_speed(int32_t speed);
extern void fieldWeakSet(bool isOpen);
extern struct state_params gs;
extern int32_t g_fb_rpm;    /* 经过滤波后的压缩机反馈转速 */
bool1 COMP_Enable_Flag;
extern void motor_foc_work(uint32_t *state);
extern uint8_t g_nvhstop;

 void Usr_pwmStart(void)
{
    eTMR0->SYNC |= eTMR_SYNC_CLDOK_MASK;
    eTMR0->CHMASK = 0x0000000;

    eTMR0->CH[2].VAL0 = EPWM_PERIOD - (EPWM_PERIOD>>1);
    eTMR0->CH[2].VAL1 = EPWM_PERIOD + (EPWM_PERIOD>>1);
    eTMR0->CH[0].VAL0 = EPWM_PERIOD - (EPWM_PERIOD>>1);
    eTMR0->CH[0].VAL1 = EPWM_PERIOD + (EPWM_PERIOD>>1);
    eTMR0->CH[4].VAL0 = EPWM_PERIOD - (EPWM_PERIOD>>1);
    eTMR0->CH[4].VAL1 = EPWM_PERIOD + (EPWM_PERIOD>>1);
    eTMR0->SYNC |= eTMR_SYNC_LDOK_MASK;
}

 void Usr_pwmStop(void)
{
	
    eTMR0->SYNC |= eTMR_SYNC_CLDOK_MASK;
    eTMR0->CHMASK = 0x00000FF;
    eTMR0->CH[2].VAL0 = EPWM_PERIOD - (EPWM_PERIOD>>1);
    eTMR0->CH[2].VAL1 = EPWM_PERIOD + (EPWM_PERIOD>>1);
    eTMR0->CH[0].VAL0 = EPWM_PERIOD - (EPWM_PERIOD>>1);
    eTMR0->CH[0].VAL1 = EPWM_PERIOD + (EPWM_PERIOD>>1);
    eTMR0->CH[4].VAL0 = EPWM_PERIOD - (EPWM_PERIOD>>1);
    eTMR0->CH[4].VAL1 = EPWM_PERIOD + (EPWM_PERIOD>>1);
    eTMR0->SYNC |= eTMR_SYNC_LDOK_MASK;
}

void FridgeCtrl_CanSignalInit(void)
{    
    /* 有记忆功能要求的信号，在上电初始化后应按照记忆值反馈 */
    RTE_APP_Can_Write_FridgeHeatTempSt(FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeHeatTemoretureStroed-74);  /* 上电初始化制热设定温度为0x1：35℃ */  
    RTE_APP_Can_Write_FridgeCoolTempSt(FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeCoolTemoretureStroed-33);  /* 上电初始化制冷温度为0x7：0℃ */  
    if(0xA5 == FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeModeStroed)      
    {
        RTE_APP_Can_Write_FridgeModeSt(0x02u);  /* 上电初始化工作模式为：0x2：制热模式 */
    }
    else    
    {
        RTE_APP_Can_Write_FridgeModeSt(0x01u);  /* 上电初始化工作模式为：0x1：制冷模式 */
    }
    RTE_APP_Can_Write_FridgeDoorWarnTimeSt(FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeDoorWarnTimeSetStroed);  /* 上电初始化门未关报警时间设置为0x1：1min */

    /* 其他信号按照默认值反馈 */
    RTE_APP_Can_Write_FridgeHeatActSt(0x10u);   /* 上电初始化实时温度为0℃ */
    RTE_APP_Can_Write_FridgeUVLedSt(0x02u);     /* 上电初始化杀菌状态为0x2：未杀菌 */ 
    RTE_APP_Can_Write_FridgeUVLedWorkSt(0x01u); /* 上电初始化杀菌剩余时长为0x1：0min */ 
    RTE_APP_Can_Write_FridgeDoorSt(0x02u);      /* 上电初始化门状态为0x2：门关闭 */            
    RTE_APP_Can_Write_FridgeDoorWarnSt(0x01u);  /* 上电初始化门未关报警状态反馈为0x1：正常 */ 
    RTE_APP_Can_Write_ContinueWorkTimeSt(0x00u);/* 上电初始化离车持续工作时间设置反馈为0x0：0h */ 
    RTE_APP_Can_Write_FridgeQFunSt(0x00u);      /* 上电初始化快捷模式反馈为0x0 */ 
    RTE_APP_Can_Write_FridgeWorkSt(0x02u);      /* 上电初始化冰箱工作状态反馈为0x2：冰箱关闭 */         
    RTE_APP_Can_Write_FridgeErrSt(0x00u);       /* 上电初始化冰箱故障状态为0x0：正常 */
}

void FridgeCtrl_Initialization(void)
{
    FridgeSMAppl_Init();
    // FridgeCtrl_Memory_Init();
    FridgeAppl_Init();
    FridgeFault_Init();
	_syscoun=0;
	syscount=0;
	CompTaskCnt=0;
	Usr_pwmStop();
    // FridgeCtrl_CanSignalInit();
	
}

/********************************** Fridge Application Functions **********************************/
/*******************************************************************************
*Function    	    : void FridgeCtrl_Basic_Control_Function(void)
*ReturnValue 	    : void
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : None
*Description		: Fridge Basic Control Function 
|******************************************************************************/
void FridgeCtrl_Basic_Control_Function(void)
{
    /* 冰箱内部状态获取 */
    FridgeCtrl_Status_Feedback_Function();
    /* 冰箱故障诊断 */
    FridgeCtrl_Fault_Diagnosis();
    /* 冰箱制冷/加热功能执行状态机 */
    FridgeApplCtrl_Mainfunction();
    /* 冰箱照明灯功能 */
    FridgeCtrl_Headlamp_Control();
    /* 冰箱信号交互 */
    FridgeCtrl_CANSignal_Control();
    /* */
    //FridgePeriApplCtrl_Mainfunction();
}


/********************************** Fridge CANSignal Control **********************************/
/*******************************************************************************
*Function    	    : uint8 FridgeCtrl_CANSignal_Control(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Energy save mode request status
*Description		: CAN Signal control for Fridge
||******************************************************************************/
uint8 FridgeCtrl_CANSignal_Control(void)
{
    /* 冰箱开关控制 */
    FridgeCtrl_CanSingalDeal_SwitchControl();

    if(1u == FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeWorkstate)/*Fridge ON*/
    {
        /* 冰箱制冷/制热模式选择 */
        FridgeCtrl_CanSingalDeal_CoolingorHeatingMode();
    }
    else/*Fridge OFF*/
    {
        ;
    }

    /* 冰箱门未关提示 */
    FridgeCtrl_CanSingalDeal_Door();

    /* 冰箱快捷模式 */
    FridgeCtrl_CanSingalDeal_QuickMode();

    /*冰箱杀菌模式*/
    FridgeCtrl_CanSingalDeal_UV();

    /* 冰箱离车运行 */
    FridgeCtrl_CanSingalDeal_GetOffCar();

    /* 冰箱异常关闭 */
    FridgeCtrl_CanSingalDeal_AbnormalTermination();

    return 0;
}

/******************** Fridge CAN data processing Function **********************/
/*******************************************************************************
*Function    	    : uint8 FridgeCtrl_CanSingalDeal_SwitchControl(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : None
*Description		: Fridge Switch function & signal processing function   冰箱开关控制 
||******************************************************************************/
void FridgeCtrl_CanSingalDeal_SwitchControl(void)
{
    if(1u == RTE_NET_Can_Timeout_0x3ED_Msg())/*0=timeout, 1=normal*/
    {
        if(0x1 == RTE_APP_Can_Read_FridgeWorkReq())  /*ON*/
        {
            FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeWorkstate = 1u;    
        }
        else if(0x2 == RTE_APP_Can_Read_FridgeWorkReq())  /*off*/
        {
            FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeWorkstate = 2u;
        }
        else  /*invalid or reserved*/
        {
            /*keep last state*/
        }  
    }
    else
    {
        FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeWorkstate = 2u;
    }
     
    /*send response*/
    if(0u == uVrhcuOffReas)
    {
        ;
    }
    else
    {
        FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeWorkstate = 2u;
    }

    RTE_APP_Can_Write_FridgeWorkSt(FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeWorkstate);
    
}
/*******************************************************************************
*Function    	    : uint8 FridgeCtrl_CanSingalDeal_CoolingorHeatingMode(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : None
*Description		: Fridge Cooling/Heating Mode function & signal processing function   冰箱制冷/制热模式选择 
||******************************************************************************/
void FridgeCtrl_CanSingalDeal_CoolingorHeatingMode(void)
{
    if(0x1 == RTE_APP_Can_Read_FridgeModeReq()) /*code*/
    {
        FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeModeStroed = 0x96;
    }
    else if(0x2 == RTE_APP_Can_Read_FridgeModeReq()) /*heat*/
    {
        FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeModeStroed = 0xA5;
    }
    else /*invalid or reseved*/
    {

    }
    /* 冰箱制冷工作温度调节 */
    if((RTE_APP_Can_Read_FridgeCoolTempReq() >= 0x1) && (RTE_APP_Can_Read_FridgeCoolTempReq() <= 0x1B))
    {
        FridgeCoolTempSet = RTE_APP_Can_Read_FridgeCoolTempReq();
        FridgeCoolTempSet += 33;  /* -7+40 */
        FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeCoolTemoretureStroed = FridgeCoolTempSet;
    }
    else /*out of range*/
    {

    }

    /* 冰箱加热工作温度调节 */
    if((RTE_APP_Can_Read_FridgeHeatTempReq() >= 0x1) && (RTE_APP_Can_Read_FridgeHeatTempReq() <= 0x10))
    {
        FridgeHeatTempSet = RTE_APP_Can_Read_FridgeHeatTempReq();
        FridgeHeatTempSet += 74;  /* +34+40 */
        FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeHeatTemoretureStroed = FridgeHeatTempSet;
    }
    else /*out of range*/
    {

    }
    /*send response*/
    /*mode*/
    if (FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeModeStroed == 0x96)
    {
        RTE_APP_Can_Write_FridgeModeSt(1);
    }
    else if (FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeModeStroed == 0xA5)
    {
        RTE_APP_Can_Write_FridgeModeSt(2);
    }
    else
    {

    }
    /*cool tempreture*/
    if (FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeCoolTemoretureStroed>=33)
    {
        RTE_APP_Can_Write_FridgeCoolTempSt(FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeCoolTemoretureStroed-33);
    }
    else
    {

    }
    /*heat tempreture*/
    if (FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeHeatTemoretureStroed>=74)
    {
        RTE_APP_Can_Write_FridgeHeatTempSt(FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeHeatTemoretureStroed-74);
    }
    else
    {

    }
    
}

/*******************************************************************************
*Function    	    : uint8 FridgeCtrl_CanSingalDeal_Door(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : None
*Description		: Fridge Door function & signal processing function   冰箱门未关提示 
||******************************************************************************/
void FridgeCtrl_CanSingalDeal_Door(void)
{
    if(0x1 == RTE_APP_Can_Read_FridgeDoorWarnTimeSet())
    {
        FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeDoorWarnTimeSetStroed = 1u;
    }
    else if(0x2 == RTE_APP_Can_Read_FridgeDoorWarnTimeSet())
    {
        FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeDoorWarnTimeSetStroed = 5u;
    }
    else if(0x3 == RTE_APP_Can_Read_FridgeDoorWarnTimeSet())
    {
        FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeDoorWarnTimeSetStroed = 10u;
    }
    else if(0x4 == RTE_APP_Can_Read_FridgeDoorWarnTimeSet())
    {
        FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeDoorWarnTimeSetStroed = 0xA5u;  /*never warning*/
    }
    else  /*invalid*/
    {

    }

    if (\
        (FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeDoorWarnTimeSetStroed>=1)&&\
        (FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeDoorWarnTimeSetStroed<=10)\
       )
    {  
        if(1u == FridgeDoorStatus_Flag)
        {
            if(Count_DoorWarn >= FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeDoorWarnTimeSetStroed*60*200)
            {
               FridgeDoorWarnTime_Flag=0xA5;
            }
            else 
            {
                Count_DoorWarn++; 
                FridgeDoorWarnTime_Flag=0x0;
            }               
        }
        else
        {
            Count_DoorWarn = 0u;
            FridgeDoorWarnTime_Flag=0x0;
        }
    }
    else 
    {
        Count_DoorWarn = 0u;
        FridgeDoorWarnTime_Flag=0x0;
    }
    /*send response*/
    /*setting time */
    if (FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeDoorWarnTimeSetStroed == 1u)
    {
        RTE_APP_Can_Write_FridgeDoorWarnTimeSt(0x1);
    }
    else if (FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeDoorWarnTimeSetStroed == 5u)
    {
        RTE_APP_Can_Write_FridgeDoorWarnTimeSt(0x2);
    }
    else if (FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeDoorWarnTimeSetStroed == 10u)
    {
        RTE_APP_Can_Write_FridgeDoorWarnTimeSt(0x3);
    }
    else if (FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeDoorWarnTimeSetStroed == 0xA5u)
    {
        RTE_APP_Can_Write_FridgeDoorWarnTimeSt(0x0);
    }
    else
    {

    }
    /*door warning*/
    if (FridgeDoorWarnTime_Flag==0xA5)
    {
        RTE_APP_Can_Write_FridgeDoorWarnSt(0x02u);
    }
    else
    {
        RTE_APP_Can_Write_FridgeDoorWarnSt(0x1);
    }   
}

/*******************************************************************************
*Function    	    : uint8 FridgeCtrl_CanSingalDeal_QuickMode(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : None
*Description		: Fridge Quick Mode function & signal processing function   冰箱快捷模式 
||******************************************************************************/
void FridgeCtrl_CanSingalDeal_QuickMode(void)
{

    if((RTE_APP_Can_Read_FridgeQFunReq() >= 0x1) && (RTE_APP_Can_Read_FridgeQFunReq() <= 0x5))
    {
        RTE_APP_Can_Write_FridgeQFunSt(RTE_APP_Can_Read_FridgeQFunReq());
    }
    else
    {

    }
}

/*******************************************************************************
*Function    	    : uint8 FridgeCtrl_CanSingalDeal_UV(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : None
*Description		: Fridge UV function & signal processing function   冰箱杀菌模式 
||******************************************************************************/

void FridgeCtrl_UVLedSMInit(void)
{
    FridgeUVLedSM=FridgeUVLedSM_Init;
    FridgeDoorStatus_Flag=0x0; /*invalid*/
    FridgeUVLedState=0;  /*UV led is off*/
}

/*******************************************************************************
*Function    	    : uint8 FridgeCtrl_CanSingalDeal_UV(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : None
*Description		: Fridge UV function & signal processing function   冰箱杀菌模式 
||******************************************************************************/
void FridgeCtrl_CanSingalDeal_UV(void)
{
    static uint32 Count_FridgeUVLedWorkSt=0;
    static uint8 Prev_UVLedReq=0;
    uint8 Current_UVLedReq=0;      /*invalid*/
    Current_UVLedReq = RTE_APP_Can_Read_FridgeUVLedReq();

    switch(FridgeUVLedSM)
    {
        case FridgeUVLedSM_Init:
            if (Current_UVLedReq==1) /*on*/
            {
                FridgeUVLedSM=FridgeUVLedSM_Start;
            }
            else if(Current_UVLedReq==2) /*off*/
            {
                FridgeUVLedSM=FridgeUVLedSM_Off;
            }
            else
            {
                /*maintain current state*/
            }
            break;
        case FridgeUVLedSM_Start:
            Count_FridgeUVLedWorkSt=(FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeUVLedWorkTimeSetStroed)*60*200;/*minites to sec,sec to 5ms count*/
            FridgeUVLedSM=FridgeUVLedSM_Run;
            break;
        case FridgeUVLedSM_Run:
            if(Current_UVLedReq==2) /*off*/
            {
                FridgeUVLedSM=FridgeUVLedSM_Off;
                /* 关闭杀菌灯 */
                //FridgeAppl_UVLed_Ctrl_Disable();
                FridgeApp_OutputControl(OutputControlObj_UvLed,ControlType_NormalRelease,0u);
            }
            else
            {
                if (FridgeDoorStatus_Flag != 1)   /*not open*/
                {
                    /* 打开杀菌灯 */
                    //FridgeAppl_UVLed_Ctrl_Enable();
                    FridgeApp_OutputControl(OutputControlObj_UvLed,ControlType_Normalrequest,FridgeApplUVLed);
                    if (Count_FridgeUVLedWorkSt>0)
                    {
                        Count_FridgeUVLedWorkSt--;
                    }
                    else /*complete*/
                    {
                        FridgeUVLedSM=FridgeUVLedSM_Off;
                        /* 关闭杀菌灯 */
                        //FridgeAppl_UVLed_Ctrl_Disable();
                        FridgeApp_OutputControl(OutputControlObj_UvLed,ControlType_NormalRelease,0u);
                    }
                }
                else   /*pause*/
                {
                    /* 杀菌过程中打开门，则进入杀菌暂停模式 */
                    FridgeUVLedSM=FridgeUVLedSM_Pause;
                }
            }                
            break;
        case FridgeUVLedSM_Pause:
            /* 门关闭，则杀菌继续计时 */
            if (FridgeDoorStatus_Flag != 1)
            {
                FridgeUVLedSM=FridgeUVLedSM_Run;
            }
            else
            {
                /* 关闭杀菌灯 */
                //FridgeAppl_UVLed_Ctrl_Disable();
                FridgeApp_OutputControl(OutputControlObj_UvLed,ControlType_NormalRelease,0u);
            }
            break;
        case FridgeUVLedSM_Off:
            if ((Current_UVLedReq==1) && (Prev_UVLedReq!=1)) /*on, Signal switching*/
            {
                FridgeUVLedSM=FridgeUVLedSM_Start;
            }
            else
            {
                /* 关闭杀菌灯 */
                Count_FridgeUVLedWorkSt=0;
                //FridgeAppl_UVLed_Ctrl_Disable();
                FridgeApp_OutputControl(OutputControlObj_UvLed,ControlType_NormalRelease,0u);
            }
            break;
        case FridgeUVLedSM_Failure:
            FridgeUVLedSM=FridgeUVLedSM_Init; 
            break;
        default:
            FridgeUVLedSM=FridgeUVLedSM_Init;
            break;
    }

    /*send response*/
    /*FridgeUVLedSt*/
    if (FridgeUVLedState==1)  /*on*/
    {
        RTE_APP_Can_Write_FridgeUVLedSt(0x1);
    }
    else
    {
        /* 杀菌暂停时，杀菌状态反馈：杀菌中 */
        if(FridgeUVLedSM == FridgeUVLedSM_Pause)
        {
            RTE_APP_Can_Write_FridgeUVLedSt(0x1);
        }
        else
        {
            RTE_APP_Can_Write_FridgeUVLedSt(0x2);
        }
    }
    /*FridgeUVLedWorkSt*/
    if (Count_FridgeUVLedWorkSt==0)
    {
        RTE_APP_Can_Write_FridgeUVLedWorkSt(0x1u);
    }
    else
    {
        RTE_APP_Can_Write_FridgeUVLedWorkSt((uint8)((Count_FridgeUVLedWorkSt-1) / 12000u + 2u));
    }

    Prev_UVLedReq = Current_UVLedReq;
}

/*******************************************************************************
*Function    	    : uint8 FridgeCtrl_CanSingalDeal_GetOffCar(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : None
*Description		: Fridge is running away from the vehicle function & signal processing function   冰箱离车运行 
||******************************************************************************/
void FridgeCtrl_CanSingalDeal_GetOffCar(void)
{

    if((RTE_APP_Can_Read_ContinueWorkTimeSet() >= 0x1) && (RTE_APP_Can_Read_ContinueWorkTimeSet() <= 0xF0))
    {
        RTE_APP_Can_Write_ContinueWorkTimeSt(RTE_APP_Can_Read_ContinueWorkTimeSet());
    }
    else
    {

    }
}

/*******************************************************************************
*Function    	    : uint8 FridgeCtrl_CanSingalDeal_AbnormalTermination(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : None
*Description		: Fridge Abnormal Termination function & signal processing function   冰箱异常关闭 
||******************************************************************************/
void FridgeCtrl_CanSingalDeal_AbnormalTermination(void)
{
    if(0x2u != RTE_APP_Can_Read_DcdcOperSts())
    {
        uVrhcuOffReas = 1u;
    }
    else
    {
        uVrhcuOffReas = 0u;
    }

    if(130u <= FridgeCtrl_CompTemp_Feedback_Function()) /*comp>=90℃(130) */
    {
        uVrhcuOffReas = 3u;
    }
    else if((115u >= FridgeCtrl_CompTemp_Feedback_Function()) && (30u <= FridgeCtrl_CompTemp_Feedback_Function())) /*comp<=75℃(115) && comp>=-10℃(30) */
    {
        uVrhcuOffReas = 0u;
    }
    else
    {
        ;
    }  

    if((1u == FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeWorkstate) && (FridgeFaultSM_Normal == FridgeCtrl_Fault_Diagnosis()))
    { 
        RTE_APP_Can_Write_VrhcuOffReas(uVrhcuOffReas);
    }
    else
    {
       ;
    }
}
    
/********************************** Fridge Diagnosis Function **********************************/
/*******************************************************************************
*Function    	    : uint8 FridgeCtrl_Fault_Diagnosis(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Energy save mode request status
*Description		: Fridge Fault Diagnosis
||******************************************************************************/
uint8 FridgeCtrl_Fault_Diagnosis(void)
{
      /* 冰箱关闭状态下不反馈故障 */
    if(1u == FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeWorkstate) //Open
    {
        if(TRUE != BTRCTR_GetSysBatteryModeAStatus())
        {/*The supply voltage exceeds the range 冰箱供电电压超出范围*/
            FridgeErrStSingal = FridgeFaultSM_PowerSupplyVolFault;
            /* 冰箱所有功能关闭 */
        }
        else if(TRUE == FLT_TEST_LINER_TEMPSENSOR())
        {/*Internal temperature sensing head malfunction 冰箱内部感温头故障*/
            FridgeErrStSingal = FridgeFaultSM_InsideTempSensorFault;
            /* 杀菌消毒功能保持开启 */
            /* 冰箱其他功能关闭 */
        }
        else if(TRUE == FLT_TEST_PCB_OVER_TEMP())
        {/*Controller temperature exceeds the range 冰箱控制器温度超出范围故障*/
            FridgeErrStSingal = FridgeFaultSM_ControllerTempFault;
            /* 冰箱制冷、制热功能关闭 */
            /* 冰箱其他功能保持开启 */
        }
        else if(TRUE == FLT_TEST_COMP_STARTUP_FAIL())
        {/*Compressor startup failed 冰箱压缩机启动失败故障*/
            FridgeErrStSingal = FridgeFaultSM_CompressorStartsFault;
        }
        else if((TRUE == FLT_TEST_HEAT_FILM_FAULT()) || (TRUE == FLT_TEST_HEAT_FILM_UC_FAULT()))
        {/*heating film Fault 冰箱加热膜故障*/
            FridgeErrStSingal = FridgeFaultSM_HeatingFilmFault;
        }
        else if(TRUE == FLT_TEST_FAN_FAULT() || (TRUE == FLT_TEST_FAN_UC_FAULT()))//
        {/*Fan current exceeds the range 冰箱风扇电流超出范围故障*/
            FridgeErrStSingal = FridgeFaultSM_FanCurrentFault;
             /* 冰箱制冷功能关闭 */
            /* 冰箱快捷模式部分功能（制冷相关）关闭 */
            /* 冰箱其他功能保持开启 */
        }
        else if((TRUE == FLT_TEST_UVLED_OVER_CURRENT()) || (TRUE == FLT_TEST_UVLED_UNDER_CURRENT()))
        {/*UV LED Fault 杀菌灯故障*/
            FridgeErrStSingal = FridgeFaultSM_UVLampFault;
            /* 不能使用杀菌功能 */
        }
        else if((TRUE == FLT_TEST_WLED_OVER_CURRENT()) || (TRUE == FLT_TEST_WLED_UNDER_CURRENT()))
        {/*Cold LED Fault 冰箱制冷照明灯故障*/
            FridgeErrStSingal = FridgeFaultSM_CoolLampFault;
            /* 不影响功能使用，冰箱模型页面显示照明灯故障 */
        }
        else if((TRUE == FLT_TEST_ALED_OVER_CURRENT()) || (TRUE ==FLT_TEST_ALED_UNDER_CURRENT()))
        {/*Heating LED Fault 冰箱制热照明灯故障*/
            FridgeErrStSingal = FridgeFaultSM_HeatLampFault;
            /* 不影响功能使用，冰箱模型页面显示照明灯故障 */
        }
        else if((TRUE == FLT_TEST_HEAT_STRIP_FAULT()) || (TRUE == FLT_TEST_HEAT_STRIP_UC_FAULT()))
        {/*heating wire Fault 冰箱加热丝故障*/
            FridgeErrStSingal = FridgeFaultSM_HeatingWireFault;
            /* 不影响功能使用，制冷时可能会产生冷凝水 */
        }
        else if((TRUE == FLT_TEST_HALL_UNDER_VOL_FAULT()) || (TRUE == FLT_TEST_HALL_OVER_VOL_FAULT()))
        {/*Hall Fault 冰箱霍尔传感器故障*/
            FridgeErrStSingal = FridgeFaultSM_HallSensorFault;
        }
        else if((TRUE == FLT_TEST_COMP_OVER_SPEED()) || (TRUE == FLT_TEST_COMP_UNDER_SPEED()))
        {/*Compressor speed exceeds the range 冰箱压缩机转速超出范围故障*/
            FridgeErrStSingal = FridgeFaultSM_CompressorSpeedFault;
        }
        else if((TRUE == FLT_TEST_COMP_OVER_PHASE_CURRENT()))
        {/*Controller overcurrent 冰箱控制器过流故障*/
            FridgeErrStSingal = FridgeFaultSM_ControllerCurrentFault;
        }
        else if(0)
        {/*Box door motor malfunction 冰箱开门电机故障*/
            FridgeErrStSingal = FridgeFaultSM_DoorMotorFault;
        }
        else if(0)
        {/*reserved*/
            FridgeErrStSingal = FridgeFaultSM_ReservedFault;
        }
        else
        {
            FridgeErrStSingal = FridgeFaultSM_Normal;
        }
    }
    else
    {
        FridgeErrStSingal = FridgeFaultSM_Normal;  
    }

    RTE_APP_Can_Write_FridgeErrSt(FridgeErrStSingal);

    return FridgeErrStSingal;
}


/********************************** Fridge Status Feedback **********************************/
/*******************************************************************************
*Function    	    : void FridgeCtrl_Status_Feedback_Function(void)
*ReturnValue 	    : void
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : None
*Description		: Fridge Status Feedback
|******************************************************************************/
void FridgeCtrl_Status_Feedback_Function(void)
{
    /* 冰箱内部状态获取 */
    FridgeCtrl_Door_Status_Feedback_Function();
    FridgeCtrl_Temp_Feedback_Function();
    FridgeCtrl_CompTemp_Feedback_Function();

    /* 冰箱内部状态反馈 */
    RTE_APP_Can_Write_FridgeDoorSt(FridgeDoorStatus_Flag);
    RTE_APP_Can_Write_VrhcuRefrAcpTemp(FridgeCtrl_CompTemp_Feedback_Function()-30);     /* 向上偏移10：+40-30（通讯矩阵最低温度为-10：0x0） */
    RTE_APP_Can_Write_FridgeHeatActSt(FridgeCtrl_Temp_Feedback_Function()-24);     /* 向上偏移16：+40-24（通讯矩阵最低温度为-15：0x1） */
}

/*******************************************************************************
*Function    	    : uint8 FridgeCtrl_Door_Status_Feedback_Function(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Door Status Feedback
||******************************************************************************/
uint8 FridgeCtrl_Door_Status_Feedback_Function(void)
{
    /* 冰箱门状态 */
    FridgeDoorStatus_Flag = FridgeAppl_FridgeDoor_Status();

    return FridgeDoorStatus_Flag;
}

/*******************************************************************************
*Function    	    : sint16 FridgeCtrl_Temp_Feedback_Function(void)
*ReturnValue 	    : sint16
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : sint16					    :Fridge child lock request status
*Description		: Fridge Current Temperature Feedback
||******************************************************************************/
sint16 FridgeCtrl_Temp_Feedback_Function(void)
{
    uint8 F1FC_u_DataPtr[20] ={0u};
	
    /* 冰箱温度 */
    FridgeTEMP = FridgeAppl_FridgeTEMP_Calculate();   /* AD反馈值为精确到小数点后一位0.1，例如100代表10.0℃ */
    FridgeTEMP = (FridgeTEMP/10) + 40;   /* 冰箱温度换算成整数位的实际温度后，向上偏移40 */

    EEPM_AppReadBlock(EEP_BLOCK_DIDF1FC_ID, &F1FC_u_DataPtr[0]);

    if(0xA5==FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeModeStroed)
    {
		FridgeTEMP -= 1;
        if((F1FC_u_DataPtr[5] == 0xA5u) && (F1FC_u_DataPtr[6] == 0x96u))
        {
            FridgeTEMP += (F1FC_u_DataPtr[7]-6u);
        }
        else
        {
            ;
        }
    }
    else if(0x96==FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeModeStroed)
    {
		if(FridgeTEMP >= 40)
		{
			FridgeTEMP -= 0;
		}
		else
		{
			FridgeTEMP -= 1;
		}

        if((F1FC_u_DataPtr[2] == 0xA5u) && (F1FC_u_DataPtr[3] == 0x96u))
        {
            FridgeTEMP += (F1FC_u_DataPtr[4]-6u);
        }
        else
        {
            ;
        }
    }
    else
    {
		;
    }

    return FridgeTEMP;
}

/*******************************************************************************
*Function    	    : sint16 FridgeCtrl_CompTemp_Feedback_Function(void)
*ReturnValue 	    : sint16
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : sint16					    :Fridge child lock request status
*Description		: Fridge Compressor Temperature Feedback
||******************************************************************************/
sint16 FridgeCtrl_CompTemp_Feedback_Function(void)
{
    /* 冷凝器温度 */
    FridgeCompTemp = FridgeAppl_FridgeCompTemp_Calculate();   /* AD反馈值为精确到小数点后一位0.1，例如100代表10.0℃ */
    FridgeCompTemp = (FridgeCompTemp/10) + 40;   

    return FridgeCompTemp;
}


/********************************** Fridge Headlamp Control **********************************/
/*******************************************************************************
*Function    	    : void FridgeCtrl_Headlamp_Control(void)
*ReturnValue 	    : void
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : void					    :Energy save mode request status
*Description		: Fridge Control for Headlamp
||******************************************************************************/
uint8 FridgeCtrl_Headlamp_Control(void)
{
    uint8 FridgeDoorStatus_Tmp;
    uint8 LED_FaultDetectEnable_Flag;

    FridgeDoorStatus_Tmp = FridgeAppl_FridgeDoor_Status();
    if(1u == FridgeDoorStatus_Tmp)
    {
        if(0xA5==FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeModeStroed)
        {
             /* 关闭白色灯 */
             //FridgeAppl_WLed_Ctrl_Disable();
             FridgeApp_OutputControl(OutputControlObj_WLed,ControlType_NormalRelease,0u);
             /* 加热模式，开启黄色灯 */
             //FridgeAppl_ALed_Ctrl_Enable();    
             FridgeApp_OutputControl(OutputControlObj_ALed,ControlType_Normalrequest,FridgeALedCtrlCtrl);
        }
        else
        {
            /* 关闭黄色灯 */
            //FridgeAppl_ALed_Ctrl_Disable();
            FridgeApp_OutputControl(OutputControlObj_ALed,ControlType_NormalRelease,0u);
            /* 制冷模式，开启白色灯 */
            //FridgeAppl_WLed_Ctrl_Enable();
            FridgeApp_OutputControl(OutputControlObj_WLed,ControlType_Normalrequest,FridgeWLedCtrlCtrl);
        }

        LED_FaultDetectEnable_Flag = 1;
    }
    else 
    {
        /* 关闭黄色灯 */
        //FridgeAppl_ALed_Ctrl_Disable();
        FridgeApp_OutputControl(OutputControlObj_ALed,ControlType_NormalRelease,0u);
        /* 关闭白色灯 */
        //FridgeAppl_WLed_Ctrl_Disable();
        FridgeApp_OutputControl(OutputControlObj_WLed,ControlType_NormalRelease,0u);

        LED_FaultDetectEnable_Flag = 0;
    }

    return LED_FaultDetectEnable_Flag;
}

/********************************** Fridge Heat Strip Control **********************************/
/*******************************************************************************
*Function    	    : void FridgeCtrl_Heat_Strip_Control(void)
*ReturnValue 	    : void
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : void					    :Energy save mode request status
*Description		: Fridge Control for Heat Strip
||******************************************************************************/
uint8 FridgeCtrl_Heat_Strip_Control(void)
{
    uint8 HeatStrip_FaultDetectEnable_Flag;

    if((0x96==FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeModeStroed) && (1u == FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeWorkstate))
    {
        /* 口宽加热丝功能 */
        /* 冰箱开启后，进入制冷模式，判断传感器温度<15℃，则开启加热丝 */
        if(FridgeCtrl_Temp_Feedback_Function() < FridgeStrip_WorkTemp)
        {
            FridgeStrip_Enable_Flag = 1;
        }
        else
        {
            // FridgeStrip_Enable_Flag = 0;
        }

        /* 开启加热丝后，加热丝工作20min，停止5min，周期循环，直到退出制冷模式 */
        if(1 == FridgeStrip_Enable_Flag)
        {
            if(1 == FridgeStrip_Work_Flag)
            {  
                if(FridgeStrip_Work_Count >= FridgeStrip_WorkcntMax)
                {
                    FridgeStrip_Work_Flag = 0;
                }
                else
                {
                    FridgeStrip_Work_Count++;
                    //FridgePeriRequest[Index_HealWire]=TRUE;
                    FridgeApp_OutputControl(OutputControlObj_HeatWire,ControlType_Normalrequest,FridgeApplWireCtrl);
                    /* 冰箱故障检测使能 */
                    HeatStrip_FaultDetectEnable_Flag = 1;
                }

                FridgeStrip_Stop_Count = 0;
            }
            else
            {
                if(FridgeStrip_Stop_Count >= FridgeStrip_StopcntMax)
                {
                    FridgeStrip_Work_Flag = 1;
                }
                else
                {
                    FridgeStrip_Stop_Count++;
                    //FridgePeriRequest[Index_HealWire]=FALSE;
                    FridgeApp_OutputControl(OutputControlObj_HeatWire,ControlType_NormalRelease,0u);
                    /* 冰箱故障检测关闭 */
                    HeatStrip_FaultDetectEnable_Flag = 0;
                }

                FridgeStrip_Work_Count = 0;             
            }
        }
        else
        {
            /* 冰箱温度未达到目标温度，则加热丝停止工作 */
            //FridgePeriRequest[Index_HealWire]=FALSE;
            FridgeApp_OutputControl(OutputControlObj_HeatWire,ControlType_NormalRelease,0u);
            FridgeStrip_Work_Flag = 1;
            FridgeStrip_Work_Count = 0;
            FridgeStrip_Stop_Count = 0;

            /* 冰箱故障检测关闭 */
            HeatStrip_FaultDetectEnable_Flag = 0;
        }	
    }
    else
    {
        /* 冰箱关闭或退出制冷模式，则加热丝停止工作 */
        //FridgePeriRequest[Index_HealWire]=FALSE;
        FridgeApp_OutputControl(OutputControlObj_HeatWire,ControlType_NormalRelease,0u);
        FridgeStrip_Work_Flag = 1;
        FridgeStrip_Work_Count = 0;
        FridgeStrip_Stop_Count = 0;

        /* 冰箱故障检测关闭 */
        HeatStrip_FaultDetectEnable_Flag = 0;
    }

    return HeatStrip_FaultDetectEnable_Flag;		
}

/*******************************************************************************
*Function    	    : void FridgeCtrl_Memory_Init(void)
*ReturnValue 	    : void
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : void					    :Energy save mode request status
*Description		: Fridge Control Memory Init
||******************************************************************************/
void FridgeCtrl_Memory_Init(void)
{
    /* 上电初始化，非记忆信号需要切换为默认状态 */
    FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeUVLed = 2u;         /* 杀菌关闭 */
    FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeUVLedWorkTimeSetStroed = 6; /*6 min*/
    Count_DoorWarn = 0u;                                            /* 上电初始化门未关报警状态反馈为0x1：正常 */
	FridgeDoorWarnTime_Flag=0; /*no warning */
    FridgeAppStore_buf.FridgeStoreInfoTmp.ContinueWorkTimeSetStroed = 0u;        /* 上电初始化离车持续工作时间设置反馈为0x0：0h */
    FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeQuickSetStroed = 0u;/* 上电初始化快捷模式反馈为0x0 */ 
    FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeWorkstate = 2u;     /* 冰箱关闭 */
}






void FridgeMode_ReadbackLastInfo(FridgeStoreInfo_Type* StoreInfopapra)
{
	EEPM_AppReadBlock(EEP_BLOCK_Fridge_App_ID,StoreInfopapra);
    if (StoreInfopapra->FridgeAppDataPresence!=0xA55A)
    {
        StoreInfopapra->FridgeAppDataPresence=0xA55A;
        /*define default data  */
        /* 首次开启冰箱 */
        FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeWorkstate = 2u; /*off*/
        StoreInfopapra->FridgeModeStroed = 0x96;
        StoreInfopapra->FridgeCoolTemoretureStroed = 40;        /* 0x7+33(offset) */
        StoreInfopapra->FridgeHeatTemoretureStroed = 75;       /* 0x1+74(offset) */
        StoreInfopapra->FridgeDoorWarnTimeSetStroed = 0x1;      /* DQ 4/14 */
        FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeUVLedWorkTimeSetStroed = 6; /*6 min*/
    }
}
void FridgeMode_WritebackLastInfo(FridgeStoreInfo_Type* StoreInfopapra)
{
	ApplDescWrite_Fridge_App(StoreInfopapra);
}


/*including extern contions and internal fault conditions*/
Std_ReturnType FridgeMode_HeatContitionCheck(void)
{
	Std_ReturnType rettmp=E_OK;
	/*add user code*/
    /* 电源电压9-16V判断，加热膜相关故障判断 */
    if((0x00001000 == FAULT_Combined)||(0x00002000 == FAULT_Combined)||(0x00010000 == FAULT_Combined)||(0x04000000 == FAULT_Combined)||(TRUE != BTRCTR_GetSysBatteryModeAStatus()))
    {
        rettmp = E_NOT_OK;
    }
    else 
    {
        rettmp = E_OK;
    }

	return rettmp;
}

bool1 Heater_Film_Enable_Flag;
void FridgeAppl_HeatExecute(bool ExecutePara)
{
    Heater_Film_Enable_Flag = ExecutePara;

    if(TRUE == ExecutePara)
    {
        /* 加热膜工作 */
        //FridgeAppl_Heater_Film_Ctrl_Enable();
        FridgeApp_OutputControl(OutputControlObj_HeatFilm,ControlType_Normalrequest,FridgeHeaterFilmCtrl);
    }
    else 
    {
        /* 关闭加热膜 */
        //FridgeAppl_Heater_Film_Ctrl_Disable();
        FridgeApp_OutputControl(OutputControlObj_HeatFilm,ControlType_NormalRelease,0u);
    }
}

void FridgeAppl_HeatDiagnostic(void)
{
    /* 根据加热膜反馈电流判断加热膜是否产生过流/短路故障 */
}

void FridgeAppl_CoolExecuteInit(void)
{
    FridgeCoolExecute_SMGlo = FridgeCoolExecuteSM_Init;
    FridgeCompressor_Request=FridgeCoolExecute_Stop;
    CoolExecuteStartCnt=0;
}


void FridgeAppl_CoolExecuteMainfunction(void)
{
    switch (FridgeCoolExecute_SMGlo)
    {
        case FridgeCoolExecuteSM_Init:
            FridgeApp_OutputControl(OutputControlObj_Fan,ControlType_NormalRelease,0u);
            HwIO_COMP_12V_EN_OFF();
            HwIO_MCU_PD_SLPn_Disable();
            FridgeApp_OutputControl(OutputControlObj_Compressor,ControlType_NormalRelease,0u);
            FridgeCoolExecute_SMGlo = FridgeCoolExecuteSM_Stop;
            break;
        case FridgeCoolExecuteSM_StartStep1:
            if (CoolExecuteStartCnt<CoolStartStep1Timer)/*1s*/
            {
                CoolExecuteStartCnt++;
                FridgeApp_OutputControl(OutputControlObj_Fan,ControlType_Normalrequest,FridgeApplFanCtrl);
                HwIO_COMP_12V_EN_ON();
            }
            else
            {
                CoolExecuteStartCnt=0;
                FridgeCoolExecute_SMGlo=FridgeCoolExecuteSM_StartStep2;
            }        
            break;
        case FridgeCoolExecuteSM_StartStep2:
            if (CoolExecuteStartCnt<CoolStartStep2Timer)/*300ms*/
            {
                CoolExecuteStartCnt++;
                FridgeApp_OutputControl(OutputControlObj_Fan,ControlType_Normalrequest,FridgeApplFanCtrl);
                HwIO_COMP_12V_EN_ON();
                HwIO_MCU_PD_SLPn_Enable();
            }
            else
            {
                CoolExecuteStartCnt=0;
                FridgeCoolExecute_SMGlo=FridgeCoolExecuteSM_Run1;
            }  
            break;
        case FridgeCoolExecuteSM_Run1:
            if(FridgeCompressor_Request==FridgeCoolExecute_Run)
            {
                FridgeApp_OutputControl(OutputControlObj_Fan,ControlType_Normalrequest,FridgeApplFanCtrl);
                HwIO_COMP_12V_EN_ON();
                HwIO_MCU_PD_SLPn_Enable();
                FridgeApp_OutputControl(OutputControlObj_Compressor,ControlType_Normalrequest,FridgeApplCompressorStartSpeed);
            }
            else
            {
                FridgeCoolExecute_SMGlo=FridgeCoolExecuteSM_StopStep1;
            }
            break;
        case FridgeCoolExecuteSM_StopStep1:
            if ((CoolExecuteStartCnt<CoolStartStop1Timer)&&(g_fb_rpm>(FridgeApplCompressorStopSpeed+50u))) /*35s*/
            {
                CoolExecuteStartCnt++;
                FridgeApp_OutputControl(OutputControlObj_Compressor,ControlType_Normalrequest,FridgeApplCompressorStopSpeed);
            }
            else
            {
                CoolExecuteStartCnt=0;
                FridgeCoolExecute_SMGlo=FridgeCoolExecuteSM_StopStep2;
            }             
            break;
        case FridgeCoolExecuteSM_StopStep2:
            if (CoolExecuteStartCnt<CoolStartStop2Timer) /*5s*/
            {
                CoolExecuteStartCnt++;
                FridgeApp_OutputControl(OutputControlObj_Compressor,ControlType_NormalRelease,0u);
                //HwIO_MCU_PD_SLPn_Disable();
            }
            else
            {
                CoolExecuteStartCnt=0;
                FridgeCoolExecute_SMGlo=FridgeCoolExecuteSM_StopStep3;
            }     

            break;
        case FridgeCoolExecuteSM_StopStep3:
            if (CoolExecuteStartCnt<CoolStartStop3Timer) /*1s*/
            {
                CoolExecuteStartCnt++;
                FridgeApp_OutputControl(OutputControlObj_Fan,ControlType_NormalRelease,0u);
                HwIO_COMP_12V_EN_OFF();
                FridgeApp_OutputControl(OutputControlObj_Compressor,ControlType_NormalRelease,0u);
                HwIO_MCU_PD_SLPn_Disable();
            }
            else
            {
                CoolExecuteStartCnt=0;
                FridgeCoolExecute_SMGlo=FridgeCoolExecuteSM_Stop;
                CompressOnDelayCnt=CompressOnDelayTime;
            }     
            break;
        case FridgeCoolExecuteSM_Stop:
            if ((FridgeCoolExecute_Run==FridgeCompressor_Request)&&(0u==CompressOnDelayCnt))
            {
                FridgeCoolExecute_SMGlo=FridgeCoolExecuteSM_StartStep1;
                CoolExecuteStartCnt=0;
            }
            else
            {
                FridgeApp_OutputControl(OutputControlObj_Fan,ControlType_NormalRelease,0u);
                HwIO_COMP_12V_EN_OFF();
                HwIO_MCU_PD_SLPn_Disable();
                FridgeApp_OutputControl(OutputControlObj_Compressor,ControlType_NormalRelease,0u);
            }
            break;
        
        default:
            FridgeAppl_CoolExecuteInit();
            break;
    }

    ADC_BAT_BLDC = FridgeAppl_FridgeCompVoltage_Calculate();  /* 根据AD采样回来的电压值进行FOC运算 */
}

void FridgeAppl_CoolExecute(bool ExecutePara)
{
        if (TRUE==ExecutePara)
        {
            FridgeCompressor_Request=FridgeCoolExecute_Run;
        }
        else
        {
            FridgeCompressor_Request=FridgeCoolExecute_Stop;
        }
    #if 0
    if(TRUE == ExecutePara)
    {
        // /* 开启压缩机 */
        // UsrReqCompComd = 1u;
        /* 使能散热风扇 */
		if (CompressOnDelayFlag!=0x96)
		{
            //FridgePeriRequest[Index_Fan]=TRUE;
            FridgeApp_OutputControl(OutputControlObj_Fan,ControlType_Normalrequest,FridgeApplFanCtrl);
            HwIO_COMP_12V_EN_ON();
            // HwIO_VCC_46V_EN_High();
            HwIO_MCU_PD_SLPn_Enable();
            /*
            motor_start();
            motor_speed(3000);
            */
            FridgeApp_OutputControl(OutputControlObj_Compressor,ControlType_Normalrequest,FridgeApplCompressorStartSpeed);
			CompressOnDelayFlag=0xA5;
            COMP_Enable_Flag = TRUE;

            // /* 启动成功后开启弱磁 */
            // if(g_fb_rpm>2000)  /* 反馈转速高于2000rpm */
            // {
                // FridgeComp_FieldWeakCnt++;
                // if(FridgeComp_FieldWeakCnt > FridgeComp_FieldWeakOpencntMax)
                // {
                    // /* 弱磁开启 */
                    // fieldWeakSet(FridgeComp_FieldWeakOpen);
                    // FridgeComp_FieldWeakCnt = FridgeComp_FieldWeakOpencntMax;
                // }                
                // else
                // {
                    // /* 弱磁关闭 */
                    // fieldWeakSet(FridgeComp_FieldWeakClose);
                // }
            // }
            // else
            // {
                // FridgeComp_FieldWeakCnt = 0;
                // /* 弱磁关闭 */
                // fieldWeakSet(FridgeComp_FieldWeakClose);
            // }

        //     /* 启动上油策略 */
        //     if(g_fb_rpm>2000)  /* 反馈转速高于2000rpm */
        //     {
        //         FridgeComp_Startupcnt++;
        //         if(FridgeComp_Startupcnt > FridgeComp_StartupcntMax)
        //         {
        //             /* 2700rpm运行30s后，拉升至目标转速 */
        //             if(FridgeComp_StartupCmd >= 3600)
        //             {
        //                 FridgeComp_StartupCmd = 3600;
        //             }
        //             else
        //             {
        //                 FridgeComp_StartupCmd += 1;
        //             }
        //             motor_speed(FridgeComp_StartupCmd);
        //             FridgeComp_Startupcnt = FridgeComp_StartupcntMax;
        //         }                
        //         else
        //         {
 
        //         }
        //     }
        //     else
        //     {
        //         FridgeComp_Startupcnt = 0;
        //     }
		}
        else
        {

        }
    }
    else 
    {
        // /* 关闭压缩机 */
        // UsrReqCompComd = 0u;
        /* 关闭散热风扇 */
        //FridgePeriRequest[Index_Fan]=FALSE;
        FridgeApp_OutputControl(OutputControlObj_Fan,ControlType_NormalRelease,0u);
        HwIO_COMP_12V_EN_OFF();
	    // HwIO_VCC_46V_EN_Low();
	    HwIO_MCU_PD_SLPn_Disable();
		//motor_stop();
        FridgeApp_OutputControl(OutputControlObj_Compressor,ControlType_NormalRelease,0u);
		if (0xA5==CompressOnDelayFlag)
		{
			CompressOnDelayFlag=0x96;
			CompressOnDelayCnt=0u;
		}
        COMP_Enable_Flag = FALSE;

        FridgeComp_Startupcnt = 0;
    }
    #endif
}

void FridgeAppl_CompressDelay(void)
{   
    /*
	if (0x96==CompressOnDelayFlag)
	{
		if (CompressOnDelayCnt<CompressOnDelayTime)
		{
			CompressOnDelayCnt++;

            FridgeCoolExecute_SMGlo = FridgeCoolExecuteSM_StopStep1;
		}
		else
		{
			CompressOnDelayFlag=0;
			CompressOnDelayCnt=0;

            FridgeFault_Clear();

            FridgeCoolExecute_SMGlo = FridgeCoolExecuteSM_Init;
		}
	}
	else
	{

	}
    */
   if (CompressOnDelayCnt > 0)
   {
        CompressOnDelayCnt--;

        if(5u == CompressOnDelayCnt)
        {
            FridgeFault_Clear();
        }
        else
        {}
   }
   else
   {
    
   }
}

void FridgeAppl_CoolDiagnostic(void)
{
    /* 对压缩机进行实时故障诊断：过流，堵转，开路 */
}

sint16 TemprePara_Tmp;
Std_ReturnType FridgeMode_ReadCurrentTempreture(uint8* TemprePara)
{
	Std_ReturnType rettmp=E_OK;
    // sint16 TemprePara_Tmp;
	/*add user code*/
	TemprePara_Tmp = FridgeCtrl_Temp_Feedback_Function();
    *TemprePara = (uint8_t)TemprePara_Tmp;

	return rettmp;
}

uint32 FridgeFAULT;
uint8 FridgeFault_BatModeA;
uint16 FridgeFault_BatADValue;
Std_ReturnType FridgeMode_CoolContitionCheck(void)
{
	Std_ReturnType rettmp=E_OK;
	/*add user code*/
    /* 电源电压9-16V判断，压缩机相关故障判断 */
    if(((FAULT_Combined > 0x00000000)&&(FAULT_Combined < 0x00001000))||(0x00010000 == FAULT_Combined)||(0x00020000 == FAULT_Combined)||(0x04000000 == FAULT_Combined)||(TRUE != BTRCTR_GetSysBatteryModeAStatus()))
    {
        rettmp = E_NOT_OK;
        FridgeFAULT = FAULT_Combined;
        FridgeFault_BatModeA = BTRCTR_GetSysBatteryModeAStatus();
        FridgeFault_BatADValue = BTRCTR_GetSysBatteryVolt();
    }
    else
    {
        rettmp = E_OK;
    }

	return rettmp;
}

Std_ReturnType FridgeWork_StatusContitionCheck(void)
{
	Std_ReturnType rettmp=E_OK;
	/*add user code*/
    /* 冰箱故障判断 */
    if(TRUE != BTRCTR_GetSysBatteryModeAStatus())
    {
        rettmp = E_NOT_OK;
    }
    else
    {
        rettmp = E_OK;
    }
    
	return rettmp;
}

uint8 FridgeMode_SleepContitionCheck(void)
{
	return FridgeApplSleepFlag;
}

extern uint8 SysM_Get_SysPowerStatus(void);
uint8 FridgeMode_Extern_SleepContitionCheck(void)
{
    Std_ReturnType rettmp=E_OK;
    Nm_StateType  pApplCan_u_NMSt;
    Nm_ModeType   pApplCan_u_NMMode;

	/*add user code*/
    CanNm_GetState(0U,&pApplCan_u_NMSt,&pApplCan_u_NMMode);
    if(pApplCan_u_NMSt != NM_STATE_BUS_SLEEP)
    {
        rettmp = E_NOT_OK;
    }
    else 
    {
        rettmp = E_OK;
    }

    return rettmp;
}
	
void FridgeMode_HeatInit(void)
{
	FridgeHeat_ContiWorkCnt=0;
	FridgeHeat_FrozenkCnt=0;
	if (FridgeHeat_FaultCnt<FridgeHeat_HeatMaxFault)
	{
		FridgeHeat_SMGlo=FridgeHeatSM_Init;
	}
	else
	{
		FridgeHeat_SMGlo=FridgeHeatSM_Fault;
	}
	FridgeAppl_HeatExecute(FALSE);
}

void FridgeApplHeat_Mainfunction(void)
{
	uint8 CurrentTmpreture;

	switch (FridgeHeat_SMGlo)
	{
		case FridgeHeatSM_Init:
			FridgeMode_HeatInit();
			FridgeHeat_SMGlo=FridgeHeatSM_Stop;
			break;
		case FridgeHeatSM_Run:
			if (E_OK==FridgeMode_HeatContitionCheck())
			{
				// if (FridgeHeat_ContiWorkCnt<FridgeHeat_ContiWorkcntMax)
				// {
					FridgeMode_ReadCurrentTempreture(&CurrentTmpreture);
					FridgeHeat_ContiWorkCnt++;
					if (CurrentTmpreture<FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeHeatTemoretureStroed)
					{
						FridgeAppl_HeatExecute(TRUE);			
					}
					else
					{
						/**/
						FridgeHeat_SMGlo=FridgeHeatSM_Stop;
						FridgeAppl_HeatExecute(FALSE);
					}
				// }
				// else
				// {
				// 	FridgeHeat_SMGlo=FridgeHeatSM_RunFro;
				// 	FridgeHeat_FrozenkCnt=0;
				// 	FridgeAppl_HeatExecute(FALSE);
				// }			
			}
			else
			{
				FridgeHeat_SMGlo=FridgeHeatSM_Stop;
				FridgeAppl_HeatExecute(FALSE);
			}
			break;
		case FridgeHeatSM_Stop:
			if (E_OK==FridgeMode_HeatContitionCheck())
			{
				FridgeMode_ReadCurrentTempreture(&CurrentTmpreture);
				if (CurrentTmpreture<(FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeHeatTemoretureStroed-FridgeHeat_DeltaTempture))
				{
					FridgeHeat_ContiWorkCnt=0;
					FridgeHeat_SMGlo=FridgeHeatSM_Run;
				}
				else
				{
					/**/
					FridgeAppl_HeatExecute(FALSE);
				}
			}
			else
			{
                FridgeHeat_SMGlo=FridgeHeatSM_Fault;
				FridgeHeat_FaultCnt++;
				FridgeAppl_HeatExecute(FALSE);
			}
			break;
		case FridgeHeatSM_Fault:
			if (FridgeHeat_FaultCnt<FridgeHeat_HeatMaxFault)
			{
				if (E_OK==FridgeMode_HeatContitionCheck())
				{
					FridgeHeat_SMGlo=FridgeHeatSM_Init;
				}
				else
				{
					/*stay in fault state*/
					FridgeAppl_HeatExecute(FALSE);
				}
			}
			else
			{
				/*never try to work again in this IGN operation*/
			}
			break;
		case FridgeHeatSM_RunFro:
			if (FridgeHeat_FrozenkCnt<FridgeHeat_FrozencntMax)
			{
				FridgeHeat_FrozenkCnt++;
			}
			else
			{
				FridgeHeat_FrozenkCnt=0;
				FridgeHeat_ContiWorkCnt=0;
				FridgeHeat_SMGlo=FridgeHeatSM_Run;
			}
			break;
		default:
			FridgeHeat_SMGlo=FridgeHeatSM_Init;
			break;
	}
	FridgeAppl_HeatDiagnostic();
}

uint8 FridgeSM_RunToRestart = 0;
uint8 FridgeSM_StopToFault = 0;
void FridgeMode_CoolInit(void)
{
	// FridgeCool_ContiWorkCnt=0;
	FridgeCool_FrozenkCnt=0;
	if (FridgeCool_FaultCnt<FridgeCool_CoolMaxFault)
	{
		FridgeCool_SMGlo=FridgeCoolSM_Init;
	}
	else
	{
		FridgeCool_SMGlo=FridgeCoolSM_Fault;
        FridgeSM_StopToFault = 1u;
	}
	FridgeAppl_CoolExecute(FALSE);
    
}

void FridgeApplCool_Mainfunction(uint8 CoolCmdPara)
{
	uint8 CurrentTmpreture;
    
    FridgeAppl_CoolExecuteMainfunction();
    if (CoolCmdPara==TRUE)
    {
        switch (FridgeCool_SMGlo)
        {
            case FridgeCoolSM_Init:
                FridgeMode_CoolInit();
                if(FridgeCoolExecuteSM_Stop == FridgeCoolExecute_SMGlo)
                {
                    FridgeCool_SMGlo=FridgeCoolSM_Stop;
                } 
                break;

            //case FridgeCoolSM_Start:
                //FridgeAppl_CoolExecute(TRUE);


            case FridgeCoolSM_Run:
                if (E_OK==FridgeMode_CoolContitionCheck())
                {
                    // if (FridgeCool_ContiWorkCnt<FridgeCool_ContiWorkcntMax)
                    // {
                        FridgeMode_ReadCurrentTempreture(&CurrentTmpreture);
                        // FridgeCool_ContiWorkCnt++;
                        if (CurrentTmpreture>FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeCoolTemoretureStroed)
                        //if (CurrentTmpreture)
                        {
                            FridgeAppl_CoolExecute(TRUE);	
                            
                            /* 压缩机启动后的10s,检测压缩机转速是否小于1000rpm,是则尝试重启 */	
                            if(FridgeCool_StartupCnt >= FridgeCool_StartupcntMax)
                            {
                                if(g_fb_rpm < 1000)
                                {
                                    if(FridgeCool_StartupErrorCnt >= FridgeCool_StartupErrorcntMax)
                                    {
                                        /* 连续2s检测到压缩机转速小于1000rpm */
                                        FridgeCool_StartupErrorFlag++;
                                        FridgeCool_StartupErrorCnt = 0;
                                        FridgeCool_StartupCnt = 0;
                                        /* 进入重启状态 */
                                        FridgeCool_SMGlo=FridgeCoolSM_Restart;
                                        // FridgeAppl_CoolExecute(FALSE);
                                        FridgeSM_RunToRestart = 1u;
                                    }
                                    else
                                    {
                                        FridgeCool_StartupErrorCnt++;
                                        /* 维持运行状态 */
                                    }
                                }
                                else
                                {
                                    /* 若转速大于1000rpm，则计数器清零 */
                                    FridgeCool_StartupErrorCnt = 0;
                                    /* 维持运行状态 */
                                    if (FridgeApplCompressorSpeed>FridgeApplCompressorStartSpeed)
                                    {
                                        if (FridgeApplCompressorSpeed>=FridgeApplCompressorFwSpeed)
                                        {
                                            gp.fw_en=1;
                                        }
                                        else
                                        {
                                            gp.fw_en=0;
                                        }
                                        //FridgeApp_OutputControl(OutputControlObj_Compressor,ControlType_Normalrequest,FridgeApplCompressorSpeed);
                                        motor_speed(FridgeApplCompressorSpeed);
                                    }
                                }
                            }
                            else
                            {
                                FridgeCool_StartupCnt++;

                            }
            
                        }
                        else
                        {
                            /**/
                            FridgeCool_SMGlo=FridgeCoolSM_Stop;
                            FridgeAppl_CoolExecute(FALSE);
                            FridgeCool_StartupCnt = 0;      /* 只要压缩机停机，就要把启动失败的计数器清零 */
                        }
                    // }
                    // else
                    // {
                    // 	FridgeCool_SMGlo=FridgeCoolSM_RunFro;
                    // 	FridgeCool_FrozenkCnt=0;
                    // 	FridgeAppl_CoolExecute(FALSE);
                    // }	
                    
                }
                else
                {
                    FridgeCool_SMGlo=FridgeCoolSM_Stop;
                    FridgeAppl_CoolExecute(FALSE);
                }
                break;
            case FridgeCoolSM_Stop:
                if (E_OK==FridgeMode_CoolContitionCheck())
                {
                    FridgeMode_ReadCurrentTempreture(&CurrentTmpreture);
                    if (CurrentTmpreture>(FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeCoolTemoretureStroed + FridgeCool_DeltaTempture))
                    //if (CurrentTmpreture)
                    {
                        // FridgeCool_ContiWorkCnt=0;
                        FridgeCool_SMGlo=FridgeCoolSM_Run;
                        FridgeCool_StartupCnt = 0;
                    }
                    else
                    {
                        /**/
                        FridgeAppl_CoolExecute(FALSE);
                    }
                }
                else
                {
                    FridgeCool_SMGlo=FridgeCoolSM_Fault;
                    FridgeCool_FaultCnt++;
                    FridgeAppl_CoolExecute(FALSE);
                    FridgeSM_StopToFault = 1u;
                }
                break;
            case FridgeCoolSM_Fault:
                if(FridgeSM_StopToFault == 1u)
                {
                    //AdcIf_1_ConfigGropChannel();
                    FridgeSM_StopToFault = 0u;
                }
                if (1)//FridgeCool_FaultCnt<FridgeCool_CoolMaxFault)
                {
                    if (E_OK==FridgeMode_CoolContitionCheck())
                    {
                        FridgeCool_SMGlo=FridgeCoolSM_Init;
                    }
                    else
                    {
                        /*stay in fault state*/
                        FridgeAppl_CoolExecute(FALSE);
                    }
                }
                else
                {
                    /*never try to work again in this IGN operation*/
                }
                break;
            case FridgeCoolSM_RunFro:
                if (FridgeCool_FrozenkCnt<FridgeCool_FrozencntMax)
                {
                    FridgeCool_FrozenkCnt++;
                }
                else
                {
                    FridgeCool_FrozenkCnt=0;
                    // FridgeCool_ContiWorkCnt=0;
                    FridgeCool_SMGlo=FridgeCoolSM_Run;
                    FridgeCool_StartupCnt = 0;
                }
                break;
            case FridgeCoolSM_Restart:

                if(FridgeSM_RunToRestart == 1u)
                {
                    AdcIf_1_ConfigGropChannel();
                    FridgeSM_RunToRestart = 0u;
                }
                
                /* 重启次数小于5次 */
                if(1)//FridgeCool_StartupErrorFlag <= FridgeCool_CompReStartTime)
                {
                    /* 间隔5s重启 */
                    if(FridgeCool_CompRestartCnt > FridgeCool_CompReStartcntMax)
                    {
                        CompressOnDelayFlag=0;      /* 进入重启模式还需要再次将延时标志位清零 */
                        CompressOnDelayCnt = 0;
                        FridgeCool_SMGlo=FridgeCoolSM_Run;
                        FridgeCool_StartupCnt = 0;
                        FridgeCool_CompRestartCnt = 0;

                    }
                    else
                    {
                        FridgeCool_CompRestartCnt++;
                        FridgeAppl_CoolExecute(FALSE);
                        #if 0
                        /* 压缩机下电 */
                        HwIO_COMP_12V_EN_OFF();
                        HwIO_VCC_46V_EN_OFF();
                        HwIO_MCU_PD_SLPn_Disable();
                        //motor_stop();
                        FridgeApp_OutputControl(OutputControlObj_Compressor,ControlType_NormalRelease,0u);
                        #endif

                    }
                }
                else
                {
                    // /* 重启次数超过5次,则本次上电压缩机不再启动 */
                    // FridgeCool_SMGlo=FridgeCoolSM_Fault;
                    // FridgeCool_FaultCnt=FridgeCool_CoolMaxFault;
                    // FridgeAppl_CoolExecute(FALSE);

                    // FridgeCool_CompRestartCnt = 0;
                }
                break;
            default:
                FridgeCool_SMGlo=FridgeCoolSM_Init;
                break;
        }
        FridgeAppl_CoolDiagnostic();
    }
    else
    {
        FridgeAppl_CoolExecute(FALSE);
    }
	
}

	
void FridgeSMAppl_Init(void)
{
	FridgeSMGlo=FridgeSM_Init;
	/*sleep*/
	FridgeApplSleepFlag=0;   /*0 means not sleep,1 means sleep*/
	FridgeApplSleepCnt=0;

	/*heat*/
	FridgeHeat_SMGlo=FridgeHeatSM_Init;
	FridgeHeat_FaultCnt=0;
	FridgeMode_HeatInit();

	/*cool*/
	FridgeCool_SMGlo=FridgeCoolSM_Init;
	FridgeCool_FaultCnt=0;
	FridgeMode_CoolInit();
	CompressOnDelayCnt=0;
	CompressOnDelayFlag=0;
    FridgeAppl_CoolExecuteInit();

    /* 压缩机重启策略变量初始化 */
    FridgeCool_StartupCnt=0;
    FridgeCool_StartupErrorFlag=0;
    FridgeCool_StartupErrorCnt=0;
    FridgeCool_CompRestartFlag=0;
    FridgeCool_CompRestartCnt=0;
	
	/* 初始化加热丝允许工作标志位 */
    FridgeStrip_Enable_Flag = 0;
	
	 /*for diagnostics*/
    FridgeApp_DiagnosticsInit();


    /**/
    FridgePeriSMAppl_Init();
    FridgeApp_IoControlInit();
}

uint32 getErrorInfotmp;
void FridgeApplCtrl_Mainfunction(void)
{	
    /* 加热丝功能 */
    FridgeCtrl_Heat_Strip_Control();

	getErrorInfotmp=getErrorInfo();
	FridgeAppl_CompressDelay();
	switch (FridgeSMGlo)
	{
		case FridgeSM_Init:
			/*add user cdoe*/
			FridgeMode_ReadbackLastInfo(&(FridgeAppStore_buf._c[0]));
            /* 上电初始化后，将无需存储的状态手动调整为默认状态 */
            FridgeCtrl_Memory_Init();
            /* 上电初始化完成，EEPROM记忆值读取完成，初始化信号反馈 */
            FridgeCtrl_CanSignalInit();
			FridgeSMGlo=FridgeSM_WorkStaeOff;
			break;
		case FridgeSM_Idle:
			/*add user cdoe*/
			if (E_OK==FridgeMode_Extern_SleepContitionCheck())
			{
				FridgeSMGlo=FridgeSM_Idle;
				if (FridgeApplSleepCnt<FridgeApplSleepMaxCnt)
				{
					FridgeApplSleepCnt++;
				}
				else
				{
					FridgeApplSleepFlag=1;   /*can go to sleep*/
				}
			}
			else
			{
				FridgeSMGlo=FridgeSM_WorkStaeOff;
				FridgeApplSleepCnt=0;
				FridgeApplSleepFlag=0;
			}
			
			break;
		case FridgeSM_Cool:
			/*add user cdoe*/
			/*add user FridgeSM_Heat*/
			if (E_OK==FridgeMode_Extern_SleepContitionCheck())
			{
				FridgeSMGlo=FridgeSM_WorkStaeOff;
				FridgeMode_CoolInit();
			}
			else
			{
				if ((0xA5 == FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeModeStroed) || (2u == FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeWorkstate))   /*heat*/
				{		
                    if (FridgeCoolExecute_SMGlo!=FridgeCoolExecuteSM_Stop)
                    {
                        FridgeApplCool_Mainfunction(FALSE);	
                    }		
                    else
                    {
					    FridgeSMGlo=FridgeSM_WorkStaeOff;
                    }	
                    FridgeMode_CoolInit();
				}
                else if(0x96 == FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeModeStroed)  /*cool*/
                {
                    FridgeApplCool_Mainfunction(TRUE);
                }
                else
                {

                }
			}	
			break;
		case FridgeSM_Heat:
			/*add user FridgeSM_Heat*/
			if (E_OK==FridgeMode_Extern_SleepContitionCheck())
			{
				FridgeSMGlo=FridgeSM_WorkStaeOff;
				FridgeMode_HeatInit();
			}
			else
			{
                if ((0x96 == FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeModeStroed) || (2u == FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeWorkstate))   /*heat*/
                {
                    FridgeMode_HeatInit();
                    FridgeSMGlo=FridgeSM_WorkStaeOff;
                }
                else if(0xA5 == FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeModeStroed)/*cool*/
                {
                    FridgeApplHeat_Mainfunction();
                }
                else
                {
                    
                }
			}		
			break;
		case FridgeSM_Fault:
			/*add user cdoe*/

			break;
		case FridgeSM_Sleep:
			/*add user cdoe*/
			FridgeMode_WritebackLastInfo(&(FridgeAppStore_buf._c[0]));
			FridgeSMGlo=FridgeSM_Idle;
			break;
		case FridgeSM_WorkStaeOff:
			/*add user cdoe*/
			if (0x2==FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeWorkstate)
			{
				/*add user code*/
				if (E_OK==FridgeMode_Extern_SleepContitionCheck())
				{
					FridgeSMGlo=FridgeSM_Sleep;
				}
				else
				{
					FridgeSMGlo=FridgeSM_WorkStaeOff;
				}
			}
			else if (0x1==FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeWorkstate)
			{
				if (0xA5==FridgeAppStore_buf.FridgeStoreInfoTmp.FridgeModeStroed)   /*heat*/
				{
					FridgeHeat_SMGlo=FridgeHeatSM_Init; /*init heat state machine*/
					FridgeSMGlo=FridgeSM_Heat;
				}
                /*
				else if(0x96==FridgeStoreInfoTmp.FridgeModeStroed) //cool
				{
					FridgeSMGlo=FridgeSM_Cool;
				}
                */
				else
				{
                    FridgeCool_SMGlo=FridgeCoolSM_Init; /*init heat state machine*/
					FridgeSMGlo=FridgeSM_Cool;
				}
			}
            else
            {

            }
			break;
		default:
			/*add user cdoe*/
			FridgeSMGlo=FridgeSM_Init;
			break;	
	}
}


/*for diagnostics*/
void FridgeApp_DiagnosticsInit(void)
{
    /*compressor*/
    
    /*heat film*/
    

}
/*compressor*/
Std_ReturnType FridgeApp_GetCompressorStatus(FridgeApp_CompressorStatusType*  CompressorStatusPtr)
{
    CompressorStatusPtr->m_CompressorState=gs.state;    /* 压缩机工作状态 */
    CompressorStatusPtr->m_CompressorSpeed=g_fb_rpm;    /* 滤波后的反馈转速 */
    CompressorStatusPtr->m_CompressorPhaseUCur=gs.ia*10*25/32768;   /* ia = (int32_t)(i / PEAK_CURRENT * 32768.f)，精度0.1A */
    CompressorStatusPtr->m_CompressorPhaseVCur=gs.ib*10*25/32768;   /* ib = (int32_t)(i / PEAK_CURRENT * 32768.f)，精度0.1A */
    CompressorStatusPtr->m_CompressorPhaseWCur=gs.ic*10*25/32768;   /* ic = (int32_t)(i / PEAK_CURRENT * 32768.f)，精度0.1A */
    CompressorStatusPtr->m_CompressorBusCur=FridgeAppl_FridgeGetComp12V();
    if(CompressorType==Compressor_DAEWOO)
    {
        CompressorStatusPtr->m_CompressorSupplyVol=(uint8)(FridgeAppl_FridgeComp46V_DW_Voltage()*10/1000);  /* 1000mV,  精度0.1V*/
    } 
    else if (CompressorType==Compressor_LG)
    {
        CompressorStatusPtr->m_CompressorSupplyVol=(uint8)(FridgeAppl_FridgeComp12V_LG_Voltage()*10/1000);  /* 1000mV,  精度0.1V*/
    }
    else
    {
        CompressorStatusPtr->m_CompressorSupplyVol=0xffu;
    }
    CompressorStatusPtr->m_CompressorSM=(uint16)FridgeCool_SMGlo;
    return E_OK;
}
/*HeatFilm*/
Std_ReturnType FridgeApp_GetHeatFilmStatus(FridgeApp_HeatFilmStatusType*  HeatFilmStatusPtr)
{
    if (FLT_TEST_HEAT_FILM_FAULT()==1) /*short*/  //if (RTE_NET_Dem_Callback_DTC_97FC_19()==1)
    {
        HeatFilmStatusPtr->m_HeatFilmState=102;
    }
    else if (FLT_TEST_HEAT_FILM_UC_FAULT()==1) /*open*/       // else if (RTE_NET_Dem_Callback_DTC_97FC_18()==1)
    {
        HeatFilmStatusPtr->m_HeatFilmState=101;
    }
    else
    {
        if(TRUE == Heater_Film_Enable_Flag)
        {
            /* 加热膜工作 */
            HeatFilmStatusPtr->m_HeatFilmState=FridgeHeaterFilmCtrl;
        }
        else 
        {
            /* 关闭加热膜 */
            HeatFilmStatusPtr->m_HeatFilmState=0U;
        }
           /*not real duty*/
    }
    HeatFilmStatusPtr->m_HeatFilmCur=FridgeAppl_FridgeHeatFilm_Value()/100; /* (AD/1000)*10  */
    HeatFilmStatusPtr->m_HeatFilmSM=(uint16)FridgeHeat_SMGlo; 
    return E_OK;
}
/*HeatWire*/
Std_ReturnType FridgeApp_GetHeatWireStatus(FridgeApp_ActuatorGeneralStatusType*  HeatWireStatusPtr)
{
    if (FLT_TEST_HEAT_STRIP_FAULT()==1) /*short*/        //if (RTE_NET_Dem_Callback_DTC_97FD_19()==1)
    {
        HeatWireStatusPtr->m_ActuatorGeneralState=102;
    }
    else if (FLT_TEST_HEAT_STRIP_UC_FAULT()==1)  /*open*/       //else if (RTE_NET_Dem_Callback_DTC_97FD_18()==1)
    {
        HeatWireStatusPtr->m_ActuatorGeneralState=101;
    }
    else
    {
        HeatWireStatusPtr->m_ActuatorGeneralState=FridgeApplWireCtrl;   /*not real duty*/
    }
    HeatWireStatusPtr->m_ActuatorGeneralCur=FridgeAppl_FridgeHeatWire_Value()/100;
    return E_OK;
}
/*Fan*/
Std_ReturnType FridgeApp_GetFanStatus(FridgeApp_ActuatorGeneralStatusType*  FanStatusPtr)
{
    if (FLT_TEST_FAN_FAULT() == 1) /*short*/        //if (RTE_NET_Dem_Callback_DTC_97FB_19()==1)
    {
        FanStatusPtr->m_ActuatorGeneralState=102;
    }
    else if (FLT_TEST_FAN_UC_FAULT() == 1)  /*open*/   //else if (RTE_NET_Dem_Callback_DTC_97FB_18()==1)
    {
        FanStatusPtr->m_ActuatorGeneralState=101;
    }
    else
    {
        FanStatusPtr->m_ActuatorGeneralState=FridgeApplFanCtrl;   /*not real duty*/
    }
    FanStatusPtr->m_ActuatorGeneralCur=FridgeAppl_FridgeFAN_Value()/10;//mA/1000*100
    return E_OK;
}

/*LED diagnostics*/
void FridgeApp_LedDiagnosticsHandler(void)
{
    HwIO_GetLEDDRV_MCU_FLTn1();
    HwIO_GetLEDDRV_MCU_FLTn2();
}




/*UVLed*/
Std_ReturnType FridgeApp_GetUVLedStatus(FridgeApp_ActuatorGeneralStatusType*  UVLedStatusPtr)
{
    if (FLT_TEST_UVLED_UNDER_CURRENT() == 1) /*open*/       //if (RTE_NET_Dem_Callback_DTC_97FA_49()==1)
    {
        UVLedStatusPtr->m_ActuatorGeneralState=101;
    }
    else if(FLT_TEST_UVLED_OVER_CURRENT() == 1)/*short*/
    {
        UVLedStatusPtr->m_ActuatorGeneralState=102;
    }
    else
    {
        UVLedStatusPtr->m_ActuatorGeneralState=FridgeApplUVLed;   /*not real duty*/
    }
    return E_OK;
}

/*WVLed:cold*/
Std_ReturnType FridgeApp_GetWLedStatus(FridgeApp_ActuatorGeneralStatusType*  UVLedStatusPtr)
{
    if (FLT_TEST_WLED_UNDER_CURRENT() == 1) /*open*/    //if (RTE_NET_Dem_Callback_DTC_97F8_49()==1)
    {
        UVLedStatusPtr->m_ActuatorGeneralState=101;
    }
    else if(FLT_TEST_WLED_OVER_CURRENT() == 1)/*short*/
    {
        UVLedStatusPtr->m_ActuatorGeneralState=102;
    }
    else
    {
        UVLedStatusPtr->m_ActuatorGeneralState=FridgeWLedCtrlCtrl;   /*not real duty*/
    }
    return E_OK;
}

/*AVLed:warm*/
Std_ReturnType FridgeApp_GetALedStatus(FridgeApp_ActuatorGeneralStatusType*  UVLedStatusPtr)
{
    if (FLT_TEST_ALED_UNDER_CURRENT()==1) /*open*/    //if (RTE_NET_Dem_Callback_DTC_97F9_49()==1)
    {
        UVLedStatusPtr->m_ActuatorGeneralState=101;
    }
    else if(FLT_TEST_ALED_OVER_CURRENT() == 1)/*short*/   
    {
        UVLedStatusPtr->m_ActuatorGeneralState=102;
    }
    else
    {
        UVLedStatusPtr->m_ActuatorGeneralState=FridgeALedCtrlCtrl;   /*not real duty*/
    }
    return E_OK;
}

/*Door state*/
Std_ReturnType FridgeApp_GetDoorStatus(uint16*  DoorStatusPtr)
{
    *DoorStatusPtr=(uint16)((FridgeDoorStatus_Flag == 2u)? 0u:1u);
    return E_OK;
}

/*PCBA tempereture*/
Std_ReturnType FridgeApp_GetPcbTemp(uint8*  PcbTempPtr)
{
    *PcbTempPtr=(uint8)(FridgeAppl_PCBTemperature_Value()/10+40);
    return E_OK;
}


/*Fridge tempereture*/
Std_ReturnType FridgeApp_GetFridgeTemp(uint16*  FridgeTempPtr)
{
    FridgeMode_ReadCurrentTempreture(FridgeTempPtr);
    return E_OK;
}

/*Compressor tempereture*/
Std_ReturnType FridgeApp_GetCompressorTemp(sint16*  CompTempPtr)
{
    *CompTempPtr = FridgeCtrl_CompTemp_Feedback_Function();
    return E_OK;
}




uint8 FLT_TEST_HEAT_STRIP_FAULT_Warp(void)
{
    uint8 retVal;
    if(FLT_TEST_HEAT_STRIP_FAULT())
    {
        retVal=TRUE;
    }
    else
    {
        retVal=FALSE;
    }
    return retVal;
}
uint8 FLT_TEST_HEAT_STRIP_UC_FAULT_Warp(void)
{
    uint8 retVal;
    if(FLT_TEST_HEAT_STRIP_UC_FAULT())
    {
        retVal=TRUE;
    }
    else
    {
        retVal=FALSE;
    }
    return retVal;
}

uint8 FLT_TEST_FAN_FAULT_Warp(void)
{
    uint8 retVal;
    if(FLT_TEST_FAN_FAULT())
    {
        retVal=TRUE;
    }
    else
    {
        retVal=FALSE;
    }
    return retVal;
}
uint8 FLT_TEST_FAN_UC_FAULT_Warp(void)
{
    uint8 retVal;
    if(FLT_TEST_FAN_UC_FAULT())
    {
        retVal=TRUE;
    }
    else
    {
        retVal=FALSE;
    }
    return retVal;
}

void FridgePeriSMAppl_Init(void)
{
    uint8 L_index;
    for (L_index=0;L_index<Index_TotalNum;L_index++)
    {
        FridgePeriSMGlo[L_index]=FridgePeriSM_Init;
        FridgePeriRequest[L_index]=FALSE;
        FridgePeriErrCnt[L_index]=0;
        FridgePeriFaultCnt[L_index]=0;
    }
}

void FridgePeriApplCtrl_Mainfunction(void)
{
    uint8 L_index;
    for (L_index=0;L_index<Index_TotalNum;L_index++)
    {
        switch (FridgePeriSMGlo[L_index])
        {
            case FridgePeriSM_Init:
                /*add user code*/

                /*add user code*/
                 FridgePeriSMGlo[L_index]=FridgePeriSM_Stop;
                break;
            case FridgePeriSM_Run:
                if (FridgePeriRequest[L_index]==TRUE)
                {
                    if (((*FridgePeriSM_Action[L_index].fpPeriRoutine_Fault1)())||((*FridgePeriSM_Action[L_index].fpPeriRoutine_Fault2)()))
                    {
                        if (FridgePeriFaultCnt[L_index]<0xff)
                        {
                            FridgePeriFaultCnt[L_index]++;
                        }
                        else
                        {

                        }       
                        //FridgePeriErrCnt[L_index]=0;  
                        //(*FridgePeriSM_Action[L_index].fpPeriRoutine_Disable)();             
                        FridgePeriSMGlo[L_index]=FridgePeriSM_Recovery;
                    }
                    else
                    {
                        (*FridgePeriSM_Action[L_index].fpPeriRoutine_Enable)();
                    }
                }
                else
                {
                    FridgePeriSMGlo[L_index]=FridgePeriSM_Stop;
                }
                break;
            case FridgePeriSM_Stop:
                 if (FridgePeriRequest[L_index]==TRUE)
                 {
                    FridgePeriSMGlo[L_index]=FridgePeriSM_Run;
                 }
                 else
                 {
                    (*FridgePeriSM_Action[L_index].fpPeriRoutine_Disable)();
                 }
                break;
            case FridgePeriSM_Recovery:
                (*FridgePeriSM_Action[L_index].fpPeriRoutine_Disable)();  
                if (FridgePeriFaultCnt[L_index]>FridgePeriSM_Action[L_index].FridgePeriFaultCntThre)
                {
                    FridgePeriSMGlo[L_index]=FridgePeriSM_Fault;
                }
                else
                {
                    if (FridgePeriRequest[L_index]==TRUE)
                    {
                        if (FridgePeriErrCnt[L_index]<FridgePeriSM_Action[L_index].FridgePeriErrCntThre)
                        {
                            FridgePeriErrCnt[L_index]++;
                        }
                        else
                        {
                            FridgePeriErrCnt[L_index]=0; 
                            FridgePeriSMGlo[L_index]=FridgePeriSM_Run;
                        }
                    }
                    else
                    {
                        FridgePeriSMGlo[L_index]=FridgePeriSM_Stop;
                    }
                }
                break;
            case FridgePeriSM_Fault:
                /*dump:stay this state,keep off*/
                (*FridgePeriSM_Action[L_index].fpPeriRoutine_Disable)();
                break;
            case FridgePeriSM_Idle:
                FridgePeriSMGlo[L_index]=FridgePeriSM_Init;
                (*FridgePeriSM_Action[L_index].fpPeriRoutine_Disable)();
                break;
            default:
                FridgePeriSMGlo[L_index]=FridgePeriSM_Init;
                (*FridgePeriSM_Action[L_index].fpPeriRoutine_Disable)();
                break;
        }
    }
}

/******************************************************************************************* */
/*IO Control Interface*/
/******************************************************************************************* */


/*Compressor*/
Std_ReturnType CompressorControlEnable(uint16 IoControlPara)
{
    motor_start();
    motor_speed((uint32)IoControlPara);

    /*使能压缩机故障检测*/
    COMP_Enable_Flag = TRUE;

    return E_OK;
}

Std_ReturnType CompressorControlDisable(void)
{
    motor_stop();

    /*不使能压缩机故障检测*/
    COMP_Enable_Flag = FALSE;
    
    return E_OK;
}
void FridgeApp_IoControlInit(void)
{
    uint8 OutConIndex;
    /*output*/
    for (OutConIndex=0;OutConIndex<OutputControlObj_MaxNum;OutConIndex++)
    {
        Fridge_OutControlState[OutConIndex]=ControlType_NormalState;
    }
    /*Input*/    
    for (OutConIndex=0;OutConIndex<InputControlObj_MaxNum;OutConIndex++)
    {
        InputControl_State[OutConIndex].VaInputControl_State=ControlType_NormalState;
        InputControl_State[OutConIndex].VaInputControl_Value=0;
    }
}
/*
ConPara_Diag:
*/
Std_ReturnType FridgeApp_OutputControl(Fridge_OutputControlObjType OutConIndex,Fridge_ControlRequestType OutConReqTypePara,uint16 OutConReqTarPara)
{
    static Fridge_ControlRequestType OutConPara_EnTmp[OutputControlObj_MaxNum];
    static uint16 OutConPara_SpeedTmp[OutputControlObj_MaxNum];
    static uint16 OutConPara_DiagSpeedTmp[OutputControlObj_MaxNum];
    if (ControlType_DiagRequest==OutConReqTypePara)
    {
        Fridge_OutControlState[OutConIndex]=ControlType_DiagState;
        OutConPara_DiagSpeedTmp[OutConIndex]=OutConReqTarPara;
    }
    else if (ControlType_DiagRelease==OutConReqTypePara)
    {
        Fridge_OutControlState[OutConIndex]=ControlType_NormalState;
    }
    else
    {
        OutConPara_EnTmp[OutConIndex]=OutConReqTypePara;
        OutConPara_SpeedTmp[OutConIndex]=OutConReqTarPara;
        //Fridge_CompressControlState=ControlType_NormalState;
    }
    switch (Fridge_OutControlState[OutConIndex])
    {
        case ControlType_NormalState:
            if (ControlType_Normalrequest==OutConPara_EnTmp[OutConIndex])
            {
                FridgeOutputControl_Action[OutConIndex].fpIoControl_Enable(OutConPara_SpeedTmp[OutConIndex]);
            }
            else
            {
                FridgeOutputControl_Action[OutConIndex].fpIoControl_Disable();
            }
            break;
        case ControlType_DiagState:
            FridgeOutputControl_Action[OutConIndex].fpIoControl_Enable(OutConPara_DiagSpeedTmp[OutConIndex]);
            break;  
        default:
            Fridge_OutControlState[OutConIndex]=ControlType_NormalState;
            break; 
    }
    return E_OK;
}







Std_ReturnType FridgeApp_InputputControl(Fridge_InputputControlObjType IputConIndex,Fridge_ControlRequestType InConReqTypePara,uint16 InConReqTarPara)
{
    if (ControlType_DiagRequest==InConReqTypePara)
    {
        InputControl_State[IputConIndex].VaInputControl_State=ControlType_DiagState;
        InputControl_State[IputConIndex].VaInputControl_Value=InConReqTarPara;
    }
    else
    {
        InputControl_State[IputConIndex].VaInputControl_State=ControlType_NormalState;
        InputControl_State[IputConIndex].VaInputControl_Value=0;
    }
    return E_OK;
}