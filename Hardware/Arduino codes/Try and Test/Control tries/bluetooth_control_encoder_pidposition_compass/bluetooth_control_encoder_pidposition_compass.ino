// Compass
#include <Wire.h>
#include <HMC5883L.h>
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

int Left_Encoder_Ticks=0;
int Right_Encoder_Ticks=0;
int Temp_Left_Ticks = 0;
int Temp_Right_Ticks = 0;

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

int Robot_Speed = 100;

// Cycle
long Last_Tic;
long Time_Now;
int Sample_Time = 100;
char Dir='S';

// PID Parameters
float Kp_S=3;
float Ki_S=0.5;
float Kd_S=0.2;

float Kp_P=5;
float Ki_P=1;
float Kd_P=0.2;

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
  
  Right_Speed = Robot_Speed;
  Left_Speed = Robot_Speed;
  
  Wire.begin();
  compass_x_offset = 122.17;
  compass_y_offset = 230.08;
  compass_z_offset = 389.85;
  compass_x_gainError = 1.12;
  compass_y_gainError = 1.13;
  compass_z_gainError = 1.03;  
  compass_init(2);
  compass_debug = 1;
  setMotorSpeed(Left_Speed, Right_Speed);
  turnRight();
  compass_offset_calibration(3);
  stopMotion();
  delay(1000);
  attachInterrupt(1, countRight, FALLING);
  attachInterrupt(0, countLeft,FALLING);
  Last_Tic = millis();
}
