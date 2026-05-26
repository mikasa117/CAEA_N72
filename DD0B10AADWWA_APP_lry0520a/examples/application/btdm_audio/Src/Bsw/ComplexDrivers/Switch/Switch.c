/*
 * @Author: liuranyang liuranyang@cncaea.cn
 * @Date: 2026-01-29 15:46:51
 * @LastEditors: liuranyang liuranyang@cncaea.cn
 * @LastEditTime: 2026-03-17 16:36:53
 * @FilePath: \FR30xxC-SDK-v0.3.1\examples\application\btdm_audio\Src\Bsw\ComplexDrivers\Switch\Switch.c
 * @Description: 默认设置
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Switch.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static void Switch_GetKey1St(void);
static void Switch_GetKey2St(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static uint8_t SeSw_u_KeySt[KEY_CH_MAXNUM]; /*0:release 1:press*/
static uint16_t SeSw_u_PressCnt[KEY_CH_MAXNUM];
static uint16_t SeSw_u_ReleaseCnt[KEY_CH_MAXNUM];
static uint8_t SeSw_u_PressSt[KEY_CH_MAXNUM]; /*0:PRESS_DOWN 1:PRESS_SHORTRELEASE 2:PRESS_LONG 3:PRESS_LONGRELEASE */
static uint8_t SeSw_u_PressOldSt[KEY_CH_MAXNUM];
static uint16_t SeSw_u_ContPressCnt[KEY_CH_MAXNUM]; // 新增：连按计数（记录长按后已过时间）

static const Key_AdcThresh_s key_adc_table[KEY_CH_MAXNUM] = 
{
    {KEY1_Down,     CeSw_w_Key1Down_Min,        CeSw_w_Key1Down_Max},
    {KEY1_Up,       CeSw_w_Key1Up_Min,          CeSw_w_Key1Up_Max},
    {KEY1_Right,    CeSw_w_Key1Right_Min,       CeSw_w_Key1Right_Max},
    {KEY1_Left,     CeSw_w_Key1Left_Min,        CeSw_w_Key1Left_Max},
    {KEY1_OK,       CeSw_w_Key1OK_Min,          CeSw_w_Key1OK_Max},
    {KEY1_Return,   CeSw_w_Key1Return_Min,      CeSw_w_Key1Return_Max},
    {KEY2_WorkMode, CeSw_w_Key2WorkMode_Min,    CeSw_w_Key2WorkMode_Max},
    {KEY2_Mute,     CeSw_w_Key2Mute_Min,        CeSw_w_Key2Mute_Max},
    {KEY2_Tel,      CeSw_w_Key2Tel_Min,         CeSw_w_Key2Tel_Max}
};
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* ========================================================================== */
/*                        Application Local Functions                         */
/* ========================================================================== */

