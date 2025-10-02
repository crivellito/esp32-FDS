#ifndef SENSORES_H
#define SENSORES_H
#define PIN_SENSOR_GAS 32

#include <Adafruit_Sensor.h>
#include <DHT.h>

extern DHT dht;
extern int temp_ext;


#include <Arduino.h>

bool sensor_gas();

bool sensor_temp();


#endif
