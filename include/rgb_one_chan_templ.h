#ifndef RGB_ONE_CHAN_TEMPL_H
#define RGB_ONE_CHAN_TEMPL_H

#include"rgb_controller.h"
#include"colors.h"
#include"esp_random.h"

#define PIN_1 GPIO_NUM_17
#define PIN_2 GPIO_NUM_16
#define PIN_3 GPIO_NUM_5
#define PIN_4 GPIO_NUM_18

#define TIMER LEDC_TIMER_0

#define RED_PIN_0 GPIO_NUM_15
#define RED_CHANNEL_0 LEDC_CHANNEL_0
#define GREEN_PIN_0 GPIO_NUM_2
#define GREEN_CHANNEL_0 LEDC_CHANNEL_1
#define BLUE_PIN_0 GPIO_NUM_4
#define BLUE_CHANNEL_0 LEDC_CHANNEL_2

void rgb_one_chan_four_leds_random_fade(void *param);

#endif