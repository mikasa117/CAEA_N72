/*
 * @Author: liuranyang liuranyang@cncaea.cn
 * @Date: 2026-01-29 16:33:04
 * @LastEditors: liuranyang liuranyang@cncaea.cn
 * @LastEditTime: 2026-04-29 16:31:58
 * @FilePath: \FR30xxC-SDK-v0.3.1\examples\application\btdm_audio\Src\Hmi\Hmi.c
 * @Description: 默认设置
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Hmi_Private.h"
#include "STD_BtrM.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* VIN验证状态定义 */
#define Hmi_Vin_Verf_Succ                                  (0x01u)
#define Hmi_Vin_Verf_Fail                                  (0x00u)

/* 蓝牙连接状态定义 */
#define Hmi_Bt_Status_Disconnected                         (0x00u)
#define Hmi_Bt_Status_Connected                            (0x01u)

/* 蓝牙功能状态定义 */
#define Hmi_Bt_Func_Enable                                 (0x00u)
#define Hmi_Bt_Func_Disable                                (0x01u)

/* 方控工作模式定义 */
#define Hmi_WorkMode_BTM                                   (0x00u)
#define Hmi_WorkMode_IPK                                   (0x01u)

/* 按键处理通用参数结构体 */
typedef struct
{
    void (*SetSwStatusFunc)(uint32_t);            /* 设置按键状态函数 */
    void (*ShortReleaseCallback)(void);           /* 短按释放回调 */
    void (*LongPressCallback)(void);              /* 长按回调 */
    TeSwitch_e_KEY key_id;
} KeyProcessParam_t;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static void Hmi_CommonKeyProcess(const KeyProcessParam_t *pParam);
static void Hmi_DownKeyShortReleaseCallback(void);
static void Hmi_UpKeyShortReleaseCallback(void);
static void Hmi_RightKeyShortReleaseCallback(void);
static void Hmi_LeftKeyShortReleaseCallback(void);
static void Hmi_MuteKeyShortReleaseCallback(void);
static void Hmi_TelKeyLongPressCallback(void);
static void Hmi_TelKeyShortReleaseCallback(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static uint8_t bt_state;
uint8_t bt_mediavol;
uint8_t flag_sync = 1;
static uint8_t bt_mute_sts;
static uint8_t last_bt_state;
static uint8_t swc_work_mode;

static uint16_t swc_work_mode_timer;


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
extern struct user_bt_env_t user_bt_env;
/* ========================================================================== */
/*                        Application Local Functions                         */
/* ========================================================================== */

/**
 * @description: HMI应用初始化
 * @return {void}
 */
void Hmi_Init(void)
{
    /* 初始化蓝牙相关状态 */
    bt_state = BT_STATE_IDLE;
    bt_mediavol = Hmi_Volume_Default;
    bt_mute_sts = Hmi_Mute_On;
    last_bt_state = BT_STATE_IDLE;
    swc_work_mode = Hmi_WorkMode_BTM;

    Hmi_Core_Init();
    Rte_Hmi_Set_Bt_Sts(0x01);
}

/**
 * @description: 通用按键处理函数（消除重复逻辑）
 * @param {const KeyProcessParam_t*} pParam - 按键处理参数
 * @return {void}
 */
static void Hmi_CommonKeyProcess(const KeyProcessParam_t *pParam)
{
    /* 参数合法性检查 */
    if (NULL == pParam)
    {
        return;
    }

    Rte_e_KeySts ePressSt = (Rte_e_KeySts)Rte_Hmi_GetKeyStsFunc(pParam->key_id);

    if ((Hmi_WorkMode_IPK == swc_work_mode) && (Rte_KeySts_Idle != ePressSt))
    {
        swc_work_mode_timer = 0u;
    }

    switch (ePressSt)
    {
        case Rte_KeySts_Press:
            if (NULL != pParam->SetSwStatusFunc)
                pParam->SetSwStatusFunc(Rte_SigSts_Short_Press);
            LOG_DEBUG("Hmi_CommonKeyProcess: key_id = %d, KeySts_Press", pParam->key_id);
            break;

        case Rte_KeySts_Continuous:
            /* 长按持续触发时，优先执行长按回调 */
            if ((NULL != pParam->LongPressCallback) && (Hmi_WorkMode_BTM == swc_work_mode))
            {
                pParam->LongPressCallback();
            }
            /* 无break，继续执行LongPress逻辑 */
        case Rte_KeySts_LongPress:
            if (NULL != pParam->SetSwStatusFunc)
                pParam->SetSwStatusFunc(Rte_SigSts_Long_Press);
            LOG_DEBUG("Hmi_CommonKeyProcess: key_id = %d, KeySts_LongPress", pParam->key_id);
            break;

        case Rte_KeySts_Stuck:
            if (NULL != pParam->SetSwStatusFunc)
                pParam->SetSwStatusFunc(Rte_SigSts_LongPressNotRelease);
            LOG_DEBUG("Hmi_CommonKeyProcess: key_id = %d, KeySts_Stuck", pParam->key_id);
            break;

        case Rte_KeySts_ShortRelease:
            /* 短按释放时，执行自定义回调 */
            if (NULL != pParam->ShortReleaseCallback)
            {
                if (Hmi_WorkMode_BTM == swc_work_mode)
                {
                    pParam->ShortReleaseCallback();
                }
                else
                {
                    if (KEY2_WorkMode == pParam->key_id)
                        pParam->ShortReleaseCallback();
                }
            }
            /* 无break，继续执行释放后状态重置 */
        case Rte_KeySts_LongRelease:
        case Rte_KeySts_StuckRelease:
            if (NULL != pParam->SetSwStatusFunc)
                pParam->SetSwStatusFunc(Rte_SigSts_No_Press);
            LOG_DEBUG("Hmi_CommonKeyProcess: key_id = %d, KeySts_Release", pParam->key_id);
            break;

        case Rte_KeySts_Idle:
        default:
            break;
    }
}

/**
 * @description: 音量减按键（Down）短按释放回调
 * @return {void}
 */
static void Hmi_DownKeyShortReleaseCallback(void)
{
// ===================== 修复：静音状态下短按音量-，优先解除静音 =====================
    if (bt_mute_sts == Hmi_Mute_On)
    {
        bt_mute_sts = Hmi_Mute_Off;
        return;
    }
    if (bt_mediavol > Hmi_Volume_Min)
    {
        bt_mediavol--;
        flag_sync = 1;
    }
}

/**
 * @description: 音量减按键（Down）长按回调
 * @return {void}
 */
static void Hmi_DownKeyLongPressCallback(void)
{
// ===================== 修复：静音状态下长按音量-，优先解除静音 =====================
    if (bt_mute_sts == Hmi_Mute_On)
    {
        bt_mute_sts = Hmi_Mute_Off;
        return;
    }
    if (bt_mediavol > Hmi_Volume_Min)
    {
        bt_mediavol--;
        flag_sync = 1;
    }
}

/**
 * @description: 音量加按键（Up）短按释放回调
 * @return {void}
 */
static void Hmi_UpKeyShortReleaseCallback(void)
{
// ===================== 修复：静音状态下短按音量+，优先解除静音 =====================
    if (bt_mute_sts == Hmi_Mute_On)
    {
        bt_mute_sts = Hmi_Mute_Off;
        return;
    }
    if (bt_mediavol < Hmi_Volume_Max)
    {
        bt_mediavol++;
        flag_sync = 1;
    }
}

/**
 * @description: 音量加按键（Up）长按回调
 * @return {void}
 */
static void Hmi_UpKeyLongPressCallback(void)
{
// ===================== 修复：静音状态下长按音量+，优先解除静音 =====================
    if (bt_mute_sts == Hmi_Mute_On)
    {
        bt_mute_sts = Hmi_Mute_Off;
        return;
    }
    if (bt_mediavol < Hmi_Volume_Max)
    {
        bt_mediavol++;
        flag_sync = 1;
    }
}

/**
 * @description: 右按键（Right）短按释放回调
 * @return {void}
 */
static void Hmi_RightKeyShortReleaseCallback(void)
{
    /* 仅在蓝牙媒体播放状态下执行下一曲操作 */
    if (BT_STATE_MEDIA_PLAYING == bt_state)
    {
        /* --- bug修复 walter 0311 --- */
        // BtStatus status = AVRCP_SetPanelKey(user_bt_env.dev[user_bt_env.last_active_index].rcp_chan, AVRCP_POP_BACKWARD, TRUE);
        BtStatus status = AVRCP_SetPanelKey(user_bt_env.dev[user_bt_env.last_active_index].rcp_chan, AVRCP_POP_FORWARD, TRUE);
        LOG_INFO("AVRCP status = %d", status);
    }
}

/**
 * @description: 左按键（Left）短按释放回调
 * @return {void}
 */
static void Hmi_LeftKeyShortReleaseCallback(void)
{
    /* 仅在蓝牙媒体播放状态下执行上一曲操作 */
    if (BT_STATE_MEDIA_PLAYING == bt_state)
    {
        /* --- bug修复 walter 0311 --- */
        // BtStatus status = AVRCP_SetPanelKey(user_bt_env.dev[user_bt_env.last_active_index].rcp_chan, AVRCP_POP_FORWARD, TRUE);
        BtStatus status = AVRCP_SetPanelKey(user_bt_env.dev[user_bt_env.last_active_index].rcp_chan, AVRCP_POP_BACKWARD, TRUE);
        LOG_INFO("AVRCP status = %d", status);
    }
}

/**
 * @description: 静音按键（Mute）短按释放回调
 * @return {void}
 */
static void Hmi_MuteKeyShortReleaseCallback(void)
{
    /* 切换静音状态（简化条件判断） */
    bt_mute_sts = (Hmi_Mute_On == bt_mute_sts) ? Hmi_Mute_Off : Hmi_Mute_On;
}

/**
 * @description: 电话按键（Tel）长按回调
 * @return {void}
 */
static void Hmi_TelKeyLongPressCallback(void)
{
    LOG_DEBUG("Hmi_TelKeyLongPressCallback\r\n");
    /* 通话状态下执行挂断操作 */
    if ((BT_STATE_HFP_INCOMMING == bt_state) || (BT_STATE_HFP_OUTGOING == bt_state) || (BT_STATE_HFP_CALLACTIVE == bt_state))
    {
        BtStatus status = bt_hang_up(user_bt_env.last_active_index);
        LOG_INFO("Call status = %d\r\n", status);
    }
}

/**
 * @description: 电话按键（Tel）短按释放回调
 * @return {void}
 */
static void Hmi_TelKeyShortReleaseCallback(void)
{
    BtStatus status;
    LOG_DEBUG("Hmi_TelKeyShortReleaseCallback bt_state = %d\r\n", bt_state);
    switch (bt_state)
    {
        case BT_STATE_CONNECTED:
            LOG_DEBUG("Hmi_TelKeyShortReleaseCallback last_active_index = %d\r\n", user_bt_env.last_active_index);
        case BT_STATE_MEDIA_PLAYING:
            /* <已连接/播放> 状态下重拨 */
            if (user_bt_env.dev[user_bt_env.last_active_index].conFlags & LINK_STATUS_PBAP_CONNECTED)
            {
                uint8_t cmd_buffer[3] = {'F','M','0'};
                struct app_task_event *event;
                event = app_task_event_alloc(APP_TASK_EVENT_AT_CMD, sizeof(cmd_buffer), false);
                if(event) {
                    memcpy(event->param, cmd_buffer, sizeof(cmd_buffer));
                    app_task_event_post(event, false);
                }
            }
            else
            {
                status = bt_redial(user_bt_env.last_active_index);
            }
            break;
        case BT_STATE_HFP_INCOMMING:
            /* 来电状态下接听 */
            status = bt_answer_call(user_bt_env.last_active_index);
            break;
        default:
            return;
    }
    LOG_INFO("Call status = %d\r\n", status);
}

/**
 * @description: 工作模式按键（WorkMode）短按释放回调
 * @return {void}
 */
static void Hmi_WorkModeKeyShortReleaseCallback(void)
{
    /* 切换工作模式 */
    swc_work_mode = (Hmi_WorkMode_BTM == swc_work_mode) ? Hmi_WorkMode_IPK : Hmi_WorkMode_BTM;
    
    LOG_INFO("Work mode = %d", swc_work_mode);
    Rte_Hmi_Set_MMI_WorkMode(swc_work_mode);
    swc_work_mode_timer = 0u;
}

/**
 * @description: 蓝牙状态处理
 * @return {void}
 */
void Hmi_BtSts_Process(void)
{
    BtDeviceRecord record;
    BtStatus status;
    BD_ADDR remote_bd;
    static uint8_t ucmode = 0u;
    static uint16_t reconnect_Cnt = 0u;
    static uint16_t tmr = 0u;
    static uint16_t avrcp_tmr = 0u;
    /* static uint8_t avrcp_flag = 0u; 
    static uint16_t avrcp_tmr = 0u;
    static AvrcpChannel * last_sta = NULL; */

    /* 获取最新蓝牙状态 */
    bt_state = user_bt_get_state(user_bt_env.last_active_index);

    if (1u == media_replay_sts)
    {
        if (BT_STATE_MEDIA_PLAYING == bt_state)
        {
            media_replay_sts = 0u;
        }
        else if (BT_STATE_CONNECTED == bt_state)
        {
            if (100 < avrcp_tmr++)
            {
                LOG_DEBUG(">>>>>>>> media replay");
                AVRCP_SetPanelKey(user_bt_env.dev[user_bt_env.last_active_index].rcp_chan, AVRCP_POP_PLAY, TRUE);
                avrcp_tmr = 0u;
            }
        }
        else
        {}
        return;
    }

#if 0
    if ((last_sta == NULL) && (user_bt_env.dev[user_bt_env.last_active_index].rcp_chan != NULL))
    {
        if (1u == media_play_sts) {
            avrcp_flag = 1u;
            LOG_DEBUG(">>>>>>>> media play flag");
        }

        media_play_sts_flag = 1u;
    }
    last_sta = user_bt_env.dev[user_bt_env.last_active_index].rcp_chan;
    
    if (1u == avrcp_flag)
    {
        if (200 < avrcp_tmr++)
        {
            AVRCP_SetPanelKey(user_bt_env.dev[user_bt_env.last_active_index].rcp_chan, AVRCP_POP_PLAY, TRUE);
            LOG_DEBUG(">>>>>>>> media playing cmd");
            avrcp_flag = 0u;
        }
    }
#endif
    /* if ((user_bt_env.dev[user_bt_env.last_active_index].rcp_chan != NULL) && (1u == media_play_sts))
    {
        if (( 0 == avrcp_flag ) && (avrcp_tmr++ > 100)){
            AVRCP_SetPanelKey(user_bt_env.dev[user_bt_env.last_active_index].rcp_chan, AVRCP_POP_PLAY, TRUE);
            avrcp_flag = 1u;
        }
    }
    else
    {
        avrcp_tmr = 0u;
        avrcp_flag = 0u;
    } */

    /* if ((BT_STATE_HFP_CALLACTIVE == bt_state) || (BT_STATE_HFP_OUTGOING == bt_state) || (BT_STATE_HFP_INCOMMING == bt_state))
    {
        if (tmr++ > 100)
        {
            tmr = 0u;
            bt_list_current_calls(user_bt_env.last_active_index);
        }
    } */
    
    if (BT_STATE_HFP_CALLACTIVE == bt_state)
    {
        if (tmr++ > 100)
        {
            tmr = 0u;
            bt_list_current_calls(user_bt_env.last_active_index);
        }
    }


    if (bt_state != last_bt_state)
    {
        LOG_INFO(">>>> Current BT state = %d", bt_state);

        switch (bt_state)
        {
            case BT_STATE_HFP_CALLACTIVE:
                if (last_bt_state != BT_STATE_HFP_CALLACTIVE)
                {
                    bt_mediavol = HF_SpeakerGain(user_bt_env.dev[user_bt_env.last_active_index].hf_chan);
                    flag_sync = 0;
                }
            case BT_STATE_HFP_OUTGOING:
            case BT_STATE_HFP_INCOMMING:
                // if (1u == xdelay_req_bt_list_current_calls_flag)
                // {
                //     xdelay_req_bt_list_current_calls_flag = 0u;
                //     bt_list_current_calls(user_bt_env.last_active_index);
                // }
            case BT_STATE_CONNECTED:
            case BT_STATE_MEDIA_PLAYING:
                if (last_bt_state == BT_STATE_IDLE || last_bt_state == BT_STATE_CONNECTING)
                {
                    ucmode = 1u; /* 由断开状态转换为连接状态时，更新连接状态 */
                }
                break;
            case BT_STATE_CONNECTING:
            case BT_STATE_IDLE:
                if (last_bt_state >= BT_STATE_CONNECTED)
                {
                    vHmi_CallId_Clean();
                    vHmi_MediaInfo_Clean();
                }
                /* ----- 由其他状态变更为 idle 时，更新总线连接状态 ----- */
                Rte_Hmi_Set_Bt_ConnSts(Hmi_Bt_Status_Disconnected);
                ucmode = 0u;
                break;
            default:
                break;
        }
        last_bt_state = bt_state;
    }

    if (1 == ucmode)
    {
        /* if (reconnect_Cnt == 0u) {
            extern void turn_on_audio_amp(uint8_t on);
            turn_on_audio_amp(1); // 提前唤醒功放，防止"蓝牙已"吃字
        } */

        if (80u <= reconnect_Cnt++) // approx 800ms delay to let profiles settle and PA warm up
        {
            /* ----- 查询配对信息 ----- */
            remote_bd = user_bt_env.dev[0].remote_bd;
            status = SEC_FindDeviceRecord(&remote_bd, &record);
            if (status == BT_STATUS_SUCCESS)
            {
                LOG_DEBUG("设备已配对，信任状态：%d, 密钥类型：%d", record.trusted, record.keyType);
                /* ----- 更新总线连接状态 ----- */
                Rte_Hmi_Set_Bt_ConnSts(Hmi_Bt_Status_Connected);
                /* ----- 播报"蓝牙已连接"提示音 ----- */
                //app_audio_tone_play(AUDIO_TYPE_SBC, sbc_sample2, sbc_sample2_get_size());
                ucmode = 2u;
                reconnect_Cnt = 0u;
            }
        }
    }
    else if (2 == ucmode)
    {
        if (100u <= reconnect_Cnt++) // 1s
        {
            LOG_DEBUG("pbap client %d",pbap_client[user_bt_env.last_active_index].cApp.connState);
            status = PBAP_ClientConnect(&pbap_client[user_bt_env.last_active_index],&user_bt_env.dev[user_bt_env.last_active_index].remote_bd);
            if(status == BT_STATUS_PENDING){
                user_bt_env.dev[user_bt_env.last_active_index].pbap_client = &pbap_client[user_bt_env.last_active_index];
            }
            LOG_DEBUG("PBAP_ClientConnect status = %d",status);
            reconnect_Cnt = 0u;
        }

        if (user_bt_env.dev[user_bt_env.last_active_index].conFlags & LINK_STATUS_PBAP_CONNECTED)
        {
            ucmode = 3u;
        }
    }
    else
    {} 
}

/**
 * @description: 蓝牙身份验证
 * @return {void}
 */
static void Hmi_BtSts_IdVerf(void)
{
    static uint8_t bt_onoff_sts_l = HMI_STATE_UNKNOWN;
    uint8_t bt_onoff_sts;
    uint8_t voltagemode;

    uint8_t id_verf = Rte_Hmi_Get_Vin_Cmp();
    Rte_Read_BtrM_BtrM_VoltageMode(&voltagemode);

    if (HMI_TRUE == after_app_bt_init)
    {
        if ((HMI_TRUE == id_verf) && (STD_BTRM_MODE_A == voltagemode))
        {
            bt_onoff_sts = HMI_TRUE;
        }
        else
        {
            bt_onoff_sts = HMI_FALSE;
        }

        if ((bt_onoff_sts != bt_onoff_sts_l) || (HMI_STATE_UNKNOWN == bt_onoff_sts_l))
        {
            if (bt_onoff_sts)
            {
                Rte_Hmi_Set_Bt_Sts(0x00);
                my_bt_start_adv();
                printf("start_adv\r\n");
            }
            else
            {
                Rte_Hmi_Set_Bt_Sts(0x01);
                my_bt_stop_adv();
                printf("stop_adv\r\n");
            }

            bt_onoff_sts_l = bt_onoff_sts;
        }
    }
}

/**
 * @description: 音量设置
 * @return {void}
 */
static void Hmi_Set_CodecVol(void)
{
    static uint8_t last_vol = 0x0Au; 

    if (bt_mediavol != last_vol)
    {
        if (0x0 == bt_mediavol)
        {
            /* --- 音量从 other -> 0x0 时，静音 --- */
            bt_mute_sts = Hmi_Mute_On;
            LOG_DEBUG(">>>> Volume from other -> 0x0, mute on");
        }
        else
        {
            /* --- 音量从 所有值 -> 非0值时，如果处于静音状态，取消静音 --- */
            if (Hmi_Mute_On == bt_mute_sts)
            {
                LOG_DEBUG(">>>> Volume from all values -> non-0 value, mute off");
                bt_mute_sts = Hmi_Mute_Off;
                if (0 != last_vol)
                {
                    LOG_DEBUG(">>>> Volume from non-0 value -> non-0 value, do nothing");
                    bt_mediavol = last_vol;
                    return;
                }
                else
                {
                    LOG_DEBUG(">>>> Volume from 0 -> non-0 value, vol ++");
                }
            }
        }

        last_vol = bt_mediavol;
        /* --- 映射音量档位 0x0 - 0x7f --- */
        float vol_float = (float)bt_mediavol * 127.0f / Hmi_Volume_Max + 0.5f;
        uint8_t bt_vol = (uint8_t)vol_float;

        LOG_DEBUG(">>>> Current BT volume = 0x%02X\r\n", bt_mediavol);

        /* --- 设置本地 Codec 音量 --- */
        set_audio_codec_volumn(bt_mediavol);
        if(flag_sync != 0)
        {
            /* --- 设置对端（手机）音量 0x0 - 0x7f --- */
            bt_set_media_volume(user_bt_env.last_active_index, bt_vol);
            printf(">>>>>>>>set_media_volume %d\r\n", bt_vol);
        }
    }
}

/**
 * @description: 静音设置
 * @return {void}
 */
static void Hmi_Set_CodecMute(void)
{
    static uint8_t mute_sts_L = HMI_TRUE;
    uint8_t mute_sts = HMI_TRUE;

    /* 通话状态下强制开启播放（优先级最高） */
    #if 1
    if (BT_STATE_HFP_CALLACTIVE == bt_state)
    {
        mute_sts = HMI_FALSE;
    }
    else
    {
        /* 非通话状态下，按静音状态控制播放 */
        if (Hmi_Mute_Off == bt_mute_sts)
        {
            mute_sts = HMI_FALSE;
        }
        else
        {
            mute_sts = HMI_TRUE;
        }
    }

    if (mute_sts_L != mute_sts)
    {
        /* --- 解除静音时，如果音量等于0， 将音量设置为默认值 --- */
        if ((HMI_FALSE == mute_sts) && (0 == bt_mediavol))
        {
            LOG_DEBUG(">>>> Set Volume to Default = 0x%02X", Hmi_Volume_Default);
            bt_mediavol = Hmi_Volume_Default;
        }
        enable_amp_mute(mute_sts);
        LOG_DEBUG(">>>> mute sts = %d\r\n", mute_sts);
        mute_sts_L = mute_sts;
    }

    #endif
}

/**
 * @description: HMI应用主处理函数（简化调用逻辑）
 * @return {void}
 */
void Hmi_MainFunction(void)
{
    /* 定义按键处理参数 */
    const KeyProcessParam_t downKeyParam = {
        .SetSwStatusFunc = Rte_Hmi_Set_MMI_DownSwStatus,
        .ShortReleaseCallback = Hmi_DownKeyShortReleaseCallback,
        .LongPressCallback = Hmi_DownKeyLongPressCallback,
        .key_id = KEY1_Down
    };

    const KeyProcessParam_t upKeyParam = {
        .SetSwStatusFunc = Rte_Hmi_Set_MMI_UpSwStatus,
        .ShortReleaseCallback = Hmi_UpKeyShortReleaseCallback,
        .LongPressCallback = Hmi_UpKeyLongPressCallback,
        .key_id = KEY1_Up
    };

    const KeyProcessParam_t rightKeyParam = {
        .SetSwStatusFunc = Rte_Hmi_Set_MMI_RightSwStatus,
        .ShortReleaseCallback = Hmi_RightKeyShortReleaseCallback,
        .LongPressCallback = NULL,
        .key_id = KEY1_Right
    };

    const KeyProcessParam_t leftKeyParam = {
        .SetSwStatusFunc = Rte_Hmi_Set_MMI_LeftSwStatus,
        .ShortReleaseCallback = Hmi_LeftKeyShortReleaseCallback,
        .LongPressCallback = NULL,
        .key_id = KEY1_Left
    };

    const KeyProcessParam_t okKeyParam = {
        .SetSwStatusFunc = Rte_Hmi_Set_MMI_ConfirmSwStatus,
        .ShortReleaseCallback = NULL,
        .LongPressCallback = NULL,
        .key_id = KEY1_OK
    };

    const KeyProcessParam_t returnKeyParam = {
        .SetSwStatusFunc = Rte_Hmi_Set_MMI_ReturnSwStatus,
        .ShortReleaseCallback = NULL,
        .LongPressCallback = NULL,
        .key_id = KEY1_Return
    };

    const KeyProcessParam_t workModeKeyParam = {
        .SetSwStatusFunc = NULL,
        .ShortReleaseCallback = Hmi_WorkModeKeyShortReleaseCallback,
        .LongPressCallback = NULL,
        .key_id = KEY2_WorkMode
    };

    const KeyProcessParam_t muteKeyParam = {
        .SetSwStatusFunc = NULL,
        .ShortReleaseCallback = Hmi_MuteKeyShortReleaseCallback,
        .LongPressCallback = NULL,
        .key_id = KEY2_Mute
    };

    const KeyProcessParam_t telKeyParam = {
        .SetSwStatusFunc = NULL,
        .ShortReleaseCallback = Hmi_TelKeyShortReleaseCallback,
        .LongPressCallback = Hmi_TelKeyLongPressCallback,
        .key_id = KEY2_Tel
    };

    /* 统一调用通用按键处理函数 */
    Hmi_CommonKeyProcess(&workModeKeyParam);

    Hmi_CommonKeyProcess(&downKeyParam);
    Hmi_CommonKeyProcess(&upKeyParam);
    Hmi_CommonKeyProcess(&rightKeyParam);
    Hmi_CommonKeyProcess(&leftKeyParam);
    Hmi_CommonKeyProcess(&okKeyParam);
    Hmi_CommonKeyProcess(&returnKeyParam);
    Hmi_CommonKeyProcess(&muteKeyParam);
    Hmi_CommonKeyProcess(&telKeyParam);

    /* 音量、静音、蓝牙状态处理 */
    Hmi_Set_CodecVol();
    Hmi_Set_CodecMute();
    Hmi_BtSts_Process();
    Hmi_BtSts_IdVerf();

    if (Hmi_WorkMode_IPK == swc_work_mode)
    {
        swc_work_mode_timer++;
        if ((10000 / 10) <= swc_work_mode_timer)
        {
            swc_work_mode = Hmi_WorkMode_BTM;
            Rte_Hmi_Set_MMI_WorkMode(swc_work_mode);
            swc_work_mode_timer = 0u;
        }
    }
}