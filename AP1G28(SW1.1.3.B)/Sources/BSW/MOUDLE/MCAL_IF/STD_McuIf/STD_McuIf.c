#include "STD_McuIf.h"
#include "sdk_project_config.h"


status_t McuIf_ClockInit(void)
{

	status_t ucReturn;

	/* Initialize clocks*/
	(void)CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,
				  g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
	ucReturn = CLOCK_SYS_UpdateConfiguration(CLOCK_MANAGER_ACTIVE_INDEX,CLOCK_MANAGER_POLICY_AGREEMENT);

	return ucReturn;
}







void McuIf_SoftwareReset(void)
{
	SystemSoftwareReset();
}


void McuIf_EnableIRQ(McuIf_IRQnType IRQnId)
{
	INT_SYS_EnableIRQ(IRQnId);
}
void McuIf_DisableIRQ(McuIf_IRQnType IRQnId)
{
	INT_SYS_DisableIRQ(IRQnId);
}


