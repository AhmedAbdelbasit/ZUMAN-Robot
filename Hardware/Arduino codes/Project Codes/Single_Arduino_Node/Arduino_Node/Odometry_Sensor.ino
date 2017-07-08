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

  Inst_Left_Distance = (Inst_Left_Encoder_Ticks/180.0)*Distance_Per_Rev;
  if(DirLeft == 'B'){
    Inst_Left_Distance *= -1;
  }
  Inst_Right_Distance = (Inst_Right_Encoder_Ticks/180.0)*Distance_Per_Rev;
  if(DirRight == 'B'){
    Inst_Right_Distance *= -1;
  }
  
  float Mean_Distance = (Inst_Left_Distance + Inst_Right_Distance)/2.0;
  Distance += Mean_Distance;
  X_Position += Mean_Distance * cos(Angle);
  Y_Position += Mean_Distance * sin(Angle);
  
  Angle += Inst_Angle;
}
