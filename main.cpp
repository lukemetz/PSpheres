#include "Node.hpp"
#include <stdio.h>
#include <gts.h>
#include "utils.hpp"
#include "Vec3f.hpp"

using namespace psphere;

Node * biped();
Node * swimmer();

int main(int argc, char *argv[])
{
  Node * root = swimmer();
  root->fillNodes(.1);
  printf(root->treeDescription().c_str());
  GtsSurface * surf = root->generateChildSurfacePyrite();
  write_surface_to_file(argv[1], surf);
}

Node * swimmer()
{
  Node * lower = new Node(Vec3f(0,-.5,1), .3);
  Node * root = new Node(Vec3f(0,.5,1), .3);
  Node * upper = new Node(Vec3f(0,1,1), .3);
  root->addChild(lower);
  root->addChild(upper);
  for (int flip=-1; flip < 2; flip+=2) {
    Node * fin = new Node(Vec3f(flip*.6,.5,1), .3);
    root->addChild(fin);
  }
  return root;
}

Node * biped()
{
  Node * root = new Node(Vec3f(0, 0, 1), .3);
  Node * upper = new Node(Vec3f(0,0,1.7), .3);
  root->addChild(upper);
  for (int flip=-1; flip < 2; flip+=2) {
    printf("Testing %d \n", flip);
    Node * leg = new Node(Vec3f(flip*.3, 0, .5), .2);
    root->addChild(leg);

    Node * arm = new Node(Vec3f(flip*.3, 0, 1.5), .2);
    upper->addChild(arm);

    Node * hand = new Node(Vec3f(flip*.6, 0, 1.5), .2);
    arm->addChild(hand);
  }
  return root;
}
