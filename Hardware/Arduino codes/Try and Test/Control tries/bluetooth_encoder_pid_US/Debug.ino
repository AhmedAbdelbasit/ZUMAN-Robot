void startDebug(){
  Serial.println("W: clear encoder ticks");
  Serial.println("U: Tune US PID");
  Serial.println("F: Tune Filter");

  while(Serial.available() < 1){}
  char Temp_Msg = Serial.read();
  
  if(Temp_Msg == 'W' || Temp_Msg == 'w'){
    Total_Left_Ticks = 0;
    Total_Right_Ticks = 0;
  }else if(Temp_Msg == 'U' || Temp_Msg == 'u'){
    tuneUSPID();
  }else if(Temp_Msg == 'F' || Temp_Msg == 'f'){
    tuneFilters();
  }
}

void tuneUSPID(){
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
      Filter_Speed_Constant += 0.01;
    else if(C=='A')
      Filter_Speed_Constant -= 0.01;
    else if(C=='E')
      break;
    Serial.println(Filter_Speed_Constant);
  }
}
