#ifndef CONEXION_ONLINE_H
#define CONEXION_ONLINE_H
#define PIN_SENSOR_GAS 32
#include <string.h>
#define CHAT_ID "1965602246"
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <stdio.h>

void conexion_wifi (char*, char*);
String comunicacion_telegram (int);
void test ();
void sensor_gas();

extern WiFiClientSecure secured_client;
extern UniversalTelegramBot bot;

#endif



