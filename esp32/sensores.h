#ifndef SENSORES_H
#define SENSORES_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "logica.h"

extern LiquidCrystal pantalla_lcd;
extern DHT sensor_dht;


void configurar_sensores();
float leer_temperatura();
bool leer_gas();
void mostrar_estado_lcd(float temperatura, bool hay_gas);

#endif