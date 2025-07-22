#include "rgb_controller.h"

void rgb_two_color(rgb_t *rgb1, rgb_t *rgb2){
    rgb_set_color(rgb1, &(rgb1->color));
    rgb_enable(rgb1);
    rgb_disable(rgb2);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    rgb_set_color(rgb2, &(rgb2->color));
    rgb_enable(rgb2);
    rgb_disable(rgb1);
    vTaskDelay(10 / portTICK_PERIOD_MS);
}