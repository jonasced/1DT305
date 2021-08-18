#include <dummy.h>

const float ADC_VMAX = 3.3; // Maximum voltage of ADC
const int ADC_bits = 10;    // Number of bits
const int ADC_sensMAX = 1 << ADC_bits;  // Maxmimum sensor reading
const float VCC = 5;        // 5V input voltage
const float QOV = VCC/2;    // The voltage read when no current is applied
const float offset = 0.15;     // Manual calibration

const float sens = 40; // 40mV/A sensitivity
const float FACTOR = sens/1000;

float voltage;  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.println(ADC_sensMAX);

}

void loop() {
  float sens = analogRead(A0);
  Serial.println("Sensor reading:");
  Serial.println(sens);
  
  float voltage_raw = ADC_VMAX * (sens/ADC_sensMAX); // Rescales sensor reading to voltage
  voltage = voltage_raw - QOV + offset; // Extracts voltage that measure current
  float current = voltage / FACTOR;
  
  Serial.print("V: ");
  Serial.print(voltage,4);
  Serial.print("V, I: ");
  Serial.print(current,2); Serial.println("A");
  

  
  delay(1000);
}
