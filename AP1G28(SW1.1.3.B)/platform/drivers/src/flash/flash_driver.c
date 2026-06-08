/*
 * Copyright 2020-2022 Yuntu Microelectronics co.,ltd
 * All rights reserved.
 *
 * YUNTU Confidential. This software is owned or controlled by YUNTU and may
 * only be used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms. If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software. The production use license in
 * Section 2.3 is expressly granted for this software.
 */
/*!
 * @file flash_driver.c
 */

#include "flash_driver.h"
#include "flash_hw_access.h"
#include "interrupt_manager.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Table of base addresses for EFM instances. */
static EFM_Type * const s_efmBase[EFM_INSTANCE_COUNT] = EFM_BASE_PTRS;

/* Pointer to runtime state structure.*/
static flash_state_t * s_FlashStatePtr[EFM_INSTANCE_COUNT] = {NULL};

/* Table for EFM IRQ numbers */
static const IRQn_Type s_efmIrqId[EFM_INSTANCE_COUNT] = EFM_IRQS;

#ifdef EFM_READ_COLLISION_IRQS
static const IRQn_Type s_efmReadCollisionIrqId[I2C_INSTANCE_COUNT] = EFM_READ_COLLISION_IRQS;
#endif /* EFM_READ_COLLISION_IRQS */

static flash_syncCallback_t s_SyncCallBackFunction = NULL_SYNCCALLBACK;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/* Declaration of EFM_IRQHandler. Needed just to avoid MISRA violation. */
void EFM_IRQHandler(void);

/* Declaration of EFM_Error_IRQHandler. Needed just to avoid MISRA violation. */
void EFM_Error_IRQHandler(void);

/*******************************************************************************
 * Internal Functions
 ******************************************************************************/
/*!
 * @brief Internal flash command to execute flash commands.
 *        This function will be copy to RAM section when system boot.
 *
 * @param[in] command Target flash command.
 */
START_FUNCTION_DECLARATION_RAMSECTION
status_t FLASH_LaunchCommandSequence(uint32_t instance) __attribute__((noinline))
END_FUNCTION_DECLARATION_RAMSECTION

/*!
 * @brief Internal flash command to execute flash commands.
 *        This function will be copy to RAM section when system boot.
 *
 * @param[in] command Target flash command.
 */
 uint32_t FLASH_GetSectorSize(uint32_t dest);

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_LaunchCommandSequence
 * Description   : Perform command write sequence on Flash.
 * It is internal function, called by driver APIs only.
 *
 *END**************************************************************************/
START_FUNCTION_DEFINITION_RAMSECTION
DISABLE_CHECK_RAMSECTION_FUNCTION_CALL
status_t FLASH_LaunchCommandSequence(uint32_t instance)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];
    flash_state_t *state = s_FlashStatePtr[instance];
    DEV_ASSERT(state != NULL);
    status_t status = STATUS_SUCCESS; /* Return code variable */
    uint32_t primask_bit;

    /* Enter critical section: Disable interrupts to avoid any interruption during the command launch */
    primask_bit = __get_PRIMASK();
    __disable_irq();

#ifndef EFM_CTRL_WE_MASK
    /* Add NOP command to clear write buffer */
    base->CMD = 0;
#endif

    /* clear pending status */
    /* static inline functions are risks due to "-o0" optimization not inlined,
       So operate registers directly in ram function */
    base->STS = FEATURE_EFM_CMD_ERROR_MASK | EFM_STS_DONE_MASK;

    EFM_ENABLE_WE_COMMAND();
    /* Passing parameter to the command */
    for (uint32_t i = 0; i < state->cmdParam.word_size; i++)
    {
        state->cmdParam.dest[i] = state->cmdParam.pdata[i];
#ifdef EFM_STS_ARRAY_SELECTED_MASK
        while (EFM_STS_ARRAY_SELECTED_MASK != (base->STS & EFM_STS_ARRAY_SELECTED_MASK))
            ;
#endif /* EFM_STS_SET_ADDR_MASK */
    }
#ifdef EFM_STS_SET_ADDR_MASK
    while (EFM_STS_SET_ADDR_MASK != (base->STS & EFM_STS_SET_ADDR_MASK))
        ;
#endif /* EFM_STS_SET_ADDR_MASK */
    EFM_DISABLE_WE_COMMAND();

    EFM_UNLOCK_CMD_REGISTER();
    /* Write command register to launch command */
    if (state->cmdParam.cmdCode == 0xFEU)
    {
        /* Quick erase sector by split erase sector time */
        base->CMD = FEATURE_EFM_ERASE_SECTOR_CMD_CODE;
    }else{
        base->CMD = EFM_CMD_CMD(state->cmdParam.cmdCode);
    }
    /* if sync mode config disGlobalInt, keep disable global interrupt */
    if(false == state->disGlobalInt)
    {
        /* Exit critical section: restore previous priority mask */
        __set_PRIMASK(primask_bit);
    }

    if (false == state->async)
    {
        while (EFM_STS_IDLE_MASK != (base->STS & EFM_STS_IDLE_MASK))
        {
            /* Wait till IDLE bit is set
             * Serve callback function as often as possible
             */
            if (NULL_SYNCCALLBACK != s_SyncCallBackFunction)
            {
                /* Temporarily disable compiler's check for ROM access call from within a ram function.
                 * The use of a function pointer type makes this check irrelevant.
                 * Nevertheless, it is imperative that the user-provided callback be defined in RAM SECTION */
                s_SyncCallBackFunction();
            }
        }

        if (0U != (base->STS & FEATURE_EFM_CMD_ERROR_MASK))
        {
            status = STATUS_ERROR;
        }
    }
#if defined(FEATURE_SOC_SUPPORT_CACHE) && FEATURE_SOC_SUPPORT_CACHE
        /* Invalidate flash cache */
        CACHE->CACR |= CACHE_CACR_CMDREQ_MASK | CACHE_CACR_IW1_MASK | CACHE_CACR_IW0_MASK;
        while (CACHE->CACR & CACHE_CACR_CMDREQ_MASK)
            ;
#endif /* FEATURE_SOC_SUPPORT_CACHE */

#if defined(__DCACHE_PRESENT) && __DCACHE_PRESENT
        if (SCB->CCR & SCB_CCR_DC_Msk)
        {
            SCB_CleanInvalidateDCache();
        }
#endif
    if(true == state->disGlobalInt)
    {
        /* Exit critical section: restore previous priority mask */
        __set_PRIMASK(primask_bit);
    }

    return status;
}
ENABLE_CHECK_RAMSECTION_FUNCTION_CALL
END_FUNCTION_DEFINITION_RAMSECTION

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_GetSectorSize
 * Description   : Get flash sector size based on the destination address.
 * It is internal function, called by driver APIs only.
 *
 *END**************************************************************************/
uint32_t FLASH_GetSectorSize(uint32_t dest)
{
    uint32_t sectorSize = 0;
    if ((dest < FEATURE_EFM_MAIN_ARRAY_END_ADDRESS)
#if defined(FEATURE_EFM_MAIN_ARRAY_START_ADDRESS) && (FEATURE_EFM_MAIN_ARRAY_START_ADDRESS != 0)
            && (dest >= FEATURE_EFM_MAIN_ARRAY_START_ADDRESS)
#endif /* FEATURE_EFM_MAIN_ARRAY_START_ADDRESS */
        )
    {
        /* Flash main array */
        sectorSize = FEATURE_EFM_MAIN_ARRAY_SECTOR_SIZE;
    }
#if FEATURE_EFM_HAS_DATA_FLASH
    else if ((dest < FEATURE_EFM_DATA_ARRAY_END_ADDRESS)
            && (dest >= FEATURE_EFM_DATA_ARRAY_START_ADDRESS))
    {
        /* Flash data array */
        sectorSize = FEATURE_EFM_DATA_ARRAY_SECTOR_SIZE;
    }
#endif
#if FEATURE_EFM_HAS_NVR_FLASH
    else if ((dest < FEATURE_EFM_NVR_ARRAY_END_ADDRESS)
             && (dest >= FEATURE_EFM_NVR_ARRAY_START_ADDRESS))
    {
        /* Flash NVR array */
        sectorSize = FEATURE_EFM_NVR_ARRAY_SECTOR_SIZE;
    }
#endif
    else{
        sectorSize = 0;
    }
    return sectorSize;
}

