void driveMotor(){
  if(Dir == 'S' || Dir == 's'){
    Front_Left_Speed = 0;
    Front_Right_Speed = 0;
  }else{
    if( Dir=='F' || Dir=='f'){
      moveForward();
    }else if(Dir == 'B' || Dir=='b'){
      moveBackward();
    }else if(Dir == 'R' || Dir=='r'){
      turnRight();
    }else if(Dir == 'L' || Dir=='l'){
      turnLeft();
    }else{
      Dir = 'S';
      Front_Left_Speed = 0;
      Front_Right_Speed = 0;
    }
  }
  setMotorSpeed(Filtered_Left_Speed, Filtered_Right_Speed, Back_Left_Speed, Back_Right_Speed);
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

void turnLeft(){
  digitalWrite(Back_Left_Dir,LOW);
  digitalWrite(Back_Right_Dir,HIGH);
  digitalWrite(Front_Left_Dir,LOW);
  digitalWrite(Front_Right_Dir,HIGH);
}

void turnRight(){
  digitalWrite(Back_Left_Dir,HIGH);
  digitalWrite(Back_Right_Dir,LOW);
  digitalWrite(Front_Left_Dir,HIGH);
  digitalWrite(Front_Right_Dir,LOW);
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

