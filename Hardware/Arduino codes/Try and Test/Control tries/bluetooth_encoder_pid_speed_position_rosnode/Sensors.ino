float measureDistance(){
  return ( Goal_Distance*180.0/Distance_Per_Rev + ( abs(Left_Encoder_Ticks + Right_Encoder_Ticks) * Distance_Per_Rev/360.0) ) ;
}

void filterReading(){
  Filtered_Left_Read = (1-Filter_Read_Constant)*Filtered_Left_Read + Filter_Read_Constant*Measured_Left_Speed;
  Filtered_Right_Read = (1-Filter_Read_Constant)*Filtered_Right_Read + Filter_Read_Constant*Measured_Right_Speed;
}

void checkGoal(){
  if(Move_Ack && Left_Encoder_Ticks <= 0 && Right_Encoder_Ticks <= 0){
      hw_msg.arg1 = Goal_Distance;
      info_Pub.publish(&hw_msg);
      Move_Ack = LOW;
      Dir == 'S';
      Filtered_Left_Speed = 0;
      Filtered_Right_Speed = 0;
      Measured_Left_Speed = 0;
      Measured_Right_Speed = 0;
    }else if(Rotate_Ack && Left_Encoder_Ticks <= 0 && Right_Encoder_Ticks <= 0){
      hw_msg.arg1 = Rotation_Tick;
      info_Pub.publish(&hw_msg);
      Rotate_Ack = LOW;
      Dir == 'S';
      Filtered_Left_Speed = 0;
      Filtered_Right_Speed = 0;
      Measured_Left_Speed = 0;
      Measured_Right_Speed = 0;
    }
}

