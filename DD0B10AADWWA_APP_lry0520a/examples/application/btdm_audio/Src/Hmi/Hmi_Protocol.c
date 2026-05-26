/*
 * @Author: liuranyang liuranyang@cncaea.cn
 * @Date: 2026-02-06
 * @FilePath: \FR30xxC-SDK-v0.3.1\examples\application\btdm_audio\Src\Hmi\Rte_Hmi_Protocol.c
 * @Description: Rte_HMI协议模块（通用帧封装，统一处理通话/音乐帧，原核心优化逻辑）
 */
#include "Hmi_Private.h"

/**
 * @brief  通用帧封装协议（模块内核心，消除冗余）
 * @note   封装8字节帧、分包、校验和，统一处理通话ID/音乐信息帧
 * @param  frame_type: 帧类型（通话/音乐）
 * @param  sub_type: 子类型（音乐子类型/通话状态）
 * @param  data_len: 原始数据长度
 * @param  data: 原始数据缓冲区
 * @param  queue: 发送目标队列
 * @retval 0-成功，1-失败
 */
uint8_t Hmi_CommonFrameProtocol(Rte_Hmi_FrameType frame_type, uint8_t sub_type,
                                          uint8_t data_len, char *data, QueueHandle_t queue)
{
    // 入参合法性校验
    if(data == NULL || queue == NULL || data_len == 0)
    {
        LOG_ERR("Hmi_CommonFrameProtocol param invalid!");
        return 1U;
    }

    uint8_t rte_frame_seq = 0U;
    uint8_t rte_frame_data[HMI_QUEUE_FRAME_SIZE] = {0};
    uint8_t word_cnt = data_len / 2U;
    uint8_t data_pos = 0U;
    uint8_t i = 0U, len = 0U;
    uint16_t chk_sum = 0U;
    uint8_t total_cnt = (data_len > 6U) ? (data_len + 1U) : data_len; // +1为校验和

    while(data_pos < total_cnt)
    {
        memset(rte_frame_data, 0, sizeof(rte_frame_data));
        // 首帧（FF帧）
        if(0U == rte_frame_seq)
        {
            rte_frame_seq = 1U;
            // 帧头区分：通话/音乐
            if(RTE_HMI_FRAME_TYPE_CALL == frame_type)
            {
                rte_frame_data[0U] = HMI_PROTO_FRAME_TYPE_CALL | (sub_type & 0x07U);
                rte_frame_data[1U] = (user_bt_env.battery_level & 0x07U) << 5U;
                rte_frame_data[1U] |= (user_bt_env.signal_strength & 0x07U) << 2U;
                rte_frame_data[1U] |= (word_cnt >> 3U) & 0x03U;
                rte_frame_data[2U] = (word_cnt & 0x07U) << 5U;
                chk_sum += rte_frame_data[0U] + rte_frame_data[1U] + rte_frame_data[2U];
                
                // 首帧填充5字节数据
                uint8_t fill_len = (data_len - data_pos) > 5U ? 5U : (data_len - data_pos);
                for(i = 0; i < fill_len; i++)
                {
                    rte_frame_data[3U + i] = data[data_pos++];
                    chk_sum += rte_frame_data[3U + i];
                }
                // if (fill_len < 5U)
                // {
                //     rte_frame_data[3U + fill_len] = chk_sum;
                // }
            }
            else if(RTE_HMI_FRAME_TYPE_MUSIC == frame_type)
            {
                rte_frame_data[0U] = HMI_PROTO_FRAME_TYPE_MUSIC;
                rte_frame_data[1U] = (word_cnt & 0x1FU) << 3U | (sub_type & 0x03U) << 1U;
                chk_sum += rte_frame_data[0U] + rte_frame_data[1U];
                
                // 首帧填充6字节数据
                uint8_t fill_len = (data_len - data_pos) > 6U ? 6U : (data_len - data_pos);
                for(i = 0; i < fill_len; i++)
                {
                    rte_frame_data[2U + i] = data[data_pos++];
                    chk_sum += rte_frame_data[2U + i];
                }
                // if (fill_len < 6U)
                // {
                //     rte_frame_data[2U + fill_len] = chk_sum;
                // }
            }
        }
        // 后续帧（CF帧）
        else
        {
            rte_frame_data[0U] = (rte_frame_seq++ & 0x0FU) << 4U; // 多帧序号
            chk_sum += rte_frame_data[0U];

            // 填充7字节数据（剩余数据足够）
            if(data_len >= (data_pos + 7U))
            {
                for(i = 0; i < 7U; i++)
                {
                    rte_frame_data[1U + i] = data[data_pos++];
                    chk_sum += rte_frame_data[1U + i];
                }
            }
            // 剩余数据不足7字节，填充剩余数据+校验和
            else
            {
                if(data_len == data_pos)
                {
                    rte_frame_data[1U] = (uint8_t)chk_sum;
                    data_pos++;
                }
                else
                {
                    len = data_len - data_pos;
                    for(i = 0; i < len; i++)
                    {
                        rte_frame_data[1U + i] = data[data_pos++];
                        chk_sum += rte_frame_data[1U + i];
                    }
                    rte_frame_data[1U + i] = (uint8_t)chk_sum;
                    data_pos++;
                }
            }
        }

        // 发送队列（非阻塞，失败打印日志）
        if(xQueueSend(queue, rte_frame_data, 0) != pdPASS)
        {
             LOG_ERR("Hmi_CommonFrameProtocol %s frame seq %d send fail, queue full!",
                   (frame_type == RTE_HMI_FRAME_TYPE_CALL) ? "CallId" : "MusicInfo", rte_frame_seq);
        }
    }
    return 0U;
}

