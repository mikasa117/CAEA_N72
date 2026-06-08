/*******************************************************************************
|  File Name:  STD_EepCfg.h
|  Description:  Implementation of the NvM_App Management
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
| 2019-03-01    01.00.01     CXL	   Eep_BankCfg add ucRomDataAddr;
|******************************************************************************/

#if !defined (_STD_EEPCFG_H)
#define _STD_EEPCFG_H

#include "CAEA_Types.h"

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_BtrM.h"
/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define EEP_DISABLE                          (0u)
#define EEP_ENABLE                           (1u)
#define EEP_MODULE_EN                       EEP_ENABLE

#if (EEP_MODULE_EN == EEP_ENABLE)

#define EEPM_CODE_RAM   //__attribute__ ((section(".KAM_APP")))
#define EEPM_CODE_KAM   //__attribute__ ((section(".KAM_APP")))
/*eeprom storage type Enable*/
#define EEP_TYPE_DFLASH_ENABLE              EEP_DISABLE
#define EEP_TYPE_EXT_EEP_ENABLE             EEP_DISABLE
#define EEP_TYPE_FLEXMEM_ENABLE             EEP_ENABLE

/*eeprom storage type*/
#define EEP_STORAGE_TYPE_DFLASH             (0u)
#define EEP_STORAGE_TYPE_EXT_EEP            (1u)
#define EEP_STORAGE_TYPE_FLEXMEM            (2u)

#define EEP_SUPPORT_DEBUG

#define EEP_BANK_FLAG_OFF                   (0x00u)
#define EEP_BANK_KAM_BACKUP_ON              (0x01u)
#define EEP_BANK_CLEAR_ON                   (0x02u)

/*config Kam backup function*/
#define EEP_KAM_BACKUP_CLASS                EEP_ENABLE


#define EEPM_SERVICE_READALL                (12u)

/*Dflash NvM total ID num*/
#define DFLASH_ID_TOTAL_NUMBER              (55U)
/*EEPROm NvM total ID num*/
#define EEP_ID_TOTAL_NUMBER                 (0U) 
/*Dflash NVM ID offset*/
#define DFLASH_ID_OFFSET                    (2u)
/*Eeprom NVM ID offset*/
#define EEP_ID_OFFSET                       (0x200u)

/*the corresponding Bank ID*/
#define EEP_BANK0_ID                        (0u)
#define EEP_BANK1_ID                        (1u)
#define EEP_BANK2_ID                        (2u)
#define EEP_BANK3_ID                        (3u)
#define EEP_BANK4_ID                        (4u)
#define EEP_BANK5_ID                        (5u)
#define EEP_BANK6_ID                        (6u)
#define EEP_BANK7_ID                        (7u)

#define EEP_BANK_MAX_NUM                    (8u)

/*the corresponding Bank length*/
#define EEP_BANK0_DATA_LEN                  (94u)
#define EEP_BANK1_DATA_LEN                  (94u)
#define EEP_BANK2_DATA_LEN                  (94u)
#define EEP_BANK3_DATA_LEN                  (94u)
#define EEP_BANK4_DATA_LEN                  (94u)
#define EEP_BANK5_DATA_LEN					(94u)
#define EEP_BANK6_DATA_LEN					(94u)
#define EEP_BANK7_DATA_LEN					(94u)


#define EEP_BANK_RAM_FLAG                   (0xE5u)
#define EEP_BANK_ROM_DEFAULT_FLAG           (0xEAu)

#define EEP_BANK_RERVED_FLAG1               (0xA5u)       
#define EEP_BANK_RERVED_FLAG2               (0x5Au) 
/*the corresponding Block ID*/ 


