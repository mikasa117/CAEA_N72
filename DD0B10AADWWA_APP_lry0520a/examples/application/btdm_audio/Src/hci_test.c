#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "co_util.h"

#include "gatt_api.h"
#include "gap_api.h"

#include "FreeRTOS.h"
#include "timers.h"
#include "task.h"
#include "app_ble.h"
#include "app_at.h"
#include "app_task.h"
#include "hci_test.h"
#include "me_api.h"
#include "btdm_host.h"

#define AT_RECV_MAX_LEN             64
#define HOST_RECV_MAX_LEN           64
#define FREQ_ADJUST_NUM             12

enum EVT_STATUS
{
    EVT_AT,
    EVT_HCI,
};
enum
{
    MAC_ADDR_WRITE,
    MAC_ADDR_READ,
    SKU_WRITE,
    SKU_READ,
    VER_READ,
    EARSE_TEST,
    HCI_TX_SINGLE_POWER,
    FREQ_ADJUST,
};

enum EVT_STATUS evt_status = EVT_HCI;

static uint8_t hci_test_mode = 0;
static uint8_t hci_get_rf_freq = 0;
static uint8_t app_at_recv_char;
static uint8_t hci_recv_char;
static uint8_t hci_recv_state = 0;
static uint8_t hci_recv_param_len = 0;

static uint8_t host_recv_index = 0;
static uint8_t host_hci_recv_state = 0;
static uint8_t host_recv_buffer[HOST_RECV_MAX_LEN];
static uint8_t host_rf_freq_default = 0x58;
static uint8_t cur_freq_adjust_val = 0xFF;

uint16_t recv_len = 0;
uint8_t recv_type = 0;
uint32_t recv_val = 0;
static uint32_t Rx_Packet_NUM =0; //Fixed frequency test RX
void  bt_dut_test(void);

struct user_uart_recv_t //串口接收数据结构体
{
  uint8_t length;
  uint8_t indx;
  uint8_t recv_data[AT_RECV_MAX_LEN];
  uint8_t start_flag;
  uint8_t finish_flag;
};

typedef struct _govee_sku_config_t
{
//    uint8_t sku[GOVEE_SKU_MAX_LEN +1];
    uint8_t crc; 
} govee_sku_config_t;

struct user_uart_recv_t uart_recv = {
    .length = 0,
    .indx = 0,
    .recv_data = {0},
    .start_flag = 0,
    .finish_flag = 0,
};

static void dev_freq_adjust_store(uint8_t adjust_val)
{
    uint8_t store_data[10] = {'f','r','e','q',0xff,0xff,'c','h','i','p'};
    
    store_data[4] = adjust_val;
    store_data[5] = adjust_val^0xff;
    flash_OTP_erase(QSPI0,FREQ_ADJUST_STORE_ADDR);
    flash_OTP_write(QSPI0,FREQ_ADJUST_STORE_ADDR,sizeof(store_data),store_data);
}

void dev_freq_adjust_check(void)
{
    uint8_t hci_cmd[8];
    uint8_t get_data[10] = {0};
    uint8_t check_temp = 0;
    uint8_t osc_adjust_val = 0;
    flash_OTP_read(QSPI0,FREQ_ADJUST_STORE_ADDR,sizeof(get_data),get_data);

    if(!memcmp(get_data,"freq",4) && !memcmp(&get_data[6],"chip",4))
    {
        check_temp = get_data[4]^0xff;
        if(check_temp == get_data[5])
        {
            host_rf_freq_default = get_data[4];
            cur_freq_adjust_val = host_rf_freq_default & 0x0f;
        }
    }
    else
    {

    }
    
    if(cur_freq_adjust_val <= FREQ_ADJUST_NUM)
    {
        osc_adjust_val = host_rf_freq_default;
        // set freq reg
        hci_cmd[0] = 0x01;
        hci_cmd[1] = 0x71;
        hci_cmd[2] = 0xfc;
        hci_cmd[3] = 0x04;
        hci_cmd[4] = 0x01;
        hci_cmd[5] = 0x02;
        hci_cmd[6] = 0xec; // tx_power reg
        hci_cmd[7] = osc_adjust_val;
        uart_transmit(&HCI_handle,hci_cmd,8);
        vTaskDelay(3);
        //co_printf("=freq aujust=%d\r\n",cur_freq_adjust_val);
    }
}

