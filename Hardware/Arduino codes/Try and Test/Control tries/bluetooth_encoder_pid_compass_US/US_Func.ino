void measureLeftDistance(){
    digitalWrite(Left_Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Left_Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Left_Trig, LOW);
    Left_Duration = pulseIn(Left_Echo, HIGH,100000);
    Left_Distance = Left_Duration*0.034/2;
    
    if(Left_Distance == 0){
      resetLeftUS();
    }
}

void measureRightDistance(){
    digitalWrite(Right_Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Right_Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Right_Trig, LOW);
    Right_Duration = pulseIn(Right_Echo, HIGH,100000);
    Right_Distance = Right_Duration*0.034/2;
    
    if(Right_Distance == 0){
      resetRightUS();
    }
}

void resetLeftUS(){
  pinMode(Left_Echo, OUTPUT);
  digitalWrite(Left_Echo,LOW);
  delay(10);
  pinMode(Left_Echo,INPUT);
  delay(10);
}

void resetRightUS(){
  pinMode(Right_Echo, OUTPUT);
  digitalWrite(Right_Echo,LOW);
  delay(10);
  pinMode(Right_Echo,INPUT);
  delay(10);
}
