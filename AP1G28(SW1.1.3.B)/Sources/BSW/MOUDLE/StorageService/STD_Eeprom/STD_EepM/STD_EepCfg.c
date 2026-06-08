/* polyspace<MISRA-C3:1.1:Not a defect:Justified> Normal. */
/*******************************************************************************
|  File Name:  STD_EepCfg.c
|  Description:  Implementation of the Eep Config Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           YaJun Xia              CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2018-07-23    01.00.00     XYJ       Creation
| 2019-03-01    01.00.01     CXL       Add QAC
|									   stEepBankCfguc add RomDataAddr
|******************************************************************************/
/* polyspace:begin<MISRA-C3:8.9:Not a defect:Justified> Normal. */
/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_EepCfg.h"
#include "CAEA_Types.h"
/* polyspace:begin<MISRA-C3:8.7:Not a defect:Justified> Normal. */
#if (EEP_MODULE_EN == EEP_ENABLE)
/*******************************************************************************
|    Macro Definition
|******************************************************************************/
/*the corresponding Block length*/


/////////////////////////////////////////////////////////////////BANK0 
#define EEP_BLOCK0_BANK_ID          EEP_BANK0_ID
#define EEP_BLOCK1_BANK_ID			EEP_BANK0_ID
#define EEP_BLOCK2_BANK_ID			EEP_BANK0_ID
#define EEP_BLOCK3_BANK_ID			EEP_BANK0_ID
#define EEP_BLOCK4_BANK_ID			EEP_BANK0_ID
#define EEP_BLOCK5_BANK_ID			EEP_BANK0_ID
#define EEP_BLOCK6_BANK_ID			EEP_BANK0_ID
#define EEP_BLOCK7_BANK_ID			EEP_BANK0_ID
#define EEP_BLOCK8_BANK_ID			EEP_BANK0_ID
#define EEP_BLOCK9_BANK_ID			EEP_BANK0_ID
////////////////////////////////////////////////////////////////BANK1
#define EEP_BLOCK10_BANK_ID			EEP_BANK1_ID
#define EEP_BLOCK11_BANK_ID			EEP_BANK1_ID
#define EEP_BLOCK12_BANK_ID			EEP_BANK1_ID
#define EEP_BLOCK13_BANK_ID			EEP_BANK1_ID
#define EEP_BLOCK14_BANK_ID			EEP_BANK1_ID
#define EEP_BLOCK15_BANK_ID			EEP_BANK1_ID
#define EEP_BLOCK16_BANK_ID			EEP_BANK1_ID
#define EEP_BLOCK17_BANK_ID			EEP_BANK1_ID
////////////////////////////////////////////////////////////////BANK2
#define EEP_BLOCK18_BANK_ID			EEP_BANK2_ID
#define EEP_BLOCK19_BANK_ID			EEP_BANK2_ID
#define EEP_BLOCK20_BANK_ID			EEP_BANK2_ID
#define EEP_BLOCK21_BANK_ID			EEP_BANK2_ID
#define EEP_BLOCK22_BANK_ID			EEP_BANK2_ID
#define EEP_BLOCK23_BANK_ID			EEP_BANK2_ID
#define EEP_BLOCK24_BANK_ID			EEP_BANK2_ID
#define EEP_BLOCK25_BANK_ID			EEP_BANK2_ID
////////////////////////////////////////////////////////////////BANK3
#define EEP_BLOCK26_BANK_ID			EEP_BANK3_ID
#define EEP_BLOCK27_BANK_ID			EEP_BANK3_ID
////////////////////////////////////////////////////////////////BANK4
#define EEP_BLOCK28_BANK_ID			EEP_BANK4_ID
#define EEP_BLOCK29_BANK_ID			EEP_BANK4_ID
#define EEP_BLOCK30_BANK_ID			EEP_BANK4_ID
#define EEP_BLOCK31_BANK_ID			EEP_BANK4_ID
#define EEP_BLOCK32_BANK_ID			EEP_BANK4_ID
#define EEP_BLOCK33_BANK_ID			EEP_BANK4_ID
#define EEP_BLOCK34_BANK_ID			EEP_BANK4_ID
#define EEP_BLOCK35_BANK_ID			EEP_BANK4_ID
////////////////////////////////////////////////////////////////BANK5
#define EEP_BLOCK36_BANK_ID			EEP_BANK5_ID
#define EEP_BLOCK37_BANK_ID			EEP_BANK5_ID
#define EEP_BLOCK38_BANK_ID			EEP_BANK5_ID
////////////////////////////////////////////////////////////////BANK6
#define EEP_BLOCK39_BANK_ID			EEP_BANK6_ID
#define EEP_BLOCK40_BANK_ID			EEP_BANK6_ID
#define EEP_BLOCK41_BANK_ID			EEP_BANK6_ID







