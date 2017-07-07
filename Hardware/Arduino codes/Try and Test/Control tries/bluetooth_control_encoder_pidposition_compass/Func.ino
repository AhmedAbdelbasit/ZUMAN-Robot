void selfTest()
{          
  float averageX = 0;
  float averageY = 0;
  float averageZ = 0;

  HMC5883L mycompass;
  mycompass = HMC5883L();
  mycompass.SetScale(1.3);
  delay(25);
  Wire.beginTransmission(0x3C);     // write address
  
  Wire.write(0x00);                 // address of register
  Wire.write(0x71);                 // 8 average, 15hz default, positive test
  delay(10);
  Wire.write(0x01);                 // address of register
  Wire.write(0xA0);                 // gain = 5
  delay(10);
  Wire.write(0x02);                 // address of register
  Wire.write(0x00);                 // set continuous measurement mode
  delay(10);
  Wire.endTransmission();

  delay(10);                        // wait for DRDY
  
  for(int i=0; i <=7; i++)          // take and average 8 measurements
  {
     MagnetometerRaw raw = mycompass.ReadRawAxis();       // read 6 bytes, 3 16bit 2's compliment

     float testX = raw.XAxis;             // read raw values each axis
     float testY = raw.YAxis;
     float testZ = raw.ZAxis; 

     averageX = averageX + testX;   // add test values to be averaged later
     averageY = averageY + testY;
     averageZ = averageZ + testZ;
/*
     Serial.print("Raw:\t");        // print the test values
     Serial.print(testX);
     Serial.print("   ");   
     Serial.print(testY);
     Serial.print("   ");   
     Serial.println(testZ);

     Serial.print("Averages:\t");   // print the averages sum before averaging / 8
     Serial.print(averageX);
     Serial.print("   ");   
     Serial.print(averageY);
     Serial.print("   ");   
     Serial.println(averageZ);
*/   
     delay(67);
  }

  // check limits...

  averageX = averageX / 8;          // calc averages for 8 samples
  averageY = averageY / 8;
  averageZ = averageZ / 8;
  
  Serial.print("\nCalculated Averages:\t");
  Serial.print(averageX);   
  Serial.print("   ");
  Serial.print(averageY);   
  Serial.print("   ");
  Serial.println(averageZ);
  boolean passX, passY, passZ;
  
  if(abs(averageX) >= 243 && abs(averageX) <= 575)  // work with absolute values
  {
    Serial.println("\nX within limits");
    passX = true;  
  }
    else  
    {
      Serial.println("\nX not within limits"); 
      passX = false; 
    }
    
  if(abs(averageY) >= 243 && abs(averageY) <=575)  
  {
    Serial.println("\nY within limits");
    passY = true;  
  }
    else  
    {
      Serial.println("\nY not within limits"); 
      passY = false; 
    }
    
  if(abs(averageZ) >= 243 && abs(averageZ) <=575)  
  {
    Serial.println("\nZ within limits");
    passZ = true;  
  }
    else  
    {
      Serial.println("\nZ not within limits"); 
      passZ = false; 
    }
      
  if(passX == true && passY == true && passZ == true)   // if all axes passed
  {
    Wire.beginTransmission(0x3C);     // write address
    Wire.write(0x01);                 // address of register
    Wire.write(0x70);                 // 8 average, 15hz default, positive test
    delay(10);
    Serial.println("\n\nSelf Test Passed - Moving On...\n");
  }
    else
    {
      Serial.println("\n\nSelf Test Failed - Moving On...\n");
    }
    
  Serial.flush();                   // clear serial buffers
  //softSerial.flush();
}
