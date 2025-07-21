#include"rgb.h"

void rgb_init(rgb_t *rgb){
    ledc_timer_init(rgb->timer);
    ledc_channel_init(rgb->red_channel, rgb->timer, rgb->red_channel_pin);
    ledc_channel_init(rgb->green_channel, rgb->timer, rgb->green_channel_pin);
    ledc_channel_init(rgb->blue_channel, rgb->timer, rgb->blue_channel_pin);
    gpio_init(rgb->enable_pin);
}

void rgb_enable(rgb_t *rgb){
    gpio_set_level(rgb->enable_pin, 0); //0 so GPIO acts as a 'ground'
}

void rgb_disable(rgb_t *rgb){
    gpio_set_level(rgb->enable_pin, 1); //1 so no current flow
}

void rgb_set_color(rgb_t *rgb, const color_t* color){
    rgb->color = *(color);
    ledc_channel_set(rgb->red_channel, rgb->color.red);
    ledc_channel_set(rgb->blue_channel, rgb->color.green);
    ledc_channel_set(rgb->green_channel, rgb->color.blue);
}