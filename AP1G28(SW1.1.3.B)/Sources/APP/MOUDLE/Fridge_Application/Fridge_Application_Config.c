/*******************************************************************************
||  File Name: Fridge_Application_Config.c
||  Description: Implementation of the AUTOSAR Fridge Application Config
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
#include "Fridge_Application_Config.h"
#include "HallM.h"
#include "STD_SrM.h"
#include "AMP_AdCtr.h"
#include "VOLT_AdCtr.h"
#include "STD_BtrCtr.h"
#include "HallCtr_Cfg.h"
#include "PwmM.h"
#include "Fridge_Basic_Control.h"
/*******************************************************************************
||    Macro Definition
||******************************************************************************/

/*******************************************************************************
||    Enum Definition
||******************************************************************************/

uint8 FridgeLedState;
/*******************************************************************************
||    Typedef Definition
||******************************************************************************/

/*******************************************************************************
||    Global variables Declaration
||******************************************************************************/


/* 故障检测使能标志位 */
bool1 UVLED_FaultDetectEnable_Flag = FALSE;
bool1 Fan_FaultDetectEnable_Flag = FALSE;
bool1 Strip_FaultDetectEnable_Flag = FALSE;
bool1 Film_FaultDetectEnable_Flag = FALSE;
bool1 WLed_FaultDetectEnable_Flag = FALSE;
bool1 ALed_FaultDetectEnable_Flag = FALSE;

/*******************************************************************************
||    static local variables Declaration
||******************************************************************************/

/*******************************************************************************
||    static Local Functions Declaration
||******************************************************************************/
// static uint8 FridgeAppl_UVLed_Ctrl(void);
// static uint8 FridgeAppl_Fan_Ctrl(void);
// static uint8 FridgeAppl_Heater_Strip_Ctrl(void);
// static uint8 FridgeAppl_Heater_Film_Ctrl(void);
// static uint8 FridgeAppl_WLed_Ctrl(void);
// static uint8 FridgeAppl_ALed_Ctrl(void);
/*******************************************************************************
||    Extern variables and functions declaration
||******************************************************************************/

/********************************** Fridge Application Initialization **********************************/
/*******************************************************************************
*Function    	    : void FridgeAppl_Init(void)
*ReturnValue 	    : void
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : None
*Description		: Fridge Application Initialization
|******************************************************************************/
void FridgeAppl_Init(void)
{
    /* Fridge Application initialization implementation */
    FridgeAppl_UVLed_Ctrl_Disable();
    FridgeAppl_Fan_Ctrl_Disable();
    FridgeAppl_Heater_Strip_Ctrl_Disable();
    FridgeAppl_Heater_Film_Ctrl_Disable();
    FridgeAppl_WLed_Ctrl_Disable();
    FridgeAppl_ALed_Ctrl_Disable();

	/* ʹ������������ */
	HwIO_COMP_12V_DEN_ON();
	HwIO_HW_12V_DEN_ON();
	HwIO_HF_12V_DEN_ON();
	HwIO_FAN_12V_DEN_Enable();
}

