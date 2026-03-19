#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

// Credenciais da rede (substitua)
const char* ssid = "Galaxy A017688";
const char* password = "pdtn6853";

// URL de teste (JSONPlaceholder é um serviço comum para testes de API)
const char* serverName = "https://jsonplaceholder.typicode.com/todos/1";

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado com sucesso!");

  delay(5000);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    WiFiClientSecure *client = new WiFiClientSecure;

    if (client) {

      // Para exemplo simples, vamos ignorar validação do certificado
      client->setInsecure();

      HTTPClient https;

      Serial.print("[HTTPS] Iniciando requisição...\n");

      if (https.begin(*client, serverName)) {

        // Realiza GET
        int httpCode = https.GET();

        // httpCode > 0 significa que o servidor respondeu
        if (httpCode > 0) {
          Serial.printf("[HTTPS] Código de resposta: %d\n", httpCode);

          if (httpCode == HTTP_CODE_OK) {
            String payload = https.getString();
            Serial.println("Conteúdo recebido:");
            Serial.println(payload);
          }
        } else {
          Serial.printf("[HTTPS] Falha na requisição, erro: %s\n",
                        https.errorToString(httpCode).c_str());
        }

        https.end();
      } else {
        Serial.println("[HTTPS] Não foi possível conectar ao servidor");
      }

      delete client; // Libera memória
    }
  }

  // Aguarda 30 segundos para a próxima leitura (evita sobrecarga no servidor)
  delay(30000);
}