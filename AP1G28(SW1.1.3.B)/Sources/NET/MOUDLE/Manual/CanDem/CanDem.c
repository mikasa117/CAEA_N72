/* polyspace:begin<DEFECT:UINT_CONV_OVFL:Not a defect:No action planned> No Defect */
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
|                      9.// changed to
|                      10.Filter operation repair switch modified to if
|                      11.Add Signal function in CanDem_CallBack for extern
|                     use
|                      12.Add notes
|*******************************************************************************************/
#include "CanDem.h"
//#include "NVM_Cfg.h"
#include "CanDem_Cfg.h"
#include "CanDem_CallBack.h"
//#include "STD_AdcM.h"
#include "Std_Types.h"
//#include "Rte_Can.h"
//#include "STD_AdcM.h"
#include "STD_EepM.h"
#include "CanApp.h"
/* Make all CANdesc specific typedefs available */
#include "desc.h"
#include "RTE_DEM.h"
/* Include the implementation prototypes for prototype checks */
#include "appdesc.h"
//#include "STD_BtrCtr.h"
#include "Rte_Can.h"
////#include "NtcCtrl_Cfg.h"
//#include "Can_Fbl.h"
//#include "SpiIf.h"
#include "desc.h"
#include "flash_driver.h"
#include "Appl_CPID_Callback.h"
#include "DID_Callback.h"



static void CanDem_SaveDTCOperating(uint8 LeDEM_u_DtcId,uint8 LeDEM_u_DtcLen);
static uint8 CanDem_PeriodEventOperating(uint8 LeDEM_u_DtcId);
static void CanDem_DebounceOperating(uint8 LeDEM_u_DtcId);
static void CanDem_DcmAgingCounter(uint8 LeDEM_u_DtcId);
static void CanDem_GetConditionStatus(void);
static void CanDem_SetConditionStatus(void);
static void CanDem_PeriodQueueListen(void);
static void CanDem_SetSnapShotData(uint8 LeDEM_u_DtcId);
static void CanDem_ClearSnapShotData(void);
static void CanDem_SetExtendData(uint8 LeDEM_u_DtcId);
static void CanDem_ClearExtendData(void);
void CanDem_MainFunction10ms(void);
void CanDem_InitMemory(void);
static void CanDem_SaveAllDTC(void); 
void Check_VehicleSpeed_Status(void);
uint8 PendingPDCM_actualGear(void);
uint8 PendingVehicleSpeed(void);
static void CanApp_CheckDtcGenerate(void);



static DebounceInfo_Type    SsDem_h_DebounceInfo[CanDem_u_DtcNumber];
static AgingInfo_Type       SsDem_h_AgingInfo[CanDem_u_DtcNumber];
static SysEnCond_Type       SsDem_h_MoniEnCond;
static uint16               SeDem_w_MoniEnCondDebounceCnt[CanDem_u_SysEnCondNumber];

uint8 Diag_flag;
uint8 DTC_Enable_Conditions_Flg;
uint8 PowerMode_Flg;
uint8 PowerMode_RUN_1500ms;

uint32 tmpKey;

DTCInfo_Type    SeDem_u_DTCInfo[CanDem_u_DtcNumber];


//SnapShotTable_Type          SeDem_u_DTCSnapShotData[CanDem_u_DtcNumber][CanDEM_u_SnapOccurtimesMax]; /* Ã¥Â­ËœÃ¥â€šÂ¨Ã¥Â¿Â«Ã§â€¦Â§Ã¦â€¢Â°Ã¦ÂÂ®Ã¨Â®Â°Ã¥Â½ï¿½*/
static uint8                SeDem_u_DTCLastTimeStatus[CanDem_u_DtcNumber];/* ?????????? */
//static uint8              SeDem_u_DTCOccurTimes[CanDem_u_DtcNumber];/* ???????? */

static uint8                SeDem_u_DTCFilterIndexList[CanDem_u_DtcNumber];/* ??????mask ???DTC  ???,??DCM19 02?? */

static uint8                SeDem_u_NvmWriteFlag[CanDem_u_DtcNumber];
static uint8                SeDem_u_DTCSupport[CanDem_u_DtcNumber];
static uint8                SeDem_u_OperatingCycleEnCond;/* ??????? */

static uint8                SeDem_u_DTCSettingDisabled;


/////////////////////////////////////////////////////////
static uint8 SeCanApp_u_DtcSendBuf[CanDem_u_DtcNumber][8];
static uint8 SeCanApp_u_DtcNeedSend[CanDem_u_DtcNumber];
static uint16 SeCanApp_w_DtcDelaySend=0;
////////////////////////////////////////////////////////

uint8 Current_VehicleSpeed_Gear_Flag;
uint8 VehicleSpeed_Gear_Timeout_Flag;
uint8 VehicleSpeed_Gear_TimeoutCounter;

/* #pragma section text Code_CanDem */

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
    uint8 LaDEM_u_DtcNVMData[13];

    SeDem_u_DTCSettingDisabled = CanDem_u_True;

    CanDem_Cfg_InitMemory();
    DID_Callback_Init();
    DID_AgingModeFunction();

    for(LeDem_u_Id = CanDEM_u_Zero;LeDem_u_Id < (uint8)CanDem_u_DtcNumber;++LeDem_u_Id)
    {
        LeDem_u_Result = EEPM_AppReadBlock(DsDem_h_ManagementUnit[LeDem_u_Id].e_u_DTC_EepID, &LaDEM_u_DtcNVMData[0]);

        if(LeDem_u_Result == TRUE )
        {
            SeDem_u_DTCInfo[LeDem_u_Id].SeDem_u_DTCStatus                  = LaDEM_u_DtcNVMData[0];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_OdometerValue  = ((uint32)LaDEM_u_DtcNVMData[3] << 16) | ((uint32)LaDEM_u_DtcNVMData[2] << 8) | LaDEM_u_DtcNVMData[1];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_ECU_Voltage    = LaDEM_u_DtcNVMData[4];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_Speed          = ((uint16)LaDEM_u_DtcNVMData[6] << 8) | LaDEM_u_DtcNVMData[5];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_Sec            = LaDEM_u_DtcNVMData[7];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_Min            = LaDEM_u_DtcNVMData[8];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_Hour           = LaDEM_u_DtcNVMData[9];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_Day            = LaDEM_u_DtcNVMData[10];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_Month          = LaDEM_u_DtcNVMData[11];
            SeDem_u_DTCInfo[LeDem_u_Id].DTCSnapShotData.e_u_Year           = LaDEM_u_DtcNVMData[12];
        
            // SeDem_u_DTCInfo[LeDem_u_Id].DTCExtendData.ExtendDataRecord_One   = LaDEM_u_DtcNVMData[13];
            // SeDem_u_DTCInfo[LeDem_u_Id].DTCExtendData.ExtendDataRecord_Two   = LaDEM_u_DtcNVMData[14];   GGL
            // SeDem_u_DTCInfo[LeDem_u_Id].DTCExtendData.ExtendDataRecord_Three = LaDEM_u_DtcNVMData[14];

            SsDem_h_DebounceInfo[LeDem_u_Id].e_u_DtcStatus =(((SeDem_u_DTCInfo[LeDem_u_Id].SeDem_u_DTCStatus & (uint8)0x80U) == (uint8)0x80U)?CanDem_u_UDSStatus_CDTC:CanDEM_u_Zero);
            SsDem_h_AgingInfo[LeDem_u_Id].e_u_AgingCounter = (SeDem_u_DTCInfo[LeDem_u_Id].SeDem_u_DTCStatus & (uint8)CanDem_u_AgingMaxValue);
            SeDem_u_DTCLastTimeStatus[LeDem_u_Id] = (((SeDem_u_DTCInfo[LeDem_u_Id].SeDem_u_DTCStatus & (uint8)0x40U) == (uint8)0x40U)?CanDem_u_FaultNoRecover:CanDem_u_FaultRecover);
        }
        else
        {
            SsDem_h_DebounceInfo[LeDem_u_Id].e_u_DtcStatus = CanDEM_u_Zero;
            SsDem_h_AgingInfo[LeDem_u_Id].e_u_AgingCounter = CanDEM_u_Zero;
        }
        SeDem_u_DTCFilterIndexList[LeDem_u_Id] = CanDEM_u_Zero;
        SsDem_h_DebounceInfo[LeDem_u_Id].e_w_DebounceTime = CanDEM_u_Zero;
        SsDem_h_DebounceInfo[LeDem_u_Id].e_u_DebounceFlag = CanDem_u_DebounceNone;
        SsDem_h_DebounceInfo[LeDem_u_Id].e_u_DTCEvent_OldStatus = CanDEM_u_EventPassed;
        SsDem_h_AgingInfo[LeDem_u_Id].e_u_AgingFlag = CanDem_u_False;
        SeDem_u_NvmWriteFlag[LeDem_u_Id] = CanDem_u_False;
        SeDem_u_DTCSupport[LeDem_u_Id] = DsDem_h_ManagementUnit[LeDem_u_Id].e_u_DtcSupport;

        /*ZGZ 20200515*/
        SsDem_h_DebounceInfo[LeDem_u_Id].e_u_DtcEvent_LastCycle = CanDEM_u_EventPassed;
        SsDem_h_DebounceInfo[LeDem_u_Id].e_u_DtcEvent_ThisCycle = CanDEM_u_EventPassed;

    }

    for(LeDem_u_Id = CanDEM_u_Zero;LeDem_u_Id < (uint8)CanDem_u_SysEnCondNumber;LeDem_u_Id++)
    {
        SeDem_w_MoniEnCondDebounceCnt[LeDem_u_Id] = CanDEM_u_Zero;
    }

    SsDem_h_MoniEnCond.e_u_DebounceCurStatus = CanDEM_u_Zero;
    SsDem_h_MoniEnCond.e_u_DebounceHisStatus = CanDEM_u_Zero;

    SeDem_u_OperatingCycleEnCond = CanDem_u_PowerCycle;
    
    PowerMode_RUN_1500ms = 0U;
    Diag_flag = 0U;
	tmpKey		= 0;
	
	Current_VehicleSpeed_Gear_Flag 		=0;
	VehicleSpeed_Gear_Timeout_Flag 		=1;
	VehicleSpeed_Gear_TimeoutCounter	=0;
	

}