/********************************** Fridge Application **********************************/
/*******************************************************************************
*Function    	    : uint8 FridgeAppl_Compressor_Ctrl(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge unlock control status
*Description		: Fridge Application Compressor Control
|******************************************************************************/
uint8 FridgeAppl_Compressor_Ctrl(void)
{
    return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_Fan_Ctrl(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge door warning time setting
*Description		: Fridge Application Fan Control
||******************************************************************************/
uint8 FridgeAppl_Fan_Ctrl_Enable(uint16 Fanpara)
{
    PwmM_set_FAN_12V_DutyCycle(Fanpara*10);

    /* 使能风扇故障检测 */
    Fan_FaultDetectEnable_Flag = TRUE;
    return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_Fan_Ctrl(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge door warning time setting
*Description		: Fridge Application Fan Control
||******************************************************************************/
uint8 FridgeAppl_Fan_Ctrl_Disable(void)
{
    PwmM_set_FAN_12V_DutyCycle(0u);

    /* 关闭风扇故障检测 */
    Fan_FaultDetectEnable_Flag = FALSE;
    return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_Heater_Strip_Ctrl(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application Heater Strip Control
||******************************************************************************/
uint8 FridgeAppl_Heater_Strip_Ctrl_Enable(uint16 HeatWirepara)
{
    PwmM_set_HW_12V_DutyCycle(HeatWirepara*10);

    /* 使能加热丝故障检测 */
    Strip_FaultDetectEnable_Flag = TRUE;
    return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_Heater_Strip_Ctrl(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application Heater Strip Control
||******************************************************************************/
uint8 FridgeAppl_Heater_Strip_Ctrl_Disable(void)
{
    PwmM_set_HW_12V_DutyCycle(0u);

    /* 关闭加热丝故障检测 */
    Strip_FaultDetectEnable_Flag = FALSE;
    return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_Heater_Film_Ctrl(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application Heater Film Control
||******************************************************************************/
uint8 FridgeAppl_Heater_Film_Ctrl_Enable(uint16 HeatFilmpara)
{
    PwmM_set_HF_12V_DutyCycle(HeatFilmpara*10);

    /* 使能加热膜故障检测 */
    Film_FaultDetectEnable_Flag = TRUE;
    return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_Heater_Film_Ctrl(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application Heater Film Control
||******************************************************************************/
uint8 FridgeAppl_Heater_Film_Ctrl_Disable(void)
{
    PwmM_set_HF_12V_DutyCycle(0u);

    /* 关闭加热膜故障检测 */
    Film_FaultDetectEnable_Flag = FALSE;
    return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_UVLed_Ctrl(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application UVLed Control
||******************************************************************************/
uint8 FridgeAppl_UVLed_Ctrl_Enable(uint16 UvLedpara)
{
    PwmM_set_MCU_UVCLED_DutyCycle(UvLedpara*10);
    FridgeLedState |= FridgeLedBit_UV;

    /* 使能杀菌灯故障检测 */
    UVLED_FaultDetectEnable_Flag = TRUE;

    FridgeUVLedState = 1u;

    return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_UVLed_Ctrl(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application UVLed Control
||******************************************************************************/
uint8 FridgeAppl_UVLed_Ctrl_Disable(void)
{
    PwmM_set_MCU_UVCLED_DutyCycle(0u);
    FridgeLedState &= ~FridgeLedBit_UV;

    /* 关闭杀菌灯故障检测 */
    UVLED_FaultDetectEnable_Flag = FALSE;

    FridgeUVLedState = 0u;

    return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_WLed_Ctrl(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application WLed Control-Coolmode
||******************************************************************************/
uint8 FridgeAppl_WLed_Ctrl_Enable(uint16 WLedpara)
{
    PwmM_set_MCU_WLED_DutyCycle( WLedpara*10);
    FridgeLedState |= FridgeLedBit_W;

    /* 使能照明灯故障检测 */
    WLed_FaultDetectEnable_Flag = TRUE;
    return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_WLed_Ctrl(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application WLed Control-Coolmode
||******************************************************************************/
uint8 FridgeAppl_WLed_Ctrl_Disable(void)
{
    PwmM_set_MCU_WLED_DutyCycle(0u);
    FridgeLedState &= ~FridgeLedBit_W;

    /* 关闭照明灯故障检测 */
    WLed_FaultDetectEnable_Flag = FALSE;
    return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_ALed_Ctrl(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application ALed Control-Heatmode
||******************************************************************************/
uint8 FridgeAppl_ALed_Ctrl_Enable(uint16 ALedpara)
{
    PwmM_set_MCU_ALED_DutyCycle(ALedpara*10);
    FridgeLedState |= FridgeLedBit_A;

    /* 使能照明灯故障检测 */
    ALed_FaultDetectEnable_Flag = TRUE;
    return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_ALed_Ctrl(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application ALed Control-Heatmode
||******************************************************************************/
uint8 FridgeAppl_ALed_Ctrl_Disable(void)
{
    PwmM_set_MCU_ALED_DutyCycle(0u);
    FridgeLedState &= ~FridgeLedBit_A;

    /* 关闭照明灯故障检测 */
    ALed_FaultDetectEnable_Flag = FALSE;
    return 0;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_FridgeTEMP_Calculate(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application Fridge Temperature Calculate
||******************************************************************************/
sint16 FridgeAppl_FridgeTEMP_Calculate(void)
{
    sint16 FridgeTEMP_Tmp;
    uint16 Fridge_DiagTemperature;
    FridgeTEMP_Tmp = SRM_GetValidValue(SRCFG_TEMP_TS2_NTC_CH);

    /*IO control start*/
    if (ControlType_DiagState==InputControl_State[InputControlObj_BodyTemp].VaInputControl_State)
    {
        Fridge_DiagTemperature=InputControl_State[InputControlObj_BodyTemp].VaInputControl_Value;
        FridgeTEMP_Tmp=(Fridge_DiagTemperature-40)*10;
    }
    else
    {
        /*keep the real state*/
    }
    /*IO control end*/

    return FridgeTEMP_Tmp;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_FridgeCompTemp_Calculate(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application Compressor Temperature Calculate
||******************************************************************************/
sint16 FridgeAppl_FridgeCompTemp_Calculate(void)
{
    sint16 FridgeCompTemp_Tmp;
    uint16 Fridge_DiagTemperature;
    FridgeCompTemp_Tmp = SRM_GetValidValue(SRCFG_TEMP_TS1_NTC_CH);

    /*IO control start*/
    if (ControlType_DiagState==InputControl_State[InputControlObj_EnvTemp].VaInputControl_State)
    {
        Fridge_DiagTemperature=InputControl_State[InputControlObj_EnvTemp].VaInputControl_Value;
        FridgeCompTemp_Tmp=(Fridge_DiagTemperature-40)*10;
    }
    else
    {
        /*keep the real state*/
    }
    /*IO control end*/

    return FridgeCompTemp_Tmp;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_FridgeDoor_Status(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application Fridge Door Status
||******************************************************************************/
uint8 FridgeAppl_FridgeDoor_Status(void)
{
     #if 0
    uint8 FridgeDoor_Status;

    /* Enable Hall 5V Output */
    HwIO_HALL_5V_EN_ON();

   
    if(1u == HALL_M_GetHALL_SwitchStatus())
    {
        FridgeDoor_Status = 1u;
    }
    else if(0u == HALL_M_GetHALL_SwitchStatus())
    {
        FridgeDoor_Status = 2u;
    }else{}

    #endif

    uint8 FridgeDoor_Status;
    uint8 Hall_Status;
    static uint8 Last_Confirmed_Status = 2u;  /* 上次确认的状态，默认门关闭2，门开启1 */
    static uint8 Filter_Cnt = 0u;            

    /* Enable Hall 5V Output */
    HwIO_HALL_5V_EN_ON();

    Hall_Status = HALL_M_GetHALL_SwitchStatus();
    
    /* 当前采样值与上次确认状态比较 */
    if ((Hall_Status == 1u && Last_Confirmed_Status == 2u) || 
        (Hall_Status == 0u && Last_Confirmed_Status == 1u))
    {
        Filter_Cnt++;
        if (Filter_Cnt >= FRIDGE_DOOR_FILTER_CNT)
        {
            /* 连续多次采样一致，确认状态变化 */
            Last_Confirmed_Status = (Hall_Status == 1u) ? 1u : 2u;
            Filter_Cnt = 0u;
        }
    }
    else
    {
        Filter_Cnt = 0u;
    }

    FridgeDoor_Status = Last_Confirmed_Status;

    /*IO control start*/
    if (ControlType_DiagState==InputControl_State[InputControlObj_Hall].VaInputControl_State)
    {
        FridgeDoor_Status=InputControl_State[InputControlObj_Hall].VaInputControl_Value;
    }
    else
    {
        /*keep the real state*/
    }
    /*IO control end*/

    return FridgeDoor_Status;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_FridgeHALL_5VAD_Value(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application HALL 5V AD Feedback
||******************************************************************************/
uint16 FridgeAppl_FridgeHALL_5VAD_Value(void)
{
    uint16 FridgeHALL_5VAD_Value;
    FridgeHALL_5VAD_Value = HALLCTR_GetBatteryAdValue();
    return FridgeHALL_5VAD_Value;
}

/********************************** Get Fridge Hardware Fault **********************************/
/*******************************************************************************
*Function    	    : uint8 FridgeAppl_Fridge12V_KL30_Voltage(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application Compressor 12V Voltage LG
||******************************************************************************/
uint16 FridgeComp12V_Voltage;
uint16 FridgeAppl_Fridge12V_KL30_Voltage(void)
{
    //uint16 FridgeComp12V_Voltage;
    FridgeComp12V_Voltage = BTRCTR_Get_KL30_VoltValue(); 
    return FridgeComp12V_Voltage;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_FridgeCompVoltage_Calculate(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application Compress Supply Voltage Calculate
||******************************************************************************/
uint32 FridgeComp_Voltage_Tmp;
uint16 FridgeAppl_FridgeCompVoltage_Calculate(void)
{
    uint16 FridgeComp_Voltage;
    //uint32 FridgeComp_Voltage_Tmp;
#if 0
    /* 压缩机母线电压读取 */
    FridgeComp_Voltage_Tmp = (uint32)BTRCTR_Get_KL30_VoltValue();  //accuracy=0.1v
    if(FridgeComp_Voltage_Tmp < 120)
    {
        FridgeComp_Voltage = (uint16)((FridgeComp_Voltage_Tmp*863)/120);
    }
    else
    {
        FridgeComp_Voltage = (uint16)((((FridgeComp_Voltage_Tmp-120)*998)/130)+863);
    }
#endif

    FridgeComp_Voltage_Tmp = VOLT_AdCtr_Get_COMP_12V_AD_VOLT_Souce_Value();  //accuracy=0.001v

    return (uint16)FridgeComp_Voltage_Tmp;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_FridgeComp12V_LG_Voltage(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application Compressor 12V Voltage LG
||******************************************************************************/
uint16 FridgeAppl_FridgeComp12V_LG_Voltage(void)
{
    uint16 FridgeComp12V_LG_Voltage;
    FridgeComp12V_LG_Voltage = VOLT_AdCtr_Get_COMP_12V_AD_VOLT_Value();
    return FridgeComp12V_LG_Voltage;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_FridgeComp46V_DW_Voltage(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application Compressor 46V Voltage
||******************************************************************************/
uint16 FridgeAppl_FridgeComp46V_DW_Voltage(void)
{
    uint16 FridgeComp46V_Voltage;
    FridgeComp46V_Voltage = VOLT_AdCtr_Get_COMP_12V_AD_VOLT_Value();
    return FridgeComp46V_Voltage;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_FridgeGetComp12V(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :
*Description		: Fridge Application Compressor 12V
||******************************************************************************/
uint16 FridgeAppl_FridgeGetComp12V(void)
{
    uint16 FridgeComp12V_Value;
    FridgeComp12V_Value = (uint16)(AMP_AdCtr_Get_COMP_12V_Value()/100);/*mA/1000*10 */

    return FridgeComp12V_Value;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_FridgeHeatWire_Value(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application HeatWire Value
||******************************************************************************/
uint16 FridgeAppl_FridgeHeatWire_Value(void)
{
    uint16 FridgeHeatWire_Value;
    FridgeHeatWire_Value = AMP_AdCtr_Get_HeatWire_Value();
    return FridgeHeatWire_Value;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_FridgeHeatFilm_Value(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application HeatFilm Value
||******************************************************************************/
uint16 FridgeAppl_FridgeHeatFilm_Value(void)
{
    uint16 FridgeHeatFilm_Value;
    FridgeHeatFilm_Value = AMP_AdCtr_Get_HeatFilm_Value();
    return FridgeHeatFilm_Value;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_FridgeHeatFilm_Value(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint8					    :Fridge child lock request status
*Description		: Fridge Application FAN Value
||******************************************************************************/
uint16 FridgeAppl_FridgeFAN_Value(void)
{
    uint16 FridgeFAN_Value;
    FridgeFAN_Value = AMP_AdCtr_Get_FAN_Value();
    return FridgeFAN_Value;
}

/*******************************************************************************
*Function    	    : uint8 FridgeAppl_PCBTemperature_Value(void)
*ReturnValue 	    : uint8
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : uint16			    :PCB Temperature
*Description		: Get PCB Temperature
||******************************************************************************/
sint16 FridgeAppl_PCBTemperature_Value(void)
{
    sint16 Fridge_PCBTemperature;
    uint16 Fridge_DiagTemperature;
    Fridge_PCBTemperature = SRM_GetValidValue(SRCFG_TEMP_PCB_NTC_CH);

    /*IO control start*/
    if (ControlType_DiagState==InputControl_State[InputControlObj_PcbTemp].VaInputControl_State)
    {
        Fridge_DiagTemperature=InputControl_State[InputControlObj_PcbTemp].VaInputControl_Value;
        Fridge_PCBTemperature=(Fridge_DiagTemperature-40)*10;
    }
    else
    {
        /*keep the real state*/
    }
    /*IO control end*/

    return Fridge_PCBTemperature;
}

/********************************** Fridge Application Functions **********************************/
/*******************************************************************************
*Function    	    : void Fridge_Application_Function(void)
*ReturnValue 	    : void
*Parameters(in)	    : None
*Parameters(in)	    : None
*Parameters(out)    : None						
*Return value	    : None
*Description		: Fridge Application Function
|******************************************************************************/
void Fridge_Application_Function(void)
{
    /* Fridge Application Function Implementation */
    FridgeAppl_FridgeComp12V_LG_Voltage();
    FridgeAppl_FridgeComp46V_DW_Voltage();
    FridgeAppl_FridgeHeatWire_Value();
    FridgeAppl_FridgeHeatFilm_Value();
    FridgeAppl_FridgeFAN_Value();
}
