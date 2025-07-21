#ifndef RGB_H
#define RGB_H

#include"led_controller.h"

typedef struct{
    ledc_timer_t timer;
    ledc_channel_t red_channel;
    ledc_channel_t green_channel;
    ledc_channel_t blue_channel;
    uint8_t red_value;
    uint8_t green_value;
    uint8_t blue_value;
} rgb_t;



#endif