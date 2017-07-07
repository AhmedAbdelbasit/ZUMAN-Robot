#ifndef _ROS_beginner_tutorials_HWInstruction_h
#define _ROS_beginner_tutorials_HWInstruction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace beginner_tutorials
{

  class HWInstruction : public ros::Msg
  {
    public:
      typedef uint8_t _instruction_type;
      _instruction_type instruction;
      typedef uint32_t _distance_type;
      _distance_type distance;
      typedef uint32_t _angle_type;
      _angle_type angle;

    HWInstruction():
      instruction(0),
      distance(0),
      angle(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->instruction >> (8 * 0)) & 0xFF;
      offset += sizeof(this->instruction);
      *(outbuffer + offset + 0) = (this->distance >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->distance >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->distance >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->distance >> (8 * 3)) & 0xFF;
      offset += sizeof(this->distance);
      *(outbuffer + offset + 0) = (this->angle >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->angle >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->angle >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->angle >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angle);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->instruction =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->instruction);
      this->distance =  ((uint32_t) (*(inbuffer + offset)));
      this->distance |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->distance |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->distance |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->distance);
      this->angle =  ((uint32_t) (*(inbuffer + offset)));
      this->angle |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->angle |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->angle |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->angle);
     return offset;
    }

    const char * getType(){ return "beginner_tutorials/HWInstruction"; };
    const char * getMD5(){ return "c6b2679d9f8aca32692984d49f32a283"; };

  };

}
#endif