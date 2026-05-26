/* polyspace<MISRA-C3:1.1:Not a defect:Maintian> have no effect */
/*******************************************************************************
|  (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name           Company
|--------------------------------------------------------------------------------------------
| psp       panshouping        CAEA
|--------------------------------------------------------------------------------------------
|           R E V I S I O N   H I S T O R Y
|--------------------------------------------------------------------------------------------
| Date      Version      Author    Description
| ------------  --------     -------  -------------------------------------------------------
| 2017-10-14      0.01     psp     DEM operation
| 2017-11-06      0.02     psp     Add Aging and fault count processing
| 2017-11-13      0.03     psp     1.updata macros CeDem->CanDem
|                      2.Remove invalid code
|                      3.Support DTC macros
|                      4.Support DTC transfer format macros switch
|                      5.Global static variable initialization InitMemory()
|                      6.Initialize the moniroting frequency parameters
|                    in InitMemory ()
|                      7.Encapsulate the DTC_CallBack_ReadEsprom() function
|                    and add the length parameter
|                      8.All DTC macros changed to CanDem_True
|                      9. changed to
|                      10.Filter operation repair switch modified to if
|                      11.Add Signal function in CanDem_CallBack for extern
|                     use
|                      12.Add notes
|*******************************************************************************************/
#include "CanDem.h"
#include "CanDem_Cfg.h"
//#include "Flash_If.h"
#include "il_par.h"
#include "Adc_If.h"
#include "DTC_Callback.h"
#include "CanDem_Callback.h"
#include "fdb_def.h"

static void  CanDem_SaveDTCOperating(uint8 LeDEM_u_DtcId, uint8 LeDEM_u_DtcLen);
static uint8 CanDem_PeriodEventOperating(uint8 LeDEM_u_DtcId);
static void  CanDem_DebounceOperating(uint8 LeDEM_u_DtcId);
static void  CanDem_DcmAgingCounter(uint8 LeDEM_u_DtcId);
static void  CanDem_GetConditionStatus(void);
static void  CanDem_SetConditionStatus(void);
static void  CanDem_PeriodQueueListen(void);
static void  CanDem_SetSnapShotData(uint8 LeDEM_u_DtcId);
static void  CanDem_ClearSnapShotData(void);
static void  CanDem_SetExtendData(uint8 LeDEM_u_DtcId);
static void  CanDem_SaveAllDTC(void);
/* Static variables */

uint8                    AgingCounterTest      = 0;
static uint8             EraseMemoryErrorsFlag = 0;
static DebounceInfo_Type SsDem_h_DebounceInfo[CanDem_u_DtcNumber];
static AgingInfo_Type    SsDem_h_AgingInfo[CanDem_u_DtcNumber];
static SysEnCond_Type    SsDem_h_MoniEnCond;
static uint16            SeDem_w_MoniEnCondDebounceCnt[CanDem_u_SysEnCondNumber];

DTCInfo_Type SeDem_u_DTCInfo[CanDem_u_DtcNumber];

static uint8 SeDem_u_DTCLastTimeStatus[CanDem_u_DtcNumber];
static uint8 SeDem_u_DTCFilterIndexList[CanDem_u_DtcNumber];
static uint8 SeDem_u_NvmWriteFlag[CanDem_u_DtcNumber];
static uint8 SeDem_u_DTCSupport[CanDem_u_DtcNumber];
static uint8 SeDem_u_OperatingCycleEnCond;
static uint8 SeDem_u_DTCSettingDisabled;

