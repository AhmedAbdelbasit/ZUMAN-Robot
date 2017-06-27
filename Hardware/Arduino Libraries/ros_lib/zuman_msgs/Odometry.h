#ifndef _ROS_zuman_msgs_Odometry_h
#define _ROS_zuman_msgs_Odometry_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace zuman_msgs
{

  class Odometry : public ros::Msg
  {
    public:
      typedef float _Xposition_type;
      _Xposition_type Xposition;
      typedef float _Yposition_type;
      _Yposition_type Yposition;
      typedef float _Angle_type;
      _Angle_type Angle;

    Odometry():
      Xposition(0),
      Yposition(0),
      Angle(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_Xposition;
      u_Xposition.real = this->Xposition;
      *(outbuffer + offset + 0) = (u_Xposition.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Xposition.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Xposition.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Xposition.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Xposition);
      union {
        float real;
        uint32_t base;
      } u_Yposition;
      u_Yposition.real = this->Yposition;
      *(outbuffer + offset + 0) = (u_Yposition.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Yposition.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Yposition.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Yposition.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Yposition);
      union {
        float real;
        uint32_t base;
      } u_Angle;
      u_Angle.real = this->Angle;
      *(outbuffer + offset + 0) = (u_Angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Angle);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_Xposition;
      u_Xposition.base = 0;
      u_Xposition.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Xposition.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Xposition.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Xposition.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Xposition = u_Xposition.real;
      offset += sizeof(this->Xposition);
      union {
        float real;
        uint32_t base;
      } u_Yposition;
      u_Yposition.base = 0;
      u_Yposition.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Yposition.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Yposition.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Yposition.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Yposition = u_Yposition.real;
      offset += sizeof(this->Yposition);
      union {
        float real;
        uint32_t base;
      } u_Angle;
      u_Angle.base = 0;
      u_Angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Angle = u_Angle.real;
      offset += sizeof(this->Angle);
     return offset;
    }

    const char * getType(){ return "zuman_msgs/Odometry"; };
    const char * getMD5(){ return "ee1e4ce83b8a1baeaf53ebedc6946f55"; };

  };

}
#endif