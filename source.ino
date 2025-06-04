#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)

#define trigger 4
#define echo 18
#define LDR 36

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("Connected");
      client.publish("iotfrontier/mqtt", "iotfrontier");
      client.subscribe("iotfrontier/mqtt");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

float measureWaterLevel() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  long duration = pulseIn(echo, HIGH);
  return duration * 0.034 / 2; // cm
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float waterLevel = measureWaterLevel();
  int light = analogRead(LDR);

  String status = "Normal";
  
  if (waterLevel < 200 && light < 1000) {
    status = "Bueiro em situacao critica! Nivel da agua e lixo acima do normal!";
  } else if (waterLevel < 200) {
    status = "Nivel da agua acima do normal!";
  } else if (light < 1000) {
    status = "Nivel do lixo acima do normal!";
  }

  String strWaterLevel = String(waterLevel);
  String strLight = String(light);

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    Serial.print("Nivel da agua: ");
    Serial.println(waterLevel);
    client.publish("iotfrontier/waterLevel", strWaterLevel.c_str());
    Serial.print("Nivel do lixo: ");
    Serial.println(light);
    client.publish("iotfrontier/light", strLight.c_str());
    Serial.print("Status: ");
    Serial.println(status);
    client.publish("iotfrontier/status", status.c_str());
  }

  delay(2000);
}
