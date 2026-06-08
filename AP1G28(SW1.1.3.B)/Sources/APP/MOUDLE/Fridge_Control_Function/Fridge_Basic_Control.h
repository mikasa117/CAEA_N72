
/*******************************************************************************
||  File Name: Fridge_Basic_Control.h
||  Description: Header file for AUTOSAR Fridge Control Function
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

#ifndef FRIDGE_BASIC_CONTROL_H
#define FRIDGE_BASIC_CONTROL_H
#include "CAEA_Types.h"
#include "Std_Types.h"
/*******************************************************************************
||    Other Header File Inclusion
||******************************************************************************/ 

/*******************************************************************************
||    Macro Definition
||******************************************************************************/
#define DEBUG_FRIDGE_CONTROL                    0
/*******************************************************************************
||    Enum Definition
||******************************************************************************/

/*******************************************************************************
||    Typedef Definition
||******************************************************************************/

/*******************************************************************************
||    Global variables Declaration
||******************************************************************************/
/*for diagnostics*/
typedef enum
  {
    Compressor_DAEWOO       =  (uint8)1,        
    Compressor_LG           = (uint8)2,        
  } FridgeAppCompressorType;
#define CompressorType Compressor_LG
typedef enum
  {
    CompressorState_Normal              = (uint16)0,        
    CompressorState_OverTemp            = (uint16)1,       
    CompressorState_OverCur             = (uint16)2,       
    CompressorState_Stall               = (uint16)3,  
    CompressorState_Open                = (uint16)4, 
    CompressorState_Unkown              = (uint16)0xff    
  } FridgeAppCompressorStateType;
typedef struct
{
    FridgeAppCompressorStateType m_CompressorState;
   	uint16 m_CompressorSpeed;
    uint16 m_CompressorPhaseUCur;
    uint16 m_CompressorPhaseVCur;
    uint16 m_CompressorPhaseWCur;
    uint16 m_CompressorBusCur;
    uint8  m_CompressorSupplyVol;
    uint16  m_CompressorSM;         /*update to enum type later*/
    uint32  m_CompressorReserved; 
}FridgeApp_CompressorStatusType;
//FridgeApp_CompressorStatusType G_CompressorStatus;

typedef struct
{
    uint16  m_HeatFilmState;
    uint16  m_HeatFilmCur;
    uint16  m_HeatFilmSM;
    uint8  m_HeatFilmReserved1;
    uint8  m_HeatFilmReserved2;
    uint8  m_HeatFilmReserved3;
}FridgeApp_HeatFilmStatusType;
//FridgeApp_HeatFilmStatusType G_HeatFilmStatus;

typedef struct
{
    uint16  m_ActuatorGeneralState;
    uint16  m_ActuatorGeneralCur;
}FridgeApp_ActuatorGeneralStatusType;




/*********************IO Control*************************** */
typedef enum 
{
    OutputControlObj_Compressor			= 0, 
    OutputControlObj_ALed,
    OutputControlObj_WLed,
    OutputControlObj_UvLed,
    OutputControlObj_Fan,
    OutputControlObj_HeatWire,
    OutputControlObj_HeatFilm,
    OutputControlObj_MaxNum		 
} Fridge_OutputControlObjType;

typedef enum {
    ControlType_NormalRelease= 0, 
    ControlType_Normalrequest, 
    ControlType_DiagRequest, 
    ControlType_DiagRelease, 
} Fridge_ControlRequestType;

typedef enum {
    ControlType_NormalState			= 0, 
    ControlType_DiagState		= 1, 
} Fridge_OutControlStateType;

typedef enum {
    InputControlObj_Hall			= 0, 
    InputControlObj_PcbTemp,
    InputControlObj_BodyTemp,
    InputControlObj_EnvTemp,
    InputControlObj_MaxNum		 
} Fridge_InputputControlObjType;

typedef struct {
    Fridge_OutControlStateType VaInputControl_State;
    uint16 VaInputControl_Value;
} InputControl_StateType;

typedef enum {
  FridgeCoolExecuteSM_Init		    =0, 
  FridgeCoolExecuteSM_StartStep1      =1,
  FridgeCoolExecuteSM_StartStep2      =2,
  FridgeCoolExecuteSM_Run1            =3,
  FridgeCoolExecuteSM_StopStep1       =4,
  FridgeCoolExecuteSM_StopStep2       =5, 
  FridgeCoolExecuteSM_StopStep3       =6, 
  FridgeCoolExecuteSM_Stop            =7,
} FridgeCoolExecute_StateMachineType;

