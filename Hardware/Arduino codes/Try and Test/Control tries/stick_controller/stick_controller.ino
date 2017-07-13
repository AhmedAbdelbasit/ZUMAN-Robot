#include <ros.h>
#include <zuman_msgs/Instruction.h>

#define Switch_Pin 4
#define Left_Pot_Pin A0
#define Right_Pot_Pin A1
#define Yaw_Pot_Pin A2
#define Pitch_Pot_Pin A3

#define Sample_Time 1000
#define ReadingsPerTick 10

int16_t Left_Pot = 512 ;
int16_t Right_Pot = 512 ;
int16_t Yaw_Pot = 512 ;
int16_t Pitch_Pot = 512 ;

int16_t Last_Left = 0;
int16_t Last_Right = 0;
int16_t Last_Yaw = 80;
int16_t Last_Pitch = 80;

boolean Switch_State = false;
boolean Spin = HIGH;

zuman_msgs::Instruction _msg;
ros::Publisher pub("hw_low", &_msg);
ros::NodeHandle nh;


void setup(){

  pinMode(Switch_Pin, INPUT);
  nh.initNode();
  nh.advertise(pub);

}

void loop(){

  readPots();

  Spin = HIGH;
  
  if( Left_Pot != Last_Left || Right_Pot != Last_Right){
    _msg.command = "set_pwm";
    _msg.arg1 = Left_Pot;
    _msg.arg2 = Right_Pot;
    pub.publish(&_msg);
    Last_Left = Left_Pot;
    Last_Right = Right_Pot;
    nh.spinOnce();
    Spin = LOW;
  }
  
  if( Yaw_Pot != Last_Yaw || Pitch_Pot != Last_Pitch){
    _msg.command = "set_cam";
    _msg.arg1 = Yaw_Pot;
    _msg.arg2 = Pitch_Pot;
    pub.publish(&_msg);
    Last_Yaw = Yaw_Pot;
    Last_Pitch = Pitch_Pot;
    nh.spinOnce();
    Spin = LOW;
  }
  
  if(Spin){
    nh.spinOnce();
  }
  delay(Sample_Time);
}

void readPots(){
  int l = 0, 
      r = 0, 
      y = 0, 
      p = 0;
  
  for(int i=0; i<ReadingsPerTick ; i++){
    l += analogRead(Left_Pot_Pin);
    r += analogRead(Right_Pot_Pin);
    y += analogRead(Yaw_Pot_Pin);
    p += analogRead(Pitch_Pot_Pin);
  }
  Left_Pot = map(l/ReadingsPerTick, 0, 1023, -150, 150);
  Right_Pot = map(r/ReadingsPerTick, 0, 1023, -150, 150);
  Yaw_Pot = map(y/ReadingsPerTick, 0, 1023, 10, 170);
  Pitch_Pot = map(p/ReadingsPerTick, 0, 1023, 10, 170);
}

void printData(){
  Serial.print(digitalRead(Switch_Pin));
  Serial.print("\t\t");
  Serial.print(Left_Pot);
  Serial.print("\t\t");
  Serial.print(Right_Pot);
  Serial.print("\t\t");
  Serial.print(Yaw_Pot);
  Serial.print("\t\t");
  Serial.println(Pitch_Pot);
}

