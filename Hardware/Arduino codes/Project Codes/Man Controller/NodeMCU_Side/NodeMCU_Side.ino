////////////////////////////////
// reference:
// Find last versions at:
// https://github.com/agnunez/espros.git
//
// MIT License 2017 Agustin Nunez
/////////////////////////////////

#include <ESP8266WiFi.h>
#include <ros.h>
#include <zuman_msgs/Instruction.h>
#include <SoftwareSerial.h>

/////////////////////
// Software Serial //
/////////////////////
SoftwareSerial mySerial(14, 12); // RX, TX  (D5 , D6)

//////////////////////
// WiFi Definitions //
//////////////////////
const char* ssid = "ahmedpoto";
const char* password = "30ahmed30";
IPAddress server(192, 168, 1, 6); // ip of your ROS server
IPAddress ip_address;
int status = WL_IDLE_STATUS;
WiFiClient client;

class WiFiHardware {
  
  public:
  WiFiHardware() {};

  void init() {
    // do your initialization here. this probably includes TCP server/client setup
    client.connect(server, 11411);
  }

  // read a byte from the serial port. -1 = failure
  int read() {
    // implement this method so that it reads a byte from the TCP connection and returns it
    //  you may return -1 is there is an error; for example if the TCP connection is not open
    return client.read();         //will return -1 when it will works
  }

  // write data to the connection to ROS
  void write(uint8_t* data, int length) {
    // implement this so that it takes the arguments and writes or prints them to the TCP connection
    for(int i=0; i<length; i++)
      client.write(data[i]);
  }

  // returns milliseconds since start of program
  unsigned long time() {
     return millis(); // easy; did this one for you
  }
};

void setupWiFi()
{
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting to "); Serial.println(ssid);
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 20) delay(500);
  if(i == 21){
    Serial.print("Could not connect to"); Serial.println(ssid);
    while(1) delay(500);
  }
  Serial.print("Ready! Use ");
  Serial.print(WiFi.localIP());
  Serial.println(" to access client");
}

int i;

zuman_msgs::Instruction my_msg;
ros::Publisher pub("hw_low", &my_msg);
ros::NodeHandle_<WiFiHardware> nh;

void setup() {
  Serial.begin(115200);
  setupWiFi();
  delay(2000);
  nh.initNode();
  nh.advertise(pub);

  mySerial.begin(115200);
  mySerial.flush();
}

void loop() {
  if (mySerial.available()) {   //read the two 
    my_msg.command = "";
    my_msg.arg1 = 0;
    my_msg.arg2 = 0;
    
    char command = mySerial.read();
    if( command == 's'){
      my_msg.command = "set_pwm";
      my_msg.arg1 = mySerial.read()*4;
      my_msg.arg2 = mySerial.read()*4;
      pub.publish(&my_msg);
    }else if(command == 'l'){
      if(mySerial.read() == 'o'){
        my_msg.command = "switch_on_light";
      }else{
        my_msg.command = "switch_off_light";
      }
      pub.publish(&my_msg);
    }else if(command == 'z'){
      my_msg.command = "sync";
    }
    
    
    if (mySerial.read() == '\n') {
      Serial.print(my_msg.command);
      Serial.print("\t\t");
      Serial.print(my_msg.arg1);
      Serial.print("\t\t");
      Serial.println(my_msg.arg2);
    }
    nh.spinOnce();
  }
  delay(50);
}
