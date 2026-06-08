/*******************************************************************************
||  File Name: RTE_APP.c
||  Description: Implementation of the AUTOSAR APP Can Interface
||-------------------------------------------------------------------------------
||  (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
||     All rights are reserved by CAEA.
||-------------------------------------------------------------------------------
|| Initials      Name                   Company
|| --------      ---------------------  -----------------------------------------
||                                    CAEA
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
#include "Rte_CAN.h"
#include "CanApp.h"

/*******************************************************************************
||    Macro Definition
||******************************************************************************/

/*******************************************************************************
||    Enum Definition
||******************************************************************************/

/*******************************************************************************
||    Typedef Definition
||******************************************************************************/

/*******************************************************************************
||    Global variables Declaration
||******************************************************************************/

/*******************************************************************************
||    static local variables Declaration
||******************************************************************************/

/*******************************************************************************
||    static Local Functions Declaration
||******************************************************************************/

/*******************************************************************************
||    Extern variables and functions declaration
||******************************************************************************/

// /********************************** Can Read Functions **********************************/
// /*******************************************************************************
// *Function            : uint8 RTE_NET_Can_Read_FridgeUnlockCtrl(void)
// *ReturnValue         : uint8
// *Parameters(in)        : None
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : uint8                        :Fridge unlock control status
// *Description        : Read Fridge Unlock Control signal(0x3ED)
// |******************************************************************************/
// uint8 RTE_NET_Can_Read_FridgeUnlockCtrl(void)
// {
//     return GetCanApp_u_FridgeUnlockCtrl();
// }

// /*******************************************************************************
// *Function            : uint8 RTE_NET_Can_Read_BcuOperMod(void)
// *ReturnValue         : uint8
// *Parameters(in)        : None
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : uint8                        :BCU operation mode
// *Description        : Read BCU Operation Mode signal(0x3D3)
// ||******************************************************************************/
// uint8 RTE_NET_Can_Read_BcuOperMod(void)
// {
//     return GetCanApp_u_BcuOperMod();
// }

