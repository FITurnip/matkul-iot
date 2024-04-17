#include <Arduino.h>
#include <stdlib.h>

uint8_t led_pin = 9;
int i;

char* intToString(int number);

void setup() {
  Serial.begin(115200);
  Serial.println("Start");
  pinMode(led_pin, OUTPUT);
}

void loop() {
  for(i = 0; i < 255; i++) {
    analogWrite(led_pin, i);
    // char *str = intToString(i);
    // Serial.println(str);
    // free(str);
    delay(100);
  }

  for(int i = 255; i >= 0; i--) {
    analogWrite(led_pin, i);
    // char *str = intToString(i);
    // Serial.println(str);
    // free(str);
    delay(100);
  }

  delay(1000);
}

char* intToString(int number) {
    int i = 0;
    int temp = number;
    int length = 0;

    // Counting the number of digits
    while (temp != 0) {
        temp /= 10;
        length++;
    }

    // Allocate memory for the string
    char *str = (char *)malloc((length + 1) * sizeof(char));
    if (str == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Converting each digit to character
    for (i = length - 1; i >= 0; i--) {
        str[i] = '0' + (number % 10);
        number /= 10;
    }

    // Null-terminating the string
    str[length] = '\0';

    return str;
}