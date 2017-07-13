void controlSpeed(){
  Error_Left = Robot_Speed - Filtered_Left_Read;
  float Error_Diff = (Error_Left - Last_Error_Left)*1000.0/Sample_Time;
  Last_Error_Left = Error_Left;
  Error_Sum_Left += Error_Left*Sample_Time/1000.0;
  Front_Left_Speed = Kp_S*Error_Left + Ki_S*Error_Sum_Left + Kd_S*Error_Diff;
  
  if(Front_Left_Speed >250){
    Front_Left_Speed = 250;
  }
  if(Front_Left_Speed < 0){
    Front_Left_Speed = 0;
  }
    
  Error_Right = Robot_Speed - Filtered_Right_Read;
  Error_Diff = (Error_Right - Last_Error_Right)*1000.0/Sample_Time;
  Last_Error_Right = Error_Right;
  Error_Sum_Right += Error_Right*Sample_Time/1000.0;
  Front_Right_Speed = Kp_S*Error_Right + Ki_S*Error_Sum_Right + Kd_S*Error_Diff;

  if(Front_Right_Speed >250){
    Front_Right_Speed = 250;
  }
  if(Front_Right_Speed < 0){
    Front_Right_Speed = 0;
  }

  if(Left_Encoder_Ticks <= 0){
    Front_Left_Speed = 0;
  }
  if(Right_Encoder_Ticks <= 0){
    Front_Right_Speed = 0;
  }
  
}

void filterMotorSpeed(){
  Filtered_Left_Speed = (1-Filter_Speed_Constant)*Filtered_Left_Speed + Filter_Speed_Constant*Front_Left_Speed;
  Filtered_Right_Speed = (1-Filter_Speed_Constant)*Filtered_Right_Speed + Filter_Speed_Constant*Front_Right_Speed;
}

