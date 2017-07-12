void measureSpeed(){
  Measured_Left_Speed = float(Left_Encoder_Ticks/180.0)*60.0*float(1000.0/Sample_Time);
  Left_Encoder_Ticks = 0;
  Measured_Right_Speed = float(Right_Encoder_Ticks/180.0)*60.0*float(1000.0/Sample_Time);
  Right_Encoder_Ticks = 0; 
}

void printData(){
  Serial.print(Measured_Left_Speed);
  Serial.print("\t\t");
  Serial.print(Measured_Right_Speed);
  Serial.print("\t\t");
  Serial.print(analogRead(Front_Left_Cur)*5.0/1024.0);
  Serial.print("\t\t");
  Serial.println(analogRead(Front_Right_Cur)*5.0/1024.0);
}

void filterMotorSpeed(){
  Filtered_Left_Speed = (1-Filter_Speed_Constant)*Filtered_Left_Speed + Filter_Speed_Constant*Front_Left_Speed;
  Filtered_Right_Speed = (1-Filter_Speed_Constant)*Filtered_Right_Speed + Filter_Speed_Constant*Front_Right_Speed;
}
