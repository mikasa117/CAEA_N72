/*
 * Copyright 2020-2026 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * @file etmr_config.c
 * @brief 
 * 
 */


#include <stddef.h>
#include "etmr_config.h"

/*
 * Common
*/

etmr_pwm_sync_t ETMR_CM_Config0PwmSync={
    .regSyncFreq=1,
    .regSyncSel=REG_SYNC_WITH_MOD,
    .cntInitSyncSel=CNT_SYNC_WITH_REG,
    .maskOutputSyncSel=CHMASK_SYNC_WITH_REG,
    .regSyncTrigSrc=DISABLE_TRIGGER,
    .cntInitSyncTrigSrc=DISABLE_TRIGGER,
    .maskOutputSyncTrigSrc=DISABLE_TRIGGER,
    .hwTrigFromTmuEnable=false,
    .hwTrigFromCimEnable=false,
    .hwTrigFromPadEnable=false,
};


etmr_trig_config_t ETMR_CM_Config0TrigConf={
    .trigSrc=TRIGGER_FROM_MATCHING_EVENT,
    .pwmOutputChannel=0,
    .outputTrigWidth=0,
    .outputTrigFreq=1,
    .modMatchTrigEnable=true,
    .midMatchTrigEnable=false,
    .initMatchTrigEnable=false,
    .numOfChannels=0,
    .channelTrigParamConfig=NULL,
};

etmr_user_config_t ETMR_CM_Config0={
    .etmrClockSource=eTMR_CLOCK_SOURCE_INTERNALCLK,
    .etmrPrescaler=1,
    .debugMode=false,
    .syncMethod=&ETMR_CM_Config0PwmSync,
    .outputTrigConfig=&ETMR_CM_Config0TrigConf,
    .isTofIntEnabled=false,
};

etmr_state_t ETMR_CM_Config0_State;


etmr_pwm_sync_t ETMR_CM_Config1PwmSync={
    .regSyncFreq=1,
    .regSyncSel=REG_SYNC_WITH_MOD,
    .cntInitSyncSel=CNT_SYNC_WITH_REG,
    .maskOutputSyncSel=CHMASK_SYNC_WITH_REG,
    .regSyncTrigSrc=DISABLE_TRIGGER,
    .cntInitSyncTrigSrc=DISABLE_TRIGGER,
    .maskOutputSyncTrigSrc=DISABLE_TRIGGER,
    .hwTrigFromTmuEnable=false,
    .hwTrigFromCimEnable=false,
    .hwTrigFromPadEnable=false,
};


etmr_trig_config_t ETMR_CM_Config1TrigConf={
    .trigSrc=TRIGGER_FROM_MATCHING_EVENT,
    .pwmOutputChannel=0,
    .outputTrigWidth=0,
    .outputTrigFreq=1,
    .modMatchTrigEnable=false,
    .midMatchTrigEnable=false,
    .initMatchTrigEnable=false,
    .numOfChannels=0,
    .channelTrigParamConfig=NULL,
};

etmr_user_config_t ETMR_CM_Config1={
    .etmrClockSource=eTMR_CLOCK_SOURCE_INTERNALCLK,
    .etmrPrescaler=2,
    .debugMode=false,
    .syncMethod=&ETMR_CM_Config1PwmSync,
    .outputTrigConfig=&ETMR_CM_Config1TrigConf,
    .isTofIntEnabled=false,
};

etmr_state_t ETMR_CM_Config1_State;


etmr_pwm_sync_t ETMR_CM_Config2PwmSync={
    .regSyncFreq=1,
    .regSyncSel=REG_SYNC_WITH_MOD,
    .cntInitSyncSel=CNT_SYNC_WITH_REG,
    .maskOutputSyncSel=CHMASK_SYNC_WITH_REG,
    .regSyncTrigSrc=DISABLE_TRIGGER,
    .cntInitSyncTrigSrc=DISABLE_TRIGGER,
    .maskOutputSyncTrigSrc=DISABLE_TRIGGER,
    .hwTrigFromTmuEnable=false,
    .hwTrigFromCimEnable=false,
    .hwTrigFromPadEnable=false,
};


