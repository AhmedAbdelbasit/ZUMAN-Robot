#include <SoftwareSerial.h>

SoftwareSerial mySerial(12, 13); // RX, TX

uint16_t Left_Pot = 0 ;
uint16_t Right_Pot = 0 ;

uint16_t Last_Left = 512;
uint16_t Last_Right = 512;

float Filtered_Left;
float Filtered_Right;
float Filter_Constant = 0.9;

int Sample_Time = 1;
int CountsPerMsg = 250;
int counter = 0;
int Time_Out_Ticks = 2500;
int Sync_Msg_Counter = 0;
int ReadingsPerTick = 5;

void setup(){
  Serial.begin(115200);
  Serial.flush();

  mySerial.begin(115200);
  mySerial.flush();
}

void loop(){
  Left_Pot = 0;
  Right_Pot = 0;

  for(int i=0; i<ReadingsPerTick ; i++){
    Left_Pot += analogRead(0);
    Right_Pot += analogRead(1);
  }
  Left_Pot /= ReadingsPerTick;
  Right_Pot /= ReadingsPerTick;

  filterLeft();
  filterRight();
  
  if( counter == CountsPerMsg ){
    if(Last_Left != floor(Filtered_Left) || Last_Right != floor(Filtered_Right) || Sync_Msg_Counter >= Time_Out_Ticks){
      mySerial.print(char( floor(Filtered_Left/4) ));
      mySerial.print(char( floor(Filtered_Right/4) ));
      mySerial.print('\n');
      
      Serial.print( floor(Filtered_Left/4) );
      Serial.print("\t\t");
      Serial.print( floor(Filtered_Right/4) );
      Serial.print("\t\t");
      Serial.print(counter);
      Serial.print("\t\t");
      Serial.println(Sync_Msg_Counter);
      
      Last_Left = floor(Filtered_Left);
      Last_Right = floor(Filtered_Right);
      Sync_Msg_Counter = 0;
    }
    counter = 0;
  }
  
  counter ++;
  Sync_Msg_Counter ++;
  delay(Sample_Time);
}

void filterLeft(){
  Filtered_Left = (1-Filter_Constant)*Last_Left + Filter_Constant * Left_Pot;
}

void filterRight(){
  Filtered_Right = (1-Filter_Constant)*Last_Right + Filter_Constant * Right_Pot;
}