/*the corresponding Block length*/

/////////////////////////////////////////////////////////////////BANK0 
#define EEP_BLOCK0_LENGTH          EEP_BLOCK_DIDF089_LEN   
#define EEP_BLOCK1_LENGTH 		   EEP_BLOCK_DIDF18C_LEN
#define EEP_BLOCK2_LENGTH 		   EEP_BLOCK_DIDF190_LEN
#define EEP_BLOCK3_LENGTH 		   EEP_BLOCK_DIDF184_LEN
#define EEP_BLOCK4_LENGTH 		   EEP_BLOCK_DIDF1F0_LEN
#define EEP_BLOCK5_LENGTH          EEP_BLOCK_DIDF1F6_LEN
#define EEP_BLOCK6_LENGTH          EEP_BLOCK_descSecureFAAflag_LEN
#define EEP_BLOCK7_LENGTH          EEP_BLOCK_descSecureFBLflag_LEN
#define EEP_BLOCK8_LENGTH          EEP_BLOCK_UNUSED0_LEN
#define EEP_BLOCK9_LENGTH          EEP_BLOCK_RESERVED0_FLAG_LEN
////////////////////////////////////////////////////////////////BANK1
#define EEP_BLOCK10_LENGTH          EEP_BLOCK_E6B8_87_LEN
#define EEP_BLOCK11_LENGTH          EEP_BLOCK_E6BB_88_LEN		
#define EEP_BLOCK12_LENGTH          EEP_BLOCK_97F8_16_LEN
#define EEP_BLOCK13_LENGTH          EEP_BLOCK_97F8_17_LEN
#define EEP_BLOCK14_LENGTH          EEP_BLOCK_97F8_06_LEN
#define EEP_BLOCK15_LENGTH          EEP_BLOCK_97FB_18_LEN		
#define EEP_BLOCK16_LENGTH          EEP_BLOCK_UNUSED1_LEN
#define EEP_BLOCK17_LENGTH          EEP_BLOCK_RESERVED1_FLAG_LEN
////////////////////////////////////////////////////////////////BANK2
#define EEP_BLOCK18_LENGTH          EEP_BLOCK_97FB_19_LEN
#define EEP_BLOCK19_LENGTH          EEP_BLOCK_97F8_4B_LEN		
#define EEP_BLOCK20_LENGTH          EEP_BLOCK_97FC_19_LEN
#define EEP_BLOCK21_LENGTH          EEP_BLOCK_97FC_18_LEN
#define EEP_BLOCK22_LENGTH          EEP_BLOCK_97FD_19_LEN
#define EEP_BLOCK23_LENGTH          EEP_BLOCK_97FD_18_LEN
#define EEP_BLOCK24_LENGTH          EEP_BLOCK_UNUSED2_LEN
#define EEP_BLOCK25_LENGTH          EEP_BLOCK_RESERVED2_FLAG_LEN
////////////////////////////////////////////////////////////////BANK3
#define EEP_BLOCK26_LENGTH          EEP_BLOCK_Fridge_App_LEN
#define EEP_BLOCK27_LENGTH          EEP_BLOCK_RESERVED3_FLAG_LEN
////////////////////////////////////////////////////////////////BANK4
#define EEP_BLOCK28_LENGTH          EEP_BLOCK_97F8_09_LEN
#define EEP_BLOCK29_LENGTH          EEP_BLOCK_97F9_09_LEN		
#define EEP_BLOCK30_LENGTH          EEP_BLOCK_97F8_71_LEN
#define EEP_BLOCK31_LENGTH          EEP_BLOCK_97F8_49_LEN
#define EEP_BLOCK32_LENGTH          EEP_BLOCK_97F9_49_LEN
#define EEP_BLOCK33_LENGTH          EEP_BLOCK_97FA_49_LEN
#define EEP_BLOCK34_LENGTH          EEP_BLOCK_97FA_09_LEN
#define EEP_BLOCK35_LENGTH          EEP_BLOCK_RESERVED4_FLAG_LEN
////////////////////////////////////////////////////////////////BANK5
#define EEP_BLOCK36_LENGTH          EEP_BLOCK_DIDF1FA_LEN
#define EEP_BLOCK37_LENGTH          EEP_BLOCK_UNUSED5_LEN
#define EEP_BLOCK38_LENGTH          EEP_BLOCK_RESERVED5_FLAG_LEN
////////////////////////////////////////////////////////////////BANK6
#define EEP_BLOCK39_LENGTH          EEP_BLOCK_DIDF1FC_LEN
#define EEP_BLOCK40_LENGTH          EEP_BLOCK_UNUSED6_LEN
#define EEP_BLOCK41_LENGTH          EEP_BLOCK_RESERVED6_FLAG_LEN





