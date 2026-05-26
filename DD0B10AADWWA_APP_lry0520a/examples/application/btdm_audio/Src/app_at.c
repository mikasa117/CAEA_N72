#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "fr30xx.h"

#include "co_util.h"

#include "bt_types.h"
#include "me_api.h"
#include "hfg_api.h"
#include "gatt_api.h"

#include "app_at.h"
#include "app_task.h"
#include "app_ble.h"
#include "app_bt.h"
#include "app_audio.h"
#include "btdm_mem.h"
#include "fdb_app.h"
#include "user_bt.h"
#include "dsp_mem.h"
#include "heap.h"
#include "host.h"

#include "sbc_sample.h"

#if BTDM_STACK_ENABLE_PAN
#include "pan_api.h"
#include "ethernetif.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"
#include "lwip/api.h"
#endif

#include "audio_codec.h"
#define USER_ATCMD_EZ   0
#define AT_RECV_MAX_LEN             32

static uint8_t app_at_recv_char;
static uint8_t at_recv_buffer[AT_RECV_MAX_LEN];
static uint8_t at_recv_index = 0;
static uint8_t at_recv_state = 0;
extern uint8_t enable_audio_transfer;

#if BTDM_STACK_ENABLE_A2DP_SNK || BTDM_STACK_ENABLE_A2DP_SRC
void bt_source_get_sbc_param(uint8_t dev_index, struct sbc_encoder_param *sbc_param)
{
    sbc_param->i_bitpool = sbcinfo[dev_index].info.bitPool;
    sbc_param->i_blocks = sbcinfo[dev_index].info.numBlocks;
    sbc_param->i_num_chan = sbcinfo[dev_index].info.numChannels;
    if(sbcinfo[dev_index].info.sampleFreq == 2){
        sbc_param->i_samp_freq = 44100;
    }
    else if(sbcinfo[dev_index].info.sampleFreq == 3){
        sbc_param->i_samp_freq = 48000;
    }
    else{
        sbc_param->i_samp_freq = 0;
    }
    sbc_param->i_snr = (sbcinfo[dev_index].info.allocMethod == 2) ? 1 : 0;
    sbc_param->i_subbands = sbcinfo[dev_index].info.numSubBands;
}
#endif
void btdm_host_send_vendor_cmd(uint8_t type, uint8_t length, void *data);

