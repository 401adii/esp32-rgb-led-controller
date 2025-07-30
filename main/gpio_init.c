#include "gpio_init.h"

static bool gpio_used[GPIO_NUM_MAX] = {0};

esp_err_t gpio_init(gpio_num_t pin){
    if(gpio_used[pin]) return ESP_OK;
    gpio_config_t config = {
        .pin_bit_mask = 1ULL << pin,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    esp_err_t ret = gpio_config(&config);
    if(ret == ESP_OK) gpio_used[pin] = true;
    return ret;
}

esp_err_t gpio_deinit(gpio_num_t pin){
    esp_err_t ret = gpio_set_direction(pin, GPIO_MODE_OUTPUT);
    if(ret != ESP_OK) return ret;
    ret = gpio_reset_pin(pin);
    if(ret == ESP_OK) gpio_used[pin] = false;
    return ret;
}
