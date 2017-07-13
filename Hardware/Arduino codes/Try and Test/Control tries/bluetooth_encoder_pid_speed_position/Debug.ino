void tuneSpeedPID(){
  char C;
  while(1){
    while(Serial.available()<1){}
    C = Serial.read();
    if(C=='Q' || C== 'q')
      Kp_S += 0.1;
    else if(C=='A' || C== 'a')
      Kp_S -= 0.1;
    else if(C=='Z' || C== 'z')
      Ki_S += 0.1;
    else if(C=='X' || C== 'x')
      Ki_S -= 0.1;
    else if(C=='C' || C== 'c')
      Kd_S += 0.1;
    else if(C=='V' || C== 'v')
      Kd_S -= 0.1;
    else if(C=='O' || C== 'o')
      Robot_Speed += 1;
    else if(C=='L' || C== 'l')
      Robot_Speed -= 1;
    else if(C=='E' || C== 'e')
      break;

    Serial.print(Robot_Speed);
    Serial.print("\t\t");
    Serial.print(Kp_S);
    Serial.print("\t\t");
    Serial.print(Ki_S);
    Serial.print("\t\t");
    Serial.println(Kd_S);
  }
}