extern uint8_t uds_flash_set(uint16_t id, uint8_t *value, uint32_t length);
extern uint8_t uds_flash_get(uint16_t id, uint8_t *value, uint32_t length);
/*************************************************************
Name            : CanDem_InitMemory
Syntax          :
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : Intialize variables
Call By         : DTC_Callback_ReadEeprom
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CanDem_InitMemory(void)
{
    uint8 LeDem_u_Id = CanDEM_u_Zero;
    uint8 LeDem_u_Result;
    uint8 LaDEM_u_DtcNVMData[18] = {0};

    SeDem_u_DTCSettingDisabled = CanDem_u_True;

    CanDem_Cfg_InitMemory();

    for (LeDem_u_Id = CanDEM_u_Zero; LeDem_u_Id < (uint8)CanDem_u_DtcNumber; ++LeDem_u_Id)
    {
        LeDem_u_Result = uds_flash_get(DsDem_h_ManagementUnit[LeDem_u_Id].e_u_DTC_EepID, &LaDEM_u_DtcNVMData[0], 18);

        if (LeDem_u_Result == 0u) // TRUE )
        {
            SeDem_u_DTCInfo[LeDem_u_Id].SeDem_u_DTCStatus                 = LaDEM_u_DtcNVMData[0];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_ECU_Voltage   = LaDEM_u_DtcNVMData[1];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_Speed         = ((uint16)LaDEM_u_DtcNVMData[3] << 8) | LaDEM_u_DtcNVMData[2];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_OccurrenceCnt = LaDEM_u_DtcNVMData[4];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_FirstODO      = ((uint16)LaDEM_u_DtcNVMData[7] << 16) | ((uint16)LaDEM_u_DtcNVMData[6] << 8) | LaDEM_u_DtcNVMData[5];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_LastODO       = ((uint16)LaDEM_u_DtcNVMData[10] << 16) | ((uint16)LaDEM_u_DtcNVMData[9] << 8) | LaDEM_u_DtcNVMData[8];
//            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_Engine        = ((uint16)LaDEM_u_DtcNVMData[12] << 8) | LaDEM_u_DtcNVMData[11];
//            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_PowerMode     = LaDEM_u_DtcNVMData[13];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_Sec           = LaDEM_u_DtcNVMData[11];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_Min           = LaDEM_u_DtcNVMData[12];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_Hour          = LaDEM_u_DtcNVMData[13];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_Month         = LaDEM_u_DtcNVMData[14];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_Day           = LaDEM_u_DtcNVMData[15];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_Year          = LaDEM_u_DtcNVMData[16];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_FirstFlag     = LaDEM_u_DtcNVMData[17];

            /*SeDem_u_DTCInfo[LeDem_u_Id].DTCExtendData.ExtendDataRecord_One    = LaDEM_u_DtcNVMData[20];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCExtendData.ExtendDataRecord_Two    = LaDEM_u_DtcNVMData[21];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCExtendData.ExtendDataRecord_Three  = LaDEM_u_DtcNVMData[22];*/

            SsDem_h_DebounceInfo[LeDem_u_Id].e_u_DtcStatus = (((SeDem_u_DTCInfo[LeDem_u_Id].SeDem_u_DTCStatus & (uint8)0x80U) == (uint8)0x80U) ? CanDem_u_UDSStatus_CDTC : CanDEM_u_Zero);
            SsDem_h_AgingInfo[LeDem_u_Id].e_u_AgingCounter = (SeDem_u_DTCInfo[LeDem_u_Id].SeDem_u_DTCStatus & (uint8)CanDem_u_AgingMaxValue);
            SeDem_u_DTCLastTimeStatus[LeDem_u_Id]          = (((SeDem_u_DTCInfo[LeDem_u_Id].SeDem_u_DTCStatus & (uint8)0x40U) == (uint8)0x40U) ? CanDem_u_FaultNoRecover : CanDem_u_FaultRecover);
        }
        else
        {
            SsDem_h_DebounceInfo[LeDem_u_Id].e_u_DtcStatus = CanDEM_u_Zero;
            SsDem_h_AgingInfo[LeDem_u_Id].e_u_AgingCounter = CanDEM_u_Zero;
        }
        SeDem_u_DTCFilterIndexList[LeDem_u_Id]                  = CanDEM_u_Zero;
        SsDem_h_DebounceInfo[LeDem_u_Id].e_w_DebounceTime       = CanDEM_u_Zero;
        SsDem_h_DebounceInfo[LeDem_u_Id].e_u_DebounceFlag       = CanDem_u_DebounceNone;
        SsDem_h_DebounceInfo[LeDem_u_Id].e_u_DTCEvent_OldStatus = CanDEM_u_EventPassed;
        SsDem_h_AgingInfo[LeDem_u_Id].e_u_AgingFlag             = CanDem_u_False;
        SeDem_u_NvmWriteFlag[LeDem_u_Id]                        = CanDem_u_False;
        SeDem_u_DTCSupport[LeDem_u_Id]                          = DsDem_h_ManagementUnit[LeDem_u_Id].e_u_DtcSupport;

        /*ZGZ 20200515*/
        SsDem_h_DebounceInfo[LeDem_u_Id].e_u_DtcEvent_LastCycle = CanDEM_u_EventPassed;
        SsDem_h_DebounceInfo[LeDem_u_Id].e_u_DtcEvent_ThisCycle = CanDEM_u_EventPassed;
    }

    for (LeDem_u_Id = CanDEM_u_Zero; LeDem_u_Id < (uint8)CanDem_u_SysEnCondNumber; LeDem_u_Id++)
    {
        SeDem_w_MoniEnCondDebounceCnt[LeDem_u_Id] = CanDEM_u_Zero;
    }

    SsDem_h_MoniEnCond.e_u_DebounceCurStatus = CanDEM_u_Zero;
    SsDem_h_MoniEnCond.e_u_DebounceHisStatus = CanDEM_u_Zero;

    SeDem_u_OperatingCycleEnCond = CanDem_u_IgnitionCycle;
}

/*******************************************************************************
Name            : CanDem_MainFunction10ms
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : Traverse the DTC queue every 10ms and save the fault status
Call By         : CanDem_PeriodQueueListen
                  CanDem_SaveAllDTC
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CanDem_MainFunction10ms(void)
{
    CanDem_PeriodQueueListen();
    CanDem_SaveAllDTC(); /*xyh*/
}

