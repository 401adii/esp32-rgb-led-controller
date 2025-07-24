#include"led_controller.h"

void ledc_timer_init(ledc_timer_t timer){
    ledc_timer_config_t timer_config = {
        .speed_mode = SPEED_MODE,
        .timer_num = timer,
        .freq_hz = PWM_FREQ,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .clk_cfg = LEDC_APB_CLK,
    };
    ledc_timer_config(&timer_config);

}

void ledc_channel_init(ledc_channel_t channel, ledc_timer_t timer, int pin){
    ledc_channel_config_t channel_config = {
        .speed_mode = SPEED_MODE,
        .channel = channel,
        .gpio_num = pin,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = timer,
        .duty = 0,
    };
    ledc_channel_config(&channel_config);
}

void ledc_timer_deinit(ledc_timer_t timer){
    ledc_timer_rst(SPEED_MODE, timer);
}

void ledc_channel_deinit(ledc_channel_t channel){
    ledc_stop(SPEED_MODE, channel, 0);
}

void ledc_channel_set(ledc_channel_t channel, int duty)
{
    ledc_set_duty(SPEED_MODE, channel, duty);
    ledc_update_duty(SPEED_MODE, channel);
}

void ledc_channel_disable(ledc_channel_t channel){
    ledc_set_duty(SPEED_MODE, channel, 0);
    ledc_update_duty(SPEED_MODE, channel);
}