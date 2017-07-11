#include <Servo.h>
#define delay_step 25
#define increament_step 1

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
    }
  }

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

