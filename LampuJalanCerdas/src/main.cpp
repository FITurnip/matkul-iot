/**
 * Franklin Impianro Turnip
 * 2203211
 * C2
*/

#include <Arduino.h>
#include <BH1750.h>
#include <Wire.h>

BH1750 lightMeter(0x23);
uint8_t ledPin = 9;
bool ledOn = false, ledSwitch = false;
float highLightLux = 50;
float lowLightLux = 20;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(ledPin, OUTPUT);
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println(F("BH1750 Advanced begin"));
  } else {
    Serial.println(F("Error initialising BH1750"));
  }
}

void loop() {
  if (lightMeter.measurementReady()) {
    float lux = lightMeter.readLightLevel();
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");

    if(ledOn) {
      if(lux >= highLightLux) {
        ledSwitch = true;
        ledOn = false;
      }
    } else {
      if(lux <= lowLightLux) {
        ledSwitch = true;
        ledOn = true;
      }
    }

    if(ledSwitch) {
      if(ledOn) {
        digitalWrite(ledPin, HIGH);
      } else {
        digitalWrite(ledPin, LOW);
      }
      ledSwitch = false;
    }
  }
}
