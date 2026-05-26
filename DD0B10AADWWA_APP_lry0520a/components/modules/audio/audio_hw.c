#include "audio_hw.h"
#include "audio_common.h"

#include "fr30xx.h"
#include "FreeRTOS.h"

#define AUDIO_HW_PDM_RX_INT_LEVEL 32
#define AUDIO_HW_STORE_FRAME_COUNT 40

#define PSD_DAC_FIFO_HALF_DEPTH 32

struct audio_hw_env_t
{
    struct co_list hw_list;
};

struct audio_hw_handle_t
{
    audio_hw_t *audio_hw;
    void *hw_handle;
};

static struct audio_hw_env_t audio_hw_env = {0};
static struct audio_hw_handle_t i2s_hw_table[2];
static struct audio_hw_handle_t pdm_hw_table[2];

static struct audio_hw_handle_t codec_hw;
static struct audio_hw_handle_t psd_dac_hw;

static void i2s_rx_callback(I2S_HandleTypeDef *i2s_handle)
{
    uint8_t index;
    audio_hw_t *hw;

    for (index = 0; index < 3; index++)
    {
        if (i2s_hw_table[index].hw_handle == i2s_handle)
        {
            break;
        }
    }

    if (index < 3)
    {
        hw = i2s_hw_table[index].audio_hw;

        /* store data into internal buffer */
        if (hw->channels == AUDIO_CHANNELS_MONO)
        {
            int16_t *pcm = (void *)&hw->pcm[hw->channels * sizeof(int16_t) * hw->wr_ptr];
            for (uint32_t i = 0; i < I2S_FIFO_HALF_DEPTH;)
            {
                pcm[i++] = i2s_handle->I2Sx->DATA_L;
            }
        }
        else
        {
            uint32_t *pcm = (void *)&hw->pcm[hw->channels * sizeof(int16_t) * hw->wr_ptr];
            for (uint32_t i = 0; i < I2S_FIFO_HALF_DEPTH;)
            {
                pcm[i++] = i2s_handle->I2Sx->DATA_L;
            }
        }

        hw->wr_ptr += I2S_FIFO_HALF_DEPTH;
        if (hw->wr_ptr >= hw->pcm_samples)
        {
            hw->wr_ptr = 0;
        }

        /* notify receivers new data are available */
        audio_hw_output_t *output;
        output = (void *)co_list_pick(&hw->output_list);
        while (output)
        {
            if (output->handler)
            {
                output->handler(I2S_FIFO_HALF_DEPTH);
            }

            output = (void *)output->hdr.next;
        }
    }
}

static void i2s_tx_callback(I2S_HandleTypeDef *i2s_handle)
{
    uint8_t index;
    audio_hw_t *hw;

    for (index = 0; index < 3; index++)
    {
        if (i2s_hw_table[index].hw_handle == i2s_handle)
        {
            break;
        }
    }

    if (index < 3)
    {
        hw = i2s_hw_table[index].audio_hw;

        /* request new data to send through I2S */
        if (hw->request_handler)
        {
            hw->request_handler(hw->pcm_out, I2S_FIFO_HALF_DEPTH, hw->channels);
        }
        else
        {
            memset(hw->pcm_out, 0, hw->channels * sizeof(int16_t) * I2S_FIFO_HALF_DEPTH);
        }
        if (hw->channels == AUDIO_CHANNELS_MONO)
        {
            for (uint32_t i = 0; i < I2S_FIFO_HALF_DEPTH;)
            {
                i2s_handle->I2Sx->DATA_L = hw->pcm_out[i++];
            }
        }
        else
        {
            uint32_t *pcm = (void *)&hw->pcm_out[0];
            if (i2s_handle->Init.DataFormat == I2S_DATA_FORMAT_16BIT)
            {
                for (uint32_t i = 0; i < I2S_FIFO_HALF_DEPTH; i++)
                {
                    i2s_handle->I2Sx->DATA_L = pcm[i];
                }
            }
            else if (i2s_handle->Init.DataFormat == I2S_DATA_FORMAT_24BIT)
            {
                for (uint32_t i = 0; i < I2S_FIFO_HALF_DEPTH * AUDIO_CHANNELS_STEREO;)
                {
                    i2s_handle->I2Sx->DATA_L = hw->pcm_out[i++];
                    i2s_handle->I2Sx->DATA_R = hw->pcm_out[i++];
                }
            }
        }
    }
}

