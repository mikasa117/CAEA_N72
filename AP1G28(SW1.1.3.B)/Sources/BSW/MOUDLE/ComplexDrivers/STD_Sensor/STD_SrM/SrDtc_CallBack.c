/*******************************************************************************
|  File Name:  SrDtc_CallBack.c
|  Description:  Implementation of the Sensor Dtc Management
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
| ------------  --------     -------   ------------------------------------
| 2016-12-01    01.00.00     SHB       Creation
|
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/

#include "STD_SrAdCtr.h"
#include "STD_SrCfg.h"
#include "STD_SrPwmCtr.h"
//#include "NATS.h"
#include "STD_SrM.h"
//#include "DTC_Callback.h"

#if (SRM_DTC_EN_CLASS == SRM_ENABLE)

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


/*******************************************************************************
|    Function Source Code
|******************************************************************************/
uint8 SRDTC_Callback_NATSShortBat(void)
{
	const uint8    incar_temp_ret = CAEA_FALSE;
	/*const TeNATSCfg_e_SensorSt pcb_ntc_errstate = GetNATS_u_ErrState(CeNATS_e_PCB_NTC);
	const TeNATSCfg_e_SensorSt sfh2504_errstate = GetNATS_u_ErrState(CeNATS_e_SFH2504);

	if((CeNATS_e_ShortBatOrOpen == pcb_ntc_errstate) ||
			(CeNATS_e_ShortBatOrOpen == sfh2504_errstate))
	{
		incar_temp_ret = CAEA_TRUE;
	}
	else
	{
	}*/

	return incar_temp_ret;
}
uint8 SRDTC_Callback_NATSShortGnd(void)
{
	const uint8    incar_temp_ret = CAEA_FALSE;
	/*const TeNATSCfg_e_SensorSt pcb_ntc_errstate = GetNATS_u_ErrState(CeNATS_e_PCB_NTC);
	const TeNATSCfg_e_SensorSt sfh2504_errstate = GetNATS_u_ErrState(CeNATS_e_SFH2504);

	if((CeNATS_e_ShortGnd == pcb_ntc_errstate) ||
			(CeNATS_e_ShortGnd == sfh2504_errstate))
	{
		incar_temp_ret = CAEA_TRUE;
	}
	else
	{
	}*/

	return incar_temp_ret;
}
uint8 SRDTC_Callback_TempIncarShortGnd(void)
{
#if (SRCFG_TEMP_INCAR_ENABLE == SRCFG_ENABLE)
    return SRADCTR_TableGetShortGndStatus(SRADCTR_TABLE_TEMP_INCAR_CH);
#endif
    return 0u;
}

uint8 SRDTC_Callback_TempIncarShortBat(void)
{
#if (SRCFG_TEMP_INCAR_ENABLE == SRCFG_ENABLE)
    return SRADCTR_TableGetOpenOrShortBatStatus(SRADCTR_TABLE_TEMP_INCAR_CH);
#endif
    return 0u;
}
uint8 SRDTC_Callback_TempAmbShortGnd(void)
{
#if (SRCFG_TEMP_AMB_ENABLE == SRCFG_ENABLE)
    return SRADCTR_TableGetShortGndStatus(SRADCTR_TABLE_TEMP_AMB_CH);
#endif
    return 0u;
}

uint8 SRDTC_Callback_TempAmbShortBat(void)
{
#if (SRCFG_TEMP_AMB_ENABLE == SRCFG_ENABLE)
    return SRADCTR_TableGetOpenOrShortBatStatus(SRADCTR_TABLE_TEMP_AMB_CH);
#endif
    return 0u;
}
uint8 SRDTC_Callback_Pm2p5InShortGnd(void)
{
#if (SRCFG_PM2P5_IN_ENABLE == SRCFG_ENABLE)
	return SRPWMCTR_GetShortGndStatus(SRPWMCTR_PM2P5_IN_CH);
#endif
	return 0u;
}
uint8 SRDTC_Callback_Pm2p5InShortBat(void)
{
#if (SRCFG_PM2P5_IN_ENABLE == SRCFG_ENABLE)
	return SRPWMCTR_GetShortBatStatus(SRPWMCTR_PM2P5_IN_CH);
#endif
	return 0u;
}
uint8 SRDTC_Callback_Pm2p5OutShortGnd(void)
{
#if (SRCFG_PM2P5_OUT_ENABLE == SRCFG_ENABLE)
	return SRPWMCTR_GetShortGndStatus(SRPWMCTR_PM2P5_OUT_CH);
#endif
	return 0u;
}
uint8 SRDTC_Callback_Pm2p5OutShortBat(void)
{
#if (SRCFG_PM2P5_OUT_ENABLE == SRCFG_ENABLE)
	return SRPWMCTR_GetShortBatStatus(SRPWMCTR_PM2P5_OUT_CH);
#endif
	return 0u;
}

