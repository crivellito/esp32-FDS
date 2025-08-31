#include "conexion.h"
#include <string.h>
#define CHAT_ID "1965602246"

//void conexion_control (char* ssid, char* password){
  //if ---> mensaje recibido cambiar valores si no no

//}

void conexion (char* ssid, char* password, const char* bot_token){  
    WiFiClientSecure client; 
    UniversalTelegramBot bot (bot_token, client);
    
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

    Serial.println("");
    Serial.println("Wifi conectado! ");     
    Serial.print(" IP: ");
    Serial.println(WiFi.localIP());

    bot.sendMessage(CHAT_ID, "esp-32 NODEMCU conectado con éxito a la red ");
    //bot.sendMessage(chat_id, "esp-32 NODEMCU conectado con éxito a la red! ");
}
