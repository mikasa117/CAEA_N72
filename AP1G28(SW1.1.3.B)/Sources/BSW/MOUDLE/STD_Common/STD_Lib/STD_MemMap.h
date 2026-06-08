/*******************************************************************************
|  File Name:  STD_MemMap.h
|  Description:  Implementation of the Memery Map File
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           YaJun Xia              CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2016-11-30    01.00.00     XYJ       Creation
|
|******************************************************************************/


/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
//#include "Compiler.h"
#include "Typedef.h"
/*******************************************************************************
|    Macro Definition
|******************************************************************************/
/*#define _GREENHILLS_C_MPC560XB_*/
//#define _CODEWARRIOR_C_MPC560XB_
#define _GNU_C_Compiler_S32KXX_
/**************************************************************************************************/
/********************************************* GREENHILLS *****************************************/
/**************************************************************************************************/
#ifdef _GNU_C_Compiler_S32_

#endif/*end of _GNU_C_Compiler_S32_*/

#ifdef _GREENHILLS_C_MPC560XB_
/**************************************** BtrM Start*******************************/
#ifdef STD_BTRM_START_SEC_VAR_RAM
    #undef STD_BTRM_START_SEC_VAR_RAM
    
	#pragma ghs section bss =".myBswBSS"
	#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_BTRM_STOP_SEC_VAR_RAM
    #undef STD_BTRM_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_BTRM_START_SEC_VAR_KAM
    #undef STD_BTRM_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_BTRM_STOP_SEC_VAR_KAM
    #undef STD_BTRM_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_BTRM_START_SEC_CODE
    #undef STD_BTRM_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_BTRM_STOP_SEC_CODE
    #undef STD_BTRM_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** BtrM end*******************************/

/**************************************** CRC Start*******************************/
#ifdef STD_CRC_START_SEC_VAR_RAM
    #undef STD_CRC_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_CRC_STOP_SEC_VAR_RAM
    #undef STD_CRC_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_CRC_START_SEC_VAR_KAM
    #undef STD_CRC_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_CRC_STOP_SEC_VAR_KAM
    #undef STD_CRC_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_CRC_START_SEC_CODE
    #undef STD_CRC_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_CRC_STOP_SEC_CODE
    #undef STD_CRC_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** CRC end*******************************/

/**************************************** LIB Start*******************************/
#ifdef STD_LIB_START_SEC_VAR_RAM
    #undef STD_LIB_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_LIB_STOP_SEC_VAR_RAM
    #undef STD_LIB_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_LIB_START_SEC_VAR_KAM
    #undef STD_LIB_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_LIB_STOP_SEC_VAR_KAM
    #undef STD_LIB_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_LIB_START_SEC_CODE
    #undef STD_LIB_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_LIB_STOP_SEC_CODE
    #undef STD_LIB_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** LIB end*******************************/

/**************************************** ADCM Start*******************************/
#ifdef STD_ADCM_START_SEC_VAR_RAM
    #undef STD_ADCM_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_ADCM_STOP_SEC_VAR_RAM
    #undef STD_ADCM_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_ADCM_START_SEC_VAR_KAM
    #undef STD_ADCM_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_ADCM_STOP_SEC_VAR_KAM
    #undef STD_ADCM_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_ADCM_START_SEC_CODE
    #undef STD_ADCM_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_ADCM_STOP_SEC_CODE
    #undef STD_ADCM_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** ADCM end*******************************/

/**************************************** ADFILTER Start*******************************/
#ifdef STD_ADFILTER_START_SEC_VAR_RAM
    #undef STD_ADFILTER_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_ADFILTER_STOP_SEC_VAR_RAM
    #undef STD_ADFILTER_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_ADFILTER_START_SEC_VAR_KAM
    #undef STD_ADFILTER_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_ADFILTER_STOP_SEC_VAR_KAM
    #undef STD_ADFILTER_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_ADFILTER_START_SEC_CODE
    #undef STD_ADFILTER_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_ADFILTER_STOP_SEC_CODE
    #undef STD_ADFILTER_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** ADFILTER end*******************************/

/**************************************** EEPM Start*******************************/
#ifdef STD_EEPM_START_SEC_VAR_RAM
    #undef STD_EEPM_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_EEPM_STOP_SEC_VAR_RAM
    #undef STD_EEPM_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_EEPM_START_SEC_VAR_KAM
    #undef STD_EEPM_START_SEC_VAR_KAM
    
    #pragma ghs section bss =".NI_NVM_KAM_BSS"
		#pragma ghs section data= ".NI_NVM_KAM_DATA"
