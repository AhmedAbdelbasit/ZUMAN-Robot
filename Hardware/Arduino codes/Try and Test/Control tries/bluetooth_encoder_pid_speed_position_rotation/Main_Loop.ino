void loop() {
  Time_Now = millis();
  if(Time_Now - Last_Tic >= Sample_Time ){
    Last_Tic += Sample_Time;

    executeCallback();
//    Serial.println(Dir);
    filterReading();
//    Serial.println(Dir);
    if(Dir != 's' && Dir != 'S'){
      controlSpeed();
      printData();
    }
//    Serial.println(Dir);
    filterMotorSpeed();
//    Serial.println(Dir);
    
    checkGoal();
//    Serial.println(Dir);
    driveMotor();
  }
}