/*the corresponding Block address*/

////////////////////////////////////////////////////////////bank0
#define EEP_BLOCK0_ADD_OFFSET		(1u + 0u)  
#define EEP_BLOCK1_ADD_OFFSET		(1u + 15u)  
#define EEP_BLOCK2_ADD_OFFSET		(1u + 28u) 
#define EEP_BLOCK3_ADD_OFFSET		(1u + 45u) 
#define EEP_BLOCK4_ADD_OFFSET		(1u + 52u) 
#define EEP_BLOCK5_ADD_OFFSET		(1u + 54u)  
#define EEP_BLOCK6_ADD_OFFSET		(1u + 64u)  
#define EEP_BLOCK7_ADD_OFFSET		(1u + 65u) 
#define EEP_BLOCK8_ADD_OFFSET		(1u + 66u) 
#define EEP_BLOCK9_ADD_OFFSET		(1u + 91u)  
////////////////////////////////////////////////////////////bank1
#define EEP_BLOCK10_ADD_OFFSET		(1u + 0u)  
#define EEP_BLOCK11_ADD_OFFSET		(1u + 13u)  
#define EEP_BLOCK12_ADD_OFFSET		(1u + 26u) 
#define EEP_BLOCK13_ADD_OFFSET		(1u + 39u)  
#define EEP_BLOCK14_ADD_OFFSET		(1u + 52u)  
#define EEP_BLOCK15_ADD_OFFSET		(1u + 65u)  
#define EEP_BLOCK16_ADD_OFFSET		(1u + 78u)  
#define EEP_BLOCK17_ADD_OFFSET		(1u + 91u) 
////////////////////////////////////////////////////////////bank2
#define EEP_BLOCK18_ADD_OFFSET		(1u + 0u)  
#define EEP_BLOCK19_ADD_OFFSET		(1u + 13u)  
#define EEP_BLOCK20_ADD_OFFSET		(1u + 26u) 
#define EEP_BLOCK21_ADD_OFFSET		(1u + 39u)  
#define EEP_BLOCK22_ADD_OFFSET		(1u + 52u)  
#define EEP_BLOCK23_ADD_OFFSET		(1u + 65u)  
#define EEP_BLOCK24_ADD_OFFSET		(1u + 78u)  
#define EEP_BLOCK25_ADD_OFFSET		(1u + 91u)  
////////////////////////////////////////////////////////////bank3
#define EEP_BLOCK26_ADD_OFFSET		(1u + 0u)  
#define EEP_BLOCK27_ADD_OFFSET		(1u + 91u)  
////////////////////////////////////////////////////////////bank4
#define EEP_BLOCK28_ADD_OFFSET		(1u + 0u)  
#define EEP_BLOCK29_ADD_OFFSET		(1u + 13u)  
#define EEP_BLOCK30_ADD_OFFSET		(1u + 26u) 
#define EEP_BLOCK31_ADD_OFFSET		(1u + 39u)  
#define EEP_BLOCK32_ADD_OFFSET		(1u + 52u)  
#define EEP_BLOCK33_ADD_OFFSET		(1u + 65u)  
#define EEP_BLOCK34_ADD_OFFSET		(1u + 78u)  
#define EEP_BLOCK35_ADD_OFFSET		(1u + 91u)  
////////////////////////////////////////////////////////////bank5
#define EEP_BLOCK36_ADD_OFFSET		(1u + 0u)  
#define EEP_BLOCK37_ADD_OFFSET		(1u + 90u)  
#define EEP_BLOCK38_ADD_OFFSET		(1u + 91u) 
////////////////////////////////////////////////////////////bank6
#define EEP_BLOCK39_ADD_OFFSET		(1u + 0u)  
#define EEP_BLOCK40_ADD_OFFSET		(1u + 20u)  
#define EEP_BLOCK41_ADD_OFFSET		(1u + 91u) 

/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Global NVM KAM Declaration
|******************************************************************************/
/*define the Dflash block Kam buff*/
static uint8 EEPM_CODE_KAM ucEepBank0Kam1Array[EEP_BANK0_DATA_LEN];
static uint8 EEPM_CODE_KAM ucEepBank0Kam2Array[EEP_BANK0_DATA_LEN];
static uint8 EEPM_CODE_KAM ucEepBank0Kam3Array[EEP_BANK0_DATA_LEN];

