/*******************************************************************************
|  File Name:
|  Description:
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Zhejiang Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| FSL           fengshulin           CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2023-02-02    01.00.00     fsl       Creation
|
|******************************************************************************/
/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "security_key.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "fdb_def.h"
#include "fdb_app.h"
#include "base.h"
#include "Appl_DID_Callback.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/

#define getSBoxValue(num) (sbox[(num)])
/*******************************************************************************
|    Enum Definition
|******************************************************************************/

extern V_MEMROM0 V_MEMROM1 tFblHeader V_MEMROM2* FblHeader;
/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
 uint8_t g_FixedSeed[8] = {0};
 
/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/
/* 固定PKC值（AES密钥） - "0hojwaJEWSbvkmAE" */

static uint8_t g_FixedPKC[16] = {
    0x30, 0x68, 0x6F, 0x6A, 0x77, 0x61, 0x4A, 0x45,
    0x57, 0x53, 0x62, 0x76, 0x6B, 0x6D, 0x41, 0x45
};

/* 固定种子值 - 16字节 */
/*static const uint8_t g_FixedSeed[16] = {
    0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
    0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88
};*/
	
static const uint8_t sbox[256] = {
    0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
    0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
    0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
    0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
    0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
    0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
    0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
    0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
    0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
    0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
    0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
    0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
    0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
    0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
    0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
    0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16
};

static const uint8_t Rcon[11] = {0x8d,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36};
/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/

/*******************************************************************************
|    Extern functions declaration
|******************************************************************************/

/*******************************************************************************
|    Extern variables declaration
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/

/*============================================================================
 * Tiny-AES-128 (经过验证的实现)
 *============================================================================*/