uint8 SRDTC_Callback_AQSSelfDiagError(void)
{
#if (SRCFG_AIR_QUALITY_ENABLE == SRCFG_ENABLE)
	if ((uint8)0u != SRM_GetValidStatus(SRCFG_AIR_QUALITY_CH))
	{
	    if ((960 <= SRM_GetValidValue(SRCFG_AIR_QUALITY_CH)) && (980 >= SRM_GetValidValue(SRCFG_AIR_QUALITY_CH)))
	    {
	        return 1u;
	    }
	    else
	    {
	        return 0u;
	    }
	}
	else
	{
	    return 0u;
	}
#endif
	return 0u;
}
uint8 SRDTC_Callback_AQSShortGnd(void)
{
#if (SRCFG_AIR_QUALITY_ENABLE == SRCFG_ENABLE)
	return SRPWMCTR_GetShortGndStatus(SRPWMCTR_AIR_QUALITY_CH);
#endif
	return 0u;
}
uint8 SRDTC_Callback_AQSShortBat(void)
{
#if (SRCFG_AIR_QUALITY_ENABLE == SRCFG_ENABLE)
	return SRPWMCTR_GetShortBatStatus(SRPWMCTR_AIR_QUALITY_CH);
#endif
	return 0u;
}

uint8 SRDTC_Callback_SolarLeft_SH_ShortGnd(void)/*PRQA S 3408*/
{
#if (SRCFG_SOLAR_L_INDENSITY_SH_ENABLE == SRCFG_ENABLE)
	return SRADCTR_LineGetShortGndStatus(SRADCTR_LINE_SOLAR_L_INDENSITY_CH);
#endif
	return 0u;
}
uint8 SRDTC_Callback_SolarLeft_SH_ShortBat(void)/*PRQA S 3408*/
{/*PRQA S 0777*/
#if (SRCFG_SOLAR_L_INDENSITY_SH_ENABLE == SRCFG_ENABLE)
	return SRADCTR_LineGetOpenOrShortBatStatus(SRADCTR_LINE_SOLAR_L_INDENSITY_CH);
#endif
	return 0u;
}
uint8 SRDTC_Callback_SolarRight_SH_ShortGnd(void)/*PRQA S 3408*/
{
#if (SRCFG_SOLAR_R_INDENSITY_SH_ENABLE == SRCFG_ENABLE)
	return SRADCTR_LineGetShortGndStatus(SRADCTR_LINE_SOLAR_R_INDENSITY_CH);
#endif
	return 0u;
}
uint8 SRDTC_Callback_SolarRight_SH_ShortBat(void)/*PRQA S 3408*/
{/*PRQA S 0777*/
#if (SRCFG_SOLAR_R_INDENSITY_SH_ENABLE == SRCFG_ENABLE)
	return SRADCTR_LineGetOpenOrShortBatStatus(SRADCTR_LINE_SOLAR_R_INDENSITY_CH);
#endif
	return 0u;
}

uint8 SRDTC_Callback_SolarLeft_WH_ShortGnd(void)
{
#if (SRCFG_SOLAR_L_INDENSITY_WH_ENABLE == SRCFG_ENABLE)
    return SRADCTR_TableGetShortGndStatus(SRADCTR_SOLAR_L_INDENSITY_WH_CH);
#endif
    return 0u;
}
uint8 SRDTC_Callback_SolarLeft_WH_ShortBat(void)
{
#if (SRCFG_SOLAR_L_INDENSITY_WH_ENABLE == SRCFG_ENABLE)
    return SRADCTR_TableGetOpenOrShortBatStatus(SRADCTR_SOLAR_L_INDENSITY_WH_CH);
#endif
    return 0u;
}
uint8 SRDTC_Callback_SolarRight_WH_ShortGnd(void)
{
#if (SRCFG_SOLAR_R_INDENSITY_WH_ENABLE == SRCFG_ENABLE)
    return SRADCTR_TableGetShortGndStatus(SRADCTR_SOLAR_R_INDENSITY_WH_CH);
#endif
    return 0u;
}
uint8 SRDTC_Callback_SolarRight_WH_ShortBat(void)
{
#if (SRCFG_SOLAR_R_INDENSITY_WH_ENABLE == SRCFG_ENABLE)
    return SRADCTR_TableGetOpenOrShortBatStatus(SRADCTR_SOLAR_R_INDENSITY_WH_CH);
#endif
    return 0u;
}

uint8 SRDTC_Callback_TempEvapShortGnd(void)
{
#if (SRCFG_TEMP_EVAP_ENABLE == SRCFG_ENABLE)
    return SRADCTR_TableGetShortGndStatus(SRADCTR_TABLE_TEMP_EVAP_CH);
#endif
}

uint8 SRDTC_Callback_TempEvapShortBat(void)
{
#if (SRCFG_TEMP_EVAP_ENABLE == SRCFG_ENABLE)
    return SRADCTR_TableGetOpenOrShortBatStatus(SRADCTR_TABLE_TEMP_EVAP_CH);
#endif
}

#endif
/*EOF*/
