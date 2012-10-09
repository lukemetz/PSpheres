#pragma once
#include <stdlib.h>
#include <vector>
#include <string>
#include "Vec3f.hpp"

#include <gts.h>

struct Node;

struct Node
{
  Node(Vec3f pos, float radius);
  Vec3f pos;
  float radius;
  Node * parent;
  void addChild(Node * node);
  GtsSurface * generateChildSurface();
  GtsSurface * generateSurface();
  std::vector<Node *> children;
  std::string description();
};
