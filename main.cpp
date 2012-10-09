#include "Node.hpp"
#include <stdio.h>
#include <gts.h>
#include "utils.hpp"
int main(int argc, char *argv[])
{
  Node * root = new Node(Vec3f(1,1,1), 1);
  Node * node = new Node(Vec3f(2,1,1), 1);
  Node * node2 = new Node(Vec3f(2, 2, 1), 1.5);

  root->addChild(node);
  node->addChild(node2);

  printf(node->description().c_str());
  printf(root->description().c_str());
  GtsSurface * surf = root->generateChildSurface();
  write_surface_to_file(argv[1], surf);
};


