#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "screen.h"
#include "wifi_utils.h"

int pos = 0;

void setup() {
	screen_init();
	screen_print("Scanning for", TOP);
	screen_print("wifi networks", BOTTOM);
	delay(1000);
	screen_write_symbol('.');
	delay(1000);
	screen_write_symbol('.');
	delay(1000);
	screen_write_symbol('.');
	String networks = listNetworks();
	screen_print("Wifi networks:", TOP);
	screen_scroll(networks.c_str(), BOTTOM, 400, true);
}

void loop() {
	screen_update();
}