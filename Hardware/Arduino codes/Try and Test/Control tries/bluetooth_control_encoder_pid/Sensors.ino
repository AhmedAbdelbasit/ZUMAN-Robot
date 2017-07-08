void measureSpeed(){
  Measured_Left_Speed = float(Left_Encoder_Ticks/180.0)*60.0*float(1000.0/Sample_Time);
  Left_Encoder_Ticks = 0;
  Measured_Right_Speed = float(Right_Encoder_Ticks/180.0)*60.0*float(1000.0/Sample_Time);
  Right_Encoder_Ticks = 0; 
}

void printData(){
  Serial.print(Measured_Left_Speed);
  Serial.print("\t\t");
  Serial.println(Measured_Right_Speed);
}

void filterMotorSpeed(){
  Filtered_Left_Speed = (1-Filter_Speed_Constant)*Filtered_Left_Speed + Filter_Speed_Constant*Front_Left_Speed;
  Filtered_Right_Speed = (1-Filter_Speed_Constant)*Filtered_Right_Speed + Filter_Speed_Constant*Front_Right_Speed;
}
