#ifndef TERRAIN_MESH_H
#define TERRAIN_MESH_H

#include <vector>

#include <glm/glm.hpp>

#include "Mesh.h"

struct VertexColor
{
  glm::vec3 p;
  glm::vec3 normal;
  glm::vec4 color;
};

class TerrainMesh : public Mesh
{
public:
  virtual void render();
  virtual void init(float bottomLeftX,
                    float bottomLeftY,
                    float topRightX,
                    float topRightY,
                    int divisions,
                    float xyScale,
                    float zScale) = 0;

protected:
  std::vector<VertexColor> _v;
  std::vector<unsigned int> _indices;
  float _width;
  float _height;
  unsigned int _latticeWidth;
  unsigned int _latticeHeight;
  float _xStep;
  float _yStep;
  float _xyScale;
  float _zScale;
};

#endif
