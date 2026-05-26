/*******************************************************************************
|  File Name:  STD_Lib.c
|  Description:  Implementation of the Lib Management
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
| 2016-09-30    01.00.01     XYJ       Creation
| 2024-05-10    01.01.01     Sean      Add IIR filtering function
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_Lib.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define LIB_MAXVALUE_32         ((uint32)0xFFFFFFFFu)
#define LIB_MAXVALUE_16         ((uint16)0xFFFFu)
#define LIB_MAXVALUE_08         ((uint8)0xFFu)
#define LIB_IIR_K_VAL           (256U)
#define LIB_IIR_FIXPOINT_NUM    (7U)
/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Static local KAM variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Table Const Definition
|******************************************************************************/

/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/

#define STD_LIB_START_SEC_CODE

/*******************************************************************************
Name            : LIB_SetMemory
Syntax          : void LIB_SetMemory(uint8 *pStr, uint8 val, uint16 len)
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : pDes                  :destination data pointer
Parameters(in)  : val                   :set value
Parameters(in)  : len                   :data length
Parameters(out) : None                  :-
Return value    : None
Description     : set value to pStr
Call By         : -
|******************************************************************************/
#if(STD_LIB_ENABLE == STD_LIBCFG_SETMEMORY)
void LIB_SetMemory(uint8 *pStr, uint8 val, uint16 len)
{
    /*LIB_ENTER_EXCLUSIVE_AREA_0();*/

    if( (len > (uint16)0u) && (len < LIB_MAXVALUE_16) )
    {
        while( len != (uint16)0u )
        {
            *pStr = val;
            pStr ++;                    /* polyspace MISRA-C3:17.8 [Justified:Low] "This parameter is not a pointer and has no effect" */
            len --;                 /* polyspace MISRA-C3:17.8 [Justified:Low] "This parameter is not a pointer and has no effect" */
        }
    }

    /*LIB_EXIT_EXCLUSIVE_AREA_0();*/
}
#endif

/*******************************************************************************
Name            : LIB_Compare
Syntax          : uint8 LIB_Compare(uint8 *pSrc, uint8 *pDes, uint16 len)
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : pDes                  :destination data pointer
Parameters(in)  : pSrc                  :source data pointer
Parameters(in)  : len                   :data length
Parameters(out) : None                  :-
Return value    : None
Description     : Compare data from pDes to pSrc
Call By         : -
|******************************************************************************/
#if (STD_LIB_ENABLE == STD_LIBCFG_COMPARE)
uint8 LIB_Compare(uint8 *pSrc, uint8 *pDes, uint16 len)     /* polyspace MISRA-C3:8.13 [Justified:Low] "This is a computational function interface that needs to be considered for universality" */
{
    uint8 e_u_result = TRUE;
    uint16 e_w_len;

    if( ( len > (uint16)0u ) && ( len < LIB_MAXVALUE_16 ) )
    {
        for( e_w_len = (uint16)0u; e_w_len < len; e_w_len++ )
        {
            if( pSrc[e_w_len] != pDes[e_w_len] )
            {
                e_u_result = FALSE;
                break;
            }
        }
    }

    return (e_u_result);
}
#endif

/*******************************************************************************
Name            : LIB_CompareR
Syntax          : uint8 LIB_CompareR(uint8 *pSrc, uint8 *pDes, uint16 len)
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : pDes                  :destination data pointer
Parameters(in)  : pSrc                  :source data pointer
Parameters(in)  : len                   :data length
Parameters(out) : None                  :-
Return value    : None
Description     : Compare reverse data from pDes to pSrc
Call By         : -
|******************************************************************************/
#if (STD_LIB_ENABLE == STD_LIBCFG_COMPARER)
uint8 LIB_CompareR(uint8 *pSrc, uint8 *pDes, uint16 len)        /* polyspace MISRA-C3:8.13 [Justified:Low] "This is a computational function interface that needs to be considered for universality" */
{
    uint8 e_u_result = TRUE;
    uint16 e_w_len;
    uint8  e_u_Rvalue = (uint8)0u;

    if( ( len > (uint16)0u ) && ( len < LIB_MAXVALUE_16 ) )
    {
        for( e_w_len = (uint16)0u; e_w_len < len; e_w_len++ )
        {
            e_u_Rvalue = (uint8)( ~pDes[e_w_len] );

            if( pSrc[e_w_len] != e_u_Rvalue )
            {
                e_u_result = FALSE;
                break;
            }
        }
    }

    return e_u_result;
}
#endif

