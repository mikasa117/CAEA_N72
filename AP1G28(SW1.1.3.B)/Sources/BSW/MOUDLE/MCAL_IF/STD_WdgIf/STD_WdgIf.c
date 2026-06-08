#include "STD_WdgIf.h"
#include "sdk_project_config.h"

static const SwWdg_ConfigStruct *stWdgIfSwCfg[WDGIF_INSTANCE_MAX_NUM] = /* PRQA S 3218 */
{
	&wdg_config0,	/*   50ms  */
};



 /*******************************************************************************
Name			: WdgIf_Init
Syntax			: void WdgIf_Init(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
/* polyspace<MISRA-C3:8.7:Not a defect:Justified> Normal. */
void WdgIf_Init(uint8 InstanceId)
{
	const uint8 TempInstanceId = InstanceId;

	WdgIf_DeInit();

	if(TempInstanceId < (uint8)WDGIF_INSTANCE_MAX_NUM)
	{
		(void)WDG_DRV_Init(WDG_INST, stWdgIfSwCfg[TempInstanceId]);
	}
}

 /*******************************************************************************
Name			: WdgIf_DeInit
Syntax			: void WdgIf_DeInit(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
/* polyspace<MISRA-C3:8.7:Not a defect:Justified> Normal. */
void WdgIf_DeInit(void)
{
	WDG_DRV_Deinit(WDG_INST);
}


 /*******************************************************************************
Name			: WdgIf_Trigger
Syntax			: void WdgIf_Trigger(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
/* polyspace<MISRA-C3:8.7:Not a defect:Justified> Normal. */
void WdgIf_Trigger(void)
{
    WDG_DRV_Trigger(WDG_INST);
}

 /*******************************************************************************
Name			: WdgIf_Trigger
Syntax			: void WdgIf_Trigger(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
void WdgIf_SetMode(uint8 WdgMode)
{
	if((uint8)WDGIF_MODE_OFF == WdgMode)
	{
		WdgIf_DeInit();
	}
	else if((uint8)WDGIF_MODE_SLOW == WdgMode)
	{
		WdgIf_Init(0u);
		WdgIf_Trigger();
	}
    else
    {
    }
}
/*EOF*/

