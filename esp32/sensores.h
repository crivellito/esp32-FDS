#ifndef SENSORES_H
#define SENSORES_H

#define PIN_SENSOR_GAS 32
#define PIN_SENSOR_TEMP 4
#define DHTTYPE DHT11

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Arduino.h>
#include <LiquidCrystal.h>

extern DHT dht;
extern int temp_ext;
extern LiquidCrystal lcd;

bool sensor_gas();
float sensor_temp();

#endif