void user_at_func(uint8_t * cmd_buff,uint8_t len)
{
    uint8_t rsp_data[32] = {0x01,0xE0,0xFC};
    uint8_t hci_cmd[32] = {0};
    uint8_t *buff = cmd_buff;
    uint8_t i = 0;
    
    switch(buff[0])
    {
        case MAC_ADDR_WRITE:
//            flash_erase(HCI_TEST_MAC_ADDR,0);
//            dev_flash_write_data(HCI_TEST_MAC_ADDR,buff+1,6);
            rsp_data[3] = 7;
            rsp_data[4] = 0x60;
            memcpy(rsp_data+5,buff+1,6);
            uart_transmit(&Uart3_handle,rsp_data,(rsp_data[3]+4));
        break;
        case MAC_ADDR_READ:
        {
//            uint8_t mac_addr[6];
//            flash_read(HCI_TEST_MAC_ADDR,6,mac_addr);
//            dev_flash_read_data(HCI_TEST_MAC_ADDR,mac_addr,6);
            struct gap_ble_addr local_addr;
            gap_get_local_address(&local_addr);
            rsp_data[3] = 7;
            rsp_data[4] = 0x61;
            for(i = 0;i < 6;i++)
                rsp_data[5+i] = local_addr.addr.addr[5-i];//local_addr.addr[5-i];
            uart_transmit(&Uart3_handle,rsp_data,(rsp_data[3]+4));
        }
        break;
        case SKU_WRITE:
        {
            uint8_t sku_data[7] = {0};

            memcpy(sku_data,buff+1,GOVEE_SKU_MAX_LEN+1);
//            sku_data[6] =  chargovee_sku_crc_check(buff+1,GOVEE_SKU_MAX_LEN);
//            //co_printf("=sku val=%x\r\n",sku_data[6]); 
//            flash_erase(HCI_TEST_SKU_BASE,0);
//            flash_erase(HCI_TEST_SKU_BACK,0);

//            flash_write(HCI_TEST_SKU_BASE,GOVEE_SKU_MAX_LEN+2,sku_data);
//            flash_write(HCI_TEST_SKU_BACK,GOVEE_SKU_MAX_LEN+2,sku_data);
//            dev_flash_write_data(HCI_TEST_SKU_BASE,sku_data,GOVEE_SKU_MAX_LEN+2);
//            dev_flash_write_data(HCI_TEST_SKU_BACK,sku_data,GOVEE_SKU_MAX_LEN+2);
            rsp_data[3] = 0x01;
            rsp_data[4] = 0x62;
            uart_transmit(&Uart3_handle,rsp_data,(rsp_data[3]+4));
        }
        break;
        
        case SKU_READ:
        {
            uint8_t sku_data[7];
            rsp_data[3] = 0x06;
            rsp_data[4] = 0x63;
//            flash_read(HCI_TEST_SKU_BASE,7,sku_data);
//            dev_flash_read_data(HCI_TEST_SKU_BASE,sku_data,7);
            memcpy(rsp_data+5,sku_data,GOVEE_SKU_MAX_LEN);
            //show_reg(sku_data,7,1);
            uart_transmit(&Uart3_handle,rsp_data,(rsp_data[3]+4));
        }
        break; 
        case VER_READ:
            rsp_data[3] = 1+2*GOVEE_VERSION_MAX_LEN;
            rsp_data[4] = 0x64;
            // uart_transmit(&Uart3_handle,rsp_data,5);
        //    memcpy(&rsp_data[5],dev_msg_init_p.dev_sw_version,GOVEE_VERSION_MAX_LEN);
        //    memcpy(&rsp_data[5+GOVEE_VERSION_MAX_LEN],dev_msg_init_p.dev_hw_version,GOVEE_VERSION_MAX_LEN);
            uart_transmit(&Uart3_handle,rsp_data,(rsp_data[3]+4));
        break;
        case EARSE_TEST:
        {
//            uint8_t buff1[7]={0};
//            flash_read(PCB_TEST,7,buff1);
            //printf("%s\r\n",buff);
           // flash_erase(PCB_TEST,0);
        }
        break;
        
        case HCI_TX_SINGLE_POWER:
            rsp_data[3] = 0x02;
            rsp_data[4] = 0x66;
            rsp_data[5] = 0x01;
        
            /****************************0dbm*****************4dbm***************8dbm*******10dbm****/
            uint8_t tx_power_table[12] = {0x09,0x09,0x09,0x09,0x0a,0x0a,0x0a,0x0a,0x12,0x12,0x13,0x13};
            hci_cmd[0] = 0x01;
            hci_cmd[1] = 0x71;
            hci_cmd[2] = 0xfc;
            hci_cmd[3] = 0x02;
            hci_cmd[4] = 0x19;//1M TX STOP
            hci_cmd[5] = 0x00;
            uart_transmit(&HCI_handle,hci_cmd,6);
            
            vTaskDelay(3);
            
            hci_cmd[0] = 0x01;
            hci_cmd[1] = 0x71;
            hci_cmd[2] = 0xfc;
            hci_cmd[3] = 0x03;
            hci_cmd[4] = 0x31;//set max tx power
            hci_cmd[5] = 0x01;
            hci_cmd[6] = 0x06;            
            uart_transmit(&HCI_handle,hci_cmd,7);
            
            vTaskDelay(3);
            
            uint8_t rf_channel = buff[2];
            uint8_t set_tx_power = tx_power_table[11]; // 10dbm
            if((buff[1] > 6) && (buff[1] < 18)) // 0~10dbm
                set_tx_power = tx_power_table[buff[1]-7];
            hci_cmd[0] = 0x01;
            hci_cmd[1] = 0x71;
            hci_cmd[2] = 0xfc;
            hci_cmd[3] = 0x05;
            hci_cmd[4] = 0x18;//1M CW BURST
            hci_cmd[5] = 0x03;
            hci_cmd[6] = rf_channel; // chl 
            hci_cmd[7] = 0x00; // pyload
            hci_cmd[8] = set_tx_power; // tx power
            uart_transmit(&HCI_handle,hci_cmd,9);
            
            uart_transmit(&Uart3_handle,rsp_data,(rsp_data[3]+4));
            break;
        case FREQ_ADJUST:
        {
            uint8_t freq_adjust_tab[FREQ_ADJUST_NUM] = {0,16,16,14,13,12,11,10,10,9,8,7};
//            static uint8_t set_val = 0x50; // host_rf_freq_default;
            
            rsp_data[3] = 0x02;
            rsp_data[4] = 0x67;
            rsp_data[5] = 0x01;
            // 112 96  80  68  52  40  32  20  12  04  -08  -12  12  4  -8  -12
            // 112 95  79  65  52  40  29  19  09  00  -08  -15
            //   0 16  16  14  13  12  11  10  10  09   08  07
//            hci_cmd[0] = 0x01;
//            hci_cmd[1] = 0x71;
//            hci_cmd[2] = 0xfc;
//            hci_cmd[3] = 0x04;
//            hci_cmd[4] = 0x01;
//            hci_cmd[5] = 0x02;
//            hci_cmd[6] = 0xec; // tx_power reg
//            hci_cmd[7] = set_val;
//            uart_transmit(&HCI_handle,hci_cmd,8);
//            set_val++;
//            if(set_val > 0x6f)
//                set_val = 0x60;
        
            if((buff[1] <= 1) && (buff[2] <= 125))
            {
                uint8_t i = cur_freq_adjust_val,adjust_num = 0;
                if(buff[1])
                {
                    for(i = cur_freq_adjust_val+1;i < FREQ_ADJUST_NUM;i++)
                    {
                        adjust_num += freq_adjust_tab[i];
                        if(abs(adjust_num-buff[2]) < 10) // 10k
                        {
                            cur_freq_adjust_val = i;
                            break;
                        }
                    } 
                    if(i == FREQ_ADJUST_NUM)
                        rsp_data[5] = 0x00;
                }
                else
                {
                    for(;i > 0;i--)
                    {
                        adjust_num += freq_adjust_tab[i];
                        if(abs(adjust_num-buff[2]) < 10) // 10k
                        {
                            cur_freq_adjust_val = i-1;
                            break;
                        }
                    }
                    if(i == 0)
                        rsp_data[5] = 0x00;
                }
                if(rsp_data[5])
                {
                    if(cur_freq_adjust_val < FREQ_ADJUST_NUM)
                    {
//                        rsp_data[5] = cur_freq_adjust_val;
                        adjust_num = host_rf_freq_default&0xf0|cur_freq_adjust_val;
                        dev_freq_adjust_store(adjust_num);
                        
                        // set freq reg
                        hci_cmd[0] = 0x01;
                        hci_cmd[1] = 0x71;
                        hci_cmd[2] = 0xfc;
                        hci_cmd[3] = 0x04;
                        hci_cmd[4] = 0x01;
                        hci_cmd[5] = 0x02;
                        hci_cmd[6] = 0xec; // tx_power reg
                        hci_cmd[7] = adjust_num;
                        uart_transmit(&HCI_handle,hci_cmd,8);
                    }
                }
            }
            else
                rsp_data[5] = 0x00;
            
            uart_transmit(&Uart3_handle,rsp_data,(rsp_data[3]+4));
        }
            break;
        default:
            
        break;
    } 
}

