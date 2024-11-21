#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

// Configurações de WiFi
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";

// Configurações de MQTT
const char *BROKER_MQTT = "broker.hivemq.com";
const int BROKER_PORT = 1883;
const char *ID_MQTT = "esp32_mqtt";
const char *TOPIC_SUBSCRIBE_LED = "fiap/iot/led";
const char *TOPIC_PUBLISH_CONSUMO = "fiap/iot/consumoea";

// Configurações de Hardware
#define PIN_POTENTIOMETER 34 // Pino analógico do potenciômetro
#define PIN_LED 2            // Pino do LED
#define PUBLISH_DELAY 2000   // Intervalo de publicação (2 segundos)

// Variáveis globais
WiFiClient espClient;
PubSubClient MQTT(espClient);
unsigned long publishUpdate = 0;
int consumoEnergia = 0; // Valor simulado de consumo
bool ledLigado = false;

// Protótipos de funções
void initWiFi();
void initMQTT();
void callbackMQTT(char *topic, byte *payload, unsigned int length);
void reconnectMQTT();
void reconnectWiFi();
void checkWiFIAndMQTT();

void initWiFi() {
  Serial.print("Conectando com a rede: ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado com sucesso: ");
  Serial.println(SSID);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(callbackMQTT);
}

void callbackMQTT(char *topic, byte *payload, unsigned int length) {
  String msg = String((char*)payload).substring(0, length);

  StaticJsonDocument<200> json;
  DeserializationError error = deserializeJson(json, msg);

  if (error) {
    Serial.println("Erro ao processar JSON recebido.");
    return;
  }

  if (json.containsKey("led")) {
    int valor = json["led"];
    if (valor == 1) {
      digitalWrite(PIN_LED, HIGH);
      ledLigado = true;
      Serial.println("LED ligado via MQTT");
    } else if (valor == 0) {
      digitalWrite(PIN_LED, LOW);
      ledLigado = false;
      Serial.println("LED desligado via MQTT");
    }
  }
}

void reconnectMQTT() {
  while (!MQTT.connected()) {
    Serial.print("Tentando conectar ao broker MQTT: ");
    Serial.println(BROKER_MQTT);

    if (MQTT.connect(ID_MQTT)) {
      Serial.println("Conectado ao broker MQTT!");
      MQTT.subscribe(TOPIC_SUBSCRIBE_LED); // Assina o tópico para controle do LED
    } else {
      Serial.println("Falha na conexão. Tentando novamente em 2 segundos.");
      delay(2000);
    }
  }
}

void reconnectWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
    }

    Serial.println();
    Serial.println("Wi-Fi conectado com sucesso!");
  }
}

void checkWiFIAndMQTT() {
  if (WiFi.status() != WL_CONNECTED) reconnectWiFi();
  if (!MQTT.connected()) reconnectMQTT();
}

void setup() {
  Serial.begin(115200);

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);  // Inicialmente o LED está desligado
  initWiFi();
  initMQTT();
}

void loop() {
  checkWiFIAndMQTT();
  MQTT.loop();

  if ((millis() - publishUpdate) >= PUBLISH_DELAY) {
    publishUpdate = millis();

    // Simula o consumo de energia com base no valor do potenciômetro
    int potValue = analogRead(PIN_POTENTIOMETER);
    consumoEnergia = map(potValue, 0, 4095, 0, 100); // Converte para 0-100%

    // Publica os dados de consumo e estado do LED no MQTT
    StaticJsonDocument<200> doc;
    doc["consumo"] = consumoEnergia;
    doc["led"] = ledLigado ? "on" : "off";

    char buffer[200];
    serializeJson(doc, buffer);
    MQTT.publish(TOPIC_PUBLISH_CONSUMO, buffer);

    // Exibe no monitor serial
    Serial.println(buffer);
  }
}
