void applyControl(){
  // C_Compass  P_PosEncoder  S_SpeedEncoder   M_MPU   U_Ultrasonic N_Nocontrol
  if(Control_Type == 'C'){
    headingControl();
  }else if(Control_Type == 'P'){
    removeDrift();
  }else if(Control_Type == 'S'){
    controlSpeed();
  }else if(Control_Type == 'M'){
  }else if(Control_Type == 'U'){
  }else if(Control_Type == 'N'){
    
  }
}

void removeDrift(){
  Error_Left = Total_Right_Ticks - Total_Left_Ticks;
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

void headingControl(){
  float Heading_Error = Req_Heading - Filtered_Bearing;
  Heading_Error_Sum += Heading_Error * Sample_Time/1000.0;
  float Error_Diff = (Heading_Error - Last_Heading_Error)*1000.0/Sample_Time;
  float Speed_Change = Kp_H * Heading_Error + Ki_H * Heading_Error_Sum + Kd_H * Error_Diff;
  
  if(Dir == 'F'){
    Left_Speed  = Robot_Speed + Speed_Change;
    Right_Speed  = Robot_Speed - Speed_Change;
  }else if(Dir == 'B'){
    Left_Speed  = Robot_Speed - Speed_Change;
    Right_Speed  = Robot_Speed + Speed_Change;
  }
  if( Left_Speed > 250){
    Left_Speed = 250;
  }else if(Left_Speed < 5){
    Left_Speed = 5;
  }
  
  if( Right_Speed > 250){
    Right_Speed = 250;
  }else if(Right_Speed < 5){
    Right_Speed = 5;
  }
  Last_Heading_Error = Heading_Error;
}
