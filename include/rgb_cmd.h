#ifndef RGB_CMD_MANAGER_H
#define RGB_CMD_MANAGER_H

#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"nvs_flash.h"
#include"nvs.h"
#include"argtable3/argtable3.h"
#include"console_init.h"
#include"rgb_one_chan_templ.h"

#define LEDS_DEFAULT 4
#define LEDS_MAX 4
#define SPEED_DEFAULT 3
#define SPEED_MAX 5

#define NVS_NAMESPACE "rgb_cmd"
#define LAST_COMMAND_KEY "last_cmd"
#define LED_COUNT_KEY "led_count"
#define SPEED_KEY "speed"

typedef enum {
    CMD_NONE,
    CMD_FADE,
    CMD_FADE_RANDOM,
    CMD_ALT_BLINK,
    CMD_ALT_BLINK_RANDOM,
    CMD_RING_BLINK,
    CMD_RING_BLINK_RANDOM,
} rgb_cmd_t;

static TaskHandle_t current_task;
static uint8_t led_count;
static uint16_t effect_speed;

void save_current_command(rgb_cmd_t cmd);
rgb_cmd_t load_saved_command();
int parse_led_arg(int argc, char **argv);
int stop_task();
int fade_task(int argc, char **argv);
int fade_random_task(int argc, char **argv);
int alt_blink_task(int argc, char **argv);
int alt_blink_random_task(int argc, char **argv);
int ring_blink_task(int argc, char **argv);
int ring_blink_random_task(int argc, char **argv);
void restore_last_command();
void rgb_cmd();

#endif