void btdm_host_vendor_cmd_cmp_evt(uint8_t status, uint8_t len, uint8_t const *param)
{
    printf("status: 0x%02x.\r\n", status);
    for (uint32_t i=0; i<len; i++) {
        printf("%02x ", param[i]);
    }
    printf("\r\n");
}
void user_hci_callback(const BtEvent *event)
{
    printf("event type = %d,%d\r\n",event->eType,event->p.meToken->p.general.in.parmLen);
    if(event->eType == BTEVENT_COMMAND_COMPLETE){
        if(event->p.meToken->p.general.in.parmLen){
            btdm_free(event->p.meToken->p.general.in.parms);
        }
        btdm_free(event->p.meToken);
    }
}
static void app_at_recv_cmd_A(uint8_t sub_cmd, uint8_t *data)
{
    BD_ADDR addr;
    switch(sub_cmd)
    {
        case 'A':
        {
            uint8_t addr = ascii_strn2val((const char *)&data[0], 16, 2);
            btdm_host_send_vendor_cmd(0x00, 1, &addr);
        }
            printf("OK\r\n");
            break;
        case 'B':
        {
            uint8_t buffer[2];
            buffer[0] = ascii_strn2val((const char *)&data[0], 16, 2);
            buffer[1] = ascii_strn2val((const char *)&data[3], 16, 2);
            btdm_host_send_vendor_cmd(0x01, 2, (void *)&buffer[0]);
        }
            printf("OK\r\n");
            break;
        case 'C':
        {
            uint32_t addr = ascii_strn2val((const char *)&data[0], 16, 8);
            btdm_host_send_vendor_cmd(0x02, 4, (void *)&addr);
        }
            printf("OK\r\n");
            break;
        case 'D':
        {
            uint32_t buffer[2];
            buffer[0] = ascii_strn2val((const char *)&data[0], 16, 8);
            buffer[1] = ascii_strn2val((const char *)&data[9], 16, 8);
            btdm_host_send_vendor_cmd(0x03, 8, (void *)&buffer[0]);
        }
            printf("OK\r\n");
            break;
        case 'G':
        {
            printf("data[0] = %c\r\n", data[0]);
            switch (data[0])
            {
            case '0':
            {
                //
                // es8389_mic_start();
            }
            break;
            case '1':
            {
                printf("start bt adv....\r\n");
                my_bt_start_adv();
            }
            break;
            case '2':
            {
                printf("stop bt adv....\r\n");
                my_bt_stop_adv();
            }
            break;
            case '3':
            {
                audio_loop_start();
            }
            break;
            case '4':
            {
                audio_loop_stop();
            }
            break;
            case '5':
            {
                extern void es8389_get_vol(uint8_t * vol1, uint8_t * vol2);
                uint8_t vol1, vol2;
                es8389_get_vol(&vol1, &vol2);
                printf("--------> vol1 = %d, vol2 = %d\r\n", vol1, vol2);

                //bt_tone_play(0);
            }
            break;
            case '6':
            {
                app_audio_tone_play(AUDIO_TYPE_SBC, sbc_sample1, sbc_sample1_get_size());
                //bt_tone_play(1);
            }
            break;
            case '7':
            {
                es8389_read_all_reg();
            }
            break;
            #if (USING_AEC_RB == 1)
            case '8':
            {
                extern aec_ring_buff_t aec_rb;
                uint16_t set_delay_size = ascii_strn2val((const char *)&data[1], 10, 4);
                printf("set_delay_size = %d\r\n", set_delay_size);
                aec_rb_set_delay(&aec_rb, set_delay_size);
            }
            #endif
            break;

            default:
                break;
            }
        }
            printf("hello world!\r\n");
            break;
        case 'H':
            printf("VAL: 0x%08x.\r\n", *(volatile uint32_t *)ascii_strn2val((const char *)&data[0], 16, 8));
            break;
        case 'I':
            *(volatile uint32_t *)ascii_strn2val((const char *)&data[0], 16, 8) = ascii_strn2val((const char *)&data[9], 16, 8);
            printf("OK\r\n");
            break;
        case 'J':
            printf("OOL VAL: 0x%02x.\r\n", ool_read(ascii_strn2val((const char *)&data[0], 16, 2)));
            break;
        case 'K':
            ool_write(ascii_strn2val((const char *)&data[0], 16, 2), ascii_strn2val((const char *)&data[3], 16, 2));
            printf("OK\r\n");
            break;
        case 'L':
            printf("VAL: 0x%02x.\r\n", *(volatile uint8_t *)(ascii_strn2val((const char *)&data[0], 16, 8)));
            break;
        case 'M':
            *(volatile uint8_t *)(ascii_strn2val((const char *)&data[0], 16, 8)) = ascii_strn2val((const char *)&data[9], 16, 2);
            printf("OK\r\n");
            break;
//        case 'P':
//            co_printf("VAL: 0x%02x.\r\n", *(uint8_t *)(MODEM_BASE + ascii_strn2val((const char *)&data[0], 16, 2)));
//            break;
//        case 'Q':
//            *(uint8_t *)(MODEM_BASE + ascii_strn2val((const char *)&data[0], 16, 2)) = ascii_strn2val((const char *)&data[3], 16, 2);
//            co_printf("OK\r\n");
//            break;
//        case 'S':
//            co_printf("VAL: 0x%02x.\r\n", frspim_rd(FR_SPI_RF_COB_CHAN, ascii_strn2val((const char *)&data[0], 16, 2), 1));
//            break;
//        case 'T':
//            frspim_wr(FR_SPI_RF_COB_CHAN, ascii_strn2val((const char *)&data[0], 16, 2), 1, ascii_strn2val((const char *)&data[3], 16, 2));
//            co_printf("OK\r\n");
//            break;
        case 'N':
            DDB_EnumRecord();
            break;
        case 'O':
        {
            addr.A[0] = ascii_strn2val((const char*)&data[0],16,2);
            addr.A[1] = ascii_strn2val((const char*)&data[2],16,2);
            addr.A[2] = ascii_strn2val((const char*)&data[4],16,2);
            addr.A[3] = ascii_strn2val((const char*)&data[6],16,2);
            addr.A[4] = ascii_strn2val((const char*)&data[8],16,2);
            addr.A[5] = ascii_strn2val((const char*)&data[10],16,2);
            DDB_DeleteRecord(&addr);        
        }
            break;
        case 'Q':
        {
            ///reset local bt addr，only valid in non-broadcast and non-connected state
            uint8_t buffer[7];
            buffer[0] = 0;
            buffer[1] = ascii_strn2val((const char*)&data[0],16,2);
            buffer[2] = ascii_strn2val((const char*)&data[2],16,2);
            buffer[3] = ascii_strn2val((const char*)&data[4],16,2);
            buffer[4] = ascii_strn2val((const char*)&data[6],16,2);
            buffer[5] = ascii_strn2val((const char*)&data[8],16,2);
            buffer[6] = ascii_strn2val((const char*)&data[10],16,2);
            btdm_host_send_vendor_cmd(0x20, 7, (void *)&buffer[0]);
        }
            break;
        case 'U':
        {
            uint32_t *ptr = (uint32_t *)(ascii_strn2val((const char *)&data[0], 16, 8) & (~3));
            uint8_t count = ascii_strn2val((const char *)&data[9], 16, 2);
            uint32_t *start = (uint32_t *)((uint32_t)ptr & (~0x0f));
            for(uint8_t i=0; i<count;) {
                if(((uint32_t)start & 0x0c) == 0) {
                    printf("0x%08x: ", (uint32_t)start);
                }
                if(start < ptr) {
                    printf("        ");
                }
                else {
                    i++;
                    printf("%08x", *start);
                }
                if(((uint32_t)start & 0x0c) == 0x0c) {
                    printf("\r\n");
                }
                else {
                    printf(" ");
                }
                start++;
            }
        }
            break;
        case 'V':
            flash_erase(QSPI0, ascii_strn2val((const char *)&data[0], 16, 8), ascii_strn2val((const char *)&data[9], 16, 8));
            break;
        case 'W':
        {
            uint32_t curr_free, min_free;
            dsp_mem_get_usage(&curr_free, &min_free);
            printf("DSP MEM: %d, %d\r\n", curr_free, min_free);
        }
            break;
        case 'X':
        {
            void system_reset(void);
            system_reset();
        }
            break;
        case 'Y':
            heap_dump_used_mem(ascii_strn2val((const char *)&data[0], 16, 2));
            break;
        case 'Z':
            printf("MEM usage\r\n \
                    \tHEAP_TYPE_SRAM_BLOCK: %d, %d\r\n \
                    \tHEAP_TYPE_DRAM_BLOCK: %d, %d\r\n \
                    \tHEAP_TYPE_BTDM_BLOCK: %d, %d\r\n \
                    \tTOTAL USAGE: %d\r\n", \
                            heap_get_mem_usage(HEAP_TYPE_SRAM_BLOCK), heap_get_max_mem_usage_single(HEAP_TYPE_SRAM_BLOCK), \
                            heap_get_mem_usage(HEAP_TYPE_DRAM_BLOCK), heap_get_max_mem_usage_single(HEAP_TYPE_DRAM_BLOCK), \
                            heap_get_mem_usage(HEAP_TYPE_BTDM_BLOCK), heap_get_max_mem_usage_single(HEAP_TYPE_BTDM_BLOCK), \
                            heap_get_max_mem_usage());
            break;
        default:
            break;
    }
}
#if BTDM_STACK_ENABLE_BT
static void app_at_recv_cmd_B(uint8_t sub_cmd, uint8_t *data)
{
    struct gap_ble_addr peer_addr;
    BD_ADDR addr;
    HfgResponse *rsp;
    BtStatus status = BT_STATUS_FAILED;
    MeCommandToken *token;
//    uint16_t page_timeout = 0x400;
    
    switch(sub_cmd) {
        case 'A':
        {
            extern bool host_get_bt_last_device(BD_ADDR *addr);
            bool ret = host_get_bt_last_device(&addr);
            if(ret == true){
                user_bt_env.connect_times = 3;
                status = bt_connect(&addr, ENABLE_PROFILE_HFG|ENABLE_PROFILE_A2DP_SOURCE);
                printf("status = %d,%x,%x\r\n",status,addr.A[0],addr.A[1]);                    
            }
            else{
                printf("no saved device\r\n");
            }        
        }
            break;
        case 'B':
        {
            extern bool host_get_bt_last_device(BD_ADDR *addr);
            bool ret = host_get_bt_last_device(&addr);
            if(ret == true){
                user_bt_env.connect_times = 3;
                status = bt_connect(&addr, ENABLE_PROFILE_A2DP_SINK);
                printf("status = %d,%x,%x\r\n",status,addr.A[0],addr.A[1]);                    
            }
            else{
                printf("no saved device\r\n");
            }        
    }
    break;
    case 'C':
    {
        extern void hci_test_start(void);
        hci_test_start();
        printf("ble hci test\r\n");
        }
            break;
        case 'D':
        {
            token = btdm_malloc(sizeof(MeCommandToken));
            token->p.general.in.hciCommand = 0x1803;//HCC_ENABLE_DUT;
            token->p.general.in.parmLen = 0;
            token->p.general.in.event = 0x0e;       //HCE_COMMAND_COMPLETE
            token->callback = user_hci_callback;    //token is freed at this callback
            ME_SendHciCommandSync(token);
        }
            break;
        case 'E':
        {
            ///set poll interval to 5ms
            if(user_bt_env.dev[0].remDev != 0){
            token = btdm_malloc(sizeof(MeCommandToken));
            token->p.general.in.hciCommand = 0x0807;//HCC_QOS_SETUP;
            token->p.general.in.parmLen = 20;
                uint8_t *qos_setup_param = btdm_malloc(token->p.general.in.parmLen);
            
            uint16_t handle = ME_GetHciConnectionHandle(user_bt_env.dev[0].remDev);
            qos_setup_param[0] = handle&0xff;
            qos_setup_param[1] = (handle>>8)&0xff;
            qos_setup_param[2] = 0;
            qos_setup_param[3] = 2; // qos guaranteed
            
            qos_setup_param[4] = 0x00;
            qos_setup_param[5] = 0x00;
            qos_setup_param[6] = 0x00;
            qos_setup_param[7] = 0x00;
            
            ///Peak_bandwidth
            qos_setup_param[8] = 0x00;
            qos_setup_param[9] = 0x00;
            qos_setup_param[10] = 0x00;
            qos_setup_param[11] = 0x00;
            
            ///latency, default:0xffffffff, don't care
            qos_setup_param[12] = 0x88; //0x1388, 5000us
            qos_setup_param[13] = 0x13;
            qos_setup_param[14] = 0x00;
            qos_setup_param[15] = 0x00;
            
            ///delay variation
            qos_setup_param[16] = 0x00;
            qos_setup_param[17] = 0x00;
            qos_setup_param[18] = 0x00;
            qos_setup_param[19] = 0x00;
                token->p.general.in.parms = qos_setup_param;
                token->p.general.in.event = 0x0f;       //HCE_COMMAND_STATUS
            token->callback = user_hci_callback;    //token is freed at this callback
            status = ME_SendHciCommandAsync(token);
            }
            printf("status = %d\r\n",status);
        }
            break;
    case 'F':
    {
        extern void  bt_dut_test_start(void);
        bt_dut_test_start();
    }
        break;
        case 'H':
            ME_Inquiry(BT_IAC_GIAC, 5, 0);
            break;
        case 'I':
            ME_CancelInquiry();
            break;
        
        case 'L':
            flashdb_del(FDB_KEY_BT_LINKKEY);
            break;
        case 'M':
        {
            uint8_t *page_timeout;
            token = btdm_malloc(sizeof(MeCommandToken));
            token->p.general.in.hciCommand = 0x0c18;//HCC_WRITE_PAGE_TIMEOUT;
            token->p.general.in.parmLen = 2;
            page_timeout = btdm_malloc(token->p.general.in.parmLen);
            page_timeout[0] = 0x00;
            page_timeout[1] = 0x04;
            token->p.general.in.parms = page_timeout;
            token->p.general.in.event = 0x0e;       //HCE_COMMAND_COMPLETE
            token->callback = user_hci_callback;    //token is freed at this callback
            status = ME_SendHciCommandAsync(token);
            printf("status = %d\r\n",status);
        }
            break;
        case 'N':
        {
            addr.A[0] = ascii_strn2val((const char*)&data[0],16,2);
            addr.A[1] = ascii_strn2val((const char*)&data[2],16,2);
            addr.A[2] = ascii_strn2val((const char*)&data[4],16,2);
            addr.A[3] = ascii_strn2val((const char*)&data[6],16,2);
            addr.A[4] = ascii_strn2val((const char*)&data[8],16,2);
            addr.A[5] = ascii_strn2val((const char*)&data[10],16,2);
            user_bt_env.connect_times = 3;
            status = bt_connect(&addr,ENABLE_PROFILE_HF|ENABLE_PROFILE_A2DP_SINK);
            printf("status = %d\r\n",status);
        }
            break;

        case 'O':
        {
            addr.A[0] = ascii_strn2val((const char*)&data[0],16,2);
            addr.A[1] = ascii_strn2val((const char*)&data[2],16,2);
            addr.A[2] = ascii_strn2val((const char*)&data[4],16,2);
            addr.A[3] = ascii_strn2val((const char*)&data[6],16,2);
            addr.A[4] = ascii_strn2val((const char*)&data[8],16,2);
            addr.A[5] = ascii_strn2val((const char*)&data[10],16,2);
            user_bt_env.connect_times = 3;
            status = bt_connect(&addr,ENABLE_PROFILE_HFG|ENABLE_PROFILE_A2DP_SOURCE);
            printf("status = %d\r\n",status);
        }
            break;
        case 'P':
            addr.A[0] = ascii_strn2val((const char*)&data[0],16,2);
            addr.A[1] = ascii_strn2val((const char*)&data[2],16,2);
            addr.A[2] = ascii_strn2val((const char*)&data[4],16,2);
            addr.A[3] = ascii_strn2val((const char*)&data[6],16,2);
            addr.A[4] = ascii_strn2val((const char*)&data[8],16,2);
            addr.A[5] = ascii_strn2val((const char*)&data[10],16,2);
            bt_disconnect(&addr,false);
            break;
        
        case 'Q':
            addr.A[0] = ascii_strn2val((const char*)&data[0],16,2);
            addr.A[1] = ascii_strn2val((const char*)&data[2],16,2);
            addr.A[2] = ascii_strn2val((const char*)&data[4],16,2);
            addr.A[3] = ascii_strn2val((const char*)&data[6],16,2);
            addr.A[4] = ascii_strn2val((const char*)&data[8],16,2);
            addr.A[5] = ascii_strn2val((const char*)&data[10],16,2);
            bt_disconnect(&addr,true);
            break;
        
        case 'R':
        {
            extern bool host_get_bt_last_device(BD_ADDR *addr);
            bool ret = host_get_bt_last_device(&addr);
            if(ret == true){
                user_bt_env.connect_times = 3;
                status = bt_connect(&addr, ENABLE_PROFILE_HF|ENABLE_PROFILE_A2DP_SINK);
                printf("status = %d,%x,%x\r\n",status,addr.A[0],addr.A[1]);                    
            }
            else{
                printf("no saved device\r\n");
            }
        }
            break;
        case 'S':
        {
            BtAccessModeInfo access_mode_nc = {
                .inqInterval = 0x800,
                .inqWindow = 0x12,
                .pageInterval = 0x800,
                .pageWindow = 0x12,
            };
            status = bt_enter_pairing(BAM_GENERAL_ACCESSIBLE, &access_mode_nc);
            printf("status = %d\r\n",status);
        }
            break;
        case 'T':
        {
            status = bt_exit_pairing();
            printf("status = %d\r\n",status);

        }
            break;
        case 'U':
        {    
            #define EIR_DATA_SIZE 100
            uint8_t eir_data[EIR_DATA_SIZE];
            uint8_t index = 0;
            memset(&eir_data[0],0,EIR_DATA_SIZE);
            eir_data[index++] = sizeof("FR30xx_SDK_APP") + 1;
            eir_data[index++] = 0x09;
            memcpy(&(eir_data[index]),"FR30xx_SDK_APP",sizeof("FR30xx_SDK_APP"));
            ME_SetExtInquiryRsp(0x01,eir_data,sizeof("FR30xx_SDK_APP")+1);
            ME_SetLocalDeviceName("FR30xx_SDK_APP", 15);            
        }
            break;
        case 'V':
        {
            status = bt_disconnect(&user_bt_env.dev[user_bt_env.last_active_index].remote_bd,true);
            printf("status = %d\r\n",status);
        }
            break;
        case 'W':
            ME_SwitchRole(user_bt_env.dev[0].remDev);
            break;
        case 'X':
        {
            addr.A[0] = ascii_strn2val((const char*)&data[0],16,2);
            addr.A[1] = ascii_strn2val((const char*)&data[2],16,2);
            addr.A[2] = ascii_strn2val((const char*)&data[4],16,2);
            addr.A[3] = ascii_strn2val((const char*)&data[6],16,2);
            addr.A[4] = ascii_strn2val((const char*)&data[8],16,2);
            addr.A[5] = ascii_strn2val((const char*)&data[10],16,2);
            user_bt_env.connect_times = 3;
            status = bt_connect(&addr,ascii_strn2val((const char*)&data[13],16,2));
            printf("status = %d\r\n",status);        
        }
            break;
        default:
            break;
    }
    printf("OK\r\n");
}