/*FUNCTION**********************************************************************
*
* Function Name : FLASH_EventCallback
* Description   : Callback function for flash module.
*                 Used only for internal functions.
*
*END**************************************************************************/
static void FLASH_EventCallback(EFM_Type *base, flash_state_t *state, flash_event_t event)
{
    (void) base;
    if(event == FLASH_EVENT_ERROR || event == FLASH_EVENT_COMPLETE || event == FLASH_EVENT_ACCESS_ERROR)
    {
        state->driverBusy = false;
    }
#if (defined(FEATURE_EFM_ERASE_SECTOR_RETRY_CMD_CODE) && defined(EFM_CTRL_CMD_VERIFY_EN_MASK))
    if (state->cmdParam.cmdCode == FEATURE_EFM_ERASE_SECTOR_RETRY_CMD_CODE
#ifdef FEATURE_EFM_ERASE_SECTOR_VREAD_RETRY_CMD_CODE
        || state->cmdParam.cmdCode == FEATURE_EFM_ERASE_SECTOR_VREAD_RETRY_CMD_CODE
#endif /* FEATURE_EFM_ERASE_SECTOR_VREAD_RETRY_CMD_CODE */
    )
    {
        if (true == state->readVerify)
        {
            base->CTRL |= EFM_CTRL_CMD_VERIFY_EN_MASK;
        }
        else
        {
            base->CTRL &= ~EFM_CTRL_CMD_VERIFY_EN_MASK;
        }
    }
#endif
    if (NULL_CALLBACK != state->callback)
    {
        state->callback(event);
    }
}

/*FUNCTION**********************************************************************
*
* Function Name : FLASH_DRV_DoneIRQHandler
* Description   : Interrupt handler for flash module done event.
*
*END**************************************************************************/
void FLASH_DRV_DoneIRQHandler(uint32_t instance)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];
    flash_state_t *state = s_FlashStatePtr[instance];
    DEV_ASSERT(state != NULL);
#ifdef FEATURE_EFM_PROGRAM_NVR_CMD_CODE
    uint32_t efm_data[FEATURE_EFM_WRITE_UNIT_WORD_SIZE + 1];
#endif /* FEATURE_EFM_PROGRAM_NVR_CMD_CODE */

#ifdef EFM_CTRL_RETRY_CFG_MASK
    uint32_t retry_cfg;
#endif /* EFM_CTRL_RETRY_CFG_MASK */

    FLASH_ClearDoneStatusFlag(base);
    if (state->async)
    {
        if (FLASH_GetErrorStatus(base))
        {
#ifdef FEATURE_EFM_ERASE_SECTOR_VREAD_RETRY_CMD_CODE
            if (FEATURE_EFM_ERASE_SECTOR_VREAD_RETRY_CMD_CODE == state->cmdParam.cmdCode)
            {
                state->cmdParam.cmdCode = FEATURE_EFM_ERASE_SECTOR_RETRY_CMD_CODE;
            }
#endif /* FEATURE_EFM_ERASE_SECTOR_VREAD_RETRY_CMD_CODE */
#ifdef FEATURE_EFM_ERASE_SECTOR_RETRY_CMD_CODE
            if (FEATURE_EFM_ERASE_SECTOR_RETRY_CMD_CODE == state->cmdParam.cmdCode)
            {
                if (state->retryCount < FLASH_RETRY_MAX_COUNT)
                {
                    state->retryCount++;
#ifdef EFM_CTRL_RETRY_CFG_MASK
                    if (FLASH_RETRY_CFG_START + state->retryCount <= 0x7U)
                    {
                        retry_cfg = base->CTRL & ~EFM_CTRL_RETRY_CFG_MASK;
                        retry_cfg |= EFM_CTRL_RETRY_CFG(FLASH_RETRY_CFG_START + state->retryCount); /* IAR Warning[Pa082] */
                        base->CTRL = retry_cfg;
                    }
#endif /* EFM_CTRL_RETRY_CFG_MASK */
                    FLASH_LaunchCommandSequence(instance);
                }
                else
                {
                    FLASH_EventCallback(base, state, FLASH_EVENT_ERROR);
                }
            }
            else
#endif /* FEATURE_EFM_ERASE_SECTOR_RETRY_CMD_CODE */
            {
                FLASH_EventCallback(base, state, FLASH_EVENT_ERROR);
            }
        }
        else
        {
            switch (state->cmdParam.cmdCode)
            {
                case FEATURE_EFM_ERASE_BLOCK_CMD_CODE:
#ifdef FEATURE_EFM_ERASE_BLOCK_VERIFY_CMD_CODE
                case FEATURE_EFM_ERASE_BLOCK_VERIFY_CMD_CODE:
#endif /* FEATURE_EFM_ERASE_BLOCK_VERIFY_CMD_CODE */
                    state->leftSize = 0U;
                    break;

                case FEATURE_EFM_ERASE_SECTOR_CMD_CODE:
#ifdef FEATURE_EFM_ERASE_SECTOR_VERIFY_CMD_CODE
                case FEATURE_EFM_ERASE_SECTOR_VERIFY_CMD_CODE:
#endif /* FEATURE_EFM_ERASE_SECTOR_VERIFY_CMD_CODE */
                    state->leftSize -= FLASH_GetSectorSize((uint32_t)state->cmdParam.dest);
                    state->cmdParam.dest += FLASH_GetSectorSize((uint32_t)state->cmdParam.dest) >> 2;
                    break;

#ifdef FEATURE_EFM_ERASE_SECTOR_RETRY_CMD_CODE
                case FEATURE_EFM_ERASE_SECTOR_RETRY_CMD_CODE:
#ifdef FEATURE_EFM_ERASE_SECTOR_VREAD_RETRY_CMD_CODE
                    state->cmdParam.cmdCode = FEATURE_EFM_ERASE_SECTOR_VREAD_RETRY_CMD_CODE;
                    break;
                case FEATURE_EFM_ERASE_SECTOR_VREAD_RETRY_CMD_CODE:
                    state->cmdParam.cmdCode = FEATURE_EFM_ERASE_SECTOR_RETRY_CMD_CODE;
#endif /* FEATURE_EFM_ERASE_SECTOR_VREAD_RETRY_CMD_CODE */
#ifdef EFM_CTRL_RETRY_CFG_MASK
                    retry_cfg = (base->CTRL & ~EFM_CTRL_RETRY_CFG_MASK);
                    retry_cfg |= EFM_CTRL_RETRY_CFG(0x7U);
#endif /* EFM_CTRL_RETRY_CFG_MASK */
                    /* Append one more erase after finish to ensure erase thoroughly */
                    if (state->retryCount != 0xFFFFFFFFU)
                    {
                        state->retryCount = 0xFFFFFFFFU;
                    }
                    else
                    {
                        state->retryCount = 0U;
#ifdef EFM_CTRL_RETRY_CFG_MASK
                        retry_cfg |= EFM_CTRL_RETRY_CFG(FLASH_RETRY_CFG_START);
#endif /* EFM_CTRL_RETRY_CFG_MASK */
                        state->leftSize -= FLASH_GetSectorSize((uint32_t)state->cmdParam.dest);
                        state->cmdParam.dest += FLASH_GetSectorSize((uint32_t)state->cmdParam.dest) >> 2;
                    }
#ifdef EFM_CTRL_RETRY_CFG_MASK
                    base->CTRL = retry_cfg;
#endif /* EFM_CTRL_RETRY_CFG_MASK */
                    break;
#endif /* FEATURE_EFM_ERASE_SECTOR_RETRY_CMD_CODE */

                case FEATURE_EFM_PROGRAM_CMD_CODE:
#ifdef FEATURE_EFM_PROGRAM_VERIFY_CMD_CODE
                case FEATURE_EFM_PROGRAM_VERIFY_CMD_CODE:
#endif /* FEATURE_EFM_PROGRAM_VERIFY_CMD_CODE */
                    state->leftSize -= FEATURE_EFM_WRITE_UNIT_SIZE;
                    state->cmdParam.dest += FEATURE_EFM_WRITE_UNIT_WORD_SIZE;
                    state->cmdParam.pdata += FEATURE_EFM_WRITE_UNIT_WORD_SIZE;
                    break;

#ifdef FEATURE_EFM_PROGRAM_DATA_CMD_CODE
                case FEATURE_EFM_PROGRAM_DATA_CMD_CODE:
                    state->leftSize -= FEATURE_EFM_WRITE_DATA_UNIT_SIZE;
                    state->cmdParam.dest += FEATURE_EFM_WRITE_DATA_UNIT_WORD_SIZE;
                    state->cmdParam.pdata += FEATURE_EFM_WRITE_DATA_UNIT_WORD_SIZE;
                    break;
#endif /* FEATURE_EFM_PROGRAM_DATA_CMD_CODE */

#ifdef FEATURE_EFM_ERASE_NVR_CMD_CODE
                case FEATURE_EFM_ERASE_NVR_CMD_CODE:
                    /* Only Erase one sector, finish it */
                    break;
#endif /* FEATURE_EFM_ERASE_NVR_CMD_CODE */

#ifdef FEATURE_EFM_PROGRAM_NVR_CMD_CODE
                case FEATURE_EFM_PROGRAM_NVR_CMD_CODE:
                    state->leftSize -= FEATURE_EFM_WRITE_UNIT_SIZE;
                    state->cmdParam.pdata = efm_data;
                    state->nvr_addr += FEATURE_EFM_WRITE_UNIT_SIZE;
                    state->nvr_data += FEATURE_EFM_WRITE_UNIT_WORD_SIZE;

                    efm_data[0] = state->nvr_addr;
                    for (uint32_t i = 0U; i < FEATURE_EFM_WRITE_UNIT_WORD_SIZE; i++)
                    {
                        efm_data[i + 1U] = state->nvr_data[i];
                    }
                    break;
#endif /* FEATURE_EFM_PROGRAM_NVR_CMD_CODE */

                default:
                    break;
            }
            if (state->leftSize > 0U)
            {
                FLASH_LaunchCommandSequence(instance);
            }
            else
            {
                FLASH_EventCallback(base, state, FLASH_EVENT_COMPLETE);
            }
        }
    }
    else /* sync mode */
    {
        if (FLASH_GetErrorStatus(base))
        {
            FLASH_EventCallback(base, state, FLASH_EVENT_ERROR);
        }
        else
        {
            FLASH_EventCallback(base, state, FLASH_EVENT_COMPLETE);
        }
    }
}

