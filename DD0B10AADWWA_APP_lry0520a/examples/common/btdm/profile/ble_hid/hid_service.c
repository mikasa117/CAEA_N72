/**
 * Copyright (c) 2019, Freqchip
 *
 * All rights reserved.
 *
 *
 */

/*
 * INCLUDES
 */
#include <stdio.h>
#include <string.h>
#include "gap_api.h"
#include "gatt_api.h"
#include "gatt_sig_uuid.h"

#include "hid_service.h"
#include "co_math.h"

/*
 * MACROS (宏定义)
 */
#define CFG_CON                     20

/*
 * TYPEDEFS(类型定义) 
 */
 
/*
 * CONSTANTS(常量定义) 
 */
const uint8_t hid_svc_uuid[] = UUID16_ARR(HID_SERV_UUID);

// HID Information data
const uint8_t hid_info_value[] =
{
    LO_UINT16(0x0111), HI_UINT16(0x0111),             // bcdHID (USB HID version)
    0x00,                                             // bCountryCode
    HID_FLAGS_REMOTE_WAKE | HID_FLAGS_NORMALLY_CONNECTABLE     // Flags
};

/******************************* HID Report Map characteristic defination */
static const uint8_t hid_report_map[] =
{
    0x05, 0x01,  // Usage Page (Generic Desktop)
    0x09, 0x02,  // Usage (Mouse)
    0xA1, 0x01,  // Collection (Application)
    0x85, 0x01,  // Report Id (1)
    0x09, 0x01,  //   Usage (Pointer)
    0xA1, 0x00,  //   Collection (Physical)

//rpt id == 1
    0x05, 0x09,  //     Usage Page (Mouse)
    0x19, 0x01,  //     Usage Minimum (01) - Button 1
    0x29, 0x03,  //     Usage Maximum (03) - Button 3
    0x15, 0x00,  //     Logical Minimum (0)
    0x25, 0x01,  //     Logical Maximum (1)
    0x75, 0x01,  //     Report Size (1)
    0x95, 0x03,  //     Report Count (3)
    0x81, 0x02,  //     Input (Data, Variable, Absolute) - Button states

    0x75, 0x05,  //     Report Size (5)
    0x95, 0x01,  //     Report Count (1)
    0x81, 0x01,  //     Input (Constant) - Padding or Reserved bits

    0x05, 0x01,  //     Usage Page (Generic Desktop)
    0x09, 0x30,  //     Usage (X)
    0x09, 0x31,  //     Usage (Y)
    0x09, 0x38,  //     Usage (Wheel)
    0x15, 0x81,  //     Logical Minimum (-127)
    0x25, 0x7F,  //     Logical Maximum (127)
    0x75, 0x08,  //     Report Size (8)
    0x95, 0x03,  //     Report Count (3)
    0x81, 0x06,  //     Input (Data, Variable, Relative) - X & Y wheal  3bytes
    0xC0,        //   End Collection
    0xC0,        // End Collection

//rpt id == 1
    0x05,0x0c,               // Usage Page (Consumer Devices)
    0x09,0x01,               // Usage index(Consumer Control)
    0xa1,0x01,               // Collection (Application)
    0x85,0x02,               //  Report ID (2)
#if 0    
    0x15,0x00,         //  Logical Minimum (0)
    0x25,0x01,         //  Logical Maximum (1)
    0x75,0x01,         //  Report Size (1)
    0x95,0x01,         //  Report Count (1)

    0x09,0xcd,        // Usage index(Play/Pause)
    0x81,0x06,              //input(Data,Value,Relative,Bit,Filed)
    0x0a, 0x21, 0x02,   //   Usage (OPEN_SEARCHA) 5
    0x81,0x06,              //input(Data,Value,Relative,Bit,Filed)
    0x09,0xb5,        //  Usage (Scan Next Track)
    0x81,0x06,              //input(Data,Value,Relative,Bit,Filed)
    0x09,0xb6,        //  Usage (Scan Previous Track)
    0x81,0x06,              //input(Data,Value,Relative,Bit,Filed)

    0x09,0xea,        //  Usage (Volume -)
    0x81,0x06,              //input(Data,Value,Relative,Bit,Filed)
    0x09,0xe9,        //  Usage (Volume +)
    0x81,0x06,              //input(Data,Value,Relative,Bit,Filed)
    0x0a,0x25,0x02,     //Usage(AC Forward)
    0x81,0x06,              //input(Data,Value,Relative,Bit,Filed)
    0x0a,0x24,0x02,   //Usage(AC Back)
    0x81,0x06,              //input(Data,Value,Relative,Bit,Filed)
#else
    0x75,0x10,         //  Report Size (16)
    0x95,0x01,         //  Report Count (1)
    0x15, 0x01,         /*   LOGICAL_MINIMUM */
    0x26, 0xff, 0x03,   /*   LOGICAL_MAXIMUM */
    0x19, 0x01,          /*   USAGE MINIMUM (Consumer control) */  
    0x2a, 0xff, 0x03,   /*   USAGE MAXIMUM (Reserved) */      
    0x81, 0x60,         /*   INPUT (No preferred state, null state) */
#endif

    0xc0,                           // End Collection

//rpt id == 2
    0x05, 0x01,     // Usage Pg (Generic Desktop)
    0x09, 0x06,     // Usage (Keyboard)
    0xA1, 0x01,     // Collection: (Application)
    0x85, 0x03,     // Report Id (3 for keyboard)
    //
    0x05, 0x07,     // Usage Pg (Key Codes)
    0x19, 0xE0,     // Usage Min (224)
    0x29, 0xE7,     // Usage Max (231)
    0x15, 0x00,     // Log Min (0)
    0x25, 0x01,     // Log Max (1)
    //
    // Modifier byte
    0x75, 0x01,     // Report Size (1)   1 bit * 8
    0x95, 0x08,     // Report Count (8)
    0x81, 0x02,     // Input: (Data, Variable, Absolute)

    // Reserved byte
    0x95, 0x01, // Report Count (1)
    0x75, 0x08, // Report Size (8)
    0x81, 0x01, // Input: (Constant)

    //LED repor
    0x95, 0x05,    //Report Count (5)
    0x75, 0x01,    //Report Size (1)
    0x05, 0x08,    //Usage Pg (LEDs )
    0x19, 0x01,    //Usage Min
    0x29, 0x05,    //Usage Max
    0x91, 0x02,    //Output (Data, Variable, Absolute)
    //3 bit reserved
    0x95, 0x01,    //Report Count (1)
    0x75, 0x03,    //Report Size (3)
    0x91, 0x01,    //Output (Constant)

    // Key arrays (6 bytes)
    // this is key array,support simultaneously pressing 6keys report,
    // from report_buf[3]~report_buf[3]
    0x95, 0x06,     // Report Count (6)
    0x75, 0x08,     // Report Size (8)
    0x15, 0x00,     // Log Min (0)
    0x25, 0xE7,     // Log Max (237)
    0x05, 0x07,     // Usage Pg (Key Codes) , here is the key page,look usb hid key define
    0x19, 0x00,     // Usage Min (0)
    0x29, 0xE7,     // Usage Max (237)
    0x81, 0x00,     // Input: (Data, Array)
    0xC0,            // End Collection

};
/******************************* External Report Reference defination */
// External Report Reference Descriptor UUID
const uint8_t ext_report_ref_uuid[] = UUID16_ARR(0x00);

