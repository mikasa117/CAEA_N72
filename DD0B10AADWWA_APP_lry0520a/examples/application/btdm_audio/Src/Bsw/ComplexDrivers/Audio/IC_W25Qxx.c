
#include "IC_W25Qxx.h"
#include "driver_spi.h"

/*********************************************************************************
 * function    :  IC_W25Qxx_WriteEnable
 * Description :  Write Enable
 * Input       :
 * Output      :
 * Author      :  Chris_Kyle                  Data : 2020
 **********************************************************************************/
void IC_W25Qxx_WriteEnable(void)
{
    uint8_t lu8_DataBuffer[1];

    lu8_DataBuffer[0] = WRITE_ENABLE;

    /* CS Select */
    __SPI_CS_Select();
    /* Send command */
    __SPI_Write_Data(lu8_DataBuffer, 1);
    /* CS Realse */
    __SPI_CS_Release();
}

/*********************************************************************************
 * function   :  IC_W25Qxx_WriteDisable
 * Description :  Write Disable
 * Input       :
 * Output      :
 * Author      :  Chris_Kyle                  Data : 2020
 **********************************************************************************/
void IC_W25Qxx_WriteDisable(void)
{
    uint8_t lu8_DataBuffer[1];

    lu8_DataBuffer[0] = WRITE_DISABLE;

    /* CS Select */
    __SPI_CS_Select();
    /* Send command */
    __SPI_Write_Data(lu8_DataBuffer, 1);
    /* CS Realse */
    __SPI_CS_Release();
}

/*********************************************************************************
 * function   :  IC_W25Qxx_WriteDisable
 * Description :  Write Disable
 * Input       :
 * Output      :
 * Author      :  Chris_Kyle                  Data : 2020
 **********************************************************************************/
void IC_W25Qxx_WriteRegister(uint8_t fu8_Register_S7_S0, uint8_t fu8_Register_S15_S08)
{
    uint8_t lu8_DataBuffer[3];

    lu8_DataBuffer[0] = WRITE_STATUS_REGISTER;
    lu8_DataBuffer[1] = fu8_Register_S7_S0;
    lu8_DataBuffer[2] = fu8_Register_S15_S08;

    /* Write Enable */
    IC_W25Qxx_WriteEnable();

    /* CS Select */
    __SPI_CS_Select();
    /* Send command */
    __SPI_Write_Data(lu8_DataBuffer, 3);
    /* CS Realse */
    __SPI_CS_Release();

    /* Wait Write register End */
    IC_W25Qxx_WaitBusy();
}

/*********************************************************************************
 * function   :  IC_W25Qxx_Read_ID
 * Description :  Read Manufacture ID and Device ID
 * Input       :
 * Output      :  Manufacture ID and Device ID
 * Author      :  Chris_Kyle                  Data : 2020
 **********************************************************************************/
uint16_t IC_W25Qxx_Read_ID(void)
{
    uint8_t lu8_DataBuffer[6];

    lu8_DataBuffer[0] = READ_DEVICE_ID;     // device id reg. is 0x90;
    lu8_DataBuffer[1] = 0;
    lu8_DataBuffer[2] = 0;
    lu8_DataBuffer[3] = 0;

    /* CS Select */
    __SPI_CS_Select();
    /* Send command */
    __SPI_Write_Data(lu8_DataBuffer, 4);
    /* Recieve Manufacture ID and Device ID */
    __SPI_Read_Data(lu8_DataBuffer, 2);
    /* CS Realse */
    __SPI_CS_Release();

    return ((uint16_t)lu8_DataBuffer[0] << 8 | (uint16_t)lu8_DataBuffer[1]);
}

/*********************************************************************************
 * function   :  IC_W25Qxx_Read_RegisterS07_S00
 * Description :  Read Status Register S07 ~ S00
 * Input       :
 * Output      :  Status Register S07 ~ S00
 * Author      :  Chris_Kyle                  Data : 2020
 **********************************************************************************/
