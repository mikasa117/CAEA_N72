/*******************************************************************************
|  File Name:  DID_Callback.c
|  Description:  Implementation of the DID_Callback Config Management
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
|    Other Header File Inclusion
|******************************************************************************/
#include "DID_Callback.h"
#include "CAEA_Types.h"
#include "RTE_CAN.h"
#include "desc.h"
#include "STD_EepM.h"
#include "CanNm.h"
#include "CanDem.h"
#include "CPID_Callback.h"
#include "SysM.h"
#include "fee.h"
#include "fls_async_driver.h"
#include "STD_EvM.h"
#include "flash_driver.h"
#include "flash_hw_access.h"
#include "Fault_Diagnosis.h"
#include "Fridge_Application_Config.h"
#include "STD_WdgM.h"
#include "Fridge_Basic_Control.h"
#include "Appl_Can_Callback.h"
#include "motor.h"

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
|    Static local variables Declaration
|******************************************************************************/
 
const uint8  __attribute__ ((section(".AppFlash_Storage"))) CaDid_u_0xF189_ChangAnSoftVersion[15]={'S','W','A','.','0','.','5',0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//SWA.0.3   GGG  0x30800
const uint8  __attribute__ ((section(".AppFlash_Storage"))) CaDid_u_0xF18A_SupplierIdentifier[7]={'F','V','2','9','A',0x00,0x00};//FV29A   0x30810  
const uint8  __attribute__ ((section(".AppFlash_Storage"))) CaDid_u_0xF188_SoftVersionNumber[20]={'9','2','6','2','3','0','1','-','F','E','0','1',0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//9262301-FE01   GGG  0x30818


static uint8 const CaDid_u_0xF1F9_ChangJiang_SWVersion[10]  	= CeDid_u_0xF1F9_ChangJiang_SWVersion;
static uint8 const CaDid_u_0xF122_DiagDefinitionVersion[4]  	= CeDid_u_0xF122_DiagDefinitionVersion;
static uint8 const CaDid_u_0xF120_NetworkProtocolVersion[4]  	= CeDid_u_0xF120_NetworkProtocolVersion;
static uint8 const CaDid_u_0xF121_FuncDefinitionVersion[4]		= CeDid_u_0xF121_FuncDefinitionVersion; 


static const uint32 * FblVersionNumber_P_Addr = (const uint32*)0x00000800;
static const uint32 * App1VersionNumber_P_Addr = (const uint32*)0x3F000u;
//static const uint32 * App2VersionNumber_P_Addr = (const uint32*)0x31FFFFD0;


//const uint8 __attribute__((section(".app_version"))) CaAPP_Version[6] = CeDid_u_0xF195_SwVersion;
/*******************************************************************************
|    Global Variable with extern linkage
|******************************************************************************/
//*(.app_version) APP_VERSION 0x202bffd0 0x30
/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/

/*******************************************************************************
| Function name     :
| Called by         :
| Preconditions     :
| Input Parameters  :
| Return Value      :
| Description       : Be called Gpt_Cfg task
| History
| <No.>   <author>    <time>      <description>
|  1       lzq       20180226    Primary edition
|******************************************************************************/

static uint8  DID_0xF190_WriteFlag;		
static uint16 DID_0xF190_WriteCnt; 		

static uint8  DID_0xF1F0_WriteFlag; 		
static uint16 DID_0xF1F0_WriteCnt; 		

static uint8  DID_0xF1F6_WriteFlag; 		
static uint16 DID_0xF1F6_WriteCnt; 		

static uint8  DID_0xF18C_WriteFlag; 		
static uint16 DID_0xF18C_WriteCnt; 		


static uint8  DID_0xF1FC_WriteFlag; 		
static uint16 DID_0xF1FC_WriteCnt; 		

static uint8  DID_Fridge_App_WriteFlag; 	
static uint16 DID_Fridge_App_WriteCnt; 	

#define EFM_CUS_NVR_ADDR        (0x10030000U)

static const uint8 *src_ptr_Read0xF170 = (uint8 *)0x2FB00;
static const uint8 *src_ptr_Read0xF171 = (uint8 *)0x2FB04;
static const uint8 *src_ptr_Read0xF1F9 = (uint8 *)0x2FB08;

uint8 CUS_NVR_ReadDidF1F9[16];
uint8 CUS_NVR_WriteDidF1F9[10] 	={'H','W','A','.','0','.','1','.','0','1'};//HWA.0.1.01;

uint8 CUS_NVR_ReadDidF187[24] ={0};
uint8 CUS_NVR_WriteBuf[1024] = {0};
uint8 CUS_NVR_ReadDidF089[16] ={0};
uint8 CUS_NVR_ReadDidF1F6[16] ={0};


uint8 g_EEP_WriteF1FA_Buf[90] ;
uint8 g_EEP_WriteF1FA_flg; 	

extern uint16_t TargetSpeed;
/*******************************************************************************
|    Global Variable with extern linkage
|******************************************************************************/
//*(.app_version) APP_VERSION 0x202bffd0 0x30
/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/

/*******************************************************************************
| Function name     :
| Called by         :
| Preconditions     :
| Input Parameters  :
| Return Value      :
| Description       : Be called Gpt_Cfg task
| History
| <No.>   <author>    <time>      <description>
|  1       lzq       20180226    Primary edition
|******************************************************************************/


/*******************************************************************************
							Write DID
********************************************************************************/
////////////////////////////////////////////////////////////////////////////////////


void DID_Callback_Init(void)
{ 
 	DID_0xF190_WriteFlag 		= 0u;
 	DID_0xF190_WriteCnt 		= 0u;

  	DID_0xF1F0_WriteFlag 		= 0u;
 	DID_0xF1F0_WriteCnt 		= 0u;

  	DID_0xF1F6_WriteFlag 		= 0u;
	DID_0xF1F6_WriteCnt 		= 0u;

  	DID_0xF18C_WriteFlag 		= 0u;
	DID_0xF18C_WriteCnt 		= 0u;

  	DID_Fridge_App_WriteFlag 	= 0u;
 	DID_Fridge_App_WriteCnt 	= 0u;

	DID_0xF1FC_WriteFlag        = 0u;
	DID_0xF1FC_WriteCnt         = 0u;

	g_EEP_WriteF1FA_flg 		= 0u;	

	for(uint8 i = 0; i < 16; i++) 
	{
   		CUS_NVR_ReadDidF1F9[i] = 0;
	}


	for(uint8 i = 0; i < 90; i++) 
	{
   		g_EEP_WriteF1FA_Buf[i] = 0;
	}

}








void CUS_NVR_WriteDID(void)
{
	
	
	EFM->CUS_KEY = 0x4DFF32;

	/* FLASH_DRV_ReadNVR(0, 0x10030150, 16, CU_NVR_ReadDidF1F9);


	  if ((CUS_NVR_ReadDidF1F9[0] ==0xFF ) ||(CUS_NVR_ReadDidF1F9[0] ==0x00 ))
	  {
	  FLASH_DRV_ReadNVR(0, 0x10030000, 1024, CUS_NVR_WriteBuf);
	   FLASH_DRV_EraseNVR(0, 0x10030000);
		for(uint8 i = 0u; i< 16; i++ )
	  {
	   CUS_NVR_WriteBuf[0x150+i] =  CUS_NVR_WriteDidF1F9[i];                      
	  }
	 
	  FLASH_DRV_ProgramNVR(0, 0x10030000, 1024, CUS_NVR_WriteBuf);

	  }
	  else
	  {
	   ;
	  }*/
	
	

}


void ApplDescWrite_Fridge_App(uint8 LpDID_u_DataPtr[])
{
    
    uint16 LeDCM_u_TimeoutCnt = 0;
    const uint16 LeDCM_u_TimeoutMax = 450; // 4.5秒超时（10ms/计数）


    EEPM_AppWriteBlock(EEP_BLOCK_Fridge_App_ID, &LpDID_u_DataPtr[0]);
    EEPM_MainFunction();
    while(EEPM_GetSleepRequestStatus() == FALSE)  
    {
        EEPM_MainFunction();
        WDGM_Trigger();
        NOP();
        NOP();

                // 检查超时
        LeDCM_u_TimeoutCnt++;
        if(LeDCM_u_TimeoutCnt > LeDCM_u_TimeoutMax)
        {
            // 超时，退出循环
            break;
        }
    }

}


////////////////////////////////////////////////////////////////////////////////////////////////


uint8 DID_Write0xF187(uint8 LpDID_u_DataPtr[])
{
	uint8 e_u_Ret = ( uint8 )CeDID_Pend;

	EFM->CUS_KEY = 0x4DFF32;

      FLASH_DRV_ReadNVR(0, 0x10030100, 24, CUS_NVR_ReadDidF187);
	
	 
		 if ((CUS_NVR_ReadDidF187[0] ==0xFF ) ||(CUS_NVR_ReadDidF187[0] ==0x00 ))
		 {
				FLASH_DRV_ReadNVR(0, 0x10030000, 1024, CUS_NVR_WriteBuf);
				FLASH_DRV_EraseNVR(0, 0x10030000);
	
	
			for(uint8 i = 0u; i< 24; i++ )
			{
				CUS_NVR_WriteBuf[0x100+i] =  LpDID_u_DataPtr[i];                      
			}
	
			FLASH_DRV_ProgramNVR(0, 0x10030000, 1024, CUS_NVR_WriteBuf);

			e_u_Ret = CeDID_OK;
	
		 }
		 else
		 {
			e_u_Ret = 0x31;
		 }
	 



	
	return e_u_Ret;
}

uint8 DID_Write0xF089(uint8 LpDID_u_DataPtr[])
{
	uint8 e_u_Ret = ( uint8 )CeDID_Pend;
	EFM->CUS_KEY = 0x4DFF32;
	
	FLASH_DRV_ReadNVR(0, 0x10030120, 16, CUS_NVR_ReadDidF089);


		 if ((CUS_NVR_ReadDidF089[0] ==0xFF ) ||(CUS_NVR_ReadDidF089[0] ==0x00 ))
		 {
			FLASH_DRV_ReadNVR(0, 0x10030000, 1024, CUS_NVR_WriteBuf);
			
			for(uint8 i = 0u; i< 16; i++ )
			{
				CUS_NVR_WriteBuf[0x120+i] =  LpDID_u_DataPtr[i];                      
			}
			FLASH_DRV_EraseNVR(0, 0x10030000);
			FLASH_DRV_ProgramNVR(0, 0x10030000, 1024, CUS_NVR_WriteBuf);

			e_u_Ret = CeDID_OK;
	
		 }
		 else
		 {
			e_u_Ret = 0x31;
		 }


	 

	return e_u_Ret;


}

uint8 DID_Write0xF18C(uint8 LpDID_u_DataPtr[])
{

	uint8 e_u_Ret = ( uint8 )CeDID_Pend;

	if(DID_0xF18C_WriteFlag == 0u)
    {
		EEPM_AppWriteBlock(EEP_BLOCK_DIDF18C_ID, &LpDID_u_DataPtr[0]);
		EEPM_MainFunction();
		DID_0xF18C_WriteFlag =1u;
		e_u_Ret = ( uint8 )CeDID_Pend ;

	}
	else
	{
		
		if( DID_0xF18C_WriteCnt >450u)   /*********10MS/Cnt******/
		{
			DID_0xF18C_WriteCnt = 0u;
			DID_0xF18C_WriteFlag = 0u;
			e_u_Ret = ( uint8 )CeDID_OutTime ;
		}
		else
		{
			DID_0xF18C_WriteCnt++;
			if(EEPM_GetSleepRequestStatus() == TRUE)
			{
				DID_0xF18C_WriteCnt = 0u;
				DID_0xF18C_WriteFlag = 0u;
				e_u_Ret = ( uint8 )CeDID_OK ;
			}
			else
			{
			}
		}
	}
	return (uint8)e_u_Ret;

}

uint8 DID_Write0xF190(uint8 LpDID_u_DataPtr[])
{

	uint8 e_u_Ret = ( uint8 )CeDID_Pend;

	if(DID_0xF190_WriteFlag == 0u)
    {
		EEPM_AppWriteBlock(EEP_BLOCK_DIDF190_ID, &LpDID_u_DataPtr[0]);
		EEPM_MainFunction();
		DID_0xF190_WriteFlag =1u;
		e_u_Ret = ( uint8 )CeDID_Pend ;

	}
	else
	{
		
		if( DID_0xF190_WriteCnt >450u)   /*********10MS/Cnt******/
		{
			DID_0xF190_WriteCnt = 0u;
			DID_0xF190_WriteFlag = 0u;
			e_u_Ret = ( uint8 )CeDID_OutTime ;
		}
		else
		{
			DID_0xF190_WriteCnt++;
			if(EEPM_GetSleepRequestStatus() == TRUE)
			{
				DID_0xF190_WriteCnt = 0u;
				DID_0xF190_WriteFlag = 0u;
				e_u_Ret = ( uint8 )CeDID_OK ;
			}
			else
			{
			}
		}
	}
	return (uint8)e_u_Ret;

}



uint8 DID_Write0xF1F0(uint8 LpDID_u_DataPtr[])
{
		
	uint8 e_u_Ret = ( uint8 )CeDID_Pend;

	if(DID_0xF1F0_WriteFlag == 0u)
    {
		EEPM_AppWriteBlock(EEP_BLOCK_DIDF1F0_ID, &LpDID_u_DataPtr[0]);
		EEPM_MainFunction();
		DID_0xF1F0_WriteFlag =1u;
		e_u_Ret = ( uint8 )CeDID_Pend ;

	}
	else
	{
		
		if( DID_0xF1F0_WriteCnt >450u)   /*********10MS/Cnt******/
		{
			DID_0xF1F0_WriteCnt = 0u;
			DID_0xF1F0_WriteFlag = 0u;
			e_u_Ret = ( uint8 )CeDID_OutTime ;
		}
		else
		{
			DID_0xF1F0_WriteCnt++;
			if(EEPM_GetSleepRequestStatus() == TRUE)
			{
				DID_0xF1F0_WriteCnt = 0u;
				DID_0xF1F0_WriteFlag = 0u;
				e_u_Ret = ( uint8 )CeDID_OK ;
			}
			else
			{
			}
		}
	}
	return (uint8)e_u_Ret;

}



uint8 DID_Write0xF1F6(uint8 LpDID_u_DataPtr[])
{

/*	uint8 e_u_Ret = ( uint8 )CeDID_Pend;

	EFM->CUS_KEY = 0x4DFF32;
	
	FLASH_DRV_ReadNVR(0, 0x10030140, 16, CUS_NVR_ReadDidF1F6);

		 if ((CUS_NVR_ReadDidF1F6[0] ==0xFF ) ||(CUS_NVR_ReadDidF1F6[0] ==0x00 ))
		 {


			if((LpDID_u_DataPtr[0] == 0xFF)||(LpDID_u_DataPtr[0] == 0x00))    
			{
				return 0x22;
	
			}

			FLASH_DRV_ReadNVR(0, 0x10030000, 1024, CUS_NVR_WriteBuf);
			
			for(uint8 i = 0u; i< 16; i++ )
			{
				CUS_NVR_WriteBuf[0x140+i] =  LpDID_u_DataPtr[i];                      
			}
			FLASH_DRV_EraseNVR(0, 0x10030000);
			FLASH_DRV_ProgramNVR(0, 0x10030000, 1024, CUS_NVR_WriteBuf);

			e_u_Ret = CeDID_OK;
	
		 }
		 else
		 {
			e_u_Ret = 0x22;
		 }*/


	
	uint8 e_u_Ret = ( uint8 )CeDID_Pend;
	uint8 i;
	bool isWriteDataAll00OrFF = 0;
	bool isCurrentDataAll00OrFF = 0;
 
	// Check if write data is all 0x00 or all 0xFF
	for (i = 0; i < 10; i++)
	{
		if (LpDID_u_DataPtr[i] == 0x00)
		{
			isWriteDataAll00OrFF = TRUE;
		}
		if (LpDID_u_DataPtr[i] == 0xFF)
		{
			isWriteDataAll00OrFF = TRUE;
		}
		if (!isWriteDataAll00OrFF)
		{
			break;
		}
	}
 
	// If write data is all 0x00 or all 0xFF, return NRC22
	if (isWriteDataAll00OrFF)
	{
		return 0x22;
	}
 
	EFM->CUS_KEY = 0x4DFF32;
	
	FLASH_DRV_ReadNVR(0, 0x10030140, 16, CUS_NVR_ReadDidF1F6);
 
	// Check if current data is all 0x00 or all 0xFF
//	isCurrentDataAll00OrFF = TRUE;
	for (i = 0; i < 10; i++)
	{
		if (CUS_NVR_ReadDidF1F6[i] == 0x00)
		{
			isCurrentDataAll00OrFF = TRUE;
		}
		if (CUS_NVR_ReadDidF1F6[i] == 0xFF)
		{
			isCurrentDataAll00OrFF = TRUE;
		}
		if (!isCurrentDataAll00OrFF)
		{
			break;
		}
	}
 
	// If current data is not all 0x00 or all 0xFF, return NRC22
	if (!isCurrentDataAll00OrFF)
	{
		return 0x22;
	}
 
	// If current data is all 0x00 or all 0xFF, allow write
	FLASH_DRV_ReadNVR(0, 0x10030000, 1024, CUS_NVR_WriteBuf);
	
	for(uint8 i = 0u; i< 16; i++ )
	{
		CUS_NVR_WriteBuf[0x140+i] =  LpDID_u_DataPtr[i];                      
	}
	FLASH_DRV_EraseNVR(0, 0x10030000);
	FLASH_DRV_ProgramNVR(0, 0x10030000, 1024, CUS_NVR_WriteBuf);
 
	e_u_Ret = CeDID_OK;





	return (uint8)e_u_Ret;

}



uint8 DID_Write0xF1FA(uint8 LpDID_u_DataPtr[])
{
	//Check_DIDF1FA_CompressorFault
	return (uint8)0x31;
}

uint8 DID_Write0xF1FB(uint8 LpDID_u_DataPtr[])     
{
	
	return (uint8)0x31;
}


uint8 DID_Write0xF1FC(uint8 LpDID_u_DataPtr[])     
{
	
	uint8 e_u_Ret = ( uint8 )CeDID_Pend;

	/*控制0上制冷*/
	if(LpDID_u_DataPtr[2] ==1)
	{
		LpDID_u_DataPtr[2] = 0xA5;
		LpDID_u_DataPtr[3] = 0x96;
	}
	else
	{
		LpDID_u_DataPtr[2] = 0;
		LpDID_u_DataPtr[3] = 0;
		LpDID_u_DataPtr[4] = 0;  //温度补偿
	}

	/*控制0上制冷*/
	if(LpDID_u_DataPtr[5] ==1)
	{
		LpDID_u_DataPtr[5] = 0xA5;
		LpDID_u_DataPtr[6] = 0x96;
	}
	else
	{
		LpDID_u_DataPtr[5] = 0;
		LpDID_u_DataPtr[6] = 0;
		LpDID_u_DataPtr[7] = 0;//温度补偿
	}
	
	/*控制制热*/
	if(LpDID_u_DataPtr[8] ==1)
	{
		LpDID_u_DataPtr[8] = 0xA5;
		LpDID_u_DataPtr[9] = 0x96;
	}
	else
	{
		LpDID_u_DataPtr[8] = 0;
		LpDID_u_DataPtr[9] = 0;
		LpDID_u_DataPtr[10] = 0;//温度补偿
	}

	/*控制转速*/
	if(LpDID_u_DataPtr[11] ==1)
	{
		LpDID_u_DataPtr[11] = 0xA5;
		LpDID_u_DataPtr[12] = 0x96;
	}
	else
	{
		LpDID_u_DataPtr[11] = 0;
		LpDID_u_DataPtr[12] = 0;
		LpDID_u_DataPtr[13] = 0;//转速补偿
		LpDID_u_DataPtr[14] = 0;//转速补偿
	}


	if(DID_0xF1FC_WriteFlag == 0u)
    {   
		EEPM_AppWriteBlock(EEP_BLOCK_DIDF1FC_ID, &LpDID_u_DataPtr[0]);
		EEPM_MainFunction();
		DID_0xF1FC_WriteFlag =1u;
		e_u_Ret = ( uint8 )CeDID_Pend ;

	}
	else
	{
		if( DID_0xF1FC_WriteCnt >450u)   /*********10MS/Cnt******/
		{
			DID_0xF1FC_WriteCnt = 0u;
			DID_0xF1FC_WriteFlag = 0u;
			e_u_Ret = ( uint8 )CeDID_OutTime ;
		}
		else
		{
			DID_0xF1FC_WriteCnt++;
			if(EEPM_GetSleepRequestStatus() == TRUE)
			{
				DID_0xF1FC_WriteCnt = 0u;
				DID_0xF1FC_WriteFlag = 0u;
				e_u_Ret = ( uint8 )CeDID_OK ;
			}
			else
			{
			}
		}
	}

	if(LpDID_u_DataPtr[0] == 0x01)
	{
		CanApp_SetWakeupMode_NM(1);	
	}
	else if(LpDID_u_DataPtr[0] == 0x02)
	{
		CanApp_SetWakeupMode_NM(0);	
	}
	else
	{
		;
	}

	return (uint8)e_u_Ret;
}
/*******************************************************************************
							Read DID
********************************************************************************/
void DID_AgingModeFunction(void) 
{
	uint8 LpDID_u_DataPtr[20] = {0u};

	EEPM_AppReadBlock(EEP_BLOCK_DIDF1FC_ID, &LpDID_u_DataPtr[0]);

	if(LpDID_u_DataPtr[0] == 0x01)
	{
		CanApp_SetWakeupMode_NM(1);	
	}
	else if(LpDID_u_DataPtr[0] == 0x02)
	{
		CanApp_SetWakeupMode_NM(0);	
	}
	else
	{
		;
	}
}

uint8 DID_Read0xF089(uint8 LpDID_u_DataPtr[]) 
{
	uint8 LeDID_u_Index;
	
	
	EFM->CUS_KEY = 0x4DFF32;
	FLASH_DRV_ReadNVR(0, 0x10030120, 16, CUS_NVR_ReadDidF089);


	if((CUS_NVR_ReadDidF089[0] ==0xFF ) || (CUS_NVR_ReadDidF089[0] ==0x00 ))
	{
		uint8 defaultVal[15] = {'H','W','A','.','0','.','1',0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};

		for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)15U;LeDID_u_Index++)
    	{
        	LpDID_u_DataPtr[LeDID_u_Index] = defaultVal[LeDID_u_Index];
    	}
	}
	else 
	{
    	for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)15U;LeDID_u_Index++)
    	{
        	LpDID_u_DataPtr[LeDID_u_Index] = CUS_NVR_ReadDidF089[LeDID_u_Index];
    	}
	}

	
    return ( uint8 )E_OK;
}


