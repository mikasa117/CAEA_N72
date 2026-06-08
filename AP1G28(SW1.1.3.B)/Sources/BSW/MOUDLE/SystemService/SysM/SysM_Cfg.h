/*******************************************************************************
|  File Name:  SysM_Cfg.h
|  Description:  Implementation of the System Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
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
| 2021-05-18    00.00.01     CHP       Creation
|******************************************************************************/

#ifndef _SYSM_CFG_H_
#define _SYSM_CFG_H_

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "CanApp.h"
#include "STD_EepM.h"
#include "STD_McuIf.h"
#include "HwIO.h"
/*******************************************************************************
|    Compile Option or configuration Section
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define SYSM_TASK_PERIOD            5u  //5ms

#define SYSM_TIME_INIT2RUN          (500u / SYSM_TASK_PERIOD)           // 500ms
#define SYSM_TIME_PRESLEEP_LIMIT    (500u / SYSM_TASK_PERIOD)           // 500ms
#define SYSM_TIME_PRESLEEP_TIMEOUT  (200000u / SYSM_TASK_PERIOD)         // 200s
#define SYSM_TIME_SLEEP             (500u / SYSM_TASK_PERIOD)           // 500ms

#define SYSM_TIME_MCU_TIMEOUT       (15u/SYSM_TASK_PERIOD)  //15ms

#define SYSM_MCU_RESET()            McuIf_SoftwareReset()

#define SYSM_EN_SOURCE              SYSM_EN_TYPE_IO
#define SYSM_EN_TYPE_AD             0u
#define SYSM_EN_TYPE_IO             1u

#define SYSM_NET_CONTROL_EN         CAEA_TRUE

#if(SYSM_NET_CONTROL_EN == CAEA_TRUE)
    #define SYSM_NET_SLEEP()         GetCanApp_u_NetWorkSleepAllowed()
#endif

#define SYSM_EN_INVALID_FILTCNT     (500u/SYSM_TASK_PERIOD)  //500ms
#define SYSM_EN_VALID_FILTCNT       (25u/SYSM_TASK_PERIOD)  //25ms

#if (SYSM_EN_SOURCE == SYSM_EN_TYPE_AD)
    #define SYSM_GET_EN_ADC()           ADCM_GetValidValue((uint8)ADCMCFG_EN_CH)
    #define SYSM_EN_AD_VALID            (uint16)270u  //7V
    #define SYSM_EN_AD_INVALID          (uint16)77u   //2V
#elif (SYSM_EN_SOURCE == SYSM_EN_TYPE_IO)
    #define SYSM_GET_EN_STS()           CAEA_TRUE
    #define SYSM_EN_IO_VALID            (uint8)CAEA_TRUE
    #define SYSM_EN_IO_INVALID          (uint8)CAEA_FALSE
#else
    #error  "SYSM_EN_SOURCE not defined!"
#endif


#define SYSM_STATUS_NONE                      0u
#define SYSM_STATUS_POWERUP                   1u
#define SYSM_STATUS_POWERUP_END               2u
#define SYSM_STATUS_POWERDOWN                 3u
#define SYSM_STATUS_POWERDOWN_END             4u
/*******************************************************************************
|    Enum Definition
|******************************************************************************/
typedef enum
{
  SYSMCFG_SLEEP_APP_MODE,
  SYSMCFG_SLEEP_EEP,
  SYSMCFG_SLEEP_MAX
} SYSMCFG_SLEEP_ITEM;


typedef enum
{
    SYSM_STA_INIT,
    SYSM_STA_RUN,
    SYSM_STA_READYSLEEP,
    SYSM_STA_PRESLEEP,
	SYSM_STA_MCUCLOSE,
    SYSM_STA_POWEROFF
}SYSM_MAIN_STA;
/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef uint8 (* tSysM_FlagGetFunc)(void);

typedef struct
{
    SYSMCFG_SLEEP_ITEM e_u_Item;
    uint8 e_u_Flag;
    tSysM_FlagGetFunc p_FlagGetFunc; /* data */
}TsSysMCfg_h_SleepJudge;

/*******************************************************************************
|    Table Definition
|******************************************************************************/

/*******************************************************************************
|    Global Const Declaration
|******************************************************************************/
extern const TsSysMCfg_h_SleepJudge CaSysM_SleepJudge_Table[SYSMCFG_SLEEP_MAX];

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/
extern void SysM_SysPower(void);
extern void SysM_SysPowerOn(void);
extern void SysM_SysPowerOff(void);
extern void SysM_MCUDeinit(void);
extern void SysM_Set_SysPowerStatus(uint8 e_u_Status);
extern uint8 SysM_Get_SysPowerStatus(void);
extern uint8 SysM_GetSysSTA(void);
#endif 
/*EOF*/
