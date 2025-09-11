#include "conexion_online.h"


void test () { delay (20000); }

String comunicacion_telegram (int numNuevosSms){
  for (int i = 0 ; i < numNuevosSms ; i++){
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    text.trim();
    text.toLowerCase();
    if (from_name == ""){
      from_name = "Guest";
    }
    return text;  
  }
}

void conexion_wifi (char* ssid, char* password){  
    Serial.println ("Conectando a Wifi");
    Serial.print ("Red: ");
    Serial.print (ssid);
    WiFi.mode (WIFI_STA);
    WiFi.begin (ssid,password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      delay(500);
    }
    delay(500);
    Serial.println("");
    Serial.println("Wifi conectado! ");     
    Serial.print(" IP: ");
    Serial.println(WiFi.localIP());
}

void sensor_gas (){
    int estado = digitalRead(PIN_SENSOR_GAS);
    if (estado == LOW) {
      Serial.println("Gas detectado");
    }
}
