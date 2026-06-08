/*******************************************************************************
|  File Name:  Mcal_App.h
|  Description:  Implementation of the Mcal_App Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           XiaYaJun          CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 2018-06-11    01.00.00     XYJ       Creation
|******************************************************************************/


#ifndef _MCAL_APP_H
/* polyspace<MISRA-C3:21.1:Not a defect:Justified> Normal. */
#define _MCAL_APP_H

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Mcal_App_Cfg.h"
//#include "SysTypes.h"
/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
/* polyspace<MISRA-C3:20.9:Not a defect:Justified> Normal. */
#if (RAMTSTIF_ERM_EN == RAMTSTIF_ENABLE)
#define CeMcalApp_u_ERMChannelNumber (uint8)2
#endif

/*define the memory type number for record the ECC error information*/
#define CeMcalApp_u_SRAMECCTypeNumber (uint8)2

/*******************************************************************************
|    Enum Definition
|******************************************************************************/
typedef enum
{
    SRAM_L = 0,    /* SRAM_L */
    SRAM_U = 1     /* SRAM_U */
}TeMcalApp_e_SRAMType;

typedef enum
{
    ECC_NONE = 0,    /* no ECC error */
    ECC_SBC = 1,    /* Single-Bit Correctable ECC error */
    ECC_NCE = 2    /* double-bit None-Correctable ECC error */
}TeMcalApp_e_ECCType;

typedef enum
{
    NCE_SRAM_L = 0,
    NCE_SRAM_U = 1,
    SBE_SRAM_L = 8,
    SBE_SRAM_U = 9,
    PC_Tag_ParityError = 14,
    PC_Data_ParityError = 15
}TeMcalApp_e_PECCLocation;

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef struct
{
    TeMcalApp_e_SRAMType SRAMType;
    uint32 Address;
    TeMcalApp_e_ECCType EccType;
}TsMcalApp_h_ECC;

typedef struct
{
    TeMcalApp_e_PECCLocation Location;
    uint32 EFaddr;
    uint32 Reg_MCM_LMFATR;
    uint32 Data_Hword;
    uint32 Data_Lword;
    /* polyspace<MISRA-C3:2.3:Not a defect:Justified> Normal. */
}TsMcalApp_h_PECCError;
/* polyspace<MISRA-C3:2.3:Not a defect:Justified> Normal. */
typedef uint8 ResetType;

/*******************************************************************************
|    Global Variable with extern linkage
|******************************************************************************/

extern void MCALAPP_InitMemory(void);
extern void MCALAPP_StartGpt(void);
extern void MCALAPP_PeripheralInit(void);
extern void MCALAPP_PeripheralDeInit(void);

extern void MCALAPP_SetInterruptsPriority(void);
extern void MCALAPP_EnableInterrupts(void);
extern void MCALAPP_DisableInterrupts(void);
extern void MCALAPP_SetProgrammableInterrupts(void);
#if (MCAL_ERM_double_fault_IRQn_EN == MCAL_ENABLE)
extern void MCALAPP_CallBackERMDoubleFault_IRQHandler(void);
#endif
#if (MCAL_MCM_IRQn_EN == MCAL_ENABLE)
extern void MCALAPP_CallBackMCM_IRQHandler(void);
#endif
#if (MCAL_FTFC_Fault_IRQn_EN == MCAL_ENABLE)
extern void MCALAPP_CallBackFTFCFault_IRQHandler(void);
#endif
extern void MCALAPP_ClearResetStatus(void);
extern void MCALAPP_SetMcuMode(uint8 McuMode);

extern void MCALAPP_SetRtcSleepTickCnt(uint16 RtcSleepTickCnt);
extern void MCALAPP_EnableRTCWakeup(void);
extern void MCALAPP_DisableRTCWakeup(void);
extern void MCALAPP_EnableICUWakeup(void);
extern void MCALAPP_DisableICUWakeup(void);
extern void MCALAPP_EnableCOMWakeup(void);
extern void MCALAPP_DisableCOMWakeup(void);
extern void MCALAPP_SetI2cPowerReset(void);
extern uint8 MCALAPP_CanCheckWakeup( uint8 CanTrcvSTB, uint8 CanTrcvRXD, uint8 CanTrcvChannel);
/* polyspace<MISRA-C3:8.5:Not a defect:Justified> Normal. */
extern void DefaultISR(void);

extern volatile uint32_t Current_BUS;
extern volatile uint32_t ADC_BAT_BLDC;

#endif

/*EOF*/
