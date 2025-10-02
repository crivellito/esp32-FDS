#include "sensores.h"
#define PIN_SENSOR_TEMP 4
#define DHTTYPE DHT11

DHT dht(PIN_SENSOR_TEMP, DHTTYPE);


bool sensor_temp() {
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    Serial.println("Error al leer el sensor DHT11");
  } else {
    if (temp > 30){
      temp_ext = temp;
      return true;
    } else {
      temp_ext = temp;
      return false;
    }
  }
  
  delay(2000); 
}

bool sensor_gas() {
  int estado = digitalRead(PIN_SENSOR_GAS);
  if (estado == LOW) {
    return true;
  }
  else{
    return false;
  }
}