/*FUNCTION**********************************************************************
*
* Function Name : FLASH_DRV_ReadCollisionIRQHandler
* Description   : Interrupt handler for flash module access error event.
*
*END**************************************************************************/
void FLASH_DRV_ReadCollisionIRQHandler(uint32_t instance)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    flash_state_t *state = s_FlashStatePtr[instance];
    DEV_ASSERT(state != NULL);
    EFM_Type *base = s_efmBase[instance];

    FLASH_DRV_ClearReadCollisionFlag(base);
    FLASH_EventCallback(base, state, FLASH_EVENT_ACCESS_ERROR);
}

/*FUNCTION**********************************************************************
*
* Function Name : EFM_IRQHandler
* Description   : Interrupt handler for flash module.
* This handler is used when flash driver is configured for async mode.
*
*END**************************************************************************/
#if (EFM_INSTANCE_COUNT > 0U)
/* Implementation of EFM handler named in startup code. */
void EFM_IRQHandler(void)
{
    if (FLASH_GetDoneStatus(EFM))
    {
        FLASH_DRV_DoneIRQHandler(0);
    }
}

/* Implementation of EFM Error handler named in startup code. */
void EFM_Error_IRQHandler(void)
{
    if (FLASH_DRV_GetReadCollisionFlag(EFM))
    {
        FLASH_DRV_ReadCollisionIRQHandler(0);
    }
}
#endif

/*FUNCTION**********************************************************************
*
* Function Name : FLASH_DRV_Init
* Description   : Initialize the Flash module.
*
* Implements    : FLASH_DRV_Init_Activity
*END**************************************************************************/
status_t FLASH_DRV_Init(uint32_t instance, const flash_user_config_t * userConfigPtr, flash_state_t * state)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    DEV_ASSERT(s_FlashStatePtr[instance] == NULL);
    DEV_ASSERT(userConfigPtr != NULL);
    DEV_ASSERT(state != NULL);

    EFM_Type *base = s_efmBase[instance];
    status_t status = STATUS_SUCCESS;    /* Return code variable */

    if (FLASH_GetIdleStatus(base)){
        FLASH_ClearErrorFlags(base);
        FLASH_ClearDoneStatusFlag(base);
        s_FlashStatePtr[instance] = state;
        state->async = userConfigPtr->async;
        state->callback = userConfigPtr->callback;
        state->disGlobalInt = userConfigPtr->disGlobalInt;
        state->driverBusy = false;

#ifdef EFM_CTRL_CMD_VERIFY_EN_MASK
        if (true == userConfigPtr->readVerify)
        {
            base->CTRL |= EFM_CTRL_CMD_VERIFY_EN_MASK;
        }
        else
        {
            base->CTRL &= ~EFM_CTRL_CMD_VERIFY_EN_MASK;
        }
#endif
        state->readVerify = userConfigPtr->readVerify;

        /* Enable flash interrupt */
        if (state->async)
        {
            FLASH_DRV_EnableCmdCompleteInterrupt(instance);
            INT_SYS_EnableIRQ(s_efmIrqId[instance]);
            FLASH_DRV_EnableReadCollisionInterrupt(instance);
#ifdef EFM_READ_COLLISION_IRQS
            INT_SYS_EnableIRQ(s_efmReadCollisionIrqId[instance]);
#endif /* EFM_READ_COLLISION_IRQS */
        }

    }else{
        status = STATUS_EFM_BUSY;
    }
    return status;
}

/*FUNCTION**********************************************************************
*
* Function Name : FLASH_DRV_Deinit
* Description   : De-initialize the Flash module.
*
* Implements    : FLASH_DRV_Deinit_Activity
*END**************************************************************************/
status_t FLASH_DRV_Deinit(uint32_t instance)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];
    flash_state_t *state = s_FlashStatePtr[instance];
    status_t status = STATUS_SUCCESS;    /* Return code variable */
    DEV_ASSERT(state != NULL);

    if (FLASH_GetIdleStatus(base)){
        FLASH_ClearErrorFlags(base);
        FLASH_ClearDoneStatusFlag(base);
        /* Disable flash interrupt */
        if (state->async)
        {
            FLASH_DRV_DisableCmdCompleteInterrupt(instance);
            INT_SYS_DisableIRQ(EFM_IRQn);
        }
        s_FlashStatePtr[instance] = NULL;
    }else{
        status = STATUS_EFM_BUSY;
    }
    return status;
}