#if BTDM_STACK_ENABLE_HF
///HF
static void app_at_recv_cmd_C(uint8_t sub_cmd, uint8_t *data)
{
    BtStatus status;
    BD_ADDR addr;
    switch(sub_cmd) {
        case 'A':
            status = bt_answer_call(user_bt_env.last_active_index);
            printf("status = %d\r\n",status);
            break;
        case 'B':
            status = bt_hang_up(user_bt_env.last_active_index);
            printf("status = %d\r\n",status);
            break;
        case 'C':
            status = bt_redial(user_bt_env.last_active_index);
            printf("status = %d\r\n",status);
            break;
        case 'D':
        {
            uint8_t number[15];
            uint8_t len = 0;
            uint8_t i;
            for(i = 0; i < 15; i++)
            {
                if(data[i] != '\r'){
                    number[i] = data[i];
                }
                else{
                    break;
                }
            }
            len = i;
            //printf("dial: %s,len=%d\r\n",number,len);
            status = bt_dial_number(user_bt_env.last_active_index,number,len);
            printf("status = %d\r\n",status);
        }
        break;
        case 'E':
            status = bt_list_current_calls(user_bt_env.last_active_index);
            printf("status = %d\r\n",status);
            break;
        case 'F':
            status = bt_transfer_sco(user_bt_env.last_active_index);
            printf("status = %d\r\n",status);
            break;
        case 'G':
        {
            uint8_t dtmf = data[0];
            status = bt_send_dtmf(user_bt_env.last_active_index,dtmf);
            printf("status = %d\r\n",status);        
        }
            break;       
        case 'H':
        {
            //vol---[0x00,0x0f]
            uint8_t vol = ascii_strn2val((const char*)&data[0],16,2);
            status = bt_report_spk_volume(user_bt_env.last_active_index,vol);
            printf("status = %d\r\n",status);        
        }
            break;         
        case 'I':
        {
            uint8_t voltage_str[] = "AT+IPHONEACCEV=1,1,6";

            status = bt_send_hf_cmd(user_bt_env.last_active_index,voltage_str);
            printf("status = %d\r\n",status);        
        }
            break;    
        case 'J':
        {
            uint8_t enabled = ascii_strn2val((const char*)&data[0],16,2);
            status = bt_enable_voice_recognition(user_bt_env.last_active_index, enabled);
            printf("status = %d\r\n",status);
        }
            break;
        case 'K':
            printf("voice recog enabled : %d\r\n",bt_is_voice_rec_active(user_bt_env.last_active_index));
            break;
        case 'L':
        {
            uint8_t clk_str[] = "AT+CCLK?";
            status = bt_send_hf_cmd(user_bt_env.last_active_index,clk_str);
            printf("status = %d\r\n",status);        
        }
            break;
        default:
            break;
    }
    printf("OK\r\n");
}
#endif
#if BTDM_STACK_ENABLE_AG
///HFG
static void app_at_recv_cmd_D(uint8_t sub_cmd, uint8_t *data)
{
    BD_ADDR addr;
    HfgResponse *rsp;
    BtStatus status;
    switch(sub_cmd) {
        case 'A':
        {
            BtStatus       status;
            addr.A[0] = ascii_strn2val((const char*)&data[0],16,2);
            addr.A[1] = ascii_strn2val((const char*)&data[2],16,2);
            addr.A[2] = ascii_strn2val((const char*)&data[4],16,2);
            addr.A[3] = ascii_strn2val((const char*)&data[6],16,2);
            addr.A[4] = ascii_strn2val((const char*)&data[8],16,2);
            addr.A[5] = ascii_strn2val((const char*)&data[10],16,2);
            memcpy(&user_bt_env.dev[0].remote_bd,&addr,6);
            status = HFG_CreateServiceLink(&hfg_channel[0], &addr);
            
            if (status == BT_STATUS_PENDING) {
                printf("Opening Channel...\r\n");
            } else {
                printf("Could not open channel, status: %d\r\n", status);
            }
        }
            break;
        case 'B':
        {
            status = BT_STATUS_NO_RESOURCES;
            rsp = (HfgResponse *)btdm_malloc(sizeof(HfgResponse));
            if(rsp != NULL){
                status = HFG_CreateCodecConnection(&hfg_channel[0], ascii_strn2val((const char*)&data[0],16,2), rsp);
            }
            if(status != BT_STATUS_PENDING){
                btdm_free((void *)rsp);
                if(status == BT_STATUS_RESTRICTED){
                    CMGR_SetAudioVoiceSettings(0x60);
                    HFG_CreateAudioLink(&hfg_channel[0],HFG_AR_LOCAL_USER_ACTION);                
                }
            printf("status = %d\r\n",status);
                }
        }
            break;
        case 'C':
            HFG_SetMasterRole(&hfg_channel[0],TRUE);
            break;
        case 'D':
            HFG_DisconnectAudioLink(&hfg_channel[0], HFG_AR_LOCAL_USER_ACTION);
            break;
        #if BTDM_STACK_ENABLE_HF && BTDM_STACK_ENABLE_A2DP_SNK && BTDM_STACK_ENABLE_A2DP_SRC
        case 'N':
        {
            ///for test, conn0 for phone, conn1 for earpods
            enable_audio_transfer = 1;
            if(((user_bt_env.dev[1].conFlags & LINK_STATUS_MEDIA_PLAYING) == 0)
                && (user_bt_env.dev[0].conFlags & LINK_STATUS_MEDIA_PLAYING)){
                A2DP_StartStream(user_bt_env.dev[1].pstream);
                app_audio_a2dp_sink_stop();
            }
            else if(((user_bt_env.dev[1].conFlags & LINK_STATUS_SCO_CONNECTED) == 0)
                &&(user_bt_env.dev[0].conFlags & LINK_STATUS_SCO_CONNECTED)){
                    app_audio_sco_stop();
                    void bt_free_sco_buffer_list(void);
                    bt_free_sco_buffer_list();
                    HFG_CreateAudioLink(user_bt_env.dev[1].hfg_chan, HFG_AR_LOCAL_USER_ACTION);
            }
        }
            break;
        case 'O':
        {
            enable_audio_transfer = 0;
            if((user_bt_env.dev[0].conFlags & LINK_STATUS_MEDIA_PLAYING) 
                && (user_bt_env.dev[1].conFlags & LINK_STATUS_MEDIA_PLAYING)){
                A2DP_SuspendStream(user_bt_env.dev[1].pstream);
                app_audio_a2dp_sink_start(AUDIO_TYPE_SBC, 44100);
            }
            else if((user_bt_env.dev[1].conFlags & LINK_STATUS_SCO_CONNECTED)
                    &&(user_bt_env.dev[0].conFlags & LINK_STATUS_SCO_CONNECTED)){
                extern void encoded_sco_frame_cb(void *arg, uint8_t *data, uint16_t length);
                void bt_free_sco_buffer_list(void);
                bt_free_sco_buffer_list();
                HFG_DisconnectAudioLink(user_bt_env.dev[1].hfg_chan, HFG_AR_LOCAL_USER_ACTION);
                app_audio_sco_start(AUDIO_TYPE_PCM, encoded_sco_frame_cb, user_bt_env.dev[0].hf_chan);
            }
        }
            break;
        #endif
        default:
            break;
    }
    printf("OK\r\n");    
}
#endif
            
