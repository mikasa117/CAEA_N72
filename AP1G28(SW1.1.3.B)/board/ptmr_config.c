/*
 * Copyright 2020-2026 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * @file ptmr_config.c
 * @brief 
 * 
 */


#include "ptmr_config.h"

const ptmr_user_channel_config_t ptmr_channel_0={
    .periodUnits=pTMR_PERIOD_UNITS_MICROSECONDS,
    .period=500,
    .chainChannel=false,
    .isInterruptEnabled=true,
};
const ptmr_user_channel_config_t ptmr_channel_1={
    .periodUnits=pTMR_PERIOD_UNITS_MICROSECONDS,
    .period=107374182,
    .chainChannel=false,
    .isInterruptEnabled=true,
};

const ptmr_user_config_t PTMR_Config={
    .enableRunInDebug=false,
};

