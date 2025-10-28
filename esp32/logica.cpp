#include "logica.h"
static String last_msg = ""; 
String temp_alta_msg = "Se detectaron temperaturas elevadas en el dpto: " + String(Dpto);
String posib_incendio_msg = "En el Dpto:" + String(Dpto) "se detectó posibilidad de incendio, la alarma se activó";
String gas_msg = "Se detectaron gases en el Dpto: " + String(Dpto);


void buzzer (int pin_buzzer) {
  for (int i=0 ; i<20 ; i++){
    digitalWrite(pin_buzzer, HIGH);
    delay(800);
    digitalWrite(pin_buzzer, LOW);
  }
}

void logica (bool gas, float temp, int pin_buzzer) {
  
  if (temp > temp_limit && gas == true && last_msg != posib_incendio_msg) {
    buzzer(pin_buzzer);
    bot.sendMessage(CHAT_ID, posib_incendio_msg);
    last_msg = posib_incendio_msg;
  }
  
  if (temp > temp_limit && last_msg != temp_alta_msg) {
    bot.sendMessage(CHAT_ID, temp_alta_msg);
    last_msg = temp_alta_msg;
  } 

  if (gas == true && last_msg != gas_msg) {
    bot.sendMessage(CHAT_ID, gas_msg);
    last_msg = gas_msg;
  }
}