static uint8 EEPM_CODE_KAM ucEepBank1Kam1Array[EEP_BANK1_DATA_LEN];
static uint8 EEPM_CODE_KAM ucEepBank1Kam2Array[EEP_BANK1_DATA_LEN];
static uint8 EEPM_CODE_KAM ucEepBank1Kam3Array[EEP_BANK1_DATA_LEN];

static uint8 EEPM_CODE_KAM ucEepBank2Kam1Array[EEP_BANK2_DATA_LEN];
static uint8 EEPM_CODE_KAM ucEepBank2Kam2Array[EEP_BANK2_DATA_LEN];
static uint8 EEPM_CODE_KAM ucEepBank2Kam3Array[EEP_BANK2_DATA_LEN];

static uint8 EEPM_CODE_KAM ucEepBank3Kam1Array[EEP_BANK3_DATA_LEN];
static uint8 EEPM_CODE_KAM ucEepBank3Kam2Array[EEP_BANK3_DATA_LEN];
static uint8 EEPM_CODE_KAM ucEepBank3Kam3Array[EEP_BANK3_DATA_LEN];

static uint8 EEPM_CODE_KAM ucEepBank4Kam1Array[EEP_BANK4_DATA_LEN];
static uint8 EEPM_CODE_KAM ucEepBank4Kam2Array[EEP_BANK4_DATA_LEN];
static uint8 EEPM_CODE_KAM ucEepBank4Kam3Array[EEP_BANK4_DATA_LEN];

static uint8 EEPM_CODE_KAM ucEepBank5Kam1Array[EEP_BANK5_DATA_LEN];
static uint8 EEPM_CODE_KAM ucEepBank5Kam2Array[EEP_BANK5_DATA_LEN];
static uint8 EEPM_CODE_KAM ucEepBank5Kam3Array[EEP_BANK5_DATA_LEN];

static uint8 EEPM_CODE_KAM ucEepBank6Kam1Array[EEP_BANK6_DATA_LEN];
static uint8 EEPM_CODE_KAM ucEepBank6Kam2Array[EEP_BANK6_DATA_LEN];
static uint8 EEPM_CODE_KAM ucEepBank6Kam3Array[EEP_BANK6_DATA_LEN];

static uint8 EEPM_CODE_KAM ucEepBank7Kam1Array[EEP_BANK7_DATA_LEN];
static uint8 EEPM_CODE_KAM ucEepBank7Kam2Array[EEP_BANK7_DATA_LEN];
static uint8 EEPM_CODE_KAM ucEepBank7Kam3Array[EEP_BANK7_DATA_LEN];



/*******************************************************************************
|    local variables Declaration
|******************************************************************************/
/*define the Dflash block Ram buff*/
uint8 EEPM_CODE_RAM ucEepBank0RamArray[EEP_BANK0_DATA_LEN];
uint8 EEPM_CODE_RAM ucEepBank1RamArray[EEP_BANK1_DATA_LEN];
uint8 EEPM_CODE_RAM ucEepBank2RamArray[EEP_BANK2_DATA_LEN];
uint8 EEPM_CODE_RAM ucEepBank3RamArray[EEP_BANK3_DATA_LEN];
uint8 EEPM_CODE_RAM ucEepBank4RamArray[EEP_BANK4_DATA_LEN];
uint8 EEPM_CODE_RAM ucEepBank5RamArray[EEP_BANK5_DATA_LEN];
uint8 EEPM_CODE_RAM ucEepBank6RamArray[EEP_BANK6_DATA_LEN];
uint8 EEPM_CODE_RAM ucEepBank7RamArray[EEP_BANK7_DATA_LEN];


/*******************************************************************************
|    Table Const Definition
|******************************************************************************/
/*define the Dflash block Rom buff*/
const uint8 ucEepBank0RomArray[EEP_BANK0_DATA_LEN]=
{
    EEP_BANK_ROM_DEFAULT_FLAG,
	'H','W','A','.','0','.','1',0u,0u,0u,0u,0u,0u,0u,0u,	                       //F089_LEN = 15
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0x14u,0x01u,0x01u,			                   //F18C_LEN = 13
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,		                       //F190_LEN =17
	0x14u,0x01u,0x01u,0u,0u,0u,0u,									                       //F184_LEN =7
	0u,0u,													                                                       //F1F0_LEN =2
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,							                       //F1F6_LEN =10
	0u,														                                                           //FAA	   =1
	0u,														                                                           //FBL	   =1
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,	   //UNUSED0  =25
	EEP_BANK_RERVED_FLAG1,EEP_BANK_RERVED_FLAG2
};

