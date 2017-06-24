void measureOdometry(){

  Inst_Left_Encoder_Ticks = Left_Encoder_Ticks;
  Left_Encoder_Ticks = 0;
  Inst_Right_Encoder_Ticks = Right_Encoder_Ticks;
  Right_Encoder_Ticks = 0;

  Inst_Left_Distance = (Inst_Left_Encoder_Ticks/180.0)*Wheel_Diameter;
  if(DirLeft == 'B'){
    Inst_Left_Distance *= -1;
  }
  Inst_Right_Distance = (Inst_Right_Encoder_Ticks/180.0)*Wheel_Diameter;
  if(DirRight == 'B'){
    Inst_Right_Distance *= -1;
  }
  float Mean_Distance = (Inst_Left_Distance + Inst_Right_Distance)/2.0;
  Inst_Angle = (Inst_Right_Distance - Inst_Left_Distance)/Robot_Width ;
  Angle += Inst_Angle;
  Angle_Deg = Angle*180/PI;
  
  X_Position += Mean_Distance * cos(Angle);
  Y_Position += Mean_Distance * sin(Angle);
  
  //Measured_Left_Speed = (Inst_Left_Encoder_Ticks/180.0)*60.0*(1000.0/Sample_Time);
  //Measured_Right_Speed = (Right_Encoder_Ticks/180.0)*60.0*(1000.0/Sample_Time);

}