#if BTDM_STACK_ENABLE_A2DP_SNK || BTDM_STACK_ENABLE_A2DP_SRC || BTDM_STACK_ENABLE_AVRCP
#if (USER_ATCMD_EZ == 1)
/*
 * Function: Handle AT command defined by user for testing in engineering mode
 * eg: 
 *      "AT#EZMUTE:<1|0>$"          -- mute(unmute) codec while playing mp3
 *      "AT#EZRR:<reg>$"            -- read register of codec es8389
 *      "AT#EZWR:<reg>=<val>$"      -- write register of codec es8389
 *      "AT#EZRP:<A|B|C|D>,<XX>$"   -- read gpio port of fr3066q chip
 *      "AT#EZWP:<A|B|C|D>,<XX>=<1|0>$" -- write gpio port of fr3066q chip
 *      "AT#EZSET:<PAON|PAOF|MUTE>=<val>$" -- set delay time
 *      "AT#EZMIC:<1|0>$            -- MIC's loopback test. 1: turn on; 0: turn off
 *      "AT#EZKEY:<1|2|3|4|5>$      -- test flash
 *
 * Author: chuzewei on 2026/03/05
 */
//extern void es8389_read_all_reg(void);
extern uint8_t em_audio_read_reg(uint8_t reg);
extern void em_audio_write_reg(uint8_t reg, uint8_t val);
extern int em_gpio_read_port(int group, int number);
extern void em_gpio_write_port(int group, int number, uint8_t val);
extern void enable_amp_mute(uint8_t mute);
extern void enable_media_mute(uint8_t mute);
extern void enable_phone_mute(uint8_t mute);
extern void em_audio_set_paon_delay(uint8_t delay);
extern void em_audio_set_paoff_delay(uint8_t delay);
extern void em_set_pa_mute_delay(uint8_t delay);
extern void em_audio_enable_loopback(uint8_t on);
extern void em_audio_set_mic_gain(uint8_t val);
//extern void w25q_ext_flash_write_test(void);
//extern void w25q_ext_flash_read_test(void);
extern void uds_flash_test_read(void);
extern void uds_flash_test_write(void);
extern void uds_flash_test_del(uint16_t id);
extern void uds_flash_test_add(uint16_t id);
extern void uds_flash_test_lookup(uint16_t id);
void app_at_recv_cmd_EZ_user_cmd(uint8_t* data)
{
    char *p = (char*)data;
    char *p1 = strchr(p, '$');
    
    if (p1)
    {
        *p1 = 0;
    }
    else
    {
        printf("\r\nIlleagal AT cmd: %s\r\n", p);
        return;
    }
    if (strstr(p, "MUTE:"))
    {
        int val = -1;
        //*(p + 6) = 0;
        sscanf(p, "MUTE:%d", &val);
        printf("\r\nMUTE: val = %d\r\n", val);
        if (1 == val || 0 == val)
        {
            //enable_media_mute(val);
            enable_amp_mute(val);
        }
        else
        {
            printf("\r\nMUTE error. Usage: AT#EZMUTE:<1|0>$\r\n");
        }
    }
    else if (strstr(p, "RR:"))
    {
        uint8_t reg, val;
        //*(p + 4) = 0;
        reg = ascii_strn2val(p + 3, 16, 2);
        printf("\r\nRR: reg: 0x%x\r\n", reg);
        val = em_audio_read_reg(reg);
        printf("\r\nRead reg: 0x%X, val: 0x%X\r\n", reg, val);
        //es8389_read_all_reg();
    }
    else if (strstr(p, "WR:"))
    {
        uint8_t reg, val;
        //*(p + 7) = 0;
        reg = ascii_strn2val(p + 3, 16, 2);
        val = ascii_strn2val(p + 3 + 3, 16, 2);
        printf("\r\nWR: reg: 0x%X, val: 0x%X\r\n", reg, val);
        em_audio_write_reg(reg, val);
    }
    else if (strstr(p, "RP:"))
    {
        uint8_t port_type, port_number;
        int gpio_value;
        
        //*(p + 7) = 0;
        port_type = *(p + 3);
        if (port_type >= 'a' && port_type <= 'd')
        {
            port_type = port_type - 'a';
        }
        else if (port_type >= 'A' && port_type <= 'D')
        {
            port_type = port_type - 'A';
        }
        else
        {
            printf("\r\nInput error!\r\n"
                   "Usage: AT#EZRP:<A|B|C|D>,<XX>$\r\n");
            return;
        }
        port_number = ascii_strn2val(p + 2 + 3, 10, 2);
        printf("\r\nRP: GPIO%c_%d\r\n", port_type + 'A', port_number);
        
        gpio_value = em_gpio_read_port(port_type, port_number);
    }
    else if (strstr(p, "WP:"))
    {
        uint8_t port_type, port_number, port_value;
        //*(p + 9) = 0;
        port_type = *(p + 3);
        if (port_type >= 'a' && port_type <= 'd')
        {
            port_type = port_type - 'a';
        }
        else if (port_type >= 'A' && port_type <= 'D')
        {
            port_type = port_type - 'A';
        }
        else
        {
            printf("\r\nInput error!\r\n"
                   "Usage: AT#EZWP:<A|B|C|D>,<XX>=<1|0>$\r\n");
            return;
        }
        port_number = ascii_strn2val(p + 2 + 3, 10, 2);
        port_value = *(p + 8) - '0';
        printf("\r\nWP: GPIO%c_%d=%d\r\n", port_type + 'A', port_number, port_value);
        
        em_gpio_write_port(port_type, port_number, port_value);
    }
    else if (strstr(p, "KEY:"))
    {
        int val;
        sscanf(p, "KEY:%d", &val);
        if (val == 1)
        {
            // read data into internal flash
            uds_flash_test_read();
            
        }
        else if (val == 2)
        {
            // write data from internal flash
            uds_flash_test_write();
            //
        }
        else if (val == 3)
        {
            // delete key in internal flash
            uint16_t id = 0x0;
            sscanf(p, "KEY:3=0x%x", &id);
            if (id)
            { 
                printf("Delete key ID: 0x%X \r\n", id);
                uds_flash_test_del(id);
            }
        }
        else if (val == 4)
        {
            //w25q_ext_flash_read_test();
            // add key in internal flash
            uint16_t id = 0x0;
            sscanf(p, "KEY:4=0x%x", &id);
            if (id)
            { 
                printf("Add key ID: 0x%X \r\n", id);
                uds_flash_test_add(id);
            }
        }
        else if (val == 5)
        {
            //w25q_ext_flash_write_test();
            // lookup key in internal flash
            uint16_t id = 0x0;
            sscanf(p, "KEY:5=0x%x", &id);
            if (id)
            { 
                printf("Lookup key ID: 0x%X \r\n", id);
                uds_flash_test_lookup(id);
            }
        }
        else
        {
            printf("\r\nInput error!\r\n"
                   "Usage: AT#EZKEY:<1|2|3|4|5>$\r\n");
        }
    }
    else if (strstr(p, "SET:"))
    {
        p += 4;
        if (strstr(p, "PAON"))
        {
            int val = 0;
            sscanf(p, "PAON=%d", &val);
            em_audio_set_paon_delay(val & 0xFF);
        }
        else if (strstr(p, "PAOF"))
        {
            int val = 0;
            sscanf(p, "PAOF=%d", &val);
            em_audio_set_paoff_delay(val & 0xFF);
        }
        else if (strstr(p, "MUTE"))
        {
            int val = 0;
            sscanf(p, "MUTE=%d", &val);
            em_set_pa_mute_delay(val & 0xFF);
        }
        else
        {
            printf("\r\nInput error!\r\n"
                   "Usage: AT#EZSET:<PAON|PAOF|MUTE>=<val>$\r\n");
        }
    }
    else if (strstr(p, "MIC:"))
    {
        int val;
        sscanf(p, "MIC:%d", &val);
        printf("\r\nMIC: %d\r\n", val);
        //em_audio_enable_loopback(val & 0x01);
        em_audio_set_mic_gain((uint8_t)(val&0xFF));
    }
    else
    {
        printf("\r\nUsage:\r\n");
        printf("AT#EZMUTE:<1|0>$\r\n"
               "AT#EZRR:<XX>$\r\n"
               "AT#EZWR:<XX>=<XX>$\r\n"
               "AT#EZRP:<A|B|C|D>,<XX>$\r\n"
               "AT#EZWP:<A|B|C|D>,<XX>=<1|0>$\r\n"
               "AT#EZDKY:0xXXXXXXXX$\r\n"
               "AT#EZAKY:0xXXXXXXXX$\r\n"
               "AT#EZRKY:0xXXXXXXXX$\r\n"
               "AT#EZSET:<PAON|PAOF|MUTE>=<val>$\r\n"
               "AT#EZMIC:<1|0>$\r\n"
               "AT#EZKEY:<1|2|3|4|5>$\r\n");
    }
}
#endif // USER_ATCMD_EZ

