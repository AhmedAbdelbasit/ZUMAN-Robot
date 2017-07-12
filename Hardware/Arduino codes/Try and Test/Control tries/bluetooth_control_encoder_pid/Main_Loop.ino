void loop() {
  Time_Now = millis();
  if(Time_Now - Last_Tic >= Sample_Time ){
    //Serial.println(count_idel);
    count_idel = 0;
    Last_Tic += Sample_Time;
    
    if(Serial.available() > 0){
      Error_Sum_Left = 0;
      Error_Sum_Right = 0;
      Dir = Serial.read();
      if (Dir == 'T' || Dir=='t'){
        tuneSpeedPID();
        Last_Tic = (millis()/Sample_Time)*Sample_Time ; 
      }
    }
    measureSpeed();
    if(Dir != 'S' && Dir != 's'){
      controlSpeed();
    }

    if(Measured_Left_Speed != 0 || Measured_Right_Speed != 0){
      printData();
    }
    filterMotorSpeed();
    driveMotor();
  }else{
    count_idel ++;
  }
}
