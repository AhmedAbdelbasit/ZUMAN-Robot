float measureDistance(byte trig, byte echo){
    float Temp=0;
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    long Duration = pulseIn(echo, HIGH,20000);
    Temp = Duration*0.034/2;
    
    if(Temp == 0){
      resetUS(echo);
      return -1;
    }else{
      return Temp;
    }
}

void resetUS(byte echo){
  pinMode(echo, OUTPUT);
  digitalWrite(echo,LOW);
  delay(10);
  pinMode(echo,INPUT);
  delay(10);
}
