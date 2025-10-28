#ifndef LOGICA_H
#define LOGICA_H

#include <Arduino.h>
#include <UniversalTelegramBot.h>

extern int pitidos;
extern UniversalTelegramBot bot;
extern int limite_temperatura;

static void activar_zumbador(int, int pitidos);
void configurar_logica();
void ejecutar_logica(bool hay_gas, float temperatura);

#endif