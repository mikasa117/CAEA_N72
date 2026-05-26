/*
 * @Author: BlueboxChamil
 * @Date: 2026-03-04 14:27:08
 * @LastEditTime: 2026-03-05 21:09:11
 * @FilePath: \examples\application\btdm_audio\Src\app_btdm.c
 * @Description:
 * Copyright (c) 2026 by BlueboxChamil, All Rights Reserved.
 */
#include "app_config.h"
#include "app_task.h"
#include "app_btdm.h"
#include "app_ble.h"
#include "app_bt.h"

#include "controller.h"
#include "host.h"
#include "fdb_app.h"
#include "user_bt.h"

void app_btdm_start(void)
{
    app_ble_init();
#if BTDM_STACK_ENABLE_BT == 1
    app_bt_init();
    user_bt_init();
#endif
}

void host_ready_cb(void)
{
    struct app_task_event *event;
    /* notify application BTDM stack is ready. */
    event = app_task_event_alloc(APP_TASK_EVENT_HOST_INITED, 0, true);
    app_task_event_post(event, false);
}

static const uint8_t storage_key[16] =
    {
        0x12, 0x34, 0x56, 0x78,
        0x9A, 0xBC, 0xDE, 0xF0,
        0x11, 0x22, 0x33, 0x44,
        0x55, 0x66, 0x77, 0x88};

void app_btdm_init(void)
{
    uint8_t bt_addr[] = {0x32, 0x32, 0x32, 0x32, 0x32, 0x32};
    uint8_t id_length = 5;

    system_get_unique_ID(bt_addr, &id_length);
    /* prepare for BTDM stack */
    controller_start(BTDM_STACK_HCI_BAUDRATE, bt_addr, bt_addr, 0);

    bool ret = gap_security_storage_key_set(storage_key);
    if (ret == false)
    {
        printf("error gap_security_storage_key_set\r\n");
    }
    else
    {
        printf("succeed gap_security_storage_key_set \r\n");
    }

    bt_addr[5] = 0xc0;
#if BTDM_STACK_ENABLE_BT == 1
    host_btdm_start(BTDM_STACK_HCI_BAUDRATE, HOST_TASK_STACK_SIZE, HOST_TASK_PRIORITY, bt_addr);
#else
    host_ble_start(BTDM_STACK_HCI_BAUDRATE, HOST_TASK_STACK_SIZE, HOST_TASK_PRIORITY, bt_addr);
#endif

    /*
     * init MCU->BT pin, configure PMU_PIN_8 output BBG_EN signal, this pin is used to
     * notice BT core that MCU is in working mode.
     */
    ool_write(PMU_REG_DIAG_CTRL, 0x82);
    ool_write(PMU_REG_PIN_IOMUX_H, 0x03);

    /*
     * init BT->MCU pin, system should not enter sleep mode when this pin is low level.
     * This pin is used by BT core to notice MCU than BT core is in working mode.
     */
    system_prevent_sleep_set(SYSTEM_PREVENT_SLEEP_TYPE_HCI_RX);
    pmu_gpio_int_init(PMU_PIN_9, PMU_GPIO_PULL_UP, 0);
    pmu_enable_isr(PMU_GPIO_PMU_INT_MSK_BIT);
    NVIC_SetPriority(PMU_IRQn, 4);
    NVIC_EnableIRQ(PMU_IRQn);
}
