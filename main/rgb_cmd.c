#include"rgb_cmd.h"

void save_current_command(rgb_cmd_t cmd){
    nvs_handle_t handle;
    esp_err_t ret;

    ret = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &handle);
    if(ret != ESP_OK) return;

    nvs_set_u8(handle, LAST_COMMAND_KEY, cmd);
    nvs_set_u8(handle, LED_COUNT_KEY, led_count);
    nvs_set_u16(handle, SPEED_KEY, effect_speed);
}

rgb_cmd_t load_saved_command(){
    nvs_handle_t handle;
    esp_err_t ret;
    uint8_t saved_cmd = CMD_NONE;

    ret = nvs_open(NVS_NAMESPACE, NVS_READONLY, &handle);
    if(ret != ESP_OK) return CMD_NONE;

    nvs_get_u8(handle, LAST_COMMAND_KEY, &saved_cmd);
    nvs_get_u8(handle, LED_COUNT_KEY, &led_count);
    nvs_get_u16(handle, SPEED_KEY, &effect_speed);

    return (rgb_cmd_t)saved_cmd;
}

int start_command(rgb_cmd_t cmd){
    const char *cmd_name = "";
    TaskFunction_t task_func = NULL;

    switch(cmd){
        case CMD_FADE:
            cmd_name = "Fade";
            task_func = rgb_one_chan_spectrum_fade;
            break;
        case CMD_FADE_RANDOM:
            cmd_name = "Fade Random";
            task_func = rgb_one_chan_random_fade;
            break;
        case CMD_ALT_BLINK:
            cmd_name = "Alt Blink";
            task_func = rgb_one_chan_spectrum_alt_blink;
            break;
        case CMD_ALT_BLINK_RANDOM:
            cmd_name = "Alt Blink Random";
            task_func = rgb_one_chan_random_alt_blink;
            break;    
        case CMD_RING_BLINK:
            cmd_name = "Ring Blink";
            task_func = rgb_one_chan_spectrum_ring_blink;
            break;
        case CMD_RING_BLINK_RANDOM:
            cmd_name = "Ring Blink Random";
            task_func = rgb_one_chan_random_ring_blink;
            break;
        case CMD_BREATHE:
            cmd_name = "Breathe";
            task_func = rgb_one_chan_spectrum_breathe;
            break; 
        default: return 1;
        }
        
    if(rgb_one_chan_init(led_count)) return 1;
        
    xTaskCreatePinnedToCore(task_func, cmd_name, 4096, &effect_speed, 2, &current_task, 0);
    return 0;
}

int parse_led_arg(int argc, char **argv)
{
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
    save_current_command(CMD_NONE);
    return 0;
}

int fade_task(int argc, char **argv){
    if(current_task != NULL) return 1;
    if(parse_led_arg(argc, argv)) return 1;
    if(rgb_one_chan_init(led_count)) return 1;
    xTaskCreatePinnedToCore(rgb_one_chan_spectrum_fade, "Fade", 4096, &effect_speed, 2, &current_task, 0);
    save_current_command(CMD_FADE);
    return 0;
}

int fade_random_task(int argc, char **argv){
    if(current_task != NULL) return 1;
    if(parse_led_arg(argc, argv)) return 1;
    if(rgb_one_chan_init(led_count)) return 1;
    xTaskCreatePinnedToCore(rgb_one_chan_random_fade, "Fade Random", 4096, &effect_speed, 2, &current_task, 0);
    save_current_command(CMD_FADE_RANDOM);
    return 0;
}

int alt_blink_task(int argc, char **argv){
    if(current_task != NULL) return 1;
    if(parse_led_arg(argc, argv)) return 1;
    if(rgb_one_chan_init(led_count)) return 1;
    xTaskCreatePinnedToCore(rgb_one_chan_spectrum_alt_blink, "Alt Blink", 4096, &effect_speed, 2, &current_task, 0);
    save_current_command(CMD_ALT_BLINK);
    return 0;
}

int alt_blink_random_task(int argc, char **argv){
    if(current_task != NULL) return 1;
    if(parse_led_arg(argc, argv)) return 1;
    if(rgb_one_chan_init(led_count)) return 1;
    xTaskCreatePinnedToCore(rgb_one_chan_random_alt_blink, "Alt Blink Random", 4096, &effect_speed, 2, &current_task, 0);
    save_current_command(CMD_ALT_BLINK_RANDOM);
    return 0;
}

int ring_blink_task(int argc, char **argv){
    if(current_task != NULL) return 1;
    if(parse_led_arg(argc, argv)) return 1;
    if(rgb_one_chan_init(led_count)) return 1;
    xTaskCreatePinnedToCore(rgb_one_chan_spectrum_ring_blink, "Ring Blink", 4096, &effect_speed, 2, &current_task, 0);
    save_current_command(CMD_RING_BLINK);
    return 0;
}

int ring_blink_random_task(int argc, char **argv){
    if(current_task != NULL) return 1;
    if(parse_led_arg(argc, argv)) return 1;
    if(rgb_one_chan_init(led_count)) return 1;
    xTaskCreatePinnedToCore(rgb_one_chan_random_ring_blink, "Ring Blink Random", 4096, &effect_speed, 2, &current_task, 0);
    save_current_command(CMD_RING_BLINK_RANDOM);
    return 0;
}

int breathe_task(int argc, char **argv){
    if(current_task != NULL) return 1;
    if(parse_led_arg(argc, argv)) return 1;
    if(rgb_one_chan_init(led_count)) return 1;
    xTaskCreatePinnedToCore(rgb_one_chan_spectrum_breathe, "Breathe", 4096, &effect_speed, 2, &current_task, 0);
    save_current_command(CMD_BREATHE);
    return 0;
}

void restore_last_command(){
    rgb_cmd_t saved_cmd = load_saved_command();
    if(saved_cmd != CMD_NONE){
        start_command(saved_cmd);
    }
}

void rgb_cmd(){

    esp_err_t ret = nvs_flash_init();
    if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND){
        nvs_flash_erase();
        nvs_flash_init();
    }

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
    console_add("alt_blink_random",\
         "Enables alteranting, blinking pattern with random colors",\
         "[-n|--number <n>] [-s|--speed <s>]",\
          alt_blink_random_task);
    console_add("ring_blink",\
         "Enables circular blinking pattern with full color spectrum",\
         "[-n|--number <n>] [-s|--speed <s>]",\
          ring_blink_task);
    console_add("ring_blink_random",\
         "Enables circular blinking pattern with random colors",\
         "[-n|--number <n>] [-s|--speed <s>]",\
          ring_blink_random_task);
    console_add("breathe",\
         "Enables breathing pattern with full color spectrum",\
         "[-n|--number <n>] [-s|--speed <s>]",\
          breathe_task);
    console_add("stop",\
         "Stops current pattern\n",\
         NULL,\
         stop_task);

    restore_last_command();
    
    console_start();
}
