/*******************************************************************************
|  File Name:  SrCpid_CallBack.c
|  Description:  Implementation of the Sensor Cpid Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| SHB           Hongbai Song           CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 2016-12-01    01.00.00     SHB       Creation
|
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "SysTypes.h"
#include "STD_SrM.h"

#if (SRM_CPID_EN_CLASS == SRM_ENABLE)
/*******************************************************************************
|    Macro Definition
|******************************************************************************/
/* Sensor CPID enable mask */
#define SRCPID_TEMP_DAT1_CPID_ENABLE_MASK				(0x00000001u)			/*cpid mask for set&clear CPID value,please don't modify*/
#define SRCPID_TEMP_DAT2_CPID_ENABLE_MASK				(0x00000002u)
#define SRCPID_TEMP_DAT3_CPID_ENABLE_MASK				(0x00000004u)
#define SRCPID_TEMP_DAT4_CPID_ENABLE_MASK				(0x00000008u)
#define SRCPID_TEMP_DAT5_CPID_ENABLE_MASK				(0x00000010u)
#define SRCPID_TEMP_DAT6_CPID_ENABLE_MASK				(0x00000020u)
#define SRCPID_TEMP_DAT7_CPID_ENABLE_MASK				(0x00000040u)
#define SRCPID_TEMP_DAT8_CPID_ENABLE_MASK				(0x00000080u)
#define SRCPID_TEMP_HUMIDITY_CPID_ENABLE_MASK			(0x00000100u)
#define SRCPID_TEMP_INCAR_CPID_ENABLE_MASK				(0x00000200u)
#define SRCPID_TEMP_PCAT_CPID_ENABLE_MASK				(0x00000400u)
#define SRCPID_TEMP_WINDSCREEN_CPID_ENABLE_MASK			(0x00000800u)
#define SRCPID_TEMP_EVAP_CPID_ENABLE_MASK				(0x00001000u)
#define SRCPID_SOLAR_INDENSITY_CPID_ENABLE_MASK			(0x00002000u)
#define SRCPID_SOLAR_AMBIENT_CPID_ENABLE_MASK			(0x00004000u)
#define SRCPID_SOLAR_ELEVATION_CPID_ENABLE_MASK			(0x00008000u)
#define SRCPID_SOLAR_AZIMUTH_CPID_ENABLE_MASK			(0x00010000u)
#define SRCPID_HUMIDITY_CPID_ENABLE_MASK				(0x00020000u)
#define SRCPID_AIR_QUALITY_CPID_ENABLE_MASK				(0x00040000u)
#define SRCPID_TEMP_OUTSIDE_CPID_ENABLE_MASK			(0x00080000u)
#define SRCPID_TEMP_WATER_CPID_ENABLE_MASK				(0x00100000u)
#define SRCPID_TEMP_PTC_CPID_ENABLE_MASK				(0x00200000u)

/* 1 = enable ,0 = disable*/
#define SRCPIDCFG_TEMP_OUTSIDE_ENABLE					(1u)
#define SRCPIDCFG_TEMP_WATER_ENABLE						(1u)
#define SRCPIDCFG_TEMP_PTC_ENABLE						(1u)

/*NO.1***********************DAT1*********************************/
#define SRCPIDCFG_TEMP_DAT1_CPID_BIT_MASK				(0x04u)					/*CPID control mask bit in LpCPID_u_DataPtr[0U]*/
#define SRCPIDCFG_TEMP_DAT1_CPID_DATA_INDEX				(3u)					/*CPID value index in LpCPID_u_DataPtr[]*/
#define SRCPIDCFG_TEMP_DAT1_CPID_HIGH					(850)

/*NO.2***********************DAT2*********************************/
#define SRCPIDCFG_TEMP_DAT2_CPID_BIT_MASK				(0x04u)
#define SRCPIDCFG_TEMP_DAT2_CPID_DATA_INDEX				(2u)
#define SRCPIDCFG_TEMP_DAT2_CPID_HIGH					(850)

/*NO.3***********************DAT3*********************************/
#define SRCPIDCFG_TEMP_DAT3_CPID_BIT_MASK				(0x08u)
#define SRCPIDCFG_TEMP_DAT3_CPID_DATA_INDEX				(4u)
#define SRCPIDCFG_TEMP_DAT3_CPID_HIGH					(850)

/*NO.4***********************DAT4*********************************/
#define SRCPIDCFG_TEMP_DAT4_CPID_BIT_MASK				(0x01u)
#define SRCPIDCFG_TEMP_DAT4_CPID_DATA_INDEX				(1u)
#define SRCPIDCFG_TEMP_DAT4_CPID_HIGH					(850)

/*NO.5***********************DAT5*********************************/
#define SRCPIDCFG_TEMP_DAT5_CPID_BIT_MASK				(0x02u)
#define SRCPIDCFG_TEMP_DAT5_CPID_DATA_INDEX				(2u)
#define SRCPIDCFG_TEMP_DAT5_CPID_HIGH					(850)

