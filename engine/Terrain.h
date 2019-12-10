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
  glm::vec3 getXYZ(glm::vec2 xy) const;
  /* void updateColor(glm::vec2 xy); */
  void updateColor(unsigned int index);
  std::vector<unsigned int> getVertices(glm::vec2 center, float radius);

private:
  Shader& _shader;
  TerrainMesh _mesh;
  glm::vec3 _offset{ glm::vec3(0.0f) };
  float _xyScale;
  float _zScale;
};

#endif
