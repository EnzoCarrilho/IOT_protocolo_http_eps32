// Conexão WiFi básica no ESP32

#include <WiFi.h>

// Substitua pelas suas credenciais de rede
const char* ssid = "Galaxy A017688";
const char* password = "pdtn6853";

void setup() {
  Serial.begin(115200);
  Serial.print("Conectando a: ");
  Serial.println(ssid);

  // Iniciando conexão como Station
  WiFi.begin(ssid, password);

  // Aguarda até conectar (loop bloqueante com timeout)
  int tentativas = 0;
  while (WiFi.status() != WL_CONNECTED && tentativas < 20) {
    delay(500);
    Serial.print(".");
    tentativas++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✓ Conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());   // Exibe o IP do ESP32
    Serial.print("RSSI (sinal): ");
    Serial.println(WiFi.RSSI());
  } else {
    Serial.println("✗ Falha na conexão!");
  }
}

void loop() {
  // Verifica conexão a cada 10 segundos
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Reconectando...");
    WiFi.reconnect();
  }

  delay(10000);
}