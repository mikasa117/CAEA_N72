/*******************************************************************************
|  File Name:
|  Description:  Implementation of the base Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Zhejiang Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| CHP           Chen Haopeng           CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 2021-08-09    00.00.01     CHP       Creation
|
|******************************************************************************/

#ifndef __SECURITY_KEY_H_
#define __SECURITY_KEY_H_


/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "fr30xx.h"

/*******************************************************************************
|    Compile Option or configuration Section
|******************************************************************************/
/* 安全密钥大小定义 */
#define SECURITY_KEY_SIZE       (16u)  /* 密钥大小 */
#define SECURITY_SEED_SIZE      (8u)  /* 种子大小：16字节 */

/* 安全等级定义 */
#define SECURITY_LEVEL_1        0x01   /* 安全等级1 */
#define SECURITY_LEVEL_11       0x11   /* 安全等级11 */
/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
/*******************************************************************************
|    Table Definition
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/

/* 函数声明 */

/* 获取种子 */
bool GetSeed(const uint32_t i_needRandomDataLen, uint8_t *o_pRandomDataBuf);

/* 检查密钥是否正确 */
uint8_t IsReceivedKeyRight(const uint8_t *i_pReceivedKey, const uint8_t *i_pTxSeed);

/* 根据安全等级生成密钥 */
bool GenerateKey(uint8_t security_level, const uint8_t *seed, uint8_t *key);
/* 生成8字节随机数 */
bool Generate8ByteRandom(uint8_t *o_pRandomDataBuf);
/* 安全算法初始化 */
void security_algorithm_init(void);

/* 调试用：存储MCU计算的Key和种子 */
extern uint8_t g_DebugExpectedKey[16];
extern uint8_t g_DebugFullSeed[16];
 extern uint8_t g_FixedSeed[8];

#endif