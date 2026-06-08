#include "Random.h"
#include "STD_EepCfg.h"
#include "STD_EepM.h"
#include "desc.h"



#define RANDOM_MAX 0x7FFFFFFEUL

static uint32 SeRandom_dw_TimeSeed = 0x00000001;



uint32 Random_GetRandomValue(void)
{
    uint32 quotient;
    uint32 remainderInst; 
    uint32 t;
    uint32 LeRandom_dw_RetValue;

    quotient = (uint32)(SeRandom_dw_TimeSeed / (uint32)127773L);
    remainderInst = (uint32)(SeRandom_dw_TimeSeed % (uint32)127773L);
    t = (uint32)(((uint32)16807L * remainderInst) - ((uint32)2836L * quotient));
    /*  if (t <= 0)
    {
        t = t + (uint32)0x7FFFFFFFL;
    }*/
    SeRandom_dw_TimeSeed = t;
    LeRandom_dw_RetValue = SeRandom_dw_TimeSeed % ((uint32)RANDOM_MAX + (uint32)1L);

    return ((uint32)LeRandom_dw_RetValue);


}

void Random_GetSeedMainFunction(void)
{
    SeRandom_dw_TimeSeed++;
}