const uint8 ucEepBank1RomArray[EEP_BANK1_DATA_LEN]=
{
    EEP_BANK_ROM_DEFAULT_FLAG,
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//DTC_E6B8_87
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//DTC_E6BB_88
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//DTC_97F8_16
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//DTC_97F8_17
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//DTC_97F8_06
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//DTC_97FB_18
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//UNUSED1 =13									
	EEP_BANK_RERVED_FLAG1,EEP_BANK_RERVED_FLAG2
};

const uint8 ucEepBank2RomArray[EEP_BANK2_DATA_LEN]=
{
    EEP_BANK_ROM_DEFAULT_FLAG,
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//DTC_97FB_19
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//DTC_97F8_4B
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//DTC_97FC_19
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//DTC_97FC_18
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//DTC_97FD_19
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,     		//DTC_97FD_18
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//UNUSED2 =13									
	EEP_BANK_RERVED_FLAG1,EEP_BANK_RERVED_FLAG2
};

const uint8 ucEepBank3RomArray[EEP_BANK3_DATA_LEN]=
{
    EEP_BANK_ROM_DEFAULT_FLAG,
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u, 		     //Fridge_App
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,					
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,		
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,					
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,	
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,	
	EEP_BANK_RERVED_FLAG1,EEP_BANK_RERVED_FLAG2
};
const uint8 ucEepBank4RomArray[EEP_BANK4_DATA_LEN]=
{
    EEP_BANK_ROM_DEFAULT_FLAG,
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//DTC_97F8_09
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//DTC_97F9_09
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//DTC_97F8_71
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//DTC_97F8_49
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//DTC_97F9_49
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,     		//DTC_97FA_49
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,				//DTC_97FA_09									
	EEP_BANK_RERVED_FLAG1,EEP_BANK_RERVED_FLAG2
};

const uint8 ucEepBank5RomArray[EEP_BANK5_DATA_LEN]=
{
    EEP_BANK_ROM_DEFAULT_FLAG,
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,    //DID_F1FA = 90
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,																					
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,									
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u, 
	0u,	                                                                                          //UNUSED5  =1
	EEP_BANK_RERVED_FLAG1,EEP_BANK_RERVED_FLAG2
};

const uint8 ucEepBank6RomArray[EEP_BANK6_DATA_LEN]=
{
    EEP_BANK_ROM_DEFAULT_FLAG,
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,  //DID_F1FC = 20
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,					
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,	
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,																						
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,																					//	   =1
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,		              //UNUSED0  =71
	EEP_BANK_RERVED_FLAG1,EEP_BANK_RERVED_FLAG2
};

const uint8 ucEepBank7RomArray[EEP_BANK7_DATA_LEN]=
{
    EEP_BANK_ROM_DEFAULT_FLAG,
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,					// = 13
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,		// =17
	0u,0u,0u,0u,0u,0u,0u,									// =7
	0u,0u,													// =2
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,							// =10
	0u,														//	   =1
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,		//UNUSED0  =5
	EEP_BANK_RERVED_FLAG1,EEP_BANK_RERVED_FLAG2
};
/************************************************/


/*************************************************/


