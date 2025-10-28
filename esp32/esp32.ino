#include "config.h"
#include "sensores.h"
#include "conexion_online.h"
#include "logica.h"

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include <UniversalTelegramBot.h>
#include <Preferences.h>

//OBJETOS DE LAS BIBLIOTECAS
WiFiClientSecure cliente_seguro;
LiquidCrystal pantalla_lcd( 22, 23, 5, 18, 19, 21 );
UniversalTelegramBot bot(TOKEN_BOT, cliente_seguro);
DHT sensor_dht(PIN_TEMP, TIPO_DHT);
Preferences preferences;

//VARIABLES GLOBALES
unsigned long bot_ultimo_tiempo = 0;
int limite_temperatura = LIMITE_TEMP_DEFECTO;
bool alarma_activa = true;

//CREDENCIALES
char escritura[TAM][MAX_LEN];
char* nombre_red = nullptr;
char* clave_red = nullptr;
char* Dpto = nullptr; 

void setup() {
  Serial.begin(115200);
  
  configurar_sensores();
  configurar_logica();
  configurar_telegram();

  preferences.begin(PREFERENCES_NS, false);
 
  // Cargar SSID Y CLAVE (usa el defecto si no hay nada guardado)
  String ssid_guardado = preferences.getString("ssid", WIFI_SSID_DEFECTO);
  ssid_guardado.toCharArray(escritura[0], MAX_LEN);
  nombre_red = escritura[0];

  String clave_guardada = preferences.getString("clave", WIFI_CLAVE_DEFECTO);
  clave_guardada.toCharArray(escritura[1], MAX_LEN);
  clave_red = escritura[1];

  //CARGA EL NOMBRE DEL DEPTO DESDE FLASH (PREFERENCES)
  String dpto_guardado = preferences.getString("dpto", "N/A");
  dpto_guardado.toCharArray(escritura[2], MAX_LEN);
  Dpto = escritura[2];
  
  //INTENTA CONECTAR CON LAS CREDENCIALES DEFAULT DE FLASH (PREFERENCES)
  if (strlen(nombre_red) > 0) {
      conectar_wifi(nombre_red, clave_red);
  } else {
      pantalla_lcd.print("Sin WiFi.");
      pantalla_lcd.setCursor(0,1);
      pantalla_lcd.print("Esperando Serial");
  }
}

void loop() {
  //CARGA DE CREDENCIALES POR PUERTO SERIE
  gestionar_wifi_serial();
 
  //LECTURA DE SENSORES
  float temperatura_actual = leer_temperatura();
  bool gas_detectado = leer_gas();

  //COMUNICACION TELEGRAM
  gestionar_comandos_telegram(temperatura_actual, gas_detectado);
 
  //LOGICA DEL APARATO
  ejecutar_logica(gas_detectado, temperatura_actual);

  //CONTROL DEL DISPLAY
  mostrar_estado_lcd(temperatura_actual, gas_detectado);
 
  //COMUNICACION PUERTO SERIE - ENVIO
  enviar_estado_serial(temperatura_actual, gas_detectado);

  delay(1000); 
}