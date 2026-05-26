/*******************************************************************************
|  File Name:
|  Description:
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Zhejiang Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| FSL           fengshulin           CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2023-02-02    01.00.00     fsl       Creation
|
|******************************************************************************/
/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/

#include "DID_Callback.h"
#include "STD_Lib.h"
#include "desc.h"
#include "Appl_DID_Callback.h"
#include "CanDem.h"
#include "fdb_def.h"
#include "fdb_app.h"
#include "base.h"
#include "DTC_Callback.h"
#include "adc_if.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/*******************************************************************************
|    Enum Definition
|******************************************************************************/
extern V_MEMROM0 V_MEMROM1 tFblHeader V_MEMROM2* FblHeader;
/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/
uint8 DID0xF190DefaultValue[DID_F190_LEN] = {
		0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,
		0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u};
static uint8 DID0xF1A2DefaultValue[DID_F1A2_LEN] = {
		0x20u,0x00u,0x01u,0x01u};
static uint8 DID0xF199DefaultValue[DID_F199_LEN] = {
		0x20u,0x00u,0x01u,0x01u};
static uint8 DID0xF112DefaultValue[DID_F112_LEN] = {
		0x4Eu,0x37u,0x32u,0x20u,0x20u,0x20u,0x20u,0x20u};
static uint8 DID0xF18CDefaultValue[DID_F18C_LEN] = {
		0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,
		0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,
		0x30u,0x30u,0x30u,0x30u};
static uint8 DID0x0200DefaultValue[DID_0200_LEN] = {0};
static uint8 DID0x0201DefaultValue[DID_0201_LEN] = {0};

static uint8 DID0xF101DefaultValue[DID_F101_LEN] = {
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u};

static uint8 DID0xF110DefaultValue[DID_F110_LEN] = {
		0x12u,0x00u,0x00u,0x49u,0x40u,0x91u,0x2Du,0x1Au};

static uint8 DID0xF197DefaultValue[DID_F197_LEN] = {
		0x42u,0x54u,0x4Du,0x30u,0x30u,0x30u,0x30u,0x30u};

static uint8 DID0xD135DefaultValue[DID_D135_LEN] = {
    0x30, 0x68, 0x6F, 0x6A, 0x77, 0x61, 0x4A, 0x45,
    0x57, 0x53, 0x62, 0x76, 0x6B, 0x6D, 0x41, 0x45};		

static uint8 DID0xF198DefaultValue[DID_F198_LEN] = {
		0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,
		0x30u,0x30u,0x30u,0x30u,0x30u,0x30u};


/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/
extern uint8_t uds_flash_set(uint16_t id, uint8_t *value, uint32_t length);
extern uint8_t uds_flash_get(uint16_t id, uint8_t *value, uint32_t length);
/*******************************************************************************
|    Extern functions declaration
|******************************************************************************/

