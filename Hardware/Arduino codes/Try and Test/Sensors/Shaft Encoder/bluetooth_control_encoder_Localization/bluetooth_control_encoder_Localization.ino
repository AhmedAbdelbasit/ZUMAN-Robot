// CH1
#define Back_Left_Dir 10
#define Back_Left_PWM 11
#define Back_Left_INT 3
//CH2
#define Back_Right_Dir 8
#define Back_Right_PWM 9
#define Back_Right_INT 2
// CH3
#define Front_Left_Dir 7
#define Front_Left_PWM 6
// CH4
#define Front_Right_Dir 4
#define Front_Right_PWM 5

// Odometry
#define Robot_Width 33
#define Wheel_Diameter 12.5

// Calibrated Speeds
int Cal_Left_Speed  = 50 ;
int Cal_Right_Speed = 50 ;

int Left_Encoder_Ticks=0;
int Right_Encoder_Ticks=0;
long Total_Left_Encoder_Ticks;
long Total_Right_Encoder_Ticks;

float X_Position = 0;
float Y_Position = 0;
float Angle = 0;


// Left-Side Motors Control
float Measured_Left_Speed = 0;
int Back_Left_Speed = 0;
int Front_Left_Speed = 0;
int Left_Speed = 0;

// Right-Side Motors Control
float Measured_Right_Speed = 0;
int Back_Right_Speed = 0;
int Front_Right_Speed = 0;
int Right_Speed = 0;

// Cycle
long Last_Tic;
long Time_Now;
int Sample_Time = 500;
char Dir='S';

float Filter_Speed_Constant = 0.25;
float Filtered_Left_Speed=0;
float Filtered_Right_Speed=0;

void setup() {
  Serial.begin(9600);
  pinMode(Back_Left_Dir,OUTPUT);
  pinMode(Back_Left_PWM,OUTPUT);
  pinMode(Back_Right_Dir,OUTPUT);
  pinMode(Back_Right_PWM,OUTPUT);
  pinMode(Front_Left_Dir,OUTPUT);
  pinMode(Front_Left_PWM,OUTPUT);
  pinMode(Front_Right_Dir,OUTPUT);
  pinMode(Front_Right_PWM,OUTPUT);
  
  pinMode(Back_Left_INT, INPUT);
  digitalWrite(Back_Left_INT, HIGH);
  pinMode(Back_Right_INT, INPUT);
  digitalWrite(Back_Right_INT, HIGH);
  delay(10);
  attachInterrupt(1, countLeft,FALLING);
  attachInterrupt(0, countRight,FALLING);
  
  Last_Tic = millis();
}
