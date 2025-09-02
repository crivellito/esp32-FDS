#include "conexion.h"
#include <WiFi.h>
const char* bot_token = "";
const char* bot_token = "";
char* ssid = "sc-7d86 2.4G-2.4Ghz";
char* password = "ZGZ3UGNKHDZQ";
const unsigned long BOT_MTBS = 1000;
unsigned long bot_lasttime;
const byte led_gpio =2;

WiFiClientSecure secured_client;
UniversalTelegramBot bot(bot_token, secured_client);

void setup(){
  Serial.begin(115200);
  conexion(ssid, password, bot_token);
  
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  configTime (0,0,"pool.ntp.org");

  Serial.println("Tiempo configurado. Conectando con Telegram...");
  bot.sendMessage(CHAT_ID, "Esp32 Online");

  digitalWrite(led_gpio, OUTPUT);
}


void loop (){     

  if (millis() - bot_lasttime > BOT_MTBS){
    //Serial.println("Por checkear mensajes nuevos");
    
    int numNuevosSms = bot.getUpdates(bot.last_message_received + 1);
    Serial.print("mensajes nuevos encontrados: ");
    Serial.println(numNuevosSms);
    
    while (numNuevosSms){
      controlNuevosSms (numNuevosSms, bot_token, led_gpio);
      numNuevosSms = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_lasttime = millis();
  }
}


    
