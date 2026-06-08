

#include "hardware.h"
void initGPIO(void)
{
    uint32_t temp;

    return;
}

void initADC(void)
{
    uint32_t temp;

    return;
}

void dcBusAdcRead(int32_t *current, int32_t *avg_current, int32_t *voltage, int32_t *temper)
{
    uint32_t temp;

    return;
}

// void uvwAdcRead(int32_t *u, int32_t *v, int32_t *w, int32_t *g)
// {
//     int32_t _u, _v, _w, _g;
//     uint32_t temp;
//     _g = ((_u + _v + _w) * 10922) >> 15;
//     *u = _u;
//     *v = _v;
//     *w = _w;
//     *g = _g;
// }

void initDIV(void)
{
//    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DIV, ENABLE);
//    DIV0->DIV_CTRL = 1;
}

// int32_t Divider(int32_t dividend, int32_t divisor)
// {
//     int32_t quotient, drop, remain;
//     return quotient;
// }

void initOPA(void)
{
    uint32_t temp;

}

void initACMP(void)
{

}

void initWallTIMER(void)
{
}

void initPWM(void)
{

}
