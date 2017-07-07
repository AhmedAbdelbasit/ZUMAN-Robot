void moveStraight(float req_dist){
  Distance = 0;
  DirLeft = 'F';
  DirRight = 'F';
  if(req_dist < 0){
    DirLeft = 'B';
    DirRight = 'B';
  }
  
  while(Distance < req_dist){
    Time_Now = millis();
    if(Time_Now - Last_Tic >= Sample_Time ){
      measureOdometry();
      Last_Tic = Time_Now;
      driveMotors();
    }
  }
  analogWrite(Back_Right_PWM, 0);
  analogWrite(Front_Right_PWM, 0);
  analogWrite(Back_Left_PWM, 0);
  analogWrite(Front_Left_PWM, 0);
  
  hw_msg.command = "moving done";
  hw_msg.arg1 = Distance;
  hw_msg.arg2 = 0;
  info_Pub.publish(&hw_msg);
}

