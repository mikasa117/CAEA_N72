/*
 * @Author: BlueboxChamil
 * @Date: 2026-02-03 14:01:32
 * @LastEditTime: 2026-02-03 15:19:07
 * @FilePath: \components\modules\audio\test_loop.h
 * @Description:
 * Copyright (c) 2026 by BlueboxChamil, All Rights Reserved.
 */
#ifndef _TEST_LOOP_H
#define _TEST_LOOP_H

#include "audio_scene.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    audio_type_t audio_type;
    audio_hw_type_t hw_type;
    uint32_t hw_base_addr;
    uint8_t channels;
    uint32_t sample_rate;
} test_loop_param_t;

extern audio_scene_operator_t audio_loop_operator;

typedef struct
{
    uint16_t *data;
    uint16_t head; // Index of the next byte to be written
    uint16_t tail; // Index of the next byte to be read
    uint16_t size; // Size of the buffer
} RingBuffer_t;

bool my_ring_buff_init(RingBuffer_t *ring_buff, uint16_t size);
bool my_ring_buff_free(RingBuffer_t *ring_buff);
bool my_ring_buff_write(RingBuffer_t *ring_buff, uint16_t *data, uint16_t length);
bool my_ring_buff_read(RingBuffer_t *ring_buff, uint16_t *data, uint16_t length);
uint16_t my_ring_buff_used_space(RingBuffer_t *ring_buff);
uint16_t my_ring_buff_free_space(RingBuffer_t *ring_buff);

#endif // _VOICE_RECOGNIZE_H
