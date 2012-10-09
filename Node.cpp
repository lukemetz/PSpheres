#include <sstream>
#include "Node.hpp"
Node::Node(Vec3f pos, float radius)
{
  this->pos = pos;
  this->radius = radius;
}

void Node::addChild(Node * node)
{
  children.push_back(node);
  node->parent = this;
}

std::string Node::description()
{
  std::ostringstream stream;
  stream << "<Node pos:";
  stream << pos.x << ", " << pos.y << ", " << pos.z;
  stream << " radius:";
  stream << radius;
  stream << " children:" << children.size();
  stream << ">\n";
  return stream.str();
}

GtsSurface * Node::generateChildSurface() {
  GtsSurface * surface = generateSurface();
  if (children.size() == 0) {
    return surface;
  }
  GtsSurface * out = gts_surface_new (gts_surface_class (),
		       gts_face_class (),
		       gts_edge_class (),
		       gts_vertex_class ());
  for(Node * node : children) {
    GtsSurface * s = node->generateChildSurface();
    GNode * bb1 = gts_bb_tree_surface(surface);
    GNode * bb2 = gts_bb_tree_surface(s);

    GtsSurfaceInter * inter =
      gts_surface_inter_new(gts_surface_inter_class (),
                            surface, s, bb1, bb2, false, false);

    gts_surface_inter_boolean(inter, out, GTS_1_OUT_2);
    gts_surface_inter_boolean(inter, out, GTS_2_OUT_1);
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
  int level = 4;
  gts_surface_generate_sphere (surface, level);

  gts_surface_foreach_vertex (surface, (GtsFunc) gts_point_transform, matrix);
  gts_matrix_destroy(matrix);
  return surface;
}

