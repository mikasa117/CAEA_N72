/*******************************************************************************
|  File Name:  Appl_DID_Callback.h
|  Description:  Implementation of the Dem_DTC_Detection Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| 
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date        Version   Author  Description
| ----------  --------  ------  ------------------------------------------------
| 2016-12-10  V1.0      YJ      first implementation

|******************************************************************************/
#ifndef APPL_DID_CALLBACK_H
#define APPL_DID_CALLBACK_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Std_Types.h"
/******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|*****************************************************************************/

/******************************************************************************
|    Macro Definition
|*****************************************************************************/
#define DID_F199_LEN               (4u)
#define DID_F187_LEN               (21u)
#define DID_F18A_LEN               (6u)
#define DID_F190_LEN               (17u)
#define DID_F1A2_LEN               (4u)
#define DID_F191_LEN               (10u)
#define DID_F189_LEN               (10u)
#define DID_F193_LEN               (16u)
#define DID_F195_LEN               (16u)
#define DID_F180_LEN               (16u)
#define DID_F182_LEN               (16u)
#define DID_F112_LEN               (8u)
#define DID_F198_LEN               (16u)
#define DID_F197_LEN               (8u)
#define DID_F113_LEN               (4u)
#define DID_F186_LEN               (1u)
#define DID_F18B_LEN               (4u)
#define DID_F18C_LEN               (24u)
#define DID_0200_LEN               (1u)
#define DID_0201_LEN               (1u)
#define DID_F101_LEN               (8u)
#define DID_F110_LEN               (16u)
#define DID_D135_LEN               (16u)
#define DID_7501_LEN			   (1u)
#define DID_7502_LEN			   (2u)

/******************************************************************************
|    Enum Definition
|*****************************************************************************/

/******************************************************************************
|    Typedef Definition
|*****************************************************************************/

/******************************************************************************
|    Global Variable with extern linkage
|*****************************************************************************/
extern uint8 RteDcm_ReadDid0xF199( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF187( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF18A( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_WriteDid0xF190( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF190( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_WriteDid0xF1A2( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF1A2( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF191( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF189( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF193( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF195( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF180( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF182( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_WriteDid0xF112( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF112( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF198( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF197( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_WriteDid0xF197( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF113( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF186( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF18B( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_WriteDid0xF18C( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF18C( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0x0200( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0x0201( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_WriteDid0xF101( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF101( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_WriteDid0xF110( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0xF110( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_WriteDid0xD135( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0x7501( uint8 LpDID_u_DataPtr[] );
extern uint8 RteDcm_ReadDid0x7502( uint8 LpDID_u_DataPtr[] );

/******************************************************************************
|    Global Function Prototypes
|*****************************************************************************/


#endif
