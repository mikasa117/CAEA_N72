#ifndef _ESTIMATOR_H_
#define _ESTIMATOR_H_

extern void dir_init(float rs, float ls, float dead_rate, float kfi, float alpha, float vpeak, float ipeak, float freq);
extern void dir_estimator(int32_t ialpha, int32_t ibeta, int32_t valpha, int32_t vbeta, int32_t vdc);
extern int16_t dir_angle(void);
extern int32_t dir_speed(void);
extern int32_t dir_bemfq(void);
extern void dir_updatekfi(int32_t v);
extern void svpwm_init(int16_t period, int16_t window);
extern void svpwm_window(int16_t window);
extern uint8_t svpwm(int32_t valpha, int32_t vbeta, int16_t *pwma, int16_t *pwmb, int16_t *pwmc, int16_t *s1, int16_t *s2);
extern void rebuildcurrent(uint8_t sector, int32_t c1, int32_t c2, int32_t *ia, int32_t *ib, int32_t *ic);

#endif /* _ESTIMATOR_H_ */
