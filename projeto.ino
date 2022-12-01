#include <WiFi.h>
#include "PubSubClient.h"

const char* ssid = "";
const char* password = "";
const char* mqttServer = "broker.hivemq.com";
int port = 1883;
String stMac;
char mac[50];
char clientId[50];

WiFiClient espClient;
PubSubClient client(espClient);

const int ledPin = 15;
const int ledPin2 = 4;
const int ledPin3 = 5;
const int ledPin4 = 18;
const int ledPin5 = 19;
const int ledPin6 = 21;

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  wifiConnect();

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
  stMac = WiFi.macAddress();
  stMac.replace(":", "_");
  Serial.println(stMac);
  
  client.setServer(mqttServer, port);
  client.setCallback(callback);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);

}

void wifiConnect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void mqttReconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    long r = random(1000);
    sprintf(clientId, "clientId-%ld", r);
    if (client.connect(clientId)) {
      Serial.print(clientId);
      Serial.println(" connected");
      client.subscribe("IFSP/casa");
      client.subscribe("IFSP/amarelo");
      client.subscribe("IFSP/pedro");
      client.subscribe("IFSP/verde");
      client.subscribe("IFSP/azul");
      client.subscribe("IFSP/vermelho");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Mensagem recebida no topico: ");
  Serial.print(topic);
  Serial.print(". Messagem: ");
  String stMessage;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    stMessage += (char)message[i];
  }
  Serial.println();

  if (String(topic) == "IFSP/casa") {
    Serial.print("Saida alterada para ");
    if(stMessage == "on"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
    }
    else if(stMessage == "off"){
      Serial.println("off");
      digitalWrite(ledPin, LOW);
    }
     }
  Serial.println();

  if (String(topic) == "IFSP/amarelo") {
    Serial.print("Saida alterada para ");
    if(stMessage == "on"){
      Serial.println("on");
      digitalWrite(ledPin2, HIGH);
    }
    else if(stMessage == "off"){
      Serial.println("off");
      digitalWrite(ledPin2, LOW);
    }
     }
  Serial.println();

  if (String(topic) == "IFSP/pedro") {
    Serial.print("Saida alterada para ");
    if(stMessage == "on"){
      Serial.println("on");
      digitalWrite(ledPin3, HIGH);
    }
    else if(stMessage == "off"){
      Serial.println("off");
      digitalWrite(ledPin3, LOW);
    }
     }
  Serial.println();

  if (String(topic) == "IFSP/verde") {
    Serial.print("Saida alterada para ");
    if(stMessage == "on"){
      Serial.println("on");
      digitalWrite(ledPin4, HIGH);
    }
    else if(stMessage == "off"){
      Serial.println("off");
      digitalWrite(ledPin4, LOW);
    }
     }
  Serial.println();

  if (String(topic) == "IFSP/azul") {
    Serial.print("Saida alterada para ");
    if(stMessage == "on"){
      Serial.println("on");
      digitalWrite(ledPin5, HIGH);
    }
    else if(stMessage == "off"){
      Serial.println("off");
      digitalWrite(ledPin5, LOW);
    }
     }
  Serial.println();

  if (String(topic) == "IFSP/vermelho") {
    Serial.print("Saida alterada para ");
    if(stMessage == "on"){
      Serial.println("on");
      digitalWrite(ledPin6, HIGH);
    }
    else if(stMessage == "off"){
      Serial.println("off");
      digitalWrite(ledPin6, LOW);
    }
  }

}

void loop() {
  delay(10);
  if (!client.connected()) {
    mqttReconnect();
  }
  client.loop();
}
