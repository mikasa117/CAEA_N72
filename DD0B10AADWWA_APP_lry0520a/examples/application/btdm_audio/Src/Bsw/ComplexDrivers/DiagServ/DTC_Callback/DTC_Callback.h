/*******************************************************************************
|  File Name:  Dtc_Callback.h
|  Description:  Implementation of the System Sofeware  Dtc  Service
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           YaJun Xia           CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2018-6-16    01.00.00     XYJ       Creation
|
|******************************************************************************/
#ifndef DTC_CALLBACK_H
#define DTC_CALLBACK_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/
#define VOLTAGE_LOW_THRESHOLD       1405       //9.0f      /* 9V - Low voltage threshold */
#define VOLTAGE_HIGH_THRESHOLD      2501      //16.0f     /* 16V - Hign voltage threshold */
#define VOLTAGE_RECOVERY_LOW        1483      //9.5f      /* Low-voltage threshold recovery */
#define VOLTAGE_RECOVERY_HIGH       2423      //15.5f     /* Hign-voltage threshold recovery */
#define MIC_CURRENT_HIGH0           188         /* MIC current Hign threshold 9mA()  Converted value afterwards*/
#define MIC_CURRENT_HIGH1           569         /* MIC current Hign threshold 9mA()  Converted value afterwards*/
#define MIC_CURRENT_LOW             126         /* MIC current low threshold 2mA()  Converted value afterwards */
/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/*******************************************************************************
|    Enum Definition
|******************************************************************************/
extern void  DTC_ReadVehicleNetConfig(void);
extern uint8 DTC_Callback_0xF006_16(void);
extern uint8 DTC_Callback_0xF006_17(void);
extern uint8 DTC_Callback_0xC073_00(void);
extern uint8 DTC_Callback_0x93E1_53(void);

#endif