/*NO.6***********************DAT6*********************************/
#define SRCPIDCFG_TEMP_DAT6_CPID_BIT_MASK				(0x04u)
#define SRCPIDCFG_TEMP_DAT6_CPID_DATA_INDEX				(3u)
#define SRCPIDCFG_TEMP_DAT6_CPID_HIGH					(850)

/*NO.7***********************DAT7*********************************/
#define SRCPIDCFG_TEMP_DAT7_CPID_BIT_MASK				(0x04u)
#define SRCPIDCFG_TEMP_DAT7_CPID_DATA_INDEX				(2u)
#define SRCPIDCFG_TEMP_DAT7_CPID_HIGH					(850)

/*NO.8***********************DAT8*********************************/
#define SRCPIDCFG_TEMP_DAT8_CPID_BIT_MASK				(0x04u)
#define SRCPIDCFG_TEMP_DAT8_CPID_DATA_INDEX				(2u)
#define SRCPIDCFG_TEMP_DAT8_CPID_HIGH					(850)

/*NO.9*********************Temp Humidity**************************/
#define SRCPIDCFG_TEMP_HUMIDITY_CPID_BIT_MASK			(0x01u)
#define SRCPIDCFG_TEMP_HUMIDITY_CPID_DATA_INDEX			(1u)
#define SRCPIDCFG_TEMP_HUMIDITY_CPID_HIGH				(850)

/*NO.10********************Temp Incar*****************************/
#define SRCPIDCFG_TEMP_INCAR_CPID_BIT_MASK				(0x01u)
#define SRCPIDCFG_TEMP_INCAR_CPID_DATA_INDEX			(1u)
#define SRCPIDCFG_TEMP_INCAR_CPID_HIGH					(850)

/*NO.11********************Temp Pcat******************************/
#define SRCPIDCFG_TEMP_PCAT_CPID_BIT_MASK				(0x01u)
#define SRCPIDCFG_TEMP_PCAT_CPID_DATA_INDEX				(1u)
#define SRCPIDCFG_TEMP_PCAT_CPID_HIGH					(850)

/*NO.12******************Temp WindScreen**************************/
#define SRCPIDCFG_TEMP_WINDSCREEN_CPID_BIT_MASK			(0x08u)
#define SRCPIDCFG_TEMP_WINDSCREEN_CPID_DATA_INDEX		(4u)
#define SRCPIDCFG_TEMP_WINDSCREEN_CPID_HIGH				(850)

/*NO.13********************Temp Evap******************************/
#define SRCPIDCFG_TEMP_EVAP_CPID_BIT_MASK				(0x01u)
#define SRCPIDCFG_TEMP_EVAP_CPID_DATA_INDEX				(1u)
#define SRCPIDCFG_TEMP_EVAP_CPID_HIGH					(850)

/*NO.14*******************Solar indensity*************************/
#define SRCPIDCFG_SOLAR_INDENSITY_CPID_BIT_MASK			(0x08u)
#define SRCPIDCFG_SOLAR_INDENSITY_CPID_DATA_INDEX		(3u)
#define SRCPIDCFG_SOLAR_INDENSITY_CPID_LOW				(0u)
#define SRCPIDCFG_SOLAR_INDENSITY_CPID_HIGH				(204)
#define SRCPIDCFG_SOLAR_INDENSITY_MAX					(1200u)

/*NO.15*******************Solar Ambient***************************/
#define SRCPIDCFG_SOLAR_AMBIENT_CPID_BIT_MASK			(0x08u)
#define SRCPIDCFG_SOLAR_AMBIENT_CPID_DATA_INDEX			(3u)
#define SRCPIDCFG_SOLAR_AMBIENT_CPID_LOW				(0u)
#define SRCPIDCFG_SOLAR_AMBIENT_CPID_HIGH				(0)

/*NO.16*******************Solar Elevation*************************/
#define SRCPIDCFG_SOLAR_ELEVATION_CPID_BIT_MASK			(0x08u)
#define SRCPIDCFG_SOLAR_ELEVATION_CPID_DATA_INDEX		(3u)
#define SRCPIDCFG_SOLAR_ELEVATION_CPID_LOW				(0u)
#define SRCPIDCFG_SOLAR_ELEVATION_CPID_HIGH				(0)

/*NO.17*******************Solar Azimuth***************************/
#define SRCPIDCFG_SOLAR_AZIMUTH_CPID_BIT_MASK			(0x08u)
#define SRCPIDCFG_SOLAR_AZIMUTH_CPID_DATA_INDEX			(3u)
#define SRCPIDCFG_SOLAR_AZIMUTH_CPID_LOW				(0u)
#define SRCPIDCFG_SOLAR_AZIMUTH_CPID_HIGH				(0)

/*NO.18*********************Humidity******************************/
#define SRCPIDCFG_HUMIDITY_CPID_BIT_MASK				(0x02u)
#define SRCPIDCFG_HUMIDITY_CPID_DATA_INDEX				(2u)
#define SRCPIDCFG_HUMIDITY_CPID_LOW						(0u)
#define SRCPIDCFG_HUMIDITY_CPID_HIGH					(100)

