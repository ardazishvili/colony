#ifndef SUB_TERRAIN_MESH_H
#define SUB_TERRAIN_MESH_H

#include <future>
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

using Cells = std::vector<std::pair<unsigned int, unsigned int>>;
struct LivingArea
{
  Cells cells;
  std::vector<glm::vec2> plants;
  CircularRegion region;
  glm::vec4 initRgba;
  std::future<void> future;
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
  void growLivingArea(std::shared_ptr<LivingArea> area, float radius);
  void updateLivingArea(std::shared_ptr<LivingArea> area);

  const static glm::vec4 SELECTION_COLOR;
  const static glm::vec4 DESELECTION_COLOR;

protected:
  void calculateIndices(int divisionsX,
                        int divisionsY,
                        unsigned int latticeWidth) override;

private:
  void reloadLivingArea(std::shared_ptr<LivingArea> area);
  void selectSubTerrainRegion(CircularRegion region, glm::vec4 rgba);

  LivingAreas _livingAreas;
};

#endif
