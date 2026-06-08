#ifndef _HARDWARE_H_
#define _HARDWARE_H_

#include "amb_cfg.h"
#include "main.h"


void initADC(void);
void dcBusAdcRead(int32_t *current, int32_t *avg_current, int32_t *voltage, int32_t *temper);
// void uvwAdcRead(int32_t *u, int32_t *v, int32_t *w, int32_t *g);
__STATIC_INLINE void uvwAdcStart(void)
{

}
__STATIC_INLINE void dcBusAdcStart(void)
{

}

__STATIC_INLINE void extriAdcStart(void)
{

}

__STATIC_INLINE void extriAdcStop(void)
{

}

__STATIC_INLINE void shuntAdcStart(void)
{

}

__STATIC_INLINE void otherAdcStart(void)
{

}


void initDIV(void);
// int32_t Divider(int32_t dividend, int32_t divisor);

void initOPA(void);
void initACMP(void);

void initWallTIMER(void);
__STATIC_INLINE uint32_t time(void)
{
    return SysTick->VAL;
}

#define ONE_MINI_SECOND   (48000)
/* unit ms, max 1398ms */
__STATIC_INLINE void delay(uint32_t i)
{
    uint32_t now, last, len;
    if (i > 299)
        i = 299;
    len = i * 48000;
    last = SysTick->VAL;
    do {
        now = SysTick->VAL;
        if (((last - now) & 0xFFFFFF) > len)
            break;
    } while(1);
}

void initPWM(void);
__STATIC_INLINE void pwmStart(void)
{
    eTMR0->SYNC |= eTMR_SYNC_CLDOK_MASK;
    eTMR0->CHMASK = 0x0000000;

    eTMR0->CH[2].VAL0 = EPWM_PERIOD - (EPWM_PERIOD>>1);
    eTMR0->CH[2].VAL1 = EPWM_PERIOD + (EPWM_PERIOD>>1);
    eTMR0->CH[0].VAL0 = EPWM_PERIOD - (EPWM_PERIOD>>1);
    eTMR0->CH[0].VAL1 = EPWM_PERIOD + (EPWM_PERIOD>>1);
    eTMR0->CH[4].VAL0 = EPWM_PERIOD - (EPWM_PERIOD>>1);
    eTMR0->CH[4].VAL1 = EPWM_PERIOD + (EPWM_PERIOD>>1);
    eTMR0->SYNC |= eTMR_SYNC_LDOK_MASK;
}

__STATIC_INLINE void pwmStop(void)
{
	
    eTMR0->SYNC |= eTMR_SYNC_CLDOK_MASK;
    eTMR0->CHMASK = 0x00000FF;
    eTMR0->CH[2].VAL0 = EPWM_PERIOD - (EPWM_PERIOD>>1);
    eTMR0->CH[2].VAL1 = EPWM_PERIOD + (EPWM_PERIOD>>1);
    eTMR0->CH[0].VAL0 = EPWM_PERIOD - (EPWM_PERIOD>>1);
    eTMR0->CH[0].VAL1 = EPWM_PERIOD + (EPWM_PERIOD>>1);
    eTMR0->CH[4].VAL0 = EPWM_PERIOD - (EPWM_PERIOD>>1);
    eTMR0->CH[4].VAL1 = EPWM_PERIOD + (EPWM_PERIOD>>1);
    eTMR0->SYNC |= eTMR_SYNC_LDOK_MASK;
}



#endif /* _HARDWARE_H_ */
