/*******************************************************************************
|  File Name: NmControl.c
|  Description: Implementation of NM Control Frame (0x41F) Management
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
| 2025.08.30     V1.0         Auto     NM Control Frame Implementation
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "NmControl.h"
#include "can_par.h"
#include "Vector_Platform_Types.h"
#include <stdio.h>

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
/* NM Control Frame Data Format */
#define NM_ECU_ADDRESS                  0x1F    /* DMM ECU Address */

/* Control Bit Vector Definitions */
#define NM_RMR_BIT_MASK                 0x01    /* Repeat Message Request bit 0 */
#define NM_AWB_BIT_MASK                 0x10    /* Active Wakeup Bit bit 4 */

#define NM_STATUS_BIT_MASK              0x01    /* NM Status bit 0 in User data 1 */
/*******************************************************************************
|    Global variables Declaration
|******************************************************************************/
boolean nm_RepeatMessageRequest = FALSE;
boolean nm_ActiveWakeupBit = FALSE;
static boolean nm_NetworkManagementState = FALSE;  /* FALSE: Normal, TRUE: Repeat Message Mode */

/*******************************************************************************
|    Function Implementation
|******************************************************************************/

/*******************************************************************************
Name      : NmControl_Init
Syntax      : void NmControl_Init(void)
Sync/Async    : Synchronous
Reentrancy    : Non Reentrant
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    : Initialize NM Control module
Call By      : System initialization
|******************************************************************************/
void NmControl_Init(void)
{
    nm_RepeatMessageRequest = FALSE;
    nm_ActiveWakeupBit = FALSE;
    nm_NetworkManagementState = FALSE;
    
    

}


/*******************************************************************************
Name      : NmControl_OnRepeatMessageReceived
Syntax      : void NmControl_OnRepeatMessageReceived(void)
Sync/Async    : Synchronous
Reentrancy    : Non Reentrant
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    : Handle received Repeat Message Request from other ECUs
Call By      : CAN reception callback
|******************************************************************************/
void NmControl_OnRepeatMessageReceived(void)
{
    /* When receiving Repeat Message Request (Condition 7), 
       the receiving ECU's Repeat Message Request Bit shall be kept zero */
    if(nm_RepeatMessageRequest == FALSE)
    {
        nm_NetworkManagementState = TRUE;  /* Enter Repeat Message Mode */

    }
}

/*******************************************************************************
Name      : NmControl_OnNetworkRequest
Syntax      : void NmControl_OnNetworkRequest(void)
Sync/Async    : Synchronous
Reentrancy    : Non Reentrant
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    : Handle local network request (wake up conditions)
Call By      : Application layer
|******************************************************************************/
void NmControl_OnNetworkRequest(void)
{
    /* When entering Repeat Message State from Bus Sleep State or Prepare Bus Sleep State
       because of Network Request (local wake up conditions), 
       the NM module should set Active Wakeup Bit to value of one */

    nm_NetworkManagementState = TRUE;
    

}

/*******************************************************************************
Name      : NmControl_OnRemoteWakeup
Syntax      : void NmControl_OnRemoteWakeup(void)
Sync/Async    : Synchronous
Reentrancy    : Non Reentrant
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    : Handle remote wake up message
Call By      : CAN reception callback
|******************************************************************************/
void NmControl_OnRemoteWakeup(void)
{
    /* When entering the Repeat Message State because of remote wake up message,
       the NM module should set Active Wakeup Bit to value of zero */

    nm_NetworkManagementState = TRUE;
    

}

/*******************************************************************************
Name      : NmControl_OnReturnToNormal
Syntax      : void NmControl_OnReturnToNormal(void)
Sync/Async    : Synchronous
Reentrancy    : Non Reentrant
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    : Handle return to Normal Operation State
Call By      : NM state machine
|******************************************************************************/
void NmControl_OnReturnToNormal(void)
{
    /* When re-entering Normal Operation State and Ready Sleep State,
       clear the Repeat Message Request Bit */

    nm_NetworkManagementState = FALSE;
    

}

/*******************************************************************************
Name      : NmControl_OnReturnToPrepareBS
Syntax      : void NmControl_OnReturnToPrepareBS(void)
Sync/Async    : Synchronous
Reentrancy    : Non Reentrant
Parameters(in)  : None
Parameters(out) : None
Return value  : None
Description    : Handle return to Prepare Bus Sleep State
Call By      : NM state machine
|******************************************************************************/
void NmControl_OnReturnToPrepareBS(void)
{
    /* When re-entering the Prepare Bus Sleep State,
       clear the Active Wakeup Bit */

    

}

/*******************************************************************************
Name      : NmControl_GetRepeatMessageState
Syntax      : boolean NmControl_GetRepeatMessageState(void)
Sync/Async    : Synchronous
Reentrancy    : Reentrant
Parameters(in)  : None
Parameters(out) : None
Return value  : boolean - TRUE if in Repeat Message Mode, FALSE otherwise
Description    : Get current network management state
Call By      : Application layer
|******************************************************************************/
boolean NmControl_GetRepeatMessageState(void)
{
    return nm_NetworkManagementState;
}