///A2DP & AVRCP
static void app_at_recv_cmd_E(uint8_t sub_cmd, uint8_t *data)
{
    BD_ADDR addr;
    BtStatus status;
    switch (sub_cmd)
    {
#if BTDM_STACK_ENABLE_AVRCP
    case 'A':
        status = AVRCP_SetPanelKey(user_bt_env.dev[user_bt_env.last_active_index].rcp_chan, AVRCP_POP_PLAY, TRUE);
        printf("status = %d\r\n", status);
        break;
    case 'B':
        status = AVRCP_SetPanelKey(user_bt_env.dev[user_bt_env.last_active_index].rcp_chan, AVRCP_POP_PAUSE, TRUE);
        printf("status = %d\r\n", status);
        break;
    case 'C':
        status = AVRCP_SetPanelKey(user_bt_env.dev[user_bt_env.last_active_index].rcp_chan, AVRCP_POP_FORWARD, TRUE);
        printf("status = %d\r\n", status);
        break;
    case 'D':
    {
        status = AVRCP_SetPanelKey(user_bt_env.dev[user_bt_env.last_active_index].rcp_chan, AVRCP_POP_BACKWARD, TRUE);
        printf("status = %d\r\n", status);
    }
    break;
    case 'E':
    {
            /* uint8_t vol = ascii_strn2val((const char*)&data[0],16,2);
            status = bt_set_media_volume(user_bt_env.last_active_index,vol);
            printf("status = %d\r\n",status); */
            uint8_t vol = ascii_strn2val((const char*)&data[0],16,2);
            if ( vol > 20 )
                vol = 20;
            
            extern void set_audio_codec_volumn(uint8_t level);
            set_audio_codec_volumn(vol);

            float vol_float = (float)vol * 127.0f / 20.0f + 0.5f;
            vol = (uint8_t)vol_float;
            status = bt_set_media_volume(user_bt_env.last_active_index,vol);
            printf("+++++vol = %x\r\n",vol);
			printf("status = %d\r\n", status);
    }
    break;
    case 'F':
    {
        status = bt_get_media_info(user_bt_env.last_active_index, 0x41);
        printf("status = %d\r\n", status);
    }
    break;
    case 'G':
    {
        status = bt_get_playstatus(user_bt_env.last_active_index);
        printf("status = %d\r\n", status);
    }
    break;
    case 'H':
    {
        AvrcpAdvancedPdu *avrcp_cmd;
        avrcp_cmd = (AvrcpAdvancedPdu *)btdm_malloc(sizeof(AvrcpAdvancedPdu));
        avrcp_cmd->parms = (uint8_t *)btdm_malloc(64);
        AVRCP_CtSetAbsoluteVolume(user_bt_env.dev[user_bt_env.last_active_index].rcp_chan, avrcp_cmd, 0x3f);
    }
    break;
#endif
#if BTDM_STACK_ENABLE_A2DP_SRC
    case 'K':
    {
        struct sbc_encoder_param sbc_param;
        extern void encoded_sbc_frame_cb(void *arg, uint8_t *data, uint16_t length);

        bt_source_get_sbc_param(user_bt_env.last_active_index, &sbc_param);
        A2DP_StartStream(user_bt_env.dev[user_bt_env.last_active_index].pstream);
        app_audio_a2dp_source_start(AUDIO_TYPE_MP3, &sbc_param, encoded_sbc_frame_cb, &user_bt_env.last_active_index);
    }
    break;
    case 'L':
        A2DP_SuspendStream(user_bt_env.dev[user_bt_env.last_active_index].pstream);
        app_audio_a2dp_source_stop();
        break;
    case 'M':
    {
        struct sbc_encoder_param sbc_param;
        extern void encoded_sbc_frame_cb(void *arg, uint8_t *data, uint16_t length);
        bt_source_get_sbc_param(0, &sbc_param);
        //                bt_source_get_sbc_param(&sbc_param.alloc_method, &sbc_param.sample_rate, &sbc_param.bitpool);
        A2DP_StartStream(user_bt_env.dev[0].pstream);
        A2DP_StartStream(user_bt_env.dev[1].pstream);
        app_audio_a2dp_source_start(AUDIO_TYPE_MP3, &sbc_param, encoded_sbc_frame_cb, &user_bt_env.last_active_index);
    }
    break;
    case 'R':
        A2DP_SuspendStream(user_bt_env.dev[0].pstream);
        A2DP_SuspendStream(user_bt_env.dev[1].pstream);
        app_audio_a2dp_source_stop();
        break;
#endif
    case 'N':
        // play tone
        app_audio_tone_play(AUDIO_TYPE_SBC, NULL, 0);
        break;
#if (USER_ATCMD_EZ == 1)        
    case 'Z':
        app_at_recv_cmd_EZ_user_cmd(data);
#endif        
    default:
        break;
    }
    printf("OK\r\n");
}
#endif
#if BTDM_STACK_ENABLE_PBAP   
///PBAP
static void app_at_recv_cmd_F(uint8_t sub_cmd, uint8_t *data)
{
    BD_ADDR addr;
    BtStatus status;
    switch(sub_cmd) {    
        case 'C':
//            addr.A[0] = ascii_strn2val((const char*)&data[0],16,2);
//            addr.A[1] = ascii_strn2val((const char*)&data[2],16,2);
//            addr.A[2] = ascii_strn2val((const char*)&data[4],16,2);
//            addr.A[3] = ascii_strn2val((const char*)&data[6],16,2);
//            addr.A[4] = ascii_strn2val((const char*)&data[8],16,2);
//            addr.A[5] = ascii_strn2val((const char*)&data[10],16,2);
            if(user_bt_get_state(user_bt_env.last_active_index) >= BT_STATE_CONNECTED){
                printf("pbap client %d\r\n",pbap_client[user_bt_env.last_active_index].cApp.connState);
                status = PBAP_ClientConnect(&pbap_client[user_bt_env.last_active_index],&user_bt_env.dev[user_bt_env.last_active_index].remote_bd);
                if(status == BT_STATUS_PENDING){
                    user_bt_env.dev[user_bt_env.last_active_index].pbap_client = &pbap_client[user_bt_env.last_active_index];
                }
            }
            printf("status = %d\r\n",status);
            break;
        case 'D':
            status = PBAP_ClientDisconnect(&pbap_client[user_bt_env.last_active_index]);
            printf("status = %d\r\n",status);
            break;
        case 'M':
        {
            uint8_t pbName[64];
            PbapPullPbParms     parms;
            
            memcpy(pbName,PB_LOCAL_CCH_NAME,sizeof(PB_LOCAL_CCH_NAME));
            parms.pbName = pbName;
            memset(parms.filter.byte,0,PBAP_FILTER_SIZE);
            parms.filter.byte[0] = 0x87;
            parms.listStartOffset = 0;
            parms.maxListCount = 1; //0---search missed call and total pb size
            parms.format= VCARD_FORMAT_30;
            status = PBAP_PullPhonebook(&pbap_client[0], &parms);       
            printf("status = %d\r\n",status);
        }
            break;
        case 'O':
        {
            PbapPullVcardListingParms   parms;
            uint8_t search_val[12] = {'\0'}; //= "13262651013";
            //uint8_t search_val[12] = "18016379932";
            memcpy(search_val,&data[0],11);
            uint8_t folder[] = "telecom/pb";
            parms.folderName = folder;
            parms.order = VCARD_SORT_ORDER_ALPHA;
            parms.listStartOffset = 0x00;
            parms.maxListCount = 20;
            parms.searchAttribute = VCARD_SEARCH_ATTRIB_NUMBER;
            parms.searchValue = (char *)search_val;
            status = PBAP_PullVcardListing(&pbap_client[0], &parms);       
            printf("status = %d\r\n",status);        
        }
            break;
        case 'P':
        {
            uint8_t pbName[64];
            PbapPullPbParms     parms;
            
            memcpy(pbName,PB_LOCAL_STORE_NAME,sizeof(PB_LOCAL_STORE_NAME));
            parms.pbName = pbName;
            memset(parms.filter.byte,0,PBAP_FILTER_SIZE);
            parms.filter.byte[0] = 0x87;
            parms.listStartOffset = 0;
            parms.maxListCount = 20; //0---search missed call and total pb size
            parms.format= VCARD_FORMAT_30;
            status = PBAP_PullPhonebook(&pbap_client[0], &parms);       
            printf("status = %d\r\n",status);
        }
            break;
        default:
            break;
    }
}
#endif  

