void loop() {
  Time_Now = millis();
  if(Time_Now - Last_Tic >= Sample_Time ){
    Temp_Left_Ticks += Left_Encoder_Ticks;
    Left_Encoder_Ticks = 0;
    
    Temp_Right_Ticks += Right_Encoder_Ticks;
    Right_Encoder_Ticks = 0;
    
    Measured_Left_Speed = (Temp_Left_Ticks/180.0)*60.0*(1000.0/Sample_Time);
    Measured_Right_Speed = (Temp_Right_Ticks/180.0)*60.0*(1000.0/Sample_Time);
    
    removeDrift();
    //controlSpeed();
    
    Last_Tic = Time_Now;
    //Serial.print(Measured_Left_Speed);
    //Serial.print("\t");
    //Serial.print(Measured_Right_Speed);
    //Serial.println();
    
    
    Serial.print(Temp_Left_Ticks);
    Serial.print("\t");
    Serial.print(Temp_Right_Ticks);
    Serial.println();
    
    if(Serial.available() > 0){
      Dir = Serial.read();
    }
    driveMotor();
  }
}
