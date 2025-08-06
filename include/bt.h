#include"nvs_flash.h"
#include"esp_bt.h"
#include"esp_bt_main.h"
#include"esp_bt_device.h"
#include"esp_gap_bt_api.h"
#include"esp_spp_api.h"
#include"esp_console.h"

#define TAG "BT_RGB"
#define DEVICE_NAME "ESP32_RGB_LAMP"
#define SPP_SERVER_NAME "SPP_SERVER"

static uint32_t spp_handle = 0;

void bt_init();
void esp_spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param);
