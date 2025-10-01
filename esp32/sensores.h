#ifndef SENSORES_H
#define SENSORES_H
#define PIN_SENSOR_GAS 32
#define PIN_SENSOR_TEMP 4
#define DHTTYPE DHT11 
#include <DHT.H>


#include <Arduino.h>

void sensor_gas();

void sensor_temp();


#endif
