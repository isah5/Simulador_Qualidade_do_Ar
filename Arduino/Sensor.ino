#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"

// ======== SENSOR =======
DHTesp dht;
const int DHT_PIN = 15; // Pino do DHT22 no Wokwi

// ======== REDE WIFI (Wokwi) ========
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ======== MQTT ========
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;

const char* topic_publish = "sp/sensor/umidade";
const char* topic_subscribe = "sp/comando/esp32";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;

// ---------------------------------------------------------
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando na rede: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// ---------------------------------------------------------
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.print(topic);
  Serial.print(" | Conteúdo: ");

  String msg;
  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  Serial.println(msg);

}

// ---------------------------------------------------------
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao broker MQTT... ");

    String clientId = "ESP32-SENSOR-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("CONECTADO!");
      client.subscribe(topic_subscribe);
    } else {
      Serial.print("Falhou, rc=");
      Serial.print(client.state());
      Serial.println(". Tentando novamente em 5 seg...");
      delay(5000);
    }
  }
}

// ---------------------------------------------------------
void setup() {
  Serial.begin(115200);
  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  dht.setup(DHT_PIN, DHTesp::DHT22);
}

// ---------------------------------------------------------
void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 5000) {  // Envia a cada 5 segundos
    lastMsg = now;

    float umidade = dht.getHumidity();

    if (!isnan(umidade)) {
      String payload = String(umidade, 1);  // Apenas o número
      Serial.print("Enviando umidade: ");
      Serial.println(payload);

      client.publish(topic_publish, payload.c_str());
    } else {
      Serial.println("Erro ao ler DHT22!");
    }
  }
}
