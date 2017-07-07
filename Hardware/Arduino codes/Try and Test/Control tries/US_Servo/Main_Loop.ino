void loop() {
  Time_Now = millis();
  if(Time_Now - Last_Tic >= Sample_Time ){
    Last_Tic = Time_Now;
    
    if(Mode){
      Left_Angle += 5;
      Right_Angle += 5;
      if(Left_Angle >170){
        Mode = LOW;
      }
    }else{
      Left_Angle -= 5;
      Right_Angle -= 5;
      if(Left_Angle <10){
        Mode = HIGH;
      }
    }
    Left_Servo.write(Left_Angle);
    Right_Servo.write(Right_Angle);
    
    float Temp = -1;
    Temp = measureDistance(trigR, echoR);
    if(Temp !=-1){
      Right_out_dis = Temp;
    }
    
    delay(50);
    
    Temp = measureDistance(trigL, echoL);
    if(Temp !=-1){
      Left_out_dis = Temp;
    }

    if( abs(Last_Right_out_dis - Right_out_dis) > Max_Error)
      Right_Reference = Right_out_dis;
      
    if( abs(Last_Left_out_dis - Left_out_dis) > Max_Error)
      Left_Reference = Left_out_dis;

    delay(5);
    
    printData();

    Last_Right_out_dis = Right_out_dis;
    Last_Left_out_dis = Left_out_dis;
  }
  
}
