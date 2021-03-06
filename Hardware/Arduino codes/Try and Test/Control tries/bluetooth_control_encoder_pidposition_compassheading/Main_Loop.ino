void loop() {
  Time_Now = millis();
  if(Time_Now - Last_Tic >= Sample_Time ){
    Last_Tic = Time_Now;
    
    Temp_Left_Ticks += Left_Encoder_Ticks;
    Left_Encoder_Ticks = 0;
    
    Temp_Right_Ticks += Right_Encoder_Ticks;
    Right_Encoder_Ticks = 0;
    
    Measured_Left_Speed = (Temp_Left_Ticks/180.0)*60.0*(1000.0/Sample_Time);
    Measured_Right_Speed = (Temp_Right_Ticks/180.0)*60.0*(1000.0/Sample_Time);
    
    //removeDrift();
    //controlSpeed();
    
    compass_heading();
    filterCompassReading();
    
    //compass_scalled_reading();
    if(Dir == 'F' || Dir == 'B'){
      headingControl();
    }else{
      Right_Speed = Robot_Speed;
      Left_Speed = Robot_Speed;
    }
    Serial.print(Temp_Left_Ticks);
    Serial.print("\t");
    Serial.print(Temp_Right_Ticks);
    Serial.print("\t");
    Serial.print(bearing);
    Serial.println();
    
    if(Serial.available() > 0){
      Dir = Serial.read();
    }
    driveMotor();
  }
}
