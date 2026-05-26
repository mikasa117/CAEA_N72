/*
 * @Author: liuranyang liuranyang@cncaea.cn
 * @Date: 2026-01-29 16:57:55
 * @LastEditors: liuranyang liuranyang@cncaea.cn
 * @LastEditTime: 2026-03-01 15:27:31
 * @FilePath: \FR30xxC-SDK-v0.3.1\examples\application\btdm_audio\Src\Bsw\SystemService\EcuM\EcuM.c
 * @Description: 默认设置
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "EcuM.h"
#include "dio_if.h"
#include "adc_if.h"
//#include "can_app.h"
//#include "uds_task.h"
#include "Switch.h"
#include "STD_BtrM.h"
#include "SysM.h"
#include "Hmi.h"
#include "Can_Main.h"
#include "CanDrv.h"
#include "audio_codec.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
extern void AppTaskCreate(void);
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

/*******************************************************************************
Name			: EcuM_InitMemery
Syntax			: void EcuM_InitMemery(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
void EcuM_InitMemery(void)
{	
    dio_if_Init();
	// 初始化必要的系统组件
    adc_if_init();

    my_es8389_init();
    
		
    // 优先初始化CAN相关组件，确保CAN能尽快发送消息
    CanMain_InitMemory(0u);
    CanMain_InitMemory(1u);
    CanDrv_Init();
		Switch_Init();
		BtrM_Init();
    
    // 创建应用任务，让系统尽快进入运行状态
    
    // 延迟初始化非关键组件
    
    
    SysM_InitMemory();
    Hmi_Init();
    
    /* Added by chuzewei on 20260330 below */
    //extern void audio_codec_task_init(void);
    //audio_codec_task_init();
    /* Above */
    AppTaskCreate();

}

/*EoF*/