/*******************************************************************************
Name            : CanDem_MainFunction20ms
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : Traverse enable conditions
Call By         : CanDem_GetConditionStatus
                : CanDem_SetConditionStatus
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CanDem_MainFunction20ms(void)
{
    CanDem_GetConditionStatus();
    CanDem_SetConditionStatus();
    DTC_ReadVehicleNetConfig();
}

/*******************************************************************************
Name            : CanDem_AgingCounter
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : if the number of aging reaches the requirement,the DTC data in
                  memory will be emptied
Call By         : CanDem_ClearExtendData
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
static void CanDem_DcmAgingCounter(uint8 LeDEM_u_DtcId)
{
    uint8 LaDEM_u_DtcNVMData[23] = {0};
    if (((uint8)CanDem_u_DtcNumber > LeDEM_u_DtcId) && ((uint8)CanDem_u_NotAgingSupport != DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_AgingUpperLimit))
    {
        if (((uint8)CanDem_u_True == SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingFlag) && ((uint8)CanDem_u_DebounceNone == SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DebounceFlag))
        /* Aging Flag DTC产生消抖flag置为None，即DTC状态没有变  */
        {
            if (((uint8)CanDem_u_UDSStatus_CDTC == (SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcStatus & (uint8)CanDem_u_UDSStatus_CDTC))
                && ((uint8)CanDem_u_UDSStatus_TF != (SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcStatus & (uint8)CanDem_u_UDSStatus_TF)))
            /* CDTC ==1 && TF ==0*/ /*无当前DTC，有历史DTC */
            {
                if (SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcEvent_LastCycle == CanDEM_u_EventPassed)
                /* last ON cycle NO DTC EVENT */
                {
                    SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter++; /*老化次数++*/
                    AgingCounterTest = SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter;
                    // SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_Three = SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter;/* ycl 20.05.08 */
                    if (SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter < DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_AgingUpperLimit)
                    {
                        SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_Three = SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter;
                    }
                    else if (SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter == DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_AgingUpperLimit)
                    {
                        SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_Two++; /* ycl 20.05.08 */
                        SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_Three = DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_AgingUpperLimit;

                        SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter = CanDEM_u_Zero;               /* Remove aging */
                        CanDem_u_ResetUDSStatis_CDTC(SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcStatus); /* 清历史DTC */
                        SeDem_u_DTCInfo[LeDEM_u_DtcId].SeDem_u_DTCStatus = 0x00U;                        /* ycl 18.11.30 */
                        CanDem_ClearSnapShotData();                                                      /*zc 18.8.15*/
                        // CanDem_ClearExtendData();/*zc 18.8.15*/ /*zgz 200511*/
                        // SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_Three = CanDEM_u_Zero; /*ZGZ 20.05.11*/
                        SeDem_u_DTCLastTimeStatus[LeDEM_u_DtcId] = CanDem_u_FaultRecover; /*ZGZ 20.05.11*/
                    }
                    else /*aging counter > 40*/
                    {
                        // SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter = CanDEM_u_Zero;            /*Remove aging */
                        // CanDem_u_ResetUDSStatis_CDTC(SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcStatus);    /*???DTC*/
                        // SeDem_u_DTCInfo[LeDEM_u_DtcId].SeDem_u_DTCStatus  = 0x00U;   /*ycl 18.11.30*/
                        // CanDem_ClearSnapShotData();/*zc 18.8.15*/
                        // CanDem_ClearExtendData();/*zc 18.8.15*/ /*zgz 200511*/
                        // SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_Three = CanDEM_u_Zero; /*ZGZ 20.05.11*/
                        // SeDem_u_DTCLastTimeStatus[LeDEM_u_DtcId] = CanDem_u_FaultRecover; /*ZGZ 20.05.11*/
                    }
                    SeDem_u_NvmWriteFlag[LeDEM_u_DtcId] = CanDem_u_StorageSaveDtc; /*Set Write flag*/
                }
                SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcEvent_LastCycle = CanDEM_u_EventPassed;
//                Eep_ReadData(DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_DTC_EepID, &LaDEM_u_DtcNVMData[0], 23);
                LaDEM_u_DtcNVMData[22] = SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcEvent_LastCycle;
//                Eep_WriteData(DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_DTC_EepID, &LaDEM_u_DtcNVMData[0], 23);
            }
            SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingFlag = CanDem_u_False; /*Clear Aging Enable status*/
        }
    }
}

/*******************************************************************************
Name            : CanDem_SetConditionStatus
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : Aging time to meet the specified requirements,
                  the position of the corresponding enable flag bit
Call By         : CanDem_ClearExtendData
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
static void CanDem_SetConditionStatus(void)
{
    uint8 LeDem_u_Index;
    uint8 LeDem_u_DtcIndex;

    for (LeDem_u_Index = CanDEM_u_Zero; LeDem_u_Index < (uint8)CanDem_u_SysEnCondNumber; LeDem_u_Index++)
    {
        if ((uint8)CanDEM_u_Zero != (SsDem_h_MoniEnCond.e_u_DebounceCurStatus & (0x01U << LeDem_u_Index)))
        /* 使能当前消抖状态bit，即有使能条�*/
        {
            if ((uint8)CanDEM_u_Zero == (SsDem_h_MoniEnCond.e_u_DebounceHisStatus & (0x01U << LeDem_u_Index)))
            /* 使能历史消抖状态bit为零 */
            {
                if (SeDem_w_MoniEnCondDebounceCnt[LeDem_u_Index] >= CaDEM_u_MoniEnTime[LeDem_u_Index]) /* 使能消抖时间到达设定 */
                {
                    SsDem_h_MoniEnCond.e_u_DebounceHisStatus |= (0x01U << LeDem_u_Index); /*使能历史消抖状态bit */
                    if((uint8)CanDEM_u_Zero == LeDem_u_Index)/* IGN ON */
                    {
                        for(LeDem_u_DtcIndex = CanDEM_u_Zero;LeDem_u_DtcIndex < (uint8)CanDem_u_DtcNumber;LeDem_u_DtcIndex++)
                        {
                            SsDem_h_AgingInfo[LeDem_u_DtcIndex].e_u_AgingFlag = CanDem_u_True; /* Start Aging */
                        //                            /*Aging Flag*/
                        }
                        SeDem_u_OperatingCycleEnCond |= (uint8)CanDem_u_PowerCycle; /* 操作周期，PowerMode ON */
                    }
                }
                else
                {
                    SeDem_w_MoniEnCondDebounceCnt[LeDem_u_Index]++; /* 使能消抖时间++ */
                }
            }
        }
        else
        /* 使能当前消抖状态bit为零，即使能条件不满 */
        {
            SeDem_w_MoniEnCondDebounceCnt[LeDem_u_Index] = CanDEM_u_Zero;                    /* 使能消抖时间清零 */
            SsDem_h_MoniEnCond.e_u_DebounceHisStatus &= ((uint8) ~(0x01U << LeDem_u_Index)); /* 使能历史消抖状态bit清零 */
            if ((uint8)0u == LeDem_u_Index)                                                  /* PowerMode OFF */
            {
                SeDem_u_OperatingCycleEnCond &= ((uint8) ~(CanDem_u_PowerCycle)); /* 操作周期，PowerMode OFF */
            }
        }
    }
}

