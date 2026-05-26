/*******************************************************************************
|  File Name:  Appl_CPID_Callback.h
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
#ifndef APPL_CPID_CALLBACK_H
#define APPL_CPID_CALLBACK_H
/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/

/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#include "Vector_Platform_Types.h"

/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/


/*******************************************************************************
|    Global Variable with extern linkage
|******************************************************************************/


/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/

extern uint8 CPID_CAEAShortTermAdj(const uint8 *LpCPID_u_DataPtr );
extern uint8 CPID_CAEAReturnCtlToECU(void);
extern uint8 CPID_0x7882RetCtlToECU(const uint8 * LpCPID_u_DataPtr );
extern uint8 CPID_0x7882ShortTermAdj(const uint8 * LpCPID_u_DataPtr );
extern uint8 CPID_0x2001RetCtlToECU(const uint8 * LpCPID_u_DataPtr );
extern uint8 CPID_0x2001ShortTermAdj(const uint8 * LpCPID_u_DataPtr );
extern uint8 CPID_0x2002RetCtlToECU(const uint8 * LpCPID_u_DataPtr );
extern uint8 CPID_0x2002ShortTermAdj(const uint8 * LpCPID_u_DataPtr );
extern uint8 CPID_0x2003RetCtlToECU(const uint8 * LpCPID_u_DataPtr );
extern uint8 CPID_0x2003ShortTermAdj(const uint8 * LpCPID_u_DataPtr );
extern uint8 CPID_0x2004RetCtlToECU(const uint8 * LpCPID_u_DataPtr );
extern uint8 CPID_0x2004ShortTermAdj(const uint8 * LpCPID_u_DataPtr );
#endif
