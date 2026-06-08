/*******************************************************************************
||  File Name: RTE_DCM.c
||  Description: Implementation of the AUTOSAR DCM Interface
||-------------------------------------------------------------------------------
||  (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
||     All rights are reserved by CAEA.
||-------------------------------------------------------------------------------
|| Initials      Name                   Company
|| --------      ---------------------  -----------------------------------------
||                                    CAEA
||-------------------------------------------------------------------------------
||               R E V I S I O N   H I S T O R Y
||-------------------------------------------------------------------------------
|| Date          Version      Author    Description
|| ------------  --------     -------   -----------------------------------------
|| 2025.10.20     V1.0         SSS                                               
||
||******************************************************************************/

/*******************************************************************************
||    Other Header File Inclusion
||******************************************************************************/ 
#include "RTE_DCM.h"

/*******************************************************************************
||    Macro Definition
||******************************************************************************/

/*******************************************************************************
||    Enum Definition
||******************************************************************************/

/*******************************************************************************
||    Typedef Definition
||******************************************************************************/

/*******************************************************************************
||    Global variables Declaration
||******************************************************************************/

/*******************************************************************************
||    static local variables Declaration
||******************************************************************************/

/*******************************************************************************
||    static Local Functions Declaration
||******************************************************************************/

/*******************************************************************************
||    Extern variables and functions declaration
||******************************************************************************/

/********************************** DCM Initialization **********************************/
/*******************************************************************************
*Function            : void RTE_NET_Dcm_Init(void)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : DCM module initialization
|******************************************************************************/
void RTE_NET_Dcm_Init(void)
{
    /* DCM initialization implementation */
}

