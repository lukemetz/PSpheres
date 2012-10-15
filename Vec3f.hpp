#pragma once
#include <math.h>

namespace psphere
{
  struct Vec3f
  {
    float x, y, z;
    Vec3f(float x, float y, float z)
    {
      this->x = x;
      this->y = y;
      this->z = z;
    }
    Vec3f()
    {
      this->x = 0;
      this->y = 0;
      this->z = 0;
    }

    Vec3f operator-(const Vec3f& v)
    {
      return Vec3f(x-v.x, y-v.y, z-v.z);
    }

    Vec3f operator+(const Vec3f& v)
    {
      return Vec3f(x+v.x, y+v.y, z+v.z);
    }

    Vec3f operator*(const Vec3f& v)
    {
      return Vec3f(x*v.x, y*v.y, z*v.z);
    }

    Vec3f operator/(const Vec3f& v)
    {
      return Vec3f(x/v.x, y/v.y, z/v.z);
    }

    Vec3f operator*(float v)
    {
      return Vec3f(x*v, y*v, z*v);
    }

    Vec3f operator/(float v)
    {
      return Vec3f(x/v, y/v, z/v);
    }

    Vec3f & operator+=(const Vec3f& v)
    {
      this->x = this->x+v.x;
      this->y = this->y+v.y;
      this->z = this->z+v.z;
      return *this;
    }

    Vec3f & operator*=(const Vec3f& v)
    {
      this->x = this->x*v.x;
      this->y = this->y*v.y;
      this->z = this->z*v.z;
      return *this;
    }

    Vec3f & operator/=(const Vec3f& v)
    {
      this->x = this->x/v.x;
      this->y = this->y/v.y;
      this->z = this->z/v.z;
      return *this;
    }

    Vec3f & operator-=(const Vec3f& v)
    {
      this->x = this->x-v.x;
      this->y = this->y-v.y;
      this->z = this->z-v.z;
      return *this;
    }

    Vec3f & operator+=(const float v)
    {
      this->x = this->x+v;
      this->y = this->y+v;
      this->z = this->z+v;
      return *this;
    }

    Vec3f & operator-=(const float v)
    {
      this->x = this->x-v;
      this->y = this->y-v;
      this->z = this->z-v;
      return *this;
    }

    float length()
    {
      return sqrt(x*x+y*y+z*z);
    }

    Vec3f normalize()
    {
      return *this/length();
    }
  };
};