/*******************************************************************************
Name            :
Syntax          :
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : None                      :-
Parameters(out) : None                      :-
Return value    : None                      :-
Description     : Initialize RAM Data
Call By         :
|******************************************************************************/
static void KeyExpansion(uint8_t* RoundKey, const uint8_t* Key) {
    uint8_t tempa[4];
    unsigned i = 0;
    
    for (i = 0; i < 4; ++i) {
        RoundKey[(i * 4) + 0] = Key[(i * 4) + 0];
        RoundKey[(i * 4) + 1] = Key[(i * 4) + 1];
        RoundKey[(i * 4) + 2] = Key[(i * 4) + 2];
        RoundKey[(i * 4) + 3] = Key[(i * 4) + 3];
    }
    
    for (i = 4; i < 44; ++i) {
        {
            tempa[0] = RoundKey[(i-1) * 4 + 0];
            tempa[1] = RoundKey[(i-1) * 4 + 1];
            tempa[2] = RoundKey[(i-1) * 4 + 2];
            tempa[3] = RoundKey[(i-1) * 4 + 3];
        }
        
        if (i % 4 == 0) {
            uint8_t u8tmp = tempa[0];
            tempa[0] = tempa[1];
            tempa[1] = tempa[2];
            tempa[2] = tempa[3];
            tempa[3] = u8tmp;
            
            tempa[0] = getSBoxValue(tempa[0]);
            tempa[1] = getSBoxValue(tempa[1]);
            tempa[2] = getSBoxValue(tempa[2]);
            tempa[3] = getSBoxValue(tempa[3]);
            
            tempa[0] = tempa[0] ^ Rcon[i/4];
        }
        
        RoundKey[i * 4 + 0] = RoundKey[(i - 4) * 4 + 0] ^ tempa[0];
        RoundKey[i * 4 + 1] = RoundKey[(i - 4) * 4 + 1] ^ tempa[1];
        RoundKey[i * 4 + 2] = RoundKey[(i - 4) * 4 + 2] ^ tempa[2];
        RoundKey[i * 4 + 3] = RoundKey[(i - 4) * 4 + 3] ^ tempa[3];
    }
}
/*******************************************************************************
Name            :
Syntax          :
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : None                      :-
Parameters(out) : None                      :-
Return value    : None                      :-
Description     : Initialize RAM Data
Call By         :
|******************************************************************************/
static void AddRoundKey(uint8_t round, uint8_t* state, const uint8_t* RoundKey) {
    for (uint8_t i = 0; i < 16; ++i) {
        state[i] ^= RoundKey[(round * 16) + i];
    }
}
/*******************************************************************************
Name            :
Syntax          :
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : None                      :-
Parameters(out) : None                      :-
Return value    : None                      :-
Description     : Initialize RAM Data
Call By         :
|******************************************************************************/
static void SubBytes(uint8_t* state) {
    for (uint8_t i = 0; i < 16; ++i) {
        state[i] = getSBoxValue(state[i]);
    }
}
/*******************************************************************************
Name            :
Syntax          :
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : None                      :-
Parameters(out) : None                      :-
Return value    : None                      :-
Description     : Initialize RAM Data
Call By         :
|******************************************************************************/
static void ShiftRows(uint8_t* state) {
    uint8_t temp;
    
    temp = state[1]; state[1] = state[5]; state[5] = state[9]; state[9] = state[13]; state[13] = temp;
    
    temp = state[2]; state[2] = state[10]; state[10] = temp;
    temp = state[6]; state[6] = state[14]; state[14] = temp;
    
    temp = state[3]; state[3] = state[15]; state[15] = state[11]; state[11] = state[7]; state[7] = temp;
}
/*******************************************************************************
Name            :
Syntax          :
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : None                      :-
Parameters(out) : None                      :-
Return value    : None                      :-
Description     : Initialize RAM Data
Call By         :
|******************************************************************************/
static uint8_t xtime(uint8_t x) {
    return ((x << 1) ^ (((x >> 7) & 1) * 0x1b));
}
/*******************************************************************************
Name            :
Syntax          :
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : None                      :-
Parameters(out) : None                      :-
Return value    : None                      :-
Description     : Initialize RAM Data
Call By         :
|******************************************************************************/
static void MixColumns(uint8_t* state) {
    uint8_t Tmp, Tm, t;
    for (uint8_t i = 0; i < 4; ++i) {
        t   = state[i*4+0];
        Tmp = state[i*4+0] ^ state[i*4+1] ^ state[i*4+2] ^ state[i*4+3];
        Tm  = state[i*4+0] ^ state[i*4+1]; Tm = xtime(Tm); state[i*4+0] ^= Tm ^ Tmp;
        Tm  = state[i*4+1] ^ state[i*4+2]; Tm = xtime(Tm); state[i*4+1] ^= Tm ^ Tmp;
        Tm  = state[i*4+2] ^ state[i*4+3]; Tm = xtime(Tm); state[i*4+2] ^= Tm ^ Tmp;
        Tm  = state[i*4+3] ^ t;            Tm = xtime(Tm); state[i*4+3] ^= Tm ^ Tmp;
    }
}
/*******************************************************************************
Name            :
Syntax          :
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : None                      :-
Parameters(out) : None                      :-
Return value    : None                      :-
Description     : Initialize RAM Data
Call By         :
|******************************************************************************/
static void Cipher(uint8_t* state, const uint8_t* RoundKey) {
    AddRoundKey(0, state, RoundKey);
    
    for (uint8_t round = 1; round < 10; ++round) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(round, state, RoundKey);
    }
    
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(10, state, RoundKey);
}
/*******************************************************************************
Name            :
Syntax          :
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : None                      :-
Parameters(out) : None                      :-
Return value    : None                      :-
Description     : Initialize RAM Data
Call By         :
|******************************************************************************/
static void AES128_ECB_encrypt(const uint8_t* input, const uint8_t* key, uint8_t* output) {
    static uint8_t RoundKey[176];  /* 使用静态数组避免栈溢出 */
    
    KeyExpansion(RoundKey, key);
    memcpy(output, input, 16);
    Cipher(output, RoundKey);
}

/*============================================================================
 * AES-CMAC (RFC 4493)
 *============================================================================*/
