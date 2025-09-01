#include "conexion.h"
#include <string.h>
#define CHAT_ID "1965602246"
#include <UniversalTelegramBot.h>


void controlNuevosSms (int numNuevosSms, const char* bot_token){
  WiFiClientSecure client; 
  UniversalTelegramBot bot (bot_token, client);
  Serial.println(numNuevosSms);
  
  
  for (int i = 0 ; i < numNuevosSms ; i++){
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    Serial.println("MENSAJE PARSEADO"); 
    Serial.println(text);

    text.trim();

    text.toLowerCase();

    /*if (from_name == ""){
      from_name = "Guest";
    }
    if (text == "/1"){
      Serial.println("1 DETECTADO LCDLL");
      bot.sendMessage(CHAT_ID, "Configuracion WiFi ", "");
    }
    */
  }
}


void conexion (char* ssid, char* password, const char* bot_token){  
    WiFiClientSecure client; 
    UniversalTelegramBot bot (bot_token, client);
    delay(500);
    Serial.print ("Conectando a Wifi");
    Serial.println ("");
    Serial.print ("Red: ");
    Serial.print (ssid);

    WiFi.mode (WIFI_STA);
    WiFi.begin (ssid,password);
    client.setCACert (TELEGRAM_CERTIFICATE_ROOT);
    
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }
    delay(500);
    Serial.println("");
    Serial.println("Wifi conectado! ");     
    Serial.print(" IP: ");
    Serial.println(WiFi.localIP());

    bot.sendMessage(CHAT_ID, "esp-32 NODEMCU conectado con éxito a la red ");
}