/*FUNCTION**********************************************************************
*
* Function Name : FLASH_DRV_GetDefaultConfig
* Description   : Gets the default configuration structure for the Flash module.
*
* Implements    : FLASH_DRV_GetDefaultConfig_Activity
*END**************************************************************************/
void FLASH_DRV_GetDefaultConfig(flash_user_config_t * const userConfigPtr)
{
    DEV_ASSERT(userConfigPtr != NULL);

    /* Set default configuration for flash module */
    userConfigPtr->async = false;
    userConfigPtr->disGlobalInt = true;
    userConfigPtr->readVerify = true;
    userConfigPtr->callback = NULL_CALLBACK;
}

/*FUNCTION**********************************************************************
*
* Function Name : FLASH_DRV_GetBusyStatus
* Description   : Get the Flash module busy status.
*
* Implements    : FLASH_DRV_GetBusyStatus_Activity
*END**************************************************************************/
bool FLASH_DRV_GetBusyStatus(uint32_t instance)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    flash_state_t *state = s_FlashStatePtr[instance];
    DEV_ASSERT(state != NULL);

    return state->driverBusy;
}

/*FUNCTION**********************************************************************
*
* Function Name : FLASH_DRV_SetAsyncMode
* Description   : Enable or disable async mode.
*
* Implements    : FLASH_DRV_SetAsyncMode_Activity
*END**************************************************************************/
status_t FLASH_DRV_SetAsyncMode(uint32_t instance, bool async)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];
    flash_state_t *state = s_FlashStatePtr[instance];
    DEV_ASSERT(state != NULL);
    status_t status = STATUS_SUCCESS;

    if (false == FLASH_GetIdleStatus(base) || state->driverBusy)
    {
        status = STATUS_EFM_BUSY;
    }
    else
    {
        state->async = async;
        if (true == async)
        {
            state->driverBusy = false;
            FLASH_DRV_EnableCmdCompleteInterrupt(instance);
            INT_SYS_EnableIRQ(s_efmIrqId[instance]);
            FLASH_DRV_EnableReadCollisionInterrupt(instance);
#ifdef EFM_READ_COLLISION_IRQS
            INT_SYS_EnableIRQ(s_efmReadCollisionIrqId[instance]);
#endif /* EFM_READ_COLLISION_IRQS */
        }
    }
    return status;
}

/*FUNCTION**********************************************************************
*
* Function Name : FLASH_DRV_SetDisableGlobalInt
* Description   : Enable or disable global interrupt in sync mode.
*
* Implements    : FLASH_DRV_SetDisableGlobalInt_Activity
*END**************************************************************************/
void FLASH_DRV_SetDisableGlobalInt(uint32_t instance, bool disGlobalInt)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    flash_state_t *state = s_FlashStatePtr[instance];
    DEV_ASSERT(state != NULL);

    state->disGlobalInt = disGlobalInt;
}

/*FUNCTION**********************************************************************
*
* Function Name : FLASH_DRV_SetReadVerify
* Description   : Enable or disable read verify during program/erase operation.
*
* Implements    : FLASH_DRV_SetReadVerify_Activity
*END**************************************************************************/
void FLASH_DRV_SetReadVerify(uint32_t instance, bool readVerify)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    flash_state_t *state = s_FlashStatePtr[instance];
    DEV_ASSERT(state != NULL);

    state->readVerify = readVerify;

#ifdef EFM_CTRL_CMD_VERIFY_EN_MASK
    EFM_Type *base = s_efmBase[instance];
    if (true == readVerify)
    {
        base->CTRL |= EFM_CTRL_CMD_VERIFY_EN_MASK;
    }
    else
    {
        base->CTRL &= ~EFM_CTRL_CMD_VERIFY_EN_MASK;
    }
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_EraseBlock
 * Description   : Erases a block of Flash memory.
 * This API always returns STATUS_SUCCESS if size provided by the user is
 * zero regardless of the input validation.
 *
 * Implements    : FLASH_DRV_EraseBlock_Activity
 *END**************************************************************************/
status_t FLASH_DRV_EraseBlock(uint32_t instance, uint32_t dest)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];
    flash_state_t *state = s_FlashStatePtr[instance];
    DEV_ASSERT(state != NULL);
    status_t status; /* Return code variable */
    uint32_t tmp = 0x12345678U;
    DEV_ASSERT((dest & (FEATURE_EFM_FLASH_MIN_SECTOR_SIZE - 1)) == 0U);

#if FEATURE_EFM_HAS_ERASE_TIMING_UNION
    base->TIMING2 = FEATURE_EFM_BLOCK_ERASE_TIMING;
#endif
    state->cmdParam.cmdCode = FEATURE_EFM_ERASE_BLOCK_CMD_CODE;
#if FEATURE_EFM_ERASE_BLOCK_VERIFY_CMD_CODE
    if (true == state->readVerify)
    {
        state->cmdParam.cmdCode = FEATURE_EFM_ERASE_BLOCK_VERIFY_CMD_CODE;
    }
#endif
    state->cmdParam.dest = (uint32_t *)dest;
    state->cmdParam.pdata = &(tmp);
    state->cmdParam.word_size = 1U;

    if (state->async)
    {
        if (false == FLASH_GetIdleStatus(base) || state->driverBusy)
        {
            status = STATUS_EFM_BUSY;
        }
        else
        {
            state->driverBusy = true;
            state->leftSize = 0U;
            status = FLASH_LaunchCommandSequence(instance);
        }
    }
    else
    {
        /* Check IDLE to verify the previous command is completed */
        if (false == FLASH_GetIdleStatus(base))
        {
            status = STATUS_EFM_BUSY;
        }
        else
        {
            /* Calling flash command sequence function to execute the command */
            status = FLASH_LaunchCommandSequence(instance);
        }
    }
    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_EraseSector
 * Description   : Erases one or more sectors in P-Flash or D-Flash memory.
 * This API always returns STATUS_SUCCESS if size provided by the user is
 * zero regardless of the input validation.
 *
 * Implements    : FLASH_DRV_EraseSector_Activity
 *END**************************************************************************/
status_t FLASH_DRV_EraseSector(uint32_t instance, uint32_t dest, uint32_t size)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];
    flash_state_t *state = s_FlashStatePtr[instance];
    DEV_ASSERT(state != NULL);
    status_t status = STATUS_SUCCESS; /* Return code variable */
    uint32_t sectorSize;              /* Size of one sector   */
    uint32_t tmp = 0x12345678U;
    sectorSize = FLASH_GetSectorSize(dest);
    DEV_ASSERT((dest & (sectorSize - 1)) == 0U);
    DEV_ASSERT((size & (sectorSize - 1)) == 0U);
    DEV_ASSERT(size >= sectorSize);

#if FEATURE_EFM_HAS_ERASE_TIMING_UNION
    base->TIMING2 = FEATURE_EFM_SECTOR_ERASE_TIMING;
#endif

    state->cmdParam.cmdCode = FEATURE_EFM_ERASE_SECTOR_CMD_CODE;
#if FEATURE_EFM_ERASE_SECTOR_VERIFY_CMD_CODE
    if (true == state->readVerify)
    {
        state->cmdParam.cmdCode = FEATURE_EFM_ERASE_SECTOR_VERIFY_CMD_CODE;
    }
