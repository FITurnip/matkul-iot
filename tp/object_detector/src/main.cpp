#include <Arduino.h>
#include <Wire.h>
#include <Ultrasonic.h>

Ultrasonic ultrasonic(12, 13);
int distance;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  distance = ultrasonic.read();

  Serial.println(distance);

  // Split the integer into two bytes
  byte highByte = highByte(distance);
  byte lowByte = lowByte(distance);

  // Send the two bytes over I2C
  Wire.beginTransmission(85);
  Wire.write(highByte); // Send the high byte
  Wire.write(lowByte);  // Send the low byte
  Wire.endTransmission();

  delay(1000);
}