uint8 DID_Read0xF120(uint8 LpDID_u_DataPtr[]) 
{
	
	uint8 LeDID_u_Index;
    for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)4U;LeDID_u_Index++)
    {
        LpDID_u_DataPtr[LeDID_u_Index] = CaDid_u_0xF120_NetworkProtocolVersion[LeDID_u_Index];
    }
	return (uint8)E_OK;
}

uint8 DID_Read0xF121( uint8 LpDID_u_DataPtr[] )
{
	
	uint8 LeDID_u_Index;
    for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)4U;LeDID_u_Index++)
    {
        LpDID_u_DataPtr[LeDID_u_Index] = CaDid_u_0xF121_FuncDefinitionVersion[LeDID_u_Index];
    }
	return (uint8)E_OK;
}
uint8 DID_Read0xF122( uint8 LpDID_u_DataPtr[] )
{
    uint8 LeDID_u_Index;
    for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)4U;LeDID_u_Index++)
    {
        LpDID_u_DataPtr[LeDID_u_Index] = CaDid_u_0xF122_DiagDefinitionVersion[LeDID_u_Index];
    }
	return (uint8)E_OK;

}

uint8 DID_Read0xF170( uint8 LpDID_u_DataPtr[] )
{
    for(uint8 i=0U;i<(uint8)4U;i++)
    {
        LpDID_u_DataPtr[i] = src_ptr_Read0xF170[i];
    }
	return (uint8)E_OK;
}



