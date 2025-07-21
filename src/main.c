#include"led_controller.h"
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"driver/uart.h"
#include"driver/gpio.h"

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

void gpio_init(void){
    gpio_config_t config = {
        .pin_bit_mask = 1ULL << PIN_1 | 1 << PIN_2 | 1 << PIN_3,
        .mode = GPIO_MODE_OUTPUT,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&config);
}

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
    gpio_init();
    ledc_init();

    led_t led1 = {
        .r = 255,
        .g = 255,
        .b = 0,
        .pin = PIN_1,
    };

    led_t led2 = {
        .r = 0,
        .g = 255,
        .b = 255,
        .pin = PIN_2,
    };

    led_t led3 = {
        .r = 255,
        .g = 0,
        .b = 255,
        .pin = PIN_3,
    };
    uint16_t del = 500;
    
    led_disable(&led1);
    led_disable(&led2);
    led_disable(&led3);
    
    // while(1){
    //     led_set_color(255, 255, 0);
    //     led_enable(&led1);
    //     led_disable(&led3);
    //     vTaskDelay(del / portTICK_PERIOD_MS);
    //     led_set_color(0, 255, 255);
    //     led_enable(&led2);
    //     led_disable(&led1);
    //     vTaskDelay(del / portTICK_PERIOD_MS);
    //     led_set_color(255, 0, 255);
    //     led_enable(&led3);
    //     led_disable(&led2);
    //     vTaskDelay(del / portTICK_PERIOD_MS);
    // }

    while(1){
        led_set_color(255, 0, 0);
        led_enable(&led1);
        led_disable(&led3);
        vTaskDelay(del / portTICK_PERIOD_MS);
        led_enable(&led2);
        led_disable(&led1);
        vTaskDelay(del / portTICK_PERIOD_MS);
        led_enable(&led3);
        led_disable(&led2);
        vTaskDelay(del / portTICK_PERIOD_MS);
        led_set_color(0, 255, 0);
        led_enable(&led1);
        led_disable(&led3);
        vTaskDelay(del / portTICK_PERIOD_MS);
        led_enable(&led2);
        led_disable(&led1);
        vTaskDelay(del / portTICK_PERIOD_MS);
        led_enable(&led3);
        led_disable(&led2);
        vTaskDelay(del / portTICK_PERIOD_MS);
        led_set_color(0, 0, 255);
        led_enable(&led1);
        led_disable(&led3);
        vTaskDelay(del / portTICK_PERIOD_MS);
        led_enable(&led2);
        led_disable(&led1);
        vTaskDelay(del / portTICK_PERIOD_MS);
        led_enable(&led3);
        led_disable(&led2);
        vTaskDelay(del / portTICK_PERIOD_MS);
    }

    // while(1){
    //     led_enable(&led3);
    //     vTaskDelay(del / portTICK_PERIOD_MS);
    //     led_disable(&led3);
    //     vTaskDelay(del / portTICK_PERIOD_MS);
    // }

}