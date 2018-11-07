#include <WiFi.h>
#include <PubSubClient.h>

int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

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

void callback(char* topic, byte* payload, unsigned int length) {
 Serial.print("Message arrived [");
 Serial.print(topic);
 Serial.print("] ");
 for (int i=0;i<length;i++) {
  char receivedChar = (char)payload[i];
  Serial.print(receivedChar);
  if (receivedChar == '0')
  // ESP8266 Huzzah outputs are "reversed"
  digitalWrite(ledPin, HIGH);
  if (receivedChar == '1')
   digitalWrite(ledPin, LOW);
  }
  Serial.println();
}

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
  // client.setCallback(callback);
}

void loop() {
  client.loop();
  x = analogRead(P0);
  y = analogRead(P1);
  sw = analogRead(P2);

  Serial.print("x ");
  Serial.println(x);
  Serial.print("y ");
  Serial.println(y);
  Serial.print("sw ");
  Serial.println(sw);

  client.publish("/teste", "oi jonata");
  
  delay(500);
}
