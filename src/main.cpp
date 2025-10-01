#include <Arduino.h>
#include <Wire.h>

#include "secrets.h"
#include "screen.h"
#include "wifi_utils.h"
#include "clock_app.h"
#include "my_webserver.h"
#include "weather_app.h"
#include "controller.h"

#define HOSTNAME	"esp32clock"

void setup() {
	Serial.begin(115200);
    delay(1000);
	Serial.println("ESP32 started");
	screen_init();
	connect_to_network(SSID, PASS);
	set_hostname(HOSTNAME);
	controller_init();
	set_state(MESSAGE, TOP);
	set_state(MESSAGE, BOTTOM);
	screen_print("ABCDEFGHIJKLMNOP", TOP);
	screen_print("QRSTUVWXYZ", BOTTOM);
}

void loop() {
	controller_update();
}
