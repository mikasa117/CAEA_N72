#ifndef RANDOM_H
#define RANDOM_H

#include "Vector_Platform_Types.h"

/* Function declarations */
extern void Random_Init(void);
extern void Random_GetSeed1MainFunction(void);
extern uint32 Random_GetRandomValue1(void);
extern void Random_GetSeed2MainFunction(void);
extern uint32 Random_GetRandomValue2(void);

#endif /* RANDOM_H */ 
