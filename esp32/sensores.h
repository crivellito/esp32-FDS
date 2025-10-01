#ifndef SENSORES_H
#define SENSORES_H
#define PIN_SENSOR_GAS 32

#include <Adafruit_Sensor.h>
#include <DHT.h>

extern DHT dht;



#include <Arduino.h>

void sensor_gas();

void sensor_temp();


#endif
