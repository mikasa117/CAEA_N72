#ifndef CAN_MAIN_H_
#define CAN_MAIN_H_

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Vector_Platform_Types.h"
#include "v_def.h"
/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/**/
#define CeCanMain_u_canSleep 	  1u
#define CeCanMain_u_canNotSleep   0u


/**/
#define CeCanMain_u_busActive      1u
#define CeCanMain_u_busNotActive   0u


/********************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Global Variable with extern linkage
|******************************************************************************/


/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/
extern uint8 CanMain_getCanSleepSta(void);
extern void CanMain_InitMemory( uint8 LeCanMain_u_Src );
extern void CanMain_5msAMainFunction(void);
extern void CanMain_5msBMainFunction(void);
extern void CanMain_10msAMainFunction(void);
extern void CanMain_10msBMainFunction(void);
extern void CanMain_20msMainFunction(void);
extern void CanMain_50msMainFunction();
extern void CanMain_initAllModule( void );

extern void CanMain_BusOffFlgHandler(void);
extern void Can_getBusOffStaDtc(uint8 *Le_p_busOffStaDtc);
extern void CanMain_ClrDtcBusOff(void);
extern void Can_getBusActiveSta(uint8 *Le_p_busActiveSta);

extern void CanMain_BusOffStartSet(void);
extern void CanMain_BusOffEndSet(void);
extern void CanMain_ResetKeepComCnt(uint8 ch);

extern void CanMain_init( void );

extern uint8 CanMain_GetDTCENFlag(void);
extern void CanMain_SetNeedReset(void);
extern uint8 CanMain_GetNeedReset(void);
#endif   /*EOF*/
