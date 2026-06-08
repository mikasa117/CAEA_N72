/*******************************************************************************
|  File Name:  STD_EepM.h
|  Description:  Implementation of the EepM Management
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
| 2019-03-01	01.00.01	 CXL 	   Add QAC
|******************************************************************************/

#if !defined (_STD_EEPM_H)
#define _STD_EEPM_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Std_Types.h"
#include "STD_EepCfg.h"
/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/
#if (EEP_MODULE_EN == EEP_ENABLE)
/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/*******************************************************************************
|    Enum Definition
|******************************************************************************/
typedef enum
{
    EEP_WRITE_NONE = 0u,
    EEP_WRITE_OK ,
    EEP_WRITE_FAILED,
    EEP_WRITE_PENDING,
    EEP_WRITE_REQ
} Eep_WriteResultType;
/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef unsigned short NvmDataIDType;
typedef unsigned char NvmDataType;
/*******************************************************************************
|    Table Definition
|******************************************************************************/

/*******************************************************************************
|    Global KAM with extern linkage
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/
/*EcuM*/
extern void EEPM_Init(void);
extern void EEPM_InitMemory( void );
extern void EEPM_InitKamMemory( void );
extern void EEPM_MainFunction( void );
extern void EEPM_SetUp( uint8 fblUpdataFlag,uint8 kamValidStatus);

/*Other Modules*/
extern uint8 EEPM_AppReadBlock( uint16 BlockID, uint8 ReadData[] );
extern void EEPM_AppWriteBlock( uint16 BlockID, const uint8 WriteData[] );
extern void Bsw_Callback_MultiBlockCallbackFunction( uint8 ServiceId, uint8 JobResult );

extern void EEPM_MultiBlockCallbackFunction( uint8 ServiceId, uint8 JobResult );
extern uint8 EEPM_GetSleepRequestStatus( void );
extern Eep_WriteResultType EEPM_GetBlockWriteStatus(uint16 BlockkId);

#endif/*(EEP_MODULE_EN == EEP_ENABLE)*/
#endif/*_STD_EEPM_H*/
/*EOF*/