const Eep_BankCfg stEepBankCfg[EEP_BANK_MAX_NUM] =
{
    {/*0*/
        EEP_BANK0_DATA_LEN,
        EEP_BANK_CLEAR_ON|EEP_BANK_KAM_BACKUP_ON,
        EEP_IN_EEP_DEV,
        ucEepBank0RamArray,
        ucEepBank0Kam1Array,
        ucEepBank0Kam2Array,
		ucEepBank0Kam3Array,
		ucEepBank0RomArray /*  pointer to the ROM buffer  */
    },
 	{/*1*/
		EEP_BANK1_DATA_LEN,
		EEP_BANK_KAM_BACKUP_ON,
		EEP_IN_EEP_DEV,
		ucEepBank1RamArray,
		ucEepBank1Kam1Array,
		ucEepBank1Kam2Array,
		ucEepBank1Kam3Array,
		ucEepBank1RomArray /*  pointer to the ROM buffer  */
	},
	{/*2*/
		EEP_BANK2_DATA_LEN,
		EEP_BANK_KAM_BACKUP_ON,
		EEP_IN_EEP_DEV,
		ucEepBank2RamArray,
		ucEepBank2Kam1Array,
		ucEepBank2Kam2Array,
		ucEepBank2Kam3Array,
		ucEepBank2RomArray /*  pointer to the ROM buffer  */
	},
	{/*3*/
		EEP_BANK3_DATA_LEN,
		EEP_BANK_CLEAR_ON|EEP_BANK_KAM_BACKUP_ON,
		EEP_IN_EEP_DEV,
		ucEepBank3RamArray,
		ucEepBank3Kam1Array,
		ucEepBank3Kam2Array,
		ucEepBank3Kam3Array,
		ucEepBank3RomArray /*  pointer to the ROM buffer  */
	},
    {/*4*/
		EEP_BANK4_DATA_LEN,
		EEP_BANK_CLEAR_ON|EEP_BANK_KAM_BACKUP_ON,
		EEP_IN_EEP_DEV,
		ucEepBank4RamArray,
		ucEepBank4Kam1Array,
		ucEepBank4Kam2Array,
		ucEepBank4Kam3Array,
		ucEepBank4RomArray /*  pointer to the ROM buffer  */
	},
	{/*5*/
		EEP_BANK5_DATA_LEN,
		EEP_BANK_CLEAR_ON|EEP_BANK_KAM_BACKUP_ON,
		EEP_IN_EEP_DEV,
		ucEepBank5RamArray,
		ucEepBank5Kam1Array,
		ucEepBank5Kam2Array,
		ucEepBank5Kam3Array,
		ucEepBank5RomArray /*  pointer to the ROM buffer  */
	},
	{/*6*/
		EEP_BANK6_DATA_LEN,
		EEP_BANK_CLEAR_ON|EEP_BANK_KAM_BACKUP_ON,
		EEP_IN_EEP_DEV,
		ucEepBank6RamArray,
		ucEepBank6Kam1Array,
		ucEepBank6Kam2Array,
		ucEepBank6Kam3Array,
		ucEepBank6RomArray
	},
	{/*7*/
		EEP_BANK7_DATA_LEN,
		EEP_BANK_CLEAR_ON|EEP_BANK_KAM_BACKUP_ON,
		EEP_IN_EEP_DEV,
		ucEepBank7RamArray,
		ucEepBank7Kam1Array,
		ucEepBank7Kam2Array,
		ucEepBank7Kam3Array,
		ucEepBank7RomArray
	},
 	
};

