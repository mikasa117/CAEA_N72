/*
 * @Author: liuranyang liuranyang@cncaea.cn
 * @Date: 2026-02-06
 * @FilePath: \FR30xxC-SDK-v0.3.1\examples\application\btdm_audio\Src\Hmi\Hmi_Callback.c
 * @Description: HMI回调模块（外部回调处理、媒体信息拆分提取）
 */

#include "Hmi_Private.h"


#if 0
void Hmi_MediaInfo_Extract(void)
{
    // 空指针/空字符串校验
    if(media_attr.artist == NULL || *media_attr.artist == '\0')
    {
        return;
    }

    // 分隔符查找（英文横杠/中文破折号UTF8编码：0xE28094）
    const char* sep_en = strrchr(media_attr.artist, '-');
    const char* sep_cn = strrchr(media_attr.artist, 0xE28094);
    const char* final_sep = NULL;
    const char* test_ptr = NULL;
    int title_len = 0;

    // 确定最终分隔符（取位置更靠后的）
    if(sep_en != NULL && sep_cn != NULL)
    {
        final_sep = (sep_en > sep_cn) ? sep_en : sep_cn;
        printf("both final_sep: %s\r\n", final_sep);
    }
    else if(sep_en != NULL)
    {
        final_sep = sep_en;
        title_len = final_sep - media_attr.artist;
        test_ptr = final_sep;
        while('\0' != *test_ptr)
            printf("en final_sep: %x", *test_ptr++);
        printf("\r\nen final_sep: %s, title_len: %d\r\n", final_sep, title_len);
    }
    else if(sep_cn != NULL)
    {
        final_sep = sep_cn;
        title_len = final_sep - media_attr.artist - 3; // 中文破折号占3字节
        test_ptr = final_sep;
        while('\0' != *test_ptr)
            printf("cn final_sep: %x", *test_ptr++);
        printf("\r\ncn final_sep: %s, title_len: %d\r\n", final_sep, title_len);
    }
    else
    {
        printf("no sep found\r\n");
        return;
    }

    // 提取标题（去除末尾空格/制表符）
    if(title_len > 0 && title_len < HMI_MEDIA_INFO_MAX_LEN)
    {
        strncpy(media_attr.title, media_attr.artist, title_len);
        media_attr.title[title_len] = '\0';

        char* title_end = media_attr.title + strlen(media_attr.title) - 1;
        while(title_end >= media_attr.title && (*title_end == ' ' || *title_end == '\t'))
        {
            *title_end-- = '\0';
        }
    }

    // 提取歌手（去除开头空格/制表符）
    const char* singer_start = final_sep + 1;
    while(*singer_start != '\0' && (*singer_start == ' ' || *singer_start == '\t'))
    {
        singer_start++;
    }
    HMI_STR_COPY(media_attr.artist, singer_start, HMI_MEDIA_INFO_MAX_LEN);

    // 兜底默认值
    if(strlen(media_attr.title) == 0)
    {
        HMI_STR_COPY(media_attr.title, "未知歌曲", HMI_MEDIA_INFO_MAX_LEN);
    }
    if(strlen(media_attr.artist) == 0)
    {
        HMI_STR_COPY(media_attr.artist, "未知歌手", HMI_MEDIA_INFO_MAX_LEN);
    }
}
#else
void Hmi_MediaInfo_Extract(void)
{
    char *singer = NULL;
    char *songtitle = NULL;

    if(media_attr.artist == NULL || *media_attr.artist == '\0')
    {
        return;
    }

    char *split_pos = NULL;
    if ((split_pos = strstr(media_attr.artist, "—")) != NULL) 
    {
        /* ----- 先找苹果全角 "—" ----- */
        *split_pos = '\0'; /* 截断分隔符位置 */
        songtitle = media_attr.artist; /* 从开始位置赋值给歌曲名 */
        singer = split_pos + strlen("—"); /* 从分隔符位置 + "—"开始赋值给歌手 */
    } 
    else if ((split_pos = strstr(media_attr.artist, "-")) != NULL) 
    {
        /* ----- 再找安卓半角 '-' ----- */
        *split_pos = '\0'; /* 截断分隔符位置 */
        songtitle = media_attr.artist; /* 从开始位置赋值给歌曲名 */
        singer = split_pos + strlen("-"); /* 从分隔符位置 + "-" 开始赋值给歌手 */
    }
    else
    {
        return;
    }

    if (songtitle)
    {
        strcpy(media_attr.title, songtitle);
        /* ----- 去除歌曲名末尾空格/制表符 ----- */
        char* title_end = media_attr.title + strlen(media_attr.title) - 1;
        while(title_end >= media_attr.title && (*title_end == ' ' || *title_end == '\t'))
        {
            *title_end-- = '\0';
        }
    }
    if (singer)
    {
        /* ----- 去除歌手开头空格/制表符 ----- */
        const char* singer_start = singer;
        while(*singer_start != '\0' && (*singer_start == ' ' || *singer_start == '\t'))
        {
            singer_start++;
        }
        strcpy(media_attr.artist, singer_start);
    }

    /* ----- 兜底默认值 ----- */
    if(strlen(media_attr.title) == 0)
    {
        HMI_STR_COPY(media_attr.title, "未知歌曲", HMI_MEDIA_INFO_MAX_LEN);
    }
    if(strlen(media_attr.artist) == 0)
    {
        HMI_STR_COPY(media_attr.artist, "未知歌手", HMI_MEDIA_INFO_MAX_LEN);
    }
}
#endif

