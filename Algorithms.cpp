#include "Algorithms.hpp"
#include <limits.h>
#include <stdlib.h>
using namespace psphere;

void algorithms::addNoise(Node * node, float amount)
{
#define rval static_cast<float>(rand())/INT_MAX
  node->pos += Vec3f(rval, rval, rval);
#undef rval
  for (Node * child : node->children) {
    algorithms::addNoise(child, amount);
  }
}
