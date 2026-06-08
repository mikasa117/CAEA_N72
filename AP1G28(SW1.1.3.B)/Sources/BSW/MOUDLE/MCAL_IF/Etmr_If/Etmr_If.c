#include "Etmr_If.h"
#include "sdk_project_config.h"

 /*******************************************************************************
Name			: EtmrIf_Init
Syntax			: void EtmrIf_Init(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
/* polyspace<MISRA-C3:8.7:Not a defect:Justified> Normal. */
void EtmrIf_Init()
{
	eTMR_DRV_Init(0,&ETMR_CM_Config0,&ETMR_CM_Config0_State);
    eTMR_DRV_InitPwm(0,&ETMR_PWM_Config0);
	eTMR_DRV_Init(2,&ETMR_CM_Config1,&ETMR_CM_Config1_State);
    eTMR_DRV_InitPwm(2,&ETMR_PWM_Config1);
	eTMR_DRV_Init(3,&ETMR_CM_Config2,&ETMR_CM_Config2_State);
    eTMR_DRV_InitPwm(3,&ETMR_PWM_Config2);
	eTMR_DRV_Enable(PWM_INST);
	eTMR_DRV_Enable(PWM2_INST);
	eTMR_DRV_Enable(PWM3_INST);
}

 /*******************************************************************************
Name			: EtmrIf_Enable
Syntax			: void EtmrIf_Enable(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
/* polyspace<MISRA-C3:8.7:Not a defect:Justified> Normal. */
void EtmrIf_Enable(void)
{
	eTMR_DRV_Enable(PWM_INST);
	eTMR_DRV_Enable(PWM2_INST);
	eTMR_DRV_Enable(PWM3_INST);
}
 /*******************************************************************************
Name			: EtmrIf_DeInit
Syntax			: void EtmrIf_DeInit(void)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
/* polyspace<MISRA-C3:8.7:Not a defect:Justified> Normal. */
void EtmrIf_DeInit(void)
{
	eTMR_DRV_Deinit(PWM_INST);
	eTMR_DRV_Deinit(PWM2_INST);
	eTMR_DRV_Deinit(PWM3_INST);
}
 /*******************************************************************************
Name			: EtmrIf_UpdatePwmChannel
Syntax			: void EtmrIf_UpdatePwmChannel(uint32_t instance,uint8_t channel,uint32_t dutyCycle)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
/* polyspace<MISRA-C3:8.7:Not a defect:Justified> Normal. */
void EtmrIf_UpdatePwmChannel(uint32 instance,uint8 channel,uint32 dutyCycle)
{
	eTMR_DRV_UpdatePwmChannel(instance, channel, dutyCycle, 0);
	//eTMR_DRV_SetLdok(instance);
}

 /*******************************************************************************
Name			: EtmrIf_UpdatePwmChannel_100
Syntax			: void EtmrIf_UpdatePwmChannel_100(uint32 instance,uint8 channel)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
/* polyspace<MISRA-C3:8.7:Not a defect:Justified> Normal. */
void EtmrIf_UpdatePwmChannel_100(uint32 instance,uint8 channel)
{
	g_etmrBase[instance]->CH[channel].VAL0 = 0;
    g_etmrBase[instance]->CH[channel].VAL1 = g_etmrBase[instance]->MOD + 1;
	//eTMR_DRV_SetLdok(instance);
}

/*******************************************************************************
Name			: EtmrIf_DRV_SetLdok
Syntax			: EtmrIf_DRV_SetLdok(uint32 instance)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
/* polyspace<MISRA-C3:8.7:Not a defect:Justified> Normal. */
void EtmrIf_DRV_SetLdok(uint32 instance)
{
	eTMR_DRV_SetLdok(instance);
}
/*******************************************************************************
Name			: EtmrIf_DRV_ClearLdok
Syntax			: EtmrIf_DRV_ClearLdok(uint32 instance)
Sync/Async		: Synchronous
Reentrancy		: None
Parameters(in)	: None
Parameters(out) : None
Return value	: None
Description		: None
Call By			: 
|******************************************************************************/
/* polyspace<MISRA-C3:8.7:Not a defect:Justified> Normal. */
void EtmrIf_DRV_ClearLdok(uint32 instance)
{
	eTMR_DRV_ClearLdok(instance);
}

/*EOF*/

