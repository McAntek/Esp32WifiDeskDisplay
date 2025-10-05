#include <LittleFS.h>
#include <WebServer.h>
#include "screen.h"
#include "controller.h"

WebServer server(80);
uint8_t current_brightness = 255; // start full bright by default

void handle_root() {
    File f = LittleFS.open("/index.html", "r");
    if (!f) {
        server.send(500, "text/plain", "Failed to open index.html");
        return;
    }
    server.streamFile(f, "text/html");
    f.close();
}

void handle_set() {
    if (server.hasArg("row") && server.hasArg("mode")) {
        int row = server.arg("row").toInt();
        if (row != 0 && row != 1) row = 0;

        String mode = server.arg("mode");

        if (mode == "message" && server.hasArg("msg")) {
            String msg = server.arg("msg");
            bool scroll = server.hasArg("scroll");
            if (scroll) {
                int delayMs = 300;
                if (server.hasArg("delay")) {
                    delayMs = server.arg("delay").toInt();
                    delayMs = constrain(delayMs, 50, 2000);
                }
                screen_scroll(msg.c_str(), (row_t)row, delayMs, true);
            } else {
                screen_print(msg.c_str(), (row_t)row);
            }
            set_state(MESSAGE, (row_t)row);
        } 
        else if (mode == "clock") set_state(CLOCK, (row_t)row);
        else if (mode == "weather") {
            bool symbolMode = server.hasArg("symbol");
            set_state(WEATHER, (row_t)row, !symbolMode);
        }
    }

    server.sendHeader("Location", "/");
    server.send(303);
}

void handle_brightness() {
    if (server.hasArg("value")) {
        int brightness = server.arg("value").toInt();
        brightness = constrain(brightness, 0, 255);
        current_brightness = brightness;
        screen_set_brightness((uint8_t)brightness);
        Serial.printf("Brightness set to %d\n", brightness);
        server.send(200, "text/plain", "OK");
    } else {
        server.send(400, "text/plain", "Missing 'value'");
    }
}

void handle_get_brightness() {
    server.send(200, "text/plain", String(current_brightness));
}

void webserver_init() {
    if (!LittleFS.begin()) Serial.println("Failed to mount LittleFS");
    server.on("/", handle_root);
    server.on("/set", handle_set);
    server.on("/brightness", handle_brightness);
    server.on("/get_brightness", handle_get_brightness);
    server.begin();
}

void webserver_update() {
    server.handleClient();
}