/********************************** DID Read Functions **********************************/
/*******************************************************************************
*Function            : uint8 RTE_NET_Dcm_Read_DIDF120(uint8 LaRteDcm_u_Value[])
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : LaRteDcm_u_Value            :Output data array
*Return value        : uint8                        :Status (0=OK, 1=Error)
*Description        : Read Network protocol version information
|******************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF120(uint8 LaRteDcm_u_Value[])
{
    /* DID F120 read implementation */
    return 0;
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Dcm_Read_DIDF121(uint8 LaRteDcm_u_Value[])
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : LaRteDcm_u_Value            :Output data array
*Return value        : uint8                        :Status (0=OK, 1=Error)
*Description        : Read Function definition version information
||******************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF121(uint8 LaRteDcm_u_Value[])
{
    /* DID F121 read implementation */
    return 0;
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Dcm_Read_DIDF122(uint8 LaRteDcm_u_Value[])
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : LaRteDcm_u_Value            :Output data array
*Return value        : uint8                        :Status (0=OK, 1=Error)
*Description        : Read DID F122 data
||******************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF122(uint8 LaRteDcm_u_Value[])
{
    /* DID F122 read implementation */
    return 0;
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Dcm_Read_DIDF189(uint8 LaRteDcm_u_Value[])
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : LaRteDcm_u_Value            :Output data array
*Return value        : uint8                        :Status (0=OK, 1=Error)
*Description        : Read DID F189 data
||******************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF189(uint8 LaRteDcm_u_Value[])
{
    /* DID F189 read implementation */
    return 0;
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Dcm_Read_DIDF089(uint8 LaRteDcm_u_Value[])
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : LaRteDcm_u_Value            :Output data array
*Return value        : uint8                        :Status (0=OK, 1=Error)
*Description        : Read DID F089 data
||******************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF089(uint8 LaRteDcm_u_Value[])
{
    /* DID F089 read implementation */
    return 0;
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Dcm_Read_DIDF187(uint8 LaRteDcm_u_Value[])
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : LaRteDcm_u_Value            :Output data array
*Return value        : uint8                        :Status (0=OK, 1=Error)
*Description        : Read DID F187 data
||******************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF187(uint8 LaRteDcm_u_Value[])
{
    /* DID F187 read implementation */
    return 0;
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Dcm_Read_DIDF18A(uint8 LaRteDcm_u_Value[])
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : LaRteDcm_u_Value            :Output data array
*Return value        : uint8                        :Status (0=OK, 1=Error)
*Description        : Read DID F18A data
||******************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF18A(uint8 LaRteDcm_u_Value[])
{
    /* DID F18A read implementation */
    return 0;
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Dcm_Read_DIDF18C(uint8 LaRteDcm_u_Value[])
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : LaRteDcm_u_Value            :Output data array
*Return value        : uint8                        :Status (0=OK, 1=Error)
*Description        : Read DID F18C data
||******************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF18C(uint8 LaRteDcm_u_Value[])
{
    /* DID F18C read implementation */
    return 0;
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Dcm_Read_DIDF190(uint8 LaRteDcm_u_Value[])
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : LaRteDcm_u_Value            :Output data array
*Return value        : uint8                        :Status (0=OK, 1=Error)
*Description        : Read DID F190 data
||******************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF190(uint8 LaRteDcm_u_Value[])
{
    /* DID F190 read implementation */
    return 0;
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Dcm_Read_DIDF170(uint8 LaRteDcm_u_Value[])
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : LaRteDcm_u_Value            :Output data array
*Return value        : uint8                        :Status (0=OK, 1=Error)
*Description        : Read DID F170 data
||******************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF170(uint8 LaRteDcm_u_Value[])
{
    /* DID F170 read implementation */
    return 0;
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Dcm_Read_DIDF171(uint8 LaRteDcm_u_Value[])
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : LaRteDcm_u_Value            :Output data array
*Return value        : uint8                        :Status (0=OK, 1=Error)
*Description        : Read DID F171 data
||******************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF171(uint8 LaRteDcm_u_Value[])
{
    /* DID F171 read implementation */
    return 0;
}

/******************************************************************************
 *Function    : uint8 RTE_NET_Dcm_Read_DIDF184(uint8 LaRteDcm_u_Value[])
 *Parameter   : uint8 LaRteDcm_u_Value[] - Output data array
 *ReturnValue : uint8 - Status (0=OK, 1=Error)
 *Description : Read DID F184 data
 *Length      : 7 bytes
 *Remark      : Return DID F184 data
 *****************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF184(uint8 LaRteDcm_u_Value[])
{
    /* DID F184 read implementation */
    return 0;
}

/******************************************************************************
 *Function    : uint8 RTE_NET_Dcm_Read_DIDF188(uint8 LaRteDcm_u_Value[])
 *Parameter   : uint8 LaRteDcm_u_Value[] - Output data array
 *ReturnValue : uint8 - Status (0=OK, 1=Error)
 *Description : Read DID F188 data
 *Length      : 20 bytes
 *Remark      : Return DID F188 data
 *****************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF188(uint8 LaRteDcm_u_Value[])
{
    /* DID F188 read implementation */
    return 0;
}

/******************************************************************************
 *Function    : uint8 RTE_NET_Dcm_Read_DIDF123(uint8 LaRteDcm_u_Value[])
 *Parameter   : uint8 LaRteDcm_u_Value[] - Output data array
 *ReturnValue : uint8 - Status (0=OK, 1=Error)
 *Description : Read DID F123 data
 *Length      : 20 bytes
 *Remark      : Return DID F123 data
 *****************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF123(uint8 LaRteDcm_u_Value[])
{
    /* DID F123 read implementation */
    return 0;
}

/******************************************************************************
 *Function    : uint8 RTE_NET_Dcm_Read_DIDF086(uint8 LaRteDcm_u_Value[])
 *Parameter   : uint8 LaRteDcm_u_Value[] - Output data array
 *ReturnValue : uint8 - Status (0=OK, 1=Error)
 *Description : Read DID F086 data
 *Length      : 20 bytes
 *Remark      : Return DID F086 data
 *****************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF086(uint8 LaRteDcm_u_Value[])
{
    /* DID F086 read implementation */
    return 0;
}

/******************************************************************************
 *Function    : uint8 RTE_NET_Dcm_Read_DIDF087(uint8 LaRteDcm_u_Value[])
 *Parameter   : uint8 LaRteDcm_u_Value[] - Output data array
 *ReturnValue : uint8 - Status (0=OK, 1=Error)
 *Description : Read DID F087 data
 *Length      : 20 bytes
 *Remark      : Return DID F087 data
 *****************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF087(uint8 LaRteDcm_u_Value[])
{
    /* DID F087 read implementation */
    return 0;
}

/******************************************************************************
 *Function    : uint8 RTE_NET_Dcm_Read_DIDF010(uint8 LaRteDcm_u_Value[])
 *Parameter   : uint8 LaRteDcm_u_Value[] - Output data array
 *ReturnValue : uint8 - Status (0=OK, 1=Error)
 *Description : Read DID F010 data
 *Length      : 34 bytes
 *Remark      : Return DID F010 data
 *****************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF010(uint8 LaRteDcm_u_Value[])
{
    /* DID F010 read implementation */
    return 0;
}

/******************************************************************************
 *Function    : uint8 RTE_NET_Dcm_Read_DIDF011(uint8 LaRteDcm_u_Value[])
 *Parameter   : uint8 LaRteDcm_u_Value[] - Output data array
 *ReturnValue : uint8 - Status (0=OK, 1=Error)
 *Description : Read DID F011 data
 *Length      : 20 bytes
 *Remark      : Return DID F011 data
 *****************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF011(uint8 LaRteDcm_u_Value[])
{
    /* DID F011 read implementation */
    return 0;
}

/******************************************************************************
 *Function    : uint8 RTE_NET_Dcm_Read_DIDF012(uint8 LaRteDcm_u_Value[])
 *Parameter   : uint8 LaRteDcm_u_Value[] - Output data array
 *ReturnValue : uint8 - Status (0=OK, 1=Error)
 *Description : Read DID F012 data
 *Length      : 20 bytes
 *Remark      : Return DID F012 data
 *****************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF012(uint8 LaRteDcm_u_Value[])
{
    /* DID F012 read implementation */
    return 0;
}

/******************************************************************************
 *Function    : uint8 RTE_NET_Dcm_Read_DIDF1A3(uint8 LaRteDcm_u_Value[])
 *Parameter   : uint8 LaRteDcm_u_Value[] - Output data array
 *ReturnValue : uint8 - Status (0=OK, 1=Error)
 *Description : Read DID F1A3 data
 *Length      : 8 bytes
 *Remark      : Return DID F1A3 data
 *****************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF1A3(uint8 LaRteDcm_u_Value[])
{
    /* DID F1A3 read implementation */
    return 0;
}

