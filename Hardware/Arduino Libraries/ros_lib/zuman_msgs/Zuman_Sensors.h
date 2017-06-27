#ifndef _ROS_zuman_msgs_Zuman_Sensors_h
#define _ROS_zuman_msgs_Zuman_Sensors_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace zuman_msgs
{

  class Zuman_Sensors : public ros::Msg
  {
    public:
      typedef float _CompassAngle_type;
      _CompassAngle_type CompassAngle;
      typedef float _MPUAngle_type;
      _MPUAngle_type MPUAngle;
      typedef float _UltrasonicLeft_type;
      _UltrasonicLeft_type UltrasonicLeft;
      typedef float _UltrasonicRight_type;
      _UltrasonicRight_type UltrasonicRight;

    Zuman_Sensors():
      CompassAngle(0),
      MPUAngle(0),
      UltrasonicLeft(0),
      UltrasonicRight(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_CompassAngle;
      u_CompassAngle.real = this->CompassAngle;
      *(outbuffer + offset + 0) = (u_CompassAngle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_CompassAngle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_CompassAngle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_CompassAngle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->CompassAngle);
      union {
        float real;
        uint32_t base;
      } u_MPUAngle;
      u_MPUAngle.real = this->MPUAngle;
      *(outbuffer + offset + 0) = (u_MPUAngle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_MPUAngle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_MPUAngle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_MPUAngle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->MPUAngle);
      union {
        float real;
        uint32_t base;
      } u_UltrasonicLeft;
      u_UltrasonicLeft.real = this->UltrasonicLeft;
      *(outbuffer + offset + 0) = (u_UltrasonicLeft.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_UltrasonicLeft.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_UltrasonicLeft.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_UltrasonicLeft.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->UltrasonicLeft);
      union {
        float real;
        uint32_t base;
      } u_UltrasonicRight;
      u_UltrasonicRight.real = this->UltrasonicRight;
      *(outbuffer + offset + 0) = (u_UltrasonicRight.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_UltrasonicRight.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_UltrasonicRight.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_UltrasonicRight.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->UltrasonicRight);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_CompassAngle;
      u_CompassAngle.base = 0;
      u_CompassAngle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_CompassAngle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_CompassAngle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_CompassAngle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->CompassAngle = u_CompassAngle.real;
      offset += sizeof(this->CompassAngle);
      union {
        float real;
        uint32_t base;
      } u_MPUAngle;
      u_MPUAngle.base = 0;
      u_MPUAngle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_MPUAngle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_MPUAngle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_MPUAngle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->MPUAngle = u_MPUAngle.real;
      offset += sizeof(this->MPUAngle);
      union {
        float real;
        uint32_t base;
      } u_UltrasonicLeft;
      u_UltrasonicLeft.base = 0;
      u_UltrasonicLeft.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_UltrasonicLeft.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_UltrasonicLeft.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_UltrasonicLeft.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->UltrasonicLeft = u_UltrasonicLeft.real;
      offset += sizeof(this->UltrasonicLeft);
      union {
        float real;
        uint32_t base;
      } u_UltrasonicRight;
      u_UltrasonicRight.base = 0;
      u_UltrasonicRight.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_UltrasonicRight.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_UltrasonicRight.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_UltrasonicRight.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->UltrasonicRight = u_UltrasonicRight.real;
      offset += sizeof(this->UltrasonicRight);
     return offset;
    }

    const char * getType(){ return "zuman_msgs/Zuman_Sensors"; };
    const char * getMD5(){ return "8ab9b5da5ab92564433c84f4de69d6dc"; };

  };

}
#endif