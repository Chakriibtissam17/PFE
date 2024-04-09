
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x47);
#include <IRremote.h>
int RECV_PIN = A0;
int speeds = 2000; //Initialize speed value
IRrecv irrecv(RECV_PIN);
decode_results results;
#define IR_Go      0x00ff629d
#define IR_Back    0x00ffa857
#define IR_Left    0x00ff22dd
#define IR_Right   0x00ffc23d
#define IR_Stop    0x00ff02fd

void setup() {
  Serial.begin(9600);  //set baud rate to 9600
  pwm.begin();
  pwm.setPWMFreq(60);
  irrecv.enableIRIn(); // enable IR receiver
  stopp();
}

void loop() {
  if (irrecv.decode(&results)) {
    switch (results.value)
    {
      case IR_Go: advance();  //UP
        break;
      case IR_Back: back();   //back
        break;
      case IR_Left: turnL();  //Left
        break;
      case IR_Right: turnR(); //Righ
        break;
      case IR_Stop: stopp();  //stop
        break;
      default: break;
    }
    irrecv.resume();
  }
}

void advance()     // going forward
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
