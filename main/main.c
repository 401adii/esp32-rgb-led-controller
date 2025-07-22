#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"driver/uart.h"
#include"rgb_controller.h"

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

static rgb_t rgb1;
static rgb_t rgb2;
static rgb_t rgb3;
static rgb_t rgb4;

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

void app_main(void){
    uart_init();

    rgb1.red_channel = RED_CHANNEL_0;
    rgb1.green_channel = GREEN_CHANNEL_0;
    rgb1.blue_channel = BLUE_CHANNEL_0;
    rgb1.red_channel_pin = RED_PIN_0;
    rgb1.green_channel_pin = GREEN_PIN_0;
    rgb1.blue_channel_pin = BLUE_PIN_0,
    rgb1.enable_pin = PIN_1;
    rgb1.timer = TIMER;
    rgb1.color = COLOR_WHITE;

    rgb_init(&rgb1);

    rgb2.red_channel = RED_CHANNEL_0;
    rgb2.green_channel = GREEN_CHANNEL_0;
    rgb2.blue_channel = BLUE_CHANNEL_0;
    rgb2.red_channel_pin = RED_PIN_0;
    rgb2.green_channel_pin = GREEN_PIN_0;
    rgb2.blue_channel_pin = BLUE_PIN_0,
    rgb2.enable_pin = PIN_2;
    rgb2.timer = TIMER;
    rgb2.color = COLOR_WHITE;

    rgb_init(&rgb2);

    rgb3.red_channel = RED_CHANNEL_0;
    rgb3.green_channel = GREEN_CHANNEL_0;
    rgb3.blue_channel = BLUE_CHANNEL_0;
    rgb3.red_channel_pin = RED_PIN_0;
    rgb3.green_channel_pin = GREEN_PIN_0;
    rgb3.blue_channel_pin = BLUE_PIN_0,
    rgb3.enable_pin = PIN_3;
    rgb3.timer = TIMER;
    rgb3.color = COLOR_WHITE;

    rgb_init(&rgb3);

    rgb4.red_channel = RED_CHANNEL_0;
    rgb4.green_channel = GREEN_CHANNEL_0;
    rgb4.blue_channel = BLUE_CHANNEL_0;
    rgb4.red_channel_pin = RED_PIN_0;
    rgb4.green_channel_pin = GREEN_PIN_0;
    rgb4.blue_channel_pin = BLUE_PIN_0,
    rgb4.enable_pin = PIN_4;
    rgb4.timer = TIMER;
    rgb4.color = COLOR_WHITE;
    
    rgb_init(&rgb4);
    while(1){
        rgb_four_color(&rgb1, &rgb2, &rgb3, &rgb4);
        rgb_transition(&rgb1, &COLOR_RED, 1);
        rgb_transition(&rgb2, &COLOR_BLUE, 1);
        rgb_transition(&rgb3, &COLOR_GREEN, 1);
        rgb_transition(&rgb4, &COLOR_BLACK, 1);
    }
}