#ifndef _SBC_SAMPLE_H
#define _SBC_SAMPLE_H

#include <stdint.h>

extern uint8_t sbc_sample1[];
#if 0
extern uint8_t sbc_sample2[];
#endif
extern unsigned char music_sbl_sample[];

uint32_t sbc_sample1_get_size(void);
#if 0
uint32_t sbc_sample2_get_size(void);
#endif
uint32_t music_sbl_sample_get_size(void);

#endif  // _SBC_SAMPLE_H
