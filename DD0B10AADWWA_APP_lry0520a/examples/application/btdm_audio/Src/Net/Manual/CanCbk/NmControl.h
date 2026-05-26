/*******************************************************************************
|  File Name: NmControl.h
|  Description: Header file for NM Control Frame (0x41F) Management
|-------------------------------------------------------------------------------
|  (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      ---------------------  -----------------------------------------
| 	                               CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 2025.08.30     V1.0         Auto     NM Control Frame Header
|******************************************************************************/

#ifndef NMCONTROL_H
#define NMCONTROL_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Vector_Platform_Types.h"

/*******************************************************************************
|    Function Declaration
|******************************************************************************/

/*******************************************************************************
Name      : NmControl_Init
Description : Initialize NM Control module
|******************************************************************************/
extern void NmControl_Init(void);


/*******************************************************************************
Name      : NmControl_OnRepeatMessageReceived
Description : Handle received Repeat Message Request from other ECUs
|******************************************************************************/
extern void NmControl_OnRepeatMessageReceived(void);

/*******************************************************************************
Name      : NmControl_OnNetworkRequest
Description : Handle local network request (wake up conditions)
|******************************************************************************/
extern void NmControl_OnNetworkRequest(void);

/*******************************************************************************
Name      : NmControl_OnRemoteWakeup
Description : Handle remote wake up message
|******************************************************************************/
extern void NmControl_OnRemoteWakeup(void);

/*******************************************************************************
Name      : NmControl_OnReturnToNormal
Description : Handle return to Normal Operation State
|******************************************************************************/
extern void NmControl_OnReturnToNormal(void);

/*******************************************************************************
Name      : NmControl_OnReturnToPrepareBS
Description : Handle return to Prepare Bus Sleep State
|******************************************************************************/
extern void NmControl_OnReturnToPrepareBS(void);

/*******************************************************************************
Name      : NmControl_GetRepeatMessageState
Description : Get current network management state
Return      : boolean - TRUE if in Repeat Message Mode, FALSE otherwise
|******************************************************************************/
extern boolean NmControl_GetRepeatMessageState(void);


#endif /* NMCONTROL_H */
