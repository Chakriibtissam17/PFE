#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;
int k1=80,k2=120,k3=90;  //initialize the angle value of servo 3

void servo1on(){
  myservo1.write(k1);//rotate to K1
  k1-=1;
  delay(5);
  if(k1<20)k1=20;//rotate to least 20° 
}
void servo1off(){
  myservo1.write(k1);//rotate to K1
  k1+=1;
  delay(5);
  if(k1>80)k1=80;// rotate up to 80° 
}
void servo2up(){
    myservo2.write(k2);//rotate to K2
    k2+=1;
    delay(10);
    if(k2>120)k2=120;//rotate up to 120° 
}
void servo2down(){
    myservo2.write(k2);//rotate to K2
    k2-=1;
    delay(10);
    if(k2<10)k2=10;//rotate to least 10° 
}
void servo3left(){
    myservo3.write(k3);//rotate to K3
    k3+=1;
    delay(10);
    if(k3>180)k3=180;//rotate up to 180° 
}
void servo3right(){
    myservo3.write(k3);//rotate to K3
    k3-=1;
    delay(10);
    if(k3<1)k3=0;//rotate to least 0° 
}

void setup(){
  Serial.begin(9600); //set baud rate to 9600
  myservo1.attach(11);
  myservo2.attach(10);
  myservo3.attach(9);
  myservo1.write(k1);
  delay(1000);
  myservo2.write(k2);
  delay(1000);
  myservo3.write(k3);
  delay(1000);
}

void loop(){
  if(Serial.available()>0){ //receive Bluetooth signals
    switch(Serial.read()){
      case 'f':while('f'){          //arm lifts up
                   servo2up();          
                   if(Serial.read()=='s')break;
               }break;
      case 'b':while('b'){          //arm lowers
                   servo2down();          
                   if(Serial.read()=='s')break;
               }break; 
      case 'l':while('l'){          //arm turns left
                   servo3left();          
                   if(Serial.read()=='s')break;
               }break;
      case 'r':while('r'){          //arm turns right
                   servo3right();          
                   if(Serial.read()=='s')break;
               }break;  
      case 'Q':while('Q'){          //claw opens
                   servo1on();          
                   if(Serial.read()=='s')break;
               }break;  
      case 'E':while('E'){          //claw closes
                   servo1off();          
                   if(Serial.read()=='s')break;
               }break;
    }
  } 
}
