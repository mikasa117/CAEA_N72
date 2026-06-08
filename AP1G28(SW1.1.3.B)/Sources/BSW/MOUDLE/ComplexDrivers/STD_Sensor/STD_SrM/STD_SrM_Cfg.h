/*******************************************************************************
|  File Name:  STD_SrCtr_Cfg.h
|  Description:  Implementation of the Sensor Ctr Config Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           xiayajun               CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2018-06-21    01.00.00     XYJ       Creation
| 2019-12-27	   /	     XJW       Modified for AC-DI18
|******************************************************************************/


#if !defined (_STD_SRM_CFG_H)
#define _STD_SRM_CFG_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "SysTypes.h"

#include "STD_SrAdCtr.h"
#include "STD_BtrM.h"
#include "STD_SrCfg.h"

/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
#define SRM_DISABLE	(0u)
#define SRM_ENABLE	(1u)

#define SRM_EN_CLASS				SRM_ENABLE	/*SRM used*/
#define	SRM_CPID_EN_CLASS			SRM_DISABLE	/*used*/
#define	SRM_PID_EN_CLASS			SRM_DISABLE
#define	SRM_DTC_EN_CLASS			SRM_DISABLE

#define SRM_TYPE_AD_TABLE_CLASS             SRM_ENABLE		/*Table used*/
#define SRM_TYPE_AD_LINE_CLASS              SRM_DISABLE
#define SRM_TYPE_PWM_CLASS                  SRM_DISABLE

#if (SRM_ENABLE == SRM_EN_CLASS)
#define SRCFG_GetBatteryModeAStatus         BTRM_GetSysBatteryModeAStatus

#define	SRM_GetOpenShortStatus	SRADCTR_TableGetOpenShortStatus

#define SRM_CODE_RAM	
/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef sint16 (*pSrMFunIf_GetValidValueType)(uint8 SensorChan);
typedef uint8 (*pSrMFunIf_GetValidStatusType)(uint8 SensorChan);

typedef struct
{
    uint8 SensorChan;
    pSrMFunIf_GetValidValueType 	GetValidValue;
    pSrMFunIf_GetValidStatusType	GetValidStatus;
} SrMChanCfg_Struct;
/*******************************************************************************
|    Table Definition
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/
extern const SrMChanCfg_Struct stSrMChanCfgArray[SRCFG_CH_MAX_NUM];
#endif

#endif
/*EOF*/
