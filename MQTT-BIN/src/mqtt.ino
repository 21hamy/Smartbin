#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <MqttConnector.h>
#include <Servo.h>
#include <Wire.h>
#include <VL53L0X.h>

#include "init_mqtt.h"
#include "_publish.h"
#include "_receive.h"
#include "_config.h"

Servo myservo;
VL53L0X sensor;
MqttConnector *mqtt; 

char myName[40];
int val, a, b, mm, cm, mapcm;


void init_hardware()
{
  pinMode(relayPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(relayPin, relayPinState);;
  // serial port initialization
  Serial.begin(57600);
  delay(10);
  Serial.println();
  Serial.println("Starting...");
}

void init_wifi() {
  WiFi.disconnect();
  delay(20);
  WiFi.mode(WIFI_STA);
  delay(50);
  const char* ssid =  WIFI_SSID.c_str();
  const char* pass =  WIFI_PASSWORD.c_str();
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf ("Connecting to %s:%s\r\n", ssid, pass);
    delay(300);
  }
  Serial.println("WiFi Connected.");
  digitalWrite(LED_BUILTIN, HIGH);
}

void read()
{
  a = digitalRead(0);
  b = digitalRead(13);
}

void readTrash()
{
  mm = sensor.readRangeContinuousMillimeters();
  cm = mm / 10;
  if (cm > 120)
  {
    cm = 120;
  }
  mapcm = map(cm, 3, 24, 100 , 0);
  Serial.println(cm);
  Serial.println(mapcm);
}

void open()
{
  val = val;
  for (int i = val; i <= 70; i += 4)
  {
    myservo.write(i);
    delay(30);
  }
  val = 70;
}

void close()
{
  val = val;
  myservo.write(val);
  for (int i = val; i >= 0; i--)
  {
    myservo.write(i);
    delay(35);
  }
  val = 0;
}

void setup()
{
  init_hardware();
  init_wifi();
  init_mqtt();

  Wire.begin();
  sensor.init();
  //button
  pinMode(0, INPUT);
  pinMode(13, INPUT);

  //servo
  myservo.attach(15);
  myservo.write(0);
  //sensor
  sensor.setTimeout(500);
  sensor.startContinuous();
}

void loop()
{
  mqtt->loop();
  read();
  if (val == 0){
      readTrash();
  }

}
