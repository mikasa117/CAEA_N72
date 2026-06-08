/*
 * Copyright 2020-2026 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * @file fee_config.h
 * @brief 
 * 
 */




#ifndef __FEE_CONFIG_H__
#define __FEE_CONFIG_H__



#include "fee.h"

#define FLS_CONFIGURED_SECTOR_NUMBER 8U/*Count of user configuration flash sectors*/
#define FEE_NUMBER_OF_CLUSTER_GROUPS 2U  /* Number of configured Fee cluster group */
#define FEE_CRT_CFG_NR_OF_BLOCKS  8U /* Number of configured Fee blocks */


/* Symbolic names of configured Fee blocks */
#define FEE_BLOCK_1      (1U)
#define FEE_BLOCK_2      (16U)
#define FEE_BLOCK_3      (32U)
#define FEE_BLOCK_4      (48U)
#define FEE_BLOCK_5      (64U)
#define FEE_BLOCK_6      (80U)
#define FEE_BLOCK_7      (96U)
#define FEE_BLOCK_8      (112U)




extern const Fee_ModuleUserConfig_t FEEGenConfig;

#endif


