/*******************************************************************************
|  File Name:  STD_BtrCtr.c
|  Description:  Implementation of the Battery voltage Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XZS           Zhangsheng Xia         CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2017-02-22    01.00.00     XZS       Creation
|
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_BtrCtr.h"
//#include "Rte_Can.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/*******************************************************************************
|    Enum Definition
|******************************************************************************/
/*****************************************************
# Current  MODE    ||         Init           ||      In                           || Out
#  A               || 9<V<16                 || *B->A* V>9      (500ms)           ||  *A->B* V<=8.5     (500ms)           ||
#  A               || 9<V<16                 || *B->A* V<16     (500ms)           ||  *A->B* V>=16.5    (500ms)           ||
#  A               || 9<V<16                 || *D->A* V<=10    (10ms)            ||  *A->D* V>10.8     (20ms) and V<16   ||
#  B               || 6.5<V<9                || *A->B* V<=8.5   (500ms)           ||  *B->A* V>9        (500ms)           ||
#  B               || 16<V<18                || *A->B* V>=16.5  (500ms)           ||  *B->A* V<16       (500ms)           ||
#  B               || 6.5<V<9                || *C->B* V>7      (500ms)           ||  *B->C* V<6.5      (500ms)           ||
#  B               || 16<V<18                || *C->B* V<17.5   (500ms)           ||  *B->C* V>18       (500ms)           ||
#  C               || V<6.5                  || *B->C* V<6.5    (500ms)           ||  *C->B* V>7        (500ms)           ||
#  C               || V>18                   || *B->C* V>18     (500ms)           ||  *C->B* V<17.5     (500ms)           ||
#  D               || 10.8<V<16              || *A->D* V>10.8   (20ms)            ||  *D->B* V>16.5     (500ms)           ||
#  D               || 10.8<V<16              || *A->D* V>10.8   (20ms)            ||  *D->A* V<=10      (10ms)            ||
*****************************************************/
typedef enum
{
    BTRM_MODE_INIT = 0u,
    BTRM_MODE_A, /*9<V<16*/
    BTRM_MODE_B, /*6.5<V<9 || 16<V<18 */
#if (BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_MODE_C_ENABLE)
    BTRM_MODE_C, /*V<6.5 || V>18*/
#endif
#if (BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_MODE_D_ENABLE)
    BTRM_MODE_D /*10.8<V<16*/
#endif
} BtrCtrModeEnum;
/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef	struct
{
    uint16 usSysBatteryAd;
    uint16 usSysFastAdBuff[BTRCTR_FILTER_TIME_FAST];
    uint8 ucSysFilterCnt1;
    uint8 ucSysFilterCnt2;
#if (BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_MODE_D_ENABLE)
    uint8 ucSysFilterCnt3;
#endif
    uint8 ucSysLowVoltageStatus;
    uint8 ucHighVoltageStatus;
#if (BTRCTR_ENABLE == BTRCTR_LOAD_BATTERY_ENABLE)
    uint16 usLoadBatteryAd;
	uint16 usLoadFastAdBuff[BTRCTR_LOAD_FILTER_TIME_FAST];
    uint8 ucLoadFilterCnt1;
    uint8 ucLoadFilterCnt2;
    uint8 ucLoadLowVoltageStatus;
#endif
    //uint8 ucIgonFilterCnt1s;  // 新增IGON滤波计数器
    //uint16 ucIgonFilterCnt3min;  // 新增IGON滤波计数器
} BtrCtrADStruct;
/*******************************************************************************
|    Static local KAM variables Declaration
|******************************************************************************/
#define STD_BTRCTR_START_SEC_VAR_KAM
#include "STD_MemMap.h"

static BtrCtrModeEnum BTRCTR_CODE_KAM TeBTRCTR_e_SysBatteryMode;
#if (BTRCTR_ENABLE == BTRCTR_LOAD_BATTERY_ENABLE)
static BtrCtrModeEnum BTRCTR_CODE_KAM TeBTRCTR_e_LoadBatteryMode;
#endif
#define STD_BTRCTR_STOP_SEC_VAR_KAM
#include "STD_MemMap.h"
/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/
#define STD_BTRCTR_START_SEC_VAR_RAM
#include "STD_MemMap.h"

