#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "DARAPATI";
const char* password = "B3RK4T01";
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;

int receivedData = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void publishData() {
  if (client.connected()) {
    String ip = WiFi.localIP().toString();
    String message = ip + ", " + String(receivedData);
    client.publish("object_detector_channel", message.c_str());
  }
}

void receiveData(int byteCount) {
  if (byteCount >= 2) { // Make sure we have at least 2 bytes
    byte highByte = Wire.read();
    byte lowByte = Wire.read();
    receivedData = (highByte << 8) | lowByte;
    Serial.print(WiFi.localIP());
    Serial.print(", ");
    Serial.println(receivedData);
    publishData(); // Publish data when received
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {} // Wait for serial monitor to open
  Serial.println("Starting...");

  WiFi.begin(ssid, password);

  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");

  Wire.begin(85);
  Wire.onReceive(receiveData);

  client.setServer(mqtt_server, mqtt_port); // Set MQTT server
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
