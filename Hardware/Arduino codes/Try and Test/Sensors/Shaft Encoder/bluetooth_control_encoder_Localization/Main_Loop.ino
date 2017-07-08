void loop() {
  Time_Now = millis();
  if(Time_Now - Last_Tic >= Sample_Time ){
    //Last_Tic += Sample_Time;
    Last_Tic = Time_Now ;
    measureOdometry();

    if(Dir != 'S' && Dir !='s'){
      printData();
    }
    
    if(Serial.available() > 0){
      Dir = Serial.read();
      if(Dir == 'c' || Dir == 'C'){
        X_Position = 0;
        Y_Position = 0;
        Angle = 0;
        Dir = 'S';
      }else if(Dir == 'q' || Dir == 'Q'){
         Cal_Left_Speed ++;
         Serial.println(Cal_Left_Speed);
         Dir = 'S';
      }else if(Dir == 'a' || Dir == 'A'){
        Cal_Left_Speed --;
        Serial.println(Cal_Left_Speed);
        Dir = 'S';
      }else if(Dir == 'e' || Dir == 'E'){
        Cal_Right_Speed ++;
        Serial.println(Cal_Right_Speed);
        Dir = 'S';
      }else if(Dir == 'd' || Dir == 'D'){
        Cal_Right_Speed --;
        Serial.println(Cal_Right_Speed);
        Dir = 'S';
      }
    }
    
    filterMotorSpeed();
    driveMotors();
  }
}