static BtrCtrADStruct BTRCTR_CODE_RAM TsBTRCTR_h_AD;



#define STD_BTRCTR_STOP_SEC_VAR_RAM
#include "STD_MemMap.h"
/*******************************************************************************
|    Table Const Definition
|******************************************************************************/

/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/


static void BTRCTR_SysModeJudge( void );
static void BTRCTR_SysModeFastJudge(void);
static void BTRCTR_SysModeAJudge(void);
static void BTRCTR_SysModeBJudge(void);
static void  BTRCTR_UpdataBatteryAdValue(void);
#if (BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_MODE_C_ENABLE)
static void BTRCTR_SysModeCJudge(void);
#endif
#if (BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_MODE_D_ENABLE)
static void BTRCTR_SysModeDJudge(void);
#endif

#if (BTRCTR_ENABLE == BTRCTR_LOAD_BATTERY_ENABLE)
static void BTRCTR_LoadModeJudge(void);
static void BTRCTR_LoadModeFastJudge(void);
static void BTRCTR_LoadModeAJudge(void);
static void BTRCTR_LoadModeBJudge(void);

#endif
/*******************************************************************************
|    Function Source Code
|******************************************************************************/

/*******************************************************************************
Name              : BTRCTR_InitMemory
Syntax            : void BTRCTR_InitMemory(void)
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
void BTRCTR_InitMemory(void)
{
    LIB_SetMemory( (uint8 *)&TsBTRCTR_h_AD, 0u, sizeof(TsBTRCTR_h_AD) / sizeof(uint8));/*PRQA S 0310*/
}

/*******************************************************************************
Name              : BTRCTR_InitKamMemory
Syntax            : void BTRCTR_InitKamMemory( void )
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
void BTRCTR_InitKamMemory( void )
{
    TeBTRCTR_e_SysBatteryMode = BTRM_MODE_INIT;
#if (BTRCTR_ENABLE == BTRCTR_LOAD_BATTERY_ENABLE)
    TeBTRCTR_e_LoadBatteryMode = BTRM_MODE_INIT ;
#endif
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
static void BTRCTR_UpdataBatteryAdValue(void)
{
#if(BTRCTR_ENABLE == BTRCTR_CANVOLENABLE)
    uint8  TempCanBatteryStatus = (uint8)FALSE;
    uint16 TempCanVoltageValue;
    uint16 TempBatteryAdValue;
    uint16 TempCanVoltageAdValue;
    
    TempCanBatteryStatus = BTRCTR_GetCanBatteryVoltageValue(&TempCanVoltageValue);
    TempBatteryAdValue =  BTRCTR_GetBatteryAdValue();
    TempCanVoltageAdValue = CANVOLTAGE2AD(TempCanVoltageValue);
    
    if(((uint8)TRUE == TempCanBatteryStatus)
        &&(((TempBatteryAdValue < BTRCTR_SYS_BATTERY_B2A_UP_VOLT)&&(TempCanVoltageAdValue < BTRCTR_SYS_BATTERY_B2A_DOWN_VOLT)&&(TempCanVoltageAdValue > TempBatteryAdValue)) \
        ||((TempBatteryAdValue > BTRCTR_SYS_BATTERY_B2A_DOWN_VOLT)&&(TempCanVoltageAdValue > BTRCTR_SYS_BATTERY_B2A_UP_VOLT)&&(TempCanVoltageAdValue < TempBatteryAdValue))))
    {
        TsBTRCTR_h_AD.usSysBatteryAd = TempCanVoltageAdValue;
    }
    else
#endif
    {
        TsBTRCTR_h_AD.usSysBatteryAd = BTRCTR_GetBatteryAdValue();
    }
#if (BTRCTR_ENABLE == BTRCTR_LOAD_BATTERY_ENABLE)
    TsBTRCTR_h_AD.usLoadBatteryAd = BTRCTR_GetBatteryAdValue();
#endif
}
/*******************************************************************************
Name              : BTRCTR_ModeFunction
Syntax            : void BTRCTR_ModeFunction( void )
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
void BTRCTR_ModeFunction(void)
{
    BTRCTR_UpdataBatteryAdValue();
    BTRCTR_SysModeJudge();
#if (BTRCTR_ENABLE == BTRCTR_LOAD_BATTERY_ENABLE)
    BTRCTR_LoadModeJudge();
#endif
    //BTRCTR_IsIgon1s();
    //BTRCTR_IsIgon3min();
}

/*******************************************************************************
Name              : BTRCTR_SysModeJudge
Syntax            : void BTRCTR_SysModeJudge( void )
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
static void BTRCTR_SysModeJudge( void )
{
    switch(TeBTRCTR_e_SysBatteryMode)
    {
        case BTRM_MODE_INIT:
        {
            BTRCTR_SysModeFastJudge();
            break;
        }

        case BTRM_MODE_A:
        {
            BTRCTR_SysModeAJudge();
            break;
        }

        case BTRM_MODE_B:
        {
            BTRCTR_SysModeBJudge();
            break;
        }
#if (BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_MODE_C_ENABLE)
        case BTRM_MODE_C:
        {
            BTRCTR_SysModeCJudge();
            break;
        }
#endif
#if (BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_MODE_D_ENABLE)
        case BTRM_MODE_D:
        {
            BTRCTR_SysModeDJudge();
            break;
        }
#endif
/* polyspace<RTE:UNR:Low:Other> no effect */
        default:
        {
            TeBTRCTR_e_SysBatteryMode = BTRM_MODE_INIT;
            BTRCTR_InitMemory();
            break;
        }
    }
}

