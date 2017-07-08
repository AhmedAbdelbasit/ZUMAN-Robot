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
    else if(C=='O')
      Robot_Speed += 1;
    else if(C=='L')
      Robot_Speed -= 1;
    else if(C=='E')
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