uint8_t IC_W25Qxx_Read_RegisterS07_S00(void)
{
    uint8_t lu8_DataBuffer[1];

    lu8_DataBuffer[0] = READ_STATUS_REGISTER;

    /* CS Select */
    __SPI_CS_Select();
    /* Send command */
    __SPI_Write_Data(lu8_DataBuffer, 1);
    /* Recieve Status Register S07 ~ S00 */
    __SPI_Read_Data(lu8_DataBuffer, 1);
    /* CS Realse */
    __SPI_CS_Release();

    return lu8_DataBuffer[0];
}

#if 0
/*********************************************************************************
 * function   :  IC_W25Qxx_Read_RegisterS15_S08
 * Description :  Read Status Register S15 ~ S08
 * Input       :
 * Output      :  Status Register S15 ~ S08
 * Author      :  Chris_Kyle                  Data : 2020
 **********************************************************************************/
uint8_t IC_W25Qxx_Read_RegisterS15_S08(void)
{
    uint8_t lu8_DataBuffer[1];

    lu8_DataBuffer[0] = READ_STATUS_REGISTER_S15_S08;

    /* CS Select */
    __SPI_CS_Select();
    /* Send command */
    __SPI_Write_Data(lu8_DataBuffer, 1);
    /* Recieve Status Register S15 ~ S08 */
    __SPI_Read_Data(lu8_DataBuffer, 1);
    /* CS Realse */
    __SPI_CS_Release();

    return lu8_DataBuffer[0];
}
#endif

/*********************************************************************************
 * function   :  IC_W25Qxx_Read_Data
 * Description :  Read Data
 * Input       :
 * Output      :
 * Author      :  Chris_Kyle                  Data : 2020
 **********************************************************************************/
void IC_W25Qxx_Read_Data(uint8_t *pu8_Buffer, uint32_t fu32_DataAddress, uint32_t fu32_Length)
{
    uint8_t lu8_DataBuffer[4];

    lu8_DataBuffer[0] = READ_DATA;
    lu8_DataBuffer[1] = (uint8_t)(fu32_DataAddress >> 16 & 0xFF);
    lu8_DataBuffer[2] = (uint8_t)(fu32_DataAddress >> 8 & 0xFF);
    lu8_DataBuffer[3] = (uint8_t)(fu32_DataAddress >> 0 & 0xFF);

    /* CS Select */
    __SPI_CS_Select();
    /* Send command and Recieve Data */
    __SPI_Read_flash_X1(lu8_DataBuffer, 4, pu8_Buffer, fu32_Length);
    /* CS Realse */
    __SPI_CS_Release();
}

/*********************************************************************************
 * function   :  IC_W25Qxx_Read_Dual_Output
 * Description :  Dual Output Fast Read
 * Input       :
 * Output      :
 * Author      :  Chris_Kyle                  Data : 2020
 **********************************************************************************/
void IC_W25Qxx_Read_Dual_Output(uint8_t *pu8_Buffer, uint32_t fu32_DataAddress, uint32_t fu32_Length)
{
    SPI0_Handle.MultWireParam.Wire_X2X4X8 = Wire_X2;
    SPI0_Handle.MultWireParam.ReceiveWaitCycles = 8;
    SPI0_Handle.MultWireParam.InstructLength = INST_8BIT;
    SPI0_Handle.MultWireParam.Instruct = DUAL_OUTPUT_FAST_READ;
    SPI0_Handle.MultWireParam.AddressLength = ADDR_24BIT;
    SPI0_Handle.MultWireParam.Address = fu32_DataAddress;

    /* CS Select */
    __SPI_CS_Select();
    /* Send Data */
    __SPI_Read_Data_X2X4(pu8_Buffer, fu32_Length);
    /* CS Realse */
    __SPI_CS_Release();
}

/*********************************************************************************
 * function   :  IC_W25Qxx_Read_Quad_Output
 * Description :  Quad Output Fast Read
 * Input       :
 * Output      :
 * Author      :  Chris_Kyle                  Data : 2020
 **********************************************************************************/