/*******************************************************************************
Name            : CanDem_GetConditionStatus
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : Aging time to meet the specified requirements,
                  the position of the corresponding enable flag bit
Call By         : CanDem_ClearExtendData
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
static void CanDem_GetConditionStatus(void)
{
    uint8 LeDEM_u_DtcID = CanDEM_u_Zero;
    uint8 LeDem_u_Index;

    for (LeDem_u_Index = CanDEM_u_Zero; LeDem_u_Index < (uint8)CanDem_u_SysEnCondNumber; LeDem_u_Index++)
    {
        if (CanDEM_u_Null != SsDEM_h_MoniEnCodHandler[LeDem_u_Index]) /* 使能条件函数不为0 */
        {
            if ((uint8)CanDem_u_True == (*SsDEM_h_MoniEnCodHandler[LeDem_u_Index])()) /*使能条件满足*/
            {
                SsDem_h_MoniEnCond.e_u_DebounceCurStatus |= (uint8)(0x01U << LeDem_u_Index); /* 使能当前消抖状态bit */
            }
            else /* ?????? */
            {
                SsDem_h_MoniEnCond.e_u_DebounceCurStatus &= (uint8)(~(0x01U << LeDem_u_Index)); /* 使能当前消抖状态bit请零 */
                if (LeDem_u_Index == 0u)                                                        /* Power Mode Handle */
                {
                    for (LeDEM_u_DtcID = CanDEM_u_Zero; LeDEM_u_DtcID < (uint8)CanDem_u_DtcNumber; ++LeDEM_u_DtcID)
                    {
                        if (SsDem_h_DebounceInfo[LeDEM_u_DtcID].e_u_DtcEvent_ThisCycle == CanDEM_u_EventFailed)
                        {
                            SsDem_h_DebounceInfo[LeDEM_u_DtcID].e_u_DtcEvent_LastCycle = CanDEM_u_EventFailed;
                        }
                        SsDem_h_DebounceInfo[LeDEM_u_DtcID].e_u_DtcEvent_ThisCycle = CanDEM_u_EventPassed;
                    }
                }
            }
        }
    }
}

/*******************************************************************************
Name        :   CanDem_PeriodQueueListen
Syntax      : None
Sync/Async      : Synchronous
Reentrancy      :   None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     :   Cycle increases the DTC detection time period to meet the
            implementation of DTC detection
Call By     :   CanDem_ClearExtendData
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
static void CanDem_PeriodQueueListen(void)
{
    uint8        LeDEM_u_DtcID           = CanDEM_u_Zero;
    static uint8 SeDEM_u_ChoiceToProcess = 0xAAU;

    if (CanDEM_u_Zero != SeDEM_u_ChoiceToProcess) /*first 10 DTC*/
    {
        for (LeDEM_u_DtcID = CanDEM_u_Zero; LeDEM_u_DtcID < (uint8)CanDem_u_DtcNumber; ++LeDEM_u_DtcID)
        {
            if ((uint8)CanDem_u_True == SeDem_u_DTCSupport[LeDEM_u_DtcID]) /*DTC Support*/
            {
                if ((uint8)CanDem_u_True == SeDem_u_DTCSettingDisabled) /*85 Service*/
                {
                    if ((uint8)CanDem_u_True == CanDem_PeriodEventOperating(LeDEM_u_DtcID))
                    {
                        CanDem_DebounceOperating(LeDEM_u_DtcID); /*DTC消抖*/
                    }
                    CanDem_DcmAgingCounter(LeDEM_u_DtcID);                              /*老化计数*/
                    CanDem_SaveDTCOperating(LeDEM_u_DtcID, CanDEM_u_WriteE2promLength); /*save DTC to EEPROM*/
                }
            }
        }
        SeDEM_u_ChoiceToProcess = CanDEM_u_Zero;
    }
    else /* last 10 DTC */
    {
#if 0
        for(LeDEM_u_DtcID = CanDem_u_DtcNumber-10U;LeDEM_u_DtcID < (uint8)CanDem_u_DtcNumber;++LeDEM_u_DtcID)
        {
            if((uint8)CanDem_u_True == SeDem_u_DTCSupport[LeDEM_u_DtcID])/* DTC Support */
            {
                if((uint8)CanDem_u_True == SeDem_u_DTCSettingDisabled) /* 85 Service */
                {
                    if((uint8)CanDem_u_True == CanDem_PeriodEventOperating(LeDEM_u_DtcID))
                    {
                        CanDem_DebounceOperating(LeDEM_u_DtcID);/* DTC?? */
                    }
                    CanDem_DcmAgingCounter(LeDEM_u_DtcID);  /* ???? */
                    CanDem_SaveDTCOperating(LeDEM_u_DtcID,CanDEM_u_WriteE2promLength);/* save DTC to EEPROM */
                }
            }
        }
#endif
        SeDEM_u_ChoiceToProcess = 0xAAU;
    }
}

/*******************************************************************************
Name        :   CanDem_PeriodEventOperating
Syntax      : None
Sync/Async      : Synchronous
Reentrancy      :   None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     :   Check the DTC status and initialize the filter value
Call By     :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
static uint8 CanDem_PeriodEventOperating(uint8 LeDEM_u_DtcId)
{
    uint8 LeDem_u_ReturnStatus = CanDem_u_False;
    if ((uint8)CanDem_u_DtcNumber > LeDEM_u_DtcId)
    { /*操作周期=设置*/
        if (((SeDem_u_OperatingCycleEnCond & DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_DtcOperationCycleId)
             == DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_DtcOperationCycleId)
            && ((SsDem_h_MoniEnCond.e_u_DebounceHisStatus & DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_DtcEnCond)
                == DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_DtcEnCond)) /* 使能历史消抖状态为1，即使能条件=设置 */
        {
            if (CanDEM_u_Null != DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_DTCHandler) /* DTC发生函数不为�*/
            {
                if ((uint8)CanDEM_u_EventFailed != DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_DTCHandler()) /* 没有DTC产生 */
                {
                    /* Fail->Pass */
                    if ((uint8)CanDEM_u_EventFailed == SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DTCEvent_OldStatus) /* 之前有DTC产生 */
                    {
                        SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DTCEvent_OldStatus = CanDEM_u_EventPassed;
                        SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DebounceFlag       = CanDem_u_DebouncePassed; /* DTC产生消抖flag置为PASS */
                        SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_w_DebounceTime       = CanDEM_u_Zero;           /* DTC消抖时间清零 */
                    }
                }
                else /* 有DTC产生 */
                {
                    /* Pass->Fail */
                    if ((uint8)CanDEM_u_EventPassed == SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DTCEvent_OldStatus) /*之前没有DTC产生*/
                    {
                        SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcEvent_ThisCycle = CanDEM_u_EventFailed;
                        SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DTCEvent_OldStatus = CanDEM_u_EventFailed;
                        SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DebounceFlag       = CanDem_u_DebounceFailed; /* DTC产生消抖flag置为Fail */
                        SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_w_DebounceTime       = CanDEM_u_Zero;           /* DTC消抖时间清零 */
                    }
                }
            }
            LeDem_u_ReturnStatus = CanDem_u_True;
        }
    }
    return LeDem_u_ReturnStatus;
}

