#include <Wire.h>
#include "compass.h"

// CH1
#define Front_Right_Dir 10
#define Front_Right_PWM 11
#define Front_Right_INT 3
//CH2
#define Front_Left_Dir 8
#define Front_Left_PWM 9
#define Front_Left_INT 2
// CH3
#define Back_Right_Dir 7
#define Back_Right_PWM 6
// CH4
#define Back_Left_Dir 4
#define Back_Left_PWM 5

// UltraSonic
#define Left_Trig A0
#define Left_Echo A1
#define Right_Trig A2
#define Right_Echo A3


int Left_Encoder_Ticks=0;
int Right_Encoder_Ticks=0;
int Instantaneous_Left_Ticks;
int Instantaneous_Right_Ticks;
long Total_Left_Ticks = 0;
long Total_Right_Ticks = 0;


// Left-Side Motors Control
float Measured_Left_Speed = 0;
float Error_Left = 0;
float Last_Error_Left = 0;
float Error_Sum_Left = 0;
int Left_Speed = 0;


// Right-Side Motors Control
float Measured_Right_Speed = 0;
float Error_Right = 0;
float Last_Error_Right = 0;
float Error_Sum_Right = 0;
int Right_Speed = 0;


int Robot_Speed = 60;   // rpm
int Req_Heading = 90;


// Cycle
long Last_Tic;
long Time_Now;
int Sample_Time = 50;


char Control_Type = 'C';      // C_Compass  P_PosEncoder  S_SpeedEncoder  M_MPU   U_Ultrasonic 
char Temp_Msg ='S';
char Dir = 'S';


// PID Parameters
float Kp_S=5;
float Ki_S=0;
float Kd_S=0;


float Kp_P=5;
float Ki_P=0;
float Kd_P=0;


float Kp_H=10;
float Ki_H=4;
float Kd_H=0.5;
float Last_Heading_Error = 0;
float Heading_Error_Sum = 0;


// Complimentary Filter
float Filter_Heading_Constant = 0.05;
float Filter_Speed_Constant = 0.05;
float Filtered_Bearing = 0;
int Filtered_Left_Speed=0;
int Filtered_Right_Speed=0;

// UltraSonic
float Left_Duration;
float Left_Distance;
float Right_Duration;
float Right_Distance;

void setup() {
  Serial.begin(38400);
  pinMode(Back_Left_Dir,OUTPUT);
  pinMode(Back_Left_PWM,OUTPUT);
  pinMode(Back_Right_Dir,OUTPUT);
  pinMode(Back_Right_PWM,OUTPUT);
  pinMode(Front_Left_Dir,OUTPUT);
  pinMode(Front_Left_PWM,OUTPUT);
  pinMode(Front_Right_Dir,OUTPUT);
  pinMode(Front_Right_PWM,OUTPUT);
  pinMode(Front_Left_INT, INPUT);
  digitalWrite(Front_Left_INT, HIGH);
  pinMode(Front_Right_INT, INPUT);
  digitalWrite(Front_Right_INT, HIGH);
  delay(10);
  pinMode(Left_Trig,OUTPUT);
  pinMode(Left_Echo,INPUT);
  pinMode(Right_Trig,OUTPUT);
  pinMode(Right_Echo,INPUT);
  delay(10);

  Right_Speed = Robot_Speed;
  Left_Speed = Robot_Speed;
  
  Wire.begin();
  //compass_x_offset = 122.17;
  //compass_y_offset = 230.08;
  //compass_z_offset = 389.85;
  //compass_x_gainError = 1.12;
  //compass_y_gainError = 1.13;
  //compass_z_gainError = 1.03;  
  compass_init(2);
  compass_debug = 1;
  setMotorSpeed(Left_Speed, Right_Speed);
  turnRight();
  //compass_offset_calibration(3);
  stopMotion();
  delay(1000);
  attachInterrupt(1, countRight, FALLING);
  attachInterrupt(0, countLeft,FALLING);
  Last_Tic = millis();
}
