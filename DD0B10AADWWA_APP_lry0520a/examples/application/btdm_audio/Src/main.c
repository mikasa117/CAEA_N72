/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "fr30xx.h"

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

#include "fdb_app.h"
#include "host.h"

#include "app_task.h"
#include "app_at.h"
#include "audio_scene.h"
#include "app_rpmsg.h"

#include "EcuM.h"
#include "Rte_Can.h"
#include "app_bt.h"
//#include "audio_codec.h"
#include "driver_wdt.h"

#include "CanDem.h"

#include "fdb_def.h"
#include "fdb_app.h"
#include "DID_Callback.h"
#include "heap.h"
/* hardware handlers */
UART_HandleTypeDef Uart3_handle;
static CALI_HandleTypeDef cali_handle;

#if ENABLE_RTOS_MONITOR == 1
/* FreeRTOS running status monitor task */
static TaskHandle_t monitor_task_handle;
volatile unsigned int CPU_RunTime;
static uint8_t CPU_RunInfo[2048];
#endif

/* APP task */
TaskHandle_t app_task_handle;

void controller_start(void);
void host_start(void);

#if defined(__ARMCC_VERSION) || defined(__CC_ARM)
int fputc(int c, FILE *fp)
{
    uart_transmit(&Uart3_handle, (void *)&c, 1);

    return c;
}
#endif

#ifdef __GNUC__
int _write(int file, char *ptr, int len)
{
    uart_transmit(&Uart3_handle, (void *)ptr, len);
    return len;
}
#endif

#ifdef __ICCARM__
int putchar(int c)
{
    uart_transmit(&Uart3_handle, (void *)&c, 1);
    while(!(Uart3_handle.UARTx->USR.TFE));
    return c;
}
#endif

#if ENABLE_RTOS_MONITOR == 1
static void monitor_task(void *arg)
{
    unsigned int available_mem = 0u;
    unsigned int usage_mem = 0u;
    float usage_rate = 0.0f;
    while(1) {
        vTaskDelay(10000);

        memset(CPU_RunInfo,0,2048);
        vTaskList((char *)&CPU_RunInfo);
        printf("---------------------------------------------\r\n");
        printf("name           	state     priority  stack     seq\r\n");
        printf("%s", CPU_RunInfo);
        printf("---------------------------------------------\r\n");
        
        memset(CPU_RunInfo,0,400);
        vTaskGetRunTimeStats((char *)&CPU_RunInfo);
        printf("name                counter             usage\r\n");
        printf("%s", CPU_RunInfo);
        printf("---------------------------------------------\r\n");

        available_mem = heap_get_mem_available(HEAP_TYPE_SRAM_BLOCK);
        usage_mem = heap_get_mem_usage(HEAP_TYPE_SRAM_BLOCK);
        usage_rate = (float)usage_mem / (float)(available_mem + usage_mem) * 100.0f;
        printf("sram heap available: %d usage: %d usage rate %.2f %% \r\n", available_mem, usage_mem, usage_rate);
        printf("---------------------------------------------\r\n");

        available_mem = heap_get_mem_available(HEAP_TYPE_BTDM_BLOCK);
        usage_mem = heap_get_mem_usage(HEAP_TYPE_BTDM_BLOCK);
        usage_rate = (float)usage_mem / (float)(available_mem + usage_mem) * 100.0f;
        printf("btdm heap available: %d usage: %d usage rate %.2f %% \r\n", available_mem, usage_mem, usage_rate);
        printf("---------------------------------------------\r\n");

        usage_mem = heap_get_max_mem_usage_single(HEAP_TYPE_SRAM_BLOCK);
        usage_rate = (float)usage_mem / (float)(configTOTAL_HEAP_SIZE) * 100.0f;
        printf("sram heap max usage: %d usage rate %.2f %% \r\n", usage_mem, usage_rate);
        printf("---------------------------------------------\r\n");
        usage_mem = heap_get_max_mem_usage_single(HEAP_TYPE_BTDM_BLOCK);
        usage_rate = (float)usage_mem / (float)(30 * 1024) * 100.0f;
        printf("btdm heap max usage: %d usage rate %.2f %% \r\n", usage_mem, usage_rate);
        printf("---------------------------------------------\r\n");
    }
}
#endif

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

    printf("task :%s overflow\r\n",pcTaskName);
	assert( 0 );
}

