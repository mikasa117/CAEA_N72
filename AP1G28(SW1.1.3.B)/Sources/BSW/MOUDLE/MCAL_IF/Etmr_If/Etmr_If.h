#ifndef ETMR_H
#define ETMR_H

#include <Etmr_If_Cfg.h>
#include "Typedef.h"

extern void EtmrIf_Init(void);
extern void EtmrIf_DeInit(void);
extern void EtmrIf_Enable(void);
extern void EtmrIf_UpdatePwmChannel(uint32 instance,uint8 channel,uint32 dutyCycle);
extern void EtmrIf_UpdatePwmChannel_100(uint32 instance,uint8 channel);
extern void EtmrIf_DRV_SetLdok(uint32 instance);
extern void EtmrIf_DRV_ClearLdok(uint32 instance);
#endif 