/*******************************************************************************
Name			: Switch_Init
Syntax			: void Switch_Init(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
void Switch_Init(void)
{
    uint8_t LeSw_u_Index;

    for (LeSw_u_Index = 0u; LeSw_u_Index < KEY_CH_MAXNUM; LeSw_u_Index++)
    {
        SeSw_u_KeySt[LeSw_u_Index] = KEY_RELEASE;
        SeSw_u_PressSt[LeSw_u_Index] = PRESS_IDLE;
        SeSw_u_PressOldSt[LeSw_u_Index] = PRESS_IDLE;
        SeSw_u_PressCnt[LeSw_u_Index] = 0u;
        SeSw_u_ReleaseCnt[LeSw_u_Index] = 0u;
        SeSw_u_ContPressCnt[LeSw_u_Index] = 0u; // 初始化连按计数
    } 
} 

/*******************************************************************************
Name			: Switch_MainFuction
Syntax			: void Switch_MainFuction(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
void Switch_MainFuction(void)
{
    uint8_t LeSw_u_Index;
    uint8_t LeSw_u_BtrASta;
    uint8_t LeSw_u_PwrMSta;

    LeSw_u_BtrASta = (uint8_t)SWITCH_TRUE;//BTRM_GetSysBatteryModeAStatus();
    LeSw_u_PwrMSta = (uint8_t)SWITCH_TRUE;//PwrM_GetPwrModeStatus();

    if ( (SWITCH_TRUE == LeSw_u_BtrASta) && (SWITCH_TRUE == LeSw_u_PwrMSta) )
    {
        /* ----- 获取按键原始状态 ----- */
        Switch_GetKey1St();
        Switch_GetKey2St();

        /* ----- 遍历所有按键通道 ----- */
        for ( LeSw_u_Index = 0u; LeSw_u_Index < KEY_CH_MAXNUM; LeSw_u_Index++)
        {
            /* ----- 处理按键按下状态 ----- */
            if (SeSw_u_KeySt[LeSw_u_Index] == KEY_PRESS)/*Press*/
            {
                /* ----- 重置释放计数 ----- */
                SeSw_u_ReleaseCnt[LeSw_u_Index] = 0u;
                /* ----- 增加按下计数（防止溢出） ----- */
                if (SeSw_u_PressCnt[LeSw_u_Index] < 0xFFFFu)
                {
                    SeSw_u_PressCnt[LeSw_u_Index]++;
                }

                /* ----- 按下状态过滤 ----- */
                if (SeSw_u_PressCnt[LeSw_u_Index] > CeSw_w_PressFilterCnt)
                {
                    /* ----- 根据按下时间确定按键状态 ----- */
                    if (SeSw_u_PressCnt[LeSw_u_Index] > CeSw_w_StuckFilterCnt)
                    {
                        SeSw_u_PressSt[LeSw_u_Index] = PRESS_STUCK;					
                    }
                    else if (SeSw_u_PressCnt[LeSw_u_Index] > CeSw_w_LongFilterCnt)
                    {
                        SeSw_u_PressSt[LeSw_u_Index] = PRESS_LONG;

                        /* ----- 长按计数超过阈值后，开始累计连按时间 ----- */
                        if (SeSw_u_ContPressCnt[LeSw_u_Index] < 0xFFFFu)
                        {
                            SeSw_u_ContPressCnt[LeSw_u_Index]++;
                        }
                        if (SeSw_u_ContPressCnt[LeSw_u_Index] >= CeSw_w_ContPressFilterCnt)
                        {
                            SeSw_u_PressSt[LeSw_u_Index] = PRESS_CONTINUOUS;
                            SeSw_u_ContPressCnt[LeSw_u_Index] = 0u; // 重置连按计数，循环触发
                        }
                    }
                    else if ( (SeSw_u_PressSt[LeSw_u_Index] != PRESS_LONG) || (SeSw_u_PressSt[LeSw_u_Index] == PRESS_CONTINUOUS) )
                    {
                        SeSw_u_PressSt[LeSw_u_Index] = PRESS_DOWN;
                    }
                    else {} 
                }
            }
            else/*Release*/
            {
                /* ----- 重置按下计数 ----- */
                SeSw_u_PressCnt[LeSw_u_Index] = 0u;
                /* ----- 增加释放计数（防止溢出） ----- */
                if (SeSw_u_ReleaseCnt[LeSw_u_Index] < 0xFFFFu)
                {
                    SeSw_u_ReleaseCnt[LeSw_u_Index]++;
                }
                
                /* ----- 释放状态过滤 ----- */
                if(SeSw_u_ReleaseCnt[LeSw_u_Index] > CeSw_w_ReleaseFilterCnt)
                {
                    /* ----- 根据释放前的状态确定事件类型 ----- */
                    if(SeSw_u_PressSt[LeSw_u_Index] == PRESS_DOWN)
                    {
                        SeSw_u_PressSt[LeSw_u_Index] = PRESS_SHORTRELEASE;
                    }
                    else if ((SeSw_u_PressSt[LeSw_u_Index] == PRESS_LONG) || (SeSw_u_PressSt[LeSw_u_Index] == PRESS_CONTINUOUS))
                    {
                        SeSw_u_PressSt[LeSw_u_Index] = PRESS_LONGRELEASE;
                    }
                    else if(SeSw_u_PressSt[LeSw_u_Index] == PRESS_STUCK)
                    {
                        SeSw_u_PressSt[LeSw_u_Index] = PRESS_STUCKRELEASE;	
                    }
                    else{}
                }
            }
        }
    }
    else {} 
}

