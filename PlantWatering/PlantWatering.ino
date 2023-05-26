#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "credentials.hpp" //file with WIFI and MQTT credentials

//MQTT - topic names
bool retain = true;
char topic_voltage[] = "voltage";
char topic_moisture[] = "moisture";
char topic_water[] = "water";

//pin allocation
int voltage_pin = D5;
int moisture_pin = D6;
int motor_pin = D2;
int analog_pin = A0;

float voltage = 0;
float moisture = 0;
float moisture_percent = 0;
float water = 0;

float max_moisture = 415; //422, 416, 415, 358
float max_moisture_adj = 415;
float min_moisture = 724; //724, 723, 721, 720
//measured for 4.12v

//int test=0;

void setup()
{
  //Serial.begin(74880);

  //Pin mode
  pinMode(voltage_pin, OUTPUT);
  pinMode(moisture_pin, OUTPUT);
  pinMode(motor_pin, OUTPUT);
  pinMode(analog_pin, INPUT);
  
  //to test
  pinMode(D8, INPUT);
  
  //Off all transistors
  digitalWrite(voltage_pin, LOW);
  digitalWrite(moisture_pin, LOW);
  digitalWrite(motor_pin, LOW);

  //Measure voltage
  digitalWrite(voltage_pin, HIGH);
  delay(100);
  voltage = 2 * (3.03 / 1024) * analogRead(analog_pin);
  delay(100);
  pinMode(voltage_pin, LOW);

  //Measure moisture
  digitalWrite(moisture_pin, HIGH);
  delay(100);
  moisture = analogRead(analog_pin);
  delay(100);
  pinMode(moisture_pin, LOW);
  max_moisture_adj = max_moisture - ((4.12 - voltage) * 10) * 65; 
  moisture_percent = ((min_moisture - moisture) / (min_moisture - max_moisture_adj)) * 100;

  //water the plant if needed
  water = 0;
  if(moisture_percent < 20 && voltage >= 3.7) {
    digitalWrite(motor_pin, HIGH);
    delay(8.33*1000); // 300ml (pump speed 360ml in 10 sec)
    digitalWrite(motor_pin, LOW);
    water = 1;
  }

  //Test
  //pinMode(BUILTIN_LED, OUTPUT);

  WiFiClient espClient;
  PubSubClient client(espClient);

  //connecting to WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) { delay(100); }
  
  //Send data
  Serial.println("MQTT");
  client.setServer(mqtt_server, mqtt_port);
  String clientId = "WemosD1-" + WiFi.macAddress();
  if (client.connect(clientId.c_str(), mqtt_user, mqtt_password) ) {
    if(client.publish(topic_voltage, String(voltage).c_str(), true) 
    && client.publish(topic_moisture, String(moisture_percent).c_str(), true) 
    && client.publish(topic_water, String(water).c_str(), true)) {
      Serial.println("Data sent.");
    } else {
      Serial.println("Can't send data.");
    }
  } else {
    Serial.println("MQTT connection failed.");
    Serial.println(client.state());
  }
  client.disconnect();
  //digitalWrite(BUILTIN_LED, HIGH);

  // 1 hour sleep
  ESP.deepSleep(3.6e+9);
}

void loop()
{
  /*//applied for test only
  if(digitalRead(D8)==HIGH && test==0) {
    test=1;
    digitalWrite(BUILTIN_LED, HIGH);
    digitalWrite(motor_pin, HIGH);
    delay(8.33*1000); // 300ml (pump speed 360ml in 10 sec)
    digitalWrite(motor_pin, LOW);
  }
  */
}