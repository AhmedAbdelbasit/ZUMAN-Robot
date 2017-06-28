#include <ros.h>
#include <zuman_msgs/Odometry.h>
#include <zuman_msgs/Instruction.h>

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
#define Robot_Width 42
#define Wheel_Diameter 13

// Calibrated Speeds
#define Cal_Left_Speed 130
#define Cal_Right_Speed 105

int Left_Encoder_Ticks=0;
int Right_Encoder_Ticks=0;
long Total_Left_Encoder_Ticks;
long Total_Right_Encoder_Ticks;
int Inst_Left_Encoder_Ticks;
int Inst_Right_Encoder_Ticks;

float Inst_Left_Distance;
float Inst_Right_Distance;
float Inst_Angle;
float X_Position = 0;
float Y_Position = 0;
float Angle = PI/2;
float Angle_Deg=0;

uint8_t setL;
uint8_t setR;
char DirLeft = 'F';
char DirRight = 'F';

// Cycle
long Last_Tic;
long Time_Now;
int Sample_Time = 100;
char Dir='S';

void inst_CB(const zuman_msgs::Instruction& msg) {
  if( String(msg.command) == String("clear_odometry") ){
    X_Position = 0;
    Y_Position = 0;
    Angle = PI/2;
  }else if( String(msg.command) == String("set_PWM") ){
    DirLeft='F';
    DirRight='F';
    
    if(msg.arg1 <512)
      DirLeft='B';
    if(msg.arg2 <512)
      DirRight='B';
      
    setL = abs((msg.arg1-512)/2.0 );
    setR = abs((msg.arg2-512)/2.0 );
  }
}

ros::NodeHandle nh;
zuman_msgs::Odometry pos_msg;

ros::Subscriber<zuman_msgs::Instruction> inst_sub("HW_instruction", &inst_CB);
ros::Publisher pos_Pub("pos_odometry", &pos_msg);



void setup()  
{
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

  nh.initNode();
  nh.subscribe(inst_sub);
  nh.advertise(pos_Pub);
  
  Last_Tic = millis();
}
