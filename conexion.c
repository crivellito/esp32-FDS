#include <Wifi.h>
#include <WifiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include "conexion.h"
#include <stdio.h>


void conexion (const char** ssid, const char** password, const char** bot_token, const int** chatid){
    
    * ssid = "";
    * password = "";
    * bot_token = "";
    * chatid = ;

    WifiClientSecure client; 
    UniversalTelegramBot bot (BOTtoken, client);

    Serial.print ("Conectando a Wifi");
    Serial.println ("");
    Serial.print ("Red: ");
    Serial.print (ssid);

    Wifi.mode (WIFI_STA);
    Wifi.begin (ssid,password);
    client.setCACert (TELEGRAM_CERTIFICATE_ROOT);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }
    Serial.println("");
    Serial.println("Wifi conectado! ");
    Serial.print(" IP: ");
    Serial.println(WiFi.localIP());

    bot.sendMessage(chatid, "esp-32 NODEMCU conectado con éxito a la red! ");
}