void vApplicationTickHook(void)
{
    #if ENABLE_RTOS_MONITOR == 1
    CPU_RunTime++;
    #endif
}
	
static void cali_done_handle(CALI_HandleTypeDef *hcali, uint32_t result)
{
    system_set_LPRCCLK(cali_calc_rc_freq(hcali, result));
    system_prevent_sleep_clear(SYSTEM_PREVENT_SLEEP_TYPE_CALIBRATION);
}

__RAM_CODE void hw_clock_init(void)
{
    System_ClkConfig_t ClkConfig;

    /* CORE HSCLK Config */
    ClkConfig.CORE_HSCLK_CFG.CORE_HSCLK_Source = CORE_HSCLK_SEL_HES;
    /* PLL clock = HSE_VALUE*N + (HSE_VALUE/65535)*M */
    /* SPLL CLK Config */
    ClkConfig.SPLL_CFG.PowerEn = PLL_POWER_ENABLE;
    ClkConfig.SPLL_CFG.PLL_N = 8;
    ClkConfig.SPLL_CFG.PLL_M = 0;
    /* AUPLL clock = HSE_VALUE*N + HSE_VALUE*(K/D) */
    /* AUPLL CLK Config */
    ClkConfig.AUPLL_CFG.PowerEn = PLL_POWER_ENABLE;
    ClkConfig.AUPLL_CFG.PLL_N = 6;
    ClkConfig.AUPLL_CFG.PLL_K = 219;
    ClkConfig.AUPLL_CFG.PLL_D = 625;

    System_CORE_HSCLK_config(&ClkConfig.CORE_HSCLK_CFG);
    if (System_SPLL_config(&ClkConfig.SPLL_CFG, 200) == -1)
        while (1)
            ;
    if (System_AUPLL_config(&ClkConfig.AUPLL_CFG, 200) == -1)
        while (1)
            ;

    ClkConfig.MCU_Clock_Source = MCU_CLK_SEL_SPLL_CLK;
    ClkConfig.SOC_DIV = 1; /* This parameter is valid when MCU_Clock_Source == MCU_CLK_SEL_SPLL_CLK */
    ClkConfig.MCU_DIV = 1;
    ClkConfig.APB0_DIV = 1;
    ClkConfig.APB1_DIV = 1;
    ClkConfig.APB2_DIV = 1;

    System_MCU_clock_Config(&ClkConfig);
    __SYSTEM_UART_CLK_SELECT_SPLL();
}

__RAM_CODE void hw_xip_flash_init(bool wake_up)
{
    System_XIPConfig_t xip_config;
    xip_config.CLK_SRC_SEL = XIP_CLK_SEL_SPLL;
    xip_config.DIV_SEL = QSPI_BAUDRATE_DIV_4;
    xip_config.RD_TYPE = FLASH_RD_TYPE_QUAD;
    xip_config.WR_TYPE = FLASH_WR_TYPE_SINGLE;
    system_xip_flash_init(&xip_config, wake_up);
}

__RAM_CODE bool user_deep_sleep_check(void)
{
    return host_before_sleep_check();
}

__RAM_CODE void user_entry_before_sleep(void)
{
    while(!(Uart3_handle.UARTx->USR.TFE));
    system_delay_us(100);
    ool_write16(PMU_REG_PIN_PULL_EN, 0x3fff);
    ool_write16(PMU_REG_PIN_PULL_SEL, 0x3ffd);

    ool_write(PMU_REG_PMU_GATE_M, ool_read(PMU_REG_PMU_GATE_M) | 0x40);
}

