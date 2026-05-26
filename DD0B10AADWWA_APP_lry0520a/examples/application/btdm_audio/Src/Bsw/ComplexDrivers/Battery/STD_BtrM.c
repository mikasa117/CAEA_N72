/* polyspace<MISRA-C3:1.1:Not a defect:Justify with annotations> The high number of macros is due to inclusion of microcontroller's header. */
/**
 * \file       STD_BtrM.c
 * \author     wujie
 * \brief      Implementation file for the Battery Manager.
 *
 * \par        Platform File
 *
 *
 * \copyright (c) 2019 CAEA, all rights reserved.
 */

/*-----------------------------------------------------------------------------
 Information for the configuration management-system:
-------------------------------------------------------------------------------
 (Will be generated automatically during Check-In into SVN)
 $Revision: 774 $
 $Date: 2024-04-26 09:23:54 +0800 (周五, 26 4月 2024) $
 $Author: xieshangfeng $
-------------------------------------------------------------------------------
                R E V I S I O N   H I S T O R Y
-------------------------------------------------------------------------------
 
 
------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include "STD_BtrM.h"


/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/
/**
* @addtogroup macros_enum
* @{
*/


/** @} *//* Macros_Enum definition */

/*----------------------------------------------------------------------------*/
/*                              Local data types                              */
/*----------------------------------------------------------------------------*/
/**
* @addtogroup Typedefs
* @{
*/



/** @} *//* Typedefs definition */

/*----------------------------------------------------------------------------*/
/*                             Global data at RAM                             */
/*----------------------------------------------------------------------------*/
/**
* @addtogroup Global_Variable
* @{
*/
BtrM_ModeType Rte_BtrM_VoltageMode = 0;


/** @} *//* Global_Variable definition */

/*----------------------------------------------------------------------------*/
/*                             Global data at ROM                             */
/*----------------------------------------------------------------------------*/
/**
* @addtogroup Global_Const
* @{
*/




/** @} *//* Global_Const definition */

/*----------------------------------------------------------------------------*/
/*                              Local data at RAM                             */
/*----------------------------------------------------------------------------*/
/**
* @addtogroup Static_Variable
* @{
*/
/*State machine for battery mode*/
static uint8 BtrM_ucStateMachine;
/**\brief debounce timing variable*/
static uint8 BtrM_ucStableTime;

static uint8 BtrM_ucPretreatmentMode = 0xFFu;
#if ( (defined RDPT_EEPM) || (BTRM_LOW_VOL_DETECT == STD_ON) )
static boolean BtrM_bLoadLowVolSta = FALSE;
#endif
/** @} *//* Static_Variable definition */
/*----------------------------------------------------------------------------*/
/*                              Local data at ROM                             */
/*----------------------------------------------------------------------------*/
/**
* @addtogroup Static_Const
* @{
*/




/** @} *//* Static_Const definition */

/*----------------------------------------------------------------------------*/
/*                      Declaration of local functions                        */
/*----------------------------------------------------------------------------*/

static void BtrM_ModeManage (uint8 *pucStateMachine,uint8 ucTimeScale,uint8 *pucTiming );
static void BtrM_IOControl( void );
/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/
/**
* @addtogroup Global_Function
* @{
*/

/**
* \brief :      BtrM Module Initalization,Called by StartupHook() whiche is located at Rte_Task.c.
* \param[in] -
* \param[out] -
* \pre -
* \post -
* \return -
*/
void BtrM_Init ( void )
{
    uint8 ucVoltageMode = BTRM_INITMODE;
    #if (BTRM_SUPER_FAST_FILTER == STD_ON)
    ucVoltageMode = BtrM_FastFilter_Fast();
    Rte_Write_BtrM_BtrM_VoltageMode(ucVoltageMode)
    BtrM_ucStateMachine = BTRM_NORMAL;
    #else
    /*set fast filter timing*/
    BtrM_ucStableTime     = BTRM_FAST_FILTER_TIME;
    /* enter Initial mode */
    BtrM_ucStateMachine = BTRM_INIT;
    /*set Initial mode to */
    /* polyspace<MISRA-C3:12.3:Not a defect:Justify with annotations> not affect */
    Rte_Write_BtrM_BtrM_VoltageMode(ucVoltageMode);
    #endif
    BtrM_ucPretreatmentMode = 0xFFu;
#if ( (defined RDPT_EEPM) || (BTRM_LOW_VOL_DETECT == STD_ON) )    
    BtrM_bLoadLowVolSta = FALSE;
#endif    
}

