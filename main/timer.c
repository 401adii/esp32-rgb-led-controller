#include"timer.h"

gptimer_handle_t timer_init(void){
    gptimer_handle_t timer = NULL;
    gptimer_config_t config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = RESOLUTION,
    };

    gptimer_new_timer(&config, &timer);

    return timer;
}

void timer_start(gptimer_handle_t timer){
    gptimer_enable(timer);
    gptimer_start(timer);
}

void timer_reset(gptimer_handle_t timer){
    gptimer_set_raw_count(timer, 0);
}

int timer_passed(gptimer_handle_t timer, uint32_t time_ms){
    uint64_t time_ticks;
    gptimer_get_raw_count(timer, &time_ticks);
    if(time_ticks >= timer_ms_to_ticks(time_ms))
        return 1;
    return 0;
}

int timer_ms_to_ticks(uint32_t time_ms){
    return time_ms * 1 / RESOLUTION;
}

