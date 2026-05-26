#ifndef CANAPPCFG_H
#define CANAPPCFG_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Vector_Platform_Types.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
// CAN Controller Configuration
/*Tseg1 = 70
Tseg2 = 23
Sjw = 23（同步跳转宽度，通常设置为Tseg2的值）
Prescaler = 0
采样点(%) = (1 + Tseg1) / (1 + Tseg1 + Tseg2) × 100%
= (1 + 36) / (1 + 36 + 9) × 100%
= 37 / 46 × 100%
≈ 80%
时钟频率 = 波特率 × [(1 + Tseg1 + Tseg2) × (Prescaler + 1)]
= 500,000 × [(1 + 36 + 9) × (1 + 1)]
= 500,000 × 92
= 46,000,000 Hz = 46 MHz

采样点：80%
时钟频率：46MHz
波特率：500kbps (46MHz/92)*/
#define CAN_CONTROLLER_TYPE    OMX146N
#define CAN_BAUDRATE          500000  // 500kbps
#define CAN_SAMPLE_POINT      80      // 采样点80%
#define CAN_TRANSCEIVER_TYPE  144     // CAN收发器型号

// Message Timeouts (in milliseconds)
#define MSG_TIMEOUT_BCM_MuxInfo_L  50    // 0x18FFC321
#define MSG_TIMEOUT_TBOX_TD        500   // 0x18FF9DF1
#define MSG_TIMEOUT_TD             500   // 0x18FEE6EE
#define MSG_TIMEOUT_BCM_VDHR       500   // 0x18FEC1EE
#define MSG_TIMEOUT_EBC2           100   // 0x18FEBF0B
#define MSG_TIMEOUT_EEC1           100   // 0xCF00400
#define MSG_TIMEOUT_BCM_StsBcan    100   // 0xA18A000

// Network Management Configuration
#define NM_TIMEOUT_COUNT           50    // 50ms
#define BUSOFF_RECOVERY_TIME       50    // 50ms
#define MAX_BUSOFF_COUNT           3     // Maximum Bus-off occurrences before error

// Diagnostic Configuration
#define DIAG_REQUEST_TIMEOUT       5000  // 5s timeout for diagnostic requests
#define SECURITY_ACCESS_DELAY      10    // 10ms delay between security access attempts

// Buffer Sizes
#define RX_BUFFER_SIZE            10
#define TX_BUFFER_SIZE            8

extern boolean ModeC_judge(void);
extern void  DMM_CalculateChecksum(void);
extern unsigned char DMM_CheckE2EStatus(uint8 *data, uint8 len);
extern uint8 Message_GetCheckSum(const uint8 *xData, uint16 xDataLen);
/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

#endif /* CANAPPCFG_H */ 