void IC_W25Qxx_Read_Quad_Output(uint8_t *pu8_Buffer, uint32_t fu32_DataAddress, uint32_t fu32_Length)
{
    SPI0_Handle.MultWireParam.Wire_X2X4X8 = Wire_X4;
    SPI0_Handle.MultWireParam.ReceiveWaitCycles = 8;
    SPI0_Handle.MultWireParam.InstructLength = INST_8BIT;
    SPI0_Handle.MultWireParam.Instruct = QUAD_OUTPUT_FAST_READ;
    SPI0_Handle.MultWireParam.AddressLength = ADDR_24BIT;
    SPI0_Handle.MultWireParam.Address = fu32_DataAddress;

    /* CS Select */
    __SPI_CS_Select();
    /* Send Data */
    __SPI_Read_Data_X2X4(pu8_Buffer, fu32_Length);
    /* CS Realse */
    __SPI_CS_Release();
}

/*********************************************************************************
 * function   :  IC_W25Qxx_PageProgram
 * Description :  Page Program
 * Input       :
 * Output      :
 * Author      :  Chris_Kyle                  Data : 2020
 **********************************************************************************/
void IC_W25Qxx_PageProgram(uint8_t *pu8_Buffer, uint32_t fu32_DataAddress, uint32_t fu32_Length)
{
    uint8_t lu8_DataBuffer[4];

    lu8_DataBuffer[0] = PAGE_PROGARM;
    lu8_DataBuffer[1] = (uint8_t)(fu32_DataAddress >> 16 & 0xFF);
    lu8_DataBuffer[2] = (uint8_t)(fu32_DataAddress >> 8 & 0xFF);
    lu8_DataBuffer[3] = (uint8_t)(fu32_DataAddress >> 0 & 0xFF);

    /* Write Enable */
    IC_W25Qxx_WriteEnable();

    /* CS Select */
    __SPI_CS_Select();
    /* Send command */
    __SPI_Write_Data(lu8_DataBuffer, 4);
    /* Send Data */
    __SPI_Write_Data(pu8_Buffer, fu32_Length);
    /* CS Realse */
    __SPI_CS_Release();

    /* Wait Erase End */
    IC_W25Qxx_WaitBusy();
}

/*********************************************************************************
 * function   :  IC_W25Qxx_PageProgram_Quad
 * Description :  Quad Page Program
 * Input       :
 * Output      :
 * Author      :  Chris_Kyle                  Data : 2020
 **********************************************************************************/
void IC_W25Qxx_PageProgram_Quad(uint8_t *pu8_Buffer, uint32_t fu32_DataAddress, uint32_t fu32_Length)
{
    SPI0_Handle.MultWireParam.Wire_X2X4X8 = Wire_X4;
    SPI0_Handle.MultWireParam.InstructLength = INST_8BIT;
    SPI0_Handle.MultWireParam.Instruct = QUAD_PAGE_PROGRAM;
    SPI0_Handle.MultWireParam.AddressLength = ADDR_24BIT;
    SPI0_Handle.MultWireParam.Address = fu32_DataAddress;

    /* Write Enable */
    IC_W25Qxx_WriteEnable();

    /* CS Select */
    __SPI_CS_Select();
    /* Send Data */
    __SPI_Write_Data_X2X4(pu8_Buffer, fu32_Length);
    /* CS Realse */
    __SPI_CS_Release();

    /* Wait Erase End */
    IC_W25Qxx_WaitBusy();
}

/*********************************************************************************
 * function   :  IC_W25Qxx_EraseSector
 * Description :  Erease The specific Sector
 * Input       :
 * Output      :
 * Author      :  Chris_Kyle                  Data : 2020
 **********************************************************************************/
void IC_W25Qxx_EraseSector(uint32_t fu32_DataAddress)
{
    uint8_t lu8_DataBuffer[4];

    lu8_DataBuffer[0] = SECTOR_ERASE;
    lu8_DataBuffer[1] = (uint8_t)(fu32_DataAddress >> 16 & 0xFF);
    lu8_DataBuffer[2] = (uint8_t)(fu32_DataAddress >> 8 & 0xFF);
    lu8_DataBuffer[3] = (uint8_t)(fu32_DataAddress >> 0 & 0xFF);

    /* Write Enable */
    IC_W25Qxx_WriteEnable();

    /* CS Select */
    __SPI_CS_Select();
    /* Send command */
    __SPI_Write_Data(lu8_DataBuffer, 4);
    /* CS Realse */
    __SPI_CS_Release();

    /* Wait Erase End */
    IC_W25Qxx_WaitBusy();
}

