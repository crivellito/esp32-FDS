#ifndef CONEXION_H
#define CONEXION_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include "conexion.h"
#include <stdio.h>

void conexion (char* ssid, char* password, const char* bot_token);
void conexion_control (char * ssid, char* password);

#endif