#endif

#ifdef STD_EEPM_STOP_SEC_VAR_KAM
    #undef STD_EEPM_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_EEPM_START_SEC_CODE
    #undef STD_EEPM_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_EEPM_STOP_SEC_CODE
    #undef STD_EEPM_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** EEPM end*******************************/

/**************************************** EvM Start*******************************/
#ifdef STD_EVM_START_SEC_VAR_RAM
    #undef STD_EVM_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_EVM_STOP_SEC_VAR_RAM
    #undef STD_EVM_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_EVM_START_SEC_VAR_KAM
    #undef STD_EVM_START_SEC_VAR_KAM
    
    #pragma ghs section bss =".NI_NVM_KAM_BSS"
		#pragma ghs section data= ".NI_NVM_KAM_DATA"
#endif

#ifdef STD_EVM_STOP_SEC_VAR_KAM
    #undef STD_EVM_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_EVM_START_SEC_CODE
    #undef STD_EVM_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_EVM_STOP_SEC_CODE
    #undef STD_EVM_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** EvM end*******************************/

/**************************************** Ea Start*******************************/
#ifdef STD_EA_START_SEC_VAR_RAM
    #undef STD_EA_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_EA_STOP_SEC_VAR_RAM
    #undef STD_EA_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_EA_START_SEC_VAR_KAM
    #undef STD_EA_START_SEC_VAR_KAM
    
    #pragma ghs section bss =".NI_NVM_KAM_BSS"
		#pragma ghs section data= ".NI_NVM_KAM_DATA"
#endif

#ifdef STD_EA_STOP_SEC_VAR_KAM
    #undef STD_EA_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_EA_START_SEC_CODE
    #undef STD_EA_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_EA_STOP_SEC_CODE
    #undef STD_EA_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** Ea end*******************************/

/**************************************** LCDM Start*******************************/
#ifdef STD_LCDM_START_SEC_VAR_RAM
    #undef STD_LCDM_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_LCDM_STOP_SEC_VAR_RAM
    #undef STD_LCDM_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_LCDM_START_SEC_VAR_KAM
    #undef STD_LCDM_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_LCDM_STOP_SEC_VAR_KAM
    #undef STD_LCDM_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_LCDM_START_SEC_CODE
    #undef STD_LCDM_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_LCDM_STOP_SEC_CODE
    #undef STD_LCDM_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** LCDM end*******************************/

/**************************************** LcdCtr Start*******************************/
#ifdef STD_LCDCTR_START_SEC_VAR_RAM
    #undef STD_LCDCTR_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_LCDCTR_STOP_SEC_VAR_RAM
    #undef STD_LCDCTR_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_LCDCTR_START_SEC_VAR_KAM
    #undef STD_LCDCTR_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_LCDCTR_STOP_SEC_VAR_KAM
    #undef STD_LCDCTR_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_LCDCTR_START_SEC_CODE
    #undef STD_LCDCTR_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_LCDCTR_STOP_SEC_CODE
    #undef STD_LCDCTR_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** LCDCTR end*******************************/

/**************************************** LcdDiag Start*******************************/
#ifdef STD_LCDDIAG_START_SEC_VAR_RAM
    #undef STD_LCDDIAG_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_LCDDIAG_STOP_SEC_VAR_RAM
    #undef STD_LCDDIAG_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_LCDDIAG_START_SEC_VAR_KAM
    #undef STD_LCDDIAG_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_LCDDIAG_STOP_SEC_VAR_KAM
    #undef STD_LCDDIAG_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_LCDDIAG_START_SEC_CODE
    #undef STD_LCDDIAG_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_LCDDIAG_STOP_SEC_CODE
    #undef STD_LCDDIAG_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** LCDDIAG end*******************************/

/**************************************** B9795 Start*******************************/
#ifdef STD_B9795_START_SEC_VAR_RAM
    #undef STD_B9795_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_B9795_STOP_SEC_VAR_RAM
    #undef STD_B9795_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_B9795_START_SEC_VAR_KAM
    #undef STD_B9795_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_B9795_STOP_SEC_VAR_KAM
    #undef STD_B9795_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_B9795_START_SEC_CODE
    #undef STD_B9795_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_B9795_STOP_SEC_CODE
    #undef STD_B9795_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** B9795 end*******************************/