#endif
    state->cmdParam.dest = (uint32_t *)dest;
    state->cmdParam.pdata = &tmp;
    state->cmdParam.word_size = 1U;

    if (state->async)
    {
        if (false == FLASH_GetIdleStatus(base) || state->driverBusy)
        {
            status = STATUS_EFM_BUSY;
        }
        else
        {
            state->driverBusy = true;
            state->leftSize = size;
            status = FLASH_LaunchCommandSequence(instance);
        }
    }
    else
    {
        while ((size > 0U) && (STATUS_SUCCESS == status) && (sectorSize > 0U))
        {
            /* Check IDLE to verify the previous command is completed */
            if (false == FLASH_GetIdleStatus(base))
            {
                status = STATUS_EFM_BUSY;
            }
            else
            {
                /* Calling flash command sequence function to execute the command */
                status = FLASH_LaunchCommandSequence(instance);
            }
            size -= sectorSize;
            state->cmdParam.dest += sectorSize>>2;
            sectorSize = FLASH_GetSectorSize((uint32_t)state->cmdParam.dest);
        }
    }

    return status;
}

#ifdef FEATURE_EFM_ERASE_SECTOR_RETRY_CMD_CODE
/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_EraseSectorQuick
 * Description   : Erases one or more sectors in P-Flash or D-Flash memory.
 * This API always returns STATUS_SUCCESS if size provided by the user is
 * zero regardless of the input validation.
 * This API is used for the case that the flash need to be erased quickly.
 *
 * Implements    : FLASH_DRV_EraseSector_Activity
 *END**************************************************************************/
status_t FLASH_DRV_EraseSectorQuick(uint32_t instance, uint32_t dest, uint32_t size)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];
    flash_state_t *state = s_FlashStatePtr[instance];
    DEV_ASSERT(state != NULL);
    status_t status = STATUS_SUCCESS; /* Return code variable */
    uint32_t sectorSize;              /* Size of one sector   */
    uint32_t tmp = 0x12345678U;
    uint32_t i = 0;
    sectorSize = FLASH_GetSectorSize(dest);
    DEV_ASSERT((dest & (sectorSize - 1)) == 0U);
    DEV_ASSERT((size & (sectorSize - 1)) == 0U);
    DEV_ASSERT(size >= sectorSize);

#if FEATURE_EFM_HAS_ERASE_TIMING_UNION
    base->TIMING2 = FEATURE_EFM_SECTOR_ERASE_RETRY_TIMING;
#endif

#ifdef EFM_CTRL_CMD_VERIFY_EN_MASK
#ifdef FEATURE_EFM_ERASE_SECTOR_VREAD_RETRY_CMD_CODE
    base->CTRL &= ~EFM_CTRL_CMD_VERIFY_EN_MASK;
#else
    base->CTRL |= EFM_CTRL_CMD_VERIFY_EN_MASK;
#endif
#endif
    state->cmdParam.cmdCode = FEATURE_EFM_ERASE_SECTOR_RETRY_CMD_CODE;
    state->cmdParam.dest = (uint32_t *)dest;
    state->cmdParam.pdata = &tmp;
    state->cmdParam.word_size = 1U;

    if (state->async)
    {
        if (false == FLASH_GetIdleStatus(base) || state->driverBusy)
        {
            status = STATUS_EFM_BUSY;
        }
        else
        {
            state->driverBusy = true;
            state->leftSize = size;
            state->retryCount = 0U;
#ifdef EFM_CTRL_RETRY_CFG_MASK
            base->CTRL &= ~EFM_CTRL_RETRY_CFG_MASK;
            base->CTRL |= EFM_CTRL_RETRY_CFG(FLASH_RETRY_CFG_START);
#endif /* EFM_CTRL_RETRY_CFG_MASK */
            status = FLASH_LaunchCommandSequence(instance);
        }
    }
    else
    {
        while ((size > 0U) && (STATUS_SUCCESS == status) && (sectorSize > 0U))
        {
            /* Check IDLE to verify the previous command is completed */
            if (false == FLASH_GetIdleStatus(base))
            {
                status = STATUS_EFM_BUSY;
            }
            else
            {
                for (i = 0; i < FLASH_RETRY_MAX_COUNT; i++)
                {
#if defined(EFM_CTRL_RETRY_CFG_MASK)
                    if (FLASH_RETRY_CFG_START + i <= 0x7U)
                    {
                        base->CTRL &= ~EFM_CTRL_RETRY_CFG_MASK;
                        base->CTRL |= EFM_CTRL_RETRY_CFG(FLASH_RETRY_CFG_START + i);
                    }
#endif /* EFM_CTRL_RETRY_CFG_MASK */
                    state->cmdParam.cmdCode = FEATURE_EFM_ERASE_SECTOR_RETRY_CMD_CODE;
                    status = FLASH_LaunchCommandSequence(instance);
                    if (STATUS_SUCCESS == status)
                    {
#ifdef FEATURE_EFM_ERASE_SECTOR_VREAD_RETRY_CMD_CODE
                        state->cmdParam.cmdCode = FEATURE_EFM_ERASE_SECTOR_VREAD_RETRY_CMD_CODE;
                        status = FLASH_LaunchCommandSequence(instance);
                        if (STATUS_SUCCESS != status)
                        {
                            continue;
                        }
#endif /* FEATURE_EFM_ERASE_SECTOR_VREAD_RETRY_CMD_CODE */
                        break;
                    }
                }
                if (i >= FLASH_RETRY_MAX_COUNT)
                {
                    status = STATUS_ERROR;
                    break;
                }

                /* Append 0x7 RETRY_CFG retry after finish to ensure erase thoroughly */
                {
#if defined(EFM_CTRL_RETRY_CFG_MASK)
                    base->CTRL &= ~EFM_CTRL_RETRY_CFG_MASK;
                    base->CTRL |= EFM_CTRL_RETRY_CFG(0x7);
#endif /* EFM_CTRL_RETRY_CFG_MASK */
                    state->cmdParam.cmdCode = FEATURE_EFM_ERASE_SECTOR_RETRY_CMD_CODE;
                    status = FLASH_LaunchCommandSequence(instance);
                    if (STATUS_SUCCESS == status)
                    {
#ifdef FEATURE_EFM_ERASE_SECTOR_VREAD_RETRY_CMD_CODE
                        state->cmdParam.cmdCode = FEATURE_EFM_ERASE_SECTOR_VREAD_RETRY_CMD_CODE;
                        status = FLASH_LaunchCommandSequence(instance);
                        if (STATUS_SUCCESS != status)
                        {
                            break;
                        }
#endif /* FEATURE_EFM_ERASE_SECTOR_VREAD_RETRY_CMD_CODE */
                    }
                    else
                    {
                        break;
                    }
                }

#ifdef EFM_CTRL_CMD_VERIFY_EN_MASK
                if (true == state->readVerify)
                {
                    base->CTRL |= EFM_CTRL_CMD_VERIFY_EN_MASK;
                }
                else
                {
                    base->CTRL &= ~EFM_CTRL_CMD_VERIFY_EN_MASK;
                }
#endif
            }

            size -= sectorSize;
            state->cmdParam.dest += sectorSize >> 2;
            sectorSize = FLASH_GetSectorSize((uint32_t)state->cmdParam.dest);
        }
    }

    return status;
}
#endif /* FEATURE_EFM_ERASE_SECTOR_RETRY_CMD_CODE */

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_Program
 * Description   : Program command on flash
 * This API always returns STATUS_SUCCESS if size provided by user is
 * zero regardless of the input validation.
 *
 * Implements    : FLASH_DRV_Program_Activity
 *END**************************************************************************/
status_t FLASH_DRV_Program(uint32_t instance, uint32_t dest, uint32_t size, const void * pData)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];
    flash_state_t *state = s_FlashStatePtr[instance];
    DEV_ASSERT(state != NULL);
    status_t status = STATUS_SUCCESS;    /* Return code variable */

    DEV_ASSERT((dest & (FEATURE_EFM_WRITE_UNIT_SIZE - 1)) == 0U);
    DEV_ASSERT((size & (FEATURE_EFM_WRITE_UNIT_SIZE - 1)) == 0U);
    DEV_ASSERT(size >= FEATURE_EFM_WRITE_UNIT_SIZE);
    DEV_ASSERT(((uint32_t)pData & 0x03U) == 0U);

    state->cmdParam.cmdCode = FEATURE_EFM_PROGRAM_CMD_CODE;
