//void filterReading(){
//  Filtered_X_Reading = (1-Filter_Constant)*Filtered_X_Reading + Filter_Constant * compass_x;
//  Filtered_Y_Reading = (1-Filter_Constant)*Filtered_Y_Reading + Filter_Constant * compass_y;
//}

void rotateRobot(char d){
  if(d == 'r'){
    Compass_Servo.write(10);
  }else if(d == 'l'){
    Compass_Servo.write(180);
  }
  
  delay(3000);

  // taking reference
  int Reference_x = 0;
  int Reference_y = 0;
  int Reference_z = 0;
  
  for (int i=0 ; i<10 ; i++){
    compass_read_XYZdata();
  }
  compass_read_XYZdata();
  Reference_x = compass_x;
  Reference_y = compass_y;
  Reference_z = compass_z;
  
  Serial.print("Reference taken as : ");
  Serial.print(Reference_x);
  Serial.print("\t\t");
  Serial.print(Reference_y);
  Serial.print("\t\t");
  Serial.println(Reference_z);
  delay(1000);
  
  Compass_Servo.write(90);
  delay(3000);

  while(1){
    // rotate robot
    for (int i=0 ; i<10 ; i++){
      compass_read_XYZdata();
    }
    Serial.print(Reference_x);
    Serial.print("\t ");
    Serial.print(compass_x);
    Serial.print("\t ");
    Serial.print(Reference_y);
    Serial.print("\t ");
    Serial.print(compass_y);
    Serial.print("\t ");
    Serial.print(Reference_z);
    Serial.print("\t ");
    Serial.println(compass_z);
    
    if(Serial.available() > 0){
      break;
    }
    if( (abs(compass_x - Reference_x) < 20) && (abs(compass_y - Reference_y) < 20) ) {
      // stop robot
      Serial.println("Robot reached desired angle");
      break;
    }
    delay(100);
  }
}

