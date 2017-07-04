void driveMotors(){
  driveLeftMotor();
  driveRightMotor();
}

void driveLeftMotor(){
  uint8_t setL_F;
  uint8_t setL_B;
  if(DirLeft == 'F'){
    digitalWrite(Back_Left_Dir,HIGH);
    digitalWrite(Front_Left_Dir,HIGH);
  }else{
    digitalWrite(Back_Left_Dir,LOW);
    digitalWrite(Front_Left_Dir,LOW);
  }
  if(setL <20){
    setL_B = 0;
    setL_F = 0;
  }else{
    setL_B = setL;
    setL_F = setL + 15;
  }
  analogWrite(Back_Left_PWM, setL_B);
  analogWrite(Front_Left_PWM, setL_F);
}

void driveRightMotor(){
  uint8_t setR_F;
  uint8_t setR_B;
  
  if(DirRight == 'F'){
    digitalWrite(Back_Right_Dir,HIGH);
    digitalWrite(Front_Right_Dir,HIGH);
  }else{
    digitalWrite(Back_Right_Dir,LOW);
    digitalWrite(Front_Right_Dir,LOW);
  }
  if(setR <20){
    setR_B = 0;
    setR_F = 0;
  }else{
    setR_B = setR;
    setR_F = setR + 15;
  }
  analogWrite(Back_Right_PWM, setR_B);
  analogWrite(Front_Right_PWM, setR_F);
}
