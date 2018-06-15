#include <Servo.h>
#include <Wire.h>
#include <VL53L0X.h>

#define ECHO 14 // Espresso lite pin 04
#define TRIG 12 // Espresso lite pin 05
Servo myservo;
VL53L0X sensor;

int val, a, b, mm, cm;

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
    Serial.println("More than 120 cm");
  }
  Serial.println(cm);
}

void open()
{
  val = val;
  for (int i = val; i <= 80; i += 4)
  {
    myservo.write(i);
    delay(30);
    read();
  }
  val = 80;
}

void close()
{
  val = val;
  myservo.write(val);
  for (int i = val; i >= 0; i--)
  {
    myservo.write(i);
    delay(35);
    read();
  }
  val = 0;
}

void setup()
{
  Serial.begin(115200);
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
  read();
  if (val == 0){
      readTrash();
  }
  if (a == 0)
  {
    open();
  }
  if (b == 0)
  {
    close();
  }
}
