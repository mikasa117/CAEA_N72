#ifndef _DSP_MEM_H
#define _DSP_MEM_H

#include <stdint.h>

void *dsp_mem_alloc(uint32_t size);
void dsp_mem_free(void *ptr);
void dsp_mem_get_usage(uint32_t *curr_free, uint32_t *min_free);
void dsp_mem_get_usage_v2(uint8_t type, uint32_t *curr_free, uint32_t *min_free);   // type: 0-local memory; 1-sram
void dsp_mem_sram_heap_init(uint32_t base_addr, uint32_t length);

uint32_t dsp_mem32_read(uint32_t address);
void dsp_mem32_write(uint32_t address, uint32_t value);

void dsp_cache_attr_set(uint32_t icache_attr, uint32_t dcache_attr, uint8_t icache_ways, uint8_t dcache_ways);

#endif  // _DSP_MEM_H
