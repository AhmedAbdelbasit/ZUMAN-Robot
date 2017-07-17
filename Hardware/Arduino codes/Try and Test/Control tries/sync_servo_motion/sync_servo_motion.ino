#include <Servo.h>
#define delay_step 25
#define increament_step 1
#define Light 4
#define Num_Of_Readings 20
#define Yaw_In A0
#define Pitch_In A1

Servo Yaw;
Servo Pitch;

int Yaw_Angle = 90;
int Pitch_Angle = 90;

int Yaw_Goal = 90;
int Pitch_Goal = 90;

char c = 'c';
int degree = 0;


void setup() {
  Serial.begin(9600);
  Yaw.attach(9);
  Pitch.attach(10);

  Yaw_Angle = Yaw.read();
  Pitch_Angle = Pitch.read();

  pinMode(Light, OUTPUT);
  
  Yaw_Goal = Yaw_Angle;
  Pitch_Goal = Pitch_Angle;  
}

void loop() {
  
  if( Serial.available() > 0){
    c = Serial.read();
    degree = Serial.parseInt();
    if(c == 'y'){
      Yaw_Goal = degree;
    }else if(c == 'p'){
      Pitch_Goal = degree;
    }else if(c == 'l'){
      digitalWrite(Light, 1-digitalRead(Light));
    }
  }

//  int y=0, p=0;
//  for (int i=0 ; i<Num_Of_Readings ; i++){
//    y += analogRead(Yaw_In);
//    p += analogRead(Pitch_In);
//  }
//  Yaw_Goal = map(y/Num_Of_Readings, 0, 1023, 10, 170);
//  Pitch_Goal = map(p/Num_Of_Readings, 0, 1023, 10, 170);;
//  
  if(Yaw_Goal > Yaw_Angle){
    Yaw_Angle ++;
  }else if(Yaw_Goal < Yaw_Angle){
    Yaw_Angle --;
  }
  if(Pitch_Goal > Pitch_Angle){
    Pitch_Angle ++;
  }else if(Pitch_Goal < Pitch_Angle){
    Pitch_Angle --;
  }

  Yaw.write(Yaw_Angle);
  Pitch.write(Pitch_Angle);
  
  delay(delay_step);
}

