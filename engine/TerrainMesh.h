#ifndef TERRAIN_MESH_H
#define TERRAIN_MESH_H

#include "ModelMesh.h"

struct VertexColor
{
  glm::vec3 p;
  glm::vec3 normal;
  glm::vec4 color;
};

struct RectangleRegion
{
  float x;
  float y;
  float width;
  float height;
};

struct CircularRegion
{
  float x;
  float y;
  float r;
};

struct LivingArea
{
  std::vector<std::pair<unsigned int, unsigned int>> cells;
  std::vector<glm::vec2> plants;
};

using LivingAreas = std::vector<std::shared_ptr<LivingArea>>;
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
  glm::vec3 getRgbColor(float x, float y) const;
  /* void updateColor(float x, float y); */
  void selectSubTerrainRegion(RectangleRegion region, glm::vec4 rgba);
  std::shared_ptr<LivingArea> addLivingArea(CircularRegion region,
                                            glm::vec4 rgba);
  void updateLivingArea(std::shared_ptr<LivingArea> area);
  void selectSubTerrainRegion(CircularRegion region, glm::vec4 rgba);
  void deselect();
  void updateColor(unsigned int index);
  std::vector<unsigned int> getVertices(glm::vec2 center, float radius);
  static float UPDATE_COLOR_SPEED;
  static float plantsColor[3];

  const static glm::vec4 SELECTION_COLOR;
  const static glm::vec4 DESELECTION_COLOR;
  const static glm::vec4 DEFAULT_BARRIER_COLOR;

private:
  void initSubTerrain(float bottomLeftX,
                      float bottomLeftY,
                      float topRightX,
                      float topRightY,
                      int divisions);
  void reloadLivingArea(std::shared_ptr<LivingArea> area);

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
  RectangleRegion _lastSelected{ 0.0f, 0.0f, 0.0f, 0.0f };
  LivingAreas _livingAreas;
};

#endif
