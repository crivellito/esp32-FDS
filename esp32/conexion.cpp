#include "conexion_online.h"

void info () { 
  String mensaje = String("Temperatura actual: ") + sensor_temp() + "\n" + "Detección de humo: " + sensor_gas();
  bot.sendMessage(CHAT_ID, mensaje);

}

String last_mensaje (int numNuevosSms){
  for (int i = 0 ; i < numNuevosSms ; i++){
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    text.trim();
    text.toLowerCase();
    if (from_name == ""){
      from_name = "Guest";
    }
    return text;  
  }
}

void conexion_wifi (char* ssid, char* password){
    lcd.setCursor(0,0);
    lcd.print("Conectando Wifi..");
    lcd.setCursor(0,2);
    lcd.print(ssid);
    
    WiFi.mode (WIFI_STA);
    WiFi.begin (ssid,password);
    while (WiFi.status() != WL_CONNECTED) {
      for (int i=0 ; i<16 ; i++) {
        lcd.setCursor(i,0);
        lcd.print(".");
        delay(200);
      }
    }
    lcd.clear();
    lcd.print("Wifi conectado! ");
    delay(1000);    
    lcd.clear();
}

void new_mensajes (const unsigned long bot_mtbs, unsigned long bot_lasttime) {
  if (millis() - bot_lasttime > bot_mtbs){
    int numNuevosSms = bot.getUpdates(bot.last_message_received + 1 );
    while (numNuevosSms){
    last_mensaje (numNuevosSms);
      numNuevosSms = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_lasttime = millis();
  } 
}



