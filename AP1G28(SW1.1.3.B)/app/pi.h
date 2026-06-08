#ifndef _PI_H_
#define _PI_H_

#include <stdint.h>
//#include <core_cm0.h>

typedef struct {
    int32_t   q15_sum;
    int32_t   q15_kp;
    int32_t   q15_ki;
    int32_t   q15_out_max;
    int32_t   q15_out_min;
    int32_t   q15_error;
    int32_t   q15_out;
} t_PIParm;

struct pi_test {
    float  kp;
    float  ki;
    float  ti_kp;
    float  ti_ki;
};

__STATIC_INLINE void calcPI(t_PIParm *pparm)
{
    int32_t out;
    int32_t dsum;

    dsum = (pparm->q15_error * pparm->q15_ki);
    out  = (pparm->q15_error * pparm->q15_kp) + pparm->q15_sum + dsum;
    pparm->q15_out = out>>15;

    if (pparm->q15_out >  pparm->q15_out_max) {
        pparm->q15_out =  pparm->q15_out_max;
        if (pparm->q15_error < 0)
            pparm->q15_sum += dsum;
    } else if (pparm->q15_out < pparm->q15_out_min) {
        pparm->q15_out =  pparm->q15_out_min;
        if (pparm->q15_error > 0)
            pparm->q15_sum += dsum;
    } else {
        pparm->q15_sum += dsum;
    }
}

typedef struct {
    int32_t   q15_sum;
    int32_t   q15_kp;
    int32_t   q15_ki;
    int32_t   q15_out_max;
    int32_t   q15_out_min;
    int32_t   q15_error;
    int32_t   q15_error_max;
    int32_t   q15_out;
    int32_t   q15_kf;
    int32_t   q15_inff;
} t_PIFFParm;

__STATIC_INLINE void calcPIFF(t_PIFFParm *pparm)
{
    int32_t out;
    int32_t dsum;

//    if (pparm->q15_error > pparm->q15_error_max)
//        pparm->q15_error = pparm->q15_error_max;
//    if (pparm->q15_error < -pparm->q15_error_max)
//        pparm->q15_error = -pparm->q15_error_max;

    dsum = (pparm->q15_error * pparm->q15_ki);
    out  = (pparm->q15_error * pparm->q15_kp) + pparm->q15_sum + dsum;
    out += pparm->q15_inff * pparm->q15_kf;
    pparm->q15_out = out>>15;

    if (pparm->q15_out >  pparm->q15_out_max) {
        pparm->q15_out =  pparm->q15_out_max;
        if (pparm->q15_error < 0)
            pparm->q15_sum += dsum;
    } else if (pparm->q15_out < pparm->q15_out_min) {
        pparm->q15_out =  pparm->q15_out_min;
        if (pparm->q15_error > 0)
            pparm->q15_sum += dsum;
    } else {
        pparm->q15_sum += dsum;
    }
}

#endif /* _PI_H_ */
