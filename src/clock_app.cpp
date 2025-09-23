#include <Arduino.h>
#include <time.h>

#include "clock_app.h"

static unsigned long lastUpdate = 0;
static const unsigned long updateInterval = 1000;

static String time_format;

void clock_init(long gmt_offset, int daylight_offset, const char* ntp_server, const char* format) {
    configTime(gmt_offset, daylight_offset, ntp_server);
    time_format = format;
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

    char timeStr[CHAR_PER_LINE + 1];
    strftime(timeStr, sizeof(timeStr), time_format.c_str(), &timeinfo);

    screen_print(timeStr, row);
}