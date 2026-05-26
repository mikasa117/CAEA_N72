/* -----------------------------------------------------------------------------
  Filename:    ccl_par.c
  Description: Toolversion: 02.03.18.01.80.01.04.01.00.00
               
               Serial Number: CBD1800104
               Customer Info: Wenzhou Changjiang Automobile Electronic System Co.,Ltd.?CAEA)
                              Package: CBD_Vector_SLP2
                              Micro: FS32K146
                              Compiler: GNU 9.2.0
               
               
               Generator Fwk   : GENy 
               Generator Module: Ccl__core
               
               Configuration   : D:\2.OV_eclipse+Jlink\program\CFG\N72\cfg\N72.gny
               
               ECU: 
                       TargetSystem: Hw_S32Cpu
                       Compiler:     GNU
                       Derivates:    S32K146
               
               Channel "Channel0":
                       Databasefile: D:\2.OV_eclipse+Jlink\program\CFG\N72\cfg\DD0B66BACWWA.dbc
                       Bussystem:    CAN
                       Manufacturer: Vector
                       Node:         DMM

 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2001-2015 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

#define CCL_PAR_MODULE
#include "ccl_inc.h"
#include "ccl_par.h"
#include "Can_Trcv.h"
#include "BusOff_Recovery.h"   /* BusOffª÷∏¥ƒ£øÈ */
#include "Rte_BtrM.h"
#include "STD_BtrM.h"

/******************************************************************************/
/* function external declaration                                              */
/******************************************************************************/



/******************************************************************************/
/* internal declarations (ROM const)                                          */
/******************************************************************************/
/******************************************************************************/
/* external declarations (ROM const)                                          */
/******************************************************************************/
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 cclNmWakeUpAble = 0x1;   /* The variable store the wake up able channels (one bit per channel). */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 cclChannelWithoutNm = 0x1;
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 cclStartIndex[1] = {
    0
};

V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 cclStopIndex[1] = {
    0
};
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 cclUserOffset[kCclNumberOfUser] = {
      0x0,   0x0
};

V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 cclUserMask[kCclNumberOfUser] = {
      0x1,   0x2
};

V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 cclUserChannel[kCclNumberOfUser] = {
    0x0, 0x0
};
/******************************************************************************/
/* global data definitions                                                    */
/******************************************************************************/
/***************************************************************************** 
| NAME:             CclInitPowerOnFct                                          
| PROTOTYPE:        void CclInitPowerOnFct( void )                             
| CALLED BY:        CclInitPowerOn                                             
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!          
| INPUT PARAMETERS: void                                                       
| RETURN VALUE:     void                                                       
| DESCRIPTION:      This function is a generated init container function. It   
|                   contains different init routines depending on the          
|                   used modules.                                              
|*****************************************************************************/

void CclInitPowerOnFct(void)
{
  #if defined(C_SINGLE_RECEIVE_CHANNEL) || defined(C_MULTIPLE_RECEIVE_CHANNEL)
    CanInitPowerOn();
  #else
    CanInitPowerOn(0);
  #endif
  IlInitPowerOn();
  CanOffline();
  CclCanStandby();
  //BusOff_Init();  /* ∆Ù”√≤‚ ‘ - ≥ı ºªØBusOffª÷∏¥ƒ£øÈ */
  TpInitPowerOn();
  DescInitPowerOn(kDescPowerOnInitParam);
}
/***************************************************************************** 
| NAME:             CclInitFct                                                 
| PROTOTYPE:        void CclInitFct( void )                                    
| CALLED BY:        CclInit                                                    
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!          
| INPUT PARAMETERS: void                                                       
| RETURN VALUE:     void                                                       
| DESCRIPTION:      This function is a generated init container function. It   
|                   contains different init routines depending on the          
|                   used modules.                                              
|*****************************************************************************/

void CclInitFct(void)
{
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  CanInit(0, 0);
#else
  CanInit(0);
#endif
  IlInit();
  CanOffline();
  CclCanStandby();
  ApplCclInit();
}

/**************************************************************************************
| NAME:             CclSystemShutdownFct                                               
| PROTOTYPE:        void CclSystemShutdownFct( void )                                  
| CALLED BY:        CclSystemShutdown                                                  
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!                  
| INPUT PARAMETERS: void                                                               
| RETURN VALUE:     void                                                               
| DESCRIPTION:      This function is a generated system shutdown container             
|                   function. It could be used to stop services or deinitialize        
|                   variables after the system leaves the "normal" mode.             
|*************************************************************************************/

void CclSystemShutdownFct(void) 
{ 
}

