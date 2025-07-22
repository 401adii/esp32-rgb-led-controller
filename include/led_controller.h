#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include"driver/ledc.h"

#define SPEED_MODE LEDC_LOW_SPEED_MODE
#define PWM_FREQ 156250

void ledc_timer_init(ledc_timer_t timer);
void ledc_channel_init(ledc_channel_t channel, ledc_timer_t timer, int pin);
void ledc_channel_set(ledc_channel_t channel, int duty);
void ledc_channel_disable(ledc_channel_t channel);

#endif