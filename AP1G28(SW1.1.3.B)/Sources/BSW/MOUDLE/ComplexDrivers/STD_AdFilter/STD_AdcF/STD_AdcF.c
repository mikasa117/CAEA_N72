/*******************************************************************************
|  File Name:  STD_AdcF.c
|  Description:  Implementation of the Adc Filter Management
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
| 2016-09-30    01.00.00     XYJ       Creation
|
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_AdcF.h"
#include "STD_AdcM.h"
#include "STD_Lib.h"
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
    uint16 e_w_Buff[ADCFCFG_COLLECT_MAX_NUM];    /*cache array*/
    uint16 e_w_ValidValue;                       /*valid value when filtering is completed*/
    uint16 e_w_CurrentValue;                     /*the current value - unfiltered value*/
    uint8 e_u_Index;                             /*the current input index*/
    uint8 e_u_CollectNum;                        /*acquisition size*/
    uint8 e_u_Flag;                              /*completion flag*/
} TsAdcF_h_Struct;
/*******************************************************************************
|    Static local KAM variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/
/* polyspace<MISRA-C3:2.5:Not a defect:Other> No fluence */
#define STD_ADCF_START_SEC_VAR_RAM
/* polyspace<MISRA-C3:20.1:Not a defect:Other> No fluence */
#include "STD_MemMap.h"