uint8 DID_Read0xF171( uint8 LpDID_u_DataPtr[] )
{
	
    for(uint8 i=0U;i<(uint8)4U;i++)
    {
        LpDID_u_DataPtr[i] = src_ptr_Read0xF171[i];
    }
	return (uint8)E_OK;
}
uint8 DID_Read0xF184( uint8 LpDID_u_DataPtr[] )
{

    EEPM_AppReadBlock(EEP_BLOCK_DIDF184_ID, &LpDID_u_DataPtr[0]);

    return ( uint8 )E_OK;
}



uint8 DID_Read0xF187( uint8 LpDID_u_DataPtr[] )
{

	uint8 LeDID_u_Index;
	
	EFM->CUS_KEY = 0x4DFF32;
	FLASH_DRV_ReadNVR(0, 0x10030100, 24, CUS_NVR_ReadDidF187);

    	for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)21U;LeDID_u_Index++)
    	{
        	LpDID_u_DataPtr[LeDID_u_Index] = CUS_NVR_ReadDidF187[LeDID_u_Index];
		
    	}

	
    return ( uint8 )E_OK;
}
uint8 DID_Read0xF188( uint8 LpDID_u_DataPtr[] )
{
    uint8 LeDID_u_Index;
	
	
    for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)20U;LeDID_u_Index++)
    {
        LpDID_u_DataPtr[LeDID_u_Index] = CaDid_u_0xF188_SoftVersionNumber[LeDID_u_Index];
    }
	return (uint8)E_OK;
}



