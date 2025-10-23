#include "conexion_online.h"
#include "sensores.h"
#include "logica.h"
#include <LiquidCrystal.h>
#include <WiFi.h>

#define CHAT_ID "-1003100355289"                                         //"7720847255"
#define PIN_SENSOR_GAS 32
#define PIN_SENSOR_TEMP 4
#define PIN_BUZZER 12

const char* bot_token = "8444785999:AAFXDQE1KP1wdjh0JGw4b-xsq0FxqFU2Nkg";
const unsigned long BOT_MTBS = 1000;
unsigned long bot_lasttime;

char* ssid = "sc-7d86 2.4G-2.4Ghz";
char* password = "ZGZ3UGNKHDZQ";
int temp_limit = 40;
String info_telegram = "info";


WiFiClientSecure secured_client;
UniversalTelegramBot bot(bot_token, secured_client);
LiquidCrystal lcd (22,23,5,18,19,21);



void setup(){
  Serial.begin(115200);
  lcd.begin(16,2);
  dht.begin();

  pinMode(PIN_SENSOR_GAS, INPUT);
  pinMode(PIN_SENSOR_TEMP, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  
  conexion_wifi(ssid, password);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  configTime (0,0,"pool.ntp.org");
  //   bot.sendMessage(CHAT_ID, "FDS-Online");
}
  


void loop (){     
  
  new_mensajes (BOT_MTBS, bot_lasttime);
  logica (sensor_gas(), sensor_temp(), PIN_BUZZER);

  if (last_mensaje(1) == info_telegram){
    info();
  }
}   


    