/**
 * @brief  媒体信息回调函数（外部调用）
 * @note   接收媒体信息，完整接收后触发处理任务
 */
void Hmi_MediaInfo_Callback(uint8_t attr_id, const char *media_info, uint32_t info_len)
{
    static uint8_t media_info_received = 0x00U;

    // 入参校验
    if(info_len >= HMI_MEDIA_INFO_MAX_LEN)
    {
        LOG_ERR("Hmi_MediaInfo_Callback Invalid parameter");
        return;
    }

    // 按类型存储信息
    switch(attr_id)
    {
        case RTE_HMI_MEDIA_ATTR_TITLE:
            HMI_STR_COPY(media_attr.title, media_info, info_len + 1);
            media_info_received |= (0x01 << RTE_HMI_MEDIA_ATTR_TITLE);
            break;
        case RTE_HMI_MEDIA_ATTR_ARTIST:
            HMI_STR_COPY(media_attr.artist, media_info, info_len + 1);
            media_info_received |= (0x01 << RTE_HMI_MEDIA_ATTR_ARTIST);
            break;
        case RTE_HMI_MEDIA_ATTR_ALBUM:
            HMI_STR_COPY(media_attr.album, media_info, info_len + 1);
            media_info_received |= (0x01 << RTE_HMI_MEDIA_ATTR_ALBUM);
            break;
        default:
            break;
    }

    // 标题/艺术家/专辑都接收完成后，触发处理任务
    if((media_info_received & 0x0EU) == 0x0EU)
    {
        media_info_received = 0x00U;
        Hmi_MediaInfo_Extract();
        if(xHmi_MediaInfoTaskHandle != NULL)
        {
            xTaskNotifyGive(xHmi_MediaInfoTaskHandle);
        }
    }
}

/**
 * @brief  媒体暂停回调函数
 * @note   接收媒体媒体暂停事件
 */
void Hmi_MediaPaused_Callback(void)
{
    vHmi_MediaInfo_Clean();
}

/**
 * @brief  查询到的姓名回调函数
 * @note   
 */
void Hmi_CallName_Callback(const char *call_name, uint8_t call_name_len, uint8_t is_direct)
{
    /* --- 接通和挂断触发直接访问操作 --- */
    if(!is_direct)
    {
        uint8_t ucNameLen = (call_name_len > HMI_CALL_NAME_MAX_LEN) ? (HMI_CALL_NAME_MAX_LEN) : (call_name_len);

        taskENTER_CRITICAL();
        if (NULL != call_name)
        {
            memset(&szHmiCallId.name[0], '\0', HMI_CALL_NAME_MAX_LEN);
            strncpy(&szHmiCallId.name[0], (call_name), ucNameLen);
            szHmiCallId.name_len = ucNameLen;
            taskEXIT_CRITICAL();
        }
        else
        {
            szHmiCallId.name_len = 0u;
            taskEXIT_CRITICAL();
        }
    }

    if(xHmi_CallIdTaskHandle != NULL)
    {
        xTaskNotifyGive(xHmi_CallIdTaskHandle);
    }
}

/**
 * @brief  通话ID回调函数（外部调用）
 * @note   提取数字+号，内容变化时触发处理任务
 */