/*******************************************************************************
Name			: Switch_GetKey1St
Syntax			: void Switch_GetKey1St(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
static void Switch_GetKey1St(void)
{
    uint8_t index = 0u;
    uint16_t SeSw_w_Key1Ad = 0u;
    static uint8_t is_all_key1_release  = SWITCH_TRUE;
    SeSw_w_Key1Ad = adc_if_get_currValue(adc_cl_msw_r);

    /* ----- 全释放 置位所有按键为释放 ----- */
    if (SeSw_w_Key1Ad > CeSw_w_KeyAd_Invalid)
    {
        is_all_key1_release = SWITCH_TRUE;
        for (index = Key1_Start; index <= Key1_End; index++)
        {
            SeSw_u_KeySt[index] = KEY_RELEASE;
        }
    }

    /* ----- 全释放时检测按键按下 ----- */
    if (is_all_key1_release == SWITCH_TRUE)
    {
        for (index = Key1_Start; index <= Key1_End; index++)
        {
            if ((SeSw_w_Key1Ad >= key_adc_table[index].adc_min) && (SeSw_w_Key1Ad <= key_adc_table[index].adc_max))
            {
                SeSw_u_KeySt[index] = KEY_PRESS;
                is_all_key1_release = SWITCH_FALSE;
                break;
            }
        }
    }
}

/*******************************************************************************
Name			: Switch_GetKey2St
Syntax			: void Switch_GetKey2St(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
static void Switch_GetKey2St(void)
{
    uint8_t index = 0u;
    uint16_t SeSw_w_Key2Ad = 0u;
    static uint8_t is_all_key2_release  = SWITCH_TRUE;
    SeSw_w_Key2Ad = adc_if_get_currValue(adc_cl_msw_l);

    /* ----- 全释放 置位所有按键为释放 ----- */
    if (SeSw_w_Key2Ad > CeSw_w_KeyAd_Invalid)
    {
        is_all_key2_release = SWITCH_TRUE;
        for (index = Key2_Start; index <= Key2_End; index++)
        {
            SeSw_u_KeySt[index] = KEY_RELEASE;
        }
    }

    /* ----- 全释放时检测按键按下 ----- */
    if (is_all_key2_release == SWITCH_TRUE)
    {
        for (index = Key2_Start; index <= Key2_End; index++)
        {
            if ((SeSw_w_Key2Ad >= key_adc_table[index].adc_min) && (SeSw_w_Key2Ad <= key_adc_table[index].adc_max))
            {
                SeSw_u_KeySt[key_adc_table[index].key_idx] = KEY_PRESS;
                is_all_key2_release = SWITCH_FALSE;
                break;
            }
        }
    }
}

/*******************************************************************************
Name			: Switch_GetPressSt
Syntax			: TeSwitch_e_PressSt Switch_GetPressSt(uint8_t ch)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
TeSwitch_e_PressSt Switch_GetPressSt(uint8_t ch)
{
    uint8_t rtn;
    if (ch <= KEY_CH_MAXNUM)
    {
        if (SeSw_u_PressOldSt[ch] != SeSw_u_PressSt[ch])
        {
            rtn = SeSw_u_PressSt[ch];
            SeSw_u_PressOldSt[ch] = SeSw_u_PressSt[ch];

            /* ----- 连按事件触发后，恢复为PRESS_LONG，等待下一个150ms周期 ----- */
            if (rtn == PRESS_CONTINUOUS)
            {
                SeSw_u_PressSt[ch] = PRESS_LONG;
            }
        }
        else
        {
            rtn = PRESS_IDLE;
        }
    }
    else
    {
        rtn = PRESS_IDLE;
    }
    return rtn;
}

/*EoF*/