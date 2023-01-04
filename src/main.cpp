#include <Arduino.h>
#include <WiFiMulti.h>
#include <secrets.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>

// ----------------------------------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------------------------------
#define LED_PIN 14
#define WS_HOST ""
#define WS_PORT 443
#define WS_URL ""

// ----------------------------------------------------------------------------------------------------
// globals
// ----------------------------------------------------------------------------------------------------
WiFiMulti wifiMulti;
WebSocketsClient wsClient;

// ----------------------------------------------------------------------------------------------------
// function definitions
// ----------------------------------------------------------------------------------------------------
void initWiFi()
{
  wifiMulti.addAP(SSID, PASS);

  while (wifiMulti.run() != WL_CONNECTED)
  {
    delay(100);
  }

  Serial.println("Connected");
}

void onWSEvent(WStype_t type, uint8_t *payload, size_t length)
{
  switch (type)
  {
  case WStype_CONNECTED:
    Serial.println("WS connected");
    break;
  case WStype_DISCONNECTED:
    Serial.println("WS disconnected");
    break;
  case WStype_TEXT:
    Serial.printf("WS Message: %s\n", payload);
    break;
  }
}

void initClient()
{
  wsClient.beginSSL(WS_HOST, WS_PORT, WS_URL, "", "wss");
  wsClient.onEvent(onWSEvent);
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  initWiFi();
  initClient();
}

void loop()
{
  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED); // turn on builtin led once conncted to wifi
  wsClient.loop();                                          // keep client connection alive
}