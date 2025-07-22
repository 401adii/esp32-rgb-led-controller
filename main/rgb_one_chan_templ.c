#include "rgb_one_chan_templ.h"

void rgb_one_chan_four_leds_random_fade(void *param){
    
    rgb_t rgb1;
    rgb_t rgb2;
    rgb_t rgb3;
    rgb_t rgb4;

    color_t rgb1_color_to = COLORS[esp_random() % COLORS_LEN];
    color_t rgb2_color_to = COLORS[esp_random() % COLORS_LEN];
    color_t rgb3_color_to = COLORS[esp_random() % COLORS_LEN];
    color_t rgb4_color_to = COLORS[esp_random() % COLORS_LEN];
    
    const uint8_t INCREMENT = 5;
    
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
        
        if(rgb_transition(&rgb1, &rgb1_color_to, INCREMENT))
            rgb1_color_to = COLORS[esp_random() % COLORS_LEN];
        
        if(rgb_transition(&rgb2, &rgb2_color_to, INCREMENT))
            rgb2_color_to = COLORS[esp_random() % COLORS_LEN];
        
        if(rgb_transition(&rgb3, &rgb3_color_to, INCREMENT))
            rgb3_color_to = COLORS[esp_random() % COLORS_LEN];
        
        if(rgb_transition(&rgb4, &rgb4_color_to, INCREMENT))
            rgb4_color_to = COLORS[esp_random() % COLORS_LEN];    
        
    }
}