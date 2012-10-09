#pragma once

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
};
