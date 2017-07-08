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
#define Back_Left_PWM 55

#define LOW_Back_Left_Speed 100
#define LOW_Back_Right_Speed 100
#define LOW_Front_Left_Speed 100
#define LOW_Front_Right_Speed 100

#define HIGH_Back_Left_Speed 200
#define HIGH_Back_Right_Speed 200
#define HIGH_Front_Left_Speed 200
#define HIGH_Front_Right_Speed 200

int Left_Encoder_Ticks=0;
int Right_Encoder_Ticks=0;

// Left-Side Motors Control
float Measured_Left_Speed = 0;
int Back_Left_Speed = 150;
int Front_Left_Speed = 150;

// Right-Side Motors Control
float Measured_Right_Speed = 0;
int Back_Right_Speed = 150;
int Front_Right_Speed = 150;

// Cycle
long Last_Tic;
long Time_Now;
int Sample_Time = 100;
char Dir='F';

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
  
  Last_Tic = millis();
}
