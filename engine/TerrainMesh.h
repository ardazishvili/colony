#ifndef TERRAIN_MESH_H
#define TERRAIN_MESH_H

#include "ModelMesh.h"

struct VertexColor
{
  glm::vec3 p;
  glm::vec3 normal;
  glm::vec3 color;
};

class TerrainMesh
{
public:
  TerrainMesh();
  ~TerrainMesh();
  void render();
  void initTerrain(float bottomLeftX,
                   float bottomLeftY,
                   float topRightX,
                   float topRightY,
                   int divisions,
                   float xyScale,
                   float zScale);
  void deinit();
  float getZ(float x, float y) const;
  void updateColor(float x, float y);
  static float UPDATE_COLOR_SPEED;
  static float plantsColor[3];

private:
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
  GLuint _vao;
  GLuint _vertexVbo;
  GLuint _indicesEbo;
};

#endif
