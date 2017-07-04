#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <zuman_msgs/Instruction.h>

class SubPubClass
{
public:
	// constructor
	SubPubClass();

private:
	// call back function of subscriber
	void CV_Callback(const zuman_msgs::Instruction::ConstPtr& msg);
        void ARD_Callback(const zuman_msgs::Instruction::ConstPtr& msg);
	// node handle
	ros::NodeHandle nh;
	// publisher object
	ros::Publisher cv_pub;
        ros::Publisher ard_low_pub;
	// subscriber object
	ros::Subscriber cv_sub;
	ros::Subscriber ard_low_sub;
  
};

// Constructor subroutine
SubPubClass::SubPubClass(){
    // advertising topics / msg types for publishers and subscribers
    cv_pub = nh.advertise<zuman_msgs::Instruction>("hw_landmark", 10);
    cv_sub = nh.subscribe<zuman_msgs::Instruction>("hw_landmark", 10, &SubPubClass::CV_Callback, this);
    ard_low_pub = nh.advertise<zuman_msgs::Instruction>("hw_low", 10);
    ard_low_sub = nh.subscribe<zuman_msgs::Instruction>("hw_low", 10, &SubPubClass::ARD_Callback, this);

}

// call back function for subscribers
void SubPubClass::CV_Callback(const zuman_msgs::Instruction::ConstPtr& msg)
{
    // handle " move(d 0), rotate(theta 0) and again(1 >> send("tune") || 0>>ok 0) "
    zuman_msgs::Instruction msg_to_send;
    
    if(msg->command == "move"){
        ROS_INFO("recived move %f cm",msg->arg1);
        msg_to_send.command="move";
        msg_to_send.arg1 = msg->arg1;
        msg_to_send.arg2 = 0;
        ard_low_pub.publish(msg_to_send);
    }
}


void SubPubClass::ARD_Callback(const zuman_msgs::Instruction::ConstPtr& msg)
{
    // handle " move(d 0), rotate(theta 0) and again(1 >> send("tune") || 0>>ok 0) "
    zuman_msgs::Instruction msg_to_send;
    
    if(msg->command == "moving done"){
        ROS_INFO("robot moved %f cm",msg->arg1);
        msg_to_send.command="reached";
        msg_to_send.arg1 = msg->arg1;
        msg_to_send.arg2 = 0;
        cv_pub.publish(msg_to_send);
    }
}


// main function loop
int main(int argc, char** argv)
{
	// initializing ROS, must be first to be executed
	ros::init(argc, argv, "HW_node_cpp");
	// creating object of the class containing publisher/subsciber
	SubPubClass object;
	// handling communication msgs continueously
	ros::spin();
}


