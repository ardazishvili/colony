#ifndef SUB_TERRAIN_MESH_H
#define SUB_TERRAIN_MESH_H

#include <memory>
#include <vector>

#include "TerrainMesh.h"
#include <glm/glm.hpp>

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
class SubTerrainMesh : public TerrainMesh
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
  std::shared_ptr<LivingArea> addLivingArea(CircularRegion region,
                                            glm::vec4 rgba);
  void updateLivingArea(std::shared_ptr<LivingArea> area);

  const static glm::vec4 SELECTION_COLOR;
  const static glm::vec4 DESELECTION_COLOR;

private:
  void reloadLivingArea(std::shared_ptr<LivingArea> area);
  void selectSubTerrainRegion(CircularRegion region, glm::vec4 rgba);

  RectangleRegion _lastSelected{ 0.0f, 0.0f, 0.0f, 0.0f };
  LivingAreas _livingAreas;
};

#endif