const Eep_BlockIDCfg stEepBlockCfg[EEP_BLOCK_MAX_NUM] =
{
    {/*0*/
        EEP_BLOCK0_ADD_OFFSET,
        EEP_BLOCK0_LENGTH,
        EEP_BLOCK0_BANK_ID
    },
    {/*1*/
		EEP_BLOCK1_ADD_OFFSET,
		EEP_BLOCK1_LENGTH,
		EEP_BLOCK1_BANK_ID
	},
	{/*2*/
		EEP_BLOCK2_ADD_OFFSET,
		EEP_BLOCK2_LENGTH,
		EEP_BLOCK2_BANK_ID	
	},
	{/*3*/
		EEP_BLOCK3_ADD_OFFSET,
		EEP_BLOCK3_LENGTH,
		EEP_BLOCK3_BANK_ID
	},
	{/*4*/
		EEP_BLOCK4_ADD_OFFSET,
		EEP_BLOCK4_LENGTH,
		EEP_BLOCK4_BANK_ID
	},
	{/*5*/
		EEP_BLOCK5_ADD_OFFSET,
		EEP_BLOCK5_LENGTH,
		EEP_BLOCK5_BANK_ID
	},
    {/*6*/
		EEP_BLOCK6_ADD_OFFSET,
		EEP_BLOCK6_LENGTH,
		EEP_BLOCK6_BANK_ID
	},
    {/*7*/
		EEP_BLOCK7_ADD_OFFSET,
		EEP_BLOCK7_LENGTH,
		EEP_BLOCK7_BANK_ID
	},
	{/*8*/
		EEP_BLOCK8_ADD_OFFSET,
		EEP_BLOCK8_LENGTH,
		EEP_BLOCK8_BANK_ID
	},
	{/*9*/
		EEP_BLOCK9_ADD_OFFSET,
		EEP_BLOCK9_LENGTH,
		EEP_BLOCK9_BANK_ID
	},
	{/*10*/
		EEP_BLOCK10_ADD_OFFSET,
		EEP_BLOCK10_LENGTH,
		EEP_BLOCK10_BANK_ID
	},
	{/*11*/
		EEP_BLOCK11_ADD_OFFSET,
		EEP_BLOCK11_LENGTH,
		EEP_BLOCK11_BANK_ID
	}, 
	{/*12*/
		EEP_BLOCK12_ADD_OFFSET,
		EEP_BLOCK12_LENGTH,
		EEP_BLOCK12_BANK_ID
	}, 
	{/*13*/
		EEP_BLOCK13_ADD_OFFSET,
		EEP_BLOCK13_LENGTH,
		EEP_BLOCK13_BANK_ID
	}, 
	{/*14*/
		EEP_BLOCK14_ADD_OFFSET,
		EEP_BLOCK14_LENGTH,
		EEP_BLOCK14_BANK_ID
	}, 
	{/*15*/
		EEP_BLOCK15_ADD_OFFSET,
		EEP_BLOCK15_LENGTH,
		EEP_BLOCK15_BANK_ID
	}, 
	{/*16*/
		EEP_BLOCK16_ADD_OFFSET,
		EEP_BLOCK16_LENGTH,
		EEP_BLOCK16_BANK_ID
	}, 	
	{/*17*/
		EEP_BLOCK17_ADD_OFFSET,
		EEP_BLOCK17_LENGTH,
		EEP_BLOCK17_BANK_ID
	},
	{/*18*/
		EEP_BLOCK18_ADD_OFFSET,
		EEP_BLOCK18_LENGTH,
		EEP_BLOCK18_BANK_ID
	},
	{/*19*/
		EEP_BLOCK19_ADD_OFFSET,
		EEP_BLOCK19_LENGTH,
		EEP_BLOCK19_BANK_ID
	}, 
	{/*20*/
		EEP_BLOCK20_ADD_OFFSET,
		EEP_BLOCK20_LENGTH,
		EEP_BLOCK20_BANK_ID
	}, 
	{/*21*/
		EEP_BLOCK21_ADD_OFFSET,
		EEP_BLOCK21_LENGTH,
		EEP_BLOCK21_BANK_ID
	}, 
	{/*22*/
		EEP_BLOCK22_ADD_OFFSET,
		EEP_BLOCK22_LENGTH,
		EEP_BLOCK22_BANK_ID
	}, 
	{/*23*/
		EEP_BLOCK23_ADD_OFFSET,
		EEP_BLOCK23_LENGTH,
		EEP_BLOCK23_BANK_ID
	}, 
	{/*24*/
		EEP_BLOCK24_ADD_OFFSET,
		EEP_BLOCK24_LENGTH,
		EEP_BLOCK24_BANK_ID
	}, 
	{/*25*/
		EEP_BLOCK25_ADD_OFFSET,
		EEP_BLOCK25_LENGTH,
		EEP_BLOCK25_BANK_ID
	}, 
	{/*26*/
		EEP_BLOCK26_ADD_OFFSET,
		EEP_BLOCK26_LENGTH,
		EEP_BLOCK26_BANK_ID
	},
	{/*27*/
		EEP_BLOCK27_ADD_OFFSET,
		EEP_BLOCK27_LENGTH,
		EEP_BLOCK27_BANK_ID
	}, 
	{/*28*/
		EEP_BLOCK28_ADD_OFFSET,
		EEP_BLOCK28_LENGTH,
		EEP_BLOCK28_BANK_ID
	}, 
	{/*29*/
		EEP_BLOCK29_ADD_OFFSET,
		EEP_BLOCK29_LENGTH,
		EEP_BLOCK29_BANK_ID
	}, 
	{/*30*/
		EEP_BLOCK30_ADD_OFFSET,
		EEP_BLOCK30_LENGTH,
		EEP_BLOCK30_BANK_ID
	}, 
	{/*31*/
		EEP_BLOCK31_ADD_OFFSET,
		EEP_BLOCK31_LENGTH,
		EEP_BLOCK31_BANK_ID
	}, 
	{/*32*/
		EEP_BLOCK32_ADD_OFFSET,
		EEP_BLOCK32_LENGTH,
		EEP_BLOCK32_BANK_ID
	},
	{/*33*/
		EEP_BLOCK33_ADD_OFFSET,
		EEP_BLOCK33_LENGTH,
		EEP_BLOCK33_BANK_ID
	},
	{/*34*/
		EEP_BLOCK34_ADD_OFFSET,
		EEP_BLOCK34_LENGTH,
		EEP_BLOCK34_BANK_ID
	}, 
	{/*35*/
		EEP_BLOCK35_ADD_OFFSET,
		EEP_BLOCK35_LENGTH,
		EEP_BLOCK35_BANK_ID
	},
	{/*36*/
		EEP_BLOCK36_ADD_OFFSET,
		EEP_BLOCK36_LENGTH,
		EEP_BLOCK36_BANK_ID
	},
	{/*37*/
		EEP_BLOCK37_ADD_OFFSET,
		EEP_BLOCK37_LENGTH,
		EEP_BLOCK37_BANK_ID
	}, 
	{/*38*/
		EEP_BLOCK38_ADD_OFFSET,
		EEP_BLOCK38_LENGTH,
		EEP_BLOCK38_BANK_ID
	},
	{/*39*/
		EEP_BLOCK39_ADD_OFFSET,
		EEP_BLOCK39_LENGTH,
		EEP_BLOCK39_BANK_ID
	},
	{/*40*/
		EEP_BLOCK40_ADD_OFFSET,
		EEP_BLOCK40_LENGTH,
		EEP_BLOCK40_BANK_ID
	}, 
	{/*41*/
		EEP_BLOCK41_ADD_OFFSET,
		EEP_BLOCK41_LENGTH,
		EEP_BLOCK41_BANK_ID
	},
};
/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/

