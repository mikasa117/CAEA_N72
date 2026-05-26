/*
 ******************************************************************************
 * @file    IC_W25Qxx.h
 * @author  FreqChip Firmware Team
 * @version V1.0.0
 * @date    2020
 * @brief   IC_W25Qxx Config header file.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2020 FreqChip.
 * All rights reserved.
 ******************************************************************************
 */
#ifndef __IC_W25QXX_H__
#define __IC_W25QXX_H__

#include "fr30xx.h"

extern SPI_HandleTypeDef SPI0_Handle;

#define __SPI_CS_Release() gpio_write_pin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET)

#define __SPI_CS_Select() gpio_write_pin(GPIOD, GPIO_PIN_1, GPIO_PIN_CLEAR)

#define __SPI_Read_Data(__BUFFER__, __SIZE__) spi_master_receive_X1(&SPI0_Handle, __BUFFER__, __SIZE__)

#define __SPI_Write_Data(__BUFFER__, __SIZE__) spi_master_transmit_X1(&SPI0_Handle, __BUFFER__, __SIZE__)

//#define __SPI_Read_flash_X1(__CMD__, __CSIZE__, __BUFFER__, __SIZE__) spi_master_readflash_X1(&SPI0_Handle, (uint16_t *)__CMD__, __CSIZE__, __BUFFER__, __SIZE__)
#define __SPI_Read_flash_X1(__CMD__, __CSIZE__, __BUFFER__, __SIZE__) spi_master_readflash_X1(&SPI0_Handle, (uint8_t *)__CMD__, __CSIZE__, __BUFFER__, __SIZE__)

#define __SPI_Write_Data_X2X4(__BUFFER__, __SIZE__) spi_master_transmit_X2X4X8(&SPI0_Handle, __BUFFER__, __SIZE__)

#define __SPI_Read_Data_X2X4(__BUFFER__, __SIZE__) spi_master_receive_X2X4X8(&SPI0_Handle, __BUFFER__, __SIZE__)

/*********************************************************************************
                          One Block have 32K

           Block                Setor                 Address Range

                                  17               0x011000 ~ 0x011FFF
                                  16               0x010000 ~ 0x010FFF
                                  15               0x00F000 ~ 0x00FFFF
                                  14               0x00E000 ~ 0x00EFFF
             1                    13               0x00D000 ~ 0x00DFFF
                                  12               0x00C000 ~ 0x00CFFF
                                  11               0x00B000 ~ 0x00BFFF
                                  10               0x00A000 ~ 0x00AFFF
                                  9                0x009000 ~ 0x009FFF

                                  8                0x008000 ~ 0x008FFF
                                  7                0x007000 ~ 0x007FFF
                                  6                0x006000 ~ 0x006FFF
                                  5                0x005000 ~ 0x005FFF
             0                    4                0x004000 ~ 0x004FFF
                                  3                0x003000 ~ 0x003FFF
                                  2                0x002000 ~ 0x002FFF
                                  1                0x001000 ~ 0x001FFF
                                  0                0x000000 ~ 0x000FFF
**********************************************************************************/

/**
 * @brief  W25Qxx Size
 */
#define W25QXX_PAGE_SIZE 	(256U)    // Each Page has 256 Bytes
#define W25QXX_SECTOR_SIZE 	(4096U) // Each Sector has 4k
#define W25QXX_BLOCK_SIZE   (65536U)  // Each Block has 16 sectors, 64 kbyts in all

/**
 * @brief  W25Qxx Command Descriptions
 */
#define WRITE_ENABLE (0x06)
#define WRITE_DISABLE (0x04)
#define READ_STATUS_REGISTER                     (0x05)
//#define READ_STATUS_REGISTER_S15_S08             (0x35)
#define WRITE_STATUS_REGISTER (0x01)
//#define WRITE_ENABLE_VOLATILE_STATUS_REGISTER    (0x50)
#define READ_FUNCTION_REGISTER                   (0x48)
#define WRITE_FUNCTION_REGISTER                  (0x42)

#define READ_DATA                                (0x03)
#define READ_DATA_FAST                           (0x0B)
#define DUAL_OUTPUT_FAST_READ                    (0x3B)
#define QUAD_OUTPUT_FAST_READ                    (0x6B)
#define DUAL_IO_FAST_READ                        (0xBB)
#define QUAD_IO_FAST_READ                        (0xEB)
#define SET_BURST_WITH_WRAP                      (0xC0) // (0x77)
#define PAGE_PROGARM                             (0x02)
#define QUAD_PAGE_PROGRAM                        (0x32)

#define SECTOR_ERASE                             (0xD7) // (0x20)
#define BLOCK_ERASE_32K                          (0x52)
#define BLOCK_ERASE_64K                          (0xD8)
#define CHIP_ERASE                               (0xC7)

#define READ_DEVICE_ID                           (0x90)
#define READ_ID                                  (0xAB) // (0x9F)
#define READ_UNIQUE_ID                           (0x4B)
#define READ_SFDP                                (0x5A)
#define READ_JEDEC_ID                            (0x9F)

/*
#define ERASE_SECURITY_REGISTER (0x44)
#define PROGRAM_SECURITY_REGISTER (0x42)
#define READ_SECURITY_REGISTER (0x48)
*/
#define ERASE_INFOMATION_ROW                     (0x64)
#define PROGRAM_INFOMATION_ROW                   (0x62)
#define READ_INFOMATION_ROW                      (0x68)

