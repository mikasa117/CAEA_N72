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
//#include "EepromM.h"
/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#include "CAEA_Types.h"
#include "desc.h"



/*#define RID_789E_START_LEN         (1u)
#define RID_789E_RES_LEN           (1u)
#define RID_789E_STOP_LEN          (0u)

#define RID_789F_START_LEN         (1u)
#define RID_789F_RES_LEN           (5u)
#define RID_789F_STOP_LEN          (0u)*/

#define RID_Step_Start  0x01u
#define RID_Step_Stop   0x02u
#define RID_Step_Res    0x03u

/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/


/*******************************************************************************
|    Global Variable with extern linkage
|******************************************************************************/
extern uint8 DID_WriteDid0xF187( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_WriteDid0xF089( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_WriteDid0xF18C( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_WriteDid0xF190( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_WriteDid0xF1F0( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_WriteDid0xF1F6( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_WriteDid0xF1FA( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_WriteDid0xF1FB( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_WriteDid0xF1FC( uint8 LpDID_u_DataPtr[] );


extern uint8 DID_ReadDid0xF089( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF120( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF121( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF122( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF170( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF171( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF184( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF187( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF188( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF189( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF18A( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF18C( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF190( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF1F0( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF1F6( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF1F7( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF1F8( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF1F9( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF1FA( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF1FB( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_ReadDid0xF1FC( uint8 LpDID_u_DataPtr[] );
extern uint8 ReadMemoryByAddress_23( DescMsgContext* pMsgContext );
extern uint8 WriteMemoryByAddress_3D( DescMsgContext* pMsgContext );

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/


#endif
