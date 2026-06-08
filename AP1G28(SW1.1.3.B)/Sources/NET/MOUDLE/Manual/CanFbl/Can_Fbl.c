#include "desc.h"
#include "Can_Fbl.h"
/*
vuint8  SecMagicFlag[4];
vuint8  fblProgmedMagicFlag[4];
vuint8  AppDesc_FailureAttemptFlag;
vuint16 SeCurretFlahBootID;
vuint8  fblStartMagicFlag[8];
*/


tFblInfo __attribute__ ((section(".RegionKam"))) FblInfo;

/***********************************************************************************************************************
 *  FblStart
 **********************************************************************************************************************/
/*! \brief       Transition from application into flash boot loader
 *  \pre         Valid application program running
 *  \param[in]   pCanInitTable CanInitTable pointer with CAN initialization data
 **********************************************************************************************************************/
__attribute__ ((section(".AppBootInteract"))) void FblStart(void)//( tCanInitTable * pCanInitTable )
{
   FblInterruptDisable();  /* PRQA S 3109 */ /* MD_CBD_14.3 */


    //FblInitSdaBases();

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  // (void)pCanInitTable;
#endif

   /* Set FblStart magic flag
    * Please pay attention: The FblStart magic flag does not use a shared memory area so that the buffer may overlap
    * with the application stack. */
   FblSetFblStartMagicFlag(); /* PRQA S 3109 */ /* MD_CBD_14.3 */

   /* Generate reset */
   APPL_FBL_RESET();
}

