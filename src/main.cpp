#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "screen.h"
#include "wifi_utils.h"

#define SSID "ssid"
#define PASS "pass"

int pos = 0;

void setup() {
	screen_init();
	connect_to_network(SSID, PASS);
}

void loop() {
	screen_update() ;
}