/*******************************************************************************
Name              : BTRCTR_SysModeFastJudge
Syntax            : void BTRCTR_SysModeFastJudge( void )
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
static void BTRCTR_SysModeFastJudge(void)
{
    TsBTRCTR_h_AD.usSysFastAdBuff[TsBTRCTR_h_AD.ucSysFilterCnt1] = TsBTRCTR_h_AD.usSysBatteryAd;
    TsBTRCTR_h_AD.ucSysFilterCnt1++;

    if(TsBTRCTR_h_AD.ucSysFilterCnt1 >= BTRCTR_FILTER_TIME_FAST)
    {
        LIB_BubbleSort(TsBTRCTR_h_AD.usSysFastAdBuff, TsBTRCTR_h_AD.ucSysFilterCnt1);
        TsBTRCTR_h_AD.usSysBatteryAd = TsBTRCTR_h_AD.usSysFastAdBuff[BTRCTR_FILTER_TIME_FAST / (uint8)2];
        TsBTRCTR_h_AD.ucSysFilterCnt1 = 0u;

        if ( (TsBTRCTR_h_AD.usSysBatteryAd >= (uint16)BTRCTR_SYS_BATTERY_B2A_UP_VOLT ) && ( TsBTRCTR_h_AD.usSysBatteryAd <= (uint16)BTRCTR_SYS_BATTERY_B2A_DOWN_VOLT))
        {
            TeBTRCTR_e_SysBatteryMode = BTRM_MODE_A;	/*if battery voltage is larger than 9V and lower than 16V,set battery mode to mode A*/
        }

#if (BTRCTR_ENABLE  == BTRCTR_SYS_BATTERY_MODE_C_ENABLE)
        else if ( ( TsBTRCTR_h_AD.usSysBatteryAd >= BTRCTR_SYS_BATTERY_C2B_UP_VOLT) && (TsBTRCTR_h_AD.usSysBatteryAd <= BTRCTR_SYS_BATTERY_C2B_DOWN_VOLT))
        {
            TeBTRCTR_e_SysBatteryMode = BTRM_MODE_B;	/*if battery voltage is larger than 7V and lower than 18V,set battery mode to mode B*/
        }
        else
        {
            TeBTRCTR_e_SysBatteryMode = BTRM_MODE_C;	/*set battery mode to mode C*/
        }

#else
        else
        {
            TeBTRCTR_e_SysBatteryMode = BTRM_MODE_B;	/*set battery mode to mode C*/
        }

