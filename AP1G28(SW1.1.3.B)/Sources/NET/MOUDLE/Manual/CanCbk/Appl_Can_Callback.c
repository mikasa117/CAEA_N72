/*******************************************************************************
|  File Name:  Can_Main.c
|  Description:  Implementation of the Dem_DTC_Detection Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| 
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date        Version   Author  Description
| ----------  --------  ------  ------------------------------------------------
| 2016-10-11  V1.0      chenf   first implementation

|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#define NM_ASRNMCANWRAPPEREXT_SOURCE

#include "can_cfg.h"
#include "can_def.h"
#include "drv_par.h"
#include "CanApp.h"
#include "Appl_Can_Callback.h"
#include "Nm_Cbk.h"
//#include "STD_PowerMode_Cfg.h"
#include "CanNm.h"
#include "NmCbdWrp.h"
#include "can_par.h"
#include "il_def.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define CeCanCbk_u_BasicNMID      (vuint16)0x400
#define CeCanCbk_u_MaxNMID        (vuint16)0x4FF
#define CeCanCbk_u_DiagPhyID      (vuint16)0x777
#define CeCanCbk_u_DiagFunID      (vuint16)0x7DF

#define CeCanCbk_u_NMRESERVEDBITS (vuint8)0xE6
#define CeCanCbk_u_NmMsgDataLen   6u
#define ilTxHandle_VRHCU_6F9      (0u)
#define ilTxHandle_VRHCU_6EE      (1u)
#define ilTxHandle_VRHCU_3F3      (2u)
#define ilTxHandle_VRHCU_3EE      (3u)

/*define for 0x3EE-->FridgeDoorWarnSt*/
#define FRIDGE_WARN_MASK      0xC0u      /* bits 7-6 */
#define FRIDGE_WARN_SHIFT     6
#define FRIDGE_WARN_NORMAL    1u
#define FRIDGE_WARN_ACTIVE    2u
#define FRIDGE_WARN_OVERRIDE_THRESHOLD  3u
/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Global variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/
static uint8 ApplCanWakeupFlag = 0x00u;
static uint8 ApplCanBussleepToRepeatFlag = 0x00u;
static uint8 ApplCanNmNodeID = 0x00U;
uint16 ApplCan_u_AppMsgKeepAliveTimer = 0u;

static uint8 FridgeDoorWarnSt_Previous = 0u;
static uint8 FridgeDoorWarnSt_Counter = 0u;

/*******************************************************************************
|    static Local Functions Declaration
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
vuint8 ApplCanMsgReceived(CanRxInfoStructPtr rxStruct)
{
    vuint16 currentCanId; /* 16 bit IDs */
    vuint8 currentCanDlc;
    vuint8 currentRetVal = kCanCopyData; 

    currentCanId =(vuint16)CanRxActualId(rxStruct);
    currentCanDlc = (vuint8)CanRxActualDLC(rxStruct);
    
    if((CeCanCbk_u_BasicNMID <= currentCanId)&&(CeCanCbk_u_MaxNMID >= currentCanId))
    {
        if((currentCanDlc == (uint8)0x08) && (0x00U ==(CeCanCbk_u_NMRESERVEDBITS & CanRxActualData(rxStruct,1U))) &&
           (0x00U == CanRxActualData(rxStruct,2U)) && (0x00U == CanRxActualData(rxStruct,3U)) && 
           (0x00U == CanRxActualData(rxStruct,4U)) && (0x00U ==(0x7F & CanRxActualData(rxStruct,5U))) && 
           (0x00U == CanRxActualData(rxStruct,6U)))
        {
            currentRetVal = kCanCopyData;
            CanApp_SetAwakeSource_Nm(1U);
            ApplCanNmNodeID = CanRxActualData(rxStruct,0U);
        }        
        else
        {
            currentRetVal = kCanNoCopyData;
        }
    }
    else if((CeCanCbk_u_DiagPhyID == currentCanId)||(CeCanCbk_u_DiagFunID == currentCanId))
    {
        if (CanNm_NmState[0] == NM_STATE_PREPARE_BUS_SLEEP)
        {
            currentRetVal = kCanNoCopyData;
        }
        else
        {
            if( ((0x02U == CanRxActualData(rxStruct,0U)) && (0x11U == CanRxActualData(rxStruct,1U))) ||
            ((0x02U == CanRxActualData(rxStruct,0U)) && (0x10U == CanRxActualData(rxStruct,1U)) && (0x02U == CanRxActualData(rxStruct,2U))))
            {
                
            }
            else
            {
                CanApp_SetDiagReqNet(1U);
            }
            currentRetVal = kCanCopyData;
        }
    }
    else
    {    
        ApplCan_u_AppMsgKeepAliveTimer = 0u;
        currentRetVal = kCanCopyData;
    }
    return currentRetVal;
}

