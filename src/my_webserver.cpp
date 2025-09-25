#include <LittleFS.h>
#include <WebServer.h>
#include "screen.h"
#include "controller.h"

WebServer server(80);

void handle_root() {
    File f = LittleFS.open("/index.html", "r");
    if(!f){
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
                    if (delayMs < 50) delayMs = 50;
                    if (delayMs > 2000) delayMs = 2000;
                }
                screen_scroll(msg.c_str(), (row_t)row, delayMs, true);
            } 
            else screen_print(msg.c_str(), (row_t)row);
            set_state(MESSAGE, (row_t)row);
        } 
        else if (mode == "clock") set_state(CLOCK, (row_t)row);
        else if (mode == "weather") set_state(WEATHER, (row_t)row);
    }

    server.sendHeader("Location", "/");
    server.send(303);
}

void webserver_init() {
    if(!LittleFS.begin()) Serial.println("Failed to mount LittleFS");
    server.on("/", handle_root);
    server.on("/set", handle_set);
    server.begin();
}

void webserver_update() {
    server.handleClient();
}