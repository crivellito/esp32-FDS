#include "sensores.h"
DHT dht(PIN_SENSOR_TEMP, DHTTYPE);


float sensor_temp() {
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    Serial.println("Error al leer el sensor DHT11");
  } else {
    /*
      Serial.print("temp: ");   
      Serial.println(temp); 
    */
    return temp;
  }
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

void show_temp_display (int temp){
  lcd.setCursor(0,0);
  lcd.print("Temperatura: ");
  lcd.print(temp);
}
