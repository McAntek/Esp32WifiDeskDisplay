#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>

#include "screen.h"

int pos = 0;

void setup() {
	screen_init();
	screen_print("Hello World :3", TOP);
	screen_print("(^ w ^) ", BOTTOM);
	screen_write_symbol(0);
	screen_write_symbol(' ');
	screen_write_symbol(0);
	screen_write_symbol(' ');
	screen_write_symbol(0);
	delay(3000);
	const char* lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc sit amet tortor vestibulum, tempus dolor id, venenatis urna. Phasellus nulla justo, cursus nec tellus ac, dignissim efficitur felis.";
	screen_scroll(lorem, BOTTOM, 200, true);
}

void loop() {
	screen_update();
}