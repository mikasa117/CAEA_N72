
#ifndef __SYS_TASK_H__
#define __SYS_TASK_H__

#include "sdk_project_config.h"

extern uint16_t system_1ms_TCF;
extern uint16_t system_10ms_TCF;
extern uint16_t system_100ms_TCF;

extern void sys_TaskInit(void) ;
extern void sys_LoopTask(void);

#endif
