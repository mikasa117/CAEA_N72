/*
 * Copyright 2020-2026 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * @file etmr_config.h
 * @brief 
 * 
 */




#ifndef __ETMR_CONFIG_H__
#define __ETMR_CONFIG_H__



#include "etmr_common.h"


#include "etmr_pwm_driver.h"





/*
 * Common
*/
extern etmr_user_config_t ETMR_CM_Config0;
extern etmr_state_t ETMR_CM_Config0_State;
extern etmr_user_config_t ETMR_CM_Config1;
extern etmr_state_t ETMR_CM_Config1_State;
extern etmr_user_config_t ETMR_CM_Config2;
extern etmr_state_t ETMR_CM_Config2_State;


/*
 * MC
*/


/*
 * PWM
*/
extern etmr_pwm_param_t ETMR_PWM_Config0;
extern etmr_pwm_param_t ETMR_PWM_Config1;
extern etmr_pwm_param_t ETMR_PWM_Config2;


/*
 * IC
*/


/*
 * OC
*/



/*
 * QD
*/

#endif


