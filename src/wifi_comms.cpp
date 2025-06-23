// wifi_comms.cpp
#include "wifi_comms.h"
#include "config.h"
#include "globals.h"
#include <SD.h>

WiFiServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

void setupWiFi(const char* ssid, const char* password) {
  Serial.print("Connecting to WiFi...");
  if (WiFi.begin(ssid, password) != WL_CONNECTED) {
    Serial.println("FAILED");
    while (true);
  }
  Serial.println("Connected!");
  Serial.println(WiFi.localIP());

  server.begin();
  webSocket.begin();
  webSocket.onEvent([](uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    if (type == WStype_TEXT) {
      Serial.print("WebSocket message: ");
      Serial.println((char*)payload);
    }
  });
}

void handleClient() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Nowe połączenie HTTP");

    String request = client.readStringUntil('\r');
    client.read();  // Odczytaj '\n'

    Serial.print("Żądanie HTTP: ");
    Serial.println(request);

    if (request.indexOf("GET / ") >= 0 || request.indexOf("GET /index.html") >= 0) {
      File file = SD.open("/INDEX~1.HTM");
      if (file) {
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();
        while (file.available()) client.write(file.read());
        file.close();
      } else {
        client.println("HTTP/1.1 404 Not Found");
        client.println("Content-Type: text/plain");
        client.println("Connection: close");
        client.println();
        client.println("Plik index.html nie znaleziony.");
      }
    }

    else if (request.indexOf("GET /style.css") >= 0) {
      File file = SD.open("/style.css");
      if (file) {
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/css");
        client.println("Connection: close");
        client.println();
        while (file.available()) client.write(file.read());
        file.close();
      }
    }

    else if (request.indexOf("GET /script.js") >= 0) {
      File file = SD.open("/script.js");
      if (file) {
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: application/javascript");
        client.println("Connection: close");
        client.println();
        while (file.available()) client.write(file.read());
        file.close();
      }
    }

    else if (request.indexOf("GET /map.csv") >= 0) {
      File file = SD.open("/map.csv");
      if (file) {
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/csv");
        client.println("Connection: close");
        client.println();
        while (file.available()) client.write(file.read());
        file.close();
      }
    }

    else if (request.indexOf("GET /patrol.csv") >= 0) {
      File file = SD.open("/patrol.csv");
      if (file) {
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/csv");
        client.println("Connection: close");
        client.println();
        while (file.available()) client.write(file.read());
        file.close();
      }
    }

    else if (request.indexOf("GET /mapowanie") >= 0) {
      mapping = true;
      leftWheelCount = 0;
      rightWheelCount = 0;
      measurementNumber = 0;
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/plain");
      client.println("Connection: close");
      client.println();
      client.println("TRYB: Mapowanie");
    }

    else if (request.indexOf("GET /patrolowanie") >= 0) {
      mapping = false;
      leftWheelCount = 0;
      rightWheelCount = 0;
      measurementNumber = 0;
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/plain");
      client.println("Connection: close");
      client.println();
      client.println("TRYB: Patrolowanie");
    }

    else if (request.indexOf("GET /start") >= 0) {
      newMove = true;
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/plain");
      client.println("Connection: close");
      client.println();
      client.println("START OK");
    }

    else if (request.indexOf("GET /stop") >= 0) {
      newMove = false;
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/plain");
      client.println("Connection: close");
      client.println();
      client.println("STOP OK");
    }

    else {
      client.println("HTTP/1.1 404 Not Found");
      client.println("Content-Type: text/plain");
      client.println("Connection: close");
      client.println();
      client.println("404 - Nie znaleziono zasobu");
    }

    delay(1);
    client.stop();
    Serial.println("Połączenie zakończone");
  }

  webSocket.loop();
}