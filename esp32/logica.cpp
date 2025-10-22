#include "logica.h"

void buzzer (int pin_buzzer){
  for (int i=0 ; i<20 ; i++){
    digitalWrite(pin_buzzer, LOW);
    delay(200);
    digitalWrite(pin_buzzer, HIGH);
  }
}

void logica(bool gas, float temp, int pin_buzzer) {
  if (temp > 40) {
    bot.sendMessage(CHAT_ID, "Se detectaron temperaturas elevadas");
  }

  if (temp > 40 && gas == true) {
    buzzer(pin_buzzer);
    bot.sendMessage(CHAT_ID, "Se detectó posibilida d de incendio, la alarma se activó");
  }

  if (gas == true) {
    bot.sendMessage(CHAT_ID, "Se detectaron gases");
  }
}



