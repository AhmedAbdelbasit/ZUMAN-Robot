#include <Servo.h>
#define delay_step 25
#define increament_step 1

Servo Yaw;
Servo Pitch;

int Yaw_Angle = 90;
int Pitch_Angle = 90;

char c = 'c';
int degree = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Yaw.attach(9);
  Pitch.attach(10);

  Yaw_Angle = Yaw.read();
  Pitch_Angle = Pitch.read();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if( Serial.available() > 0){
    c = Serial.read();
    degree = Serial.parseInt();
    if(c == 'y'){
      Yaw_Angle = rotateServo(Yaw, Yaw_Angle, degree);
    }else if(c == 'p'){
      Pitch_Angle = rotateServo(Pitch, Pitch_Angle, degree);
    }
    
//    c = Serial.read();
//    if( c == 'r'){
//      Yaw.write(10);
//    }else if( c == 'l'){
//      Yaw.write(170);
//    }else if( c == 'u'){
//      Pitch.write(10);
//    }else if( c == 'd'){
//      Pitch.write(170);
//    }else if( c == 'c'){
//      Pitch.write(90);
//      Yaw.write(90);
//    }
  }
  delay(100);
}

int rotateServo(Servo S, int Current, int deg){
  int goal;
  if (Current + deg > 170){
    goal = 170;
  }else if (Current + deg < 10){
    goal = 10;
  }else{
    goal = Current + deg;
  }

  if(goal > Current){
    for (int i=Current ; i<goal ; i+= increament_step ){
      S.write(i);
      Current = i;
      delay(delay_step);
    }
  }else{
    for (int i=Current ; i>goal ; i-= increament_step ){
      S.write(i);
      Current = i;
      delay(delay_step);
    }
  }

  return Current;
}

