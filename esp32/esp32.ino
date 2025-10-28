#include "conexion_online.h"
#include "sensores.h"
#include "logica.h"
#include <LiquidCrystal.h>
#include <WiFi.h>

#define CHAT_ID "-1003100355289"                                         //"7720847255"
#define PIN_SENSOR_GAS 32
#define PIN_SENSOR_TEMP 4
#define PIN_BUZZER 12

#define TAM 10
#define MAX_LEN 50
char escritura[TAM][MAX_LEN];
char cmd[10];

const char* bot_token = "8444785999:AAFXDQE1KP1wdjh0JGw4b-xsq0FxqFU2Nkg";
const unsigned long BOT_MTBS = 1000;
unsigned long bot_lasttime;

char* ssid = nullptr;
char* password = nullptr;
char* Dpto = nullptr;

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
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  configTime (0,0,"pool.ntp.org");
  //   bot.sendMessage(CHAT_ID, "FDS-Online");
}
  


void loop (){     
  
  float temp = sensor_temp();

  new_mensajes (BOT_MTBS, bot_lasttime);
  logica (sensor_gas(), sensor_temp(), PIN_BUZZER);

  if (last_mensaje(1) == info_telegram){
    info();
  }

if(Serial.available()) {
    String linea = Serial.readStringUntil('\n'); // Lee hasta el salto de línea

    // Verificamos que comience con "E~"
    if(linea.startsWith("E~")) {
        int idx1 = linea.indexOf('~', 2); // busca la segunda "~"
        if(idx1 == -1) return; // mal formato, ignorar

        String indiceStr = linea.substring(2, idx1);
        int i = indiceStr.toInt(); // 0 = SSID, 1 = password
        String valor = linea.substring(idx1 + 1);

        // Guardar en el arreglo
        valor.toCharArray(escritura[i], MAX_LEN);

        // Actualizar punteros
        if(i == 0) ssid = escritura[0];
        else if(i == 1) password = escritura[1];
        else if(i == 2) Dpto = escritura[2];

        // Conectar solo si ya tenemos ssid y password
        if(ssid && password) {
            conexion_wifi(escritura[0], escritura[1]);
        }

        Serial.println("Recibido: " + linea); // opcional, para debug
    }
}

String mensaje = "sensor~";
  mensaje += sensor_gas() ? "true" : "false";
  mensaje += "~";
  mensaje += String(temp, 2);

  // Enviar por Serial
  Serial.println(mensaje);

  delay(1000); // enviar cada segundo
}


    
