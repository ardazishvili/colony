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
  void init(float bottomLeftX,
            float bottomLeftY,
            float topRightX,
            float topRightY,
            int divisions,
            float xyScale,
            float zScale);
  virtual void calculateHeights(unsigned int width,
                                float bottomLeftX,
                                float bottomLeftY,
                                float& min,
                                float& max) = 0;
  virtual void calculateColors(float min,
                               float max,
                               unsigned int width,
                               unsigned int augmentedWidth) = 0;
  void getSegmentVertices(glm::vec2 bottomLeft,
                          glm::vec2 topRight,
                          std::vector<VertexColor>& v,
                          int& divisions,
                          int& divisionsY,
                          unsigned int& latticeWidth);

protected:
  void calculateIndices(int divisionsX,
                        int divisionsY,
                        unsigned int latticeWidth);
  void calculateNormals(int width, unsigned int latticeWidth);

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
