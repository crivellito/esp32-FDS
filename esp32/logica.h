#ifndef LOGICA_H
#define LOGICA_H

#include <Arduino.h>
#include <UniversalTelegramBot.h>


extern bool alarma_activa;
extern UniversalTelegramBot bot;
extern int limite_temperatura;

void activar_zumbador(int, int pitidos);
void configurar_logica();
void ejecutar_logica(bool hay_gas, float temperatura);

#endif