/*********************************************************************************************** 
| NAME:             Ccl_5_0msTaskCont    
| PROTOTYPE:        void Ccl_5_0msTaskCont( void ) 
| CALLED BY:        task handler                                                                 
| PRECONDITIONS:                                                                                 
| INPUT PARAMETERS: void                                                                         
| RETURN VALUE:     void                                                                         
| DESCRIPTION:      This function is a generated <x> ms task container                           
|                   function. It contains different cyclic routines                              
|                   depending on the used modules.                                               
|***********************************************************************************************/
void CCL_API_CALL_TYPE Ccl_5_0msTaskCont(void) 
{ 
  IlTxTask();

  IlRxTask(); 

   BusOff_Task();  /* ∆Ù”√≤‚ ‘ - BusOffª÷∏¥¥¶¿Ì */

   TpRxTask();

   TpTxTask();

}


/*********************************************************************************************** 
| NAME:             Ccl_10_0msTaskCont    
| PROTOTYPE:        void Ccl_10_0msTaskCont( void ) 
| CALLED BY:        task handler                                                                 
| PRECONDITIONS:                                                                                 
| INPUT PARAMETERS: void                                                                         
| RETURN VALUE:     void                                                                         
| DESCRIPTION:      This function is a generated <x> ms task container                           
|                   function. It contains different cyclic routines                              
|                   depending on the used modules.                                               
|***********************************************************************************************/
void CCL_API_CALL_TYPE Ccl_10_0msTaskCont(void) 
{ 
	
uint8_t ucBatValue = 0;

Rte_Read_BtrM_BtrM_VoltageMode(&ucBatValue);

  CclTask();

	if(ucBatValue != STD_BTRM_MODE_C )  
	{
		DescTask();
	}
	
 
}


/******************************************************************************
| NAME:             CclComStart                                                
| PROTOTYPE:        void CclComStart(void)                                  
| CALLED BY:        network management                                         
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!          
| INPUT PARAMETERS:                                                            
| RETURN VALUE:     void                                                       
| DESCRIPTION:      This function start the communication with interaction layer.
|*****************************************************************************/
void CclComStart(void)
{
  cclComSwState[0]=kCclComSwOn;
  ApplCclComStart();
    IlTxStart();
  IlRxStart();
}
/******************************************************************************
| NAME:             CclComStop                                                 
| PROTOTYPE:        void CclComStop(void)                                      
| CALLED BY:        network management                                         
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!          
| INPUT PARAMETERS:                                                            
| RETURN VALUE:     void                                                       
| DESCRIPTION:      This function stop the communication with interaction layer.
|*****************************************************************************/
void CclComStop(void)
{
  IlTxStop();
  IlRxStop();
  cclComSwState[0]=kCclComSwOff;
  ApplCclComStop();
}
/******************************************************************************
| NAME:             CclComWait                                                
| PROTOTYPE:        void CclComWait(void)                                  
| CALLED BY:        network management                                         
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!          
| INPUT PARAMETERS:                                                            
| RETURN VALUE:     void                                                       
| DESCRIPTION:      This function sets the interaction layer into the wait state.
|*****************************************************************************/
void CclComWait(void)
{
  cclComSwState[0]=kCclComSwOff;
  ApplCclComWait();
  IlTxWait();
  IlRxWait();
}
/******************************************************************************
| NAME:             CclComResume                                                 
| PROTOTYPE:        void CclComResume(void)                                      
| CALLED BY:        network management                                         
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!          
| INPUT PARAMETERS:                                                            
| RETURN VALUE:     void                                                       
| DESCRIPTION:      This function resumes the communication with interaction layer.
|*****************************************************************************/
void CclComResume(void)
{
    IlTxRelease();
  IlRxRelease();
  cclComSwState[0]=kCclComSwOn;
  ApplCclComResume();
}






/******************************************************************************
| NAME:             CclBusOffStart                                             
| PROTOTYPE:        void CclBusOffStart(void)                                  
| CALLED BY:        network management                                         
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!          
| INPUT PARAMETERS:                                          ,                 
| RETURN VALUE:     void                                                       
| DESCRIPTION:      This function stop the communication with interaction layer.
|*****************************************************************************/
void CclBusOffStart(void)
{
  #if defined( CCL_ENABLE_STOP_TIMEOUT)
  /*  IlTxWait();
    IlRxWait();*/
	IlTxStop(); /*modify by zc 19.3.6*/
	IlRxStop();
  #endif
  ApplCclBusOffStart();
}
/******************************************************************************
| NAME:             CclBusOffEnd                                               
| PROTOTYPE:        void CclBusOffEnd(void)                                    
| CALLED BY:        network management                                         
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!          
| INPUT PARAMETERS:                                                            
| RETURN VALUE:     void                                                       
| DESCRIPTION:      This function start the communication with interaction layer.
|*****************************************************************************/
void CclBusOffEnd(void)
{
  #if defined(CCL_ENABLE_STOP_TIMEOUT)
  /*  IlTxRelease();
    IlRxRelease();*/
	IlTxStart();/*modify by zc*/
    IlRxStart();
  #endif
  ApplCclBusOffEnd();
}

