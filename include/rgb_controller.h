#ifndef RGB_CONTROLLER_H
#define RGB_CONTROLLER_H

#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"driver/gpio.h"
#include"led_controller.h"
#include"gpio_init.h"
#include"colors.h"

#define MIN_DELAY_MS 1

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
void rgb_set_color(rgb_t *rgb, const color_t* color);
void rgb_mux(rgb_t *rgbs, uint8_t len);
int rgb_transition(rgb_t *rgb, const color_t *color_to, int increment);
int rgb_color_increment(int val_from, int val_to, int increment);

#endif