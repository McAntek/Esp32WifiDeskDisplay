#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

#include <Arduino.h>

struct __attribute__((packed)) Data {
  int16_t seq;
  int8_t row;
  char text[16];
  
};

extern Data data;

void scan_networks();
void display_networks();
void set_hostname(const char* hostname);
String list_networks();
void connect_to_network(const char* ssid, const char* pass);
void init_server();
void recive_data();

#endif