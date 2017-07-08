void tuneSpeeds(){
  char C;
  while(1){
    while(Serial.available()<1){}
    C = Serial.read();
    if(C=='Q' || C=='q')
      Cal_Left_Speed += 1;
    else if(C=='A' || C=='a')
      Cal_Left_Speed -= 1;
    else if(C=='Z' || C=='z')
      Cal_Right_Speed += 1;
    else if(C=='X' || C=='x')
      Cal_Right_Speed -= 1;
    else if(C=='E' || C=='e')
      break;

    Serial.print(Cal_Left_Speed);
    Serial.print("\t\t");
    Serial.println(Cal_Right_Speed);
  }
}
