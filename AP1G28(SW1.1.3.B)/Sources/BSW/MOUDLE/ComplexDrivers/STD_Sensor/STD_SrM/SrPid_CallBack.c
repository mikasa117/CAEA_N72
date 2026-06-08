/*******************************************************************************
|  File Name:  SrPid_CallBack.c
|  Description:  Implementation of the Sensor Pid Management
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
#include "STD_SrCfg.h"
#include "STD_SrM.h"

#if (SRM_PID_EN_CLASS == SRM_ENABLE)
/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Static local KAM variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/


/*******************************************************************************
|    Table Const Definition
|******************************************************************************/

/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/

/*static sint16 SRPID_ValueRounding(sint16 Temp);*/
static sint16 SRPID_ValueRounding2(sint16 Temp);
/*******************************************************************************
|    Function Source Code
|******************************************************************************/
/*static sint16 SRPID_ValueRounding(sint16 Temp)
{
	sint16 result;
	result = ( ((Temp) >= 0 ) ? (((Temp) + 5) / 10) : (((Temp) - 5) / 10) );
	return result;
}*/
static sint16 SRPID_ValueRounding2(sint16 Temp)
{
    sint16 result;
    result = ( ((Temp) >= 0 ) ? (((Temp) + 2) / 5) : (((Temp) - 2) / 5) );
    return result;
}
/*******************************************************************************
Name			: SRPID_GetValidValue
Syntax			: uint8 SRPID_GetValidValue(uint8 SensorChannel, uint8 LaPID_u_Data[] )
Sync/Async		: Async
Reentrancy		:
Parameters(in)	: Channel				: sensor channel
Parameters(in)	: LaPID_u_Data[]		: PID data buffer
Parameters(out) : LaPID_u_Data[]		: PID data buffer
Return value	: E_OK					:-
Description		:
Call By			: Appl_Dcm.c
|******************************************************************************/
uint8 SRPID_GetValidValue(SRCFG_CH_Enum ucChannel, uint8 LaPID_u_Data[] )/*PRQA S 3408*/
{
    uint16 SensorValidValue = 0x0000u;
    sint16 tmp = 0x0000;

    switch( ucChannel )
    {
#if (SRCFG_TEMP_DAT1_ENABLE == 1u)

        case SRCFG_TEMP_DAT1_CH:
		{
            tmp = SRM_GetValidValue(ucChannel);
            SensorValidValue = (uint16)(SRPID_ValueRounding2(tmp) + 80);
            LaPID_u_Data[0u] = (uint8)SensorValidValue;
            break;
		}
#endif
#if (SRCFG_TEMP_DAT2_ENABLE == 1u)

        case SRCFG_TEMP_DAT2_CH:
		{
            tmp = SRM_GetValidValue(ucChannel);
            SensorValidValue = (uint16)(SRPID_ValueRounding2(tmp) + 80);
            LaPID_u_Data[0u] = (uint8)SensorValidValue;
            break;
		}
#endif
#if (SRCFG_TEMP_DAT3_ENABLE == 1u)

        case SRCFG_TEMP_DAT3_CH:
		{
            tmp = SRM_GetValidValue(ucChannel);
            SensorValidValue = (uint16)(SRPID_ValueRounding2(tmp) + 80);
            LaPID_u_Data[0u] = (uint8)SensorValidValue;
            break;
		}
#endif
#if (SRCFG_TEMP_DAT4_ENABLE == 1u)

        case SRCFG_TEMP_DAT4_CH:
		{
            tmp = SRM_GetValidValue(ucChannel);
            SensorValidValue = (uint16)(SRPID_ValueRounding2(tmp) + 80);
            LaPID_u_Data[0u] = (uint8)SensorValidValue;
			break;
		}
#endif
#if (SRCFG_TEMP_DAT5_ENABLE == 1u)

        case SRCFG_TEMP_DAT5_CH:
		{
            tmp = SRM_GetValidValue(ucChannel);
            SensorValidValue = (uint16)(SRPID_ValueRounding2(tmp) + 80);
            LaPID_u_Data[0u] = (uint8)SensorValidValue;
            break;
		}
#endif
#if (SRCFG_TEMP_DAT6_ENABLE == 1u)

        case SRCFG_TEMP_DAT6_CH:
		{
            tmp = SRM_GetValidValue(ucChannel);
            SensorValidValue = (uint16)(SRPID_ValueRounding2(tmp) + 80);
            LaPID_u_Data[0u] = (uint8)SensorValidValue;
            break;
		}
#endif
#if (SRCFG_TEMP_HUMIDITY_ENABLE == 1u)

        case SRCFG_TEMP_HUMIDITY_CH:
		{
            tmp = SRM_GetValidValue(ucChannel);
            SensorValidValue = (uint16)( SRPID_ValueRounding( tmp ) + 40 );		/*0-125*/
            LaPID_u_Data[0u] = (uint8)(SensorValidValue & 0x00ffu);
            break;
		}
#endif
#if (SRCFG_TEMP_INCAR_ENABLE == 1u)

        case SRCFG_TEMP_INCAR_CH:
		{
            if ((uint8)0u != SRM_GetValidStatus(ucChannel))
            {
                tmp = SRM_GetValidValue(ucChannel);
                SensorValidValue = (uint16)(SRPID_ValueRounding2(tmp)) + (uint16)80u;
                LaPID_u_Data[0u] = (uint8)SensorValidValue;
            }
            else
            {
                LaPID_u_Data[0u] = (uint8)130;
            }

            break;
		}
#endif
#if (SRCFG_TEMP_AMB_ENABLE == 1u)

        case SRCFG_TEMP_AMB_CH:
        {
            if ((uint8)0u != SRM_GetValidStatus(ucChannel))
            {
                tmp = SRM_GetValidValue(ucChannel);
                SensorValidValue = (uint16)(SRPID_ValueRounding2(tmp)) + (uint16)80u;
                LaPID_u_Data[0u] = (uint8)SensorValidValue;
            }
            else
            {
                LaPID_u_Data[0u] = (uint8)130;
            }

            break;
        }
#endif
#if (SRCFG_TEMP_PCAT_ENABLE == 1u)

        case SRCFG_TEMP_PCAT_CH:
		{
            tmp = SRM_GetValidValue(ucChannel);
            SensorValidValue = (uint16)(SRPID_ValueRounding2(tmp)) + (uint16)80u;
            LaPID_u_Data[0u] = (uint8)SensorValidValue;
            break;
		}
#endif
#if (SRCFG_TEMP_WINDSCREEN_ENABLE == 1u)

        case SRCFG_TEMP_WINDSCREEN_CH:
		{
            tmp = SRM_GetValidValue(ucChannel);
            SensorValidValue = (uint16)(SRPID_ValueRounding2(tmp)) + (uint16)80u;
            LaPID_u_Data[0u] = (uint8)SensorValidValue;
            break;
		}
#endif
#if (SRCFG_TEMP_EVAP_ENABLE == 1u)

        case SRCFG_TEMP_EVAP_CH:
		{
            if ((uint8)0u != SRM_GetValidStatus(ucChannel))
            {
                tmp = SRM_GetValidValue(ucChannel);
                SensorValidValue = (uint16)(SRPID_ValueRounding2(tmp)) + (uint16)80u;
                LaPID_u_Data[0u] = (uint8)SensorValidValue;
            }
            else
            {
                LaPID_u_Data[0u] = (uint8)80;
            }

            break;
		}
#endif
#if (SRCFG_SOLAR_L_INDENSITY_SH_ENABLE == 1u)

        case SRCFG_SOLAR_L_INDENSITY_SH_CH:
		{
            tmp = SRM_GetValidValue(ucChannel);
            SensorValidValue = (uint16)(SRPID_ValueRounding2(tmp)) + (uint16)80u;
            LaPID_u_Data[0u] = (uint8)SensorValidValue;
            break;
		}
#endif
#if (SRCFG_SOLAR_R_INDENSITY_SH_ENABLE == 1u)

        case SRCFG_SOLAR_R_INDENSITY_SH_CH:
		{
            tmp = SRM_GetValidValue(ucChannel);
            SensorValidValue = (uint16)(SRPID_ValueRounding2(tmp)) + (uint16)80u;
            LaPID_u_Data[0u] = (uint8)SensorValidValue;
            break;
		}
#endif
#if (SRCFG_HUMIDITY_ENABLE == 1u)

        case SRCFG_HUMIDITY_CH:
		{
            tmp = SRM_GetValidValue(ucChannel);
            SensorValidValue = (uint16)(SRPID_ValueRounding2(tmp)) + (uint16)80u;
            LaPID_u_Data[0u] = (uint8)SensorValidValue;
            break;
		}
#endif
#if (SRCFG_AIR_QUALITY_ENABLE == 1u)

        case SRCFG_AIR_QUALITY_CH:
		{
            if (((uint8)0u != SRM_GetValidStatus(ucChannel))
                &&((960 > SRM_GetValidValue(SRCFG_AIR_QUALITY_CH)) || (980 < SRM_GetValidValue(SRCFG_AIR_QUALITY_CH))))
            {
                tmp = SRM_GetValidValue(ucChannel);
                SensorValidValue = (uint16)(SRPID_ValueRounding(tmp));
                LaPID_u_Data[0u] = (uint8)(SensorValidValue);
            }
            else
            {
                LaPID_u_Data[0u] = (uint8)10;
            }

            break;
		}
#endif
#if (SRCFG_PM2P5_IN_ENABLE == 1u)

        case SRCFG_PM2P5_IN_CH:
        {
            if ((uint8)0u != SRM_GetValidStatus(ucChannel))
            {
                tmp = SRM_GetValidValue(ucChannel);
                SensorValidValue = (uint16)(SRPID_ValueRounding(tmp));
                LaPID_u_Data[0u] = (uint8)(SensorValidValue);
            }
            else
            {
                LaPID_u_Data[0u] = (uint8)0;
            }

            break;
        }
#endif
#if (SRCFG_PM2P5_OUT_ENABLE == 1u)

        case SRCFG_PM2P5_OUT_CH:
        {
            if ((uint8)0u != SRM_GetValidStatus(ucChannel))
            {
                tmp = SRM_GetValidValue(ucChannel);
                SensorValidValue = (uint16)(SRPID_ValueRounding(tmp));
                LaPID_u_Data[0u] = (uint8)(SensorValidValue);
            }
            else
            {
                LaPID_u_Data[0u] = (uint8)0;
            }

            break;
        }
#endif
#if (SRCFG_SOLAR_L_INDENSITY_WH_ENABLE == 1u)

        case SRCFG_SOLAR_L_INDENSITY_WH_CH:
        {
            if ((uint8)0u != SRM_GetValidStatus(ucChannel))
            {
                tmp = SRM_GetValidValue(ucChannel);
                SensorValidValue = (uint16)(SRPID_ValueRounding(tmp));
                LaPID_u_Data[0u] = (uint8)(SensorValidValue);
            }
            else
            {
                LaPID_u_Data[0u] = (uint8)0;
            }

            break;
        }
#endif
#if (SRCFG_SOLAR_R_INDENSITY_WH_ENABLE == 1u)

        case SRCFG_SOLAR_R_INDENSITY_WH_CH:
        {
            if ((uint8)0u != SRM_GetValidStatus(ucChannel))
            {
                tmp = SRM_GetValidValue(ucChannel);
                SensorValidValue = (uint16)(SRPID_ValueRounding(tmp));
                LaPID_u_Data[0u] = (uint8)(SensorValidValue);
            }
            else
            {
                LaPID_u_Data[0u] = (uint8)0;
            }

            break;
        }
#endif

        default:
		{
			break;
		}
    }

    return 0u;	/*E_OK*/
}

