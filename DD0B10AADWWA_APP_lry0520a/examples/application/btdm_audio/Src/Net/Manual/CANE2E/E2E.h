/**
 * @file E2E.h
 * @brief E2E(End-to-End)通信保护机制的头文件
 * @details 实现了基于计数器和CRC8校验的通信保护机制
 */

#ifndef _E2E_H_
#define _E2E_H_

/** @brief E2E状态掩码 - 计数器检查失败 */
#define E2E_ALIVEOUNT_FAILED 0x01
/** @brief E2E状态掩码 - CRC校验失败 */
#define E2E_CHECKSUM_FAILED  0x02
/** @brief E2E状态掩码 - 未初始化状态 */
#define E2E_UNINIT           0x04

/**
 * @brief E2E信息结构体
 * @details 用于存储E2E通信保护的状态信息
 */
typedef struct{
  unsigned char count;     /**< 计数器值(0-15) */
  unsigned char stateMask; /**< 状态掩码，用于标识通信状态 */
}E2E_Info_t;

/**
 * @brief 初始化E2E信息结构体
 * @param e2eInfo 指向E2E信息结构体的指针
 */
extern void E2E_InfoInit(E2E_Info_t *e2eInfo);

/**
 * @brief 预发送处理函数
 * @param e2eInfo 指向E2E信息结构体的指针
 * @param count 计数器指针，用于存储计算后的计数器值
 * @param checksum CRC校验和指针，用于存储计算后的校验和
 * @param pData 待发送数据的指针
 * @param length 数据长度
 */
extern void E2E_PreTransmit(E2E_Info_t *e2eInfo, unsigned char *count, unsigned char *checksum, unsigned char *pData, unsigned short length);

/**
 * @brief 发送确认函数
 * @param e2eInfo 指向E2E信息结构体的指针
 * @details 发送成功后更新计数器值
 */
extern void E2E_TransmitConfirmation(E2E_Info_t *e2eInfo);

/**
 * @brief 预拷贝检查函数
 * @param e2eInfo 指向E2E信息结构体的指针
 * @param count 接收到的计数器值
 * @param checksum 接收到的CRC校验和
 * @param pData 接收到的数据指针
 * @param length 数据长度
 * @details 检查计数器值和CRC校验和，更新状态掩码
 */
extern void E2E_PreCopyCheck(E2E_Info_t *e2eInfo, unsigned char count, unsigned char checksum, unsigned char *pData, unsigned short length);

/**
 * @brief 获取E2E状态
 * @param e2eInfo 指向E2E信息结构体的指针
 * @return 返回当前E2E状态掩码
 */
extern unsigned char E2E_GetE2EState(E2E_Info_t *e2eInfo);

/**
 * @brief 计算CRC8校验和
 * @param polynomial CRC多项式
 * @param initial 初始值
 * @param xorValue 异或值
 * @param pData 数据指针
 * @param length 数据长度
 * @return 返回计算得到的CRC8校验和
 */
extern unsigned char calcCRC8(unsigned char polynomial, unsigned char initial, unsigned char xorValue, unsigned char *pData, unsigned short length);

#endif
