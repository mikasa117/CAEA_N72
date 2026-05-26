/*
 * @Author: liuranyang liuranyang@cncaea.cn
 * @Date: 2026-02-06
 * @FilePath: \FR30xxC-SDK-v0.3.1\examples\application\btdm_audio\Src\Hmi\Rte_Hmi_Core.c
 * @Description: Rte_HMI核心模块（初始化、定时器回调、模块反初始化）
 */
#include "Hmi_Private.h"
#include "STD_BtrM.h"


/************************** 模块内共享静态变量定义 **************************/
// FreeRTOS资源句柄
TaskHandle_t xHmi_MediaInfoTaskHandle = NULL;
TaskHandle_t xHmi_CallIdTaskHandle = NULL;
TimerHandle_t xBtReconnectTimer = NULL;
TimerHandle_t xHmiCallIdTimer = NULL;
QueueHandle_t xHmiMediaInfoQueue = NULL;
QueueHandle_t xHmiCallIdQueue = NULL;

// 媒体属性与数据缓存
Hmi_MediaAttr media_attr = {NULL, NULL, NULL};
char szHmiTitle[HMI_MEDIA_INFO_MAX_LEN] = {0};
char szHmiArtist[HMI_MEDIA_INFO_MAX_LEN] = {0};
char szHmiAlbum[HMI_MEDIA_INFO_MAX_LEN] = {0};
HmiCallId_t szHmiCallId;
uint8_t gzHmiCallSta;

uint8_t media_play_sts = 0u;
uint8_t media_replay_sts = 0u;
uint8_t media_play_sts_flag = 0u;

// uint8_t xdelay_req_bt_list_current_calls_flag = 0u;

/************************** 函数定义 **************************/
/**
 * @brief  RTE HMI模块初始化（对外入口）
 * @note   创建任务、定时器，初始化核心资源
 */
void Hmi_Core_Init(void)
{
    BaseType_t xTaskCreateStatus = pdFAIL;

    // 1. 创建媒体信息处理任务
    xTaskCreateStatus = xTaskCreate(vHmi_MediaInfoTask,
                                   "Hmi_MediaInfo_Task",
                                   HMI_TASK_CONFIG_STACK_SIZE,
                                   NULL,
                                   HMI_TASK_CONFIG_PRIO,
                                   &xHmi_MediaInfoTaskHandle);
    if(xTaskCreateStatus != pdPASS)
    {
        LOG_ERR("vHmi_MediaInfoTask Create fail!");
        return;
    }

    // 2. 创建通话ID处理任务
    xTaskCreateStatus = xTaskCreate(vHmi_CallIdTask,
                                    "Hmi_CallId_Task",
                                    HMI_TASK_CONFIG_STACK_SIZE,
                                    NULL,
                                    HMI_TASK_CONFIG_PRIO,
                                    &xHmi_CallIdTaskHandle);
    if(xTaskCreateStatus != pdPASS)
    {
        LOG_ERR("vHmi_CallIdTask Create fail!");
        Hmi_ModuleDeinit();  // 回滚已创建资源
        return;
    }

    // 3. 创建蓝牙重连定时器（1秒周期）
    xBtReconnectTimer = xTimerCreate("BtReconnTimer",
                                     pdMS_TO_TICKS(1000),
                                     pdTRUE,
                                     (void *)0,
                                     xHmi_ReconnTimer);
    if(xBtReconnectTimer != NULL)
    {
        if(xTimerStart(xBtReconnectTimer, 0) != pdPASS)
        {
            LOG_ERR("vHmi_ReconnTimer start fail!");
        }
    }
    else
    {
        LOG_ERR("vHmi_CallIdTask Create fail!");
        Hmi_ModuleDeinit();
        return;
    }

    // 4. 创建通话ID 2s 定时器
    xHmiCallIdTimer = xTimerCreate("HmiCallIdTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, xHmi_CallIdTimer);
    if (xHmiCallIdTimer == NULL)
    {
        LOG_ERR("vHmi_CallIdTimer Create fail!");
        Hmi_ModuleDeinit();
        return;
    }

    LOG_INFO("Hmi Module Init Success!");
}

/**
 * @brief  蓝牙重连定时器回调
 * @note   栈初始化完成后重连最后设备，执行后安全删除定时器
 */
static void xHmi_CallIdTimer(TimerHandle_t xTimer)
{
    vHmi_CallId_Clean();
}

/**
 * @brief  蓝牙重连定时器回调
 * @note   栈初始化完成后重连最后设备，执行后安全删除定时器
 */
static void xHmi_ReconnTimer(TimerHandle_t xTimer)
{
    // static uint8_t power_on_prompt_played = 0;
    extern uint8_t user_bt_conn_last_device(void);
    if(xTimer == NULL) return;

    LOG_DEBUG("Waiting for MODE_A && VIN_OK to be met to connect...");

    BtStackState state = ME_GetStackInitState();
    if(state == BTSS_INITIALIZED)
    {
        /* 发送"蓝牙已开机"语音提示，与VIN状态无关，证明开机成功 */
        // if (!power_on_prompt_played)
        // {
        //     app_audio_tone_play(AUDIO_TYPE_SBC, sbc_sample1, sbc_sample1_get_size());
        //     power_on_prompt_played = 1;
        // }

        /* VIN校验 + 电压模式校验：只有通过后并发起自动重连 */
        uint8_t vin_ok = Rte_Hmi_Get_Vin_Cmp();
        uint8_t voltagemode;
        Rte_Read_BtrM_BtrM_VoltageMode(&voltagemode);

        if ((HMI_TRUE == vin_ok) && (STD_BTRM_MODE_A == voltagemode))
        {
            user_bt_conn_last_device();

            // 安全删除定时器
            if(xTimerDelete(xTimer, 0) == pdPASS)
            {
                xBtReconnectTimer = NULL;
                LOG_INFO("vHmi_ReconnTimer execute success, timer deleted!");
            }
        }
    }
}

/**
 * @brief  模块反初始化（内部使用）
 * @note   释放所有动态内存，删除任务/队列/定时器，防止资源泄漏
 */
static void Hmi_ModuleDeinit(void)
{
    // 1. 释放媒体属性动态内存
    HMI_SAFE_FREE(media_attr.title);
    HMI_SAFE_FREE(media_attr.artist);
    HMI_SAFE_FREE(media_attr.album);

    // 2. 删除定时器
    if(xBtReconnectTimer != NULL)
    {
        xTimerDelete(xBtReconnectTimer, portMAX_DELAY);
        xBtReconnectTimer = NULL;
    }

    // 3. 删除队列
    if(xHmiMediaInfoQueue != NULL)
    {
        vQueueDelete(xHmiMediaInfoQueue);
        xHmiMediaInfoQueue = NULL;
    }
    if(xHmiCallIdQueue != NULL)
    {
        vQueueDelete(xHmiCallIdQueue);
        xHmiCallIdQueue = NULL;
    }

    // 4. 删除任务
    if(xHmi_MediaInfoTaskHandle != NULL)
    {
        vTaskDelete(xHmi_MediaInfoTaskHandle);
        xHmi_MediaInfoTaskHandle = NULL;
    }
    if(xHmi_CallIdTaskHandle != NULL)
    {
        vTaskDelete(xHmi_CallIdTaskHandle);
        xHmi_CallIdTaskHandle = NULL;
    }

     LOG_INFO("Hmi Module Deinit Success!");
}