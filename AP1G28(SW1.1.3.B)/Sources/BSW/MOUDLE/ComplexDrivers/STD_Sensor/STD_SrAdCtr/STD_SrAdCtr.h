/*******************************************************************************
|  File Name:  STD_SrAdCtr.h
|  Description:  Implementation of the Sensor Ctr Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           xiayajun               CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2018-06-21    01.00.00     XYJ       Creation
|
|******************************************************************************/


#if !defined (_STD_SRADCTR_H)
/* polyspace<MISRA-C3:2.5:Not a defect:Justified> NO fluence *//* polyspace<MISRA-C3:21.1:Not a defect:Justified> NO fluence */
#define _STD_SRADCTR_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
//#include "SysTypes.h"
#include "STD_SrAdCtr_Cfg.h"
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
|    Global Function Prototypes
|******************************************************************************/

extern void SRADCTR_InitMemory( void );
extern void SRADCTR_ConvMainFunction( void );
extern void SRADCTR_DiagMainFunction( void );
extern sint16 SRADCTR_TableGetValidValue( uint8 CtrChannel );
extern uint8 SRADCTR_TableErrValue( SRADCTR_Table_CH_Enum ucChannel );
extern uint8 SRADCTR_TableGetValidStatus(  uint8 CtrChannel  );
extern uint8 SRADCTR_TableGetShortGndStatus( SRADCTR_Table_CH_Enum ucChannel );
extern uint8 SRADCTR_TableGetOpenOrShortBatStatus( SRADCTR_Table_CH_Enum ucChannel );
extern uint32 SRADCTR_TableGetOpenShortStatus( void );

#if (0)
extern sint16 SRADCTR_LineGetValidValue( SRADCTR_Line_CH_Enum CtrChannel );
extern uint8 SRADCTR_LineGetValidStatus(  SRADCTR_Line_CH_Enum CtrChannel  );
extern uint8 SRADCTR_LineGetShortGndStatus( SRADCTR_Line_CH_Enum ucChannel );
extern uint8 SRADCTR_LineGetOpenOrShortBatStatus( SRADCTR_Line_CH_Enum ucChannel );
#endif

extern uint16 LIB_BinarySearch( const uint32 *SearchTablePtr, uint16 TableLength, uint32 SearchValue );


#endif/*End of ifndef*/
/*EOF*/
