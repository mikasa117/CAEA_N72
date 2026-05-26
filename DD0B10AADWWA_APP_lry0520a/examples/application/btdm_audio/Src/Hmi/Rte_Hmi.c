/*
 * @Author: liuranyang liuranyang@cncaea.cn
 * @Date: 2026-01-31 15:51:08
 * @LastEditors: liuranyang liuranyang@cncaea.cn
 * @LastEditTime: 2026-02-06 14:47:04
 * @FilePath: \FR30xxC-SDK-v0.3.1\examples\application\btdm_audio\Src\Hmi\Rte_Hmi.c
 * @Description: 默认设置
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Hmi_Private.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* ========================================================================== */
/*                        Application Local Functions                         */
/* ========================================================================== */

/**
 * @brief  获取通话ID数据（从队列读取）
 * @note   非阻塞读取，返回1表示有数据，0表示无数据
 * @param  data: 输出数据缓冲区（需至少8字节）
 * @retval 1-成功读取，0-无数据/失败
 */
uint8_t Rte_Hmi_Get_TextBTData(uint8_t *data)
{
    /* 入参校验 */
    if(data == NULL || xHmiCallIdQueue == NULL)
        return 0u;

    uint8_t recv_frame[HMI_QUEUE_FRAME_SIZE] = {0};
    if(xQueueReceive(xHmiCallIdQueue, recv_frame, 0) == pdPASS)
    {
        memcpy(data, recv_frame, HMI_QUEUE_FRAME_SIZE);
        return 1u;
    }

    return 0u;
}

/**
 * @brief  获取歌曲信息（从队列读取）
 * @note   非阻塞读取，返回1表示有数据，0表示无数据
 * @param  data: 输出数据缓冲区（需至少8字节）
 * @retval 1-成功读取，0-无数据/失败
 */
uint8_t Rte_Hmi_Get_TextMMData(uint8_t *data)
{
    /* 入参校验 */
    if(data == NULL || xHmiMediaInfoQueue == NULL)
        return 0u;

    uint8_t recv_frame[HMI_QUEUE_FRAME_SIZE] = {0};
    if(xQueueReceive(xHmiMediaInfoQueue, recv_frame, 0) == pdPASS)
    {
        memcpy(data, recv_frame, HMI_QUEUE_FRAME_SIZE);
        return 1u;
    }

    return 0u;
}

#ifdef RTE_DEBUG
/**
 * @description: vRte_Hmi_DebugTask
 * @param {void} *pvParameters
 * @return {*}
 */
static void vRte_Hmi_DebugTask(void *pvParameters)
{
    uint8_t data[8u] = {0};
    while(1)
    {
        if (1u == Rte_Hmi_Get_TextMMData(&data[0u]))
        {
            for (uint8_t i = 0u; i < 8u; i++)
            {
                printf("0x%02X ", data[i]);
            }
            printf("\r\n");
        }

        vTaskDelay(pdMS_TO_TICKS(20u));
    }
}
#endif