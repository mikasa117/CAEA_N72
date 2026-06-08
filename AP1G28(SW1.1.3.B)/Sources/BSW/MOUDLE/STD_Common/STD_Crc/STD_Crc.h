/*******************************************************************************
|  File Name:  Std_Crc.h
|  Description:  Implementation of the EepromM Management
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

#if !defined (_STD_CRC_H)
#define _STD_CRC_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_CrcCfg.h"

/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/

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
|    Global KAM with extern linkage
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/
#define STD_CRC_START_SEC_CODE
#include "STD_MemMap.h"
#if ( STD_CRCCFG_CLASS_CRC8== STD_CRC_ENABLE)
extern uint8 CRC_CalculateCRC8(const uint8 * Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8, uint8 Crc_IsFirstCall);
#endif
#if ( STD_CRCCFG_CLASS_CRC16== STD_CRC_ENABLE)
extern uint16 CRC_CalculateCRC16(const uint8 * Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16, uint8 Crc_IsFirstCall);
#endif
#if ( STD_CRCCFG_CLASS_CRC32 == STD_CRC_ENABLE)
extern uint32 CRC_CalculateCRC32(const uint8 * Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32, uint8 Crc_IsFirstCall);
#endif

#define STD_CRC_STOP_SEC_CODE
#include "STD_MemMap.h"

#endif

/*EOF*/
