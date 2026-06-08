/*******************************************************************************
||  File Name: RTE_DEM.h
||  Description: Header file for AUTOSAR DEM Interface
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

#ifndef RTE_DEM_H
#define RTE_DEM_H
#include "CAEA_Types.h"
#include "CanDem.h"
/*******************************************************************************
||    Other Header File Inclusion
||******************************************************************************/ 

/*******************************************************************************
||    Macro Definition
||******************************************************************************/
#define CAN_DEM_BATTERYL_ON      1386U   /* 9V */
#define CAN_DEM_BATTERYL_OFF     1308U   /* 8.5V */
#define CAN_DEM_BATTERYH_ON      2547U   /* 16.5V */
#define CAN_DEM_BATTERYH_OFF     2469U   /* 16V */
#define CanDem_MODE_A         1u
#define CanDem_MODE_B         0u
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
||    Extern variables and functions declaration
||******************************************************************************/

/********************************** DEM Initialization **********************************/
extern void RTE_NET_Dem_Init(void);

/********************************** DTC Callback Functions **********************************/
extern uint8 RTE_NET_Dem_Callback_DTC_E6B8_87(void);
extern uint8 RTE_NET_Dem_Callback_DTC_E6BB_88(void);
extern uint8 RTE_NET_Dem_Callback_DTC_97F8_16(void);
extern uint8 RTE_NET_Dem_Callback_DTC_97F8_17(void);
extern uint8 RTE_NET_Dem_Callback_DTC_97F8_06(void);
extern uint8 RTE_NET_Dem_Callback_DTC_97FB_18(void);
extern uint8 RTE_NET_Dem_Callback_DTC_97FB_19(void);
extern uint8 RTE_NET_Dem_Callback_DTC_97F8_4B(void);
extern uint8 RTE_NET_Dem_Callback_DTC_97FC_19(void);
extern uint8 RTE_NET_Dem_Callback_DTC_97FC_18(void);
extern uint8 RTE_NET_Dem_Callback_DTC_97FD_19(void);
extern uint8 RTE_NET_Dem_Callback_DTC_97FD_18(void);
extern uint8 RTE_NET_Dem_Callback_DTC_97F8_09(void);
extern uint8 RTE_NET_Dem_Callback_DTC_97F9_09(void);
extern uint8 RTE_NET_Dem_Callback_DTC_97F8_71(void);
extern uint8 RTE_NET_Dem_Callback_DTC_97F8_49(void);
extern uint8 RTE_NET_Dem_Callback_DTC_97F9_49(void);
extern uint8 RTE_NET_Dem_Callback_DTC_97FA_49(void);
extern uint8 RTE_NET_Dem_Callback_DTC_97FA_09(void);

/********************************** DEM Main Functions **********************************/
extern void RTE_NET_Dem_10msMainFunction(void);
extern void RTE_NET_Dem_20msMainFunction(void);

extern uint8 RTE_NET_Dem_GetIgnStatus(void);
extern uint8 RTE_NET_Dem_GetBatteryMode(void);
extern uint8 RTE_NET_Dem_GetDTC_85EN(void);
extern uint8 RTE_NET_Dem_GetNFirstPowerOn(void);
extern uint8 RTE_NET_Dem_GetBusOffSta(void);
#endif /* RTE_DEM_H */
