/*
 * @Author: liuranyang liuranyang@cncaea.cn
 * @Date: 2026-01-29 15:47:02
 * @LastEditors: liuranyang liuranyang@cncaea.cn
 * @LastEditTime: 2026-02-27 17:41:29
 * @FilePath: \FR30xxC-SDK-v0.3.1\examples\application\btdm_audio\Src\Bsw\ComplexDrivers\Switch\Switch.h
 * @Description: 默认设置
 */

#ifndef __SWITCH_H_
#define __SWITCH_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "adc_if.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define SWITCH_TRUE                   (uint8_t)(1u)
#define SWITCH_FALSE                  (uint8_t)(0u)

#define CeSw_u_TaskPeriod             (uint8_t)(10u)
#define CeSw_w_PressFilterCnt         (uint16_t)((uint16_t)50u/CeSw_u_TaskPeriod)
#define CeSw_w_ReleaseFilterCnt       (uint16_t)((uint16_t)50u/CeSw_u_TaskPeriod)
#define CeSw_w_ContPressFilterCnt     (uint16_t)((uint16_t)200u/CeSw_u_TaskPeriod) // 200ms连按周期
#define CeSw_w_LongFilterCnt          (uint16_t)((uint16_t)1000u/CeSw_u_TaskPeriod)
#define CeSw_w_StuckFilterCnt         (uint16_t)((uint16_t)12000u)/*120s*/

#define CeSw_w_KeyAd_Invalid          (uint16_t)3400u

/***********************KEY1 AMP8************************ */
#define CeSw_w_Key1Down_Max           (uint16_t)2999u
#define CeSw_w_Key1Down               (uint16_t)2739u /*2.20v*/
#define CeSw_w_Key1Down_Min           (uint16_t)2400u 

#define CeSw_w_Key1Up_Max             (uint16_t)2399u
#define CeSw_w_Key1Up                 (uint16_t)2068u /*1.66v*/
#define CeSw_w_Key1Up_Min             (uint16_t)1700u

#define CeSw_w_Key1Right_Max          (uint16_t)1699u
#define CeSw_w_Key1Right              (uint16_t)1444u /*1.16v*/
#define CeSw_w_Key1Right_Min          (uint16_t)1300u

#define CeSw_w_Key1Left_Max           (uint16_t)1299u
#define CeSw_w_Key1Left               (uint16_t)1004u /*0.80v*/
#define CeSw_w_Key1Left_Min           (uint16_t)800u

#define CeSw_w_Key1OK_Max             (uint16_t)799u
#define CeSw_w_Key1OK                 (uint16_t)610u /*0.49v*/
#define CeSw_w_Key1OK_Min             (uint16_t)500u

#define CeSw_w_Key1Return_Max         (uint16_t)499u
#define CeSw_w_Key1Return             (uint16_t)285u /*0.23v*/
#define CeSw_w_Key1Return_Min         (uint16_t)100u

/***********************KEY2 AMP5************************ */
#define CeSw_w_Key2WorkMode_Max       (uint16_t)1399u
#define CeSw_w_Key2WorkMode           (uint16_t)1159u /*0.93v*/
#define CeSw_w_Key2WorkMode_Min       (uint16_t)900u 

#define CeSw_w_Key2Mute_Max           (uint16_t)899u
#define CeSw_w_Key2Mute               (uint16_t)668u /*0.54v*/
#define CeSw_w_Key2Mute_Min           (uint16_t)400u 

#define CeSw_w_Key2Tel_Max            (uint16_t)399u
#define CeSw_w_Key2Tel                (uint16_t)285u /*0.23v*/
#define CeSw_w_Key2Tel_Min            (uint16_t)100u 

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
typedef enum
{ 
    KEY1_Down = 0u,
    KEY1_Up,
    KEY1_Right,
    KEY1_Left,
    KEY1_OK,
	KEY1_Return,   
    KEY2_WorkMode,
    KEY2_Mute,
    KEY2_Tel,
    KEY_CH_MAXNUM
}TeSwitch_e_KEY;

#define Key1_Start                     (uint8_t)( KEY1_Down )
#define Key1_End                       (uint8_t)( KEY1_Return )
#define Key2_Start                     (uint8_t)( KEY2_WorkMode )
#define Key2_End                       (uint8_t)( KEY2_Tel )

typedef enum
{  
    KEY_RELEASE = 0u,
	KEY_PRESS 
}TeSwitch_e_KeySt;

typedef enum
{  
    PRESS_DOWN = 0u,
	PRESS_SHORTRELEASE,
	PRESS_LONG,
	PRESS_LONGRELEASE,
    PRESS_STUCK,
    PRESS_STUCKRELEASE,
    PRESS_CONTINUOUS, // 新增：长按连按触发状态
	PRESS_IDLE,
}TeSwitch_e_PressSt;

typedef struct
{
    TeSwitch_e_KEY key_idx;    // 按键索引
    uint16_t adc_min;    // 按下的最小ADC值
    uint16_t adc_max;    // 按下的最大ADC值
} Key_AdcThresh_s;


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
extern void Switch_Init(void);
extern void Switch_MainFuction(void);
extern TeSwitch_e_PressSt Switch_GetPressSt(uint8_t ch);

#endif /* #ifndef __SWITCH_H_ */

/*EoF*/