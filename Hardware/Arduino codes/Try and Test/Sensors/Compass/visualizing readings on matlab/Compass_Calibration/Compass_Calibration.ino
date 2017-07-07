#include <Wire.h>
#include "compass.h"

float filtered_bearing;
float filter_constant = 0.1;

void setup(){
  Serial.begin(9600);
  Wire.begin();
  compass_init(2);    //gain factor 1.22
  compass_debug = 1;
  //compass_offset_calibration(3);
}
int tt = 0;
void loop(){
  compass_read_XYZdata();
  Serial.println(compass_x);
  Serial.println(compass_y);
  Serial.println(compass_z);
  Serial.println(tt);
  delay(100);
}

