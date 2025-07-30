#include"ledc_8bit_lowspeed.h"

static bool timer_used[LEDC_TIMER_MAX] = {0};
static bool channel_used[LEDC_CHANNEL_MAX] = {0};

esp_err_t ledc_timer_init(ledc_timer_t timer){
    if(timer_used[timer]) return ESP_ERR_INVALID_STATE;
    ledc_timer_config_t timer_config = {
        .speed_mode = SPEED_MODE,
        .timer_num = timer,
        .freq_hz = PWM_FREQ,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .clk_cfg = LEDC_APB_CLK,
    };
    timer_used[timer] = true;
    return ledc_timer_config(&timer_config);
}

esp_err_t ledc_channel_init(ledc_channel_t channel, ledc_timer_t timer, gpio_num_t pin){
    if(channel_used[channel]) return ESP_ERR_INVALID_STATE;
    ledc_channel_config_t channel_config = {
        .speed_mode = SPEED_MODE,
        .channel = channel,
        .gpio_num = pin,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = timer,
        .duty = 0,
    };
    channel_used[channel] = true;
    return ledc_channel_config(&channel_config);
}

esp_err_t ledc_timer_deinit(ledc_timer_t timer){
    esp_err_t ret = ledc_timer_pause(SPEED_MODE, timer);
    if(ret != ESP_OK) return ret;
    timer_used[timer] = false;
    return ledc_timer_rst(SPEED_MODE, timer);
}

esp_err_t ledc_channel_deinit(ledc_channel_t channel){
    channel_used[channel] = false;
    return ledc_stop(SPEED_MODE, channel, 0);
}

esp_err_t ledc_channel_set(ledc_channel_t channel, uint8_t duty){
    if(duty > 255) return ESP_ERR_INVALID_ARG;
    esp_err_t ret = ledc_set_duty(SPEED_MODE, channel, duty);
    if(ret != ESP_OK) return ret;
    return ledc_update_duty(SPEED_MODE, channel);
}

esp_err_t ledc_channel_disable(ledc_channel_t channel){
    esp_err_t ret = ledc_set_duty(SPEED_MODE, channel, 0);
    if(ret != ESP_OK) return ret;
    return ledc_update_duty(SPEED_MODE, channel);
}