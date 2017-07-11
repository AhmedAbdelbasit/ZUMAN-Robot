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
    void MAP_Callback(const zuman_msgs::Instruction::ConstPtr& msg);

	// node handle
	ros::NodeHandle nh;
	// publisher object
	ros::Publisher cv_pub;
	ros::Publisher map_pub;
        ros::Publisher ard_low_pub;
	// subscriber object
	ros::Subscriber cv_sub;
	ros::Subscriber map_sub;
	ros::Subscriber ard_low_sub;
  
};

// Constructor subroutine
SubPubClass::SubPubClass(){
    // advertising topics / msg types for publishers and subscribers
    cv_pub = nh.advertise<zuman_msgs::Instruction>("hw_landmark", 10);
    cv_sub = nh.subscribe<zuman_msgs::Instruction>("hw_landmark", 10, &SubPubClass::CV_Callback, this);
    map_pub = nh.advertise<zuman_msgs::Instruction>("hw_map", 10);
    map_sub = nh.subscribe<zuman_msgs::Instruction>("hw_map", 10, &SubPubClass::MAP_Callback, this);
    ard_low_pub = nh.advertise<zuman_msgs::Instruction>("hw_low", 10);
    ard_low_sub = nh.subscribe<zuman_msgs::Instruction>("hw_low", 10, &SubPubClass::ARD_Callback, this);

}


// callback function to handle recieved instructions from CV_node 
void SubPubClass::CV_Callback(const zuman_msgs::Instruction::ConstPtr& msg){

    zuman_msgs::Instruction msg_to_send;

    msg_to_send.arg1 = msg->arg1;
    msg_to_send.arg2 = msg->arg2;

    if(msg->command == "tuned"){		// send "next_step" to map
        msg_to_send.command = "next_step";
        map_pub.publish(msg_to_send);
    }else{
        if (msg->command == "move"){		// send instruction with "map_" to ARD
            msg_to_send.command = "cv_move";

        }else if (msg->command == "rotate"){	// send instruction with "map_" to ARD
            msg_to_send.command = "cv_rotate";

        }else if (msg->command == "move_rotate"){	// send instruction with "map_" to ARD
            msg_to_send.command = "cv_move_rotate";
    
        }else if (msg->command == "rotate_cam"){	// send instruction with "map_" to ARD
            msg_to_send.command = "cv_rotate_cam";
    
        }else{
            return;
        }
        ard_low_pub.publish(msg_to_send);
    }
}


// callback function to handle recieved information from ARD_node 
void SubPubClass::ARD_Callback(const zuman_msgs::Instruction::ConstPtr& msg){
    
    zuman_msgs::Instruction msg_to_send;
    msg_to_send.arg1 = 0;
    msg_to_send.arg2 = 0;

    // distinguish between response of cv or map instruction
    // append cv_ or map_ to command before sending it to arduino..

    if ( msg->command == "cv_done"){			// send "tune" to CV
        msg_to_send.command = "tune";
        cv_pub.publish(msg_to_send);

    }else if ( msg->command == "map_done"){		// send "next_step" to map
        msg_to_send.command = "next_step";
        map_pub.publish(msg_to_send);

    }else if ( msg->command == "obstacle_alarm"){	// send "remap" to map
        msg_to_send.command = "remap";
        map_pub.publish(msg_to_send);
    }
}


// callback function to handle recieved information from MAP_node 
void SubPubClass::MAP_Callback(const zuman_msgs::Instruction::ConstPtr& msg){

    zuman_msgs::Instruction msg_to_send;

    msg_to_send.arg1 = msg->arg1;
    msg_to_send.arg2 = msg->arg2;

    if (msg->command == "move"){		// send instruction with "map_" to ARD
        msg_to_send.command = "map_move";

    }else if (msg->command == "rotate"){	// send instruction with "map_" to ARD
        msg_to_send.command = "map_rotate";

    }else if (msg->command == "move_rotate"){	// send instruction with "map_" to ARD
        msg_to_send.command = "map_move_rotate";
    
    }else if (msg->command == "rotate_cam"){	// send instruction with "map_" to ARD
        msg_to_send.command = "map_rotate_cam";
    
    }else{
        return;
    }
    ard_low_pub.publish(msg_to_send);
    
}





// main function loop
int main(int argc, char** argv){
	// initializing ROS, must be first to be executed
	ros::init(argc, argv, "HW_node_cpp");
	// creating object of the class containing publisher/subsciber
	SubPubClass object;
	// handling communication msgs continueously
	ros::spin();
}


