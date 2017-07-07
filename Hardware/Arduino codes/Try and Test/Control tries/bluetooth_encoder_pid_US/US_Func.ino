void measureRightDistance(){
    float Temp=0;
    digitalWrite(Right_Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Right_Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Right_Trig, LOW);
    Right_Duration = pulseIn(Right_Echo, HIGH,10000);
    Temp = Right_Duration*0.034/2;
    
    if(Temp == 0){
      resetRightUS();
    }else{
      Right_Distance = Temp;
    }
}

void resetRightUS(){
  pinMode(Right_Echo, OUTPUT);
  digitalWrite(Right_Echo,LOW);
  delay(10);
  pinMode(Right_Echo,INPUT);
  delay(10);
}
