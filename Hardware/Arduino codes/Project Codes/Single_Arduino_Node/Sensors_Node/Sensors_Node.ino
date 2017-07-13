#include <ros.h>
#include <zuman_msgs/Instruction.h>
#include <Servo.h>

#define Light_Pin 4
#define Yaw_Pin 9
#define Pitch_Pin 10

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
  hw_msg.arg1 = 0;
  hw_msg.arg2 = 0;
  
  if( String(msg.command) == String("cv_rotate_cam") ){
    Yaw_Goal = msg.arg1;
    Pitch_Goal = msg.arg2;
    Cam_Done = HIGH;
    
  }else if( String(msg.command) == String("map_rotate_cam") ){
    Yaw_Goal = msg.arg1;
    Pitch_Goal = msg.arg2;
    Cam_Done = HIGH;
    
  }else if( String(msg.command) == String("set_cam") ){
    Yaw_Goal = msg.arg1;
    Pitch_Goal = msg.arg2;
    Cam_Done = HIGH;
    
  }else if( String(msg.command) == String("switch_on_light") ){
    digitalWrite(Light_Pin,HIGH);
    hw_msg.command = "light_on";
    info_Pub.publish(&hw_msg);
    
  }else if( String(msg.command) == String("switch_off_light") ){
    digitalWrite(Light_Pin,LOW);
    hw_msg.command = "light_off";
    info_Pub.publish(&hw_msg); 
  }
}
ros::Subscriber<zuman_msgs::Instruction> inst_sub("hw_low", &inst_CB);


void setup()  
{
  pinMode(Light_Pin, OUTPUT);
  
  Yaw.attach(Yaw_Pin);
  Pitch.attach(Pitch_Pin);

  nh.initNode();
  nh.subscribe(inst_sub);
  nh.advertise(info_Pub);
}
