#include "wifi_utils.h"
#include "screen.h"
#include <WiFi.h>

#define MAX_TRIES	5
#define PORT		10000

WiFiServer server(PORT);
Data data;

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

void display_networks(){
	screen_print("Scanning for", TOP);
	screen_print("wifi networks", BOTTOM);
	delay(1000);
	screen_write_symbol('.');
	delay(1000);
	screen_write_symbol('.');
	delay(1000);
	screen_write_symbol('.');
	String networks = list_networks();
	screen_print(" Wifi networks:", TOP);
	screen_scroll(networks.c_str(), BOTTOM, 400, true);
}

void connect_to_network(const char* ssid, const char* pass){
	screen_print("Connecting to:", TOP);
	screen_print(ssid, BOTTOM);
	int tries = 0;
	WiFi.begin(ssid, pass);
	while (WiFi.status() != WL_CONNECTED && tries < MAX_TRIES) {
		tries ++;
		delay(10000);
	}
	if (WiFi.status() == WL_CONNECTED){
		screen_clear();
		screen_print("Connected!", TOP);
		screen_print(WiFi.localIP().toString().c_str(), BOTTOM);
		delay(5000);
	}
	else{
		screen_clear();
		screen_print("Could not", TOP);
		screen_print("connect :c", BOTTOM);
		delay(5000);
		display_networks();
	}
}

void init_server(){
	server.begin();
}

boolean alreadyConnected = false;

void recive_data() {
    static WiFiClient client;

    if (!client || !client.connected()) {
        client = server.accept();
        if (client) {
            Serial.println("New client connected");
            client.clear();
        }
    }

    if (client && client.connected()) {
        int availableBytes = client.available();
        if (availableBytes > 0) {
            Serial.printf("Bytes available: %d (expecting %d)\n", availableBytes, sizeof(Data));
        }
        if (availableBytes >= sizeof(Data)) {
            client.readBytes((char*)&data, sizeof(data));
            Serial.printf("Received struct: seq=%d row=%d text='%s'\n",
                          data.seq, data.row, data.text);

			screen_print(data.text, (row_t)data.row);
        }
    }
}