/*******************************************************************************
Name        :   CanDem_DebounceOperating
Syntax      : None
Sync/Async      : Synchronous
Reentrancy      :   None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     :   Fault occurrence and recovery filter time processing
Call By     :   CanDem_SetExtendData
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
static void CanDem_DebounceOperating(uint8 LeDEM_u_DtcId)
{
    if (LeDEM_u_DtcId < (uint8)CanDem_u_DtcNumber)
    {
        if ((uint8)CanDem_u_DebouncePassed == SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DebounceFlag) /* DTC产生消抖flag为Pass,即DTC从有到无 */
        {
            if (SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_w_DebounceTime
                >= SsDem_e_DebounceTimeTable[DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_w_DebounceTimeTableIndex].e_w_DtcTimePass)
            /*DTC消抖时间大于设置 ms)*/
            {
                SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DebounceFlag = CanDem_u_DebounceNone;  /*DTC产生消抖flag置为None*/
                SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_w_DebounceTime = CanDEM_u_Zero;          /*DTC消抖时间清零*/
                CanDem_u_ResetUDSStatus_TF(SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcStatus); /*DTC Status的TF位设置为0，无当前DTC*/
                SeDem_u_DTCLastTimeStatus[LeDEM_u_DtcId] = CanDem_u_FaultRecover;              /*zc add 18.8.15*/

                SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter = CanDEM_u_Zero; /*老化计数清零*/
            }
            else
            {
                SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_w_DebounceTime++; /*10ms*/
            }
        }
        else if ((uint8)CanDem_u_DebounceFailed == SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DebounceFlag) /*DTC产生消抖flag为Fail,即DTC从无到有*/
        {
            if (SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_w_DebounceTime
                >= SsDem_e_DebounceTimeTable[DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_w_DebounceTimeTableIndex].e_w_DtcTimeFail)
            /*DTC消抖时间大于设置 ms)*/
            {
                SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DebounceFlag = CanDem_u_DebounceNone;  /*DTC产生消抖flag置为None*/
                SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_w_DebounceTime = CanDEM_u_Zero;          /*DTC消抖时间清零*/
                CanDem_u_SetUDSStatus_TF(SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcStatus);   /*DTC Status的TF位设置为1，有当前DTC*/
                CanDem_u_SetUDSStatis_CDTC(SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcStatus); /*DTC Status的CDTC位设置为1，有历史DTC*/

                if ((uint8)CanDem_u_FaultRecover == SeDem_u_DTCLastTimeStatus[LeDEM_u_DtcId])
                {
                    if (SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_One < 0xFF) /*ycl 20.05.08*/
                    {
                        SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_One++; /*ZGZ 20.05.11*/
                        SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_Three = CanDEM_u_Zero;
                        // SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_One = 0xff;/*ZGZ 20.05.11*/
                    }

                    CanDem_SetSnapShotData(LeDEM_u_DtcId); /*设置快照信息   zc 18.8.15*/
                    CanDem_SetExtendData(LeDEM_u_DtcId);
                    SeDem_u_DTCLastTimeStatus[LeDEM_u_DtcId] = CanDem_u_FaultNoRecover;
                }
                else
                {
                    ;
                }

                SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter = CanDEM_u_Zero; /*??????*/

                SeDem_u_NvmWriteFlag[LeDEM_u_DtcId] = CanDem_u_StorageSaveDtc; /*DTC?EEPROM?flag??1*/
            }
            else
            {
                SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_w_DebounceTime++; /*10ms*/
            }
        }
        else
        {
        }
    }
}