etmr_trig_config_t ETMR_CM_Config2TrigConf={
    .trigSrc=TRIGGER_FROM_MATCHING_EVENT,
    .pwmOutputChannel=0,
    .outputTrigWidth=0,
    .outputTrigFreq=1,
    .modMatchTrigEnable=false,
    .midMatchTrigEnable=false,
    .initMatchTrigEnable=false,
    .numOfChannels=0,
    .channelTrigParamConfig=NULL,
};

etmr_user_config_t ETMR_CM_Config2={
    .etmrClockSource=eTMR_CLOCK_SOURCE_INTERNALCLK,
    .etmrPrescaler=2,
    .debugMode=false,
    .syncMethod=&ETMR_CM_Config2PwmSync,
    .outputTrigConfig=&ETMR_CM_Config2TrigConf,
    .isTofIntEnabled=false,
};

etmr_state_t ETMR_CM_Config2_State;


/*
 * MC
*/


/*
 * PWM
*/

etmr_pwm_ch_param_t ETMR_PWM_Config0IndChConfig[3]={
    {
        .hwChannelId=0,
        .polarity=eTMR_POLARITY_NORMAL,
        .pwmSrcInvert=false,
        .align=eTMR_PWM_CENTER_ALIGN,
        .channelInitVal=0,
        .typeOfUpdate=eTMR_PWM_UPDATE_IN_DUTY_CYCLE,
        .dutyCycle=0x4000,
        .offset=0,
        .enableSecondChannelOutput=true,
        .secondChannelPolarity=eTMR_POLARITY_NORMAL,
        .enableDoubleSwitch=false,
        .evenDeadTime=120,
        .oddDeadTime=120,
    },
    {
        .hwChannelId=2,
        .polarity=eTMR_POLARITY_NORMAL,
        .pwmSrcInvert=false,
        .align=eTMR_PWM_CENTER_ALIGN,
        .channelInitVal=0,
        .typeOfUpdate=eTMR_PWM_UPDATE_IN_DUTY_CYCLE,
        .dutyCycle=0x4000,
        .offset=0,
        .enableSecondChannelOutput=true,
        .secondChannelPolarity=eTMR_POLARITY_NORMAL,
        .enableDoubleSwitch=false,
        .evenDeadTime=120,
        .oddDeadTime=120,
    },
    {
        .hwChannelId=4,
        .polarity=eTMR_POLARITY_NORMAL,
        .pwmSrcInvert=false,
        .align=eTMR_PWM_CENTER_ALIGN,
        .channelInitVal=0,
        .typeOfUpdate=eTMR_PWM_UPDATE_IN_DUTY_CYCLE,
        .dutyCycle=0x4000,
        .offset=0,
        .enableSecondChannelOutput=true,
        .secondChannelPolarity=eTMR_POLARITY_NORMAL,
        .enableDoubleSwitch=false,
        .evenDeadTime=120,
        .oddDeadTime=120,
    },
};


etmr_fault_param_t ETMR_PWM_Config0FaultConfig={
    .pwmFaultInterrupt=false,
    .faultFilterSampleCounter=0,
    .faultFilterSamplePeriod=0,
    .faultInputStrentch=0,
    .pwmRecoveryOpportunity=eTMR_FAULT_PWM_RECOVERY_DISABLED,
    .pwmAutoRecoveryMode=eTMR_MANUAL_CLEAR_FAULT_FLAG_THEN_AUTO_RECOVERY,
    .faultMode=eTMR_FAULT_WITH_CLK,
    .etmrFaultChannelParam=
    {
        {
            .faultChannelEnabled=false,
            .faultInputPolarity=eTMR_FAULT_SIGNAL_HIGH,
        },
        {
            .faultChannelEnabled=false,
            .faultInputPolarity=eTMR_FAULT_SIGNAL_HIGH,
        },
        {
            .faultChannelEnabled=false,
            .faultInputPolarity=eTMR_FAULT_SIGNAL_HIGH,
        },
        {
            .faultChannelEnabled=false,
            .faultInputPolarity=eTMR_FAULT_SIGNAL_HIGH,
        },
    },
    .safeState={
        eTMR_LOW_STATE,
        eTMR_LOW_STATE,
        eTMR_LOW_STATE,
        eTMR_LOW_STATE,
    }
};


