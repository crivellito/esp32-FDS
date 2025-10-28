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

WiFiClientSecure cliente_seguro;
// Se usan los pines del config.h para compatibilidad, aunque no se hayan definido en config.h, es la forma que estabas usando
LiquidCrystal pantalla_lcd( 22, 23, 5, 18, 19, 21 ); 
UniversalTelegramBot bot(TOKEN_BOT, cliente_seguro);
DHT sensor_dht(PIN_TEMP, TIPO_DHT);
Preferences preferences;

unsigned long bot_ultimo_tiempo = 0;
int limite_temperatura = LIMITE_TEMP_DEFECTO; // Límite de temperatura
bool alarma_activa = true;

char* nombre_red = nullptr;
char* clave_red = nullptr;
char escritura[TAM][MAX_LEN];


void setup() {
  Serial.begin(115200);
  configurar_sensores();
  configurar_logica();
  configurar_telegram();

  preferences.begin(PREFERENCES_NS, false);
 
  // Cargar SSID (usa el defecto si no hay nada guardado)
  String ssid_guardado = preferences.getString("ssid", WIFI_SSID_DEFECTO);
  ssid_guardado.toCharArray(escritura[0], MAX_LEN);
  nombre_red = escritura[0];

  // Cargar Clave (usa el defecto si no hay nada guardado)
  String clave_guardada = preferences.getString("clave", WIFI_CLAVE_DEFECTO);
  clave_guardada.toCharArray(escritura[1], MAX_LEN);
  clave_red = escritura[1];
  
  // Intentar conectar con las credenciales cargadas
  if (strlen(nombre_red) > 0) {
      conectar_wifi(nombre_red, clave_red);
  } else {
      pantalla_lcd.print("Sin WiFi.");
      pantalla_lcd.setCursor(0,1);
      pantalla_lcd.print("Esperando Serial");
  }
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