void TxAckCbk_VRHCU_3EE(CanTransmitHandle txObject)
{
    (void)txObject;
    SetCanApp_BusOffOccurNumClr();
    cbdWrpBusOffThresholdCounter[0U] = kCbdWrpBusOffThreshold;
	
	/*Clear ilState after transmited*/
    CanInterruptDisable();
    ilTxState[ilTxHandle_VRHCU_3EE] &= kTxNotQueueInit;
    CanInterruptRestore();
}

void TxAckCbk_VRHCU_3F3(CanTransmitHandle txObject)
{
    (void)txObject;
    SetCanApp_BusOffOccurNumClr();
    cbdWrpBusOffThresholdCounter[0U] = kCbdWrpBusOffThreshold;
	
	/*Clear ilState after transmited*/
    CanInterruptDisable();
    ilTxState[ilTxHandle_VRHCU_3F3] &= kTxNotQueueInit;
    CanInterruptRestore();
}

void TxAckCbk_VRHCU_6EE(CanTransmitHandle txObject)
{
    (void)txObject;
    SetCanApp_BusOffOccurNumClr();
    cbdWrpBusOffThresholdCounter[0U] = kCbdWrpBusOffThreshold;
	
	/*Clear ilState after transmited*/
    CanInterruptDisable();
    ilTxState[ilTxHandle_VRHCU_6EE] &= kTxNotQueueInit;
    CanInterruptRestore();
}

void TxAckCbk_VRHCU_6F9(CanTransmitHandle txObject)
{
    (void)txObject;
    SetCanApp_BusOffOccurNumClr();
    cbdWrpBusOffThresholdCounter[0U] = kCbdWrpBusOffThreshold;
    CanApp_SetAwakeSource_Nm(0);
	
	/*Clear ilState after transmited*/
    CanInterruptDisable();
    ilTxState[ilTxHandle_VRHCU_6F9] &= kTxNotQueueInit;
    CanInterruptRestore();
}

vuint8 Pretransmit_VRHCU_6F9(CanTxInfoStruct ctis)
{
    CanGlobalInterruptDisable();

    if (0U != CanApp_GetWakeUpSource_Nm())
    {
        VRHCU_6F9._c[3] |= 0x01U;
    }
    else
    {
        VRHCU_6F9._c[3] &= 0xFEU;
    }

    if (0U != CanApp_GetAwakeSource_Nm())
    {
        VRHCU_6F9._c[7] |= 0x02U;
    }
    else
    {
        VRHCU_6F9._c[7] &= 0xFDU;
    }

    if (0U != CanApp_GetDiagReqNetFlag())
    {
        VRHCU_6F9._c[7] |= 0x04U;
    }
    else
    {
        VRHCU_6F9._c[7] &= 0xFBU;
    }

    if (0U != IlGetRxBcmPwrStsFb())
    {
        VRHCU_6F9._c[7] |= 0x01U;
    }
    else
    {
        VRHCU_6F9._c[7] &= 0xFEU;
    }
    
    CanGlobalInterruptRestore();
	
	/*Init ilState before transmited*/
    CanInterruptDisable();
    ilTxState[ilTxHandle_VRHCU_6F9] |= kTxQueueInit;
    CanInterruptRestore();  
    return kCanCopyData;
}

