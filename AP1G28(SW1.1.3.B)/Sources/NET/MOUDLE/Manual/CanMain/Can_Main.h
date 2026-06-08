/*******************************************************************************
|  File Name: Can_Main.h
|  Description: .c file of Can_Main
|-------------------------------------------------------------------------------
|  (c)This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      ---------------------  -----------------------------------------
|               Qiuxiaojian            CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 20171009      1.0.0        kenw       Primary edition.
| 20171025      1.0.1        kenw       ���ǹ��ú궨���Ƶ���ģ���c֮��
|******************************************************************************/
#ifndef CAN_MAIN_H_
#define CAN_MAIN_H_

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Platform_Types.h"
#include "SysM.h"
/*******************************************************************************
|    Compile Option or configuration Section (for test/debug)
|******************************************************************************/

/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/**/
#define CeCanMain_u_canSleep       1u
#define CeCanMain_u_canNotSleep   0u


/**/
#define CeCanMain_u_busActive      1u
#define CeCanMain_u_busNotActive   0u


/********************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
# define FblHeaderTable *(( tFblHeader *)(0x3007FFC0))

# define CallFblStart() (FblHeaderTable->pFblStartFct)()

typedef void (*tExportFct)(void);

typedef void (*tFblStrtFct)(void);

typedef struct tBlockDescriptorTag
{
    vuint8 blockNr; /* Number of logical block */
    vuint32 blockIndex;
    vuint32 blockStartAddress; /* Start address of current block */
    vuint32 blockLength; /* Block length in bytes */
    vuint16 maxProgAttempts; /* Maximum number of reprogramming attempts */
    tExportFct verifyOutput;
} tBlockDescriptor;

/* The logical block table describes the memory layout of logical blocks */
typedef struct tLogicalBlockTableTag
{
    vuint32 magicFlag; /* Value of FBL_MTAB_MAGIC_FLAG - Indicates the existence of the table */
    vuint8 assignFlags[1]; /* Disposability bit field (mandatory/optional) */
    vuint8 noOfBlocks; /* Number of configured logical blocks */
    tBlockDescriptor logicalBlock[1];
} tLogicalBlockTable;

/** Pointer type to logical block table */
typedef tLogicalBlockTable const * tFblHeaderLogicalBlockTablePtr;



/** FBL header structure */
typedef struct
{
    tFblHeaderLogicalBlockTablePtr pLogicalBlockTable;
    tFblStrtFct pFblStartFct; /**< Pointer to FblStart-function */
} tFblHeader;
/*******************************************************************************
|    Global Variable with extern linkage
|******************************************************************************/


/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/
extern void CanMain_InitMemory( uint8 LeCanMain_u_Src );
extern void CanMain_5msAMainFunction(void);
extern void CanMain_5msBMainFunction(void);
extern void CanMain_10msAMainFunction(void);
extern void CanMain_10msBMainFunction(void);
extern void CanMain_20msMainFunction(void);

extern uint8 CanMain_GetDTCENFlag(void);
extern void CanMain_SetNeedReset(void);
extern uint8 CanMain_GetNeedReset(void);
#endif   /*EOF*/
