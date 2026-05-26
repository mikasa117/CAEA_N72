/*******************************************************************************
|  (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      ---------------------  -----------------------------------------
| psp           panshouping            CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 2017-10-14    0.01         psp       DEM operation
|******************************************************************************/
#ifndef CAN_DEM_H
#define CAN_DEM_H


#include "Vector_Platform_Types.h"

/*******************************************************************************
|    Typedef Definition:DEMDtcInfo_Type
|******************************************************************************/



/*DTC Monitor Enable conditions */
#define CanDEM_u_Zero                           0x00U
#define CanDEM_u_Null                           0x00U


#define CanApplDem_u_DTCKind                    0x01U  /*DEFINE*/


#define CanDem_u_Ok                             0x00U
#define CanDem_u_Nok                            0x01U
#define CanDem_u_OtherNokState                  0x02U
#define CanDem_u_False                          0x00U
#define CanDem_u_True                           0x01U

#define CanDem_u_FaultRecover                   0x00U
#define CanDem_u_FaultNoRecover                 0x01U

#define Can_u_StatusAvailabilityMask            0x09U

typedef uint8 ( *DTCHandler_Type )( void );

typedef enum
{
   OpCycle_None =0,
   OpCycle_IGN,
   OpCycle_POWER
}OpCycle_Type;

typedef struct
{
    uint8                           e_u_DebounceCurStatus;
    uint8                           e_u_DebounceHisStatus;
}SysEnCond_Type;

/* structure of DTC infomation used for update DTC message */
typedef struct
{
    uint32                          e_w_DebounceTime;
    uint8                           e_u_DebounceFlag;
    uint8                           e_u_DTCEvent_OldStatus; /*DTC Handle Change Flag*/
    uint8                           e_u_DtcStatus;
    uint8                           e_u_DtcEvent_LastCycle; /*last IGN ON Handle Flag*/
    uint8                           e_u_DtcEvent_ThisCycle; /*This IGN ON Handle Flag*/
}DebounceInfo_Type;

typedef struct
{
    uint8                           e_u_AgingCounter;   /*Aging cycle counter*/
    uint8                           e_u_AgingFlag;      /*allowed aging counter flag*/
}AgingInfo_Type;

typedef struct
{
    DTCHandler_Type                 e_u_DTCHandler;             /*DTC Handler*/
    uint16                          e_w_Num;                    /*DTC number*/
    uint8                           e_u_FailType;               /*DTC failure type*/
    uint32                          e_u_DTC_EepID;              /*DTC failure type*/
    uint8                           e_w_DebounceTimeTableIndex;
    uint16                          e_u_DtcEnCond;           	/*Enable Condition:bit0--IGN;bit1--Battery;bit2---85Enable;bit3__FirstPowerOn;bit4_Busoff*/
    uint8                           e_u_MoniCycle;              /*DTC Cycle Time*/
    OpCycle_Type                    e_u_DtcOperationCycleId;
    uint8                           e_u_AgingUpperLimit;
    uint8                           e_u_DtcSupport;
}DtcInfo_Type;

typedef struct
{
    uint16                              e_w_DtcTimeQuick;/*During Start up*/
    uint16                              e_w_DtcTimePass;
    uint32                              e_w_DtcTimeFail;
}DebounceTimeTable_Type;

typedef struct
{
	uint8   	e_u_ECU_Voltage;                        /*ECU Voltage*/
	uint16  	e_u_Speed;
	uint8       e_u_OccurrenceCnt;
	uint32		e_u_FirstODO;
	uint32		e_u_LastODO;
//	uint16  	e_u_Engine;
//	uint8   	e_u_PowerMode;
	uint8   	e_u_Sec;
	uint8   	e_u_Min;
	uint8   	e_u_Hour;
	uint8   	e_u_Month;
	uint8   	e_u_Day;
	uint8   	e_u_Year;
	uint8		e_u_FirstFlag;
}SnapShotTable_Type;

typedef struct
{
    uint8    ExtendDataRecord_One;
    uint8    ExtendDataRecord_Two;
    uint8    ExtendDataRecord_Three;
}DTCExtendData_Type;

typedef struct
{
    uint8                SeDem_u_DTCStatus;
    SnapShotTable_Type   DTCSnapShotData;
    DTCExtendData_Type   DTCExtendData;
}DTCInfo_Type;


extern void     CanDem_MainFunction10ms(void);
extern void     CanDem_MainFunction20ms(void);
extern void     CanDem_InitMemory(void);
extern uint8    CanDem_DcmEnableDTCSetting(void);
extern uint8    CanDem_DcmGetNumberOfFilteredDTC(uint16* NumberOfFilteredDTC,uint8 DTC_RequestMask);
extern uint8    CanDem_DcmGetNextFilteredDTC(uint32* DTC,uint8* DTCStatus,uint16 DTCNumber);

extern uint16   CanDem_DcmFindEventFromDtcInfo(uint32 Dtc,uint32  MemoryId);
extern uint8    CanDem_DcmGetStatusOfDTC(uint32 DTC,uint32 DTCOrigin,uint8* DTCStatus);
extern uint8    CanDem_DcmGetNumberOfFilteredDTC(uint16* NumberOfFilteredDTC,uint8 DTC_RequestMask);
extern uint8    CanDem_DcmGetDTCStatusAvailabilityMask(uint8* DTCStatusMask);
extern uint8    CanDem_DcmGetNextFilteredDTC(uint32* DTC,uint8* DTCStatus,uint16 DTCNumber);
extern uint8    CanDem_DcmDisableDTCSetting(void);
extern uint8    CanDem_DcmEnableDTCSetting(void);
extern uint8    CanDem_DcmClearDTCSignal(uint32 LeCanDem_dw_DTCNum);

extern void CanDem_DcmGetAllSupportDTC(uint32* DTC,uint8* DTCStatus,uint8 DTCNumber);
extern uint8 CanDem_DcmGet_NetDtc_EnableConditionStatus(void);
extern void CanDem_DcmGetAllSupportDTC(uint32* DTC,uint8* DTCStatus,uint8 DTCNumber);
extern uint8 CanDem_GetDTCSetting(void);
extern void CanDem_SetConditionstatuts_ontooff(void);

extern uint8 AgingCounterTest;
#endif
