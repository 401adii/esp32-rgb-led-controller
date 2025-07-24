#include"cmd_console.h"

void console_init(void){
    repl = NULL;
    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
    repl_config.prompt = PROMPT_STR;
    esp_console_register_help_command();
    esp_console_dev_uart_config_t hw_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();
    esp_console_new_repl_uart(&hw_config, &repl_config, &repl);
}

void console_start(void){
    esp_console_start_repl(repl);
}

void console_add(char *cmd, char *help, esp_console_cmd_func_t func){
    esp_console_cmd_t config = {
        .command = cmd,
        .help = help,
        .hint = NULL,
        .func = func,
        .argtable = NULL,
    };
    esp_console_cmd_register(&config);
}
