void loop() {
  Time_Now = millis();
  if(Time_Now - Last_Tic >= Sample_Time ){
    Last_Tic = Time_Now;

    filterReading();

    if(Dir != 'S')
      controlSpeed();
      
    filterMotorSpeed();

    checkGoal();
    
    driveMotor();
  }
  nh.spinOnce();
}
