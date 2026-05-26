#ifndef CAN_DEM_CALLBACK_H
#define CAN_DEM_CALLBACK_H

#include "Vector_Platform_Types.h"

extern uint8 CanDem_GetIgnStatus(void);
extern uint8 CanDem_GetBatteryMode(void);
extern uint8 CanDem_GetDTC_85EN(void);
extern uint8 CanDem_GetPowerModeOn(void);
extern uint8 CanDem_GetBusOffState(void);
extern uint8 CanDem_GetSPIComState(void);
#endif