vuint8 Pretransmit_NmMsg(CanTxInfoStruct ctis)
{
    Nm_StateType  pApplCan_u_NMSt;
    Nm_ModeType   pApplCan_u_NMMode;
    uint8  i = 0u;
    uint8 SeCan_u_NmMsgData[CeCanCbk_u_NmMsgDataLen]=
    {
        0x00u,
        0x00u,
        0x00u,
        0x00u,
        0x00u,
        0x00u
	};	

    if(NM_E_OK == CanNm_GetState(0U,&pApplCan_u_NMSt,&pApplCan_u_NMMode))
    {
        if(pApplCan_u_NMSt == NM_STATE_REPEAT_MESSAGE)
        {
            SeCan_u_NmMsgData[3] = 0x0U;
        }
        else if(pApplCan_u_NMSt == NM_STATE_NORMAL_OPERATION)
        {
            SeCan_u_NmMsgData[3] = 0x80U;
        }
    }

    SeCan_u_NmMsgData[5] = ApplCanNmNodeID;

    for( i=0U; i<CeCanCbk_u_NmMsgDataLen;i++)
    {
        NMm_VRHCU._c[i+2U] = SeCan_u_NmMsgData[i];
    }

    return kCanCopyData;
}


vuint8 Pretransmit_VRHCU_6EE(CanTxInfoStruct ctis)
{
	/*Init ilState before transmited*/
    CanInterruptDisable();
    ilTxState[ilTxHandle_VRHCU_6EE] |= kTxQueueInit;
    CanInterruptRestore();  
    return kCanCopyData;
}
vuint8 Pretransmit_VRHCU_3F3(CanTxInfoStruct ctis)
{
	/*Init ilState before transmited*/
    CanInterruptDisable();
    ilTxState[ilTxHandle_VRHCU_3F3] |= kTxQueueInit;
    CanInterruptRestore();  
    return kCanCopyData;
}
vuint8 Pretransmit_VRHCU_3EE(CanTxInfoStruct ctis)
{
 

    /*FridgeDoorWarnSt */
    uint8 currentByte = VRHCU_3EE._c[3];
    uint8 current_FridgeDoorWarnSt = currentByte & 0x03u; /* Replace with actual getter if different */


    /*Check for FridgeDoorWarnSt value 1-->2 or it may already be in the counting state.*/
    if ((FridgeDoorWarnSt_Previous == FRIDGE_WARN_NORMAL  && current_FridgeDoorWarnSt == FRIDGE_WARN_ACTIVE) || (FridgeDoorWarnSt_Counter > 0u)) 
    {
        
        if (FridgeDoorWarnSt_Counter < (FRIDGE_WARN_OVERRIDE_THRESHOLD + 1u))
        {
             FridgeDoorWarnSt_Counter++;
        }
    } 

    /*Check for FridgeDoorWarnSt value is 1*/
    if (current_FridgeDoorWarnSt == 1u) 
    {
        /*reset overwrite counter*/
        FridgeDoorWarnSt_Counter = 0u;

    }

    FridgeDoorWarnSt_Previous = current_FridgeDoorWarnSt;

    /*Overwrite FridgeDoorWarnSt three times when FridgeDoorWarnSt is 2*/
    if (FridgeDoorWarnSt_Counter > FRIDGE_WARN_OVERRIDE_THRESHOLD) 
    {
        current_FridgeDoorWarnSt = 0u;
        FridgeDoorWarnSt_Previous = current_FridgeDoorWarnSt;

        CanGlobalInterruptDisable();
        VRHCU_3EE._c[3] = VRHCU_3EE._c[3]&(~(0x03u));
        CanGlobalInterruptRestore();
    }



    /*Init ilState before transmited*/
    CanInterruptDisable();
    ilTxState[ilTxHandle_VRHCU_3EE] |= kTxQueueInit;
    CanInterruptRestore();  
    return kCanCopyData;
}

void ApplCanSetWakeupFlag(void)
{
    ApplCanWakeupFlag = 1U;
}

void ApplCanClearWakeupFlag(void)
{
    ApplCanWakeupFlag = 0U;
}

uint8 ApplCanGetCanBusWakeupValid(void)
{
    uint8 LeApplCan_u_Ret = NM_E_NOT_OK;
    if(1U == ApplCanWakeupFlag)
    {
        LeApplCan_u_Ret = NM_E_OK;
    }
    return LeApplCan_u_Ret;
}

void ApplCanSetNMBussleepToRepeatFlag(vuint8 LeCan_u_Temp)
{
    ApplCanBussleepToRepeatFlag = LeCan_u_Temp;
}
/* polyspace:end<MISRA-C3:2.2,2.7,10.1,11.3,17.8,18.4:Not a defect:Justified> NO fluence */