/*NO.19*********************Air quality***************************/
#define SRCPIDCFG_AIR_QUALITY_CPID_BIT_MASK				(0x08u)
#define SRCPIDCFG_AIR_QUALITY_CPID_DATA_INDEX			(3u)
#define SRCPIDCFG_AIR_QUALITY_CPID_LOW					(0u)
#define SRCPIDCFG_AIR_QUALITY_CPID_HIGH					(1000)

/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/
typedef struct
{
    uint8 CpidEnableStatus;
    sint16 CpidValidValue;
} stCpidCtrl;
/*******************************************************************************
|    Static local KAM variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/


static stCpidCtrl SRM_CODE_RAM CpidCtrlTable[SRCFG_CH_MAX_NUM];


/*******************************************************************************
|    Table Const Definition
|******************************************************************************/

/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/
static void SRCPID_ClearValidValue( SRCFG_CH_Enum Channel );
static void SRCPID_SetValidValue( SRCFG_CH_Enum Channel, sint16 CpidValue );

/*******************************************************************************
|    Function Source Code
|******************************************************************************/


/*******************************************************************************
Name			: SRCPID_ClearValidValue
Syntax			: STATIC void SRCPID_ClearValidValue( uint8 Channel )
Sync/Async		: Async
Reentrancy		:
Parameters(in)	: Channel				: Sensor channel
Parameters(out) : None					:-
Return value	: None					:-
Description		: clear cpid enable flag and cpid value
Call By			: SRCPID
|******************************************************************************/
static void SRCPID_ClearValidValue( SRCFG_CH_Enum Channel )
{
    if ( SRCFG_CH_MAX_NUM > Channel )
    {
        CpidCtrlTable[ Channel ].CpidEnableStatus = SRCFG_DISABLE;
        CpidCtrlTable[ Channel ].CpidValidValue = 0x0000;
    }
}

/*******************************************************************************
Name			: SRCPID_SetValidValue
Syntax			: STATIC void SRCPID_SetValidValue( uint8 Channel, sint16 CpidValue )
Sync/Async		: Async
Reentrancy		:
Parameters(in)	: Channel				:-Sensor Channel
Parameters(in)	: CpidValue				:-CPID Set Value
Parameters(out) : None					:-
Return value	: None					:-
Description		: set cpid valid value and cpid enable flag
Call By			: SRCPID
|******************************************************************************/
static void SRCPID_SetValidValue( SRCFG_CH_Enum Channel, sint16 CpidValue )
{
    if ( SRCFG_CH_MAX_NUM > Channel )
    {
        CpidCtrlTable[ Channel ].CpidEnableStatus = SRCFG_ENABLE;
        CpidCtrlTable[ Channel ].CpidValidValue = CpidValue;
    }
}

/*******************************************************************************
Name			: SRCPID_InitMemory
Syntax			: void SRCPID_InitMemory(void)
Sync/Async		: Sync
Reentrancy		:
Parameters(in)	: None					:-
Parameters(out) : None					:-
Return value	: None					:-
Description		: CPID init function
Call By			: SRM
|******************************************************************************/
void SRCPID_InitMemory(void)
{
	uint8 Channel = 0u;

    for ( Channel = 0u; Channel < (uint8)SRCFG_CH_MAX_NUM; Channel++ )
    {
        CpidCtrlTable[Channel].CpidEnableStatus = SRCFG_DISABLE;
        CpidCtrlTable[Channel].CpidValidValue  = 0x0000;
    }
}

/*******************************************************************************
Name			: SRCPID_GetEnableStatus
Syntax			: uint8 SRCPID_GetEnableStatus( uint8 ucChannel )
Sync/Async		: Async
Reentrancy		:
Parameters(in)	: ucChannel				:-Sensor Channel
Parameters(out) : None					:-
Return value	: SensorValidStatus		:-Sensor Cpid Control status
Description		: Get Sensor cpid control status
Call By			: SRCTR
|******************************************************************************/
uint8 SRCPID_GetEnableStatus( SRCFG_CH_Enum ucChannel )
{
    uint8 SensorValidStatus = SRCFG_DISABLE;

    if ( SRCFG_CH_MAX_NUM > ucChannel )
    {
        SensorValidStatus = CpidCtrlTable[ ucChannel ].CpidEnableStatus;
    }

    return SensorValidStatus;
}

/*******************************************************************************
Name			: SRCPID_GetValidValue
Syntax			: sint16 SRCPID_GetValidValue( uint8 ucChannel )
Sync/Async		: Async
Reentrancy		:
Parameters(in)	: ucChannel				:-Sensor Channel
Parameters(out) : None					:-
Return value	: SensorValidValue		:-Sensor cpid valid value
Description		: Get Sensor CPID valid value
Call By			: SRCTR
|******************************************************************************/
sint16 SRCPID_GetValidValue( SRCFG_CH_Enum ucChannel )
{
    sint16 SensorValidValue = 0x0000;

    if ( SRCFG_CH_MAX_NUM > ucChannel )
    {
        SensorValidValue = CpidCtrlTable[ ucChannel ].CpidValidValue;
    }

    return SensorValidValue;
}

