/*
 * @Author: liuranyang liuranyang@cncaea.cn
 * @Date: 2026-02-27 19:44:16
 * @LastEditors: liuranyang liuranyang@cncaea.cn
 * @LastEditTime: 2026-03-02 10:47:02
 * @FilePath: \DD0B10AADWWA_APP\examples\application\btdm_audio\Src\app_bt.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _APP_BT_H
#define _APP_BT_H

#include "app_btdm.h"

#include "hf_api.h"
#include "me_api.h"
#include "a2dp_api.h"
#include "hfg_api.h"
#include "avrcp_api.h"
#include "hid_api.h"
#include "spp_api.h"
#include "pbap_api.h"
#include "map_api.h"

#define NUM_STREAMS 4

extern HfChannel *hf_channel;
extern HfgChannel *hfg_channel;
extern A2dpStream *Stream;
extern AvrcpChannel *rcpCtChannel;
extern PbapClientSession *pbap_client;
extern MapClientSession *map_client;
extern SppDev *spp_dev;
extern HidChannel *hid_channel;

extern uint8_t after_app_bt_init;

uint8_t bt_get_free_hf_channel(void);
uint8_t bt_get_free_hfg_channel(void);
uint8_t bt_get_free_a2dp_sink_stream(void);
uint8_t bt_get_free_a2dp_source_stream(void);
uint8_t bt_get_free_avrcp_channel(void);
uint8_t bt_get_free_spp_channel(void);
uint8_t bt_get_free_hid_channel(void);

void app_bt_send_sco_data(void *channel, uint8_t seq, uint8_t *data, uint16_t length);
void app_bt_init(void);
void bt_avrcp_register_notification(AvrcpChannel *chnl, uint16_t event_mask);
void bt_name_query(BD_ADDR *addr, BtPageScanInfo *psi);

void my_bt_start_adv();
void my_bt_stop_adv();

#endif // _APP_BT_H
