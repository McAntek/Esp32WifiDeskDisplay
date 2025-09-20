#include <Arduino.h>
#include <Wire.h>

#include "screen.h"
#include "wifi_utils.h"
#include "clock_app.h"

#define SSID "ssid"
#define PASS "pass"

int pos = 0;

void setup() {
	Serial.begin(115200);
    delay(1000);
	Serial.println("ESP32 started");
	screen_init();
	connect_to_network(SSID, PASS);
	clock_init(7200, 0, "pl.pool.ntp.org");
	screen_print("Current time:", TOP);
	init_server();
}

void loop() {
	screen_update();
	clock_update(BOTTOM);
	recive_data();
}