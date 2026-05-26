/**
 * Copyright (c) 2021, Freqchip
 *
 * All rights reserved.
 *
 *
 */
#ifndef DRIVER_IIC_SOFT_H
#define DRIVER_IIC_SOFT_H

/*
 * INCLUDES (����ͷ�ļ�)
 */
#include <stdint.h>
/*
 * MACROS (�궨��)
 */

/*
 * CONSTANTS (��������)
 */

/*
 * TYPEDEFS (���Ͷ���)
 */

/*
 * GLOBAL VARIABLES (ȫ�ֱ���)
 */

/*
 * LOCAL VARIABLES (���ر���)
 */

/*
 * LOCAL FUNCTIONS (���غ���)
 */

/*
 * EXTERN FUNCTIONS (�ⲿ����)
 */

/*
 * PUBLIC FUNCTIONS (ȫ�ֺ���)
 */
uint8_t iic_Read_handle(uint8_t iic_addr, uint8_t read_reg, uint8_t *buff, uint8_t len);

uint8_t iic_Write_handle(uint8_t iic_addr, uint8_t write_reg, uint8_t *buff, uint8_t len);

uint8_t iic_Read_NoRegAddr_handle(uint8_t iic_addr, uint8_t *buff, uint8_t len);

uint8_t iic_Write_NoRegAddr_handle(uint8_t iic_addr, uint8_t *buff, uint8_t len);

void user_i2c_init(void);

#endif
