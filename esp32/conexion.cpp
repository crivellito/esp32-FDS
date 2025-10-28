#include "conexion_online.h"
#include "config.h"
#include "logica.h"


//FUNCION - ENVIA INFO DE LOS SENSORES POR TELEGRAM
static void enviar_info_telegram(float temperatura, bool hay_gas) {
  String Dpto_str = (Dpto == nullptr) ? "" : " (Dpto: " + String(Dpto) + ")";
  String mensaje = "--- Info del Sistema" + Dpto_str + " ---\n";
  mensaje += "Temperatura: " + String(temperatura, 1) + " C\n";
  mensaje += "Deteccion de gas: " + String(hay_gas ? "SI" : "NO");
  bot.sendMessage(CHAT_ID, mensaje);
}


//FUNCION - PROCESA MENSAJES DE TELEGRAM
static void procesar_mensaje(String texto_mensaje, float temperatura, bool hay_gas) {
  texto_mensaje.trim();
  texto_mensaje.toLowerCase();

  if (texto_mensaje == "/info") {
    enviar_info_telegram(temperatura, hay_gas);
  }
  if (texto_mensaje == "/alarmaoff") {
    alarma_activa = false;
    digitalWrite(PIN_ZUMBADOR, LOW); //APAGA EL BUZZER
    bot.sendMessage(CHAT_ID, "Alarma desactivada");
  }
  if (texto_mensaje == "/alarmaon") {
    alarma_activa = true;
    bot.sendMessage(CHAT_ID, "Alarma activada");
  }
}


//FUNCION - CONFIGURACION DE CLIENTE Y ZONA HORARIA
void configurar_telegram() {
  cliente_seguro.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  configTime(0, 0, "pool.ntp.org");
}


//FUNCION - CONEXION CON WIFI 
void conectar_wifi(const char* nombre_red, const char* clave_red) {
  pantalla_lcd.clear();
  pantalla_lcd.setCursor(0, 0);
  pantalla_lcd.print("Conectando Wifi..");
  pantalla_lcd.setCursor(0, 1);
  pantalla_lcd.print(nombre_red);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(nombre_red, clave_red);

  //TIEMPO DE ESPERA PARA LA CONEXION
  unsigned long inicio_tiempo = millis();
  const long TIEMPO_MAXIMO_MS = 15000; // 15S

  while (WiFi.status() != WL_CONNECTED && millis() - inicio_tiempo < TIEMPO_MAXIMO_MS) {
    pantalla_lcd.setCursor(15, 0);
    pantalla_lcd.print(".");
    delay(500);
  }

  
  if (WiFi.status() == WL_CONNECTED) {
    String Dpto_str = (Dpto == nullptr) ? "" : " (Dpto: " + String(Dpto) + ")";
    bot.sendMessage(CHAT_ID, "Sistema conectado a " + String(nombre_red) + Dpto_str);
    pantalla_lcd.clear();
    pantalla_lcd.print("Wifi conectado!");
    activar_zumbador(PIN_ZUMBADOR, 2); 
    delay(1000);
  } else {
    WiFi.disconnect(true); 
    pantalla_lcd.clear();
    pantalla_lcd.print("Fallo de conexion");
    pantalla_lcd.setCursor(0, 1);
    pantalla_lcd.print("Esperando Serial");
  }
  pantalla_lcd.clear();
}


//FUNCION - COMUNICACION - LEE PUERTO SERIE EN BUSCA DE WIFI
void gestionar_wifi_serial() {
  if (Serial.available()) {
    String linea = Serial.readStringUntil('\n');

    if (linea.startsWith("E~")) {
      int indice_separador = linea.indexOf('~', 2);
      if (indice_separador == -1) {
        return; // VERIFICACION - EN CASO DE MAL FORMATO
      }

      String indice_str = linea.substring(2, indice_separador);
      int indice = indice_str.toInt();
      // 0 --> SSID
      // 1 --> CONTRA
      // 2 --> DEPTO
      String valor = linea.substring(indice_separador + 1);
      
      valor.toCharArray(escritura[indice], MAX_LEN);
    
      if (indice == 0) {
          nombre_red = escritura[0];
          preferences.putString("ssid", valor);
          WiFi.disconnect(true); 
          delay(500); //DELAY PARA QUE BORRE LA RED ANTERIOR
      } 
      else if (indice == 1) {
        clave_red = escritura[1];
        preferences.putString("clave", valor);
        WiFi.disconnect(true);
        delay(500);
      }
      else if (indice == 2) {
        Dpto = escritura[2];
        preferences.putString("dpto", valor);
        return; 
      }
      
      //VERIFICACION - CONECTA EN CASO DE TENER AMBAS CREDENCIALES Y SI NO ESTA CONECTADO
      if (nombre_red && clave_red && WiFi.status() != WL_CONNECTED) {
        conectar_wifi(nombre_red, clave_red);
      }
    }
  }
}


//FUNCION - COMUNICACION - GESTIONA MENSAJES DE TELEGRAM
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


//FUNCION - COMUNICACION - ENVIA POR PUERTO SERIE EL ESTADO DE LOS SENSORES
void enviar_estado_serial(float temperatura, bool hay_gas) {
  String mensaje = "sensor~";
  mensaje += hay_gas ? "true" : "false";
  mensaje += "~";
  mensaje += String(temperatura, 2);
  Serial.println(mensaje);
}