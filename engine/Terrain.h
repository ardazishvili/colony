#ifndef TERRAIN_H
#define TERRAIN_H

#include "Shader.h"
#include "TerrainMesh.h"

class Terrain
{
public:
  Terrain(Shader& shader,
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
  void selectSubTerrainRegion(RectangleRegion region, glm::vec4 rgba);
  std::shared_ptr<LivingArea> addLivingArea(CircularRegion region,
                                            glm::vec4 rgba);
  void updateLivingArea(std::shared_ptr<LivingArea> area);
  void deselect();

private:
  Shader& _shader;
  TerrainMesh _mesh;
  glm::vec3 _offset{ glm::vec3(0.0f) };
  float _xyScale;
  float _zScale;
};

#endif
