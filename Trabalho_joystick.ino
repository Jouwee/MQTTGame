#include <WiFi.h>
#include <PubSubClient.h>

int P0 = 33;
int P1 = 32;
int P2 = 35;

int x = 0;
int y = 0;
int sw = 0;

const char* ssid = "jonatabecker-670Z5E";
const char* password = "GHOU22ZM";
const char* mqtt_server = "172.18.0.1";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.println("CONNECTING...");
    delay(300);
  }

  client.setServer(mqtt_server, 1883);
  while (!client.connected()) {
    Serial.println("CONNECTING MQTT...");
    client.connect("ESP32Client");
    delay(300);
  }
}

void loop() {
  client.loop();
  x = analogRead(P0);
  y = analogRead(P1);
  sw = analogRead(P2);

  client.publish("/teste", x);
  
  delay(500);
}
