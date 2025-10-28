#include "conexion_online.h"
#include "config.h"



//Funcion para enviar info por Telegram
static void enviar_info_telegram(float temperatura, bool hay_gas) {
  String mensaje = "--- Info del Sistema ---\n";
  mensaje += "Temperatura: " + String(temperatura, 1) + " C\n";
  mensaje += "Deteccion de gas: " + String(hay_gas ? "SI" : "NO");
  bot.sendMessage(CHAT_ID, mensaje);
}



//Funcion para procesar mensajes
static void procesar_mensaje(String texto_mensaje, float temperatura, bool hay_gas) {
  texto_mensaje.trim();
  texto_mensaje.toLowerCase();

  if (texto_mensaje == "/info") {
    enviar_info_telegram(temperatura, hay_gas);
  }
}



//Configura el cliente y la zona horaria
void configurar_telegram() {
  cliente_seguro.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  configTime(0, 0, "pool.ntp.org");
}




//Se conecta al WiFi y lo muestra en el LCD
void conectar_wifi(const char* nombre_red, const char* clave_red) {
  pantalla_lcd.clear();
  pantalla_lcd.setCursor(0, 0);
  pantalla_lcd.print("Conectando Wifi..");
  pantalla_lcd.setCursor(0, 1);
  pantalla_lcd.print(nombre_red);

  WiFi.mode(WIFI_STA);
  WiFi.begin(nombre_red, clave_red);
  while (WiFi.status() != WL_CONNECTED) {
    //Comentario cuando no se conecta
  }

  pantalla_lcd.clear();
  pantalla_lcd.print("Wifi conectado!");
  delay(1000);
  pantalla_lcd.clear();
}




// Revisa el puerto serie buscando WiFi
void gestionar_wifi_serial() {
  if (Serial.available()) {
    String linea = Serial.readStringUntil('\n');

    if (linea.startsWith("E~")) {
      int indice_separador = linea.indexOf('~', 2);
      if (indice_separador == -1) return;
//Checkea si esta mal el formato

      String indice_str = linea.substring(2, indice_separador);
      int indice = indice_str.toInt();
      // 0 SSID, 1 password
      String valor = linea.substring(indice_separador + 1);
      
      valor.toCharArray(escritura[indice], MAX_LEN);

      if (indice == 0) nombre_red = escritura[0];
      else if (indice == 1) clave_red = escritura[1];

      // Se conecta solo si estan ambos y no esta ya conectado
      if (nombre_red && clave_red && WiFi.status() != WL_CONNECTED) {
        conectar_wifi(nombre_red, clave_red);
      }
      Serial.println("Recibido: " + linea);
    }
  }
}




//Revisa si hay nuevos mensajes de Telegram y los procesa
void gestionar_comandos_telegram(float temperatura, bool hay_gas) {
  if (millis() - bot_ultimo_tiempo > INTERVALO_BOT_MS) {
    int num_mensajes_nuevos = bot.getUpdates(bot.last_message_received + 1);

    while (num_mensajes_nuevos) {
      for (int i = 0; i < num_mensajes_nuevos; i++) {
        procesar_mensaje(bot.messages[i].text, temperatura, hay_gas);
      }
      num_mensajes_nuevos = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_ultimo_tiempo = millis();
  }
}




//Envía el estado actual de los sensores por puerto serie
void enviar_estado_serial(float temperatura, bool hay_gas) {
  String mensaje = "sensor~";
  mensaje += hay_gas ? "true" : "false";
  mensaje += "~";
  mensaje += String(temperatura, 2);
  Serial.println(mensaje);
}