uint8 SRPID_GetValidPeriod(SRPWMCTR_CH_Enum ucChannel, uint8 LaPID_u_Data[] )/*PRQA S 3408*/
{
    /*uint16 SensorValidValue = 0x0000u;*/

    switch( ucChannel )
    {
#if (SRCFG_AIR_QUALITY_ENABLE == 1u)

        case SRPWMCTR_AIR_QUALITY_CH:
		{
            if (((uint8)0u != SRM_GetValidStatus(SRCFG_AIR_QUALITY_CH))
                &&((960 > SRM_GetValidValue(SRCFG_AIR_QUALITY_CH)) || (980 < SRM_GetValidValue(SRCFG_AIR_QUALITY_CH))))
            {
                SensorValidValue = SRPWMCTR_GetFreq(ucChannel);
                LaPID_u_Data[0u] = (uint8)SensorValidValue;
                LaPID_u_Data[1u] = (uint8)(SensorValidValue >> 8u);
            }
            else
            {
                LaPID_u_Data[0u] = (uint8)0;
                LaPID_u_Data[1u] = (uint8)0;
            }

            break;
		}
#endif
#if (SRCFG_PM2P5_IN_ENABLE == 1u)

        case SRPWMCTR_PM2P5_IN_CH:
        {
            if ((uint8)0u != SRM_GetValidStatus(SRCFG_PM2P5_IN_CH))
            {
                SensorValidValue = SRPWMCTR_GetFreq(ucChannel);
                LaPID_u_Data[0u] = (uint8)SensorValidValue;
                LaPID_u_Data[1u] = (uint8)(SensorValidValue >> 8u);
            }
            else
            {
                LaPID_u_Data[0u] = (uint8)0;
                LaPID_u_Data[1u] = (uint8)0;
            }

            break;
        }
#endif
#if (SRCFG_PM2P5_OUT_ENABLE == 1u)

        case SRPWMCTR_PM2P5_OUT_CH:
        {
            if ((uint8)0u != SRM_GetValidStatus(SRCFG_PM2P5_OUT_CH))
            {
                SensorValidValue = SRPWMCTR_GetFreq(ucChannel);
                LaPID_u_Data[0u] = (uint8)SensorValidValue;
                LaPID_u_Data[1u] = (uint8)(SensorValidValue >> 8u);
            }
            else
            {
                LaPID_u_Data[0u] = (uint8)0;
                LaPID_u_Data[1u] = (uint8)0;
            }

            break;
        }
#endif
        default:
		{
			break;
		}
    }/*PRQA S 3315*/

    return 0u;	/*E_OK*/
}
/*******************************************************************************
Name			:SRPID_Callback_8383
Syntax			:uint8 SRPID_Callback_8383( uint8 LaPID_u_Data[] )
Sync/Async		: Async
Reentrancy		:
Parameters(in)	: LaPID_u_Data[]		: PID value buffer
Parameters(out) : LaPID_u_Data[]		: PID value buffer
Return value	: E_OK					:-
Description		: PID Callback function to get evap sensor valid value
Call By			: Appl_Dcm.c
|******************************************************************************/

