/****************************************
 * Include Libraries
 ****************************************/

#include "Ubidots.h"

/****************************************
 * Define Instances and Constants
 ****************************************/

// Ubidots and wireless connection
const char* UBIDOTS_TOKEN = "BBFF-rR5qq0wxEahPXj3tkcVyeWFCJtQKjo";  // Put here your Ubidots TOKEN
/****************************************
 * Mobile Hotspot
****************************************/
const char* WIFI_SSID = "Nakula"; // Put here your Wi-Fi SSID
const char* WIFI_PASS = "jones123"; // Put here your Wi-Fi password
/****************************************
 * Home wifi
const char* WIFI_SSID = "Hackernet"; // Put here your Wi-Fi SSID
const char* WIFI_PASS = "Ubiquiti1337"; // Put here your Wi-Fi password
 ****************************************/

//// Variables
float switch_status = 0;  // Sets switch to off by default

// Timer variables
const long interval = 5000;     // Defines the delay between each loop
unsigned long previousMillis = 0; // Used as a timer variable

// Microcontroller specs
const float ADC_VMAX = 3.3; // Maximum voltage of ADC
const int ADC_bits = 10;    // Number of bits in the ADC
const int ADC_sensMAX = 1 << ADC_bits;  // Maxmimum sensor reading is 2^ADC_bits
const float VCC = 5;        // 5V input voltage to current sensor

// Current sensor specs
const float QOV = VCC/2;    // The voltage read when no current is applied
const float sens = 40; // 40mV/A sensitivity
const float FACTOR = sens/1000;

// Current sensor calibration offsets
float offset;
float offsetOFF = 0.258;    // Manual calibration s.t. 0V when 0A
float offsetON = 0.166;     // Different values on/off since the relay effects the measurements

// Data send thresholds
float MIN_THRESHOLD = 0.20; // Set threshold at 20mA, about the tolerance of the sensor
float MAX_CURRENT = 10; // Set max to 10A

Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

/****************************************
 * Auxiliar Functions
 ****************************************/

// Put here your auxiliar functions

float readCurrent() {
  // Credit to: https://robojax.com/learn/arduino/?vid=robojax-allegro_ACS758 
  float sens = analogRead(A0);
  float voltage_raw = ADC_VMAX * (sens/ADC_sensMAX); // Rescales sensor reading to voltage
  if (switch_status == 1.0) offset = offsetON;
  if (switch_status == 0.0) offset = offsetOFF;
  float voltage = voltage_raw - QOV + offset; // Extracts voltage that measure current
  float current = voltage / FACTOR;
  
  //Serial.print("Sensor reading:");
  //Serial.println(sens);
  //Serial.print("V: ");
  //Serial.print(voltage,4);
  //Serial.print(" Switch status:"); Serial.print(switch_status);
  //Serial.print(" Offset:"); Serial.println(offset);
  //Serial.print("V, I: ");
  //Serial.print(current,2); Serial.println("A");
  
  return current;
}


float calcIRMS(int nSamples) {
  float iSum;
  float iRMS;
  // Loop over nSamples, sum and calculate RMS current
  for (unsigned int n = 0; n < nSamples; n++) {
    float current = readCurrent();
    float sqI = current * current;    
    iSum += sqI;
  }
  iRMS = sqrt(iSum / nSamples);

  Serial.print("IRMS:");
  Serial.println(iRMS);
  return iRMS;
}


void sendDataIRMS(float iRMS) {
  if (iRMS < MIN_THRESHOLD) {
    Serial.println("Current below threshold. No current or error. No data will be sent");
  }
  else {
    if (iRMS > MAX_CURRENT) Serial.println("Current above max value. Error. No data will be sent");
    // Send sensor data to ubidots
    else {
      ubidots.add("Current [A]", iRMS);
      bool bufferSent = false;
      bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id
      if (bufferSent) Serial.println("Values sent by the device");
      else Serial.println("Transmission failed");
    }
  }
}

void toggleSwitch() {
  float switch_toggle = ubidots.get("e8db84dc6cca", "switch-status");   // Recieve toggle status from ubidots
  if (switch_toggle != ERROR_VALUE) {   // Check for errors
    if (switch_toggle != switch_status) {   // Check for change in status
      Serial.println("SWITCHING");
      if (switch_toggle == 1) digitalWrite(D3,HIGH);
      if (switch_toggle == 0) digitalWrite(D3,LOW);
      switch_status = switch_toggle;
    }
    Serial.print("Power:");
    Serial.println(switch_status);
  }
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  // ubidots.setDebug(true);  // Uncomment this line for printing debug messages

  // Pin declaration
  pinMode(D3,OUTPUT);
  // A0 is used for analog read, set as default in the LOLIN(WEMOS) D1 R2 & mini board
  // D3 is used for control of the switch
  
}


void loop() {
  int nSamples = 1024; // Number of samples to calculate the RMS over
  float iRMS = calcIRMS(nSamples);
  float approxPower = iRMS * 230;
  Serial.print("Approximated power:");
  Serial.println(approxPower);
  
  // Timer: only send data and toggle switch every interval time
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis  >= interval) {
    previousMillis = currentMillis;
    // Send data & check if switch is toggled
    sendDataIRMS(iRMS);
    toggleSwitch();
  } 
}
