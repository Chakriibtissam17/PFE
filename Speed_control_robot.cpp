#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x47);
int speeds = 2000; //set initial rotation speed of motor

void setup() {
  Serial.begin(9600); //set baud rate to 9600
  pwm.begin();
  pwm.setPWMFreq(60);
  stopp();  //Car stops
}

void loop() {
  if (Serial.available() > 0) {
    switch (Serial.read()) {
      case 'F': advance(); Serial.println("advance");  break;

      case 'B': back();   Serial.println("back"); break;

      case 'L': turnL();  Serial.println("left"); break;

      case 'R': turnR();  Serial.println("right");  break;

      case 'S': stopp();  Serial.println("stop");  break;

      case 'd': while ('d') {        //receive‘d’, motor slows down
          Serial.println(speeds);
          if (speeds >= 5)speeds -= 5; //slow down by 5, minimum to 0
          if (Serial.read() == 'S') {
            Serial.println(speeds);
            break;
          }
        } break;
      case 'a': while ('a') {       //receive‘a’, motor speeds up 
          Serial.println(speeds);
          if (speeds <= 2555)speeds += 5; //speed up by 5, and up to 2560
          if (Serial.read() == 'S') {
            Serial.println(speeds);
            break;
          }
        } break;
    }
  }
}

void advance()     // going forward
{
  pwm.setPWM(0, 0, 4095); //turn clockwise
  pwm.setPWM(1, 0, speeds);
  pwm.setPWM(2, 0, 4095);
  pwm.setPWM(3, 0, speeds);
  pwm.setPWM(4, 0, 4095);
  pwm.setPWM(5, 0, speeds);
  pwm.setPWM(6, 0, 4095);
  pwm.setPWM(7, 0, speeds);
}
void turnR()       //turn right
{
  pwm.setPWM(0, 0, 4095); //turn clockwise
  pwm.setPWM(1, 0, speeds);
  pwm.setPWM(2, 0, 4095);
  pwm.setPWM(3, 0, speeds);
  pwm.setPWM(4, 0, 0); //turn anticlockwise
  pwm.setPWM(5, 0, speeds);
  pwm.setPWM(6, 0, 0);
  pwm.setPWM(7, 0, speeds);
}
void turnL()      //turn left
{
  pwm.setPWM(0, 0, 0); //turn anticlockwise
  pwm.setPWM(1, 0, speeds);
  pwm.setPWM(2, 0, 0);
  pwm.setPWM(3, 0, speeds);
  pwm.setPWM(4, 0, 4095); //turn clockwise
  pwm.setPWM(5, 0, speeds);
  pwm.setPWM(6, 0, 4095);
  pwm.setPWM(7, 0, speeds);
}
void stopp()         //stop
{
  pwm.setPWM(1, 0, 0); //adjust speed as 0
  pwm.setPWM(3, 0, 0);
  pwm.setPWM(5, 0, 0);
  pwm.setPWM(7, 0, 0);
}
void back()          //back
{
  pwm.setPWM(0, 0, 0); //turn anticlockwise
  pwm.setPWM(1, 0, speeds);
  pwm.setPWM(2, 0, 0);
  pwm.setPWM(3, 0, speeds);
  pwm.setPWM(4, 0, 0);
  pwm.setPWM(5, 0, speeds);
  pwm.setPWM(6, 0, 0);
  pwm.setPWM(7, 0, speeds);
}
