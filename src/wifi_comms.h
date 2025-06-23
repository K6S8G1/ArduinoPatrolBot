// wifi_comms.h

#ifndef WIFI_COMMS_H
#define WIFI_COMMS_H

#include <WiFiS3.h>
#include <WebSocketsServer.h>
#include <WiFiServer.h>

// Inicjalizacja funkcji
void setupWiFi(const char* ssid, const char* password);
void handleClient();

#endif
