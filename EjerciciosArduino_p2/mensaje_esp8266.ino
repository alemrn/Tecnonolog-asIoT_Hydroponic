/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 - Se conecta a la WiFi y al servidor de mensajes (broker) MQTT
 - Cada X segundos envía al topic master/holamundo un mensaje con el identificador ESP_#######
 - El LED se apaga con cada envío
 - Comprobar en el monitor serie los mensajes  de depuración
 - Comprobar en el IU de node-red que llegan los mensajes 

*/
#include "DHTesp.h"

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

DHTesp dht;

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "MASTER";
const char* password = "malagaiot";

const char* mqtt_server = "iot.ac.uma.es";
const char* mqtt_user = "master";
const char* mqtt_pass = "malagaiot";
const char* mqtt_topic = "master/temperatura/TeSeguimosEsperando";
const char* mqtt_topich = "master/humedad/TeSeguimosEsperando";
char mqtt_cliente[50];

#define LED 2

WiFiClient espClient;
PubSubClient client(espClient);

#define INTERVALO 20000
long lastMsg = -INTERVALO;

void setup() {
  pinMode(LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  
  client.setServer(mqtt_server, 1883);
  snprintf(mqtt_cliente, 50, "ESP_%d", ESP.getChipId());
  Serial.print("Mi ID es "); Serial.println(mqtt_cliente);

  //Serial.println();
  //Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
  String thisBoard= ARDUINO_BOARD;
  //Serial.println(thisBoard);

  // Autodetect is not working reliable, don't use the following line
  // dht.setup(17);
  // use this instead: 
  dht.setup(5, DHTesp::DHT11); // Connect DHT sensor to GPIO 17
  
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(mqtt_cliente, mqtt_user, mqtt_pass)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {

  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  char result[8];
  char hresult[8]; 
  dtostrf(temperature, 6, 2, result);
  dtostrf(humidity, 6, 2, hresult);

 /* Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.print(dht.toFahrenheit(temperature), 1);
  Serial.print("\t\t");
  Serial.print(dht.computeHeatIndex(temperature, humidity, false), 1);
  Serial.print("\t\t");
  Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperature), humidity, true), 1);
  delay(2000);
  */
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > INTERVALO) {
    lastMsg = now;
    Serial.print("Mensaje publicado: ");  Serial.println(temperature);
    Serial.print("En topic: ");  Serial.println(mqtt_topic);
    client.publish(mqtt_topic, result);
    digitalWrite(LED,HIGH); delay(200); digitalWrite(LED,LOW);

    Serial.print("Mensaje publicado: ");  Serial.println(humidity);
    Serial.print("En topic: ");  Serial.println(mqtt_topich);
    client.publish(mqtt_topich, hresult);
    digitalWrite(LED,HIGH); delay(200); digitalWrite(LED,LOW);
  }
}
