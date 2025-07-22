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

int rgb_transition(rgb_t *rgb, const color_t *color_to, int increment){
    uint8_t red_flag = rgb->color.red == color_to->red ? 1 : 0;
    uint8_t green_flag = rgb->color.green == color_to->green ? 1 : 0;
    uint8_t blue_flag = rgb->color.blue == color_to->blue ? 1 : 0;

    if(red_flag && green_flag && blue_flag)
        return 1;

    if(!red_flag)
        rgb->color.red = rgb_color_increment(rgb->color.red, color_to->red, increment);

    if(!green_flag)
        rgb->color.green = rgb_color_increment(rgb->color.green, color_to->green, increment);
    
    if(!blue_flag)
        rgb->color.blue = rgb_color_increment(rgb->color.blue, color_to->blue, increment);
    rgb_set_color(rgb, &(rgb->color));
    return 0;
}

int rgb_color_increment(int val_from, int val_to, int increment){
    return val_from + (val_from > val_to ? -increment : increment);
}