////////////////////// BANK0
#define EEP_BLOCK_DIDF089_ID					(0u)
#define EEP_BLOCK_DIDF18C_ID					(1u)
#define EEP_BLOCK_DIDF190_ID					(2u)
#define EEP_BLOCK_DIDF184_ID					(3u)
#define EEP_BLOCK_DIDF1F0_ID					(4u)
#define EEP_BLOCK_DIDF1F6_ID			    	(5u)
#define EEP_BLOCK_descSecureFAAflag_ID			(6u)
#define EEP_BLOCK_descSecureFBLflag_ID			(7u)
#define EEP_BLOCK_UNUSED0_ID			    	(8u)
#define EEP_BLOCK_RESERVED0_FLAG_ID			    (9u)
///////////////////////BANK1
#define EEP_BLOCK_E6B8_87_ID					(10u)
#define EEP_BLOCK_E6BB_88_ID 					(11u)
#define EEP_BLOCK_97F8_16_ID 					(12u)
#define EEP_BLOCK_97F8_17_ID			        (13u)
#define EEP_BLOCK_97F8_06_ID					(14u)
#define EEP_BLOCK_97FB_18_ID 					(15u)
#define EEP_BLOCK_UNUSED1_ID 					(16u)
#define EEP_BLOCK_RESERVED1_FLAG_ID			    (17u)
///////////////////////BANK2
#define EEP_BLOCK_97FB_19_ID					(18u)
#define EEP_BLOCK_97F8_4B_ID 					(19u)
#define EEP_BLOCK_97FC_19_ID 					(20u)
#define EEP_BLOCK_97FC_18_ID 					(21u)
#define EEP_BLOCK_97FD_19_ID 					(22u)
#define EEP_BLOCK_97FD_18_ID			        (23u)
#define EEP_BLOCK_UNUSED2_ID			        (24u)
#define EEP_BLOCK_RESERVED2_FLAG_ID				(25u)
///////////////////////BANK3
#define EEP_BLOCK_Fridge_App_ID					(26u)	
#define EEP_BLOCK_RESERVED3_FLAG_ID				(27u)
///////////////////////BANK4
#define EEP_BLOCK_97F8_09_ID					(28u)
#define EEP_BLOCK_97F9_09_ID					(29u)
#define EEP_BLOCK_97F8_71_ID					(30u)
#define EEP_BLOCK_97F8_49_ID					(31u)
#define EEP_BLOCK_97F9_49_ID					(32u)
#define EEP_BLOCK_97FA_49_ID					(33u)	
#define EEP_BLOCK_97FA_09_ID			        (34u)	
#define EEP_BLOCK_RESERVED4_FLAG_ID				(35u)
///////////////////////BANK5
#define EEP_BLOCK_DIDF1FA_ID					(36u)
#define EEP_BLOCK_UNUSED5_ID			        (37u)	
#define EEP_BLOCK_RESERVED5_FLAG_ID				(38u)
///////////////////////BANK6
#define EEP_BLOCK_DIDF1FC_ID					(39u)
#define EEP_BLOCK_UNUSED6_ID			        (40u)	
#define EEP_BLOCK_RESERVED6_FLAG_ID				(41u)


#define EEP_BLOCK_MAX_NUM                       (42u)

/*the corresponding Block length*/

/**********BANK0************/
#define EEP_BLOCK_DIDF089_LEN					(15u)
#define EEP_BLOCK_DIDF18C_LEN					(13u)
#define EEP_BLOCK_DIDF190_LEN					(17u)
#define EEP_BLOCK_DIDF184_LEN					(7u)
#define EEP_BLOCK_DIDF1F0_LEN					(2u)
#define EEP_BLOCK_DIDF1F6_LEN			    	(10u)
#define EEP_BLOCK_descSecureFAAflag_LEN			(1u)
#define EEP_BLOCK_descSecureFBLflag_LEN			(1u)
#define EEP_BLOCK_UNUSED0_LEN			        (25u)
#define EEP_BLOCK_RESERVED0_FLAG_LEN			(2u)
/**********BANK1************/
#define EEP_BLOCK_E6B8_87_LEN					(13u)	 
#define EEP_BLOCK_E6BB_88_LEN					(13u)
#define EEP_BLOCK_97F8_16_LEN					(13u)
#define EEP_BLOCK_97F8_17_LEN			        (13u)
#define EEP_BLOCK_97F8_06_LEN					(13u)
#define EEP_BLOCK_97FB_18_LEN					(13u)
#define EEP_BLOCK_UNUSED1_LEN			        (13u)
#define EEP_BLOCK_RESERVED1_FLAG_LEN			(2u)
/**********BANK2************/
#define EEP_BLOCK_97FB_19_LEN					(13u)	
#define EEP_BLOCK_97F8_4B_LEN					(13u)
#define EEP_BLOCK_97FC_19_LEN					(13u)
#define EEP_BLOCK_97FC_18_LEN			        (13u)
#define EEP_BLOCK_97FD_19_LEN					(13u)
#define EEP_BLOCK_97FD_18_LEN					(13u)
#define EEP_BLOCK_UNUSED2_LEN			        (13u)
#define EEP_BLOCK_RESERVED2_FLAG_LEN			(2u)
/**********BANK3************/
#define EEP_BLOCK_Fridge_App_LEN				(91u)	
#define EEP_BLOCK_RESERVED3_FLAG_LEN			(2u)
/**********BANK4************/
#define EEP_BLOCK_97F8_09_LEN					(13u)	
#define EEP_BLOCK_97F9_09_LEN					(13u)
#define EEP_BLOCK_97F8_71_LEN					(13u)
#define EEP_BLOCK_97F8_49_LEN			        (13u)
#define EEP_BLOCK_97F9_49_LEN					(13u)
#define EEP_BLOCK_97FA_49_LEN					(13u)
#define EEP_BLOCK_97FA_09_LEN			        (13u)
#define EEP_BLOCK_RESERVED4_FLAG_LEN			(2u)
/**********BANK5************/
#define EEP_BLOCK_DIDF1FA_LEN					(90u)
#define EEP_BLOCK_UNUSED5_LEN			        (1u)
#define EEP_BLOCK_RESERVED5_FLAG_LEN			(2u)
/**********BANK6************/
#define EEP_BLOCK_DIDF1FC_LEN					(20u)
#define EEP_BLOCK_UNUSED6_LEN			        (71u)
#define EEP_BLOCK_RESERVED6_FLAG_LEN			(2u)








