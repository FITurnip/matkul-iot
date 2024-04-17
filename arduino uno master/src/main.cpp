#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  Serial.println("Running");
  mySerial.println("Halo");
  delay(1000);
}