/*******************************************************************************
Name            : CanDem_SaveDTCOperating
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : After the flag is satisfied,the correspanding DTC static
                  data is save
Call By         : DTC_Callback_ReadEeprom
                  CanDem_WriteEeprom
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
static void CanDem_SaveDTCOperating(uint8 LeDEM_u_DtcId, uint8 LeDEM_u_DtcLen)
{
    uint8  LaDEM_u_DtcNVMData[21] = {0};
    uint16 LeVehicleSpeed;
    uint32 LeFirstODO;
    uint32 LeLastODO;
    uint16 LeEngSpeed;
    // uint8 LeDem_u_Change_Flag = CanDem_u_False;

    if (((uint8)CanDem_u_DtcNumber > LeDEM_u_DtcId) && ((uint8)CanDEM_u_Zero != LeDEM_u_DtcLen))
    {
        if ((uint8)CanDem_u_StorageSaveDtc == SeDem_u_NvmWriteFlag[LeDEM_u_DtcId]) /*DTC写EEPROM的flag等于1*/
        {
//            LeEngSpeed = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_Engine;

            LeFirstODO     = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_FirstODO;
            LeLastODO      = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_LastODO;
            LeVehicleSpeed = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_Speed;
            if ((SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcStatus & CanDem_u_UDSStatus_CDTC) == CanDem_u_UDSStatus_CDTC)
            /*DTC Status的CDTC位等，有历史DTC*/
            {
                SeDem_u_DTCInfo[LeDEM_u_DtcId].SeDem_u_DTCStatus = 0x80U;
                SeDem_u_DTCInfo[LeDEM_u_DtcId].SeDem_u_DTCStatus |= (SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter);
            }

            LaDEM_u_DtcNVMData[0]  = SeDem_u_DTCInfo[LeDEM_u_DtcId].SeDem_u_DTCStatus; /*ycl 181026*/
            LaDEM_u_DtcNVMData[1]  = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_ECU_Voltage;
            LaDEM_u_DtcNVMData[2]  = (uint8)(LeVehicleSpeed & 0xFF);
            LaDEM_u_DtcNVMData[3]  = (uint8)((LeVehicleSpeed >> 8) & 0xFF);
            LaDEM_u_DtcNVMData[4]  = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_OccurrenceCnt;
            LaDEM_u_DtcNVMData[5]  = (uint8)(LeFirstODO & 0xFF);
            LaDEM_u_DtcNVMData[6]  = (uint8)((LeFirstODO >> 8) & 0xFF);
            LaDEM_u_DtcNVMData[7]  = (uint8)((LeFirstODO >> 16) & 0xFF);
            LaDEM_u_DtcNVMData[8]  = (uint8)(LeLastODO & 0xFF);
            LaDEM_u_DtcNVMData[9]  = (uint8)((LeLastODO >> 8) & 0xFF);
            LaDEM_u_DtcNVMData[10] = (uint8)((LeLastODO >> 16) & 0xFF);
            LaDEM_u_DtcNVMData[11] = (uint8)(LeEngSpeed & 0xFF);
            LaDEM_u_DtcNVMData[12] = (uint8)((LeEngSpeed >> 8) & 0xFF);
//            LaDEM_u_DtcNVMData[13] = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_PowerMode;
            LaDEM_u_DtcNVMData[13] = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_Sec;
            LaDEM_u_DtcNVMData[14] = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_Min;
            LaDEM_u_DtcNVMData[15] = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_Hour;
            LaDEM_u_DtcNVMData[16] = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_Month;
            LaDEM_u_DtcNVMData[17] = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_Day;
            LaDEM_u_DtcNVMData[18] = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_Year;
            LaDEM_u_DtcNVMData[19] = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_FirstFlag;
            LaDEM_u_DtcNVMData[20] = SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcEvent_ThisCycle;

            EraseMemoryErrorsFlag = uds_flash_set(DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_DTC_EepID, &LaDEM_u_DtcNVMData[0], 0x15);

            SeDem_u_NvmWriteFlag[LeDEM_u_DtcId] = CanDem_u_StorageNone; 
        }
    }
}
/*******************************************************************************
Name						:	CanDem_SaveAllDTC
Syntax					: None
Sync/Async			: Synchronous
Reentrancy			:	None
Parameters(in)  : None
Parameters(out) : None
Return value		: None
Description			:	Save All Dtc
Call By					:	CanDem_SaveDTCOperating
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
static void CanDem_SaveAllDTC(void)
{
    uint8 LeDem_u_Index;
    for (LeDem_u_Index = CanDEM_u_Zero; LeDem_u_Index < (uint8)CanDem_u_DtcNumber; LeDem_u_Index++)
    {
        CanDem_SaveDTCOperating(LeDem_u_Index, CanDEM_u_WriteE2promLength);
    }
}

static void CanDem_SetSnapShotData(uint8 LeDEM_u_DtcId)
{
    SnapShotTable_Type TsDEM_h_SnapShotData;
    uint16             LeVehicleSpeed = IlGetRxEHB_VehicleSpeed();
    uint32             LeFirstODO     = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_FirstODO;
    uint32             LeLastODO      = (uint32)(IlGetRxIPK_IPKTotalOdometer() / 10U);
    uint8              LeSec          = IlGetRxTBOX_Second();
    uint8              LeMin          = IlGetRxTBOX_Minute();
    uint8              LeHr           = IlGetRxTBOX_Hour();
    uint8              LeMonth        = IlGetRxTBOX_Month();
    uint8              LeDay          = IlGetRxTBOX_Day();
    uint8              LeYr           = IlGetRxTBOX_Year();
    uint8              LeFlag         = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_FirstFlag;

    if (LeFlag == 0u)
    {
        LeFirstODO = LeLastODO;
        LeFlag     = 1u;
    }

    TsDEM_h_SnapShotData.e_u_ECU_Voltage = (uint8)(adc_if_get_validValue(adc_cl_bat)/15.6);
    TsDEM_h_SnapShotData.e_u_Speed       = LeVehicleSpeed;
    // 从全局数组中读取当前OccurrenceCnt�
    TsDEM_h_SnapShotData.e_u_OccurrenceCnt = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_OccurrenceCnt;
    if (TsDEM_h_SnapShotData.e_u_OccurrenceCnt < 0xFFu)
    {
        TsDEM_h_SnapShotData.e_u_OccurrenceCnt++;
    }
    else
    {
        TsDEM_h_SnapShotData.e_u_OccurrenceCnt = 1;
    }
    TsDEM_h_SnapShotData.e_u_FirstODO              = LeFirstODO;
    TsDEM_h_SnapShotData.e_u_LastODO               = LeLastODO;
    TsDEM_h_SnapShotData.e_u_Sec                   = LeSec;
    TsDEM_h_SnapShotData.e_u_Min                   = LeMin;
    TsDEM_h_SnapShotData.e_u_Hour                  = LeHr;
    TsDEM_h_SnapShotData.e_u_Month                 = LeMonth;
    TsDEM_h_SnapShotData.e_u_Day                   = LeDay;
    TsDEM_h_SnapShotData.e_u_Year                  = LeYr;
    TsDEM_h_SnapShotData.e_u_FirstFlag             = LeFlag;
    SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData = TsDEM_h_SnapShotData;
    // SeDem_u_DTCSnapShotData[LeDEM_u_DtcId][0].e_u_RecordNumber = 1U;
}
/*******************************************************************************
Name            : CanDem_ClearSnapShotData
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     :
Call By         :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
static void CanDem_ClearSnapShotData(void)
{
    uint8 LeDem_u_DtcId;
    // uint8 LeDem_u_DtcRecordNumber;

    for (LeDem_u_DtcId = CanDem_u_Zero; LeDem_u_DtcId < CanDem_u_DtcNumber; LeDem_u_DtcId++)
    {
        // for(LeDem_u_DtcRecordNumber = CanDem_u_Zero;LeDem_u_DtcRecordNumber < (uint8)CanDEM_u_SnapOccurtimesMax;LeDem_u_DtcRecordNumber++)
        {
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_ECU_Voltage   = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_Speed         = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_OccurrenceCnt = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_FirstODO      = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_LastODO       = CanDEM_u_Zero;
//            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_Engine        = CanDEM_u_Zero;
//            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_PowerMode     = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_Sec           = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_Min           = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_Hour          = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_Month         = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_Day           = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_Year          = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_FirstFlag     = CanDEM_u_Zero;
        }
        SeDem_u_DTCLastTimeStatus[LeDem_u_DtcId] = CanDem_u_FaultRecover;
    }
}

static void CanDem_SetExtendData(uint8 LeDEM_u_DtcId)
{
    // DTCExtendData_Type TsDEM_h_ExtendData;

    // TsDEM_h_ExtendData.ExtendDataRecord_One     = 1;
    // TsDEM_h_ExtendData.ExtendDataRecord_Two     = 2;
    // TsDEM_h_ExtendData.ExtendDataRecord_Three   = 3;

    // SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData = TsDEM_h_ExtendData;
    // SeDem_u_DTCSnapShotData[LeDEM_u_DtcId][0].e_u_RecordNumber = 1U;
}

/*******************************************************************************
Name            : CanDem_DcmGetDTCStatusAvailabilityMask
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : Return Dtc Availability Mask
Call By         :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
uint8 CanDem_DcmGetDTCStatusAvailabilityMask(uint8 *DTCStatusMask)
{
    *DTCStatusMask = Can_u_StatusAvailabilityMask;
    return CanDem_u_Ok;
}

/*******************************************************************************
Name            : CanDem_DcmGetNumberOfFilteredDTC
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : Get the number of DTC Failures
Call By         :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
uint8 CanDem_DcmGetNumberOfFilteredDTC(uint16 *NumberOfFilteredDTC, uint8 DTC_RequestMask) /*19 02*/
{
    uint16 LeDem_w_NumberOfEvents;
    uint8  LeDem_u_Index;
    LeDem_w_NumberOfEvents = CanDEM_u_Zero;

    for (LeDem_u_Index = CanDEM_u_Zero; LeDem_u_Index < (uint8)CanDem_u_DtcNumber - CanDem_u_DisRepNumber; LeDem_u_Index++)
    {
        if (((SsDem_h_DebounceInfo[LeDem_u_Index].e_u_DtcStatus) & DTC_RequestMask) != (uint8)CanDEM_u_Zero) /*zc change*/
        {
            SeDem_u_DTCFilterIndexList[LeDem_w_NumberOfEvents] = LeDem_u_Index;
            LeDem_w_NumberOfEvents++;
        }
    }
    *NumberOfFilteredDTC = LeDem_w_NumberOfEvents;
    return CanDem_u_Ok;
}