uint8 SRPID_GetTempEvapValidValue( uint8 LaPID_u_Data[] )/*PRQA S 3408*/
{
#if (SRCFG_TEMP_EVAP_ENABLE == SRCFG_ENABLE)
    return SRPID_GetValidValue( SRCFG_TEMP_EVAP_CH, LaPID_u_Data );
#endif
    return 0u;
}
/*******************************************************************************
Name			: SRPID_Callback_82CE
Syntax			: uint8 SRPID_Callback_82CE( uint8 LaPID_u_Data[] )
Sync/Async		: Async
Reentrancy		:
Parameters(in)	: LaPID_u_Data[]		: PID value buffer
Parameters(out) : LaPID_u_Data[]		: PID value buffer
Return value	: E_OK					:-
Description		: PID Callback function to get solar indensity sensor valid value
Call By			: Appl_Dcm.c
|******************************************************************************/

uint8 SRPID_GetSolarLeftIndensityValidValue( uint8 LaPID_u_Data[] )/*PRQA S 3408*/
{
#if (SRCFG_SOLAR_L_INDENSITY_SH_ENABLE == SRCFG_ENABLE)
    return SRPID_GetValidValue( SRCFG_SOLAR_L_INDENSITY_SH_CH, LaPID_u_Data );
#endif
    return 0u;
}

