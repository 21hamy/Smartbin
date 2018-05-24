#include <Servo.h>
#define ECHO 12  // Espresso lite pin 04
#define TRIG 13  // Espresso lite pin 05
Servo myservo;
int val;

void setup() {
  Serial.begin (115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  myservo.attach(15);

}

void loop() {
  long duration, distance;

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);
  distance = (duration / 2) / 29.1;

  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(10);
  
  if(distance < 30){
    myservo.write(30);
  }else{
    myservo.write(0);
  }

}
