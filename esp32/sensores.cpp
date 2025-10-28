#include "sensores.h"
#include "config.h"


//FUNCION - INICIALIZACION - DEFINE PINES DE LOS SENSORES
void configurar_sensores() {
  pantalla_lcd.begin(16, 2);
  sensor_dht.begin();
  pinMode(PIN_GAS, INPUT);
  pinMode(PIN_TEMP, INPUT);
}

//FUNCION - LECTURA - CONTROL Y RETORNO DE MEDICION DE TEMPERATURA
float leer_temperatura() {
  float temperatura = sensor_dht.readTemperature();
  if (isnan(temperatura)) {
    Serial.println("Error al leer el sensor DHT11");
    return -99.9; // VERIFICACION - VALOR DE ERROR
  } else {
    return temperatura;
  }
}

//FUNCION - LECTURA - CONTROLA Y RETORNA MEDICION DEL SENSOR DE GAS
bool leer_gas() {
  int estado = digitalRead(PIN_GAS);
  return (estado == LOW); // DEVUELVE true si hay gas (LOW)
}

//FUNCION - IMPRESION - MUESTRA LECTURAS EN LCD
void mostrar_estado_lcd(float temperatura, bool hay_gas) {
  pantalla_lcd.clear();
  pantalla_lcd.setCursor(0, 0);
  pantalla_lcd.print("Temp: ");
  pantalla_lcd.print(temperatura, 1); //1 DECIMAL
  pantalla_lcd.print(" C");

  pantalla_lcd.setCursor(0, 1);
  pantalla_lcd.print("Gas: ");
  pantalla_lcd.print(hay_gas ? "DETECTADO" : "Normal   ");
}