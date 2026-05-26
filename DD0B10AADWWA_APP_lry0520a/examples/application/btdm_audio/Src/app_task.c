#include "FreeRTOS.h"
#include "task.h"

#include "app_at.h"
#include "app_task.h"
#include "app_bt.h"
#include "app_ble.h"
#include "app_audio.h"
#include "app_rpmsg.h"
#include "app_config.h"
#include "hci_test.h"

static struct co_list event_list;

extern TaskHandle_t app_task_handle;

void hci_controller_read(void);
void hci_host_read(void);

static void app_task_event_handler(void)
{
    struct app_task_event *event = NULL;

    taskENTER_CRITICAL();
    event = (struct app_task_event *)co_list_pop_front(&event_list);
    taskEXIT_CRITICAL();

    if (event)
    {
        switch (event->event_type)
        {
        case APP_TASK_EVENT_AT_CMD:
            app_at_cmd_recv_handler(event->param, event->param_len);
            break;
        case APP_TASK_EVENT_RPMSG_INITED:
            app_btdm_init();
            break;
        case APP_TASK_EVENT_HOST_INITED:
            app_btdm_start();
            break;
        case APP_TASK_EVENT_AUDIO:
            app_audio_event_handler(event);
            break;
        case APP_TASK_EVENT_PY_TRANS:
            // py_uart_receive((event->param));
            break;
        case APP_TASK_EVENT_HCI_CMD:
            //                uart_transmit(&Uart3_handle,event->param,event->param_len);
            uart_transmit(&HCI_handle, event->param, event->param_len);
            break;
        case APP_TASK_EVENT_HCI_AT_CMD:
            //                uart_transmit(&Uart3_handle,event->param,event->param_len);
            // user_at_func(event->param,event->param_len);
            break;
        case APP_TASK_EVENT_HOST_HCI_RSP:
            uart_transmit(&Uart3_handle, event->param, event->param_len);
            break;
        default:
            printf("Unknown event!\r\n");
            break;
        }
        
        vPortFree((void *)event);
    }
}

void app_task_event_post(struct app_task_event *event, bool high)
{
    uint32_t old_basepri;
    
    if(xPortIsInsideInterrupt()) {
        BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
        old_basepri = taskENTER_CRITICAL_FROM_ISR();
        if(high) {
            co_list_push_front(&event_list, &event->hdr);
        }
        else {
            co_list_push_back(&event_list, &event->hdr);
        }
        taskEXIT_CRITICAL_FROM_ISR(old_basepri);
        vTaskNotifyGiveFromISR(app_task_handle, &pxHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
    }
    else {
        taskENTER_CRITICAL();
        if(high) {
            co_list_push_front(&event_list, &event->hdr);
        }
        else {
            co_list_push_back(&event_list, &event->hdr);
        }
        taskEXIT_CRITICAL();
        xTaskNotifyGive(app_task_handle);
    }
}

struct app_task_event *app_task_event_alloc(uint8_t event_type, uint32_t param_len, bool block)
{
    struct app_task_event *event = NULL;
    
    while(event == NULL) {
        event = pvPortMalloc(sizeof(struct app_task_event) + param_len);
        if (event == NULL) {
            if (block) {
                vTaskDelay(10);
            }
            else {
                return NULL;
            }
        }
    }
    
    event->event_type = event_type;
    event->param_len = param_len;
    
    return event;
}

static void app_task(void *arg)
{
    co_list_init(&event_list);

    app_rpmsg_init();

    while(1) {
        ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
        app_task_event_handler();
    }
}

void app_task_init(void)
{
    xTaskCreate(app_task, "app", APP_TASK_STACK_SIZE, NULL, APP_TASK_PRIORITY, &app_task_handle);
}
