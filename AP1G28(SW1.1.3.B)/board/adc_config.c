/*
 * Copyright 2020-2026 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * @file adc_config.c
 * @brief 
 * 
 */


#include "adc_config.h"



/* adc_config0 */
const adc_converter_config_t adc_config0={
    .clockDivider=0,
    .startTime=48,
    .sampleTime=10,
    .overrunMode=false,
    .autoOffEnable=false,
    .waitEnable=false,
    .trigger=ADC_TRIGGER_SOFTWARE,
    .align=ADC_ALIGN_RIGHT,
    .resolution=ADC_RESOLUTION_12BIT,
    .dmaWaterMark=0,
    .dmaEnable=false,
    .sequenceConfig={
        .sequenceMode=ADC_CONV_LOOP,
        .sequenceIntEnable=false,
        .convIntEnable=false,
        .readyIntEnable=false,
        .ovrunIntEnable=false,
        .sampIntEnable=false,
        .channels={
            ADC_INPUTCHAN_EXT0,
            ADC_INPUTCHAN_EXT1,
            ADC_INPUTCHAN_EXT7,
            ADC_INPUTCHAN_EXT2,
            ADC_INPUTCHAN_EXT3,
            ADC_INPUTCHAN_EXT4,
            ADC_INPUTCHAN_EXT5,
            ADC_INPUTCHAN_EXT12,
        },
        .totalChannels=8,
    },
    .compareConfig={
        .compareEnable=false,
        .compareAllChannelEnable=false,

        .compHigh=4095,
        .compLow=0,
        .compIntEnable=false,
    },
};


/* adc_config1 */
const adc_converter_config_t adc_config1={
    .clockDivider=0,
    .startTime=48,
    .sampleTime=2,
    .overrunMode=false,
    .autoOffEnable=false,
    .waitEnable=false,
    .trigger=ADC_TRIGGER_HARDWARE,
    .align=ADC_ALIGN_RIGHT,
    .resolution=ADC_RESOLUTION_12BIT,
    .dmaWaterMark=0,
    .dmaEnable=false,
    .sequenceConfig={
        .sequenceMode=ADC_CONV_LOOP,
        .sequenceIntEnable=true,
        .convIntEnable=false,
        .readyIntEnable=false,
        .ovrunIntEnable=false,
        .sampIntEnable=false,
        .channels={
            ADC_INPUTCHAN_EXT2,
            ADC_INPUTCHAN_EXT1,
            ADC_INPUTCHAN_EXT0,
        },
        .totalChannels=3,
    },
    .compareConfig={
        .compareEnable=false,
        .compareAllChannelEnable=false,

        .compHigh=4095,
        .compLow=0,
        .compIntEnable=false,
    },
};


/* adc_config2 */
const adc_converter_config_t adc_config2={
    .clockDivider=0,
    .startTime=48,
    .sampleTime=40,
    .overrunMode=false,
    .autoOffEnable=false,
    .waitEnable=false,
    .trigger=ADC_TRIGGER_SOFTWARE,
    .align=ADC_ALIGN_RIGHT,
    .resolution=ADC_RESOLUTION_12BIT,
    .dmaWaterMark=0,
    .dmaEnable=false,
    .sequenceConfig={
        .sequenceMode=ADC_CONV_LOOP,
        .sequenceIntEnable=false,
        .convIntEnable=false,
        .readyIntEnable=false,
        .ovrunIntEnable=false,
        .sampIntEnable=false,
        .channels={
            ADC_INPUTCHAN_EXT9,
            ADC_INPUTCHAN_EXT10,
            ADC_INPUTCHAN_EXT11,
        },
        .totalChannels=3,
    },
    .compareConfig={
        .compareEnable=false,
        .compareAllChannelEnable=false,

        .compHigh=4095,
        .compLow=0,
        .compIntEnable=false,
    },
};


