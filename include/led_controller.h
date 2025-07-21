#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include"driver/ledc.h"
#include"driver/gpio.h"

#define SPEED_MODE LEDC_LOW_SPEED_MODE
#define PWM_FREQ 4000

typedef struct {
    uint8_t pin;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} led_t;


void ledc_timer_init(ledc_timer_t timer);
void ledc_channel_init(ledc_channel_t channel, ledc_timer_t timer, int pin);
void ledc_set(ledc_channel_t channel, int duty);
void ledc_disable(ledc_channel_t channel);

#endif