/*
 * @Author: liuranyang liuranyang@cncaea.cn
 * @Date: 2026-02-06
 * @FilePath: \FR30xxC-SDK-v0.3.1\examples\application\btdm_audio\Src\Hmi\Hmi_Tasks.c
 * @Description: Rte_HMI任务模块（媒体信息/通话ID FreeRTOS任务处理逻辑）
 */
#include "Hmi_Private.h"

#if WALTER_TMP_DEBUG
char hmicallidx = 0u;
hmicalltmp_t tmp_call_id[5u];
#endif

/**
 * @brief  通话ID处理任务
 * @note   接收通知→UTF8转UTF16→通用帧封装→发送到队列
 */
void vHmi_CallIdTask(void *pvParameters)
{
    // 创建通话ID队列（初始化校验）
    xHmiCallIdQueue = xQueueCreate(HMI_QUEUE_CALL_ID_LEN, HMI_QUEUE_FRAME_SIZE);
    if(xHmiCallIdQueue == NULL)
    {
        LOG_ERR("Hmi_CallIdTask queue create fail!");
        vTaskDelete(NULL);
        return;
    }

    char *call_utf16_ptr;
    uint16_t utf16_len = 0U;
    uint8_t i;

    while(1)
    {
        ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

        call_utf16_ptr = btdm_malloc(HMI_CALL_NAME_MAX_LEN * 2);
        if(call_utf16_ptr == NULL)
        {
            LOG_ERR("Hmi_CallIdTask malloc utf16 fail!");
            continue;
        }

        taskENTER_CRITICAL();

        if (szHmiCallId.name_len != 0)
        {
            LOG_DEBUG("call name = [%s]",szHmiCallId.name);
            utf16_len = utf8_to_utf16_le(&szHmiCallId.name[0], call_utf16_ptr, HMI_CALL_NAME_MAX_LEN * 2);   
            #if WALTER_TMP_DEBUG
            if (hmicallidx >= 5)
            {
                hmicallidx = 0u;
            }
            memcpy(tmp_call_id[hmicallidx].name, szHmiCallId.name, HMI_CALL_NAME_MAX_LEN);
            memcpy(tmp_call_id[hmicallidx].number, szHmiCallId.number, HMI_CALL_NUM_MAX_LEN);
            hmicallidx++;
            #endif
        }
        else if (szHmiCallId.number_len != 0)
        {
            #if WALTER_TMP_DEBUG
            for (i = 0u; i < 5; i++)
            {
                if(strcmp(tmp_call_id[i].number, szHmiCallId.number) == 0)
                {
                    break;
                }
            }
            
            if(i == 5)
            {
                utf16_len = utf8_to_utf16_le(&szHmiCallId.number[0], call_utf16_ptr, HMI_CALL_NAME_MAX_LEN * 2);
            }
            else
            {
                utf16_len = utf8_to_utf16_le(tmp_call_id[i].name, call_utf16_ptr, HMI_CALL_NAME_MAX_LEN * 2);
            }

            #else
            utf16_len = utf8_to_utf16_le(&szHmiCallId.number[0], call_utf16_ptr, HMI_CALL_NAME_MAX_LEN * 2);
            #endif
        }
        else {
            taskEXIT_CRITICAL();
            btdm_free(call_utf16_ptr);
            continue;
        }

        if (HMI_PROTO_CALL_ID_END == gzHmiCallSta)
        {
            memset(&szHmiCallId.number[0], 0, HMI_CALL_NUM_MAX_LEN);
            szHmiCallId.number_len = 0;
            szHmiCallId.name_len = 0;
        }

        taskEXIT_CRITICAL();
        
        if(utf16_len == 0)
        {
            LOG_ERR("Hmi_CallIdTask utf8 to utf16 fail!");
            continue;
        }

        // 通用帧封装（通话类型）
        Hmi_CommonFrameProtocol(RTE_HMI_FRAME_TYPE_CALL, gzHmiCallSta, utf16_len, call_utf16_ptr, xHmiCallIdQueue);

        if (HMI_PROTO_CALL_ID_END == gzHmiCallSta)
        {
            if(xTimerStart(xHmiCallIdTimer, 0) != pdPASS)
            {
                LOG_ERR("xHmiCallIdTimer start fail!");
            }
        }
        else 
        {
            xTimerStop(xHmiCallIdTimer, 0);
        }

        btdm_free(call_utf16_ptr);
    }
}

void vHmi_CallId_Clean(void)
{
    uint8_t rte_frame_data[HMI_QUEUE_FRAME_SIZE];

    memset(rte_frame_data, 0, HMI_QUEUE_FRAME_SIZE);
    memset(&szHmiCallId.number[0], 0, HMI_CALL_NUM_MAX_LEN);

    // 发送队列（非阻塞，失败打印日志）
    if(xQueueSend(xHmiCallIdQueue, rte_frame_data, 0) != pdPASS)
    {
        LOG_ERR("call id queue full!");
    }
}

/**
 * @brief  媒体信息处理任务
 * @note   接收通知→校验变化→UTF8转UTF16→通用帧封装→发送到队列
 */
