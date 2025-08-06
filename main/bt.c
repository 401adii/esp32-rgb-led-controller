#include "bt.h"

void bt_init(){
    esp_err_t ret;
    
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        ret = nvs_flash_init();
    }
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    bt_cfg.mode = ESP_BT_MODE_CLASSIC_BT;
    
    esp_bt_controller_init(&bt_cfg);
    esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT);

    esp_bluedroid_init();

    esp_bluedroid_enable();
    esp_bt_gap_set_device_name(DEVICE_NAME);
    esp_spp_register_callback(esp_spp_cb);
    esp_spp_init(ESP_SPP_MODE_CB);
    esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
}

void esp_spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
    switch (event) {
        case ESP_SPP_INIT_EVT:
            esp_spp_start_srv(ESP_SPP_SEC_NONE, ESP_SPP_ROLE_SLAVE, 0, SPP_SERVER_NAME);
            break;
            
        case ESP_SPP_START_EVT:
            break;
            
        case ESP_SPP_SRV_OPEN_EVT:
            spp_handle = param->srv_open.handle;
            break;
            
        case ESP_SPP_CLOSE_EVT:
            spp_handle = 0;
            break;
            
        case ESP_SPP_DATA_IND_EVT:
            if (spp_handle != 0) {
            }
            break;
        default:
            break;
    }
}
