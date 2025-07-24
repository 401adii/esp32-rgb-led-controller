#ifndef CMD_CONSOLE_H
#define CMD_CONSOLE_H

#include"esp_console.h"

#define PROMPT_STR "rgb-controller>"

static esp_console_repl_t *repl;

void console_init(void);
void console_start(void);
void console_add(char *cmd, char *help, esp_console_cmd_func_t func);

#endif