/******************************************************************************
 *Function    : uint8 RTE_NET_Dcm_Read_DIDF1A4(uint8 LaRteDcm_u_Value[])
 *Parameter   : uint8 LaRteDcm_u_Value[] - Output data array
 *ReturnValue : uint8 - Status (0=OK, 1=Error)
 *Description : Read DID F1A4 data
 *Length      : 1 byte
 *Remark      : Return DID F1A4 data
 *****************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF1A4(uint8 LaRteDcm_u_Value[])
{
    /* DID F1A4 read implementation */
    return 0;
}

/******************************************************************************
 *Function    : uint8 RTE_NET_Dcm_Read_DIDF1A5(uint8 LaRteDcm_u_Value[])
 *Parameter   : uint8 LaRteDcm_u_Value[] - Output data array
 *ReturnValue : uint8 - Status (0=OK, 1=Error)
 *Description : Read DID F1A5 data
 *Length      : 7 bytes
 *Remark      : Return DID F1A5 data
 *****************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF1A5(uint8 LaRteDcm_u_Value[])
{
    /* DID F1A5 read implementation */
    return 0;
}

/******************************************************************************
 *Function    : uint8 RTE_NET_Dcm_Read_DIDF1A9(uint8 LaRteDcm_u_Value[])
 *Parameter   : uint8 LaRteDcm_u_Value[] - Output data array
 *ReturnValue : uint8 - Status (0=OK, 1=Error)
 *Description : Read DID F1A9 data
 *Length      : 2 bytes
 *Remark      : Return DID F1A9 data
 *****************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF1A9(uint8 LaRteDcm_u_Value[])
{
    /* DID F1A9 read implementation */
    return 0;
}

