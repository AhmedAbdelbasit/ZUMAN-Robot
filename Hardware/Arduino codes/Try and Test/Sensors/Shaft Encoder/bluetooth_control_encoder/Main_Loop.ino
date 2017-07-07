void loop() {
  Time_Now = millis();
  if(Time_Now - Last_Tic >= Sample_Time ){
    Measured_Left_Speed = (Left_Encoder_Ticks/180.0)*60.0*(1000.0/Sample_Time);
    Left_Encoder_Ticks = 0;
    Measured_Right_Speed = (Right_Encoder_Ticks/180.0)*60.0*(1000.0/Sample_Time);
    Right_Encoder_Ticks = 0;
    Last_Tic = Time_Now;
    Serial.print(Measured_Left_Speed);
    Serial.print("\t");
    Serial.print(Measured_Right_Speed);
    Serial.println();
    if(Serial.available() > 0){
      Dir = Serial.read();
    }
    driveMotor();
  }
}
