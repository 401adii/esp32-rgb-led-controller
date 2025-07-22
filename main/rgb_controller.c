#include "rgb_controller.h"

void rgb_two_color(rgb_t *rgb1, rgb_t *rgb2){
    rgb_set_color(rgb1, &(rgb1->color));
    rgb_enable(rgb1);
    rgb_disable(rgb2);
    vTaskDelay(MIN_DELAY_MS / portTICK_PERIOD_MS);
    rgb_set_color(rgb2, &(rgb2->color));
    rgb_enable(rgb2);
    rgb_disable(rgb1);
    vTaskDelay(MIN_DELAY_MS / portTICK_PERIOD_MS);
}

void rgb_three_color(rgb_t *rgb1, rgb_t *rgb2, rgb_t *rgb3){
    rgb_set_color(rgb1, &(rgb1->color));
    rgb_enable(rgb1);
    rgb_disable(rgb3);
    vTaskDelay(MIN_DELAY_MS / portTICK_PERIOD_MS);
    rgb_set_color(rgb2, &(rgb2->color));
    rgb_enable(rgb2);
    rgb_disable(rgb1);
    vTaskDelay(MIN_DELAY_MS / portTICK_PERIOD_MS);
    rgb_set_color(rgb3, &(rgb3->color));
    rgb_enable(rgb3);
    rgb_disable(rgb2);
    vTaskDelay(MIN_DELAY_MS / portTICK_PERIOD_MS);
}

void rgb_four_color(rgb_t *rgb1, rgb_t *rgb2, rgb_t *rgb3, rgb_t *rgb4){
    rgb_set_color(rgb1, &(rgb1->color));
    rgb_enable(rgb1);
    rgb_disable(rgb4);
    vTaskDelay(MIN_DELAY_MS / portTICK_PERIOD_MS);
    rgb_set_color(rgb2, &(rgb2->color));
    rgb_enable(rgb2);
    rgb_disable(rgb1);
    vTaskDelay(MIN_DELAY_MS / portTICK_PERIOD_MS);
    rgb_set_color(rgb3, &(rgb3->color));
    rgb_enable(rgb3);
    rgb_disable(rgb2);
    vTaskDelay(MIN_DELAY_MS / portTICK_PERIOD_MS);
    rgb_set_color(rgb4, &(rgb4->color));
    rgb_enable(rgb4);
    rgb_disable(rgb3);
    vTaskDelay(MIN_DELAY_MS / portTICK_PERIOD_MS);
}
