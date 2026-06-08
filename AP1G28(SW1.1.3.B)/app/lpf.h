#ifndef _LPF_H_
#define _LPF_H_

#include <stdint.h>
#include "cmsis_gcc.h"

typedef struct {
    int32_t  qIn;
    int32_t  qOut;
    int32_t  qAlpha;
    int32_t  qState;
} tLPFParm;

__STATIC_INLINE void calcLPF(tLPFParm *pParm)
{
    pParm->qState += (pParm->qIn - pParm->qOut) * pParm->qAlpha;
    pParm->qOut = (pParm->qState >> 12);
}

#endif /* _LPF_H_ */
