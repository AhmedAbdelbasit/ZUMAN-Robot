void removeDrift(){
  Error_Left = Temp_Right_Ticks - Temp_Left_Ticks;
  Error_Sum_Left = Error_Sum_Left + Error_Left*Sample_Time/1000.0;
  float Error_Diff = (Error_Left - Last_Error_Left)*1000.0/Sample_Time;
  
  Left_Speed = Kp_P * Error_Left + Ki_P * Error_Sum_Left + Kd_P * Error_Diff;
  Last_Error_Left = Error_Left;
}

void controlSpeed(){
  Error_Right = Robot_Speed - Measured_Right_Speed;
  Error_Sum_Right = Error_Sum_Right + Error_Right*Sample_Time/1000.0;
  float Error_Diff = (Error_Right - Last_Error_Right)*1000.0/Sample_Time;
  Right_Speed = Kp_S * Error_Right + Ki_S * Error_Sum_Right + Kd_S * Error_Diff;
  Last_Error_Right = Error_Right;
}

