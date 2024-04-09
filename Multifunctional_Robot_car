#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x47);
#include <Servo.h>
#include <IRremote.h>
int RECV_PIN = A0;
int echoPin = 13; // ultrasonic module   ECHO to D13
int trigPin = 12; // ultrasonic module  TRIG to D12
IRrecv irrecv(RECV_PIN);
decode_results results;
#define IR_Go      0x00ff629d
#define IR_Back    0x00ffa857
#define IR_Left    0x00ff22dd
#define IR_Right   0x00ffc23d
#define IR_Stop    0x00ff02fd
#define SensorLeft    6   //input pin of left sensor
#define SensorMiddle  7   //input pin of middle sensor
#define SensorRight   8   //input pin of right sensor
unsigned char SL;        //state of left sensor
unsigned char SM;        //state of middle sensor
unsigned char SR;        //state of right sensor
Servo myservo1;
Servo myservo2;
Servo myservo3;

int k1 = 80, k2 = 120, k3 = 90; //initialize angle value of servo 3
int M1[20], M2[20], M3[20];
int i = 0, j = 0, t = 0, speeds = 2000;
char blue_val;
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
  myservo1.attach(11);
  myservo2.attach(10);
  myservo3.attach(9);
  myservo1.write(k1);
  delay(1000);
  myservo2.write(k2);
  delay(1000);
  myservo3.write(k3);
  delay(1000);
  pinMode(SensorLeft, INPUT);
  pinMode(SensorMiddle, INPUT);
  pinMode(SensorRight, INPUT);
  stopp();
  irrecv.enableIRIn(); // enable IR receiver
}

void loop() {
  if (Serial.available() > 0) { //receive Bluetooth signals
    blue_val = Serial.read();
    Serial.println(blue_val);
    switch (blue_val) {
      case 'F': advance(); Serial.println("advance"); break; //receive‘F’, go forward

      case 'B': back();   Serial.println("back");   break; //receive‘B’, go back
      case 'L': turnL();  Serial.println("turn left"); break; //receive‘L’, turn left
      case 'R': turnR();  Serial.println("turn right"); break; //receive‘R’, turn right
      case 'S': stopp();  Serial.println("stop");   break; //receive‘S’, Car stops
      case 'a': speeds_a(); break;//receive‘a’, motor speeds up

      case 'd': speeds_d(); break;//receive‘d’, motor slows down

      case 'f': servo2up(); break;     //robots arm lifts up

      case 'b': servo2down(); break;     //robots arm lowers

      case 'l': servo3left(); break;     //robot arm turns left

      case 'r': servo3right(); break;     //robot arm turns right

      case 'Q': servo1on(); break;      //claw opens

      case 'E': servo1off(); break;     //claw closes

      case 't': read_servo(); break;  //receive‘t’, record action

      case 'i': do_servo(); break;   //receive‘i’, execute motion

      case 'Y': avoid();    Serial.println("avoid"); break;  //receive‘Y’ to enter the obstacle avoidance mode

      case 'X': tracking(); Serial.println("tracking"); break;      //receive‘X’to enter line tracking mode

      case 'U': follow();   Serial.println("follow"); break; //receive‘U’to enter ultrasonic follow mode
      case 'G': Fall();     Serial.println("Fall"); break;      //receive‘G’to enter anti-fall mode
      default: break;
    }
  }

  if (irrecv.decode(&results)) {  //receive IR signals
    switch (results.value) {
      case IR_Go: advance();  break;
      case IR_Back: back();   break;
      case IR_Left: turnL();  break;
      case IR_Right: turnR();  break;
      case IR_Stop: stopp();  break;
      default:  break;
    }
    irrecv.resume();  //
  }

}

void advance()     // going forwards
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

void speeds_a() {
  bool a_flag = 1;
  while (a_flag) {
    Serial.println(speeds);
    if (speeds <= 2555) { //speed up by 5, set the number to change speed, up to 2560
      speeds += 5;
      delay(2);  //change delay time to alter the speed of smart car
    }
    if (Serial.read() == 'S') a_flag = 0; //S’to stop speeding up 
  }
}