__RAM_CODE void user_entry_after_sleep(void)
{
    /* 
     * enable pull up of all 3.3v IO, these configuration will be latched by set 
     * BIT6 of PMU_REG_PMU_GATE_M regsiter. used to avoid electric leakage
     */
    SYSTEM->PortA_PullSelect = 0x0000ffff;
    SYSTEM->PortB_PullSelect = 0x0000fff7;
    SYSTEM->PortC_PullSelect = 0x0000ffff;
    SYSTEM->PortD_PullSelect = 0x0000ffff;
    SYSTEM->PortE_PullSelect = 0x0000ffff;
    SYSTEM->PortA_PullEN = 0x0000ffff;
    SYSTEM->PortB_PullEN = 0x0000ffff;
    SYSTEM->PortC_PullEN = 0x0000ffff;
    SYSTEM->PortD_PullEN = 0x0000ffff;
    SYSTEM->PortE_PullEN = 0x0000ffff;
    SYSTEM->QspiPadConfig.QSPI_PullEN = 0x0000000;
    
    SYSTEM->PortA_InputOpenCircuit = 0xFFFFFFFF;
    SYSTEM->PortB_InputOpenCircuit = 0xFFFFFFFF;
    SYSTEM->PortC_InputOpenCircuit = 0xFFFFFFFF;
    SYSTEM->PortD_InputOpenCircuit = 0xFFFFFFFF;
    SYSTEM->PortE_InputOpenCircuit = 0xFFFFFFFF;

    hw_clock_init();
    hw_xip_flash_init(true);
    host_hci_reinit();
    ool_write(PMU_REG_PMU_GATE_M, ool_read(PMU_REG_PMU_GATE_M) & (~0x40));
    
    GPIO_InitTypeDef gpio_config;

    /* configure all interrupt priority to 2 */
    *(volatile uint32_t *)0xE000E400 = 0x40404040;
    *(volatile uint32_t *)0xE000E404 = 0x40404040;
    *(volatile uint32_t *)0xE000E408 = 0x40404040;
    *(volatile uint32_t *)0xE000E40C = 0x40404040;
    *(volatile uint32_t *)0xE000E410 = 0x40404040;
    *(volatile uint32_t *)0xE000E414 = 0x40404040;
    *(volatile uint32_t *)0xE000E418 = 0x40404040;
    *(volatile uint32_t *)0xE000E41C = 0x40404040;
    *(volatile uint32_t *)0xE000E420 = 0x40404040;
    *(volatile uint32_t *)0xE000E424 = 0x40404040;
    *(volatile uint32_t *)0xE000E428 = 0x40404040;
    *(volatile uint32_t *)0xE000E42C = 0x40404040;
    *(volatile uint32_t *)0xE000E430 = 0x40404040;
    *(volatile uint32_t *)0xE000E434 = 0x40404040;
    *(volatile uint32_t *)0xE000E438 = 0x40404040;
    *(volatile uint32_t *)0xE000E43C = 0x40404040;
    *(volatile uint32_t *)0xE000E440 = 0x40404040;

    NVIC_SetPriority(UART0_IRQn, 2);
    NVIC_EnableIRQ(UART0_IRQn);
    NVIC_SetPriority(PMU_IRQn, 4);
    NVIC_EnableIRQ(PMU_IRQn);
    
    /* configure PB4 and PB5 to UART3 function */
    __SYSTEM_GPIOB_CLK_ENABLE();
    gpio_config.Pin = GPIO_PIN_4 | GPIO_PIN_5;
    gpio_config.Mode = GPIO_MODE_AF_PP;
    gpio_config.Pull = GPIO_PULLUP;
    gpio_config.Alternate = GPIO_FUNCTION_1;
    gpio_init(GPIOB, &gpio_config);
    
    /* UART0: used for Log and AT command */
    __SYSTEM_UART3_CLK_ENABLE();
    Uart3_handle.UARTx = UART3;
    Uart3_handle.Init.BaudRate   = 921600;
    Uart3_handle.Init.DataLength = UART_DATA_LENGTH_8BIT;
    Uart3_handle.Init.StopBits   = UART_STOPBITS_1;
    Uart3_handle.Init.Parity     = UART_PARITY_NONE;
    Uart3_handle.Init.FIFO_Mode  = UART_FIFO_ENABLE;
    Uart3_handle.TxCpltCallback  = NULL;
    Uart3_handle.RxCpltCallback  = app_at_rx_done;
    uart_init(&Uart3_handle);
    NVIC_SetPriority(UART3_IRQn, 4);
    NVIC_EnableIRQ(UART3_IRQn);
    
    {
        static bool first_wakeup = true;
        bool do_calib = false;
        static TickType_t last_tick;
        TickType_t curr_tick;
        if (first_wakeup) {
            first_wakeup = false;
            last_tick = xTaskGetTickCount();
            curr_tick = last_tick;
            do_calib = true;
        }
        else {
            curr_tick = xTaskGetTickCount();
            if ((curr_tick - last_tick) > 10000) {
                last_tick = curr_tick;
                do_calib = true;
            }
        }
        
        if (do_calib) {
            /* restart calibration */
            __SYSTEM_CALI_CLK_ENABLE();
            cali_handle.mode = CALI_UP_MODE_NORMAL;
            cali_handle.rc_cnt = 60;
            cali_handle.DoneCallback = cali_done_handle;
            cali_init(&cali_handle);
            cali_start_IT(&cali_handle);
            system_prevent_sleep_set(SYSTEM_PREVENT_SLEEP_TYPE_CALIBRATION);
            NVIC_SetPriority(CALI_IRQn, 2);
            NVIC_EnableIRQ(CALI_IRQn);
        }
    }
    app_rpmsg_recover();
}

