/*******************************************************************************
|  File Name:  StdLib.h
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
| 2016-09-30    01.00.00     XYJ       Creation
|
|******************************************************************************/

#if !defined (_STD_LIB_H)
#define _STD_LIB_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_Lib_Cfg.h"
#include "Typedef.h"
/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define LIB_SET_UINT32_BIT(Data, Offset)    ((Data) |= (uint32)((uint32)1u << (Offset)))
#define LIB_SET_UINT16_BIT(Data, Offset)    ((Data) |= (uint16)((uint16)1u << (Offset)))
#define LIB_SET_UINT8_BIT(Data, Offset)     ((Data) |= (uint8)((uint8) 1u << (Offset)))

#define LIB_RESET_UINT32_BIT(Data, Offset)  ((Data) &= (uint32)(~(uint32)((uint32)1u << (Offset))))
#define LIB_RESET_UINT16_BIT(Data, Offset)  ((Data) &= (uint16)(~(uint16)((uint16)1u << (Offset))))
#define LIB_RESET_UINT8_BIT(Data, Offset)   ((Data) &= (uint8 )(~(uint8 )((uint8 )1u << (Offset))))

#define LIB_GET_UINT32_BIT(Data, Offset)    (((uint8)(((uint32) (Data)) >> (Offset))) & (uint8)0x01u)
#define LIB_GET_UINT16_BIT(Data, Offset)    (((uint8)(((uint16) (Data)) >> (Offset))) & (uint8)0x01u)
#define LIB_GET_UINT8_BIT(Data, Offset)     (((uint8)(((uint8 ) (Data)) >> (Offset))) & (uint8)0x01u)

#define LIB_GET_BYTE_0(Data)                ((uint8) (Data))
#define LIB_GET_BYTE_1(Data)                ((uint8)((Data)>>(uint8)8u))
#define LIB_GET_BYTE_2(Data)                ((uint8)((Data)>>(uint8)16u))
#define LIB_GET_BYTE_3(Data)                ((uint8)((Data)>>(uint8)24u))

#define LIB_GET_BYTE_LIT_UINT16(Data)		((uint16)Data[0u] + ((uint16)Data[1u] << 8u))
#define LIB_GET_BYTE_BIG_UINT16(Data)		((uint16)Data[1u] + ((uint16)Data[0u] << 8u))
/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef struct Type_FilterStruct
{
    uint8 ucStatus;
    uint8 ucLastStatus;
    uint8 ucValidStatus;
    uint16 usFilterCount;
} LibFilterStruct;
/*******************************************************************************
|    Table Definition
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/
#define STD_LIB_START_SEC_CODE
#include "STD_MemMap.h"
#if (STD_LIB_ENABLE == STD_LIBCFG_SETMEMORY)
extern void LIB_SetMemory(uint8 *pStr, uint8 val, uint16 len);
#endif

#if (STD_LIB_ENABLE == STD_LIBCFG_COMPARE)
extern uint8 LIB_Compare(const uint8 *pSrc, const uint8 *pDes, uint16 len);
#endif

#if (STD_LIB_ENABLE == STD_LIBCFG_COMPARER)
extern uint8 LIB_CompareR(const uint8 *pSrc, const uint8 *pDes, uint16 len);
#endif

#if (STD_LIB_ENABLE == STD_LIBCFG_COPY)
extern void LIB_Copy(uint8 *pDes, const uint8 *pSrc, uint16 len);
#endif

#if (STD_LIB_ENABLE == STD_LIBCFG_COPYR)
extern void LIB_CopyR(uint8 *pDes, const uint8 *pSrc, uint16 len);
#endif

#if (STD_LIB_ENABLE == STD_LIBCFG_BUBBLESORT)
extern void LIB_BubbleSort(uint16 *pData, uint8 length);
#endif

#if (STD_LIB_ENABLE == STD_LIBCFG_CALCULATEAVERAGE)
extern uint16 LIB_CalculateAverage(const uint16 *pData, uint8 length);
#endif

#if (STD_LIB_ENABLE == STD_LIBCFG_READDATA)
extern void LIB_ReadData(uint8 *pDes, uint32 pSrcAdd, uint32 len);
#endif

#if (STD_LIB_ENABLE == STD_LIBCFG_STATUSFILTER)
extern uint8 LIB_StatusFilter(LibFilterStruct *pFilterStatus, uint16 filterMaxCnt);
#endif

#if (STD_LIB_ENABLE == STD_LIBCFG_BINARYSEARCH)
extern uint16 LIB_BinarySearch( const uint32 *SearchTablePtr, uint16 TableLength, uint32 SearchValue );
#endif

#define STD_LIB_STOP_SEC_CODE
#include "STD_MemMap.h"

#endif
/*EOF*/