/**
* \brief :      
* \param[in] -
* \param[out] -
* \pre -
* \post -
* \return -
*/

void BtrM_IOControl( void )
{
		uint8 uBtrMode = 0;
	
		Rte_Read_BtrM_BtrM_VoltageMode(&uBtrMode);
	
		if(STD_BTRM_MODE_B == uBtrMode)
		{
			gpio_write_pin(GPIOB, GPIO_PIN_0, GPIO_PIN_CLEAR);
		}
		else
		{
			gpio_write_pin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
		}
}

/**
* \brief :      BtrM Module Initalization,Called by 5ms FUNC_OS_TASK_5MS_0() which is located at Rte_Task.c.
* \param[in] -
* \param[out] -
* \pre -
* \post -
* \return -
*/
void BtrM_MainFunction( void )
{
    switch ( BtrM_ucStateMachine )
    {
    case BTRM_INIT:
    {
        BtrM_ModeManage (&BtrM_ucStateMachine, BTRM_FAST_FILTER_TIME, &BtrM_ucStableTime );
        /*suppervision the fast filter procedure*/
        if( BTRM_NORMAL == BtrM_ucStateMachine )
        {
            BtrM_ucStableTime = BTRM_SLOW_FILTER_TIME;
        }
    }
    break;

    case BTRM_NORMAL:
    {
        BtrM_ModeManage (&BtrM_ucStateMachine,BTRM_SLOW_FILTER_TIME, &BtrM_ucStableTime );

        if ( BtrM_ucStableTime == BTRM_DEFAULT_VALUE )
        {
            BtrM_ucStableTime = BTRM_SLOW_FILTER_TIME;
        }
        else
        {
            /*Nothing to do*/
        }
    }
    break;

    default:
    {
        BtrM_ucStateMachine = BTRM_NORMAL;
    }
    break;

    }
		
		BtrM_IOControl();
}

#if ( (defined RDPT_EEPM) || (BTRM_LOW_VOL_DETECT == STD_ON) )
Std_ReturnType BtrM_GetLoadLowVoltageStatus(boolean * pbStatus)
{
    uint16 usBatteryAd;
    
    (void)Rte_Read_BtrM_EcuIfAdc_AdcConvRes (BTRM_SAMPLING_CHANNEL, &usBatteryAd ) ;
    if(usBatteryAd < BTRM_LOAD_THRESHOLD_LOW_BATTERY_IN )
    {
        BtrM_bLoadLowVolSta = TRUE;
    }
    else if(usBatteryAd > BTRM_LOAD_THRESHOLD_LOW_BATTERY_OUT)
    {
        BtrM_bLoadLowVolSta = FALSE; 
    }
    else
    {}
    *pbStatus = BtrM_bLoadLowVolSta;
    
    return E_OK;
}
#endif
/** @} *//* Global_Function definition */
/*----------------------------------------------------------------------------*/
/*                      Implementation of local functions                     */
/*----------------------------------------------------------------------------*/
/**
* @addtogroup Static_Function
* @{
*/

