/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Can_Main.h"
#include "Vector_Platform_Types.h"
#include "Can_Main.h"
#include "CanApp.h"
#include "Rte_Can.h"
#include "Can_Trcv.h"
#include "ccl_inc.h"
#include "ccl_cfg.h"
#include "Random.h"
#include "CanDem.h"
#include "appdesc.h"
#include "can_def.h"
#include "DID_Callback.h"
#include "fdb_def.h"
#include "fdb_app.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/

#define RX_MESSAGE_BUFFER_NUM (9)
#define TX_MESSAGE_BUFFER_NUM (8)
#define EXAMPLE_CAN CAN3
/* Select OSC24Mhz as master flexcan clock source */
#define FLEXCAN_CLOCK_SOURCE_SELECT (1U)
/* Clock divider for master flexcan clock source */
#define FLEXCAN_CLOCK_SOURCE_DIVIDER (1U)

#define EXAMPLE_CAN_CLK_FREQ ((CLOCK_GetRootClockFreq(kCLOCK_Root_Can3) / 100000U) * 100000U)
/*#define CeCanMain_u_canChannel  0u*/


/* polyspace<MISRA-C3:2.5:Not a defect:Justified> the value define of Local KL15 on in CanMain, reserve */
#define CeCanMain_u_LocalKL15On   1u
#define CeCanMain_u_LocalKL15Off  0u

/* polyspace<MISRA-C3:2.5:Not a defect:Justified> the value define of Vbat mode normal in CanMain, reserve */
#define CeCanMain_u_VbatMNormal  (uint8)1u
#define CeCanMain_u_VbatMAbnormal  (uint8)0u
#define CeCanMain_u_True                         (uint8)1U
#define CeCanMain_u_False                        (uint8)0U

#define CeCanMain_w_ComKeepTime		1010u
#define CeCanMain_w_SleepTime		500u
#define CeCanMain_w_StartUpTime		2u
/* polyspace<MISRA-C3:2.5:Not a defect:[STATUS]> the value define of Vbat mode normal in CanMain, reserve */
#define CeCanMain_w_Zero			(uint8)0u
/******************************************************************************/
/*********************************�꿪��  **********************************/
/* polyspace<MISRA-C3:2.5:Not a defect:Justified> Not affect */
#define POWER_ON_OSEK_ACTIVE
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


/* polyspace<MISRA-C3:8.8:Not a defect:Justified> Not affect */

/*static uint8 SeCanMain_u_LocalKL15Cnt;*/
static uint8 	SeCanMain_u_Start5SFlag;
static uint8 	SeCanMain_u_5SCount;
static uint8 	SeCanMain_u_StartRxTimeout;

static uint8 	SeCanMain_u_ResetFlag;
static void CanMain_AllVarInit( void );
static void CanMain_AllModuInit( void );
static void CanMain_IntEnableIRQFunction( void );
/*******************************************************************************
Name			:
Syntax			:
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None						:-
Parameters(out) : None						:-
Return value	: None						:-
Description		: Receive  Notification
Call By			:
history
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
static void CanMain_AllVarInit( void )
{
	CanApp_InitMemory();
	CanDem_InitMemory();
	CanDcm_InitMemory();
}

static void CanMain_AllModuInit( void )
{
    /* Initialize CAN modules */
    CclInitPowerOn();
    CanApp_InitMemory();

    SeCanMain_u_Start5SFlag = 0u;
    SeCanMain_u_5SCount = 250U;
    
}

/*******************************************************************************
Name			:
Syntax			:
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None						:-
Parameters(out) : None						:-
Return value	: None						:-
Description		: Receive  Notification
Call By			:
history
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
void CanMain_InitMemory( uint8 LeCanMain_u_Src )
{
	switch(LeCanMain_u_Src)
	{
		case 0u:
	    {
	        CanMain_AllModuInit();
	    	break;
	    }
	    case 1u:
	    {
	    	CanMain_AllVarInit();
	    	CanMain_IntEnableIRQFunction();
	    	break;
	    }
	    default:
	    {
	        CanMain_AllModuInit();
	        CanMain_IntEnableIRQFunction();
	    	break;
	    }
	}
}
/*******************************************************************************
Name			:
Syntax			:
Sync/Async		:
Reentrancy		:
Parameters(in)	:
Parameters(out) :
Return value	:
Description		:
Call By			:
history
<No.>    <author>    <time>      <description>
  1      kenw        20170930    creation
|******************************************************************************/
void CanMain_5msAMainFunction( void )
{
//	NmMsgReCheck();
}

