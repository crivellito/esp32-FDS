#include "sensores.h"
#define PIN_SENSOR_TEMP 4
#define DHTTYPE DHT11 
DHT dht(PIN_SENSOR_TEMP, DHTTYPE);


bool sensor_temp() {
  float temp = dht.readTemperature();

  if (isnan(temp)) {
    Serial.println("Error al leer el sensor DHT11");
  } else {
    Serial.print("Temperatura: ");
    Serial.print(temp);
    Serial.println(" °C");
  }
  
  if (temp > 50)
  { return true; }
  else
  { return false; }

  delay(2000); 
}

bool sensor_gas() {
  int estado = digitalRead(PIN_SENSOR_GAS);
  if (estado == LOW) {
    Serial.println("Gas detectado");
  }

  if (estado == HIGH) {
    return false;}
  else {
    return true;
  }

bool bocina() { //falta definir pin bovina en "sensores.h"

  int bocina digitalRead(PIN_BOCINA);

  bool temp = sensor_temp();
  bool gas = sensor_gas();

  if (temp || gas) {
    digitalWrite(PIN_BOCINA, HIGH); 
    return true;
  } else {
    digitalWrite(PIN_BOCINA, LOW); 
    return false;

}



}
