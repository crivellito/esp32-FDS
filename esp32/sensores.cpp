#include "sensores.h"


void sensor_gas() {
  int estado = digitalRead(PIN_SENSOR_GAS);
  if (estado == LOW) {
    Serial.println("Gas detectado");
  }
}