static TsAdcF_h_Struct	ADCF_CODE_RAM stAdcF[ADCFCFG_CH_MAX_NUM];
/* polyspace<MISRA-C3:2.5:Not a defect:Other> No fluence */
#define STD_ADCF_STOP_SEC_VAR_RAM
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
Name			: ADCF_InitMemory
Syntax			: void ADCF_InitMemory(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: RAM initialize
Call By			: -
|******************************************************************************/
void ADCF_InitMemory(void)
{
    uint8 ucChannal;
    uint8 ucIndex;

    for(ucChannal = 0u; ucChannal < (uint8)(ADCFCFG_CH_MAX_NUM); ucChannal++)
    {
        stAdcF[ucChannal].e_u_Flag = CAEA_FALSE;

        if(stAdcM_CfgTable[ucChannal].e_u_StartOffset >= (uint8)ADCFCFG_COLLECT_MAX_NUM)
        {
            stAdcF[ucChannal].e_u_Index	=  0u;
        }
        else
        {
            stAdcF[ucChannal].e_u_Index	= stAdcM_CfgTable[ucChannal].e_u_StartOffset;
        }

        if(stAdcM_CfgTable[ucChannal].e_u_CollectNum >= (uint8)ADCFCFG_COLLECT_MAX_NUM)
        {
            stAdcF[ucChannal].e_u_CollectNum = ADCFCFG_COLLECT_MAX_NUM;
        }
        else
        {
            stAdcF[ucChannal].e_u_CollectNum = stAdcM_CfgTable[ucChannal].e_u_CollectNum;
        }

        for(ucIndex = 0u; ucIndex < (stAdcF[ucChannal].e_u_CollectNum); ucIndex++)
        {
            stAdcF[ucChannal].e_w_Buff[ucIndex] = ADCFCFG_AD_INIT_VALUE;
        }
    }
}

/*******************************************************************************
Name			: ADCF_GetCurrentValue
Syntax			: uint16 ADCF_GetCurrentValue(uint8 ucChannel)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: ucChannel
Parameters(in)	: None
Parameters(out) : None
Return value	: stAdcF[channel].usCurrentValue
Description		: Gets the current value
Call By			: -
|******************************************************************************/
uint16 ADCF_GetCurrentValue(uint8 ucChannel)
{
    uint16 usReVal = ADCFCFG_AD_INIT_VALUE;

    if(ucChannel < (uint8)ADCFCFG_CH_MAX_NUM)
    {
        usReVal = stAdcF[ucChannel].e_w_CurrentValue;
    }
    else
    {
    }

    return usReVal;
}

/*******************************************************************************
Name			: ADCF_GetValidValue
Syntax			: uint16 ADCF_GetValidValue(uint8 ucChannel)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: ucChannel
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: Gets the valid value
Call By			: -
|******************************************************************************/
uint16 ADCF_GetValidValue(uint8 ucChannel)
{
    uint16 usReVal = ADCFCFG_AD_INIT_VALUE;

    if(ucChannel < (uint8)ADCFCFG_CH_MAX_NUM)
    {
        usReVal = stAdcF[ucChannel].e_w_ValidValue;
    }
    else
    {
    }

    return usReVal;
}

#if (ADCFCFG_CLASS_BUDDLE_MIDDLE == ADCFCFG_ENABLE)
/*******************************************************************************
Name			: ADCF_BubbleSortMiddleConversion
Syntax			: void ADCF_BubbleSortMiddleConversion(uint8 ucChannel,uint16 usInsertValue)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: channel
Parameters(in)	: usInsertValue
Parameters(out) : None
Return value	: None
Description		: Using the bubble sort method, with a median effective value
Call By			: -
|******************************************************************************/
void ADCF_BubbleSortMiddleConversion(uint8 ucChannel, uint16 usInsertValue)
{
    uint8                   ucMirrorindex;
    uint8                   ucMiddleIndex;
    uint8                   ucCollectActualNum;
    TsAdcF_h_Struct * const pAdcF = &stAdcF[ucChannel];
    pAdcF->e_w_CurrentValue	= usInsertValue;
    pAdcF->e_w_Buff[pAdcF->e_u_Index] = usInsertValue;

    if(pAdcF->e_u_Index >= (pAdcF->e_u_CollectNum - (uint8)1u))
    {
        if((uint16)ADCFCFG_AD_INIT_VALUE != pAdcF->e_w_Buff[0u])
        {
            LIB_BubbleSort(pAdcF->e_w_Buff, pAdcF->e_u_CollectNum);
            ucCollectActualNum = pAdcF->e_u_CollectNum & (uint8)0x01u;

            if ( (uint8)0u != ucCollectActualNum )                                       /*odd number: take the median*/
            {
                ucMiddleIndex = (pAdcF->e_u_CollectNum >> 1u);
                pAdcF->e_w_ValidValue = pAdcF->e_w_Buff[ucMiddleIndex];
            }
            else                                                                  /*even number: take the average*/
            {
                ucMiddleIndex = ( pAdcF->e_u_CollectNum >> 1u );
                ucMirrorindex = (pAdcF->e_u_CollectNum >> 1u) - (uint8)1u;
                pAdcF->e_w_ValidValue = ( pAdcF->e_w_Buff[ucMiddleIndex] + pAdcF->e_w_Buff[ucMirrorindex] ) / (uint8)2u;
            }

            pAdcF->e_u_Flag = CAEA_TRUE;
        }

        pAdcF->e_u_Index = 0u;
    }
    else
    {
        pAdcF->e_u_Index++;
    }

    if((uint8)CAEA_TRUE != pAdcF->e_u_Flag)
    {
        pAdcF->e_w_ValidValue = usInsertValue;
    }
}
#endif

#if (ADCFCFG_CLASS_BUDDLE_AVERAGE == ADCFCFG_ENABLE)
/*******************************************************************************
Name			: ADCF_BubbleSortAverageConversion
Syntax			: void ADCF_BubbleSortAverageConversion(uint8 ucChannel,uint16 usInsertValue)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: ucChannel
Parameters(in)	: usInsertValue
Parameters(out) : None
Return value	: None
Description		: Using the bubble sort method, then calculate the average value of effective value
Call By			: -
|******************************************************************************/
void ADCF_BubbleSortAverageConversion(uint8 ucChannel, uint16 usInsertValue)
{
    TsAdcF_h_Struct * const pAdcF = &stAdcF[ucChannel];
    pAdcF->e_w_CurrentValue	= usInsertValue;
    pAdcF->e_w_Buff[pAdcF->e_u_Index] = usInsertValue;

    if(pAdcF->e_u_Index >= (pAdcF->e_u_CollectNum - (uint8)1u))
    {
        if((uint16)ADCFCFG_AD_INIT_VALUE != pAdcF->e_w_Buff[0u])
        {
            LIB_BubbleSort(pAdcF->e_w_Buff, pAdcF->e_u_CollectNum);
            pAdcF->e_w_ValidValue =  LIB_CalculateAverage(&(pAdcF->e_w_Buff[1u]), (pAdcF->e_u_CollectNum - (uint8)2u));
            pAdcF->e_u_Flag = CAEA_TRUE;
        }

        pAdcF->e_u_Index = 0u;
    }
    else
    {
        pAdcF->e_u_Index++;
    }

    if((uint8)CAEA_TRUE != pAdcF->e_u_Flag)
    {
        pAdcF->e_w_ValidValue = usInsertValue;
    }
}
#endif

#if ( ADCFCFG_CLASS_SIMPLE_AVERAGE == ADCFCFG_ENABLE)
/*******************************************************************************
Name			: ADCF_SimpleAverageConversion
Syntax			: void ADCF_SimpleAverageConversion(uint8 ucChannel, uint16 usInsertValue)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: ucChannel
Parameters(in)	: usInsertValue
Parameters(out) : None
Return value	: None
Description		: Using the bubble sort method, then calculate the average value of effective value
Call By			: -
|******************************************************************************/
void ADCF_SimpleAverageConversion(uint8 ucChannel, uint16 usInsertValue)
{
    TsAdcF_h_Struct * const pAdcF = &stAdcF[ucChannel];
    pAdcF->e_w_CurrentValue	= usInsertValue;
    pAdcF->e_w_Buff[pAdcF->e_u_Index] = usInsertValue;

    if(pAdcF->e_u_Index >= (pAdcF->e_u_CollectNum - (uint8)1u))
    {
        if((uint16)ADCFCFG_AD_INIT_VALUE != pAdcF->e_w_Buff[0u])
        {
            pAdcF->e_w_ValidValue =  LIB_CalculateAverage(&(pAdcF->e_w_Buff[0u]), (pAdcF->e_u_CollectNum));
            pAdcF->e_u_Flag = CAEA_TRUE;
        }

        pAdcF->e_u_Index = 0u;
    }
    else
    {
        pAdcF->e_u_Index++;
    }

    if((uint8)CAEA_TRUE != pAdcF->e_u_Flag)
    {
        pAdcF->e_w_ValidValue = usInsertValue;
    }
}
#endif

#if ( ADCFCFG_CLASS_FAST_AVERAGE == ADCFCFG_ENABLE)
/*******************************************************************************
Name			: ADCF_FastAverageConversion
Syntax			: void ADCF_FastAverageConversion(uint8 ucChannel,uint16 usInsertValue)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: ucChannel
Parameters(in)	: usInsertValue
Parameters(out) : None
Return value	: None
Description		: Using the bubble sort method, then calculate the average value of effective value
Call By			: -
|******************************************************************************/
void ADCF_FastAverageConversion(uint8 ucChannel, uint16 usInsertValue)
{
    TsAdcF_h_Struct * const pAdcF = &stAdcF[ucChannel];
    pAdcF->e_w_CurrentValue	= usInsertValue;
    pAdcF->e_w_Buff[pAdcF->e_u_Index] = usInsertValue;

    if(pAdcF->e_u_Index >= (pAdcF->e_u_CollectNum - (uint8)1u))
    {
        pAdcF->e_u_Index = 0u;
        pAdcF->e_u_Flag = CAEA_TRUE;
    }
    else
    {
        pAdcF->e_u_Index++;
    }

    if((uint8)CAEA_TRUE == pAdcF->e_u_Flag)
    {
        pAdcF->e_w_ValidValue =  LIB_CalculateAverage(&(pAdcF->e_w_Buff[0u]), (pAdcF->e_u_CollectNum));
    }
    else
    {
        pAdcF->e_w_ValidValue =  LIB_CalculateAverage(&(pAdcF->e_w_Buff[0u]), (pAdcF->e_u_Index));
    }
}
#endif


/*EOF*/