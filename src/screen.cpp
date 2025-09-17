#include "screen.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define CHAR_PER_LINE   16
#define SDA_PIN         17
#define SCL_PIN         18

static bool scrolling[2] = {false, false};

byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

void screen_set_cursor(row_t row){
    if (row == TOP) lcd.setCursor(0,0);
    else lcd.setCursor(0, 1);
}

void screen_init(){
    Wire.begin(SDA_PIN, SCL_PIN);
    lcd.init();
    lcd.backlight();
    lcd.createChar(0, heart);
}

void screen_write_symbol(char chr){
    lcd.write(chr);
}

void screen_write_symbol(int chr){
    lcd.write(byte(chr));
}

void screen_print(const char* msg, row_t row){
    scrolling[row] = false;
    screen_clear_row(row);
    screen_set_cursor(row);
    lcd.print(msg);
}

void screen_clear_row(row_t row){
    screen_set_cursor(row);
    for (int i = 0; i < CHAR_PER_LINE; ++i){
        lcd.write(' ');
    }
}

void screen_clear(){
    lcd.clear();
}

void screen_scroll(const char* msg, row_t row, int delay_ms){
    scrolling[row] = false;
    delay(100);
    scrolling[row] = true;
    int pos = 0;
    int len = strlen(msg);

    while(scrolling[row]){
        screen_clear_row(row);
        screen_set_cursor(row);
        for (int i = 0; i < CHAR_PER_LINE; ++i){
            char c = msg[(pos + i) % len];
            lcd.print(c);
        }
        if (pos < len) pos++;
        else pos = 0;
        delay(delay_ms);
    }
}

int screen_scroll_tick(const char* msg, row_t row, int pos){
    int len = strlen(msg);
    screen_clear_row(row);
    screen_set_cursor(row);
    for (int i = 0; i < CHAR_PER_LINE; ++i){
        char c = msg[(pos + i) % len];
        lcd.print(c);
    }
    if (pos < len) pos++;
    else pos = 0;
    return pos;
}