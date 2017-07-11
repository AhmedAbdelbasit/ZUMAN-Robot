#include <Wire.h>
#include "compass.h"
#include <Servo.h>

Servo Compass_Servo;

float Filtered_X_Reading;
float Filtered_Y_Reading;
float Filter_Constant = 0.1;

char Deg = 's';

void setup(){
  Serial.begin(9600);
  Wire.begin();
  compass_init(2);    //gain factor 1.22

  Compass_Servo.attach(9);
  delay(10);
  Compass_Servo.write(90);
  
}

int tt = 0;
void loop(){
  compass_read_XYZdata();
  Serial.print(compass_x);
  Serial.print("\t\t");
  Serial.print(compass_y);
  Serial.print("\t\t");
  Serial.println(compass_z);

  
  delay(100);

  if(Serial.available() > 0){
    Deg = Serial.read();
    if (Deg == 'r'){
      rotateRobot(Deg);
      //Compass_Servo.write(10);
      Deg = 's';
    }else if (Deg == 'l'){
      rotateRobot(Deg);
      //Compass_Servo.write(170);
      Deg = 's';
    }else if (Deg == 'c'){
      Compass_Servo.write(90);
      Deg = 's';
    }
  }
}

