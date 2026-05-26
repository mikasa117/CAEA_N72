#include "audio_scene.h"
#include "audio_rpmsg.h"
#include "audio_hw.h"
#include "audio_encoder.h"
#include "dsp_mem.h"

#include "audio_loop.h"
void stereo_to_left(int16_t *pcm, int samples);
#define STORE_MIC_PCM_DATA_SAMPLES 128
RingBuffer_t my_ring;
#define MY_RING_SIZE 128
uint16_t my_ring_buff[MY_RING_SIZE];
uint16_t my_ring_wr[MY_RING_SIZE];
uint16_t my_ring_re[MY_RING_SIZE];

typedef struct
{
    audio_hw_t *hw;
    audio_hw_output_t *hw_output;

    uint16_t *buffer;
} voice_recognize_env_t;

static audio_scene_t *audio_loop_scene = NULL;
void stereo_to_left(int16_t *pcm, int samples)
{
    for (int i = 0; i < samples; i++)
    {
        pcm[i] = pcm[2 * i];
    }
}
static void hw_receive_pcm(uint32_t samples)
{
    audio_scene_evt_hw_in_new_samples_t *evt = (void *)pvPortMalloc(sizeof(audio_scene_evt_hw_in_new_samples_t));

    if (evt)
    {
        evt->evt.type = AUDIO_SCENE_EVT_TYPE_HW_IN_NEW_SAMPLES;
        evt->evt.scene = audio_loop_scene;
        evt->adc_new_samples = samples;
        audio_scene_send_event(&evt->evt);
    }
}

static audio_scene_t *allocate(void *_param)
{
    audio_scene_t *scene = pvPortMalloc(sizeof(audio_scene_t));

    if (scene)
    {
        voice_recognize_env_t *env = pvPortMalloc(sizeof(voice_recognize_env_t));
        if (env == NULL)
        {
            vPortFree(scene);
            return NULL;
        }

        test_loop_param_t *param = pvPortMalloc(sizeof(test_loop_param_t));
        if (param == NULL)
        {
            vPortFree(env);
            vPortFree(scene);
            return NULL;
        }

        scene->env = env;
        memcpy((void *)param, _param, sizeof(test_loop_param_t));
        scene->param = param;
        scene->op = &audio_loop_operator;
    }

    return scene;
}

void send_mic_data_to_skp(void *pcm, uint32_t samples, uint8_t channels)
{
    // printf("send_mic_data_to_skp\r\n");
    bool result = my_ring_buff_read(&my_ring, my_ring_re, samples);
    if (!result)
    {
        printf("Failed to read from ring buffer!\r\n");
    }
    // printf("iis want samples = %d,channels = %d\r\n", samples, channels);
    if (channels == 1)
    {
        memcpy(pcm, my_ring_re, samples * sizeof(int16_t));
    }
    else if (channels == 2)
    {
        int16_t *out = (int16_t *)pcm;
        for (uint8_t i = 0; i < samples; i++)
        {
            out[2 * i] = my_ring_re[i];     // Left
            out[2 * i + 1] = my_ring_re[i]; // Right
        }
    }
}

static void init(audio_scene_t *scene)
{
    voice_recognize_env_t *env = scene->env;
    test_loop_param_t *param = scene->param;

    audio_loop_scene = scene;

    env->buffer = pvPortMalloc(STORE_MIC_PCM_DATA_SAMPLES * sizeof(uint16_t) * param->channels);

    env->hw = audio_hw_create(param->hw_type, send_mic_data_to_skp, param->hw_base_addr, AUDIO_HW_DIR_INOUT, param->sample_rate, param->channels);
    env->hw_output = audio_hw_output_add(env->hw, hw_receive_pcm);

    my_ring_buff_init(&my_ring, MY_RING_SIZE);
}

static void destroy(audio_scene_t *scene)
{
    voice_recognize_env_t *env = scene->env;

    audio_hw_destroy(env->hw);

    vPortFree(env->buffer);
    vPortFree(scene->env);
    vPortFree(scene->param);
    vPortFree(scene);
    audio_loop_scene = NULL;
}

static void event_handler(audio_scene_t *scene, audio_scene_evt_t *evt)
{
    voice_recognize_env_t *env = scene->env;
    test_loop_param_t *param = scene->param;

    switch (evt->type)
    {
    case AUDIO_SCENE_EVT_TYPE_HW_IN_NEW_SAMPLES:
    {
        int encoded_frame_count;
        audio_scene_evt_hw_in_new_samples_t *_evt = (void *)evt;
        uint32_t adc_new_samples = _evt->adc_new_samples;
        while (adc_new_samples)
        {
            uint32_t samples = adc_new_samples > STORE_MIC_PCM_DATA_SAMPLES ? STORE_MIC_PCM_DATA_SAMPLES : adc_new_samples;
            // samples = audio_hw_read_pcm(env->hw_output, env->buffer, samples, param->channels);
            samples = audio_hw_read_pcm(env->hw_output, my_ring_wr, samples, param->channels);
            //                    voice_recognize_launch((int16_t *)env->buffer, samples);
            adc_new_samples -= samples;

            stereo_to_left((int16_t *)my_ring_wr, samples);
            // uart_transmit(uart2Handler(), test_read_buf, samples * 2);
            bool result = my_ring_buff_write(&my_ring, my_ring_wr, samples);
            if (!result)
            {
                printf("Failed to write to ring buffer!\r\n");
            }

            // printf("adc_new_samples = %d,samples = %d\r\n", adc_new_samples, samples);
        }
    }
    break;

    default:
        break;
    }
}

