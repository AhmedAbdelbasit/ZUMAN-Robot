float measureDistance(){
  return ( Goal_Distance*180.0/Distance_Per_Rev + ( abs(Left_Encoder_Ticks + Right_Encoder_Ticks) * Distance_Per_Rev/360.0) ) ;
}

void filterReading(){
  Filtered_Left_Read = (1-Filter_Read_Constant)*Filtered_Left_Read + Filter_Read_Constant*Measured_Left_Speed;
  Filtered_Right_Read = (1-Filter_Read_Constant)*Filtered_Right_Read + Filter_Read_Constant*Measured_Right_Speed;
}