void vHmi_MediaInfoTask(void *pvParameters)
{
    // 动态内存分配（带失败处理）
    media_attr.title = btdm_malloc(HMI_MEDIA_INFO_MAX_LEN);
    media_attr.artist = btdm_malloc(HMI_MEDIA_INFO_MAX_LEN);
    media_attr.album = btdm_malloc(HMI_MEDIA_INFO_MAX_LEN);
    if(media_attr.title == NULL || media_attr.artist == NULL || media_attr.album == NULL)
    {
        LOG_ERR("Hmi_MediaInfoTask media attr malloc fail!");
        HMI_SAFE_FREE(media_attr.title);
        HMI_SAFE_FREE(media_attr.artist);
        HMI_SAFE_FREE(media_attr.album);
        vTaskDelete(NULL);
        return;
    }

    // 创建媒体信息队列（初始化校验）
    xHmiMediaInfoQueue = xQueueCreate(HMI_QUEUE_MEDIA_INFO_LEN, HMI_QUEUE_FRAME_SIZE);
    if(xHmiMediaInfoQueue == NULL)
    {
        LOG_ERR("Hmi_MediaInfoTask queue create fail!");
        HMI_SAFE_FREE(media_attr.title);
        HMI_SAFE_FREE(media_attr.artist);
        HMI_SAFE_FREE(media_attr.album);
        vTaskDelete(NULL);
        return;
    }

    char utf16_tmp[HMI_MEDIA_INFO_MAX_LEN * RTE_HMI_UTF16_BUF_MULTIPLIER] = {0};
    uint16_t utf16_len = 0U;
    uint32_t title_len = 0U, artist_len = 0U, album_len = 0U;

    // 任务主循环（永久阻塞等待通知）
    while(1)
    {
        ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

        // 缓存字符串长度，减少重复计算
        title_len = strlen(media_attr.title);
        artist_len = strlen(media_attr.artist);
        album_len = strlen(media_attr.album);

        // 标题未变化则跳过（性能优化）
        if(strncmp(media_attr.title, szHmiTitle, title_len) == 0)
        {
            continue;
        }

#ifdef RTE_DEBUG
        LOG_INFO("Hmi_MediaInfoTask media info update:\r\n");
        LOG_INFO("  Title: %s", media_attr.title);
        LOG_INFO("  Artist: %s", media_attr.artist);
        LOG_INFO("  Album: %s", media_attr.album);
#endif

        // 安全拷贝（避免越界）
        HMI_STR_COPY(szHmiTitle, media_attr.title, sizeof(szHmiTitle));
        HMI_STR_COPY(szHmiArtist, media_attr.artist, sizeof(szHmiArtist));
        HMI_STR_COPY(szHmiAlbum, media_attr.album, sizeof(szHmiAlbum));

        // 标题帧封装
        memset(utf16_tmp, 0, sizeof(utf16_tmp));
        utf16_len = utf8_to_utf16_le(szHmiTitle, utf16_tmp, sizeof(utf16_tmp));
        if(utf16_len > 0)
        {
            Hmi_CommonFrameProtocol(RTE_HMI_FRAME_TYPE_MUSIC, HMI_PROTO_SUBTYPE_TITLE,
                                       utf16_len, utf16_tmp, xHmiMediaInfoQueue);
        }

        // 艺术家帧封装
        memset(utf16_tmp, 0, sizeof(utf16_tmp));
        utf16_len = utf8_to_utf16_le(szHmiArtist, utf16_tmp, sizeof(utf16_tmp));
        if(utf16_len > 0)
        {
            Hmi_CommonFrameProtocol(RTE_HMI_FRAME_TYPE_MUSIC, HMI_PROTO_SUBTYPE_ARTIST,
                                       utf16_len, utf16_tmp, xHmiMediaInfoQueue);
        }

        // 专辑帧封装
        memset(utf16_tmp, 0, sizeof(utf16_tmp));
        utf16_len = utf8_to_utf16_le(szHmiAlbum, utf16_tmp, sizeof(utf16_tmp));
        if(utf16_len > 0)
        {
            Hmi_CommonFrameProtocol(RTE_HMI_FRAME_TYPE_MUSIC, HMI_PROTO_SUBTYPE_ALBUM,
                                       utf16_len, utf16_tmp, xHmiMediaInfoQueue);
        }
    }
}

void vHmi_MediaInfo_Clean(void)
{
    uint8_t rte_frame_data[HMI_QUEUE_FRAME_SIZE];

    memset(szHmiTitle, 0, HMI_MEDIA_INFO_MAX_LEN);
    memset(media_attr.title, 0, HMI_MEDIA_INFO_MAX_LEN);

    memset(rte_frame_data, 0, HMI_QUEUE_FRAME_SIZE);

    // 发送队列（非阻塞，失败打印日志）
    if(xQueueSend(xHmiMediaInfoQueue, rte_frame_data, 0) != pdPASS)
    {
        LOG_ERR("call id queue full!");
    }
}