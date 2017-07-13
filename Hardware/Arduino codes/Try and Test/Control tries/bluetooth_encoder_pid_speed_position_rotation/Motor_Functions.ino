void driveMotor(){

  if(Dir == 'F' || Dir == 'f'){
    digitalWrite(Back_Left_Dir,HIGH);
    digitalWrite(Back_Right_Dir,HIGH);
    digitalWrite(Front_Left_Dir,HIGH);
    digitalWrite(Front_Right_Dir,HIGH);
    
  }else if(Dir == 'B' || Dir == 'b'){
    digitalWrite(Back_Left_Dir,LOW);
    digitalWrite(Back_Right_Dir,LOW);
    digitalWrite(Front_Left_Dir,LOW);
    digitalWrite(Front_Right_Dir,LOW);
  
  }else if(Dir == 'L' || Dir == 'l'){
    digitalWrite(Back_Left_Dir,LOW);
    digitalWrite(Back_Right_Dir,HIGH);
    digitalWrite(Front_Left_Dir,LOW);
    digitalWrite(Front_Right_Dir,HIGH);
  
  }else if(Dir == 'R' || Dir == 'r'){
    digitalWrite(Back_Left_Dir,HIGH);
    digitalWrite(Back_Right_Dir,LOW);
    digitalWrite(Front_Left_Dir,HIGH);
    digitalWrite(Front_Right_Dir,LOW);
  }

  analogWrite(Back_Left_PWM, Filtered_Left_Speed);
  analogWrite(Back_Right_PWM, Filtered_Right_Speed);
  analogWrite(Front_Left_PWM, Filtered_Left_Speed);
  analogWrite(Front_Right_PWM, Filtered_Right_Speed);
}

