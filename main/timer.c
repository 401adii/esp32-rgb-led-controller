#include"timer.h"

static uint32_t ticks_per_ms = RESOLUTION / 1000;

gptimer_handle_t timer_init(void){
    gptimer_handle_t timer = NULL;
    gptimer_config_t config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = RESOLUTION,
    };

    gptimer_new_timer(&config, &timer);

    gptimer_enable(timer);
    return timer;
}

esp_err_t timer_deinit(gptimer_handle_t timer){
    if(timer == NULL) return ESP_ERR_INVALID_ARG;
    gptimer_stop(timer);
    esp_err_t ret = gptimer_disable(timer);
    if(ret != ESP_OK) return ret;
    return gptimer_del_timer(timer);
}

esp_err_t timer_start(gptimer_handle_t timer){
    return gptimer_start(timer);
}

esp_err_t timer_stop(gptimer_handle_t timer){
    return gptimer_stop(timer);
}

esp_err_t timer_reset(gptimer_handle_t timer){
    return gptimer_set_raw_count(timer, 0);
}

bool timer_passed(gptimer_handle_t timer, uint32_t time_ms){
    uint64_t time_ticks;
    gptimer_get_raw_count(timer, &time_ticks);
    if(time_ticks >= timer_ms_to_ticks(time_ms))
        return true;
    return false;
}

uint64_t timer_ms_to_ticks(uint32_t time_ms){
    return (uint64_t)time_ms * ticks_per_ms;
}

