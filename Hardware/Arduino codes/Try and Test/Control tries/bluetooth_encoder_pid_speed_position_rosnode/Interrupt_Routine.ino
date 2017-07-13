void countLeft(){
  long Time = millis();
  Left_Encoder_Ticks --;
  if(Time - Last_Left_Tick != 0){ 
    Measured_Left_Speed = 1000.0/(3.0*(Time - Last_Left_Tick)) ;
    Last_Left_Tick = Time;
  }
}

void countRight(){
  long Time = millis();
  Right_Encoder_Ticks --;
  if(Time - Last_Right_Tick != 0){ 
    Measured_Right_Speed = 1000.0/(3.0*(Time - Last_Right_Tick)) ;
    Last_Right_Tick = Time;
  }
}

