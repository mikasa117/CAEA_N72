/* polyspace<MISRA-C3:1.1:Low:Fix> No effect on the program. */


#include "BusOff_Recovery.h"
#include "CanDem_Callback.h"
#include "CanDem.h"
#include "STD_BtrM.h"
#include "Rte_Can.h"
#include "CanApp.h"

uint8 CanDem_GetIgnStatus(void)
{
    uint8 LeDEM_u_DtcIGNState1 = CanDEM_u_Zero;
    uint8 LeDEM_u_DtcIGNState2 = CanDEM_u_Zero;
    uint8 LeDEM_u_DtcIGNState;

//  //  LeDEM_u_DtcIGNState1 = PWM_GetHwIgnStatus();//0:IGN ON  1:IGN OFF
//    LeDEM_u_DtcIGNState1 = (~LeDEM_u_DtcIGNState1)&0x01;
////	if(Rte_Read_PEPS_PowerMode() == 2u)
////	{
////		LeDEM_u_DtcIGNState2 = TRUE;
////	}
////	else
////	{
////		LeDEM_u_DtcIGNState2 = FALSE;
////	}
//	LeDEM_u_DtcIGNState = LeDEM_u_DtcIGNState1|LeDEM_u_DtcIGNState2;
//	if(LeDEM_u_DtcIGNState1 == 0)
//	{
////		LeDEM_u_DtcIGNState = LeDEM_u_DtcIGNState1|LeDEM_u_DtcIGNState2;
////		debug_printf("LeDEM_u_DtcIGNState:%d\n",LeDEM_u_DtcIGNState1);
////		debug_printf("LeDEM_u_DtcIGNState:%d\n",LeDEM_u_DtcIGNState2);
////		debug_printf("LeDEM_u_DtcIGNState:%d\n",LeDEM_u_DtcIGNState);
//	}




    uint8 LeDEM_u_DtcIndex=CanDEM_u_Zero;

	if(1 == GetCan_IGN_Flag())
    {
        LeDEM_u_DtcIndex = CanDem_u_True;
    }     
    else
    {
        LeDEM_u_DtcIndex = CanDem_u_False;
    }




    return  LeDEM_u_DtcIndex;
}

uint8 CanDem_GetBatteryMode(void)/*9-16V*/
{
	uint8 LeDEM_u_DtcBatState = CanDEM_u_Zero;
	uint8 LeDEM_flag = 0;
	//LeDEM_u_DtcBatState = BTRM_GetSysBatteryModeAStatus();
//	LeDEM_flag = ((BTRDTC_GetLowVolDtcStatus())||(BTRDTC_GetHighVolDtcStatus()));
//	if(LeDEM_flag == 0x00u)
//	{
//		 LeDEM_u_DtcBatState = 0x01;
//	}
//	else
//	{
//		LeDEM_u_DtcBatState =  CanDEM_u_Zero;
//	}
	return 1;
}

uint8 CanDem_GetDTC_85EN(void)
{
    uint8 LeDEM_u_Dtc85EnState = CanDEM_u_Zero;

    LeDEM_u_Dtc85EnState = CanDem_GetDTCSetting();

    return LeDEM_u_Dtc85EnState;
}

uint8 CanDem_GetPowerModeOn(void)
{
	uint8 LeDEM_u_DtcPowerModeState = 0;

//	if(Rte_Read_PEPS_PowerMode() == 2u)
//	{
//		LeDEM_u_DtcPowerModeState = TRUE;
//	}
//	else if(Rte_Read_PEPS_PowerMode() == 0u)
//	{
//		LeDEM_u_DtcPowerModeState = FALSE;
//	}
//	else
//	{
//		;
//	}

    return 1;
}

uint8 CanDem_GetBusOffState(void)
{
	uint8 LeDEM_u_DtcBusoffState = CanDEM_u_Zero;

	LeDEM_u_DtcBusoffState = CanCbk_GetBusOffDtcConditionState();//0:No BusOff  1:BusOff
 
    return (uint8)(1-LeDEM_u_DtcBusoffState);
}

uint8 CanDem_GetSPIComState(void)
{
	uint8 LeDEM_u_DtcSPIComState = CanDEM_u_Zero;

	//LeDEM_u_DtcSPIComState = DmsGetSpiCommStatus();//0:Normal  1:Abnormal
	//add by zk
//	if(LeDEM_u_DtcSPIComState != 0)
//	{
//		return 0;
//	}
//	else
//	{
//		return 1;
//	}

    return 1;
}