/*******************************************************************************
Name            : CanDem_DcmGetNextFilteredDTC
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : Find the next DTC error number
Call By         :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
uint8 CanDem_DcmGetNextFilteredDTC(uint32 *DTC, uint8 *DTCStatus, uint16 DTCNumber) /*19 02*/
{
    uint8  LeDem_u_IndexList;
    uint32 LeDem_u_DtcNumTemp;
    LeDem_u_IndexList  = SeDem_u_DTCFilterIndexList[DTCNumber];
    LeDem_u_DtcNumTemp = ((uint32)DsDem_h_ManagementUnit[LeDem_u_IndexList].e_w_Num) << 8U;
    LeDem_u_DtcNumTemp |= (uint32)(DsDem_h_ManagementUnit[LeDem_u_IndexList].e_u_FailType);
    *DTC       = LeDem_u_DtcNumTemp;
    *DTCStatus = ((SsDem_h_DebounceInfo[LeDem_u_IndexList].e_u_DtcStatus) & (uint8)Can_u_StatusAvailabilityMask);
    return CanDem_u_Ok;
}

/*******************************************************************************
Name            : CanDem_DcmGetStatusOfDTC
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : Determine whether the DTC status bit is supported
Call By         : CanDem_DcmFindEventFromDtcInfo
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
uint8 CanDem_DcmGetStatusOfDTC(uint32 DTC, uint32 DTCOrigin, uint8 *DTCStatus) /*19 04*/
{
    uint16 LeDem_w_DTCIndex;
    uint8  LeDem_u_Return;
    LeDem_w_DTCIndex = CanDem_DcmFindEventFromDtcInfo(DTC, DTCOrigin);
    if ((uint16)0xFFFFU != LeDem_w_DTCIndex)
    {
        *DTCStatus     = ((SsDem_h_DebounceInfo[LeDem_w_DTCIndex].e_u_DtcStatus) & (uint8)Can_u_StatusAvailabilityMask);
        LeDem_u_Return = CanDem_u_Ok;
    }
    else
    {
        LeDem_u_Return = CanDem_u_Nok;
    }
    return LeDem_u_Return;
}

/*******************************************************************************
Name            : CanDem_DcmGetAllSupportDTC
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     :
Call By         :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CanDem_DcmGetAllSupportDTC(uint32 *DTC, uint8 *DTCStatus, uint8 DTCNumber) /*19 0A*/
{
    uint32 LeDem_u_DtcNumTemp;
    LeDem_u_DtcNumTemp = ((uint32)DsDem_h_ManagementUnit[DTCNumber].e_w_Num) << 8U;
    LeDem_u_DtcNumTemp |= (uint32)(DsDem_h_ManagementUnit[DTCNumber].e_u_FailType);
    *DTC       = LeDem_u_DtcNumTemp;
    *DTCStatus = SsDem_h_DebounceInfo[DTCNumber].e_u_DtcStatus;
}

