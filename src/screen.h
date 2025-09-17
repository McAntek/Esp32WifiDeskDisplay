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
void screen_scroll(const char* msg, row_t row, int delay_ms);
int screen_scroll_tick(const char* msg, row_t row, int pos);

#endif