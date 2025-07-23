#ifndef TIMER_INIT_H
#define TIMER_INIT_H

#include"driver/gptimer.h"

#define RESOLUTION 10000

gptimer_handle_t timer_init(void);
void timer_start(gptimer_handle_t timer);
void timer_reset(gptimer_handle_t timer);
int timer_passed(gptimer_handle_t timer, uint32_t time_ms);
int timer_ms_to_ticks(uint32_t time_ms);

#endif