/*******************************************************************************
Name			:
Syntax			:
Sync/Async		:
Reentrancy		:
Parameters(in)	:
Parameters(out) :
Return value	:
Description		:
Call By			:
history
<No.>    <author>    <time>      <description>
  1      kenw        20170930    creation
|******************************************************************************/
void CanMain_5msBMainFunction( void )
{
     CanTrcv_MainFunction();
	 Ccl_5_0msTaskCont();
	 CanApp_MainFunction();
	 Random_GetSeed1MainFunction();
//    if((CanDem_DcmGet_NetDtc_EnableConditionStatus() == 0u) && (SeCanMain_u_StartRxTimeout == 0U) )
//    {
//        IlRxStop();
//        IlRxStart();
//        SetCanApp_ClearTimeOut();
//    }
//    else
//    {
//    	SeCanMain_u_StartRxTimeout = 1U;
//    }
}

/*******************************************************************************
Name			:
Syntax			:
Sync/Async		:
Reentrancy		:
Parameters(in)	:
Parameters(out) :
Return value	:
Description		:
Call By			:
history
<No.>    <author>    <time>      <description>
 1       kenw        20170930    creation
|******************************************************************************/

void CanMain_10msAMainFunction( void )
{
	Ccl_10_0msTaskCont();
	CanApp_MainFunction_10ms();
	Random_GetSeed2MainFunction();


}


/*******************************************************************************
Name			:
Syntax			:
Sync/Async		:
Reentrancy		:
Parameters(in)	:
Parameters(out) :
Return value	:
Description		:
Call By			:
history
<No.>    <author>    <time>      <description>
  1      kenw        20170930    creation
|******************************************************************************/
void CanMain_10msBMainFunction( void )
{
  CanDem_MainFunction10ms();


	
	
	
}

/*******************************************************************************
Name			:
Syntax			:
Sync/Async		:
Reentrancy		:
Parameters(in)	:
Parameters(out) :
Return value	:
Description		:
Call By			:
history
<No.>    <author>    <time>      <description>
  1	     kenw        20170926    creation
|******************************************************************************/
void CanMain_20msMainFunction(void)
{
	can_Hmi_20ms();
	CanDem_MainFunction20ms();
	//CDiagUart_MainFunction();
    if(SeCanMain_u_Start5SFlag == 0u)
    {
        SeCanMain_u_5SCount --;
        if(SeCanMain_u_5SCount == 0u)
        {
            SeCanMain_u_Start5SFlag = 1u;
			if(SeCanMain_u_ResetFlag == 1)
			{
//				SystemSoftwareReset();            
			}
        }
    }
}



void CanMain_50msMainFunction(void)
{

	
}

/*******************************************************************************
| Function name     :
| Called by         :
| Preconditions     :
| Input Parameters  :
| Return Value      :
| Description       :
| <No.>   <author>    <time>      <description>
|  1       kenw       20171026     primary edition.
|******************************************************************************/
uint8 CanMain_GetDTCENFlag(void)
{
    return SeCanMain_u_Start5SFlag;
    
}

void CanMain_SetNeedReset(void)
{
	SeCanMain_u_ResetFlag = 1;
}

uint8 CanMain_GetNeedReset(void)
{
	return SeCanMain_u_ResetFlag;
}

/*******************************************************************************
Name			:
Syntax			:
Sync/Async		: Synchronous
Reentrancy		:
Parameters(in)	: None						:-
Parameters(out) : None						:-
Return value	: None						:-
Description		: Receive  Notification
Call By			:
history
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
static void CanMain_IntEnableIRQFunction( void )
{
//	CanBusOffIsr_0();
}

