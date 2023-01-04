#include <Arduino.h>
#include <WiFiMulti.h>
#include <secrets.h>

#define LED_PIN 14

WiFiMulti wifiMulti;

void initWiFi()
{
  wifiMulti.addAP(SSID, PASS);

  while (wifiMulti.run() != WL_CONNECTED)
  {
    delay(100);
  }

  Serial.println("Connected");
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  initWiFi();
}

void loop()
{
  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED);
}