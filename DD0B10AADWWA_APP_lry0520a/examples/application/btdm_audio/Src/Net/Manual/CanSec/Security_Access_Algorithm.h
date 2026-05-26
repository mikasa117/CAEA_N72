#ifndef SECURITY_ACCESS_ALGORITHM_H
#define SECURITY_ACCESS_ALGORITHM_H

#include "Platform_Types.h"

/* Function declarations */
extern uint32 SecurityAccess_GenerateKey(uint32 seed);
extern uint8 SecurityAccess_ValidateKey(uint32 seed, uint32 key);
extern void SecurityAccess_GetSeed(uint32* seed);

#endif /* SECURITY_ACCESS_ALGORITHM_H */ 