uint8 SRPID_GetSolarRightIndensityValidValue( uint8 LaPID_u_Data[] )/*PRQA S 3408*/
{
#if (SRCFG_SOLAR_R_INDENSITY_SH_ENABLE == SRCFG_ENABLE)
    return SRPID_GetValidValue( SRCFG_SOLAR_R_INDENSITY_SH_CH, LaPID_u_Data );
#endif
    return 0u;
}
/*******************************************************************************
Name			: SRPID_Callback_8187
Syntax			: uint8 SRPID_Callback_8187( uint8 LaPID_u_Data[] )
Sync/Async		: Async
Reentrancy		:
Parameters(in)	: LaPID_u_Data[]		: PID value buffer
Parameters(out) : LaPID_u_Data[]		: PID value buffer
Return value	: E_OK					:-
Description		: PID Callback function to get dat2 sensor valid value
Call By			: Appl_Dcm.c
|******************************************************************************/

uint8 SRPID_GetTempData2ValidValue( uint8 LaPID_u_Data[] )/*PRQA S 3408*/
{
#if (SRCFG_TEMP_DAT2_ENABLE == SRCFG_ENABLE)
    return SRPID_GetValidValue( SRCFG_TEMP_DAT2_CH, LaPID_u_Data );
#endif
    return 0u;
}
/*******************************************************************************
Name			: SRPID_Callback_8185
Syntax			: uint8 SRPID_Callback_8185( uint8 LaPID_u_Data[] )
Sync/Async		: Async
Reentrancy		:
Parameters(in)	: LaPID_u_Data[]		: PID value buffer
Parameters(out) : LaPID_u_Data[]		: PID value buffer
Return value	: E_OK					:-
Description		: PID Callback function to get dat1 sensor valid value
Call By			: Appl_Dcm.c
|******************************************************************************/