#if FEATURE_EFM_PROGRAM_VERIFY_CMD_CODE
    if (true == state->readVerify)
    {
        state->cmdParam.cmdCode = FEATURE_EFM_PROGRAM_VERIFY_CMD_CODE;
    }
#endif
    state->cmdParam.dest = (uint32_t *) dest;
    state->cmdParam.pdata = (uint32_t *) pData;
    state->cmdParam.word_size = FEATURE_EFM_WRITE_UNIT_WORD_SIZE;

    if (state->async)
    {
        if (false == FLASH_GetIdleStatus(base) || state->driverBusy)
        {
            status = STATUS_EFM_BUSY;
        }
        else
        {
            state->driverBusy = true;
            state->leftSize = size;
            status = FLASH_LaunchCommandSequence(instance);
        }
    }
    else
    {
        while ((size > 0U) && (STATUS_SUCCESS == status))
        {
            /* Check IDLE to verify the previous command is completed */
            if (false == FLASH_GetIdleStatus(base))
            {
                status = STATUS_EFM_BUSY;
            }
            else
            {
                /* Calling flash command sequence function to execute the command */
                status = FLASH_LaunchCommandSequence(instance);

                /* Update destination address for next iteration */
                state->cmdParam.dest += FEATURE_EFM_WRITE_UNIT_WORD_SIZE;
                /* Update size for next iteration */
                size -= FEATURE_EFM_WRITE_UNIT_SIZE;
                /* Increment the source address by unit word size */
                state->cmdParam.pdata += FEATURE_EFM_WRITE_UNIT_WORD_SIZE;
            }
        }
    }

    return status;
}

#ifdef FEATURE_EFM_PROGRAM_DATA_CMD_CODE
/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_ProgramDFlash
 * Description   : Program command on DFlash
 * This API always returns STATUS_SUCCESS if size provided by user is
 * zero regardless of the input validation.
 *
 * Implements    : FLASH_DRV_Program_Activity
 *END**************************************************************************/
status_t FLASH_DRV_ProgramDFlash(uint32_t instance, uint32_t dest, uint32_t size, const void * pData)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];
    flash_state_t *state = s_FlashStatePtr[instance];
    DEV_ASSERT(state != NULL);
    status_t status = STATUS_SUCCESS;    /* Return code variable */

    DEV_ASSERT((dest & (FEATURE_EFM_WRITE_DATA_UNIT_SIZE - 1)) == 0U);
    DEV_ASSERT(((uint32_t)pData & 0x03U) == 0U);
    DEV_ASSERT((size & (FEATURE_EFM_WRITE_DATA_UNIT_SIZE - 1)) == 0U);
    DEV_ASSERT(size >= FEATURE_EFM_WRITE_DATA_UNIT_SIZE);

    state->cmdParam.cmdCode = FEATURE_EFM_PROGRAM_DATA_CMD_CODE;
    state->cmdParam.dest = (uint32_t *) dest;
    state->cmdParam.pdata = (uint32_t *) pData;
    state->cmdParam.word_size = FEATURE_EFM_WRITE_DATA_UNIT_WORD_SIZE;

    if (state->async)
    {
        if (false == FLASH_GetIdleStatus(base) || state->driverBusy)
        {
            status = STATUS_EFM_BUSY;
        }
        else
        {
            state->driverBusy = true;
            state->leftSize = size;
            status = FLASH_LaunchCommandSequence(instance);
        }
    }
    else
    {
        while ((size > 0U) && (STATUS_SUCCESS == status))
        {
            /* Check IDLE to verify the previous command is completed */
            if (false == FLASH_GetIdleStatus(base))
            {
                status = STATUS_EFM_BUSY;
            }
            else
            {
                /* Calling flash command sequence function to execute the command */
                status = FLASH_LaunchCommandSequence(instance);

                /* Update destination address for next iteration */
                state->cmdParam.dest += FEATURE_EFM_WRITE_DATA_UNIT_WORD_SIZE;
                /* Update size for next iteration */
                size -= FEATURE_EFM_WRITE_DATA_UNIT_SIZE;
                /* Increment the source address by unit word size */
                state->cmdParam.pdata += FEATURE_EFM_WRITE_DATA_UNIT_WORD_SIZE;
            }
        }
    }

    return status;
}
#endif /* FEATURE_EFM_WRITE_DATA_UNIT_SIZE */


/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_CheckSum
 * Description   : Performs 32 bit sum of each byte data over a specified Flash
 * memory range without carry which provides rapid method for checking data integrity.
 * The callback time period of this API is determined via FLASH_CALLBACK_CS macro in the
 * flash_driver.h which is used as a counter value for the CallBack() function calling in
 * this API. This value can be changed as per the user requirement. User can change this value
 * to obtain the maximum permissible callback time period.
 * This API always returns STATUS_SUCCESS if size provided by user is zero regardless of the input
 * validation.
 *
 * Implements    : FLASH_DRV_CheckSum_Activity
 *END**************************************************************************/
status_t FLASH_DRV_CheckSum(uint32_t instance, uint32_t dest, uint32_t size, uint32_t * pSum)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];
    flash_state_t *state = s_FlashStatePtr[instance];
    DEV_ASSERT(state != NULL);
    DEV_ASSERT(pSum != NULL);
    status_t status = STATUS_SUCCESS;      /* Return code variable           */
    uint32_t counter = 0U;              /* Counter for callback operation */
    uint32_t data;                      /* Data read from Flash address   */
    uint32_t tempSize = size;           /* Temporary of size variation    */

    *pSum = 0U;
    /* Doing sum operation */
    while (tempSize > 0U)
    {
        data = *(uint8_t *)(dest);
        *pSum += data;
        dest += 1U;
        tempSize -= 1U;
        ++counter;

        /* Check if flash need to serve callback function */
        if (counter >= FLASH_CALLBACK_CS)
        {
            /* Serve callback function if counter reaches limitation */
            FLASH_EventCallback(base, state, FLASH_EVENT_CHECKSUM);

            /* Reset counter */
            counter = 0U;
        }
    }

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_EnableCmdCompleteInterrupt
 * Description   : Enable the command complete interrupt is generated when
 * an EFM command completes.
 *
 * Implements    : FLASH_DRV_EnableCmdCompleteInterrupt_Activity
 *END**************************************************************************/
void FLASH_DRV_EnableCmdCompleteInterrupt(uint32_t instance)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];

    /* Enable the command complete interrupt */
    base->CTRL |= EFM_CTRL_DONEIE_MASK;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_DisableCmdCompleteInterrupt
 * Description   : Disable the command complete interrupt.
 *
 * Implements    : FLASH_DRV_DisableCmdCompleteInterrupt_Activity
 *END**************************************************************************/
void FLASH_DRV_DisableCmdCompleteInterrupt(uint32_t instance)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];

    /* Disable the command complete interrupt */
    base->CTRL &= ~EFM_CTRL_DONEIE_MASK;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_EnableReadCollisionInterrupt
 * Description   : Enable the read collision error interrupt generation when an
 * EFM read collision error occurs.
 *
 * Implements    : FLASH_DRV_EnableReadCollisionInterrupt_Activity
 *END**************************************************************************/
void FLASH_DRV_EnableReadCollisionInterrupt(uint32_t instance)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];

    /* Enable the read collision error interrupt */
    base->CTRL |= EFM_CTRL_ACCERRIE_MASK;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_DisableReadCollisionInterrupt
 * Description   : Disable the read collision error interrupt
 *
 * Implements    : FLASH_DRV_DisableReadCollisionInterrupt_Activity
 *END**************************************************************************/
