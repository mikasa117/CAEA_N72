 /*******************************************************************************
|  File Name: 
|  Description: Implementation of the AUTOSAR CAN Interface
|-------------------------------------------------------------------------------
|  (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      ---------------------  -----------------------------------------
|                                    CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------


|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "ccl.h"
#include "Can_Trcv.h"
#include "sdk_project_config.h"
#include "pins_driver.h"
#include "STD_McuIf.h"
#include "STD_BtrCtr.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/



/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
#define OV_UV_CONTROL_COM
#define NOT_ENABLED_C_MODE          (0u)
#define MODE_C_ENABLED              (1u)
#define CANTRCV_WAKEUP_ACTIVE       (1u)
#define CANTRCV_WAKEUP_PASSIVE      (0u)
/*******************************************************************************
|    Global variables Declaration
|******************************************************************************/

/******************************************************************************/


/*******************************************************************************
|    static local variables Declaration
|******************************************************************************/
static vuint8 SeCanTrcv_u_CurrentMode;
static vuint8 SeCanTrcv_u_ModeCDisabled = false;
/* wakeup mode set by upper layer: default passive */
static vuint8 SeCanTrcv_u_WakeupMode = CANTRCV_WAKEUP_PASSIVE;
/*******************************************************************************
|    static Local Functions Declaration
|******************************************************************************/
static void CanTrcv_HandlePassiveWakeup(void);


/*******************************************************************************
|    Extern variables and functions declaration
|******************************************************************************/


/*******************************************************************************
|    Function Source Code
|******************************************************************************/

/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/ 
uint8 GetCanTrcv_CurrentMode(void)
{
    return SeCanTrcv_u_CurrentMode;
}
/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :��������������������������������������������������������
History
<No.>    <author>    <time>    <description>

|******************************************************************************/ 
void CanTrcv_WakeupClearFlag(void)
{
    /*ClrCanApp_IcuFlag();*/
}
/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :������������
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CanTrcv_DisableWakeup(void)
{
    PINS_DRV_ClearPortIntFlagCmd(GPIOA);/*CAN RX PA12*/
    PINS_DRV_SetPinIntSel(GPIOA,12U,PCTRL_DMA_INT_DISABLED);
    PINS_DRV_SetMuxModeSel(PCTRLA,12U,PCTRL_MUX_ALT3);/*CAN RX Mode*/
    McuIf_DisableIRQ(MCUIF_PORTA_IRQn);
}
/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :����������������
History
<No.>    <author>    <time>    <description>

|******************************************************************************/ 
void CanTrcv_EnableWakeup(void)
{
    PINS_DRV_SetMuxModeSel(PCTRLA,12U,PCTRL_MUX_AS_GPIO);/*GPIO Mode*/
    PINS_DRV_ClearPortIntFlagCmd(GPIOA);/*CAN RX PA12*/
    PINS_DRV_SetPinIntSel(GPIOA,12U,PCTRL_INT_FALLING_EDGE);
    McuIf_EnableIRQ(MCUIF_PORTA_IRQn);
}

/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :��������������Normal����������������
History
<No.>    <author>    <time>    <description>

|******************************************************************************/ 
void CanTrcv_WakeUpTrcv(void)
{
    PINS_DRV_SetPins(GPIOA,1<<11);/*CAN EN  PA11*/
    PINS_DRV_SetPins(GPIOE,1<<1);/*CAN STB  PE1*/
    SeCanTrcv_u_CurrentMode = CeCanTrcv_e_Normalmode;
}
/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :��������������Standy����������������
History
<No.>    <author>    <time>    <description>

|******************************************************************************/ 
void CanTrcv_DisableTrcv(void)
{
    PINS_DRV_ClearPins(GPIOA,1<<11);/*CAN EN  PA11*/
    PINS_DRV_ClearPins(GPIOE,1<<1);/*CAN STB  PE1*/
    SeCanTrcv_u_CurrentMode = CeCanTrcv_e_Standbymode;    
}


static void CanTrcv_HandlePassiveWakeup(void)
{
#ifdef OV_UV_CONTROL_COM
    vuint8 batteryStatus = BTRCTR_GetSysBatteryModeCStatus();

    if (batteryStatus == MODE_C_ENABLED)
    {
        if (SeCanTrcv_u_CurrentMode != CeCanTrcv_e_Standbymode)
        {
            CanTrcv_DisableTrcv();
        }
        SeCanTrcv_u_ModeCDisabled = true;
    }
    else if (SeCanTrcv_u_ModeCDisabled != false)
    {
        CanTrcv_WakeUpTrcv();
        SeCanTrcv_u_ModeCDisabled = false;
    }
#endif
}

/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/ 
void CanTrcv_DummyFun(void)
{
}

/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/ 
uint8 CanTrcv_CheckWakeup(void)
{
    return 1u;
}

/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/ 
/* API: called by upper layer to inform transceiver of current wakeup mode */
void CanTrcv_SetWakeupMode(uint8 mode)
{
    SeCanTrcv_u_WakeupMode = (mode != 0U) ? CANTRCV_WAKEUP_ACTIVE : CANTRCV_WAKEUP_PASSIVE;
}

/*******************************************************************************
Name            :
Syntax            : 
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None
Parameters(out) : None
Return value    : None
Description        :
Call By            :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/ 
void CanTrcv_MainFunction(void)
{
/*    if((uint8)CeCanTrcv_e_Normalmode != SeCanTrcv_u_CurrentMode)
    {
        CclCanWakeUpInt();
    }
*/

    if (SeCanTrcv_u_WakeupMode == CANTRCV_WAKEUP_ACTIVE)
    {
        return;
    }

    CanTrcv_HandlePassiveWakeup();
}

/* polyspace:end<MISRA-C3:10.1:Not a defect:Justified> NO fluence */











