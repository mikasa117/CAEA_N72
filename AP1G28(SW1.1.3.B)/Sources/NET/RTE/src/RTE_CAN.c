/*******************************************************************************
||  File Name: RTE_CAN.c
||  Description: Implementation of the AUTOSAR Can Interface
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
#include "RTE_CAN.h"
#include "CanApp.h"
#include "CanNm_Cfg.h"
#include "Appl_Can_Callback.h"
#include "ccl_inc.h"

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

/********************************** Can Initialization **********************************/
/*******************************************************************************
*Function            : void RTE_NET_Can_Init(void)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Can module initialization
|******************************************************************************/
void RTE_NET_Can_Init(void)
{
    /* Can initialization implementation */
}

/********************************** Can Read Functions **********************************/
/*******************************************************************************
*Function            : uint32 RTE_NET_Can_Read_EspVehSpd(void)
*ReturnValue         : uint32
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint32                        :Estimated Vehicle Speed
*Description        : Read Estimated Vehicle Speed signal(0x1C3)
|******************************************************************************/
uint32 RTE_NET_Can_Read_EspVehSpd(void)/*0-46074375 y=5625x*/
{
    uint32 LeRte_u_RetVal = GetCanApp_u_EspVehSpd();

    LeRte_u_RetVal = 5625 * LeRte_u_RetVal;

    return LeRte_u_RetVal;
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_EspVehSpdVld(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :Estimated Vehicle Speed Valid status(0:Valid;1:Invalid)
*Description        : Read Estimated Vehicle Speed Valid signal(0x1C3)
|******************************************************************************/
uint8 RTE_NET_Can_Read_EspVehSpdVld(void)/*0-1*/
{
    return GetCanApp_u_EspVehSpdVld();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_VcuGearPosn(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        : Vehicle Control Unit Gear Position
*Description        : Read Vehicle Control Unit Gear Position signal(0x2EC)
|******************************************************************************/
uint8 RTE_NET_Can_Read_VcuGearPosn(void)/*0-7*/
{
    return GetCanApp_u_VcuGearPosn();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_VcuVehGearPosnVld(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        : Vehicle Control Unit Gear Position status(0:Valid;1:Invalid)
*Description        : Read Vehicle Control Unit Gear Position signal(0x2EC)
|******************************************************************************/
uint8 RTE_NET_Can_Read_VcuVehGearPosnVld(void)/*0-1*/
{
    return GetCanApp_u_VcuVehGearPosnVld();
}

/*******************************************************************************
*Function            : uint16 RTE_NET_Can_Read_CdcTotMilg(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint16                       : Total Mileage of CDC
*Description        : Read Total Mileage of CDC signal(0x2EF)
|******************************************************************************/
uint16 RTE_NET_Can_Read_CdcTotMilg(void)/*0-65535*/
{
    return GetCanApp_u_CdcTotMilg();
}


/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_TboxLocalTiDate(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        : Local Time Information Date
*Description        : Read Local Time Information Date signal(0x2F7)
|******************************************************************************/
uint8 RTE_NET_Can_Read_TboxLocalTiDate(void)/*0-31*/
{
    return GetCanApp_u_TboxLocalTiDate();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_TboxLocalTiHr(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        : Local Time Information Hour
*Description        : Read Local Time Information Hour signal(0x2F7)
|******************************************************************************/
uint8 RTE_NET_Can_Read_TboxLocalTiHr(void)/*0-31*/
{
    return GetCanApp_u_TboxLocalTiHr();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_TboxLocalTiMins(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        : Local Time Information Minutes
*Description        : Read Local Time Information Minutes signal(0x2F7)
|******************************************************************************/
uint8 RTE_NET_Can_Read_TboxLocalTiMins(void)/*0-63*/
{
    return GetCanApp_u_TboxLocalTiMins();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_TboxLocalTiMth(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        : Local Time Information Month
*Description        : Read Local Time Information Month signal(0x2F7)
|******************************************************************************/
uint8 RTE_NET_Can_Read_TboxLocalTiMth(void)/*0-15*/
{
    return GetCanApp_u_TboxLocalTiMth();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_TboxLocalTiSec(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        : Local Time Information Seconds
*Description        : Read Local Time Information Seconds signal(0x2F7)
|******************************************************************************/
uint8 RTE_NET_Can_Read_TboxLocalTiSec(void)/*0-63*/
{
    return GetCanApp_u_TboxLocalTiSec();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_TboxLocalTiVld(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        : Telematics Box Local Time Information Valid status(0:Valid;1:Invalid)
*Description        : Read Telematics Box Local Time Information Valid signal(0x2F7)
|******************************************************************************/
uint8 RTE_NET_Can_Read_TboxLocalTiVld(void)/*0-1*/
{
    return GetCanApp_u_TboxLocalTiVld();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_TboxLocalTiYear(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        : Local Time Information Year
*Description        : Read Local Time Information Year signal(0x2F7)
|******************************************************************************/
uint16 RTE_NET_Can_Read_TboxLocalTiYear(void)/*2000-2255 y=x+2000*/
{
    uint16 LeRte_u_RetVal = GetCanApp_u_TboxLocalTiYear();

    LeRte_u_RetVal = LeRte_u_RetVal + 2000U;

    return LeRte_u_RetVal;
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_FridgeUnlockCtrl(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :Fridge unlock control status
*Description        : Read Fridge Unlock Control signal(0x3ED)
|******************************************************************************/
uint8 RTE_NET_Can_Read_FridgeUnlockCtrl(void)/*0-3*/
{
    return GetCanApp_u_FridgeUnlockCtrl();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_FridgeDoorWarnTimeSet(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :Fridge door warning time setting
*Description        : Read Fridge Door Warning Time Set signal(0x3ED)
||******************************************************************************/
uint8 RTE_NET_Can_Read_FridgeDoorWarnTimeSet(void)/*0-4*/
{
    return GetCanApp_u_FridgeDoorWarnTimeSet(); 
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_FridgeChdLockReq(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :Fridge child lock request status
*Description        : Read Fridge Child Lock Request signal(0x3ED)
||******************************************************************************/
uint8 RTE_NET_Can_Read_FridgeChdLockReq(void)/*0-3*/
{
    return GetCanApp_u_FridgeChdLockReq(); 
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_EgySaveModReq(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :Energy save mode request status
*Description        : Read Energy Save Mode Request signal(0x3ED)
||******************************************************************************/
uint8 RTE_NET_Can_Read_EgySaveModReq(void)/*0-3*/
{
    return GetCanApp_u_EgySaveModReq();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_FridgeWorkReq(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :Fridge work request status
*Description        : Read Fridge Work Request signal(0x3ED)
||******************************************************************************/
uint8 RTE_NET_Can_Read_FridgeWorkReq(void)/*0-3*/
{
    return GetCanApp_u_FridgeWorkReq();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_FridgeQFunReq(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :Fridge quick function request status
*Description        : Read Fridge Quick Function Request signal(0x3ED)
||******************************************************************************/
uint8 RTE_NET_Can_Read_FridgeQFunReq(void)/*0-15*/
{
    return GetCanApp_u_FridgeQFunReq();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_ContinueWorkSw(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :Continue work switch status
*Description        : Read Continue Work Switch signal(0x3ED)
||******************************************************************************/
uint8 RTE_NET_Can_Read_ContinueWorkSw(void)/*0-3*/
{
    return GetCanApp_u_ContinueWorkSw();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_ContinueWorkTimeSet(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :Continue work time setting
*Description        : Read Continue Work Time Set signal(0x3ED)
||******************************************************************************/
uint8 RTE_NET_Can_Read_ContinueWorkTimeSet(void)/*0-24*/
{
    return GetCanApp_u_ContinueWorkTimeSet();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_FridgeUVLedReq(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :Fridge UV LED request status
*Description        : Read Fridge UV LED Request signal(0x3ED)
||******************************************************************************/
uint8 RTE_NET_Can_Read_FridgeUVLedReq(void)/*0-3*/
{
    return GetCanApp_u_FridgeUVLedReq();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_FridgeUVLedWorkTimeSet(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :Fridge UV LED work time setting
*Description        : Read Fridge UV LED Work Time Set signal(0x3ED)
||******************************************************************************/
uint8 RTE_NET_Can_Read_FridgeUVLedWorkTimeSet(void)/*0-31*/
{
    return GetCanApp_u_FridgeUVLedWorkTimeSet();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_FridgeModeReq(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :Fridge mode request status
*Description        : Read Fridge Mode Request signal(0x3ED)
||******************************************************************************/
uint8 RTE_NET_Can_Read_FridgeModeReq(void)/*0-3*/
{
    return GetCanApp_u_FridgeModeReq();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_FridgeCoolTempReq(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :Fridge cool temperature request
*Description        : Read Fridge Cool Temperature Request signal(0x3ED)
||******************************************************************************/
uint8 RTE_NET_Can_Read_FridgeCoolTempReq(void)/*0-31*/
{
    return GetCanApp_u_FridgeCoolTempReq();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_FridgeHeatTempReq(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :Fridge heat temperature request
*Description        : Read Fridge Heat Temperature Request signal(0x3ED)
||******************************************************************************/
uint8 RTE_NET_Can_Read_FridgeHeatTempReq(void)/*0-31*/
{
    return GetCanApp_u_FridgeHeatTempReq();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_VrhcuExOffReas(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :VRHCU external off reason
*Description        : Read VRHCU External Off Reason signal(0x3ED)
||******************************************************************************/
uint8 RTE_NET_Can_Read_VrhcuExOffReas(void)/*0-3*/
{
    return GetCanApp_u_VrhcuExOffReas();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_VrhcuONReas(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :VRHCU ON reason
*Description        : Read VRHCU ON Reason signal(0x3ED)
||******************************************************************************/
uint8 RTE_NET_Can_Read_VrhcuONReas(void)/*0-2*/
{
    return GetCanApp_u_VrhcuONReas();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_BcmPwrStsFb(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :BCM power status feedback
*Description        : Read BCM Power Status Feedback signal(0x288)
||******************************************************************************/
uint8 RTE_NET_Can_Read_BcmPwrStsFb(void)/*0-3*/
{
    return GetCanApp_u_BcmPwrStsFb();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_DcdcOperSts(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :DCDC operation status
*Description        : Read DCDC Operation Status signal(0x3D1)
||******************************************************************************/
uint8 RTE_NET_Can_Read_DcdcOperSts(void)/*0-15*/
{
    return GetCanApp_u_DcdcOperSts();
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_BcuOperMod(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :BCU operation mode
*Description        : Read BCU Operation Mode signal(0x3D3)
||******************************************************************************/
uint8 RTE_NET_Can_Read_BcuOperMod(void)/*0-15*/
{
    return GetCanApp_u_BcuOperMod();
}

/********************************** Can Write Functions **********************************/
/*******************************************************************************
*Function            : void RTE_NET_Can_Write_FridgeErrSt(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write Fridge Error Status signal(0x3EE)
|******************************************************************************/
void RTE_NET_Can_Write_FridgeErrSt(uint8 LeRteCan_u_Value)/*0-31*/
{
    /* Write fridge error status implementation */
    WriteCanApp_FridgeErrSt(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_FridgeDoorWarnTimeSt(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write Fridge Door Warning Time Status signal(0x3EE)
||******************************************************************************/
void RTE_NET_Can_Write_FridgeDoorWarnTimeSt(uint8 LeRteCan_u_Value)/*0-3*/
{
    /* Write fridge door warning time status implementation */
    WriteCanApp_FridgeDoorWarnTimeSt(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_FridgeChdLockSt(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write Fridge Child Lock Status signal(0x3EE)
||******************************************************************************/
void RTE_NET_Can_Write_FridgeChdLockSt(uint8 LeRteCan_u_Value)/*0-3*/
{
    /* Write fridge child lock status implementation */
    WriteCanApp_FridgeChdLockSt(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_EgySaveModSt(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write Energy Save Mode Status signal(0x3EE)
||******************************************************************************/
void RTE_NET_Can_Write_EgySaveModSt(uint8 LeRteCan_u_Value)/*0-3*/
{
    /* Write energy save mode status implementation */
    WriteCanApp_EgySaveModSt(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_FridgeWorkSt(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write Fridge Work Status signal(0x3EE)
||******************************************************************************/
void RTE_NET_Can_Write_FridgeWorkSt(uint8 LeRteCan_u_Value)/*0-3*/
{
    /* Write fridge work status implementation */
    WriteCanApp_FridgeWorkSt(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_FridgeQFunSt(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write Fridge Quick Function Status signal(0x3EE)
||******************************************************************************/
void RTE_NET_Can_Write_FridgeQFunSt(uint8 LeRteCan_u_Value)/*0-15*/
{
    /* Write fridge quick function status implementation */
    WriteCanApp_FridgeQFunSt(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_ContinueWorkTimeSt(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write Continue Work Time Status signal(0x3EE)
||******************************************************************************/
void RTE_NET_Can_Write_ContinueWorkTimeSt(uint8 LeRteCan_u_Value)/*0-24*/
{
    /* Write continue work time status implementation */
    WriteCanApp_ContinueWorkTimeSt(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_FridgeDoorWarnSt(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write Fridge Door Warning Status signal(0x3EE)
||******************************************************************************/
void RTE_NET_Can_Write_FridgeDoorWarnSt(uint8 LeRteCan_u_Value)/*0-3*/
{
    /* Write fridge door warning status implementation */
    WriteCanApp_FridgeDoorWarnSt(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_FridgeDoorSt(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write Fridge Door Status signal(0x3EE)
||******************************************************************************/
void RTE_NET_Can_Write_FridgeDoorSt(uint8 LeRteCan_u_Value)/*0-3*/
{
    /* Write fridge door status implementation */
    WriteCanApp_FridgeDoorSt(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_FridgeUVLedWorkSt(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write Fridge UV LED Work Status signal(0x3EE)
||******************************************************************************/
void RTE_NET_Can_Write_FridgeUVLedWorkSt(uint8 LeRteCan_u_Value)/*0-31*/
{
    /* Write fridge UV LED work status implementation */
    WriteCanApp_FridgeUVLedWorkSt(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_FridgeUVLedSt(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write Fridge UV LED Status signal(0x3EE)
||******************************************************************************/
void RTE_NET_Can_Write_FridgeUVLedSt(uint8 LeRteCan_u_Value)/*0-3*/
{
    /* Write fridge UV LED status implementation */
    WriteCanApp_FridgeUVLedSt(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_FridgeHeatActSt(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write Fridge Heat Act Status signal(0x3EE)
||******************************************************************************/
void RTE_NET_Can_Write_FridgeHeatActSt(uint8 LeRteCan_u_Value)/*0-127*/
{
    /* Write fridge heat act status implementation */
    WriteCanApp_FridgeHeatActSt(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_FridgestuffSt(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write Fridge Stuff Status signal(0x3EE)
||******************************************************************************/
void RTE_NET_Can_Write_FridgestuffSt(uint8 LeRteCan_u_Value)/*0-3*/
{
    /* Write fridge stuff status implementation */
    WriteCanApp_FridgestuffSt(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_FridgeModeSt(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write Fridge Mode Status signal(0x3EE)
||******************************************************************************/
void RTE_NET_Can_Write_FridgeModeSt(uint8 LeRteCan_u_Value)/*0-3*/
{
    /* Write fridge mode status implementation */
    WriteCanApp_FridgeModeSt(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_FridgeCoolTempSt(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write Fridge Cool Temperature Status signal(0x3EE)
||******************************************************************************/
void RTE_NET_Can_Write_FridgeCoolTempSt(uint8 LeRteCan_u_Value)/*0-31*/
{
    /* Write fridge cool temperature status implementation */
    WriteCanApp_FridgeCoolTempSt(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_FridgeHeatTempSt(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write Fridge Heat Temperature Status signal(0x3EE)
||******************************************************************************/
void RTE_NET_Can_Write_FridgeHeatTempSt(uint8 LeRteCan_u_Value)/*0-31*/
{
    /* Write fridge heat temperature status implementation */
    WriteCanApp_FridgeHeatTempSt(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_VRHCP_WakeUp_BYTE3BIT0(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write VRHCP WakeUp BYTE3BIT0 signal(0x6F9)
||******************************************************************************/
void RTE_NET_Can_Write_VRHCP_WakeUp_BYTE3BIT0(uint8 LeRteCan_u_Value)/*0-1*/
{
    /* Write VRHCP wake up byte3 bit0 implementation */
    WriteCanApp_VRHCP_WakeUp_BYTE3BIT0(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_VRHCP_NotSleep_BYTE7BIT0(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write VRHCP NotSleep BYTE7BIT0 signal(0x6F9)
||******************************************************************************/
void RTE_NET_Can_Write_VRHCP_NotSleep_BYTE7BIT0(uint8 LeRteCan_u_Value)/*0-1*/
{
    /* Write VRHCP not sleep byte7 bit0 implementation */
    WriteCanApp_VRHCP_NotSleep_BYTE7BIT0(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_VRHCP_NotSleep_BYTE7BIT1(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write VRHCP NotSleep BYTE7BIT1 signal(0x6F9)
||******************************************************************************/
void RTE_NET_Can_Write_VRHCP_NotSleep_BYTE7BIT1(uint8 LeRteCan_u_Value)/*0-1*/
{
    /* Write VRHCP not sleep byte7 bit1 implementation */
    WriteCanApp_VRHCP_NotSleep_BYTE7BIT1(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_VRHCP_NotSleep_BYTE7BIT2(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write VRHCP NotSleep BYTE7BIT2 signal(0x6F9)
||******************************************************************************/
void RTE_NET_Can_Write_VRHCP_NotSleep_BYTE7BIT2(uint8 LeRteCan_u_Value)/*0-1*/
{
    /* Write VRHCP not sleep byte7 bit2 implementation */
    WriteCanApp_VRHCP_NotSleep_BYTE7BIT2(LeRteCan_u_Value);
}

/****************** Can ID 0x3F3 Write Functions *********************/

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_VrhcuRequestACOn(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write VRHCU Request AC On signal(0x3F3)
||******************************************************************************/
void RTE_NET_Can_Write_VrhcuRequestACOn(uint8 LeRteCan_u_Value)/*0-1*/
{
    /* Write VRHCU request AC on implementation */
    WriteCanApp_VrhcuRequestACOn(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_VrhcuRefrAcpTemp(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write VRHCU Refrigerant AC Pressure Temperature signal(0x3F3)
||******************************************************************************/
void RTE_NET_Can_Write_VrhcuRefrAcpTemp(sint8 LeRteCan_u_Value)/*-10-60*/
{
    sint8 LeSeRteCan_w_Result = LeRteCan_u_Value; 
    LeSeRteCan_w_Result = LeSeRteCan_w_Result +10;/*y=x-10 -> x=y+10*/
    
    /* Write VRHCU refrigerant AC pressure temperature implementation */
    WriteCanApp_VrhcuRefrAcpTemp((uint8)LeSeRteCan_w_Result);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_Vrhcupower(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write VRHCU Power signal(0x3F3)
||******************************************************************************/
void RTE_NET_Can_Write_Vrhcupower(uint8 LeRteCan_u_Value)/*1-100*/
{
    /* Write VRHCU power implementation */
    WriteCanApp_Vrhcupower(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_VrhcuOffReas(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write VRHCU Off Reason signal(0x3F3)
||******************************************************************************/
void RTE_NET_Can_Write_VrhcuOffReas(uint8 LeRteCan_u_Value)/*0-3*/
{
    /* Write VRHCU off reason implementation */
    WriteCanApp_VrhcuOffReas(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_VrhcuDTC1_HighByte(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write VRHCU DTC1 High Byte signal(0x6EE)
||******************************************************************************/
void RTE_NET_Can_Write_VrhcuDTC1_HighByte(uint8 LeRteCan_u_Value)/*0-255*/
{
    /* Write VRHCU DTC1 high byte implementation */
    WriteCanApp_VrhcuDTC1_HighByte(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_VrhcuDTC1_LowByte(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write VRHCU DTC1 Low Byte signal(0x6EE)
||******************************************************************************/
void RTE_NET_Can_Write_VrhcuDTC1_LowByte(uint8 LeRteCan_u_Value)/*0-255*/
{
    /* Write VRHCU DTC1 low byte implementation */
    WriteCanApp_VrhcuDTC1_LowByte(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_VrhcuDTC1_MiddByte(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write VRHCU DTC1 Middle Byte signal(0x6EE)
||******************************************************************************/
void RTE_NET_Can_Write_VrhcuDTC1_MiddByte(uint8 LeRteCan_u_Value)/*0-255*/
{
    /* Write VRHCU DTC1 middle byte implementation */
    WriteCanApp_VrhcuDTC1_MiddByte(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_VrhcuDTC1_Status(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write VRHCU DTC1 Status signal(0x6EE)
||******************************************************************************/
void RTE_NET_Can_Write_VrhcuDTC1_Status(uint8 LeRteCan_u_Value)/*0-255*/
{
    /* Write VRHCU DTC1 status implementation */
    WriteCanApp_VrhcuDTC1_Status(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_VrhcuDTC2_HighByte(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write VRHCU DTC2 High Byte signal(0x6EE)
||******************************************************************************/
void RTE_NET_Can_Write_VrhcuDTC2_HighByte(uint8 LeRteCan_u_Value)/*0-255*/
{
    /* Write VRHCU DTC2 high byte implementation */
    WriteCanApp_VrhcuDTC2_HighByte(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_VrhcuDTC2_LowByte(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write VRHCU DTC2 Low Byte signal(0x6EE)
||******************************************************************************/
void RTE_NET_Can_Write_VrhcuDTC2_LowByte(uint8 LeRteCan_u_Value)/*0-255*/
{
    /* Write VRHCU DTC2 low byte implementation */
    WriteCanApp_VrhcuDTC2_LowByte(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_VrhcuDTC2_MiddByte(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write VRHCU DTC2 Middle Byte signal(0x6EE)
||******************************************************************************/
void RTE_NET_Can_Write_VrhcuDTC2_MiddByte(uint8 LeRteCan_u_Value)/*0-255*/
{
    /* Write VRHCU DTC2 middle byte implementation */
    WriteCanApp_VrhcuDTC2_MiddByte(LeRteCan_u_Value);
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_VrhcuDTC2_Status(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write VRHCU DTC2 Status signal(0x6EE)
||******************************************************************************/
void RTE_NET_Can_Write_VrhcuDTC2_Status(uint8 LeRteCan_u_Value)/*0-255*/
{
    /* Write VRHCU DTC2 status implementation */
    WriteCanApp_VrhcuDTC2_Status(LeRteCan_u_Value);
}

/********************************** Diagnostic Functions ID**********************************/
/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Read_DiagRequest(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Read data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Read Diagnostic Request signal(0x777)
||******************************************************************************/
uint8 RTE_NET_Can_Read_DiagRequest(uint8 LeRteCan_u_Value)
{
    return 0;    /* Write diagnostic request implementation */
}

/*******************************************************************************
*Function            : void RTE_NET_Can_Write_DiagResponse(uint8 LeRteCan_u_Value)
*ReturnValue         : void
*Parameters(in)        : LeRteCan_u_Value            :Write data value
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Write Diagnostic Response signal(0x77F)
||******************************************************************************/
void RTE_NET_Can_Write_DiagResponse(uint8 LeRteCan_u_Value)
{
    /* Write diagnostic response implementation */
}


/********************************** Timeout Functions **********************************/
/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Timeout_0x1C3_Msg(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :0x1C3 message timeout status (0=timeout, 1=normal)
*Description        : Check 0x1C3 Message Timeout status(0x1C3)
||******************************************************************************/
uint8 RTE_NET_Can_Timeout_0x1C3_Msg(void)
{
    return GetCanApp_u_MsgCurrentPresent(VeCanApp_e_VIU_FR_1C3);
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Timeout_0x2EC_Msg(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :0x2EC message timeout status (0=timeout, 1=normal)
*Description        : Check 0x2EC Message Timeout status(0x2EC)
||******************************************************************************/
uint8 RTE_NET_Can_Timeout_0x2EC_Msg(void)
{
    return GetCanApp_u_MsgCurrentPresent(VeCanApp_e_VIU_FR_2EC);
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Timeout_0x2EF_Msg(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :0x2EF message timeout status (0=timeout, 1=normal)
*Description        : Check 0x2EF Message Timeout status(0x2EF)
||******************************************************************************/
uint8 RTE_NET_Can_Timeout_0x2EF_Msg(void)
{
    return GetCanApp_u_MsgCurrentPresent(VeCanApp_e_VIU_FR_2EF);
}
/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Timeout_0x2F7_Msg(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :0x2F7 message timeout status (0=timeout, 1=normal)
*Description        : Check 0x2F7 Message Timeout status(0x2F7)
||******************************************************************************/
uint8 RTE_NET_Can_Timeout_0x2F7_Msg(void)
{
    return GetCanApp_u_MsgCurrentPresent(VeCanApp_e_VIU_FR_2F7);
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Timeout_0x3ED_Msg(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :3ED message timeout status (0=timeout, 1=normal)
*Description        : Check 3ED Message Timeout status(0x3ED)
||******************************************************************************/
uint8 RTE_NET_Can_Timeout_0x3ED_Msg(void)
{
    return GetCanApp_u_MsgCurrentPresent(VeCanApp_e_VIU_FR_3ED);
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Timeout_0x288_Msg(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :0x288 message timeout status (0=timeout, 1=normal)
*Description        : Check 0x288 Message Timeout status(0x288)
||******************************************************************************/
uint8 RTE_NET_Can_Timeout_0x288_Msg(void)
{
    return GetCanApp_u_MsgCurrentPresent(VeCanApp_e_VIU_FR_288);
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Timeout_0x3D1_Msg(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :0x3D1 message timeout status (0=timeout, 1=normal)
*Description        : Check 0x3D1 Message Timeout status(0x3D1)
||******************************************************************************/
uint8 RTE_NET_Can_Timeout_0x3D1_Msg(void)
{
    return GetCanApp_u_MsgCurrentPresent(VeCanApp_e_VIU_FR_3D1);
}
/*******************************************************************************
*Function            : uint8 RTE_NET_Can_Timeout_0x3D3_Msg(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :0x3D3 message timeout status (0=timeout, 1=normal)
*Description        : Check 0x3D3 Message Timeout status(0x3D3)
||******************************************************************************/
uint8 RTE_NET_Can_Timeout_0x3D3_Msg(void)
{
    return GetCanApp_u_MsgCurrentPresent(VeCanApp_e_VIU_FR_3D3);
}

/********************************** Can BusOff Functions **********************************/
/*******************************************************************************
*Function            : uint8 RTE_NET_Can_BusOff(void)
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint8                        :Can bus off status (0=normal, 1=bus off)
*Description        : Check Can Bus Off status(System Level)
||******************************************************************************/
uint8 RTE_NET_Can_BusOff(void)
{
    return CanApp_u_GetBusOffStaus();
}

/********************************** Can communicate Stop and Start **********************************/
/*******************************************************************************
*Function            : void RTE_NET_Can_IlRxStop(void)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Can Receive Stop
||******************************************************************************/
void RTE_NET_Can_IlRxStop(void)
{
   IlRxStop();
}

/*******************************************************************************
*Function            : void RTE_NET_Can_IlRxStart(void)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Can Receive Start
||******************************************************************************/
void RTE_NET_Can_IlRxStart(void)
{
   IlRxStart();
}

/*******************************************************************************
*Function            : void RTE_NET_Can_IlTxStop(void)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Can Transmit Stop
||******************************************************************************/
void RTE_NET_Can_IlTxStop(void)
{
   IlRxStop();
}

/*******************************************************************************
*Function            : void RTE_NET_Can_IlTxStart(void)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Can Transmit Start
||******************************************************************************/
void RTE_NET_Can_IlTxStart(void)
{
   IlTxStart();
}

/********************************** Can Main Functions **********************************/
/*******************************************************************************
*Function            : void RTE_NET_Can_10msMainFunction(void)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Can 10ms main function
|******************************************************************************/
void RTE_NET_Can_10msMainFunction(void)
{
    /* Can 10ms main function implementation */
}

/*******************************************************************************
*Function            : void RTE_NET_Can_20msMainFunction(void)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Can 20ms main function
|******************************************************************************/
void RTE_NET_Can_20msMainFunction(void)
{
    /* Can 20ms main function implementation */
}

/*******************************************************************************
*Function            : void RteCan_SetPositiveReqNet(uint8 LeRteCan_u_ReqNetFlag)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Set up a positive communication request
|******************************************************************************/
void RteCan_SetPositiveReqNet(uint8 LeRteCan_u_ReqNetFlag)
{
    CanApp_SetPositiveReqNet(LeRteCan_u_ReqNetFlag);
}

/*******************************************************************************
*Function            : uint8 RteCan_GetNetworkSleepAllowed(void)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Get network sleep allowed flag(0U=SleepAllowed,1U=SleepNoAllowed)
|******************************************************************************/
uint8 RteCan_GetNetworkSleepAllowed(void)
{
    return (1 - GetCanApp_u_NetWorkSleepAllowed());
}

/*******************************************************************************
*Function            : void RteCan_EnableImmediateNmTx(void)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Enable the immediate transmission of network management messages
|******************************************************************************/
void RteCan_EnableImmediateNmTx(void)
{
    CanApp_EnableImmediateNmTx();
}

/*******************************************************************************
*Function            : void RteCan_DisableImmediateNmTx(void)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Disable the immediate transmission of network management messages
|******************************************************************************/
void RteCan_DisableImmediateNmTx(void)
{
    CanApp_DisableImmediateNmTx();
}

/*******************************************************************************
*Function            : uint8 RteCan_CanApp_GetWakeUpSource_Nm(void)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Get the NM wake-up flag(0U=no wakeup,1U=Nm wakeup)
|******************************************************************************/
uint8 RteCan_CanApp_GetWakeUpSource_Nm(void)
{
    return CanApp_GetWakeUpSource_Nm();
}

/*******************************************************************************
*Function            : uint8 RteCan_CanApp_GetAwakeSource_Nm(void)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Get the NM wake-up flag(0U=no Nm awake,1U=Nm awake)
|******************************************************************************/
uint8 RteCan_CanApp_GetAwakeSource_Nm(void)
{
    return CanApp_GetAwakeSource_Nm();
}

/*******************************************************************************
*Function            : uint8 RteCan_CanApp_GetAwakeSource_Nm(void)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Get the NM wake-up flag(0U=no Diag awake,1U=Diag awake)
|******************************************************************************/
uint8 RteCan_CanApp_GetDiagReqNetFlag(void)
{
    uint8 LeApplCan_u_Ret = 0U;
    if(0U != CanApp_GetDiagReqNetFlag())
    {
        LeApplCan_u_Ret = 1U;
    }
    return LeApplCan_u_Ret;
}

/*******************************************************************************
*Function            : void RteCan_CanBusWakeupInt(void)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Wake up can bus
|******************************************************************************/
void RteCan_CanBusWakeupInt(void)
{
    CclCanWakeUpInt();
}
