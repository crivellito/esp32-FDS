#include "conexion_online.h"
#include "sensores.h"
#include <LiquidCrystal.h>
#include <WiFi.h>
#define CHAT_ID "7720847255"
#define PIN_SENSOR_GAS 32
#define PIN_SENSOR_TEMP 4
#define PIN_BUZZER X

const char* bot_token = "";
char* ssid = "";
char* password = "";

const unsigned long BOT_MTBS = 1000;
unsigned long bot_lasttime;
LiquidCrystal lcd (22,23,5,18,19,21);
int temp_ext;

//NOMBRES DE FUNCIONES ACTIVADAS POR TELEGRAM
String comando_test = "test";

WiFiClientSecure secured_client;
UniversalTelegramBot bot(bot_token, secured_client);






void setup(){
  Serial.begin(115200);
  pinMode(PIN_SENSOR_GAS, INPUT);
  pinMode(PIN_SENSOR_TEMP, INPUT);
//INICIALIZACION DEL DISPLAY LCD
  lcd.begin(16,2);
  dht.begin();
//CONFIGURACION WIFI EN EL BOOT
  conexion_wifi(ssid, password);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  configTime (0,0,"pool.ntp.org");
  bot.sendMessage(CHAT_ID, "Esp32 Online");
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
  sensor_gas();

//FUNCION SENSOR DE TEMPERATURA
  sensor_temp();


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
  delay(500);
}   


    
