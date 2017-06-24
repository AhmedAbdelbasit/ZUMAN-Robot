#include "ros/ros.h"
#include "zuman_msgs/Qlandmark.h"

void chatterCallback(const zuman_msgs::Qlandmark& msg){
  ROS_INFO("I heard: [%c]", msg.type);
  ROS_INFO("I heard: [%f]", msg.data);
}

int main(int argc, char **argv){

  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
  ros::spin();
  return 0;
}

