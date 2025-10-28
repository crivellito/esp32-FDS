#ifndef LOGICA_H
#define LOGICA_H

#include <Arduino.h>
#include <UniversalTelegramBot.h>

// VARIABLES GLOBALES 
extern UniversalTelegramBot bot;
extern int limite_temperatura;
extern bool alarma_activa;
extern char* Dpto; // <-- AÑADIDO


void activar_zumbador(int pin_zumbador, int pitidos);
void configurar_logica();
void ejecutar_logica(bool hay_gas, float temperatura);

#endif