/*******************************************************************************
Name			: SRCPID_ClearSpecificSensorValidValue
Syntax			: void SRCPID_ClearSpecificSensorValidValue(uint32 ChannelMask)
Sync/Async		: Async
Reentrancy		:
Parameters(in)	: ChannelMask			:-Sensor channel Mask
Parameters(out) : None					:-
Return value	: None					:-
Description		: Clear sensor CPID valid value
Call By			: CPID_Callback
|******************************************************************************/
void SRCPID_ClearSpecificSensorValidValue(uint32 ChannelMask)/*PRQA S 3408*/
{
#if (SRCFG_TEMP_DAT1_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_DAT1_CPID_ENABLE_MASK) != 0u )
    {
        SRCPID_ClearValidValue(SRCFG_TEMP_DAT1_CH);
    }

#endif
#if (SRCFG_TEMP_DAT2_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_DAT2_CPID_ENABLE_MASK) != 0u )
    {
        SRCPID_ClearValidValue(SRCFG_TEMP_DAT2_CH);
    }

#endif
#if (SRCFG_TEMP_DAT3_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_DAT3_CPID_ENABLE_MASK) != 0u )
    {
        SRCPID_ClearValidValue(SRCFG_TEMP_DAT3_CH);
    }

#endif
#if (SRCFG_TEMP_DAT4_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_DAT4_CPID_ENABLE_MASK) != 0u )
    {
        SRCPID_ClearValidValue(SRCFG_TEMP_DAT4_CH);
    }

#endif
#if (SRCFG_TEMP_DAT5_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_DAT5_CPID_ENABLE_MASK) != 0u )
    {
        SRCPID_ClearValidValue(SRCFG_TEMP_DAT5_CH);
    }

#endif
#if (SRCFG_TEMP_DAT6_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_DAT6_CPID_ENABLE_MASK) != 0u )
    {
        SRCPID_ClearValidValue(SRCFG_TEMP_DAT6_CH);
    }

#endif
#if (SRCFG_TEMP_HUMIDITY_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_HUMIDITY_CPID_ENABLE_MASK) != 0u )
    {
        SRCPID_ClearValidValue(SRCFG_TEMP_HUMIDITY_CH);
    }

#endif
#if (SRCFG_TEMP_INCAR_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_INCAR_CPID_ENABLE_MASK) != 0u )
    {
        SRCPID_ClearValidValue(SRCFG_TEMP_INCAR_CH);
    }

#endif
#if (SRCFG_TEMP_PCAT_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_PCAT_CPID_ENABLE_MASK) != 0u )
    {
        SRCPID_ClearValidValue(SRCFG_TEMP_PCAT_CH);
    }

#endif
#if (SRCFG_TEMP_WINDSCREEN_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_WINDSCREEN_CPID_ENABLE_MASK) != 0u )
    {
        SRCPID_ClearValidValue(SRCFG_TEMP_WINDSCREEN_CH);
    }

#endif
#if (SRCFG_TEMP_EVAP_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_EVAP_CPID_ENABLE_MASK) != 0u )
    {
        SRCPID_ClearValidValue(SRCFG_TEMP_EVAP_CH);
    }

#endif
#if (SRCFG_SOLAR_L_INDENSITY_WH_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_SOLAR_INDENSITY_CPID_ENABLE_MASK) != 0u )
    {
        SRCPID_ClearValidValue(SRCFG_SOLAR_L_INDENSITY_WH_CH);
    }

#endif
#if (SRCFG_SOLAR_R_INDENSITY_WH_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_SOLAR_INDENSITY_CPID_ENABLE_MASK) != 0u )
    {
        SRCPID_ClearValidValue(SRCFG_SOLAR_R_INDENSITY_WH_CH);
    }

#endif
#if (SRCFG_SOLAR_L_INDENSITY_SH_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_SOLAR_INDENSITY_CPID_ENABLE_MASK) != 0u )
    {
        SRCPID_ClearValidValue(SRCFG_SOLAR_L_INDENSITY_SH_CH);
    }

#endif
#if (SRCFG_SOLAR_R_INDENSITY_SH_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_SOLAR_INDENSITY_CPID_ENABLE_MASK) != 0u )
    {
        SRCPID_ClearValidValue(SRCFG_SOLAR_R_INDENSITY_SH_CH);
    }

#endif
#if (SRCFG_HUMIDITY_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_HUMIDITY_CPID_ENABLE_MASK) != 0u )
    {
        SRCPID_ClearValidValue(SRCFG_HUMIDITY_CH);
    }

#endif
#if (SRCFG_AIR_QUALITY_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_AIR_QUALITY_CPID_ENABLE_MASK) != 0u )
    {
        SRCPID_ClearValidValue(SRCFG_AIR_QUALITY_CH);
    }

#endif
}

