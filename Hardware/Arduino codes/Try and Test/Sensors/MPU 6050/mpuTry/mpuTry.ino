#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#define GYRO_SCL 131.0
#define ACC_SCL 16383.0

MPU6050 accelgyro;

int16_t ax, ay, az;        // ay,az only used    accelerometer reading
int16_t gx, gy, gz;        // gx only used       gyroscope reading
double gyro_rate;          // to store angular velocity calculated from gyroscope

double NewXacc, Xacc , Yacc;
double Xvelocity = 0, 
       Yvelocity = 0;
double Xdistance = 0,
       Ydistance = 0;
double a = 0.7 ,
       b = 0.01;

unsigned long dt, now;                    // loop time period
int count = 0;
unsigned long SampleTime = 10;    // time of iteration of recalculating motor output
unsigned long LastTime;            // Used to determine what if time period has passed or not " @ Copute Function "

void setup() {
    Serial.begin(115200);
    Wire.begin();
    accelgyro.initialize();
    LastTime = millis();
}

void loop() {
    now = millis();
    dt = now - LastTime;
    if ( dt < SampleTime ){
      delay(SampleTime - dt);
    }
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    NewXacc = (ax / ACC_SCL)*9.8;
    highPass();
    lowPass();
    Yacc = (ay / ACC_SCL)*9.8;

    Xvelocity += Xacc * SampleTime/1000.0 ;
    Yvelocity += Xacc * SampleTime/1000.0 ;

    Xdistance += Xvelocity * SampleTime/1000.0 ;
    Ydistance += Xvelocity * SampleTime/1000.0 ;
    
    pr();
    LastTime = now;
}
void highPass(){
  double AV = (1-a)*Xacc + a*NewXacc;
  NewXacc = NewXacc - AV;
}
void lowPass(){
  Xacc = (1-b)*Xacc + b*NewXacc ;
}
void pr(){
  Serial.println(Xacc*10);
  /*
    Serial.print("    Acc X: ");
    Serial.print(Xacc);
    Serial.print("    Vel X: ");
    Serial.print(Xvelocity);
    Serial.print("    Dis X: ");
    Serial.print(Xdistance);
    
    Serial.println();*/
}

