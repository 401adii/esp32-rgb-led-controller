#ifndef RGB_ONE_CHAN_TEMPL_H
#define RGB_ONE_CHAN_TEMPL_H

#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"driver/gptimer.h"
#include"rgb_controller.h"
#include"colors.h"
#include"esp_random.h"
#include"timer.h"
#include"esp_log.h"

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

#define MAX_LEDS 4

static rgb_t rgbs[MAX_LEDS];
static uint8_t led_count;
static gptimer_handle_t timer;

int rgb_one_chan_check_leds(int n);
int rgb_one_chan_init(int n);
void rgb_one_chan_deinit(int n);
void rgb_one_chan_spectrum_fade(void *param);
void rgb_one_chan_random_fade(void *param);
void rgb_one_chan_spectrum_blink(void *param);
void rgb_one_chan_random_blink(void *param);
void rgb_one_chan_spectrum_alt_blink(void *param);
void rgb_one_chan_random_alt_blink(void *param);
void rgb_one_chan_spectrum_ring_blink(void *param);
void rgb_one_chan_random_ring_blink(void *param);
void rgb_one_chan_spectrum_breathe(void *param);
void rgb_one_chan_random_breathe(void *param);

#endif