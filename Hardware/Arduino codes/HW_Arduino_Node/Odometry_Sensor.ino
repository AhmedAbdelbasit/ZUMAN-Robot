void measureOdometry(){

  Inst_Left_Encoder_Ticks = Left_Encoder_Ticks;
  Left_Encoder_Ticks = 0;
  Inst_Right_Encoder_Ticks = Right_Encoder_Ticks;
  Right_Encoder_Ticks = 0;

  Inst_Left_Distance = 2*PI*(Inst_Left_Encoder_Ticks/180.0)*Wheel_Radius;
  if(DirLeft == 'B'){
    Inst_Left_Distance *= -1;
  }
  Inst_Right_Distance = 2*PI*(Inst_Right_Encoder_Ticks/180.0)*Wheel_Radius;
  if(DirRight == 'B'){
    Inst_Right_Distance *= -1;
  }
  
  //float Mean_Distance = (Inst_Left_Distance + Inst_Right_Distance)/2.0;
  float R = 0;
  if( Inst_Left_Distance != 0 || Inst_Right_Distance != 0 ){
    if( Inst_Right_Distance != Inst_Left_Distance){
      R = Robot_Width * ( Inst_Left_Distance + Inst_Right_Distance ) / ( 2* (Inst_Right_Distance - Inst_Left_Distance));
      Inst_Angle = (Inst_Right_Distance - Inst_Left_Distance)/Robot_Width ;
      
      X_Position = X_Position + R * sin(Inst_Angle + Angle) - R * sin(Angle);
      Y_Position = Y_Position - R * cos(Inst_Angle + Angle) + R * cos(Angle);
      Angle = Angle + Inst_Angle;
    }else{
      X_Position += Inst_Left_Distance;
      Y_Position += Inst_Left_Distance;
    }
    
  }
  
  //Angle += Inst_Angle;
  //X_Position += Mean_Distance * cos(Angle);
  //Y_Position += Mean_Distance * sin(Angle);
  //X_Position = X_Position + R * sin(Inst_Angle + Angle) - R * sin(Angle);
  //Y_Position = Y_Position - R * cos(Inst_Angle + Angle) + R * cos(Angle);
  //Angle = Angle + Inst_Angle;
  
  //Measured_Left_Speed = (Inst_Left_Encoder_Ticks/180.0)*60.0*(1000.0/Sample_Time);
  //Measured_Right_Speed = (Right_Encoder_Ticks/180.0)*60.0*(1000.0/Sample_Time);
  Angle_Deg = Angle*180/PI;
}
