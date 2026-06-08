/* polyspace<MISRA-C3:1.1:Not a defect:Justified> Normal */
/*******************************************************************************
|  File Name:  STD_FlsIf.c
|  Description:  Implementation of the STD_FlsIf Config Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           XiaYaJun          CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 2018-05-23    01.00.00     XYJ       Creation
|******************************************************************************/

/*******************************************************************************
|	 Other Header File Inclusion
|******************************************************************************/
#include "STD_FlsIf.h"

#if 0
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
|	 Static local variables Declaration
|******************************************************************************/
/* polyspace<MISRA-C3:8.9:Not a defect:Justified> Normal */
static flash_ssd_config_t FLSIF_CODE_RAM stFmSSDConfig;

/*******************************************************************************
|	 Global Variable with extern linkage
|******************************************************************************/

/*******************************************************************************
|	 Global Function Prototypes
|******************************************************************************/

/****************************************************************************************
 *��������  : void FlsIf_Init(void)
 
 *����      :void
 
 *����ֵ    : void

 *����      : Fls�ӿڳ�ʼ��

 *�༭ʱ��  :

 *��ע      : ����
 ****************************************************************************************/
void FlsIf_Init(void)
{
    (void)FLASH_DRV_Init(&Flash1_InitConfig0, &stFmSSDConfig);
/* polyspace<DEFECT:DEAD_CODE:Not a defect:Justified> Normal. */
    if (stFmSSDConfig.EEESize == 0u)
    {
		/* Configure FlexRAM as EEPROM and FlexNVM as EEPROM backup region,
		 * DEFlashPartition will be failed if the IFR region isn't blank.
		 * Refer to the device document for valid EEPROM Data Size Code
		 * and FlexNVM Partition Code. For example on S32K144:
		 * - EEEDataSizeCode = 0x02u: EEPROM size = 4 Kbytes
		 * - DEPartitionCode = 0x08u: EEPROM backup size = 64 Kbytes */
    	(void)FLASH_DRV_DEFlashPartition(&stFmSSDConfig, 0x02u, 0x08u, 0x0u, false, true);

		/* Re-initialize the driver to update the new EEPROM configuration */
    	(void)FLASH_DRV_Init(&Flash1_InitConfig0, &stFmSSDConfig);

		/* Make FlexRAM available for EEPROM */
    	(void)FLASH_DRV_SetFlexRamFunction(&stFmSSDConfig, EEE_ENABLE, 0x00u, NULL);
	}
	else    /* FLexRAM is already configured as EEPROM */
	{
		/* Make FlexRAM available for EEPROM, make sure that FlexNVM and FlexRAM
		 * are already partitioned successfully before */
		(void)FLASH_DRV_SetFlexRamFunction(&stFmSSDConfig, EEE_ENABLE, 0x00u, NULL);
	}
}


/****************************************************************************************
 *��������  : uint8 FlsIf_GetFmReadyStauts(void)
 
 *����      :void
 
 *����ֵ    : uint8

 *����      : ��ȡFm׼��״̬ 

 *�༭ʱ��  :

 *��ע      : ����
 ****************************************************************************************/

uint8 FlsIf_GetFmReadyStauts(void)
{
	uint8 ReValue = E_NOT_OK;
	/* polyspace<MISRA-C3:11.4:Not a defect:Justified> Normal */
	if ((FTFx_FCNFG & FTFx_FCNFG_EEERDY_MASK) == FTFx_FCNFG_EEERDY_MASK)
	{
		ReValue = E_OK;
	}
	return ReValue;
}

/****************************************************************************************
 *��������  : uint8 FlsIf_GetFmErrorStauts(void)
 
 *����      :void
 
 *����ֵ    : uint8

 *����      : ��ȡFm�쳣״̬ 

 *�༭ʱ��  :

 *��ע      : ����
 ****************************************************************************************/
uint8 FlsIf_GetFmErrorStauts(void)
{
	uint8 ReValue = FALSE;
	/* polyspace<MISRA-C3:11.4:Not a defect:Justified> Normal */
	if ((FTFx_FSTAT & (FTFx_FSTAT_MGSTAT0_MASK | FTFx_FSTAT_FPVIOL_MASK | FTFx_FSTAT_ACCERR_MASK | FTFx_FSTAT_RDCOLERR_MASK)) != 0U)
	{
		ReValue = TRUE;
	}
	return ReValue;
}
#endif
/*******************************************************************************
Name            : FlsIf_Init
Syntax          : void FlsIf_Init(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : Initialize DFLASH
Call By         :
|******************************************************************************/
void FlsIf_Init()
{
    /*Fee Init*/
    Fee_Init(&FEEGenConfig);
    do
    {
        Fee_MainFunction();
    } while (Fee_GetStatus() != MEMIF_IDLE);
}

/*******************************************************************************
Name            : FlsIf_Write
Syntax          : uint8_t FlsIf_Write(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : Write DataBufferPtr to BlockNumber
Call By         :
|******************************************************************************/
uint8_t FlsIf_Write(uint16_t BlockNumber, const uint8_t * DataBufferPtr)
{
	uint8_t ret = E_OK;

    /*Write data*/
	ret = Fee_Write(BlockNumber, DataBufferPtr);

    /*Perform write data*/
    do
    {
        Fee_MainFunction();
    } while (Fee_GetStatus() != MEMIF_IDLE);

    return ret;
}

/*******************************************************************************
Name            : FlsIf_Read
Syntax          : uint8_t FlsIf_Read(void)
Sync/Async      : Synchronous
Reentrancy      : None
Parameters(in)  : None
Parameters(out) : None
Return value    : None
Description     : Read data of Length to DataBufferPtr from BlockNumber
Call By         :
|******************************************************************************/
uint8_t FlsIf_Read(uint16_t BlockNumber, uint16_t BlockOffset, uint8_t * DataBufferPtr, uint16_t Length)
{
	uint8_t ret = E_OK;

	/*Read data*/
	ret = Fee_Read(BlockNumber, BlockOffset, DataBufferPtr, Length);

	/*Perform read data*/
	do
	{
		Fee_MainFunction();
	} while (Fee_GetStatus() != MEMIF_IDLE);

	return ret;
}
/*EOF*/

