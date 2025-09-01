#include "conexion.h"
#include <WiFi.h>
const char* bot_token = "8230292931:AAFpT_B9qp5DdEuSFsVK28-Bkt6AwrORpTw";
char* ssid = "sc-7d86 2.4G-2.4Ghz";
char* password = "ZGZ3UGNKHDZQ";
const unsigned long BOT_MTBS = 1000;
unsigned long bot_lasttime;

WiFiClientSecure secured_client;
UniversalTelegramBot bot(bot_token, secured_client);

void setup(){
  Serial.begin(115200);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  conexion(ssid, password, bot_token);  
  
  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}


void loop (){

  if (millis() - bot_lasttime > BOT_MTBS){
    Serial.println("Por checkear mensajes nuevos");
    int numNuevosSms = bot.getUpdates(bot.last_message_received + 1);
    Serial.println("mensajes nuevos encontrados: ");
    Serial.println(numNuevosSms);
    
    while (numNuevosSms){
      controlNuevosSms (numNuevosSms, bot_token);
      numNuevosSms = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_lasttime = millis();
  }
}