#endif

    }
}

/*******************************************************************************
Name              : BTRCTR_SysModeAJudge
Syntax            : void BTRCTR_SysModeAJudge( void )
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
static void BTRCTR_SysModeAJudge(void)
{
    /*in mode A, battery voltage is larger than 16.5V,set battery mode to mode B*/
    if( TsBTRCTR_h_AD.usSysBatteryAd >= (uint16)BTRCTR_SYS_BATTERY_A2B_UP_VOLT )
    {
        if( TsBTRCTR_h_AD.ucSysFilterCnt1 >= BTRCTR_FILTER_TIME_NORMAL )/*arrived to filtering time*/
        {
            TeBTRCTR_e_SysBatteryMode = BTRM_MODE_B;/*set battery mode to mode B*/
            TsBTRCTR_h_AD.ucSysFilterCnt1 = 0u;		/*reset filtering time count*/
        }

        TsBTRCTR_h_AD.ucSysFilterCnt1++;
    }
    else
    {
        TsBTRCTR_h_AD.ucSysFilterCnt1 = 0u;
    }

    if( TsBTRCTR_h_AD.usSysBatteryAd <= (uint16)BTRCTR_SYS_BATTERY_A2B_DOWN_VOLT )/*in mode A, battery voltage is lower than 8.5V,set battery mode to mode B*/
    {

        if( TsBTRCTR_h_AD.ucSysFilterCnt2 >= BTRCTR_FILTER_TIME_NORMAL )/*arrived to filtering time*/
        {
            TeBTRCTR_e_SysBatteryMode = BTRM_MODE_B;/*set battery mode to mode B*/
            TsBTRCTR_h_AD.ucSysFilterCnt2 = 0u;/*reset filtering time count*/
        }

        TsBTRCTR_h_AD.ucSysFilterCnt2++;
    }
    else
    {
        TsBTRCTR_h_AD.ucSysFilterCnt2 = 0u;	/*reset filtering time count*/
    }
#if (BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_MODE_D_ENABLE)

    if ((TsBTRCTR_h_AD.usSysBatteryAd >= (uint16)BTRCTR_SYS_BATTERY_A2D_UP_VOLT) && (TsBTRCTR_h_AD.usSysBatteryAd <= (uint16)BTRCTR_SYS_BATTERY_A2D_DOWN_VOLT))
    {
        if (TsBTRCTR_h_AD.ucSysFilterCnt3 >= BTRCTR_FILTER_20MS) /*arrived to filtering time*/
        {
            TeBTRCTR_e_SysBatteryMode = BTRM_MODE_D; /*set battery mode to mode B*/
            TsBTRCTR_h_AD.ucSysFilterCnt3 = 0u;      /*reset filtering time count*/
        }
        TsBTRCTR_h_AD.ucSysFilterCnt3++;
    }
    else
    {
        TsBTRCTR_h_AD.ucSysFilterCnt3 = 0u;
    }

#endif
}

/*******************************************************************************
Name              : BTRCTR_SysModeBJudge
Syntax            : STATIC void BTRCTR_SysModeBJudge(void)
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
static void BTRCTR_SysModeBJudge(void)
{
    /*in mode B, battery voltage is larger than 9V and lower than 16V,set battery mode to mode A*/
    if(( TsBTRCTR_h_AD.usSysBatteryAd >= (uint16)BTRCTR_SYS_BATTERY_B2A_UP_VOLT ) && ( TsBTRCTR_h_AD.usSysBatteryAd <= (uint16)BTRCTR_SYS_BATTERY_B2A_DOWN_VOLT ))
    {
        if( TsBTRCTR_h_AD.ucSysFilterCnt1 >= BTRCTR_FILTER_TIME_NORMAL )/*arrived to filtering time*/
        {
            TeBTRCTR_e_SysBatteryMode = BTRM_MODE_A;/*set battery mode to mode B*/
            TsBTRCTR_h_AD.ucSysFilterCnt1 = 0u;		/*reset filtering time count*/
        }
        TsBTRCTR_h_AD.ucSysFilterCnt1++;
    }
    else
    {
        TsBTRCTR_h_AD.ucSysFilterCnt1 = 0u;
    }