etmr_pwm_param_t ETMR_PWM_Config0={
    .nNumPwmChannels=3,
    .mode=eTMR_PWM_MODE,
    .uFrequencyHZ=16000,
    .counterInitValFromInitReg=true,
    .cntVal=0,
    .pwmChannelConfig=ETMR_PWM_Config0IndChConfig,
    .faultConfig=&ETMR_PWM_Config0FaultConfig,
};

etmr_pwm_ch_param_t ETMR_PWM_Config1IndChConfig[3]={
    {
        .hwChannelId=1,
        .polarity=eTMR_POLARITY_NORMAL,
        .pwmSrcInvert=false,
        .align=eTMR_PWM_RIGHT_EDGE_ALIGN,
        .channelInitVal=0,
        .typeOfUpdate=eTMR_PWM_UPDATE_IN_DUTY_CYCLE,
        .dutyCycle=0x0000,
        .offset=0,
        .enableSecondChannelOutput=false,
        .secondChannelPolarity=eTMR_POLARITY_NORMAL,
        .enableDoubleSwitch=false,
        .evenDeadTime=0,
        .oddDeadTime=0,
    },
    {
        .hwChannelId=2,
        .polarity=eTMR_POLARITY_NORMAL,
        .pwmSrcInvert=false,
        .align=eTMR_PWM_RIGHT_EDGE_ALIGN,
        .channelInitVal=0,
        .typeOfUpdate=eTMR_PWM_UPDATE_IN_DUTY_CYCLE,
        .dutyCycle=0x0000,
        .offset=0,
        .enableSecondChannelOutput=false,
        .secondChannelPolarity=eTMR_POLARITY_NORMAL,
        .enableDoubleSwitch=false,
        .evenDeadTime=0,
        .oddDeadTime=0,
    },
    {
        .hwChannelId=3,
        .polarity=eTMR_POLARITY_NORMAL,
        .pwmSrcInvert=false,
        .align=eTMR_PWM_RIGHT_EDGE_ALIGN,
        .channelInitVal=0,
        .typeOfUpdate=eTMR_PWM_UPDATE_IN_DUTY_CYCLE,
        .dutyCycle=0x0000,
        .offset=0,
        .enableSecondChannelOutput=false,
        .secondChannelPolarity=eTMR_POLARITY_NORMAL,
        .enableDoubleSwitch=false,
        .evenDeadTime=0,
        .oddDeadTime=0,
    },
};


etmr_fault_param_t ETMR_PWM_Config1FaultConfig={
    .pwmFaultInterrupt=false,
    .faultFilterSampleCounter=0,
    .faultFilterSamplePeriod=0,
    .faultInputStrentch=0,
    .pwmRecoveryOpportunity=eTMR_FAULT_PWM_RECOVERY_DISABLED,
    .pwmAutoRecoveryMode=eTMR_MANUAL_CLEAR_FAULT_FLAG_THEN_AUTO_RECOVERY,
    .faultMode=eTMR_FAULT_WITH_CLK,
    .etmrFaultChannelParam=
    {
        {
            .faultChannelEnabled=false,
            .faultInputPolarity=eTMR_FAULT_SIGNAL_HIGH,
        },
        {
            .faultChannelEnabled=false,
            .faultInputPolarity=eTMR_FAULT_SIGNAL_HIGH,
        },
        {
            .faultChannelEnabled=false,
            .faultInputPolarity=eTMR_FAULT_SIGNAL_HIGH,
        },
        {
            .faultChannelEnabled=false,
            .faultInputPolarity=eTMR_FAULT_SIGNAL_HIGH,
        },
    },
    .safeState={
        eTMR_LOW_STATE,
        eTMR_LOW_STATE,
        eTMR_LOW_STATE,
        eTMR_LOW_STATE,
    }
};