void speeds_d() {
  bool d_flag = 1;
  while (d_flag) {
    Serial.println(speeds);
    if (speeds >= 5) { //reduce to 0 at least
      speeds -= 5;
      delay(2);  //change delay time to alter the speed of smart car
    }
    if (Serial.read() == 'S') d_flag = 0; //receive‘S’to stop slowing down 
  }
}

void servo1on() { //claw opens
  bool servo1on_flag = 1;
  while (servo1on_flag) {
    k1 -= 1;
    myservo1.write(k1);
    delay(5);
    if (k1 < 20) {
      k1 = 20;
    }
    if (Serial.read() == 's')servo1on_flag = 0;
  }
}
void servo1off() { //claw closes
  bool servo1off_flag = 1;
  while (servo1off_flag) {
    k1 += 1; //control the rotation accuracy 
    myservo1.write(k1);
    delay(5); //control the rotation speed of servo
    if (k1 > 80) {
      k1 = 80;
    }
    if (Serial.read() == 's')servo1off_flag = 0;
  }
}
void servo2up() { //robot arm lifts up
  bool servo2up_flag = 1;
  while (servo2up_flag) {
    k2 += 1; //Control the rotation accuracy
    myservo2.write(k2);
delay(10); //control rotation speed of servo
    if (k2 > 120) {
      k2 = 120;
    }
    if (Serial.read() == 's')servo2up_flag = 0;
  }
}
void servo2down() { //robot arm lowers
  bool servo2down_flag = 1;
  while (servo2down_flag) {
    k2 -= 1; //control the rotation accuracy
    myservo2.write(k2);
    delay(10); //control the rotation speed of servo
    if (k2 < 10) {
      k2 = 10;
    }
    if (Serial.read() == 's')servo2down_flag = 0;
  }
}
void servo3left() { //robot arm turns left
  bool servo3left_flag = 1;
  while (servo3left_flag) {
    k3 += 1; //control the rotation accuracy
    myservo3.write(k3);
    delay(10); // control the rotation speed of servos
    if (k3 > 180) {
      k3 = 180;
    }
    if (Serial.read() == 's')servo3left_flag = 0;
  }
}
void servo3right() { //robot arm turns right
  bool servo3right_flag = 1;
  while (servo3right_flag) {
    k3 -= 1; //control the rotation accuracy
    myservo3.write(k3);
    delay(10); //control the rotation speed of servos
    if (k3 < 1) {
      k3 = 0;
    }
    if (Serial.read() == 's')servo3right_flag = 0;
  }
}

void read_servo() {
  M1[i] = myservo1.read(); //save the current angles of servos in array 
  delay(100); //add delay time to save angle value
  M2[i] = myservo2.read();
  delay(100);
  M3[i] = myservo3.read();
  delay(100);
  i++;  // i adds 1 every time i is saved
  j = i; //set the value of i to j
  //  if(i>20)i=19;
  delay(200);
}