/*******************************************************************************
Name			: SRCPID_SetSpecificSensorValidValue
Syntax			: void SRCPID_SetSpecificSensorValidValue(uint32 ChannelMask, const uint8 CPIDDataPtr[])
Sync/Async		: Async
Reentrancy		:
Parameters(in)	: ChannelMask			: The specific sensor channel mask of CPID control
Parameters(in)	: CPIDDataPtr[]			: CPID valid value buffer
Parameters(out) : None					:-
Return value	: None					:-
Description		:
Call By			: CPID_callback.c
|******************************************************************************/
void SRCPID_SetSpecificSensorValidValue(uint32 ChannelMask, const uint8 CPIDDataPtr[])/*PRQA S 3408*/
{
    sint16 TmpVal = 0x0000;
#if (SRCFG_TEMP_DAT1_ENABLE == 1u)

    if ((ChannelMask & SRCPID_TEMP_DAT1_CPID_ENABLE_MASK) != 0u )
    {
        if ( (CPIDDataPtr[0u] & SRCPIDCFG_TEMP_DAT1_CPID_BIT_MASK) != 0u )
        {
            TmpVal = (sint16)CPIDDataPtr[SRCPIDCFG_TEMP_DAT1_CPID_DATA_INDEX];		/*CPID y=x*/
            TmpVal *= 10;

            if (TmpVal > SRCPIDCFG_TEMP_DAT1_CPID_HIGH)
            {
                TmpVal = SRCPIDCFG_TEMP_DAT1_CPID_HIGH;
            }

            SRCPID_SetValidValue(SRCFG_TEMP_DAT1_CH, TmpVal);
        }
        else
        {
            SRCPID_ClearValidValue(SRCFG_TEMP_DAT1_CH);
        }
    }

#endif
#if (SRCFG_TEMP_DAT2_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_DAT2_CPID_ENABLE_MASK) != 0u )
    {
        if ( (CPIDDataPtr[0u] & SRCPIDCFG_TEMP_DAT2_CPID_BIT_MASK) != 0u )
        {
            TmpVal = (sint16)CPIDDataPtr[SRCPIDCFG_TEMP_DAT2_CPID_DATA_INDEX];		/*CPID y=x*/
            TmpVal *= 10;

            if (TmpVal > SRCPIDCFG_TEMP_DAT2_CPID_HIGH)
            {
                TmpVal = SRCPIDCFG_TEMP_DAT2_CPID_HIGH;
            }

            SRCPID_SetValidValue(SRCFG_TEMP_DAT2_CH, TmpVal);
        }
        else
        {
            SRCPID_ClearValidValue(SRCFG_TEMP_DAT2_CH);
        }
    }

#endif
#if (SRCFG_TEMP_DAT3_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_DAT3_CPID_ENABLE_MASK) != 0u )
    {
        if ( (CPIDDataPtr[0u] & SRCPIDCFG_TEMP_DAT3_CPID_BIT_MASK) != 0u )
        {
            TmpVal = (sint16)CPIDDataPtr[SRCPIDCFG_TEMP_DAT3_CPID_DATA_INDEX];		/*CPID y=x*/
            TmpVal *= 10;

            if (TmpVal > SRCPIDCFG_TEMP_DAT3_CPID_HIGH)
            {
                TmpVal = SRCPIDCFG_TEMP_DAT3_CPID_HIGH;
            }

            SRCPID_SetValidValue(SRCFG_TEMP_DAT3_CH, TmpVal);
        }
        else
        {
            SRCPID_ClearValidValue(SRCFG_TEMP_DAT3_CH);
        }
    }

#endif
#if (SRCFG_TEMP_DAT4_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_DAT4_CPID_ENABLE_MASK) != 0u )
    {
        if ( (CPIDDataPtr[0u] & SRCPIDCFG_TEMP_DAT4_CPID_BIT_MASK) != 0u )
        {
            TmpVal = (sint16)CPIDDataPtr[SRCPIDCFG_TEMP_DAT4_CPID_DATA_INDEX];		/*CPID y=x*/
            TmpVal *= 10;

            if (TmpVal > SRCPIDCFG_TEMP_DAT4_CPID_HIGH)
            {
                TmpVal = SRCPIDCFG_TEMP_DAT4_CPID_HIGH;
            }

            SRCPID_SetValidValue(SRCFG_TEMP_DAT4_CH, TmpVal);
        }
        else
        {
            SRCPID_ClearValidValue(SRCFG_TEMP_DAT4_CH);
        }
    }

#endif
#if (SRCFG_TEMP_DAT5_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_DAT5_CPID_ENABLE_MASK) != 0u )
    {
        if ( (CPIDDataPtr[0u] & SRCPIDCFG_TEMP_DAT5_CPID_BIT_MASK) != 0u )
        {
            TmpVal = (sint16)CPIDDataPtr[SRCPIDCFG_TEMP_DAT5_CPID_DATA_INDEX];		/*CPID y=x*/
            TmpVal *= 10;

            if (TmpVal > SRCPIDCFG_TEMP_DAT5_CPID_HIGH)
            {
                TmpVal = SRCPIDCFG_TEMP_DAT5_CPID_HIGH;
            }

            SRCPID_SetValidValue(SRCFG_TEMP_DAT5_CH, TmpVal);
        }
        else
        {
            SRCPID_ClearValidValue(SRCFG_TEMP_DAT5_CH);
        }
    }

#endif
#if (SRCFG_TEMP_DAT6_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_DAT6_CPID_ENABLE_MASK) != 0u )
    {
        if ( (CPIDDataPtr[0u] & SRCPIDCFG_TEMP_DAT6_CPID_BIT_MASK) != 0u )
        {
            TmpVal = (sint16)CPIDDataPtr[SRCPIDCFG_TEMP_DAT6_CPID_DATA_INDEX];		/*CPID y=x*/
            TmpVal *= 10;

            if (TmpVal > SRCPIDCFG_TEMP_DAT6_CPID_HIGH)
            {
                TmpVal = SRCPIDCFG_TEMP_DAT6_CPID_HIGH;
            }

            SRCPID_SetValidValue(SRCFG_TEMP_DAT6_CH, TmpVal);
        }
        else
        {
            SRCPID_ClearValidValue(SRCFG_TEMP_DAT6_CH);
        }
    }

#endif
#if (SRCFG_TEMP_HUMIDITY_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_HUMIDITY_CPID_ENABLE_MASK) != 0u )
    {
        if ( (CPIDDataPtr[0u] & SRCPIDCFG_TEMP_HUMIDITY_CPID_BIT_MASK) != 0u )
        {
            TmpVal = (sint16)CPIDDataPtr[SRCPIDCFG_TEMP_HUMIDITY_CPID_DATA_INDEX];		/*CPID y=x*/
            TmpVal *= 10;

            if (TmpVal > SRCPIDCFG_TEMP_HUMIDITY_CPID_HIGH)
            {
                TmpVal = SRCPIDCFG_TEMP_HUMIDITY_CPID_HIGH;
            }

            SRCPID_SetValidValue(SRCFG_TEMP_HUMIDITY_CH, TmpVal);
        }
        else
        {
            SRCPID_ClearValidValue(SRCFG_TEMP_HUMIDITY_CH);
        }
    }

#endif
#if (SRCFG_TEMP_INCAR_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_INCAR_CPID_ENABLE_MASK) != 0u )
    {
        if ( (CPIDDataPtr[0u] & (uint8)SRCPIDCFG_TEMP_INCAR_CPID_BIT_MASK) != (uint8)0u )
        {
            TmpVal = (sint16)CPIDDataPtr[SRCPIDCFG_TEMP_INCAR_CPID_DATA_INDEX];		/*CPID y=x*/
            TmpVal *= 10;

            if (TmpVal > SRCPIDCFG_TEMP_INCAR_CPID_HIGH)
            {
                TmpVal = SRCPIDCFG_TEMP_INCAR_CPID_HIGH;
            }

            SRCPID_SetValidValue(SRCFG_TEMP_INCAR_CH, TmpVal);
        }
        else
        {
            SRCPID_ClearValidValue(SRCFG_TEMP_INCAR_CH);
        }
    }

#endif
#if (SRCFG_TEMP_PCAT_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_PCAT_CPID_ENABLE_MASK) != 0u )
    {
        if ( (CPIDDataPtr[0u] & SRCPIDCFG_TEMP_PCAT_CPID_BIT_MASK) != 0u )
        {
            TmpVal = (sint16)CPIDDataPtr[SRCPIDCFG_TEMP_PCAT_CPID_DATA_INDEX];		/*CPID y=x*/
            TmpVal *= 10;

            if (TmpVal > SRCPIDCFG_TEMP_PCAT_CPID_HIGH)
            {
                TmpVal = SRCPIDCFG_TEMP_PCAT_CPID_HIGH;
            }

            SRCPID_SetValidValue(SRCFG_TEMP_PCAT_CH, TmpVal);
        }
        else
        {
            SRCPID_ClearValidValue(SRCFG_TEMP_PCAT_CH);
        }
    }

#endif
#if (SRCFG_TEMP_WINDSCREEN_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_WINDSCREEN_CPID_ENABLE_MASK) != 0u )
    {
        if ( (CPIDDataPtr[0u] & SRCPIDCFG_TEMP_WINDSCREEN_CPID_BIT_MASK) != 0u )
        {
            TmpVal = (sint16)CPIDDataPtr[SRCPIDCFG_TEMP_WINDSCREEN_CPID_DATA_INDEX];		/*CPID y=x*/
            TmpVal *= 10;

            if (TmpVal > SRCPIDCFG_TEMP_WINDSCREEN_CPID_HIGH)
            {
                TmpVal = SRCPIDCFG_TEMP_WINDSCREEN_CPID_HIGH;
            }

            SRCPID_SetValidValue(SRCFG_TEMP_WINDSCREEN_CH, TmpVal);
        }
        else
        {
            SRCPID_ClearValidValue(SRCFG_TEMP_WINDSCREEN_CH);
        }
    }

#endif
#if (SRCFG_TEMP_EVAP_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_TEMP_EVAP_CPID_ENABLE_MASK) != 0u )
    {
        if ( (CPIDDataPtr[0u] & (uint8)SRCPIDCFG_TEMP_EVAP_CPID_BIT_MASK) != (uint8)0u )
        {
            TmpVal = (sint16)CPIDDataPtr[SRCPIDCFG_TEMP_EVAP_CPID_DATA_INDEX];		/*CPID y=x-40*/
            TmpVal -= 40;
            TmpVal *= 10;

            if (TmpVal > SRCPIDCFG_TEMP_EVAP_CPID_HIGH)
            {
                TmpVal = SRCPIDCFG_TEMP_EVAP_CPID_HIGH;
            }

            SRCPID_SetValidValue(SRCFG_TEMP_EVAP_CH, TmpVal);
        }
        else
        {
            SRCPID_ClearValidValue(SRCFG_TEMP_EVAP_CH);
        }
    }

#endif
#if (SRCFG_SOLAR_L_INDENSITY_WH_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_SOLAR_INDENSITY_CPID_ENABLE_MASK) != 0u )
    {
        if ( (CPIDDataPtr[0u] & (uint8)SRCPIDCFG_SOLAR_INDENSITY_CPID_BIT_MASK) != (uint8)0u )
        {
            TmpVal = (sint16)CPIDDataPtr[SRCPIDCFG_SOLAR_INDENSITY_CPID_DATA_INDEX];        /*CPID x=0-204*/

            if (TmpVal > SRCPIDCFG_SOLAR_INDENSITY_CPID_HIGH)
            {
                TmpVal = SRCPIDCFG_SOLAR_INDENSITY_CPID_HIGH;
            }

            TmpVal = (sint16)(( (uint32)((uint32)TmpVal - SRCPIDCFG_SOLAR_INDENSITY_CPID_LOW) * (uint32)SRCPIDCFG_SOLAR_INDENSITY_MAX)
                              / (uint32)SRCPIDCFG_SOLAR_INDENSITY_CPID_HIGH);
            SRCPID_SetValidValue(SRCFG_SOLAR_L_INDENSITY_WH_CH, TmpVal);
        }
        else
        {
            SRCPID_ClearValidValue(SRCFG_SOLAR_L_INDENSITY_WH_CH);
        }
    }

#endif
#if (SRCFG_SOLAR_R_INDENSITY_WH_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_SOLAR_INDENSITY_CPID_ENABLE_MASK) != 0u )
    {
        if ( (CPIDDataPtr[0u] & (uint8)SRCPIDCFG_SOLAR_INDENSITY_CPID_BIT_MASK) != (uint8)0u )
        {
            TmpVal = (sint16)CPIDDataPtr[SRCPIDCFG_SOLAR_INDENSITY_CPID_DATA_INDEX];        /*CPID x=0-204*/

            if (TmpVal > SRCPIDCFG_SOLAR_INDENSITY_CPID_HIGH)
            {
                TmpVal = SRCPIDCFG_SOLAR_INDENSITY_CPID_HIGH;
            }

            TmpVal = (sint16)(( (uint32)((uint32)TmpVal - SRCPIDCFG_SOLAR_INDENSITY_CPID_LOW) * (uint32)SRCPIDCFG_SOLAR_INDENSITY_MAX)
                              / (uint32)SRCPIDCFG_SOLAR_INDENSITY_CPID_HIGH);
            SRCPID_SetValidValue(SRCFG_SOLAR_R_INDENSITY_WH_CH, TmpVal);
        }
        else
        {
            SRCPID_ClearValidValue(SRCFG_SOLAR_R_INDENSITY_WH_CH);
        }
    }

#endif
#if (SRCFG_SOLAR_L_INDENSITY_SH_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_SOLAR_INDENSITY_CPID_ENABLE_MASK) != 0u )
    {
        if ( (CPIDDataPtr[0u] & SRCPIDCFG_SOLAR_INDENSITY_CPID_BIT_MASK) != 0u )
        {
            TmpVal = (sint16)CPIDDataPtr[SRCPIDCFG_SOLAR_INDENSITY_CPID_DATA_INDEX];		/*CPID x=0-204*/

            if (TmpVal > SRCPIDCFG_SOLAR_INDENSITY_CPID_HIGH)
            {
                TmpVal = SRCPIDCFG_SOLAR_INDENSITY_CPID_HIGH;
            }

            TmpVal = (sint16)(( (uint32)((uint32)TmpVal - SRCPIDCFG_SOLAR_INDENSITY_CPID_LOW) * (uint32)SRCPIDCFG_SOLAR_INDENSITY_MAX)
                              / (uint32)SRCPIDCFG_SOLAR_INDENSITY_CPID_HIGH);
            SRCPID_SetValidValue(SRCFG_SOLAR_L_INDENSITY_SH_CH, TmpVal);
        }
        else
        {
            SRCPID_ClearValidValue(SRCFG_SOLAR_L_INDENSITY_SH_CH);
        }
    }

#endif
#if (SRCFG_SOLAR_R_INDENSITY_SH_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_SOLAR_INDENSITY_CPID_ENABLE_MASK) != 0u )
    {
        if ( (CPIDDataPtr[0u] & SRCPIDCFG_SOLAR_INDENSITY_CPID_BIT_MASK) != 0u )
        {
            TmpVal = (sint16)CPIDDataPtr[SRCPIDCFG_SOLAR_INDENSITY_CPID_DATA_INDEX];        /*CPID x=0-204*/

            if (TmpVal > SRCPIDCFG_SOLAR_INDENSITY_CPID_HIGH)
            {
                TmpVal = SRCPIDCFG_SOLAR_INDENSITY_CPID_HIGH;
            }

            TmpVal = (sint16)(( (uint32)((uint32)TmpVal - SRCPIDCFG_SOLAR_INDENSITY_CPID_LOW) * (uint32)SRCPIDCFG_SOLAR_INDENSITY_MAX)
                              / (uint32)SRCPIDCFG_SOLAR_INDENSITY_CPID_HIGH);
            SRCPID_SetValidValue(SRCFG_SOLAR_R_INDENSITY_SH_CH, TmpVal);
        }
        else
        {
            SRCPID_ClearValidValue(SRCFG_SOLAR_R_INDENSITY_SH_CH);
        }
    }

#endif
#if (SRCFG_HUMIDITY_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_HUMIDITY_CPID_ENABLE_MASK) != 0u )
    {
        if ( (CPIDDataPtr[0u] & SRCPIDCFG_HUMIDITY_CPID_BIT_MASK) != 0u )
        {
            TmpVal = (sint16)CPIDDataPtr[SRCPIDCFG_HUMIDITY_CPID_DATA_INDEX];

            if (TmpVal > SRCPIDCFG_HUMIDITY_CPID_HIGH)
            {
                TmpVal = SRCPIDCFG_HUMIDITY_CPID_HIGH;
            }

            SRCPID_SetValidValue(SRCFG_HUMIDITY_CH, TmpVal);
        }
        else
        {
            SRCPID_ClearValidValue(SRCFG_HUMIDITY_CH);
        }
    }

#endif
#if (SRCFG_AIR_QUALITY_ENABLE == 1u)

    if ( (ChannelMask & SRCPID_AIR_QUALITY_CPID_ENABLE_MASK) != 0u )
    {
        if ( (CPIDDataPtr[0u] & (uint8)SRCPIDCFG_AIR_QUALITY_CPID_BIT_MASK) != (uint8)0u )
        {
            TmpVal = (sint16)CPIDDataPtr[SRCPIDCFG_AIR_QUALITY_CPID_DATA_INDEX];
            TmpVal *= 10;

            if (TmpVal > SRCPIDCFG_AIR_QUALITY_CPID_HIGH)
            {
                TmpVal = SRCPIDCFG_AIR_QUALITY_CPID_HIGH;
            }

            SRCPID_SetValidValue(SRCFG_AIR_QUALITY_CH, TmpVal);
        }
        else
        {
            SRCPID_ClearValidValue(SRCFG_AIR_QUALITY_CH);
        }
    }

#endif
}

