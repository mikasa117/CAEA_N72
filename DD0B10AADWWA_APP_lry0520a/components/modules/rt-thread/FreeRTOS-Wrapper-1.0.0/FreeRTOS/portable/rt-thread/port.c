#include <FreeRTOS.h>

static rt_base_t level = 0;
static rt_base_t critical_nesting = 0;

void vPortEnterCritical( void )
{
    if ( critical_nesting == 0 )
    {
        level = rt_hw_interrupt_disable();
    }
    critical_nesting += 1;
}

void vPortExitCritical( void )
{
    critical_nesting -= 1;
    if ( critical_nesting == 0 )
    {
        rt_hw_interrupt_enable( level );
    }
}

void vPortEndScheduler( void )
{
    /* Not implemented in ports where there is nothing to return to. */
}

BaseType_t rt_err_to_freertos(rt_err_t rt_err)
{
    switch(-rt_err)
    {
        case RT_EOK:
            return pdPASS;
        case RT_ENOMEM:
            return errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY;
        case RT_EFULL:
            return errQUEUE_FULL;
        case RT_EEMPTY:
            return errQUEUE_EMPTY;
        default:
            return pdFAIL;
    }
}

BaseType_t xPortIsInsideInterrupt( void )
{
    uint32_t ulCurrentInterrupt;
    BaseType_t xReturn;

    /* Obtain the number of the currently executing interrupt. Interrupt Program
     * Status Register (IPSR) holds the exception number of the currently-executing
     * exception or zero for Thread mode.*/
    __asm volatile ( "mrs %0, ipsr" : "=r" ( ulCurrentInterrupt )::"memory" );

    if( ulCurrentInterrupt == 0 )
    {
        xReturn = pdFALSE;
    }
    else
    {
        xReturn = pdTRUE;
    }

    return xReturn;
}
