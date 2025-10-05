#include "screen.h"
#include <LiquidCrystal_I2C.h>
#include <driver/ledc.h>
#include <Arduino.h> 
#include <LittleFS.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SDA_PIN         0
#define SCL_PIN         1
#define LCD_BL_PIN      2

struct ScrollState {
    bool active = false;
    bool loop = false;
    String text;
    int pos = 0;
    unsigned long lastUpdate = 0;
    unsigned int delay_ms = 300;
};

static ScrollState scrollStates[2];

void screen_set_cursor(row_t row){
    if (row == TOP) lcd.setCursor(0,0);
    else lcd.setCursor(0, 1);
}

void screen_stop_scroll(row_t row){
    scrollStates[row].active = false;
}

void screen_init(){
    Wire.begin(SDA_PIN, SCL_PIN);
    lcd.init();
    lcd.backlight();

    pinMode(LCD_BL_PIN, OUTPUT);
    screen_set_brightness(255);
}

void screen_write_symbol(char chr){
    lcd.write(chr);
}

void screen_write_symbol(int chr){
    lcd.write(byte(chr));
}

void screen_print(const char* msg, row_t row){
    screen_stop_scroll(row);
    screen_clear_row(row);
    screen_set_cursor(row);
    lcd.print(msg);
}

void screen_write(const char* msg){
    lcd.print(msg);
}

void screen_clear_row(row_t row){
    screen_set_cursor(row);
    for (int i = 0; i < CHAR_PER_LINE; ++i){
        lcd.write(' ');
    }
}

bool screen_load_icon(const char* path, int slot){
    File f = LittleFS.open(path, "r");
    if (!f) {
        Serial.printf("Failed to open file: %s\n", path);
        return false;
    }
    if (f.size() != 8) {
        Serial.printf("Wrong size: %s\n", path);
        return false;
    }

    byte glyph[8];
    for (int row = 0; row < 8; row++) glyph[row] = f.read();

    lcd.createChar(slot, glyph);
    f.close();
    return true;
}

void screen_draw_icon(row_t row, int col, int slot){
    lcd.setCursor(col, row);
    lcd.write(slot);
}

void screen_clear(){
    screen_stop_scroll(TOP);
    screen_stop_scroll(BOTTOM);
    lcd.clear();
}

void screen_scroll(const char* msg, row_t row, unsigned int delay_ms, bool loop){
    screen_stop_scroll(row);

    scrollStates[row].active = true;
    scrollStates[row].loop = loop;
    scrollStates[row].text = "                " + String(msg);
    scrollStates[row].pos = 0;
    scrollStates[row].lastUpdate = 0;
    scrollStates[row].delay_ms = delay_ms;
}

void screen_update(){
    unsigned long now = millis();
    for (int r = 0; r < 2; r++) {
        auto &state = scrollStates[r];
        if (!state.active) continue;

        if (now - state.lastUpdate >= state.delay_ms) {
            state.lastUpdate = now;
            int len = state.text.length();
            row_t row = (row_t)r;
            screen_clear_row(row);
            screen_set_cursor(row);
            for (int i = 0; i < CHAR_PER_LINE; ++i){
                char c = state.text[(state.pos + i) % len];
                lcd.print(c);
            }
            if(state.pos < len) state.pos++;
            else {
                if (state.loop) state.pos = 0;
                else state.active = false;
            }
        }
    }
}

void screen_set_brightness(uint8_t brightness){
    if(brightness == 0) {
        digitalWrite(LCD_BL_PIN, HIGH);
    } else if(brightness >= 255) {
        digitalWrite(LCD_BL_PIN, LOW);
    } else {
        analogWrite(LCD_BL_PIN, 255 - brightness);
    }
}