void do_servo() {
  i = 0; //i clears 0
  t = 1; //used for while loop
  k1 = myservo1.read(); //read the current angle value and set them to k1,k2,k3
  k2 = myservo2.read();
  k3 = myservo3.read();

  while (t) {
for (int k = 0; k < j; k++) { //loop j times to execute all motions saved
      if (k1 < M1[k]) { //if angle value of servo 1 is less than the value saved in array 1
        while (k1 < M1[k]) { //while loops, make servo rotate where the value saved in array
          myservo1.write(k1); //servo 1 executes actions
          k1++;   //k1adds 1
          delay(10); //delay in 10ms, control the rotation speed of servos
        }
      }
      else {  //if the angle of servo 1 is more than the vale saved in array 1.
        while (k1 > M1[k]) { //while loops，make servo rotate the location where the value is saved in array
          myservo1.write(k1); //servo 1 executes actions
          k1--;   //k1 reduces 1
          delay(10); //delay 10ms to control rotation speed of servos
        }
      }
      //the same below
      if (k2 < M2[k]) {
        while (k2 < M2[k]) {
          myservo2.write(k2);
          k2++;
          delay(10);
        }
      }
      else {
        while (k2 > M2[k]) {
          myservo2.write(k2);
          k2--;
          delay(10);
        }
      }

      if (k3 < M3[k]) {
        while (k3 < M3[k]) {
          myservo3.write(k3);
          k3++;
          delay(10);
        }
      }
      else {
        while (k3 > M3[k]) {
          myservo3.write(k3);
          k3--;
          delay(10);
        }
      }

      if (Serial.available() > 0) { //in order to exit loop
        if (Serial.read() == 't') { //receive‘i’ then‘t’
          t = 0; //set t to 0，exit while loop
          break;  //exit
        }
      }
    }
  }
}

void avoid() { //self-going, ultrasonic obstacle avoidance
  bool avoid_flag = 1;
  while (avoid_flag) {
    int distance = Ultrasonic_Ranging();
    Serial.print("distance=");
    Serial.println(distance);
    if (distance < 30) { //assuming the front distance less than 30cm
      if (distance < 15) { //assuming the front distance less than 15cm
        stopp();
        delay(100);
        back();
        delay(300);
      }
      else { //when 10 <the distance<30, turn right
        stopp();
        delay(100);
        turnR();
        delay(500);
      }
    }
    else {  //when the distance>30, go forward
      advance();
    }
    blue_val = Serial.read();
    if (blue_val == 'S') {
      stopp();
      avoid_flag = 0;
    }
  }
}

void tracking(void) {   //follow black lines
  bool tracking_flag = 1;
  while (tracking_flag) {
    SL = digitalRead(SensorLeft);
    SM = digitalRead(SensorMiddle);
    SR = digitalRead(SensorRight);
    if (SM == HIGH) {
      if (SL == LOW && SR == HIGH) {  // black on right, white on left, turn right
        turnR();
      }
      else if (SR == LOW && SL == HIGH) {  // black on left, white on right, turn left
        turnL();
      }
      else {  // white on both sides, going forward
        advance();
      }
    }
    else {
      if (SL == LOW && SR == HIGH) { // black on right, white on left, turn right
        turnR();
      }
      else if (SR == LOW && SL == HIGH) {  // white on right, black on left, turn left
        turnL();
      }
      else { // all white, stop
        stopp() ;
      }
    }
    blue_val = Serial.read();
    if (blue_val == 'S') {
      stopp();
      tracking_flag = 0;
    }
  }
}

void follow() {   //ultrasonic follow
  bool follow_flag = 1;
  while (follow_flag) {
    int distance = Ultrasonic_Ranging();
    Serial.print("distance=");
    Serial.println(distance);
    if (distance < 15) { //when the distance is less than 15, go back      back();
    }
    else if (distance >= 15 && distance < 20) { //when the distance is in 15~20, stop
      stopp();
    }
    else if (distance >= 20 && distance < 40) { //when the distance is in 20~40, go forward
      advance();
    }
    else {
      stopp();  //otherwise, stop
    }
    blue_val = Serial.read();
    if (blue_val == 'S') {
      stopp();
      follow_flag = 0;
    }
  }
}

void Fall(void) {   //anti-fall
  bool Fall_flag = 1;
  while (Fall_flag) {
    SL = digitalRead(SensorLeft);
    SM = digitalRead(SensorMiddle);
    SR = digitalRead(SensorRight);
    if (SM == HIGH || SL == HIGH || SR == HIGH) {
      back();
      delay(500);
      turnL();
      delay(500);
    }
    else {
      advance();
    }
    blue_val = Serial.read();
    if (blue_val == 'S') {
      stopp();
      Fall_flag = 0;
    }
  }
}