/**
* \brief :      BtrM Module Manage.
* \param[in] : pucTiming : Power supply filtering time
* \param[out] -
* \pre -
* \post -
* \return -
*/
static void BtrM_ModeManage (uint8* pucStateMachine,uint8 ucTimeScale, uint8 *pucTiming )
{
    uint16 usAdSamplingBuffer;
    BtrM_ModeType  tVoltageMode;

    /*Mode changing state machine*/
    if( BTRM_INIT == *pucStateMachine )
    {
#if (BTRM_FAST_FILTER_TIME > 0U)
        if( ( *pucTiming ) > 0u )
        {
            ( *pucTiming )--;
        }

        if( 0u == ( *pucTiming ) )
        {
            /*get Rte adc buffer address*/
            /* polyspace<MISRA-C3:12.3:Not a defect:Justified> not affect */
            Rte_Read_BtrM_EcuIfAdc_AdcConvRes (BTRM_SAMPLING_CHANNEL, &usAdSamplingBuffer );                
            if( (BTRM_B_TO_A_MODE_UPPER >= usAdSamplingBuffer) && (BTRM_B_TO_A_MODE_LOWER <= usAdSamplingBuffer) )
            {
                Rte_Write_BtrM_BtrM_VoltageMode(STD_BTRM_MODE_A);
            }
            else
            {
            #if (BTRM_SUPPORT_C_MODE == STD_ON)
                if( (BTRM_B_TO_C_MODE_UPPER <= usAdSamplingBuffer) || (BTRM_B_TO_C_MODE_LOWER >= usAdSamplingBuffer) )
                {
                    Rte_Write_BtrM_BtrM_VoltageMode(STD_BTRM_MODE_C); 
                }
                else
                {
                    Rte_Write_BtrM_BtrM_VoltageMode(STD_BTRM_MODE_B);                
                }
            #else
                Rte_Write_BtrM_BtrM_VoltageMode(STD_BTRM_MODE_B);
            #endif
            }
            *pucStateMachine = BTRM_NORMAL;
        }
#else
        *pucStateMachine = BTRM_NORMAL;    
#endif
    
    }
    else
    {
        /*get Rte adc buffer address*/
        /* polyspace<MISRA-C3:12.3:Not a defect:Justified> not affect */
        Rte_Read_BtrM_EcuIfAdc_AdcConvRes (BTRM_SAMPLING_CHANNEL, &usAdSamplingBuffer );         
        /*get power mode*/
        /* polyspace<MISRA-C3:12.3:Not a defect:Justified> not affect */
        Rte_Read_BtrM_BtrM_VoltageMode(&tVoltageMode);        
        switch ( tVoltageMode )
        {
        case STD_BTRM_MODE_A  :
        {
            if ( ( BTRM_A_TO_B_MODE_UPPER <= usAdSamplingBuffer ) || ( BTRM_A_TO_B_MODE_LOWER >= usAdSamplingBuffer ) )
            {
                /* decrease timing counter */
                if( ( *pucTiming ) > 0u )
                {
                    ( *pucTiming )--;
                }

                /*Time is up*/
                if ( BTRM_DEFAULT_VALUE == ( *pucTiming ) )
                {
                    /* polyspace<MISRA-C3:12.3:Not a defect:Justified> not affect */
                    Rte_Write_BtrM_BtrM_VoltageMode(STD_BTRM_MODE_B);
                }
                else
                {
                    /*Nothing to do*/
                }
            }
            else
            {
                (*pucTiming) = ucTimeScale;  /*Nothing to do*/
            }
        }
        break;

        case STD_BTRM_MODE_B:
        {
            if ( ( BTRM_B_TO_A_MODE_UPPER >= usAdSamplingBuffer ) && ( BTRM_B_TO_A_MODE_LOWER <= usAdSamplingBuffer ) )
            {
                /*In B mode, if the fluctuation of Battery voltage is great, The timing measurement accuracy may be affected.So it should define sub-mode for B2C and B2A mode*/
                if (BtrM_ucPretreatmentMode == STD_BTRM_MODE_B_TO_C)
                {
                    ( *pucTiming ) = ucTimeScale;
                }
                else
                {
                    /*Nothing to do*/
                }
                
                /*Enter B to A mode*/
                BtrM_ucPretreatmentMode = STD_BTRM_MODE_B_TO_A;

                /*time count down*/
                ( *pucTiming )--;

                if ( BTRM_DEFAULT_VALUE == ( *pucTiming ) )
                {
                    /* polyspace<MISRA-C3:12.3:Not a defect:Justified> not affect */
                    Rte_Write_BtrM_BtrM_VoltageMode(STD_BTRM_MODE_A);
                    BtrM_ucPretreatmentMode = STD_BTRM_MODE_A;
                }
                else
                {
                    /*Nothing to do*/
                }
            }


    #if (BTRM_SUPPORT_C_MODE == STD_ON)
            else if ( ( BTRM_B_TO_C_MODE_UPPER <= usAdSamplingBuffer ) || ( BTRM_B_TO_C_MODE_LOWER >= usAdSamplingBuffer ) )
            {
                if (BtrM_ucPretreatmentMode == STD_BTRM_MODE_B_TO_A)
                {
                    ( *pucTiming ) = ucTimeScale;
                }

                BtrM_ucPretreatmentMode = STD_BTRM_MODE_B_TO_C;
                ( *pucTiming )--;


                if ( BTRM_DEFAULT_VALUE == ( *pucTiming ) )
                {
                    /* polyspace<MISRA-C3:12.3:Not a defect:Justified> not affect */
                    Rte_Write_BtrM_BtrM_VoltageMode(STD_BTRM_MODE_C);
                    BtrM_ucPretreatmentMode = STD_BTRM_MODE_C;
                }
                else
                {
                    /*Nothing to do*/
                }
            }
    #endif
            else
            {
                 ( *pucTiming ) = ucTimeScale;/*Nothing to do*/
            }
        }
        break;

    #if (BTRM_SUPPORT_C_MODE == STD_ON)

        case STD_BTRM_MODE_C:
        {
            if ( ( BTRM_C_TO_B_MODE_UPPER >= usAdSamplingBuffer ) && ( BTRM_C_TO_B_MODE_LOWER <= usAdSamplingBuffer ) )
            {
                ( *pucTiming )--;

                if ( BTRM_DEFAULT_VALUE == ( *pucTiming ) )
                {
                    /* polyspace<MISRA-C3:12.3:Not a defect:Justified> not affect */
                    Rte_Write_BtrM_BtrM_VoltageMode(STD_BTRM_MODE_B);
                }
                else
                {
                    /*Nothing to do*/
                }
            }
            else
            {
                ( *pucTiming ) = ucTimeScale;/*Nothing to do*/
            }
        }
        break;
    #endif

        default:
        {
    #if (BTRM_SUPPORT_C_MODE == STD_OFF)
            /* polyspace<MISRA-C3:12.3:Not a defect:Justified> not affect */
            Rte_Write_BtrM_BtrM_VoltageMode(STD_BTRM_MODE_B);
            BtrM_ucPretreatmentMode = STD_BTRM_MODE_B;
    #else
            /* polyspace<MISRA-C3:12.3:Not a defect:Justified> not affect */
            Rte_Write_BtrM_BtrM_VoltageMode(STD_BTRM_MODE_C);
            BtrM_ucPretreatmentMode = STD_BTRM_MODE_C;
    #endif
        }
        break;
        }
    }
    /*wrie VoltageMode into Rte Data pool*/
}



