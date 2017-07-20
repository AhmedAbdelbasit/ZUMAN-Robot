#include <SoftwareSerial.h>

#define Switch_Pin 4
#define Left_Pot_Pin A0
#define Right_Pot_Pin A1
#define Yaw_Pot_Pin A2
#define Pitch_Pot_Pin A3

SoftwareSerial mySerial(5, 6); // RX, TX

uint16_t Left_Pot = 512 ;
uint16_t Right_Pot = 512 ;
uint16_t Yaw_Pot = 512 ;
uint16_t Pitch_Pot = 512 ;

uint16_t Last_Left = 512;
uint16_t Last_Right = 512;
uint16_t Last_Yaw = 512;
uint16_t Last_Pitch = 512;

float Filtered_Left;
float Filtered_Right;
float Filtered_Yaw;
float Filtered_Pitch;

float Filter_Constant = 0.75;

boolean Switch_State = false;

int Sample_Time = 1;
int CountsPerMsg = 100;
int counter = 0;
int Time_Out_Ticks = 2500;
int Sync_Msg_Counter = 0;
int ReadingsPerTick = 10;

void setup(){
  Serial.begin(115200);
  Serial.flush();

  mySerial.begin(115200);
  mySerial.flush();

  pinMode(Switch_Pin, INPUT);
  
}

void loop(){
  
  readPots();
  
  filterPots();
  
  if( counter == CountsPerMsg ){
    if(Last_Left != floor(Filtered_Left/4) || Last_Right != floor(Filtered_Right/4) ){
      mySerial.print('s');
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
      
      Last_Left = floor(Filtered_Left/4);
      Last_Right = floor(Filtered_Right/4);
      Sync_Msg_Counter = 0;
      
    }
    // added 
    if(Last_Yaw != floor(Filtered_Yaw/4) || Last_Pitch != floor(Filtered_Pitch/4) ){
      mySerial.print('c');
      mySerial.print(char( floor(Filtered_Yaw/4) ));
      mySerial.print(char( floor(Filtered_Pitch/4) ));
      mySerial.print('\n');
      
      Serial.print( floor(Filtered_Yaw/4) );
      Serial.print("\t\t");
      Serial.print( floor(Filtered_Pitch/4) );
      Serial.print("\t\t");
      Serial.print(counter);
      Serial.print("\t\t");
      Serial.println(Sync_Msg_Counter);
      
      Last_Yaw = floor(Filtered_Yaw/4);
      Last_Pitch = floor(Filtered_Pitch/4);
      Sync_Msg_Counter = 0;
      
    }
    
    if( digitalRead(Switch_Pin) != Switch_State ){
      Switch_State = digitalRead(Switch_Pin);
      mySerial.print('l');
      if(Switch_State){
        mySerial.print('f');
        Serial.println("off");
      }else{
        mySerial.print('o');
        Serial.println("on");
      }
      mySerial.print('\n');

      Sync_Msg_Counter = 0;
    }
    counter = 0;

    if ( Sync_Msg_Counter >= Time_Out_Ticks ){
      mySerial.print('z');
      mySerial.print('\n');
      
      Serial.println("sending sync");
      Sync_Msg_Counter = 0;
    }
  }
  
  counter ++;
  Sync_Msg_Counter ++;
  delay(Sample_Time);
}

void filterPots(){
  Filtered_Left = (1-Filter_Constant)*Last_Left + Filter_Constant * Left_Pot;
  Filtered_Right = (1-Filter_Constant)*Last_Right + Filter_Constant * Right_Pot;
  Filtered_Yaw = (1-Filter_Constant)*Last_Yaw + Filter_Constant * Yaw_Pot;
  Filtered_Pitch = (1-Filter_Constant)*Last_Pitch + Filter_Constant * Pitch_Pot;
}

void readPots(){
  Left_Pot = 0;
  Right_Pot = 0;
  Yaw_Pot = 0;
  Pitch_Pot = 0;
  
  for(int i=0; i<ReadingsPerTick ; i++){
    Left_Pot += analogRead(Left_Pot_Pin);
    Right_Pot += analogRead(Right_Pot_Pin);
    Yaw_Pot += analogRead(Yaw_Pot_Pin);
    Pitch_Pot += analogRead(Pitch_Pot_Pin);
  }
  Left_Pot /= ReadingsPerTick;
  Right_Pot /= ReadingsPerTick;
  Yaw_Pot /= ReadingsPerTick;
  Pitch_Pot /= ReadingsPerTick;
}

