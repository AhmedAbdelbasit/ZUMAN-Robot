#include <ros.h>
#include <zuman_msgs/Instruction.h>

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

// Odometry
#define Robot_Width 33
#define Distance_Per_Rev 38.73

// Calibrated Speeds
int Cal_Left_Speed = 80;
int Cal_Right_Speed = 90;
int Left_Speed;
int Right_Speed;

int Left_Encoder_Ticks=0;
int Right_Encoder_Ticks=0;

float X_Position = 0;
float Y_Position = 0;
float Angle = PI/2;

char DirLeft = 'F';
char DirRight = 'F';

// Cycle
long Last_Tic;
long Time_Now;
int Sample_Time = 100;

float Distance;

ros::NodeHandle nh;
zuman_msgs::Instruction hw_msg;
ros::Publisher info_Pub("hw_low", &hw_msg);

void inst_CB(const zuman_msgs::Instruction& msg) {
  if( String(msg.command) == String("move")){
    Last_Tic = millis();
    moveStraight(msg.arg1);
  }else if( String(msg.command) == String("calspeed")){
    Cal_Left_Speed = floor(msg.arg1);
    Cal_Right_Speed = floor(msg.arg2);
    delay(20);
    hw_msg.command = "speed_set";
    hw_msg.arg1 = Cal_Left_Speed;
    hw_msg.arg2 = Cal_Right_Speed;
    info_Pub.publish(&hw_msg);
  }else if( String(msg.command) == String("set_PWM") ){
    moveRobot(msg.arg1, msg.arg2);
  }
}
ros::Subscriber<zuman_msgs::Instruction> inst_sub("hw_low", &inst_CB);


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
  
  pinMode(Front_Left_INT, INPUT);
  digitalWrite(Front_Left_INT, HIGH);
  pinMode(Front_Right_INT, INPUT);
  digitalWrite(Front_Right_INT, HIGH);
  delay(10);
  attachInterrupt(1, countLeft,FALLING);
  attachInterrupt(0, countRight,FALLING);

  nh.initNode();
  nh.subscribe(inst_sub);
  nh.advertise(info_Pub);
  
  Last_Tic = millis();
}