/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
uint8 BtrM_GetVersioninfo(Std_VersionInfoType  *tVersioninfoStruct)
{
    /* ----- Local Variables ---------------------------------------------- */
    uint8 errorId = BTRM_E_NO_ERROR;

    /* ----- Development Error Checks ------------------------------------- */
    /* #20 Check that the passed parameter is not a Null Pointer. */
    if (NULL_PTR == tVersioninfoStruct)
    {
        errorId = BTRM_E_NULL_POINTER;
    }
    else
    {
        /* ----- Implementation ----------------------------------------------- */
        /* #30 Pass the BTNSINGLEHDLR version info from component header to the Std_VersionInfoType Pointer. */

        /*tVersioninfoStruct->vendorId = (uint16)BTRM_VENDOR_ID; */ /* SBSW_BTNSINGLEHDLR_POINTERACCESS_tVersioninfoStruct *//* polyspace MISRA-C3:D4.14 [Justified:Low] "No garbage value is written when called, and the risk is controllable" */
        tVersioninfoStruct->moduleID = (uint16)BTRM_MODULE_ID;  /* SBSW_BTNSINGLEHDLR_POINTERACCESS_tVersioninfoStruct *//* polyspace MISRA-C3:D4.14 [Justified:Low] "Safe Pointers are used when called, with manageable risk" */

        tVersioninfoStruct->sw_major_version = (uint8)BTRM_SW_MAJOR_VERSION;  /* SBSW_BTNSINGLEHDLR_POINTERACCESS_tVersioninfoStruct */
        tVersioninfoStruct->sw_minor_version = (uint8)BTRM_SW_MINOR_VERSION;  /* SBSW_BTNSINGLEHDLR_POINTERACCESS_tVersioninfoStruct */
        tVersioninfoStruct->sw_patch_version = (uint8)BTRM_SW_PATCH_VERSION;  /* SBSW_BTNSINGLEHDLR_POINTERACCESS_tVersioninfoStruct */
    }
    return errorId;
}

/** @} *//* Static_Function definition */
/*EOF*/
