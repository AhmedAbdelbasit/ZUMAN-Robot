void driveMotor(){
  if( Dir=='F'){
    moveForward();
    setMotorSpeed(Front_Left_Speed, Front_Right_Speed, Back_Left_Speed, Back_Right_Speed);
  }else if(Dir == 'B'){
    moveBackward();
    setMotorSpeed(Front_Left_Speed, Front_Right_Speed, Back_Left_Speed, Back_Right_Speed);
  }else if(Dir == 'R'){
    turnRight();
    setMotorSpeed(Front_Left_Speed, Front_Right_Speed, Back_Left_Speed, Back_Right_Speed);
  }else if(Dir == 'L'){
    turnLeft();
    setMotorSpeed(Front_Left_Speed, Front_Right_Speed, Back_Left_Speed, Back_Right_Speed);
  }else if(Dir == 'G'){ // forward left
    moveForward();
    setMotorSpeed(LOW_Front_Left_Speed, HIGH_Front_Right_Speed, LOW_Back_Left_Speed, HIGH_Back_Right_Speed); // (FL FR BL BR)
  }else if(Dir == 'I'){ // forward Right
    moveForward();
    setMotorSpeed(HIGH_Front_Left_Speed, LOW_Front_Right_Speed, HIGH_Back_Left_Speed, LOW_Back_Right_Speed);
  }else if(Dir == 'H'){ // backward left
    moveBackward();
    setMotorSpeed(LOW_Front_Left_Speed, HIGH_Front_Right_Speed, LOW_Back_Left_Speed, HIGH_Back_Right_Speed);
  }else if(Dir == 'J'){ // backward right
    moveBackward();
    setMotorSpeed(HIGH_Front_Left_Speed, LOW_Front_Right_Speed, HIGH_Back_Left_Speed, LOW_Back_Right_Speed);
  }else if(Dir == 'W' || Dir == 'w'){
    Back_Left_Speed += 10;
    Back_Right_Speed += 10;
    if(Back_Left_Speed >250){
      Back_Left_Speed = 250;
    }
    if(Back_Right_Speed >250){
      Back_Right_Speed = 250;
    }
  }else if(Dir == 'U' || Dir == 'u'){
    Back_Left_Speed -= 10;
    Back_Right_Speed -= 10;
    if(Back_Left_Speed < 0){
      Back_Left_Speed = 0;
    }
    if(Back_Right_Speed < 0){
      Back_Right_Speed = 0;
    }
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

void setMotorSpeed(int FL,int FR, int BL, int BR){
  analogWrite(Back_Left_PWM, BL);
  analogWrite(Back_Right_PWM, BR);
  analogWrite(Front_Left_PWM, FL);
  analogWrite(Front_Right_PWM, FR);
}

