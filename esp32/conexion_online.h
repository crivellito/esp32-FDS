#ifndef CONEXION_ONLINE_H
#define CONEXION_ONLINE_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <LiquidCrystal.h>
#include <Preferences.h>
#include "config.h"


extern UniversalTelegramBot bot;
extern WiFiClientSecure cliente_seguro;
extern LiquidCrystal pantalla_lcd;
extern unsigned long bot_ultimo_tiempo;
extern bool alarma_activa;
extern Preferences preferences;

extern char* nombre_red;
extern char* clave_red;
extern char escritura[TAM][MAX_LEN];


void configurar_telegram();
void conectar_wifi(const char* nombre_red, const char* clave_red);
void gestionar_wifi_serial();
void gestionar_comandos_telegram(float temperatura, bool hay_gas);
void enviar_estado_serial(float temperatura, bool hay_gas);

#endif