/**
 * @brief  UTF8转UTF16-LE（小端，对外暴露）
 * @note   处理单/双/三字节UTF8，忽略四字节，带缓冲区校验
 * @retval 转换后的字节长度
 */
uint16_t utf8_to_utf16_le(const char *utf8, char *utf16_le, int max_utf16_len)
{
    // 入参校验
    if(utf8 == NULL || utf16_le == NULL || max_utf16_len <= 0)
    {
        return 0U;
    }

    uint16_t usByteLen = 0U;
    const unsigned char *pUtf8 = (const unsigned char *)utf8;

    while(*pUtf8 != '\0' && (usByteLen + 2) <= max_utf16_len)
    {
        if(*pUtf8 < 0x80U)
        {
            // 单字节字符 (0xxxxxxx)
            utf16_le[usByteLen++] = *pUtf8;
            utf16_le[usByteLen++] = 0x00U;
            pUtf8++;
        }
        else if(*pUtf8 < 0xE0U)
        {
            // 双字节字符 (110xxxxx 10xxxxxx)
            if(*(pUtf8 + 1) == '\0') break; // 防止截断
            uint16_t usCode = (((*pUtf8 & 0x1FU) << 6) | (*(pUtf8 + 1) & 0x3FU));
            utf16_le[usByteLen++] = usCode & 0xFFU;
            utf16_le[usByteLen++] = (usCode >> 8) & 0xFFU;
            pUtf8 += 2U;
        }
        else if(*pUtf8 < 0xF0U)
        {
            // 三字节字符 (1110xxxx 10xxxxxx 10xxxxxx)
            if(*(pUtf8 + 1) == '\0' || *(pUtf8 + 2) == '\0') break; // 防止截断
            uint16_t usCode = (((*pUtf8 & 0x0FU) << 12) | ((*(pUtf8 + 1) & 0x3FU) << 6) | (*(pUtf8 + 2) & 0x3FU));
            utf16_le[usByteLen++] = usCode & 0xFFU;
            utf16_le[usByteLen++] = (usCode >> 8) & 0xFFU;
            pUtf8 += 3U;
        }
        else
        {
            // 四字节字符忽略（超出UTF16基础平面）
            pUtf8 += 4U;
        }
    }

    return usByteLen;
}