/*******************************************************************************
|    Extern variables declaration
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/

/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
static void App_WritableDID_Traversal(uint32 address, uint8 *Data, uint32 length)
{
	uint8 HasBeenWrittenFlag = 1u;
	uint8 Temp[24];

	uds_flash_get(address,Temp,length);

	for(uint8 i = 0; i < length; i++)
	{
	    if(Temp[i] != 0xFFu)
	    {
	    	HasBeenWrittenFlag = 0u;
	    }
	}

	if(1u == HasBeenWrittenFlag)
	{
		uds_flash_set(address,Data,length);
	}
	else
	{
		;
	}
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
void CanDcm_InitMemory(void)
{
	App_WritableDID_Traversal(USER_ID_UDS_F190,DID0xF190DefaultValue,USERID_DATA_LEN(USER_ID_UDS_F190));
	//App_WritableDID_Traversal(FDBKEY_FROM_USERID(USER_ID_UDS_F1A2),DID0xF1A2DefaultValue,USERID_DATA_LEN(USER_ID_UDS_F1A2));
	//App_WritableDID_Traversal(FDBKEY_FROM_USERID(USER_ID_UDS_F112),DID0xF112DefaultValue,USERID_DATA_LEN(USER_ID_UDS_F112));
	App_WritableDID_Traversal(USER_ID_UDS_F101,DID0xF101DefaultValue,USERID_DATA_LEN(USER_ID_UDS_F101));
//	App_WritableDID_Traversal(FDBKEY_FROM_USERID(USER_ID_UDS_F199),DID0xF199DefaultValue,USERID_DATA_LEN(USER_ID_UDS_F199));
//	App_WritableDID_Traversal(FDBKEY_FROM_USERID(USER_ID_UDS_F198),DID0xF198DefaultValue,USERID_DATA_LEN(USER_ID_UDS_F198));
//	App_WritableDID_Traversal(FDBKEY_FROM_USERID(USER_ID_UDS_F197),DID0xF197DefaultValue,USERID_DATA_LEN(USER_ID_UDS_F197));
//	App_WritableDID_Traversal(FDBKEY_FROM_USERID(USER_ID_UDS_D135),DID0xD135DefaultValue,USERID_DATA_LEN(USER_ID_UDS_D135));
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****Programming Or Configuration Date*****/
uint8 DID_Read0xF199(uint8 DataPtr[])
{
	FblHeader->pApplFblNvReadDataByIdentifier(0xF199u,DataPtr,DID_F199_LEN);
	
	return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****Geely Spare Part Number****/
uint8 DID_Read0xF187(uint8 DataPtr[])
{
    uint8 Data_F187[DID_F187_LEN] = {"9900320774           "};

    LIB_Copy(DataPtr, Data_F187, DID_F187_LEN);

    return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****System Supplier Identifier*****/
uint8 DID_Read0xF18A(uint8 DataPtr[])
{
    uint8 Data_F18A[DID_F18A_LEN] = {"577077"};

    LIB_Copy(DataPtr, Data_F18A, DID_F18A_LEN);

    return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****VIN*****/
uint8 DID_Write0xF190(uint8 LpDID_u_DataPtr[])
{
	uint8 ReVal = 0xff;

	ReVal = uds_flash_set(USER_ID_UDS_F190, LpDID_u_DataPtr, USERID_DATA_LEN(USER_ID_UDS_F190));
	
  return (uint8)ReVal;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
uint8 DID_Read0xF190(uint8 DataPtr[])
{
	uint8 LeDID_u_Index;
	static uint8 Read0xF190_DataPtr[17] = {0};

	
	uds_flash_get(USER_ID_UDS_F190, Read0xF190_DataPtr,USERID_DATA_LEN(USER_ID_UDS_F190));
	
	

	if((Read0xF190_DataPtr[0] == 0x00) || (Read0xF190_DataPtr[0] == 0xFF))
	{
			uint8 defaultVal[17] = {0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u,0x30u};  

			LIB_Copy(DataPtr, defaultVal, 17);
	}
	else
	{
		for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)17U;LeDID_u_Index++)
		{
			DataPtr[LeDID_u_Index] = Read0xF190_DataPtr[LeDID_u_Index];
		}
	}
	

  return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****ECU Installation Date*****/
uint8 DID_Write0xF1A2(uint8 LpDID_u_DataPtr[])
{
		uint8 ReVal = 0xff;

		ReVal = uds_flash_set(USER_ID_UDS_F1A2, LpDID_u_DataPtr, USERID_DATA_LEN(USER_ID_UDS_F1A2));
	
    return (uint8)ReVal;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
uint8 DID_Read0xF1A2(uint8 DataPtr[])
{
	uint8 LeDID_u_Index;
	static uint8 Read0xF1A2_DataPtr[4] = {0};
	
	
	uds_flash_get(USER_ID_UDS_F1A2, Read0xF1A2_DataPtr,USERID_DATA_LEN(USER_ID_UDS_F1A2));
	

	if((Read0xF1A2_DataPtr[0] == 0x00) || (Read0xF1A2_DataPtr[0] == 0xFF))
	{
			uint8 defaultVal[4] = {0x20,0x00,0x01,0x01};  

			LIB_Copy(DataPtr, defaultVal, 4);
	}
	else
	{
			for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)4U;LeDID_u_Index++)
			{
					DataPtr[LeDID_u_Index] = Read0xF1A2_DataPtr[LeDID_u_Index];
			}
	}
	

	return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****Manufacturer ECU Hardware Version Number*****/
uint8 DID_Read0xF191(uint8 DataPtr[])
{
    uint8 Data_F191[DID_F191_LEN] = {"HW002.001 "};

    LIB_Copy(DataPtr, Data_F191, DID_F191_LEN);

    return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****Manufacturer ECU Software Version Number*****/
uint8 DID_Read0xF189(uint8 DataPtr[])
{

    uint8  Data_F189[DID_F189_LEN] = {"SW102.013 "};

    LIB_Copy(DataPtr, Data_F189, DID_F189_LEN);

    return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****System Supplier ECU Hardware Version Number*****/
uint8 DID_Read0xF193(uint8 DataPtr[])
{
    uint8 Data_F193[DID_F193_LEN] = {"HW002.001       "};

    LIB_Copy(DataPtr, Data_F193, DID_F193_LEN);

    return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****System Supplier ECU Software Version Number*****/
uint8 DID_Read0xF195(uint8 DataPtr[])
{
    uint8 Data_F195[DID_F195_LEN] = {"SW002.001       "};

    LIB_Copy(DataPtr, Data_F195, DID_F195_LEN);

    return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****Boot Software Identification*****/
uint8 DID_Read0xF180(uint8 DataPtr[])
{
    uint8 Data_F180[DID_F180_LEN] = {"BV002.003       "};

    LIB_Copy(DataPtr, Data_F180, DID_F180_LEN);

    return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****Calibration Software Version Number*****/
uint8 DID_Read0xF182(uint8 DataPtr[])
{
    uint8 Data_F182[DID_F182_LEN] = {"CV001.001       "};

    LIB_Copy(DataPtr, Data_F182, DID_F182_LEN);

    return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****Vehicle Name*****/
uint8 DID_Write0xF112(uint8 LpDID_u_DataPtr[])
{
		uint8 ReVal = 0xff;
	
		ReVal = uds_flash_set(USER_ID_UDS_F112, LpDID_u_DataPtr, USERID_DATA_LEN(USER_ID_UDS_F112));
    
    return (uint8)ReVal;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
uint8 DID_Read0xF112(uint8 DataPtr[])
{
	uint8 LeDID_u_Index;
	static uint8 Read0xF112_DataPtr[8] = {0};
		
	
	uds_flash_get(USER_ID_UDS_F112, Read0xF112_DataPtr,USERID_DATA_LEN(USER_ID_UDS_F112));
	


	if((Read0xF112_DataPtr[0] == 0x00) || (Read0xF112_DataPtr[0] == 0xFF))
	{
			uint8 defaultVal[8] = {'N','7','2',' ',' ',' ',' ',' '};

			LIB_Copy(DataPtr, defaultVal, 8);
	}
	else
	{
			for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)8U;LeDID_u_Index++)
			{
					DataPtr[LeDID_u_Index] = Read0xF112_DataPtr[LeDID_u_Index];
			}
	}
	

	return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****Repair Shop Code Or Tester Serial Number*****/
uint8 DID_Read0xF198(uint8 DataPtr[])
{
	FblHeader->pApplFblNvReadDataByIdentifier(0xF198u,DataPtr,DID_F198_LEN);
	
	return (uint8)E_OK;
}

/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****Vehicle Name*****/
uint8 DID_Write0xF197(uint8 LpDID_u_DataPtr[])
{
		uint8 ReVal = 0xff;
	
		ReVal = uds_flash_set(USER_ID_UDS_F197, LpDID_u_DataPtr, USERID_DATA_LEN(USER_ID_UDS_F197));
    
    return (uint8)ReVal;
}

/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****System Name*****/


uint8 DID_Read0xF197(uint8 DataPtr[])
{
	uint8 LeDID_u_Index;
	static uint8 Read0xF197_DataPtr[8] = {0};
		

	uds_flash_get(USER_ID_UDS_F197, Read0xF197_DataPtr,USERID_DATA_LEN(USER_ID_UDS_F197));
	
	if(Read0xF197_DataPtr[0] == 0)
	{
			uint8 defaultVal[8] = {'B','T','M',' ',' ',' ',' ',' '};  

			LIB_Copy(DataPtr, defaultVal, 8);
	}
	else
	{
		  for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)8U;LeDID_u_Index++)
			{
					DataPtr[LeDID_u_Index] = Read0xF197_DataPtr[LeDID_u_Index];
			}
	}

  return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****Diagnostic Version*****/
uint8 DID_Read0xF113(uint8 DataPtr[])
{
    uint8 Data_F113[DID_F113_LEN] = {0x02u,0x00u,0x01u,0x00u};

    LIB_Copy(DataPtr, Data_F113, DID_F113_LEN);

    return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****Active Diagnostic Session*****/
uint8 DID_Read0xF186(uint8 DataPtr[])
{
	uint8 Data_F186[DID_F186_LEN] = {0};
	uint8 CurrentSession = DescGetStateSession();

	Data_F186[0] = (CurrentSession == 0x04u) ? 3u : CurrentSession;

  LIB_Copy(DataPtr, Data_F186, DID_F186_LEN);

  return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****ECU Manufacturing Date*****/
uint8 DID_Read0xF18B(uint8 DataPtr[])
{
	uint8 Data_F18B[DID_F18B_LEN] = {0x20u,0x00u,0x01u,0x01u};

  LIB_Copy(DataPtr, Data_F18B, DID_F18B_LEN);

  return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****ECU Serial Number*****/
uint8 DID_Write0xF18C(uint8 LpDID_u_DataPtr[])
{
	uint8 ReVal = 0xff;

	return (uint8)ReVal;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
uint8 DID_Read0xF18C(uint8 DataPtr[])
{
	LIB_Copy(DataPtr, DID0xF18CDefaultValue, DID_F18C_LEN);

	return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****Programming Counter*****/
uint8 DID_Read0x0200(uint8 DataPtr[])
{
	FblHeader->pApplFblNvReadDataByIdentifier(0x0200u,DataPtr,DID_0200_LEN);
	
	return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****Programming Attemp Counter*****/
uint8 DID_Read0x0201(uint8 DataPtr[])
{
	FblHeader->pApplFblNvReadDataByIdentifier(0x0201u,DataPtr,DID_0201_LEN);

	return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
uint8 DID_Read0x7501(uint8 DataPtr[])
{
	uint8 Data_7501[1] = {0x00u};
	
	if(adc_if_get_validValue(adc_cl_mic_8v_cs) < MIC_CURRENT_LOW)
	{
		Data_7501[0] = 1u;
	}
	else if((adc_if_get_validValue(adc_cl_mic_8v_cs) > MIC_CURRENT_HIGH0 )&&(adc_if_get_validValue(adc_cl_mic_8v_cs) < MIC_CURRENT_HIGH1))
	{
	  Data_7501[0] = 0u;
	}
	else
	{
		;
	}

  LIB_Copy(DataPtr, Data_7501, DID_7501_LEN);
		
	return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	

uint8 DID_Read0x7502(uint8 DataPtr[])
{
	uint8 Data_7502[DID_7502_LEN] = {0x00u,0x00u};
	uint16 get_validValue;
	
	get_validValue = adc_if_get_validValue(adc_cl_bat) ;


	Data_7502[0] =  get_validValue & 0xFF;
	Data_7502[1] = (get_validValue >> 8) & 0xFF;
	
  LIB_Copy(DataPtr, Data_7502, DID_7502_LEN);
		
	return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****ECU Function Configuration*****/
uint8 DID_Write0xF101(uint8 LpDID_u_DataPtr[])
{
		uint8 ReVal = 0xff;
	
		ReVal = uds_flash_set(USER_ID_UDS_F101, LpDID_u_DataPtr, USERID_DATA_LEN(USER_ID_UDS_F101));
    
    return (uint8)ReVal;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
uint8 DID_Read0xF101(uint8 DataPtr[])
{
	uint8 LeDID_u_Index;
	static uint8 Read0xF101_DataPtr[8] = {0};
	
	
	uds_flash_get(USER_ID_UDS_F101, Read0xF101_DataPtr,USERID_DATA_LEN(USER_ID_UDS_F101));
	
	for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)8U;LeDID_u_Index++)
  {
		DataPtr[LeDID_u_Index] = Read0xF101_DataPtr[LeDID_u_Index];
  }

	return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****Vehicle Network Configuration*****/
uint8 DID_Write0xF110(uint8 LpDID_u_DataPtr[])
{
	uint8 ReVal = 0xff;
	
	ReVal = uds_flash_set(USER_ID_UDS_F110, LpDID_u_DataPtr, USERID_DATA_LEN(USER_ID_UDS_F110));
    
  return (uint8)ReVal;

}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
uint8 DID_Read0xF110(uint8 DataPtr[])
{
	uint8 LeDID_u_Index;
	static uint8 Read0xF110_DataPtr[16] = {0};
	
	
	uds_flash_get(USER_ID_UDS_F110, Read0xF110_DataPtr,USERID_DATA_LEN(USER_ID_UDS_F110));
	
	for(LeDID_u_Index=0U;LeDID_u_Index<(uint8)16U;LeDID_u_Index++)
  {
		DataPtr[LeDID_u_Index] = Read0xF110_DataPtr[LeDID_u_Index];
  }

	return (uint8)E_OK;
}
/*******************************************************************************
|  Function Name    :
|  Syntax           :
|  Sync/Async       : Synchronous
|  Reentrancy       : Non-reentrant
|  Parameters (in)  : None
|  Parameters (out) : None
|  Return value     : None
|  Description      :
|  Call By          : Internal
*******************************************************************************/	
/*****S27-Level 1 PKC*****/

uint8 DID_Write0xD135(uint8 LpDID_u_DataPtr[])
{
	  uint8 DID_D135BufTemp[DID_D135_LEN] = {0};
		
		for(uint8 i = 0;i<DID_D135_LEN;i++)
		{
			DID_D135BufTemp[i] = LpDID_u_DataPtr[i];
		}
		
		FblHeader->pApplFblNvLevel1PkcNumber(DID_D135BufTemp,0,DID_D135_LEN,2);
	
		return (uint8)E_OK;
	
}


/*****DID List End*****/