///BLE
static void app_at_recv_cmd_G(uint8_t sub_cmd, uint8_t *data)
{
    struct gap_ble_addr peer_addr;

    switch(sub_cmd) {
        case 'C':
            app_ble_scan_start();
            break;
        case 'D':
            app_ble_scan_stop();
            break;
        case 'E':
            // AT#GE0123456789ab_01
            peer_addr.addr.addr[5] = ascii_strn2val((const char *)&data[0], 16, 2);
            peer_addr.addr.addr[4] = ascii_strn2val((const char *)&data[2], 16, 2);
            peer_addr.addr.addr[3] = ascii_strn2val((const char *)&data[4], 16, 2);
            peer_addr.addr.addr[2] = ascii_strn2val((const char *)&data[6], 16, 2);
            peer_addr.addr.addr[1] = ascii_strn2val((const char *)&data[8], 16, 2);
            peer_addr.addr.addr[0] = ascii_strn2val((const char *)&data[10], 16, 2);
            peer_addr.addr_type = ascii_strn2val((const char *)&data[13], 16, 2);
            app_ble_conn_start(&peer_addr);
            break;
        case 'F':
            app_ble_conn_stop();
            break;
        default:
            break;
    }
    printf("OK\r\n");
}

#if BTDM_STACK_ENABLE_MAP
///MAP
static void app_at_recv_cmd_M(uint8_t sub_cmd, uint8_t *data)
{
    BD_ADDR addr;
    switch(sub_cmd) {
        case 'E':
        {
            ObStatus status;
            ObexTpAddr     target = {0};
            extern bool host_get_bt_last_device(BD_ADDR *addr);
            host_get_bt_last_device(&addr);
            memcpy(&target.proto.bt.addr,&addr,6); 
            target.type = OBEX_TP_BLUETOOTH;
            status = MAP_ClientConnect(&map_client[0],&target);
            printf("status = 0x%x\r\n",status);
        }
            break;
        case 'F':
        {
            ObStatus            status;
            MapGetMessagesListParms     parms;
                /* Assign the phonebook to retrieve */

            parms.mapName = (const uint8_t*)"inbox";
            parms.maxListCount = 0;  
            parms.listStartOffset = 0; 
            //parms.paramMask = 0x108f;
            /* filter unread */
            parms.filterReadStatus = 0;
            status = MAP_ClientGetMessagesListing(&map_client[0],&parms);
            printf("status = %d\r\n",status);
        }
            break;       
        case 'G':
        {
            MapSetFolderParms params;
            ObStatus            status;
            params.folderName = (const uint8_t*)"telecom";
            params.reset = 0;
            params.flags = MAP_SET_FLAG_GO_DOWN;
            status = MAP_ClientSetFolder(&map_client[0],&params);
            printf("status = %d\r\n",status);
        }
            break;    
        case 'H':
        {
            MapSetFolderParms params;
            ObStatus            status;
            params.folderName = (const uint8_t*)"msg";
            params.reset = 0;
            params.flags = MAP_SET_FLAG_GO_DOWN;
            status = MAP_ClientSetFolder(&map_client[0],&params);
            printf("status = %d\r\n",status);
        }
            break;    
        case 'J':
        {
            ObStatus            status;
            status = MAP_ClientDisconnect(&map_client[0]);
            printf("status = %d\r\n",status);
        }
            break;    
        default:
            break;
    }
    printf("OK\r\n");
}
#endif