void i2s0_irq(void)
{
    //    fputc('I', NULL);
    i2s_IRQHandler(i2s_hw_table[0].hw_handle);
}

void i2s1_irq(void)
{
    i2s_IRQHandler(i2s_hw_table[1].hw_handle);
}

audio_hw_t *audio_hw_create(audio_hw_type_t type, audio_hw_request_pcm_t handler, uint32_t base_addr, audio_hw_dir_t dir, uint32_t sample_rate, uint8_t channels)
{
    audio_hw_t *tmp;
    bool reject = false;

    /* check duplication */
    tmp = (void *)co_list_pick(&audio_hw_env.hw_list);
    while (tmp)
    {
        if ((type == tmp->type) && (base_addr == tmp->base_addr))
        {
            reject = true;
        }
        tmp = (void *)tmp->hdr.next;
    }
    if (reject)
    {
        return NULL;
    }

    tmp = pvPortMalloc(sizeof(audio_hw_t));
    if (tmp == NULL)
    {
        goto __err;
    }
    tmp->type = type;
    tmp->dir = dir;
    tmp->channels = channels;
    tmp->sample_rate = sample_rate;
    tmp->base_addr = base_addr;
    tmp->hw_handle = NULL;
    tmp->request_handler = handler;
    tmp->pcm_out = NULL;
    tmp->wr_ptr = 0;
    co_list_init(&tmp->output_list);
    tmp->pcm = NULL;

    switch (type)
    {
    case AUDIO_HW_TYPE_I2S:
    case AUDIO_HW_TYPE_I2S_SLAVE:
    {
        I2S_HandleTypeDef *i2s_handle = pvPortMalloc(sizeof(I2S_HandleTypeDef));
        if (i2s_handle == NULL)
        {
            goto __err;
        }
        tmp->hw_handle = i2s_handle;

        switch (base_addr)
        {
        case I2S0_BASE:
            __SYSTEM_I2S0_CLK_ENABLE();
            i2s_handle->I2Sx = I2S0;
            i2s_hw_table[0].hw_handle = i2s_handle;
            i2s_hw_table[0].audio_hw = tmp;
            break;
        case I2S1_BASE:
            __SYSTEM_I2S1_CLK_ENABLE();
            i2s_handle->I2Sx = I2S1;
            i2s_hw_table[1].hw_handle = i2s_handle;
            i2s_hw_table[1].audio_hw = tmp;
            break;
        default:
            goto __err;
        }

        if (type == AUDIO_HW_TYPE_I2S)
            i2s_handle->Init.Mode = I2S_MODE_MASTER;
        else
            i2s_handle->Init.Mode = I2S_MODE_SLAVE;

        i2s_handle->Init.Standard = I2S_STANDARD_PHILIPS;
        i2s_handle->Init.DataFormat = I2S_DATA_FORMAT_16BIT;

        if (sample_rate == 48000)
        {
            __SYSTEM_I2S_CLK_SELECT_COREH();
            /* I2S Audio Clock Source: 24.576M */
            __SYSTEM_I2S_TUNE_SELECT_MODE1();
            __SYSTEM_I2S_TUNE_ENABLE();
            __SYSTEM_I2S_TUNE_CLK_GATE(42, 125);

            i2s_handle->Init.BCLKDIV = 8;
            i2s_handle->Init.ChannelLength = 32;
        }
        else if (sample_rate == 44100)
        {
            __SYSTEM_I2S_CLK_SELECT_AUPLL();
            /* I2S Audio Frequency: 22.5792M */
            __SYSTEM_I2S_TUNE_SELECT_MODE0();
            __SYSTEM_I2S_TUNE_ENABLE();
            __SYSTEM_I2S_TUNE_CLK_GATE(17, 625);

            i2s_handle->Init.BCLKDIV = 54;
            i2s_handle->Init.ChannelLength = 32;
        }
        else if (sample_rate == 16000)
        {
            __SYSTEM_I2S_CLK_SELECT_COREH();
            /* I2S Audio Clock Source: 24.576M */
            __SYSTEM_I2S_TUNE_SELECT_MODE1();
            __SYSTEM_I2S_TUNE_ENABLE();
            __SYSTEM_I2S_TUNE_CLK_GATE(42, 125);

            i2s_handle->Init.BCLKDIV = 48;       // 24;
            i2s_handle->Init.ChannelLength = 16; // 32;
        }
        else if (sample_rate == 8000)
        {
            __SYSTEM_I2S_CLK_SELECT_COREH();
            /* I2S Audio Clock Source: 24.576M */
            __SYSTEM_I2S_TUNE_SELECT_MODE1();
            __SYSTEM_I2S_TUNE_ENABLE();
            __SYSTEM_I2S_TUNE_CLK_GATE(42, 125);

            i2s_handle->Init.BCLKDIV = 96;       // 48;
            i2s_handle->Init.ChannelLength = 16; // 32;
        }

        else
        {
            goto __err;
        }

        /* insert new audio hw to list before enable interrupt */
        co_list_push_back(&audio_hw_env.hw_list, &tmp->hdr);

        /* Initialize and start I2S */
        i2s_init(i2s_handle);
        if (dir & AUDIO_HW_DIR_IN)
        {
            tmp->pcm_samples = I2S_FIFO_HALF_DEPTH * AUDIO_HW_STORE_FRAME_COUNT;
            tmp->pcm = (void *)pvPortMalloc(sizeof(int16_t) * channels * tmp->pcm_samples);
            if (tmp->pcm == NULL)
            {
                goto __err;
            }

            i2s_handle->RxIntCallback = i2s_rx_callback;
            i2s_receive_IT(i2s_handle);
        }
        if (dir & AUDIO_HW_DIR_OUT)
        {
            tmp->pcm_out = (void *)pvPortMalloc(sizeof(int16_t) * channels * I2S_FIFO_HALF_DEPTH);
            if (tmp->pcm_out == NULL)
            {
                goto __err;
            }

            i2s_handle->TxIntCallback = i2s_tx_callback;
            i2s_transmit_IT(i2s_handle);
        }

        switch (base_addr)
        {
        case I2S0_BASE:
            NVIC_EnableIRQ(I2S0_IRQn);
            break;
        case I2S1_BASE:
            NVIC_EnableIRQ(I2S1_IRQn);
            break;
        default:
            goto __err;
        }
    }
    break;

    default:
        goto __err;
    }

    return tmp;

__err:
    if (tmp->hw_handle)
    {
        vPortFree(tmp->hw_handle);
    }
    if (tmp->pcm)
    {
        vPortFree(tmp->pcm);
    }
    if (tmp->pcm_out)
    {
        vPortFree(tmp->pcm_out);
    }
    co_list_extract(&audio_hw_env.hw_list, &tmp->hdr);
    vPortFree(tmp);

    return NULL;
}

