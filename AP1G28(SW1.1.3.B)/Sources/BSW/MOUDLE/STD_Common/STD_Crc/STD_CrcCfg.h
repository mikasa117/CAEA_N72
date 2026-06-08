/*******************************************************************************
|  File Name:  Std_CrcCfg.h
|  Description:  Implementation of the Crc Config Management
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

#if!defined (_STD_CRCCFG_H)
#define _STD_CRCCFG_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
/* CRC8 polynomial */
#define STD_CRC_INITIAL_VALUE8          ((uint8)0xFFu)
#define STD_CRC_POLYNOMIAL_8            ((uint8)0x1Du)
#define STD_CRC_FINAL_XOR_CRC8          ((uint8)0xFFu)

#define STD_CRC_INITIAL_VALUE16         ((uint16)0xFFFFu)
#define STD_CRC_POLYNOMIAL_16           ((uint16)0x1021u)

#define STD_CRC_INITIAL_VALUE32         ((uint32)0xFFFFFFFFuL)
#define STD_CRC_POLYNOMIAL_32           ((uint32)0xEDB88320uL)
#define STD_CRC_FINAL_XOR_CRC32         ((uint32)0xFFFFFFFFuL)

#define STD_LoopNum                ((uint8)8u)
#define STD_BufferSize            256u

#define STD_CRC_DISABLE            0U
#define STD_CRC_ENABLE            1U

/* CRC 8 */
#define STD_CRC_8_RUNTIME          (1u)
#define STD_CRC_8_TABLE                (0u)

/* CRC 16 */
#define STD_CRC_16_RUNTIME          (0u)
#define STD_CRC_16_TABLE            (1u)

/* CRC 32 */
#define STD_CRC_32_RUNTIME          (0u)
#define STD_CRC_32_TABLE            (1u)

#define STD_CRCCFG_8_MODE                  (STD_CRC_8_RUNTIME)
#define STD_CRCCFG_16_MODE             (STD_CRC_16_RUNTIME)
#define STD_CRCCFG_32_MODE             (STD_CRC_32_RUNTIME)

/*config the method class*/
#define STD_CRCCFG_CLASS_CRC8            STD_CRC_ENABLE
#define STD_CRCCFG_CLASS_CRC16        STD_CRC_ENABLE
#define STD_CRCCFG_CLASS_CRC32        STD_CRC_ENABLE

/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Table Definition
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/
#define STD_CRC_START_SEC_CODE
#include "STD_MemMap.h"

#define STD_CRC_STOP_SEC_CODE
#include "STD_MemMap.h"

#endif
/*EOF*/
