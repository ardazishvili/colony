#ifndef SUB_TERRAIN_MESH_H
#define SUB_TERRAIN_MESH_H

#include <memory>
#include <vector>

/* #include "ModelMesh.h" */
#include "Mesh.h"
/* #include <GL/glew.h> */
#include <glm/glm.hpp>

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
class SubTerrainMesh : public Mesh
{
public:
  /* SubTerrainMesh(); */
  /* ~SubTerrainMesh(); */
  void render();
  void init(float bottomLeftX,
            float bottomLeftY,
            float topRightX,
            float topRightY,
            int divisions,
            float xyScale,
            float zScale);
  void selectSubTerrainRegion(RectangleRegion region, glm::vec4 rgba);
  std::shared_ptr<LivingArea> addLivingArea(CircularRegion region,
                                            glm::vec4 rgba);
  void updateLivingArea(std::shared_ptr<LivingArea> area);
  void deselect();

  const static glm::vec4 SELECTION_COLOR;
  const static glm::vec4 DESELECTION_COLOR;

private:
  /* void deinit(); */
  void reloadLivingArea(std::shared_ptr<LivingArea> area);
  void selectSubTerrainRegion(CircularRegion region, glm::vec4 rgba);

  float _xyScale;
  float _zScale;
  float _width;
  float _height;
  std::vector<VertexColor> _vSub;
  std::vector<unsigned int> _indicesSub;
  unsigned int _latticeWidthSub;
  unsigned int _latticeHeightSub;
  float _xStepSub;
  float _yStepSub;
  /* GLuint _vaoSub; */
  /* GLuint _vertexVboSub; */
  /* GLuint _indicesEboSub; */
  RectangleRegion _lastSelected{ 0.0f, 0.0f, 0.0f, 0.0f };
  LivingAreas _livingAreas;
};

#endif
