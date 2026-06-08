/*******************************************************************************
||  File Name: Fridge_Application_Config.h
||  Description: Header file for AUTOSAR Fridge Application Config
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

#ifndef FRIDGE_APPLICATION_CONFIG_H
#define FRIDGE_APPLICATION_CONFIG_H
#include "CAEA_Types.h"
/*******************************************************************************
||    Other Header File Inclusion
||******************************************************************************/ 

/*******************************************************************************
||    Macro Definition
||******************************************************************************/
#define FRIDGE_DOOR_FILTER_CNT  40u  
/*******************************************************************************
||    Enum Definition
||******************************************************************************/

/*******************************************************************************
||    Typedef Definition
||******************************************************************************/
#define FridgeLedBit_UV (uint8)0x1
#define FridgeLedBit_W (uint8)0x2
#define FridgeLedBit_A (uint8)0x4
extern uint8 FridgeLedState;
/*
extern const uint16 FridgeApplUVLed;
extern const uint16 FridgeApplFanCtrl;
extern const uint16 FridgeApplWireCtrl;
extern const uint16 FridgeHeaterFilmCtrl;
extern const uint16 FridgeWLedCtrlCtrl;
extern const uint16 FridgeALedCtrlCtrl;
*/
/*******************************************************************************
||    Global variables Declaration
||******************************************************************************/

/*******************************************************************************
||    Extern variables and functions declaration
||******************************************************************************/

// /********************************** Fridge Application Initialization **********************************/
// extern void RTE_NET_Can_Init(void);

// /********************************** Fridge Application **********************************/
// extern uint8 RTE_NET_Can_Read_FridgeUnlockCtrl(void);


/********************************** Fridge Application Functions **********************************/
extern void FridgeAppl_Init(void);
extern void Fridge_Application_Function(void);
extern uint8 FridgeAppl_UVLed_Ctrl_Enable(uint16 UvLedpara);
extern uint8 FridgeAppl_UVLed_Ctrl_Disable(void);
extern uint8 FridgeAppl_Fan_Ctrl_Enable(uint16 Fanpara);
extern uint8 FridgeAppl_Fan_Ctrl_Disable(void);
extern uint8 FridgeAppl_Heater_Strip_Ctrl_Enable(uint16 HeatWirepara);
extern uint8 FridgeAppl_Heater_Strip_Ctrl_Disable(void);
extern uint8 FridgeAppl_Heater_Film_Ctrl_Enable(uint16 HeatFilmpara);
extern uint8 FridgeAppl_Heater_Film_Ctrl_Disable(void);
extern uint8 FridgeAppl_WLed_Ctrl_Enable(uint16 WLedpara);
extern uint8 FridgeAppl_WLed_Ctrl_Disable(void);
extern uint8 FridgeAppl_ALed_Ctrl_Enable(uint16 ALedpara);
extern uint8 FridgeAppl_ALed_Ctrl_Disable(void);
extern sint16 FridgeAppl_FridgeTEMP_Calculate(void);
extern sint16 FridgeAppl_FridgeCompTemp_Calculate(void);
extern uint8 FridgeAppl_FridgeDoor_Status(void);
extern uint16 FridgeAppl_FridgeComp12V_LG_Voltage(void);
extern uint16 FridgeAppl_FridgeComp46V_DW_Voltage(void);
extern uint16 FridgeAppl_FridgeGetComp12V(void);
extern uint16 FridgeAppl_FridgeHeatWire_Value(void);
extern uint16 FridgeAppl_FridgeHeatFilm_Value(void);
extern uint16 FridgeAppl_FridgeFAN_Value(void);
extern sint16 FridgeAppl_PCBTemperature_Value(void);
extern uint16 FridgeAppl_FridgeCompVoltage_Calculate(void);
extern uint16 FridgeAppl_FridgeHALL_5VAD_Value(void);
extern uint16 FridgeAppl_Fridge12V_KL30_Voltage(void);

extern bool1 UVLED_FaultDetectEnable_Flag;
extern bool1 Fan_FaultDetectEnable_Flag;
extern bool1 Strip_FaultDetectEnable_Flag;
extern bool1 Film_FaultDetectEnable_Flag;
extern bool1 WLed_FaultDetectEnable_Flag;
extern bool1 ALed_FaultDetectEnable_Flag;

#endif /* FRIDGE_APPLICATION_CONFIG_H */
