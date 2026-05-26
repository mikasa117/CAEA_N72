/**
 * Copyright (c) 2021, Freqchip
 * 
 * All rights reserved.
 * 
 * 
 */
#ifndef HCI_TEST_H
#define HCI_TEST_H
 
 /*
 * INCLUDES (包含头文件)
 */
#include <stdint.h>
#include <stdbool.h>

#include "driver_uart.h"
/*
 * MACROS (宏定义)
 */
#define GOVEE_TEST_MODE

#define GOVEE_SKU_MAX_LEN 5
#define GOVEE_VERSION_MAX_LEN   7
//#define GOVEE_FLASH_DATA_BLOCK_SIZE         512
//#define GOVEE_FLASH_DATA_BLOCK_COUNT        (0x1000/512)
//#define HCI_TEST_MAC_ADDR 0xF7000
//#define HCI_TEST_SKU_BASE 0xF9000
//#define HCI_TEST_SKU_BACK 0xF8000
//#define PCB_TEST          0xF6000
#define FREQ_ADJUST_STORE_ADDR              0x3000
/*
 * CONSTANTS (常量定义)
 */


/*
 * TYPEDEFS (类型定义)
 */



/*
 * GLOBAL VARIABLES (全局变量)
 */
extern UART_HandleTypeDef HCI_handle;          //kernel communication UART0
extern UART_HandleTypeDef Uart3_handle;

/*
 * LOCAL VARIABLES (本地变量)
 */
 
/*
 * LOCAL FUNCTIONS (本地函数)
 */

/*
 * EXTERN FUNCTIONS (外部函数)
 */

/*
 * PUBLIC FUNCTIONS (全局函数)
 */

void user_at_func(uint8_t * cmd_buff,uint8_t len);

void dev_freq_adjust_check(void);

void host_hci_uart_init(uint32_t baudrate);

void dev_freq_adjust_check(void);
    
void dev_msg_init(uint8_t * s_version,uint8_t s_version_len,uint8_t * h_version,uint8_t h_version_len);

uint8_t dev_in_hci_mode(void);

uint8_t dev_check_hci_test_mode(void);

void	hci_test_start(void);

void  bt_dut_test_start(void);

#endif
