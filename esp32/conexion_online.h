#ifndef CONEXION_ONLINE_H
#define CONEXION_ONLINE_H
#define CHAT_ID "-1003100355289"                             //"7720847255"

#include <string.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <stdio.h>
#include <LiquidCrystal.h>
#include "sensores.h"


void conexion_wifi (char*, char*);
String last_mensaje (int);
void info ();
void new_mensajes (const unsigned long, unsigned long);

extern WiFiClientSecure secured_client;
extern UniversalTelegramBot bot;
extern LiquidCrystal lcd;

#endif