void FLASH_DRV_DisableReadCollisionInterrupt(uint32_t instance)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];

    /* Disable the read collision error interrupt */
    base->CTRL &= ~EFM_CTRL_ACCERRIE_MASK;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_EnableSingleBitFaultInterrupt
 * Description   : Enable the platform Flash single bit fault detect interrupt 
 * generation when an recovery ECC fault is detected during a valid flash 
 * read access from the platform flash controller.
 *
 * Implements    : FLASH_DRV_EnableSingleBitFaultInterrupt
 *END**************************************************************************/
void FLASH_DRV_EnableSingleBitFaultInterrupt(uint32_t instance)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];

    /* Enable the single bit fault detect interrupt */
    base->CTRL |= EFM_CTRL_RECOVERRIE_MASK;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_DisableSingleBitFaultInterrupt
 * Description   : Disable the platform Flash single bit fault detect interrupt
 *
 * Implements    : FLASH_DRV_DisableSingleBitFaultInterrupt
 *END**************************************************************************/
void FLASH_DRV_DisableSingleBitFaultInterrupt(uint32_t instance)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];

    /* Disable the single bit fault detect interrupt */
    base->CTRL &= ~EFM_CTRL_RECOVERRIE_MASK;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_EnableDoubleBitFaultInterrupt
 * Description   : Enable the platform Flash double bit fault detect interrupt 
 * generation when an uncorrectable ECC fault is detected during a valid flash 
 * read access from the platform flash controller.
 *
 * Implements    : FLASH_DRV_EnableDoubleBitFaultInterrupt_Activity
 *END**************************************************************************/
void FLASH_DRV_EnableDoubleBitFaultInterrupt(uint32_t instance)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];

    /* Enable the double bit fault detect interrupt */
    base->CTRL |= EFM_CTRL_UNRECOVERRIE_MASK;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_DisableDoubleBitFaultInterrupt
 * Description   : Disable the platform Flash double bit fault detect interrupt
 *
 * Implements    : FLASH_DRV_DisableDoubleBitFaultInterrupt_Activity
 *END**************************************************************************/
void FLASH_DRV_DisableDoubleBitFaultInterrupt(uint32_t instance)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];
    
    /* Disable the double bit fault detect interrupt */
    base->CTRL &= ~EFM_CTRL_UNRECOVERRIE_MASK;
}

#ifdef FEATURE_EFM_ERASE_NVR_CMD_CODE
/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_EraseNVR
 * Description   : Erase NVR one sector on flash
 * This API always returns STATUS_SUCCESS even if the address passed 
 * in is incorrect.
 *
 * Implements    : FLASH_DRV_EraseNVR_Activity
 *END**************************************************************************/
status_t FLASH_DRV_EraseNVR(uint32_t instance, uint32_t dest)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];
    flash_state_t *state = s_FlashStatePtr[instance];
    DEV_ASSERT(state != NULL);
    status_t status;    /* Return code variable */

    state->cmdParam.cmdCode = FEATURE_EFM_ERASE_NVR_CMD_CODE;
    state->cmdParam.dest = (uint32_t *)&base->NVR_ADDR;
    state->cmdParam.pdata = &dest;
    state->cmdParam.word_size = 1U;

    if (state->async)
    {
        if (false == FLASH_GetIdleStatus(base) || state->driverBusy)
        {
            status = STATUS_EFM_BUSY;
        }
        else
        {
            state->driverBusy = true;
            state->leftSize = 0;
            status = FLASH_LaunchCommandSequence(instance);
        }
    }
    else
    {
        if (false == FLASH_GetIdleStatus(base))
        {
            status = STATUS_EFM_BUSY;
        }
        else
        {
            status = FLASH_LaunchCommandSequence(instance);
        }
    }

    return status;
}
#endif /* FEATURE_EFM_ERASE_NVR_CMD_CODE */

#ifdef FEATURE_EFM_PROGRAM_NVR_CMD_CODE
/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_Program_NVR
 * Description   : Program NVR command on flash
 * This API always returns STATUS_SUCCESS if size provided by user is
 * zero regardless of the input validation.
 *
 * Implements    : FLASH_DRV_ProgramNVR_Activity
 *END**************************************************************************/
status_t FLASH_DRV_ProgramNVR(uint32_t instance, uint32_t dest, uint32_t size, const void *pData)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];
    flash_state_t *state = s_FlashStatePtr[instance];
    DEV_ASSERT(state != NULL);
    status_t status = STATUS_SUCCESS; /* Return code variable */

    DEV_ASSERT((dest & (FEATURE_EFM_WRITE_UNIT_SIZE - 1)) == 0U);
    DEV_ASSERT((size & (FEATURE_EFM_WRITE_UNIT_SIZE - 1)) == 0U);
    DEV_ASSERT(size > FEATURE_EFM_WRITE_UNIT_SIZE);
    DEV_ASSERT(((uint32_t)pData & 0x03U) == 0U);

    uint32_t efm_data[FEATURE_EFM_WRITE_UNIT_WORD_SIZE + 1];
    uint32_t * nvr_data = (uint32_t *)pData;

    state->cmdParam.cmdCode = FEATURE_EFM_PROGRAM_NVR_CMD_CODE;
    state->cmdParam.dest = (uint32_t *)&base->NVR_ADDR;
    state->cmdParam.pdata = (uint32_t *)efm_data;
    state->cmdParam.word_size = FEATURE_EFM_WRITE_UNIT_WORD_SIZE + 1;

    if (state->async)
    {
        if (false == FLASH_GetIdleStatus(base) || state->driverBusy)
        {
            status = STATUS_EFM_BUSY;
        }
        else
        {
            state->driverBusy = true;
            state->leftSize = size;
            state->nvr_addr = dest;
            state->nvr_data = nvr_data;
            efm_data[0] = state->nvr_addr;
            for (uint32_t i = 0U; i < FEATURE_EFM_WRITE_UNIT_WORD_SIZE; i++)
            {
                efm_data[i + 1U] = state->nvr_data[i];
            }
            status = FLASH_LaunchCommandSequence(instance);
        }
    }
    else
    {
        while ((size > 0U) && (STATUS_SUCCESS == status))
        {
            /* Check IDLE to verify the previous command is completed */
            if (false == FLASH_GetIdleStatus(base))
            {
                status = STATUS_EFM_BUSY;
            }
            else
            {
                efm_data[0] = dest;
                for (uint8_t i = 0U; i < FEATURE_EFM_WRITE_UNIT_WORD_SIZE; i++)
                {
                    efm_data[i + 1U] = nvr_data[i];
                }
                /* Calling flash command sequence function to execute the command */
                status = FLASH_LaunchCommandSequence(instance);

                /* Update size for next iteration */
                size -= FEATURE_EFM_WRITE_UNIT_SIZE;
                /* Update address for next iteration */
                dest += FEATURE_EFM_WRITE_UNIT_SIZE;
                /* Increment the source address by unit word size */
                nvr_data += FEATURE_EFM_WRITE_UNIT_WORD_SIZE;
            }
        }
    }
    return status;
}
#endif /* FEATURE_EFM_PROGRAM_NVR_CMD_CODE */

#ifdef FEATURE_EFM_READ_NVR_CMD_CODE
/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_ReadNVR
 * Description   : Read NVR command on flash
 * This API always returns STATUS_SUCCESS if size provided by user is
 * zero regardless of the input validation.
 *
 * Implements    : FLASH_DRV_ReadNVR_Activity
 *END**************************************************************************/
