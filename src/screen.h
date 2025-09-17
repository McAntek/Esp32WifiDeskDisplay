#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>

typedef enum {
    TOP,
    BOTTOM
} row_t;

void screen_init();
void screen_write_symbol(char chr);
void screen_write_symbol(int byte);
void screen_print(const char* msg, row_t row);
void screen_clear_row(row_t row);
void screen_clear();

#endif