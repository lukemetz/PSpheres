#pragma once
#include <math.h>
struct Vec3f
{
  float x, y, z;
  Vec3f(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
  Vec3f() {
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

  Vec3f operator/(float v)
  {
    return Vec3f(x/v, y/v, y/z);
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
