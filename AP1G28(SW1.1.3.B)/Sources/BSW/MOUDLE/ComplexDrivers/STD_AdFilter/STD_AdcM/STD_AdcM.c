/*******************************************************************************
|  File Name:  AdcM.c
|  Description:  Implementation of the Adc Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           YaJun Xia              CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2017-01-05    01.00.00     XYJ       Creation
|
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_AdcM.h"
#include "STD_AdcF.h"

#include "STD_Lib.h"
#include <STD_AdcIf.h>
/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef	struct
{
    uint16 e_w_Data[ADCMCFG_CH_MAX_NUM];
    uint8 e_u_Flag[ADCMCFG_CH_MAX_NUM];

} TsAdcM_h_Struct;
/*******************************************************************************
|    Static local KAM variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/
/* polyspace<MISRA-C3:2.5:Not a defect:Other> No fluence */
#define STD_ADCM_START_SEC_VAR_RAM
/* polyspace<MISRA-C3:20.1:Not a defect:Other> No fluence */
#include "STD_MemMap.h"

static TsAdcM_h_Struct ADCM_CODE_RAM stAdcM;
/* polyspace<MISRA-C3:2.5:Not a defect:Other> No fluence */
#define STD_ADCM_STOP_SEC_VAR_RAM
/* polyspace<MISRA-C3:20.1:Not a defect:Other> No fluence */
#include "STD_MemMap.h"
/*******************************************************************************
|    Table Const Definition
|******************************************************************************/

/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/


/*******************************************************************************
Name			: ADCM_InitMemory
Syntax			: void ADCM_InitMemory( void )
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Initialize Ram Data
Call By			: EcuM
|******************************************************************************/
void ADCM_InitMemory( void )
{
    LIB_SetMemory( (uint8 *)(&stAdcM), 0u, (uint16)(sizeof(stAdcM) / sizeof(uint8)) );/*PRQA S 0310*/
    ADCF_InitMemory();
#if (ADCMCFG_CALLBACK_EN == 1u)
	ADCB_InitMemory();
#endif

}

/*******************************************************************************
Name			: ADCM_CallbackSampleValue
Syntax			: void ADCM_CallbackSampleValue( uint8 ucChannal, uint16 usSampleValue )
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: ucChannal				: usSampleValue
Parameters(out) : None
Return value	: None
Description		: -
Call By			: -
|******************************************************************************/
void ADCM_CallbackSampleValue( uint8 ucChannal, uint16 usSampleValue )
{
    if(ucChannal < (uint8)ADCMCFG_CH_MAX_NUM)
    {
        stAdcM.e_w_Data[ucChannal] = usSampleValue;
        stAdcM.e_u_Flag[ucChannal] = TRUE;
    }
}

/*******************************************************************************
Name			: ADCM_GetSensorValidValue
Syntax			: uint16 ADCM_GetSensorValidValue( uint8 ucChannal )
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: ucchannal
Parameters(out) : None
Return value	: None
Description		: -
Call By			: -
|******************************************************************************/
uint16 ADCM_GetValidValue( uint8 ucChannal )
{
    return ADCF_GetValidValue(ucChannal);
}

/*******************************************************************************
Name			: ADCM_GetCurrentValue
Syntax			: uint16 ADCM_GetCurrentValue(  uint8 ucChannal )
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: ucchannal
Parameters(out) : None
Return value	: None
Description		: Gets the Battery current value
Call By			: -
|******************************************************************************/
uint16 ADCM_GetCurrentValue( uint8 ucChannal )
{
    return ADCF_GetCurrentValue(ucChannal);
}

/*******************************************************************************
Name			: ADCM_MainFunction
Syntax			: void ADCM_MainFunction(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: -
Call By			: -
|******************************************************************************/
void ADCM_MainFunction( void )
{
    uint8 TempChannal;

    for(TempChannal = 0u; TempChannal < (uint8)(ADCMCFG_CH_MAX_NUM); TempChannal++)
    {
        if(TRUE == stAdcM.e_u_Flag[TempChannal])
        {
            stAdcM_CfgTable[TempChannal].e_p_FunFilterProcess(TempChannal, stAdcM.e_w_Data[TempChannal]);
            stAdcM.e_u_Flag[TempChannal] = FALSE;
        }
        else
        {
        }
    }
}

/*******************************************************************************
Name			: ADCM_ADC0_StartFunction
Syntax			: void ADCM_ADC0_StartFunction(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: -
Call By			: -
|******************************************************************************/
void ADCM_ADC0_StartFunction( void )
{
    AdcIf_0_Start();
}


/*EOF*/
