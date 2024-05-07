#include <Arduino.h>
#include <Wire.h>

int counter = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  counter++;
  Serial.println(counter);
  Wire.beginTransmission(85);
  Wire.write(counter);
  Wire.endTransmission();
  delay(500);
}