/*__attribute__((section("ram_code"))) */void user_uart_at(uint8_t c)
{
    uart_recv.recv_data[uart_recv.indx++] = c;
    
    if((uart_recv.indx>3 )&&(uart_recv.indx>=uart_recv.recv_data[2]+3))
    {
       if(uart_recv.recv_data[1] == 0x0E)
       {
            uart_recv.length = uart_recv.recv_data[2];
            if(uart_recv.indx==uart_recv.length+3 )
            {
                uart_recv.finish_flag = 1;
                uart_recv.indx = 0;
                
                struct app_task_event *event;
                event = app_task_event_alloc(APP_TASK_EVENT_HCI_AT_CMD, uart_recv.length, false);
                if(event) {
                    memcpy(event->param, &uart_recv.recv_data[3], uart_recv.length);
                    event->param_len = uart_recv.length;
                    app_task_event_post(event, false);
                }
                evt_status = EVT_HCI;
            }
            else
            {
                uart_recv.indx = 0;
                uart_recv.start_flag = 0;
                uart_recv.finish_flag = 0;
                evt_status = EVT_HCI;
            }   
        }
        else
        {
                uart_recv.indx = 0;
                uart_recv.start_flag = 0;
                uart_recv.finish_flag = 0;
                evt_status = EVT_HCI;
         }       
    }
    if(uart_recv.indx >= AT_RECV_MAX_LEN)
       uart_recv.indx = 0; 
}

