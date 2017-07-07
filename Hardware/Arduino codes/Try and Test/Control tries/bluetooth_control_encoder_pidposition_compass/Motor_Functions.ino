void driveMotor(){
  if( Dir=='F'){
    moveForward();
    setMotorSpeed(Left_Speed, Right_Speed);
  }else if(Dir == 'B'){
    moveBackward();
    setMotorSpeed(Left_Speed, Right_Speed);
  }else if(Dir == 'R'){
    turnRight();
    setMotorSpeed(Left_Speed, Right_Speed);
  }else if(Dir == 'L'){
    turnLeft();
    setMotorSpeed(Left_Speed, Right_Speed);
  }else if(Dir == 'W' || Dir == 'w'){
    Temp_Left_Ticks = 0;
    Temp_Right_Ticks = 0;
  }else{
    stopMotion();
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