/*******************************************************************************
|    Extern variables and functions declaration
|******************************************************************************/

/*******************************************************************************
|    Extern variables and functions declaration
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/
void EEPCFG_InitRamMemory( void )
{
	uint16 len;
	for(len = 0u;len < (uint16)EEP_BANK0_DATA_LEN;len++)
	{
		ucEepBank0RamArray[len] = 0u;
	}

	for(len = 0u;len < (uint16)EEP_BANK1_DATA_LEN;len++)
	{
		ucEepBank1RamArray[len] = 0u;
	}

	for(len = 0u;len < (uint16)EEP_BANK2_DATA_LEN;len++)
	{
		ucEepBank2RamArray[len] = 0u;
	}

	for(len = 0u;len < (uint16)EEP_BANK3_DATA_LEN;len++)
	{
		ucEepBank3RamArray[len] = 0u;
	}

	for(len = 0u;len < (uint16)EEP_BANK4_DATA_LEN;len++)
	{
		ucEepBank4RamArray[len] = 0u;
	}

	for(len = 0u;len < (uint16)EEP_BANK5_DATA_LEN;len++)
	{
		ucEepBank5RamArray[len] = 0u;
	}
	for(len = 0u;len < (uint16)EEP_BANK6_DATA_LEN;len++)
	{
		ucEepBank6RamArray[len] = 0u;
	}
	for(len = 0u;len < EEP_BANK7_DATA_LEN;len++)
    {
        ucEepBank7RamArray[len] = 0u;
    }

}
void EEPCFG_InitKamMemory( void )
{
	uint16 len;
	for(len = 0u;len < (uint16)EEP_BANK0_DATA_LEN;len++)
	{
		ucEepBank0Kam1Array[len] = 0u;
		ucEepBank0Kam2Array[len] = 0u;
		ucEepBank0Kam3Array[len] = 0u;
	}

	for(len = 0u;len < (uint16)EEP_BANK1_DATA_LEN;len++)
	{
		ucEepBank1Kam1Array[len] = 0u;
		ucEepBank1Kam2Array[len] = 0u;
		ucEepBank1Kam3Array[len] = 0u;
	}

	for(len = 0u;len < (uint16)EEP_BANK2_DATA_LEN;len++)
	{
		ucEepBank2Kam1Array[len] = 0u;
		ucEepBank2Kam2Array[len] = 0u;
		ucEepBank2Kam3Array[len] = 0u;
	}

	for(len = 0u;len < (uint16)EEP_BANK3_DATA_LEN;len++)
	{
		ucEepBank3Kam1Array[len] = 0u;
		ucEepBank3Kam2Array[len] = 0u;
		ucEepBank3Kam3Array[len] = 0u;
	}

	for(len = 0u;len < (uint16)EEP_BANK4_DATA_LEN;len++)
	{
		ucEepBank4Kam1Array[len] = 0u;
		ucEepBank4Kam2Array[len] = 0u;
		ucEepBank4Kam3Array[len] = 0u;
	}

	for(len = 0u;len < (uint16)EEP_BANK5_DATA_LEN;len++)
	{
		ucEepBank5Kam1Array[len] = 0u;
		ucEepBank5Kam2Array[len] = 0u;
		ucEepBank5Kam3Array[len] = 0u;
	}

	for(len = 0u;len < (uint16)EEP_BANK6_DATA_LEN;len++)
	{
		ucEepBank6Kam1Array[len] = 0u;
		ucEepBank6Kam2Array[len] = 0u;
		ucEepBank6Kam3Array[len] = 0u;
    }
	for(len = 0u;len < EEP_BANK7_DATA_LEN;len++)
    {
        ucEepBank7Kam1Array[len] = 0u;
        ucEepBank7Kam2Array[len] = 0u;
        ucEepBank7Kam3Array[len] = 0u;
    }

}
/* polyspace:end<MISRA-C3:8.7:Not a defect:Justified> Normal. */
/* polyspace:end<MISRA-C3:8.9:Not a defect:Justified> Normal. */
#endif/*(EEP_MODULE_EN == EEP_ENABLE)*/
/*EOF*/
