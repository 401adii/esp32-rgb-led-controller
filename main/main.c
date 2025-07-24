#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"rgb_one_chan_templ.h"
#include"cmd_console.h"

#define LEDS 4

TaskHandle_t current_task;

int fadeTask(){
    if(current_task != NULL)
        return 1;
    uint8_t leds = LEDS;
    xTaskCreatePinnedToCore(rgb_one_chan_spectrum_fade, "Spectrum fade task", 4096, &leds, 2, &current_task, 0);
    return 0;
}

int fadeRandomTask(){
    if(current_task != NULL)
        return 1;
    uint8_t leds = LEDS;
    xTaskCreatePinnedToCore(rgb_one_chan_spectrum_fade, "Random fade task", 4096, &leds, 2, &current_task, 0);
    return 0;
}

int stopTask(){
    if(current_task == NULL)
        return 1;
    rgb_one_chan_deinit(LEDS);
    vTaskDelete(current_task);
    current_task = NULL;
    return 0;
}


void app_main(void){
    const char *fade_cmd = "fade";
    const char *fade_help = "Starts a full color spectrum fade pattern";
    const char *stop_cmd = "stop";
    const char *stop_help = "Stop all leds";
    const char *fade_random_cmd = "fade_random";
    const char *fade_random_help = "Stars a random color fade pattern";
    
    console_init();
    
    console_add(fade_cmd, fade_help, fadeTask);
    console_add(stop_cmd, stop_help, stopTask);
    console_add(fade_random_cmd, fade_random_help, fadeRandomTask);
    
    console_start();
}   