status_t FLASH_DRV_ReadNVR(uint32_t instance, uint32_t address, uint32_t size, void * dest)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];
    flash_state_t *state = s_FlashStatePtr[instance];
    DEV_ASSERT(state != NULL);
    status_t status = STATUS_SUCCESS;    /* Return code variable */

    DEV_ASSERT((address & (FEATURE_EFM_WRITE_UNIT_SIZE - 1)) == 0U);
    DEV_ASSERT((size & (FEATURE_EFM_WRITE_UNIT_SIZE - 1)) == 0U);
    DEV_ASSERT(size >= FEATURE_EFM_WRITE_UNIT_SIZE);

    uint32_t *pData = (uint32_t *)dest;
    bool pre_state = state->async;

    state->cmdParam.cmdCode = FEATURE_EFM_READ_NVR_CMD_CODE;
    state->cmdParam.dest = (uint32_t *) &base->NVR_ADDR ;
    state->cmdParam.pdata = &address;
    state->cmdParam.word_size = 1U;

    /* Read the NVR synchronously, due to very short time */
    state->async = false;
    base->CTRL &= ~EFM_CTRL_DONEIE_MASK;
    while ((size > 0U) && (STATUS_SUCCESS == status))
    {
        /* Check IDLE to verify the previous command is completed */
        if (false == FLASH_GetIdleStatus(base))
        {
            status = STATUS_EFM_BUSY;
        }
        else
        {
            /* Calling flash command sequence function to execute the command */
            status = FLASH_LaunchCommandSequence(instance);
            if (STATUS_SUCCESS != status){
                break;
            }
            /* Passing parameter to the command */
            for (uint32_t i = 0U; i < FEATURE_EFM_WRITE_UNIT_WORD_SIZE; i++)
            {
                pData[i] = base->NVR_DATA[i];
            }

            /* Update size for next iteration */
            size -= FEATURE_EFM_WRITE_UNIT_SIZE;
            /* Update address for next iteration */
            address += FEATURE_EFM_WRITE_UNIT_SIZE;
            /* Increment the source address by unit word size */
            pData += FEATURE_EFM_WRITE_UNIT_WORD_SIZE;
        }
    }
    state->async = pre_state;
    if (state->async == true)
    {
        base->CTRL |= EFM_CTRL_DONEIE_MASK;
    }
    return status;
}
#endif /* FEATURE_EFM_READ_NVR_CMD_CODE */

#ifdef FEATURE_EFM_BOOT_SWAP_CMD_CODE
/*!
 * @brief Internal flash command to execute bootswap.
 *        It is called by FLASH_DRV_BootSwap.
 *
 * @param[in] instance Target flash instance.
 */
status_t FLASH_BootSwap(uint32_t instance)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];
    flash_state_t *state = s_FlashStatePtr[instance];
    DEV_ASSERT(state != NULL);
    status_t status;    /* Return code variable */
    uint32_t tmp = 0x5a5a5a5aU;
    bool pre_state = state->async;

    /* Check IDLE to verify the previous command is completed */
    if (false == FLASH_GetIdleStatus(base))
    {
        status = STATUS_EFM_BUSY;
    }
    else
    {
        /* Boot swap synchronously */
        state->async = false;
        base->CTRL &= ~EFM_CTRL_DONEIE_MASK;
        state->cmdParam.cmdCode = FEATURE_EFM_BOOT_SWAP_CMD_CODE;
        state->cmdParam.pdata = &tmp;
        state->cmdParam.word_size = 0U;
#if defined(FEATURE_EFM_BOOT_SWAP_TAG_ADDR)
        state->cmdParam.dest = (uint32_t *)FEATURE_EFM_BOOT_SWAP_TAG_ADDR;
        state->cmdParam.word_size = 1U;
#endif
        /* Calling flash command sequence function to execute the command */
        status = FLASH_LaunchCommandSequence(instance);
        state->async = pre_state;
        if (state->async == true)
        {
            base->CTRL |= EFM_CTRL_DONEIE_MASK;
        }
    }
    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_BootSwap
 * Description   : Swap MCU boot flash blocks
 *
 * Implements    : FLASH_DRV_BootSwap_Activity
 *END**************************************************************************/
status_t FLASH_DRV_BootSwap(uint32_t instance)
{
    status_t status = STATUS_SUCCESS;    /* Return code variable */
    INT_SYS_DisableIRQGlobal();
    status = FLASH_BootSwap(instance);
    if (STATUS_SUCCESS != status)
    {
        /* Erase Boot NVR and try again */
#ifdef EFM_BOOT_SWAP_UNLOCK
        EFM_BOOT_SWAP_UNLOCK();
#endif /* EFM_BOOT_SWAP_UNLOCK */

#ifdef FEATURE_EFM_ERASE_NVR_CMD_CODE
        status = FLASH_DRV_EraseNVR(instance, FEATURE_EFM_BOOT_NVR_ADDR);
#else
        status = FLASH_DRV_EraseSector(instance, FEATURE_EFM_BOOT_SWAP_TAG_ADDR, FEATURE_EFM_NVR_ARRAY_SECTOR_SIZE);
#endif /* FEATURE_EFM_ERASE_NVR_CMD_CODE */

#ifdef EFM_BOOT_SWAP_LOCK
        EFM_BOOT_SWAP_LOCK();
#endif /* EFM_BOOT_SWAP_LOCK */

        if (STATUS_SUCCESS == status)
        {
            status = FLASH_BootSwap(instance);
        }   
    }
    INT_SYS_EnableIRQGlobal();
    return status;
}
#endif

#ifdef FEATURE_EFM_LOAD_AES_KEY_CMD_CODE
/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_LoadAESKey
 * Description   : Load AES key for HCU
 *
 * Implements    : FLASH_DRV_LoadAESKey_Activity
 *END**************************************************************************/
status_t FLASH_DRV_LoadAESKey(uint32_t instance, uint32_t address)
{
    DEV_ASSERT(instance < EFM_INSTANCE_COUNT);
    EFM_Type *base = s_efmBase[instance];
    flash_state_t *state = s_FlashStatePtr[instance];
    DEV_ASSERT(state != NULL);
    bool pre_state = state->async;
    status_t status;    /* Return code variable */

    /* Check address if align to FEATURE_EFM_AES_KEY_SIZE bytes */
    if (0U != (address % FEATURE_EFM_AES_KEY_SIZE))
    {
        return STATUS_ERROR;
    }
    /* Check IDLE to verify the previous command is completed */
    if (false == FLASH_GetIdleStatus(base))
    {
        status = STATUS_EFM_BUSY;
    }
    else
    {
        state->cmdParam.cmdCode = FEATURE_EFM_LOAD_AES_KEY_CMD_CODE;
#if defined(CPU_YTM32B1ME0)
        base->CTRL &= ~EFM_CTRL_AES_KEY_SEL_MASK;
        base->CTRL |= EFM_CTRL_AES_KEY_SEL(((uint32_t)(address) - 0x10000000U) / 0x20U);
        state->cmdParam.word_size = 0U;
#elif defined(CPU_YTM32B1MD1) || defined(CPU_YTM32B1MD2)
        state->cmdParam.dest = (uint32_t *)&base->NVR_ADDR;
        state->cmdParam.pdata = &address;
        state->cmdParam.word_size = 1U;
#else
        uint32_t tmp = 0x12345678U;
        state->cmdParam.dest = (uint32_t *)address;
        state->cmdParam.pdata = &tmp;
        state->cmdParam.word_size = 1U;
#endif
        /* Load AES key synchronously, due to very short time */
        state->async = false;
        base->CTRL &= ~EFM_CTRL_DONEIE_MASK;
        /* Calling flash command sequence function to execute the command */
        status = FLASH_LaunchCommandSequence(instance);
        state->async = pre_state;
        if (state->async == true)
        {
            base->CTRL |= EFM_CTRL_DONEIE_MASK;
        }
    }
    return status;
}
#endif /* FEATURE_EFM_LOAD_AES_KEY_CMD_CODE */


/*******************************************************************************
* EOF
*******************************************************************************/
