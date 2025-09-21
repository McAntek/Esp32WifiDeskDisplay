#include <Arduino.h>
#include <Wire.h>

#include "secrets.h"
#include "screen.h"
#include "wifi_utils.h"
#include "clock_app.h"
#include "my_webserver.h"

#define HOSTNAME	"esp32clock"

void setup() {
	Serial.begin(115200);
    delay(1000);
	Serial.println("ESP32 started");
	screen_init();
	connect_to_network(SSID, PASS);
	set_hostname(HOSTNAME);
	clock_init(7200, 0, "pl.pool.ntp.org");
	screen_print("Current time:", TOP);
	webserver_init();
}

void loop() {
	screen_update();
	clock_update(BOTTOM);
	webserver_update();
}