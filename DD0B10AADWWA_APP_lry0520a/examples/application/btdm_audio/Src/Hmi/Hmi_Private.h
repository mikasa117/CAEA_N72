/*
 * @Author: liuranyang liuranyang@cncaea.cn
 * @Date: 2026-02-06
 * @FilePath: \FR30xxC-SDK-v0.3.1\examples\application\btdm_audio\Src\Hmi\Hmi_Private.h
 * @Description: HMI私有头文件（仅模块内使用，对外隐藏所有内部细节）
 */
#ifndef __HMI_PRIVATE_H__
#define __HMI_PRIVATE_H__

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Rte_Hmi.h"
#include "btdm_mem.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"
#include <string.h>
#include <stdio.h>
#include "me_api.h"
#include "app_audio.h"
#include "sbc_sample.h"
#include "user_bt.h"
#include "app_bt.h"
#include "CanApp.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
// 定义打印级别
#define LOG_LEVEL_ERROR   1
#define LOG_LEVEL_WARN    2
#define LOG_LEVEL_INFO    3
#define LOG_LEVEL_DEBUG   4

#define CURRENT_LOG_LEVEL LOG_LEVEL_DEBUG

#if CURRENT_LOG_LEVEL >= LOG_LEVEL_ERROR
#define LOG_ERR(fmt, ...)    printf("[ERROR] " fmt "\r\n", ##__VA_ARGS__)
#else
#define LOG_ERR(fmt, ...)    do {} while(0)
#endif

#if CURRENT_LOG_LEVEL >= LOG_LEVEL_WARN
#define LOG_WARN(fmt, ...)   printf("[WARN]  " fmt "\r\n", ##__VA_ARGS__)
#else
#define LOG_WARN(fmt, ...)   do {} while(0)
#endif

#if CURRENT_LOG_LEVEL >= LOG_LEVEL_INFO
#define LOG_INFO(fmt, ...)   printf("[INFO]  " fmt "\r\n", ##__VA_ARGS__)
#else
#define LOG_INFO(fmt, ...)   do {} while(0)
#endif

#if CURRENT_LOG_LEVEL >= LOG_LEVEL_DEBUG
#define LOG_DEBUG(fmt, ...)  printf("[DEBUG] " fmt "\r\n", ##__VA_ARGS__)
#else
#define LOG_DEBUG(fmt, ...)  do {} while(0)
#endif

#define HMI_FALSE                     (0u)
#define HMI_TRUE                      (1u)
#define HMI_STATE_UNKNOWN             (0xFFu)

// 任务配置
#define HMI_TASK_CONFIG_PRIO          3U
#define HMI_TASK_CONFIG_STACK_SIZE    1024U

// 队列配置
#define HMI_QUEUE_MEDIA_INFO_LEN      20U
#define HMI_QUEUE_CALL_ID_LEN         5U
#define HMI_QUEUE_FRAME_SIZE          8U

// 协议帧类型
#define HMI_PROTO_FRAME_TYPE_CALL     0x08U
#define HMI_PROTO_FRAME_TYPE_MUSIC    0x05U
#define HMI_PROTO_CALL_STS_ACTIVE     0x01U

#define HMI_PROTO_CALL_ID_IDLE        0x00U /* --- 空闲状态 --- */
#define HMI_PROTO_CALL_ID_IN_ING      0x01U /* --- 来电中 --- */
#define HMI_PROTO_CALL_ID_ACTIVE      0x02U /* --- 通话中 --- */
#define HMI_PROTO_CALL_ID_OUT_ING     0x03U /* --- 拨打中 --- */
#define HMI_PROTO_CALL_ID_END         0x04U /* --- 通话结束 --- */
#define HMI_PROTO_CALL_ID_WAITING     0x05U /* --- 等待中 --- */

// 媒体协议子类型
#define HMI_PROTO_SUBTYPE_TITLE       0x00U
#define HMI_PROTO_SUBTYPE_ARTIST      0x01U
#define HMI_PROTO_SUBTYPE_ALBUM       0x02U

