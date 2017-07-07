void controlSpeed(){
  Error_Right = Robot_Speed - Measured_Right_Speed;
  Error_Sum_Right = Error_Sum_Right + Error_Right*Sample_Time/1000.0;
  float Error_Diff = (Error_Right - Last_Error_Right)*1000.0/Sample_Time;
  Right_Speed = Kp_S * Error_Right + Ki_S * Error_Sum_Right + Kd_S * Error_Diff;
  Last_Error_Right = Error_Right;
}

void setMotorSpeed(){
  Right_Speed = 100 + Kp_S*(40-Right_Distance);
  Left_Speed = 100 - Kp_S*(40-Right_Distance);

  if(Right_Speed>250){
    Right_Speed = 250;
  }
  if(Left_Speed>250){
    Left_Speed = 250;
  }
  if(Right_Speed < 5){
    Right_Speed = 5;
  }
  if(Left_Speed < 5){
    Left_Speed = 5;
  }
}