#if (BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_MODE_C_ENABLE)

    /*in mdoe B, battery voltage is lower than 6.5V or larger than 18.5V,set battery mode to mode C*/
    if(( TsBTRCTR_h_AD.usSysBatteryAd > BTRCTR_SYS_BATTERY_B2C_UP_VOLT ) || ( TsBTRCTR_h_AD.usSysBatteryAd < BTRCTR_SYS_BATTERY_B2C_DOWN_VOLT ))
    {
        if ( TsBTRCTR_h_AD.ucSysFilterCnt2 >= BTRCTR_FILTER_TIME_NORMAL )/*arrived to filtering time*/
        {
            TeBTRCTR_e_SysBatteryMode = BTRM_MODE_C;/*set battery mode to mode B*/
            TsBTRCTR_h_AD.ucSysFilterCnt2 = 0u;/*reset filtering time count*/
        }

        TsBTRCTR_h_AD.ucSysFilterCnt2++;
    }
    else
    {
        TsBTRCTR_h_AD.ucSysFilterCnt2 = 0u;	/*reset filtering time count*/
    }

#endif
}
#if (BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_MODE_C_ENABLE)
/*******************************************************************************
Name              : BTRCTR_SysModeCJudge
Syntax            : STATIC void BTRCTR_SysModeCJudge(void)
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
static void BTRCTR_SysModeCJudge(void)
{
    /*in mode C, battery voltage is larger than 7V and lower than 18V,set battery mode to mode B*/
    if(( TsBTRCTR_h_AD.usSysBatteryAd >= BTRCTR_SYS_BATTERY_C2B_UP_VOLT ) && ( TsBTRCTR_h_AD.usSysBatteryAd <= BTRCTR_SYS_BATTERY_C2B_DOWN_VOLT ))
    {   
        if( TsBTRCTR_h_AD.ucSysFilterCnt1 >= BTRCTR_FILTER_TIME_NORMAL )/*arrived to filtering time*/
        {
            TeBTRCTR_e_SysBatteryMode = BTRM_MODE_B;/*set battery mode to mode B*/
            TsBTRCTR_h_AD.ucSysFilterCnt1 = 0u;		/*reset filtering time count*/
        }

        TsBTRCTR_h_AD.ucSysFilterCnt1++;
    }
    else
    {
        TsBTRCTR_h_AD.ucSysFilterCnt1 = 0u;	/*reset filtering time count*/
    }
}
#endif
#if (BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_MODE_D_ENABLE)
/*******************************************************************************
Name              : BTRCTR_SysModeDJudge
Syntax            : STATIC void BTRCTR_SysModeDJudge(void)
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
static void BTRCTR_SysModeDJudge(void)
{
    if( TsBTRCTR_h_AD.usSysBatteryAd <= (uint16)BTRCTR_SYS_BATTERY_D2A_DOWN_VOLT )/*in mode A, battery voltage is lower than 8.5V,set battery mode to mode B*/
    {

        if( TsBTRCTR_h_AD.ucSysFilterCnt1 >= BTRCTR_FILTER_10MS )/*arrived to filtering time*/
        {
            TeBTRCTR_e_SysBatteryMode = BTRM_MODE_A;/*set battery mode to mode B*/
            TsBTRCTR_h_AD.ucSysFilterCnt1 = 0u;/*reset filtering time count*/
        }

        TsBTRCTR_h_AD.ucSysFilterCnt1++;
    }
    else
    {
        TsBTRCTR_h_AD.ucSysFilterCnt1 = 0u;	/*reset filtering time count*/
    }
    if( TsBTRCTR_h_AD.usSysBatteryAd >= (uint16)BTRCTR_SYS_BATTERY_D2B_UP_VOLT )
    {

        if( TsBTRCTR_h_AD.ucSysFilterCnt2 >= BTRCTR_FILTER_TIME_NORMAL )/*arrived to filtering time*/
        {
            TeBTRCTR_e_SysBatteryMode = BTRM_MODE_B;/*set battery mode to mode B*/
            TsBTRCTR_h_AD.ucSysFilterCnt2 = 0u;/*reset filtering time count*/
        }

        TsBTRCTR_h_AD.ucSysFilterCnt2++;
    }
    else
    {
        TsBTRCTR_h_AD.ucSysFilterCnt2 = 0u;	/*reset filtering time count*/
    }
}
#endif
/*******************************************************************************
Name              : BTRCTR_GetSysBatteryVolt
Syntax            :uint16 BTRCTR_GetSysBatteryVolt(void)
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
uint16 BTRCTR_GetSysBatteryVolt(void)
{
    return TsBTRCTR_h_AD.usSysBatteryAd ;
}

/*******************************************************************************
Name              : BTRCTR_GetSYSBatteryModeAStatus
Syntax            : uint8 BTRCTR_GetSYSBatteryModeAStatus(void)
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
uint8 BTRCTR_GetSysBatteryModeAStatus(void)
{
    return (uint8)( BTRM_MODE_A == TeBTRCTR_e_SysBatteryMode  );
}

/*******************************************************************************
Name              : BTRCTR_GetSYSBatteryModeBStatus
Syntax            : uint8 BTRCTR_GetSYSBatteryModeBStatus(void)
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
uint8 BTRCTR_GetSysBatteryModeBStatus(void)
{
    return (uint8)( BTRM_MODE_B == TeBTRCTR_e_SysBatteryMode  );
}

#if (BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_MODE_C_ENABLE)
/*******************************************************************************
Name              : BTRCTR_GetSYSBatteryModeCStatus
Syntax            : uint8 BTRCTR_GetSYSBatteryModeCStatus(void)
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
uint8 BTRCTR_GetSysBatteryModeCStatus(void)
{
    return (uint8)( BTRM_MODE_C == TeBTRCTR_e_SysBatteryMode  );
}
#endif
#if (BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_MODE_D_ENABLE)
/*******************************************************************************
Name              : BTRCTR_GetSYSBatteryModeCStatus
Syntax            : uint8 BTRCTR_GetSYSBatteryModeCStatus(void)
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
uint8 BTRCTR_GetSysBatteryModeDStatus(void)
{
    return (uint8)( BTRM_MODE_D == TeBTRCTR_e_SysBatteryMode  );
}
#endif
#if (BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_LOW_VOL_ENABLE)
/*******************************************************************************
Name              : BTRCTR_GetHighVoltageStatus
Syntax            : uint8 BTRCTR_GetHighVoltageStatus(void)
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
uint8 BTRCTR_GetHighVoltageStatus(void)
{
    const uint16 TempBatteryAd = BTRCTR_GetBatteryAdValue() ;

    if(TempBatteryAd > (uint16)BTRCTR_THRESHOLD_HIGH_BATTERY_IN )
    {
        TsBTRCTR_h_AD.ucHighVoltageStatus = TRUE;
    }
    else if(TempBatteryAd < (uint16)BTRCTR_THRESHOLD_HIGH_BATTERY_OUT)
    {
        TsBTRCTR_h_AD.ucHighVoltageStatus = FALSE;
    }
	else	
	{}

    return ( TsBTRCTR_h_AD.ucHighVoltageStatus );
}
/*******************************************************************************
Name              : BTRCTR_GetLowVoltageStatus
Syntax            : uint8 BTRCTR_GetLowVoltageStatus(void)
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
uint8 BTRCTR_GetSysLowVoltageStatus(void)
{
    uint16 TempBatteryAd;
    TempBatteryAd = BTRCTR_GetBatteryAdValue() ;

    if(TempBatteryAd < BTRCTR_SYS_THRESHOLD_LOW_BATTERY_IN )
    {
        TsBTRCTR_h_AD.ucSysLowVoltageStatus = TRUE;
    }
    else if(TempBatteryAd > BTRCTR_SYS_THRESHOLD_LOW_BATTERY_OUT)
    {
        TsBTRCTR_h_AD.ucSysLowVoltageStatus = FALSE;
    }
    else
    {}

    return ( TsBTRCTR_h_AD.ucSysLowVoltageStatus );
}
#endif /*  BTRCTR_ENABLE == BTRCTR_SYS_BATTERY_LOW_VOL_ENABLE */

