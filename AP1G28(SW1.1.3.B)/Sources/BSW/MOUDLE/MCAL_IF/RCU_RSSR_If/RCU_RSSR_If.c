#include "RCU_RSSR_If.h"
#include "sdk_project_config.h"


static uint32 ucRCU_RSSR_If_HistoryFlag = 0u;
 /*******************************************************************************
Name			: RCU_RSSR_IF_Get_Flag
Syntax			: void RCU_RSSR_IF_Get_Flag(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/

void RCU_RSSR_IF_Get_HistoryRegFlag(void)
{
	ucRCU_RSSR_If_HistoryFlag = RCU->RSSR;
}
 /*******************************************************************************
Name			: RCU_RSSR_IF_Get_Flag
Syntax			: void RCU_RSSR_IF_Get_Flag(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/

void RCU_RSSR_IF_Clear_HistoryFlag(void)
{
	RCU->RSSR|=0x1<<0;
	RCU->RSSR|=0x1<<1;
	RCU->RSSR|=0x1<<8;
	RCU->RSSR|=0x1<<9;
	RCU->RSSR|=0x1<<16;
	RCU->RSSR|=0x1<<17;
	RCU->RSSR|=0x1<<18;
	RCU->RSSR|=0x1<<19;
	RCU->RSSR|=0x1<<20;
}





/*EOF*/

