#include"rgb_cmd.h"

int parse_led_arg(int argc, char **argv){
    struct arg_int *num_leds = arg_int0(NULL, NULL, "<n>", "Number of LEDs (optional)");
    struct arg_end *end = arg_end(1);
    void *argtable[] = {num_leds, end};

    int nerrors = arg_parse(argc, argv, argtable);
    if(nerrors != 0){
        return 1;
    }

    led_count = (num_leds->count > 0) ? (uint8_t)num_leds->ival[0] : LEDS_DEFAULT;
    
    if(led_count < 1 || led_count > LEDS_MAX){
        return 1;
    }

    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
    return 0;
}

int stop_task(){
    if(current_task == NULL) 
        return 1;
    vTaskDelete(current_task);
    rgb_one_chan_deinit(led_count);
    current_task = NULL;
    return 0;
}

int fade_task(int argc, char **argv){
    if(current_task != NULL)
        return 1;
    if(parse_led_arg(argc, argv))
        return 1;
    xTaskCreatePinnedToCore(rgb_one_chan_spectrum_fade, "Fade", 4096, &led_count, 2, &current_task, 0);
    return 0;
}

int fade_random_task(int argc, char **argv){
    if(current_task != NULL)
        return 1;
    if(parse_led_arg(argc, argv))
        return 1;
    xTaskCreatePinnedToCore(rgb_one_chan_random_fade, "Fade Random", 4096, &led_count, 2, &current_task, 0);
    return 0;
}

int alt_blink_task(int argc, char **argv){
    if(current_task != NULL)
        return 1;
    if(parse_led_arg(argc, argv))
        return 1;
    xTaskCreatePinnedToCore(rgb_one_chan_spectrum_alt_blink, "Alt Blink", 4096, &led_count, 2, &current_task, 0);
    return 0;
}

void rgb_cmd_init(){
    console_init();
    
    console_add("fade",\
         "Enables full color spectrum fade pattern",\
         "[<n> - Number of LEDs]",\
          fade_task);
    console_add("fade_random",\
         "Enables fade pattern with random colors",\
         "[<n> - Number of LEDs]",\
          fade_random_task);
    console_add("alt_blink",\
         "Enables alteranting, blinking pattern with full color spectrum",\
         "[<n> - Number of LEDs]",\
          alt_blink_task);
    console_add("stop",\
         "Stops current pattern\n",\
         NULL,\
         stop_task);
    
    
    console_start();
}
