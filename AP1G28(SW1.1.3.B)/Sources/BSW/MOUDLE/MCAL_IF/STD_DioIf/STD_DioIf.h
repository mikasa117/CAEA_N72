#ifndef DIOIF_H
#define DIOIF_H

#include "STD_DioIf_Cfg.h"
#include "YTM32B1ME0.h"

extern void DioIf_Init(void);
extern void DioIf_DeInit(void);
extern void DioIf_WriteChannel(uint8 ChannelId,uint8 Level);
extern uint8 DioIf_ReadChannel(uint8 ChannelId);

#endif
