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
        screen_print(msg.c_str(), (row_t)row);
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