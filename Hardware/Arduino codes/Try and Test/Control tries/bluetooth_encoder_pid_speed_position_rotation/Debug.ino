void executeCallback(){
  if(Serial.available() > 0){
    Serial.println("From Callback");
    Error_Sum_Left = 0;
    Error_Sum_Right = 0;
    Last_Error_Left = 0;
    Last_Error_Right = 0;
    
    Dir = Serial.read();
    if (Dir == 'T' || Dir=='t'){
      tuneSpeedPID();
      Dir = 'S';
      Last_Tic = (millis()/Sample_Time)*Sample_Time ; 
    }else if(Dir == 'n' || Dir == 'N'){
      digitalWrite(Light_Pin, 1-digitalRead(Light_Pin));
      Dir = 'S';
    }else{
      if (Dir == 'f' || Dir=='b' ){
        Error_Sum_Left = 0;
        Error_Sum_Right = 0;
        Last_Error_Left = 0;
        Last_Error_Right = 0;
    
        float Distance = Goal_Distance;
        int Ticks = floor(Distance*180.0/Distance_Per_Rev);

        Right_Encoder_Ticks = abs(Ticks);
        Left_Encoder_Ticks = abs(Ticks);
        Move_Ack = HIGH;
        
      }else if (Dir == 'l' || Dir=='r' ){
        Error_Sum_Left = 0;
        Error_Sum_Right = 0;
        Last_Error_Left = 0;
        Last_Error_Right = 0;
    
        int Ticks = Rotation_Ticks;

        Right_Encoder_Ticks = abs(Ticks);
        Left_Encoder_Ticks = abs(Ticks);
        Rotate_Ack = HIGH;
      }
    }
  }
}

void checkGoal(){
  if(Move_Ack && Left_Encoder_Ticks <= 0 && Right_Encoder_Ticks <= 0){
    Serial.print( "Moving Done by : ");
    Serial.println( Goal_Distance + abs( measureDistance() ) );
    
    Move_Ack = LOW;
    Dir = 'S';
    
    Filtered_Left_Speed = 0;
    Filtered_Right_Speed = 0;
    Measured_Left_Speed = 0;
    Measured_Right_Speed = 0;
    
  }else if(Rotate_Ack && Left_Encoder_Ticks <= 0 && Right_Encoder_Ticks <= 0){
    Serial.print( "Rotation Done by : ");
    Serial.print( Rotation_Ticks + abs(Left_Encoder_Ticks) );
    Serial.print("\t");
    Serial.println( Rotation_Ticks + abs(Right_Encoder_Ticks) );
    
    Rotate_Ack = LOW;
    Dir = 'S';
    Filtered_Left_Speed = 0;
    Filtered_Right_Speed = 0;
    Measured_Left_Speed = 0;
    Measured_Right_Speed = 0;
    
  }
}

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
    else if(C=='T' || C== 't')
      Rotation_Ticks += 1;
    else if(C=='G' || C== 'g')
      Rotation_Ticks -= 1;
    else if(C=='Y' || C== 'y')
      Goal_Distance += 1;
    else if(C=='H' || C== 'h')
      Goal_Distance -= 1;
    else if(C=='E' || C== 'e')
      break;

    Serial.print(Robot_Speed);
    Serial.print("\t\t");
    Serial.print(Kp_S);
    Serial.print("\t\t");
    Serial.print(Ki_S);
    Serial.print("\t\t");
    Serial.print(Kd_S);
    Serial.print("\t\t");
    Serial.print(Rotation_Ticks);
    Serial.print("\t\t");
    Serial.println(Goal_Distance);
  }
}
