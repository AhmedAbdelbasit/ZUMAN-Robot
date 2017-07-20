void loop() {
  Time_Now = millis();
  if(Time_Now - Last_Tic >= Sample_Time ){
    Last_Tic = Time_Now;

    filterReading();

    if(Dir != 'S' && !Manned_Mode)
      controlSpeed();
      
    filterMotorSpeed();
    if(!Manned_Mode){
      checkGoal();
    }
    
    driveMotor();
  }
  nh.spinOnce();
}
