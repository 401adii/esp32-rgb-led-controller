#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"driver/uart.h"
#include"rgb_one_chan_templ.h"

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
    int rgb_count = 2;
    uart_init();

    // xTaskCreatePinnedToCore(rgb_one_chan_one_led_spectrum_fade, "RGB Task", 4096, NULL, 1, NULL, 0);
    // xTaskCreatePinnedToCore(rgb_one_chan_four_leds_spectrum_fade, "RGB Task", 4096, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(rgb_one_chan_four_leds_random_fade, "RGB Task", 4096, &rgb_count, 1, NULL, 0);
}