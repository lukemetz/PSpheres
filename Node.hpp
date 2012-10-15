#pragma once
#include <stdlib.h>
#include <vector>
#include <string>
#include "Vec3f.hpp"
#include <pyrite/VoxelData.h>
#include <gts.h>

using namespace psphere;
namespace psphere
{
  struct Node;
  struct Node
  {
  public:
    Node(Vec3f pos, float radius);
    Node(Node *node);
    ~Node();

    Vec3f pos;
    float radius;
    int type;
    Node * parent;

    void addChild(Node * node);
    void removeChild(Node * node);
    void detach();

    GtsSurface * generateChildSurfaceGts();
    GtsSurface * generateChildSurfacePyrite();
    std::vector<Node *> children;
    std::string description();
    std::string treeDescription();
    Node * fillNodes(float fill);
  private:
    GtsSurface * generateSurface();
    std::string treeDescriptionWithPre(std::string add, std::string current);
    void generateChildPyrite(pyrite::VoxelData * voxelData);
  };
};
