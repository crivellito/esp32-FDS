#ifndef CONEXION_ONLINE_H
#define CONEXION_ONLINE_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include "conexion_online.h"
#include <stdio.h>

void conexion_wifi (char*, char*);
String comunicacion_telegram (int);
void test ();

extern WiFiClientSecure secured_client;
extern UniversalTelegramBot bot;

#endif



