#include <Arduino.h>
#include <HardwareSerial.h>

HardwareSerial mySerial(1);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600, SERIAL_8N1, 16, 4);
}

void loop() {
  while (mySerial.available()) {
    char c = (char) mySerial.read();
    Serial.print(c);
  }
}