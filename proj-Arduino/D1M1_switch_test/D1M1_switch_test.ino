#include <dummy.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(D3,OUTPUT);
  Serial.println("Switching in NO mode");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(D3,HIGH);
  Serial.println("Switch off");
  delay(2000);
  digitalWrite(D3,LOW);
  Serial.println("Switch on");
  delay(2000);

}
