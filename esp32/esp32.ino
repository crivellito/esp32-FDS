#include "config.h"
#include "sensores.h"
#include "conexion_online.h"
#include "logica.h"

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include <UniversalTelegramBot.h>


WiFiClientSecure cliente_seguro;
UniversalTelegramBot bot(TOKEN_BOT, cliente_seguro);
LiquidCrystal pantalla_lcd( 22, 23, 5, 18, 19, 21 );
DHT sensor_dht(PIN_TEMP, TIPO_DHT);


unsigned long bot_ultimo_tiempo = 0;
int limite_temperatura = LIMITE_TEMP_DEFECTO; // Límite de temperatura
bool hay_gas = false;


char* nombre_red = nullptr;
char* clave_red = nullptr;
char escritura[TAM][MAX_LEN];


void setup() {
  Serial.begin(115200);
  configurar_sensores();
  configurar_logica();
  configurar_telegram();


  #ifdef WIFI_SSID
    nombre_red = (char*)WIFI_SSID;
    clave_red = (char*)WIFI_CLAVE;
    conectar_wifi(nombre_red, clave_red);
  #endif
}

void loop() {
  //Revisa si hay nuevas credenciales WiFi por puerto serie
  gestionar_wifi_serial();

  //Lee sensores
  float temperatura_actual = leer_temperatura();
  bool gas_detectado = leer_gas();

  //Maneja comunicación con telegram
  gestionar_comandos_telegram(temperatura_actual, gas_detectado);

  //Ejecuta lógica de alarma
  ejecutar_logica(gas_detectado, temperatura_actual);

  //Actualiza el lcd
  mostrar_estado_lcd(temperatura_actual, gas_detectado);

  //Enviar estado por puerto serie
  enviar_estado_serial(temperatura_actual, gas_detectado);

  delay(1000); 
}