#if (BTRCTR_ENABLE == BTRCTR_LOAD_BATTERY_ENABLE)
/*******************************************************************************
Name              : BTRCTR_MotorModeJudge
Syntax            : void BTRCTR_MotorModeJudge( void )
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
static void BTRCTR_LoadModeJudge( void )
{
    TsBTRCTR_h_AD.usLoadBatteryAd = BTRCTR_GetLoadBatAdValue();

    /*Step Motor*/
    switch( TeBTRCTR_e_LoadBatteryMode )
    {
		case BTRM_MODE_INIT :			/*in A mode*/
		{
			BTRCTR_LoadModeFastJudge();
			break;
		}
			
        case BTRM_MODE_A :			/*in A mode*/
		{
			BTRCTR_LoadModeAJudge();
			break;
		}

        case BTRM_MODE_B :			/*in B mode*/
		{
			BTRCTR_LoadModeBJudge();
			break;
		}

        default :
		{
			TeBTRCTR_e_LoadBatteryMode = BTRM_MODE_B ;
			break ;
		}
    }
}

/*******************************************************************************
Name              : BTRCTR_SysModeFastJudge
Syntax            : void BTRCTR_SysModeFastJudge( void )
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
static void BTRCTR_LoadModeFastJudge(void)
{
    TsBTRCTR_h_AD.usLoadFastAdBuff[TsBTRCTR_h_AD.ucLoadFilterCnt1] = TsBTRCTR_h_AD.usLoadBatteryAd;
    TsBTRCTR_h_AD.ucLoadFilterCnt1++;

    if(TsBTRCTR_h_AD.ucLoadFilterCnt1 >= BTRCTR_LOAD_FILTER_TIME_FAST)
    {
        LIB_BubbleSort(TsBTRCTR_h_AD.usLoadFastAdBuff, TsBTRCTR_h_AD.ucLoadFilterCnt1);
        TsBTRCTR_h_AD.usLoadBatteryAd = TsBTRCTR_h_AD.usLoadFastAdBuff[BTRCTR_LOAD_FILTER_TIME_FAST / (uint8)2];
        TsBTRCTR_h_AD.ucLoadFilterCnt1 = 0u;

        if ( (TsBTRCTR_h_AD.usLoadBatteryAd >= (uint16)BTRCTR_LOAD_BATTERY_B2A_UP_VOLT ) && ( TsBTRCTR_h_AD.usLoadBatteryAd <= (uint16)BTRCTR_LOAD_BATTERY_B2A_DOWN_VOLT))
        {
            TeBTRCTR_e_LoadBatteryMode = BTRM_MODE_A;	/*if battery voltage is larger than 9V and lower than 16V,set battery mode to mode A*/
        }
        else
        {
            TeBTRCTR_e_LoadBatteryMode = BTRM_MODE_B;	/*set battery mode to mode C*/
        }

    }
}

