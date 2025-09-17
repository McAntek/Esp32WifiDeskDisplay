#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "screen.h"

void setup() {
	screen_init();
	screen_print("Hello World :3", TOP);
	screen_print("(^ w ^) ", BOTTOM);
	screen_write_symbol(0);
	screen_write_symbol(' ');
	screen_write_symbol(0);
	screen_write_symbol(' ');
	screen_write_symbol(0);
}

void loop() {

}