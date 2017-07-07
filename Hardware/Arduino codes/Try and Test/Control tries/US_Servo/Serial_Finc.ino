void printData(){
  //Serial.print("Left Error in cm : "); 
    //Serial.println(Left_Reference - Left_out_dis);
    //Serial.print("Right Error in cm : "); 
    //Serial.print(Right_Reference - Right_out_dis);

    Serial.print(Left_out_dis);
    Serial.print("\t\t");
    Serial.println(Right_out_dis);
}

