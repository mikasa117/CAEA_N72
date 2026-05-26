#include "Random.h"

#define RANDOM_MAX 0x7FFFFFFEUL

static uint32  SeRandom_dw_TimeSeed1 = 0x00000001;
static uint32  SeRandom_dw_TimeSeed2 = 0x00000001;

void Random_Init(void)
{
    //Random_Seed = 0x12345678U;
}

void Random_GetSeed1MainFunction(void)
{
    SeRandom_dw_TimeSeed1++;
}

uint32 Random_GetRandomValue1(void)
{
    uint32 quotient;
    uint32 remainderInst;
    uint32 t;
    uint32 LeRandom_dw_RetValue;

    quotient      = (uint32)(SeRandom_dw_TimeSeed1 / (uint32)127773L);
    remainderInst = (uint32)(SeRandom_dw_TimeSeed1 % (uint32)127773L);
    t             = (uint32)(((uint32)16807L * remainderInst) - ((uint32)2836L * quotient));
    SeRandom_dw_TimeSeed1 = t;
    LeRandom_dw_RetValue  = SeRandom_dw_TimeSeed1 % ((uint32)RANDOM_MAX + (uint32)1L);
    return ((uint32)LeRandom_dw_RetValue);
}

void Random_GetSeed2MainFunction(void)
{
    SeRandom_dw_TimeSeed2++;
}

uint32 Random_GetRandomValue2(void)
{
    uint32 quotient;
    uint32 remainderInst;
    uint32 t;
    uint32 LeRandom_dw_RetValue;
    
    quotient      = (uint32)(SeRandom_dw_TimeSeed2 / (uint32)127773L);
    remainderInst = (uint32)(SeRandom_dw_TimeSeed2 % (uint32)127773L);
    t             = (uint32)(((uint32)16807L * remainderInst) - ((uint32)2836L * quotient));
    SeRandom_dw_TimeSeed2 = t;
    LeRandom_dw_RetValue  = SeRandom_dw_TimeSeed2 % ((uint32)RANDOM_MAX + (uint32)1L);
    return ((uint32)LeRandom_dw_RetValue);
}
