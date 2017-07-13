void loop() {
  Time_Now = millis();
  if(Time_Now - Last_Tic >= Sample_Time ){
    Last_Tic += Sample_Time;
    
    if(Serial.available() > 0){
      Error_Sum_Left = 0;
      Error_Sum_Right = 0;
      Last_Error_Left = 0;
      Last_Error_Right = 0;
      
      Dir = Serial.read();
      if (Dir == 'T' || Dir=='t'){
        tuneSpeedPID();
        Dir = 's';
        Last_Tic = (millis()/Sample_Time)*Sample_Time ; 
      }else if(Dir == 'n' || Dir == 'N'){
        digitalWrite(Light_Pin, 1-digitalRead(Light_Pin));
        Dir = 's';
      }
    }
    //measure Speed
    if(Dir == 's' || Dir == 'S'){
      if(millis() - Last_Left_Tick > 100 ){
        Measured_Left_Speed = 0;
      }
      if(millis() - Last_Right_Tick > 100){
        Measured_Right_Speed = 0;
      }
    }
    filterReading();
    if(floor(Filtered_Left_Read) != 0 || floor(Filtered_Right_Read) != 0){
      printData();
    }else{
      Left_Encoder_Ticks = 0;
      Right_Encoder_Ticks = 0;
    }

    if(Dir != 'S' && Dir != 's'){
      controlSpeed();
    }
    
    filterMotorSpeed();
    driveMotor();
  }
}