/**************************************** LDM Start*******************************/
#ifdef STD_LDM_START_SEC_VAR_RAM
    #undef STD_LDM_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_LDM_STOP_SEC_VAR_RAM
    #undef STD_LDM_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_LDM_START_SEC_VAR_KAM
    #undef STD_LDM_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_LDM_STOP_SEC_VAR_KAM
    #undef STD_LDM_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_LDM_START_SEC_CODE
    #undef STD_LDM_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_LDM_STOP_SEC_CODE
    #undef STD_LDM_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** LDM end*******************************/

/**************************************** LDCTR Start*******************************/
#ifdef STD_LDCTR_START_SEC_VAR_RAM
    #undef STD_LDCTR_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_LDCTR_STOP_SEC_VAR_RAM
    #undef STD_LDCTR_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_LDCTR_START_SEC_VAR_KAM
    #undef STD_LDCTR_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_LDCTR_STOP_SEC_VAR_KAM
    #undef STD_LDCTR_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_LDCTR_START_SEC_CODE
    #undef STD_LDCTR_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_LDCTR_STOP_SEC_CODE
    #undef STD_LDCTR_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** LDCTR end*******************************/

/**************************************** LDDIAG Start*******************************/
#ifdef STD_LDDIAG_START_SEC_VAR_RAM
    #undef STD_LDDIAG_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_LDDIAG_STOP_SEC_VAR_RAM
    #undef STD_LDDIAG_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_LDDIAG_START_SEC_VAR_KAM
    #undef STD_LDDIAG_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_LDDIAG_STOP_SEC_VAR_KAM
    #undef STD_LDDIAG_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_LDDIAG_START_SEC_CODE
    #undef STD_LDDIAG_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_LDDIAG_STOP_SEC_CODE
    #undef STD_LDDIAG_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** LDDIAG end*******************************/

/**************************************** LTM Start*******************************/
#ifdef STD_LTM_START_SEC_VAR_RAM
    #undef STD_LTM_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_LTM_STOP_SEC_VAR_RAM
    #undef STD_LTM_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_LTM_START_SEC_VAR_KAM
    #undef STD_LTM_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_LTM_STOP_SEC_VAR_KAM
    #undef STD_LTM_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_LTM_START_SEC_CODE
    #undef STD_LTM_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_LTM_STOP_SEC_CODE
    #undef STD_LTM_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** LTM end*******************************/

/**************************************** LTCTR Start*******************************/
#ifdef STD_LTCTR_START_SEC_VAR_RAM
    #undef STD_LTCTR_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_LTCTR_STOP_SEC_VAR_RAM
    #undef STD_LTCTR_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_LTCTR_START_SEC_VAR_KAM
    #undef STD_LTCTR_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_LTCTR_STOP_SEC_VAR_KAM
    #undef STD_LTCTR_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_LTCTR_START_SEC_CODE
    #undef STD_LTCTR_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_LTCTR_STOP_SEC_CODE
    #undef STD_LTCTR_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** LTCTR end*******************************/

/**************************************** SRM Start*******************************/
#ifdef STD_SRM_START_SEC_VAR_RAM
    #undef STD_SRM_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_SRM_STOP_SEC_VAR_RAM
    #undef STD_SRM_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_SRM_START_SEC_VAR_KAM
    #undef STD_SRM_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_SRM_STOP_SEC_VAR_KAM
    #undef STD_SRM_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_SRM_START_SEC_CODE
    #undef STD_SRM_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_SRM_STOP_SEC_CODE
    #undef STD_SRM_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** SRM end*******************************/

/**************************************** SRCTR Start*******************************/
#ifdef STD_SRCTR_START_SEC_VAR_RAM
    #undef STD_SRCTR_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_SRCTR_STOP_SEC_VAR_RAM
    #undef STD_SRCTR_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_SRCTR_START_SEC_VAR_KAM
    #undef STD_SRCTR_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_SRCTR_STOP_SEC_VAR_KAM
    #undef STD_SRCTR_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_SRCTR_START_SEC_CODE
    #undef STD_SRCTR_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_SRCTR_STOP_SEC_CODE
    #undef STD_SRCTR_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** SRCTR end*******************************/