/*
 * EXTERNAL VARIABLES(外部变量) 
 */
extern uint8_t slave_link_conidx;

/*
 * GLOBAL VARIABLES(全局变量) 
 */
uint8_t hid_svc_id = 0;


/*
 * LOCAL VARIABLES(本地变量) 
 */
// HID report information table
static hid_report_ref_t  hid_rpt_info[HID_NUM_REPORTS];
static bool hid_link_ntf_enable[CFG_CON] = {0};
static bool hid_link_enable[CFG_CON] = {0};


const gatt_attribute_t hid_profile_att_table[] =
{
    [HID_SERVICE_IDX]               =   { 
                                            { UUID_SIZE_2, UUID16_ARR(GATT_PRIMARY_SERVICE_UUID) },
                                            GATT_PROP_READ, 
                                            UUID_SIZE_2, 
                                            (uint8_t *)hid_svc_uuid,
                                        },

#if ((HID_DEV & HID_DEV_MAP_EXT_REF) == HID_DEV_MAP_EXT_REF)
    //[HID_INCLUDED_SERVICE_IDX]      =   { 
    //                                        { UUID_SIZE_2, UUID16_ARR(GATT_INCLUDE_UUID) },
    //                                        GATT_PROP_READ,
    //                                        0,
    //                                        NULL,
    //                                    },
#endif //((HID_DEV & HID_DEV_MAP_EXT_REF) == HID_DEV_MAP_EXT_REF)

    [HID_INFO_DECL_IDX]             =   { 
                                            { UUID_SIZE_2, UUID16_ARR(GATT_CHARACTER_UUID) },
                                            GATT_PROP_READ,
                                            0, 
                                            NULL,
                                        },
    
    [HID_INFO_IDX]                  =   { 
                                            { UUID_SIZE_2, UUID16_ARR(HID_INFORMATION_UUID) },
                                            GATT_PROP_READ | GATT_PROP_READ_UNAUTH | GATT_PROP_WRITE_UNAUTH | GATT_PROP_NI_UNAUTH,     //GATT_PROP_AUTHEN
                                            sizeof(hid_info_value), 
                                            NULL,
                                        },


    // HID Control Point characteristic declaration
    [HID_CONTROL_POINT_DECL_IDX]    =   { 
                                            { UUID_SIZE_2, UUID16_ARR(GATT_CHARACTER_UUID) },
                                            GATT_PROP_READ, 
                                            0,
                                            NULL,
                                        },
                                        
    // HID Control Point characteristic value
    [HID_CONTROL_POINT_IDX]         =   { 
                                            { UUID_SIZE_2, UUID16_ARR(HID_CTRL_PT_UUID) },
                                            GATT_PROP_WRITE_REQ | GATT_PROP_WRITE_CMD, 
                                            sizeof(uint8_t), 
                                            NULL,
                                        },

    // HID Report Map characteristic declaration
    [HID_REPORT_MAP_DECL_IDX]       =   { 
                                            { UUID_SIZE_2, UUID16_ARR(GATT_CHARACTER_UUID) },
                                            GATT_PROP_READ, 
                                            0, 
                                            NULL,
                                        },

    // HID Report Map characteristic
    [HID_REPORT_MAP_IDX]            =   { 
                                            { UUID_SIZE_2, UUID16_ARR(REPORT_MAP_UUID) },
                                            GATT_PROP_READ,  
                                            512, 
                                            NULL,
                                        },

#if ((HID_DEV & HID_DEV_MAP_EXT_REF) == HID_DEV_MAP_EXT_REF)
    // Report Map Characteristic - External Report Reference Descriptor
    [HID_REPORT_MAP_EXT_REP_REF]    =   { 
                                            { UUID_SIZE_2, UUID16_ARR(GATT_EXT_REPORT_REF_UUID) },
                                            GATT_PROP_WRITE, 
                                            sizeof(ext_report_ref_uuid), 
                                            (uint8_t *)ext_report_ref_uuid,
                                        },
#endif //((HID_DEV & HID_DEV_MAP_EXT_REF) == HID_DEV_MAP_EXT_REF)

#if ((HID_DEV & HID_DEV_PROTO_MODE) == HID_DEV_PROTO_MODE)
    // HID Protocol Mode characteristic declaration
    [HID_PROTOCOL_MODE_DECL_IDX]    =   { 
                                            { UUID_SIZE_2, UUID16_ARR(GATT_CHARACTER_UUID) },
                                            GATT_PROP_READ, 
                                            0,
                                            NULL,
                                        },
                                        
    // HID Protocol Mode characteristic
    [HID_PROTOCOL_MODE_IDX]         =   { 
                                            { UUID_SIZE_2, UUID16_ARR(PROTOCOL_MODE_UUID) },
                                            GATT_PROP_READ | GATT_PROP_WRITE, 
                                            sizeof(uint8_t),
                                            NULL,
                                        },
#endif //((HID_DEV & HID_DEV_PROTO_MODE) == HID_DEV_PROTO_MODE)

#if ((HID_DEV & HID_DEV_KEYBOARD) == HID_DEV_KEYBOARD)
    // HID Boot Keyboard Input Report declaration
    [HID_BOOT_KEY_IN_DECL_IDX]      =   { 
                                            { UUID_SIZE_2, UUID16_ARR(GATT_CHARACTER_UUID) },
                                            GATT_PROP_READ,
                                            0,
                                            NULL,
                                        },
    // HID Boot Keyboard Input Report
    [HID_BOOT_KEY_IN_IDX]           =   { 
                                            { UUID_SIZE_2, UUID16_ARR(BOOT_KEY_INPUT_UUID) },
                                            GATT_PROP_READ | GATT_PROP_NOTI,
                                            8,
                                            NULL,
                                        },
    // HID Report characteristic, key input client characteristic configuration
    [HID_BOOT_KEY_IN_CCCD_IDX]      =   { 
                                            { UUID_SIZE_2, UUID16_ARR(GATT_CLIENT_CHAR_CFG_UUID) },
                                            GATT_PROP_READ | GATT_PROP_WRITE_CMD | GATT_PROP_WRITE_REQ,
                                            0,
                                            NULL,
                                        },

    // HID Boot Keyboard Output Report declaration
    [HID_BOOT_KEY_OUT_DECL_IDX]     =   { 
                                            { UUID_SIZE_2, UUID16_ARR(GATT_CHARACTER_UUID) },
                                            GATT_PROP_READ,
                                            0,
                                            NULL,
                                        },
                                        
    // HID Boot Keyboard Output Report
    [HID_BOOT_KEY_OUT_IDX]          =   { 
                                            { UUID_SIZE_2, UUID16_ARR(BOOT_KEY_OUTPUT_UUID) },
                                            GATT_PROP_READ | GATT_PROP_WRITE_CMD | GATT_PROP_WRITE_REQ,
                                            8,
                                            NULL,
                                        },
#endif //((HID_DEV & HID_DEV_KEYBOARD) == HID_DEV_KEYBOARD)

#if ((HID_DEV & HID_DEV_MOUSE) == HID_DEV_MOUSE)
    // HID Boot Mouse Input Report declaration
    [HID_BOOT_MOUSE_IN_DECL_IDX]    =   { 
                                            { UUID_SIZE_2, UUID16_ARR(GATT_CHARACTER_UUID) },
                                            GATT_PROP_READ,
                                            0,
                                            NULL,
                                        },
                                        
    // HID Boot Mouse Input Report
    [HID_BOOT_MOUSE_IN_IDX]         =   { 
                                            { UUID_SIZE_2, UUID16_ARR(BOOT_MOUSE_INPUT_UUID) },
                                            GATT_PROP_READ | GATT_PROP_WRITE | GATT_PROP_NOTI,
                                            8,
                                            NULL,
                                        },
                                        
    // HID Report characteristic, key input client characteristic configuration
    [HID_BOOT_MOUSE_IN_CCCD_IDX]    =   { 
                                            { UUID_SIZE_2, UUID16_ARR(GATT_CLIENT_CHAR_CFG_UUID) },
                                            GATT_PROP_READ | GATT_PROP_WRITE,
                                            0,
                                            NULL,
                                        },
#endif // ((HID_DEV & HID_DEV_MOUSE) == HID_DEV_MOUSE)

// HID Feature Report No 0
    [HID_FEATURE_DECL_IDX]          =   { 
                                            { UUID_SIZE_2, UUID16_ARR(GATT_CHARACTER_UUID) },
                                            GATT_PROP_READ, 
                                            0,
                                            NULL,
                                        },
                                        
    [HID_FEATURE_IDX]               =   { 
                                            { UUID_SIZE_2, UUID16_ARR(REPORT_UUID) },
                                            GATT_PROP_READ | GATT_PROP_NOTI,
                                            60,
                                            NULL,
                                        },
                                        
    [HID_REPORT_REF_FEATURE_IDX]    =   { 
                                            { UUID_SIZE_2, UUID16_ARR(GATT_REPORT_REF_UUID) },
                                            GATT_PROP_READ,
                                            sizeof(hid_report_ref_t), 
                                            NULL,
                                        },
                                        
    [HID_FEATURE_CCCD_IDX]          =   { 
                                            { UUID_SIZE_2, UUID16_ARR(GATT_CLIENT_CHAR_CFG_UUID) },
                                            GATT_PROP_READ | GATT_PROP_WRITE_CMD | GATT_PROP_WRITE_REQ, 
                                            0, 
                                            NULL,
                                        },

    // HID Feature Report No 1
    [HID_FEATURE_DECL_IDX + 4 * 1]          =   { 
                                                    { UUID_SIZE_2, UUID16_ARR(GATT_CHARACTER_UUID) },
                                                    GATT_PROP_READ, 
                                                    0,
                                                    NULL,
                                                },
                                        
    [HID_FEATURE_IDX + 4 * 1]               =   { 
                                                    { UUID_SIZE_2, UUID16_ARR(REPORT_UUID) },
                                                    GATT_PROP_READ | GATT_PROP_NOTI,
                                                    60,
                                                    NULL,
                                                },
                                        
    [HID_REPORT_REF_FEATURE_IDX + 4 * 1]    =   { 
                                                    { UUID_SIZE_2, UUID16_ARR(GATT_REPORT_REF_UUID) },
                                                    GATT_PROP_READ,
                                                    sizeof(hid_report_ref_t), 
                                                    NULL,
                                                },
                                                
    [HID_FEATURE_CCCD_IDX + 4 * 1]          =   { 
                                                    { UUID_SIZE_2, UUID16_ARR(GATT_CLIENT_CHAR_CFG_UUID) },
                                                    GATT_PROP_READ | GATT_PROP_WRITE_CMD | GATT_PROP_WRITE_REQ, 
                                                    0, 
                                                    NULL,
                                                },

    // HID Feature Report No 2
    [HID_FEATURE_DECL_IDX + 4 * 2]          =   { 
                                                    { UUID_SIZE_2, UUID16_ARR(GATT_CHARACTER_UUID) },
                                                    GATT_PROP_READ, 
                                                    0,
                                                    NULL,
                                                },
                                                
    [HID_FEATURE_IDX + 4 * 2]               =   { 
                                                    { UUID_SIZE_2, UUID16_ARR(REPORT_UUID) },
                                                    GATT_PROP_READ | GATT_PROP_NOTI,
                                                    60,
                                                    NULL,
                                                },
                                                
    [HID_REPORT_REF_FEATURE_IDX + 4 * 2]    =   { 
                                                    { UUID_SIZE_2, UUID16_ARR(GATT_REPORT_REF_UUID) },
                                                    GATT_PROP_READ,
                                                    sizeof(hid_report_ref_t), 
                                                    NULL,
                                                },
                                                
    [HID_FEATURE_CCCD_IDX + 4 * 2]          =   { 
                                                    { UUID_SIZE_2, UUID16_ARR(GATT_CLIENT_CHAR_CFG_UUID) },
                                                    GATT_PROP_READ | GATT_PROP_WRITE_CMD | GATT_PROP_WRITE_REQ, 
                                                    0, 
                                                    NULL,
                                                },

    // HID Feature Report No 3
    [HID_FEATURE_DECL_IDX + 4 * 3]          =   { 
                                                    { UUID_SIZE_2, UUID16_ARR(GATT_CHARACTER_UUID) },
                                                    GATT_PROP_READ, 
                                                    0,
                                                    NULL,
                                                },
                                                
    [HID_FEATURE_IDX + 4 * 3]               =   { 
                                                    { UUID_SIZE_2, UUID16_ARR(REPORT_UUID) },
                                                    GATT_PROP_READ | GATT_PROP_WRITE_CMD | GATT_PROP_WRITE_REQ,
                                                    60,
                                                    NULL,
                                                },
                                                
    [HID_REPORT_REF_FEATURE_IDX + 4 * 3]    =   { 
                                                    { UUID_SIZE_2, UUID16_ARR(GATT_REPORT_REF_UUID) },
                                                    GATT_PROP_READ,
                                                    sizeof(hid_report_ref_t), 
                                                    NULL,
                                                },
                                                
    [HID_FEATURE_CCCD_IDX + 4 * 3]          =   { 
                                                    { UUID_SIZE_2, UUID16_ARR(GATT_CLIENT_CHAR_CFG_UUID) },
                                                    GATT_PROP_READ | GATT_PROP_WRITE_CMD | GATT_PROP_WRITE_REQ, 
                                                    0, 
                                                    NULL,
                                                },
};


