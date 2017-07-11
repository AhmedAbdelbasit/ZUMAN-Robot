void moveRobot(int ls, int rs){
  DirLeft='F';
  DirRight='F';
  
  if(ls <512)
    DirLeft='B';
  if(rs <512)
    DirRight='B';
    
  Left_Speed = abs((ls-512)/2.0 );
  Right_Speed = abs((rs-512)/2.0 );
  driveMotors();
}

