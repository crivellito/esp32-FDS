#include "sensores.h"
#include "config.h"
#include "logica.h"

//Inicializa pines
void configurar_sensores() {
  pantalla_lcd.begin(16, 2);
  sensor_dht.begin();
  pinMode(PIN_GAS, INPUT);
  pinMode(PIN_TEMP, INPUT);
}

//Lee la temp del DHT11
float leer_temperatura() {
  float temperatura = sensor_dht.readTemperature();
  if (isnan(temperatura)) {
    Serial.println("Error al leer el sensor DHT11");
    return -99.9; // Retorna un valor de error
  } else {
    return temperatura;
  }
}

//Lee el sensor de gas devuelve el estado
bool leer_gas() {
  int estado = digitalRead(PIN_GAS);
  if (estado == LOW) {
    hay_gas = true;
  }
  return (estado == LOW); // Retorna true si hay gas (LOW)
}

//Muestra el estado en el LCD
void mostrar_estado_lcd(float temperatura, bool hay_gas) {
  pantalla_lcd.clear();
  pantalla_lcd.setCursor(0, 0);
  pantalla_lcd.print("Temp: ");
  pantalla_lcd.print(temperatura, 1); // Muestra con 1 decimal
  pantalla_lcd.print(" C");

  pantalla_lcd.setCursor(0, 1);
  pantalla_lcd.print("Gas: ");
  pantalla_lcd.print(hay_gas ? "DETECTADO" : "Normal   ");
}