#if BTDM_STACK_ENABLE_HID
///HID
static void app_at_recv_cmd_H(uint8_t sub_cmd, uint8_t *data)
{
    BD_ADDR addr;
    BtStatus status;
    switch(sub_cmd) {
        case 'A'://左移
        {
            HidInterrupt *Interrupt = (HidInterrupt*)btdm_malloc(sizeof(HidInterrupt));
            
            Interrupt->reportType = HID_REPORT_INPUT;
            Interrupt->dataLen = 4;
            Interrupt->data = (uint8_t *)btdm_malloc(Interrupt->dataLen);

            Interrupt->data[0] = 0x01;
            Interrupt->data[1] = 0xF1;
            Interrupt->data[2] = 0x00;
            Interrupt->data[3] = 0x00;
            
            HID_SendInterrupt(user_bt_env.dev[user_bt_env.last_active_index].hid_chan, Interrupt);
        }
            break;
        case 'B'://右移
        {
            HidInterrupt *Interrupt = (HidInterrupt*)btdm_malloc(sizeof(HidInterrupt));
            
            Interrupt->reportType = HID_REPORT_INPUT;
            Interrupt->dataLen = 4;
            Interrupt->data = (uint8_t *)btdm_malloc(Interrupt->dataLen);

            Interrupt->data[0] = 0x01;
            Interrupt->data[1] = 0x0F;
            Interrupt->data[2] = 0x00;
            Interrupt->data[3] = 0x00;
            
            HID_SendInterrupt(user_bt_env.dev[user_bt_env.last_active_index].hid_chan, Interrupt);
        }
            break;
        
        case 'C': //下移
        {  
            HidInterrupt *Interrupt = (HidInterrupt*)btdm_malloc(sizeof(HidInterrupt));
            
            Interrupt->reportType = HID_REPORT_INPUT;
            Interrupt->dataLen = 4;
            Interrupt->data = (uint8_t *)btdm_malloc(Interrupt->dataLen);

            Interrupt->data[0] = 0x02;
            Interrupt->data[1] = 0x00;
            Interrupt->data[2] = 0x0F;
            Interrupt->data[3] = 0x00;
            
            HID_SendInterrupt(user_bt_env.dev[user_bt_env.last_active_index].hid_chan, Interrupt);
        }
            break;
        
        case 'D': //上移
        {
            HidInterrupt *Interrupt = (HidInterrupt*)btdm_malloc(sizeof(HidInterrupt));
            
            Interrupt->reportType = HID_REPORT_INPUT;
            Interrupt->dataLen = 4;
            Interrupt->data = (uint8_t *)btdm_malloc(Interrupt->dataLen);

            Interrupt->data[0] = 0x02;
            Interrupt->data[1] = 0x00;
            Interrupt->data[2] = 0xF1;
            Interrupt->data[3] = 0x00;
            
            HID_SendInterrupt(user_bt_env.dev[user_bt_env.last_active_index].hid_chan, Interrupt);
        }
            break;
        case 'E':
        {
            addr.A[0] = ascii_strn2val((const char*)&data[0],16,2);
            addr.A[1] = ascii_strn2val((const char*)&data[2],16,2);
            addr.A[2] = ascii_strn2val((const char*)&data[4],16,2);
            addr.A[3] = ascii_strn2val((const char*)&data[6],16,2);
            addr.A[4] = ascii_strn2val((const char*)&data[8],16,2);
            addr.A[5] = ascii_strn2val((const char*)&data[10],16,2);
            memcpy(&user_bt_env.dev[0].remote_bd,&addr,6);
            status = HID_OpenConnection(&hid_channel[0], &addr);
            printf("status = %d\r\n",status);            
        }
            break;
        case 'F':
        {
            status = HID_CloseConnection(user_bt_env.dev[user_bt_env.last_active_index].hid_chan);
            printf("status = %d\r\n",status); 
        }
            break;
        case 'G':
        {
            addr.A[0] = ascii_strn2val((const char*)&data[0],16,2);
            addr.A[1] = ascii_strn2val((const char*)&data[2],16,2);
            addr.A[2] = ascii_strn2val((const char*)&data[4],16,2);
            addr.A[3] = ascii_strn2val((const char*)&data[6],16,2);
            addr.A[4] = ascii_strn2val((const char*)&data[8],16,2);
            addr.A[5] = ascii_strn2val((const char*)&data[10],16,2);
            user_bt_env.connect_times = 3;
            status = bt_connect(&addr,ENABLE_PROFILE_HID);
            printf("status = %d\r\n",status);
        }
            break;
    }
    printf("OK\r\n");
}
#endif

#if BTDM_STACK_ENABLE_SPP
///SPP
static void app_at_recv_cmd_S(uint8_t sub_cmd, uint8_t *data)
{
    BD_ADDR addr;
    BtStatus status;
    switch(sub_cmd) {    
        case 'A':
            addr.A[0] = ascii_strn2val((const char*)&data[0],16,2);
            addr.A[1] = ascii_strn2val((const char*)&data[2],16,2);
            addr.A[2] = ascii_strn2val((const char*)&data[4],16,2);
            addr.A[3] = ascii_strn2val((const char*)&data[6],16,2);
            addr.A[4] = ascii_strn2val((const char*)&data[8],16,2);
            addr.A[5] = ascii_strn2val((const char*)&data[10],16,2);
            user_bt_env.connect_times = 3;
            status = bt_connect(&addr,ENABLE_PROFILE_SPP);
            printf("status = %d\r\n",status);
            break;
        case 'B':
            addr.A[0] = ascii_strn2val((const char*)&data[0],16,2);
            addr.A[1] = ascii_strn2val((const char*)&data[2],16,2);
            addr.A[2] = ascii_strn2val((const char*)&data[4],16,2);
            addr.A[3] = ascii_strn2val((const char*)&data[6],16,2);
            addr.A[4] = ascii_strn2val((const char*)&data[8],16,2);
            addr.A[5] = ascii_strn2val((const char*)&data[10],16,2);
            memcpy(&user_bt_env.dev[0].remote_bd,&addr,6);

            status = spp_connect(&spp_dev[0],&addr);
            printf("status = %d\r\n",status);
            break;
        case 'D':
            status = spp_disconnect(user_bt_env.dev[user_bt_env.last_active_index].spp_dev);
            printf("status = %d\r\n",status);
            break;
        case 'S':
        {
            uint8_t test_data[] = {'1','2','3','4'};
            status = spp_send(user_bt_env.dev[user_bt_env.last_active_index].spp_dev,test_data,sizeof(test_data));
            printf("status = %d\r\n",status);        
        }
            break;
        default:
            break;
    }
    printf("OK\r\n");
}
#endif
#if BTDM_STACK_ENABLE_PAN
/* 定义端口 */
#define TCP_REMOTE_PORT    80 /* 远端端口 */
#define TCP_LOCAL_PORT     8880 /* 本地端口 */

/******************************************************************************
 * 描述  : 数据接收回调函数
 * 参数  : -
 * 返回  : -
******************************************************************************/
static err_t tcp_client_recv(void *arg, struct tcp_pcb *tpcb,
                             struct pbuf *p, err_t err)
{
    uint32_t i;
    
    /* 数据回传 */
    //tcp_write(tpcb, p->payload, p->len, 1);
    
    if (p != NULL)
    {
        struct pbuf *ptmp = p;
        
#if 1
        printf(".");
#else
        /* 打印接收到的数据 */
        printf("get msg from %d:%d:%d:%d port:%d:\r\n",
            *((uint8_t *)&tpcb->remote_ip.addr),
            *((uint8_t *)&tpcb->remote_ip.addr + 1),
            *((uint8_t *)&tpcb->remote_ip.addr + 2),
            *((uint8_t *)&tpcb->remote_ip.addr + 3),
            tpcb->remote_port);
        
        while(ptmp != NULL)
        {
            for (i = 0; i < p->len; i++)
            {
                printf("%c", *((char *)p->payload + i));
            }
            
            ptmp = p->next;
        }
        
        printf("\r\n");
#endif

        tcp_recved(tpcb, p->tot_len);
        
        /* 释放缓冲区数据 */
        pbuf_free(p);
    }
    else if (err == ERR_OK)
    {
        printf("tcp client closed\r\n");
        
        tcp_recved(tpcb, p->tot_len);
        
        return tcp_close(tpcb);
    }

    return ERR_OK;
}

/******************************************************************************
 * 描述  : 连接服务器回调函数
 * 参数  : -
 * 返回  : -
******************************************************************************/
static err_t tcp_client_connected(void *arg, struct tcp_pcb *tpcb, err_t err)
{
    printf("tcp client connected\r\n");
    
    tcp_write(tpcb, "tcp client connected", strlen("tcp client connected"), 0);

    /* 注册接收回调函数 */
    tcp_recv(tpcb, tcp_client_recv);

    return ERR_OK;
}

