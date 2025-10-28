#include "logica.h"
static String last_msg = ""; 
String temp_alta_msg = "Se detectaron temperaturas elevadas en el dpto: " + String(Dpto);
String posib_incendio_msg = "En el Dpto:" + String(Dpto) "se detectó posibilidad de incendio, la alarma se activó";
String gas_msg = "Se detectaron gases en el Dpto: " + String(Dpto);


static String ultimo_mensaje_alerta = "";
static const String msg_temp_alta = "Se detectaron temperaturas elevadas";
static const String msg_incendio = "Se detecto posibilidad de incendio, la alarma se activo";
static const String msg_gas = "Se detectaron gases";


void activar_zumbador(int pin_zumbador, int pitidos) {
  if (alarma_activa){
    for (int i = 0; i < pitidos; i++) {
      digitalWrite(pin_zumbador, HIGH);
      delay(300);
      digitalWrite(pin_zumbador, LOW);
      delay(300);
    }
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
      activar_zumbador(PIN_ZUMBADOR, 20);
      bot.sendMessage(CHAT_ID, msg_incendio);
      ultimo_mensaje_alerta = msg_incendio;
    }
  }
  //Solo Temp Alta
  else if (temperatura > limite_temperatura) {
    if (ultimo_mensaje_alerta != msg_temp_alta) {
      bot.sendMessage(CHAT_ID, msg_temp_alta );
      activar_zumbador(PIN_ZUMBADOR, 1);
      ultimo_mensaje_alerta = msg_temp_alta;
    }
  }
  //Solo Gas
  else if (hay_gas == true) {
    if (ultimo_mensaje_alerta != msg_gas) {
      bot.sendMessage(CHAT_ID, msg_gas);
      activar_zumbador(PIN_ZUMBADOR, 1);
      ultimo_mensaje_alerta = msg_gas;
    }
  }
  //Normal
  else {
    ultimo_mensaje_alerta = ""; // Limpia el ultimo mensaje
  }
}