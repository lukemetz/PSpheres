#include <math.h>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include "utils.hpp"

void write_face (GtsTriangle * t, std::ofstream *file)
{
  GtsVertex * v1, * v2, * v3;
  GtsVector n;
  gts_triangle_vertices (t, &v1, &v2, &v3);
  gts_triangle_normal (t, &n[0], &n[1], &n[2]);
  gts_vector_normalize (n);
  *file << "facet normal " << n[0] << " " << n[1] << " " << n[2] << "\nouter loop\n";
  *file << "vertex " << GTS_POINT (v1)->x << " " << GTS_POINT (v1)->y << " " << GTS_POINT (v1)->z << "\n";
  *file << "vertex " << GTS_POINT (v2)->x << " " << GTS_POINT (v2)->y << " " << GTS_POINT (v2)->z << "\n";
  *file << "vertex " << GTS_POINT (v3)->x << " " << GTS_POINT (v3)->y << " " << GTS_POINT (v3)->z << "\n";
  *file << "endloop\nendfacet\n";
}

void write_surface_to_file(std::string filePath, GtsSurface * surface)
{
  std::ofstream file;
  file.open (filePath.c_str());
  int c = 0;
  file << "solid \n";
  gts_surface_foreach_face (surface, (GtsFunc) write_face, &file);
  file << "endsolid \n";

  file.close();
}
