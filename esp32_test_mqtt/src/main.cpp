#include <WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>

const char *ssid = "realme 9 Pro+";
const char *password = "h1234567";
const char *mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char *mqttTopic = "praktikum/response";
const char *mqttClientId = "Yasin";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void callback(char *topic, byte *payload, unsigned int length);


void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(callback);

  while (!mqttClient.connected())
  {
    Serial.println("Connecting to MQTT server...");

    if (mqttClient.connect(mqttClientId))
    {
      Serial.println("Connected to MQTT server");
    }
    else
    {
      Serial.print("Failed to connect to MQTT server, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

unsigned long lastMillis = 0;

void loop()
{
  if (millis() - lastMillis > 1000)
  {
    if (mqttClient.connected())
    {
      String message = "Hello, MQTT!";
      mqttClient.publish(mqttTopic, message.c_str());
      Serial.println("Message sent");
    }
    lastMillis = millis();
  }

  mqttClient.loop();
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message received on topic: ");
  Serial.println(topic);

  Serial.print("Payload: ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}