#ifndef TERRAIN_H
#define TERRAIN_H

#include "MainTerrainMesh.h"
#include "Shader.h"

class Terrain
{
public:
  Terrain(Shader& shader,
          Camera& camera,
          float bottomLeftX,
          float bottomLeftY,
          float topRightX,
          float topRightY,
          int divisions,
          float xyScale,
          float zScale);
  void render();
  void renderSub();
  glm::vec3 getXYZ(glm::vec2 xy) const;
  glm::vec3 getRgbColor(float x, float y) const;
  std::shared_ptr<LivingArea> addLivingArea(CircularRegion region,
                                            glm::vec4 rgba);
  void updateLivingArea(std::shared_ptr<LivingArea> area);
  void growLivingArea(std::shared_ptr<LivingArea> area, float radius);
  float getMaxXy() const;
  void getSegmentVertices(glm::vec2 bottomLeft,
                          glm::vec2 topRight,
                          std::vector<VertexColor>& v,
                          unsigned int& divisionsX,
                          unsigned int& divisionsY,
                          unsigned int& latticeWidth);
  void getSegmentObstaclesMap(glm::vec2 bottomLeft,
                              glm::vec2 topRight,
                              std::vector<bool>& m,
                              unsigned int& divisionsX,
                              unsigned int& divisionsY,
                              unsigned int& latticeWidth);
  float halfWidth() const;
  float halfHeight() const;

private:
  Shader& _shader;
  Camera& _camera;
  MainTerrainMesh _mainMesh;
  SubTerrainMesh _subMesh;
  glm::vec3 _offset{ glm::vec3(0.0f) };
  float _maxXy;
  float _xyScale;
  float _zScale;
};

#endif