uint8 DID_Read0xF189( uint8 LpDID_u_DataPtr[] )
{
    uint8 LeDID_u_Index;
    for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)15U;LeDID_u_Index++)
    {
        LpDID_u_DataPtr[LeDID_u_Index] = CaDid_u_0xF189_ChangAnSoftVersion[LeDID_u_Index];
    }
	return (uint8)E_OK;
}


uint8 DID_Read0xF18A( uint8 LpDID_u_DataPtr[] )
{
    uint8 LeDID_u_Index;
    for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)7U;LeDID_u_Index++)
    {
        LpDID_u_DataPtr[LeDID_u_Index] = CaDid_u_0xF18A_SupplierIdentifier[LeDID_u_Index];
    }
	return (uint8)E_OK;
}
uint8 DID_Read0xF18C( uint8 LpDID_u_DataPtr[] )
{
	EEPM_AppReadBlock(EEP_BLOCK_DIDF18C_ID, &LpDID_u_DataPtr[0]);

    return ( uint8 )E_OK;
}
uint8 DID_Read0xF190( uint8 LpDID_u_DataPtr[] )
{
   EEPM_AppReadBlock(EEP_BLOCK_DIDF190_ID, &LpDID_u_DataPtr[0]);

    return ( uint8 )E_OK;
}
uint8 DID_Read0xF1F0( uint8 LpDID_u_DataPtr[] )
{
   EEPM_AppReadBlock(EEP_BLOCK_DIDF1F0_ID, &LpDID_u_DataPtr[0]);

    return ( uint8 )E_OK;
}
uint8 DID_Read0xF1F6( uint8 LpDID_u_DataPtr[] )
{
	/*uint8 LeDID_u_Index;
   	EFM->CUS_KEY = 0x4DFF32;

	FLASH_DRV_ReadNVR(0, 0x10030140, 16, CUS_NVR_ReadDidF1F6);

    for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)15U;LeDID_u_Index++)
    {
        LpDID_u_DataPtr[LeDID_u_Index] = CUS_NVR_ReadDidF1F6[LeDID_u_Index];
		
    }*/


		uint8 LeDID_u_Index;
    	EFM->CUS_KEY = 0x4DFF32;
 
	FLASH_DRV_ReadNVR(0, 0x10030140, 16, CUS_NVR_ReadDidF1F6);
 
	// Check if CUS_NVR_ReadDidF1F6 is all FF
	bool isAllFF = 0;
	for (LeDID_u_Index = 0; LeDID_u_Index < 16; LeDID_u_Index++)
	{
		if (CUS_NVR_ReadDidF1F6[LeDID_u_Index] == 0xFF)
		{
			isAllFF = TRUE;
			
		}
		else
		{
			isAllFF = FALSE;
			break;
		}

	}
 
	if (isAllFF)
	{
		// If all FF, return all 0
		for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)15U;LeDID_u_Index++)
		{
			LpDID_u_DataPtr[LeDID_u_Index] = 0x00;
		}
	}
	else
	{
		// Otherwise, return the actual data
		for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)15U;LeDID_u_Index++)
		{
			LpDID_u_DataPtr[LeDID_u_Index] = CUS_NVR_ReadDidF1F6[LeDID_u_Index];
		}
	}


    return ( uint8 )E_OK;
}

