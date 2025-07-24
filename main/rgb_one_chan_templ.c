#include "rgb_one_chan_templ.h"

int rgb_one_chan_check_leds(int n){
    return n <= MAX_LEDS ? 1 : 0;
}

int rgb_one_chan_init(int n){
    if(!rgb_one_chan_check_leds(n))
        return 0;
    
    const int pins[] = {PIN_1, PIN_2, PIN_3, PIN_4};

    for(int i = 0; i < n; i++){
        rgbs[i].red_channel = RED_CHANNEL_0;
        rgbs[i].green_channel = GREEN_CHANNEL_0;
        rgbs[i].blue_channel = BLUE_CHANNEL_0;
        rgbs[i].red_channel_pin = RED_PIN_0;
        rgbs[i].green_channel_pin = GREEN_PIN_0;
        rgbs[i].blue_channel_pin = BLUE_PIN_0,
        rgbs[i].enable_pin = pins[i];
        rgbs[i].timer = TIMER;
        rgbs[i].color = COLOR_BLACK;
        rgb_init(&rgbs[i]);    
        rgb_disable(&rgbs[i]);
    }
    return 1;
}

void rgb_one_chan_spectrum_fade(void *param){
    uint8_t n = *(uint8_t*)param;

    if(!rgb_one_chan_init(n))
        return;

    uint8_t idx = 0;
    color_t color_to[MAX_LEDS];
    const uint8_t INCREMENT = 1;
    
    for(int i = 0; i < n; i++){
        rgbs[i].color = COLORS[0 + i];
        color_to[i] = COLORS[1 + i];
    }

    while(1){
        rgb_mux(rgbs, n);

        if(rgb_transition(&rgbs[0], &color_to[0], INCREMENT)){
            if(++idx >= COLORS_LEN)
                idx = 0;
            for(int i = 0; i < n; i++){
                color_to[i] = COLORS[(idx + i + 1) % COLORS_LEN];
            }
        }
        for(int i = 1; i < n; i++){
            rgb_transition(&rgbs[i], &color_to[i], INCREMENT);
        }
    }
}


void rgb_one_chan_random_fade(void *param){
    uint8_t n = *(int*)param;
    
    if(!rgb_one_chan_init(n))
        return;
    
    color_t color_to[MAX_LEDS];
    const uint8_t INCREMENT = 1;

    for(int i = 0; i < n; i++){
        rgbs[i].color = COLOR_WHITE;
        color_to[i] = COLORS[esp_random() % COLORS_LEN];
    }
    
    while(1){
        rgb_mux(rgbs, n);

        for(int i = 0; i < n; i++){
            if(rgb_transition(&rgbs[i], &color_to[i], INCREMENT))
                color_to[i] = COLORS[esp_random() % COLORS_LEN];
        }
    }
}

void rgb_one_chan_test(void *param){
    uint8_t n = *(int*)param;

    if(!rgb_one_chan_init(n))
        return;


    uint8_t sw_flag = 1;
    color_t color_to[MAX_LEDS];
    
    gptimer_handle_t timer = timer_init();
    
    for(int i = 0; i < n; i++){
        rgbs[i].color = COLORS[0 + i];
        color_to[i] = COLORS[1 + i];
    }

    rgb_set_color(&rgbs[0], &(rgbs[0].color));
    timer_start(timer);
    while(1){   
        if(timer_passed(timer,500)){
            timer_reset(timer);
            sw_flag = !sw_flag;
        }
        if(sw_flag)
            rgb_enable(&rgbs[0]);
        else
            rgb_disable(&rgbs[0]);
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}
