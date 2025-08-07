#include "rgb_one_chan_templ.h"

int rgb_one_chan_check_leds(int n){
    return n <= MAX_LEDS ? 1 : 0;
}

int rgb_one_chan_init(int n){
    if(!rgb_one_chan_check_leds(n))
    return 1;
    
    const int pins[] = {PIN_1, PIN_2, PIN_3, PIN_4};
    
    led_count = n;
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
    
    timer = timer_init();
    
    return 0;
}

void rgb_one_chan_deinit(int n){
    for(int i = 0; i < n; i++){
        rgb_deinit(&rgbs[i]);
    }
    timer_deinit(timer);
}

void rgb_one_chan_spectrum_fade(void *param){
    const uint8_t INCREMENT = *(uint8_t*)param;
    uint8_t idx = 0;
    color_t color_to[MAX_LEDS];
    
    for(int i = 0; i < led_count; i++){
        rgbs[i].color = COLORS[0 + i];
        color_to[i] = COLORS[1 + i];
    }

    while(1){
        rgb_mux(rgbs, led_count);

        if(rgb_transition(&rgbs[0], &color_to[0], INCREMENT)){
            if(++idx >= COLORS_LEN)
                idx = 0;
            for(int i = 0; i < led_count; i++){
                color_to[i] = COLORS[(idx + i + 1) % COLORS_LEN];
            }
        }
        for(int i = 1; i < led_count; i++){
            rgb_transition(&rgbs[i], &color_to[i], INCREMENT);
        }
    }
}


void rgb_one_chan_random_fade(void *param){
    const uint8_t INCREMENT = *(uint8_t*)param;
    color_t color_to[MAX_LEDS];

    for(int i = 0; i < led_count; i++){
        rgbs[i].color = COLOR_WHITE;
        color_to[i] = COLORS[esp_random() % COLORS_LEN];
    }
    
    while(1){
        rgb_mux(rgbs, led_count);

        for(int i = 0; i < led_count; i++){
            if(rgb_transition(&rgbs[i], &color_to[i], INCREMENT))
                color_to[i] = COLORS[esp_random() % COLORS_LEN];
        }
    }
}

void rgb_one_chan_spectrum_alt_blink(void *param){
    const uint16_t TIME_MS = *(uint16_t*)param * 100;
    uint8_t idx = 0;
    uint8_t sw_flag = 0;

    for(int i = 0; i < led_count; i++)
        rgbs[i].color = COLORS[0 + i];

    timer_start(timer);
    
    while(1){
        rgb_mux(rgbs, led_count);
        
        if(timer_passed(timer, TIME_MS)){
            timer_reset(timer);
            sw_flag = !sw_flag;
            if(++idx >= COLORS_LEN)
                idx = 0;
            for(int i = 0; i < led_count; i++)
                rgbs[i].color = COLORS[(sw_flag + idx + i) % COLORS_LEN];
        }
        
        for(int i = 0; i < led_count; i++){
            if(i % 2 == sw_flag){
                rgb_set_color(&rgbs[i], &rgbs[i].color);
            }
            else{
                rgb_set_color(&rgbs[i], &COLOR_BLACK);
            }
        }
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }

}

void rgb_one_chan_random_alt_blink(void *param){
    const uint16_t TIME_MS = *(uint16_t*)param * 100;
    uint8_t sw_flag = 0;

    timer_start(timer);
    
    while(1){
        rgb_mux(rgbs, led_count);
        
        if(timer_passed(timer, TIME_MS)){
            timer_reset(timer);
            sw_flag = !sw_flag;
            for(int i = 0; i < led_count; i++){
                if(i % 2 == sw_flag){
                    rgb_set_color(&rgbs[i], &COLORS[esp_random() % COLORS_LEN]);
                }
                else{
                    rgb_set_color(&rgbs[i], &COLOR_BLACK);
                }
            }
        }
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }

}

void rgb_one_chan_spectrum_ring_blink(void *param){
    const uint16_t TIME_MS = *(uint16_t*)param * 100;
    uint8_t color_idx = 0;
    uint8_t led_idx = 0;
    timer_start(timer);
    while(1){
        if(timer_passed(timer, TIME_MS)){
            timer_reset(timer);
            if(++color_idx >= COLORS_LEN)
                color_idx = 0;
            if(++led_idx >= led_count)
                led_idx = 0;
        }
        for(int i = 0; i < led_count; i++){
            if(i != led_idx)
                rgb_disable(&rgbs[i]);
            else{
                rgb_enable(&rgbs[i]);
                rgb_set_color(&rgbs[i], &COLORS[color_idx]);
            }
        }
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}

void rgb_one_chan_random_ring_blink(void *param){
    const uint16_t TIME_MS = *(uint16_t*)param * 100;
    uint8_t led_idx = 0;
    timer_start(timer);
    while(1){
        if(timer_passed(timer, TIME_MS)){
            timer_reset(timer);
            if(++led_idx >= led_count)
                led_idx = 0;
            for(int i = 0; i < led_count; i++){
                if(i != led_idx)
                    rgb_disable(&rgbs[i]);
                else{
                    rgb_enable(&rgbs[i]);
                    rgb_set_color(&rgbs[i], &COLORS[esp_random() % COLORS_LEN]);
                }
            }
        }
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}

void rgb_one_chan_spectrum_breathe(void *param){
    const uint8_t INCREMENT = *(uint8_t*)param;
    uint8_t idx = 0;
    bool flag = true;
    for(int i = 0; i < led_count; i++)
        rgb_enable(&rgbs[i]);
    
    rgb_set_color(&rgbs[0], &COLORS[idx]);
    while(1){
        if(flag){
            if(rgb_transition(&rgbs[0], &COLORS[idx], INCREMENT)){
                flag = !flag;
                if(++idx >= COLORS_LEN)
                    idx = 0;
            }
        }
        else if(rgb_transition(&rgbs[0], &COLOR_BLACK, INCREMENT))
            flag = !flag;
        
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}

void rgb_one_chan_random_breathe(void *param){
    const uint8_t INCREMENT = *(uint8_t*)param;
    color_t color_to = COLORS[esp_random() % COLORS_LEN];
    bool flag = true;
    for(int i = 0; i < led_count; i++)
        rgb_enable(&rgbs[i]);
    
    rgb_set_color(&rgbs[0], &color_to);
    while(1){
        if(flag){
            if(rgb_transition(&rgbs[0], &color_to, INCREMENT)){
                flag = !flag;
                color_to = COLORS[esp_random() % COLORS_LEN];
            }
        }
        else if(rgb_transition(&rgbs[0], &COLOR_BLACK, INCREMENT))
            flag = !flag;
        
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}
