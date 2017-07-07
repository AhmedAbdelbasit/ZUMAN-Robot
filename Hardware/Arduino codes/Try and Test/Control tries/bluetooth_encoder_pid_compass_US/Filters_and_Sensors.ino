void filterCompassReading(){
  Filtered_Bearing = (1-Filter_Heading_Constant)*Filtered_Bearing + Filter_Heading_Constant*bearing;
}

void filterMotorSpeed(){
  Filtered_Left_Speed = (1-Filter_Speed_Constant)*Filtered_Left_Speed + Filter_Speed_Constant*Left_Speed;
  Filtered_Right_Speed = (1-Filter_Speed_Constant)*Filtered_Right_Speed + Filter_Speed_Constant*Right_Speed;
}

void takeReadings(){
  // Encoders Ticks
  Instantaneous_Left_Ticks = Left_Encoder_Ticks;
  Left_Encoder_Ticks = 0;
  Instantaneous_Right_Ticks = Left_Encoder_Ticks;
  Right_Encoder_Ticks = 0;
  
  Total_Left_Ticks += Instantaneous_Left_Ticks;
  Total_Right_Ticks += Instantaneous_Right_Ticks;

  // Speed Measure
  Measured_Left_Speed = (Instantaneous_Left_Ticks/180.0)*60.0*(1000.0/Sample_Time);
  Measured_Right_Speed = (Instantaneous_Right_Ticks/180.0)*60.0*(1000.0/Sample_Time);

  // Compass Reading
  compass_heading();
  filterCompassReading();

  // MPU Gyroscope

  // Ultrasonic
  
}

