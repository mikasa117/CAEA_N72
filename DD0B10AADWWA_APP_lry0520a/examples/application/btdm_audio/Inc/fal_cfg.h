/*
 * @Author: BlueboxChamil
 * @Date: 2026-01-28 10:59:45
 * @LastEditTime: 2026-04-08 11:08:57
 * @FilePath: \examples\application\btdm_audio\Inc\fal_cfg.h
 * @Description:
 * Copyright (c) 2026 by BlueboxChamil, All Rights Reserved.
 */
/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     armink       the first version
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#define FAL_DEBUG 1
#define FAL_PART_HAS_TABLE_CFG
#define FAL_USING_SFUD_PORT

#define NOR_FLASH_DEV_NAME "norflash0"

/* ===================== Flash device Configuration ========================= */
extern const struct fal_flash_dev onchip_flash;
extern const struct fal_flash_dev flash_w25qxx;
// extern struct fal_flash_dev nor_flash0;

/* flash device table */
#define FAL_FLASH_DEV_TABLE \
    {                       \
        &onchip_flash,      \
    }
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
// #define FAL_PART_TABLE                                                                  \
//     {                                                                                   \
//         {FAL_PART_MAGIC_WORD, "FlashEnv", "flashdb_onchip", 1012 * 1024, 12 * 1024, 0}, \
//         {FAL_PART_MAGIC_WORD, "ExtEnv", "flash_w25qxx", 112 * 1024, 400 * 1024, 0},       \
//     }
// #endif /* FAL_PART_HAS_TABLE_CFG */

#define FAL_PART_TABLE                                                                  \
    {                                                                                   \
        {FAL_PART_MAGIC_WORD, "FlashEnv", "flashdb_onchip", 960 * 1024, 12 * 1024, 0}, \
    }
#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */
