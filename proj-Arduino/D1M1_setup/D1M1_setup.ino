/****************************************
 * Include Libraries
 ****************************************/

#include "Ubidots.h"

/****************************************
 * Define Instances and Constants
 ****************************************/

const char* UBIDOTS_TOKEN = "BBFF-rR5qq0wxEahPXj3tkcVyeWFCJtQKjo";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "Hackernet"; // Put here your Wi-Fi SSID
const char* WIFI_PASS = "Ubiquiti1337"; // Put here your Wi-Fi password

Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

/****************************************
 * Auxiliar Functions
 ****************************************/

// Put here your auxiliar functions

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);

  // ubidots.setDebug(true);  // Uncomment this line for printing debug messages
}

void loop() {
  
  float current = random(0, 9) * 10;
  float switch_toggle = 0; // Default is off
  ubidots.add("Current [A]", current);  // Change for your variable name
  ubidots.add("Switch status", switch_toggle);

  bool bufferSent = false;
  bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id

  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Values sent by the device");
  }

  delay(5000);
}
