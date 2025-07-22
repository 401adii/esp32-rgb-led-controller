#ifndef COLORS_H
#define COLORS_H

#include<stdint.h>

typedef struct{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} color_t;

extern const color_t COLOR_BLACK;
extern const color_t COLOR_WHITE;
extern const color_t COLOR_RED;
extern const color_t COLOR_BLUE;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_PINK;
extern const color_t COLOR_YELLOW;
extern const color_t COLOR_CYAN;

extern const color_t COLORS[];
extern const uint8_t COLORS_LEN;

#endif