uint8 DID_Read0xF1F7( uint8 LpDID_u_DataPtr[] )
{	
	FridgeApp_CompressorStatusType Diag_CompressorStatusTemp;
	FridgeApp_HeatFilmStatusType Diag_HeatFilmStatusTemp;
	FridgeApp_ActuatorGeneralStatusType Diag_HeatWireStatusTemp;
	FridgeApp_ActuatorGeneralStatusType Diag_FanStatusTemp;
	FridgeApp_ActuatorGeneralStatusType Diag_UVLedStatusTemp;
	FridgeApp_ActuatorGeneralStatusType Diag_WLedStatusTemp;
	FridgeApp_ActuatorGeneralStatusType Diag_ALedStatusTemp;
	uint16 DootWorkStatusTemp = 0;
	uint8 PCBTemperatureTemp = 0;
	uint16 FridgeTemperatureTemp = 0;
	sint16 CompressorTemperatureTemp = 0;

	FridgeApp_GetCompressorStatus(&Diag_CompressorStatusTemp);
	FridgeApp_GetHeatFilmStatus(&Diag_HeatFilmStatusTemp);
	FridgeApp_GetHeatWireStatus(&Diag_HeatWireStatusTemp);
	FridgeApp_GetFanStatus(&Diag_FanStatusTemp);
	FridgeApp_GetUVLedStatus(&Diag_UVLedStatusTemp);

	FridgeApp_GetWLedStatus(&Diag_WLedStatusTemp);
	FridgeApp_GetALedStatus(&Diag_ALedStatusTemp);
	FridgeApp_GetDoorStatus(&DootWorkStatusTemp);
	FridgeApp_GetPcbTemp(&PCBTemperatureTemp);
	FridgeApp_GetFridgeTemp(&FridgeTemperatureTemp);
	FridgeApp_GetCompressorTemp(&CompressorTemperatureTemp);

    //压缩机工作状态（gs.state）
    LpDID_u_DataPtr[0] = (uint8)(Diag_CompressorStatusTemp.m_CompressorState);
	//压缩机转速
    LpDID_u_DataPtr[1] = (uint8)(Diag_CompressorStatusTemp.m_CompressorSpeed >> 8u);
    LpDID_u_DataPtr[2] = (uint8)(Diag_CompressorStatusTemp.m_CompressorSpeed & 0xFFu);
	//压缩机相电流1
    LpDID_u_DataPtr[3] = (uint8)(Diag_CompressorStatusTemp.m_CompressorPhaseUCur >> 8u);
	LpDID_u_DataPtr[4] = (uint8)(Diag_CompressorStatusTemp.m_CompressorPhaseUCur & 0xFFu);
	//压缩机相电流2
    LpDID_u_DataPtr[5] = (uint8)(Diag_CompressorStatusTemp.m_CompressorPhaseVCur >> 8u);
    LpDID_u_DataPtr[6] = (uint8)(Diag_CompressorStatusTemp.m_CompressorPhaseVCur & 0xFFu);
	//压缩机母线电流
    LpDID_u_DataPtr[7] = (uint8)(Diag_CompressorStatusTemp.m_CompressorBusCur >> 8u);
    LpDID_u_DataPtr[8] = (uint8)(Diag_CompressorStatusTemp.m_CompressorBusCur & 0xFFu);
	//压缩机供电电压
    LpDID_u_DataPtr[9] = (uint8)(Diag_CompressorStatusTemp.m_CompressorSupplyVol & 0xFFu);
	//制冷状态机（软件状态）
    LpDID_u_DataPtr[10] = (uint8)(Diag_CompressorStatusTemp.m_CompressorSM);
	//压缩机状态机（软件状态）
	LpDID_u_DataPtr[11] = (uint8)(FridgeCoolExecute_SMGlo);
	//压缩机目标转速
    LpDID_u_DataPtr[12] = (uint8)(TargetSpeed >> 8u);
    LpDID_u_DataPtr[13] = (uint8)(TargetSpeed & 0xFFu);
	//压缩机母线电压
    LpDID_u_DataPtr[14] = (uint8)(ADC_BAT_BLDC >> 8u);
    LpDID_u_DataPtr[15] = (uint8)(ADC_BAT_BLDC & 0xFFu);
	//压缩机历史故障（Fault）
	LpDID_u_DataPtr[16] = (uint8)(FridgeFAULT >> 24u);
	LpDID_u_DataPtr[17] = (uint8)(FridgeFAULT >> 16u);
	LpDID_u_DataPtr[18] = (uint8)(FridgeFAULT >> 8u);
	LpDID_u_DataPtr[19] = (uint8)(FridgeFAULT & 0xFFu);
	//电源A模式标志（Fault）
	LpDID_u_DataPtr[20] = (uint8)FridgeFault_BatModeA;
	//电源电压AD值（Fault）
	LpDID_u_DataPtr[21] = (uint8)(FridgeFault_BatADValue >> 8u);
	LpDID_u_DataPtr[22] = (uint8)(FridgeFault_BatADValue & 0xFFu);

	//加热膜工作状态
    LpDID_u_DataPtr[23] = (uint8)(Diag_HeatFilmStatusTemp.m_HeatFilmState >> 8u);
    LpDID_u_DataPtr[24] = (uint8)(Diag_HeatFilmStatusTemp.m_HeatFilmState & 0xFFu);
	//加热膜电流
    LpDID_u_DataPtr[25] = (uint8)(Diag_HeatFilmStatusTemp.m_HeatFilmCur >> 8u);
	LpDID_u_DataPtr[26] = (uint8)(Diag_HeatFilmStatusTemp.m_HeatFilmCur & 0xFFu);
	//加热膜状态机（软件状态）
	LpDID_u_DataPtr[27] = (uint8)(Diag_HeatFilmStatusTemp.m_HeatFilmSM >> 8u);
	LpDID_u_DataPtr[28] = (uint8)(Diag_HeatFilmStatusTemp.m_HeatFilmSM & 0xFFu);
	//加热丝工作状态
	LpDID_u_DataPtr[29] = (uint8)(Diag_HeatWireStatusTemp.m_ActuatorGeneralState >> 8u);
	LpDID_u_DataPtr[30] = (uint8)(Diag_HeatWireStatusTemp.m_ActuatorGeneralState & 0xFFu);
	//加热丝电流
	LpDID_u_DataPtr[31] = (uint8)(Diag_HeatWireStatusTemp.m_ActuatorGeneralCur >> 8u);
	LpDID_u_DataPtr[32] = (uint8)(Diag_HeatWireStatusTemp.m_ActuatorGeneralCur & 0xFFu);
	//FAN风扇工作状态
	LpDID_u_DataPtr[33] = (uint8)(Diag_FanStatusTemp.m_ActuatorGeneralState >> 8u);
	LpDID_u_DataPtr[34] = (uint8)(Diag_FanStatusTemp.m_ActuatorGeneralState & 0xFFu);
	//FAN风扇电流
	LpDID_u_DataPtr[35] = (uint8)(Diag_FanStatusTemp.m_ActuatorGeneralCur >> 8u);
	LpDID_u_DataPtr[36] = (uint8)(Diag_FanStatusTemp.m_ActuatorGeneralCur & 0xFFu);
	//UV-C led工作状态
	LpDID_u_DataPtr[37] = (uint8)(Diag_UVLedStatusTemp.m_ActuatorGeneralState >> 8u);
	LpDID_u_DataPtr[38] = (uint8)(Diag_UVLedStatusTemp.m_ActuatorGeneralState & 0xFFu);
	//UV-C led电流
	LpDID_u_DataPtr[39] = (uint8)(Diag_UVLedStatusTemp.m_ActuatorGeneralCur >> 8u);
	LpDID_u_DataPtr[40] = (uint8)(Diag_UVLedStatusTemp.m_ActuatorGeneralCur & 0xFFu);
	//light1 led工作状态（制冷）
	LpDID_u_DataPtr[41] = (uint8)(Diag_WLedStatusTemp.m_ActuatorGeneralState >> 8u);
	LpDID_u_DataPtr[42] = (uint8)(Diag_WLedStatusTemp.m_ActuatorGeneralState & 0xFFu);
	//light1 led电流
	LpDID_u_DataPtr[43] = (uint8)(Diag_WLedStatusTemp.m_ActuatorGeneralCur >> 8u);
	LpDID_u_DataPtr[44] = (uint8)(Diag_WLedStatusTemp.m_ActuatorGeneralCur & 0xFFu);
	//light2 led工作状态（制热）
	LpDID_u_DataPtr[45] = (uint8)(Diag_ALedStatusTemp.m_ActuatorGeneralState >> 8u);
	LpDID_u_DataPtr[46] = (uint8)(Diag_ALedStatusTemp.m_ActuatorGeneralState & 0xFFu);
	//light2 led电流
	LpDID_u_DataPtr[47] = (uint8)(Diag_ALedStatusTemp.m_ActuatorGeneralCur >> 8u);
	LpDID_u_DataPtr[48] = (uint8)(Diag_ALedStatusTemp.m_ActuatorGeneralCur & 0xFFu);
	//工作门工作状态
	LpDID_u_DataPtr[49] = (uint8)(DootWorkStatusTemp >> 8u);
	LpDID_u_DataPtr[50] = (uint8)(DootWorkStatusTemp & 0xFFu);
	//板载温度
	LpDID_u_DataPtr[51] = (uint8)(PCBTemperatureTemp);
	//TEMP.Sensor1温度监测
	LpDID_u_DataPtr[52] = (uint8)(FridgeTemperatureTemp >> 8u);
	LpDID_u_DataPtr[53] = (uint8)(FridgeTemperatureTemp & 0xFFu);
	//TEMP.Sensor2温度监测
	LpDID_u_DataPtr[54] = (uint8)(CompressorTemperatureTemp >> 8u);
	LpDID_u_DataPtr[55] = (uint8)(CompressorTemperatureTemp & 0xFFu);

	LpDID_u_DataPtr[56] = (uint8)(gs.error >> 24u);
	LpDID_u_DataPtr[57] = (uint8)(gs.error >> 16u);
	LpDID_u_DataPtr[58] = (uint8)(gs.error >> 8u);
	LpDID_u_DataPtr[59] = (uint8)(gs.error & 0xFFu);

	LpDID_u_DataPtr[60] = (uint8)(FridgeAppl_FridgeHALL_5VAD_Value() >> 8u);
    LpDID_u_DataPtr[61] = (uint8)(FridgeAppl_FridgeHALL_5VAD_Value() & 0xFFu);

    return ( uint8 )E_OK;
}

