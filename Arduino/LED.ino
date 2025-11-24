#include <WiFi.h>
#include <PubSubClient.h>

// WiFi do Wokwi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT 
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* topic_subscribe = "sp/atuador/leds";

WiFiClient espClient;
PubSubClient client(espClient);

// Pinos dos LEDs
#define LED_VERDE 21
#define LED_AMARELO 18
#define LED_VERMELHO 19

void setup_leds() {
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);
}

void acenderLed(String comando) {
  // Apaga todos antes
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  // Acende o LED correto e mostra no Serial
  if (comando == "LED_VERDE") {
    digitalWrite(LED_VERDE, HIGH);
    Serial.println("LED aceso: VERDE");
  }
  else if (comando == "LED_AMARELO") {
    digitalWrite(LED_AMARELO, HIGH);
    Serial.println("LED aceso: AMARELO");
  }
  else if (comando == "LED_VERMELHO") {
    digitalWrite(LED_VERMELHO, HIGH);
    Serial.println("LED aceso: VERMELHO");
  }
  else {
    Serial.println("Nenhum LED aceso (comando desconhecido)");
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";

  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Comando recebido: ");
  Serial.println(message);

  acenderLed(message);
}

void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(300);
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32_ATUADOR")) {
      client.subscribe(topic_subscribe);
    } else delay(2000);
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  setup_leds();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  Serial.println("Sistema iniciado! Aguardando comandos MQTT...");
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
}
