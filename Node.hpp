#pragma once
#include <stdlib.h>
#include <vector>
#include <string>
#include "Vec3f.hpp"

#include <gts.h>

struct Node;

struct Node
{
public:
  Node(Vec3f pos, float radius);
  Vec3f pos;
  float radius;
  Node * parent;
  void addChild(Node * node);
  void removeChild(Node * node);
  void detach();
  GtsSurface * generateChildSurface();
  std::vector<Node *> children;
  std::string description();
  std::string treeDescription();
  Node * fillNodes(float fill);
private:
  GtsSurface * generateSurface();
  std::string treeDescriptionWithPre(std::string add, std::string current);
};
