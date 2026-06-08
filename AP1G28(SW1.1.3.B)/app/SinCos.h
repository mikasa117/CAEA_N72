
#ifndef SINCOS_H
#define SINCOS_H

#include <stdint.h>

#define TRIG_TABLE         /* 是否使能自定义sin/cos查找表 */
#define SMALL_TRIG_TABLE 1 /* 使能512元素或1024元素查找表 */

/* Divquo = Dividend/Divisor */
//#define Divider(Dividend, Divisor, Divquo)	{\
//																								HDIV->DIVIDEND = Dividend;\
//																								HDIV->DIVISOR = Divisor;\
//																								__nop();\
//																								__nop();\
//																								Divquo = HDIV->QUOTIENT;\
//																						}
#ifdef TRIG_TABLE
#if(SMALL_TRIG_TABLE==1)
extern const volatile int16_t Q15Sin[];       /* 小表 */
#define Q15SIN(x) (Q15Sin[(uint16_t)(x)>>7])
#define Q15COS(x) (Q15Sin[((uint16_t)((uint16_t)(x)+16384))>>7])
#else
extern const volatile int16_t Q15Sin[];      /* 大表 */
#define Q15SIN(x) (Q15Sin[(uint16_t)(x)>>6])
#define Q15COS(x) (Q15Sin[((uint16_t)((uint16_t)(x)+16384))>>6])
#endif
#endif

void InitVqSqrtTable(uint16_t MaxValue);
int32_t VqMaxSqrt(int32_t Vd);
uint16_t i32sqrt(uint32_t a);
int16_t i16sin(uint16_t x);

#endif
