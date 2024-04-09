#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x47);
int speeds = 2000; //initialize speed value
int echoPin = 13; // ultrasonic module   ECHO to D13
int trigPin = 12; // ultrasonic module  TRIG to D12

int Ultrasonic_Ranging() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int distance = pulseIn(echoPin, HIGH);  // reading the duration of high level
  distance = distance / 58; // Transform pulse time to distance
  delay(50);
  return distance;
}

void setup() {
  Serial.begin(9600); //set baud rate to 9600
  pwm.begin();
  pwm.setPWMFreq(60);
  stopp();
}

void loop() {
  int distance = Ultrasonic_Ranging();
  Serial.print("distance=");
  Serial.println(distance);
  if (distance < 30) {     //assuming the front distance less than 30cm
    if (distance < 15) {     //assuming the front distance less than 15cm
      stopp();
      delay(100);
      back();
      delay(300);
    }
    else {
      stopp();
      delay(100);
      turnL();
      delay(500);
    }
  }
  else {
    advance();
  }
}

void advance()     // go forward
{
  pwm.setPWM(0, 0, 4095);
  pwm.setPWM(1, 0, speeds);
  pwm.setPWM(2, 0, 4095);
  pwm.setPWM(3, 0, speeds);
  pwm.setPWM(4, 0, 4095);
  pwm.setPWM(5, 0, speeds);
  pwm.setPWM(6, 0, 4095);
  pwm.setPWM(7, 0, speeds);
}
void turnR()
{
  pwm.setPWM(0, 0, 4095);
  pwm.setPWM(1, 0, speeds);
  pwm.setPWM(2, 0, 4095);
  pwm.setPWM(3, 0, speeds);
  pwm.setPWM(4, 0, 0);
  pwm.setPWM(5, 0, speeds);
  pwm.setPWM(6, 0, 0);
  pwm.setPWM(7, 0, speeds);
}
void turnL()
{
  pwm.setPWM(0, 0, 0);
  pwm.setPWM(1, 0, speeds);
  pwm.setPWM(2, 0, 0);
  pwm.setPWM(3, 0, speeds);
  pwm.setPWM(4, 0, 4095);
  pwm.setPWM(5, 0, speeds);
  pwm.setPWM(6, 0, 4095);
  pwm.setPWM(7, 0, speeds);
}
void stopp()         //stop
{
  pwm.setPWM(1, 0, 0);
  pwm.setPWM(3, 0, 0);
  pwm.setPWM(5, 0, 0);
  pwm.setPWM(7, 0, 0);
}
void back()          //back
{
  pwm.setPWM(0, 0, 0);
  pwm.setPWM(1, 0, speeds);
  pwm.setPWM(2, 0, 0);
  pwm.setPWM(3, 0, speeds);
  pwm.setPWM(4, 0, 0);
  pwm.setPWM(5, 0, speeds);
  pwm.setPWM(6, 0, 0);
  pwm.setPWM(7, 0, speeds);
}
