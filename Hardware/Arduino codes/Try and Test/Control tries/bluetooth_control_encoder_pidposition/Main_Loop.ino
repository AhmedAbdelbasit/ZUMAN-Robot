void loop() {
  Time_Now = millis();
  if(Time_Now - Last_Tic >= Sample_Time ){

    Last_Tic += Sample_Time;
       
    if(Serial.available() > 0){
      Dir = Serial.read();
      if(Dir == 'W' || Dir == 'w'){
        clearAccumulation();
        Dir = 'S';
      }else if (Dir == 'T' || Dir == 't'){
        tuneSpeeds();
        Last_Tic = (millis()/Sample_Time)*Sample_Time;
      }
    }
    
    // measurement
    measureOdometry();
    //measureSpeed();

    //control
    //removeDrift();
    //controlSpeed();
    
    // data output
    printData();
    
    filterMotorSpeed();
    driveMotor();
  }
}
