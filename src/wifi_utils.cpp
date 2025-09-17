#include "wifi_utils.h"
#include <WiFi.h>


String listNetworks() {
  int numSsid = WiFi.scanNetworks();
  String result = "";

  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    result += String(thisNet) + ") " + WiFi.SSID(thisNet) + "  ";
  }

  return result;
}