#include <ros.h>
#include <zuman_msgs/Instruction.h>
#include <Servo.h>

#include <Wire.h>
#include "compass.h"

#define Light_Pin A0

Servo Yaw;
Servo Pitch;

ros::NodeHandle nh;
zuman_msgs::Instruction hw_msg;
ros::Publisher info_Pub("hw_sensor", &hw_msg);

void inst_CB(const zuman_msgs::Instruction& msg) {
  hw_msg.arg1 = 0;
  hw_msg.arg2 = 0;
  
  if( String(msg.command) == String("cv_rotate_cam") ){
    //rotateCam(msg.arg1);
    hw_msg.command = "cv_done";
    info_Pub.publish(&hw_msg);
    
  }else if( String(msg.command) == String("map_rotate_cam") ){
    //rotateCam(msg.arg1);
    hw_msg.command = "map_done";
    info_Pub.publish(&hw_msg);

    
  }else if( String(msg.command) == String("set_cam") ){
    //setCam(msg.arg1, msg.arg2);
    
  }else if( String(msg.command) == String("switch_on_light") ){
    digitalWrite(Light_Pin,HIGH);
    
  }else if( String(msg.command) == String("switch_off_light") ){
    digitalWrite(Light_Pin,LOW);
    
  }

  
}
ros::Subscriber<zuman_msgs::Instruction> inst_sub("hw_low", &inst_CB);


void setup()  
{
  pinMode(Light_Pin, OUTPUT);
  
  Yaw.attach(12);
  Pitch.attach(13);
  
  nh.initNode();
  nh.subscribe(inst_sub);
  nh.advertise(info_Pub);

  Wire.begin();
  compass_init(2);    //gain factor 1.22

}
