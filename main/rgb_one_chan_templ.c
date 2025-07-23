#include "rgb_one_chan_templ.h"

int rgb_one_chan_check_leds(int n){
    return n <= MAX_LEDS ? 1 : 0;
}

void rgb_one_chan_spectrum_fade(void *param){
    
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
        rgb_init(&rgbs[i]);    
    }
    return 1;
}

void rgb_one_chan_random_fade(void *param){
    uint8_t n = *(int*)param;
    
    if(!rgb_one_chan_init(n))
        return;
    
    color_t color_to[4];
    const uint8_t INCREMENT = 1;

    for(int i = 0; i < n; i++){
        rgbs[i].color = COLOR_WHITE;
    }
    
    for(int i = 0; i < n; i++){
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