uint8 DID_Read0xF1F8( uint8 LpDID_u_DataPtr[] )
{
	
	uint32      signal_u_OdometerValue;
	uint16      signal_u_Speed;


	signal_u_Speed      	= (uint16)GetCanApp_u_EspVehSpd();
	signal_u_OdometerValue 	= (uint32)GetCanApp_u_CdcTotMilg();

	LpDID_u_DataPtr[0] = (uint8)(signal_u_OdometerValue & 0xFF);
	LpDID_u_DataPtr[1] = (uint8)((signal_u_OdometerValue >> 8)& 0xFF);
	LpDID_u_DataPtr[2] = (uint8)((signal_u_OdometerValue >> 16)& 0xFF);
	LpDID_u_DataPtr[3] = (uint8)(ADCM_GetValidValue(ADCMCFG_KL30_AD_CH) / 15.3);
	LpDID_u_DataPtr[4] = (uint8)( signal_u_Speed & 0xFF);
	LpDID_u_DataPtr[5] = (uint8)((signal_u_Speed >> 8) & 0xFF);
	LpDID_u_DataPtr[6] = RTE_NET_Can_Read_TboxLocalTiSec();
	LpDID_u_DataPtr[7] = RTE_NET_Can_Read_TboxLocalTiMins();
	LpDID_u_DataPtr[8] = RTE_NET_Can_Read_TboxLocalTiHr();
	LpDID_u_DataPtr[9] = RTE_NET_Can_Read_TboxLocalTiDate();
	LpDID_u_DataPtr[10] = RTE_NET_Can_Read_TboxLocalTiMth();
	LpDID_u_DataPtr[11] = RTE_NET_Can_Read_TboxLocalTiYear();

    return ( uint8 )E_OK;
}