/*******************************************************************************
Name            : CanDem_DcmClearDTCSignal
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : Traverse and clear all DTC signal values
Call By         :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
uint8 CanDem_DcmClearDTCSignal(uint32 LeCanDem_dw_DTCNum) /*14*/
{
    uint8 LeDem_u_Index;
    uint8 LeDem_u_Return;
    if ((uint32)0xFFFFFFU == LeCanDem_dw_DTCNum)
    {
        if (EraseMemoryErrorsFlag == 0u) // Write EEP OK
        {
            for (LeDem_u_Index = CanDEM_u_Zero; LeDem_u_Index < (uint8)CanDem_u_DtcNumber; LeDem_u_Index++)
            {
                SsDem_h_DebounceInfo[LeDem_u_Index].e_u_DtcStatus          = CanDEM_u_Zero;        /*clear DTC status*/
                SsDem_h_DebounceInfo[LeDem_u_Index].e_u_DTCEvent_OldStatus = CanDEM_u_EventPassed; /*clear event status*/
                SsDem_h_AgingInfo[LeDem_u_Index].e_u_AgingCounter          = CanDEM_u_Zero;        /*clear aging counter*/
                SeDem_u_DTCInfo[LeDem_u_Index].SeDem_u_DTCStatus           = (uint8)0x00U;

                CanDem_ClearSnapShotData(); /*zc 18.8.15*/
                SeDem_u_NvmWriteFlag[LeDem_u_Index] = CanDem_u_StorageSaveDtc;
            }

            LeDem_u_Return = CanDem_u_Ok;
        }
        else // Write EEP NOK
        {
            LeDem_u_Return = CanDem_u_OtherNokState;
        }
    }
    else
    {
        LeDem_u_Return = CanDem_u_Nok;
    }
    return LeDem_u_Return;
}

/*******************************************************************************
Name            : CanDem_DcmFindEventFromDtcInfo
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : Determine where the DTC is loacted
Call By         :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
uint32 LeDem_dw_DTC;
uint16 CanDem_DcmFindEventFromDtcInfo(uint32 Dtc, uint32 MemoryId)
{
    uint16 LeDem_u_Index;
    uint16 LeDem_u_Result;

    LeDem_u_Result = 0xFFFFU;
    if ((uint8)CanDEM_u_Zero != MemoryId)
    {
        ;
    }
    for (LeDem_u_Index = CanDEM_u_Zero; LeDem_u_Index <= (uint8)CanDem_u_DtcNumber - CanDem_u_DisRepNumber; LeDem_u_Index++)
    {
        LeDem_dw_DTC = (uint32)(((uint32)DsDem_h_ManagementUnit[LeDem_u_Index].e_w_Num << (uint32)0x08U) + DsDem_h_ManagementUnit[LeDem_u_Index].e_u_FailType);
        if (LeDem_dw_DTC == Dtc)
        {
            LeDem_u_Result = LeDem_u_Index;
            break;
        }
    }
    return LeDem_u_Result;
}

/*******************************************************************************
Name            : CanDem_DcmEnableDTCSetting
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : 85 Server(Diagnostic function is Enable)
Call By         :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
uint8 CanDem_DcmEnableDTCSetting(void) /*85 01*/
{
    SeDem_u_DTCSettingDisabled = CanDem_u_True;
    return CanDem_u_Ok;
}

/*******************************************************************************
Name            : CanDem_DcmDisableDTCSetting
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : 85 Server(Diagnostic disable)
Call By         :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
uint8 CanDem_DcmDisableDTCSetting(void) /*85 02*/
{
    SeDem_u_DTCSettingDisabled = CanDem_u_False;
    return CanDem_u_Ok;
}
/*******************************************************************************
Name            : CanDem_DcmGet_NetDtc_EnableConditionStatus
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : Get 85 status
Call By         :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
uint8 CanDem_DcmGet_NetDtc_EnableConditionStatus(void)
{
    uint8 CanDem_u_temp = CanDem_u_False;
    if (SsDem_h_MoniEnCond.e_u_DebounceHisStatus == 0x1Fu)
    {
        CanDem_u_temp = CanDem_u_True;
    }
    else
    {
        CanDem_u_temp = CanDem_u_False;
    }
    return CanDem_u_temp;
}
/* polyspace:end<DEFECT:UINT_CONV_OVFL:Not a defect:No action planned> No Defect */

/*******************************************************************************
Name            : CanDem_GetDTCSetting
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : 85 Server(Diagnostic disable)
Call By         :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
uint8 CanDem_GetDTCSetting(void) /*85*/
{
    return SeDem_u_DTCSettingDisabled;
}
/*******************************************************************************
Name            : CanDem_GetDTCSetting
Syntax          : None
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : 85 Server(Diagnostic disable)
Call By         :
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
void CanDem_SetConditionstatuts_ontooff(void)
{
    uint8        LeDem_u_DtcIndex;
    static uint8 Last_ignstatus;
    static uint8 This_ignstatus;
    This_ignstatus = CanDem_GetIgnStatus();
    if ((This_ignstatus == 0) && (Last_ignstatus == 1)) //
    {
        for (LeDem_u_DtcIndex = CanDEM_u_Zero; LeDem_u_DtcIndex < (uint8)CanDem_u_DtcNumber; LeDem_u_DtcIndex++)
        {
           // SsDem_h_AgingInfo[LeDem_u_DtcIndex].e_u_AgingFlag = CanDem_u_True; /*Start  Aging*/
            /*Aging Flag*/
        }
    }
    Last_ignstatus = This_ignstatus;
}
