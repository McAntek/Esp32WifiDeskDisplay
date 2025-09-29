#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#define CHAR_PER_LINE   16

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
void screen_write(const char* msg);
void screen_stop_scroll(row_t row);
void screen_scroll(const char* msg, row_t row, unsigned int delay_ms, bool loop);
void screen_set_brightness(uint8_t brightness);
void screen_update();
bool screen_load_icon(const char* path, int slot);
void screen_draw_icon(row_t row, int col, int slot);

#endif