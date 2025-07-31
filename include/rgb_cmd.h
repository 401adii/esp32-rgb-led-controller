#ifndef RGB_CMD_MANAGER_H
#define RGB_CMD_MANAGER_H

#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"console_init.h"
#include"rgb_one_chan_templ.h"
#include"argtable3/argtable3.h"

#define LEDS_DEFAULT 4
#define LEDS_MAX 4
#define SPEED_DEFAULT 3
#define SPEED_MAX 5

static TaskHandle_t current_task;
static uint8_t led_count;
static uint16_t effect_speed;

int parse_led_arg(int argc, char **argv);
int stop_task();
int fade_task(int argc, char **argv);
int fade_random_task(int argc, char **argv);
int alt_blink_task(int argc, char **argv);
void rgb_cmd_init();

#endif