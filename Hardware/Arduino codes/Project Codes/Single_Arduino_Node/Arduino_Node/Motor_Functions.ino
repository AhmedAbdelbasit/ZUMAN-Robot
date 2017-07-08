void driveMotors(){
  driveLeftMotor();
  driveRightMotor();
}

void driveLeftMotor(){
  if(DirLeft == 'F'){
    digitalWrite(Back_Left_Dir,HIGH);
    digitalWrite(Front_Left_Dir,HIGH);
  }else{
    digitalWrite(Back_Left_Dir,LOW);
    digitalWrite(Front_Left_Dir,LOW);
  }

  analogWrite(Back_Left_PWM, Left_Speed);
  analogWrite(Front_Left_PWM, Left_Speed);
}

void driveRightMotor(){  
  if(DirRight == 'F'){
    digitalWrite(Back_Right_Dir,HIGH);
    digitalWrite(Front_Right_Dir,HIGH);
  }else{
    digitalWrite(Back_Right_Dir,LOW);
    digitalWrite(Front_Right_Dir,LOW);
  }

  analogWrite(Back_Right_PWM, Right_Speed);
  analogWrite(Front_Right_PWM, Right_Speed);
}
