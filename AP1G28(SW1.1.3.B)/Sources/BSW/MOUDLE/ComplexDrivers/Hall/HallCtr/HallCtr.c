/*******************************************************************************
|  File Name:  HallCtr.c
|  Description:  Implementation of the Battery voltage Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| WCj           Chaojian Wang         CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2025-11-29    01.00.00     WCj       Creation
|
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "HallCtr.h"
#include "STD_Lib.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/*******************************************************************************
|    Enum Definition
|******************************************************************************/
typedef enum
{
    HALL_M_MODE_INIT = 0u,
    HALL_M_MODE_NORMAL,
    HALL_M_MODE_FAULT
} BtrCtrModeEnum;
/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef	struct
{
    uint16 usSysHallAd;
    uint16 usSysFastAdBuff[HALLCTR_FILTER_TIME_FAST];
    uint8 ucSysFilterCnt1;
    uint8 ucSysFilterCnt2;
    uint8 ucSysLowVoltageStatus;
    uint8 ucHighVoltageStatus;
} HallCtrADStruct;
/*******************************************************************************
|    Static local KAM variables Declaration
|******************************************************************************/

#include "STD_MemMap.h"

static BtrCtrModeEnum HALL_CTR_CODE_KAM TeHALLCTR_e_SysHallMode;

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/


static HallCtrADStruct HALL_CTR_CODE_RAM TsHALLCTR_h_AD;


/*******************************************************************************
|    Table Const Definition
|******************************************************************************/

/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/


static void HALL_CTR_HallModeJudge( void );
static void HALL_CTR_HallModeFastJudge(void);
static void HALL_CTR_HallModeNormalJudge(void);
static void HALL_CTR_HallModeFaultJudge(void);
static void  HALL_CTR_UpdataHallAdValue(void);


/*******************************************************************************
|    Function Source Code
|******************************************************************************/

/*******************************************************************************
Name              : HALL_CTR_InitMemory
Syntax            : void HALL_CTR_InitMemory(void)
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      : None
Description       :
Call By           : EcuM_App Module
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
void HALL_CTR_InitMemory(void)
{
    LIB_SetMemory( (uint8 *)&TsHALLCTR_h_AD, 0u, sizeof(TsHALLCTR_h_AD) / sizeof(uint8));/*PRQA S 0310*/
}

/*******************************************************************************
Name              : HALL_CTR_InitKamMemory
Syntax            : void HALL_CTR_InitKamMemory( void )
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      : E_OK
Description       :
Call By           : Appl_Dcm Module
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
void HALL_CTR_InitKamMemory( void )
{
    TeHALLCTR_e_SysHallMode = HALL_M_MODE_INIT;
}


/*******************************************************************************
Name              : BTRCTR_GetMotorBatteryModeBStatus
Syntax            :uint8 BTRCTR_GetMotorBatteryModeBStatus(void)
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      :
Description       :
Call By           :
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
static void HALL_CTR_UpdataHallAdValue(void)
{
    TsHALLCTR_h_AD.usSysHallAd = HALLCTR_GetBatteryAdValue();
}
/*******************************************************************************
Name              : HALL_CTR_ModeFunction
Syntax            : void HALL_CTR_ModeFunction( void )
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      :
Description       :
Call By           :
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
void HALL_CTR_ModeFunction(void)
{
    HALL_CTR_UpdataHallAdValue();
    HALL_CTR_HallModeJudge(); 
}

/*******************************************************************************
Name              : HALL_CTR_HallModeJudge
Syntax            : void HALL_CTR_HallModeJudge( void )
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      : E_OK
Description       :
Call By           :
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
static void HALL_CTR_HallModeJudge( void )
{
    switch(TeHALLCTR_e_SysHallMode)
    {
        case HALL_M_MODE_INIT:
        {
            HALL_CTR_HallModeFastJudge();
            break;
        }

        case HALL_M_MODE_NORMAL:
        {
            HALL_CTR_HallModeNormalJudge();
            break;
        }

        case HALL_M_MODE_FAULT:
        {
            HALL_CTR_HallModeFaultJudge();
            break;
        }

/* polyspace<RTE:UNR:Low:Other> no effect */
        default:
        {
            TeHALLCTR_e_SysHallMode = HALL_M_MODE_INIT;
            HALL_CTR_InitMemory();
            break;
        }
    }
}

