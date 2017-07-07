void measureOdometry(){
  int Inst_Left_Encoder_Ticks;
  int Inst_Right_Encoder_Ticks;
  float Inst_Left_Distance;
  float Inst_Right_Distance;
  float Inst_Angle;

  Inst_Left_Encoder_Ticks = Left_Encoder_Ticks;
  Left_Encoder_Ticks = 0;
  Inst_Right_Encoder_Ticks = Right_Encoder_Ticks;
  Right_Encoder_Ticks = 0;

//  Inst_Left_Distance = PI*(Inst_Left_Encoder_Ticks/180.0)*Wheel_Diameter;
//  if(!(digitalRead(Back_Left_Dir))){
//    Inst_Left_Distance *= -1;
//  }
//  Inst_Right_Distance = PI*(Inst_Right_Encoder_Ticks/180.0)*Wheel_Diameter;
//  if(!(digitalRead(Back_Right_Dir))){
//    Inst_Right_Distance *= -1;
//  }
//  float Mean_Distance = (Inst_Left_Distance + Inst_Left_Distance)/2.0;
//  Inst_Angle = (Inst_Right_Distance - Inst_Left_Distance)/Robot_Width ;
//
//  X_Position += Mean_Distance * cos(Angle);
//  Y_Position += Mean_Distance * sin(Angle);
//  Angle += Inst_Angle;
  
  Measured_Left_Speed = (Inst_Left_Encoder_Ticks/180.0)*60.0*(1000.0/Sample_Time);
  Measured_Right_Speed = (Inst_Right_Encoder_Ticks/180.0)*60.0*(1000.0/Sample_Time);

}

void filterMotorSpeed(){
  Filtered_Left_Speed = (1-Filter_Speed_Constant)*Filtered_Left_Speed + Filter_Speed_Constant*Left_Speed;
  Filtered_Right_Speed = (1-Filter_Speed_Constant)*Filtered_Right_Speed + Filter_Speed_Constant*Right_Speed;
}

void printData(){
  //Serial.print(X_Position);
  //Serial.print("\t");
  //Serial.print(Y_Position);
  //Serial.print("\t");
  //Serial.print(Angle*180/PI);
  //Serial.print("\t");
  Serial.print(Measured_Left_Speed);
  Serial.print("\t");
  Serial.print(Measured_Right_Speed);
  Serial.println();
}

