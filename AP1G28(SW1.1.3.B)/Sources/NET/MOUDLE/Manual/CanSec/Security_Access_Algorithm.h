
#ifndef SECURITY_ACCESS_ALGORITHM_H_
#define SECURITY_ACCESS_ALGORITHM_H_


/*=======[M A C R O S]========================================================*/
#define  SECM_OK        0x00
#define  SECM_NOT_OK    0x01

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
/*************************************************************************/
/*
 * Brief               This service calculated key accord with seed and keyK
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      seed: Latest requested seed
 * Param-Name[in]      keyK: ECU permanent specific parameter for calculat-ing
 *                           the key, this value is provided by OEM
 * Param-Name[in/out]  None
 * Param-Name[out]     key:  Calculated key accord with seed and keyK
 * Return              SECM_OK 0x00:    Calculate success
 *                     SECM_NOT_OK 0x01:Calculate failure
 * PreCondition        None
 */
/*************************************************************************/
extern unsigned char SecM_ComputeKeyLevel1(unsigned long seed,unsigned long KeyK,unsigned long *key);

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
/*************************************************************************/
/*
 * Brief               This service calculated key accord with seed and keyK
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      seed: Latest requested seed
 * Param-Name[in]      keyK: ECU permanent specific parameter for calculat-ing
 *                           the key, this value is provided by OEM
 * Param-Name[in/out]  None
 * Param-Name[out]     key:  Calculated key accord with seed and keyK
 * Return              SECM_OK 0x00:    Calculate success
 *                     SECM_NOT_OK 0x01:Calculate failure
 * PreCondition        None
 */
/*************************************************************************/
extern unsigned char SecM_ComputeKeyLevel2(unsigned long seed,unsigned long KeyK,unsigned long *key);

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
/*************************************************************************/
/*
 * Brief               This service calculated key accord with seed and keyK
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      seed: Latest requested seed
 * Param-Name[in]      keyK: ECU permanent specific parameter for calculat-ing
 *                           the key, this value is provided by OEM
 * Param-Name[in/out]  None
 * Param-Name[out]     key:  Calculated key accord with seed and keyK
 * Return              SECM_OK 0x00:    Calculate success
 *                     SECM_NOT_OK 0x01:Calculate failure
 * PreCondition        None
 */
/*************************************************************************/
extern unsigned char SecM_ComputeKeyLevel3(unsigned long seed,unsigned long KeyK,unsigned long *key);

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
/*************************************************************************/
/*
 * Brief               This service calculated key accord with seed and keyK
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      seed: Latest requested seed
 * Param-Name[in]      keyK: ECU permanent specific parameter for calculat-ing
 *                           the key, this value is provided by OEM
 * Param-Name[in/out]  None
 * Param-Name[out]     key:  Calculated key accord with seed and keyK
 * Return              SECM_OK 0x00:    Calculate success
 *                     SECM_NOT_OK 0x01:Calculate failure
 * PreCondition        None
 */
/*************************************************************************/
extern unsigned char SecM_ComputeKeyLevel4(unsigned long seed,unsigned long KeyK,unsigned long *key);


#endif /*SECURITY_ACCESS_ALGORITHM_H_*/


/*=======[E N D   O F   F I L E]==============================================*/