/*********************************************************************************
 * function   :  IC_W25Qxx_EraseChip
 * Description :  Erease The Whole Chip
 * Input       :
 * Output      :
 * Author      :  Chris_Kyle                  Data : 2020
 **********************************************************************************/
void IC_W25Qxx_EraseChip(void)
{
    uint8_t lu8_DataBuffer[1];

    lu8_DataBuffer[0] = CHIP_ERASE;

    /* Write Enable */
    IC_W25Qxx_WriteEnable();

    /* CS Select */
    __SPI_CS_Select();
    /* Send command */
    __SPI_Write_Data(lu8_DataBuffer, 1);
    /* CS Realse */
    __SPI_CS_Release();

    /* Wait Erase End */
    IC_W25Qxx_WaitBusy();
}

/*********************************************************************************
 * function   :  IC_W25Qxx_QuadConfig
 * Description :  Quad Function Config
 * Input       :
 * Output      :
 * Author      :  Chris_Kyle                  Data : 2020
 **********************************************************************************/
void IC_W25Qxx_QuadConfig(bool fb_Config)
{
    #if 0
    if (fb_Config == true)
    {
        /* Set W25Qxx Quad Enable */
        IC_W25Qxx_WriteRegister(WRITE_STATUS_REGISTER, REGISTER_STATUS_QE); // REGISTER_S15_S08_QE
    }
    else
    {
        /* Set W25Qxx Quad Disable */
        IC_W25Qxx_WriteRegister(WRITE_STATUS_REGISTER, WRITE_STATUS_REGISTER);
    }
    #endif
}

/*********************************************************************************
 * function   :  IC_W25Qxx_WaitBusy
 * Description :  Wait IC Not Busy
 * Input       :
 * Output      :
 * Author      :  Chris_Kyle                  Data : 2020
 **********************************************************************************/
void IC_W25Qxx_WaitBusy(void)
{
    /* Wait IC Not Busy */
    while (IC_W25Qxx_Read_RegisterS07_S00() & REGISTER_STATUS_WIP);
}

/*********************************************************************************
 * function   :  IC_W25Qxx_PowerDown
 * Description :
 * Input       :
 * Output      :
 * Author      :  Chris_Kyle                  Data : 2020
 **********************************************************************************/
void IC_W25Qxx_PowerDown(void)
{
    uint8_t lu8_DataBuffer[1];

    lu8_DataBuffer[0] = DEEP_POWER_DOWN;

    /* CS Select */
    __SPI_CS_Select();
    /* Send command */
    __SPI_Write_Data(lu8_DataBuffer, 1);
    /* CS Realse */
    __SPI_CS_Release();
}

/*********************************************************************************
 * function   :  IC_W25Qxx_Wakeup
 * Description :
 * Input       :
 * Output      :
 * Author      :  Chris_Kyle                  Data : 2020
 **********************************************************************************/
void IC_W25Qxx_Wakeup(void)
{
    uint8_t lu8_DataBuffer[1];

    lu8_DataBuffer[0] = RELEASE_FORM_DEEP_POWER_DOWN;

    /* CS Select */
    __SPI_CS_Select();
    /* Send command */
    __SPI_Write_Data(lu8_DataBuffer, 1);
    /* CS Realse */
    __SPI_CS_Release();
}

/*********************************************************************************
 * function   :  IC_W25Qxx_Reset
 * Description :  W25Qxx Reset
 * Input       :
 * Output      :
 * Author      :  Chris_Kyle                  Data : 2020
 **********************************************************************************/
void IC_W25Qxx_Reset(void)
{
    uint8_t lu8_DataBuffer[1];

    lu8_DataBuffer[0] = ENABLE_RESET;

    /* CS Select */
    __SPI_CS_Select();
    /* Send command */
    __SPI_Write_Data(lu8_DataBuffer, 1);
    /* CS Realse */
    __SPI_CS_Release();

    lu8_DataBuffer[0] = RESET;

    /* CS Select */
    __SPI_CS_Select();
    /* Send command */
    __SPI_Write_Data(lu8_DataBuffer, 1);
    /* CS Realse */
    __SPI_CS_Release();
}
