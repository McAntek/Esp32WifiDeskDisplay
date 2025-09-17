#include <Arduino.h>
#include <time.h>

#include "clock_app.h"

static unsigned long lastUpdate = 0;
static const unsigned long updateInterval = 1000;

void clock_init(long gmt_offset, int daylight_offset, const char* ntp_server) {
    configTime(gmt_offset, daylight_offset, ntp_server);
}

void clock_update(row_t row) {
    unsigned long now = millis();
    if (now - lastUpdate < updateInterval) return;
    lastUpdate = now;

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        screen_print("Time sync error", row);
        return;
    }

    char timeStr[16];
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);

    screen_print(timeStr, row);
}