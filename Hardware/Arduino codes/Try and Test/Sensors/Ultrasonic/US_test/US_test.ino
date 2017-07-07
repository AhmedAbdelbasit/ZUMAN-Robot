#define trigR 12 
#define echoR 11
#define trigL 9
#define echoL 8
#define Max_Error 10

float Right_out_dis;
float Last_Right_out_dis;
float Left_out_dis;
float Last_Left_out_dis;

float Left_Reference ;
float Right_Reference ;

float Left_Error;
float Right_Error;

// Cycle
long Last_Tic;
long Time_Now;
int Sample_Time = 100;

void setup() { 
  pinMode(trigR, OUTPUT);
  digitalWrite(trigR, LOW);
  pinMode(echoR, INPUT);
  
  pinMode(trigL, OUTPUT); 
  digitalWrite(trigL, LOW); 
  pinMode(echoL, INPUT); 
  Serial.begin(9600);

  Right_Reference = -1;
  while(Right_Reference == -1){
    Right_Reference = measureDistance(trigR, echoR);
  }
  
  Left_Reference = -1;
  while(Left_Reference == -1){
    Left_Reference = measureDistance(trigL, echoL);
  }

  Last_Right_out_dis = Right_Reference;
  Last_Left_out_dis = Left_Reference;

  Serial.print(Left_Reference);
  Serial.print("\t\t");
  Serial.println(Right_Reference);
  Serial.println("*****************");

  Last_Tic = millis();
}