/**************************************** SRDIAG Start*******************************/
#ifdef STD_SRDIAG_START_SEC_VAR_RAM
    #undef STD_SRDIAG_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_SRDIAG_STOP_SEC_VAR_RAM
    #undef STD_SRDIAG_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_SRDIAG_START_SEC_VAR_KAM
    #undef STD_SRDIAG_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_SRDIAG_STOP_SEC_VAR_KAM
    #undef STD_SRDIAG_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_SRDIAG_START_SEC_CODE
    #undef STD_SRDIAG_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_SRDIAG_STOP_SEC_CODE
    #undef STD_SRDIAG_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** SRDIAG end*******************************/

/**************************************** SWM Start*******************************/
#ifdef STD_SWM_START_SEC_VAR_RAM
    #undef STD_SWM_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_SWM_STOP_SEC_VAR_RAM
    #undef STD_SWM_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_SWM_START_SEC_VAR_KAM
    #undef STD_SWM_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_SWM_STOP_SEC_VAR_KAM
    #undef STD_SWM_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_SWM_START_SEC_CODE
    #undef STD_SWM_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_SWM_STOP_SEC_CODE
    #undef STD_SWM_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** SWM end*******************************/

/**************************************** SWCTR Start*******************************/
#ifdef STD_SWCTR_START_SEC_VAR_RAM
    #undef STD_SWCTR_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_SWCTR_STOP_SEC_VAR_RAM
    #undef STD_SWCTR_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_SWCTR_START_SEC_VAR_KAM
    #undef STD_SWCTR_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_SWCTR_STOP_SEC_VAR_KAM
    #undef STD_SWCTR_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_SWCTR_START_SEC_CODE
    #undef STD_SWCTR_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_SWCTR_STOP_SEC_CODE
    #undef STD_SWCTR_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** SWCTR end*******************************/

/**************************************** MTRM Start*******************************/
#ifdef STD_MTRM_START_SEC_VAR_RAM
    #undef STD_MTRM_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_MTRM_STOP_SEC_VAR_RAM
    #undef STD_MTRM_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_MTRM_START_SEC_VAR_KAM
    #undef STD_MTRM_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_MTRM_STOP_SEC_VAR_KAM
    #undef STD_MTRM_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_MTRM_START_SEC_CODE
    #undef STD_MTRM_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_MTRM_STOP_SEC_CODE
    #undef STD_MTRM_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** MTRM end*******************************/

/**************************************** MTRIF Start*******************************/
#ifdef STD_MTRIF_START_SEC_VAR_RAM
    #undef STD_MTRIF_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_MTRIF_STOP_SEC_VAR_RAM
    #undef STD_MTRIF_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_MTRIF_START_SEC_VAR_KAM
    #undef STD_MTRIF_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_MTRIF_STOP_SEC_VAR_KAM
    #undef STD_MTRIF_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_MTRIF_START_SEC_CODE
    #undef STD_MTRIF_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_MTRIF_STOP_SEC_CODE
    #undef STD_MTRIF_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** MTRIF end*******************************/

/**************************************** STCTR Start*******************************/
#ifdef STD_STCTR_START_SEC_VAR_RAM
    #undef STD_STCTR_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_STCTR_STOP_SEC_VAR_RAM
    #undef STD_STCTR_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_STCTR_START_SEC_VAR_KAM
    #undef STD_STCTR_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_STCTR_STOP_SEC_VAR_KAM
    #undef STD_STCTR_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_STCTR_START_SEC_CODE
    #undef STD_STCTR_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_STCTR_STOP_SEC_CODE
    #undef STD_STCTR_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** STCTR end*******************************/

/**************************************** STDIAG Start*******************************/
#ifdef STD_STDIAG_START_SEC_VAR_RAM
    #undef STD_STDIAG_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_STDIAG_STOP_SEC_VAR_RAM
    #undef STD_STDIAG_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_STDIAG_START_SEC_VAR_KAM
    #undef STD_STDIAG_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_STDIAG_STOP_SEC_VAR_KAM
    #undef STD_STDIAG_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_STDIAG_START_SEC_CODE
    #undef STD_STDIAG_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_STDIAG_STOP_SEC_CODE
    #undef STD_STDIAG_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** STDIAG end*******************************/

/**************************************** E520 Start*******************************/
#ifdef STD_E520_START_SEC_VAR_RAM
    #undef STD_E520_START_SEC_VAR_RAM
    
    #pragma ghs section bss =".myBswBSS"
		#pragma ghs section data= ".myBswDATA"
#endif