/*******************************************************************************
Name            : LIB_Copy
Syntax          : void LIB_Copy(uint8 *pDes, uint8 *pSrc, uint16 len)
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : pDes                  :destination data pointer
Parameters(in)  : pSrc                  :source data pointer
Parameters(in)  : len                   :data length
Parameters(out) : None                      :-
Return value    : None
Description     : Copy data from pSrc to pDes
Call By         : -
|******************************************************************************/
#if (STD_LIB_ENABLE == STD_LIBCFG_COPY)
void LIB_Copy(uint8 *pDes, const uint8 *pSrc, uint16 len)     /* polyspace MISRA-C3:8.13 [Justified:Low] "This is a computational function interface that needs to be considered for universality" */
{
    uint16 e_w_len;
/*  LIB_ENTER_EXCLUSIVE_AREA_0();  */

    if( ( len > (uint16)0u ) && ( len < LIB_MAXVALUE_16 ) )
    {
        for( e_w_len = (uint16)0u; e_w_len < len; e_w_len++ )
        {
            pDes[e_w_len] = pSrc[e_w_len];
        }
    }

/*  LIB_EXIT_EXCLUSIVE_AREA_0();  */
}
#endif

/*******************************************************************************
Name            : LIB_CopyR
Syntax          : void LIB_CopyR(uint8 * pDes, uint8 * pSrc, uint16 len)
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : pDes                  :destination data pointer
Parameters(in)  : pSrc                  :source data pointer
Parameters(in)  : len                   :data length
Parameters(out) : None                      :-
Return value    : None
Description     : Copy reverse data from pSrc to pDes
Call By         : -
|******************************************************************************/
#if (STD_LIB_ENABLE == STD_LIBCFG_COPYR)
void LIB_CopyR(uint8 *pDes, uint8 *pSrc, uint16 len)        /* polyspace MISRA-C3:8.13 [Justified:Low] "This is a computational function interface that needs to be considered for universality" */
{
    uint16 e_w_Len;
/*  LIB_ENTER_EXCLUSIVE_AREA_0();*/

    if( ( len > (uint16)0u ) && ( len < LIB_MAXVALUE_16 ) )
    {
        for( e_w_Len = (uint16)0u; e_w_Len < len; e_w_Len++ )
        {
            pDes[e_w_Len] = (uint8)( ~pSrc[e_w_Len] );
        }
    }

/*  LIB_EXIT_EXCLUSIVE_AREA_0(); */
}
#endif

/*******************************************************************************
Name            : LIB_BubbleSort
Syntax          : void LIB_BubbleSort(uint16 *pData, uint8 length)
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : pData                 :data pointer
Parameters(in)  : length                :data length
Parameters(out) : None                  :-
Return value    : None
Description     : Use bubble sort method
Call By         : -
|******************************************************************************/
#if (STD_LIB_ENABLE == STD_LIBCFG_BUBBLESORT)
void LIB_BubbleSort(uint16 *pData, uint8 length)
{
    uint8  i;
    uint8  j;
    uint16 e_w_temp;
    uint8  e_u_length = (uint8)0u;

    if( ( length > (uint16)0u ) && ( length < LIB_MAXVALUE_08 ) )
    {
        for ( j = (uint8)0u; j < ( length - (uint8)1u ); j++ )
        {
            e_u_length = length - j - (uint8)1u;

            for ( i = (uint8)0u; i < e_u_length; i++ )
            {
                if ( pData[i + (uint8)1u] < pData[i] )
                {
                    e_w_temp = pData[i];
                    pData[i] = pData[i + (uint8)1u];
                    pData[i + (uint8)1u] = e_w_temp;
                }
            }
        }
    }
}
#endif

/*******************************************************************************
Name            : LIB_CalculateAverage
Syntax          : uint16 LIB_CalculateAverage(const uint16 *pData, uint8 length)
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : pData                 :data pointer
Parameters(in)  : length                :data length
Parameters(out) : None                  :-
Return value    : None
Description     : Use bubble sort method
Call By         : -
|******************************************************************************/
#if (STD_LIB_ENABLE == STD_LIBCFG_CALCULATEAVERAGE)
uint16 LIB_CalculateAverage(const uint16 *pData, uint8 length)
{
    uint8 i;
    uint32 e_dw_sum = (uint32)0u;
    uint16 e_w_average = (uint16)0u;

    if( ( length > (uint8)0u ) && ( length < LIB_MAXVALUE_08 ) )
    {
        for( i = (uint8)0u; i < length; i++ )
        {
            e_dw_sum += pData[i];
        }

        e_w_average = (uint16)( e_dw_sum / length );
    }
    else
    {
    }

    return (e_w_average);
}
#endif

