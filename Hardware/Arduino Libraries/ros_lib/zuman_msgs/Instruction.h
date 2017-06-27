#ifndef _ROS_zuman_msgs_Instruction_h
#define _ROS_zuman_msgs_Instruction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace zuman_msgs
{

  class Instruction : public ros::Msg
  {
    public:
      typedef const char* _command_type;
      _command_type command;
      typedef float _arg1_type;
      _arg1_type arg1;
      typedef float _arg2_type;
      _arg2_type arg2;

    Instruction():
      command(""),
      arg1(0),
      arg2(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_command = strlen(this->command);
      varToArr(outbuffer + offset, length_command);
      offset += 4;
      memcpy(outbuffer + offset, this->command, length_command);
      offset += length_command;
      union {
        float real;
        uint32_t base;
      } u_arg1;
      u_arg1.real = this->arg1;
      *(outbuffer + offset + 0) = (u_arg1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_arg1.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_arg1.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_arg1.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->arg1);
      union {
        float real;
        uint32_t base;
      } u_arg2;
      u_arg2.real = this->arg2;
      *(outbuffer + offset + 0) = (u_arg2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_arg2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_arg2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_arg2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->arg2);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_command;
      arrToVar(length_command, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_command; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_command-1]=0;
      this->command = (char *)(inbuffer + offset-1);
      offset += length_command;
      union {
        float real;
        uint32_t base;
      } u_arg1;
      u_arg1.base = 0;
      u_arg1.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_arg1.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_arg1.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_arg1.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->arg1 = u_arg1.real;
      offset += sizeof(this->arg1);
      union {
        float real;
        uint32_t base;
      } u_arg2;
      u_arg2.base = 0;
      u_arg2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_arg2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_arg2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_arg2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->arg2 = u_arg2.real;
      offset += sizeof(this->arg2);
     return offset;
    }

    const char * getType(){ return "zuman_msgs/Instruction"; };
    const char * getMD5(){ return "22db7cf47707ed15d576c944473b1120"; };

  };

}
#endif