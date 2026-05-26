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
#include <NET/Manual/CanDcm/Appl_DID_Callback.h>
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

/*******************************************************************************
Name              : DID_WriteDid0xF199
Syntax            : uint8 DID_WriteDid0xF199(uint8 LpDID_u_DataPtr[])
Sync/Async        : Synchronous
Reentrancy        :
Parameters(in)    :                                         :-
Parameters(out)   : uint8 LpDID_u_DataPtr[]                 :-
Return value      : Operation status                        :-
Description       : read data by identifier
Call By           : DCM WriteDid
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
uint8 RteDcm_ReadDid0xF199( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF199(&LpDID_u_DataPtr[0]);
}

uint8 RteDcm_ReadDid0xF187( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF187(&LpDID_u_DataPtr[0]);
}

uint8 RteDcm_ReadDid0xF18A( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF18A(&LpDID_u_DataPtr[0]);
}

uint8 DID_WriteDid0xF190( uint8 LpDID_u_DataPtr[] )
{	
	uint8 LeDCM_u_RetVal;

	LeDCM_u_RetVal = DID_Write0xF190(LpDID_u_DataPtr);

	return LeDCM_u_RetVal;
}

uint8 RteDcm_ReadDid0xF190( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF190(&LpDID_u_DataPtr[0]);
}

uint8 DID_WriteDid0xF1A2( uint8 LpDID_u_DataPtr[] )
{	
	uint8 LeDCM_u_RetVal;

	LeDCM_u_RetVal = DID_Write0xF1A2(LpDID_u_DataPtr);

	return LeDCM_u_RetVal;
}

uint8 RteDcm_ReadDid0xF1A2( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF1A2(&LpDID_u_DataPtr[0]);
}

uint8 RteDcm_ReadDid0xF191( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF191(&LpDID_u_DataPtr[0]);
}

uint8 RteDcm_ReadDid0xF189( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF189(&LpDID_u_DataPtr[0]);
}

uint8 RteDcm_ReadDid0xF193( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF193(&LpDID_u_DataPtr[0]);
}

uint8 RteDcm_ReadDid0xF195( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF195(&LpDID_u_DataPtr[0]);
}

uint8 RteDcm_ReadDid0xF180( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF180(&LpDID_u_DataPtr[0]);
}
uint8 RteDcm_ReadDid0xF182( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF182(&LpDID_u_DataPtr[0]);
}

uint8 DID_WriteDid0xF112( uint8 LpDID_u_DataPtr[] )
{	
	uint8 LeDCM_u_RetVal;

	LeDCM_u_RetVal = DID_Write0xF112(LpDID_u_DataPtr);

	return LeDCM_u_RetVal;
}

uint8 RteDcm_ReadDid0xF112( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF112(&LpDID_u_DataPtr[0]);
}

uint8 RteDcm_ReadDid0xF198( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF198(&LpDID_u_DataPtr[0]);
}

uint8 RteDcm_ReadDid0xF197( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF197(&LpDID_u_DataPtr[0]);
}

uint8 DID_WriteDid0xF197( uint8 LpDID_u_DataPtr[] )
{	
	uint8 LeDCM_u_RetVal;

	LeDCM_u_RetVal = DID_Write0xF197(LpDID_u_DataPtr);

	return LeDCM_u_RetVal;
}

uint8 RteDcm_ReadDid0xF113( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF113(&LpDID_u_DataPtr[0]);
}

uint8 RteDcm_ReadDid0xF186( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF186(&LpDID_u_DataPtr[0]);
}

uint8 RteDcm_ReadDid0xF18B( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF18B(&LpDID_u_DataPtr[0]);
}

uint8 DID_WriteDid0xF18C( uint8 LpDID_u_DataPtr[] )
{	
	uint8 LeDCM_u_RetVal;

	LeDCM_u_RetVal = DID_Write0xF18C(LpDID_u_DataPtr);

	return LeDCM_u_RetVal;
}

uint8 RteDcm_ReadDid0xF18C( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF18C(&LpDID_u_DataPtr[0]);
}

uint8 RteDcm_ReadDid0x0200( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0x0200(&LpDID_u_DataPtr[0]);
}

uint8 RteDcm_ReadDid0x7501( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0x7501(&LpDID_u_DataPtr[0]);
}

uint8 RteDcm_ReadDid0x7502( uint8 LpDID_u_DataPtr[] )
{
   return DID_Read0x7502(&LpDID_u_DataPtr[0]);
}
uint8 RteDcm_ReadDid0x0201( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0x0201(&LpDID_u_DataPtr[0]);
}

uint8 DID_WriteDid0xF101( uint8 LpDID_u_DataPtr[] )
{	
	uint8 LeDCM_u_RetVal;

	LeDCM_u_RetVal = DID_Write0xF101(LpDID_u_DataPtr);

	return LeDCM_u_RetVal;
}

uint8 RteDcm_ReadDid0xF101( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF101(&LpDID_u_DataPtr[0]);
}

uint8 DID_WriteDid0xF110( uint8 LpDID_u_DataPtr[] )
{
	uint8 LeDCM_u_RetVal;

	LeDCM_u_RetVal = DID_Write0xF110(LpDID_u_DataPtr);

	return LeDCM_u_RetVal;
}

uint8 RteDcm_ReadDid0xF110( uint8 LpDID_u_DataPtr[] )
{
    return DID_Read0xF110(&LpDID_u_DataPtr[0]);
}

uint8 DID_WriteDid0xD135( uint8 LpDID_u_DataPtr[] )
{
	uint8 LeDCM_u_RetVal;

	LeDCM_u_RetVal = DID_Write0xD135(LpDID_u_DataPtr);

	return LeDCM_u_RetVal;
}

