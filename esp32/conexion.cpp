#include "conexion.h"

void test () { delay (20000); }

conexion :: conexion () {
    num_nuevos_mensajes = 0;
    ssid = password = "";
}


String conexion :: comunicacion_telegram (int num_nuevos_sms){
  for (int i = 0 ; i < num_nuevos_sms ; i++){
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

void conexion :: conexion_wifi (char* ssid, char* password){  
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