uint8 DID_Read0xF1F9( uint8 LpDID_u_DataPtr[] )
{
    uint8 LeDID_u_Index;
	
	
	///////SWA.0.1.01

    for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)10U;LeDID_u_Index++)
    {
        LpDID_u_DataPtr[LeDID_u_Index] = CaDid_u_0xF1F9_ChangJiang_SWVersion[LeDID_u_Index];
    }
	
	
	////////HWA.0.1.01
	FLASH_DRV_ReadNVR(0, 0x10030150, 16, CUS_NVR_ReadDidF1F9);

    for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)10U;LeDID_u_Index++)
    {
        LpDID_u_DataPtr[10+LeDID_u_Index] = CUS_NVR_WriteDidF1F9[LeDID_u_Index];
		
    }
	
	//读取硬件电路
	 LpDID_u_DataPtr[20] = 0;
	
	////////FBL.0.1.01	

	for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)10U;LeDID_u_Index++)
    {
        LpDID_u_DataPtr[21+LeDID_u_Index] = src_ptr_Read0xF1F9[LeDID_u_Index];
    }
	
	return (uint8)E_OK;
}





void Check_DIDF1FA_CompressorFault(void)
{
	uint16 LeDCM_u_TimeoutCnt = 0;
    const uint16 LeDCM_u_TimeoutMax = 450; // 4.5秒超时（10ms/计数）

    //压缩机运行电压低
    g_EEP_WriteF1FA_Buf[0] = FLT_TEST_COMP_UNDERVOL();
    //压缩机运行电压高
    g_EEP_WriteF1FA_Buf[1] = FLT_TEST_COMP_OVERVOL();
	//压缩机温度过高
    g_EEP_WriteF1FA_Buf[2] = FLT_TEST_COMP_OVERTEMP();
	//电流缺相
    g_EEP_WriteF1FA_Buf[3] = FLT_TEST_COMP_LACK_PHASE_CURRENT();		
	//运行电流过高
    g_EEP_WriteF1FA_Buf[4] = FLT_TEST_COMP_OVER_PHASE_CURRENT();
	//压缩机限功率
    g_EEP_WriteF1FA_Buf[5] = FLT_TEST_COMP_OVERCURRENT();		/* 压缩机功率过高 */
	//板温过高
    g_EEP_WriteF1FA_Buf[6] = FLT_TEST_PCB_OVER_TEMP();
	//环温过高
    g_EEP_WriteF1FA_Buf[7] = 0;
	//运行速度超出超速额定运行速度
    g_EEP_WriteF1FA_Buf[8] = FLT_TEST_COMP_OVER_SPEED();
	//运行速度低于低速额定运行速度
    g_EEP_WriteF1FA_Buf[9] = FLT_TEST_COMP_UNDER_SPEED();	
	//堵转故障
    g_EEP_WriteF1FA_Buf[10] = FLT_TEST_COMP_STALL();
	//压缩机历史故障1
    g_EEP_WriteF1FA_Buf[11] = 0;
	//压缩机历史故障2
    g_EEP_WriteF1FA_Buf[12] = 0;
	//压缩机启动失败故障
    g_EEP_WriteF1FA_Buf[13] = FLT_TEST_COMP_STARTUP_FAIL();
	/* 压缩机重启次数 */
    g_EEP_WriteF1FA_Buf[14] = FridgeCool_StartupErrorFlag;		

	//制冷灯故障类型
    g_EEP_WriteF1FA_Buf[15] = 0u;
	//制热灯故障类型
    g_EEP_WriteF1FA_Buf[16] = 0u;
	//杀菌灯故障类型
    g_EEP_WriteF1FA_Buf[17] = 0u;			
	/* 风扇过流故障 */
    g_EEP_WriteF1FA_Buf[18] = FLT_TEST_FAN_FAULT();			
	/* 风扇欠流故障 */
    g_EEP_WriteF1FA_Buf[19] = FLT_TEST_FAN_UC_FAULT();
	/*压缩机故障 */
    g_EEP_WriteF1FA_Buf[20] = (uint8)(FAULT_Combined >> 24U);
    g_EEP_WriteF1FA_Buf[21] = (uint8)(FAULT_Combined >> 16u);
    g_EEP_WriteF1FA_Buf[22] = (uint8)(FAULT_Combined >> 8u);
    g_EEP_WriteF1FA_Buf[23] = (uint8)(FAULT_Combined & 0xFF);
    g_EEP_WriteF1FA_Buf[24] = 0u;
	//秒
    g_EEP_WriteF1FA_Buf[25] = RTE_NET_Can_Read_TboxLocalTiSec();
	//分
    g_EEP_WriteF1FA_Buf[26] = RTE_NET_Can_Read_TboxLocalTiMins();
	//时
    g_EEP_WriteF1FA_Buf[27] = RTE_NET_Can_Read_TboxLocalTiHr();
	//日
    g_EEP_WriteF1FA_Buf[28] = RTE_NET_Can_Read_TboxLocalTiDate();
	//月
    g_EEP_WriteF1FA_Buf[29] = RTE_NET_Can_Read_TboxLocalTiMth();
	//年
    g_EEP_WriteF1FA_Buf[30] = RTE_NET_Can_Read_TboxLocalTiYear();


	Nm_StateType  pApplCan_u_NMSt;
	Nm_ModeType   pApplCan_u_NMMode;

    CanNm_GetState(0U,&pApplCan_u_NMSt,&pApplCan_u_NMMode);


	if((pApplCan_u_NMSt == NM_STATE_BUS_SLEEP) && (g_EEP_WriteF1FA_flg == 0))
	{
		EEPM_AppWriteBlock(EEP_BLOCK_DIDF1FA_ID, &g_EEP_WriteF1FA_Buf[0]);
    	EEPM_MainFunction();
    	while(EEPM_GetSleepRequestStatus() == FALSE)
    	{
        	EEPM_MainFunction();
       	 	WDGM_Trigger();
        	NOP();
        	NOP();
			g_EEP_WriteF1FA_flg = 1; 
                // 检查超时
        	LeDCM_u_TimeoutCnt++;
        	if(LeDCM_u_TimeoutCnt > LeDCM_u_TimeoutMax)
        	{
            	// 超时，退出循环
           	 	break;
        	}
    	}
	}


	
}