/******************************************************************************
 * 描述  : 创建tcp客户端
 * 参数  : -
 * 返回  : -
******************************************************************************/
void tcp_client_init(uint8_t ip_1, uint8_t ip_2, uint8_t ip_3, uint8_t ip_4, uint16_t port)
{
    struct tcp_pcb *tpcb;
    ip_addr_t serverIp;
    
    printf("tcp_client_init: %d.%d.%d.%d:%d\r\n", ip_1, ip_2, ip_3, ip_4, port);

     /* 服务器IP */
    IP4_ADDR(&serverIp, ip_1, ip_2, ip_3, ip_4);

    /* 创建tcp控制块 */
    tpcb = tcp_new();
    
    if (tpcb != NULL)
    {
        err_t err;
        
        /* 绑定本地端号和IP地址 */
        err = tcp_bind(tpcb, IP_ADDR_ANY, TCP_LOCAL_PORT);

        if (err == ERR_OK)
        {
            /* 连接服务器 */
            tcp_connect(tpcb, &serverIp, port, tcp_client_connected);
        }
        else
        {
            memp_free(MEMP_TCP_PCB, tpcb);
            
            printf("can not bind pcb\r\n");
        }
    }
}

/******************************** END OF FILE ********************************/

static void udp_receive_callback(void *arg, struct udp_pcb *upcb,
                                    struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    uint32_t i;

    /* 打印接收到的数据 */
    printf("get msg from %d:%d:%d:%d port:%d:\r\n",
        *((uint8_t *)&addr->addr), *((uint8_t *)&addr->addr + 1),
        *((uint8_t *)&addr->addr + 2), *((uint8_t *)&addr->addr + 3), port);
    
    if (p != NULL)
    {
        struct pbuf *ptmp = p;
        
        while(ptmp != NULL)
        {
            for (i = 0; i < p->len; i++)
            {
                printf("%c", *((char *)p->payload + i));
            }
            
            ptmp = p->next;
        }
        
        printf("\r\n");
    }
    
    /* 释放缓冲区数据 */
    pbuf_free(p);
}

static void udp_client_send(struct udp_pcb *upcb, char *pData)
{
    struct pbuf *p;
    
    /* 分配缓冲区空间 */
    p = pbuf_alloc(PBUF_TRANSPORT, strlen(pData), PBUF_POOL);
    
    if (p != NULL)
    {
        /* 填充缓冲区数据 */
        pbuf_take(p, pData, strlen(pData));

        /* 发送udp数据 */
        udp_send(upcb, p);

        /* 释放缓冲区空间 */
        pbuf_free(p);
    }
}

static void client(void *thread_param)
{
    ip4_addr_t dns_ip;
    
    char *host_name[] = {"www.baidu.com", "www.csdn.net", "www.hp.com"};
    static uint8_t index = 0;
    
    netconn_gethostbyname(host_name[index], &dns_ip);
    printf("%s: %d.%d.%d.%d.\r\n", host_name[index], dns_ip.addr&0xff,      \
                                                        (dns_ip.addr>>8)&0xff,   \
                                                        (dns_ip.addr>>16)&0xff,   \
                                                        (dns_ip.addr>>24)&0xff);
    index++;
    if (index >= sizeof(host_name)/sizeof(host_name[0])) {
        index = 0;
    }
    
    vTaskDelete(NULL);
}

void client_init(void)
{
    sys_thread_new("client", client, NULL, 512, 4);
}

static void app_at_recv_cmd_P(uint8_t sub_cmd, uint8_t *data)
{
    static PanUser pan;
    static struct udp_pcb *pudp;

    switch(sub_cmd) {
        case 'A':
            {
                extern BtRemoteDevice *last_rem_dev;
				int16_t err_code;
				
                err_code =PAN_Open(last_rem_dev, &pan, benp_lwip_recv_cb, 0x1116);   // 0x1116: NAP
				printf("PAN Open:%d\r\n",err_code);
            }
            break;
        case 'B':
            // AT#PBxxx_xxxxx
            {
                pudp = udp_new();
                if (pudp) {
                    err_t err;
                    ip_addr_t serverIP;
                    
                    IP4_ADDR(&serverIP, 192, 168, 31, ascii_strn2val((const char*)&data[0],10,3));
                    pudp->local_port = ascii_strn2val((const char*)&data[4],10,5);

                    err= udp_connect(pudp, &serverIP, 8080);
                    if (err == ERR_OK) {
                        udp_recv(pudp, udp_receive_callback, NULL);
                    }
                    else {
                        printf("connect UDP failed: %d.\r\n", err);
                    }
                }
                else {
                    printf("create UDP failed.\r\n");
                }
            }
            break;
        case 'C':
            // AT#PB
            {
                udp_client_send(pudp, "udp client connected");
            }
            break;
        case 'D':
            // AT#PDxxx_xxx_xxx_xxx_xxxxx
            {
                uint8_t ip_1, ip_2, ip_3, ip_4;
                uint16_t port;
                ip_1 = ascii_strn2val((const char*)&data[0],10,3);
                ip_2 = ascii_strn2val((const char*)&data[4],10,3);
                ip_3 = ascii_strn2val((const char*)&data[8],10,3);
                ip_4 = ascii_strn2val((const char*)&data[12],10,3);
                port = ascii_strn2val((const char*)&data[16],10,5);
                tcp_client_init(ip_1, ip_2, ip_3, ip_4, port);
            }
            break;
        case 'E':
            // TEST DNS
            {
                void client_init(void);
                client_init();
            }
            break;
    }
}
#endif
#endif //#if BTDM_STACK_ENABLE_BT
void app_at_cmd_recv_handler(uint8_t *data, uint16_t length)
{
    switch(data[0])
    {
        ///rd/wr reg + test
        case 'A':
            app_at_recv_cmd_A(data[1], &data[2]);
            break;
#if BTDM_STACK_ENABLE_BT
        ///me cmd
        case 'B':
            app_at_recv_cmd_B(data[1], &data[2]);
            break;
#if BTDM_STACK_ENABLE_HF           
        ///hf 
        case 'C':
            app_at_recv_cmd_C(data[1], &data[2]);
            break;
#endif
#if BTDM_STACK_ENABLE_AG
        ///hfg
        case 'D':
            app_at_recv_cmd_D(data[1], &data[2]);
            break;
#endif
#if BTDM_STACK_ENABLE_A2DP_SNK || BTDM_STACK_ENABLE_A2DP_SRC || BTDM_STACK_ENABLE_AVRCP
        ///a2dp&avrcp
        case 'E':
            app_at_recv_cmd_E(data[1], &data[2]);
            break;
#endif
#if BTDM_STACK_ENABLE_PBAP
        ///pbap
        case 'F':
            app_at_recv_cmd_F(data[1], &data[2]);
            break;
#endif
        ///BLE
        case 'G':
            app_at_recv_cmd_G(data[1], &data[2]);
            break;
#if BTDM_STACK_ENABLE_MAP
        ///map
        case 'M':
            app_at_recv_cmd_M(data[1], &data[2]);
            break;
#endif
#if BTDM_STACK_ENABLE_HID
        ///hid
        case 'H':
            app_at_recv_cmd_H(data[1], &data[2]);
            break;
#endif
#if BTDM_STACK_ENABLE_SPP
        ///spp
        case 'S':
            app_at_recv_cmd_S(data[1], &data[2]);
            break;
#endif
#if BTDM_STACK_ENABLE_PAN
        case 'P':
            app_at_recv_cmd_P(data[1],&data[2]);
            break;
#endif
#endif
        default:
            break;
    }
}

static void app_at_recv_c(uint8_t c)
{
    switch(at_recv_state)
    {
        case 0:
            if(c == 'A')
            {
                at_recv_state++;
            }
            break;
        case 1:
            if(c == 'T')
                at_recv_state++;
            else
                at_recv_state = 0;
            break;
        case 2:
            if(c == '#')
                at_recv_state++;
            else
                at_recv_state = 0;
            break;
        case 3:
            at_recv_buffer[at_recv_index++] = c;
            if((c == '\n')
               ||(at_recv_index >= AT_RECV_MAX_LEN))
            {
                struct app_task_event *event;
                event = app_task_event_alloc(APP_TASK_EVENT_AT_CMD, at_recv_index, false);
                if(event) {
                    memcpy(event->param, at_recv_buffer, at_recv_index);
                    app_task_event_post(event, false);
                }
                at_recv_state = 0;
                at_recv_index = 0;
            }
            break;
    }
}

void app_at_rx_done(struct __UART_HandleTypeDef *handle)
{
    app_at_recv_c(app_at_recv_char);
    if (handle) {
        uart_receive_IT(handle, &app_at_recv_char, 1);
    }
}

void app_at_init(struct __UART_HandleTypeDef *handle)
{
    uart_receive_IT(handle, &app_at_recv_char, 1);
}
