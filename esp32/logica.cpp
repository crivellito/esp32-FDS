#include "logica.h"
#include "config.h"

// MENSAJES PREDEFINIDOS 
static const String msg_temp_alta = "Se detectaron temperaturas elevadas";
static const String msg_incendio = "Se detecto posibilidad de incendio, la alarma se activo";
static const String msg_gas = "Se detectaron gases";

// MENSAJE PARA EVITAR SPAM
static String ultimo_mensaje_alerta = "";


// FUNCION - CONTROL - MANEJA EL PITIDO DEL ZUMBADOR
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

// FUNCION - INICIALIACION - DEFINE PINES DEL ZUMBADOR
void configurar_logica() {
  pinMode(PIN_ZUMBADOR, OUTPUT);
  digitalWrite(PIN_ZUMBADOR, LOW); 
}


void ejecutar_logica(bool hay_gas, float temperatura) {

  // CONCATENACION STRING DEPTO
  String Dpto_str = "";
  if (Dpto != nullptr && strlen(Dpto) > 0) {
    Dpto_str = " en Dpto: " + String(Dpto);
  }

//CONDICIONES DE ALERTA SEGUN GRAVEDAD

  // FUEGO (Temp alta y Gas)
  if (temperatura > limite_temperatura && hay_gas == true) {
    if (ultimo_mensaje_alerta != msg_incendio) {
      activar_zumbador(PIN_ZUMBADOR, 20);
      bot.sendMessage(CHAT_ID, msg_incendio + Dpto_str);
      ultimo_mensaje_alerta = msg_incendio;
    }
  }
  // TEMPERATURA ALTA
  else if (temperatura > limite_temperatura) {
    if (ultimo_mensaje_alerta != msg_temp_alta) {
      bot.sendMessage(CHAT_ID, msg_temp_alta + Dpto_str);
      activar_zumbador(PIN_ZUMBADOR, 1);
      ultimo_mensaje_alerta = msg_temp_alta;
    }
  }
  // GAS DETECTADO
  else if (hay_gas == true) {
    if (ultimo_mensaje_alerta != msg_gas) {
      bot.sendMessage(CHAT_ID, msg_gas + Dpto_str);
      activar_zumbador(PIN_ZUMBADOR, 1);
      ultimo_mensaje_alerta = msg_gas;
    }
  }
  // CONDICIONES NORMALES
  else {
    ultimo_mensaje_alerta = ""; // LIMPIA EL BUFER, EVITANDO SPAM
  }
}