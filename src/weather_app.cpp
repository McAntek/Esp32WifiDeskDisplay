#include "weather_app.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include "secrets.h"



String weather_url = String("https://api.open-meteo.com/v1/forecast?latitude=") +
    String(LATITUDE, 8) + "&longitude=" + String(LONGITUDE, 8) +
    "&current=temperature_2m,is_day,weather_code&timezone=auto";

unsigned long last_update = 0;
const unsigned long update_interval = 15 * 60000; // ms

String code_to_description(int code) {
    if (code == 0) return "Clear";
    if (code == 1 || code == 2 || code == 3) return "Cloudy";
    if (code == 45 || code == 48) return "Fog";
    if (code == 51 || code == 53 || code == 55) return "Drizzle";
    if (code == 56 || code == 57) return "Frz Drizzle";
    if (code == 61 || code == 63 || code == 65) return "Rain";
    if (code == 66 || code == 67) return "Frz Rain";
    if (code == 71 || code == 73 || code == 75) return "Snow";
    if (code == 77) return "Snow Grains";
    if (code == 80 || code == 81 || code == 82) return "Showers";
    if (code == 85 || code == 86) return "Snow Shwr";
    if (code == 95) return "Tstorm";
    if (code == 96 || code == 99) return "Hailstorm";
    return "Unknown";
}

void weather_init() {
    last_update = millis() - update_interval;
}

void weather_update(row_t row) {
    unsigned long now = millis();
    if (now - last_update < update_interval) return;
    last_update = now;

    if (WiFi.status() != WL_CONNECTED) {
        screen_print("WiFi error", row);
        return;
    }

    HTTPClient http;
    http.begin(weather_url);
    int httpCode = http.GET();

    if (httpCode == 200) {
        String payload = http.getString();
        
        JsonDocument doc;
        DeserializationError err = deserializeJson(doc, payload);
        if (err) {
            screen_print("JSON parse error", row);
            return;
        }

        float temp = doc["current"]["temperature_2m"].as<float>();
        int code = doc["current"]["weather_code"].as<int>();
        String desc = code_to_description(code);

        char tempStr[10];
        snprintf(tempStr, sizeof(tempStr), "%.1f%cC", temp, (char)223);

        int totalWidth = 16;
        int tempLen = strlen(tempStr);
        int descLen = desc.length();

        char line[17];

        if (tempLen + 1 + descLen <= totalWidth) {
            int spaces = totalWidth - (tempLen + descLen);
            snprintf(line, sizeof(line), "%s%*s%s", tempStr, spaces, "", desc.c_str());
        } 
        else snprintf(line, sizeof(line), "%s %s", tempStr, desc.c_str());

        screen_clear_row(row);
        screen_print(line, row);

        Serial.printf("Weather row: [%s]\n", line);
    } 
    else {
        char error[17];
        snprintf(error, sizeof(error), "HTTP err %d", httpCode);
        screen_print(error, row);
    }

    http.end();
}