/*******************************************************************************
Name              : BTRCTR_MotorModeAJudge
Syntax            : STATIC void BTRCTR_MotorModeAJudge(void)
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
static void BTRCTR_LoadModeAJudge(void)
{
    if( TsBTRCTR_h_AD.usLoadBatteryAd >= BTRCTR_LOAD_BATTERY_A2B_UP_VOLT )
    {
        if( TsBTRCTR_h_AD.ucLoadFilterCnt1 >= BTRCTR_LOAD_FILTER_TIME_ABNORMAL )
        {
            TeBTRCTR_e_LoadBatteryMode = BTRM_MODE_B ;
            TsBTRCTR_h_AD.ucLoadFilterCnt1 = 0u ;
        }

        TsBTRCTR_h_AD.ucLoadFilterCnt1++;
    }
    else
    {
        TsBTRCTR_h_AD.ucLoadFilterCnt1 = 0u ;
    }

    if(TsBTRCTR_h_AD.usLoadBatteryAd < BTRCTR_LOAD_BATTERY_A2B_DOWN_VOLT)
    {
        if( TsBTRCTR_h_AD.ucLoadFilterCnt2 >= BTRCTR_LOAD_FILTER_TIME_ABNORMAL )
        {
            TeBTRCTR_e_LoadBatteryMode = BTRM_MODE_B ;
            TsBTRCTR_h_AD.ucLoadFilterCnt2 = 0u ;
        }

        TsBTRCTR_h_AD.ucLoadFilterCnt2++;
    }
    else
    {
        TsBTRCTR_h_AD.ucLoadFilterCnt2 = 0u ;
    }
}

/*******************************************************************************
Name              : BTRCTR_MotorModeBJudge
Syntax            : STATIC void BTRCTR_MotorModeBJudge(void)
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
static void BTRCTR_LoadModeBJudge(void)
{
    if( ( TsBTRCTR_h_AD.usLoadBatteryAd < BTRCTR_LOAD_BATTERY_B2A_DOWN_VOLT ) && ( TsBTRCTR_h_AD.usLoadBatteryAd >= BTRCTR_LOAD_BATTERY_B2A_UP_VOLT ) )
    {
        if( TsBTRCTR_h_AD.ucLoadFilterCnt1 >= BTRCTR_LOAD_FILTER_TIME_NORMAL )
        {
            TeBTRCTR_e_LoadBatteryMode = BTRM_MODE_A ;
            TsBTRCTR_h_AD.ucLoadFilterCnt1 = 0u ;
        }

        TsBTRCTR_h_AD.ucLoadFilterCnt1++;
    }
    else
    {
        TsBTRCTR_h_AD.ucLoadFilterCnt1 = 0u ;
    }
}

/*******************************************************************************
Name              : BTRCTR_GetMotorBatteryModeAStatus
Syntax            :uint8 BTRCTR_GetMotorBatteryModeAStatus(void)
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
uint8 BTRCTR_GetLoadBatteryModeAStatus(void)
{
    return (uint8)( BTRM_MODE_A == TeBTRCTR_e_SysBatteryMode  );
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
uint8 BTRCTR_GetLoadBatteryModeBStatus(void)
{
    return (uint8)( BTRM_MODE_B == TeBTRCTR_e_LoadBatteryMode  );
}

#if (BTRCTR_ENABLE == BTRCTR_LOAD_BATTERY_LOW_VOL_ENABLE)
/*******************************************************************************
Name              : BTRCTR_GetLowVoltageStatus
Syntax            : uint8 BTRCTR_GetLowVoltageStatus(void)
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
uint8 BTRCTR_GetLoadLowVoltageStatus(void)
{
    uint16 TempBatteryAd;
    TempBatteryAd = BTRCTR_GetBatteryAdValue() ;

    if(TempBatteryAd < BTRCTR_LOAD_THRESHOLD_LOW_BATTERY_IN )
    {
        TsBTRCTR_h_AD.ucLoadLowVoltageStatus = TRUE;
    }
    else if(TempBatteryAd > BTRCTR_LOAD_THRESHOLD_LOW_BATTERY_OUT)
    {
        TsBTRCTR_h_AD.ucLoadLowVoltageStatus = FALSE;
    }
	else
	{}

    return ( TsBTRCTR_h_AD.ucLoadLowVoltageStatus );
}
#endif /* BTRCTR_ENABLE == BTRCTR_LOAD_BATTERY_LOW_VOL_ENABLE */
#endif /* BTRCTR_ENABLE == BTRCTR_LOAD_BATTERY_ENABLE */

uint16 BTRCTR_Get_KL30_VoltValue(void) // accuracy=0.1v
{

    uint16 TempBatteryAd = 0u;
    float tempDerivedValue = 0;
    uint16 tempVOLT = 0u;
    TempBatteryAd = BTRCTR_GetBatteryAdValue();
    tempDerivedValue = (TempBatteryAd / 153.9) + 0.03;
    tempDerivedValue = tempDerivedValue * 10;

    tempVOLT = (uint16)tempDerivedValue;
    return tempVOLT;
}





/*EOF*/