void SRCPID_CallBack_0xf006_ClearValidValue(void)/*PRQA S 3408*/
{
    SRCPID_ClearSpecificSensorValidValue(SRCPID_TEMP_OUTSIDE_CPID_ENABLE_MASK |
                                         SRCPID_TEMP_EVAP_CPID_ENABLE_MASK | SRCPID_TEMP_DAT1_CPID_ENABLE_MASK);
}

void SRCPID_CallBack_0xf00b_ClearValidValue(void)/*PRQA S 3408*/
{
    SRCPID_ClearSpecificSensorValidValue(SRCPID_TEMP_DAT2_CPID_ENABLE_MASK |
                                         SRCPID_TEMP_PCAT_CPID_ENABLE_MASK | SRCPID_SOLAR_INDENSITY_CPID_ENABLE_MASK);
}

void SRCPID_CallBack_0xf00f_ClearValidValue(void)/*PRQA S 3408*/
{
    SRCPID_ClearSpecificSensorValidValue(SRCPID_TEMP_WATER_CPID_ENABLE_MASK | SRCPID_TEMP_PTC_CPID_ENABLE_MASK);
}
void SRCPID_CallBack_0xf006_SetValidValue(const uint8 CPIDDataPtr[])/*PRQA S 3408*/
{
    SRCPID_SetSpecificSensorValidValue(SRCPID_TEMP_OUTSIDE_CPID_ENABLE_MASK |
                                       SRCPID_TEMP_EVAP_CPID_ENABLE_MASK | SRCPID_TEMP_DAT1_CPID_ENABLE_MASK, CPIDDataPtr );
}

void SRCPID_CallBack_0xf00b_SetValidValue(const uint8 CPIDDataPtr[])/*PRQA S 3408*/
{
    SRCPID_SetSpecificSensorValidValue(SRCPID_TEMP_DAT2_CPID_ENABLE_MASK |
                                       SRCPID_TEMP_PCAT_CPID_ENABLE_MASK | SRCPID_SOLAR_INDENSITY_CPID_ENABLE_MASK, CPIDDataPtr );
}

void SRCPID_CallBack_0xf00f_SetValidValue(const uint8 CPIDDataPtr[])/*PRQA S 3408*/
{
    SRCPID_SetSpecificSensorValidValue(SRCPID_TEMP_WATER_CPID_ENABLE_MASK | SRCPID_TEMP_PTC_CPID_ENABLE_MASK, CPIDDataPtr );
}

#endif
/*EOF*/
