void tuneControllers(){
  while(Serial.available()<1){}
  
  char Mode = Serial.read();
  if(Mode == 'S'){
    tuneSpeedPID();
  }else if(Mode == 'P'){
    tunePositionPID();
  }else if(Mode == 'H'){
    tuneHeadingPID();
  }else if(Mode == 'F'){
    tuneFilter();
  }
}

void tuneSpeedPID(){
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

void tuneFilter(){
  char C;
  while(1){
    while(Serial.available()<1){}
    C = Serial.read();
    if(C=='Q')
      filter_constant += 0.01;
    else if(C=='A')
      filter_constant -= 0.01;
    else if(C=='E')
      break;

    Serial.println(filter_constant);
  }
}

