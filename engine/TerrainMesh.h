#ifndef TERRAIN_MESH_H
#define TERRAIN_MESH_H

#include "ModelMesh.h"

struct VertexColor
{
  glm::vec3 p;
  glm::vec3 normal;
  glm::vec4 color;
};

struct Region
{
  float x;
  float y;
  float width;
  float height;
};

class TerrainMesh
{
public:
  TerrainMesh();
  ~TerrainMesh();
  void render();
  void renderSub();
  void initTerrain(float bottomLeftX,
                   float bottomLeftY,
                   float topRightX,
                   float topRightY,
                   int divisions,
                   float xyScale,
                   float zScale);
  void deinit();
  float getZ(float x, float y) const;
  /* void updateColor(float x, float y); */
  void selectSubTerrainRegion(Region region, float alfa);
  void deselect();
  void updateColor(unsigned int index);
  std::vector<unsigned int> getVertices(glm::vec2 center, float radius);
  static float UPDATE_COLOR_SPEED;
  static float plantsColor[3];

private:
  void initSubTerrain(float bottomLeftX,
                      float bottomLeftY,
                      float topRightX,
                      float topRightY,
                      int divisions);

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

  std::vector<VertexColor> _vSub;
  std::vector<unsigned int> _indicesSub;
  unsigned int _latticeWidthSub;
  unsigned int _latticeHeightSub;
  float _xStepSub;
  float _yStepSub;
  GLuint _vaoSub;
  GLuint _vertexVboSub;
  GLuint _indicesEboSub;
  Region _lastSelected{ 0.0f, 0.0f, 0.0f, 0.0f };
};

template<typename T>
int sgn(T val)
{
  return (T(0) < val) - (val < T(0));
}

#endif
