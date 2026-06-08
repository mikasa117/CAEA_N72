/*******************************************************************************
|  File Name:  Appl_DID_Callback.c
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

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "task.h"
#include "CAEA_Types.h"
#include "Std_Types.h"
#include "desc.h"
#include "CanDem.h"  
//#include "CY_Touchscreen.h"
//#include "STD_AdcM.h"
#include "tp_cfg.h"

//#include "STD_Eepm.h"
#include "CanApp.h"
#include "Appl_DID_Callback.h"
#include "DID_Callback.h"
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
|    Global variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|    static Local Functions Declaration
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/
//#pragma section text Code_Appl_DID_Callback



/*******************************************************************************
Name              : DID_ReadDid0x7864
Syntax            : uint8 DID_ReadDid0x7864(void)
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    : None                        :-
Parameters(out)   : None                        :-
Return value      : Operation status            :-
Description       : 
Call By           : 
History
<No.>    <author>    <time>    <description>
1
******************************************************************************/

/*****************************************************************************
                        Write DID        
*****************************************************************************/
uint8 DID_WriteDid0xF089( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Write0xF089(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_WriteDid0xF187( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Write0xF187(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_WriteDid0xF18C( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Write0xF18C(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_WriteDid0xF190( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Write0xF190(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_WriteDid0xF1F0( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Write0xF1F0(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_WriteDid0xF1F6( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Write0xF1F6(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_WriteDid0xF1FA( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Write0xF1FA(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_WriteDid0xF1FB( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Write0xF1FB(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_WriteDid0xF1FC( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Write0xF1FC(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}


/*****************************************************************************
                        Read DID        
*****************************************************************************/


uint8 DID_ReadDid0xF089( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF089(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_ReadDid0xF120( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF120(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_ReadDid0xF121( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF121(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_ReadDid0xF122( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF122(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_ReadDid0xF170( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF170(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_ReadDid0xF171( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF171(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_ReadDid0xF184( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF184(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_ReadDid0xF187( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF187(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_ReadDid0xF188( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF188(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}
uint8 DID_ReadDid0xF189( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF189(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_ReadDid0xF18A( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF18A(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_ReadDid0xF18C( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF18C(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_ReadDid0xF190( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF190(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_ReadDid0xF1F0( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF1F0(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_ReadDid0xF1F6( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF1F6(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_ReadDid0xF1F7( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF1F7(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_ReadDid0xF1F8( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF1F8(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_ReadDid0xF1F9( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF1F9(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}

uint8 DID_ReadDid0xF1FA( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF1FA(LpDID_u_DataPtr);

    return LeDCM_u_RetVal;
}


uint8 DID_ReadDid0xF1FB( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF1FB(LpDID_u_DataPtr);


    return LeDCM_u_RetVal;
}

uint8 DID_ReadDid0xF1FC( uint8 LpDID_u_DataPtr[] )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = DID_Read0xF1FC(LpDID_u_DataPtr);


    return LeDCM_u_RetVal;
}




/////////////////////////////////////////23////////////////////////
/////////////////////////////////////////23////////////////////////
uint8 ReadMemoryByAddress_23( DescMsgContext* pMsgContext )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = ReadMemory_ByAddress_23(pMsgContext);
    
    return LeDCM_u_RetVal;
}


uint8 WriteMemoryByAddress_3D( DescMsgContext* pMsgContext )
{    
    uint8 LeDCM_u_RetVal;

    LeDCM_u_RetVal = WriteMemory_ByAddress_3D(pMsgContext);

    return LeDCM_u_RetVal;
}












/////////////////////////////////