// /********************************** Can Write Functions **********************************/
// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_FridgeErrSt(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write Fridge Error Status signal(0x3EE)
// |******************************************************************************/
// void RTE_NET_Can_Write_FridgeErrSt(uint8 LeRteCan_u_Value)
// {
//     /* Write fridge error status implementation */
//     WriteCanApp_FridgeErrSt(LeRteCan_u_Value);
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_FridgeDoorWarnTimeSt(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write Fridge Door Warning Time Status signal(0x3EE)
// ||******************************************************************************/
// void RTE_NET_Can_Write_FridgeDoorWarnTimeSt(uint8 LeRteCan_u_Value)
// {
//     /* Write fridge door warning time status implementation */
//     WriteCanApp_FridgeDoorWarnTimeSt(LeRteCan_u_Value);
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_FridgeChdLockSt(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write Fridge Child Lock Status signal(0x3EE)
// ||******************************************************************************/
// void RTE_NET_Can_Write_FridgeChdLockSt(uint8 LeRteCan_u_Value)
// {
//     /* Write fridge child lock status implementation */
//     WriteCanApp_FridgeChdLockSt(LeRteCan_u_Value);
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_EgySaveModSt(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write Energy Save Mode Status signal(0x3EE)
// ||******************************************************************************/
// void RTE_NET_Can_Write_EgySaveModSt(uint8 LeRteCan_u_Value)
// {
//     /* Write energy save mode status implementation */
//     WriteCanApp_EgySaveModSt(LeRteCan_u_Value);
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_FridgeWorkSt(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write Fridge Work Status signal(0x3EE)
// ||******************************************************************************/
// void RTE_NET_Can_Write_FridgeWorkSt(uint8 LeRteCan_u_Value)
// {
//     /* Write fridge work status implementation */
//     WriteCanApp_FridgeWorkSt(LeRteCan_u_Value);
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_FridgeQFunSt(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write Fridge Quick Function Status signal(0x3EE)
// ||******************************************************************************/
// void RTE_NET_Can_Write_FridgeQFunSt(uint8 LeRteCan_u_Value)
// {
//     /* Write fridge quick function status implementation */
//     WriteCanApp_FridgeQFunSt(LeRteCan_u_Value);
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_ContinueWorkTimeSt(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write Continue Work Time Status signal(0x3EE)
// ||******************************************************************************/
// void RTE_NET_Can_Write_ContinueWorkTimeSt(uint8 LeRteCan_u_Value)
// {
//     /* Write continue work time status implementation */
//     WriteCanApp_ContinueWorkTimeSt(LeRteCan_u_Value);
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_FridgeDoorWarnSt(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write Fridge Door Warning Status signal(0x3EE)
// ||******************************************************************************/
// void RTE_NET_Can_Write_FridgeDoorWarnSt(uint8 LeRteCan_u_Value)
// {
//     /* Write fridge door warning status implementation */
//     WriteCanApp_FridgeDoorWarnSt(LeRteCan_u_Value);
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_FridgeDoorSt(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write Fridge Door Status signal(0x3EE)
// ||******************************************************************************/
// void RTE_NET_Can_Write_FridgeDoorSt(uint8 LeRteCan_u_Value)
// {
//     /* Write fridge door status implementation */
//     WriteCanApp_FridgeDoorSt(LeRteCan_u_Value);
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_FridgeUVLedWorkSt(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write Fridge UV LED Work Status signal(0x3EE)
// ||******************************************************************************/
// void RTE_NET_Can_Write_FridgeUVLedWorkSt(uint8 LeRteCan_u_Value)
// {
//     /* Write fridge UV LED work status implementation */
//     WriteCanApp_FridgeUVLedWorkSt(LeRteCan_u_Value);
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_FridgeUVLedSt(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write Fridge UV LED Status signal(0x3EE)
// ||******************************************************************************/
// void RTE_NET_Can_Write_FridgeUVLedSt(uint8 LeRteCan_u_Value)
// {
//     /* Write fridge UV LED status implementation */
//     WriteCanApp_FridgeUVLedSt(LeRteCan_u_Value);
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_FridgeHeatActSt(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write Fridge Heat Act Status signal(0x3EE)
// ||******************************************************************************/
// void RTE_NET_Can_Write_FridgeHeatActSt(uint8 LeRteCan_u_Value)
// {
//     /* Write fridge heat act status implementation */
//     WriteCanApp_FridgeHeatActSt(LeRteCan_u_Value);
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_FridgestuffSt(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write Fridge Stuff Status signal(0x3EE)
// ||******************************************************************************/
// void RTE_NET_Can_Write_FridgestuffSt(uint8 LeRteCan_u_Value)
// {
//     /* Write fridge stuff status implementation */
//     WriteCanApp_FridgestuffSt(LeRteCan_u_Value);
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_FridgeModeSt(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write Fridge Mode Status signal(0x3EE)
// ||******************************************************************************/
// void RTE_NET_Can_Write_FridgeModeSt(uint8 LeRteCan_u_Value)
// {
//     /* Write fridge mode status implementation */
//     WriteCanApp_FridgeModeSt(LeRteCan_u_Value);
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_FridgeCoolTempSt(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write Fridge Cool Temperature Status signal(0x3EE)
// ||******************************************************************************/
// void RTE_NET_Can_Write_FridgeCoolTempSt(uint8 LeRteCan_u_Value)
// {
//     /* Write fridge cool temperature status implementation */
//     WriteCanApp_FridgeCoolTempSt(LeRteCan_u_Value);
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_FridgeHeatTempSt(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write Fridge Heat Temperature Status signal(0x3EE)
// ||******************************************************************************/
// void RTE_NET_Can_Write_FridgeHeatTempSt(uint8 LeRteCan_u_Value)
// {
//     /* Write fridge heat temperature status implementation */
//     WriteCanApp_FridgeHeatTempSt(LeRteCan_u_Value);
// }

// /****************** Can ID 0x3F3 Write Functions *********************/

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_VrhcuRequestACOn(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write VRHCU Request AC On signal(0x3F3)
// ||******************************************************************************/
// void RTE_NET_Can_Write_VrhcuRequestACOn(uint8 LeRteCan_u_Value)
// {
//     /* Write VRHCU request AC on implementation */
//     WriteCanApp_VrhcuRequestACOn(LeRteCan_u_Value);
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_VrhcuRefrAcpTemp(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write VRHCU Refrigerant AC Pressure Temperature signal(0x3F3)
// ||******************************************************************************/
// void RTE_NET_Can_Write_VrhcuRefrAcpTemp(uint8 LeRteCan_u_Value)
// {
//     /* Write VRHCU refrigerant AC pressure temperature implementation */
//     WriteCanApp_VrhcuRefrAcpTemp(LeRteCan_u_Value);
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_Vrhcupower(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write VRHCU Power signal(0x3F3)
// ||******************************************************************************/
// void RTE_NET_Can_Write_Vrhcupower(uint8 LeRteCan_u_Value)
// {
//     /* Write VRHCU power implementation */
//     WriteCanApp_Vrhcupower(LeRteCan_u_Value);
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_Write_VrhcuOffReas(uint8 LeRteCan_u_Value)
// *ReturnValue         : void
// *Parameters(in)        : LeRteCan_u_Value            :Write data value
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Write VRHCU Off Reason signal(0x3F3)
// ||******************************************************************************/
// void RTE_NET_Can_Write_VrhcuOffReas(uint8 LeRteCan_u_Value)
// {
//     /* Write VRHCU off reason implementation */
//     WriteCanApp_VrhcuOffReas(LeRteCan_u_Value);
// }

// /********************************** Can Main Functions **********************************/
// /*******************************************************************************
// *Function            : void RTE_NET_Can_10msMainFunction(void)
// *ReturnValue         : void
// *Parameters(in)        : None
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Can 10ms main function
// |******************************************************************************/
// void RTE_NET_Can_10msMainFunction(void)
// {
//     /* Can 10ms main function implementation */
// }

// /*******************************************************************************
// *Function            : void RTE_NET_Can_20msMainFunction(void)
// *ReturnValue         : void
// *Parameters(in)        : None
// *Parameters(in)        : None
// *Parameters(out)    : None                        
// *Return value        : None
// *Description        : Can 20ms main function
// |******************************************************************************/
// void RTE_NET_Can_20msMainFunction(void)
// {
//     /* Can 20ms main function implementation */
// }

