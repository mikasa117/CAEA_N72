#ifndef CAN_TRCV_H
#define CAN_TRCV_H

#include "Vector_Platform_Types.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define CeCanTrcv_e_Sleepmode  2u
#define CeCanTrcv_e_Standbymode  1u
#define CeCanTrcv_e_Normalmode  0u


extern void CanTrcv_WakeUpTrcv(void);
extern void CanTrcv_WakeupClearFlag(void);
extern void CanTrcv_EnableWakeup(void);
extern void CanTrcv_DummyFun(void);
extern void CanTrcv_DisableWakeup(void);
extern void CanTrcv_DisableTrcv(void);
extern uint8 CanTrcv_CheckWakeup(void);

#define CeCanTrcv_e_Normalmode  0u

extern void CanTrcv_MainFunction(void);
extern uint8 GetCanTrcv_CurrentMode(void);







#endif /* CAN_TRCV_H */ 
