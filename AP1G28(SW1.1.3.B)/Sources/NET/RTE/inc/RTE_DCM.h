/*******************************************************************************
||  File Name: RTE_DCM.h
||  Description: Header file for AUTOSAR DCM Interface
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

#ifndef RTE_DCM_H
#define RTE_DCM_H
#include "CAEA_Types.h"
/*******************************************************************************
||    Other Header File Inclusion
||******************************************************************************/ 

/*******************************************************************************
||    Macro Definition
||******************************************************************************/

/********************************** DID Length Definitions **********************************/
#define RTE_DCM_DID_F120_LENGTH                   4
#define RTE_DCM_DID_F121_LENGTH                   4
#define RTE_DCM_DID_F122_LENGTH                   4
#define RTE_DCM_DID_F170_LENGTH                   4
#define RTE_DCM_DID_F171_LENGTH                   4
#define RTE_DCM_DID_F189_LENGTH                   15
#define RTE_DCM_DID_F089_LENGTH                   15
#define RTE_DCM_DID_F187_LENGTH                   21
#define RTE_DCM_DID_F18A_LENGTH                   7
#define RTE_DCM_DID_F184_LENGTH                   7
#define RTE_DCM_DID_F1A5_LENGTH                   7
#define RTE_DCM_DID_F18C_LENGTH                   13
#define RTE_DCM_DID_F190_LENGTH                   17
#define RTE_DCM_DID_F188_LENGTH                   20
#define RTE_DCM_DID_F123_LENGTH                   20
#define RTE_DCM_DID_F086_LENGTH                   20
#define RTE_DCM_DID_F087_LENGTH                   20
#define RTE_DCM_DID_F011_LENGTH                   20
#define RTE_DCM_DID_F012_LENGTH                   20
#define RTE_DCM_DID_F010_LENGTH                   34
#define RTE_DCM_DID_F1A3_LENGTH                   8
#define RTE_DCM_DID_F1A4_LENGTH                   1
#define RTE_DCM_DID_F1A9_LENGTH                   2
#define RTE_DCM_DID_F1AA_LENGTH                   2
#define RTE_DCM_DID_F1AB_LENGTH                   6
#define RTE_DCM_DID_F1AC_LENGTH                   5

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
||    Extern variables and functions declaration
||******************************************************************************/

/********************************** DCM Initialization **********************************/
extern void RTE_NET_Dcm_Init(void);

/********************************** DID Read Functions **********************************/
extern uint8 RTE_NET_Dcm_Read_DIDF120(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF121(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF122(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF189(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF089(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF187(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF18A(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF18C(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF190(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF170(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF171(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF184(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF188(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF123(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF086(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF087(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF010(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF011(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF012(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF1A3(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF1A4(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF1A5(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF1A9(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF1AA(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF1AB(uint8 LaRteDcm_u_Value[]);
extern uint8 RTE_NET_Dcm_Read_DIDF1AC(uint8 LaRteDcm_u_Value[]);

/********************************** Security Access Functions **********************************/
extern uint32 RTE_NET_Dcm_Get_SecuritySeedValue(void);
extern void RTE_NET_Dcm_Get_SecurityKeyValue(uint32 LaRteDcm_dw_key1, uint32 LaRteDcm_dw_key2);

/**********************************App Jump to FBL**********************************/
extern void RTE_NET_Dcm_AppJumpToFBL(void);

/********************************** DCM Main Functions **********************************/
extern void RTE_NET_Dcm_10msMainFunction(void);

#endif /* RTE_DCM_H */
