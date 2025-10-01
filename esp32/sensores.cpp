#include "sensores.h"
#define PIN_SENSOR_TEMP 4
#define DHTTYPE DHT11 
DHT dht(PIN_SENSOR_TEMP, DHTTYPE);


void sensor_temp() {
  float temp = dht.readTemperature();

  if (isnan(temp)) {
    Serial.println("Error al leer el sensor DHT11");
  } else {
    Serial.print("Temperatura: ");
    Serial.print(temp);
    Serial.println(" °C");
  }

  delay(2000); 
}

void sensor_gas() {
  int estado = digitalRead(PIN_SENSOR_GAS);
  if (estado == LOW) {
    Serial.println("Gas detectado");
  }
}