uint8 DID_Read0xF1FA( uint8 LpDID_u_DataPtr[] )
{
    uint8 LeDID_u_Index;


    for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)90U;LeDID_u_Index++)
    {
        LpDID_u_DataPtr[LeDID_u_Index] = g_EEP_WriteF1FA_Buf[LeDID_u_Index];
    }


    return ( uint8 )E_OK;
}

uint8 DID_Read0xF1FB( uint8 LpDID_u_DataPtr[] )
{

    return ( uint8 )E_OK;
}


uint8 DID_Read0xF1FC( uint8 LpDID_u_DataPtr[] )
{
	EEPM_AppReadBlock(EEP_BLOCK_DIDF1FC_ID, &LpDID_u_DataPtr[0]);

    return ( uint8 )E_OK;
}


uint8 ReadMemory_ByAddress_23( DescMsgContext* pMsgContext )
{
 uint8 LeDCM_u_RetVal = (uint8)kDescNrcNone;  /* 返回值，初始化为成功 */
    uint32 LeMem_u_Address = 0u;                  /* 目标内存地址 */
    uint32 LeMem_u_Size = 0u;                     /* 要读取的内存大小 */
    uint8* LpReqData = pMsgContext->reqData;      /* 请求数据指针 */
    uint8* LpResData = pMsgContext->resData;      /* 响应数据指针 */
 
    /* 解析4字节地址 (大端序) */
    LeMem_u_Address = ((uint32)LpReqData[1] << 24) | 
                      ((uint32)LpReqData[2] << 16) | 
                      ((uint32)LpReqData[3] << 8) | 
                      (uint32)LpReqData[4];
 
    /* 解析2字节长度 (大端序) */
    LeMem_u_Size = ((uint32)LpReqData[5] << 8) | 
                   (uint32)LpReqData[6];
    /* 验证内存大小（0无效，最大4095字节） */
    if((LeMem_u_Size == 0u) || (LeMem_u_Size > 0xFFFFu))
    {
        return (uint8)kDescNrcRequestOutOfRange;
    }

    /* 验证地址范围:
     * - Flash: 0x00000000 - 0x0013FFFF 
     * - RAM:   0x1FFF0000 - 0x2000FFFF 
     */
    if( ((LeMem_u_Address >= 0x00000000u) && 
         (LeMem_u_Address + LeMem_u_Size <= 0x0013FFFFu)) ||
        ((LeMem_u_Address >= 0x1FFF0000u) && 
         (LeMem_u_Address + LeMem_u_Size <= 0x2000FFFF)) )
    {
        /* 地址有效，执行读取操作 */
        uint8* LpSrc_u_Ptr = (uint8*)LeMem_u_Address;


        /* 将内存数据复制到响应缓冲区 */
        for(uint8 i = 0u; i < (uint8)LeMem_u_Size; i++)
        {
            LpResData[i] = LpSrc_u_Ptr[i];
        }

        /* 设置响应数据长度 */
        pMsgContext->resDataLen = (uint16)LeMem_u_Size;
        LeDCM_u_RetVal = (uint8)kDescNrcNone;
    }
    else
    {
        /* 地址超出有效范围 */
        LeDCM_u_RetVal = (uint8)kDescNrcRequestOutOfRange;
    }

    return LeDCM_u_RetVal;
}

/**************************************************************************************************************
* 函数名称: WriteMemory_ByAddress_3D
* 功能描述: UDS服务0x3D (WriteMemoryByAddress) 实现函数
*          参考 ReadMemory_ByAddress_23 的格式，支持 SubFunction = 0x24
* 参数:
*   pMsgContext - 消息上下文指针，包含请求数据和响应数据缓冲区
* 返回值:
*   uint8 - 操作结果码
*           kDescNrcNone (0x00) - 成功
*           kDescNrcRequestOutOfRange (0x31) - 请求参数无效或地址越界
* 协议格式 (仅支持 SubFunction = 0x24):
*   请求数据格式: [0x3D] [0x24] [Address(4字节)] [Length(2字节)] [Data...]
*   SubFunction 0x24 固定格式:
*     - 地址: 4字节大端序
*     - 长度: 2字节大端序
*     - 数据: 要写入的内容
* 支持的地址范围:
*   - RAM:   0x1FFF0000 - 0x2000FFFF
**************************************************************************************************************/
uint8 WriteMemory_ByAddress_3D( DescMsgContext* pMsgContext )
{
     uint8 LeDCM_u_RetVal = (uint8)kDescNrcNone;  // 返回值，初始化为成功
    uint32 LeMem_u_Address = 0u;                  // 目标内存地址
    uint32 LeMem_u_Size = 0u;                     // 要写入的内存大小
    uint8* LpReqData = pMsgContext->reqData;      // 请求数据指针（指向 SubFunction）
	uint8* LpResData = pMsgContext->resData;
    uint8* LpSrcData = NULL;                      // 源数据指针

   
    // 步骤3: 解析4字节地址（大端序）
    LeMem_u_Address = ((uint32)LpReqData[1] << 24) |  // 第1字节（最高位）
                      ((uint32)LpReqData[2] << 16) |  // 第2字节
                      ((uint32)LpReqData[3] << 8) |   // 第3字节
                      (uint32)LpReqData[4];            // 第4字节（最低位）

    // 步骤4: 解析2字节长度（大端序）
    LeMem_u_Size = ((uint32)LpReqData[5] << 8) |      // 长度高字节
                   (uint32)LpReqData[6];               // 长度低字节

    // 步骤5: 验证长度有效性
    if((LeMem_u_Size == 0u) || (LeMem_u_Size > 0xFFFFu))
    {
        return (uint8)kDescNrcRequestOutOfRange;
    }

// 步骤8: 验证地址范围（RAM: 0x1FFF0000 - 0x2000FFFF）
if( (LeMem_u_Address >= 0x1FFF0000u) && 
    (LeMem_u_Address + LeMem_u_Size <= 0x2000FFFFu) )
{
    uint8* LpDst_u_Ptr = (uint8*)LeMem_u_Address;  // 目标地址指针

    // 步骤9: 执行写入操作
    for(uint8 i = 0u; i < (uint8)LeMem_u_Size; i++)
    {
        LpDst_u_Ptr[i] = LpReqData[i + 7u];  // 逐字节写入
    }

    LeDCM_u_RetVal = (uint8)kDescNrcNone;  // 写入成功
}
    else
    {
        LeDCM_u_RetVal = (uint8)kDescNrcRequestOutOfRange;  // 地址越界
    }

    return LeDCM_u_RetVal;
}







/**************************************************************************************************************
*************************************************************************************************************/


/*EOF*/