void audio_hw_destroy(audio_hw_t *hw)
{
    if (hw == NULL)
    {
        return;
    }

    GLOBAL_INT_DISABLE();
    if (co_list_extract(&audio_hw_env.hw_list, &hw->hdr))
    {
        switch (hw->type)
        {
        case AUDIO_HW_TYPE_I2S:
        case AUDIO_HW_TYPE_I2S_SLAVE:
            i2s_deinit(hw->hw_handle);
            switch (hw->base_addr)
            {
            case I2S0_BASE:
                __SYSTEM_I2S0_CLK_DISABLE();
                NVIC_DisableIRQ(I2S0_IRQn);
                break;
            case I2S1_BASE:
                __SYSTEM_I2S1_CLK_DISABLE();
                NVIC_DisableIRQ(I2S1_IRQn);
                break;
            default:
                break;
            }
            break;

        default:
            break;
        }
    }
    GLOBAL_INT_RESTORE();

    audio_hw_output_t *output;
    output = (void *)co_list_pop_front(&hw->output_list);
    while (output)
    {
        vPortFree(output);
        output = (void *)co_list_pop_front(&hw->output_list);
    }

    if (hw->hw_handle)
    {
        vPortFree(hw->hw_handle);
    }
    if (hw->pcm)
    {
        vPortFree(hw->pcm);
    }
    if (hw->pcm_out)
    {
        vPortFree(hw->pcm_out);
    }
    vPortFree(hw);
}

