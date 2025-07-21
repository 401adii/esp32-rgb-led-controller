#ifndef RGB_H
#define RGB_H

#include"led_controller.h"
#include"driver/gpio.h"
#include"gpio_init.h"

typedef struct{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} color_t;

typedef struct{
    ledc_timer_t timer;
    ledc_channel_t red_channel;
    ledc_channel_t green_channel;
    ledc_channel_t blue_channel;
    uint8_t red_channel_pin;
    uint8_t green_channel_pin;
    uint8_t blue_channel_pin;
    uint8_t enable_pin;
    color_t color;
} rgb_t;

void rgb_init(rgb_t *rgb);
void rgb_enable(rgb_t *rgb);
void rgb_disable(rgb_t *rgb);
void rgb_set_color(rgb_t *rgb, color_t* color);

#endif