/*******************************************************************************
Name            :
Syntax          :
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : None                      :-
Parameters(out) : None                      :-
Return value    : None                      :-
Description     : Initialize RAM Data
Call By         :
|******************************************************************************/
static void xor_block(uint8_t* a, const uint8_t* b) {
    for (int i = 0; i < 16; i++) a[i] ^= b[i];
}
/*******************************************************************************
Name            :
Syntax          :
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : None                      :-
Parameters(out) : None                      :-
Return value    : None                      :-
Description     : Initialize RAM Data
Call By         :
|******************************************************************************/
static void leftshift_onebit(uint8_t* out, const uint8_t* in) {
    uint8_t overflow = 0;
    for (int i = 15; i >= 0; i--) {
        out[i] = (in[i] << 1) | overflow;
        overflow = (in[i] >> 7) & 1;
    }
}
/*******************************************************************************
Name            :
Syntax          :
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : None                      :-
Parameters(out) : None                      :-
Return value    : None                      :-
Description     : Initialize RAM Data
Call By         :
|******************************************************************************/
static void generate_subkey(const uint8_t* key, uint8_t* K1, uint8_t* K2) {
    uint8_t L[16] = {0};
    
    AES128_ECB_encrypt(L, key, L);
    
    leftshift_onebit(K1, L);
    if (L[0] & 0x80) K1[15] ^= 0x87;
    
    leftshift_onebit(K2, K1);
    if (K1[0] & 0x80) K2[15] ^= 0x87;
}
/*******************************************************************************
Name            :
Syntax          :
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : None                      :-
Parameters(out) : None                      :-
Return value    : None                      :-
Description     : Initialize RAM Data
Call By         :
|******************************************************************************/
static void AES_CMAC(const uint8_t* key, const uint8_t* input, uint32_t length, uint8_t* mac) {
    uint8_t K1[16], K2[16];
    uint8_t M_last[16], padded[16];
    uint8_t X[16], Y[16];
    uint32_t n, flag;
    
    /* 初始化所有数组 */
    memset(K1, 0, 16);
    memset(K2, 0, 16);
    memset(M_last, 0, 16);
    memset(padded, 0, 16);
    memset(X, 0, 16);
    memset(Y, 0, 16);
    generate_subkey(key, K1, K2);
    
    n = (length + 15) / 16;
    if (n == 0) { n = 1; flag = 0; }
    else { flag = ((length % 16) == 0) ? 1 : 0; }
    
    if (flag) {
        memcpy(M_last, &input[16*(n-1)], 16);
        xor_block(M_last, K1);
    } else {
        uint32_t last_len = length % 16;
        memset(padded, 0, 16);
        memcpy(padded, &input[16*(n-1)], last_len);
        padded[last_len] = 0x80;
        memcpy(M_last, padded, 16);
        xor_block(M_last, K2);
    }
    
    for (uint32_t i = 0; i < n-1; i++) {
        memcpy(Y, X, 16);
        xor_block(Y, &input[16*i]);
        AES128_ECB_encrypt(Y, key, X);
    }
    
    memcpy(Y, X, 16);
    xor_block(Y, M_last);
    AES128_ECB_encrypt(Y, key, mac);
}

/*============================================================================
 * 安全访问接口
 *============================================================================*/

/* 调试用：存储MCU计算的Key */
uint8_t g_DebugExpectedKey[16] = {0};
uint8_t g_DebugFullSeed[16] = {0};

//void security_algorithm_init(void) {}
//////////////
/* 随机数生成器状态 */
static uint8_t g_rng_state[16] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0, 
                                  0x0f, 0xed, 0xcb, 0xa9, 0x87, 0x65, 0x43, 0x21};
static uint32_t g_rng_counter = 0;
																	