audio_hw_output_t *audio_hw_output_add(audio_hw_t *hw, audio_hw_receive_pcm_ntf_t handler)
{
    audio_hw_output_t *output;

    if (hw == NULL)
    {
        return NULL;
    }

    output = pvPortMalloc(sizeof(audio_hw_output_t));
    if (output)
    {
        GLOBAL_INT_DISABLE();
        output->audio_hw = hw;
        output->handler = handler;
        output->rd_ptr = hw->wr_ptr;
        co_list_push_back(&hw->output_list, &output->hdr);
        GLOBAL_INT_RESTORE();
    }

    return output;
}

void audio_hw_output_remove(audio_hw_t *hw, audio_hw_output_t *output)
{
    if (hw == NULL)
    {
        return;
    }

    GLOBAL_INT_DISABLE();
    co_list_extract(&hw->output_list, &output->hdr);
    GLOBAL_INT_RESTORE();

    vPortFree(output);
}

static void *copy_pcm(audio_hw_output_t *output, void *pcm, uint32_t samples, uint8_t channels)
{
    audio_hw_t *hw = output->audio_hw;

    if (channels == AUDIO_CHANNELS_MONO)
    {
        if (hw->channels == AUDIO_CHANNELS_MONO)
        {
            int16_t *src = (int16_t *)hw->pcm + output->rd_ptr;
            int16_t *dst = pcm;
            for (uint32_t i = 0; i < samples; i++)
            {
                *dst++ = *src++;
            }
            pcm = dst;
        }
        else
        {
            int16_t *src = (int16_t *)hw->pcm + (output->rd_ptr << 1);
            int16_t *dst = pcm;
            for (uint32_t i = 0; i < samples; i++)
            {
                *dst++ = *src;
                src += 2;
            }
            pcm = dst;
        }
    }
    else
    {
        if (hw->channels == AUDIO_CHANNELS_MONO)
        {
            int16_t *src = (int16_t *)hw->pcm + output->rd_ptr;
            int16_t *dst = pcm;
            for (uint32_t i = 0; i < samples; i++)
            {
                *dst++ = *src;
                *dst++ = *src++;
            }
            pcm = dst;
        }
        else
        {
            uint32_t *src = (uint32_t *)hw->pcm + output->rd_ptr;
            uint32_t *dst = pcm;
            for (uint32_t i = 0; i < samples; i++)
            {
                *dst++ = *src++;
            }
            pcm = dst;
        }
    }

    return pcm;
}

uint32_t audio_hw_read_pcm(audio_hw_output_t *output, void *pcm, uint32_t samples, uint8_t channels)
{
    audio_hw_t *hw = output->audio_hw;
    uint32_t tail_samples;
    uint32_t read_samples = 0;

    tail_samples = hw->pcm_samples - output->rd_ptr;
    if (tail_samples <= samples)
    {
        pcm = copy_pcm(output, pcm, tail_samples, channels);
        output->rd_ptr = 0;
        samples -= tail_samples;
        read_samples = tail_samples;
    }
    if (samples)
    {
        pcm = copy_pcm(output, pcm, samples, channels);
        output->rd_ptr += samples;
        read_samples += samples;
    }

    return read_samples;
}
