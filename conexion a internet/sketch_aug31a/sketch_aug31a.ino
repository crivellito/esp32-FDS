#include <WiFi.h>   // Librería para manejar WiFi en ESP32

const char* ssid     = "sc-7d86 2.4G-2.4Ghz";       // Nombre de tu red WiFi
const char* password = "ZGZ3UGNKHDZQ";   // Contraseña

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);

  // Espera hasta conectar
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("✅ Conectado a la red WiFi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());   // Muestra la IP asignada
}

void loop() {
  // Tu código principal
}
