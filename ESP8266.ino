#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>

// Connecting to the internet
char * ssid     = "Casa 03 2.4G";
char * password = "8532785419";
char * address  = "vize-iot.herokuapp.com";
char * path     = "/";
int    port     = 80;

// Setting up the websocket client
WebSocketsClient webSocket;

void setup() {
  Serial.begin(115200);
  Serial.println("");
  WiFi.begin(ssid, password);

  Serial.print("[WiFi] Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("[WiFi] Conectado.");

  // Initializing the websocket communication
  Serial.println("[WebSocket] Conectando...");
  webSocket.begin(address, port, path);
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000);
}

void loop() {
  webSocket.loop();
} 

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.println("[WebSocket] Desconectado.");
      break;
    case WStype_CONNECTED:
      Serial.println("[WebSocket] Conectado.");
      break;
    case WStype_TEXT:
      Serial.printf("[WebSocket] Dado recebido: %s\n", payload);
      DynamicJsonBuffer jBuffer;
      JsonObject &root = jBuffer.parseObject(payload);
      break;
  }
}
