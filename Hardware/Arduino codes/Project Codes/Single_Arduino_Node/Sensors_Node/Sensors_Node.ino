#include <ros.h>
#include <zuman_msgs/Instruction.h>
#include <Servo.h>

#define Yaw_Pin 9
#define Pitch_Pin 10

// Cycle
long Last_Tic;
long Time_Now;
int Sample_Time = 30;

byte Yaw_Goal = 80;
byte Yaw_Angle = 80;
byte Pitch_Goal = 80;
byte Pitch_Angle = 80;

boolean Cam_Done = false;

Servo Yaw;
Servo Pitch;

ros::NodeHandle nh;
zuman_msgs::Instruction hw_msg;
ros::Publisher info_Pub("hw_low", &hw_msg);

void inst_CB(const zuman_msgs::Instruction& msg) {
  hw_msg.arg1 = msg.arg1;
  hw_msg.arg2 = 0;
  
  if( String(msg.command) == String("cv_rotate_cam") ){
    hw_msg.command = "cv_done";
    Yaw_Goal = msg.arg1;
    Pitch_Goal = msg.arg2;
    Cam_Done = HIGH;
    
  }else if( String(msg.command) == String("map_rotate_cam") ){
    hw_msg.command = "map_done";
    Yaw_Goal = msg.arg1;
    Pitch_Goal = msg.arg2;
    Cam_Done = HIGH;
    
  }else if( String(msg.command) == String("set_cam") ){
    Yaw_Goal = msg.arg1;
    Pitch_Goal = msg.arg2;
  }
}
ros::Subscriber<zuman_msgs::Instruction> inst_sub("hw_low", &inst_CB);


void setup()  
{
  Yaw.attach(Yaw_Pin);
  Pitch.attach(Pitch_Pin);

  nh.initNode();
  nh.subscribe(inst_sub);
  nh.advertise(info_Pub);

  Last_Tic = millis();
}
