void moveStraight(float req_dist){
  float Distance = 0;
  DirLeft = 'F';
  DirRight = 'F';
  
  if(req_dist < 0){
    DirLeft = 'B';
    DirRight = 'B';
  }

  Left_Speed = Cal_Left_Speed;
  Right_Speed = Cal_Right_Speed;
  
  while(Distance < req_dist){
    Time_Now = millis();
    if(Time_Now - Last_Tic >= Sample_Time ){
      Distance += measureDistance();
      Last_Tic = Time_Now;
      driveMotors();
    }
  }
  analogWrite(Back_Right_PWM, 0);
  analogWrite(Front_Right_PWM, 0);
  analogWrite(Back_Left_PWM, 0);
  analogWrite(Front_Left_PWM, 0);
}

void rotateRobot(float angle){
  
}
