#include <Arduino.h>
#include <OneButton.h>

uint8_t buttonPin = 5;
OneButton myButton(buttonPin);

uint8_t led_pin[3] = {3, 9, 11};
bool led_on[3] = {true, true, true};
bool is_led_switch[3] = {false, false, false};

void clickCallback();
void doubleClickCallback();
void longClickCallback();

void setup() {
  Serial.begin(9600);
  myButton.attachClick(clickCallback);
  myButton.attachDoubleClick(doubleClickCallback);
  myButton.attachLongPressStart(longClickCallback);

  for(uint8_t i = 0; i < 3; i++) {
    pinMode(led_pin[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  myButton.tick();
  for(uint8_t i = 0; i < 3; i++) {
    if(is_led_switch[i]) {
      if(led_on[i]) digitalWrite(led_pin[i], HIGH);
      else digitalWrite(led_pin[i], LOW);
      led_on[i] = !led_on[i];
      is_led_switch[i] = !is_led_switch[i];
    }
  }
}

void clickCallback() {
  Serial.println("click");
  is_led_switch[0] = true;
}

void doubleClickCallback() {
  Serial.println("double click");
  is_led_switch[1] = true;
}

void longClickCallback() {
  Serial.println("long click");
  is_led_switch[2] = true;
}