/**********************************************************************************
| NAME:             CclNmActiveReqFct                                              
| PROTOTYPE:        vuint8 CclNmActiveReqFct( vuint8 network )                     
| CALLED BY:        CclTask                                                        
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!              
| INPUT PARAMETERS: vuint8 network                                                 
| RETURN VALUE:     vuint8                                                         
| DESCRIPTION:      This function contains the algorithm to go in the active       
|                   mode. The algorithm depends on the used modules.               
|*********************************************************************************/

vuint8 CclNmActiveReqFct(vuint8 network)
{
  switch(cclNmState[0])
  {
    case kCclStateWaitBusSleep:
      CanOnline();
      CclComResume();
      break;
    case kCclNmStateSleep:
      CclCanNormal();
      CanOnline();
      CclComStart();
      break;
    default: /* nothing to do */
      break;
  }
  return NM_OK;
}
/***********************************************************************************
| NAME:             CclNmPrepareSleepReqFct                                          
| PROTOTYPE:        void CclNmPrepareSleepReqFct( void )                             
| CALLED BY:        CclTask                                                          
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!                
| INPUT PARAMETERS: void                                                             
| RETURN VALUE:     void                                                             
| DESCRIPTION:      This function contains the algorithm to set the system in        
|                   prepare sleep mode. The algorithm depends on the used            
|                   modules.                                                         
|***********************************************************************************/

void CclNmPrepareSleepReqFct(void)
{
  CclCanNormal();
  CanOnline();
  CclComStart();
}
/***********************************************************************************
| NAME:             CclNmSleepReqFct                                                
| PROTOTYPE:        void CclNmSleepReqFct( vuint8 network )                         
| CALLED BY:        CclRelNetRequest                                                
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!               
| INPUT PARAMETERS: vuint8 network                                                  
| RETURN VALUE:     void                                                            
| DESCRIPTION:      This function contains the algorithm to go in the sleep         
|                   mode. The algorithm depends on the used modules.                
|**********************************************************************************/
void CclNmSleepReqFct(vuint8 network)
{
  network = network;

}
/********************************************************************************
| NAME:             CclExtEmcComReqFct                                              
| PROTOTYPE:        void CclExtEmcComReqFct(void)                                   
| CALLED BY:        ApplCanWakeUp,                                               
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!            
| INPUT PARAMETERS: void                                                         
| RETURN VALUE:     void                                                         
| DESCRIPTION:      This function sets a communication flag. This flag is        
|                   used to synchronize the state requests between CCL           
|                   and higher layer component.                                  
|*******************************************************************************/

void CclExtEmcComReqFct(void)
{
  CbkWakeupValidationNotification();
}
/********************************************************************************
| NAME:             CclExtCanComReqFct                                              
| PROTOTYPE:        void CclExtCanComReqFct(void)                                   
| CALLED BY:        ApplCanWakeUp,                                               
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!            
| INPUT PARAMETERS: void                                                         
| RETURN VALUE:     void                                                         
| DESCRIPTION:      This function sets a communication flag. This flag is        
|                   used to synchronize the state requests between CCL           
|                   and higher layer component.                                             
|*******************************************************************************/

void CclExtCanComReqFct(void)
{
  CbkWakeupbyBus();
}
/********************************************************************************
| NAME:             CclIntComReqFct                                              
| PROTOTYPE:        void CclIntComReqFct(void)                                   
| CALLED BY:        CclRequestNetwork                                            
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!            
| INPUT PARAMETERS: void                                                         
| RETURN VALUE:     void                                                         
| DESCRIPTION:      This function sets a communication flag. This flag is        
|                   used to synchronize the state requests between CCL           
|                   and higher layer component.                                             
|*******************************************************************************/

void CclIntComReqFct(void)
{
  CbkFirstCommunicationRequest();
}
/********************************************************************************
| NAME:             CclComRelFct                                            
| PROTOTYPE:        void CclComRelFct(void)                                 
| CALLED BY:        ApplNmCanSleep                                               
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!            
| INPUT PARAMETERS: void                                                         
| RETURN VALUE:     void                                                         
| DESCRIPTION:      This function clears a communication flag. This flag are     
|                   used to synchronize the state requests between CCL           
|                   and higher layer component.                                             
|*******************************************************************************/

void CclComRelFct(void)
{
  CbkBusSleep();
}

/********************************************************************************
| NAME:             CclInitTrcvFct                                              
| PROTOTYPE:        void CclInitTrcvFct( void )                                 
| CALLED BY:        CclInitPortsPowerOn                                          
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!            
| INPUT PARAMETERS: void                                                         
| RETURN VALUE:     void                                                         
| DESCRIPTION:      This function contains the transceiver init routine.         
|                   The routine depends on the used transceiver type.            
|*******************************************************************************/