static void hci_recv_c(uint8_t c)
{
//    printf("host hci:%d,%x\r\n",hci_recv_state,c);
    switch(hci_recv_state)
    {
        case 0:
        {
            uart_recv.indx = 0;
            uart_recv.recv_data[uart_recv.indx++] = c;
            if(c == 0x01)
            {
                hci_recv_state = 1; //cmd
            }
            else if(c == 0x02)
            {
                printf("err cmd type: acl!!!\r\n");
                hci_recv_state = 2; //acl
            }
            else if(c == 0x03)
            {
                printf("err cmd type: sco!!!\r\n");
                hci_recv_state = 3; //sco
            }        
        }

            break;
        case 1:
            if(uart_recv.indx >= 2){
                hci_recv_state = 4;
            }
            uart_recv.recv_data[uart_recv.indx++] = c;
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            hci_recv_param_len = c;
            uart_recv.recv_data[uart_recv.indx++] = c;
            if(c > 60){
                printf("err cmd len!!!\r\n");
            }
            if(c == 0){
                hci_recv_state = 0;
                struct app_task_event *event;
                event = app_task_event_alloc(APP_TASK_EVENT_HCI_CMD, uart_recv.indx, false);
                if(event) {
                    memcpy(event->param, uart_recv.recv_data, uart_recv.indx);
                    event->param_len = uart_recv.indx;
                    app_task_event_post(event, false);
                    uart_recv.indx = 0;
                }
            }
            else{
                hci_recv_state = 5;
            }
            break;
            
        case 5:
            uart_recv.recv_data[uart_recv.indx++] = c;
            hci_recv_param_len --;

            if(hci_recv_param_len == 0){
                hci_recv_state = 0;
                struct app_task_event *event;
                event = app_task_event_alloc(APP_TASK_EVENT_HCI_CMD, uart_recv.indx, false);
                if(event) {
                    memcpy(event->param, uart_recv.recv_data, uart_recv.indx);
                    event->param_len = uart_recv.indx;
                    app_task_event_post(event, false);
                    uart_recv.indx = 0;
                }
            }
            break;
    }
    if(uart_recv.indx >= AT_RECV_MAX_LEN)
       uart_recv.indx = 0; 
}

 static void app_uart_recv_c(uint8_t c)
{
    //AT TEST
    if((c == 0x34) && (evt_status == EVT_HCI) && (uart_recv.indx == 0))
    {
        evt_status = EVT_AT; 
    }

    if(evt_status == EVT_AT)
    {
				//printf("user custom HCI \r\n");
        user_uart_at(c);           
    }
    else
    {
				//printf("Standard HCI \r\n");
        hci_recv_c(c);
    }
}

