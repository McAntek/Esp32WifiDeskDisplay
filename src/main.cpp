#include <Arduino.h>
#include <Wire.h>

#include "screen.h"
#include "wifi_utils.h"
#include "clock_app.h"

#define SSID "ssid"
#define PASS "pass"

int pos = 0;

void setup() {
	screen_init();
	connect_to_network(SSID, PASS);
	clock_init(7200, 0, "pl.pool.ntp.org");
	screen_print("Current time:", TOP);
}

void loop() {
	screen_update();
	clock_update(BOTTOM);
}