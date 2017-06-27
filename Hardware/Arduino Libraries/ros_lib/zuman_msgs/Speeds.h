#ifndef _ROS_zuman_msgs_Speeds_h
#define _ROS_zuman_msgs_Speeds_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace zuman_msgs
{

  class Speeds : public ros::Msg
  {
    public:
      typedef int16_t _leftSpeed_type;
      _leftSpeed_type leftSpeed;
      typedef int16_t _rightSpeed_type;
      _rightSpeed_type rightSpeed;

    Speeds():
      leftSpeed(0),
      rightSpeed(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_leftSpeed;
      u_leftSpeed.real = this->leftSpeed;
      *(outbuffer + offset + 0) = (u_leftSpeed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_leftSpeed.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->leftSpeed);
      union {
        int16_t real;
        uint16_t base;
      } u_rightSpeed;
      u_rightSpeed.real = this->rightSpeed;
      *(outbuffer + offset + 0) = (u_rightSpeed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rightSpeed.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->rightSpeed);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_leftSpeed;
      u_leftSpeed.base = 0;
      u_leftSpeed.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_leftSpeed.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->leftSpeed = u_leftSpeed.real;
      offset += sizeof(this->leftSpeed);
      union {
        int16_t real;
        uint16_t base;
      } u_rightSpeed;
      u_rightSpeed.base = 0;
      u_rightSpeed.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rightSpeed.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->rightSpeed = u_rightSpeed.real;
      offset += sizeof(this->rightSpeed);
     return offset;
    }

    const char * getType(){ return "zuman_msgs/Speeds"; };
    const char * getMD5(){ return "e34042ec89931b05b0575ac436f3db56"; };

  };

}
#endif