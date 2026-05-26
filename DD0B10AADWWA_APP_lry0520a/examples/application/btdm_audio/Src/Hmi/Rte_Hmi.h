/*
 * @Author: liuranyang liuranyang@cncaea.cn
 * @Date: 2026-01-30 14:23:40
 * @LastEditors: liuranyang liuranyang@cncaea.cn
 * @LastEditTime: 2026-05-07 10:55:34
 * @FilePath: \FR30xxC-SDK-v0.3.1\examples\application\btdm_audio\Src\Hmi\Rte_Hmi.h
 * @Description: 默认设置
 */




#ifndef __RTE_HMI_H__
#define __RTE_HMI_H__


/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Switch.h"
#include "Rte_can.h"

#define DEBUG_FALSE                                                            (0x00u)
#define DEBUG_TRUE                                                             (0x01u)
#define RTE_IF_DEBUG                                                           (DEBUG_FALSE)
//#define WL_DEBUG                                                               (DEBUG_TRUE)
//#define DV_TEST                                                                (DEBUG_TRUE)

#define HMI_CALL_DIR_NONE             0x02U
#define HMI_CALL_DIR_OUT              0x00U
#define HMI_CALL_DIR_IN               0x01U

#define HMI_CALL_STA_NONE             0x02U
#define HMI_CALL_STA_ACTIVE           0x01U
#define HMI_CALL_STA_END              0x00U

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

typedef enum
{  
    Rte_KeySts_Press = 0u,
	Rte_KeySts_ShortRelease,
	Rte_KeySts_LongPress,
	Rte_KeySts_LongRelease,
    Rte_KeySts_Stuck,
    Rte_KeySts_StuckRelease,
	Rte_KeySts_Continuous,
	Rte_KeySts_Idle,
} Rte_e_KeySts;

typedef enum
{
	Rte_SigSts_No_Press = 0u,
	Rte_SigSts_Short_Press,
	Rte_SigSts_Long_Press,
	Rte_SigSts_LongPressNotRelease,
} Rte_e_Signal_Value;

/* ----- signal in ----- */
#ifdef WL_DEBUG
#define Rte_Hmi_Get_Vin_Cmp()                              HMI_TRUE
#else
#define Rte_Hmi_Get_Vin_Cmp()                              VIN_compare()
#endif

#define Rte_Hmi_GetKeyStsFunc                              Switch_GetPressSt

/* ----- signal out ----- */
#define Rte_Hmi_Set_MMI_DownSwStatus                       RteCan_Write_MMI_DownSwStatus
#define Rte_Hmi_Set_MMI_UpSwStatus                         RteCan_Write_MMI_UpSwStatus
#define Rte_Hmi_Set_MMI_RightSwStatus                      RteCan_Write_MMI_RightSwStatus
#define Rte_Hmi_Set_MMI_LeftSwStatus                       RteCan_Write_MMI_LeftSwStatus
#define Rte_Hmi_Set_MMI_ConfirmSwStatus                    RteCan_Write_MMI_ConfirmSwStatus
#define Rte_Hmi_Set_MMI_ReturnSwStatus                     RteCan_Write_MMI_ReturnSwStatus
#define Rte_Hmi_Set_MMI_WorkMode                           RteCan_Write_MMI_WorkMode
#define Rte_Hmi_Set_MMI_Mute                               //RteCan_Write_MMI_Mute(x)
#define Rte_Hmi_Set_MMI_Tel                                //RteCan_Write_MMI_Tel(x)

#define Rte_Hmi_Set_Bt_ConnSts                             RteCan_Write_TTS_BluetoothConnect
#define Rte_Hmi_Set_Bt_Sts                                 RteCan_Write_TTS_BluetoothFunction

// 媒体信息类型（外部回调传参使用）
#define RTE_HMI_MEDIA_ATTR_TITLE          0x01U
#define RTE_HMI_MEDIA_ATTR_ARTIST         0x02U
#define RTE_HMI_MEDIA_ATTR_ALBUM          0x03U
#define RTE_HMI_MEDIA_ATTR_GENRE          0x06U

extern uint8_t bt_mediavol;
extern uint8_t media_play_sts;
extern uint8_t media_replay_sts;
extern uint8_t media_play_sts_flag;

// 队列数据读取（外部模块获取封装后的帧数据）
uint8_t Rte_Hmi_Get_TextBTData(uint8_t *data);
uint8_t Rte_Hmi_Get_TextMMData(uint8_t *data);

// 工具函数（外部可复用的编码转换）
uint16_t utf8_to_utf16_le(const char *utf8, char *utf16_le, int max_utf16_len);

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

extern void Hmi_Core_Init(void);
extern void Hmi_MediaInfo_Callback(uint8_t attr_id, const char *media_info, uint32_t info_len);
extern void Hmi_MediaPaused_Callback(void);
extern void Hmi_CallId_Callback(const char *call_id, uint32_t len, uint8_t dir, uint8_t sta);
extern void Hmi_CallSetUp_Callback(uint8_t call_set_up);
extern void Hmi_CallName_Callback(const char *call_name, uint8_t call_name_len, uint8_t is_direct);
extern void Hmi_ConnSts_Callback(uint8_t conn_sts);
extern void Hmi_Volume_Callback(uint8_t vol);
extern void Hmi_Pbap_ConnSts_Callback(uint8_t conn_sts);
extern void Hmi_Call_ReReqName_Callback(void);
extern void Hmi_RePlay_Callback(void);

extern uint8_t Rte_Hmi_Get_TextMMData(uint8_t *data);
extern uint8_t Rte_Hmi_Get_TextBTData(uint8_t *data);
#endif /* #ifndef __RTE_HMI_H__ */

/*EoF*/