#ifndef MCUIF_H
#define MCUIF_H

//#include "SysTypes.h"
#include "STD_McuIf_Cfg.h"
//#include "rcu_driver.h"

//extern void RCM_ClearStickySrcStatus(void);
extern status_t McuIf_ClockInit(void);
//extern void McuIf_SysModeInit(void);
//extern void McuIf_ClearLastResetStatus(void);
extern void McuIf_SoftwareReset(void);
extern void McuIf_EnableIRQ(McuIf_IRQnType IRQnId);
extern void McuIf_DisableIRQ(McuIf_IRQnType IRQnId);


#endif
