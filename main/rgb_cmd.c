#include"rgb_cmd.h"

int parse_led_arg(int argc, char **argv){
    struct arg_int *num_leds = arg_int0("n", "number", "<n>", "Number of LEDs (optional)");
    struct arg_int *speed = arg_int0("s", "speed", "<s>", "Speed (1-5) (optional)");
    struct arg_end *end = arg_end(20);
    void *argtable[] = {num_leds, speed, end};

    int nerrors = arg_parse(argc, argv, argtable);
    if(nerrors != 0){
        arg_freetable(argtable, sizeof(argtable)/sizeof(argtable[0]));
        return 1;
    }
    
    led_count = (num_leds->count > 0) ? (uint8_t)num_leds->ival[0] : LEDS_DEFAULT;
    
    if(led_count < 1 || led_count > LEDS_MAX){
        arg_freetable(argtable, sizeof(argtable)/sizeof(argtable[0]));
        return 1;
    }
    
    uint8_t speed_val = (speed->count > 0) ? (uint8_t)speed->ival[0] : SPEED_DEFAULT;
    
    if(speed_val < 1|| speed_val > SPEED_MAX){
        arg_freetable(argtable, sizeof(argtable)/sizeof(argtable[0]));
        return 1;
    }

    effect_speed = speed_val;
    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
    return 0;
}

int stop_task(){
    if(current_task == NULL)  return 1;
    rgb_one_chan_deinit(led_count);
    vTaskDelete(current_task);
    current_task = NULL;
    return 0;
}

int fade_task(int argc, char **argv){
    if(current_task != NULL) return 1;
    if(parse_led_arg(argc, argv)) return 1;
    if(rgb_one_chan_init(led_count)) return 1;
    xTaskCreatePinnedToCore(rgb_one_chan_spectrum_fade, "Fade", 4096, &effect_speed, 2, &current_task, 0);
    return 0;
}

int fade_random_task(int argc, char **argv){
    if(current_task != NULL) return 1;
    if(parse_led_arg(argc, argv)) return 1;
    if(rgb_one_chan_init(led_count)) return 1;
    xTaskCreatePinnedToCore(rgb_one_chan_random_fade, "Fade Random", 4096, &effect_speed, 2, &current_task, 0);
    return 0;
}

int alt_blink_task(int argc, char **argv){
    if(current_task != NULL) return 1;
    if(parse_led_arg(argc, argv)) return 1;
    if(rgb_one_chan_init(led_count)) return 1;
    xTaskCreatePinnedToCore(rgb_one_chan_spectrum_alt_blink, "Alt Blink", 4096, &effect_speed, 2, &current_task, 0);
    return 0;
}

void rgb_cmd(){
    console_init();
    
    console_add("fade",\
         "Enables full color spectrum fade pattern",\
         "[-n|--number <n>] [-s|--speed <s>]",\
          fade_task);
    console_add("fade_random",\
         "Enables fade pattern with random colors",\
         "[-n|--number <n>] [-s|--speed <s>]",\
          fade_random_task);
    console_add("alt_blink",\
         "Enables alteranting, blinking pattern with full color spectrum",\
         "[-n|--number <n>] [-s|--speed <s>]",\
          alt_blink_task);
    console_add("stop",\
         "Stops current pattern\n",\
         NULL,\
         stop_task);
    
    
    console_start();
}