#ifdef STD_E520_STOP_SEC_VAR_RAM
    #undef STD_E520_STOP_SEC_VAR_RAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_E520_START_SEC_VAR_KAM
    #undef STD_E520_START_SEC_VAR_KAM
    
	#pragma ghs section bss =".NI_BSW_KAM_BSS"
	#pragma ghs section data= ".NI_BSW_KAM_DATA"
#endif

#ifdef STD_E520_STOP_SEC_VAR_KAM
    #undef STD_E520_STOP_SEC_VAR_KAM
    
    #pragma ghs section bss =  default
		#pragma ghs section data = default
#endif

#ifdef STD_E520_START_SEC_CODE
    #undef STD_E520_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_E520_STOP_SEC_CODE
    #undef STD_E520_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** STDIAG end*******************************/


#endif	/*end of _GREENHILLS_C_MPC560XB_*/




#ifdef _CODEWARRIOR_C_MPC560XB_

/**************************************** LIB Start*******************************/
#ifdef STD_LIB_START_SEC_VAR_RAM
    #undef STD_LIB_START_SEC_VAR_RAM
    
    #pragma push	/* PRQA S 3116 */
	#pragma section sdata_type data_type ".myBswDATA" ".myBswBSS"	/* PRQA S 3116 */

#endif

#ifdef STD_LIB_STOP_SEC_VAR_RAM
    #undef STD_LIB_STOP_SEC_VAR_RAM
    
    #pragma pop	/* PRQA S 3116 */
#endif

#ifdef STD_LIB_START_SEC_VAR_KAM
    #undef STD_LIB_START_SEC_VAR_KAM
    
	#pragma push	/* PRQA S 3116 */
	#pragma section sdata_type data_type ".TempDATA" ".NI_BSW_KAM_BSS" 	/* PRQA S 3116 */

#endif

#ifdef STD_LIB_STOP_SEC_VAR_KAM
    #undef STD_LIB_STOP_SEC_VAR_KAM
    
    #pragma pop	/* PRQA S 3116 */
#endif

#ifdef STD_LIB_START_SEC_CODE
    #undef STD_LIB_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_LIB_STOP_SEC_CODE
    #undef STD_LIB_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** LIB end*******************************/

/**************************************** CRC Start*******************************/
#ifdef STD_CRC_START_SEC_VAR_RAM
    #undef STD_CRC_START_SEC_VAR_RAM
    
    #pragma push	/* PRQA S 3116 */
	#pragma section sdata_type data_type ".myBswDATA" ".myBswBSS"	/* PRQA S 3116 */

#endif

#ifdef STD_CRC_STOP_SEC_VAR_RAM
    #undef STD_CRC_STOP_SEC_VAR_RAM
    
    #pragma pop	/* PRQA S 3116 */
#endif

#ifdef STD_CRC_START_SEC_VAR_KAM
    #undef STD_CRC_START_SEC_VAR_KAM
    
	#pragma push	/* PRQA S 3116 */
	#pragma section sdata_type data_type ".TempDATA" ".NI_BSW_KAM_BSS" 	/* PRQA S 3116 */

#endif

#ifdef STD_CRC_STOP_SEC_VAR_KAM
    #undef STD_CRC_STOP_SEC_VAR_KAM
    
    #pragma pop	/* PRQA S 3116 */
#endif

#ifdef STD_CRC_START_SEC_CODE
    #undef STD_CRC_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_CRC_STOP_SEC_CODE
    #undef STD_CRC_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** CRC end*******************************/

/**************************************** MTRM Start*******************************/
#ifdef STD_MTRM_START_SEC_VAR_RAM
    #undef STD_MTRM_START_SEC_VAR_RAM
    
    #pragma push	/* PRQA S 3116 */
	#pragma section sdata_type data_type ".myBswDATA" ".myBswBSS"	/* PRQA S 3116 */
#endif

#ifdef STD_MTRM_STOP_SEC_VAR_RAM
    #undef STD_MTRM_STOP_SEC_VAR_RAM
    
    #pragma pop	/* PRQA S 3116 */
#endif

#ifdef STD_MTRM_START_SEC_VAR_KAM
    #undef STD_MTRM_START_SEC_VAR_KAM
    
	#pragma push	/* PRQA S 3116 */
	#pragma section sdata_type data_type ".TempDATA" ".NI_BSW_KAM_BSS" 	/* PRQA S 3116 */
#endif

