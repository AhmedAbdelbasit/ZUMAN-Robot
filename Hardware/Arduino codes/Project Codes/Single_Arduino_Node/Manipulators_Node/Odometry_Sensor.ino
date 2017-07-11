float measureDistance(){
  int Inst_Left_Encoder_Ticks;
  int Inst_Right_Encoder_Ticks;
  
  float Inst_Left_Distance;
  float Inst_Right_Distance;

  Inst_Left_Encoder_Ticks = Left_Encoder_Ticks;
  Left_Encoder_Ticks = 0;
  Inst_Right_Encoder_Ticks = Right_Encoder_Ticks;
  Right_Encoder_Ticks = 0;

  Inst_Left_Distance = (Inst_Left_Encoder_Ticks/180.0)*Distance_Per_Rev;
  if(DirLeft == 'B'){
    Inst_Left_Distance *= -1;
  }
  Inst_Right_Distance = (Inst_Right_Encoder_Ticks/180.0)*Distance_Per_Rev;
  if(DirRight == 'B'){
    Inst_Right_Distance *= -1;
  }
  
  return ( (Inst_Left_Distance + Inst_Right_Distance)/2.0 );
}
