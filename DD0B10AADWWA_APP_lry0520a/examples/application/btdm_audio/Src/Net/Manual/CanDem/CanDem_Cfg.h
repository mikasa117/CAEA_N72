#ifndef CAN_DEM_CFG_H
#define CAN_DEM_CFG_H

#include "CanDem.h"

#define CanDem_u_SysEnCondNumber                        0x06U
#define CanDem_u_DtcNumber                              0x04U   /* 4 DTC */
#define CanDem_u_DisRepNumber                           0x00U   /* 1 DTC */
#define CanDem_u_Zero                                   0x00U

#define CanDEM_u_EventPassed                            0x00U
#define CanDEM_u_EventFailed                            0x01U

#define CanDem_u_UDSStatus_TF                           0x01U
#define CanDem_u_SetUDSStatus_TF(Status)                ((Status) |= (uint8)CanDem_u_UDSStatus_TF)
#define CanDem_u_ResetUDSStatus_TF(Status)              ((Status) &= ((uint8)~(CanDem_u_UDSStatus_TF)))

#define CanDem_u_UDSStatus_CDTC                         0x08U
#define CanDem_u_SetUDSStatis_CDTC(Status)              ((Status) |= (uint8)CanDem_u_UDSStatus_CDTC)
#define CanDem_u_ResetUDSStatis_CDTC(Status)            ((Status) &= ((uint8)~(CanDem_u_UDSStatus_CDTC)))

#define CanDem_u_StorageNone                            0x00U
#define CanDem_u_StorageSaveDtc                         0x01U
#define CanDem_u_StorageReadDtc                         0x02U
#define CanDem_u_StorageClearDtc                        0x03U

/*  Aging- and OperationCycle IDs [symbolic name value]  */
#define CanDem_u_IgnitionCycle                          0x01U
#define CanDem_u_PowerCycle                             0x02U

#define CanDem_u_TimeBase                               0x14u//0x0AU
#define CanDem_u_EnTimeBase                             20U

#define CanDem_u_DebounceNone                           0x00U
#define CanDem_u_DebounceStart                          0x01U
#define CanDem_u_DebounceCount                          0x02U
#define CanDem_u_DebounceEnd                            0x03U
#define CanDem_u_DebouncePassed                         0x04U
#define CanDem_u_DebounceFailed                         0x05U

#define CanDEM_u_WriteE2promLength                              1U


#define CanDem_u_NotAgingSupport                         0x7FU
#define CanDem_u_AgingMaxValue                           0x7FU

#define Can_Dem_u_ISO15031_6

/* Maximum number of DEM events */
#define CAN_DEM_MAX_EVENTS    32U

/* DEM event IDs */
#define DEM_EVENT_CAN_BUS_OFF         0U
#define DEM_EVENT_CAN_ERROR_PASSIVE   1U
#define DEM_EVENT_CAN_ERROR_WARNING   2U
#define DEM_EVENT_CAN_RX_TIMEOUT      3U

#define AgingCounter         40U

extern const DtcInfo_Type DsDem_h_ManagementUnit[];
extern DTCInfo_Type     SeDem_u_DTCInfo[CanDem_u_DtcNumber];
extern const uint8 CaDEM_u_MoniEnTime[];
extern const DTCHandler_Type SsDEM_h_MoniEnCodHandler[CanDem_u_SysEnCondNumber];
extern const DebounceTimeTable_Type SsDem_e_DebounceTimeTable[];
extern void CanDem_Cfg_InitMemory(void);

#endif /* CAN_DEM_CFG_H */ 
