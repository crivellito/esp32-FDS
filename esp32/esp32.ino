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
char cmd[10];

const char* bot_token = "8444785999:AAFXDQE1KP1wdjh0JGw4b-xsq0FxqFU2Nkg";
const unsigned long BOT_MTBS = 1000;
unsigned long bot_lasttime;

char* ssid = nullptr;
char* password = nullptr;
char* Dpto = nullptr;


void setup() {
  Serial.begin(115200);
  configurar_sensores();
  configurar_logica();
  configurar_telegram();

  preferences.begin(PREFERENCES_NS, false);
 
  //Se carga el ssid y la clave, usa el ssid_defecto de config.h si no hay uno definido
  String ssid_guardado = preferences.getString("ssid", WIFI_SSID_DEFECTO);
  ssid_guardado.toCharArray(escritura[0], MAX_LEN);
  nombre_red = escritura[0];

  String clave_guardada = preferences.getString("clave", WIFI_CLAVE_DEFECTO);
  clave_guardada.toCharArray(escritura[1], MAX_LEN);
  clave_red = escritura[1];
  
  //Intenta conectar
  if (strlen(nombre_red) > 0) {
      conectar_wifi(nombre_red, clave_red);
  } else {
      //En caso de no poder conectarse el wifi:
      pantalla_lcd.print("Sin WiFi.");
      pantalla_lcd.setCursor(0,1);
      pantalla_lcd.print("Esperando Serial");
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

  //Actualiza el lcd y muestra lo sensado
  mostrar_estado_lcd(temperatura_actual, gas_detectado);
 
  //Envia estado por puerto serie
  enviar_estado_serial(temperatura_actual, gas_detectado);

  delay(1000); 
}