/*******************************************************************************
Name              : HALL_CTR_HallModeFastJudge
Syntax            : void HALL_CTR_HallModeFastJudge( void )
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      :
Description       :
Call By           :
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
static void HALL_CTR_HallModeFastJudge(void)
{
    TsHALLCTR_h_AD.usSysFastAdBuff[TsHALLCTR_h_AD.ucSysFilterCnt1] = TsHALLCTR_h_AD.usSysHallAd;
    TsHALLCTR_h_AD.ucSysFilterCnt1++;

    if(TsHALLCTR_h_AD.ucSysFilterCnt1 >= HALLCTR_FILTER_TIME_FAST)
    {
        LIB_BubbleSort(TsHALLCTR_h_AD.usSysFastAdBuff, TsHALLCTR_h_AD.ucSysFilterCnt1);
        TsHALLCTR_h_AD.usSysHallAd = TsHALLCTR_h_AD.usSysFastAdBuff[HALLCTR_FILTER_TIME_FAST / (uint8)2];
        TsHALLCTR_h_AD.ucSysFilterCnt1 = 0u;

        if ( (TsHALLCTR_h_AD.usSysHallAd >= (uint16)BTRCTR_SYS_HALL_5V_LOW_VOLT ) && ( TsHALLCTR_h_AD.usSysHallAd <= (uint16)BTRCTR_SYS_HALL_5V_HIGH_VOLT))
        {
            TeHALLCTR_e_SysHallMode = HALL_M_MODE_NORMAL;	/*if battery voltage is larger than 4.5V and lower than 5.5V,set battery mode to mode A*/
        }
        else if ( ( TsHALLCTR_h_AD.usSysHallAd >= BTRCTR_SYS_HALL_5V_HIGH_VOLT) || (TsHALLCTR_h_AD.usSysHallAd <= BTRCTR_SYS_HALL_5V_LOW_VOLT))
        {
            TeHALLCTR_e_SysHallMode = HALL_M_MODE_FAULT;	/*if battery voltage is larger than 7V and lower than 18V,set battery mode to mode B*/
        }
        else
        {
           
        }

    }
}

/*******************************************************************************
Name              : HALL_CTR_HallModeNormalJudge
Syntax            : void HALL_CTR_HallModeNormalJudge( void )
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      :
Description       :
Call By           :
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
static void HALL_CTR_HallModeNormalJudge(void)
{
   
    if( TsHALLCTR_h_AD.usSysHallAd >= (uint16)BTRCTR_SYS_HALL_5V_HIGH_VOLT )
    {
        if( TsHALLCTR_h_AD.ucSysFilterCnt1 >= HALLCTR_FILTER_TIME_LONG )
        {
            TeHALLCTR_e_SysHallMode = HALL_M_MODE_FAULT;
            TsHALLCTR_h_AD.ucSysFilterCnt1 = 0u;		/*reset filtering time count*/
        }

        TsHALLCTR_h_AD.ucSysFilterCnt1++;
    }
    else
    {
        TsHALLCTR_h_AD.ucSysFilterCnt1 = 0u;
    }

    if( TsHALLCTR_h_AD.usSysHallAd <= (uint16)BTRCTR_SYS_HALL_5V_LOW_VOLT )
    {

        if( TsHALLCTR_h_AD.ucSysFilterCnt2 >= HALLCTR_FILTER_TIME_LONG )
        {
            TeHALLCTR_e_SysHallMode = HALL_M_MODE_FAULT;
            TsHALLCTR_h_AD.ucSysFilterCnt2 = 0u;/*reset filtering time count*/
        }

        TsHALLCTR_h_AD.ucSysFilterCnt2++;
    }
    else
    {
        TsHALLCTR_h_AD.ucSysFilterCnt2 = 0u;	/*reset filtering time count*/
    }
}

/*******************************************************************************
Name              : HALL_CTR_HallModeFaultJudge
Syntax            : STATIC void HALL_CTR_HallModeFaultJudge(void)
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      :
Description       :
Call By           :
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
static void HALL_CTR_HallModeFaultJudge(void)
{
    /*in mode B, battery voltage is larger than 9V and lower than 16V,set battery mode to mode A*/
    if(( TsHALLCTR_h_AD.usSysHallAd >= (uint16)BTRCTR_SYS_HALL_5V_LOW_VOLT ) && ( TsHALLCTR_h_AD.usSysHallAd <= (uint16)BTRCTR_SYS_HALL_5V_HIGH_VOLT ))
    {
        if( TsHALLCTR_h_AD.ucSysFilterCnt1 >= HALLCTR_FILTER_TIME_LONG )/*arrived to filtering time*/
        {
            TeHALLCTR_e_SysHallMode = HALL_M_MODE_NORMAL;/*set battery mode to mode B*/
            TsHALLCTR_h_AD.ucSysFilterCnt1 = 0u;		/*reset filtering time count*/
        }
        TsHALLCTR_h_AD.ucSysFilterCnt1++;
    }
    else
    {
        TsHALLCTR_h_AD.ucSysFilterCnt1 = 0u;
    }

}


/*******************************************************************************
Name              : HALL_CTR_GetHallVolt
Syntax            :uint16 HALL_CTR_GetHallVolt(void)
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      :
Description       :
Call By           :
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
uint16 HALL_CTR_GetHallVolt(void)
{
    return TsHALLCTR_h_AD.usSysHallAd ;
}

/*******************************************************************************
Name              : HALL_CTR_GetHallModeNormalStatus
Syntax            : uint8 HALL_CTR_GetHallModeNormalStatus(void)
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      :
Description       :
Call By           :
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
uint8 HALL_CTR_GetHallModeNormalStatus(void)
{
    return (uint8)( HALL_M_MODE_NORMAL == TeHALLCTR_e_SysHallMode  );
}

/*******************************************************************************
Name              : HALL_CTR_GetHallModeFaultStatus
Syntax            : uint8 HALL_CTR_GetHallModeFaultStatus(void)
Sync/Async        : Synchronous
Reentrancy        : None
Parameters(in)    : None
Parameters(out)   : None
Return value      :
Description       :
Call By           :
History
<No.>    <author>    <time>    <description>
1
|******************************************************************************/
uint8 HALL_CTR_GetHallModeFaultStatus(void)
{
    return (uint8)( HALL_M_MODE_FAULT == TeHALLCTR_e_SysHallMode  );
}




/*EOF*/