#define EEP_WRITE_TIMEOUT_MAX_TIMER         (8000u)
#define EEP_WRITE_CLEAR_MIN_TIMER           (16u)
#define EEP_READALL_LOOP_MAX_CNT            (6000u)
#define EEPM_GetSysLowVoltageStatus        BTRM_GetSysLowVoltageStatus

/*******************************************************************************
|    Enum Definition
|******************************************************************************/
typedef enum
{
#if (EEP_TYPE_DFLASH_ENABLE == EEP_ENABLE)
	EEP_DFLASH_DEV,
#endif
#if (EEP_TYPE_EXT_EEP_ENABLE == EEP_ENABLE)
	EEP_EXT_EEP_DEV,
#endif
#if (EEP_TYPE_FLEXMEM_ENABLE == EEP_ENABLE)
	EEP_IN_EEP_DEV,
#endif
    EEP_DEV_MAX_NUM
}EEP_DeviceEnumType;
/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef	struct Eep_BankCfgStruct
{
	uint16 usLength;		/*DataLength*/
	uint8 ucFlag;/*Kam backup flag,clear flag*/
	EEP_DeviceEnumType ucDevId;
	uint8 *ucRamAdd;
	uint8 *ucKam1Add;
	uint8 *ucKam2Add;
	uint8 *ucKam3Add;
	const uint8 *ucRomDataAddr;
}Eep_BankCfg;

typedef	struct Eep_BlockIdCfgStruct
{
	uint16 usAddOffset;
	uint16 usLength;		/*DataLength*/
	uint8 ucBankId;
}Eep_BlockIDCfg;

/*******************************************************************************
|    local variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Table Definition
|******************************************************************************/
extern const Eep_BankCfg		stEepBankCfg[EEP_BANK_MAX_NUM];
extern const Eep_BlockIDCfg stEepBlockCfg[EEP_BLOCK_MAX_NUM];


extern uint8 EEPM_CODE_RAM ucEepBank0RamArray[EEP_BANK0_DATA_LEN];
extern uint8 EEPM_CODE_RAM ucEepBank1RamArray[EEP_BANK1_DATA_LEN];
extern uint8 EEPM_CODE_RAM ucEepBank2RamArray[EEP_BANK2_DATA_LEN];
extern uint8 EEPM_CODE_RAM ucEepBank3RamArray[EEP_BANK3_DATA_LEN];
extern uint8 EEPM_CODE_RAM ucEepBank4RamArray[EEP_BANK4_DATA_LEN];
extern uint8 EEPM_CODE_RAM ucEepBank5RamArray[EEP_BANK5_DATA_LEN];
extern uint8 EEPM_CODE_RAM ucEepBank6RamArray[EEP_BANK6_DATA_LEN];
extern uint8 EEPM_CODE_RAM ucEepBank7RamArray[EEP_BANK7_DATA_LEN];


extern const uint8 ucEepBank0RomArray[EEP_BANK0_DATA_LEN];
extern const uint8 ucEepBank1RomArray[EEP_BANK1_DATA_LEN];
extern const uint8 ucEepBank2RomArray[EEP_BANK2_DATA_LEN];
extern const uint8 ucEepBank3RomArray[EEP_BANK3_DATA_LEN];
extern const uint8 ucEepBank4RomArray[EEP_BANK4_DATA_LEN];
extern const uint8 ucEepBank5RomArray[EEP_BANK5_DATA_LEN];
extern const uint8 ucEepBank6RomArray[EEP_BANK6_DATA_LEN];
extern const uint8 ucEepBank7RomArray[EEP_BANK7_DATA_LEN];
/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/
extern void EEPCFG_InitRamMemory( void );
extern void EEPCFG_InitKamMemory( void );

#endif/*(EEP_MODULE_EN == EEP_ENABLE)*/
#endif

/*EOF*/
