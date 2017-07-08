void measureOdometry(){
  Temp_Right_Ticks = Right_Encoder_Ticks;
  Right_Encoder_Ticks = 0;
  Temp_Left_Ticks = Left_Encoder_Ticks;
  Left_Encoder_Ticks = 0;
  
  Total_Left_Ticks += Temp_Left_Ticks;
  Total_Right_Ticks += Temp_Right_Ticks;
}

void measureSpeed(){
  Measured_Left_Speed = float(Temp_Left_Ticks/180.0)*60.0*float(1000.0/Sample_Time);
  Left_Encoder_Ticks = 0;
  Measured_Right_Speed = float(Temp_Right_Ticks/180.0)*60.0*float(1000.0/Sample_Time);
  Right_Encoder_Ticks = 0; 
}

void printData(){
  Serial.print(Total_Left_Ticks);
  Serial.print("\t\t");
  Serial.println(Total_Right_Ticks);
}

void filterMotorSpeed(){
  Filtered_Left_Speed = (1-Filter_Speed_Constant)*Filtered_Left_Speed + Filter_Speed_Constant*Front_Left_Speed;
  Filtered_Right_Speed = (1-Filter_Speed_Constant)*Filtered_Right_Speed + Filter_Speed_Constant*Front_Right_Speed;
}
