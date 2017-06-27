#ifndef _ROS_zuman_msgs_Obstacle_Alert_h
#define _ROS_zuman_msgs_Obstacle_Alert_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace zuman_msgs
{

  class Obstacle_Alert : public ros::Msg
  {
    public:
      typedef float _Distance_type;
      _Distance_type Distance;

    Obstacle_Alert():
      Distance(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_Distance;
      u_Distance.real = this->Distance;
      *(outbuffer + offset + 0) = (u_Distance.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Distance.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Distance.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Distance.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Distance);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_Distance;
      u_Distance.base = 0;
      u_Distance.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Distance.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Distance.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Distance.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Distance = u_Distance.real;
      offset += sizeof(this->Distance);
     return offset;
    }

    const char * getType(){ return "zuman_msgs/Obstacle_Alert"; };
    const char * getMD5(){ return "3d67dc7b370bfdeb182b2ab46c68e2a9"; };

  };

}
#endif