extern FridgeCoolExecute_StateMachineType FridgeCoolExecute_SMGlo;

typedef enum {
  FridgeFaultSM_Normal		            =   0x00u, 
  FridgeFaultSM_PowerSupplyVolFault       =   0x01,
  FridgeFaultSM_FanCurrentFault           =   0x02,
  FridgeFaultSM_CompressorStartsFault     =   0x03,
  FridgeFaultSM_CompressorSpeedFault      =   0x04,
  FridgeFaultSM_ControllerTempFault       =   0x05, 
  FridgeFaultSM_ControllerCurrentFault    =   0x06, 
  FridgeFaultSM_InsideTempSensorFault     =   0x07,
  FridgeFaultSM_HeatingWireFault          =   0x08,
  FridgeFaultSM_HeatingFilmFault          =   0x09,
  FridgeFaultSM_HallSensorFault           =   0x0Au,
  FridgeFaultSM_CoolLampFault             =   0x0Bu,
  FridgeFaultSM_UVLampFault               =   0x0Cu,
  FridgeFaultSM_HeatLampFault             =   0x0Du,
  FridgeFaultSM_DoorMotorFault            =   0x0Eu,
  FridgeFaultSM_ReservedFault             =   0x0Fu
} FridgeFaultType;

extern InputControl_StateType InputControl_State[InputControlObj_MaxNum];
extern Std_ReturnType FridgeApp_InputputControl(Fridge_InputputControlObjType IputConIndex,Fridge_ControlRequestType InConReqTypePara,uint16 InConReqTarPara);
extern Std_ReturnType FridgeApp_OutputControl(Fridge_OutputControlObjType OutConIndex,Fridge_ControlRequestType OutConReqTypePara,uint16 OutConReqTarPara);

/*******************************************************************************
||    Extern variables and functions declaration
||******************************************************************************/


/********************************** Fridge Basic Control Function **********************************/
extern void FridgeCtrl_Basic_Control_Function(void);
extern uint8 FridgeMode_SleepContitionCheck(void);
extern void FridgeCtrl_Initialization(void);
extern uint8 FridgeCtrl_Headlamp_Control(void);
extern sint16 FridgeCtrl_Temp_Feedback_Function(void);
extern sint16 FridgeCtrl_CompTemp_Feedback_Function(void);

extern Std_ReturnType FridgeApp_GetCompressorStatus(FridgeApp_CompressorStatusType*  CompressorStatusPtr);
extern Std_ReturnType FridgeApp_GetHeatFilmStatus(FridgeApp_HeatFilmStatusType*  HeatFilmStatusPtr);
extern Std_ReturnType FridgeApp_GetHeatWireStatus(FridgeApp_ActuatorGeneralStatusType*  HeatWireStatusPtr);
extern Std_ReturnType FridgeApp_GetFanStatus(FridgeApp_ActuatorGeneralStatusType*  FanStatusPtr);
extern void FridgeApp_LedDiagnosticsHandler(void);
extern Std_ReturnType FridgeApp_GetUVLedStatus(FridgeApp_ActuatorGeneralStatusType*  UVLedStatusPtr);
extern Std_ReturnType FridgeApp_GetWLedStatus(FridgeApp_ActuatorGeneralStatusType*  UVLedStatusPtr);
extern Std_ReturnType FridgeApp_GetALedStatus(FridgeApp_ActuatorGeneralStatusType*  UVLedStatusPtr);
extern Std_ReturnType FridgeApp_GetDoorStatus(uint16*  DoorStatusPtr);
extern Std_ReturnType FridgeApp_GetPcbTemp(uint8*  PcbTempPtr);
extern Std_ReturnType FridgeApp_GetFridgeTemp(uint16*  FridgeTempPtr);
extern Std_ReturnType FridgeApp_GetCompressorTemp(sint16*  CompTempPtr);

extern uint8 FridgeCtrl_Heat_Strip_Control(void);
extern sint16 FridgeCompTemp;
extern bool1 COMP_Enable_Flag;
extern bool1 Heater_Film_Enable_Flag;
extern uint8 FridgeCool_StartupErrorFlag;
extern uint8 FridgeUVLedState;
extern uint32 FridgeFAULT;
extern uint8 FridgeFault_BatModeA;
extern uint16 FridgeFault_BatADValue;
#endif /* FRIDGE_BASIC_CONTROL_H */