static void app_uart_rx_done(struct __UART_HandleTypeDef *handle)
{
    app_uart_recv_c(app_at_recv_char);
    if (handle) {
        uart_receive_IT(handle, &app_at_recv_char, 1);
    }
}

void app_hci_test_init(void)
{
    GPIO_InitTypeDef gpio_config;

    /* ========================================================== */
    /* =========         Uart LOG configuration         ========= */
    /* ========================================================== */
    /* configure PB4 and PB5 to UART1 function */
    gpio_config.Pin = GPIO_PIN_4 | GPIO_PIN_5;
    gpio_config.Mode = GPIO_MODE_AF_PP;
    gpio_config.Pull = GPIO_PULLUP;
    gpio_config.Alternate = GPIO_FUNCTION_1;
    gpio_init(GPIOB, &gpio_config);
    
    /* UART1: used for Log and AT cmd */
    // __UART_IS_TxFIFO_EMPTY(UART1);
    __SYSTEM_UART3_RESET();
    __SYSTEM_UART3_CLK_ENABLE();
    Uart3_handle.UARTx = UART3;
    Uart3_handle.Init.BaudRate   = 115200;
    Uart3_handle.Init.DataLength = UART_DATA_LENGTH_8BIT;
    Uart3_handle.Init.StopBits   = UART_STOPBITS_1;
    Uart3_handle.Init.Parity     = UART_PARITY_NONE;
    Uart3_handle.Init.FIFO_Mode  = UART_FIFO_ENABLE;
    Uart3_handle.TxCpltCallback  = NULL;
    Uart3_handle.RxCpltCallback  = app_uart_rx_done;
    uart_init(&Uart3_handle);
    __UART_AUTO_FLOW_CONTROL_DISABLE(UART3);
    NVIC_SetPriority(UART3_IRQn, 4);
    NVIC_EnableIRQ(UART3_IRQn);
    
    uart_receive_IT(&Uart3_handle, &app_at_recv_char, 1);
}

