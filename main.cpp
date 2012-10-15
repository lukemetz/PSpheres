#include "Node.hpp"
#include <stdio.h>
#include <gts.h>
#include <sstream>

#include "utils.hpp"
#include "Vec3f.hpp"
#include "Algorithms.hpp"
using namespace psphere;

Node * biped();
Node * swimmer();

int main(int argc, char *argv[])
{
  Node * root = swimmer();

  for (int i=0; i < 10; ++i) {
    printf("On %d \n", i);
    std::ostringstream name;
    Node * modRoot = new Node(root);
    algorithms::addNoise(modRoot, .2);
    name << "Export." << i << ".stl";
    modRoot->fillNodes(.05);
    //printf(modRoot->treeDescription().c_str());
    printf("making surface\n");
    GtsSurface * surf = modRoot->generateChildSurfacePyrite();
    printf("rendering surface\n");
    write_surface_to_file(name.str(), surf);
    delete modRoot;
  }
}

Node * swimmer()
{
  Node * lower = new Node(Vec3f(0,-.5,1), .22);
  Node * root = new Node(Vec3f(0,.5,1), .22);
  Node * upper = new Node(Vec3f(0,1,1), .22);
  root->addChild(lower);
  root->addChild(upper);
  for (int flip=-1; flip < 2; flip+=2) {
    Node * fin = new Node(Vec3f(flip*.6,.5,1), .22);
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