/*****************************************************************************
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
    
	RTE_NET_Dem_10msMainFunction();
	CanApp_CheckDtcGenerate();


//	FLASH_DRV_EraseNVR(0, 0x10030000);
	
	
	/*uint8 LpDID_u_Data[20] ={0};
	uint8 *src_ptr = (uint8 *)0x30818 ;
	
	
	for (uint8 i = 0; i < 20; i++) 
	{
		LpDID_u_Data[i] = src_ptr[i];  
	}*/
	
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
	
	
	Check_VehicleSpeed_Status();
	PendingPDCM_actualGear();
	PendingVehicleSpeed();
    Check_DIDF1FA_CompressorFault();
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
    if(((uint8)CanDem_u_DtcNumber > LeDEM_u_DtcId) && ((uint8)CanDem_u_NotAgingSupport != DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_AgingUpperLimit))
    {
        if(((uint8)CanDem_u_True == SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingFlag) && ((uint8)CanDem_u_DebounceNone == SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DebounceFlag))
            /* Aging Flag Ã¯Â¿Â½Ã¯Â¿Â½DTCÃ¤ÂºÂ§Ã§â€Å¸Ã¦Â¶Ë†Ã¦Å â€“flagÃ§Â½Â®Ã¤Â¸ÂºNoneÃ¯Â¼Å’Ã¥ÂÂ³DTCÃ§Å Â¶Ã¦â‚¬ÂÃ¦Â²Â¡Ã¦Å“â€°Ã¥Âï¿½*/
        {
            if(((uint8)CanDem_u_UDSStatus_CDTC == (SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcStatus & (uint8)CanDem_u_UDSStatus_CDTC))
            && ((uint8)CanDem_u_UDSStatus_TF != (SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcStatus & (uint8)CanDem_u_UDSStatus_TF)))
                /* CDTC ==1 && TF ==0*/ /*Ã¦â€”Â Ã¥Â½â€œÃ¥â€°ÂDTCÃ¯Â¼Å’Ã¦Å“â€°Ã¥Å½â€ Ã¥ÂÂ²DTC */
            {
                if(SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcEvent_LastCycle == CanDEM_u_EventPassed)
                    /* last ON cycle NO DTC EVENT */
                {
                    SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter++;  /*Ã¨â‚¬ÂÃ¥Å’â€“Ã¦Â¬Â¡Ã¦â€¢ï¿½+*/
                    //SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_Three = SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter;/* ycl 20.05.08 */
                    if(SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter < DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_AgingUpperLimit)
                    {
                        SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_Three = SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter;
                    }
                    else if(SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter > DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_AgingUpperLimit)
                    {
                        SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_Two ++;/* ycl 20.05.08 */
                        SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_Three = DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_AgingUpperLimit;

                        SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter = CanDEM_u_Zero;            /* Remove aging */
                        CanDem_u_ResetUDSStatis_CDTC(SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcStatus);    /* Ã¦Â¸â€¦Ã¥Å½â€ Ã¥ÂÂ²DTC */
                        SeDem_u_DTCInfo[LeDEM_u_DtcId].SeDem_u_DTCStatus  = 0x00U;   /* ycl 18.11.30 */
                        CanDem_ClearSnapShotData();/*zc 18.8.15*/
                        //CanDem_ClearExtendData();/*zc 18.8.15*/ /*zgz 200511*/
                        //SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_Three = CanDEM_u_Zero; /*ZGZ 20.05.11*/
                        SeDem_u_DTCLastTimeStatus[LeDEM_u_DtcId] = CanDem_u_FaultRecover; /*ZGZ 20.05.11*/
                    }
                    else/*aging counter > 40*/
                    {
                        //SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter = CanDEM_u_Zero;            /*Remove aging */
                        //CanDem_u_ResetUDSStatis_CDTC(SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcStatus);    /*Ã¦Â¸â€¦Ã¥Å½â€ Ã¥ÂÂ²DTC*/
                        //SeDem_u_DTCInfo[LeDEM_u_DtcId].SeDem_u_DTCStatus  = 0x00U;   /*ycl 18.11.30*/
                        //CanDem_ClearSnapShotData();/*zc 18.8.15*/
                        //CanDem_ClearExtendData();/*zc 18.8.15*/ /*zgz 200511*/
                        //SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_Three = CanDEM_u_Zero; /*ZGZ 20.05.11*/
                        //SeDem_u_DTCLastTimeStatus[LeDEM_u_DtcId] = CanDem_u_FaultRecover; /*ZGZ 20.05.11*/

                    }
                    SeDem_u_NvmWriteFlag[LeDEM_u_DtcId] = CanDem_u_StorageSaveDtc;                /*Set Write flag*/
                }
                SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcEvent_LastCycle = CanDEM_u_EventPassed;

                // EEPM_AppReadBlock(DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_DTC_EepID, &LaDEM_u_DtcNVMData[0]);
				// EEPM_AppWriteBlock(DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_DTC_EepID, &LaDEM_u_DtcNVMData[0]);
            }
            SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingFlag = CanDem_u_False;                /*Clear Aging Enable status*/
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
    for(LeDem_u_Index = CanDEM_u_Zero;LeDem_u_Index < (uint8)CanDem_u_SysEnCondNumber;LeDem_u_Index++)
    {
        if( (uint8)CanDEM_u_Zero != (SsDem_h_MoniEnCond.e_u_DebounceCurStatus & (0x01U << LeDem_u_Index)) )
        /* Ã¤Â½Â¿Ã¨Æ’Â½Ã¥Â½â€œÃ¥â€°ÂÃ¦Â¶Ë†Ã¦Å â€“Ã§Å Â¶Ã¦â‚¬ÂbitÃ¯Â¿Â½Ã¯Â¼Å’Ã¥ÂÂ³Ã¦Å“â€°Ã¤Â½Â¿Ã¨Æ’Â½Ã¦ÂÂ¡Ã¤Â»ï¿½*/
        {
            if((uint8)CanDEM_u_Zero == (SsDem_h_MoniEnCond.e_u_DebounceHisStatus & (0x01U << LeDem_u_Index)))
            /* Ã¤Â½Â¿Ã¨Æ’Â½Ã¥Å½â€ Ã¥ÂÂ²Ã¦Â¶Ë†Ã¦Å â€“Ã§Å Â¶Ã¦â‚¬ÂbitÃ¤Â¸ÂºÃ©â€ºï¿½*/
            {
                if(SeDem_w_MoniEnCondDebounceCnt[LeDem_u_Index] >= CaDEM_u_MoniEnTime[LeDem_u_Index])/* Ã¤Â½Â¿Ã¨Æ’Â½Ã¦Â¶Ë†Ã¦Å â€“Ã¦â€”Â¶Ã©â€”Â´Ã¥Ë†Â°Ã¨Â¾Â¾Ã¨Â®Â¾Ã¥Â®ï¿½*/
                {
                    SsDem_h_MoniEnCond.e_u_DebounceHisStatus |= (0x01U << LeDem_u_Index);/*Ã¤Â½Â¿Ã¨Æ’Â½Ã¥Å½â€ Ã¥ÂÂ²Ã¦Â¶Ë†Ã¦Å â€“Ã§Å Â¶Ã¦â‚¬Âbit */
                    if((uint8)CanDEM_u_Zero == LeDem_u_Index)/* IGN ON */
                    {
                        for(LeDem_u_DtcIndex = CanDEM_u_Zero;LeDem_u_DtcIndex < (uint8)CanDem_u_DtcNumber;LeDem_u_DtcIndex++)
                        {
                            SsDem_h_AgingInfo[LeDem_u_DtcIndex].e_u_AgingFlag = CanDem_u_True; /* Start Aging */
                            /*Aging Flag  */
                        }
                        SeDem_u_OperatingCycleEnCond |= (uint8)CanDem_u_IgnitionCycle;/* Ã¦â€œÂÃ¤Â½Å“Ã¥â€˜Â¨Ã¦Å“Å¸Ã¯Â¼Å’IGN ON */
                    }
                }
                else
                {
                    SeDem_w_MoniEnCondDebounceCnt[LeDem_u_Index]++;/* Ã¤Â½Â¿Ã¨Æ’Â½Ã¦Â¶Ë†Ã¦Å â€“Ã¦â€”Â¶Ã©â€”ï¿½+ */
                }
            }
        }
        else
        /* Ã¤Â½Â¿Ã¨Æ’Â½Ã¥Â½â€œÃ¥â€°ÂÃ¦Â¶Ë†Ã¦Å â€“Ã§Å Â¶Ã¦â‚¬ÂbitÃ¤Â¸ÂºÃ©â€ºÂ¶Ã¯Â¼Å’Ã¥ÂÂ³Ã¤Â½Â¿Ã¨Æ’Â½Ã¦ÂÂ¡Ã¤Â»Â¶Ã¤Â¸ÂÃ¦Â»ï¿½*/
        {
            SeDem_w_MoniEnCondDebounceCnt[LeDem_u_Index] = CanDEM_u_Zero;/* Ã¤Â½Â¿Ã¨Æ’Â½Ã¦Â¶Ë†Ã¦Å â€“Ã¦â€”Â¶Ã©â€”Â´Ã¦Â¸â€¦Ã©â€ºï¿½*/
            SsDem_h_MoniEnCond.e_u_DebounceHisStatus &=((uint8)~(0x01U << LeDem_u_Index));/* Ã¤Â½Â¿Ã¨Æ’Â½Ã¥Å½â€ Ã¥ÂÂ²Ã¦Â¶Ë†Ã¦Å â€“Ã§Å Â¶Ã¦â‚¬ÂbitÃ¦Â¸â€¦Ã©â€ºï¿½*/
            if((uint8)CanDEM_u_Zero == LeDem_u_Index)/* IGN OFF */
            {
                SeDem_u_OperatingCycleEnCond &= ((uint8)~(CanDem_u_IgnitionCycle));/* Ã¦â€œÂÃ¤Â½Å“Ã¥â€˜Â¨Ã¦Å“Å¸Ã¯Â¼Å’IGN OFF */
            }
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
static void CanDem_GetConditionStatus(void)
{
    uint8 LeDEM_u_DtcID = CanDEM_u_Zero;
    uint8 LeDem_u_Index;
    for(LeDem_u_Index = CanDEM_u_Zero;LeDem_u_Index < (uint8)CanDem_u_SysEnCondNumber;LeDem_u_Index++)
    {
        if(CanDEM_u_Null != SsDEM_h_MoniEnCodHandler[LeDem_u_Index])/* Ã¤Â½Â¿Ã¨Æ’Â½Ã¦ÂÂ¡Ã¤Â»Â¶Ã¥â€¡Â½Ã¦â€¢Â°Ã¤Â¸ÂÃ¤Â¸ï¿½ */
        {
            if((uint8)CanDem_u_True == (*SsDEM_h_MoniEnCodHandler[LeDem_u_Index])())/*Ã¤Â½Â¿Ã¨Æ’Â½Ã¦ÂÂ¡Ã¤Â»Â¶Ã¦Â»Â¡Ã¨Â¶Â³*/
            {
                SsDem_h_MoniEnCond.e_u_DebounceCurStatus |=(uint8)(0x01U << LeDem_u_Index);/* Ã¤Â½Â¿Ã¨Æ’Â½Ã¥Â½â€œÃ¥â€°ÂÃ¦Â¶Ë†Ã¦Å â€“Ã§Å Â¶Ã¦â‚¬Âbit */
            }
            else/* Ã¤Â½Â¿Ã¨Æ’Â½Ã¦ÂÂ¡Ã¤Â»Â¶Ã¤Â¸ÂÃ¦Â»Â¡ */
            {
                SsDem_h_MoniEnCond.e_u_DebounceCurStatus &=(uint8)(~(0x01U << LeDem_u_Index));/* Ã¤Â½Â¿Ã¨Æ’Â½Ã¥Â½â€œÃ¥â€°ÂÃ¦Â¶Ë†Ã¦Å â€“Ã§Å Â¶Ã¦â‚¬ÂbitÃ¨Â¯Â·Ã©â€ºï¿½*/
                if(LeDem_u_Index ==  CanDEM_u_Zero) /* IGN Hanlde */
                {
                    for(LeDEM_u_DtcID = CanDEM_u_Zero;LeDEM_u_DtcID < (uint8)CanDem_u_DtcNumber;++LeDEM_u_DtcID)
                    {
                        if(SsDem_h_DebounceInfo[LeDEM_u_DtcID].e_u_DtcEvent_ThisCycle == CanDEM_u_EventFailed)
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
    uint8 LeDEM_u_DtcID = CanDEM_u_Zero;
    static uint8 SeDEM_u_ChoiceToProcess = 0xAAU;

    if(CanDEM_u_Zero != SeDEM_u_ChoiceToProcess)  /*first 10 DTC*/
    {
   //     for(LeDEM_u_DtcID = CanDEM_u_Zero;LeDEM_u_DtcID < (uint8)CanDem_u_DtcNumber-10U;++LeDEM_u_DtcID)  ggl
        for(LeDEM_u_DtcID = CanDEM_u_Zero;LeDEM_u_DtcID < (uint8)CanDem_u_DtcNumber;++LeDEM_u_DtcID)  
        {
            if((uint8)CanDem_u_True == SeDem_u_DTCSupport[LeDEM_u_DtcID]) /*DTC Support*/
            {
                if((uint8)CanDem_u_True == SeDem_u_DTCSettingDisabled) /*85 Service*/
                {
                    if((uint8)CanDem_u_True == CanDem_PeriodEventOperating(LeDEM_u_DtcID))
                    {
                        CanDem_DebounceOperating(LeDEM_u_DtcID); 
                    }
                    CanDem_DcmAgingCounter(LeDEM_u_DtcID);  
                    CanDem_SaveDTCOperating(LeDEM_u_DtcID,CanDEM_u_WriteE2promLength);/*save DTC to EEPROM*/
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
                        CanDem_DebounceOperating(LeDEM_u_DtcID);/* DTCæ¶ˆæŠ– */
                    }
                    CanDem_DcmAgingCounter(LeDEM_u_DtcID);  /* è€åŒ–è®¡æ•° */
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
    if((uint8)CanDem_u_DtcNumber > LeDEM_u_DtcId)
    { /*æ“ä½œå‘¨æœŸ=è®¾ç½®*/
        if( ((SeDem_u_OperatingCycleEnCond & DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_DtcOperationCycleId ) \
                == DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_DtcOperationCycleId ) \
          &&((SsDem_h_MoniEnCond.e_u_DebounceHisStatus & DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_DtcEnCond) \
                == DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_DtcEnCond))/* ä½¿èƒ½åŽ†å²æ¶ˆæŠ–çŠ¶æ€ä¸º1ï¼Œå³ä½¿èƒ½æ¡ä»¶=è®¾ç½® */
        {
            if(CanDEM_u_Null != DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_DTCHandler)/* DTCå‘ç”Ÿå‡½æ•°ä¸ä¸º */
            {
                if((uint8)CanDEM_u_EventFailed != DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_DTCHandler())/* æ²¡æœ‰DTCäº§ç”Ÿ */
                {
                    /* Fail->Pass */
                    if((uint8)CanDEM_u_EventFailed == SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DTCEvent_OldStatus)/* ä¹‹å‰æœ‰DTCäº§ç”Ÿ */
                    {
                        SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DTCEvent_OldStatus = CanDEM_u_EventPassed;
                        SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DebounceFlag = CanDem_u_DebouncePassed;/* DTCäº§ç”Ÿæ¶ˆæŠ–flagç½®ä¸ºPASS */
                        SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_w_DebounceTime = CanDEM_u_Zero;/* DTCæ¶ˆæŠ–æ—¶é—´æ¸…é›¶ */
                    }
                }
                else/* æœ‰DTCäº§ç”Ÿ */
                {
                    /* Pass->Fail */
                    if((uint8)CanDEM_u_EventPassed == SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DTCEvent_OldStatus)/*ä¹‹å‰æ²¡æœ‰DTCäº§ç”Ÿ*/
                    {						
                        SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcEvent_ThisCycle = CanDEM_u_EventFailed;
                        SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DTCEvent_OldStatus = CanDEM_u_EventFailed;
                        SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DebounceFlag = CanDem_u_DebounceFailed;/* DTCäº§ç”Ÿæ¶ˆæŠ–flagç½®ä¸ºFail */
                        SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_w_DebounceTime = CanDEM_u_Zero;/* DTCæ¶ˆæŠ–æ—¶é—´æ¸…é›¶ */
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
static void CanDem_DebounceOperating(uint8 LeDEM_u_DtcId )
{
    if(LeDEM_u_DtcId < (uint8)CanDem_u_DtcNumber)
    {
        if((uint8)CanDem_u_DebouncePassed == SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DebounceFlag)/* DTCäº§ç”Ÿæ¶ˆæŠ–flagä¸ºPass,å³DTCä»Žæœ‰åˆ°æ—  */
        {
            if(SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_w_DebounceTime \
            >= SsDem_e_DebounceTimeTable[DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_w_DebounceTimeTableIndex].e_w_DtcTimePass)
            /*DTCæ¶ˆæŠ–æ—¶é—´å¤§äºŽè®¾ç½®ï¿½ms)*/
            {
                SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DebounceFlag = CanDem_u_DebounceNone;/*DTCäº§ç”Ÿæ¶ˆæŠ–flagç½®ä¸ºNone*/
                SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_w_DebounceTime = CanDEM_u_Zero;/*DTCæ¶ˆæŠ–æ—¶é—´æ¸…é›¶*/
                CanDem_u_ResetUDSStatus_TF(SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcStatus);/*DTC Statusçš„TFä½è®¾ç½®ä¸º0ï¼Œæ— å½“å‰DTC*/
                SeDem_u_DTCLastTimeStatus[LeDEM_u_DtcId] = CanDem_u_FaultRecover; /*zc add 18.8.15*/

                SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter = CanDEM_u_Zero;/*è€åŒ–è®¡æ•°æ¸…é›¶*/
            }
            else
            {
                SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_w_DebounceTime++;/*10ms*/
            }
        }
        else if((uint8)CanDem_u_DebounceFailed == SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DebounceFlag)/*DTCäº§ç”Ÿæ¶ˆæŠ–flagä¸ºFail,å³DTCä»Žæ— åˆ°æœ‰*/
        {
            if(SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_w_DebounceTime \
            >= SsDem_e_DebounceTimeTable[DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_w_DebounceTimeTableIndex].e_w_DtcTimeFail)
            /*DTCæ¶ˆæŠ–æ—¶é—´å¤§äºŽè®¾ç½®ï¿½ms)*/
            {
                SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DebounceFlag = CanDem_u_DebounceNone;/*DTCäº§ç”Ÿæ¶ˆæŠ–flagç½®ä¸ºNone*/
                SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_w_DebounceTime = CanDEM_u_Zero;/*DTCæ¶ˆæŠ–æ—¶é—´æ¸…é›¶*/
                CanDem_u_SetUDSStatus_TF(SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcStatus);/*DTC Statusçš„TFä½è®¾ç½®ä¸º1ï¼Œæœ‰å½“å‰DTC*/
                CanDem_u_SetUDSStatis_CDTC(SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcStatus);/*DTC Statusçš„CDTCä½è®¾ç½®ä¸º1ï¼Œæœ‰åŽ†å²DTC*/

                if((uint8)CanDem_u_FaultRecover == SeDem_u_DTCLastTimeStatus[LeDEM_u_DtcId])
                {
                    // if(SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_One < 0xff)/*ycl 20.05.08*/
                    // {
                    //     SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_One ++;/*ZGZ 20.05.11*/
                    //     SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_Three  = CanDEM_u_Zero;
                    //     //SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_One = 0xff;/*ZGZ 20.05.11*/
                    // }

                    CanDem_SetSnapShotData(LeDEM_u_DtcId);  /*è®¾ç½®å¿«ç…§ä¿¡æ¯   zc 18.8.15*/
                    // CanDem_SetExtendData(LeDEM_u_DtcId);sss
                    SeDem_u_DTCLastTimeStatus[LeDEM_u_DtcId] = CanDem_u_FaultNoRecover;
                }
                else
                {
                    ;
                }

                SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter = CanDEM_u_Zero;/*è€åŒ–è®¡æ•°æ¸…é›¶*/

                SeDem_u_NvmWriteFlag[LeDEM_u_DtcId] = CanDem_u_StorageSaveDtc;/*DTCå†™EEPROMçš„flagç½®ä¸º1*/
            }
            else
            {
                SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_w_DebounceTime++;/*10ms*/
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
static void CanDem_SaveDTCOperating(uint8 LeDEM_u_DtcId,uint8 LeDEM_u_DtcLen)
{
    uint8 LaDEM_u_DtcNVMData[13];
    uint16 DTCSnapShotData_Speed;
    uint32 DTCSnapShotData_Odometer;

    //uint8 LeDem_u_Change_Flag = CanDem_u_False;

    if(((uint8)CanDem_u_DtcNumber > LeDEM_u_DtcId) && ((uint8)CanDEM_u_Zero != LeDEM_u_DtcLen))
    {
        if((uint8)CanDem_u_StorageSaveDtc == SeDem_u_NvmWriteFlag[LeDEM_u_DtcId])/*DTCÃ¥â€ â„¢EEPROMÃ§Å¡â€žflagÃ§Â­â€°Ã¤Âºï¿½*/
        {   
            DTCSnapShotData_Speed = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_Speed;
            DTCSnapShotData_Odometer = SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_OdometerValue;

            if((SsDem_h_DebounceInfo[LeDEM_u_DtcId].e_u_DtcStatus & CanDem_u_UDSStatus_CDTC) == CanDem_u_UDSStatus_CDTC)
            /*DTC StatusÃ§Å¡â€žCDTCÃ¤Â½ÂÃ§Â­â€°Ã¯Â¿Â½Ã¯Â¼Å’Ã¦Å“â€°Ã¥Å½â€ Ã¥ÂÂ²DTC*/
            {
               SeDem_u_DTCInfo[LeDEM_u_DtcId].SeDem_u_DTCStatus  = 0x80U;
               SeDem_u_DTCInfo[LeDEM_u_DtcId].SeDem_u_DTCStatus |= (SsDem_h_AgingInfo[LeDEM_u_DtcId].e_u_AgingCounter);
            }

            LaDEM_u_DtcNVMData [0]  =  SeDem_u_DTCInfo[LeDEM_u_DtcId].SeDem_u_DTCStatus;/*ycl 181026*/
            LaDEM_u_DtcNVMData [1]  =  (uint8)(DTCSnapShotData_Odometer & 0xFF);
            LaDEM_u_DtcNVMData [2]  =  (uint8)((DTCSnapShotData_Odometer >> 8)& 0xFF);
            LaDEM_u_DtcNVMData [3]  =  (uint8)((DTCSnapShotData_Odometer >> 16)& 0xFF);
            LaDEM_u_DtcNVMData [4]  =  SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_ECU_Voltage;
            LaDEM_u_DtcNVMData [5]  =  (uint8)( DTCSnapShotData_Speed & 0xFF);
            LaDEM_u_DtcNVMData [6]  =  (uint8)((DTCSnapShotData_Speed >> 8) & 0xFF);
            LaDEM_u_DtcNVMData [7]  =  SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_Sec;
            LaDEM_u_DtcNVMData [8]  =  SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_Min;
            LaDEM_u_DtcNVMData [9]  =  SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_Hour;
            LaDEM_u_DtcNVMData [10]  =  SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_Day;
            LaDEM_u_DtcNVMData [11]  =  SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_Month;
            LaDEM_u_DtcNVMData [12]  =  SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData.e_u_Year;
            
            // LaDEM_u_DtcNVMData [13]  =  SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_One;
            // LaDEM_u_DtcNVMData [14]  =  SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_Two; GGL
            // LaDEM_u_DtcNVMData [14]  =  SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData.ExtendDataRecord_Three;

            EEPM_AppWriteBlock(DsDem_h_ManagementUnit[LeDEM_u_DtcId].e_u_DTC_EepID, &LaDEM_u_DtcNVMData[0]);
            SeDem_u_NvmWriteFlag[LeDEM_u_DtcId] = CanDem_u_StorageNone;/*DTCå†™EEPROMçš„flagæ¸…é›¶*/
        }
    }
}

/*******************************************************************************
Name			:	CanDem_SaveAllDTC
Syntax			:   None
Sync/Async	    :   Synchronous
Reentrancy		:   None
Parameters(in)  :   None
Parameters(out) :   None
Return value	:   None
Description		:   Save All Dtc
Call By			:	CanDem_SaveDTCOperating
History
<No.>    <author>    <time>    <description>

|******************************************************************************/
static void CanDem_SaveAllDTC(void)
{
	uint8 LeDem_u_Index;
	for(LeDem_u_Index = CanDEM_u_Zero;LeDem_u_Index < (uint8)CanDem_u_DtcNumber;LeDem_u_Index++)
	{
		CanDem_SaveDTCOperating(LeDem_u_Index,CanDEM_u_WriteE2promLength);
	}
}

static void CanDem_SetSnapShotData(uint8 LeDEM_u_DtcId)
{
    SnapShotTable_Type TsDEM_h_SnapShotData;

    TsDEM_h_SnapShotData.e_u_OdometerValue     = (uint32)GetCanApp_u_CdcTotMilg();
    TsDEM_h_SnapShotData.e_u_ECU_Voltage       = (uint8)(ADCM_GetValidValue(ADCMCFG_KL30_AD_CH) / 15.3);
    TsDEM_h_SnapShotData.e_u_Speed             = (uint16)GetCanApp_u_EspVehSpd();
    TsDEM_h_SnapShotData.e_u_Sec               = RTE_NET_Can_Read_TboxLocalTiSec();     
    TsDEM_h_SnapShotData.e_u_Min               = RTE_NET_Can_Read_TboxLocalTiMins();    
    TsDEM_h_SnapShotData.e_u_Hour              = RTE_NET_Can_Read_TboxLocalTiHr();
    TsDEM_h_SnapShotData.e_u_Day               = RTE_NET_Can_Read_TboxLocalTiDate();
    TsDEM_h_SnapShotData.e_u_Month             = RTE_NET_Can_Read_TboxLocalTiMth();
    TsDEM_h_SnapShotData.e_u_Year              = RTE_NET_Can_Read_TboxLocalTiYear();

    SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCSnapShotData = TsDEM_h_SnapShotData;
    //SeDem_u_DTCSnapShotData[LeDEM_u_DtcId][0].e_u_RecordNumber = 1U;
}


static void CanDem_ClearSnapShotData(void)
{
    uint8 LeDem_u_DtcId;
    //uint8 LeDem_u_DtcRecordNumber;

    for(LeDem_u_DtcId = CanDem_u_Zero;LeDem_u_DtcId < CanDem_u_DtcNumber ;LeDem_u_DtcId++)
    {
       //for(LeDem_u_DtcRecordNumber = CanDem_u_Zero;LeDem_u_DtcRecordNumber < (uint8)CanDEM_u_SnapOccurtimesMax;LeDem_u_DtcRecordNumber++)
       {
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_OdometerValue    = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_ECU_Voltage      = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_Speed            = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_Sec              = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_Min              = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_Hour             = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_Day              = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_Month            = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCSnapShotData.e_u_Year             = CanDEM_u_Zero;
       }
       SeDem_u_DTCLastTimeStatus[LeDem_u_DtcId] = CanDem_u_FaultRecover;

    }
}

static void CanDem_SetExtendData(uint8 LeDEM_u_DtcId)
{
    //DTCExtendData_Type TsDEM_h_ExtendData;

    //TsDEM_h_ExtendData.ExtendDataRecord_One     = 1;
    //TsDEM_h_ExtendData.ExtendDataRecord_Two     = 2;
    //TsDEM_h_ExtendData.ExtendDataRecord_Three   = 3;

    //SeDem_u_DTCInfo[LeDEM_u_DtcId].DTCExtendData = TsDEM_h_ExtendData;
    //SeDem_u_DTCSnapShotData[LeDEM_u_DtcId][0].e_u_RecordNumber = 1U;
}


static void CanDem_ClearExtendData(void)
{
    uint8 LeDem_u_DtcId;
    //uint8 LeDem_u_DtcRecordNumber;

    for(LeDem_u_DtcId = CanDem_u_Zero;LeDem_u_DtcId < CanDem_u_DtcNumber ;LeDem_u_DtcId++)
    {
        //for(LeDem_u_DtcRecordNumber = CanDem_u_Zero;LeDem_u_DtcRecordNumber < (uint8)CanDEM_u_SnapOccurtimesMax;LeDem_u_DtcRecordNumber++)
        {
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCExtendData.ExtendDataRecord_One = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCExtendData.ExtendDataRecord_Two = CanDEM_u_Zero;
            SeDem_u_DTCInfo[LeDem_u_DtcId].DTCExtendData.ExtendDataRecord_Three = CanDEM_u_Zero;
        }
        SeDem_u_DTCLastTimeStatus[LeDem_u_DtcId] = CanDem_u_FaultRecover;

    }
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
uint8 CanDem_DcmGetDTCStatusAvailabilityMask(uint8* DTCStatusMask)
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
uint8 CanDem_DcmGetNumberOfFilteredDTC(uint16* NumberOfFilteredDTC,uint8 DTC_RequestMask)/*19 01*/
{
    volatile uint16  LeDem_w_NumberOfEvents;
    uint8   LeDem_u_Index;
    LeDem_w_NumberOfEvents = CanDEM_u_Zero;

    for(LeDem_u_Index = CanDEM_u_Zero;LeDem_u_Index <= (uint8)CanDem_u_DtcNumber - CanDem_u_DisRepNumber;LeDem_u_Index++)  
    {
        if(((SsDem_h_DebounceInfo[LeDem_u_Index].e_u_DtcStatus) & DTC_RequestMask) != (uint8)CanDEM_u_Zero)  /*zc change*/
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
uint8 CanDem_DcmGetNextFilteredDTC(uint32* DTC,uint8* DTCStatus,uint16 DTCNumber)/*19 02*/
{
    uint8 LeDem_u_IndexList;
    uint32 LeDem_u_DtcNumTemp;
    LeDem_u_IndexList = SeDem_u_DTCFilterIndexList[DTCNumber];
    LeDem_u_DtcNumTemp =((uint32)DsDem_h_ManagementUnit[LeDem_u_IndexList].e_w_Num) << 8U;
    LeDem_u_DtcNumTemp |=(uint32)(DsDem_h_ManagementUnit[LeDem_u_IndexList].e_u_FailType);
    *DTC = LeDem_u_DtcNumTemp;
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
uint8 CanDem_DcmGetStatusOfDTC(uint32 DTC,uint32 DTCOrigin,uint8* DTCStatus)/*19 04*/
{
    uint16 LeDem_w_DTCIndex;
    uint8  LeDem_u_Return;
    LeDem_w_DTCIndex = CanDem_DcmFindEventFromDtcInfo(DTC,DTCOrigin);
    if((uint16)0xFFFFU != LeDem_w_DTCIndex)
    {
        *DTCStatus = ( ( SsDem_h_DebounceInfo[LeDem_w_DTCIndex].e_u_DtcStatus) & (uint8)Can_u_StatusAvailabilityMask);
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
void CanDem_DcmGetAllSupportDTC(uint32* DTC,uint8* DTCStatus,uint8 DTCNumber)/*19 0A*/
{
    uint32 LeDem_u_DtcNumTemp;
    LeDem_u_DtcNumTemp =((uint32)DsDem_h_ManagementUnit[DTCNumber].e_w_Num) << 8U;
    LeDem_u_DtcNumTemp |=(uint32)(DsDem_h_ManagementUnit[DTCNumber].e_u_FailType);
    *DTC = LeDem_u_DtcNumTemp;
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
uint8 CanDem_DcmClearDTCSignal(uint32 LeCanDem_dw_DTCNum)/*14*/
{
    uint8 LeDem_u_Index;
    uint8 LeDem_u_Return;
    if((uint32)0xFFFFFFU == LeCanDem_dw_DTCNum)
    {
        for(LeDem_u_Index = CanDEM_u_Zero;LeDem_u_Index < (uint8)CanDem_u_DtcNumber;LeDem_u_Index++)
        {
                SsDem_h_DebounceInfo[LeDem_u_Index].e_u_DtcStatus = CanDEM_u_Zero; /* clear DTC status */
                SsDem_h_DebounceInfo[LeDem_u_Index].e_u_DTCEvent_OldStatus = CanDEM_u_EventPassed; /* clear event status */
                SsDem_h_AgingInfo[LeDem_u_Index].e_u_AgingCounter = CanDEM_u_Zero; /* clear aging counter*/
                SeDem_u_DTCInfo[LeDem_u_Index].SeDem_u_DTCStatus = (uint8)0x00U;

                CanDem_ClearSnapShotData();/*zc 18.8.15*/
                //CanDem_ClearExtendData();
                SeDem_u_NvmWriteFlag[LeDem_u_Index] = CanDem_u_StorageSaveDtc;
        }
       
        LeDem_u_Return = CanDem_u_Ok;
    }
    else
    {
        LeDem_u_Return =  CanDem_u_Nok;
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
uint16 CanDem_DcmFindEventFromDtcInfo(uint32 Dtc,uint32  MemoryId)
{
    uint16 LeDem_u_Index;
    uint16 LeDem_u_Result;

    LeDem_u_Result = 0xFFFFU;
    if((uint8)CanDEM_u_Zero != MemoryId)
    {
        ;
    }

    for(LeDem_u_Index = CanDEM_u_Zero;LeDem_u_Index <= (uint8)CanDem_u_DtcNumber - CanDem_u_DisRepNumber;LeDem_u_Index++) 
    {
        LeDem_dw_DTC = (uint32)(((uint32)DsDem_h_ManagementUnit[LeDem_u_Index].e_w_Num << (uint32)0x08U) + DsDem_h_ManagementUnit[LeDem_u_Index].e_u_FailType);
        if(LeDem_dw_DTC == Dtc)
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
uint8 CanDem_DcmEnableDTCSetting(void)/*85 01*/
{
    Diag_flag = 0U;
    //ifGetCanApp_u_GW_OTAMode())//SSS-20251122
    //{
        SeDem_u_DTCSettingDisabled = CanDem_u_True;
    //}    

    return CanDem_u_Ok;
}

/*******************************************************************************
Name            : CanDem_DcmEnableDTCSetting
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
uint8 CanDem_DcmDisableDTCSetting(void)/*85 02*/
{
    Diag_flag = 1U;
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
    uint8 CanDem_u_temp= CanDem_u_False;
    if(SsDem_h_MoniEnCond.e_u_DebounceHisStatus == 0x1Fu)
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
uint8 CanDem_GetDTCSetting(void)/*85*/
{
    return SeDem_u_DTCSettingDisabled;
}





#define APP_KEY_CONST_0 0x03
#define APP_KEY_CONST_1 0x8B
#define APP_KEY_CONST_2 0x69
#define APP_KEY_CONST_3 0xA9
  
unsigned char SecM_ComputeKeyLevel1(unsigned long seed,unsigned long KeyK,unsigned long *key)
{
	
	uint8 Key1[4];
    uint8 Seed2[4];
    uint8 Key2[4];
	uint8 tempseed[4];
	uint8 Key3[4];

	uint32 tempKey1;
	uint32 tempKey2;
	

	tempseed[0] = (uint8)((seed&0xFF000000) >>24);
	tempseed[1] = (uint8)((seed&0xFF0000) >>16);
	tempseed[2] = (uint8)((seed&0xFF00) >>8);
	tempseed[3] = (uint8)(seed&0xFF);
	
	
	
	Key1[0] = tempseed[0] ^ APP_KEY_CONST_0;
    Key1[1] = tempseed[1] ^ APP_KEY_CONST_1;
    Key1[2] = tempseed[2] ^ APP_KEY_CONST_2;
    Key1[3] = tempseed[3] ^ APP_KEY_CONST_3;
	
	
	Seed2[0] = ((tempseed[3] &0x80) >>7 ) |((tempseed[3] &0x40)>>5 )|((tempseed[3] &0x20)>>3)|((tempseed[3]&0x10 ) >>1)|((tempseed[3]&0x08 ) <<1)|((tempseed[3]&0x04) <<3)|((tempseed[3]&0x02 ) <<5)|((tempseed[3]&0x01 ) <<7); 
	Seed2[1] = ((tempseed[2] &0x80) >>7 ) |((tempseed[2] &0x40)>>5 )|((tempseed[2] &0x20)>>3)|((tempseed[2]&0x10 ) >>1)|((tempseed[2]&0x08 ) <<1)|((tempseed[2]&0x04) <<3)|((tempseed[2]&0x02 ) <<5)|((tempseed[2]&0x01 ) <<7); 
	Seed2[2] = ((tempseed[1] &0x80) >>7 ) |((tempseed[1] &0x40)>>5 )|((tempseed[1] &0x20)>>3)|((tempseed[1]&0x10 ) >>1)|((tempseed[1]&0x08 ) <<1)|((tempseed[1]&0x04) <<3)|((tempseed[1]&0x02 ) <<5)|((tempseed[1]&0x01 ) <<7); 
	Seed2[3] = ((tempseed[0] &0x80) >>7 ) |((tempseed[0] &0x40)>>5 )|((tempseed[0] &0x20)>>3)|((tempseed[0]&0x10 ) >>1)|((tempseed[0]&0x08 ) <<1)|((tempseed[0]&0x04) <<3)|((tempseed[0]&0x02 ) <<5)|((tempseed[0]&0x01 ) <<7); 

 
	Key2[0] = Seed2[0] ^ APP_KEY_CONST_0;
    Key2[1] = Seed2[1] ^ APP_KEY_CONST_1;
    Key2[2] = Seed2[2] ^ APP_KEY_CONST_2;
    Key2[3] = Seed2[3] ^ APP_KEY_CONST_3;
	
	
	tempKey1 = (Key1[3]&0xFF) | ((Key1[2]<<8) & 0xFF00) | ((Key1[1]<<16) & 0xFF0000) | ((Key1[0]<<24) & 0xFF000000);
	tempKey2 = (Key2[3]&0xFF) | ((Key2[2]<<8) & 0xFF00) | ((Key2[1]<<16) & 0xFF0000) | ((Key2[0]<<24) & 0xFF000000);
	
	*key = (tempKey1 + tempKey2) & 0xFFFFFFFF;
	
	return 0;
}

uint32 CanApp_SecurityAccessCheckKey(uint8 CanApp_u_Level)
{
    uint32 LeCanApp_dw_ComputeKey = 0U;
    
    SecM_ComputeKeyLevel1(g_applDescSeedX,0,&LeCanApp_dw_ComputeKey);
    
    return LeCanApp_dw_ComputeKey;
}



/////////////////////////////NRC22////////////////////////////////////////


void Check_VehicleSpeed_Status(void)
{
	if((0u == GetCanApp_u_MsgCurrentPresent(VeCanApp_e_VIU_FR_1C3)) && (0u == GetCanApp_u_MsgCurrentPresent(VeCanApp_e_VIU_FR_2EC)) && (1u == VehicleSpeed_Gear_Timeout_Flag))  //ÃŽÂ´ÃŠÃ•ÂµÂ½Â³ÂµÃ‹Ã™ÂºÃÂµÂµÃŽÂ»ÃÃ…ÂºÃ…
	{
		Current_VehicleSpeed_Gear_Flag = 1;
		
	}
	else
	{
		Current_VehicleSpeed_Gear_Flag = 0;
		
		VehicleSpeed_Gear_TimeoutCounter++;
		if(VehicleSpeed_Gear_TimeoutCounter >100 )
		{
			VehicleSpeed_Gear_Timeout_Flag = 0;
			VehicleSpeed_Gear_TimeoutCounter = 66;
		}
		
		
	}
	
	
/*	if( ( Current_VehicleSpeed_Gear_Flag == Last_VehicleSpeed_Gear_Flag) && (Current_VehicleSpeed_Gear_Flag ==1) )
	{
		
	//	Last_VehicleSpeed_Gear_Flag = Current_VehicleSpeed_Gear_Flag;
		VehicleSpeed_Gear_Flag = 1;
		
	}
	else
	{		
		VehicleSpeed_Gear_Flag = 0;
		Last_VehicleSpeed_Gear_Flag = Current_VehicleSpeed_Gear_Flag;
		
	}*/
	
	
}




uint8 PendingVehicleSpeed(void)
{
    uint16 TempVehicleSpeed;/*VehicleSpeed value*/
    uint8  TempVehicleSpeedStatus;
	
	//TempVehicleSpeed = GetCanApp_u_EspVehSpd();
    
	/*_vehicleSpeed lost*/
	if(((uint8)1u == Current_VehicleSpeed_Gear_Flag) &&(1 == CanApp_u_GetNetWorkStaus()))
	{
		TempVehicleSpeedStatus = 1;
	}
	/*VehicleSpeed   0Â£ÂºÃ“ÃÃÂ§Â£Â¬1Â£ÂºÃŽÃžÃÂ§*/
	else if(1u == RTE_NET_Can_Read_EspVehSpdVld()) 
	{
		TempVehicleSpeedStatus = 1;
	}
	else if (0.05625f * GetCanApp_u_EspVehSpd() <= 3.0f)
	{
        TempVehicleSpeedStatus = 1;
	}
	else
	{
		TempVehicleSpeedStatus = 0;
	}  
    return TempVehicleSpeedStatus;
}


uint8 PendingPDCM_actualGear(void)
{
    uint8 TempPDCM_actualGear;   //ÂµÂ²ÃŽÂ»
    uint8 TempPDCM_actualGearStatus;
	
	
	TempPDCM_actualGear = RTE_NET_Can_Read_VcuGearPosn();
	
	/*Gear lost*/
	if(((uint8)1u == Current_VehicleSpeed_Gear_Flag) &&(1 == CanApp_u_GetNetWorkStaus()))
	{
		TempPDCM_actualGearStatus = 1;
	}
	/*Gear   0Â£ÂºÃ“ÃÃÂ§Â£Â¬1Â£ÂºÃŽÃžÃÂ§*/
	else if(1u == RTE_NET_Can_Read_VcuVehGearPosnVld()) 
	{
		TempPDCM_actualGearStatus = 1;
	}
	else if ((TempPDCM_actualGear == 3) || (TempPDCM_actualGear == 1))  //1Â£ÂºPÂµÂµ   3Â£ÂºNÂµÂµ
	{
        TempPDCM_actualGearStatus = 1;
	}
	else
	{
		TempPDCM_actualGearStatus = 0;
	}  
    return TempPDCM_actualGearStatus;
}


/////////////////DTC_Trigger///////////////////////




static void CanApp_CheckDtcGenerate(void)
{
    static uint16 e_w_delaytime;
    static uint8 a_u_LastStatus[CanDem_u_DtcNumber - CanDem_u_DisRepNumber];
    static uint16 LeAppdesc_w_ActiveDtcIndex = 0;
    static uint8 LeAppdesc_u_IsSendingStatusChange = 0; // 标记是否正在处理状态变化发送
    
    uint8  LeAppdesc_u_StatusMask;
    uint16 LeAppdesc_w_Index;
    uint16 LeAppdesc_u_DtcNumber = (CanDem_u_DtcNumber - CanDem_u_DisRepNumber);/*支持的DTC数量*/
    uint8 LeAppdesc_u_ActiveDtcCount = 0;
    uint16 LeAppdesc_u_ActiveDtcList[CanDem_u_DtcNumber - CanDem_u_DisRepNumber];
    uint8 LeAppdesc_u_HasStatusChange = 0; // 标记是否有状态变化
    uint16 LeAppdesc_u_ChangedDtcIndex = 0; // 状态变化的DTC索引
    
    (void)CanDem_DcmGetDTCStatusAvailabilityMask(&LeAppdesc_u_StatusMask);
    
    // 检查DTC状态变化并统计活跃DTC
    for(LeAppdesc_w_Index = 0; LeAppdesc_w_Index < LeAppdesc_u_DtcNumber; LeAppdesc_w_Index++)
    {
        uint32 LeAppdesc_u_DTCCode;
        uint8  LeAppdesc_u_DTCStatus;
        
        if(DsDem_h_ManagementUnit[LeAppdesc_w_Index + 1].e_u_DtcSupport == TRUE)
        {
            CanDem_DcmGetAllSupportDTC(&LeAppdesc_u_DTCCode, &LeAppdesc_u_DTCStatus, LeAppdesc_w_Index);
            
            // 存储DTC信息
            SeCanApp_u_DtcSendBuf[LeAppdesc_w_Index][0] = (uint8)((LeAppdesc_u_DTCCode >> 16U) & 0xFFU);
            SeCanApp_u_DtcSendBuf[LeAppdesc_w_Index][1] = (uint8)((LeAppdesc_u_DTCCode >> 8U) & 0xFFU);
            SeCanApp_u_DtcSendBuf[LeAppdesc_w_Index][2] = (uint8)(LeAppdesc_u_DTCCode & 0xFFU);
            SeCanApp_u_DtcSendBuf[LeAppdesc_w_Index][3] = LeAppdesc_u_DTCStatus;
            
            // 检测状态变化
            if(LeAppdesc_u_DTCStatus != a_u_LastStatus[LeAppdesc_w_Index])
            {
                LeAppdesc_u_HasStatusChange = 1;
                LeAppdesc_u_ChangedDtcIndex = LeAppdesc_w_Index;
                SeCanApp_u_DtcNeedSend[LeAppdesc_w_Index] = TRUE;
                a_u_LastStatus[LeAppdesc_w_Index] = LeAppdesc_u_DTCStatus;
            }
            
            // 统计活跃DTC并记录索引
            if(LeAppdesc_u_DTCStatus != 0)
            {
                LeAppdesc_u_ActiveDtcList[LeAppdesc_u_ActiveDtcCount] = LeAppdesc_w_Index;
                LeAppdesc_u_ActiveDtcCount++;
            }
        }
    }
    
    // 处理状态变化的情况（立即发送）
    if(LeAppdesc_u_HasStatusChange)
    {
        // 设置状态变化处理标记
        LeAppdesc_u_IsSendingStatusChange = 1;
        
        // 发送第一个状态变化的DTC
        RTE_NET_Can_Write_VrhcuDTC1_HighByte(SeCanApp_u_DtcSendBuf[LeAppdesc_u_ChangedDtcIndex][0]);
        RTE_NET_Can_Write_VrhcuDTC1_MiddByte(SeCanApp_u_DtcSendBuf[LeAppdesc_u_ChangedDtcIndex][1]);
        RTE_NET_Can_Write_VrhcuDTC1_LowByte(SeCanApp_u_DtcSendBuf[LeAppdesc_u_ChangedDtcIndex][2]);
        RTE_NET_Can_Write_VrhcuDTC1_Status(SeCanApp_u_DtcSendBuf[LeAppdesc_u_ChangedDtcIndex][3]);
        
        // 查找第二个状态变化的DTC
        uint8 LeAppdesc_u_HasSecondChange = 0;
        uint16 LeAppdesc_u_SecondChangedDtcIndex = 0;
        
        for(LeAppdesc_w_Index = 0; LeAppdesc_w_Index < LeAppdesc_u_DtcNumber; LeAppdesc_w_Index++)
        {
            if(LeAppdesc_w_Index != LeAppdesc_u_ChangedDtcIndex && SeCanApp_u_DtcNeedSend[LeAppdesc_w_Index])
            {
                LeAppdesc_u_HasSecondChange = 1;
                LeAppdesc_u_SecondChangedDtcIndex = LeAppdesc_w_Index;
                break;
            }
        }
        
        // 发送第二个状态变化的DTC或填充为0
        if(LeAppdesc_u_HasSecondChange)
        {
            RTE_NET_Can_Write_VrhcuDTC2_HighByte(SeCanApp_u_DtcSendBuf[LeAppdesc_u_SecondChangedDtcIndex][0]);
            RTE_NET_Can_Write_VrhcuDTC2_MiddByte(SeCanApp_u_DtcSendBuf[LeAppdesc_u_SecondChangedDtcIndex][1]);
            RTE_NET_Can_Write_VrhcuDTC2_LowByte(SeCanApp_u_DtcSendBuf[LeAppdesc_u_SecondChangedDtcIndex][2]);
            RTE_NET_Can_Write_VrhcuDTC2_Status(SeCanApp_u_DtcSendBuf[LeAppdesc_u_SecondChangedDtcIndex][3]);
            
            // 标记第二个DTC为已发送
            SeCanApp_u_DtcNeedSend[LeAppdesc_u_SecondChangedDtcIndex] = FALSE;
        }
        else
        {
            // 填充DTC2为0
            RTE_NET_Can_Write_VrhcuDTC2_HighByte(0);
            RTE_NET_Can_Write_VrhcuDTC2_MiddByte(0);
            RTE_NET_Can_Write_VrhcuDTC2_LowByte(0);
            RTE_NET_Can_Write_VrhcuDTC2_Status(0);
        }
        
        // 标记第一个DTC为已发送
        SeCanApp_u_DtcNeedSend[LeAppdesc_u_ChangedDtcIndex] = FALSE;
        
        // 重置发送延迟
        SeCanApp_w_DtcDelaySend = 500/10; // 假设10ms为一个周期
        return; // 立即返回，不执行后续的周期性发送
    }
    
    // 处理周期性发送
    if(SeCanApp_w_DtcDelaySend > 0)
    {
        SeCanApp_w_DtcDelaySend--;
    }
    else
    {
        // 无DTC状态变化，发送全0
        RTE_NET_Can_Write_VrhcuDTC1_HighByte(0);
        RTE_NET_Can_Write_VrhcuDTC1_MiddByte(0);
        RTE_NET_Can_Write_VrhcuDTC1_LowByte(0);
        RTE_NET_Can_Write_VrhcuDTC1_Status(0);
        RTE_NET_Can_Write_VrhcuDTC2_HighByte(0);
        RTE_NET_Can_Write_VrhcuDTC2_MiddByte(0);
        RTE_NET_Can_Write_VrhcuDTC2_LowByte(0);
        RTE_NET_Can_Write_VrhcuDTC2_Status(0);
        
        // 重置索引
        LeAppdesc_w_ActiveDtcIndex = 0;
        
        // 设置发送周期为500ms
        SeCanApp_w_DtcDelaySend = 500/10; // 假设10ms为一个周期
    }
}















