#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"driver/uart.h"
#include"rgb.h"

#define PIN_1 GPIO_NUM_17
#define PIN_2 GPIO_NUM_16
#define PIN_3 GPIO_NUM_5

#define TIMER LEDC_TIMER_0

#define RED_PIN_0 GPIO_NUM_15
#define RED_CHANNEL_0 LEDC_CHANNEL_0
#define GREEN_PIN_0 GPIO_NUM_2
#define GREEN_CHANNEL_0 LEDC_CHANNEL_1
#define BLUE_PIN_0 GPIO_NUM_4
#define BLUE_CHANNEL_0 LEDC_CHANNEL_2

void uart_init(void){
    uart_config_t config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .stop_bits = UART_STOP_BITS_1,
        .parity = UART_PARITY_DISABLE,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    uart_param_config(UART_NUM_0, &config);
    uart_driver_install(UART_NUM_0, 2 * 1024, 0, 0, NULL, 0);
}

void init(){
    rgb_t rgb1 = {
        .red_channel = RED_CHANNEL_0,
        .green_channel = GREEN_CHANNEL_0,
        .blue_channel = BLUE_CHANNEL_0,
        .red_channel_pin = RED_PIN_0,
        .green_channel_pin = GREEN_PIN_0,
        .blue_channel_pin = BLUE_PIN_0,
        .enable_pin = PIN_1,
        .timer = TIMER,
    };
    rgb_init(&rgb1);
    color_t user_color = {
        .red = 255,
        .green = 100,
        .blue = 50,
    };
    while(1){
        rgb_enable(&rgb1);
        rgb_set_color(&rgb1, &COLOR_WHITE);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        rgb_set_color(&rgb1, &COLOR_RED);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        rgb_set_color(&rgb1, &COLOR_GREEN);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        rgb_set_color(&rgb1, &COLOR_BLUE);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        rgb_set_color(&rgb1, &user_color);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        rgb_disable(&rgb1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void){
    uart_init();
    init();
}