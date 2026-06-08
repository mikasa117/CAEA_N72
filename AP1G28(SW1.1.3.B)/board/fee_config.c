/*
 * Copyright 2020-2026 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * @file fee_config.c
 * @brief 
 * 
 */


#include <stddef.h>
#include "fee_config.h"


/* general */
static const Fls_SectorType sectorList[8]={
    {
        .sectorId=0,
        .sectorStartAddress=0x0,
        .sectorSize=0x400,
        .pageSize=8,
        .sectorHwStartAddress=0x100000,
        .asyncAccess=1,
    },
    {
        .sectorId=1,
        .sectorStartAddress=0x400,
        .sectorSize=0x400,
        .pageSize=8,
        .sectorHwStartAddress=0x100400,
        .asyncAccess=1,
    },
    {
        .sectorId=2,
        .sectorStartAddress=0x800,
        .sectorSize=0x400,
        .pageSize=8,
        .sectorHwStartAddress=0x100800,
        .asyncAccess=1,
    },
    {
        .sectorId=3,
        .sectorStartAddress=0xc00,
        .sectorSize=0x400,
        .pageSize=8,
        .sectorHwStartAddress=0x100c00,
        .asyncAccess=1,
    },
    {
        .sectorId=4,
        .sectorStartAddress=0x1000,
        .sectorSize=0x400,
        .pageSize=8,
        .sectorHwStartAddress=0x101000,
        .asyncAccess=1,
    },
    {
        .sectorId=5,
        .sectorStartAddress=0x1400,
        .sectorSize=0x400,
        .pageSize=8,
        .sectorHwStartAddress=0x101400,
        .asyncAccess=1,
    },
    {
        .sectorId=6,
        .sectorStartAddress=0x1800,
        .sectorSize=0x400,
        .pageSize=8,
        .sectorHwStartAddress=0x101800,
        .asyncAccess=1,
    },
    {
        .sectorId=7,
        .sectorStartAddress=0x1c00,
        .sectorSize=0x400,
        .pageSize=8,
        .sectorHwStartAddress=0x101c00,
        .asyncAccess=1,
    },
};

extern void Fee_JobEndNotification(void);
extern void Fee_JobErrorNotification(void);




static const Fls_ConfigType flashConfig={
    .acEraseFunPtr=NULL,
    .acWriteFunPtr=NULL,
    .jobEndNotificationFunPtr=Fee_JobEndNotification,
    .jobErrorNotificationFunPtr=Fee_JobErrorNotification,
    .eDefaultMode=MEMIF_MODE_SLOW,
    .maxReadFastMode=512,
    .maxReadNormalMode=256,
    .maxWriteFastMode=128,
    .maxWriteNormalMode=8,
    .ConfigSectorNum=8,
    .sectorList=sectorList,
};


/* cluster */
static Fee_ClusterType clrType0[4]={
    {
        .StartAddr=0x0,
        .Length=0x400,
    },
    {
        .StartAddr=0x400,
        .Length=0x400,
    },
    {
        .StartAddr=0x800,
        .Length=0x400,
    },
    {
        .StartAddr=0xc00,
        .Length=0x400,
    },
};
static Fee_ClusterType clrType1[4]={
    {
        .StartAddr=0x1000,
        .Length=0x400,
    },
    {
        .StartAddr=0x1400,
        .Length=0x400,
    },
    {
        .StartAddr=0x1800,
        .Length=0x400,
    },
    {
        .StartAddr=0x1c00,
        .Length=0x400,
    },
};

static const Fee_ClusterGroupType clusterConfig[2]={
    {
        .ReservedSize=128,
        .ClrCount=4,
        .ClrPtr=clrType0,
    },
    {
        .ReservedSize=128,
        .ClrCount=4,
        .ClrPtr=clrType1,
    },
};

/* block */
static const Fee_BlockConfigType blockConfig[8]={
    {
        .BlockNumber=1,
        .BlockSize=96,
        .ClrGrp=0,
        .ImmediateData=1,
        .BlockAssignment=FEE_PROJECT_RESERVED,
    },
    {
        .BlockNumber=16,
        .BlockSize=96,
        .ClrGrp=0,
        .ImmediateData=0,
        .BlockAssignment=FEE_PROJECT_RESERVED,
    },
    {
        .BlockNumber=32,
        .BlockSize=96,
        .ClrGrp=0,
        .ImmediateData=0,
        .BlockAssignment=FEE_PROJECT_RESERVED,
    },
    {
        .BlockNumber=48,
        .BlockSize=96,
        .ClrGrp=0,
        .ImmediateData=0,
        .BlockAssignment=FEE_PROJECT_RESERVED,
    },
    {
        .BlockNumber=64,
        .BlockSize=96,
        .ClrGrp=1,
        .ImmediateData=1,
        .BlockAssignment=FEE_PROJECT_RESERVED,
    },
    {
        .BlockNumber=80,
        .BlockSize=96,
        .ClrGrp=1,
        .ImmediateData=0,
        .BlockAssignment=FEE_PROJECT_RESERVED,
    },
    {
        .BlockNumber=96,
        .BlockSize=96,
        .ClrGrp=1,
        .ImmediateData=0,
        .BlockAssignment=FEE_PROJECT_RESERVED,
    },
    {
        .BlockNumber=112,
        .BlockSize=96,
        .ClrGrp=1,
        .ImmediateData=0,
        .BlockAssignment=FEE_PROJECT_RESERVED,
    },
};



/* top */

const Fee_ModuleUserConfig_t FEEGenConfig={
    .blockCnt=8,
    .clusterCnt=2,
    .clusterConfigPtr=clusterConfig,
    .blockConfigPtr=blockConfig,
    .flashConfigPtr=&flashConfig,
};





