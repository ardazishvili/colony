#ifndef MAIN_TERRAIN_MESH_H
#define MAIN_TERRAIN_MESH_H

#include "SubTerrainMesh.h"
#include "TerrainMesh.h"

class MainTerrainMesh : public TerrainMesh
{
public:
  void render() override;
  void calculateHeights(unsigned int width,
                        float bottomLeftX,
                        float bottomLeftY,
                        float& min,
                        float& max) override;
  void calculateColors(float min,
                       float max,
                       unsigned int width,
                       unsigned int augmentedWidth) override;
  float getZ(float x, float y) const;
  glm::vec3 getRgbColor(float x, float y) const;
  static float plantsColor[3];
};

#endif
