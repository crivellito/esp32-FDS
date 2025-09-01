#include "conexion.h"
#include <string.h>
#define CHAT_ID "1965602246"
#include <UniversalTelegramBot.h>
#include <Arduino.h>

void controlNuevosSms (int numNuevosSms, const char* bot_token, const byte led_gpio){
  Serial.println(numNuevosSms);
  
  
  for (int i = 0 ; i < numNuevosSms ; i++){
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    
    Serial.println("MENSAJE PARSEADO"); 

    text.trim();
    text.toLowerCase();

    if (from_name == ""){
      from_name = "Guest";
    }
    if (text == "/1"){
      bot.sendMessage(CHAT_ID, "Configuracion WiFi ", "");
      digitalWrite(led_gpio, HIGH);
      delay(200);
      digitalWrite(led_gpio, LOW);
      delay(200);
      digitalWrite(led_gpio, HIGH);
      delay(200);
    }
  
  }
}


void conexion (char* ssid, char* password, const char* bot_token){  
  
    Serial.println ("Conectando a Wifi");
    Serial.print ("Red: ");
    Serial.print (ssid);

    WiFi.mode (WIFI_STA);
    WiFi.begin (ssid,password);
    
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }
    delay(500);
    Serial.println("");
    Serial.println("Wifi conectado! ");     
    Serial.print(" IP: ");
    Serial.println(WiFi.localIP());

    //bot.sendMessage(CHAT_ID, "esp-32 NODEMCU conectado con éxito a la red ");
}
