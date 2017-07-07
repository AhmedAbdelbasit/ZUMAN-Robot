void driveMotors(){
  if(Dir == 'S' || Dir == 's'){
    Left_Speed = 0;
    Right_Speed = 0;
  }else{
    Left_Speed = Cal_Left_Speed;
    Right_Speed = Cal_Right_Speed;
    
    if( Dir=='F' || Dir == 'f'){
      moveForward();
    }else if(Dir == 'B' || Dir == 'b'){
      moveBackward();
    }else if(Dir == 'R' || Dir == 'r'){
      turnRight();
    }else if(Dir == 'L' || Dir == 'l'){
      turnLeft();
    }else{
      Dir = 's';
      Left_Speed = 0;
      Right_Speed = 0;
    }
  }
  setMotorSpeed(Filtered_Left_Speed,Filtered_Right_Speed, Filtered_Left_Speed, Filtered_Right_Speed);     // FL, FR, BL, BR
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
  digitalWrite(Back_Left_Dir,HIGH);
  digitalWrite(Back_Right_Dir,LOW);
  digitalWrite(Front_Left_Dir,HIGH);
  digitalWrite(Front_Right_Dir,LOW);
}

void turnRight(){
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

void setMotorSpeed(float FL,float FR, float BL, float BR){
  analogWrite(Back_Left_PWM, floor(BL));
  analogWrite(Back_Right_PWM, floor(BR));
  analogWrite(Front_Left_PWM, floor(FL));
  analogWrite(Front_Right_PWM, floor(FR));
}

