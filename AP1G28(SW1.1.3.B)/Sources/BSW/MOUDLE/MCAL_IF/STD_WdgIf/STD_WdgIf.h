#ifndef WDGIF_H
#define WDGIF_H

#include <STD_WdgIf_Cfg.h>

#define WDG_INST        0

extern void WdgIf_Init(uint8 InstanceId);
extern void WdgIf_DeInit(void);
extern void WdgIf_Trigger(void);
extern void WdgIf_SetMode(uint8 WdgMode);
#endif 
