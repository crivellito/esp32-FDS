#ifndef SENSORES_H
#define SENSORES_H
#define PIN_SENSOR_GAS 32
#define PIN_BOCINA //falta definir 

#include <Adafruit_Sensor.h>
#include <DHT.h>

extern DHT dht;



#include <Arduino.h>

bool sensor_gas();

bool sensor_temp();

bool bocina();

#endif
