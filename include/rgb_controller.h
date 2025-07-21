#ifndef RGB_CONTROLLER_H
#define RGB_CONTROLLER_H

#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"esp_rom_sys.h"
#include"rgb.h"

#define MIN_DELAY_MS 10

void rgb_two_color(rgb_t *rgb1, rgb_t *rgb2);

#endif