#ifndef COLORS_H
#define COLORS_H

#include<stdint.h>

typedef struct{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} color_t;

extern const color_t COLOR_WHITE;
extern const color_t COLOR_RED;
extern const color_t COLOR_BLUE;
extern const color_t COLOR_GREEN;

#endif