__RAM_CODE void user_entry_after_sleep_user(void)
{
}

#ifdef UART2_PRINT
UART_HandleTypeDef Uart2_handle;
UART_HandleTypeDef *uart2Handler()
{
    return &Uart2_handle;
}
void aec_test_uart_init()
{
    GPIO_InitTypeDef gpio_config;
    __SYSTEM_GPIOB_CLK_ENABLE();
    gpio_config.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    gpio_config.Mode = GPIO_MODE_AF_PP;
    gpio_config.Pull = GPIO_PULLUP;
    gpio_config.Alternate = GPIO_FUNCTION_1;
    gpio_init(GPIOB, &gpio_config);

    __SYSTEM_UART2_CLK_ENABLE();
    Uart2_handle.UARTx = UART2;
    Uart2_handle.Init.BaudRate = 3000000;
    Uart2_handle.Init.DataLength = UART_DATA_LENGTH_8BIT;
    Uart2_handle.Init.StopBits = UART_STOPBITS_1;
    Uart2_handle.Init.Parity = UART_PARITY_NONE;
    Uart2_handle.Init.FIFO_Mode = UART_FIFO_ENABLE;
    Uart2_handle.TxCpltCallback = NULL;
    Uart2_handle.RxCpltCallback = NULL;
    uart_init(&Uart2_handle);

    NVIC_EnableIRQ(UART2_IRQn);
    NVIC_SetPriority(UART2_IRQn, 4);

    // uint8_t tttt[16];
    // for (size_t i = 0; i < 16; i++)
    // {
    //     tttt[i] = i + 8;
    // }
    // uart_transmit(uart4Handler(), tttt, 16);
}
#endif
static void interrupt_init(void)
{
    /* configure all interrupt priority to 2 */
    *(volatile uint32_t *)0xE000E400 = 0x40404040;
    *(volatile uint32_t *)0xE000E404 = 0x40404040;
    *(volatile uint32_t *)0xE000E408 = 0x40404040;
    *(volatile uint32_t *)0xE000E40C = 0x40404040;
    *(volatile uint32_t *)0xE000E410 = 0x40404040;
    *(volatile uint32_t *)0xE000E414 = 0x40404040;
    *(volatile uint32_t *)0xE000E418 = 0x40404040;
    *(volatile uint32_t *)0xE000E41C = 0x40404040;
    *(volatile uint32_t *)0xE000E420 = 0x40404040;
    *(volatile uint32_t *)0xE000E424 = 0x40404040;
    *(volatile uint32_t *)0xE000E428 = 0x40404040;
    *(volatile uint32_t *)0xE000E42C = 0x40404040;
    *(volatile uint32_t *)0xE000E430 = 0x40404040;
    *(volatile uint32_t *)0xE000E434 = 0x40404040;
    *(volatile uint32_t *)0xE000E438 = 0x40404040;
    *(volatile uint32_t *)0xE000E43C = 0x40404040;
    *(volatile uint32_t *)0xE000E440 = 0x40404040;
}

