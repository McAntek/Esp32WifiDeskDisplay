#include "screen.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define CHAR_PER_LINE   16
#define SDA_PIN         17
#define SCL_PIN         18

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
    screen_clear_row(row);
    if (row == TOP) lcd.setCursor(0,0);
    else lcd.setCursor(0, 1);
    lcd.print(msg);
}

void screen_clear_row(row_t row){
    if (row == TOP) lcd.setCursor(0,0);
    else lcd.setCursor(0, 1);
    for (int i = 0; i < CHAR_PER_LINE; ++i){
        lcd.write(' ');
    }
}

void screen_clear(){
    lcd.clear();
}