static void show_reg(uint8_t *data,uint32_t len,uint8_t dbg_on)
{
    uint32_t i=0;
    if(len == 0 || (dbg_on==0)) return;
    for(; i<len; i++)
    {
        printf("0x%02X,",data[i]);
    }
    printf("\r\n");
}

/*********************************************************************
 * @fn      hid_gatt_msg_handler
 *
 * @brief   HID gatt message handler.
 *
 *
 * @param   p_msg  - messages from GATT layer.
 *
 * @return  none.
 */
static uint16_t hid_gatt_msg_handler(struct gatt_msg *p_msg)
{
    switch(p_msg->msg_evt)
    {
        case GATTS_MSG_READ_REQ:
            {   
                uint16_t rsp_length = 0;
                uint16_t user_mtu;
                gatt_mtu_get(p_msg->conn_idx,&user_mtu);
                if(p_msg->att_idx == HID_REPORT_MAP_IDX)
                {
                    if(sizeof(hid_report_map) > p_msg->param.gatt_data.offset)
                    {
                        rsp_length = sizeof(hid_report_map) - p_msg->param.gatt_data.offset;
                        rsp_length = co_min(user_mtu-1,rsp_length);
                        printf("report_map request:%d\r\n",sizeof(hid_report_map));
                        memcpy(p_msg->param.gatt_data.p_msg_data, hid_report_map + p_msg->param.gatt_data.offset, rsp_length);
                    }
                    return rsp_length;
                }
                else if (p_msg->att_idx == HID_INFO_IDX)
                {
                    if(sizeof(hid_info_value) > p_msg->param.gatt_data.offset)
                    {
                        rsp_length = sizeof(hid_info_value) - p_msg->param.gatt_data.offset;
                        rsp_length = co_min(user_mtu-1,rsp_length);
                        printf("hid info request\r\n");
                        memcpy(p_msg->param.gatt_data.p_msg_data, hid_info_value + p_msg->param.gatt_data.offset , rsp_length);
                    }
                    return rsp_length;
                }
                else
                {
                    for(uint8_t idx=0; idx<HID_NUM_REPORTS; idx++)
                    {
                        if(p_msg->att_idx == HID_REPORT_REF_FEATURE_IDX + 4 * idx)
                        {
                            if(sizeof(hid_report_ref_t) > p_msg->param.gatt_data.offset)
                            {
                                rsp_length = sizeof(hid_report_ref_t) - p_msg->param.gatt_data.offset;
                                rsp_length = co_min(user_mtu-1,rsp_length);
                                memcpy(p_msg->param.gatt_data.p_msg_data, (uint8_t *)&hid_rpt_info[idx] + p_msg->param.gatt_data.offset, rsp_length);
                            }
                            printf("report_ref[%d] request\r\n",idx);
                            return rsp_length;
                        }
                    }
                }
            }
            break;

        case GATTS_MSG_WRITE_REQ:
            {
                if(p_msg->att_idx == HID_BOOT_KEY_IN_CCCD_IDX)
                {
                    printf("boot_key_ntf_enable:");
                    show_reg(p_msg->param.gatt_data.p_msg_data,p_msg->param.gatt_data.msg_len,1);
                }
                else if(p_msg->att_idx == HID_FEATURE_IDX + 4 * 3)
                {
                    printf("write report_id 3:");
                    show_reg(p_msg->param.gatt_data.p_msg_data,p_msg->param.gatt_data.msg_len,1);
                    uint8_t *data = p_msg->param.gatt_data.p_msg_data;
                    if(data[0] & (1<<0))
                        printf("num_lock on\r\n");
                    else
                        printf("num_lock off\r\n");
                    if (data[0] & (1<<1))
                        printf("caps_lock on\r\n");
                    else
                        printf("caps_lock off\r\n");
                    hid_link_ntf_enable[p_msg->conn_idx] = true;
                }
                else
                {
                    for(uint8_t idx=0; idx<HID_NUM_REPORTS; idx++)
                    {
                        if(p_msg->att_idx == HID_FEATURE_CCCD_IDX + 4 * idx)
                        {
                            printf("ntf_enable[%d]:",idx);
                            show_reg(p_msg->param.gatt_data.p_msg_data,p_msg->param.gatt_data.msg_len,1);
                        }
                        if(idx == 2)
                            hid_link_ntf_enable[p_msg->conn_idx] = true;
                    }
                }
            }
            break;

        case GATTC_MSG_CMP_EVT:
            {
                switch(p_msg->param.gatt_op_cmp.operation)
                {
                    case GATT_OP_NOTIFY:
                        printf("ntf cmp,conidx:%d,status:%02x\r\n",p_msg->conn_idx,p_msg->param.gatt_op_cmp.status);
                        break;
                    
                    default:
                        break;
                }
            }
            break;
        case GATTC_MSG_LINK_CREATE:
            {
                printf("hid link[%d] create\r\n",p_msg->conn_idx);
                hid_link_ntf_enable[p_msg->conn_idx] = true;
            }
            break;
        case GATTC_MSG_LINK_LOST:
            {
                hid_link_ntf_enable[p_msg->conn_idx] = false;
                hid_link_enable[p_msg->conn_idx] = false;
            }
            break;
        default:
            break;
    }
    return 0;
}

