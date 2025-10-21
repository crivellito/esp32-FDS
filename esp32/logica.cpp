#include "logica.h"

void buzzer (int pin_buzzer){
  for (int i=0 ; i<20 ; i++){
    delay(200);
    digitalWrite(pin_buzzer, HIGH);
  }
}

void logica (bool gas, bool temp, int temp_ext, int pin_buzzer){
  if(temp_ext > 40) {
    bot.sendMessage(CHAT_ID, "Se detectaron temperaturas elevadas");  
  } 
  else if (gas == true && temp == true) {
    buzzer(pin_buzzer);
    bot.sendMessage(CHAT_ID, "Se detectó posibilidad de incendio, la alarma se activó");  
  }
  else if (gas == true){
    bot.sendMessage(CHAT_ID, "Se detectaron gases");      
  }
}


