/*******************************************************************************
|  File Name:  base.h
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
#ifndef __BASE_H__
#define __BASE_H__
/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#define FBL_ENABLE_FBL_START
#define FBL_CALL_TYPE

#define FBL_HEADER_ADDRESS                   0x08003100u

#ifndef __far
#define __far
#endif

#ifndef V_MEMRAM0
# define V_MEMRAM0                  /* addition qualifier data access in RAM  */
#endif


#ifndef V_MEMRAM1
# define V_MEMRAM1                 /* fast data access in RAM */
#endif


# ifndef V_MEMRAM2
#  define V_MEMRAM2                 /* fast data access in RAM */


#ifndef V_MEMROM0
# define V_MEMROM0                  /* addition qualifier data access in ROM  */
#endif


#ifndef V_MEMROM1
# define V_MEMROM1                 /* fast data access in ROM */
#endif

# ifndef V_MEMROM2
#  define V_MEMROM2        const    /* fast data access in ROM */
# endif


#ifndef V_MEMROM1_FAR
# define V_MEMROM1_FAR             /* slow addressing mode in ROM */
#endif


# endif

#define kNrOfValidationBytes                 1
#define FBL_MTAB_NO_OF_BLOCKS                1
/*******************************************************************************
|    Compile Option or configuration Section
|******************************************************************************/
typedef unsigned char  vuint8;
typedef unsigned short vuint16;
typedef unsigned long  vuint32;
/*******************************************************************************
|    Macro Definition
|******************************************************************************/
typedef struct tagFblInfo
{
	vuint8 fblStartMagicFlag[8];
	vuint8 fblProgmedMagicFlag[4];   /* Support app to adjust programming status */
	vuint8 SecurAccessFAAFlag;      /* 27 unlock flag */ /*FBL_000008*/
	vuint8 :8;
	vuint8 :8;
	vuint8 :8;
	vuint8 SecMagicFlag[4];
	vuint8 CanTp_FblMagicFlag[4];
}tFblInfo;
/*******************************************************************************
|    Enum Definition
|******************************************************************************/
typedef vuint32 FBL_ADDR_TYPE;
typedef vuint32 FBL_MEMSIZE_TYPE;
/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef FBL_ADDR_TYPE       tFblAddress;
typedef FBL_MEMSIZE_TYPE    tFblLength;

/* Entry type of logical block table */
typedef struct tBlockDescriptorTag
{
  vuint8 blockNr; /* Number of logical block */
  vuint32 blockIndex;
  tFblAddress blockStartAddress; /* Start address of current block */
  tFblLength blockLength; /* Block length in bytes */
  tFblAddress presencePatternAddress;
  vuint16 maxProgAttempts; /* Maximum number of reprogramming attempts */
} tBlockDescriptor;
/* The logical block table describes the memory layout of logical blocks */
typedef struct tLogicalBlockTableTag
{
  vuint32 magicFlag; /* Value of FBL_MTAB_MAGIC_FLAG - Indicates the existence of the table */
  vuint8 assignFlags[kNrOfValidationBytes]; /* Disposability bit field (mandatory/optional) */
  vuint8 noOfBlocks; /* Number of configured logical blocks */
  tBlockDescriptor logicalBlock[FBL_MTAB_NO_OF_BLOCKS];
} tLogicalBlockTable;

/** Pointer type to logical block table */
typedef V_MEMROM1_FAR tLogicalBlockTable __far const * tFblHeaderLogicalBlockTablePtr;
/** Pointer to call FblStart() function */
typedef FBL_CALL_TYPE void (*tFblStrtFct)(vuint8 WdgType);
/** Pointer to call ApplFblNvReadDataByIdentifier() function */
typedef vuint8 (*tFblReadDID)(vuint16 Did, vuint8 *ReadData, vuint8 length);
/** Pointer to call ApplFblNvSecurAccessFAAFlag() function */
typedef vuint8 (*tFblSecurAccessFlag)(vuint8 *SecurAccessFAAFlag, vuint8 ReadFlag, vuint8 WdgType);
typedef vuint8 (*tFblLevel1PkcNumber)(vuint8 *Data, vuint8 ReadFlag, vuint8 length, vuint8 WdgType);
/** FBL header structure */
typedef struct
{
tFblHeaderLogicalBlockTablePtr pLogicalBlockTable;
tFblStrtFct pFblStartFct;
tFblReadDID pApplFblNvReadDataByIdentifier;
tFblSecurAccessFlag pApplFblNvSecurAccessFAAFlag;
tFblLevel1PkcNumber pApplFblNvLevel1PkcNumber;
} tFblHeader;
/*******************************************************************************
|    Table Definition
|******************************************************************************/
#if defined( FBL_ENABLE_FBL_START )
/** Reprogramming request storage variable , FBL_KAM_DATA.bss region */
extern V_MEMRAM0 volatile V_MEMRAM1 __attribute__ ((section(".fbl_kam_data"))) tFblInfo V_MEMRAM2 FblInfo;

/* Define pattern for magic flags used for reprogramming indication */
# define kFblStartMagicByte0   0x50u /* 'P' */
# define kFblStartMagicByte1   0x72u /* 'r' */
# define kFblStartMagicByte2   0x6Fu /* 'o' */
# define kFblStartMagicByte3   0x67u /* 'g' */
# define kFblStartMagicByte4   0x53u /* 'S' */
# define kFblStartMagicByte5   0x69u /* 'i' */
# define kFblStartMagicByte6   0x67u /* 'g' */
# define kFblStartMagicByte7   0x6Eu /* 'n' */
# define kFblNoOfMagicBytes    8u

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

# define FblChkFblStartMagicFlag() \
   ((    (FblInfo.fblStartMagicFlag[0] == (vuint8)kFblStartMagicByte0) \
      && (FblInfo.fblStartMagicFlag[1] == (vuint8)kFblStartMagicByte1) \
      && (FblInfo.fblStartMagicFlag[2] == (vuint8)kFblStartMagicByte2) \
      && (FblInfo.fblStartMagicFlag[3] == (vuint8)kFblStartMagicByte3) \
      && (FblInfo.fblStartMagicFlag[4] == (vuint8)kFblStartMagicByte4) \
      && (FblInfo.fblStartMagicFlag[5] == (vuint8)kFblStartMagicByte5) \
      && (FblInfo.fblStartMagicFlag[6] == (vuint8)kFblStartMagicByte6) \
      && (FblInfo.fblStartMagicFlag[7] == (vuint8)kFblStartMagicByte7)) ? (vuint8)1u : (vuint8)0u)

# define FblClrFblStartMagicFlag() \
{ \
   vuint8 byteIndex; \
   for (byteIndex = (vuint8)0U; byteIndex < (vuint8)kFblNoOfMagicBytes; byteIndex++) \
   { \
      FblInfo.fblStartMagicFlag[byteIndex] = (vuint8)0x00u; \
   } \
}



/* Define to access the FBL header structure */

#endif /* FBL_ENABLE_FBL_START */


/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/
extern void AppJmpFBL(void);





#endif /* __BASE_H__ */