static void user_uart_init(void)
{
    GPIO_InitTypeDef gpio_config;
    __SYSTEM_GPIOA_CLK_ENABLE();
    /* configure PB4 and PB5 to UART3 function */
    gpio_config.Pin = GPIO_PIN_4 | GPIO_PIN_5;
    gpio_config.Mode = GPIO_MODE_AF_PP;
    gpio_config.Pull = GPIO_PULLUP;
    gpio_config.Alternate = GPIO_FUNCTION_1;
    gpio_init(GPIOB, &gpio_config);

    /* UART3: used for Log and AT command */
    __SYSTEM_UART3_CLK_ENABLE();
    Uart3_handle.UARTx = UART3;
    Uart3_handle.Init.BaudRate   = 921600;
    Uart3_handle.Init.DataLength = UART_DATA_LENGTH_8BIT;
    Uart3_handle.Init.StopBits   = UART_STOPBITS_1;
    Uart3_handle.Init.Parity     = UART_PARITY_NONE;
    Uart3_handle.Init.FIFO_Mode  = UART_FIFO_ENABLE;
    Uart3_handle.TxCpltCallback  = NULL;
    Uart3_handle.RxCpltCallback  = app_at_rx_done;
    uart_init(&Uart3_handle);
    NVIC_EnableIRQ(UART3_IRQn);
    NVIC_SetPriority(UART3_IRQn, 4);
}

static void user_cali_init(void)
{
    /* do calibration, get current RC frequency */
    __SYSTEM_CALI_CLK_ENABLE();
    cali_handle.mode = CALI_UP_MODE_NORMAL;
    cali_handle.rc_cnt = 200;
    cali_handle.DoneCallback = cali_done_handle;
    cali_init(&cali_handle);
    cali_start_IT(&cali_handle);
    system_prevent_sleep_set(SYSTEM_PREVENT_SLEEP_TYPE_CALIBRATION);
    NVIC_SetPriority(CALI_IRQn, 4);
    NVIC_EnableIRQ(CALI_IRQn);
}

int main( void )
{
    uint32_t error;

    //system_delay_us(1000000);


    interrupt_init();

    pmu_init();

    /* initial system clock and XIP flash */
    hw_clock_init();
    hw_xip_flash_init(false);
		flashdb_init();  
    EcuM_InitMemery();
    
    user_uart_init();

    user_cali_init();
    
    /* init flashdb to store user data */


    /* get random seed*/
    uint32_t rand_num;    
    size_t size = flashdb_get(FDB_KEY_RANDOM_SEED, (void *)&rand_num, 4);
    //printf("flashdb get random seed :%d\r\n",size);
    if(size == 0){
        __SYSTEM_TRNG_CLK_ENABLE();
        trng_init();
        trng_read_rand_num((uint8_t *)&rand_num,4);
        flashdb_set(FDB_KEY_RANDOM_SEED,(uint8_t *)&rand_num,4);
        __SYSTEM_TRNG_CLK_DISABLE();
    }
    srand(rand_num);
    printf("flash db get rand num: %x\r\n",rand_num);
    /* Create tasks */
#if ENABLE_RTOS_MONITOR == 1
    xTaskCreate(monitor_task, "monitor", MONITOR_TASK_STACK_SIZE, NULL, MONITOR_TASK_PRIORITY, &monitor_task_handle);
#endif

    
    uds_flash_get(USER_ID_UDS_F190, DID0xF190DefaultValue,USERID_DATA_LEN(USER_ID_UDS_F190));
    app_task_init();
    audio_scene_init(AUDIO_SCENE_TASK_STACK_SIZE, AUDIO_SCENE_TASK_PRIORITY);

    /* initialize AT command */
    app_at_init(&Uart3_handle);

    wdt_init(WDT, WDT_MODE_0, 3000000); // 3s
    wdt_start(WDT);

    /* Start the scheduler itself. */
    vTaskStartScheduler();
		
    return 0;
}

void uart3_irq(void)
{
    uart_IRQHandler(&Uart3_handle);
}

void PMU_GPIO_PMU_IRQHandler(void)
{
    uint16_t data = ool_read16(PMU_REG_PIN_DATA);
    uint16_t result = ool_read16(PMU_REG_PIN_XOR_RESULT);
    
    /* update last value with latest data */
    ool_write16(PMU_REG_PIN_LAST_V, data);
    /* clear last XOR result */
    ool_write16(PMU_REG_PIN_XOR_CLR, result);
    
    if (data & PMU_PIN_9) {
        system_prevent_sleep_clear(SYSTEM_PREVENT_SLEEP_TYPE_HCI_RX);
    }
    else {
        system_prevent_sleep_set(SYSTEM_PREVENT_SLEEP_TYPE_HCI_RX);
    }
}

void cali_irq(void)
{
    cali_IRQHandler(&cali_handle);
}