etmr_pwm_param_t ETMR_PWM_Config1={
    .nNumPwmChannels=3,
    .mode=eTMR_PWM_MODE,
    .uFrequencyHZ=1000,
    .counterInitValFromInitReg=true,
    .cntVal=0,
    .pwmChannelConfig=ETMR_PWM_Config1IndChConfig,
    .faultConfig=&ETMR_PWM_Config1FaultConfig,
};

etmr_pwm_ch_param_t ETMR_PWM_Config2IndChConfig[3]={
    {
        .hwChannelId=0,
        .polarity=eTMR_POLARITY_NORMAL,
        .pwmSrcInvert=false,
        .align=eTMR_PWM_RIGHT_EDGE_ALIGN,
        .channelInitVal=0,
        .typeOfUpdate=eTMR_PWM_UPDATE_IN_DUTY_CYCLE,
        .dutyCycle=0x0000,
        .offset=0,
        .enableSecondChannelOutput=false,
        .secondChannelPolarity=eTMR_POLARITY_NORMAL,
        .enableDoubleSwitch=false,
        .evenDeadTime=0,
        .oddDeadTime=0,
    },
    {
        .hwChannelId=1,
        .polarity=eTMR_POLARITY_NORMAL,
        .pwmSrcInvert=false,
        .align=eTMR_PWM_RIGHT_EDGE_ALIGN,
        .channelInitVal=0,
        .typeOfUpdate=eTMR_PWM_UPDATE_IN_DUTY_CYCLE,
        .dutyCycle=0x0000,
        .offset=0,
        .enableSecondChannelOutput=false,
        .secondChannelPolarity=eTMR_POLARITY_NORMAL,
        .enableDoubleSwitch=false,
        .evenDeadTime=0,
        .oddDeadTime=0,
    },
    {
        .hwChannelId=2,
        .polarity=eTMR_POLARITY_NORMAL,
        .pwmSrcInvert=false,
        .align=eTMR_PWM_RIGHT_EDGE_ALIGN,
        .channelInitVal=0,
        .typeOfUpdate=eTMR_PWM_UPDATE_IN_DUTY_CYCLE,
        .dutyCycle=0x0000,
        .offset=0,
        .enableSecondChannelOutput=false,
        .secondChannelPolarity=eTMR_POLARITY_NORMAL,
        .enableDoubleSwitch=false,
        .evenDeadTime=0,
        .oddDeadTime=0,
    },
};


etmr_fault_param_t ETMR_PWM_Config2FaultConfig={
    .pwmFaultInterrupt=false,
    .faultFilterSampleCounter=0,
    .faultFilterSamplePeriod=0,
    .faultInputStrentch=0,
    .pwmRecoveryOpportunity=eTMR_FAULT_PWM_RECOVERY_DISABLED,
    .pwmAutoRecoveryMode=eTMR_MANUAL_CLEAR_FAULT_FLAG_THEN_AUTO_RECOVERY,
    .faultMode=eTMR_FAULT_WITH_CLK,
    .etmrFaultChannelParam=
    {
        {
            .faultChannelEnabled=false,
            .faultInputPolarity=eTMR_FAULT_SIGNAL_HIGH,
        },
        {
            .faultChannelEnabled=false,
            .faultInputPolarity=eTMR_FAULT_SIGNAL_HIGH,
        },
        {
            .faultChannelEnabled=false,
            .faultInputPolarity=eTMR_FAULT_SIGNAL_HIGH,
        },
        {
            .faultChannelEnabled=false,
            .faultInputPolarity=eTMR_FAULT_SIGNAL_HIGH,
        },
    },
    .safeState={
        eTMR_LOW_STATE,
        eTMR_LOW_STATE,
        eTMR_LOW_STATE,
        eTMR_LOW_STATE,
    }
};


etmr_pwm_param_t ETMR_PWM_Config2={
    .nNumPwmChannels=3,
    .mode=eTMR_PWM_MODE,
    .uFrequencyHZ=1000,
    .counterInitValFromInitReg=true,
    .cntVal=0,
    .pwmChannelConfig=ETMR_PWM_Config2IndChConfig,
    .faultConfig=&ETMR_PWM_Config2FaultConfig,
};


/*
 * IC
*/


/*
 * OC
*/


/*
 * QD
*/


