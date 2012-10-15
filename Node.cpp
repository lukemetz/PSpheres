#include <sstream>
#include <algorithm>
#include "Node.hpp"

using namespace psphere;

Node::Node(Vec3f pos, float radius)
{
  this->pos = pos;
  this->radius = radius;
  this->type = 0;
  parent = nullptr;
}

Node::Node(Node * node)
{
  this->pos = node->pos;
  this->radius = node->radius;
  this->type = node->type;
  for (Node * child : node->children) {
    Node * temp = new Node(child);
    this->addChild(temp);
  }
}

Node::~Node()
{
  for (Node * child : children) {
    delete child;
  }
}

void Node::addChild(Node * node)
{
  children.push_back(node);
  node->parent = this;
}

void Node::removeChild(Node * node)
{
  auto iterator = std::find(children.begin(), children.end(), node);
  if (iterator != children.end()) {
    children.erase(iterator);
  }
  printf("Child size %d \n", children.size());
}

void Node::detach()
{
  parent->removeChild(this);
  parent = nullptr;
}

std::string Node::description()
{
  std::ostringstream stream;
  stream << "<Node pos:";
  stream << pos.x << ", " << pos.y << ", " << pos.z;
  stream << " radius:";
  stream << radius;
  stream << " children:" << children.size();
  stream << " type:" << type;
  stream << ">\n";
  return stream.str();
}

std::string Node::treeDescriptionWithPre(std::string add, std::string current)
{
  std::string ret = current + description();
  for (Node * n : children) {
    ret += n->treeDescriptionWithPre(add, current+add);
  }
  return ret;
}

std::string Node::treeDescription()
{
  return treeDescriptionWithPre("-", " ");
}

Node * Node::fillNodes(float fill)
{
  int origSize = children.size();
  for (int i=0; i < origSize; ++i) {
    Node *node = children[0];
    Vec3f diff = node->pos - this->pos;
    Vec3f direction = diff.normalize();
    int extraNodes = static_cast<int>(diff.length()/fill);
    extraNodes = abs(extraNodes)+1;

    Node * aboveNode = this;
    float movePerNode = diff.length()/extraNodes;
    float radiusPerNode = (node->radius - this->radius)/extraNodes;
    for (int i=1; i < extraNodes; i++) {
      Node * n = new Node(direction*movePerNode*i+this->pos, radiusPerNode*i+this->radius);
      aboveNode->addChild(n);
      n->type = 1;
      aboveNode = n;
    }

    node->detach();
    aboveNode->addChild(node);
    node->fillNodes(fill);
  }
}

GtsSurface * Node::generateChildSurfacePyrite()
{
  pyrite::VoxelData *v = new pyrite::VoxelData(Horde3D::Vec3f(3, 3, 3), 1.0/16.0);
  printf("init opencl \n");
  v->initOpenCl();
  printf("Generating \n");
  generateChildPyrite(v);
  printf("Running marching cube \n");
  return v->marchingCube();
}

void Node::generateChildPyrite(pyrite::VoxelData * voxelData)
{
  printf("Generating %s", this->description().c_str());
  voxelData->clAddSphere(Horde3D::Vec3f(pos.x+1.5, pos.y+1.5, pos.z), radius);
  printf("Done \n");
  for (Node * n : children) {
    printf("Generating loopin?\n");
    n->generateChildPyrite(voxelData);
  }
  printf("asdf \n");
}

GtsSurface * Node::generateChildSurfaceGts()
{
  GtsSurface * surface = generateSurface();
  if (children.size() == 0) {
    return surface;
  }
  GtsSurface * out = gts_surface_new (gts_surface_class (),
		       gts_face_class (),
		       gts_edge_class (),
		       gts_vertex_class ());
  for(Node * node : children) {
    GtsSurface * s = node->generateChildSurfaceGts();
    GNode * bb1 = gts_bb_tree_surface(surface);
    GNode * bb2 = gts_bb_tree_surface(s);
    printf("Failing on 1 %s", node->description().c_str());
    GtsSurfaceInter * inter =
      gts_surface_inter_new(gts_surface_inter_class (),
                            surface, s, bb1, bb2, false, false);

    gts_surface_inter_boolean(inter, out, GTS_1_OUT_2);
    gts_surface_inter_boolean(inter, out, GTS_2_OUT_1);
    gts_object_destroy(GTS_OBJECT(s));
    gts_object_destroy(GTS_OBJECT(inter));
    gts_object_destroy(GTS_OBJECT(bb1));
    gts_object_destroy(GTS_OBJECT(bb2));
  }
  return out;
}

GtsSurface * Node::generateSurface() {
  GtsMatrix * matrix = gts_matrix_identity(NULL);
  matrix[0][0] = matrix[1][1] = matrix[2][2] = radius;
  matrix[0][3] = this->pos.x;
  matrix[1][3] = this->pos.y;
  matrix[2][3] = this->pos.z;

  GtsSurface * surface = gts_surface_new (gts_surface_class (),
		       gts_face_class (),
		       gts_edge_class (),
		       gts_vertex_class ());
  int level = 3;
  gts_surface_generate_sphere (surface, level);

  gts_surface_foreach_vertex (surface, (GtsFunc) gts_point_transform, matrix);
  gts_matrix_destroy(matrix);
  return surface;
}

