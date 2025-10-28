#include "logica.h"
#include "config.h"


static String ultimo_mensaje_alerta = "";
static const String msg_temp_alta = "Se detectaron temperaturas elevadas";
static const String msg_incendio = "Se detecto posibilidad de incendio, la alarma se activo";
static const String msg_gas = "Se detectaron gases";


static void activar_zumbador(int pin_zumbador) {
  for (int i = 0; i < 5; i++) {
    digitalWrite(pin_zumbador, HIGH);
    delay(800);
    digitalWrite(pin_zumbador, LOW);
  }
}

void configurar_logica() {
  pinMode(PIN_ZUMBADOR, OUTPUT);
  digitalWrite(PIN_ZUMBADOR, LOW); 
}




void ejecutar_logica(bool hay_gas, float temperatura) {

  //Fuego (Temp alta y Gas)
  if (temperatura > limite_temperatura && hay_gas == true) {
    if (ultimo_mensaje_alerta != msg_incendio) {
      activar_zumbador(PIN_ZUMBADOR);
      bot.sendMessage(CHAT_ID, msg_incendio);
      ultimo_mensaje_alerta = msg_incendio;
    }
  }
  //Solo Temp Alta
  else if (temperatura > limite_temperatura) {
    if (ultimo_mensaje_alerta != msg_temp_alta) {
      bot.sendMessage(CHAT_ID, msg_temp_alta);
      ultimo_mensaje_alerta = msg_temp_alta;
    }
  }
  //Solo Gas
  else if (hay_gas == true) {
    if (ultimo_mensaje_alerta != msg_gas) {
      bot.sendMessage(CHAT_ID, msg_gas);
      ultimo_mensaje_alerta = msg_gas;
    }
  }
  //Normal
  else {
    ultimo_mensaje_alerta = ""; // Limpia el ultimo mensaje
  }
}