void CclInitTrcvFct(void)
{
  /* RS Pin, configuration PORT, OUTPUT, LOW */
  CanTrcv_WakeUpTrcv();
}
/************************************************************************************
| NAME:             CclWakeUpTrcvFct                                                
| PROTOTYPE:        void CclWakeUpTrcvFct( void )                                   
| CALLED BY:        ApplNmCanNormal                                                  
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!                
| INPUT PARAMETERS: void                                                             
| RETURN VALUE:     void                                                             
| DESCRIPTION:      This function contains the routine to wakeup the                 
|                   transceiver. The routine depends on the used transceiver         
|                   type.                                                            
|***********************************************************************************/

void CclWakeUpTrcvFct(void)
{ 
  /* RS Pin set to low to enable transceiver hardware */
  CanTrcv_WakeUpTrcv();
}
/************************************************************************************
| NAME:             CclSleepTrcvFct                                                 
| PROTOTYPE:        void CclSleepTrcvFct( void )                                    
| CALLED BY:        ApplNmCanSleep                                                   
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!                
| INPUT PARAMETERS: void                                                             
| RETURN VALUE:     void                                                             
| DESCRIPTION:      This function contains the routine to switch the                 
|                   transceiver into sleep mode. The routine depends on              
|                   the used transceiver type.                                       
|***********************************************************************************/

void CclSleepTrcvFct(void)
{
  /* RS Pin set to high to disable the transceiver hardware now */
  CanTrcv_DisableTrcv();
}





/*********************************************************************************
| NAME:             CclConfigTrcvIntFct                                           
| PROTOTYPE:        void CclConfigTrcvIntFct(void)                                
| CALLED BY:        CclInitPortsPowerOn                                           
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!             
| INPUT PARAMETERS: void                                                          
| RETURN VALUE:     void                                                          
| DESCRIPTION:      This function contains the routine to configure the           
|                   transceiver wakeup interrupt.                                 
|********************************************************************************/

void CclConfigTrcvIntFct(void)
{
  CanTrcv_DummyFun();
}
/*********************************************************************************
| NAME:             CclClearTrcvIntFct                                            
| PROTOTYPE:        void CclClearTrcvIntFct(void)                                 
| CALLED BY:        CclInitPortsPowerOn,                                          
|                   ApplNmCanSleep                                                
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!             
| INPUT PARAMETERS: void                                                          
| RETURN VALUE:     void                                                          
| DESCRIPTION:      This function contains the routine to clear the               
|                   transceiver wakeup interrupt.                                 
|********************************************************************************/

void CclClearTrcvIntFct(void)
{
  CanTrcv_WakeupClearFlag();
}


/*********************************************************************************
| NAME:             CclDisableTrcvIntFct                                          
| PROTOTYPE:        void CclDisableTrcvIntFct(void)                               
| CALLED BY:        CclInitPortsPowerOn,                                          
|                   CclCanWakeUpInt,                                              
|                   CclSetNetRequest                                              
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!             
| INPUT PARAMETERS: void                                                          
| RETURN VALUE:     void                                                          
| DESCRIPTION:      This function contains the routine to disable the             
|                   transceiver wakeup interrupt.                                 
|********************************************************************************/

void CclDisableTrcvIntFct(void)
{
  CanTrcv_DisableWakeup();
}


/*********************************************************************************
| NAME:             CclEnableTrcvIntFct                                           
| PROTOTYPE:        void CclEnableTrcvIntFct(void)                                
| CALLED BY:        ApplNmCanSleep                                                
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!             
| INPUT PARAMETERS: void                                                          
| RETURN VALUE:     void                                                          
| DESCRIPTION:      This function contains the routine to enable the              
|                   transceiver wakeup interrupt.                                 
|********************************************************************************/

void CclEnableTrcvIntFct(void)
{
  CanTrcv_EnableWakeup();
}
/**********************************************************************************
| NAME:             CclCheckTrcvIntFct                                             
| PROTOTYPE:        vuint8 CclCheckTrcvIntFct( void )                              
| CALLED BY:        CclCanStandby                                                  
| PRECONDITIONS:    Application is NOT ALLOWED to call this function!              
| INPUT PARAMETERS: void                                                           
| RETURN VALUE:     kCclTrcvWakeIntPending                                         
|                   kCclTrcvWakeIntNoPending                                       
| DESCRIPTION:      This function checks if an interrupt is pending at the wake up port.
|*********************************************************************************/

vuint8 CclCheckTrcvIntFct(void)
{
  if( CanTrcv_CheckWakeup() ==  0x00 )
    return kCclTrcvWakeIntPending;
  else
    return kCclTrcvWakeIntNoPending;
}