/*******************************************************************************
Name            :
Syntax          :
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : None                      :-
Parameters(out) : None                      :-
Return value    : None                      :-
Description     : Initialize RAM Data
Call By         :
|******************************************************************************/																	
void security_algorithm_init(void) {
    /* 可以在这里添加随机数生成器的初始化代码 */
}
/*******************************************************************************
Name            :
Syntax          :
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : None                      :-
Parameters(out) : None                      :-
Return value    : None                      :-
Description     : Initialize RAM Data
Call By         :
|******************************************************************************/
/* 生成8字节随机数 - 基于AES的安全随机数生成器 */
bool Generate8ByteRandom(uint8_t *o_pRandomDataBuf) {
    if (o_pRandomDataBuf == NULL) {
        return false;
    }
    
    uint8_t input[16];
    uint8_t key[16];
    uint8_t temp[16];
		
		//FblHeader->pApplFblNvReadLevel1PkcNumber(g_FixedPKC,16);
		FblHeader->pApplFblNvLevel1PkcNumber(g_FixedPKC,1,DID_D135_LEN,2);
    
    /* 使用计数器和当前状态作为输入 */
    memcpy(input, g_rng_state, 16);
    input[0] ^= (uint8_t)(g_rng_counter >> 24);
    input[1] ^= (uint8_t)(g_rng_counter >> 16);
    input[2] ^= (uint8_t)(g_rng_counter >> 8);
    input[3] ^= (uint8_t)(g_rng_counter);
    
    /* 使用固定PKC和计数器生成动态密钥 */
    memcpy(key, g_FixedPKC, 16);
    key[4] ^= (uint8_t)(g_rng_counter >> 24);
    key[5] ^= (uint8_t)(g_rng_counter >> 16);
    key[6] ^= (uint8_t)(g_rng_counter >> 8);
    key[7] ^= (uint8_t)(g_rng_counter);
    
    /* 使用AES加密生成随机数 */
    AES128_ECB_encrypt(input, key, temp);
    
    /* 更新状态和计数器 */
    memcpy(g_rng_state, temp, 16);
    g_rng_counter++;
    
    /* 仅输出8字节 */
    memcpy(o_pRandomDataBuf, temp, 8);
    
    return true;
}
/*******************************************************************************
Name            :
Syntax          :
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : None                      :-
Parameters(out) : None                      :-
Return value    : None                      :-
Description     : Initialize RAM Data
Call By         :
|******************************************************************************/
bool GetSeed(const uint32_t i_needRandomDataLen, uint8_t *o_pRandomDataBuf) {
    if (o_pRandomDataBuf == NULL || i_needRandomDataLen > SECURITY_SEED_SIZE) return false;
    
    /* 使用随机数生成器生成种子 */
    if (!Generate8ByteRandom(g_FixedSeed)) {
        return false;
    }
    
    memcpy(o_pRandomDataBuf, g_FixedSeed, i_needRandomDataLen);
    return true;
}
/*******************************************************************************
Name            :
Syntax          :
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : None                      :-
Parameters(out) : None                      :-
Return value    : None                      :-
Description     : Initialize RAM Data
Call By         :
|******************************************************************************/
uint8_t IsReceivedKeyRight(const uint8_t *i_pReceivedKey, const uint8_t *i_pTxSeed) {
    if (i_pReceivedKey == NULL || i_pTxSeed == NULL) return 1;
    
    /* 保存种子用于调试 */
    memcpy(g_DebugFullSeed, i_pTxSeed, 16);
	
   // FblHeader->pApplFblNvReadLevel1PkcNumber(g_FixedPKC,16);
	FblHeader->pApplFblNvLevel1PkcNumber(g_FixedPKC,1,DID_D135_LEN,2);
    /* i_pTxSeed现在是16字节: 请求的8字节 + 响应的8字节 */
    AES_CMAC(g_FixedPKC, i_pTxSeed, 16, g_DebugExpectedKey);
    return (memcmp(i_pReceivedKey, g_DebugExpectedKey, 16) == 0) ? 0 : 1;
}
/*******************************************************************************
Name            :
Syntax          :
Sync/Async      : Synchronous
Reentrancy      :
Parameters(in)  : None                      :-
Parameters(out) : None                      :-
Return value    : None                      :-
Description     : Initialize RAM Data
Call By         :
|******************************************************************************/
bool GenerateKey(uint8_t security_level, const uint8_t *seed, uint8_t *key) {
    if (seed == NULL || key == NULL) return false;
    /* seed现在是16字节: 请求的8字节 + 响应的8字节 */
	 // FblHeader->pApplFblNvReadLevel1PkcNumber(g_FixedPKC,16);
	FblHeader->pApplFblNvLevel1PkcNumber(g_FixedPKC,1,DID_D135_LEN,2);
    AES_CMAC(g_FixedPKC, seed, 16, key);
    return true;
}

