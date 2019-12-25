#ifndef MAIN_TERRAIN_MESH_H
#define MAIN_TERRAIN_MESH_H

#include "SubTerrainMesh.h"
#include "TerrainMesh.h"

class MainTerrainMesh : public TerrainMesh
{
public:
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
  void getSegmentObstaclesMap(glm::vec2 bottomLeft,
                              glm::vec2 topRight,
                              std::vector<bool>& m,
                              unsigned int& divisionsX,
                              unsigned int& divisionsY,
                              unsigned int& latticeWidth);

private:
  std::vector<bool> _obstaclesMap;
};

#endif
