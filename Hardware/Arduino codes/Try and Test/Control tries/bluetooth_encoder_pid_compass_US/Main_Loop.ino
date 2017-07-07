void loop() {
  Time_Now = millis();
  if(Time_Now - Last_Tic >= Sample_Time ){
    Last_Tic = Time_Now;
    
    if(Serial.available() > 0){
      Temp_Msg = Serial.read();
    }
      
    if (Temp_Msg == 'E'){
      stopMotion();
      Dir = 'S';
      startDebug();
      Temp_Msg = 'S';
    }else{
      Dir = Temp_Msg;
      //takeReadings();
      //applyControl();
      //driveMotors();
      
    }
    //Serial.println("###################################");
  }else{
    //Serial.println("IDLE");
  }
}
