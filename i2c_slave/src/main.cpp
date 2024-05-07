#include <Arduino.h>
#include <Wire.h>

byte inputFromMaster = 0;

void I2C_RxHandler(int numBytes) {
  // Serial.println("jalan");
  while (Wire.available()) {
    // char c = (char)Wire.read();
    inputFromMaster = Wire.read();
    Serial.println(inputFromMaster);
  }
}

void setup() {
  Wire.begin(85);
  Serial.begin(9600);
  Wire.onReceive(I2C_RxHandler);
}

void loop() {
  // Serial.println("test");
  // while (Wire.available()) {
  //   inputFromMaster = Wire.read();
  //   Serial.println(inputFromMaster);
  // }
}