audio_scene_operator_t audio_loop_operator = {
    .allocate = allocate,
    .init = init,
    .destroy = destroy,
    .event_handler = event_handler,
    .decoder_started = NULL,
    .support_tone = false,
};

/**
 * @brief 初始化环形数组
 *
 * @param ring_buff
 * @param size
 * @return true
 * @return false
 */
bool my_ring_buff_init(RingBuffer_t *ring_buff, uint16_t size)
{
    ring_buff->size = size;
    ring_buff->data = my_ring_buff; //(int16_t *)malloc(ring_buff->size * sizeof(int16_t));
    if (ring_buff->data == NULL)
    {
        printf("Memory allocation failed!\r\n");
        return false;
    }
    ring_buff->head = 0;
    ring_buff->tail = 0;
    printf("Ring buffer initialized with size %d\r\n", ring_buff->size);
    return true;
}

/**
 * @brief 释放环形数组
 *
 * @param ring_buff
 * @return true
 * @return false
 */
bool my_ring_buff_free(RingBuffer_t *ring_buff)
{
    if (ring_buff->data != NULL)
    {
        // free(ring_buff->data);
        ring_buff->data = NULL;
        ring_buff->head = 0;
        ring_buff->tail = 0;
        ring_buff->size = 0;
        printf("Ring buffer memory freed\r\n");
        return true;
    }
    else
    {
        printf("Ring buffer is already freed or not initialized!\r\n");
        return false;
    }
}

/**
 * @brief 向环形数组写入数据
 *
 * @param ring_buff
 * @param data
 * @param length
 * @return true
 * @return false
 */
bool my_ring_buff_write(RingBuffer_t *ring_buff, uint16_t *data, uint16_t length)
{
    uint16_t used = (ring_buff->head + ring_buff->size - ring_buff->tail) % ring_buff->size;
    uint16_t available_space = ring_buff->size - used - 1; // 通常留一个空位区分满/空

    if (length > available_space)
    {
        // printf("Not enough space in the buffer to write data!\n");
        return false;
    }
    // Write data to the ring buffer
    if (length > ring_buff->size - ring_buff->head)
    {
        uint16_t first_part = ring_buff->size - ring_buff->head;
        memcpy(&ring_buff->data[ring_buff->head], data, first_part * sizeof(uint16_t));
        memcpy(ring_buff->data, &data[first_part], (length - first_part) * sizeof(uint16_t));
        ring_buff->head = (ring_buff->head + length) % ring_buff->size;
    }
    else
    {
        memcpy(&ring_buff->data[ring_buff->head], data, length * sizeof(uint16_t));
        ring_buff->head = (ring_buff->head + length) % ring_buff->size; // Update head position
    }
    // printf("write data done\n");
    return true;
}

/**
 * @brief 从环形数组读取数据
 *
 * @param ring_buff
 * @param data
 * @param length
 * @return true
 * @return false
 */
bool my_ring_buff_read(RingBuffer_t *ring_buff, uint16_t *data, uint16_t length)
{
    uint16_t used = (ring_buff->head + ring_buff->size - ring_buff->tail) % ring_buff->size;

    if (length > used)
    {
        // printf("Not enough data in the buffer to read!\n");
        return false;
    }

    // Read data from the ring buffer
    if (length > ring_buff->size - ring_buff->tail)
    {
        uint16_t first_part = ring_buff->size - ring_buff->tail;
        memcpy(data, &ring_buff->data[ring_buff->tail], first_part * sizeof(uint16_t));
        memcpy(&data[first_part], ring_buff->data, (length - first_part) * sizeof(uint16_t));
        ring_buff->tail = (ring_buff->tail + length) % ring_buff->size;
    }
    else
    {
        memcpy(data, &ring_buff->data[ring_buff->tail], length * sizeof(uint16_t));
        ring_buff->tail = (ring_buff->tail + length) % ring_buff->size; // Update tail position
    }
    // printf("read data done\n");
    return true;
}

/**
 * @brief 获取环形数组已使用的空间
 *
 * @param ring_buff
 * @return uint16_t
 */
uint16_t my_ring_buff_used_space(RingBuffer_t *ring_buff)
{
    return (ring_buff->head + ring_buff->size - ring_buff->tail) % ring_buff->size;
}

/**
 * @brief 获取环形数组已使用的空间
 *
 * @param ring_buff
 * @return uint16_t
 */
uint16_t my_ring_buff_free_space(RingBuffer_t *ring_buff)
{
    return ring_buff->size - my_ring_buff_used_space(ring_buff) - 1; // 通常留一个空位区分满/空
}