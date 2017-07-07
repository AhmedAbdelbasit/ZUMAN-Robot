void startDebug(){
  Serial.println("W: clear encoder ticks");
  Serial.println("U: Reset Heading Var/Set Current");
  Serial.println("T: Compass Calibration");
  Serial.println("C: Controller Type");
  Serial.println("S: Tune Speed PID");
  Serial.println("P: Tune Pos PID");
  Serial.println("H: Tune Compass PID");
  Serial.println("F: Tune Filter");

  
  while(Serial.available() < 1){}
  char Temp_Msg = Serial.read();
  
  if(Temp_Msg == 'W' || Temp_Msg == 'w'){
    Total_Left_Ticks = 0;
    Total_Right_Ticks = 0;
  }else if(Temp_Msg == 'U' || Temp_Msg == 'u'){
    Heading_Error_Sum = 0;
    Last_Heading_Error = 0;
    Req_Heading = Filtered_Bearing;
  }else if(Temp_Msg == 'T' || Temp_Msg == 't'){
    setMotorSpeed(Left_Speed, Right_Speed);
    turnRight();
    compass_offset_calibration(3);
    stopMotion();
    Heading_Error_Sum = 0;
    Last_Heading_Error = 0;
  }else if(Temp_Msg == 'C' || Temp_Msg == 'c'){
    selectControllerType();
  }else if(Temp_Msg == 'S' || Temp_Msg == 's'){
    tuneSpeedPID();
  }else if(Temp_Msg == 'P' || Temp_Msg == 'p'){
    tunePositionPID();
  }else if(Temp_Msg == 'H' || Temp_Msg == 'h'){
    tuneHeadingPID();
  }else if(Temp_Msg == 'F' || Temp_Msg == 'f'){
    tuneFilters();
  }
}

void tuneSpeedPID(){
  Serial.println("_#_Speed PID Tuning_#_");
  Serial.println("Q: Kp+=0.1");
  Serial.println("A: Kp-=0.1");
  Serial.println("Z: Ki+=0.1");
  Serial.println("X: Ki-=0.1");
  Serial.println("C: Kd+=0.1");
  Serial.println("V: Kd-=0.1");
  Serial.println("E: Exit");
  Serial.println("_______");
  char C;
  while(1){
    while(Serial.available()<1){}
    C = Serial.read();
    if(C=='Q')
      Kp_S += 0.1;
    else if(C=='A')
      Kp_S -= 0.1;
    else if(C=='Z')
      Ki_S += 0.1;
    else if(C=='X')
      Ki_S -= 0.1;
    else if(C=='C')
      Kd_S += 0.1;
    else if(C=='V')
      Kd_S -= 0.1;
    else if(C=='E')
      break;

    Serial.print(Kp_S);
    Serial.print("\t\t");
    Serial.print(Ki_S);
    Serial.print("\t\t");
    Serial.println(Kd_S);
  }
}

void tunePositionPID(){
  Serial.println("_#_Position PID Tuning_#_");
  Serial.println("Q: Kp+=0.1");
  Serial.println("A: Kp-=0.1");
  Serial.println("Z: Ki+=0.1");
  Serial.println("X: Ki-=0.1");
  Serial.println("C: Kd+=0.1");
  Serial.println("V: Kd-=0.1");
  Serial.println("E: Exit");
  Serial.println("_______");
  
  char C;
  while(1){
    while(Serial.available()<1){}
    C = Serial.read();
    if(C=='Q')
      Kp_P += 0.1;
    else if(C=='A')
      Kp_P -= 0.1;
    else if(C=='Z')
      Ki_P += 0.1;
    else if(C=='X')
      Ki_P -= 0.1;
    else if(C=='C')
      Kd_P += 0.1;
    else if(C=='V')
      Kd_P -= 0.1;
    else if(C=='E')
      break;

    Serial.print(Kp_P);
    Serial.print("\t\t");
    Serial.print(Ki_P);
    Serial.print("\t\t");
    Serial.println(Kd_P);
  }
}

void tuneHeadingPID(){
  Serial.println("_#_ Heading PID Tuning _#_");
  Serial.println("Q: Kp+=0.1");
  Serial.println("A: Kp-=0.1");
  Serial.println("Z: Ki+=0.1");
  Serial.println("X: Ki-=0.1");
  Serial.println("C: Kd+=0.1");
  Serial.println("V: Kd-=0.1");
  Serial.println("E: Exit");
  Serial.println("________");
  
  char C;
  while(1){
    while(Serial.available()<1){}
    C = Serial.read();
    if(C=='Q')
      Kp_H += 0.1;
    else if(C=='A')
      Kp_H -= 0.1;
    else if(C=='Z')
      Ki_H += 0.1;
    else if(C=='X')
      Ki_H -= 0.1;
    else if(C=='C')
      Kd_H += 0.1;
    else if(C=='V')
      Kd_H -= 0.1;
    else if(C=='E')
      break;

    Serial.print(Kp_H);
    Serial.print("\t\t");
    Serial.print(Ki_H);
    Serial.print("\t\t");
    Serial.println(Kd_H);
  }
}

void tuneFilters(){
  Serial.println("_#_ Speed PID Tuning _#_");
  Serial.println("Q: Constant+=0.01");
  Serial.println("A: Constant-=0.01");
  Serial.println("E: Exit");
  Serial.println("_______");
  
  char C;
  while(1){
    while(Serial.available()<1){}
    C = Serial.read();
    if(C=='Q')
      Filter_Heading_Constant += 0.01;
    else if(C=='A')
      Filter_Heading_Constant -= 0.01;
    else if(C=='E')
      break;
    Serial.println(Filter_Heading_Constant);
  }
}

void selectControllerType(){
  Serial.println("_#_ Select Control Type _#_");
  Serial.println("C: Compass");
  Serial.println("P: P Encoder");
  Serial.println("S: S Encoder");
  Serial.println("M: MPU Gyroscope");
  Serial.println("U: Ultrasonic");
  Serial.println("N: Open Loop");
  Serial.println("____________");
  
  while(Serial.available()<1){}
  Temp_Msg == Serial.read();
  Control_Type = Temp_Msg;
}
