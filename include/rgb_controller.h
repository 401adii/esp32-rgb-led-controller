#ifndef RGB_CONTROLLER_H
#define RGB_CONTROLLER_H

#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"esp_rom_sys.h"
#include"rgb.h"

#define MIN_DELAY_MS 1

void rgb_two_color(rgb_t *rgb1, rgb_t *rgb2);
void rgb_three_color(rgb_t *rgb1, rgb_t *rgb2, rgb_t *rgb3);
void rgb_four_color(rgb_t *rgb1, rgb_t *rgb2, rgb_t *rgb3, rgb_t *rgb4);
int rgb_transition(rgb_t *rgb, const color_t *color_to, int increment);
int rgb_color_increment(int val_from, int val_to, int increment);

#endif