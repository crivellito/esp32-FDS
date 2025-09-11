#include "conexion_online.h"
#include <LiquidCrystal.h>
#include <WiFi.h>
#define CHAT_ID "1965602246"
#define PIN_SENSOR_GAS 32
const char* bot_token = "8230292931:AAFpT_B9qp5DdEuSFsVK28-Bkt6AwrORpTw";
char* ssid = "sc-7d86 2.4G-2.4Ghz";
char* password = "ZGZ3UGNKHDZQ";
const unsigned long BOT_MTBS = 1000;
unsigned long bot_lasttime;
LiquidCrystal lcd (22,23,5,18,19,21);


//NOMBRES DE FUNCIONES ACTIVADAS POR TELEGRAM
String comando_test = "test";

WiFiClientSecure secured_client;
UniversalTelegramBot bot(bot_token, secured_client);

//CONEXION CON EL LCD


void setup(){
  Serial.begin(115200);
//INICIALIZACION DEL DISPLAY LCD
  lcd.begin(16,2);

  //CONFIGURACION WIFI EN EL BOOT
  conexion_wifi(ssid, password);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  configTime (0,0,"pool.ntp.org");
  bot.sendMessage(CHAT_ID, "Esp32 Online");
  pinMode(PIN_SENSOR_GAS, INPUT);
}
  


void loop (){     

  //COMUNICACION CON TELEGRAM
  if (millis() - bot_lasttime > BOT_MTBS){
    int numNuevosSms = bot.getUpdates(bot.last_message_received + 1 );
    while (numNuevosSms){
    comunicacion_telegram (numNuevosSms);
      numNuevosSms = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_lasttime = millis();
  }

  //FUNCION SENSOR DE GASES




  //PRUEBA DE FUNCION ACTIVADA POR TELEGRAM, NOMBRE DE LA FUNCIÓN: TEST
  if (comunicacion_telegram(1) == comando_test){
    Serial.println("Se ha entrado a una función o bloque externo mediante el comando 'test'!");
    bot.sendMessage(CHAT_ID, "Se entró a una funcion o bloque externo mediante el comando 'test'! ");
    test();
  }
 
  //DISPLAY
  delay(100);
  lcd.setCursor(0,0);
  lcd.print(comunicacion_telegram(1));
  //lcd.setCursor(0,2);
  //lcd.print("Neeeeeeek");
  sensor_gas();
  delay(500);
}   


    