void host_uart_hci_recv_c(uint8_t c)
{
//    uart_transmit(&Uart3_handle,&host_hci_recv_state,1);
    switch(host_hci_recv_state)
    {
        case 0:
        {
            host_recv_index = 0;
            host_recv_buffer[host_recv_index++] = c;
            if(c == 0x04)
            {
                host_hci_recv_state = 1; //evt
            }
            else if(c == 0x02)
            {
                printf("err cmd type: acl!!!\r\n");
            }
            else if(c == 0x03)
            {
                printf("err cmd type: sco!!!\r\n");
            }
            else if(c == 0x01){
                printf("err cmd type: cmd!!!\r\n");
            }
        }

            break;
        case 1:
            recv_type = c;
            host_recv_buffer[host_recv_index++] = c;
            if(recv_type == 0x0e){
                host_hci_recv_state = 4; 
            }
            else{
                host_hci_recv_state = 2; 

            }
            break;
        case 2:
            recv_len = c;
            host_recv_buffer[host_recv_index++] = c;
            if(c == 0){
                host_hci_recv_state = 0;
                struct app_task_event *event;
                event = app_task_event_alloc(APP_TASK_EVENT_HOST_HCI_RSP, host_recv_index, false);
                if(event) {
                    memcpy(event->param, host_recv_buffer, host_recv_index);
                    event->param_len = host_recv_index;
                    app_task_event_post(event, false);
                }
                host_recv_index = 0;
            }
            else{
                host_hci_recv_state = 3;
            }
            break;
        case 3:
            host_recv_buffer[host_recv_index++] = c;
            recv_len --;
            if(recv_len == 0){
                host_hci_recv_state = 0;
                struct app_task_event *event;
                event = app_task_event_alloc(APP_TASK_EVENT_HOST_HCI_RSP, host_recv_index, false);
                if(event) {
                    memcpy(event->param, host_recv_buffer, host_recv_index);
                    event->param_len = host_recv_index;
                    app_task_event_post(event, false);
                }
                host_recv_index = 0;
            }
            break;
        case 4:
            //param len
            recv_len = c;
            host_recv_buffer[host_recv_index++] = c;
            if(c > 60){
                printf("err cmd len!!!\r\n");
            }
            if(c == 0){
                host_hci_recv_state = 0;
                struct app_task_event *event;
                event = app_task_event_alloc(APP_TASK_EVENT_HOST_HCI_RSP, host_recv_index, false);
                if(event) {
                    memcpy(event->param, host_recv_buffer, host_recv_index);
                    event->param_len = host_recv_index;
                    app_task_event_post(event, false);
                }
                host_recv_index = 0;
            }
            else{
                host_hci_recv_state = 5;
            }
            break;
            
        case 5:
            //num of complete pkts
            host_recv_buffer[host_recv_index++] = c;
            recv_len --;
            host_hci_recv_state = 6; 

            break;
        case 6:
            host_recv_buffer[host_recv_index++] = c;
            recv_len --;
            if(c == 0x71){
                host_hci_recv_state = 7; 
            }
            else{
                host_hci_recv_state = 8;
            }
            break;
            
        case 7:
            host_recv_buffer[host_recv_index++] = c;
            recv_len --;
            if(c == 0xfc){
                recv_len = 2;
                host_hci_recv_state = 12; 
                host_recv_index = 0;
            }
            else{
                host_hci_recv_state = 8;
            }
            break;
            
        case 8:
            host_recv_buffer[host_recv_index++] = c;
            recv_len --;
            if(recv_len == 0){
                host_hci_recv_state = 0;
                struct app_task_event *event;
                event = app_task_event_alloc(APP_TASK_EVENT_HOST_HCI_RSP, host_recv_index, false);
                if(event) {
                    memcpy(event->param, host_recv_buffer, host_recv_index);
                    event->param_len = host_recv_index;
                    app_task_event_post(event, false);
                }
                host_recv_index = 0;
            }
            break;
            
        case 10:
            recv_len --;
            if(recv_len == 0){
                host_hci_recv_state = 0;
                host_recv_index = 0;
            }
            break;
        case 12:
            //recv status and param len
            recv_len --;
            if(recv_len == 0){
                host_hci_recv_state = 13;
            }
            break;
        case 13:
            //recv type, 0---ool read,1---ool write,2---sys read,3---sys write,c---rf read,d---rf write, e---mdm read 1B,f---mdm write 1B
            recv_type = c;
            host_hci_recv_state = 14;
            break;
        case 14:
            if(recv_type == 0 ){
                //ool read
                recv_len = 1;
                host_hci_recv_state = 15;
            }
            else if(recv_type == 1){
                //ool write
                recv_len = 1;
                host_hci_recv_state = 10;
                uint8_t at_char[] = "OK\r\n";
//                uart_transmit(&Uart3_handle,at_char,4);
            }
            else if((recv_type == 2)){
                //sys read
                recv_len = 3;
                host_hci_recv_state = 16;
            }
            else if(recv_type == 3){
                //sys write
                recv_len = 7;
                host_hci_recv_state = 18;
            }
            else if(recv_type == 0x0c){
                //read apb 16bits
                recv_len = 3;
                host_hci_recv_state = 16;
            }
            else if(recv_type == 0x0d){
                //write apb 16bits
                recv_len = 5;
                host_hci_recv_state = 18;
            }
            else if(recv_type == 0x0e){
                //read apb 8bits
                recv_len = 3;
                host_hci_recv_state = 16;
            }
            else if(recv_type == 0x0f){
                //write apb 8bits
                recv_len = 4;
                host_hci_recv_state = 18;
            }
            else if((recv_type>= 0x17 && recv_type<=0x26) 
                    || recv_type == 0x2f
                    || recv_type == 0x30
                    || recv_type == 0x31)
            {
                if(recv_type == 0x23 || recv_type == 0x30){ //RX stop
                    recv_len = 4;
                    Rx_Packet_NUM = c;
                    recv_len--;
                    host_hci_recv_state = 19;
                }
                else{
//                    printf("OK\r\n");
                    host_hci_recv_state = 0;
                }
            }
            
            break;
        case 15:
            recv_len --;
//            printf("recv len = %d,%x\r\n",recv_len,ch);
            if(recv_len == 0){
//                uart_transmit(&Uart3_handle,&tx_ch,1);
//                printf("0x%02x\r\n",c);
                host_rf_freq_default = c;
                cur_freq_adjust_val = host_rf_freq_default&0x0f;
                host_hci_recv_state = 0;
            }
            break;
        case 16:
            recv_len --;
            if(recv_len == 0){        
                if(recv_type == 2){
                    recv_len = 4;
                }
                else if(recv_type == 0x0c){
                    recv_len = 2;
                }
                else if(recv_type == 0x0e){
                    recv_len = 1;
                }
                recv_val = 0;
                host_hci_recv_state = 17;
            }    
            break;
        case 17:
            recv_len --;
            if(recv_type == 2){
                recv_val += c<<((3-recv_len)*8);
            }
            else if(recv_type == 0x0c){
                recv_val += c<<((1-recv_len)*8);
            }
            else if(recv_type == 0x0e){
                recv_val = c;
            }
            if(recv_len == 0){
                if(recv_type == 2){//sys read
//                    printf("0x%08x\r\n",recv_val);
                }
                else if(recv_type == 0x0c){//16bit read
//                    printf("0x%04x\r\n",recv_val);
                }
                else if(recv_type == 0x0e){//8bit read
//                    printf("0x%02x\r\n",recv_val);
                }
                host_hci_recv_state = 0;
            }
        
            break;
        case 18:
            recv_len --;
            if(recv_len == 0){  
//                printf("OK\r\n");
                host_hci_recv_state = 0;
            }
            break;
            
        case 19:
        {
            if(recv_len == 3)
                Rx_Packet_NUM |= c <<8;
            else if(recv_len == 2)
                Rx_Packet_NUM |= c <<16;
            else if(recv_len == 1)
                Rx_Packet_NUM |= c <<24;

            recv_len--;
            host_hci_recv_state = 19;
            
            if(recv_len == 0)
            {
//                printf("Rx_Packet_NUM: %x\r\n",Rx_Packet_NUM);
                Rx_Packet_NUM =0;
                host_hci_recv_state = 0;
            }
                    
                
        }
        break;
        
        default:
            break;
            
    }
    if(host_recv_index >= HOST_RECV_MAX_LEN)
        host_recv_index = 0;
}