void Hmi_CallId_Callback(const char *call_id, uint32_t len, uint8_t dir, uint8_t sta)
{
    char szNumber[HMI_CALL_NUM_MAX_LEN] = {'\0'};
    uint8_t ucNumberLen = 0U;
    char c = '\0';
    uint8_t i, idx = 0u;
    uint8_t call_sta = HMI_PROTO_CALL_ID_IDLE;

    if (HMI_CALL_DIR_NONE > dir)
    {
        switch (gzHmiCallSta)
        {
            case HMI_PROTO_CALL_ID_IDLE:
            case HMI_PROTO_CALL_ID_IN_ING:
            case HMI_PROTO_CALL_ID_OUT_ING:
            case HMI_PROTO_CALL_ID_END:
                if (sta == HMI_CALL_STA_ACTIVE)
                {
                    gzHmiCallSta = HMI_PROTO_CALL_ID_ACTIVE;
                }
                else{
                    call_sta = (HMI_CALL_DIR_IN == dir) ? (HMI_PROTO_CALL_ID_IN_ING) : (HMI_PROTO_CALL_ID_OUT_ING);
                    gzHmiCallSta = call_sta;
                }
                break;
            case HMI_PROTO_CALL_ID_ACTIVE:
                break;
            default:
                break;
        }

        ucNumberLen = (len > HMI_CALL_NUM_MAX_LEN) ? (HMI_CALL_NUM_MAX_LEN) : (len);
        for (i = 0u; i < ucNumberLen; i++)
        {
            c = call_id[i];
            if((c >= '0' && c <= '9') || c == '+')
            {
                szNumber[idx++] = c;
            }
        }

        taskENTER_CRITICAL();

        if(strncmp(&szHmiCallId.number[0], szNumber, idx) != 0)
        {
            HMI_STR_COPY(&szHmiCallId.number[0], szNumber, HMI_CALL_NUM_MAX_LEN);

            taskEXIT_CRITICAL();

            szHmiCallId.number_len = idx;

            /* --- PBAP已连接 => 查询通讯录姓名；否则直接用号码显示 --- */
            if (user_bt_env.dev[user_bt_env.last_active_index].conFlags & LINK_STATUS_PBAP_CONNECTED)
            {
                BtStatus status;
                PbapPullVcardListingParms parms;

                uint8_t folder[] = "telecom/pb";
                parms.folderName = folder;
                parms.order = VCARD_SORT_ORDER_ALPHA;
                parms.listStartOffset = 0x00;
                parms.maxListCount = 1;
                parms.searchAttribute = VCARD_SEARCH_ATTRIB_NUMBER;
                parms.searchValue = (char *)szNumber;
                status = PBAP_PullVcardListing(&pbap_client[0], &parms);
                LOG_DEBUG("PBAP_PullVcardListing status = %d\r\n",status);
            }
            else
            {
                /* PBAP未连接（用户未授权通讯录），直接用号码显示 */
                Hmi_CallName_Callback(NULL, 0, FALSE);
            }
        }
        else
        {
            taskEXIT_CRITICAL();
        }
    }
    else if (HMI_CALL_STA_NONE > sta)
    {
        switch (gzHmiCallSta)
        {
            case HMI_PROTO_CALL_ID_IN_ING:
            case HMI_PROTO_CALL_ID_OUT_ING:
            case HMI_PROTO_CALL_ID_ACTIVE:
                call_sta = (HMI_CALL_STA_ACTIVE == sta) ? (HMI_PROTO_CALL_ID_ACTIVE) : (HMI_PROTO_CALL_ID_END);
                if (gzHmiCallSta != call_sta)
                {
                    gzHmiCallSta = call_sta;
                    Hmi_CallName_Callback(NULL, 0, TRUE);
                }
                break;
            case HMI_PROTO_CALL_ID_IDLE:
            case HMI_PROTO_CALL_ID_END:
                break;
            default:
                break;
        }
    }
    else {}
}

/**
 * @brief  通话状态回调函数
 * @note   有电话请求时连接PBAP协议
 */
void Hmi_CallSetUp_Callback(uint8_t call_set_up)
{
    BtStatus status;
    static uint8_t pbap_sts = 0x00U;

    LOG_DEBUG("----> call_set_up = %d",call_set_up);

    if (HF_CALL_SETUP_NONE == call_set_up)
    {
        /* --- 这里来电和去电状态，未接通情况下挂断，不会触发active流程的挂断，此处怎加挂断判定 --- */
        if (HF_CALL_ACTIVE != user_bt_env.dev[user_bt_env.last_active_index].active)
        {
            Hmi_CallId_Callback(NULL, 0, HMI_CALL_DIR_NONE, HMI_CALL_STA_END);
        }
    }
    //else
    {
        status = bt_list_current_calls(user_bt_env.last_active_index);
        LOG_DEBUG("status = %d\r\n",status);
    }
}

void Hmi_RePlay_Callback(void)
{
    media_play_sts_flag = 1u;
    if (1u == media_play_sts)
    {
        LOG_DEBUG(">>>>>>>> Hmi_RePlay_Callback");
        //AVRCP_SetPanelKey(user_bt_env.dev[user_bt_env.last_active_index].rcp_chan, AVRCP_POP_PLAY, TRUE);
        media_replay_sts = 1u;
    }
}

/**
 * @brief  连接状态回调函数（外部调用）
 * @note   打印连接状态，便于调试，可扩展后续逻辑
 */
void Hmi_ConnSts_Callback(uint8_t conn_sts)
{
    LOG_INFO("蓝牙连接状态: %d", conn_sts);
}

void Hmi_Volume_Callback(uint8_t vol)
{
    if (Hmi_Volume_Max >= vol)
    {
        bt_mediavol = vol;
        flag_sync = 0;
    }
}