uint8 SRPID_GetTempData1ValidValue( uint8 LaPID_u_Data[] )/*PRQA S 3408*/
{
#if (SRCFG_TEMP_DAT1_ENABLE == SRCFG_ENABLE)
    return SRPID_GetValidValue( SRCFG_TEMP_DAT1_CH, LaPID_u_Data );
#endif
    return 0u;
}
/*******************************************************************************
Name			:SRPID_Callback_8181
Syntax			:uint8 SRPID_Callback_8181( uint8 LaPID_u_Data[] )
Sync/Async		: Async
Reentrancy		:
Parameters(in)	: LaPID_u_Data[]		: PID value buffer
Parameters(out) : LaPID_u_Data[]		: PID value buffer
Return value	: E_OK					:-
Description		: PID Callback function to get pcat sensor valid value
Call By			: Appl_Dcm.c
|******************************************************************************/

uint8 SRPID_GetTempPcatValidValue( uint8 LaPID_u_Data[] )/*PRQA S 3408*/
{
#if (SRCFG_TEMP_PCAT_ENABLE == SRCFG_ENABLE)
    return SRPID_GetValidValue( SRCFG_TEMP_PCAT_CH, LaPID_u_Data );
#endif
    return 0u;
}

#endif/*SRM_PID_EN_CLASS*/
/*EOF*/
