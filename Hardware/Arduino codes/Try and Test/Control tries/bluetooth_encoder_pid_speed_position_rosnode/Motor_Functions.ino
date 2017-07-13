void driveMotor(){

  if(Dir == 'F'){
    digitalWrite(Back_Left_Dir,HIGH);
    digitalWrite(Back_Right_Dir,HIGH);
    digitalWrite(Front_Left_Dir,HIGH);
    digitalWrite(Front_Right_Dir,HIGH);
  }else if(Dir == 'B'){
    digitalWrite(Back_Left_Dir,LOW);
    digitalWrite(Back_Right_Dir,LOW);
    digitalWrite(Front_Left_Dir,LOW);
    digitalWrite(Front_Right_Dir,LOW);
  }
  
  analogWrite(Back_Left_PWM, Filtered_Left_Speed);
  analogWrite(Back_Right_PWM, Filtered_Right_Speed);
  analogWrite(Front_Left_PWM, Filtered_Left_Speed);
  analogWrite(Front_Right_PWM, Filtered_Right_Speed);
}

void rotateRobot(){
  
}

