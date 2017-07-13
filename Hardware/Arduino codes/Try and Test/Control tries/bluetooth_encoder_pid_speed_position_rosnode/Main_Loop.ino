void loop() {
  Time_Now = millis();
  if(Time_Now - Last_Tic >= Sample_Time ){
    Last_Tic = Time_Now;

    filterReading();

    if(Dir == 'F' || Dir == 'B')
      controlSpeed();
      
    filterMotorSpeed();
    
    if(Move_Ack && Left_Encoder_Ticks <= 0 && Right_Encoder_Ticks <= 0){
      hw_msg.command = "done";
      hw_msg.arg1 = Goal_Distance;
      info_Pub.publish(&hw_msg);
      Move_Ack = LOW;
      Dir == 'S';
      Filtered_Left_Speed = 0;
      Filtered_Right_Speed = 0;
      Measured_Left_Speed = 0;
      Measured_Right_Speed = 0;
    }
    driveMotor();
    nh.spinOnce();
  }
}