// 长度限制
#define HMI_MEDIA_INFO_MAX_LEN        0x80U
#define HMI_CALL_NAME_MAX_LEN         0x50U
#define HMI_CALL_NUM_MAX_LEN          0x0FU
#define RTE_HMI_UTF16_BUF_MULTIPLIER  2U

/* 音量相关常量 */
#define Hmi_Volume_Default                                 (10u)
#define Hmi_Volume_Min                                     (0u)
#define Hmi_Volume_Max                                     (15u)
#define Hmi_Mute_On                                        (1u)
#define Hmi_Mute_Off                                       (0u)

#define HMI_SAFE_FREE(ptr) do { if((ptr) != NULL) { btdm_free(ptr); (ptr) = NULL; } } while(0)
#define HMI_STR_COPY(dst, src, max_len) do { \
    if((dst) != NULL && (src) != NULL && (max_len) > 0) { \
        strncpy((dst), (src), (max_len) - 1); \
        (dst)[(max_len) - 1] = '\0'; \
    } \
} while(0)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
// 帧类型枚举
typedef enum {
    RTE_HMI_FRAME_TYPE_CALL = 0,
    RTE_HMI_FRAME_TYPE_MUSIC
} Rte_Hmi_FrameType;

// 媒体属性结构体
typedef struct {
    char* title;
    char* artist;
    char* album;
} Hmi_MediaAttr;

typedef struct{
    char name[HMI_CALL_NAME_MAX_LEN];
    char number[HMI_CALL_NUM_MAX_LEN];
    uint8_t name_len;
    uint8_t number_len;
} HmiCallId_t;

#define WALTER_TMP_DEBUG  1u

#if WALTER_TMP_DEBUG
typedef struct{
    char name[HMI_CALL_NAME_MAX_LEN];
    char number[HMI_CALL_NUM_MAX_LEN];
    char is_vaild;
} hmicalltmp_t;

#endif


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

// FreeRTOS资源句柄
extern TaskHandle_t xHmi_MediaInfoTaskHandle;
extern TaskHandle_t xHmi_CallIdTaskHandle;
extern TimerHandle_t xBtReconnectTimer;
extern QueueHandle_t xHmiMediaInfoQueue;
extern QueueHandle_t xHmiCallIdQueue;
// 媒体属性核心变量
extern Hmi_MediaAttr media_attr;

extern uint8_t bt_mediavol;

// 数据缓存缓冲区
extern char szHmiTitle[HMI_MEDIA_INFO_MAX_LEN];
extern char szHmiArtist[HMI_MEDIA_INFO_MAX_LEN];
extern char szHmiAlbum[HMI_MEDIA_INFO_MAX_LEN];
extern HmiCallId_t szHmiCallId;
extern uint8_t gzHmiCallSta;
extern uint8_t flag_sync;

extern TimerHandle_t xHmiCallIdTimer;

/************************** 模块内内部函数声明 **************************/
// 核心模块：定时器回调、反初始化
static void xHmi_ReconnTimer(TimerHandle_t xTimer);
static void xHmi_CallIdTimer(TimerHandle_t xTimer);
static void Hmi_ModuleDeinit(void);

// 协议模块：通用帧封装
uint8_t Hmi_CommonFrameProtocol(Rte_Hmi_FrameType frame_type, uint8_t sub_type,
                                          uint8_t data_len, char *data, QueueHandle_t queue);

// 任务模块：FreeRTOS任务函数
void vHmi_MediaInfoTask(void *pvParameters);
void vHmi_CallIdTask(void *pvParameters);

void vHmi_CallId_Clean(void);
void vHmi_MediaInfo_Clean(void);

// 回调模块：媒体信息提取
void Hmi_MediaInfo_Extract(void);

#endif /* #ifndef __HMI_PRIVATE_H__ */

/*EoF*/