/*********************************************************************
 * @fn      hid_gatt_report_notify
 *
 * @brief   Send HID notification, keys, mouse values, etc.
 *
 *
 * @param   rpt_info_id - report idx of the hid_rpt_info array.
 *          len         - length of the HID information data.
 *          p_data      - data of the HID information to be sent.
 *
 * @return  none.
 */
void hid_gatt_report_notify(uint8_t conidx, uint8_t rpt_info_id, uint8_t *p_data, uint16_t len)
{
    if (rpt_info_id < HID_NUM_REPORTS && hid_link_ntf_enable[conidx])
    {
        struct gatt_send_event ntf;
        uint16_t user_mtu;
        
        gatt_mtu_get(conidx,&user_mtu);
        
        ntf.conidx = conidx;
        ntf.svc_id = hid_svc_id;
        ntf.att_idx = HID_FEATURE_IDX + 4*(rpt_info_id) ;
        ntf.data_len = co_min(user_mtu-3,len);
        ntf.p_data = p_data;
        gatt_notification(&ntf);
    }
}

/*********************************************************************
 * @fn      consumer_control
 *
 * @brief   HID consumer control
 *
 *
 * @param   conidx      - connect idx
 *          uint8_t     - consumer value.
 *
 * @return  none.
 */
void hid_consumer_control(uint8_t conidx,uint8_t value)
{
    uint8_t hid_rpt_buff[2];
    
    hid_rpt_buff[0] = value;
    hid_rpt_buff[1] = 0x00;
    hid_gatt_report_notify(conidx,1,hid_rpt_buff,2);
    
    hid_rpt_buff[0] = 0x00;
    hid_rpt_buff[1] = 0x00;
    hid_gatt_report_notify(conidx,1,hid_rpt_buff,2);
}

