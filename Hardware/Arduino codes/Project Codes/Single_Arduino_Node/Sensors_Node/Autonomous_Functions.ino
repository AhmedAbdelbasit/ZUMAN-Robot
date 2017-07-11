void rotateRobot(float angle){
//  rotate servo
//  take reading
//  return servo
//
//  send rotate command to hw_low
//  until compass read reach ref
//  send stop command to hw_low
//  
//  use: compass_read_XYZdata();
}

void rotateCam(float angle){
  Yaw.write(angle);
}
