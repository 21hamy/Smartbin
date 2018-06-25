#include <Arduino.h>
#include <MqttConnector.h>

#include <Servo.h>
#include <Wire.h>
#include <VL53L0X.h>

extern Servo myservo;
extern VL53L0X sensor;
extern void close();
extern void open();
extern void readTrash();
extern int val, a, b, mm, cm;

extern MqttConnector* mqtt;

extern String MQTT_CLIENT_ID;
extern String MQTT_PREFIX;

extern int relayPin;
extern int relayPinState;
extern char myName[];



void register_receive_hooks() {
  mqtt->on_subscribe([&](MQTT::Subscribe *sub) -> void {
    Serial.printf("myName = %s \r\n", myName);
    sub->add_topic(MQTT_PREFIX + myName + "/$/+");
    sub->add_topic(MQTT_PREFIX + MQTT_CLIENT_ID + "/$/+");
  });

  mqtt->on_before_message_arrived_once([&](void) { });

  mqtt->on_message([&](const MQTT::Publish & pub) { });

  mqtt->on_after_message_arrived([&](String topic, String cmd, String payload) {
    Serial.printf("topic: %s\r\n", topic.c_str());
    Serial.printf("cmd: %s\r\n", cmd.c_str());
    Serial.printf("payload: %s\r\n", payload.c_str());
    if (cmd == "$/command") {
      if (payload == "ON") {
        open();
      }
      else if (payload == "OFF") {
        close();
        if (val == 0){
          readTrash();
        }
      }
    }
    else if (cmd == "$/reboot") {
      ESP.reset();
    }
    else {
      // another message.
    }
  });
}
