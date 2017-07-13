float measureDistance(){
  return (Left_Encoder_Ticks + Right_Encoder_Ticks) * Distance_Per_Rev/360.0 ;
}

void printData(){
  Serial.print(Filtered_Left_Read);
  Serial.print("\t\t");
  Serial.print(Filtered_Right_Read);
  Serial.print("\t\t");
  Serial.print(Left_Encoder_Ticks);
  Serial.print("\t\t");
  Serial.print(Right_Encoder_Ticks);
  Serial.print("\t\t");
  Serial.print(measureDistance());
  Serial.print("\t\t");
  Serial.println(Dir);
//  Serial.print(Measured_Left_Speed);
//  Serial.print("\t\t");
//  Serial.println(Measured_Right_Speed);
//  Serial.print("\t\t");
//  Serial.print(analogRead(Front_Left_Cur)*5.0/1024.0);
//  Serial.print("\t\t");
//  Serial.println(analogRead(Front_Right_Cur)*5.0/1024.0);
}

void filterReading(){
  Filtered_Left_Read = (1-Filter_Read_Constant)*Filtered_Left_Read + Filter_Read_Constant*Measured_Left_Speed;
  Filtered_Right_Read = (1-Filter_Read_Constant)*Filtered_Right_Read + Filter_Read_Constant*Measured_Right_Speed;
}

