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

// Left-Side Motors Control
float Measured_Left_Speed = 0;
float Error_Left = 0;
float Last_Error_Left = 0;
float Error_Sum_Left = 0;
int Back_Left_Speed = 0;
int Front_Left_Speed = 50;

// Right-Side Motors Control
float Measured_Right_Speed = 0;
float Error_Right = 0;
float Last_Error_Right = 0;
float Error_Sum_Right = 0;
int Back_Right_Speed = 0;
int Front_Right_Speed = 50;

float Robot_Speed = 40;
float Filter_Speed_Constant = 0.1;
int Filtered_Left_Speed = 0;
int Filtered_Right_Speed = 0;

// Cycle
long Last_Tic;
long Time_Now;
int Sample_Time = 100;
char Dir='S';

// PID Parameters
float Kp_S= 1.2;
float Ki_S= 1.25;
float Kd_S= 0.4;

int count_idel = 0;

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
  attachInterrupt(0, countLeft,FALLING);
  attachInterrupt(1, countRight,FALLING);
  
  Last_Tic = (millis()/Sample_Time)*Sample_Time;
}
