#include <LittleFS.h>
#include <WebServer.h>
#include "screen.h"

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
    if (server.hasArg("msg") && server.hasArg("row")) {
        String msg = server.arg("msg");
        int row = server.arg("row").toInt();
        if (row != 0 && row != 1) row = 0;

        bool scroll = server.hasArg("scroll");
        if (scroll) {
            int delayMs = 300; // default
            if (server.hasArg("delay")) {
                delayMs = server.arg("delay").toInt();
                if (delayMs < 50) delayMs = 50;       // enforce min
                if (delayMs > 2000) delayMs = 2000;   // enforce max
            }
            screen_scroll(msg.c_str(), (row_t)row, delayMs, true);
        } else {
            screen_print(msg.c_str(), (row_t)row);
        }
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