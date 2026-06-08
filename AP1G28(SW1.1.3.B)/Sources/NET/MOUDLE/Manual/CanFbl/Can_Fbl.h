#ifndef __FBL_DEF_H__
#define __FBL_DEF_H__
#include "Can_Fbl_Cfg.h"
#include "core_common.h"
#include "system_YTM32B1ME0.h"
/*******************************************************************************
|     Macro Definition
|******************************************************************************/
# define FblInterruptDisable()       DISABLE_INTERRUPTS()/*__asm( "wrteei 0" )*/
# define FblInterruptEnable()        ENABLE_INTERRUPTS()
# define APPL_FBL_RESET()            SystemSoftwareReset()    

#define FBL_ENABLE_FBL_START

#define FBL_GMHEADER_NOAR_FBL               1

#define FBL_HEADER_ADDRESS  0x00000700   /* FBL�结构体指针的起始地址 */

/*#define FBL_PRINTFINGER_ADDRESS  0x0003FFB0
#define FBL_FBLVERSION_ADDRESS   0x0003FFC0*/
/* Define to access the FBL header structure point */
#define FblHeaderTable ((tFblHeader*)(FBL_HEADER_ADDRESS))

#define CallFblStart(pParam)    (FblHeaderTable->FblStartFct)(pParam)  /* FBL启动函数，形�Can初始化结构体 */

/*******************************************************************************
|     Enum Definition
|******************************************************************************/

/*******************************************************************************
|     Typedef Definition
|******************************************************************************/

typedef struct tagCanInitTable tCanInitTable;

#if defined( FBL_ENABLE_FBL_START )                   
typedef MEMORY_HUGE MEMORY_FAR void (*tFblStrtFct)( uint8 );
#endif

typedef struct tagFblHeader
{
    vuint8      CS[2];      /**< Module Checksum */
    vuint8      MID[2];     /**< Module ID */
    vuint8      HFI[2];     /**< Header Format Identifier */
    vuint8      SWMI[4];    /**< SoftWare Module Identifier/Hex Part Number */
    vuint8      DLS[2];     /**< Design Level Suffix */
    vuint8      DCID[2];    /**< Data Compatibility Identifier */
    vuint8      NOAR[2];    /**< Number Of Address Regions */
    /* Product Memory Address + Number Of Bytes */
    vuint8      AddressRegions[FBL_GMHEADER_NOAR_FBL * 8];
    tFblStrtFct FblStartFct;
#  if defined( SEC_SECURITY_CLASS )
#   if ( (SEC_SECURITY_CLASS == SEC_CLASS_C) || (SEC_SECURITY_CLASS == SEC_CLASS_CCC) )
    tExportFct  pSecVerifySignatureFct;
#   endif
#  endif
    vuint8      kFblMainVersion;
    vuint8      kFblSubVersion;
    vuint8      kFblBugFixVersion;
    vuint8      kFblBuildVersion;
} tFblHeader;
/*******************************************************************************
|     Global Variable with extern linkage
|******************************************************************************/

/** CAN initialization data structure */
struct tagCanInitTable
{
   vuint8 TpRxIdHigh;       /**< CAN receive identifier */
   vuint8 TpRxIdLow;
   vuint8 TpTxIdHigh;       /**< CAN transmit identifier */
   vuint8 TpTxIdLow;
   vuint8  CanInitCtrl0;
   vuint8  CanInitCtrl1;
   vuint8  CanInitPrDiv;
   vuint8  CanInitCtrl2;
   vuint8 ProgrammedState;             /**< Mode byte for ReportProgrammedState service */
   vuint8 ErrorCode;                   /**< This byte determines SPS_TYPE_B or SPS_TYPE_C */
   vuint8 RequestProgrammingMode;      /**< Highspeed programming or normal mode */
   vuint8 requestDownloadFormatID;     /**< Subparameter of Request download */
   vuint32 requestDownloadMemorySize;  /**< unCompressedMemorySize param of Request Download */
};

extern tFblInfo __attribute__ ((section(".RegionKam"))) FblInfo;

# define FblSetFblStartMagicFlag() \
{ \
   FblInfo.fblStartMagicFlag[0] = (vuint8)kFblStartMagicByte0; \
   FblInfo.fblStartMagicFlag[1] = (vuint8)kFblStartMagicByte1; \
   FblInfo.fblStartMagicFlag[2] = (vuint8)kFblStartMagicByte2; \
   FblInfo.fblStartMagicFlag[3] = (vuint8)kFblStartMagicByte3; \
   FblInfo.fblStartMagicFlag[4] = (vuint8)kFblStartMagicByte4; \
   FblInfo.fblStartMagicFlag[5] = (vuint8)kFblStartMagicByte5; \
   FblInfo.fblStartMagicFlag[6] = (vuint8)kFblStartMagicByte6; \
   FblInfo.fblStartMagicFlag[7] = (vuint8)kFblStartMagicByte7; \
}

extern __attribute__ ((section(".AppBootInteract"))) void FblStart(void);//( tCanInitTable * pCanInitTable );


#endif