#define ENABLE_RESET                             (0x66)
#define RESET                                    (0x99)
#define PROGRAM_ERASE_SUSPEND                    (0x75)
#define PROGRAM_ERASE_RESUME                     (0x7A)

#define DEEP_POWER_DOWN                          (0xB9)
#define RELEASE_FORM_DEEP_POWER_DOWN             (0xAB)
//#define READ_DATA_COMPATIBILITY                  (0x5A)

#define NOP_OPERATION                            (0x00)
#define ENTER_QPI_MODE                           (0x35)
#define EXIT_QPI_MODE                            (0xF5)

/**
 * @brief  W25Qxx Stauts Register
 */
//#define REGISTER_NULL (0)
/*
#define REGISTER_STATUS_SRP0    (1 << 7)
#define REGISTER_STATUS_BP4     (1 << 6)
#define REGISTER_STATUS_BP3     (1 << 5)
#define REGISTER_STATUS_BP2     (1 << 4)
#define REGISTER_STATUS_BP1     (1 << 3)
#define REGISTER_STATUS_BP0     (1 << 2)
#define REGISTER_STATUS_WEL     (1 << 1)
#define REGISTER_STATUS_WIP     (1 << 0)
*/
#define REGISTER_STATUS_SRWD    (1 << 7)
#define REGISTER_STATUS_QE      (1 << 6)  // Quad enable
#define REGISTER_STATUS_BP3     (1 << 5)
#define REGISTER_STATUS_BP2     (1 << 4)
#define REGISTER_STATUS_BP1     (1 << 3)   
#define REGISTER_STATUS_BP0     (1 << 2)
#define REGISTER_STATUS_WEL     (1 << 1)
#define REGISTER_STATUS_WIP     (1 << 0)

#if 0
#define REGISTER_S15_S08_SUS     (1 << 7)
#define REGISTER_S15_S08_CMP     (1 << 6)
#define REGISTER_S15_S08_NULL    (1 << 5)
#define REGISTER_S15_S08_DC      (1 << 4)
#define REGISTER_S15_S08_LB1     (1 << 3)
#define REGISTER_S15_S08_LB0     (1 << 2)
#define REGISTER_S15_S08_QE      (1 << 1)    // Quad Enable
#define REGISTER_S15_S08_SRP1    (1 << 0)
#endif

/*
 * Function registers
 */
#define REGISTER_FUNC_IRL3       (1 << 7)
#define REGISTER_FUNC_IRL2       (1 << 6)
#define REGISTER_FUNC_IRL1       (1 << 5)
#define REGISTER_FUNC_IRL0       (1 << 4)
#define REGISTER_FUNC_ESUS       (1 << 3)
#define REGISTER_FUNC_PSUS       (1 << 2)
#define REGISTER_FUNC_RES1       (1 << 1) // Reserved
#define REGISTER_FUNC_RES0       (1 << 0) // Reserved

/* Function : IC_W25Qxx_WriteEnable */
void IC_W25Qxx_WriteEnable(void);

/* Function : IC_W25Qxx_WriteDisable */
void IC_W25Qxx_WriteDisable(void);

/* Function : IC_W25Qxx_WriteRegister */
void IC_W25Qxx_WriteRegister(uint8_t fu8_Register_S7_S0, uint8_t fu8_Register_S15_S08);

/* Function : IC_W25Qxx_Read_ID */
uint16_t IC_W25Qxx_Read_ID(void);

/* Function : IC_W25Qxx_Read_RegisterS07_S00 */
uint8_t IC_W25Qxx_Read_RegisterS07_S00(void);

/* Function : IC_W25Qxx_Read_RegisterS15_S08 */
//uint8_t IC_W25Qxx_Read_RegisterS15_S08(void);

/* Function : IC_W25Qxx_Read */
void IC_W25Qxx_Read_Data(uint8_t *pu8_Buffer, uint32_t fu32_DataAddress, uint32_t fu32_Length);

/* Function : IC_W25Qxx_Read_Dual_Output */
void IC_W25Qxx_Read_Dual_Output(uint8_t *pu8_Buffer, uint32_t fu32_DataAddress, uint32_t fu32_Length);

/* Function : IC_W25Qxx_Read_Quad_Output */
void IC_W25Qxx_Read_Quad_Output(uint8_t *pu8_Buffer, uint32_t fu32_DataAddress, uint32_t fu32_Length);

/* Function : IC_W25Qxx_PageProgram */
void IC_W25Qxx_PageProgram(uint8_t *pu8_Buffer, uint32_t fu32_DataAddress, uint32_t fu32_Length);

/* Function : IC_W25Qxx_PageProgram_Quad */
void IC_W25Qxx_PageProgram_Quad(uint8_t *pu8_Buffer, uint32_t fu32_DataAddress, uint32_t fu32_Length);

/* Function : IC_W25Qxx_EraseSector */
void IC_W25Qxx_EraseSector(uint32_t fu32_DataAddress);

/* Function : IC_W25Qxx_EraseChip */
void IC_W25Qxx_EraseChip(void);

/* Function : IC_W25Qxx_QuadConfig */
void IC_W25Qxx_QuadConfig(bool fb_Config);

/* Function : IC_W25Qxx_WaitBusy */
void IC_W25Qxx_WaitBusy(void);

/* Function : IC_W25Qxx_Reset */
void IC_W25Qxx_Reset(void);

/* Function : IC_W25Qxx_PowerDown */
void IC_W25Qxx_PowerDown(void);

/* Function : IC_W25Qxx_Wakeup */
void IC_W25Qxx_Wakeup(void);

#endif
