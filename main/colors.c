#include"colors.h"

const color_t COLOR_WHITE = {
    .red = 255,
    .green = 255, 
    .blue = 255
};

const color_t COLOR_BLACK = {
    .red = 0,
    .green = 0,
    .blue = 0,
};

const color_t COLOR_RED = {
    .red = 255,
    .green = 0, 
    .blue = 0
}; 

const color_t COLOR_BLUE = {
    .red = 0, 
    .green = 0, 
    .blue = 255
};

const color_t COLOR_GREEN = {
    .red = 0,
    .green = 255,
    .blue = 0
};

const color_t COLOR_PINK ={
    .red = 255,
    .green = 0,
    .blue = 255,
};

const color_t COLOR_YELLOW = {
    .red = 255,
    .green = 255,
    .blue = 0,
};

const color_t COLOR_CYAN = {
    .red = 0,
    .green = 255,
    .blue = 255,
};


const color_t COLORS[] = {COLOR_RED,
                          COLOR_GREEN,
                          COLOR_BLUE,
                          COLOR_CYAN,
                          COLOR_PINK,
                          COLOR_YELLOW};

const uint8_t COLORS_LEN = sizeof(COLORS) / sizeof(color_t);