/*********************************************************************
 * @fn      hid_gatt_add_service
 *
 * @brief   Simple Profile add GATT service function.
 *          
 *
 * @param   None.
 *
 *
 * @return  None.
 */
void hid_gatt_add_service(void)
{
    gatt_service_t hid_profie_svc;

    hid_profie_svc.p_att_tb = hid_profile_att_table;
    hid_profie_svc.att_nb = HID_ATT_NB;
    hid_profie_svc.gatt_msg_handler = hid_gatt_msg_handler;

    hid_rpt_info[0].report_id = 1;     //refer to report map, this is Mouse
    hid_rpt_info[0].report_type = HID_REPORT_TYPE_INPUT;

    hid_rpt_info[1].report_id = 2;      //refer to report map, this is Cosumer Controller
    hid_rpt_info[1].report_type = HID_REPORT_TYPE_INPUT;

    hid_rpt_info[2].report_id = 3;      //refer to report map, this is Keyboard input.
    hid_rpt_info[2].report_type = HID_REPORT_TYPE_INPUT;     //att_table, perm must be GATT_PROP_READ | GATT_PROP_NOTI

    hid_rpt_info[3].report_id = 3;      //refer to report map, this is Keyboard output.
    hid_rpt_info[3].report_type = HID_REPORT_TYPE_OUTPUT;   //att_table, perm must be GATT_PROP_READ | GATT_PROP_WRITE

    hid_svc_id = gatt_add_service(&hid_profie_svc);
}

 