static void host_hci_rx_done(struct __UART_HandleTypeDef *handle)
{
    host_uart_hci_recv_c(hci_recv_char);
    
    if (handle) {
        uart_receive_IT(handle, &hci_recv_char, 1);
    }
}

void host_hci_get_rf_freq_default(void)
{
    uint8_t hci_cmd[8] = {0};
    
    hci_cmd[0] = 0x01;
    hci_cmd[1] = 0x71;
    hci_cmd[2] = 0xfc;
    hci_cmd[3] = 0x03;
    hci_cmd[4] = 0x00;
    hci_cmd[5] = 0x01;
    hci_cmd[6] = 0xec; // tx_power reg
    uart_transmit(&HCI_handle,hci_cmd,7);
}

void host_hci_uart_init(uint32_t baudrate)
{
    GPIO_InitTypeDef gpio_config;
    /* configure PA0 and PA1 to UART0 function */
    gpio_config.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    gpio_config.Mode = GPIO_MODE_AF_PP;
    gpio_config.Pull = GPIO_PULLUP;
    gpio_config.Alternate = GPIO_FUNCTION_1;
    gpio_init(GPIOA, &gpio_config);
    
    /* UART0: used for communication with controller */
    __SYSTEM_UART0_RESET();
    __SYSTEM_UART0_CLK_ENABLE();
    HCI_handle.UARTx = UART0;
    HCI_handle.Init.BaudRate   = baudrate;
    HCI_handle.Init.DataLength = UART_DATA_LENGTH_8BIT;
    HCI_handle.Init.StopBits   = UART_STOPBITS_1;
    HCI_handle.Init.Parity     = UART_PARITY_NONE;
    HCI_handle.Init.FIFO_Mode  = UART_FIFO_ENABLE;
    HCI_handle.TxCpltCallback  = NULL;
    HCI_handle.RxCpltCallback  = host_hci_rx_done;
    uart_init(&HCI_handle);
    /* enable flow control */
    __UART_AUTO_FLOW_CONTROL_ENABLE(HCI_handle.UARTx);
    __UART_RTS_ACTIVE(HCI_handle.UARTx);
//    __UART_RxFIFO_THRESHOLD((&HCI_handle), 2);
    NVIC_SetPriority(UART0_IRQn, 2);
    NVIC_EnableIRQ(UART0_IRQn);
    
    uart_receive_IT(&HCI_handle, &hci_recv_char, 1);

    app_hci_test_init();
    host_hci_get_rf_freq_default();
}

uint8_t dev_in_hci_mode(void)
{
    return hci_test_mode;
}