#ifdef STD_MTRM_STOP_SEC_VAR_KAM
    #undef STD_MTRM_STOP_SEC_VAR_KAM
    
    #pragma pop	/* PRQA S 3116 */
#endif

#ifdef STD_MTRM_START_SEC_CODE
    #undef STD_MTRM_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_MTRM_STOP_SEC_CODE
    #undef STD_MTRM_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** MTRM end*******************************/

/**************************************** MTRIF Start*******************************/
#ifdef STD_MTRIF_START_SEC_VAR_RAM
    #undef STD_MTRIF_START_SEC_VAR_RAM
    
    #pragma push	/* PRQA S 3116 */
	#pragma section sdata_type data_type ".myBswDATA" ".myBswBSS"	/* PRQA S 3116 */
#endif

#ifdef STD_MTRIF_STOP_SEC_VAR_RAM
    #undef STD_MTRIF_STOP_SEC_VAR_RAM
    
    #pragma pop	/* PRQA S 3116 */
#endif

#ifdef STD_MTRIF_START_SEC_VAR_KAM
    #undef STD_MTRIF_START_SEC_VAR_KAM
    
	#pragma push	/* PRQA S 3116 */
	#pragma section sdata_type data_type ".TempDATA" ".NI_BSW_KAM_BSS" 	/* PRQA S 3116 */
#endif

#ifdef STD_MTRIF_STOP_SEC_VAR_KAM
    #undef STD_MTRIF_STOP_SEC_VAR_KAM
    
    #pragma pop	/* PRQA S 3116 */
#endif

#ifdef STD_MTRIF_START_SEC_CODE
    #undef STD_MTRIF_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_MTRIF_STOP_SEC_CODE
    #undef STD_MTRIF_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** MTRIF end*******************************/

/**************************************** DCCTR Start*******************************/
#ifdef STD_DCCTR_START_SEC_VAR_RAM
    #undef STD_DCCTR_START_SEC_VAR_RAM
    
    #pragma push	/* PRQA S 3116 */
	#pragma section sdata_type data_type ".myBswDATA" ".myBswBSS"	/* PRQA S 3116 */
#endif

#ifdef STD_DCCTR_STOP_SEC_VAR_RAM
    #undef STD_DCCTR_STOP_SEC_VAR_RAM
    
    #pragma pop	/* PRQA S 3116 */
#endif

#ifdef STD_DCCTR_START_SEC_VAR_KAM
    #undef STD_DCCTR_START_SEC_VAR_KAM
    
	#pragma push	/* PRQA S 3116 */
	#pragma section sdata_type data_type ".TempDATA" ".NI_BSW_KAM_BSS" 	/* PRQA S 3116 */
#endif

#ifdef STD_DCCTR_STOP_SEC_VAR_KAM
    #undef STD_DCCTR_STOP_SEC_VAR_KAM
    
    #pragma pop	/* PRQA S 3116 */
#endif

#ifdef STD_DCCTR_START_SEC_CODE
    #undef STD_DCCTR_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_DCCTR_STOP_SEC_CODE
    #undef STD_DCCTR_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** DCCTR end*******************************/

/**************************************** DCDTC Start*******************************/
#ifdef STD_DCDTC_START_SEC_VAR_RAM
    #undef STD_DCDTC_START_SEC_VAR_RAM
    
    #pragma push	/* PRQA S 3116 */
	#pragma section sdata_type data_type ".myBswDATA" ".myBswBSS"	/* PRQA S 3116 */
#endif

#ifdef STD_DCDTC_STOP_SEC_VAR_RAM
    #undef STD_DCDTC_STOP_SEC_VAR_RAM
    
    #pragma pop	/* PRQA S 3116 */
#endif

#ifdef STD_DCDTC_START_SEC_VAR_KAM
    #undef STD_DCDTC_START_SEC_VAR_KAM
    
	#pragma push	/* PRQA S 3116 */
	#pragma section sdata_type data_type ".TempDATA" ".NI_BSW_KAM_BSS" 	/* PRQA S 3116 */
#endif

#ifdef STD_DCDTC_STOP_SEC_VAR_KAM
    #undef STD_DCDTC_STOP_SEC_VAR_KAM
    
    #pragma pop	/* PRQA S 3116 */
#endif

#ifdef STD_DCDTC_START_SEC_CODE
    #undef STD_DCDTC_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_DCDTC_STOP_SEC_CODE
    #undef STD_DCDTC_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** DCDTC end*******************************/

