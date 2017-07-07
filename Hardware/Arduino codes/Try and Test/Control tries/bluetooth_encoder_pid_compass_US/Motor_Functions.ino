void driveMotors(){
  if(Dir == 'S' || Dir == 's'){
    stopMotion();
  }else{
    if( Dir=='F' || Dir == 'f')
      moveForward();
    else if(Dir == 'B' || Dir == 'b')
      moveBackward();
    else if(Dir == 'R' || Dir == 'r')
      turnRight();
    else if(Dir == 'L' || Dir == 'l')
      turnLeft();
    setMotorSpeed(Filtered_Left_Speed, Filtered_Right_Speed);
  }  
}

void moveForward(){
  digitalWrite(Back_Left_Dir,HIGH);
  digitalWrite(Back_Right_Dir,HIGH);
  digitalWrite(Front_Left_Dir,HIGH);
  digitalWrite(Front_Right_Dir,HIGH);
}

void moveBackward(){
  digitalWrite(Back_Left_Dir,LOW);
  digitalWrite(Back_Right_Dir,LOW);
  digitalWrite(Front_Left_Dir,LOW);
  digitalWrite(Front_Right_Dir,LOW);
}

void turnRight(){
  digitalWrite(Back_Left_Dir,HIGH);
  digitalWrite(Back_Right_Dir,LOW);
  digitalWrite(Front_Left_Dir,HIGH);
  digitalWrite(Front_Right_Dir,LOW);
}

void turnLeft(){
  digitalWrite(Back_Left_Dir,LOW);
  digitalWrite(Back_Right_Dir,HIGH);
  digitalWrite(Front_Left_Dir,LOW);
  digitalWrite(Front_Right_Dir,HIGH);
}

void stopMotion(){
  pinMode(Back_Left_PWM, 0);
  pinMode(Back_Right_PWM, 0);
  pinMode(Front_Left_PWM, 0);
  pinMode(Front_Right_PWM, 0);
}

void setMotorSpeed(int L,int R){
  analogWrite(Back_Left_PWM, L);
  analogWrite(Back_Right_PWM, R);
  analogWrite(Front_Left_PWM, L);
  analogWrite(Front_Right_PWM, R);
}

