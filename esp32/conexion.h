#ifndef CONEXION_H
#define CONEXION_H
#define CHAT_ID "7720847255"

#include <string.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <stdio.h>

extern WiFiClientSecure secured_client;
extern UniversalTelegramBot bot;

class conexion {
    public:
      conexion();
      void conexion_wifi (char*, char*);
      String comunicacion_telegram (int);
      void test ();
    private: 
      int num_nuevos_sms;
      char* ssid, password;
}
#endif



