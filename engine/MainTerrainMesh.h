#ifndef MAIN_TERRAIN_MESH_H
#define MAIN_TERRAIN_MESH_H

#include "SubTerrainMesh.h"
#include "TerrainMesh.h"

class MainTerrainMesh : public TerrainMesh
{
public:
  void render() override;
  void init(float bottomLeftX,
            float bottomLeftY,
            float topRightX,
            float topRightY,
            int divisions,
            float xyScale,
            float zScale) override;
  float getZ(float x, float y) const;
  glm::vec3 getRgbColor(float x, float y) const;
  static float plantsColor[3];
};

#endif
