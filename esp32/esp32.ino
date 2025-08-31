#include "conexion.h"
const char* bot_token = "8230292931:AAFpT_B9qp5DdEuSFsVK28-Bkt6AwrORpTw";

char* ssid = "sc-7d86 2.4G-2.4Ghz";
char* password = "ZGZ3UGNKHDZQ";

void setup(){
  Serial.begin(115200);
  conexion(ssid, password, bot_token);
}

void loop (){
  conexion_control(ssid, password);
  delay(500);
}


