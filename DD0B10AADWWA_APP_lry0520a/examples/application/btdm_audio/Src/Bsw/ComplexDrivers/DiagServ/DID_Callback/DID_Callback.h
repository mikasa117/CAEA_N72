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
#ifndef DID_CALLBACK_H
#define DID_CALLBACK_H

#include "Vector_Platform_Types.h"
#include "Appl_DID_Callback.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/*******************************************************************************
|    Enum DefinitionB
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|	 Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|	 Global Variable with extern linkage
|******************************************************************************/

/*******************************************************************************
|	 Global Function Prototypes
|******************************************************************************/
extern void CanDcm_InitMemory(void);
extern uint8 DID_Read0xF199(uint8 DataPtr[]);
extern uint8 DID_Read0xF187(uint8 DataPtr[]);
extern uint8 DID_Read0xF18A(uint8 DataPtr[]);
extern uint8 DID_Write0xF190(uint8 LpDID_u_DataPtr[]);
extern uint8 DID_Read0xF190(uint8 DataPtr[]);
extern uint8 DID_Write0xF1A2(uint8 LpDID_u_DataPtr[]);
extern uint8 DID_Read0xF1A2(uint8 DataPtr[]);
extern uint8 DID_Read0xF191(uint8 DataPtr[]);
extern uint8 DID_Read0xF189(uint8 DataPtr[]);
extern uint8 DID_Read0xF193(uint8 DataPtr[]);
extern uint8 DID_Read0xF195(uint8 DataPtr[]);
extern uint8 DID_Read0xF180(uint8 DataPtr[]);
extern uint8 DID_Read0xF182(uint8 DataPtr[]);
extern uint8 DID_Write0xF112(uint8 LpDID_u_DataPtr[]);
extern uint8 DID_Read0xF112(uint8 DataPtr[]);
extern uint8 DID_Read0xF198(uint8 DataPtr[]);
extern uint8 DID_Read0xF197(uint8 DataPtr[]);
extern uint8 DID_Write0xF197(uint8 LpDID_u_DataPtr[]);
extern uint8 DID_Read0xF113(uint8 DataPtr[]);
extern uint8 DID_Read0xF186(uint8 DataPtr[]);
extern uint8 DID_Read0xF18B(uint8 DataPtr[]);
extern uint8 DID_Write0xF18C(uint8 LpDID_u_DataPtr[]);
extern uint8 DID_Read0xF18C(uint8 DataPtr[]);
extern uint8 DID_Read0x0200(uint8 DataPtr[]);
extern uint8 DID_Read0x0201(uint8 DataPtr[]);
extern uint8 DID_Write0xF101(uint8 LpDID_u_DataPtr[]);
extern uint8 DID_Read0xF101(uint8 DataPtr[]);
extern uint8 DID_Write0xF110(uint8 LpDID_u_DataPtr[]);
extern uint8 DID_Read0xF110(uint8 DataPtr[]);
extern uint8 DID_Write0xD135(uint8 LpDID_u_DataPtr[]);
extern uint8 DID_Read0x7501(uint8 DataPtr[]);
extern uint8 DID_Read0x7502(uint8 DataPtr[]);

extern uint8 DID0xF190DefaultValue[DID_F190_LEN];
#endif
