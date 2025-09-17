#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

#include <Arduino.h>

void scan_networks();
void display_networks();
String list_networks();
void connect_to_network(const char* ssid, const char* pass);

#endif