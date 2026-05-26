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
#define _STD_LIB_H      /* polyspace MISRA-C3:21.1 [Justified:Low] "Preventing duplicate compilation" */

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_Lib_Cfg.h"
#include "STD_TypesDef.h"
/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
/* polyspace-begin MISRA-C3:2.5 [Justified:Low] "Platform reservation macros define configuration" */
#define LIB_SET_UINT32_BIT(Data, Offset)    (((Data)) |= ((uint32)1u << (Offset)))
#define LIB_SET_UINT16_BIT(Data, Offset)    (((Data)) |= ((uint16)1u << (Offset)))
#define LIB_SET_UINT8_BIT(Data, Offset)     (((Data)) |= ((uint8) 1u << (Offset)))

#define LIB_RESET_UINT32_BIT(Data, Offset)  (((Data)) &= ~((uint32)1u << (Offset)))
#define LIB_RESET_UINT16_BIT(Data, Offset)  (((Data)) &= ~((uint16)1u << (Offset)))
#define LIB_RESET_UINT8_BIT(Data, Offset)   (((Data)) &= ~((uint8) 1u << (Offset)))

#define LIB_GET_UINT32_BIT(Data, Offset)    (((uint8)(((uint32) (Data)) >> (Offset))) & 0x01u)
#define LIB_GET_UINT16_BIT(Data, Offset)    (((uint8)(((uint16) (Data)) >> (Offset))) & 0x01u)
#define LIB_GET_UINT8_BIT(Data, Offset)     (((uint8)(((uint8 ) (Data)) >> (Offset))) & 0x01u)

#define LIB_GET_BYTE_0(Data)                ((uint8) (Data))
#define LIB_GET_BYTE_1(Data)                ((uint8)((Data)>> 8u))
#define LIB_GET_BYTE_2(Data)                ((uint8)((Data)>>16u))
#define LIB_GET_BYTE_3(Data)                ((uint8)((Data)>>24u))

#define LIB_GET_BYTE_LIT_UINT16(Data)       ((uint16)Data[0u] + ((uint16)Data[1u] << 8u))
#define LIB_GET_BYTE_BIG_UINT16(Data)       ((uint16)Data[1u] + ((uint16)Data[0u] << 8u))
/* polyspace-end MISRA-C3:2.5 [Justified:Low] "Platform reservation macros define configuration" */


/* Version - BCD coded version number - Main- and Sub-Version - Release-Version */
#define SYSSERVICE_ASR4LIB_VERSION                                  0x0101u
#define SYSSERVICE_ASR4LIB_RELEASE_VERSION                          0x02u

/* vendor and module identification */
/*#define LIB_VENDOR_ID                                               (30u)*/   /* Vector Informatik GmbH */
#define LIB_MODULE_ID                                               (0x0603u)
/*#define LIB_INSTANCE_ID                                             (0u)*/
 
/* Component Version Information */
#define LIB_SW_MAJOR_VERSION                                        (SYSSERVICE_ASR4LIB_VERSION >> 8)
#define LIB_SW_MINOR_VERSION                                        (SYSSERVICE_ASR4LIB_VERSION & 0x00FFu)
#define LIB_SW_PATCH_VERSION                                        (SYSSERVICE_ASR4LIB_RELEASE_VERSION)

/* ----------Error Codes in Development-Mode------------------------------- */
#define LIB_E_UNINIT                                                (0x10u)     /* polyspace MISRA-C3:2.5 [Justified:Low] "Platform reservation macro definition" */
#define LIB_E_NULL_POINTER                                          (0x12u)

/* Vector extensions to the standard error codes  SWS -------------------------------*/
#define LIB_E_NO_ERROR                                              (0x00u)
/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef struct Type_FilterStruct    /* polyspace MISRA-C3:2.4 [Justified:Low] "Platform reservation type" */
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
extern uint8 Lib_GetVersioninfo(Std_VersionInfoType*  tVersioninfoStruct);

#define STD_LIB_START_SEC_CODE      /* polyspace MISRA-C3:2.5 [Justified:Low] "Macro definition for segments" */
#if (STD_LIB_ENABLE == STD_LIBCFG_SETMEMORY)
extern void LIB_SetMemory(uint8 *pStr, uint8 val, uint16 len);
#endif

#if (STD_LIB_ENABLE == STD_LIBCFG_COMPARE)
extern uint8 LIB_Compare(uint8 *pSrc, uint8 *pDes, uint16 len);
#endif

#if (STD_LIB_ENABLE == STD_LIBCFG_COMPARER)
extern uint8 LIB_CompareR(uint8 *pSrc, uint8 *pDes, uint16 len);
#endif

#if (STD_LIB_ENABLE == STD_LIBCFG_COPY)
extern void LIB_Copy(uint8 *pDes, const uint8 *pSrc, uint16 len);
#endif

#if (STD_LIB_ENABLE == STD_LIBCFG_COPYR)
extern void LIB_CopyR(uint8 *pDes, uint8 *pSrc, uint16 len);
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

#if (STD_LIB_ENABLE == STD_LIBCFG_STATUSFILTER)
extern void LIB_IirFilter_Init(uint32 *pulBuffer, uint16 usInitVal);
extern uint16 LIB_IirFilter_Update(uint32 *pulBuffer, uint8 ucCoef, uint16 usInput);
#endif

#if (STD_LIB_ENABLE == STD_LIBCFG_BINARYSEARCH)
extern uint16 LIB_BinarySearch( const uint32 *SearchTablePtr, uint16 TableLength, uint32 SearchValue );
#endif

#define STD_LIB_STOP_SEC_CODE       /* polyspace MISRA-C3:2.5 [Justified:Low] "Macro definition for segments" */


#endif
/*EOF*/
