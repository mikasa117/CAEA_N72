/*
 * Copyright 2020-2026 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * @file wdg_config.c
 * @brief 
 * 
 */



#include "wdg_config.h"


/*wdg_config0*/
const wdg_user_config_t wdg_config0 = {
    .clockSource=WDG_SIRC_CLOCK,
    .opMode={
        .deepsleep=false,
        .debug=false,
    },
    .updateEnable=true,
    .intEnable=false,
    .winEnable=false,
    .windowValue=0,
    .timeoutValue=600000,
    .apbErrorResetEnable=0,
};

