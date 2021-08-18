#include <ESP8266Wifi.h>
#include keys.h

// Following this guide: https://siytek.com/wemos-d1-mini-arduino-wifi/#Connect_to_WiFi
// OTA updates: https://siytek.com/update-esp8266-devices-ota/
// Set wifi credentials from keys.h file
const char* WIFI_SSID = WIFI_SSID_bromma;
const char* WIFI_PASS = WIFI_PASSWD_bromma;

void setup() {
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
 
  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
 
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
 
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
 
}
 
void loop() {
  // put your main code here, to run repeatedly:
 
}
