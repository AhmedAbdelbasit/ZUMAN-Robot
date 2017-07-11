#include <Servo.h>
#define delay_step 25
#define increament_step 1
#include <ros.h>
#include <zuman_msgs/Instruction.h>

Servo Yaw;
Servo Pitch;

byte Yaw_Angle = 90;
byte Pitch_Angle = 90;

byte Yaw_Goal = 90;
byte Pitch_Goal = 90;

ros::NodeHandle nh;
zuman_msgs::Instruction _msg;

void inst_CB(const zuman_msgs::Instruction& msg) {
  if( String(msg.command) == String("set_cam")){
    Yaw_Goal = msg.arg1;
    Pitch_Goal = msg.arg2;
  }
}

ros::Subscriber<zuman_msgs::Instruction> inst_sub("hw_low", &inst_CB);
ros::Publisher pos_Pub("hw_low", &_msg);

void setup() {
  Yaw.attach(9);
  Pitch.attach(10);

  Yaw_Angle = Yaw.read();
  Pitch_Angle = Pitch.read();

  Yaw_Goal = Yaw_Angle;
  Pitch_Goal = Pitch_Angle;

  nh.initNode();
  nh.subscribe(inst_sub);
  nh.advertise(pos_Pub);
  
}

void loop() {

  nh.spinOnce();

  if(Yaw_Goal > Yaw_Angle){
    Yaw_Angle ++;
  }else if(Yaw_Goal < Yaw_Angle){
    Yaw_Angle --;
  }
  if(Pitch_Goal > Pitch_Angle){
    Pitch_Angle ++;
  }else if(Pitch_Goal < Pitch_Angle){
    Pitch_Angle --;
  }

  Yaw.write(Yaw_Angle);
  Pitch.write(Pitch_Angle);
  
  delay(delay_step);
}

