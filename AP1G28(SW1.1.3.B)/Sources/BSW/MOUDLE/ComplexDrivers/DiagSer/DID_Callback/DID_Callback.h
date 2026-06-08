/*******************************************************************************
|  File Name:  DID_Callback.h
|  Description:  Implementation of the DID_Callback Config Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           XiaYaJun          CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 2018-05-23    01.00.00     XYJ       Creation
|******************************************************************************/

#ifndef _DID_Callback_H_
#define _DID_Callback_H_

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "CAEA_Types.h"
#include "desc.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/

#define CeDid_u_0xF1F9_ChangJiang_SWVersion			{'S','W','.','1','.','1','.','3','.','B'}//SW.1.1.3.11

#define CeDid_u_0xF122_DiagDefinitionVersion        {'V','1','.','2'}//V1.2
#define CeDid_u_0xF120_NetworkProtocolVersion    	{'V','1','.','0'}//V1.0
#define CeDid_u_0xF121_FuncDefinitionVersion        {'V','1','.','0'}//V1.0
#define CeDid_u_0xF170_FBLVersion					{'V','1','.','0'}//V1.0
#define CeDid_u_0xF171_FBLRequirementVersion		{'V','1','.','0'}//V1.0






#define CeDID_Pend         0x0u
#define CeDID_OK           0x1u  
#define CeDID_NOK          0x2u    
#define CeDID_OutRange     0x31u
#define CeDID_OutTime      0x72u  

/*******************************************************************************
|    Enum DefinitionB
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Global Variable with extern linkage
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/
extern uint8 DID_Write0xF187(uint8 LpDID_u_DataPtr[]);
extern uint8 DID_Write0xF089(uint8 LpDID_u_DataPtr[]);
extern uint8 DID_Write0xF18C(uint8 LpDID_u_DataPtr[]);
extern uint8 DID_Write0xF190(uint8 LpDID_u_DataPtr[]);
extern uint8 DID_Write0xF1F0(uint8 LpDID_u_DataPtr[]);
extern uint8 DID_Write0xF1F6(uint8 LpDID_u_DataPtr[]);
extern uint8 DID_Write0xF1FA(uint8 LpDID_u_DataPtr[]);
extern uint8 DID_Write0xF1FB(uint8 LpDID_u_DataPtr[]);
extern uint8 DID_Write0xF1FC(uint8 LpDID_u_DataPtr[]);
extern void ApplDescWrite_Fridge_App(uint8 LpDID_u_DataPtr[]);


extern uint8 DID_Read0xF089( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF120( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF121( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF122( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF170( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF171( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF184( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF187( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF188( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF189( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF18A( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF18C( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF190( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF1F0( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF1F6( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF1F7( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF1F8( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF1F9( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF1FA( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF1FB( uint8 LpDID_u_DataPtr[] );
extern uint8 DID_Read0xF1FC( uint8 LpDID_u_DataPtr[] );
extern uint8 ReadMemory_ByAddress_23( DescMsgContext* pMsgContext );
extern uint8 WriteMemory_ByAddress_3D( DescMsgContext* pMsgContext );


extern void CUS_NVR_WriteDID(void);
extern void Check_DIDF1FA_CompressorFault(void);
extern void DID_AgingModeFunction(void);

extern void DID_Callback_Init(void);
#endif 

