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
          int divisions);
  void render();
  glm::vec3 getXYZ(glm::vec2 xy) const;

private:
  Shader& _shader;
  TerrainMesh _mesh;
  glm::vec3 _offset{ glm::vec3(0.0f) };
};

#endif
