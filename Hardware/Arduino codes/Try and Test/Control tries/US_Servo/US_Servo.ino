#include <Servo.h>

#define trigR 4
#define echoR 5
#define trigL 6
#define echoL 7
#define Max_Error 10

Servo Left_Servo;
int Left_Angle = 5;

Servo Right_Servo;
int Right_Angle = 5;

float Right_out_dis;
float Last_Right_out_dis;
float Left_out_dis;
float Last_Left_out_dis;

float Left_Reference ;
float Right_Reference ;

float Left_Error;
float Right_Error;

// Cycle
long Last_Tic;
long Time_Now;
int Sample_Time = 250;

bool Mode = HIGH;

void setup() { 
  pinMode(trigR, OUTPUT);
  digitalWrite(trigR, LOW);
  pinMode(echoR, INPUT);
  
  pinMode(trigL, OUTPUT); 
  digitalWrite(trigL, LOW); 
  pinMode(echoL, INPUT); 
  Serial.begin(9600);

  Right_Reference = -1;
  while(Right_Reference == -1){
    Right_Reference = measureDistance(trigR, echoR);
  }
  
  Left_Reference = -1;
  while(Left_Reference == -1){
    Left_Reference = measureDistance(trigL, echoL);
  }

  Last_Right_out_dis = Right_Reference;
  Last_Left_out_dis = Left_Reference;

  Serial.print(Left_Reference);
  Serial.print("\t\t");
  Serial.println(Right_Reference);
  Serial.println("*****************");

  Left_Servo.attach(9);
  Left_Servo.write(90);
  Right_Servo.attach(10);
  Right_Servo.write(90);
  
  Last_Tic = millis();

  
}


