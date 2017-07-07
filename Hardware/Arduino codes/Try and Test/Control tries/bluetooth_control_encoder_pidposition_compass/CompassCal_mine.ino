/*
float c_x=0,
      c_y=0,
      c_z=0;  
             
int x_max=-4000,
    y_max=-4000,
    z_max=-4000; 
int x_min=4000,
    y_min=4000,
    z_min=4000;
    
void setup(){
  Serial.begin(9600);
  Wire.begin();
  compass_x_offset = 122.17;
  compass_init(2);
}

void loop(){
  compass_read_XYZdata();
  c_x = map(compass_x,x_min,x_max,-180,180);
  c_y = map(compass_y,y_min,y_max,-180,180);
  c_z = map(compass_z,z_min,z_max,-180,180);
  if (c_y>0){
    bearing = 90-atan(c_x/c_y)*180/PI;
  }else if (c_y<0){
    bearing = 270-atan(c_x/c_y)*180/PI;
  }else if (c_y==0 & c_x<0){
    bearing = 180;
  }else{
    bearing = 0;
  }
  getMinMax();
  printData();
}

void getMinMax(){
  x_min = min(x_min,compass_x);
  y_min = min(y_min,compass_y);
  z_min = min(z_min,compass_z);
  x_max = max(x_max,compass_x);
  y_max = max(y_max,compass_y);
  z_max = max(z_max,compass_z);
}

void printData(){
  Serial.print(compass_x);  Serial.print("\t");
  Serial.print(compass_y);  Serial.print("\t");
  Serial.print(compass_z);  Serial.print("\t");
  Serial.print(bearing);  Serial.print("\t");
  
  Serial.print(x_min);  Serial.print("\t");
  Serial.print(y_min);  Serial.print("\t");
  Serial.print(z_min);  Serial.print("\t");
  Serial.print(x_max);  Serial.print("\t");
  Serial.print(y_max);  Serial.print("\t");
  Serial.print(z_max);  Serial.print("\t");
 
  Serial.println();
}
*/