/*******************************************************************************
Name            : LIB_ReadData
Syntax          : void LIB_ReadData(uint8 * pDes, uint32 pSrcAdd, uint32 len)
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : pDes                  :destination data pointer
Parameters(in)  : pSrcAdd               :source data address
Parameters(in)  : len                   :data length
Parameters(out) : None                      :-
Return value    : None
Description     : Copy data from pSrcAdd to pDes
Call By         : -
|******************************************************************************/
#if (STD_LIB_ENABLE == STD_LIBCFG_READDATA)
void LIB_ReadData( uint8 *pDes, uint32 pSrcAdd, uint32 len )
{
    uint32 e_dw_Len;
    uint8 *pSrc = ( uint8 *)pSrcAdd;            /* polyspace MISRA-C3:11.4 [Justified:High] "risk controllable" */
/*  LIB_ENTER_EXCLUSIVE_AREA_0() */

    if( ( len > (uint32)0u ) && ( len < LIB_MAXVALUE_32 ) )
    {
        for( e_dw_Len = (uint32)0u; e_dw_Len < len; e_dw_Len++ )
        {
            pDes[e_dw_Len] = pSrc[e_dw_Len];
        }
    }

/*  LIB_EXIT_EXCLUSIVE_AREA_0(); */
}
#endif

/*******************************************************************************
Name            : LIB_StatusFilter
Syntax          : uint16 LIB_StatusFilter(LibFilterStruct *pFilterStatus, uint16 filterMaxCnt)
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : *pFilterStatus            :data pointer
Parameters(in)  : filterMaxCnt              :filter count
Parameters(out) : None                      :-
Return value    : None
Description     : data Filter
Call By         : -
|******************************************************************************/
#if (STD_LIB_ENABLE == STD_LIBCFG_STATUSFILTER)
uint8 LIB_StatusFilter( LibFilterStruct *pFilterStatus, uint16 filterMaxCnt )
{
    uint8 e_u_reValue = FALSE;
    uint16 e_w_filterMaxCnt = (uint16)0u;

    if(( filterMaxCnt > (uint16)0u ) && ( filterMaxCnt < LIB_MAXVALUE_16 ))
    {
        e_w_filterMaxCnt = filterMaxCnt;
    }
    else
    {
        e_w_filterMaxCnt = LIB_MAXVALUE_16;
    }

    if( pFilterStatus->ucStatus != pFilterStatus->ucLastStatus )
    {
        pFilterStatus->ucLastStatus = pFilterStatus->ucStatus;
        pFilterStatus->usFilterCount = (uint16)0u;
    }

    if( pFilterStatus->ucStatus != pFilterStatus->ucValidStatus )
    {
        if( pFilterStatus->usFilterCount < e_w_filterMaxCnt )
        {
            pFilterStatus->usFilterCount++;
        }
        else
        {
            pFilterStatus->ucValidStatus = pFilterStatus->ucStatus;
            e_u_reValue = TRUE;
        }
    }
    else
    {
    }

    return (e_u_reValue);
}
#endif