/******************************************************************************
 *Function    : uint8 RTE_NET_Dcm_Read_DIDF1AA(uint8 LaRteDcm_u_Value[])
 *Parameter   : uint8 LaRteDcm_u_Value[] - Output data array
 *ReturnValue : uint8 - Status (0=OK, 1=Error)
 *Description : Read DID F1AA data
 *Length      : 2 bytes
 *Remark      : Return DID F1AA data
 *****************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF1AA(uint8 LaRteDcm_u_Value[])
{
    /* DID F1AA read implementation */
    return 0;
}

/******************************************************************************
 *Function    : uint8 RTE_NET_Dcm_Read_DIDF1AB(uint8 LaRteDcm_u_Value[])
 *Parameter   : uint8 LaRteDcm_u_Value[] - Output data array
 *ReturnValue : uint8 - Status (0=OK, 1=Error)
 *Description : Read DID F1AB data
 *Length      : 6 bytes
 *Remark      : Return DID F1AB data
 *****************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF1AB(uint8 LaRteDcm_u_Value[])
{
    /* DID F1AB read implementation */
    return 0;
}

/*******************************************************************************
*Function            : uint8 RTE_NET_Dcm_Read_DIDF1AC(uint8 LaRteDcm_u_Value[])
*ReturnValue         : uint8
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : LaRteDcm_u_Value            :Output data array
*Return value        : uint8                    :Status (0=OK, 1=Error)
*Description        : Read DID F1AC data
||******************************************************************************/
uint8 RTE_NET_Dcm_Read_DIDF1AC(uint8 LaRteDcm_u_Value[])
{
    /* DID F1AC read implementation */
    return 0;
}

/********************************** Security Access Functions **********************************/

/*******************************************************************************
*Function            : uint32 RTE_NET_Dcm_Get_SecuritySeedValue(void)
*ReturnValue         : uint32
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : uint32                    :Security seed value
*Description        : Get security seed value
|******************************************************************************/
uint32 RTE_NET_Dcm_Get_SecuritySeedValue(void)
{
    /* Security seed value implementation */
    return 0;
}

/*******************************************************************************
*Function            : void RTE_NET_Dcm_Get_SecurityKeyValue(uint32 LaRteDcm_dw_key1, uint32 LaRteDcm_dw_key2)
*ReturnValue         : void
*Parameters(in)        : LaRteDcm_dw_key1            :Key value 1
*Parameters(in)        : LaRteDcm_dw_key2            :Key value 2
*Parameters(out)    : None                        
*Return value        : None
*Description        : Get security key value
|******************************************************************************/
void RTE_NET_Dcm_Get_SecurityKeyValue(uint32 LaRteDcm_dw_key1, uint32 LaRteDcm_dw_key2)
{
    /* Security key value implementation */
}

/*******************************************************************************
*Function            : void RTE_NET_Dcm_AppJumpToFBL(void)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : Jump to FBL Address
|******************************************************************************/
void RTE_NET_Dcm_AppJumpToFBL(void)
{

}

/********************************** DCM  Main Functions **********************************/
/*******************************************************************************
*Function            : void RTE_NET_Dcm_10msMainFunction(void)
*ReturnValue         : void
*Parameters(in)        : None
*Parameters(in)        : None
*Parameters(out)    : None                        
*Return value        : None
*Description        : DEM 10ms main function
|******************************************************************************/
void RTE_NET_Dcm_10msMainFunction(void)
{
    /* DEM 10ms main function implementation */
}