/**************************************** DCCPID Start*******************************/
#ifdef STD_DCCPID_START_SEC_VAR_RAM
    #undef STD_DCCPID_START_SEC_VAR_RAM
    
    #pragma push	/* PRQA S 3116 */
	#pragma section sdata_type data_type ".myBswDATA" ".myBswBSS"	/* PRQA S 3116 */
#endif

#ifdef STD_DCCPID_STOP_SEC_VAR_RAM
    #undef STD_DCCPID_STOP_SEC_VAR_RAM
    
    #pragma pop	/* PRQA S 3116 */
#endif

#ifdef STD_DCCPID_START_SEC_VAR_KAM
    #undef STD_DCCPID_START_SEC_VAR_KAM
    
	#pragma push	/* PRQA S 3116 */
	#pragma section sdata_type data_type ".TempDATA" ".NI_BSW_KAM_BSS" 	/* PRQA S 3116 */
#endif

#ifdef STD_DCCPID_STOP_SEC_VAR_KAM
    #undef STD_DCCPID_STOP_SEC_VAR_KAM
    
    #pragma pop	/* PRQA S 3116 */
#endif

#ifdef STD_DCCPID_START_SEC_CODE
    #undef STD_DCCPID_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_DCCPID_STOP_SEC_CODE
    #undef STD_DCCPID_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** DCCPID end*******************************/

/**************************************** DCPID Start*******************************/
#ifdef STD_DCPID_START_SEC_VAR_RAM
    #undef STD_DCPID_START_SEC_VAR_RAM
    
    #pragma push	/* PRQA S 3116 */
	#pragma section sdata_type data_type ".myBswDATA" ".myBswBSS"	/* PRQA S 3116 */
#endif

#ifdef STD_DCPID_STOP_SEC_VAR_RAM
    #undef STD_DCPID_STOP_SEC_VAR_RAM
    
    #pragma pop	/* PRQA S 3116 */
#endif

#ifdef STD_DCPID_START_SEC_VAR_KAM
    #undef STD_DCPID_START_SEC_VAR_KAM
    
	#pragma push	/* PRQA S 3116 */
	#pragma section sdata_type data_type ".TempDATA" ".NI_BSW_KAM_BSS" 	/* PRQA S 3116 */
#endif

#ifdef STD_DCPID_STOP_SEC_VAR_KAM
    #undef STD_DCPID_STOP_SEC_VAR_KAM
    
    #pragma pop	/* PRQA S 3116 */
#endif

#ifdef STD_DCPID_START_SEC_CODE
    #undef STD_DCPID_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_DCPID_STOP_SEC_CODE
    #undef STD_DCPID_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** DCPID end*******************************/

/**************************************** TLE81 Start*******************************/
#ifdef STD_TLE81_START_SEC_VAR_RAM
    #undef STD_TLE81_START_SEC_VAR_RAM
    
    #pragma push	/* PRQA S 3116 */
	#pragma section sdata_type data_type ".myBswDATA" ".myBswBSS"	/* PRQA S 3116 */

#endif

#ifdef STD_TLE81_STOP_SEC_VAR_RAM
    #undef STD_TLE81_STOP_SEC_VAR_RAM
    
    #pragma pop	/* PRQA S 3116 */
#endif

#ifdef STD_TLE81_START_SEC_VAR_KAM
    #undef STD_TLE81_START_SEC_VAR_KAM
    
	#pragma push	/* PRQA S 3116 */
	#pragma section sdata_type data_type ".TempDATA" ".NI_BSW_KAM_BSS" 	/* PRQA S 3116 */

#endif

#ifdef STD_TLE81_STOP_SEC_VAR_KAM
    #undef STD_TLE81_STOP_SEC_VAR_KAM
    
    #pragma pop	/* PRQA S 3116 */
#endif

#ifdef STD_TLE81_START_SEC_CODE
    #undef STD_TLE81_START_SEC_CODE
    
    #define START_SEC_CODE	/*mapped to default code section*/
#endif

#ifdef STD_TLE81_STOP_SEC_CODE
    #undef STD_TLE81_STOP_SEC_CODE
    
    #define STOP_SEC_CODE	/* default code stop section */
#endif
/**************************************** TLE81 end*******************************/

#endif	/*end of _CODEWARRIOR_C_MPC560XB_*/
/*EOF*/
