/****************************************
 * Include Libraries
 ****************************************/

#include "Ubidots.h"

/****************************************
 * Define Constants
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
  // ubidots.setDebug(true); //Uncomment this line for printing debug messages
}

void loop() {
  /* Obtain last value from a variable as float using HTTP */
  float switch_toggle = ubidots.get("e8db84dc6cca", "switch-status");

  // Evaluates the results obtained
  if (switch_toggle != ERROR_VALUE) {
    Serial.print("Power:");
    Serial.println(switch_toggle);
  }
  delay(5000);
}