uint8_t dev_check_hci_test_mode(void)
{
    static uint8_t test_mode_get[5] = {0}; // RSP:0xBA,0xBA,0xBA,0xBA,0xBA
    uint8_t test_mode_send[5] = {0x34,0x0E,0x01,0x6A,0x01};
    uint8_t test_mode_check[] = {0x34,0x0E,0x02,0x0A,0x01};
    uint8_t ret = 0;
    
    GPIO_InitTypeDef gpio_config;

    /* ========================================================== */
    /* =========         Uart LOG configuration         ========= */
    /* ========================================================== */
    /* configure PB4 and PB5 to UART1 function */
    gpio_config.Pin = GPIO_PIN_4 | GPIO_PIN_5;
    gpio_config.Mode = GPIO_MODE_AF_PP;
    gpio_config.Pull = GPIO_PULLUP;
    gpio_config.Alternate = GPIO_FUNCTION_1;
    gpio_init(GPIOB, &gpio_config);
    
    /* UART1: used for Log and AT cmd */
    __SYSTEM_UART1_CLK_ENABLE();
    Uart3_handle.UARTx = UART3;
    Uart3_handle.Init.BaudRate   = 115200;
    Uart3_handle.Init.DataLength = UART_DATA_LENGTH_8BIT;
    Uart3_handle.Init.StopBits   = UART_STOPBITS_1;
    Uart3_handle.Init.Parity     = UART_PARITY_NONE;
    Uart3_handle.Init.FIFO_Mode  = UART_FIFO_ENABLE;
    Uart3_handle.TxCpltCallback  = NULL;
    Uart3_handle.RxCpltCallback  = NULL;
    uart_init(&Uart3_handle);
    __UART_AUTO_FLOW_CONTROL_DISABLE(UART3);
    NVIC_SetPriority(UART3_IRQn, 4);
    NVIC_EnableIRQ(UART3_IRQn);
    
    uart_transmit(&Uart3_handle,test_mode_send,sizeof(test_mode_send));
    uart_receive_IT(&Uart3_handle, test_mode_get, 5);
    for(uint8_t i = 0;i < 50;i++) // 50ms
    {
        system_delay_us(1000);
        if(Uart3_handle.b_RxBusy == false)
        {
            if(!memcmp(test_mode_get,test_mode_check,sizeof(test_mode_check)))
            {
                test_mode_send[2] = 0x02;
                uart_transmit(&Uart3_handle,test_mode_send,sizeof(test_mode_send));
                __UART_IS_TxFIFO_EMPTY(Uart3_handle.UARTx);
                ret = 1;
                break;
            }
        }
    }
    // ret = 1;
    hci_test_mode = ret;
    return ret;
}
extern void app_ble_stop_advertising(uint8_t adv_chn);
extern const BtAccessModeInfo access_mode_nc;
static TimerHandle_t ble_hcit_test_timer = NULL;

extern void user_hci_callback(const BtEvent *event);
static TimerHandle_t bt_dut_test_timer = NULL;

static void ble_sec_req_timer_cb(TimerHandle_t pxTimer)
{
    printf("%s\r\n",__func__);
		host_hci_uart_init(BTDM_STACK_HCI_BAUDRATE);
}
void	hci_test_start(void)
{
		app_ble_stop_advertising(0);
    ME_SetAccessibleModeNC(BAM_NOT_ACCESSIBLE, &access_mode_nc);	
	
		if(ble_hcit_test_timer == NULL){
				ble_hcit_test_timer = xTimerCreate("ble_hcit_test_timer", 1000, pdFALSE, 0, ble_sec_req_timer_cb );
		}
		xTimerStart(ble_hcit_test_timer,portMAX_DELAY);
}


static void bt_dut_timer_cb(TimerHandle_t pxTimer)
{
    printf("%s\r\n",__func__);
		bt_dut_test();
}
void  bt_dut_test_start(void)
{
	app_ble_stop_advertising(0);
	
		if(bt_dut_test_timer == NULL){
				bt_dut_test_timer = xTimerCreate("bt_dut_test_timer", 1000, pdFALSE, 0, bt_dut_timer_cb );
		}
		xTimerStart(bt_dut_test_timer,portMAX_DELAY);	
}

void  bt_dut_test(void)
{
	BtStatus status = BT_STATUS_FAILED;
	MeCommandToken *token;	
	token = btdm_malloc(sizeof(MeCommandToken));
	token->p.general.in.hciCommand = 0x1803;//HCC_ENABLE_DUT;
	token->p.general.in.parmLen = 0;
	token->p.general.in.event = 0x0e;       //HCE_COMMAND_COMPLETE
	token->callback = user_hci_callback;    //token is freed at this callback
	ME_SendHciCommandSync(token);	
}