#if (STD_LIB_ENABLE == STD_LIBCFG_IIRFILTER)
/**
* \brief : IIR Filter initialization function,Called by EcuM_Callout_Stubs
* \param[in] - pulBuffer, usInitVal
* \param[out] -
* \pre : Rte has started
* \post -
* \return -
*/
void LIB_IirFilter_Init(uint32 *pulBuffer, uint16 usInitVal)
{
    *pulBuffer = (uint32)((uint32)usInitVal << LIB_IIR_FIXPOINT_NUM);
}
/**
* \brief : IIR Filter update result
* \param[in] - pulBuffer:IIR Buffer,ucCoef,usInput
* \param[out] - result of iir filter
* \pre : LIB_IirFilter_Init shall be called first
* \post -
* \return -
*/
uint16 LIB_IirFilter_Update(uint32 *pulBuffer, uint8 ucCoef, uint16 usInput)
{
    uint16 usRet = 0u;
    uint32 ulBuffTmp;
    uint32 ulInputQ = ((uint32)usInput) << LIB_IIR_FIXPOINT_NUM; 
    
    if(*pulBuffer > ((uint32)((uint32)LIB_MAXVALUE_16 << LIB_IIR_FIXPOINT_NUM)))
    {
        *pulBuffer = (uint32)((uint32)LIB_MAXVALUE_16 << LIB_IIR_FIXPOINT_NUM);
    }
    /*
        y(N) = (ucCoef * x(N) + (K - ucCoef) * y(N-1)) / K, K = LIB_IIR_K_VAL
    */    
    ulBuffTmp = (uint32)(((uint32)ucCoef * ulInputQ + ((uint32)LIB_IIR_K_VAL - (uint32)ucCoef) * pulBuffer[0]) / (uint32)LIB_IIR_K_VAL);
    *pulBuffer = ulBuffTmp;

    usRet = (uint16)(ulBuffTmp >> LIB_IIR_FIXPOINT_NUM);

    return usRet;
}
#endif

/*******************************************************************************
Name            : LIB_BinarySearch
Syntax          : uint16 LIB_BinarySearch( const uint32 *SearchTablePtr, uint16 TableLength, uint32 SearchValue )
Sync/Async      : Sync
Reentrancy      :
Parameters(in)  : SearchTablePtr        :sensor resister table address
Parameters(in)  : TableLength           :sensor resister table length
Parameters(in)  : SearchValue           :search value
Parameters(out) : None                  :-
Return value    : TempReturnValue       :resister table index
Description     : binary search algorithm
Call By         : 
|******************************************************************************/
#if (STD_LIB_ENABLE == STD_LIBCFG_BINARYSEARCH)
uint16 LIB_BinarySearch( const uint32 *SearchTablePtr, uint16 TableLength, uint32 SearchValue )
{
    uint16 mid   = (uint16)0u;
    uint16 left  = (uint16)0u;
    uint16 right = TableLength - (uint16)1u;

    while ( left <= right )
    {
        mid = left + ( ( right - left ) >> 1u );

        if ( SearchTablePtr[ mid ] > SearchValue )
        {
            left = mid + (uint16)1u;
        }
        else if ( SearchTablePtr[ mid ] < SearchValue )
        {
            right = mid - (uint16)1u;
        }
        else
        {
            break;
        }
    }

    return mid;
}
#endif

#define STD_LIB_STOP_SEC_CODE


uint8 Lib_GetVersioninfo(Std_VersionInfoType*  tVersioninfoStruct)
{
    /* ----- Local Variables ---------------------------------------------- */
    uint8 errorId = LIB_E_NO_ERROR;

    /* ----- Development Error Checks ------------------------------------- */
    /* #20 Check that the passed parameter is not a Null Pointer. */
    if (NULL_PTR == tVersioninfoStruct)
    {
        errorId = LIB_E_NULL_POINTER;
    }
    else
    {
        /* ----- Implementation ----------------------------------------------- */
        /* #30 Pass the BTNSINGLEHDLR version info from component header to the Std_VersionInfoType Pointer. */

        /*tVersioninfoStruct->vendorId = (uint16)LIB_VENDOR_ID;*/  /* SBSW_BTNSINGLEHDLR_POINTERACCESS_tVersioninfoStruct *//* polyspace MISRA-C3:D4.14 [Justified:Low] "No garbage value is written when called, and the risk is controllable" */
        tVersioninfoStruct->moduleID = (uint16)LIB_MODULE_ID;  /* SBSW_BTNSINGLEHDLR_POINTERACCESS_tVersioninfoStruct */

        tVersioninfoStruct->sw_major_version = (uint8)LIB_SW_MAJOR_VERSION;  /* SBSW_BTNSINGLEHDLR_POINTERACCESS_tVersioninfoStruct */
        tVersioninfoStruct->sw_minor_version = (uint8)LIB_SW_MINOR_VERSION;  /* SBSW_BTNSINGLEHDLR_POINTERACCESS_tVersioninfoStruct */
        tVersioninfoStruct->sw_patch_version = (uint8)LIB_SW_PATCH_VERSION;  /* SBSW_BTNSINGLEHDLR_POINTERACCESS_tVersioninfoStruct */
    }    
    return errorId;
}

/*EOF*/
