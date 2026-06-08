/*******************************************************************************
|  File Name:  STD_BtrM.h
|  Description:  Implementation of the Battery Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|	  All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XZS           Zhangsheng Xia         CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2017-02-22    01.00.00     XZS       Creation
|
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_BtrM.h"

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
|    Static local KAM variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Table Const Definition
|******************************************************************************/

/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/


/*******************************************************************************
Name              : BTRM_InitMemory
Syntax            : void BTRM_InitMemory(void)
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      : None
Description       :
Call By           :
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
void BTRM_InitMemory(void)
{
    BTRCTR_InitMemory();
#if (BTRM_ENABLE == BTRM_DTC_EN_CLASS)
    BTRDIAG_InitMemory();
#endif
}

/*******************************************************************************
Name              : BTRM_InitKamMemory
Syntax            : void BTRM_InitKamMemory( void )
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      :
Description       :
Call By           :
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
void BTRM_InitKamMemory( void )
{
    BTRCTR_InitKamMemory() ;
}


/*******************************************************************************
Name              : BTRM_MainFunction
Syntax            : void BTRM_MainFunction( void )
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      :
Description       :
Call By           :
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
void BTRM_MainFunction(void)
{
    BTRCTR_ModeFunction();
#if (BTRM_ENABLE == BTRM_DTC_EN_CLASS)
    BTRDIAG_MainFunction();
#endif
}



/*EOF*/
