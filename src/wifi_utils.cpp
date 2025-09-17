#include "wifi_utils.h"
#include <WiFi.h>


void scan_networks(){
	WiFi.scanNetworks();
}

String list_networks() {
	int numSsid = WiFi.scanNetworks();
	String result = "";

	for (int thisNet = 0; thisNet < numSsid; thisNet++) {
	result += String(thisNet) + ") " + WiFi.SSID(thisNet) + "  ";
	}

	return result;
}